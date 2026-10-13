#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t ram[0x300000];
#define MEM8(a) (*(uint8_t *)(ram + (uint32_t)(a)))
#define MEM16(a) (*(uint16_t *)(ram + (uint32_t)(a)))
#define MEM32(a) (*(uint32_t *)(ram + (uint32_t)(a)))
#define PUSH32(s,v) do { (s) -= 4u; MEM32(s) = (uint32_t)(v); } while (0)
#define POP32(s,v) do { (v) = MEM32(s); (s) += 4u; } while (0)
#define RECOMP_FCMP(a,b) (((a)!=(a)||(b)!=(b))?2:(a)<(b)?-1:(a)>(b)?1:0)

static uint32_t eax, ebx, ecx, edx, esi, edi, esp, g_ebp, g_seh_ebp;
static double g_fp_stack[8];
static uint32_t g_fp_top;
static int g_fp_cmp;
static unsigned cases, checks, locks, unlocks, cleanup11, epilogues;
static unsigned icall_init, icall_close, longjmps;
static uint32_t allocation_result, registration_result, init_result;

#define CHECK(c) do { ++checks; if (!(c)) { \
    fprintf(stderr, "FAIL case=%u line=%u %s\n", cases, __LINE__, #c); exit(1); \
} } while (0)

static void sub_00140C99(void)
{
    CHECK(MEM32(esp) == 0x001423C5u && MEM32(esp + 4u) == 0xAu);
    ++locks; esp += 4u;
}
static void sub_0014215F(void)
{
    CHECK(MEM32(esp) == 0x001423E0u && MEM32(esp + 8u) == 0xFA0u);
    eax = init_result; esp += 4u;
}
static void sub_0013A2A6(void) { ++longjmps; esp += 4u; }
static void sub_0014242B(void) { ++unlocks; esp += 4u; }
static void sub_0013CBF3(void)
{
    CHECK(MEM32(esp) == 0x00142467u && MEM32(esp + 4u) == 0x500u);
    eax = allocation_result; esp += 4u;
}
static void sub_00142290(void)
{
    CHECK(MEM32(esp) == 0x001424AAu);
    eax = registration_result; esp += 4u;
}
static void sub_001424C5(void)
{
    CHECK(MEM32(esp) == 0x001424BCu); ++cleanup11; esp += 4u;
}
static void sub_001424BF(void)
{
    CHECK(MEM32(esp) == 0xFEEDC0DEu); ++epilogues; esp += 4u;
}
static void mock_icall(uint32_t target, uint32_t saved)
{
    CHECK(esp == saved - 8u);
    if (target == 0x11111111u) ++icall_init;
    else if (target == 0x22222222u) ++icall_close;
    else CHECK(0);
    esp = saved;
}
#define RECOMP_ICALL_SAFE(target,saved) mock_icall((target),(saved))

#include "final_crt_entries.inc"

static void reset(void)
{
    ++cases; memset(ram, 0xCD, sizeof(ram)); memset(g_fp_stack, 0, sizeof(g_fp_stack));
    eax = ebx = ecx = edx = esi = edi = 0u;
    esp = 0x9000u; MEM32(esp) = 0xFEEDC0DEu;
    g_ebp = g_seh_ebp = 0x8000u;
    MEM32(g_seh_ebp - 28u) = 0xFFFFFFFFu;
    MEM32(0x00225AC4u) = 0x11111111u;
    MEM32(0x00225AC0u) = 0x22222222u;
    g_fp_top = 0u; g_fp_cmp = 0;
    locks = unlocks = cleanup11 = epilogues = 0u;
    icall_init = icall_close = longjmps = 0u;
    allocation_result = 0x10000u; registration_result = init_result = 1u;
}

static void test_x87(double input, uint32_t ch, int expect_zero, int expect_negative_inf)
{
    reset();
    MEM32(0x9000u) = 0x0013FC47u;
    MEM32(0x9004u) = 0xCAFEBABEu;
    g_fp_stack[0] = input; g_fp_stack[1] = 123.0; ecx = ch << 8;
    sub_0013FBDC();
    CHECK(eax == 0x0013FC47u && esp == 0x9008u);
    if (expect_zero) {
        CHECK(g_fp_top == 1u && g_fp_stack[g_fp_top] == 0.0);
        CHECK(MEM8(g_seh_ebp - 144u) == 4u);
    } else {
        CHECK(g_fp_top == 0u && isinf(g_fp_stack[g_fp_top]));
        CHECK(signbit(g_fp_stack[g_fp_top]) == expect_negative_inf);
    }
}

int main(void)
{
    test_x87(2.0, 0u, 0, 0);
    test_x87(2.0, 1u, 0, 1);
    test_x87(0.0, 0u, 0, 0);
    test_x87(-2.0, 0u, 1, 0);
    test_x87(NAN, 0u, 1, 0);

    reset(); MEM32(g_seh_ebp - 28u) = 77u;
    sub_001424B3();
    CHECK(eax == 77u && esp == 0x9004u && cleanup11 == 1u && epilogues == 1u);

    reset(); edi = 2u; MEM32(0x00287C08u) = 7u;
    sub_0014245C();
    CHECK(eax == 64u && MEM32(0x00287C28u) == 0x10000u);
    CHECK(MEM32(0x00287C08u) == 39u && cleanup11 == 1u && epilogues == 1u);
    for (unsigned i = 0; i < 32u; ++i) {
        uint32_t record = 0x10000u + i * 0x28u;
        CHECK(MEM32(record) == 0xFFFFFFFFu && MEM8(record + 4u) == 0u);
        CHECK(MEM8(record + 5u) == 0xAu && MEM32(record + 8u) == 0u);
    }

    reset(); allocation_result = 0u; edi = 3u;
    sub_0014245C();
    CHECK(eax == 0xFFFFFFFFu && MEM32(0x00287C2Cu) == 0xCDCDCDCDu);

    reset(); registration_result = 0u; edi = 4u;
    sub_0014245C();
    CHECK(eax == 0xFFFFFFFFu && MEM32(0x00287C30u) == 0x10000u);

    reset(); edi = 3u; MEM32(0x00287C2Cu) = 0x12000u; esi = 0x12000u + 5u * 0x28u;
    sub_00142434();
    CHECK(eax == 101u && MEM32(0x12000u + 5u * 0x28u) == 0xFFFFFFFFu);

    reset(); edi = 0u; MEM32(0x00287C20u) = 0x11000u;
    MEM32(0x00287C24u) = 0u;
    sub_00142450();
    CHECK(eax == 32u && MEM32(0x00287C24u) == 0x10000u);

    reset(); edi = 0u; MEM32(0x00287C24u) = 0x11000u;
    memset(ram + 0x11000u, 0, 0x500u);
    sub_00142450();
    CHECK(eax == 32u && MEM32(0x11008u) == 1u);
    CHECK(locks == 1u && unlocks == 1u && icall_init == 1u && icall_close == 0u);

    reset(); edi = 0u; MEM32(0x00287C24u) = 0x11000u;
    memset(ram + 0x11000u, 0, 0x500u); init_result = 0u;
    sub_00142450();
    CHECK(eax == 0xFFFFFFFFu && longjmps == 1u && locks == 1u);

    printf("PASS: %u final CRT cases, %u checks; x87 nonlocal return and descriptor CFG\n",
           cases, checks);
    return 0;
}
