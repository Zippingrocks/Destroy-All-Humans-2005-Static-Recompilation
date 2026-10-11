#ifndef DAH_RETAIL_RING_H
#define DAH_RETAIL_RING_H
#include <stdint.h>
#include <string.h>

typedef struct DahRetailRingCursor {
    uint32_t device,base,end,next;
    unsigned submitting;
} DahRetailRingCursor;
typedef void (*DahRetailRingSubmit)(void *opaque,uint32_t start,uint32_t dwords);

static void dah_retail_ring_reset(DahRetailRingCursor *cursor)
{
    memset(cursor,0,sizeof(*cursor));
}

/* The caller validates guest mappings. A PUT commits a complete prefix;
 * later commits submit only its suffix. Explicit resets identify buffer
 * reuse even when a new PUT has grown past the old cursor. No guest writes. */
static uint32_t dah_retail_ring_commit(DahRetailRingCursor *cursor,
    uint32_t device,uint32_t base,uint32_t end,uint32_t put,
    DahRetailRingSubmit submit,void *opaque)
{
    if(!cursor || !submit || !device || base>=end || put<base || put>end ||
       ((base|end|put)&3u) || cursor->submitting)return UINT32_MAX;
    if(cursor->device!=device || cursor->base!=base || cursor->end!=end){
        cursor->device=device;cursor->base=base;cursor->end=end;cursor->next=base;
    }
    /* An unannounced rewind is rejected rather than replaying commands. */
    if(cursor->next<base || cursor->next>put)return UINT32_MAX;
    uint32_t start=cursor->next,dwords=(put-start)/4u;
    if(!dwords)return 0;
    cursor->submitting=1;
    submit(opaque,start,dwords);
    cursor->next=put;
    cursor->submitting=0;
    return dwords;
}
#endif
