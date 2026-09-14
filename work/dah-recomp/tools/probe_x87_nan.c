/* Test-only hardware FADDP NaN propagation probe; link classify oracle.obj. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
extern void dah_test_faddp(const uint64_t *, const uint64_t *, uint64_t *, uint16_t *);
extern void dah_test_faddp80(const uint8_t *, const uint8_t *, uint64_t *, uint16_t *);
static void extended_nan(uint64_t bits, uint8_t out[10])
{
    uint64_t mantissa = UINT64_C(0x8000000000000000) | ((bits & UINT64_C(0x000FFFFFFFFFFFFF)) << 11);
    uint16_t exponent = (uint16_t)(0x7FFFu | (bits >> 48 & 0x8000u));
    memcpy(out, &mantissa, 8); memcpy(out + 8, &exponent, 2);
}
int main(int argc, char **argv)
{
    static const struct { const char *name; uint64_t bits; } values[] = {
        {"q1+", UINT64_C(0x7FF8000000000001)}, {"q2+", UINT64_C(0x7FF8000000000002)},
        {"q1-", UINT64_C(0xFFF8000000000001)}, {"q2-", UINT64_C(0xFFF8000000000002)},
        {"s1+", UINT64_C(0x7FF0000000000001)}, {"s2+", UINT64_C(0x7FF0000000000002)},
        {"s1-", UINT64_C(0xFFF0000000000001)}, {"s2-", UINT64_C(0xFFF0000000000002)},
        {"num", UINT64_C(0x4000000000000000)}
    };
    unsigned i, j;
    int raw80 = argc > 1 && strcmp(argv[1], "80") == 0;
    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
        for (j = 0; j < sizeof(values) / sizeof(values[0]); ++j) {
            uint64_t result = 0; uint16_t status = 0;
            if (raw80) {
                uint8_t first[10], second[10];
                if (i == 8 || j == 8) continue; /* This encoder is only for NaNs. */
                extended_nan(values[i].bits, first); extended_nan(values[j].bits, second);
                dah_test_faddp80(first, second, &result, &status);
            } else dah_test_faddp(&values[i].bits, &values[j].bits, &result, &status);
            printf("%s %s -> %016llX status%04X\n", values[i].name, values[j].name,
                (unsigned long long)result, status);
        }
    return 0;
}
