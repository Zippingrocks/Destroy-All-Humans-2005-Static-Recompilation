/* Original table + exact production function + native x87 and byte oracle.
 * This tests classifier dispatch, not the subsequent fmod arithmetic routine. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dah_x87_classify.h"
#pragma warning(disable: 4101 4102 4189)
extern uint32_t dah_test_fxam(const uint64_t *bits);
extern uint32_t dah_test_status_byte(uint32_t byte);
static uint8_t ram[0x300000];
static uint32_t eax, ebx, ecx, edx, esp, g_ebp, g_seh_ebp, g_fp_top;
static uint16_t g_fp_control_word;
static int g_fp_cmp;
static double g_fp_stack[8];
static uint32_t seen_target, seen_calls;
static uint64_t checks, cases;
#define MEM8(a) (ram[(uint32_t)(a)])
#define MEM16(a) (*(uint16_t *)(void *)(ram + (uint32_t)(a)))
#define MEM32(a) (*(uint32_t *)(void *)(ram + (uint32_t)(a)))
#define LO8(a) ((uint8_t)(a))
#define HI8(a) ((uint8_t)((a) >> 8))
#define LO16(a) ((uint16_t)(a))
#define SET_LO8(a,b) ((a) = ((a) & 0xFFFFFF00u) | (uint8_t)(b))
#define SET_HI8(a,b) ((a) = ((a) & 0xFFFF00FFu) | ((uint32_t)(uint8_t)(b) << 8))
#define SET_LO16(a,b) ((a) = ((a) & 0xFFFF0000u) | (uint16_t)(b))
#define SX8(a) ((uint32_t)(int32_t)(int8_t)(a))
#define CMP_NE(a,b) ((a) != (b))
#define CHECK(c) do { ++checks; if (!(c)) { fprintf(stderr, "FAIL line%u: %s\n", (unsigned)__LINE__, #c); exit(1); } } while (0)
static void record_tail(uint32_t target) { ++seen_calls; seen_target = target; }
#define RECOMP_ITAIL(v) record_tail(v)
#include "x87_classify_fixture.inc"
#include "x87_original_tables.inc"

static double from_bits(uint64_t bits) { double result; memcpy(&result, &bits, 8); return result; }
static uint64_t to_bits(double value) { uint64_t result; memcpy(&result, &value, 8); return result; }
static uint16_t oracle_status(uint64_t bits, unsigned top)
{
    return (uint16_t)((dah_test_fxam(&bits) & 0x4700u) | (top << 11));
}
static uint8_t byte_reference(uint8_t value)
{
    uint8_t shifted = (uint8_t)(value * 2u);
    uint8_t arithmetic = (uint8_t)(shifted / 2u + (shifted >= 128u ? 128u : 0u));
    return (uint8_t)((arithmetic * 2u) | (arithmetic / 128u));
}
static void classifier_case(uint64_t first, uint64_t second, unsigned top, uint16_t saved_control, uint8_t kind, int stale_cmp)
{
    uint16_t status0 = oracle_status(first, top), status1 = oracle_status(second, top);
    uint8_t byte0 = (uint8_t)dah_test_status_byte(status0 >> 8);
    uint8_t byte1 = (uint8_t)dah_test_status_byte(status1 >> 8);
    uint8_t offset = (uint8_t)(original_xlat[byte0 & 15] | (original_xlat[byte1 & 15] << 2));
    uint16_t expected_control = kind == 5 ? (uint16_t)((saved_control | 0x200u) & 0xFE00u) | 0x3Fu : 0x133Fu;
    uint64_t original_stack[8];
    uint32_t expected_target;
    unsigned i;
    ++cases;
    CHECK((offset & 3) == 0 && offset < 64);
    memcpy(&expected_target, original_fmod + 0x10 + offset, 4);
    g_ebp = 0x180100; g_seh_ebp = 0x170100;
    memset(ram + g_ebp - 0x200, 0xA5, 0x300);
    memset(ram + g_seh_ebp - 0x200, 0x7C, 0x300);
    MEM16(g_ebp - 164) = saved_control;
    MEM8(0x2597D0 + 0xE) = kind;
    esp = 0x100000; eax = 0xABCD1234; ebx = 0xAA551122; ecx = 0xCAFE9876; edx = 0x2597D0;
    g_fp_top = top; g_fp_control_word = saved_control; g_fp_cmp = stale_cmp;
    for (i = 0; i < 8; ++i) g_fp_stack[i] = 100.0 + i;
    g_fp_stack[top] = from_bits(first); g_fp_stack[(top + 1) & 7] = from_bits(second);
    for (i = 0; i < 8; ++i) original_stack[i] = to_bits(g_fp_stack[i]);
    seen_calls = 0; seen_target = 0;
    sub_0013F383();
    CHECK(seen_calls == 1 && seen_target == expected_target);
    CHECK(eax == offset && ebx == 0x2597E0u + offset && edx == 0x2597D0);
    CHECK(ecx == (((uint32_t)byte0 | ((uint32_t)byte1 << 8)) & 0x404u));
    CHECK(esp == 0x100000 && g_ebp == 0x180100 && g_seh_ebp == g_ebp);
    CHECK(g_fp_top == top && g_fp_cmp == stale_cmp);
    CHECK(g_fp_control_word == expected_control && MEM16(g_ebp - 162) == expected_control);
    CHECK(MEM16(g_ebp - 160) == status1 && MEM32(g_ebp - 148) == 0x2597D0 && MEM8(g_ebp - 144) == 0);
    for (i = 0; i < 8; ++i) CHECK(to_bits(g_fp_stack[i]) == original_stack[i]);
    for (i = 0; i < 0x300; ++i) CHECK(ram[0x170100 - 0x200 + i] == 0x7C);
}
static void unary_case(uint64_t value, unsigned top, unsigned table_index, unsigned control_mode, uint32_t initial_ecx)
{
    uint32_t table_address = 0x25AA9Au + table_index * 0x20u;
    uint16_t status = oracle_status(value, top), saved_control = (uint16_t)(0x3FFu + top * 0x400u);
    uint8_t transformed = (uint8_t)dah_test_status_byte(status >> 8);
    uint8_t offset = original_xlat[transformed & 15];
    uint16_t expected_control = control_mode ? (uint16_t)(((saved_control | 0x200u) & 0xFE00u) | 0x3Fu) : 0x133Fu;
    uint32_t expected_target;
    uint64_t original_stack[8];
    unsigned i;
    ++cases;
    CHECK((offset & 3) == 0 && offset < 16 && table_index < 3);
    memcpy(&expected_target, original_unary + table_index * 32u + 16u + offset, 4);
    g_ebp = 0x180100; g_seh_ebp = 0x170100;
    memset(ram + g_ebp - 0x200, 0xA5, 0x300);
    memset(ram + g_seh_ebp - 0x200, 0x7C, 0x300);
    MEM16(g_ebp - 164) = saved_control;
    MEM8(table_address + 0xE) = control_mode ? 5 : original_unary[table_index * 32u + 14];
    esp = 0x100000; eax = 0xABCD1234; ebx = 0xAA551122; ecx = initial_ecx; edx = table_address;
    g_fp_top = top; g_fp_control_word = saved_control; g_fp_cmp = 2;
    for (i = 0; i < 8; ++i) g_fp_stack[i] = 100.0 + i;
    g_fp_stack[top] = from_bits(value);
    for (i = 0; i < 8; ++i) original_stack[i] = to_bits(g_fp_stack[i]);
    seen_calls = 0; seen_target = 0;
    sub_0013F31C();
    CHECK(seen_calls == 1 && seen_target == expected_target);
    CHECK(eax == offset && ebx == table_address + 16u + offset && edx == table_address);
    CHECK(ecx == ((initial_ecx & 0x400u) | (transformed & 4u)));
    CHECK(esp == 0x100000 && g_ebp == 0x180100 && g_seh_ebp == g_ebp);
    CHECK(g_fp_top == top && g_fp_cmp == 2);
    CHECK(g_fp_control_word == expected_control && MEM16(g_ebp - 162) == expected_control);
    CHECK(MEM16(g_ebp - 160) == status && MEM32(g_ebp - 148) == table_address && MEM8(g_ebp - 144) == 0);
    for (i = 0; i < 8; ++i) CHECK(to_bits(g_fp_stack[i]) == original_stack[i]);
    for (i = 0; i < 0x300; ++i) CHECK(ram[0x170100 - 0x200 + i] == 0x7C);
}
int main(void)
{
    static const uint64_t values[] = {
        0, UINT64_C(0x8000000000000000), 1, UINT64_C(0x8000000000000001),
        UINT64_C(0x000FFFFFFFFFFFFF), UINT64_C(0x800FFFFFFFFFFFFF),
        UINT64_C(0x0010000000000000), UINT64_C(0x8010000000000000),
        UINT64_C(0x3FF0000000000000), UINT64_C(0xBFF0000000000000),
        UINT64_C(0x400921FB54442D18), UINT64_C(0xC00921FB54442D18),
        UINT64_C(0x7FEFFFFFFFFFFFFF), UINT64_C(0xFFEFFFFFFFFFFFFF),
        UINT64_C(0x7FF0000000000000), UINT64_C(0xFFF0000000000000),
        UINT64_C(0x7FF8000000000000), UINT64_C(0xFFF8000000000000),
        UINT64_C(0x7FF0000000000001), UINT64_C(0xFFF0000000000001),
        UINT64_C(0x7FFFFFFFFFFFFFFF), UINT64_C(0xFFFFFFFFFFFFFFFF)
    };
    uint64_t state = UINT64_C(0xAF3171BB005533CC);
    unsigned i, j, top, mode;
    memcpy(ram + 0x259A6C, original_xlat, sizeof(original_xlat));
    memcpy(ram + 0x2597D0, original_fmod, sizeof(original_fmod));
    memcpy(ram + 0x25AA9A, original_unary, sizeof(original_unary));
    for (i = 0; i < 256; ++i) CHECK(dah_test_status_byte(i) == byte_reference((uint8_t)i));
    for (i = 0; i < 100000; ++i) {
        uint16_t actual, expected;
        state ^= state << 13; state ^= state >> 7; state ^= state << 17;
        top = i & 7; actual = dah_x87_fxam_live_status(from_bits(state), top);
        expected = oracle_status(state, top); CHECK(actual == expected);
    }
    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
        for (j = 0; j < sizeof(values) / sizeof(values[0]); ++j)
            for (top = 0; top < 8; ++top)
                for (mode = 0; mode < 2; ++mode)
                    classifier_case(values[i], values[j], top,
                        (uint16_t)((i * 0x321u + j * 0x109u + top * 0x400u) & 0x1FFFu),
                        mode ? 5 : 0x16, (int)(i % 4) - 1);
    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
        for (j = 0; j < 3; ++j)
            for (top = 0; top < 8; ++top)
                for (mode = 0; mode < 2; ++mode) {
                    unary_case(values[i], top, j, mode, 0xCAFEBABE);
                    unary_case(values[i], top, j, mode, 0xFFFF0456);
                }
    printf("PASS: 100000 native-FXAM comparisons, all256 byte transforms, %llu actual-source dispatch cases, %llu assertions\n",
        (unsigned long long)cases, (unsigned long long)checks);
    return 0;
}
