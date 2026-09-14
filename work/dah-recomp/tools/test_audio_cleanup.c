/* Exact complete callback bodies are extracted by test_audio_cleanup.mjs. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t ram[0x230000];
static uint32_t eax, ebx, ecx, edx, esi, edi, esp;
static uint32_t lock_result, release_result, expected_argument, expected_action;
static unsigned lock_calls, release_calls, leave_calls, action_calls, cases;
static uint32_t queue_result;
static unsigned destroy_calls, queue_calls, stop_calls, stream_calls;
static unsigned buffer_destructor_calls, free_calls;
static unsigned expected_destructor;
static uint32_t g_ebp, g_seh_ebp, format_result, start_result;
static unsigned flush_calls, reconfigure_calls, format_calls, start_calls, packet_calls;
static uint32_t expected_format_word, expected_packet, packet_result;
static unsigned wrapper_mode, stream_action_mode, query_calls;
static const uint32_t stack = 0x10000, this_pointer = 0x12000;
static const uint32_t actions[] = {0x1f355a, 0x1f5076, 0x1f4c37, 0x1f4d24, 0x1f4dd4, 0x1f4865};
static const uint32_t stream_actions[] = {0x1f355a, 0x1f1c42, 0x1f1e8c, 0x1f2084, 0x1f18c5, 0x1f241a};
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "case=%u line=%d: %s\n", cases, __LINE__, #x); exit(1); } } while (0)
static void *guest_ptr(uint32_t address)
{
    CHECK(address < sizeof(ram) - 3);
    return &ram[address];
}
#define MEM32(a) (*(volatile uint32_t *)guest_ptr((uint32_t)(a)))
#define MEM16(a) (*(volatile uint16_t *)guest_ptr((uint32_t)(a)))
#define MEM8(a) (*(volatile uint8_t *)guest_ptr((uint32_t)(a)))
#define PUSH32(sp, value) do { uint32_t pv = (uint32_t)(value); (sp) -= 4; MEM32(sp) = pv; } while (0)
#define POP32(sp, value) do { (value) = MEM32(sp); (sp) += 4; } while (0)
#define g_esp esp
#define LO8(a) ((uint8_t)(a))
#define ZX8(a) ((uint32_t)(uint8_t)(a))
#define ZX16(a) ((uint32_t)(uint16_t)(a))
#define SET_LO8(a, b) ((a) = ((a) & 0xffffff00u) | (uint8_t)(b))
#define CMP_EQ(a,b) ((uint32_t)(a) == (uint32_t)(b))
#define CMP_NE(a,b) ((uint32_t)(a) != (uint32_t)(b))
#define CMP_BE(a,b) ((uint32_t)(a) <= (uint32_t)(b))
#define TEST_Z(a,b) (((uint32_t)(a) & (uint32_t)(b)) == 0)
#define TEST_S(a,b) ((int32_t)((uint32_t)(a) & (uint32_t)(b)) < 0)
static void sub_001EC935(void)
{
    const uint32_t returns[] = {0x1ece84, 0x1ed378, 0x1ed276, 0x1ed3c3};
    CHECK(MEM32(esp) == returns[wrapper_mode]);
    ++lock_calls;
    eax = lock_result;
    ecx = 0xdead4321;
    esp += 4;
}
static void sub_001EC7CA(void)
{
    CHECK(MEM32(esp) == (wrapper_mode == 2 ? 0x1ed2a6u : 0x1eceb0u));
    CHECK(MEM32(esp + 4) == (wrapper_mode == 2 ? 0x17004u : expected_argument));
    ++release_calls;
    eax = release_result;
    edx = 0xbadcafe;
    esp += 8;
}
static void indirect_call(uint32_t target, uint32_t before_args)
{
    if (target == 0xd00d0001) {
        CHECK(MEM32(esp) == 0x1ec7c7 && MEM32(esp + 4) == 1);
        CHECK(ecx == this_pointer && MEM32(ecx + 4) == 0);
        CHECK(esp + 8 == before_args);
        ++destroy_calls;
        eax = release_result;
        esp += 8;
        return;
    }
    if (target == 0xd00d0002) {
        CHECK(MEM32(esp) == 0x1f4a3a && MEM32(esp + 4) == 1);
        CHECK(ecx == this_pointer && stop_calls == 1);
        CHECK(MEM32(esp + 8) == 0 && MEM32(esp + 12) == 0 && MEM32(esp + 16) == 0);
        CHECK(esp + 20 == before_args);
        ++stream_calls;
        eax = 0xdead1234;
        esp += 20;
        return;
    }
    CHECK(target == 0xc0de1234);
    CHECK(MEM32(esp + 4) == 0x20a1c0);
    const uint32_t error_returns[] = {0x1ece9f, 0x1ed393, 0x1ed291, 0x1ed3de};
    const uint32_t success_returns[] = {0x1ecec1, 0x1ed3b7, 0x1ed2b7, 0x1ed407};
    CHECK(MEM32(esp) == (MEM32(0x20a1b4) ? error_returns[wrapper_mode] : success_returns[wrapper_mode]));
    CHECK(esp + 8 == before_args);
    ++leave_calls;
    eax = 0xdeadbeef; /* Must not destroy the saved release return value. */
    esp += 8;
}
#define RECOMP_ICALL_SAFE(target, before_args) indirect_call(target, before_args)
static void sub_001F17AD(void)
{
    CHECK(ecx == this_pointer + 0x68);
    CHECK(MEM32(esp) == 0x1f4a0a && MEM32(esp + 4) == 3);
    ++queue_calls;
    eax = queue_result;
    ecx = 0xdead1111;
    esp += 8;
}
static void sub_001F4003(void)
{
    CHECK(ecx == this_pointer);
    CHECK(MEM32(esp) == 0x1f4a1f && MEM32(esp + 4) == 0);
    CHECK(MEM8(0x13000 + 0x3f) == 0x80);
    ++stop_calls;
    eax = 0xdead2222;
    ecx = 0xdead3333;
    esp += 8;
}
static void sub_001ECE04(void)
{
    CHECK(expected_destructor == 0);
    CHECK(ecx == this_pointer && MEM32(esp) == 0x1ee1e6);
    ++buffer_destructor_calls;
    eax = 0xdead5555;
    ecx = 0xdead6666;
    esp += 4;
}
static void sub_001EEFF1(void)
{
    CHECK(expected_destructor == 1);
    CHECK(ecx == this_pointer && MEM32(esp) == 0x1ef68d);
    ++buffer_destructor_calls;
    eax = 0xdead5555;
    ecx = 0xdead6666;
    esp += 4;
}
static void sub_001F5091(void)
{
    CHECK(expected_destructor == 2);
    CHECK(ecx == this_pointer && MEM32(esp) == 0x1f5156);
    ++buffer_destructor_calls;
    eax = 0xdead5555;
    ecx = 0xdead6666;
    esp += 4;
}
static void sub_001EFB85(void)
{
    const uint32_t returns[] = {0x1ee1f3, 0x1ef69a, 0x1f5163, 0x1f2508};
    CHECK(MEM32(esp) == returns[expected_destructor] && MEM32(esp + 4) == this_pointer);
    CHECK(buffer_destructor_calls == 1);
    ++free_calls;
    eax = 0xdead7777;
    esp += 8;
}
static void action(unsigned n)
{
    CHECK(n == expected_action);
    CHECK(ecx == this_pointer);
    if (n >= 3) CHECK(MEM32(esp + 4) == expected_argument);
    ++action_calls;
    eax = actions[n] ^ 0x80000000u;
    ecx = 0xabcd1234;
    edx = 0x1234abcd;
    esp += n >= 3 ? 8 : 4;
}
static void stream_action(unsigned n)
{
    const uint32_t returns[] = {0x1f24f0, 0x1f24e9, 0x1f24e2, 0x1f24db, 0x1f24d4, 0x1f24c9};
    CHECK(stream_action_mode && n == expected_action && ecx == this_pointer);
    CHECK(MEM32(esp) == returns[n]);
    CHECK(esp == stack - (n >= 4 ? 8u : 4u));
    if (n >= 4) CHECK(MEM32(esp + 4) == expected_argument);
    ++action_calls;
    eax = stream_actions[n] ^ 0x80000000u;
    ecx = 0xabcd1234; edx = 0x1234abcd;
    esp += n >= 4 ? 8 : 4;
}
static void sub_001F355A(void) { if (stream_action_mode) stream_action(0); else action(0); }
static void sub_001F5076(void) { action(1); }
static void sub_001F4C37(void) { action(2); }
static void sub_001F4D24(void) { action(3); }
static void sub_001F4DD4(void) { action(4); }
static void sub_001F4865(void) { action(5); }
static void sub_001F1E8C(void) { stream_action(2); }
static void sub_001F2084(void) { stream_action(3); }
static void sub_001F18C5(void) { stream_action(4); }
static void sub_001F241A(void) { stream_action(5); }

static void sub_001F1FA4(void)
{
    if (wrapper_mode == 1) {
        CHECK(ecx == this_pointer && MEM32(esp) == 0x1ed3a8);
        CHECK(MEM32(esp + 4) == 0 && esp == stack - 12);
        CHECK(lock_calls == 1 && flush_calls == 0 && leave_calls == 0);
        ++flush_calls;
        eax = release_result; ecx = 0xdead1001; edx = 0xdead1002;
        esp += 8;
        return;
    }
    CHECK(ecx == this_pointer && MEM32(esp) == 0x1f2274);
    CHECK(MEM32(esp + 4) == 0 && esp == stack - 16);
    CHECK(flush_calls == 0 && reconfigure_calls == 0 && format_calls == 0);
    ++flush_calls;
    eax = 0xdead1000; ecx = 0xdead1001; edx = 0xdead1002;
    esp += 8;
}
static void sub_001F1C42(void)
{
    if (stream_action_mode) { stream_action(1); return; }
    CHECK(ecx == this_pointer && MEM32(esp) == 0x1f228f);
    CHECK(flush_calls == 1 && format_calls == 0 && esp == stack - 12);
    ++reconfigure_calls;
    eax = 0xdead2000; ecx = 0xdead2001; edx = 0xdead2002;
    esp += 4;
}
static void sub_001F2CFF(void)
{
    CHECK(ecx == this_pointer && MEM32(esp) == 0x1f2296);
    CHECK(esp == stack - 12 && format_calls == 0);
    ++format_calls;
    eax = format_result; ecx = 0xdead3001; edx = 0xdead3002;
    esp += 4;
}
static void sub_001F3BB4(void)
{
    CHECK(ecx == this_pointer && MEM32(esp) == 0xfeedface);
    CHECK(esp == stack && format_calls == 1 && flush_calls == 1);
    CHECK(ebx == 0x81234567 && esi == 0x98765432 && edi == 0xaabbccdd);
    CHECK(g_seh_ebp == 0x13572468);
    CHECK(MEM32(this_pointer + 0x84) == expected_format_word);
    ++start_calls;
    eax = start_result; ecx = 0xdead4001; edx = 0xdead4002;
    esp += 4;
}
static void sub_001F2200(void)
{
    CHECK(expected_destructor == 3);
    CHECK(ecx == this_pointer && MEM32(esp) == 0x1f24fb);
    ++buffer_destructor_calls;
    eax = 0xdead5555; ecx = 0xdead6666;
    esp += 4;
}
static void sub_001F15EB(void)
{
    CHECK(ecx == 0x16000 && MEM32(esp) == 0x1f1cae);
    CHECK(MEM32(esp + 4) == expected_packet && esp == stack - 8);
    CHECK(packet_calls == 0);
    CHECK(MEM32(expected_packet + 0x18) == MEM32(stack + 8));
    CHECK(MEM32(expected_packet + 0x1c) == MEM32(stack + 12));
    CHECK(MEM32(expected_packet + 0x14) == MEM32(stack + 16));
    ++packet_calls;
    eax = packet_result; ecx = 0xdead5001; edx = 0xdead5002;
    esp += 8;
}
static void sub_001F1937(void)
{
    CHECK(wrapper_mode == 3 && ecx == this_pointer && MEM32(esp) == 0x1ed3f6);
    CHECK(MEM32(esp + 4) == expected_argument && esp == stack - 16);
    CHECK(lock_calls == 1 && query_calls == 0 && leave_calls == 0);
    ++query_calls;
    eax = release_result; ecx = 0xdead6001; edx = 0xdead6002;
    esp += 8;
}

#pragma warning(push)
#pragma warning(disable: 4101 4102 4189)
#include "audio_cleanup_fixture.inc"
#pragma warning(pop)

static void reset(uint32_t arg0, uint32_t arg1)
{
    memset(ram + stack - 128, 0xa5, 256);
    esp = stack;
    MEM32(esp) = 0xfeedface;
    MEM32(esp + 4) = arg0;
    MEM32(esp + 8) = arg1;
    eax = 0xbad00000;
    ebx = 0x81234567; esi = 0x98765432; edi = 0xaabbccdd;
    ecx = this_pointer;
    lock_calls = release_calls = leave_calls = action_calls = 0;
    destroy_calls = queue_calls = stop_calls = stream_calls = 0;
    buffer_destructor_calls = free_calls = 0;
    flush_calls = reconfigure_calls = format_calls = start_calls = packet_calls = 0;
    query_calls = 0;
    g_ebp = 0xabcdef00; g_seh_ebp = 0x13572468;
}
static void check_registers(void)
{
    CHECK(ebx == 0x81234567 && esi == 0x98765432 && edi == 0xaabbccdd);
    CHECK(MEM32(stack) == 0xfeedface && MEM32(stack + 12) == 0xa5a5a5a5);
}
static void test_stream_format(void)
{
    const uint16_t formats[] = {0, 1, 0x69, 0xffff};
    const uint8_t bits[] = {0, 8, 16, 24, 32, 255};
    const uint8_t channels[] = {0, 1, 2, 3, 6, 31, 32, 33, 255};
    const uint8_t states[] = {0, 1, 2, 255};
    const uint32_t statuses[] = {0, 1, 0x7fffffff, 0x80000000, 0xffffffff};
    const uint32_t words[] = {0, 0xffffffff, 0x5aa55aa5};
    for (unsigned f = 0; f < sizeof(formats) / sizeof(formats[0]); ++f)
    for (unsigned b = 0; b < sizeof(bits) / sizeof(bits[0]); ++b)
    for (unsigned c = 0; c < sizeof(channels) / sizeof(channels[0]); ++c)
    for (unsigned s = 0; s < sizeof(states) / sizeof(states[0]); ++s)
    for (unsigned h = 0; h < sizeof(statuses) / sizeof(statuses[0]); ++h)
    for (unsigned w = 0; w < sizeof(words) / sizeof(words[0]); ++w)
    for (unsigned mismatch = 0; mismatch < 2; ++mismatch) {
        reset(0x8765feed, 0x1234feed);
        const unsigned active = states[s] & 1u;
        const unsigned failed = statuses[h] >> 31;
        const uint8_t old_voices = (uint8_t)((channels[c] + 1u) / 2u + mismatch);
        MEM32(this_pointer + 0x80) = 0x14000;
        MEM32(this_pointer + 0x84) = words[w];
        MEM32(this_pointer + 0x88) = 0x87654321;
        MEM8(this_pointer + 0x12) = states[s];
        MEM8(this_pointer + 0x64) = old_voices;
        MEM16(0x14000 + 0xc) = formats[f];
        MEM8(0x14000 + 0xe) = channels[c];
        MEM8(0x14000 + 0xf) = bits[b];
        format_result = statuses[h]; start_result = 0x80070005u;
        uint32_t expected = words[w];
        if (!failed) {
            if (formats[f] == 0x69) expected = (expected & ~0x10000u) | 0x20000u;
            else if (formats[f] == 1) {
                if (bits[b] == 8) expected &= ~0x30000u;
                else if (bits[b] == 16) expected = (expected & ~0x20000u) | 0x10000u;
                else if (bits[b] == 32) expected |= 0x30000u;
            }
            expected = (expected & ~0x7c0000u) | (((uint32_t)channels[c] - 1u) & 31u) * 0x40000u;
            expected = (expected & ~0x800000u) | (channels[c] > 1 ? 0x800000u : 0);
        }
        expected_format_word = expected;
        sub_001F225D();
        CHECK(esp == stack + 4 && format_calls == 1);
        CHECK(flush_calls == active && reconfigure_calls == active * mismatch);
        CHECK(start_calls == active * (1u - failed));
        CHECK(eax == ((active && !failed) ? start_result : format_result));
        CHECK(MEM32(this_pointer + 0x84) == expected);
        CHECK(MEM32(this_pointer + 0x88) == 0x87654321);
        CHECK(MEM8(this_pointer + 0x64) == old_voices);
        CHECK(MEM32(stack + 4) == 0x8765feed && MEM32(stack + 8) == 0x1234feed);
        check_registers();
        ++cases;
    }
}
static void test_stream_packet(void)
{
    const uint32_t values[] = {0, 1, 0x80000000u, 0xffffffffu, 0x12345678u};
    for (unsigned slot = 0; slot < 6; ++slot)
    for (unsigned n = 0; n < sizeof(values) / sizeof(values[0]); ++n) {
        reset(slot, values[n]);
        memset(ram + this_pointer + 0xd0, 0xa5, 0xc0);
        MEM32(this_pointer + 8) = 0x16000;
        MEM32(stack + 12) = values[(n + 1) % 5];
        MEM32(stack + 16) = values[(n + 2) % 5];
        MEM32(stack + 20) = 0xdecafbad;
        expected_packet = this_pointer + 0xd0 + slot * 0x20;
        packet_result = values[(n + 3) % 5];
        sub_001F1C82();
        CHECK(esp == stack + 20 && packet_calls == 1 && eax == packet_result);
        CHECK(MEM32(stack) == 0xfeedface && MEM32(stack + 20) == 0xdecafbad);
        CHECK(ebx == 0x81234567 && esi == 0x98765432 && edi == 0xaabbccdd);
        for (unsigned address = this_pointer + 0xd0; address < this_pointer + 0x190; ++address)
            if (address < expected_packet + 0x14 || address >= expected_packet + 0x20)
                CHECK(MEM8(address) == 0xa5);
        ++cases;
    }
}
static void test_stream_actions_and_wrappers(void)
{
    const uint32_t values[] = {0, 1, 0x80000000u, 0xffffffffu, 0x87654321u};
    const uint32_t invalid[] = {6, 7, 255, 0x7fffffffu, 0x80000000u, 0xffffffffu};
    stream_action_mode = 1;
    for (unsigned n = 0; n < 6; ++n)
    for (unsigned v = 0; v < sizeof(values) / sizeof(values[0]); ++v) {
        expected_action = n; expected_argument = values[v];
        reset(n, expected_argument);
        sub_001F24A8();
        CHECK(esp == stack + 12 && action_calls == 1);
        CHECK(eax == (stream_actions[n] ^ 0x80000000u));
        CHECK(MEM32(stack + 4) == n && MEM32(stack + 8) == expected_argument);
        check_registers();
        ++cases;
    }
    for (unsigned n = 0; n < sizeof(invalid) / sizeof(invalid[0]); ++n) {
        reset(invalid[n], 0x1234feed);
        sub_001F24A8();
        CHECK(esp == stack + 12 && action_calls == 0 && eax == invalid[n] - 5u);
        check_registers();
        ++cases;
    }
    stream_action_mode = 0;
    const uint32_t locks[] = {0, 1, 2, 0xff, 0x100, 0xffffff00, 0xffffffff};
    const uint32_t errors[] = {0, 1, 0xffffffff};
    void (*wrappers[])(void) = {NULL, sub_001ED372, sub_001ED270, sub_001ED3BD};
    for (wrapper_mode = 1; wrapper_mode <= 3; ++wrapper_mode)
    for (unsigned l = 0; l < sizeof(locks) / sizeof(locks[0]); ++l)
    for (unsigned e = 0; e < sizeof(errors) / sizeof(errors[0]); ++e)
    for (unsigned r = 0; r < sizeof(values) / sizeof(values[0]); ++r) {
        expected_argument = values[(r + 1) % 5];
        reset(0x17000, expected_argument);
        MEM32(0x17000 + 0x24) = this_pointer;
        MEM32(0x20a1b4) = errors[e];
        lock_result = locks[l]; release_result = values[r];
        wrappers[wrapper_mode]();
        CHECK(esp == stack + (wrapper_mode == 3 ? 12u : 8u));
        CHECK(lock_calls == 1 && leave_calls == (unsigned)((locks[l] & 255u) != 0));
        CHECK(flush_calls == (unsigned)(wrapper_mode == 1 && !errors[e]));
        CHECK(release_calls == (unsigned)(wrapper_mode == 2 && !errors[e]));
        CHECK(query_calls == (unsigned)(wrapper_mode == 3 && !errors[e]));
        CHECK(eax == (errors[e] ? 0x80004005u : (wrapper_mode == 1 ? 0 : release_result)));
        CHECK(MEM32(stack + 4) == 0x17000 && MEM32(stack + 8) == expected_argument);
        check_registers();
        ++cases;
    }
    wrapper_mode = 0;
}
int main(void)
{
    const uint32_t lock_values[] = {0, 1, 2, 0xff, 0x100, 0xffffff00, 0xffffffff};
    const uint32_t error_values[] = {0, 1, 0xffffffff};
    const uint32_t returned[] = {0, 1, 7, 0x80000000, 0xffffffff};
    const uint32_t invalid_actions[] = {6, 7, 0x7fffffff, 0x80000000, 0xffffffff};
    const uint32_t references[] = {0, 1, 0xffffffff};
    const uint32_t queue_values[] = {0, 1, 0xffffffff};
    const uint8_t stream_flags[] = {0, 4, 0xff, 0x80};
    const uint32_t delete_flags[] = {0, 1, 2, 3, 0xff, 0x100, 0x80000000, 0xffffffff};
    void (*destructors[])(void) = {sub_001EE1DE, sub_001EF685, sub_001F514E, sub_001F24F3};
    MEM32(0x225ac0) = 0xc0de1234;
    expected_argument = 0x87654321;
    for (unsigned l = 0; l < sizeof(lock_values) / sizeof(lock_values[0]); l++) {
        for (unsigned e = 0; e < sizeof(error_values) / sizeof(error_values[0]); e++) {
            for (unsigned r = 0; r < sizeof(returned) / sizeof(returned[0]); r++) {
                lock_result = lock_values[l]; release_result = returned[r];
                MEM32(0x20a1b4) = error_values[e];
                reset(expected_argument, 0x1234feed);
                sub_001ECE7E();
                CHECK(esp == stack + 8);
                CHECK(lock_calls == 1 && release_calls == (unsigned)(error_values[e] == 0));
                CHECK(leave_calls == (unsigned)((lock_result & 255) != 0));
                CHECK(eax == (error_values[e] ? 0x80004005u : release_result));
                CHECK(MEM32(stack + 8) == 0x1234feed);
                check_registers();
                ++cases;
            }
        }
    }
    for (unsigned a = 0; a < 6; a++) {
        expected_action = a;
        reset(a, expected_argument);
        sub_001F50FF();
        CHECK(esp == stack + 12 && action_calls == 1);
        CHECK(eax == (actions[a] ^ 0x80000000u));
        check_registers();
        ++cases;
    }
    for (unsigned a = 0; a < sizeof(invalid_actions) / sizeof(invalid_actions[0]); a++) {
        reset(invalid_actions[a], expected_argument);
        sub_001F50FF();
        CHECK(esp == stack + 12 && action_calls == 0);
        CHECK(eax == invalid_actions[a] - 5u);
        check_registers();
        ++cases;
    }
    for (unsigned ref = 0; ref < sizeof(references) / sizeof(references[0]); ref++) {
        for (unsigned r = 0; r < sizeof(returned) / sizeof(returned[0]); r++) {
            reset(this_pointer, 0x1234feed);
            MEM32(this_pointer) = 0x15000;
            MEM32(this_pointer + 4) = references[ref];
            MEM32(0x15000) = 0xd00d0001;
            release_result = returned[r];
            sub_001EC7B9();
            CHECK(esp == stack + 8 && destroy_calls == 1);
            CHECK(MEM32(this_pointer + 4) == 0 && eax == release_result);
            CHECK(MEM32(stack + 8) == 0x1234feed);
            check_registers();
            ++cases;
        }
    }
    for (unsigned q = 0; q < sizeof(queue_values) / sizeof(queue_values[0]); q++) {
        for (unsigned f = 0; f < sizeof(stream_flags) / sizeof(stream_flags[0]); f++) {
            reset(0x8765feed, 0x1234feed);
            queue_result = queue_values[q];
            MEM32(this_pointer) = 0x15000;
            MEM32(this_pointer + 0x68) = 0x13000;
            MEM32(this_pointer + 0x80) = 0x14000;
            MEM32(0x15000 + 0x1c) = 0xd00d0002;
            MEM8(0x13000 + 0x3f) = 0x27;
            MEM8(0x14000 + 0xa) = stream_flags[f];
            sub_001F49F9();
            CHECK(esp == stack + 4 && queue_calls == 1);
            CHECK(stop_calls == (unsigned)(queue_result != 0));
            CHECK(stream_calls == (unsigned)(queue_result != 0 && (stream_flags[f] & 4) != 0));
            CHECK(MEM8(0x13000 + 0x3f) == (queue_result ? 0x80 : 0x27));
            CHECK(eax == queue_result && MEM32(stack + 4) == 0x8765feed);
            CHECK(MEM32(stack + 8) == 0x1234feed);
            check_registers();
            ++cases;
        }
    }
    for (unsigned d = 0; d < sizeof(destructors) / sizeof(destructors[0]); d++) {
        expected_destructor = d;
        for (unsigned f = 0; f < sizeof(delete_flags) / sizeof(delete_flags[0]); f++) {
            reset(delete_flags[f], 0x1234feed);
            destructors[d]();
            CHECK(esp == stack + 8 && eax == this_pointer);
            CHECK(buffer_destructor_calls == 1 && free_calls == (delete_flags[f] & 1));
            CHECK(MEM32(stack + 8) == 0x1234feed);
            check_registers();
            ++cases;
        }
    }
    test_stream_format();
    test_stream_packet();
    test_stream_actions_and_wrappers();
    printf("PASS: %u exact-callback cases; release/actions, deleting destructors, queue/stop, stream format/channel modes, HRESULT/tail calls, packet arguments, registers and stack\n", cases);
    return 0;
}
