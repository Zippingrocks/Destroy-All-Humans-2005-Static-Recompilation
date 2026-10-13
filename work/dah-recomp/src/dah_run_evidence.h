#ifndef DAH_RUN_EVIDENCE_H
#define DAH_RUN_EVIDENCE_H

#include <stddef.h>
#include <stdint.h>

int dah_run_evidence_initialize(const char *run_id, const char *started_utc,
                                uint64_t executable_hash);
const char *dah_run_evidence_directory(void);
int dah_run_evidence_path(char *destination, size_t capacity,
                          const char *filename);
void dah_run_evidence_update_status(const char *status,
                                    const char *log_path,
                                    const char *event_path);

#endif
