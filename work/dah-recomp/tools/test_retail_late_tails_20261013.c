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
#define CHECK(c) do { ++checks; if (!(c)) { \
    fprintf(stderr, "FAIL case=%u line=%u: %s\n", cases, __LINE__, #c); exit(1); \
} } while (0)
static uint32_t eax, ecx, edx, esi, edi, esp, g_ebp;
static unsigned cases, checks, epilogs, decode_calls;
static uint32_t decode_result;

static void sub_0013F6C8(void) { eax = 0x1000u; esp += 4u; }
static void sub_0013F6D1(void) { eax = 0x1004u; esp += 4u; }
static void sub_001A5567(void) { ++epilogs; esp += 4u; }
static void sub_001B46DC(void)
{
    CHECK(MEM32(esp) == 0x001B6C8Cu);
    CHECK(MEM32(esp + 4u) == 0x5150u);
    ++decode_calls; eax = decode_result; esp += 12u;
}

#include "retail_late_tails.inc"

static void reset(void)
{
    ++cases; memset(ram, 0xCD, sizeof(ram));
    eax = ecx = edx = 0; esi = 0x11223344u; edi = 0x55667788u;
    esp = 0x280000u; g_ebp = 0xAABBCCDDu; epilogs = decode_calls = 0u;
    MEM32(esp) = 0xCAFEBABEu;
}

static int32_t signed_range_oracle(const int32_t values[8], int32_t limit)
{
    int32_t low = values[0], high = values[0];
    const unsigned early[] = {7, 2, 4};
    for (unsigned i = 0; i < 3; ++i) {
        int32_t value = values[early[i]];
        if (value < low) low = value; else if (value > high) high = value;
    }
    if ((int32_t)((uint32_t)high - (uint32_t)low) >= limit) return 0;
    const unsigned later[] = {1, 3, 5, 6};
    for (unsigned i = 0; i < 4; ++i) {
        int32_t value = values[later[i]];
        if (value < low) low = value; else if (value > high) high = value;
    }
    return (int32_t)((uint32_t)high - (uint32_t)low) < limit;
}

int main(void)
{
    reset(); MEM32(0x1000u) = 71u; MEM32(0x1004u) = 93u;
    sub_001A5551();
    CHECK(MEM32(0x1000u) == 9u && MEM32(0x1004u) == 0u);
    CHECK(eax == 0xFFFFFFFFu && epilogs == 1u && esp == 0x280004u);

    for (unsigned below = 0; below < 2; ++below) for (uint32_t slot = 0; slot < 5; ++slot) {
        reset(); uint32_t arg3 = below ? 12u : 13u, table_slot = slot + (below ? 9u : 0u);
        MEM32(esp + 4u) = 0x5150u; MEM32(esp + 8u) = slot;
        MEM32(esp + 12u) = arg3; MEM32(esp + 16u) = 0x6000u;
        MEM16(0x001D7C20u + table_slot * 8u) = 3u;
        MEM32(0x001D7C24u + table_slot * 8u) = 0x7000u;
        MEM32(0x7000u + 3u * 4u) = 0xABC00000u | table_slot;
        decode_result = 3u;
        uint32_t old_esi = esi, old_edi = edi, old_ebp = g_ebp;
        sub_001B6C64();
        CHECK(MEM32(0x6000u + slot * 4u) == (0xABC00000u | table_slot));
        CHECK(decode_calls == 1u && esp == 0x280014u);
        CHECK(esi == old_esi && edi == old_edi && g_ebp == old_ebp);
    }

    uint32_t random = 0xC001D00Du;
    for (unsigned iteration = 0; iteration < 1000; ++iteration) {
        int32_t values[8];
        for (unsigned i = 0; i < 8; ++i) {
            random = random * 1664525u + 1013904223u;
            values[i] = (int32_t)random;
        }
        random = random * 1664525u + 1013904223u;
        int32_t limit = (int32_t)random;
        reset();
        const unsigned offsets[] = { 4, 8, 12, 16, 20, 24, 28, 32 };
        for (unsigned i = 0; i < 8; ++i) MEM32(esp + offsets[i]) = (uint32_t)values[i];
        MEM32(esp + 36u) = (uint32_t)limit;
        uint32_t old_ebp = g_ebp;
        sub_001B747C();
        CHECK(eax == (uint32_t)signed_range_oracle(values, limit));
        CHECK(esp == 0x280028u && g_ebp == old_ebp);
    }
    printf("PASS: %u late-tail cases, %u checks\n", cases, checks);
    return 0;
}
