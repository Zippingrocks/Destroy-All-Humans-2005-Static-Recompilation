#ifndef DAH_FRAME_H
#define DAH_FRAME_H

/* Host service around one complete retail main-loop iteration. These helpers
 * do not call guest code or modify guest CPU registers. */
void dah_frame_begin(void);
void dah_frame_end(void);

#endif
