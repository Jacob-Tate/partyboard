// Party Board single-file launcher (Windows).
//
// The game is an exe plus ~90 DLLs (one per game module) and a res folder, so it can't be one file by
// itself. tools/package_friends.py appends the whole build, compressed, to this small program. On start
// it unpacks that build once into %LOCALAPPDATA%\PartyBoard\builds\<build id>\ and runs partyboard.exe
// from there with the same command line. Later starts of the same build skip straight to running it.
// A new PartyBoard.exe has a new build id, so updating is just replacing the file; older unpacked builds
// are removed once nothing runs them. `PartyBoard.exe --uninstall` (or Shift held while starting it)
// deletes everything Party Board stores on the PC.
//
// Appended data layout (end of this exe):
//   [LZMS-compressed archive][u64 archive offset][u64 archive size][16 chars build id]["PBLAUNCH"]
// Archive (after decompression):
//   "PBPK0001" u32 count, then per file: u16 path length, UTF-8 path ('/' separators), u64 size, bytes.

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <compressapi.h>
#include <shellapi.h>
#include <shlobj.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace {

constexpr char kTrailerMagic[8] = {'P', 'B', 'L', 'A', 'U', 'N', 'C', 'H'};
constexpr char kArchiveMagic[8] = {'P', 'B', 'P', 'K', '0', '0', '0', '1'};
constexpr size_t kTrailerSize = 8 + 8 + 16 + 8;
constexpr wchar_t kTitle[] = L"Party Board";

[[noreturn]] void fail(const std::wstring &message)
{
    MessageBoxW(nullptr, message.c_str(), kTitle, MB_OK | MB_ICONERROR);
    ExitProcess(1);
}

std::wstring last_error_text()
{
    const DWORD code = GetLastError();
    wchar_t *buffer = nullptr;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   nullptr, code, 0, reinterpret_cast<wchar_t *>(&buffer), 0, nullptr);
    std::wstring text = buffer ? buffer : L"";
    LocalFree(buffer);
    while (!text.empty() && (text.back() == L'\n' || text.back() == L'\r' || text.back() == L' ')) {
        text.pop_back();
    }
    return text + L" (error " + std::to_wstring(code) + L")";
}

std::wstring widen(const char *text, size_t length)
{
    const int count = MultiByteToWideChar(CP_UTF8, 0, text, static_cast<int>(length), nullptr, 0);
    std::wstring result(static_cast<size_t>(count), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text, static_cast<int>(length), result.data(), count);
    return result;
}

bool read_at(HANDLE file, uint64_t offset, void *out, size_t size)
{
    LARGE_INTEGER position;
    position.QuadPart = static_cast<LONGLONG>(offset);
    if (!SetFilePointerEx(file, position, nullptr, FILE_BEGIN)) {
        return false;
    }
    auto *dst = static_cast<uint8_t *>(out);
    while (size > 0) {
        DWORD chunk = static_cast<DWORD>(size > (1u << 30) ? (1u << 30) : size);
        DWORD got = 0;
        if (!ReadFile(file, dst, chunk, &got, nullptr) || got == 0) {
            return false;
        }
        dst += got;
        size -= got;
    }
    return true;
}

bool write_file(const std::wstring &path, const uint8_t *data, uint64_t size)
{
    HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }
    bool ok = true;
    while (size > 0 && ok) {
        DWORD chunk = static_cast<DWORD>(size > (1u << 30) ? (1u << 30) : size);
        DWORD wrote = 0;
        ok = WriteFile(file, data, chunk, &wrote, nullptr) && wrote == chunk;
        data += chunk;
        size -= chunk;
    }
    return CloseHandle(file) && ok;
}

bool exists(const std::wstring &path)
{
    return GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

void create_parents(const std::wstring &path)
{
    for (size_t i = 0; i < path.size(); i++) {
        if ((path[i] == L'\\' || path[i] == L'/') && i > 2) {
            CreateDirectoryW(path.substr(0, i).c_str(), nullptr);
        }
    }
}

// Best effort: a folder still in use (a game from that build running) just stays.
void delete_tree(const std::wstring &dir)
{
    WIN32_FIND_DATAW data;
    HANDLE find = FindFirstFileW((dir + L"\\*").c_str(), &data);
    if (find != INVALID_HANDLE_VALUE) {
        do {
            const std::wstring name = data.cFileName;
            if (name == L"." || name == L"..") {
                continue;
            }
            const std::wstring child = dir + L"\\" + name;
            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                delete_tree(child);
            } else {
                SetFileAttributesW(child.c_str(), FILE_ATTRIBUTE_NORMAL);
                DeleteFileW(child.c_str());
            }
        } while (FindNextFileW(find, &data));
        FindClose(find);
    }
    RemoveDirectoryW(dir.c_str());
}

// Removes older versions (and their leftover unpack folders). Runs on every start: a version that was still
// running when an update arrived is cleaned up the next time. Folders of this build id are left alone, so a
// second launcher unpacking the same build at the same moment isn't disturbed.
void delete_other_builds(const std::wstring &buildsDir, const std::wstring &keep)
{
    WIN32_FIND_DATAW data;
    HANDLE find = FindFirstFileW((buildsDir + L"\\*").c_str(), &data);
    if (find == INVALID_HANDLE_VALUE) {
        return;
    }
    do {
        const std::wstring name = data.cFileName;
        if (name == L"." || name == L".." || name.compare(0, keep.size(), keep) == 0 ||
            !(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            continue;
        }
        // A running game's exe can't be deleted. Leave that version whole: it loads game modules from its
        // folder as it goes, so taking any of them away would crash it.
        const std::wstring dir = buildsDir + L"\\" + name;
        const std::wstring exe = dir + L"\\partyboard.exe";
        if (exists(exe) && !DeleteFileW(exe.c_str())) {
            continue;
        }
        delete_tree(dir);
    } while (FindNextFileW(find, &data));
    FindClose(find);
}

std::wstring known_folder(REFKNOWNFOLDERID id)
{
    PWSTR path = nullptr;
    if (FAILED(SHGetKnownFolderPath(id, 0, nullptr, &path))) {
        fail(L"Couldn't find your app data folder.");
    }
    std::wstring result = path;
    CoTaskMemFree(path);
    return result;
}

// PartyBoard.exe --uninstall (or Shift held while starting it): delete everything Party Board stores on
// this PC. The game keeps settings, memory card, online saves and logs in %APPDATA%\MarioPartyRD\Party Board,
// its GPU shader cache in %APPDATA%\Party Board, and this launcher unpacks it to %LOCALAPPDATA%\PartyBoard.
int uninstall()
{
    const std::wstring roaming = known_folder(FOLDERID_RoamingAppData);
    const std::wstring local = known_folder(FOLDERID_LocalAppData);
    const std::wstring folders[] = {
        local + L"\\PartyBoard",
        roaming + L"\\MarioPartyRD\\Party Board",
        roaming + L"\\Party Board",
    };
    std::wstring list;
    for (const auto &folder : folders) {
        if (exists(folder)) {
            list += L"\n  " + folder;
        }
    }
    if (list.empty()) {
        MessageBoxW(nullptr, L"Party Board has nothing stored on this PC.", kTitle, MB_OK | MB_ICONINFORMATION);
        return 0;
    }
    const std::wstring question =
        L"Delete everything Party Board stores on this PC?\n\nThis removes your settings, controller setup, "
        L"memory card, saved online parties and logs, and the unpacked game:\n" +
        list +
        L"\n\nYour Mario Party 4 disc image and this PartyBoard.exe are not touched. Close the game first.";
    if (MessageBoxW(nullptr, question.c_str(), kTitle, MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES) {
        return 0;
    }
    std::wstring leftovers;
    for (const auto &folder : folders) {
        delete_tree(folder);
        if (exists(folder)) {
            leftovers += L"\n  " + folder;
        }
    }
    RemoveDirectoryW((roaming + L"\\MarioPartyRD").c_str()); // only if now empty
    if (!leftovers.empty()) {
        MessageBoxW(nullptr,
                    (L"Some files couldn't be deleted (is the game still running?). Close it and try again, or "
                     L"delete these folders yourself:" +
                     leftovers)
                        .c_str(),
                    kTitle, MB_OK | MB_ICONWARNING);
        return 1;
    }
    MessageBoxW(nullptr, L"Done. Party Board's data has been removed from this PC.", kTitle, MB_OK | MB_ICONINFORMATION);
    return 0;
}

bool wants_uninstall()
{
    if (GetKeyState(VK_SHIFT) & 0x8000) {
        return true;
    }
    int count = 0;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &count);
    bool found = false;
    for (int i = 1; argv && i < count; i++) {
        found |= _wcsicmp(argv[i], L"--uninstall") == 0;
    }
    LocalFree(argv);
    return found;
}

void unpack(HANDLE self, uint64_t offset, uint64_t size, const std::wstring &target)
{
    std::vector<uint8_t> compressed(static_cast<size_t>(size));
    if (!read_at(self, offset, compressed.data(), compressed.size())) {
        fail(L"Couldn't read the game data inside this file: " + last_error_text());
    }
    DECOMPRESSOR_HANDLE decompressor = nullptr;
    if (!CreateDecompressor(COMPRESS_ALGORITHM_LZMS, nullptr, &decompressor)) {
        fail(L"Couldn't start the decompressor: " + last_error_text());
    }
    SIZE_T needed = 0;
    Decompress(decompressor, compressed.data(), compressed.size(), nullptr, 0, &needed);
    std::vector<uint8_t> archive(needed);
    if (needed == 0 || !Decompress(decompressor, compressed.data(), compressed.size(), archive.data(), archive.size(),
                                   &needed)) {
        fail(L"The game data inside this file is damaged. Please download it again.\n\n" + last_error_text());
    }
    CloseDecompressor(decompressor);
    compressed = {};

    const uint8_t *p = archive.data();
    const uint8_t *end = p + needed;
    auto take = [&](void *out, size_t n) {
        if (static_cast<size_t>(end - p) < n) {
            fail(L"The game data inside this file is damaged. Please download it again.");
        }
        std::memcpy(out, p, n);
        p += n;
    };
    char magic[8];
    take(magic, sizeof(magic));
    if (std::memcmp(magic, kArchiveMagic, sizeof(magic)) != 0) {
        fail(L"The game data inside this file is damaged. Please download it again.");
    }
    uint32_t count = 0;
    take(&count, sizeof(count));
    for (uint32_t i = 0; i < count; i++) {
        uint16_t pathLength = 0;
        take(&pathLength, sizeof(pathLength));
        std::string path(pathLength, '\0');
        take(path.data(), pathLength);
        uint64_t fileSize = 0;
        take(&fileSize, sizeof(fileSize));
        if (static_cast<uint64_t>(end - p) < fileSize || path.find("..") != std::string::npos) {
            fail(L"The game data inside this file is damaged. Please download it again.");
        }
        std::wstring out = target + L"\\" + widen(path.data(), path.size());
        for (auto &c : out) {
            if (c == L'/') {
                c = L'\\';
            }
        }
        create_parents(out);
        if (!write_file(out, p, fileSize)) {
            fail(L"Couldn't unpack the game to\n" + target + L"\n\n" + last_error_text());
        }
        p += fileSize;
    }
}

} // namespace

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    if (wants_uninstall()) {
        return uninstall();
    }

    wchar_t selfPath[MAX_PATH * 4];
    const DWORD selfLength = GetModuleFileNameW(nullptr, selfPath, static_cast<DWORD>(std::size(selfPath)));
    if (selfLength == 0 || selfLength >= std::size(selfPath)) {
        fail(L"Couldn't find this program's own file.");
    }
    HANDLE self = CreateFileW(selfPath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (self == INVALID_HANDLE_VALUE) {
        fail(L"Couldn't open this program's own file: " + last_error_text());
    }
    LARGE_INTEGER fileSize{};
    GetFileSizeEx(self, &fileSize);
    uint8_t trailer[kTrailerSize];
    if (static_cast<uint64_t>(fileSize.QuadPart) < kTrailerSize ||
        !read_at(self, static_cast<uint64_t>(fileSize.QuadPart) - kTrailerSize, trailer, kTrailerSize) ||
        std::memcmp(trailer + kTrailerSize - 8, kTrailerMagic, 8) != 0) {
        fail(L"This launcher has no game inside it (it must be built with tools/package_friends.py).");
    }
    uint64_t offset = 0;
    uint64_t size = 0;
    std::memcpy(&offset, trailer, 8);
    std::memcpy(&size, trailer + 8, 8);
    const std::wstring buildId = widen(reinterpret_cast<const char *>(trailer + 16), 16);

    const std::wstring buildsDir = known_folder(FOLDERID_LocalAppData) + L"\\PartyBoard\\builds";
    const std::wstring buildDir = buildsDir + L"\\" + buildId;
    const std::wstring exePath = buildDir + L"\\partyboard.exe";

    if (!exists(buildDir + L"\\.complete")) {
        create_parents(buildDir + L"\\");
        // Unpack beside the final folder and rename it into place, so two copies started at once (or one
        // interrupted half way) never leave a half-written build that looks finished.
        const std::wstring staging = buildsDir + L"\\" + buildId + L".unpacking-" + std::to_wstring(GetCurrentProcessId());
        delete_tree(staging);
        CreateDirectoryW(staging.c_str(), nullptr);
        unpack(self, offset, size, staging);
        write_file(staging + L"\\.complete", reinterpret_cast<const uint8_t *>("ok"), 2);
        if (exists(buildDir) && !exists(buildDir + L"\\.complete")) {
            delete_tree(buildDir);
        }
        if (!MoveFileExW(staging.c_str(), buildDir.c_str(), 0)) {
            delete_tree(staging); // another copy of the launcher finished first
            if (!exists(buildDir + L"\\.complete")) {
                fail(L"Couldn't unpack the game to\n" + buildDir + L"\n\n" + last_error_text());
            }
        }
    }
    CloseHandle(self);
    delete_other_builds(buildsDir, buildId);

    // Pass our command line on unchanged (minus our own program name).
    const wchar_t *args = GetCommandLineW();
    if (*args == L'"') {
        args++;
        while (*args && *args != L'"') {
            args++;
        }
        if (*args) {
            args++;
        }
    } else {
        while (*args && *args != L' ' && *args != L'\t') {
            args++;
        }
    }
    std::wstring commandLine = L"\"" + exePath + L"\"" + args;

    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    PROCESS_INFORMATION process{};
    if (!CreateProcessW(exePath.c_str(), commandLine.data(), nullptr, nullptr, FALSE, 0, nullptr, buildDir.c_str(),
                        &startup, &process)) {
        fail(L"Couldn't start the game:\n" + exePath + L"\n\n" + last_error_text());
    }
    AllowSetForegroundWindow(process.dwProcessId);
    CloseHandle(process.hThread);
    WaitForSingleObject(process.hProcess, INFINITE);
    DWORD exitCode = 0;
    GetExitCodeProcess(process.hProcess, &exitCode);
    CloseHandle(process.hProcess);
    return static_cast<int>(exitCode);
}
