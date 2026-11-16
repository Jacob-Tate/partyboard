#!/usr/bin/env python3
"""Build the single-file Windows release for sharing: PartyBoard.exe (+ a short read-me).

PartyBoard.exe is the small launcher (CMake target partyboard-launcher) with the game appended to it:
partyboard.exe, every DLL it loads, the res folder and the Visual C++ runtime DLLs (so nobody has to
install anything). See platforms/windows/launcher/launcher.cpp for what happens when it runs.

Usage (after building the game and the launcher):
    python tools/package_friends.py [--build build/windows-msvc-relwithdebinfo] [--out build/package/friends]
"""

import argparse
import ctypes
import glob
import hashlib
import os
import shutil
import struct
import subprocess
import sys
from ctypes import wintypes

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

ARCHIVE_MAGIC = b"PBPK0001"
TRAILER_MAGIC = b"PBLAUNCH"
COMPRESS_ALGORITHM_LZMS = 5

# Visual C++ runtime DLLs the prebuilt dependencies (SDL3, Dawn, DXC, nod) import. Shipped app-local, as
# Microsoft allows, so PCs without the "VC++ Redistributable" still run the game.
CRT_DLLS = ["msvcp140.dll", "msvcp140_1.dll", "msvcp140_2.dll", "msvcp140_atomic_wait.dll",
            "vcruntime140.dll", "vcruntime140_1.dll"]

README = """\
Party Board
===========

You need: Windows 10 or 11 (64-bit), and your own Mario Party 4 (USA) disc image (.iso / .rvz / .gcm).

1. Run PartyBoard.exe. The first start takes a few seconds while it unpacks (later starts are instant).
   If Windows SmartScreen warns about it: More info > Run anyway.
2. Settings: choose your Mario Party 4 disc image, and set up your controller if needed.
3. Main menu > Play Online.
   - Server: the address you were given (e.g. 203.0.113.7:7845). Your Name: pick one and keep it,
     a continued game gives you your seat back by name.
   - Join a Game: type the 4-letter Room Code from the host, then Join Room.
   - Under Room, pick your character (and your port if you like). The host starts the game.

Good to know
  - Everyone must use the same PartyBoard.exe; the server rejects different versions.
  - If someone disconnects, a CPU takes over their player and the party goes on. To get back in, they
    join the same Room Code with the same name: after that round's minigame everyone's game restarts
    by itself (the window closes and reopens) and goes on with them back in their seat.
  - If your connection drops, the game restarts and gets you back in by itself (keep the small
    "Party Board" window open). If the games ever go out of sync, everyone's game restarts from the
    last save point the same way.
  - The taskbar button flashes when it's your turn or a minigame is about to start.
  - If the game stops to wait for someone, the window title says who.
  - START pauses the game for everyone.
  - Something went wrong? Settings > Interface > Open Data Folder, and send logs\\partyboard.log.

Updating
  Replace PartyBoard.exe with the new one. Your settings, controller setup and saves are kept;
  the old version is cleaned up automatically.

Removing everything
  Hold Shift while starting PartyBoard.exe (or run "PartyBoard.exe --uninstall") and confirm.
  This deletes all Party Board data on this PC: settings, memory card, saved online parties, logs
  and the unpacked game (in %APPDATA% and %LOCALAPPDATA%). Then delete PartyBoard.exe itself.
"""


def collect(build_dir):
    """Returns [(archive path, source path)] for everything the game needs at run time."""
    files = [("partyboard.exe", os.path.join(build_dir, "partyboard.exe"))]
    for dll in sorted(glob.glob(os.path.join(build_dir, "*.dll"))):
        files.append((os.path.basename(dll), dll))
    res = os.path.join(build_dir, "res")
    for folder, _, names in os.walk(res):
        for name in sorted(names):
            source = os.path.join(folder, name)
            files.append((os.path.relpath(source, build_dir).replace(os.sep, "/"), source))
    present = {name.lower() for name, _ in files}
    for name in CRT_DLLS:
        if name not in present:
            files.append((name, find_crt_dll(name)))
    for name, source in files:
        if not os.path.isfile(source):
            sys.exit(f"missing: {source}")
    return files


def find_crt_dll(name):
    vswhere = os.path.expandvars(r"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe")
    roots = []
    if os.path.isfile(vswhere):
        out = subprocess.run([vswhere, "-all", "-products", "*", "-property", "installationPath"],
                             capture_output=True, text=True).stdout
        roots = [line.strip() for line in out.splitlines() if line.strip()]
    candidates = []
    for root in roots:
        candidates += glob.glob(os.path.join(root, "VC", "Redist", "MSVC", "*", "x64", "Microsoft.VC*.CRT", name))
    if not candidates:
        sys.exit(f"can't find the Visual C++ runtime DLL {name} (install the VS 'C++ x64 tools')")
    return sorted(candidates)[-1]  # newest toolset


def build_archive(files):
    parts = [ARCHIVE_MAGIC, struct.pack("<I", len(files))]
    for name, source in files:
        with open(source, "rb") as f:
            data = f.read()
        encoded = name.encode("utf-8")
        parts += [struct.pack("<H", len(encoded)), encoded, struct.pack("<Q", len(data)), data]
    return b"".join(parts)


def lzms_compress(data):
    cabinet = ctypes.WinDLL("cabinet")
    cabinet.CreateCompressor.argtypes = [wintypes.DWORD, ctypes.c_void_p, ctypes.POINTER(ctypes.c_void_p)]
    cabinet.CreateCompressor.restype = wintypes.BOOL
    cabinet.Compress.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t, ctypes.c_void_p,
                                 ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t)]
    cabinet.Compress.restype = wintypes.BOOL
    cabinet.CloseCompressor.argtypes = [ctypes.c_void_p]
    handle = ctypes.c_void_p()
    if not cabinet.CreateCompressor(COMPRESS_ALGORITHM_LZMS, None, ctypes.byref(handle)):
        raise ctypes.WinError()
    try:
        source = ctypes.create_string_buffer(data, len(data))
        capacity = len(data) + len(data) // 8 + (1 << 20)
        out = ctypes.create_string_buffer(capacity)
        size = ctypes.c_size_t()
        if not cabinet.Compress(handle, source, len(data), out, capacity, ctypes.byref(size)):
            raise ctypes.WinError()
        return out.raw[:size.value]
    finally:
        cabinet.CloseCompressor(handle)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--build", default=os.path.join(ROOT, "build", "windows-msvc-relwithdebinfo"))
    parser.add_argument("--out", default=os.path.join(ROOT, "build", "package", "friends"))
    args = parser.parse_args()

    launcher = os.path.join(args.build, "partyboard-launcher.exe")
    if not os.path.isfile(launcher):
        sys.exit(f"build the launcher first (target partyboard-launcher): {launcher}")
    files = collect(args.build)
    archive = build_archive(files)
    build_id = hashlib.sha256(archive).hexdigest()[:16]
    print(f"{len(files)} files, {len(archive) / 1e6:.1f} MB; compressing (LZMS)...")
    compressed = lzms_compress(archive)

    if os.path.isdir(args.out):
        shutil.rmtree(args.out)
    os.makedirs(args.out)
    exe = os.path.join(args.out, "PartyBoard.exe")
    with open(launcher, "rb") as f:
        stub = f.read()
    with open(exe, "wb") as f:
        f.write(stub)
        f.write(compressed)
        f.write(struct.pack("<QQ", len(stub), len(compressed)))
        f.write(build_id.encode("ascii"))
        f.write(TRAILER_MAGIC)
    with open(os.path.join(args.out, "README.txt"), "w", newline="\r\n") as f:
        f.write(README)
    print(f"{exe}: {os.path.getsize(exe) / 1e6:.1f} MB, build id {build_id}")


if __name__ == "__main__":
    main()
