#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t ram[0x10000];
static uint32_t g_eax, g_esp;
static unsigned checks, forwarded;

#define MEM32(a) (*(uint32_t *)(ram + (uint32_t)(a)))
#define SET_LO8(r,v) ((r) = ((r) & 0xFFFFFF00u) | ((uint8_t)(v)))
#define CHECK(c) do { ++checks; if (!(c)) { \
    fprintf(stderr, "FAIL line=%u: %s\n", __LINE__, #c); exit(1); \
} } while (0)

static void sub_000117D0(void)
{
    ++forwarded;
    g_eax = 0x117D0ACEu;
    g_esp += 4u;
}

#include "retail_type_callbacks.inc"

int main(void)
{
    struct getter { void (*function)(void); uint32_t value; } getters[] = {
        { sub_00012700, 0x68F1100Bu }, { sub_00012A40, 0x1975BCEDu },
        { sub_00015AE0, 0x177F1145u }, { sub_000161C0, 0xF90E4ACEu },
        { sub_0005FA20, 0xF2D43FBFu }, { sub_0009A260, 0x71C8DF8Fu },
        { sub_0009C2D0, 0x8BFCF9A0u }, { sub_000A1270, 0x6460CAB8u },
        { sub_000A1DB0, 0x68195EBCu }, { sub_000A4980, 0x9BCE23F0u },
    };
    for (unsigned i = 0; i < sizeof(getters) / sizeof(getters[0]); ++i) {
        memset(ram, 0xCD, sizeof(ram));
        g_eax = 0xDEADBEEFu; g_esp = 0x8000u; MEM32(g_esp) = 0xCAFEBABEu;
        getters[i].function();
        CHECK(g_eax == getters[i].value);
        CHECK(g_esp == 0x8004u);
        CHECK(MEM32(0x8000u) == 0xCAFEBABEu);
    }

    {
        const uint32_t accepted[] = {
            0x1975BCEDu, 0xB405C7B6u, 0x883240FCu, 0x38082939u, 0xA75FFAEBu
        };
        for (unsigned i = 0; i < sizeof(accepted) / sizeof(accepted[0]); ++i) {
            g_esp = 0x8000u; g_eax = 0xAA55CC33u;
            MEM32(g_esp) = 0xCAFEBABEu; MEM32(g_esp + 4u) = accepted[i];
            sub_00012A10();
            CHECK((g_eax & 0xFFFFFF00u) == (accepted[i] & 0xFFFFFF00u));
            CHECK((g_eax & 0xFFu) == 1u);
            CHECK(g_esp == 0x8008u);
        }
        const uint32_t rejected[] = { 0u, 1u, 0x1975BCECu, 0xA75FFAEAu, 0xFFFFFFFFu };
        for (unsigned i = 0; i < sizeof(rejected) / sizeof(rejected[0]); ++i) {
            g_esp = 0x8000u; MEM32(g_esp) = 0xCAFEBABEu;
            MEM32(g_esp + 4u) = rejected[i];
            sub_00012A10();
            CHECK((g_eax & 0xFFFFFF00u) == (rejected[i] & 0xFFFFFF00u));
            CHECK((g_eax & 0xFFu) == 0u);
            CHECK(g_esp == 0x8008u);
        }
    }

    forwarded = 0u; g_esp = 0x8000u; MEM32(g_esp) = 0xCAFEBABEu;
    sub_000127D0();
    CHECK(forwarded == 1u);
    CHECK(g_eax == 0x117D0ACEu);
    CHECK(g_esp == 0x8004u);
    CHECK(MEM32(0x8000u) == 0xCAFEBABEu);
    printf("PASS: %u retail table callback checks\n", checks);
    return 0;
}
