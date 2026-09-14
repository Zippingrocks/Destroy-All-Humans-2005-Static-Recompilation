/* Exact production statement fixtures are inserted by test_sse_lahf.mjs. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xmmintrin.h>
#include "recomp_sse_flags.h"

extern uint32_t hardware_ucomiss_lahf(float lhs, float rhs);
extern uint32_t hardware_comiss_lahf(float lhs, float rhs);
typedef union TestXmm { float f[4]; uint32_t u[4]; } TestXmm;
typedef struct Result { uint32_t eax; int branch; } Result;
static uint32_t expected_memory_address;
static unsigned memory_reads;
static float memory_value;
static float *fixture_memory(uint32_t address) {
    if (address != expected_memory_address) {
        fprintf(stderr, "Wrong guest memory operand: %08X != %08X\n",
                address, expected_memory_address);
        exit(2);
    }
    ++memory_reads;
    return &memory_value;
}
#define MEMF(address) (*fixture_memory((uint32_t)(address)))

/* PRODUCTION_MACROS */
/* PRODUCTION_FIXTURES */

static float as_float(uint32_t bits) {
    float value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

static uint32_t random_bits(void) {
    static uint32_t state = 0xC001D00Du;
    state ^= state << 13; state ^= state >> 17; state ^= state << 5;
    return state;
}

static unsigned checks;
static int check_case(uint32_t a, uint32_t b, uint32_t initial_eax) {
    const float lhs = as_float(a), rhs = as_float(b);
    const uint32_t hardware = hardware_ucomiss_lahf(lhs, rhs);
    const uint32_t ordered_hardware = hardware_comiss_lahf(lhs, rhs);
    const uint8_t flags = RECOMP_COMISS_LAHF(lhs, rhs);
    if (flags != (hardware & 255u) || hardware != ordered_hardware) {
        fprintf(stderr, "Flags mismatch %08X,%08X: helper=%02X hardware=%03X ordered=%03X\n",
                a, b, flags, hardware, ordered_hardware);
        return 1;
    }
    for (unsigned i = 0; i < sizeof(sites) / sizeof(sites[0]); ++i) {
        const Result actual = sites[i].run(lhs, rhs, initial_eax);
        const uint32_t wanted_eax = (initial_eax & 0xffff00ffu) | ((hardware & 255u) << 8);
        const int wanted_branch = (int)((hardware >> 8) & 1u) ^ sites[i].is_jnp;
        if (actual.eax != wanted_eax || actual.branch != wanted_branch) {
            fprintf(stderr, "Site %08X inputs=%08X,%08X oldEAX=%08X: EAX=%08X/%08X branch=%d/%d\n",
                    sites[i].address, a, b, initial_eax, actual.eax, wanted_eax,
                    actual.branch, wanted_branch);
            return 1;
        }
        if (memory_reads != sites[i].memory_operands) {
            fprintf(stderr, "Wrong memory read count at %08X: %u\n", sites[i].address, memory_reads);
            return 1;
        }
        ++checks;
    }
    return 0;
}

int main(void) {
    /* All exceptions masked, DAZ/FTZ disabled: retail default comparison flags.
       Signaling NaN tests must not trap the host. Restore the original MXCSR. */
    const unsigned saved_mxcsr = _mm_getcsr();
    _mm_setcsr(0x1f80u);
    const uint32_t edge[] = {
        0, 0x80000000u, 1, 0x80000001u, 0x007fffffu, 0x807fffffu,
        0x00800000u, 0x80800000u, 0x3f000000u, 0xbf000000u,
        0x3f7fffffu, 0xbf7fffffu, 0x3f800000u, 0xbf800000u,
        0x3f800001u, 0xbf800001u, 0x7f7fffffu, 0xff7fffffu,
        0x7f800000u, 0xff800000u, 0x7fc00000u, 0xffc00000u,
        0x7f800001u, 0xff800001u, 0x7fffffffu, 0xffffffffu
    };
    const uint32_t eax_values[] = {0, 0xffffffffu, 0x12344478u, 0xABCDEF01u};
    for (unsigned a = 0; a < sizeof(edge) / sizeof(edge[0]); ++a)
        for (unsigned b = 0; b < sizeof(edge) / sizeof(edge[0]); ++b)
            for (unsigned e = 0; e < sizeof(eax_values) / sizeof(eax_values[0]); ++e)
                if (check_case(edge[a], edge[b], eax_values[e])) return 1;
    for (unsigned i = 0; i < 16384; ++i)
        if (check_case(random_bits(), random_bits(), random_bits())) return 1;
    _mm_setcsr(saved_mxcsr);
    printf("PASS: %u exact production LAHF/TEST/JP-JNP cases vs host UCOMISS and COMISS flags\n", checks);
    return 0;
}
