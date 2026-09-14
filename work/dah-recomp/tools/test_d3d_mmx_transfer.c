/* The runner extracts complete current production function bodies; only guest
 * RAM/registers and the three external allocator/state calls are mocked here.
 * MOVNTQ cache policy is irrelevant in ordinary emulated guest RAM: this checks
 * the architectural data transfer, including all upper DWORDs and load order.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t ram[0x400000];
static uint32_t eax, ebx, ecx, edx, esi, edi, esp, g_ebp;
static unsigned cases, allocation_calls, flush_calls;
static unsigned refill_calls;
static uint32_t device = 0x200000;
static const uint32_t stack = 0x90000, source_base = 0x10000, dest_base = 0x300000;
static uint32_t active_count, active_alignment;
static const char *active_test;

#define CHECK(x) do { if (!(x)) { fprintf(stderr, "%s count=%u align=%u line=%d: %s\n", \
    active_test, active_count, active_alignment, __LINE__, #x); exit(1); } } while (0)
static void *guest_ptr(uint32_t address, size_t size)
{
    CHECK(address <= sizeof(ram) && size <= sizeof(ram) - address);
    return &ram[address];
}
#define XBOX_PTR(a) guest_ptr((uint32_t)(a), 0)
#define MEM32(a) (*(volatile uint32_t *)guest_ptr((uint32_t)(a), 4))
#define MEM16(a) (*(volatile uint16_t *)guest_ptr((uint32_t)(a), 2))
#define PUSH32(sp, value) do { uint32_t pv=(uint32_t)(value); (sp) -= 4; MEM32(sp) = pv; } while (0)
#define POP32(sp, value) do { (value) = MEM32(sp); (sp) += 4; } while (0)
#define CMP_G(a,b) ((int32_t)(a) > (int32_t)(b))
#define CMP_GE(a,b) ((int32_t)(a) >= (int32_t)(b))
#define CMP_B(a,b) ((uint32_t)(a) < (uint32_t)(b))
#define CMP_AE(a,b) ((uint32_t)(a) >= (uint32_t)(b))
#define TEST_Z(a,b) (((uint32_t)(a) & (uint32_t)(b)) == 0)
#define LO8(a) ((uint8_t)(a))
#define HI8(a) ((uint8_t)((a) >> 8))
#define ZX16(a) ((uint32_t)(uint16_t)(a))

static void sub_001E39E0(void)
{
    CHECK(ecx == device);
    CHECK(MEM32(esp + 4) == 0x12345678);
    esp += 8;
}
static void sub_001DF820(void)
{
    const uint32_t requested = MEM32(esp + 4);
    CHECK(requested == (allocation_calls ? 0x204u : 0x209u));
    ++allocation_calls;
    eax = MEM32(device);
    esp += 8;
}
static void sub_001DF4A0(void)
{
    CHECK(MEM32(esp + 4) == 1);
    ++flush_calls;
    esp += 8;
}
static void sub_001DF810(void)
{
    CHECK(++refill_calls == 1);
    eax=MEM32(0x1e8970);
    MEM32(0x1e8974)=dest_base+0x20000;
    ecx=0x12345678; edx=0xdeadbeef;
    esp+=4;
}

/* Generated functions deliberately contain unused labels/flag temporaries and
 * local EBP's entry value is not modeled. Neither is changed in the fixture. */
#pragma warning(push)
#pragma warning(disable: 4101 4102 4189 4700)
#include "d3d_mmx_fixture.inc"
#pragma warning(pop)

static void setup(uint32_t a, uint32_t b, uint32_t c)
{
    memset(ram + stack - 256, 0xa5, 512);
    esp = stack;
    MEM32(esp) = 0xfeedface;
    MEM32(esp + 4) = a;
    MEM32(esp + 8) = b;
    MEM32(esp + 12) = c;
    ebx = 0x9abcde12;
    esi = 0xc1234567;
    edi = 0xedcba987;
    allocation_calls = flush_calls = 0;
}
static void check_return(void)
{
    CHECK(esp == stack + 16);
    CHECK(MEM32(stack + 16) == 0xa5a5a5a5);
    CHECK(ebx == 0x9abcde12 && esi == 0xc1234567 && edi == 0xedcba987);
}
static void copy_case(uint32_t count, uint32_t align, uint32_t src_align)
{
    const uint32_t src = source_base + src_align, dst = dest_base + align;
    active_test = "copy"; active_count = count; active_alignment = align;
    memset(ram + dest_base - 32, 0xcc, count * 4 + 128);
    setup(dst, src, count);
    sub_001DD740();
    CHECK(memcmp(ram + src, ram + dst, count * 4) == 0);
    for (uint32_t i = 1; i <= 32; i++) CHECK(ram[dst - i] == 0xcc);
    for (uint32_t i = 0; i < 32; i++) CHECK(ram[dst + count * 4 + i] == 0xcc);
    check_return();
    ++cases;
}
static uint16_t expected_index(uint32_t n)
{
    return (uint16_t)((n * 137u + 0x8001u) ^ (n >> 4));
}
static void index_case(uint32_t count, uint32_t align, uint32_t src_align, int flush)
{
    const uint32_t src = source_base + src_align, begin = dest_base + align;
    uint32_t cursor, end, seen = 0;
    active_test = "indexed"; active_count = count; active_alignment = align;
    memset(ram + dest_base - 32, 0xcc, 0x30000);
    for (uint32_t i = 0; i < count; i++) MEM16(src + i * 2) = expected_index(i);
    MEM32(0x1e8968) = device;
    MEM32(device) = begin;
    MEM32(device + 8) = flush ? 0x5020 : 0x4020;
    MEM32(device + 0x1c) = 0x12345678;
    setup(4, count, src);
    sub_001DD940();
    check_return();
    CHECK(flush_calls == (unsigned)flush);
    CHECK(MEM32(device + 8) == 0x4020);
    CHECK(MEM32(begin) == 0x417fc && MEM32(begin + 4) == 4);
    cursor = begin + 8;
    end = MEM32(device);
    CHECK(end > cursor && end < begin + 0x30000);
    while (cursor + 8 < end) {
        const uint32_t header = MEM32(cursor);
        const uint32_t method = header & 0x3ffff;
        const uint32_t words = (header >> 18) & 0x7ff;
        cursor += 4;
        CHECK(cursor + words * 4 <= end - 8);
        if (method == 0x1800) {
            CHECK((header & 0x40000000) != 0);
            for (uint32_t i = 0; i < words; i++) {
                const uint32_t value = MEM32(cursor);
                CHECK(seen + 2 <= count);
                CHECK((uint16_t)value == expected_index(seen));
                CHECK((uint16_t)(value >> 16) == expected_index(seen + 1));
                seen += 2;
                cursor += 4;
            }
        } else {
            CHECK(header == 0x41808 && words == 1);
            CHECK(seen < count);
            CHECK(MEM32(cursor) == expected_index(seen));
            ++seen;
            cursor += 4;
        }
    }
    CHECK(seen == count);
    CHECK(cursor == end - 8);
    CHECK(MEM32(cursor) == 0x417fc && MEM32(cursor + 4) == 0);
    for (uint32_t i = 1; i <= 32; i++) CHECK(ram[begin - i] == 0xcc);
    for (uint32_t i = 0; i < 32; i++) CHECK(ram[end + i] == 0xcc);
    for (uint32_t i = 0; i < count; i++) CHECK(MEM16(src + i * 2) == expected_index(i));
    ++cases;
}
int main(void)
{
    const uint32_t large_copy[] = {255, 256, 257, 511, 512, 513, 4095, 4096, 4097};
    const uint32_t large_index[] = {127, 128, 129, 255, 256, 257, 511, 512, 513,
        1020, 1021, 1022, 1023, 1024, 1025, 2045, 2046, 2047, 4097, 4098, 65535};
    for (uint32_t i = 0; i < 0x30000; i++) ram[source_base + i] = (uint8_t)((i * 157u) ^ (i >> 5) ^ 0x93u);
    for (uint32_t align = 0; align < 32; align += 4) {
        for (uint32_t sa = 0; sa < 8; sa += 2) {
            for (uint32_t n = 0; n <= 128; n++) copy_case(n, align, sa);
            for (size_t i = 0; i < sizeof(large_copy) / sizeof(large_copy[0]); i++) copy_case(large_copy[i], align, sa);
        }
    }
    /* Upload four vectors both to the GPU ring and the retail constant cache.
     * Exercise queue-boundary retry, unaligned sources and all valid slots. */
    for(unsigned slot=0;slot<=188;slot+=4) for(unsigned align=0;align<8;align++)
    for(unsigned refill=0;refill<2;refill++) {
        active_test="matrix-constant";active_count=slot;active_alignment=align;
        setup(0,0,0);refill_calls=0;ecx=slot;edx=source_base+align;
        memset(ram+dest_base,0xcc,128);memset(ram+0x1e78b0,0xa7,192*16);
        MEM32(0x1e8970)=dest_base;MEM32(0x1e8974)=dest_base+(refill?76:4096);
        sub_001D9ED0();
        CHECK(esp==stack+4&&MEM32(0x1e8970)==dest_base+76&&refill_calls==refill);
        CHECK(MEM32(dest_base)==0x41ea4&&MEM32(dest_base+4)==slot&&MEM32(dest_base+8)==0x400b80);
        CHECK(memcmp(ram+dest_base+12,ram+source_base+align,64)==0);
        CHECK(memcmp(ram+0x1e78b0+slot*16,ram+source_base+align,64)==0);
        CHECK(MEM32(dest_base+76)==0xcccccccc);
        CHECK(ebx==0x9abcde12&&esi==0xc1234567&&edi==0xedcba987);++cases;
    }
    /* General uploader emits consecutive 16-word packets plus an exact tail.
     * Compare the complete production stream, including refill between packets. */
    for(unsigned count=0;count<=257;count++) for(unsigned align=0;align<8;align++)
    for(unsigned refill=0;refill<3;refill++) {
        unsigned cursor=dest_base,seen=0;
        active_test="bulk-constant";active_count=count;active_alignment=align;
        setup(count,0,0);refill_calls=0;ecx=36;edx=source_base+align;
        memset(ram+dest_base,0xcc,0x4000);
        MEM32(0x1e8970)=dest_base;
        MEM32(0x1e8974)=dest_base+(refill==1?0:refill==2?76:0x20000);
        sub_001D9F80();
        CHECK(esp==stack+8&&ebx==0x9abcde12&&esi==0xc1234567&&edi==0xedcba987);
        CHECK(MEM32(cursor)==0x41ea4&&MEM32(cursor+4)==36);cursor+=8;
        do {
            unsigned amount=count-seen;if(amount>16)amount=16;
            CHECK(MEM32(cursor)==((amount<<18)|0xb80));cursor+=4;
            CHECK(memcmp(ram+cursor,ram+source_base+align+seen*4,amount*4)==0);
            cursor+=amount*4;seen+=amount;
        } while(seen<count);
        CHECK(MEM32(0x1e8970)==cursor&&MEM32(cursor)==0xcccccccc);
        CHECK(refill_calls==(unsigned)(refill==1 || (refill==2&&count>=32)));++cases;
    }
    for (uint32_t align = 0; align < 32; align += 4) {
        for (uint32_t sa = 0; sa < 4; sa += 2) {
            for (int flush = 0; flush <= 1; flush++) {
                for (uint32_t n = 0; n <= 96; n++) index_case(n, align, sa, flush);
                for (size_t i = 0; i < sizeof(large_index) / sizeof(large_index[0]); i++) index_case(large_index[i], align, sa, flush);
            }
        }
    }
    printf("PASS: %u complete-function cases; exact copy bytes/index stream, alignment, packet rollover, guards, callee registers, stack cleanup\n", cases);
    return 0;
}
