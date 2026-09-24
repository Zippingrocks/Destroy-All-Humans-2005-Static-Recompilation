#ifndef DAH_FRAME_H
#define DAH_FRAME_H
#include <stdint.h>

/* Host service around one complete retail main-loop iteration. These helpers
 * do not call guest code or modify guest CPU registers. */
void dah_frame_begin(void);
void dah_frame_end(void);
uint32_t dah_retail_pushbuffer_commit(uint32_t device, uint32_t put);
void dah_retail_pushbuffer_reset(void);

#endif
