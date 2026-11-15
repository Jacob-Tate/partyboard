// Prints a symbolised stack trace to stderr when the game crashes (Windows only).
// The test harness captures stderr, so crashes in automated runs explain themselves.

#include "port/crashhandler.h"
#include "port/autotest.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dbghelp.h>

#include <cstdio>

namespace {

void print_frame(HANDLE process, DWORD64 address, int index) {
    char symbolBuffer[sizeof(SYMBOL_INFO) + 256];
    auto *symbol = reinterpret_cast<SYMBOL_INFO *>(symbolBuffer);
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = 255;

    IMAGEHLP_MODULE64 module{};
    module.SizeOfStruct = sizeof(module);
    const char *moduleName = SymGetModuleInfo64(process, address, &module) ? module.ModuleName : "?";

    DWORD64 symOffset = 0;
    const bool haveSym = SymFromAddr(process, address, &symOffset, symbol);

    IMAGEHLP_LINE64 line{};
    line.SizeOfStruct = sizeof(line);
    DWORD lineOffset = 0;
    const bool haveLine = SymGetLineFromAddr64(process, address, &lineOffset, &line);

    fprintf(stderr, "  #%02d %s!%s+0x%llx", index, moduleName, haveSym ? symbol->Name : "?",
            static_cast<unsigned long long>(haveSym ? symOffset : address - module.BaseOfImage));
    if (haveLine) {
        fprintf(stderr, "  (%s:%lu)", line.FileName, line.LineNumber);
    }
    fprintf(stderr, "\n");
}

bool is_fatal(DWORD code) {
    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION:
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    case EXCEPTION_DATATYPE_MISALIGNMENT:
    case EXCEPTION_ILLEGAL_INSTRUCTION:
    case EXCEPTION_IN_PAGE_ERROR:
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
    case EXCEPTION_PRIV_INSTRUCTION:
    case EXCEPTION_STACK_OVERFLOW:
        return true;
    default:
        return false;
    }
}

// Vectored, not SetUnhandledExceptionFilter: game code runs on libco coroutine stacks, which
// Windows' SEH unwinder can't walk, so an unhandled-exception filter is never reached.
LONG WINAPI on_crash(EXCEPTION_POINTERS *info) {
    static volatile LONG entered = 0;
    if (!is_fatal(info->ExceptionRecord->ExceptionCode)) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    if (InterlockedExchange(&entered, 1)) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    const EXCEPTION_RECORD *record = info->ExceptionRecord;
    fprintf(stderr, "\n[crash] exception 0x%08lx at %p", record->ExceptionCode, record->ExceptionAddress);
    if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record->NumberParameters >= 2) {
        fprintf(stderr, " (%s address %p)", record->ExceptionInformation[0] ? "writing" : "reading",
                reinterpret_cast<void *>(record->ExceptionInformation[1]));
    }
    fprintf(stderr, "\n");

    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
    SymInitialize(process, nullptr, TRUE);

    CONTEXT context = *info->ContextRecord;
    STACKFRAME64 frame{};
    frame.AddrPC.Offset = context.Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context.Rbp;
    frame.AddrFrame.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context.Rsp;
    frame.AddrStack.Mode = AddrModeFlat;
    for (int i = 0; i < 48; i++) {
        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread, &frame, &context, nullptr,
                         SymFunctionTableAccess64, SymGetModuleBase64, nullptr) ||
            frame.AddrPC.Offset == 0) {
            break;
        }
        print_frame(process, frame.AddrPC.Offset, i);
    }
    fflush(stderr);
    partyboard_autotest_shutdown();  // flush the checksum log up to the crash
    return EXCEPTION_CONTINUE_SEARCH;
}

}  // namespace

extern "C" void partyboard_crashhandler_install(void) { AddVectoredExceptionHandler(1, on_crash); }

#else

extern "C" void partyboard_crashhandler_install(void) {}

#endif
