#ifndef PORT_LOG_FILE_H
#define PORT_LOG_FILE_H

// Log file: everything the game prints (stdout and stderr, including crash reports) also goes to
// <user dir>/logs/partyboard.log; the previous two runs are kept as partyboard.1.log and partyboard.2.log.
// Settings > Advanced > Write Log File turns it off. Idea from the FIZL0/partyboard fork (N109/N145).
//
// partyboard.exe is a Windows GUI program (no console window of its own). Started from a terminal it prints
// there as before; started by double-click its output goes only to the log file.

#ifdef __cplusplus
extern "C" {
#endif

// First thing at startup: hook stdout/stderr up to the parent's console when there is one (Windows GUI exe).
void partyboard_log_console_setup(void);
// After the settings load: start writing the log under `dir` (if the setting is on). Returns 1 if logging.
int partyboard_log_file_start(const char *dir);
// Waits (up to ~0.5 s) until everything printed so far has reached the log file. Used by the crash handler.
void partyboard_log_file_flush(void);

#ifdef __cplusplus
}
#endif

#endif
