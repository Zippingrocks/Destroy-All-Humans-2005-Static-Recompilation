/* Independent hardware oracle for the guest's packed 64-bit operations.
 * Build x64 with MSVC /W4 /O2 or clang/gcc -std=c11 -msse2.
 * SSE2 keeps the test independent of host x87/MMX register aliasing.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <emmintrin.h>
#include "../../templates/runtime/recomp_mmx.h"

typedef uint64_t (*BinaryOp)(uint64_t, uint64_t);
typedef struct TestOp {
    const char *name;
    BinaryOp implementation;
    BinaryOp oracle;
} TestOp;

static __m128i low64(uint64_t value)
{
    return _mm_cvtsi64_si128((int64_t)value);
}

#define ORACLE(name, expression)                                         \
    static uint64_t oracle_##name(uint64_t av, uint64_t bv)                \
    {                                                                   \
        __m128i a = low64(av), b = low64(bv);                             \
        return (uint64_t)_mm_cvtsi128_si64(expression);                   \
    }

ORACLE(PADDB,    _mm_add_epi8(a, b))
ORACLE(PADDW,    _mm_add_epi16(a, b))
ORACLE(PADDD,    _mm_add_epi32(a, b))
ORACLE(PSUBB,    _mm_sub_epi8(a, b))
ORACLE(PSUBW,    _mm_sub_epi16(a, b))
ORACLE(PSUBD,    _mm_sub_epi32(a, b))
ORACLE(PADDSB,   _mm_adds_epi8(a, b))
ORACLE(PADDSW,   _mm_adds_epi16(a, b))
ORACLE(PSUBSB,   _mm_subs_epi8(a, b))
ORACLE(PSUBSW,   _mm_subs_epi16(a, b))
ORACLE(PADDUSB,  _mm_adds_epu8(a, b))
ORACLE(PADDUSW,  _mm_adds_epu16(a, b))
ORACLE(PSUBUSB,  _mm_subs_epu8(a, b))
ORACLE(PSUBUSW,  _mm_subs_epu16(a, b))
ORACLE(PAND,     _mm_and_si128(a, b))
ORACLE(PANDN,    _mm_andnot_si128(a, b))
ORACLE(POR,      _mm_or_si128(a, b))
ORACLE(PXOR,     _mm_xor_si128(a, b))
ORACLE(PUNPCKLBW, _mm_unpacklo_epi8(a, b))
ORACLE(PUNPCKLWD, _mm_unpacklo_epi16(a, b))
ORACLE(PUNPCKLDQ, _mm_unpacklo_epi32(a, b))
/* MMX high half starts at bit32, not SSE2's bit64. Move the MMX high
 * halves down before interleaving, then retain the low64 of the result. */
ORACLE(PUNPCKHBW, _mm_unpacklo_epi8(_mm_srli_epi64(a, 32), _mm_srli_epi64(b, 32)))
ORACLE(PUNPCKHWD, _mm_unpacklo_epi16(_mm_srli_epi64(a, 32), _mm_srli_epi64(b, 32)))
ORACLE(PUNPCKHDQ, _mm_unpacklo_epi32(_mm_srli_epi64(a, 32), _mm_srli_epi64(b, 32)))
ORACLE(PMULLW,   _mm_mullo_epi16(a, b))
ORACLE(PMULHW,   _mm_mulhi_epi16(a, b))
ORACLE(PMULHUW,  _mm_mulhi_epu16(a, b))
/* Packing zero-extended a and b separately would put zero padding in
 * the result. Combine their source lanes in one128 first. */
ORACLE(PACKSSWB, _mm_packs_epi16(_mm_unpacklo_epi64(a, b), _mm_setzero_si128()))
ORACLE(PACKUSWB, _mm_packus_epi16(_mm_unpacklo_epi64(a, b), _mm_setzero_si128()))
ORACLE(PACKSSDW, _mm_packs_epi32(_mm_unpacklo_epi64(a, b), _mm_setzero_si128()))
/* The variable-count forms consume the complete low64 of b. */
ORACLE(PSLLW, _mm_sll_epi16(a, b))
ORACLE(PSLLD, _mm_sll_epi32(a, b))
ORACLE(PSLLQ, _mm_sll_epi64(a, b))
ORACLE(PSRLW, _mm_srl_epi16(a, b))
ORACLE(PSRLD, _mm_srl_epi32(a, b))
ORACLE(PSRLQ, _mm_srl_epi64(a, b))
ORACLE(PSRAW, _mm_sra_epi16(a, b))
ORACLE(PSRAD, _mm_sra_epi32(a, b))
#undef ORACLE

#define TEST_OP(name) { #name, MMX_##name, oracle_##name }
static const TestOp binary_ops[] = {
    TEST_OP(PADDB), TEST_OP(PADDW), TEST_OP(PADDD),
    TEST_OP(PSUBB), TEST_OP(PSUBW), TEST_OP(PSUBD),
    TEST_OP(PADDSB), TEST_OP(PADDSW), TEST_OP(PSUBSB), TEST_OP(PSUBSW),
    TEST_OP(PADDUSB), TEST_OP(PADDUSW), TEST_OP(PSUBUSB), TEST_OP(PSUBUSW),
    TEST_OP(PAND), TEST_OP(PANDN), TEST_OP(POR), TEST_OP(PXOR),
    TEST_OP(PUNPCKLBW), TEST_OP(PUNPCKHBW), TEST_OP(PUNPCKLWD),
    TEST_OP(PUNPCKHWD), TEST_OP(PUNPCKLDQ), TEST_OP(PUNPCKHDQ),
    TEST_OP(PMULLW), TEST_OP(PMULHW), TEST_OP(PMULHUW),
    TEST_OP(PACKSSWB), TEST_OP(PACKUSWB), TEST_OP(PACKSSDW)
};
static const TestOp shift_ops[] = {
    TEST_OP(PSLLW), TEST_OP(PSLLD), TEST_OP(PSLLQ),
    TEST_OP(PSRLW), TEST_OP(PSRLD), TEST_OP(PSRLQ),
    TEST_OP(PSRAW), TEST_OP(PSRAD)
};
#undef TEST_OP

#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))
static uint64_t checks;
static uint64_t random_state = UINT64_C(0xDAB1200500010001);

static uint64_t next_random(void)
{
    /* Fixed seed makes a failed vector reproducible. */
    uint64_t x = random_state;
    x ^= x << 13u;
    x ^= x >> 7u;
    x ^= x << 17u;
    random_state = x;
    return x;
}

static void compare(const char *name, uint64_t a, uint64_t b,
                    uint64_t actual, uint64_t expected)
{
    ++checks;
    if (actual != expected) {
        fprintf(stderr, "%s a=%016" PRIX64 " b=%016" PRIX64
                " actual=%016" PRIX64 " expected=%016" PRIX64 "\n",
                name, a, b, actual, expected);
        exit(1);
    }
}

static void check_ops(const TestOp *ops, size_t count, uint64_t a, uint64_t b)
{
    size_t i;
    for (i = 0; i < count; ++i)
        compare(ops[i].name, a, b, ops[i].implementation(a, b), ops[i].oracle(a, b));
}

static void check_known_results(void)
{
    /* Independent literals catch oracle lane-placement and signedness errors. */
    compare("unpack-low-byte-order", 0, 0,
        MMX_PUNPCKLBW(UINT64_C(0x0706050403020100), UINT64_C(0x1716151413121110)),
        UINT64_C(0x1303120211011000));
    compare("unpack-high-byte-order", 0, 0,
        MMX_PUNPCKHBW(UINT64_C(0x0706050403020100), UINT64_C(0x1716151413121110)),
        UINT64_C(0x1707160615051404));
    compare("pack-us-signed-source", 0, 0,
        MMX_PACKUSWB(UINT64_C(0xFFFF010000FF0000), UINT64_C(0x7FFF80000080007F)),
        UINT64_C(0xFF00807F00FFFF00));
    compare("signed-high-multiply", 0, 0,
        MMX_PMULHW(UINT64_C(0x8000800080008000), UINT64_C(0x8000800080008000)),
        UINT64_C(0x4000400040004000));
    compare("shift-not-modulo", 0, 0, MMX_PSLLW(UINT64_MAX, 64), 0);
    compare("shift-full-count", 0, 0, MMX_PSRLW(UINT64_MAX, UINT64_C(0x100000000)), 0);
    compare("arithmetic-shift-sign", 0, 0,
        MMX_PSRAW(UINT64_C(0x80007FFFFFFF0001), UINT64_MAX), UINT64_C(0xFFFF0000FFFF0000));
}

int main(void)
{
    static const uint64_t edges[] = {
        UINT64_C(0), UINT64_C(1), UINT64_MAX,
        UINT64_C(0x0101010101010101), UINT64_C(0x7F7F7F7F7F7F7F7F),
        UINT64_C(0x8080808080808080), UINT64_C(0xFEFEFEFEFEFEFEFE),
        UINT64_C(0x0001000100010001), UINT64_C(0x7FFF7FFF7FFF7FFF),
        UINT64_C(0x8000800080008000), UINT64_C(0xFFFEFFFEFFFEFFFE),
        UINT64_C(0x0000000100000001), UINT64_C(0x7FFFFFFF7FFFFFFF),
        UINT64_C(0x8000000080000000), UINT64_C(0xFFFFFFFEFFFFFFFE),
        UINT64_C(0x0000000080000000), UINT64_C(0x8000000000000000),
        UINT64_C(0xAAAA5555FFFF0000), UINT64_C(0x0123456789ABCDEF),
        UINT64_C(0xFEDCBA9876543210), UINT64_C(0x007F008000FF0100),
        UINT64_C(0xFF7FFF80FFFF8000), UINT64_C(0x00007FFF00008000),
        UINT64_C(0xFFFF7FFFFFFF8000)
    };
    static const uint64_t counts[] = {
        0, 1, 7, 8, 15, 16, 17, 31, 32, 33, 63, 64, 65, 127, 255, 256,
        UINT64_C(0xFFFFFFFF), UINT64_C(0x100000000),
        UINT64_C(0x8000000000000000), UINT64_MAX
    };
    size_t i, j;
    check_known_results();
    for (i = 0; i < ARRAY_COUNT(edges); ++i) {
        for (j = 0; j < ARRAY_COUNT(edges); ++j)
            check_ops(binary_ops, ARRAY_COUNT(binary_ops), edges[i], edges[j]);
        for (j = 0; j < ARRAY_COUNT(counts); ++j)
            check_ops(shift_ops, ARRAY_COUNT(shift_ops), edges[i], counts[j]);
    }
    for (i = 0; i < 100000u; ++i) {
        uint64_t a = next_random(), b = next_random();
        check_ops(binary_ops, ARRAY_COUNT(binary_ops), a, b);
        check_ops(shift_ops, ARRAY_COUNT(shift_ops), a, b);
        if (i < 4096u)
            for (j = 0; j < ARRAY_COUNT(counts); ++j)
                check_ops(shift_ops, ARRAY_COUNT(shift_ops), a, counts[j]);
    }
    printf("PASS: %" PRIu64 " comparisons across %zu MMX helpers; "
           "SSE2 oracle, boundary vectors, 100000 deterministic random pairs.\n",
           checks, ARRAY_COUNT(binary_ops) + ARRAY_COUNT(shift_ops));
    return 0;
}
