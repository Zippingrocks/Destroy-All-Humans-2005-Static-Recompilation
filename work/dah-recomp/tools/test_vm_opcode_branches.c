/* Independent expected semantics from original 0x196E6A..0x197006 bytes.
 * vm_opcode_fixture.inc is extracted unchanged from production at test time.
 * Subcalls are ABI-recording mocks; this is not an emulator/game launch. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static uint32_t memory_words[0x240000u / 4u];
#define MEM32(a) (*(uint32_t *)((uint8_t *)memory_words + (uint32_t)(a)))
#define MEMF(a) (*(float *)((uint8_t *)memory_words + (uint32_t)(a)))
#define PUSH32(s,v) do { (s) -= 4u; MEM32(s) = (uint32_t)(v); } while (0)
static uint32_t eax, ebx, ecx, edx, esi, edi, esp, g_seh_ebp;
typedef union { float f[4]; uint32_t u[4]; } TestXmm;
static TestXmm xmm0, xmm1;
static TestXmm XMM_SCALAR(float value) { TestXmm result = {{ value, 0, 0, 0 }}; return result; }
static uint32_t next_frame, next_stream, next_calls;
static unsigned assertions, cases;
static uint32_t convert_calls, convert_addresses[3], convert_result;
static uint32_t error_calls, error_messages[3];
static uint32_t iterator_calls, iterator_arg, iterator_handle, iterator_result;
static uint32_t aggregate_calls, aggregate_keys[512], aggregate_owners[512];
static uint32_t operator_calls, operator_id, operator_frame, operator_owner;
#define CHECK(c) do { ++assertions; if (!(c)) { \
    fprintf(stderr, "FAIL line=%u case=%u expression=%s\n", __LINE__, cases, #c); exit(1); } } while (0)
static void dah_script_dispatch_next(uint32_t frame)
{ next_frame = frame; next_stream = MEM32(esp + 0x10u); ++next_calls; }
static void sub_00195E20(void)
{
    CHECK(convert_calls < 3); convert_addresses[convert_calls++] = ecx;
    if (!convert_result) MEM32(ecx) = 2;
    eax = convert_result; esp += 4;
}
static void sub_001925A0(void)
{
    CHECK(ecx == edi); CHECK(error_calls < 3);
    error_messages[error_calls++] = edx; esp += 4;
}
static void sub_00197B00(void)
{
    CHECK(ecx == edi); ++iterator_calls; iterator_arg = MEM32(esp + 4);
    iterator_handle = edx; eax = iterator_result; esp += 8;
}
static void sub_00197EE0(void)
{
    CHECK(ecx == edi && MEM32(esp) == 0x196AA5); CHECK(aggregate_calls < 512);
    aggregate_keys[aggregate_calls] = MEM32(esp + 4); aggregate_owners[aggregate_calls] = edx;
    eax = 0x14000u + aggregate_calls++ * 8u;
    ecx = edx = 0xDEADBEEF; esp += 8; /* original RET 4 plus return address */
}
static void sub_00196350(void)
{
    ++operator_calls; operator_id = ebx; operator_frame = esi; operator_owner = eax;
    esp += 4;
}
#include "vm_opcode_fixture.inc"

static uint32_t token(uint32_t opcode, int32_t displacement)
{ return (((uint32_t)displacement + 0x1FFFFFFu) << 6u) | opcode; }
static uint32_t expected_branch(uint32_t stream, uint32_t instruction)
{
    int64_t displacement = (int64_t)(instruction >> 6u) - 33554431;
    return stream + (uint32_t)(displacement * 4);
}
static void reset(uint32_t instruction, uint32_t stream)
{
    ++cases; memset(memory_words, 0xCD, sizeof(memory_words));
    eax = ebx = ecx = edx = 0xABABABAB; esi = instruction;
    edi = 0x2000; esp = 0x10000; g_seh_ebp = 0x8000;
    MEM32(esp + 0x10) = stream; MEMF(0x225C20) = 0;
    next_calls = next_frame = next_stream = 0;
    convert_calls = error_calls = iterator_calls = 0; convert_result = 0;
    iterator_result = iterator_arg = iterator_handle = 0;
    aggregate_calls = operator_calls = operator_id = operator_frame = operator_owner = 0;
}
static void checked_next(uint32_t frame, uint32_t stream)
{
    CHECK(next_calls == 1); CHECK(next_frame == frame); CHECK(next_stream == stream);
    CHECK(esp == 0x10000); CHECK(edi == 0x2000);
}
static float from_bits(uint32_t bits) { float value; memcpy(&value, &bits, 4); return value; }
static uint32_t float_bits(float value) { uint32_t bits; memcpy(&bits, &value, 4); return bits; }
static void test_conditions(void)
{
    const int32_t offsets[] = { -33554431, -512, -1, 0, 1, 512, 33554432 };
    const uint32_t streams[] = { 0, 0x4000, 0xFFFFFFFCu };
    for (uint32_t tag = 0; tag < 10; ++tag)
    for (unsigned o = 0; o < sizeof(offsets) / sizeof(offsets[0]); ++o)
    for (unsigned s = 0; s < sizeof(streams) / sizeof(streams[0]); ++s) {
        uint32_t instruction = token(0x28u, offsets[o]);
        uint32_t expected = expected_branch(streams[s], instruction);
        reset(instruction, streams[s]); MEM32(0x7FF8) = tag;
        sub_00196E6A(); checked_next(tag == 1 ? 0x7FF8u : 0x8000u, tag == 1 ? streams[s] : expected);
        CHECK(MEM32(0x7FF8) == tag); CHECK(error_calls == 0);
        reset(instruction, streams[s]); MEM32(0x7FF8) = tag;
        sub_00196E78(); checked_next(tag != 1 ? 0x7FF8u : 0x8000u, tag != 1 ? streams[s] : expected);
        CHECK(MEM32(0x7FF8) == tag); CHECK(error_calls == 0);
        reset(instruction, streams[s]); sub_00196E8A(); checked_next(0x8008, streams[s] + 4u);
        CHECK(MEM32(0x8000) == 1); CHECK(MEM32(0x8004) == 0xCDCDCDCD);
    }
}
static void setup_numbers(float current, float limit, float step)
{
    MEM32(0x7FE8) = MEM32(0x7FF0) = MEM32(0x7FF8) = 2;
    MEMF(0x7FEC) = current; MEMF(0x7FF4) = limit; MEMF(0x7FFC) = step;
}
static void test_numeric_loops(void)
{
    const uint32_t patterns[] = { 0, 0x80000000, 0x3F800000, 0xBF800000,
        0x40A00000, 0xC0A00000, 0x7F800000, 0xFF800000, 0x7FC00001, 1, 0x4B800000 };
    for (unsigned c = 0; c < sizeof(patterns) / 4; ++c)
    for (unsigned l = 0; l < sizeof(patterns) / 4; ++l)
    for (unsigned s = 0; s < sizeof(patterns) / 4; ++s) {
        float current = from_bits(patterns[c]), limit = from_bits(patterns[l]), step = from_bits(patterns[s]);
        int finished = step > 0 ? current > limit : limit > current;
        uint32_t instruction = token(0x2Bu, -11), branch = expected_branch(0x5000, instruction);
        reset(instruction, 0x5000); setup_numbers(current, limit, step);
        sub_00196EA4(); checked_next(finished ? 0x7FE8u : 0x8000u, finished ? branch : 0x5000u);
        CHECK(convert_calls == 0 && error_calls == 0); CHECK(MEM32(0x7FEC) == patterns[c]);
        reset(instruction, 0x5000); setup_numbers(current, limit, step);
        { volatile float sum = step + current; float result = sum;
          finished = step > 0 ? result > limit : limit > result;
          sub_00196F35(); checked_next(finished ? 0x7FE8u : 0x8000u, finished ? 0x5000u : branch);
          CHECK((isnan(result) && isnan(MEMF(0x7FEC))) || MEM32(0x7FEC) == float_bits(result)); }
        CHECK(error_calls == 0);
    }
    for (unsigned mask = 1; mask < 8; ++mask)
    for (unsigned fail = 0; fail < 2; ++fail) {
        const uint32_t addresses[] = { 0x7FF8, 0x7FF0, 0x7FE8 };
        const uint32_t messages[] = { 0x23F458, 0x23F438, 0x23F410 };
        reset(token(0x2B, 5), 0x5000); setup_numbers(1, 3, 1); convert_result = fail;
        unsigned expected_calls = 0;
        for (unsigned i = 0; i < 3; ++i) if (mask & (1u << i)) MEM32(addresses[i]) = 3;
        sub_00196EA4(); checked_next(0x8000, 0x5000);
        for (unsigned i = 0; i < 3; ++i) if (mask & (1u << i)) {
            CHECK(convert_addresses[expected_calls] == addresses[i]);
            if (fail) CHECK(error_messages[expected_calls] == messages[i]);
            ++expected_calls;
        }
        CHECK(convert_calls == expected_calls); CHECK(error_calls == (fail ? expected_calls : 0));
    }
    reset(token(0x2C, -7), 0x5000); setup_numbers(1, 3, 1); MEM32(0x7FE8) = 3;
    sub_00196F35(); CHECK(error_calls == 1 && error_messages[0] == 0x23F3F0);
}
static void test_generic_loops(void)
{
    const uint32_t words[] = { 2, 0x40800000, 3, 0x34567 };
    for (unsigned found = 0; found < 2; ++found)
    for (unsigned correct_tag = 0; correct_tag < 2; ++correct_tag) {
        uint32_t instruction = token(0x2D, 9), branch = expected_branch(0x5000, instruction);
        reset(instruction, 0x5000); MEM32(0x7FF8) = correct_tag ? 4 : 1;
        MEM32(0x7FFC) = 0xBEEF; memcpy((uint8_t *)memory_words + 0x12000, words, sizeof(words));
        iterator_result = found ? 0x12000 : 0;
        sub_00196F85(); checked_next(found ? 0x8010u : 0x7FF8u, found ? 0x5000u : branch);
        CHECK(iterator_calls == 1 && iterator_handle == 0xBEEF && iterator_arg == 0x23F2F8);
        CHECK(error_calls == (correct_tag ? 0u : 1u)); if (!correct_tag) CHECK(error_messages[0] == 0x23F3D4);
        if (found) CHECK(memcmp((uint8_t *)memory_words + 0x8000, words, sizeof(words)) == 0);
        reset(instruction, 0x5000); MEM32(0x7FEC) = 0xCAFE;
        memcpy((uint8_t *)memory_words + 0x12000, words, sizeof(words)); iterator_result = found ? 0x12000 : 0;
        sub_00196FD1(); checked_next(found ? 0x8000u : 0x7FE8u, found ? branch : 0x5000u);
        CHECK(iterator_calls == 1 && iterator_handle == 0xCAFE && iterator_arg == 0x7FF0);
        CHECK(error_calls == 0);
        if (found) CHECK(memcmp((uint8_t *)memory_words + 0x7FF0, words, sizeof(words)) == 0);
    }
}
static void test_aggregate(void)
{
    const uint32_t chunks[] = { 0, 1, 3, 0x1FFFF };
    for (unsigned chunk = 0; chunk < sizeof(chunks) / sizeof(chunks[0]); ++chunk)
    for (unsigned count = 0; count <= 511; ++count) {
        uint32_t instruction = (chunks[chunk] << 15u) | (count << 6u) | 0x15u;
        uint32_t base = 0x8000u - count * 8u;
        reset(instruction, 0x5000); MEM32(base - 4) = 0xC0FFEE;
        for (unsigned i = 0; i < count; ++i) {
            MEM32(base + i * 8u) = 0x123000u + i; MEM32(base + i * 8u + 4u) = 0xABCD0000u + i;
        }
        sub_00196A66(); checked_next(base, 0x5000);
        CHECK(aggregate_calls == count); CHECK(MEM32(edi) == base);
        CHECK(MEM32(0x10020) == 0xC0FFEE);
        for (unsigned i = 0; i < count; ++i) {
            CHECK(aggregate_keys[i] == chunks[chunk] * 62u + count - i);
            CHECK(aggregate_owners[i] == 0xC0FFEE);
            CHECK(MEM32(0x14000u + i * 8u) == 0x123000u + count - 1u - i);
            CHECK(MEM32(0x14004u + i * 8u) == 0xABCD0000u + count - 1u - i);
        }
    }
}
static void test_arithmetic(void)
{
    typedef void (*Handler)(void);
    const Handler handlers[] = { sub_00196B05, sub_00196BB7, sub_00196C61 };
    const uint32_t operators[] = { 5, 6, 8 };
    const uint32_t patterns[] = { 0, 0x80000000, 0x3F800000, 0xBF800000,
        0x40A00000, 0xC0A00000, 0x7F800000, 0xFF800000, 0x7FC00001, 1, 0x4B800000 };
    for (unsigned op = 0; op < 3; ++op)
    for (unsigned l = 0; l < sizeof(patterns) / 4; ++l)
    for (unsigned r = 0; r < sizeof(patterns) / 4; ++r) {
        float left = from_bits(patterns[l]), right = from_bits(patterns[r]);
        volatile float expected = op == 0 ? right + left : op == 1 ? left - right : left / right;
        reset(0, 0x5000); MEM32(0x7FF0) = MEM32(0x7FF8) = 2;
        MEMF(0x7FF4) = left; MEMF(0x7FFC) = right;
        handlers[op](); checked_next(0x7FF8, 0x5000);
        CHECK(convert_calls == 0 && operator_calls == 0);
        CHECK((isnan(expected) && isnan(MEMF(0x7FF4))) || MEM32(0x7FF4) == float_bits(expected));
    }
    for (unsigned op = 0; op < 3; ++op)
    for (unsigned mask = 1; mask < 4; ++mask)
    for (unsigned fail = 0; fail < 2; ++fail) {
        unsigned expected_calls = fail ? 1u : (mask == 3 ? 2u : 1u);
        reset(0, 0x5000); MEM32(0x7FF0) = (mask & 1) ? 3 : 2;
        MEM32(0x7FF8) = (mask & 2) ? 3 : 2; MEMF(0x7FF4) = 12; MEMF(0x7FFC) = 3;
        convert_result = fail; handlers[op](); checked_next(0x7FF8, 0x5000);
        CHECK(convert_calls == expected_calls);
        CHECK(convert_addresses[0] == ((mask & 1) ? 0x7FF0u : 0x7FF8u));
        if (expected_calls == 2) CHECK(convert_addresses[1] == 0x7FF8);
        CHECK(operator_calls == fail);
        if (fail) {
            CHECK(operator_id == operators[op] && operator_frame == 0x8000 && operator_owner == edi);
            CHECK(MEMF(0x7FF4) == 12);
        } else CHECK(MEMF(0x7FF4) == (op == 0 ? 15.0f : op == 1 ? 9.0f : 4.0f));
    }
    {
        const int32_t immediate[] = { -33554431, -16777217, -1, 0, 1, 16777217, 33554432 };
        for (unsigned i = 0; i < sizeof(immediate) / sizeof(immediate[0]); ++i)
        for (unsigned conversion = 0; conversion < 3; ++conversion) {
            volatile float expected = (float)immediate[i] + 1.25f;
            reset(token(0x1A, immediate[i]), 0x5000); MEM32(0x7FF8) = conversion ? 3 : 2;
            MEMF(0x7FFC) = 1.25f; convert_result = conversion == 2;
            sub_00196B5A(); checked_next(0x8000, 0x5000);
            CHECK(convert_calls == (conversion ? 1u : 0u));
            CHECK(operator_calls == (conversion == 2 ? 1u : 0u));
            if (conversion == 2) {
                CHECK(operator_id == 5 && operator_frame == 0x8008 && operator_owner == edi);
                CHECK(MEM32(0x8000) == 2 && MEMF(0x8004) == (float)immediate[i]);
                CHECK(MEMF(0x7FFC) == 1.25f);
            } else CHECK(MEMF(0x7FFC) == expected);
        }
    }
}
int main(void)
{
    test_conditions(); test_numeric_loops(); test_generic_loops(); test_aggregate(); test_arithmetic();
    printf("PASS: %u exact-production-handler cases, %u assertions; branch/loop semantics, aggregate counts0..511, arithmetic/conversion/fallback/immediate ABI\n", cases, assertions);
    return 0;
}
