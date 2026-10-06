#ifndef DAH_EVENT_TRACE_H
#define DAH_EVENT_TRACE_H

#include <stdint.h>

void dah_event_trace_initialize(const char *run_id, const char *started_utc,
                                uint64_t executable_hash);
void dah_event_trace_shutdown(void);
void dah_event_trace_ai_state(uint32_t manager, uint32_t owner,
                              uint32_t old_state, uint32_t new_state,
                              uint32_t old_id, uint32_t new_id,
                              uint32_t old_name, uint32_t new_name,
                              uint32_t caller);
void dah_event_trace_frame(uint64_t host_frame, uint32_t loop,
                           uint32_t interval_us, uint32_t target_us,
                           uint32_t logic_us, uint32_t render_us,
                           uint32_t present_us, uint32_t total_us,
                           uint32_t draw_count, uint32_t draw_delta,
                           uint32_t present_result, uint32_t flags);

#endif
