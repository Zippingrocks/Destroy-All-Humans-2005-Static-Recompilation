/* Executes current generated functions, rather than a math reimplementation.
 * The Python driver extracts them from recomp_0009.c into the include below. */
#include <stdio.h>
#include <stdlib.h>
#define RECOMP_GENERATED_CODE
#include "recomp_types.h"

ptrdiff_t g_xbox_mem_offset;
RECOMP_TLS uint32_t g_eax, g_ecx, g_edx, g_esp, g_ebx, g_esi, g_edi;
RECOMP_TLS uint32_t g_ebp, g_seh_ebp;
RECOMP_TLS double g_fp_stack[8];
RECOMP_TLS int g_fp_top, g_fp_cmp;
RECOMP_TLS uint16_t g_fp_control_word;
RECOMP_TLS RecompXmm g_xmm0, g_xmm1, g_xmm2, g_xmm3;
RECOMP_TLS RecompXmm g_xmm4, g_xmm5, g_xmm6, g_xmm7;

#include "guest_heading_functions.inc"

static unsigned checks, negative_controls;

static void check(int okay, const char *name, float input, float output)
{
    ++checks;
    if (!okay) {
        fprintf(stderr, "FAIL %s input=%.9g output=%.9g\n", name, input, output);
        exit(1);
    }
}

static float call_acos(float input, float neighbour, int old)
{
    g_esp = 0x2F0000;
    g_fp_top = 0;
    g_esi = 0x12345678;
    MEM32(g_esp) = 0;
    MEMF(g_esp + 4) = input;
    MEMF(g_esp + 8) = neighbour;
    if (old) old_acos(); else sub_000D4520();
    check(g_esp == 0x2F0008 && g_esi == 0x12345678 && g_fp_top == 7,
          "acos ABI", input, (float)g_fp_stack[g_fp_top]);
    return (float)g_fp_stack[g_fp_top];
}

static float call_heading(float x, float y, int old)
{
    g_esp = 0x2F0000;
    g_fp_top = 0;
    g_esi = 0x12345678;
    MEM32(g_esp) = 0;
    MEMF(g_esp + 4) = x;
    MEMF(g_esp + 8) = y;
    if (old) old_heading(); else sub_000D4680();
    check(g_esp == 0x2F000C && g_esi == 0x12345678 && g_fp_top == 7,
          "heading ABI", x, (float)g_fp_stack[g_fp_top]);
    return (float)g_fp_stack[g_fp_top];
}

int main(int argc, char **argv)
{
    unsigned i, j;
    static const float samples[] = {-1.0f, -0.99f, -0.94f, -0.75f, -0.5f, -0.01f,
                                    0.0f, 0.01f, 0.5f, 0.75f, 0.94f, 0.99f, 1.0f};
    const float neighbours[] = {-10.0f, -1.0f, -0.0f, 0.0f, 1.0f, 10.0f, NAN};
    static const float axes[] = {-1.0f, -0.94f, -0.34f, 0.34f, 0.94f, 1.0f};
    const double pi = acos(-1.0);
    float heading, previous_heading;
    double maximum_error = 0.0;
    FILE *file;
    void *memory;
    if (argc != 2) return 2;
    memory = calloc(1, 0x300000);
    if (!memory) return 2;
    g_xbox_mem_offset = (ptrdiff_t)(uintptr_t)memory;
    file = fopen(argv[1], "rb");
    if (!file || fread(memory, 1, 0x300000, file) != 0x300000) return 2;
    fclose(file);
    /* Exact table indexing/input construction in original D4390. The table
     * uses standard acos; this is initialization, not the function tested. */
    for (i = 0; i < 64; ++i) {
        float input;
        MEM32(0x2F0100) = (i | 0x1C0u) << 21;
        input = 1.0f - MEMF(0x2F0100);
        MEMF(0x278A60 + i * 4) = (float)acos(input);
    }
    for (i = 0; i < sizeof(samples) / sizeof(samples[0]); ++i) {
        float reference = call_acos(samples[i], 1.0f, 0);
        double error = fabs(reference - acos(samples[i]));
        if (error > maximum_error) maximum_error = error;
        check(error < 0.005, "retail acos approximation", samples[i], reference);
        for (j = 0; j < sizeof(neighbours) / sizeof(neighbours[0]); ++j) {
            float actual = call_acos(samples[i], neighbours[j], 0);
            float previous = call_acos(samples[i], neighbours[j], 1);
            check(memcmp(&reference, &actual, sizeof(float)) == 0,
                  "acos independent of adjacent caller word", samples[i], actual);
            if (fabsf(actual - previous) > 0.1f) ++negative_controls;
        }
        check(fabs(call_acos(samples[i], 1.0f, 0) +
                   call_acos(-samples[i], 1.0f, 0) - pi) < 0.000001,
              "acos signed symmetry", samples[i], reference);
    }
    for (i = 0; i < sizeof(axes) / sizeof(axes[0]); ++i) {
        for (j = 0; j < sizeof(axes) / sizeof(axes[0]); ++j) {
            float actual = call_heading(axes[i], axes[j], 0);
            double error = fabs(actual - atan2(axes[j], axes[i]));
            if (error > maximum_error) maximum_error = error;
            check(error < 0.005, "heading quadrant", axes[i], actual);
        }
    }
    heading = call_heading(-0.94f, -0.34f, 0);
    previous_heading = call_heading(-0.94f, -0.34f, 1);
    check(cos(heading) < 0 && cos(previous_heading) > 0,
          "pre-fix control reproduces reflected X", -0.94f, previous_heading);
    check(negative_controls > 0, "pre-fix controls must fail", 0, 0);
    printf("%u actual-function checks passed; %u pre-fix stack-dependence failures reproduced; "
           "maximum approximation error %.9g rad.\n", checks, negative_controls, maximum_error);
    printf("Farm heading input x=-0.94 y=-0.34: fixed %.9g, pre-fix %.9g; "
           "cosine %.9g versus %.9g.\n", heading, previous_heading,
           cos(heading), cos(previous_heading));
    free(memory);
    return 0;
}
