#ifndef DAH_TIMING_H
#define DAH_TIMING_H
#include <stdint.h>
/* Xbox CPU-cycle clock, independent of the PC CPU's TSC frequency. */
uint64_t dah_read_tsc(void);
#endif
