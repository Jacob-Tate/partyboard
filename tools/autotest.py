#!/usr/bin/env python3
"""Run Party Board quickstart games and check them for crashes, hangs and desyncs.

Each board is played `--runs` times with the same seed. Every run writes a per-frame
checksum log; runs of the same board are compared line by line, and the first frame
where they differ is reported along with the overlay (board or minigame) running then.

Example:
    python tools/autotest.py --exe build/windows-clang-relwithdebinfo/partyboard.exe
    python tools/autotest.py --exe ... --boards 0 3 --turns 5 --runs 3 --watch
"""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import time
from dataclasses import dataclass, field
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
BOARD_NAMES = [
    "Toad's Midway Madness",
    "Goomba's Greedy Gala",
    "Shy Guy's Jungle Jam",
    "Boo's Haunted Bash",
    "Koopa's Seaside Soiree",
    "Bowser's Gnarly Party",
]


def load_overlay_names() -> list[str]:
    """Overlay numbers -> DLL names, from the TARGET_PC section of include/ovl_table.h (USA build)."""
    names: list[str] = []
    stack: list[bool] = []  # whether each nested #if branch is active
    in_pc = False
    for line in (REPO / "include" / "ovl_table.h").read_text().splitlines():
        s = line.strip()
        if s.startswith("#ifdef TARGET_PC") and not in_pc:
            in_pc = True
            continue
        if not in_pc:
            continue
        if s.startswith("#if"):
            stack.append("VERSION_JP" not in s)
            continue
        if s.startswith("#else"):
            if not stack:
                break  # end of the TARGET_PC section
            stack[-1] = not stack[-1]
            continue
        if s.startswith("#endif"):
            if not stack:
                break
            stack.pop()
            continue
        if all(stack):
            m = re.match(r"DLL\((\w+)\)", s)
            if m:
                names.append(m.group(1))
    return names


OVERLAYS = load_overlay_names()


def ovl_name(num: int) -> str:
    return OVERLAYS[num] if 0 <= num < len(OVERLAYS) else f"overlay {num}"


@dataclass
class RunResult:
    board: int
    run: int
    status: str = "ok"  # ok | crash | hang | timeout | closed (window closed before the game ended)
    exit_code: int | None = None
    frames: int = 0
    last_ovl: int = -1
    games_finished: int = 0
    seconds: float = 0.0
    log: Path | None = None
    stdout: Path | None = None
    ovl_path: list[int] = field(default_factory=list)


def read_checksums(path: Path) -> tuple[list[tuple[int, int, str]], int]:
    """Returns ([(frame, ovl, rest-of-line)], games_finished)."""
    rows = []
    finished = 0
    if not path.exists():
        return rows, finished
    with path.open() as f:
        for line in f:
            if line.startswith("#"):
                if "finished" in line:
                    finished += 1
                continue
            parts = line.split()
            if len(parts) >= 5:
                rows.append((int(parts[0]), int(parts[1]), " ".join(parts[2:])))
    return rows, finished


def run_once(args, board: int, run: int, out: Path) -> RunResult:
    res = RunResult(board=board, run=run)
    res.log = out / f"board{board}_run{run}.checksums"
    res.stdout = out / f"board{board}_run{run}.stdout.txt"
    cmd = [
        str(args.exe), "--quickstart",
        "--board", str(board),
        "--turns", str(args.turns),
        "--seed", str(args.seed),
        "--cpu-level", str(args.cpu_level),
        "--checksum-log", str(res.log),
        # Fresh settings/memory-card folder per run, so a local save can't change the game.
        "--config-dir", str(out / f"board{board}_run{run}.config"),
        "--iso", str(args.iso),
    ]
    if not args.watch:
        cmd.append("--fast")
    if args.max_frames:
        cmd += ["--max-frames", str(args.max_frames)]
    if args.dump_frame:
        cmd += ["--dump-frame", str(args.dump_frame)]

    start = time.monotonic()
    last_size, last_growth = -1, start
    with res.stdout.open("w", errors="replace") as so:
        proc = subprocess.Popen(cmd, cwd=Path(args.exe).parent, stdout=so, stderr=subprocess.STDOUT)
        while True:
            code = proc.poll()
            now = time.monotonic()
            if code is not None:
                res.exit_code = code
                if code != 0:
                    res.status = "crash"
                break
            size = res.log.stat().st_size if res.log.exists() else 0
            if size != last_size:
                last_size, last_growth = size, now
            elif now - last_growth > args.hang_seconds:
                res.status = "hang"
                proc.kill()
                break
            if now - start > args.timeout:
                res.status = "timeout"
                proc.kill()
                break
            time.sleep(0.5)
        proc.wait()
    res.seconds = time.monotonic() - start

    rows, res.games_finished = read_checksums(res.log)
    if res.status == "ok" and res.games_finished == 0:
        if "reached --max-frames" not in res.stdout.read_text(errors="replace"):
            res.status = "closed"
    if rows:
        res.frames = rows[-1][0]
        res.last_ovl = rows[-1][1]
        for _, ovl, _ in rows:
            if not res.ovl_path or res.ovl_path[-1] != ovl:
                res.ovl_path.append(ovl)
    return res


def compare(a: RunResult, b: RunResult) -> dict | None:
    """First differing frame between two runs, or None if they agree over their common length."""
    ra, _ = read_checksums(a.log)
    rb, _ = read_checksums(b.log)
    for (fa, oa, xa), (fb, ob, xb) in zip(ra, rb):
        if (fa, oa, xa) != (fb, ob, xb):
            fields = ["frand", "rand8", "boardrand", "system", "players", "playercfg"]
            va, vb = xa.split(), xb.split()
            diff = [n for n, x, y in zip(fields, va, vb) if x != y]
            if oa != ob:
                diff.insert(0, "overlay")
            return {"frame": fa, "overlay_a": ovl_name(oa), "overlay_b": ovl_name(ob), "fields": diff}
    if len(ra) != len(rb) and a.status == b.status == "ok" and not a.games_finished == b.games_finished:
        return {"frame": min(len(ra), len(rb)), "overlay_a": "-", "overlay_b": "-", "fields": ["length"]}
    return None


def main() -> int:
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("--exe", type=Path, required=True, help="path to partyboard.exe")
    p.add_argument("--iso", type=Path, help="disc image (default: the one saved in the game's normal config)")
    p.add_argument("--boards", type=int, nargs="+", default=list(range(6)), help="boards 0-5 (default all)")
    p.add_argument("--turns", type=int, default=5)
    p.add_argument("--runs", type=int, default=2, help="runs per board to compare (default 2)")
    p.add_argument("--seed", type=int, default=1234)
    p.add_argument("--cpu-level", type=int, default=1)
    p.add_argument("--max-frames", type=int, default=0, help="stop each run after this many frames")
    p.add_argument("--dump-frame", type=int, default=0, help="hex-dump hashed state at this frame in each log")
    p.add_argument("--hang-seconds", type=float, default=60, help="no new frames for this long = hang")
    p.add_argument("--timeout", type=float, default=1800, help="max seconds per run")
    p.add_argument("--watch", action="store_true", help="run at normal speed (no --fast) so you can watch")
    p.add_argument("--out", type=Path, default=REPO / "build" / "autotest", help="output directory")
    args = p.parse_args()

    args.exe = args.exe.resolve()
    if args.iso is None:
        # Fall back to the disc image saved in the game's normal config.
        cfg = Path(os.environ.get("APPDATA", "")) / "MarioPartyRD" / "Party Board" / "config.json"
        try:
            args.iso = Path(json.loads(cfg.read_text())["backend.isoPath"])
        except (OSError, KeyError, ValueError):
            print("No --iso given and no disc image saved in the game's config", file=sys.stderr)
            return 2
    if not args.exe.exists():
        print(f"exe not found: {args.exe}", file=sys.stderr)
        return 2
    stamp = time.strftime("%Y%m%d-%H%M%S")
    out = (args.out / stamp).resolve()
    out.mkdir(parents=True, exist_ok=True)
    print(f"Writing logs to {out}")

    results: list[RunResult] = []
    desyncs: list[dict] = []
    for board in args.boards:
        board_runs = []
        for run in range(1, args.runs + 1):
            label = f"board {board} ({BOARD_NAMES[board]}) run {run}/{args.runs}"
            print(f"  {label} ...", end="", flush=True)
            r = run_once(args, board, run, out)
            board_runs.append(r)
            results.append(r)
            print(f" {r.status}: {r.frames} frames, {r.games_finished} game(s) finished, "
                  f"last in {ovl_name(r.last_ovl)}, {r.seconds:.0f}s")
        for other in board_runs[1:]:
            d = compare(board_runs[0], other)
            if d:
                d.update(board=board, runs=[board_runs[0].run, other.run])
                desyncs.append(d)
                print(f"    DESYNC run 1 vs run {other.run} at frame {d['frame']} "
                      f"in {d['overlay_a']}: {', '.join(d['fields'])} differ")
            else:
                print(f"    run 1 and run {other.run} match")

    problems = [r for r in results if r.status != "ok"]
    print("\nSummary")
    print(f"  runs: {len(results)}, crashes/hangs/timeouts: {len(problems)}, desyncs: {len(desyncs)}")
    for r in problems:
        print(f"  {r.status.upper()}: board {r.board} run {r.run} at frame {r.frames} in {ovl_name(r.last_ovl)} "
              f"(exit {r.exit_code}); see {r.stdout.name}")
    summary = {
        "args": {k: str(v) for k, v in vars(args).items()},
        "runs": [{**{k: (str(v) if isinstance(v, Path) else v) for k, v in r.__dict__.items()},
                  "last_ovl_name": ovl_name(r.last_ovl),
                  "ovl_path_names": [ovl_name(o) for o in r.ovl_path]} for r in results],
        "desyncs": desyncs,
    }
    (out / "summary.json").write_text(json.dumps(summary, indent=2))
    return 1 if problems or desyncs else 0


if __name__ == "__main__":
    sys.exit(main())
