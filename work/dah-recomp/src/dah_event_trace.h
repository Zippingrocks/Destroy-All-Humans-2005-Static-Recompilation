#ifndef DAH_EVENT_TRACE_H
#define DAH_EVENT_TRACE_H

#include <stdint.h>

void dah_event_trace_initialize(void);
void dah_event_trace_shutdown(void);
void dah_event_trace_ai_state(uint32_t manager, uint32_t owner,
                              uint32_t old_state, uint32_t new_state,
                              uint32_t old_id, uint32_t new_id,
                              uint32_t old_name, uint32_t new_name,
                              uint32_t caller);

#endif
