// Log file and console hookup (port/log_file.h).
//
// stdout and stderr (file descriptors 1 and 2, and the Win32 std handles) are pointed at a pipe; a thread copies
// the pipe to the log file and to wherever the output went before (the terminal or a redirect), so nothing changes
// for whoever was reading the console.

#include "port/log_file.h"

#include <chrono>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <string>
#include <system_error>
#include <thread>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#define pb_dup _dup
#define pb_dup2 _dup2
#define pb_read _read
#define pb_write _write
#define pb_close _close
#else
#include <unistd.h>
#define pb_dup dup
#define pb_dup2 dup2
#define pb_read read
#define pb_write write
#define pb_close close
#endif

namespace {

FILE *gLog = nullptr;
int gPipeRead = -1;
int gOriginalOut = -1; // where fd 1 went before (console or redirect), or -1

void copy_loop()
{
    char buf[4096];
    for (;;) {
        const int n = pb_read(gPipeRead, buf, sizeof(buf));
        if (n <= 0) {
            break;
        }
        if (gOriginalOut >= 0) {
            pb_write(gOriginalOut, buf, static_cast<unsigned>(n));
        }
        std::fwrite(buf, 1, static_cast<size_t>(n), gLog);
        std::fflush(gLog);
    }
}

// partyboard.log -> partyboard.1.log -> partyboard.2.log
void rotate(const std::filesystem::path &dir)
{
    std::error_code ec;
    const auto log = [&](int i) { return dir / (i == 0 ? "partyboard.log" : "partyboard." + std::to_string(i) + ".log"); };
    std::filesystem::remove(log(2), ec);
    std::filesystem::rename(log(1), log(2), ec);
    std::filesystem::rename(log(0), log(1), ec);
}

} // namespace

extern "C" void partyboard_log_console_setup(void)
{
#ifdef _WIN32
    // A GUI program has no std handles unless its parent redirected them. Started from a terminal, write there.
    const HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (out == nullptr || out == INVALID_HANDLE_VALUE || GetFileType(out) == FILE_TYPE_UNKNOWN) {
        if (AttachConsole(ATTACH_PARENT_PROCESS)) {
            FILE *f;
            freopen_s(&f, "CONOUT$", "w", stdout);
            freopen_s(&f, "CONOUT$", "w", stderr);
            std::printf("\n");
        } else {
            FILE *f;
            freopen_s(&f, "NUL", "w", stdout);
            freopen_s(&f, "NUL", "w", stderr);
        }
    }
#endif
}

extern "C" int partyboard_log_file_start(const char *dirName)
{
    if (gLog != nullptr || dirName == nullptr) {
        return gLog != nullptr;
    }
    const std::filesystem::path dir = std::filesystem::u8path(dirName);
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    rotate(dir);
    gLog = std::fopen((dir / "partyboard.log").string().c_str(), "wb");
    if (gLog == nullptr) {
        return 0;
    }
    {
        const std::time_t now = std::time(nullptr);
        char stamp[64];
        std::strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        std::fprintf(gLog, "Party Board log, started %s\n", stamp);
        std::fflush(gLog);
    }

    int fds[2];
#ifdef _WIN32
    if (_pipe(fds, 64 * 1024, _O_BINARY) != 0) {
#else
    if (pipe(fds) != 0) {
#endif
        return 1; // the file has the header; nothing else will reach it
    }
    std::fflush(stdout);
    std::fflush(stderr);
    gOriginalOut = _fileno(stdout) >= 0 ? pb_dup(_fileno(stdout)) : -1;
    gPipeRead = fds[0];
    pb_dup2(fds[1], 1);
    pb_dup2(fds[1], 2);
#ifdef _WIN32
    // A GUI process starts without descriptors 0-2, so when partyboard_log_console_setup reopened stdout and
    // stderr (to NUL or the console) they got whatever descriptors were free, often not 1 and 2.
    if (_fileno(stdout) >= 0 && _fileno(stdout) != 1) {
        pb_dup2(fds[1], _fileno(stdout));
    }
    if (_fileno(stderr) >= 0 && _fileno(stderr) != 2) {
        pb_dup2(fds[1], _fileno(stderr));
    }
#endif
    pb_close(fds[1]);
    // Unbuffered: a crash loses nothing still sitting in a stdio buffer.
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    std::setvbuf(stderr, nullptr, _IONBF, 0);
#ifdef _WIN32
    SetStdHandle(STD_OUTPUT_HANDLE, reinterpret_cast<HANDLE>(_get_osfhandle(1)));
    SetStdHandle(STD_ERROR_HANDLE, reinterpret_cast<HANDLE>(_get_osfhandle(2)));
#endif
    std::thread(copy_loop).detach();
    std::printf("[log] writing %s\n", (dir / "partyboard.log").string().c_str());
    return 1;
}

extern "C" void partyboard_log_file_flush(void)
{
    if (gLog == nullptr || gPipeRead < 0) {
        return;
    }
#ifdef _WIN32
    const HANDLE pipe = reinterpret_cast<HANDLE>(_get_osfhandle(gPipeRead));
    for (int i = 0; i < 50; i++) {
        DWORD avail = 0;
        if (!PeekNamedPipe(pipe, nullptr, 0, nullptr, &avail, nullptr) || avail == 0) {
            break;
        }
        Sleep(10);
    }
    Sleep(20); // the last chunk read may still be on its way to the file
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
#endif
}
