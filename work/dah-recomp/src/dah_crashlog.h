#ifndef DAH_CRASHLOG_H
#define DAH_CRASHLOG_H

#include <windows.h>

/* Install the dedicated, append-only crash recorder.  This is separate from
 * recomp.log/recomp_crash.log and never truncates either one. */
void dah_crashlog_initialize(const char *runtime_log_path);
LONG WINAPI dah_crashlog_unhandled(EXCEPTION_POINTERS *info);

#endif
