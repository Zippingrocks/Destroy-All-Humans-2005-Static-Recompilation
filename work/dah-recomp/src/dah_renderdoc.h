#ifndef DAH_RENDERDOC_H
#define DAH_RENDERDOC_H
#include <stdint.h>

/* Optional, internal-only graphics diagnostics; no dependency when disabled. */
void dah_renderdoc_init(void);
void dah_renderdoc_begin(uint64_t host_frame, uint32_t guest_loop);
void dah_renderdoc_begin_effect(const char *label);
int dah_renderdoc_arm_next_frame(const char *label);
void dah_renderdoc_end(uint64_t host_frame, uint32_t guest_loop);
#endif
