/* Exact packed-integer operations for 64-bit guest MMX registers.
 *
 * Registers remain uint64_t so generated MOVD assignments zero their upper
 * 32 bits naturally. Helpers use unsigned bit extraction, independent of
 * host alignment, aliasing, endianness, and signed-right-shift behavior.
 * Every operation returns a new register value and leaves guest flags alone.
 * Memory translation and x87/MMX register lifetime belong to the caller.
 */
#ifndef RECOMP_MMX_H
#define RECOMP_MMX_H

#include <stdint.h>

static inline uint64_t recomp_mmx_mask(unsigned width)
{
    return width == 64u ? UINT64_MAX : (UINT64_C(1) << width) - 1u;
}

static inline int64_t recomp_mmx_signed(uint64_t bits, unsigned width)
{
    uint64_t sign = UINT64_C(1) << (width - 1u);
    /* Used for lanes <=32 bits: both subexpressions fit int64_t. */
    return (int64_t)(bits & (sign - 1u)) - (int64_t)(bits & sign);
}

static inline uint64_t recomp_mmx_addsub(uint64_t a, uint64_t b,
                                        unsigned width, int subtract,
                                        int saturation)
{
    uint64_t result = 0;
    uint64_t mask = recomp_mmx_mask(width);
    unsigned offset;
    for (offset = 0; offset < 64u; offset += width) {
        uint64_t x = (a >> offset) & mask;
        uint64_t y = (b >> offset) & mask;
        uint64_t lane;
        if (saturation == 1) {
            int64_t sx = recomp_mmx_signed(x, width);
            int64_t sy = recomp_mmx_signed(y, width);
            int64_t sum = subtract ? sx - sy : sx + sy;
            int64_t high = (int64_t)(mask >> 1u);
            int64_t low = -high - 1;
            if (sum > high) sum = high;
            if (sum < low) sum = low;
            lane = (uint64_t)sum;
        } else if (saturation == 2) {
            lane = subtract ? (x < y ? 0u : x - y) : x + y;
            if (lane > mask) lane = mask;
        } else {
            lane = subtract ? x - y : x + y;
        }
        result |= (lane & mask) << offset;
    }
    return result;
}

#define RECOMP_MMX_ARITH(name, width, subtract, saturation)               \
    static inline uint64_t name(uint64_t a, uint64_t b)                    \
    { return recomp_mmx_addsub(a, b, width, subtract, saturation); }

RECOMP_MMX_ARITH(MMX_PADDB,    8u, 0, 0)
RECOMP_MMX_ARITH(MMX_PADDW,   16u, 0, 0)
RECOMP_MMX_ARITH(MMX_PADDD,   32u, 0, 0)
RECOMP_MMX_ARITH(MMX_PSUBB,    8u, 1, 0)
RECOMP_MMX_ARITH(MMX_PSUBW,   16u, 1, 0)
RECOMP_MMX_ARITH(MMX_PSUBD,   32u, 1, 0)
RECOMP_MMX_ARITH(MMX_PADDSB,   8u, 0, 1)
RECOMP_MMX_ARITH(MMX_PADDSW,  16u, 0, 1)
RECOMP_MMX_ARITH(MMX_PSUBSB,   8u, 1, 1)
RECOMP_MMX_ARITH(MMX_PSUBSW,  16u, 1, 1)
RECOMP_MMX_ARITH(MMX_PADDUSB,  8u, 0, 2)
RECOMP_MMX_ARITH(MMX_PADDUSW, 16u, 0, 2)
RECOMP_MMX_ARITH(MMX_PSUBUSB,  8u, 1, 2)
RECOMP_MMX_ARITH(MMX_PSUBUSW, 16u, 1, 2)
#undef RECOMP_MMX_ARITH

static inline uint64_t MMX_PAND(uint64_t a, uint64_t b) { return a & b; }
static inline uint64_t MMX_PANDN(uint64_t a, uint64_t b) { return (~a) & b; }
static inline uint64_t MMX_POR(uint64_t a, uint64_t b) { return a | b; }
static inline uint64_t MMX_PXOR(uint64_t a, uint64_t b) { return a ^ b; }

static inline uint64_t recomp_mmx_unpack(uint64_t a, uint64_t b,
                                        unsigned width, int high)
{
    uint64_t result = 0;
    uint64_t mask = recomp_mmx_mask(width);
    unsigned i;
    unsigned base = high ? 32u : 0u;
    for (i = 0; i < 32u / width; ++i) {
        result |= ((a >> (base + i * width)) & mask) << (2u * i * width);
        result |= ((b >> (base + i * width)) & mask) << ((2u * i + 1u) * width);
    }
    return result;
}

#define RECOMP_MMX_UNPACK(name, width, high)                              \
    static inline uint64_t name(uint64_t a, uint64_t b)                    \
    { return recomp_mmx_unpack(a, b, width, high); }
RECOMP_MMX_UNPACK(MMX_PUNPCKLBW,  8u, 0)
RECOMP_MMX_UNPACK(MMX_PUNPCKHBW,  8u, 1)
RECOMP_MMX_UNPACK(MMX_PUNPCKLWD, 16u, 0)
RECOMP_MMX_UNPACK(MMX_PUNPCKHWD, 16u, 1)
RECOMP_MMX_UNPACK(MMX_PUNPCKLDQ, 32u, 0)
RECOMP_MMX_UNPACK(MMX_PUNPCKHDQ, 32u, 1)
#undef RECOMP_MMX_UNPACK

/* Packed shifts consume the full unsigned count (imm8 or mm/m64), never
 * the GPR shift mask. Oversized logical shifts clear every lane. */
static inline uint64_t recomp_mmx_shift(uint64_t a, uint64_t count,
                                       unsigned width, int right,
                                       int arithmetic)
{
    uint64_t result = 0;
    uint64_t mask = recomp_mmx_mask(width);
    unsigned offset;
    if (count >= width && !arithmetic) return 0;
    if (count >= width) count = width - 1u;
    for (offset = 0; offset < 64u; offset += width) {
        uint64_t lane = (a >> offset) & mask;
        uint64_t shifted = right ? lane >> count : lane << count;
        if (arithmetic && count != 0u &&
            (lane & (UINT64_C(1) << (width - 1u))))
            shifted |= mask ^ (mask >> count);
        result |= (shifted & mask) << offset;
    }
    return result;
}

#define RECOMP_MMX_SHIFT(name, width, right, arithmetic)                  \
    static inline uint64_t name(uint64_t a, uint64_t count)                \
    { return recomp_mmx_shift(a, count, width, right, arithmetic); }
RECOMP_MMX_SHIFT(MMX_PSLLW, 16u, 0, 0)
RECOMP_MMX_SHIFT(MMX_PSLLD, 32u, 0, 0)
RECOMP_MMX_SHIFT(MMX_PSLLQ, 64u, 0, 0)
RECOMP_MMX_SHIFT(MMX_PSRLW, 16u, 1, 0)
RECOMP_MMX_SHIFT(MMX_PSRLD, 32u, 1, 0)
RECOMP_MMX_SHIFT(MMX_PSRLQ, 64u, 1, 0)
RECOMP_MMX_SHIFT(MMX_PSRAW, 16u, 1, 1)
RECOMP_MMX_SHIFT(MMX_PSRAD, 32u, 1, 1)
#undef RECOMP_MMX_SHIFT

static inline uint64_t recomp_mmx_mulw(uint64_t a, uint64_t b,
                                      int high, int unsigned_inputs)
{
    uint64_t result = 0;
    unsigned offset;
    for (offset = 0; offset < 64u; offset += 16u) {
        uint64_t x = (a >> offset) & 0xFFFFu;
        uint64_t y = (b >> offset) & 0xFFFFu;
        int64_t sx = unsigned_inputs ? (int64_t)x : recomp_mmx_signed(x, 16u);
        int64_t sy = unsigned_inputs ? (int64_t)y : recomp_mmx_signed(y, 16u);
        uint32_t product = (uint32_t)(sx * sy);
        uint32_t lane = high ? product >> 16u : product;
        result |= (uint64_t)(lane & 0xFFFFu) << offset;
    }
    return result;
}
static inline uint64_t MMX_PMULLW(uint64_t a, uint64_t b)
{ return recomp_mmx_mulw(a, b, 0, 0); }
static inline uint64_t MMX_PMULHW(uint64_t a, uint64_t b)
{ return recomp_mmx_mulw(a, b, 1, 0); }
static inline uint64_t MMX_PMULHUW(uint64_t a, uint64_t b)
{ return recomp_mmx_mulw(a, b, 1, 1); }

/* Pack all lanes of a, followed by all lanes of b. PACKUSWB still reads
 * signed input words; negative source values clamp to zero. */
static inline uint64_t recomp_mmx_pack(uint64_t a, uint64_t b,
                                      unsigned source_width, int unsigned_out)
{
    uint64_t result = 0;
    unsigned width = source_width / 2u;
    uint64_t mask = recomp_mmx_mask(width);
    uint64_t source_mask = recomp_mmx_mask(source_width);
    int64_t high = (int64_t)(unsigned_out ? mask : mask >> 1u);
    int64_t low = unsigned_out ? 0 : -high - 1;
    unsigned half, lane;
    for (half = 0; half < 2u; ++half) {
        uint64_t source = half ? b : a;
        for (lane = 0; lane < 64u / source_width; ++lane) {
            int64_t value = recomp_mmx_signed(
                (source >> (lane * source_width)) & source_mask, source_width);
            if (value > high) value = high;
            if (value < low) value = low;
            result |= ((uint64_t)value & mask) << (half * 32u + lane * width);
        }
    }
    return result;
}
static inline uint64_t MMX_PACKSSWB(uint64_t a, uint64_t b)
{ return recomp_mmx_pack(a, b, 16u, 0); }
static inline uint64_t MMX_PACKUSWB(uint64_t a, uint64_t b)
{ return recomp_mmx_pack(a, b, 16u, 1); }
static inline uint64_t MMX_PACKSSDW(uint64_t a, uint64_t b)
{ return recomp_mmx_pack(a, b, 32u, 0); }

#endif /* RECOMP_MMX_H */
