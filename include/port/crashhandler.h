#ifndef PORT_CRASHHANDLER_H
#define PORT_CRASHHANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

// Installs a handler that prints a symbolised stack trace to stderr on a crash (Windows).
void partyboard_crashhandler_install(void);

#ifdef __cplusplus
}
#endif

#endif
