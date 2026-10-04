/* Exact production-function scheduling harness. No renderer, game, or input.
 * Bink callees are ABI-aware mocks; this tests the adapter, not Bink decoding. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4101 4102 4189) /* Generated unused flag variable/labels. */
static uint8_t ram[0x300000], before[sizeof(ram)];
static uint32_t eax, ecx, edx, esp;
static unsigned checks, scenarios, wait_calls, io_services, decode_calls;
static unsigned lock_calls, copy_calls, material_calls, next_calls, close_calls, release_calls;
static uint32_t wait_sequence[16], wait_length, wait_index, copy_result;
static unsigned schedule_mode;
static uint64_t host_tick, next_movie_tick;
static int dah_archives_movie_active, force_archives;
enum { STACK = 0x100000, HANDLE = 0x180000, TEXTURE0 = 0x181000,
       TEXTURE1 = 0x182000, PIXELS = 0x190000, UPDATE_PC = 0x5A46D, OPEN_PC = 0x123299 };
#define MEM8(a) (ram[(uint32_t)(a)])
#define MEM16(a) (*(uint16_t *)(void *)(ram + (uint32_t)(a)))
#define SMEM16(a) (*(int16_t *)(void *)(ram + (uint32_t)(a)))
#define MEM32(a) (*(uint32_t *)(void *)(ram + (uint32_t)(a)))
#define LO8(a) ((uint8_t)(a))
#define LO16(a) ((uint16_t)(a))
#define SET_LO8(a,b) ((a) = ((a) & 0xFFFFFF00u) | (uint8_t)(b))
#define TEST_Z(a,b) (((a) & (b)) == 0)
#define TEST_NZ(a,b) (((a) & (b)) != 0)
#define CMP_NE(a,b) ((a) != (b))
#define PUSH32(s,v) ((s) -= 4, MEM32(s) = (uint32_t)(v))
#define CHECK(c) do { ++checks; if (!(c)) { fprintf(stderr, "FAIL line %u: %s\n", (unsigned)__LINE__, #c); exit(1); } } while (0)

static void dah_movie_trace(const char *stage, uint32_t *calls) { (void)stage; ++*calls; }
static void sub_0020C950(void)
{
    CHECK(MEM32(esp) == 0x122D9E && MEM32(esp + 4) == HANDLE);
    ++wait_calls; ++io_services; /* A pending poll still services native IO/audio. */
    CHECK(wait_calls < 10000);
    if (schedule_mode) eax = host_tick < next_movie_tick;
    else { CHECK(wait_index < wait_length); eax = wait_sequence[wait_index++]; }
    esp += 8;
}
static void sub_0020CE60(void)
{
    CHECK(MEM32(esp) == 0x122DAE && MEM32(esp + 4) == HANDLE);
    ++decode_calls; eax = 0; esp += 8;
}
static void sub_001DC8D0(void)
{
    uint32_t out = MEM32(esp + 12);
    CHECK(MEM32(esp) == 0x122DCD);
    CHECK(MEM32(esp + 4) == (uint32_t)(MEM16(0x2591AC) ? TEXTURE1 : TEXTURE0));
    CHECK(MEM32(esp + 8) == 0 && MEM32(esp + 16) == 0 && MEM32(esp + 20) == 0);
    CHECK(out == STACK - 8);
    MEM32(out) = 2560; MEM32(out + 4) = PIXELS;
    ++lock_calls; eax = 0; esp += 24;
}
static void sub_0020CE20(void)
{
    CHECK(MEM32(esp) == 0x122DEE && MEM32(esp + 4) == HANDLE);
    CHECK(MEM32(esp + 8) == PIXELS && MEM32(esp + 12) == 2560);
    CHECK(MEM32(esp + 16) == 448 && MEM32(esp + 20) == 0 && MEM32(esp + 24) == 0);
    CHECK(MEM32(esp + 28) == 0x80000003u);
    ++copy_calls; eax = copy_result; esp += 32;
}
static void sub_000E5FF0(void)
{
    CHECK(MEM32(esp) == 0x122E13 && ecx == 0x2591C8);
    CHECK(MEM32(esp + 4) == 0 && MEM32(esp + 8) == (MEM16(0x2591AC) ? 72u : 71u));
    ++material_calls; eax = 0; esp += 12;
}
static void sub_0020D460(void)
{
    CHECK(MEM32(esp) == 0x122E32 && MEM32(esp + 4) == HANDLE);
    ++next_calls; ++MEM32(HANDLE + 0xC);
    if (schedule_mode) next_movie_tick += 120; /* 25fps in a 3000Hz test clock. */
    eax = 0; esp += 8;
}
static void sub_00122CA0(void)
{
    CHECK(MEM32(esp) == 0x122E44);
    ++close_calls; MEM32(0x28681C) = 0; MEM32(0x286804) = 2;
    eax = 0x12345678; esp += 4;
}
static void sub_00122D20(void)
{
    CHECK(MEM32(esp) == 0x122D8D);
    ++release_calls; MEM16(0x2591AC) = 0xFFFFu;
    eax = 0xFEDCBA98u; esp += 4;
}

#include "movie_nonblock_fixture.inc"

static void reset(void)
{
    memset(ram, 0xA5, sizeof(ram));
    eax = 0x12345678; ecx = edx = 0;
    wait_calls = io_services = decode_calls = lock_calls = copy_calls = 0;
    material_calls = next_calls = close_calls = release_calls = 0;
    wait_index = wait_length = copy_result = schedule_mode = 0;
    host_tick = next_movie_tick = 0;
    dah_archives_movie_active = force_archives;
    MEM32(0x286804) = 0; MEM32(0x28681C) = HANDLE;
    MEM32(0x286820) = 0x10203040;
    MEM16(0x2591AC) = 0; MEM16(0x286808) = 71; MEM16(0x28680A) = 72;
    MEM32(0x286810) = TEXTURE0; MEM32(0x286814) = TEXTURE1;
    MEM32(HANDLE + 4) = 448; MEM32(HANDLE + 8) = 100000;
    MEM32(HANDLE + 0xC) = 1;
    ++scenarios;
}
static void invoke(uint32_t return_pc)
{
    esp = STACK; MEM32(esp) = return_pc;
    sub_00122D70();
    CHECK(esp == STACK + 4);
    CHECK(MEM32(STACK) == return_pc);
}
static void pending_snapshot(void)
{
    memcpy(before, ram, sizeof(ram));
}
static void verify_pending_snapshot(void)
{
    /* Ignore only the function's locals/call arguments/return-PC stack area. */
    CHECK(memcmp(before, ram, STACK - 128) == 0);
    CHECK(memcmp(before + STACK + 4, ram + STACK + 4, sizeof(ram) - STACK - 4) == 0);
}
static void sequence(uint32_t a, uint32_t b, uint32_t c)
{
    wait_sequence[0] = a; wait_sequence[1] = b; wait_sequence[2] = c;
    wait_length = 3; wait_index = 0;
}

int main(int argc, char **argv)
{
    unsigned enabled, i;
    CHECK(argc == 2 || argc == 3);
    enabled = (unsigned)strtoul(argv[1], NULL, 10);
    force_archives = argc == 3 && (unsigned)strtoul(argv[2], NULL, 10) == 1u;
    reset(); sequence(1, 1, 0); pending_snapshot(); invoke(UPDATE_PC);
    CHECK(LO8(eax) == 1);
    if (enabled) {
        CHECK(wait_calls == 1 && io_services == 1);
        CHECK(!decode_calls && !copy_calls && !lock_calls && !material_calls && !next_calls);
        CHECK(!close_calls && !release_calls); verify_pending_snapshot();
        invoke(UPDATE_PC); CHECK(wait_calls == 2 && !decode_calls); verify_pending_snapshot();
        invoke(UPDATE_PC);
    }
    CHECK(wait_calls == 3 && io_services == 3);
    CHECK(decode_calls == 1 && copy_calls == 1 && lock_calls == 1 && material_calls == 1 && next_calls == 1);
    CHECK(MEM32(HANDLE + 0xC) == 2 && MEM16(0x2591AC) == 1 && MEM32(0x286820) == 0);

    /* Initial preload and all unproven callers retain exact native waiting. */
    for (i = 0; i < 3; ++i) {
        reset(); sequence(1, 0x80000000u, 0);
        invoke(i == 0 ? OPEN_PC : i == 1 ? UPDATE_PC + 1 : 0);
        CHECK(wait_calls == 3 && decode_calls == 1 && next_calls == 1 && LO8(eax) == 1);
    }
    /* Any nonzero native wait result is pending; preserved globals/texture. */
    if (enabled) for (i = 1; i <= 128; ++i) {
        reset(); sequence(0x10204081u * i, 0, 0); pending_snapshot(); invoke(UPDATE_PC);
        CHECK(wait_calls == 1 && !decode_calls && !next_calls && LO8(eax) == 1);
        verify_pending_snapshot();
    }
    /* A failed copy still takes the original NextFrame route, without flip. */
    for (i = 0; i < 2; ++i) {
        reset(); MEM16(0x2591AC) = (uint16_t)i; copy_result = 7;
        sequence(0, 0, 0); invoke(UPDATE_PC);
        CHECK(decode_calls == 1 && copy_calls == 1 && !material_calls && next_calls == 1);
        CHECK(MEM16(0x2591AC) == i && MEM32(0x286820) == 7 && LO8(eax) == 1);
    }
    /* Both native double-buffer states still select/flip the right surface. */
    for (i = 0; i < 2; ++i) {
        reset(); MEM16(0x2591AC) = (uint16_t)i;
        sequence(0, 0, 0); invoke(UPDATE_PC);
        CHECK(MEM16(0x2591AC) == (1u - i) && material_calls == 1 && next_calls == 1);
    }
    /* Native final-frame close and two-update release countdown unchanged. */
    reset(); MEM32(HANDLE + 8) = 2; sequence(0, 0, 0); invoke(UPDATE_PC);
    CHECK(close_calls == 1 && MEM32(0x28681C) == 0 && MEM32(0x286804) == 2 && LO8(eax) == 0);
    invoke(UPDATE_PC);
    CHECK(wait_calls == 1 && MEM32(0x286804) == 1 && LO8(eax) == 1 && !release_calls);
    invoke(UPDATE_PC);
    CHECK(wait_calls == 1 && MEM32(0x286804) == 0 && LO8(eax) == 0 && release_calls == 1);
    CHECK(MEM16(0x2591AC) == 0xFFFFu);

    if (enabled) {
        unsigned pending = 0;
        reset(); schedule_mode = 1;
        for (i = 0; i < 150; ++i) {
            unsigned decoded_before = decode_calls;
            host_tick = i * 100u; /* Exactly 30 host updates/sec for five seconds. */
            pending_snapshot(); invoke(UPDATE_PC);
            CHECK(wait_calls == i + 1 && io_services == i + 1 && LO8(eax) == 1);
            CHECK(next_movie_tick == (uint64_t)decode_calls * 120u);
            if (decoded_before == decode_calls) { ++pending; verify_pending_snapshot(); }
            else CHECK(decode_calls == decoded_before + 1);
        }
        CHECK(wait_calls == 150 && decode_calls == 125 && next_calls == 125 && copy_calls == 125);
        CHECK(pending == 25 && MEM32(HANDLE + 0xC) == 126 && next_movie_tick == 15000);
        CHECK(!close_calls && !release_calls);
        printf("PASS: simulated five seconds = 150 host updates, 125 native-rate decode/advance events, 25 untouched pending frames\n");
    }
    printf("PASS: movie scheduling enabled=%u, %u scenarios, %u assertions; native ABI/texture/preload/close preserved\n", enabled, scenarios, checks);
    return 0;
}
