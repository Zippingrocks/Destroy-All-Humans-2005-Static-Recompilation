#include <windows.h>
#include <d3d11.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dah_renderdoc.h"
#include "../tools/parity/vendor/renderdoc-v1.43/renderdoc/api/app/renderdoc_app.h"

extern ID3D11Device *d3d8_GetD3D11Device(void);
extern int (*g_dah_renderdoc_arm_next_frame)(const char *label);
extern ptrdiff_t g_xbox_mem_offset;
static RENDERDOC_API_1_6_0 *capture_api;
static uint64_t requested_frame;
/* The guest clock is a 32-bit float.  Store the request in the same format so
 * a decimal spelling of the exact guest value cannot round a few billionths
 * above the last rendered sample when promoted to double. */
static float requested_cinematic_seconds;
static float black_cinematic_min_seconds;
static int cinematic_time_trigger;
static int capture_started;
static int capture_completed;
static uint32_t capture_count_before;
static volatile LONG capture_armed;
static volatile LONG capture_armed_delay;
static char capture_armed_label[128];

static int dah_renderdoc_guest_u32(uint32_t address,uint32_t *value)
{
    if(!value || address<0x10000u || address>0x08000000u-4u || !g_xbox_mem_offset)
        return 0;
    memcpy(value,(const void *)((uintptr_t)g_xbox_mem_offset+address),4u);
    return 1;
}

/* Read the verified retail cinematic list without changing guest state.  The
 * time trigger is intentionally evaluated at frame start, so RenderDoc sees
 * the complete first frame at or beyond the requested movie time. */
static int dah_renderdoc_cinematic_elapsed(float *elapsed,uint32_t *name_hash)
{
    uint32_t manager,node,object,vtable,state,bits;
    if(!elapsed || !dah_renderdoc_guest_u32(0x286784u,&manager) || !manager ||
       !dah_renderdoc_guest_u32(manager,&vtable) ||
       (vtable!=0x23611cu && vtable!=0x22a6b8u) ||
       !dah_renderdoc_guest_u32(manager+8u,&node) || node==manager+8u || !node ||
       !dah_renderdoc_guest_u32(node+8u,&object) || !object ||
       !dah_renderdoc_guest_u32(object,&vtable) ||
       (vtable!=0x236100u && vtable!=0x229fb4u) ||
       !dah_renderdoc_guest_u32(object+0x74u,&state) || state!=2u ||
       !dah_renderdoc_guest_u32(object+0x6cu,&bits))return 0;
    memcpy(elapsed,&bits,sizeof(*elapsed));
    if(!isfinite(*elapsed) || *elapsed<0.0f)return 0;
    if(name_hash && !dah_renderdoc_guest_u32(object+0x20u,name_hash))*name_hash=0;
    return 1;
}

void dah_renderdoc_init(void)
{
    const char *internal=getenv("DAH_INTERNAL_RUN");
    const char *setting=getenv("DAH_RENDERDOC_FRAME");
    const char *cinematic_setting=getenv("DAH_RENDERDOC_CINEMATIC_SECONDS");
    const char *path=getenv("DAH_RENDERDOC_PATH");
    const char *black_min_setting=getenv("DAH_RENDERDOC_BLACK_CINEMATIC_MIN_SECONDS");
    char *end=NULL;
    unsigned long long value=0;
    double cinematic_value=0.0;
    if(black_min_setting && *black_min_setting){
        char *black_min_end=NULL;
        double black_min_value=strtod(black_min_setting,&black_min_end);
        if(black_min_end!=black_min_setting && !*black_min_end &&
           isfinite(black_min_value) && black_min_value>=0.0 && black_min_value<=120.0)
            black_cinematic_min_seconds=(float)black_min_value;
    }
    if(!internal || strcmp(internal,"1"))return;
    if(setting && *setting)value=strtoull(setting,&end,10);
    if(cinematic_setting && *cinematic_setting){
        char *cinematic_end=NULL;
        cinematic_value=strtod(cinematic_setting,&cinematic_end);
        if(cinematic_end!=cinematic_setting && !*cinematic_end &&
           isfinite(cinematic_value) && cinematic_value>=0.0 && cinematic_value<=120.0)
            cinematic_time_trigger=1;
    }
    if((cinematic_time_trigger && value) ||
       (!cinematic_time_trigger && (!setting || !*setting || setting==end || *end || !value || value>1000000u)) || !path ||
       strlen(path)<3u || strlen(path)>=MAX_PATH || path[1]!=':' ||
       (path[2]!='/' && path[2]!='\\')){
        fprintf(stderr,"[DAH-RENDERDOC] specify one valid frame or cinematic second and an absolute capture path; disabled\n");return;
    }
    /* Load before D3D11 initialization so all resource creation is observed.
     * No Qt/UI executable, debugger injection, or desktop input is involved. */
    HMODULE module=LoadLibraryExW(L"C:\\Program Files\\RenderDoc\\renderdoc.dll",NULL,
        LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32);
    if(!module){fprintf(stderr,"[DAH-RENDERDOC] load failed error=%lu\n",GetLastError());return;}
    pRENDERDOC_GetAPI get_api=(pRENDERDOC_GetAPI)GetProcAddress(module,"RENDERDOC_GetAPI");
    if(!get_api || !get_api(eRENDERDOC_API_Version_1_6_0,(void**)&capture_api)){
        capture_api=NULL;fprintf(stderr,"[DAH-RENDERDOC] app API unavailable; disabled\n");return;
    }
    capture_api->SetFocusToggleKeys(NULL,0);
    capture_api->SetCaptureKeys(NULL,0);
    capture_api->MaskOverlayBits(0,0);
    capture_api->SetCaptureFilePathTemplate(path);
    g_dah_renderdoc_arm_next_frame=dah_renderdoc_arm_next_frame;
    requested_frame=value;
    requested_cinematic_seconds=(float)cinematic_value;
    if(cinematic_time_trigger)
        fprintf(stderr,"[DAH-RENDERDOC] enabled cinematic-seconds=%.6f path=%s; this run's timing is invalid for parity\n",cinematic_value,path);
    else
        fprintf(stderr,"[DAH-RENDERDOC] enabled frame=%llu path=%s; this run's timing is invalid for parity\n",value,path);
}

void dah_renderdoc_begin(uint64_t host_frame,uint32_t guest_loop)
{
    float cinematic_elapsed=0.0f;uint32_t cinematic_hash=0;
    int armed=InterlockedCompareExchange(&capture_armed,0,0)!=0;
    if(armed && InterlockedCompareExchange(&capture_armed_delay,0,0)>0){
        InterlockedDecrement(&capture_armed_delay);
        return;
    }
    int due=armed || (cinematic_time_trigger?
        (dah_renderdoc_cinematic_elapsed(&cinematic_elapsed,&cinematic_hash) &&
         cinematic_elapsed>=requested_cinematic_seconds):
        host_frame==requested_frame);
    if(!capture_api || !due || capture_started || capture_completed)return;
    if(capture_api->IsFrameCapturing()){
        fprintf(stderr,"[DAH-RENDERDOC] existing capture active; request skipped\n");return;
    }
    capture_count_before=capture_api->GetNumCaptures();
    capture_api->StartFrameCapture(d3d8_GetD3D11Device(),NULL);
    capture_started=capture_api->IsFrameCapturing()!=0;
    char title[128];
    if(armed)
        snprintf(title,sizeof(title),"%s host %llu",
                 capture_armed_label[0]?capture_armed_label:"DAH1 armed frame",host_frame);
    else if(cinematic_time_trigger)
        snprintf(title,sizeof(title),"DAH1 cinematic %.6f sec hash %08X host %llu",
                 cinematic_elapsed,cinematic_hash,host_frame);
    else
        snprintf(title,sizeof(title),"DAH1 native host frame %llu guest loop %u",host_frame,guest_loop);
    capture_api->SetCaptureTitle(title);
    if(capture_started)InterlockedExchange(&capture_armed,0);
    fprintf(stderr,"[DAH-RENDERDOC] begin host-frame=%llu guest-loop=%u cinematic-seconds=%.6f cinematic-hash=%08X active=%d\n",
        host_frame,guest_loop,cinematic_elapsed,cinematic_hash,capture_started);
}

int dah_renderdoc_arm_next_frame(const char *label)
{
    float cinematic_elapsed=0.0f;
    if(!capture_api || capture_started || capture_completed ||
       InterlockedCompareExchange(&capture_armed,0,0) ||
       !dah_renderdoc_cinematic_elapsed(&cinematic_elapsed,NULL) ||
       cinematic_elapsed<black_cinematic_min_seconds)return 0;
    snprintf(capture_armed_label,sizeof(capture_armed_label),"%s",
             label && *label ? label : "DAH1 armed frame");
    InterlockedExchange(&capture_armed,1);
    /* Pixel detection happens after the bad frame is rendered.  DAH's retail
     * presentation alternates render parity, so skip the immediately following
     * clean parity and capture the next occurrence of the same bad parity. */
    InterlockedExchange(&capture_armed_delay,2);
    fprintf(stderr,"[DAH-RENDERDOC] armed-next-frame label=%s\n",capture_armed_label);
    fflush(stderr);
    return 1;
}

void dah_renderdoc_begin_effect(const char *label)
{
    if(!capture_api || capture_started || capture_completed ||
       capture_api->IsFrameCapturing())return;
    capture_count_before=capture_api->GetNumCaptures();
    capture_api->StartFrameCapture(d3d8_GetD3D11Device(),NULL);
    capture_started=capture_api->IsFrameCapturing()!=0;
    capture_api->SetCaptureTitle(label && *label ? label : "DAH1 effect draw");
    fprintf(stderr,"[DAH-RENDERDOC] begin-effect label=%s active=%d\n",
        label && *label ? label : "DAH1 effect draw",capture_started);
}

void dah_renderdoc_end(uint64_t host_frame,uint32_t guest_loop)
{
    if(!capture_api || !capture_started)return;
    uint32_t ok=capture_api->EndFrameCapture(d3d8_GetD3D11Device(),NULL);
    capture_started=0;
    capture_completed=1;
    uint32_t count=capture_api->GetNumCaptures();
    char *path=NULL;uint32_t length=0;uint64_t timestamp=0;
    if(ok && count>capture_count_before &&
       capture_api->GetCapture(count-1u,NULL,&length,&timestamp) && length && length<=32768u){
        path=calloc((size_t)length+1u,1u);
        if(path && !capture_api->GetCapture(count-1u,path,&length,&timestamp)){
            free(path);path=NULL;
        }
    }
    fprintf(stderr,"[DAH-RENDERDOC] end host-frame=%llu guest-loop=%u success=%u captures=%u path=%s\n",
        host_frame,guest_loop,ok,count,path?path:"unavailable");
    free(path);
    fflush(stderr);
}
