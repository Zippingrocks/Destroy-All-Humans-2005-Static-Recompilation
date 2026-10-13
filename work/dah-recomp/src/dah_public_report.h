#ifndef DAH_PUBLIC_REPORT_H
#define DAH_PUBLIC_REPORT_H

#include <stdint.h>
#include <windows.h>

/* Public reports are deliberately separate from debug-runs/ and crashlog/.
 * They contain only explicitly allowlisted game diagnostics. */
void dah_public_report_initialize(uint64_t executable_hash);
void dah_public_report_shutdown(void);
void dah_public_report_session(const char *status);
void dah_public_report_crash(const char *signature, DWORD exception_code,
                             uint64_t host_rva, ULONG_PTR access,
                             uint32_t guest_return);
int dah_public_report_set_consent(int crash_reports, int session_reports);
void dah_public_report_get_consent(int *crash_reports, int *session_reports);
int dah_public_report_open_issue(void);
const char *dah_public_report_path(void);

#endif
