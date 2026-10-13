/* Production translated bodies and SEH helpers are included by the runner.
 * Mocks implement only called routine ABIs; expectations follow retail bytes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static uint8_t ram[0x300000];
#define MEM32(a) (*(uint32_t *)(ram + (uint32_t)(a)))
#define MEM8(a) (*(uint8_t *)(ram + (uint32_t)(a)))
#define PUSH32(s,v) do { (s) -= 4; MEM32(s) = (uint32_t)(v); } while (0)
#define POP32(s,v) do { (v) = MEM32(s); (s) += 4; } while (0)
#define CMP_A(a,b) ((uint32_t)(a) > (uint32_t)(b))
#define CMP_EQ(a,b) ((a) == (b))
#define CMP_NE(a,b) ((a) != (b))
#define CMP_GE(a,b) ((int32_t)(a) >= (int32_t)(b))
#define CMP_L(a,b) ((int32_t)(a) < (int32_t)(b))
#define TEST_Z(a,b) (((a) & (b)) == 0)
#define TEST_NZ(a,b) (((a) & (b)) != 0)
static uint32_t eax, ebx, ecx, edx, esi, edi, esp, g_ebp, g_seh_ebp;
static unsigned cases, checks, locks, unlocks, allocations, retries, frees, closes;
static unsigned fail_allocations, allow_retries;
static uint32_t requested, freed_mask, closed_mask;
#define CHECK(c) do { ++checks; if (!(c)) { fprintf(stderr,"FAIL case=%u line=%u %s\n", cases, __LINE__, #c); exit(1); } } while (0)
static void clobber(void) { ecx=edx=0xDEADBEEF; g_seh_ebp=0xA000; }
static void sub_0013F049(void) { eax=0x6000; clobber(); esp+=4; }
static void sub_00140C99(void) { CHECK(MEM32(esp+4)==1); ++locks; clobber(); esp+=4; }
static void sub_00140BE7(void) { CHECK(MEM32(esp+4)==1); ++unlocks; clobber(); esp+=4; }
static void sub_000B4342(void) { CHECK(MEM32(esp)==0x13CA40); eax=0xBEEF; clobber(); esp+=4; }
static void sub_000B632D(void)
{
    CHECK(MEM32(esp)==0x13CA46 && MEM32(esp+4)==0xBEEF);
    CHECK(MEM32(esp+8)==0 && MEM32(esp+12)==0x4444 && MEM32(esp+16)==requested);
    ++allocations; eax=allocations<=fail_allocations?0:0x123400; clobber(); esp+=20;
}
static void sub_00140CC7(void)
{
    CHECK(MEM32(esp)==0x13CA58 && MEM32(esp+4)==requested);
    ++retries; CHECK(retries<8); eax=retries<=allow_retries; clobber(); esp+=4;
}
static void sub_00142B98(void)
{
    uint32_t slot=(MEM32(esp+4)-0x7000)/0x20;
    CHECK(slot>=3 && slot<24 && MEM32(esp)==0x142591);
    CHECK((closed_mask & (1u<<slot))==0); closed_mask|=1u<<slot; ++closes;
    eax=slot==4?0xFFFFFFFFu:0; clobber(); esp+=4;
}
static void sub_0013F74D(void)
{
    uint32_t slot=(MEM32(esp+4)-0x7000)/0x20;
    CHECK(slot>=20 && slot<24 && MEM32(esp)==0x1425AC);
    CHECK((freed_mask & (1u<<slot))==0); freed_mask|=1u<<slot; ++frees;
    eax=0xEEEEEEEE; clobber(); esp+=4;
}
#include "crt_helpers.inc"
#include "crt_tails.inc"
static void reset(void)
{
    ++cases; memset(ram,0xCD,sizeof(ram));
    eax=ecx=edx=0; ebx=0x11223344; esi=0x55667788; edi=0x99AABBCC;
    esp=0x9000; g_ebp=0xD000; g_seh_ebp=0xB000;
    MEM32(0)=0x246800; MEM32(esp)=0xFACEB00C;
    locks=unlocks=allocations=retries=frees=closes=0;
    fail_allocations=allow_retries=0; freed_mask=closed_mask=0;
}
static void enter(unsigned local_size)
{
    PUSH32(esp,local_size); PUSH32(esp,0x239338); PUSH32(esp,0x112200);
    sub_0013A120();
    CHECK(g_seh_ebp==0x8FFC && MEM32(0)==0x8FEC);
}
static void saved(void)
{
    CHECK(esp==0x9004 && g_seh_ebp==0xB000);
    CHECK(ebx==0x11223344 && esi==0x55667788 && edi==0x99AABBCC);
    CHECK(MEM32(0)==0x246800 && MEM32(0x9000)==0xFACEB00C);
}
int main(void)
{
    void (*errors[])(void)={sub_00140DE6,sub_00141081,sub_00142C8F,sub_00142DA3};
    for(unsigned f=0;f<4;++f) for(unsigned locals=12;locals<=32;locals+=4) {
        reset(); enter(locals); MEM32(0x6008)=123; MEM32(0x600C)=456;
        errors[f](); saved(); CHECK(eax==0xFFFFFFFFu && MEM32(0x6008)==9);
        CHECK(MEM32(0x600C)==(f==2?456u:0u));
    }
    const uint32_t modes[]={0,1,2,0xFFFFFFFFu};
    for(unsigned m=0;m<4;++m) {
        reset(); enter(20); MEM32(g_seh_ebp+8)=modes[m];
        MEM32(g_seh_ebp-28)=37; MEM32(g_seh_ebp-36)=0xFFFFFFFFu;
        sub_0014270F(); saved(); CHECK(unlocks==1);
        CHECK(eax==(modes[m]==1?37u:0xFFFFFFFFu)); CHECK(MEM32(0x8FF8)==0xFFFFFFFFu);
    }
    /* Allocation success, zero-size normalization, no retry, rejected retry,
       retry then success, unsigned oversized request, and retry exhaustion. */
    const uint32_t sizes[]={32,0,64,64,64,0xFFFFFFE1u,0xFFFFFFE0u};
    const unsigned failures[]={0,0,1,1,1,0,2};
    const unsigned retry_enabled[]={0,0,0,1,1,1,1};
    const unsigned allowed[]={0,0,0,0,1,0,1};
    const unsigned expected_allocs[]={1,1,1,1,2,0,2};
    const unsigned expected_retries[]={0,0,0,1,1,1,2};
    const uint32_t expected_results[]={0x123400,0x123400,0,0,0x123400,0,0};
    for(unsigned i=0;i<7;++i) {
        reset(); enter(16); MEM32(g_seh_ebp+8)=0x4444;
        esi=sizes[i]; edi=0; requested=sizes[i]?sizes[i]:1;
        fail_allocations=failures[i]; allow_retries=allowed[i];
        MEM32(0x286B6C)=retry_enabled[i];
        sub_0013CA28(); saved(); CHECK(eax==expected_results[i]);
        CHECK(allocations==expected_allocs[i] && retries==expected_retries[i]);
    }
    /* Close only eligible streams >=3; free allocated stream records >=20.
       Slots 0..2 remain untouched and failed fclose does not increment count. */
    for(unsigned count=0;count<=24;++count) {
        reset(); MEM32(0x287C00)=0x5000; MEM32(0x287C04)=count;
        for(unsigned i=0;i<24;++i) {
            MEM32(0x5000+i*4)=i==5?0:0x7000+i*0x20;
            MEM8(0x7000+i*0x20+12)=i%3==0?0:(i%3==1?1:0x80);
        }
        sub_0014254F(); saved(); CHECK(locks==1 && unlocks==1);
        unsigned expected_close=0, expected_free=0, expected_ok=0;
        for(unsigned i=0;i<24;++i) {
            int visited=i>=3 && i<count && i!=5;
            int close=visited && i%3!=0;
            int release=visited && i>=20;
            expected_close+=(unsigned)close; expected_free+=(unsigned)release;
            expected_ok+=(unsigned)(close && i!=4);
            CHECK(!!(closed_mask&(1u<<i))==close);
            CHECK(!!(freed_mask&(1u<<i))==release);
            CHECK(MEM32(0x5000+i*4)==((release||i==5)?0u:0x7000+i*0x20));
        }
        CHECK(closes==expected_close && frees==expected_free && eax==expected_ok);
    }
    printf("PASS: %u CRT cases, %u checks; real SEH helpers, stack/register/errno/retry/stream cleanup\n",cases,checks);
    return 0;
}
