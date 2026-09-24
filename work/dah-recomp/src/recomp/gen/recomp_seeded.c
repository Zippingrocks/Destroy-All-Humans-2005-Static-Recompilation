/* Indirect-call entry points discovered during DAH startup bring-up.
 * Kept separate so the large generated chunks do not need regeneration. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern volatile int dah_trace_input_lx;
extern volatile int dah_trace_input_ly;
extern volatile int dah_trace_input_rx;
extern volatile int dah_trace_input_ry;

/* Armed by the script-facing controller callback for the first non-zero
 * sample of each sign.  Keeping the trace in the central dispatcher lets us
 * follow the returned float through the real bytecode without changing it. */
int dah_vm_axis_trace_budget;
float dah_vm_axis_trace_value;
unsigned dah_vm_axis_trace_serial;

/* Retail movie.Start Lua native (0x00122980..0x00122AA1).  Its address is
 * registered by 0x00122B50 as data, so the original function discovery did
 * not emit a callable entry.  Preserve the argument conversion and the
 * in-engine cutscene path; movie.FullScreen has a separate Bink callback. */
void sub_00122980(void)
{
    uint32_t ebp = g_ebp;
    static uint32_t trace_count;
    if (trace_count++ < 12u) {
        fprintf(stderr, "[DAH-MOVIE-NATIVE-START] caller=%08X script=%08X\n",
                MEM32(esp), ecx);
    }

    esp -= 0x120u;
    PUSH32(esp, ebx);
    PUSH32(esp, ebp);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    ebx = 0;
    PUSH32(esp, 1);
    esi = ecx;
    MEM8(esp + 0x30u) = 0;
    PUSH32(esp, 0x00122999u); sub_00139520();
    edx = esp + 0x2Cu;
    ecx = eax;
    PUSH32(esp, 0x001229A4u); sub_000DA9A0();
    PUSH32(esp, 0x001229A9u); sub_000DAAF0();
    edi = eax;
    ebp = MEM32(edi);
    g_ebp = ebp;
    PUSH32(esp, 2);
    ecx = esi;
    PUSH32(esp, 0x001229B6u); sub_00139520();
    edx = 0;
    ecx = eax;
    PUSH32(esp, 0x001229BFu); sub_000D54A0();
    {
        uint32_t call_esp = esp;
        uint32_t target = MEM32(ebp + 0x10u);
        PUSH32(esp, eax);
        PUSH32(esp, 0x9709513Eu);
        ecx = edi;
        PUSH32(esp, 0x001229CAu);
        RECOMP_ICALL_SAFE(target, call_esp);
    }
    PUSH32(esp, 3);
    ecx = esi;
    ebp = eax;
    g_ebp = ebp;
    PUSH32(esp, 0x001229D5u); sub_001394F0();
    SET_LO8(eax, eax != 0);
    PUSH32(esp, 4);
    ecx = esi;
    MEM8(esp + 0x18u) = LO8(eax);
    PUSH32(esp, 0x001229E7u); sub_001394F0();
    SET_LO8(ecx, eax != 0);
    MEM8(esp + 0x10u) = LO8(ecx);
    PUSH32(esp, 5);
    ecx = esi;
    edi = 0;
    PUSH32(esp, 0x001229FBu); sub_00139410();
    if (!LO8(eax)) goto movie_start_00122A69;
    PUSH32(esp, 5);
    ecx = esi;
    PUSH32(esp, 0x00122A08u); sub_00139520();
    edx = 0;
    ecx = eax;
    PUSH32(esp, 0x00122A11u); sub_000D54A0();
    ecx = MEM32(0x24B87Cu);
    PUSH32(esp, eax);
    PUSH32(esp, 0x00122A1Du); sub_000D1870();
    edi = eax;
    if (!edi) goto movie_start_00122A69;
    PUSH32(esp, 6);
    ecx = esi;
    PUSH32(esp, 0x00122A2Cu); sub_00139430();
    if (!LO8(eax)) goto movie_start_00122A69;
    PUSH32(esp, 8);
    ecx = esi;
    PUSH32(esp, 0x00122A39u); sub_00139510();
    MEMF(esp + 0x18u) = (float)g_fp_stack[g_fp_top];
    g_fp_top = (g_fp_top + 1u) & 7u;
    PUSH32(esp, 7);
    ecx = esi;
    PUSH32(esp, 0x00122A46u); sub_00139510();
    MEMF(esp + 0x1Cu) = (float)g_fp_stack[g_fp_top];
    g_fp_top = (g_fp_top + 1u) & 7u;
    PUSH32(esp, 6);
    ecx = esi;
    PUSH32(esp, 0x00122A53u); sub_00139510();
    MEMF(esp + 0x20u) = (float)g_fp_stack[g_fp_top];
    g_fp_top = (g_fp_top + 1u) & 7u;
    edx = MEM32(esp + 0x1Cu);
    eax = MEM32(esp + 0x18u);
    MEM32(esp + 0x24u) = edx;
    MEM32(esp + 0x28u) = eax;
    SET_LO8(ebx, 1);

movie_start_00122A69:
    edx = MEM32(esp + 0x10u);
    eax = MEM32(esp + 0x14u);
    /* neg bl; sbb ebx,ebx selects the optional position vector. */
    ecx = esp + 0x20u;
    ebx = LO8(ebx) ? ecx : 0;
    PUSH32(esp, ebx);
    PUSH32(esp, edi);
    PUSH32(esp, edx);
    PUSH32(esp, eax);
    edx = ebp;
    ecx = esp + 0x3Cu;
    PUSH32(esp, 0x00122A8Au); sub_001227C0();
    ecx = esi;
    PUSH32(esp, eax);
    PUSH32(esp, 0x00122A92u); sub_001390D0();
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebp);
    g_ebp = ebp;
    eax = 1;
    POP32(esp, ebx);
    esp += 0x124u;
}

void sub_000DB500(void)
{
    static uint32_t trace_count;
    uint32_t object = ecx;
    uint32_t key = MEM32(esp + 4);
    uint32_t flags = MEM32(object + 0x4A30u);

    if ((flags & 0x20u) != 0 &&
        (key == 0xDCC321D2u || key == 0x270248B1u || key == 0x1520E7AFu)) {
        ecx = object + 0x261Cu;
    } else {
        ecx = MEM32(object + 0x4A28u);
    }

    if (trace_count++ < 24) {
        fprintf(stderr,
                "[DAH-RESOURCE-QUERY] object=%08X key=%08X flags=%08X backend=%08X\n",
                object, key, flags, ecx);
    }

    MEM32(esp + 4) = key;
    sub_000DC6B0();
}

void sub_000DB150(void)
{
    uint32_t saved_esp = esp;
    uint32_t target = MEM32(MEM32(ecx) + 0x30u);
    PUSH32(esp, 0u);
    PUSH32(esp, 0x6AE1B56Au);
    PUSH32(esp, 0x000DB15Cu);
    RECOMP_ICALL_SAFE(target, saved_esp);
    esp += 4;
}

void sub_000DB220(void)
{
    static uint32_t trace_count;
    uint32_t object = ecx;
    uint32_t backend;
    uint32_t slot;
    uint32_t out_value;

    PUSH32(esp, esi);
    backend = MEM32(object + 0x4A28u);
    slot = MEM32(backend + 0xBA4u);
    esi = MEM32(backend + slot * 4u + 0xB9Cu);
    ecx = MEM32(esp + 8u);
    edx = 0;
    PUSH32(esp, 0x000DB23Fu);
    sub_000D54A0();
    PUSH32(esp, eax);
    PUSH32(esp, 0x42EF1FD7u);
    ecx = esi;
    PUSH32(esp, 0x000DB24Cu);
    sub_0019E7F0();
    out_value = MEM32(esp + 0xCu);
    ecx = eax;
    eax = MEM32(ecx);
    ecx = MEM32(ecx + 4u);
    POP32(esp, esi);
    if (out_value != 0)
        MEM32(out_value) = ecx;
    if (trace_count++ < 24) {
        fprintf(stderr,
                "[DAH-RESOURCE-LOOKUP] object=%08X backend=%08X slot=%u result=%08X aux=%08X\n",
                object, backend, slot, eax, ecx);
    }
    esp += 12;
}

/* Vtable slot +0x68 formats the localized audio-block path.  The disassembler
 * missed this tiny function because it begins immediately after DB3A0 with no
 * alignment marker, so it needs an explicit indirect-call entry point. */
void sub_000DB3C0(void)
{
    uint32_t destination = MEM32(esp + 4u);
    int32_t language_code;

    PUSH32(esp, 0x000DB3C5u);
    sub_000D9BE0();
    ecx = eax;
    PUSH32(esp, 0x000DB3CCu);
    sub_000D9C00();
    language_code = (int32_t)(int8_t)MEM8(eax);

    PUSH32(esp, (uint32_t)language_code);
    PUSH32(esp, 0x00233B8Cu); /* "blocks\\audio\\%c" */
    PUSH32(esp, 0x104u);
    PUSH32(esp, destination);
    PUSH32(esp, 0x000DB3E4u);
    sub_000D5410();
    esp += 0x10u;

    fprintf(stderr,
            "[DAH-AUDIO-BLOCK-PATH] destination=%08X language=%02X\n",
            destination, (uint32_t)language_code & 0xFFu);
    esp += 8u;
}

/* Interior jump-table exits from sub_00195BB0.  Both entries inherit the
 * saved ESI already on the guest stack, so they must pop it before returning. */
void sub_00195BD6(void)
{
    eax = 1;
    POP32(esp, esi);
    esp += 4;
}

void sub_00195BDD(void)
{
    eax = (MEM32(ecx + 4u) == MEM32(edx + 4u)) ? 1u : 0u;
    POP32(esp, esi);
    esp += 4;
}

/* Default interior arm of 0x00191F80's six-entry name-lookup table at
 * 0x00192050. It unwinds that function's saved EDI/ESI before native RET. */
void sub_00191FAA(void)
{
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0u;
    esp += 4u;
}

void sub_0019200C(void)
{
    edx = MEM32(edi + 8u);
    eax = MEM32(edx + (eax >> 6) * 4u) + 0x14u;
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(ebx) = eax;
    eax = 0x0023E9E0u;
    esp += 4;
}

void sub_00192022(void)
{
    edx = (eax >> 6) + 1u;
    PUSH32(esp, esi);
    ecx = edi;
    PUSH32(esp, 0x00192030u);
    sub_00198A10();
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(ebx) = eax;
    eax = 0x0023E9F0u;
    esp += 4;
}

void sub_0019203A(void)
{
    ecx = MEM32(edi + 8u);
    edx = MEM32(ecx + (eax >> 6) * 4u) + 0x14u;
    POP32(esp, edi);
    POP32(esp, esi);
    MEM32(ebx) = edx;
    eax = 0x0023E9E8u;
    esp += 4;
}

/* setjmp/longjmp resume point inside sub_001925C0.  sub_001A4A30 stores
 * 0x00192607 as the continuation address and sub_001A4AAC later indirect-
 * tails back here after restoring the saved non-volatile registers, EBP and
 * ESP.  Treating this as a missing ordinary call skips the rest of the
 * container update and leaves the startup script's stream pointer corrupt. */
void sub_00192607(void)
{
    static uint32_t trace_count;
    uint32_t frame = g_seh_ebp;
    uint32_t saved_ebp;

    if (trace_count++ < 16u) {
        fprintf(stderr,
                "[DAH-CONTAINER-RESUME] frame=%08X esp=%08X result=%08X object=%08X\n",
                frame, esp, eax, MEM32(frame - 4u));
    }

    /* Discard the two arguments that surrounded the original setjmp call. */
    esp += 8u;

    if (eax != 0u) {
        eax = MEM32(frame - 4u);
        ecx = MEM32(frame - 8u);
        edx = MEM32(frame - 12u);
        esi = MEM32(eax + 0xCu);
        MEM32(eax + 0x74u) = ecx;
        ecx = MEM32(frame - 16u);
        MEM32(eax + 0x10u) = edx;
        edx = MEM32(eax + 4u);
        MEM32(eax) = ecx;
        ecx = (uint32_t)((int32_t)(ecx - edx) >> 3);
        edi = esi - 1u;

        if ((int32_t)ecx < (int32_t)edi) {
            ecx = edx + esi * 8u - 8u;
            edx = MEM32(frame - 28u);
            MEM32(eax + 8u) = ecx;
            MEM32(eax + 0x14u) = edx;
        } else {
            MEM32(eax + 0x14u) = MEM32(frame - 28u);
        }
    } else {
        uint32_t target;
        esi = MEM32(frame - 4u);
        edx = MEM32(frame + 8u);
        ecx = esi;
        target = MEM32(frame - 20u);
        {
            uint32_t call_esp = esp;
            PUSH32(esp, 0x00192657u);
            RECOMP_ICALL_SAFE(target, call_esp);
        }
        MEM32(esi + 0x14u) = MEM32(frame - 28u);
    }

    eax = MEM32(frame - 24u);
    POP32(esp, edi);
    POP32(esp, esi);
    esp = frame;
    POP32(esp, saved_ebp);
    g_seh_ebp = saved_ebp;
    esp += 8u; /* ret 4 */
}

static void dah_token_parser_finish(uint32_t frame)
{
    uint32_t saved_ebp;
    eax = 0xFFFFFFFFu;
    POP32(esp, edi);
    MEM32(frame + 8u) = eax;
    MEM32(frame + 4u) = eax;
    POP32(esp, esi);
    MEM32(frame) = 3u;
    eax = 1u;
    POP32(esp, saved_ebp);
    g_seh_ebp = saved_ebp;
    esp += 8;
}

static void dah_token_update_high_water(void)
{
    int16_t cursor = (int16_t)MEM16(edi + 0x1Cu);
    uint32_t owner = MEM32(edi);
    if (cursor > (int16_t)MEM16(owner + 0x24u)) {
        if (cursor > 250) {
            ecx = MEM32(edi + 8u);
            edx = MEM32(ecx + 4u);
            PUSH32(esp, edx);
            edx = 0x0023F808u;
            PUSH32(esp, 0x00199762u);
            sub_0019A3F0();
        }
        owner = MEM32(edi);
        MEM16(owner + 0x24u) = MEM16(edi + 0x1Cu);
    }
}

static void dah_token_append(uint32_t token)
{
    uint32_t index;
    PUSH32(esp, 0x00199777u);
    sub_00198EA0();
    index = MEM32(edi + 0x10u);
    eax = MEM32(edi);
    ecx = MEM32(edi + 0xCu);
    PUSH32(esp, 0x7FFFFFFDu);
    PUSH32(esp, 0x0023F858u);
    PUSH32(esp, 4u);
    PUSH32(esp, 1u);
    PUSH32(esp, index);
    edx = MEM32(eax + 0x18u);
    PUSH32(esp, 0x00199796u);
    sub_00198020();
    ecx = MEM32(edi);
    MEM32(ecx + 0x18u) = eax;
    eax = MEM32(edi);
    ecx = MEM32(eax + 0x18u);
    MEM32(ecx + index * 4u) = token;
    MEM32(edi + 0x10u) = index + 1u;
}

static void dah_token_emit_increment(uint32_t opcode)
{
    uint32_t frame = g_seh_ebp;
    esi = MEM32(frame + 4u);
    MEM16(edi + 0x1Cu) = (uint16_t)(MEM16(edi + 0x1Cu) + 1u);
    dah_token_update_high_water();
    esi = (esi << 6) | opcode;
    dah_token_append(esi);
    dah_token_parser_finish(frame);
}

/* Four interior destinations of sub_00199720's token-state jump table. */
void sub_00199738(void)
{
    dah_token_emit_increment(0xBu);
}

void sub_001997C4(void)
{
    dah_token_emit_increment(0xCu);
}

void sub_00199837(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t count = MEM32(edi + 0x10u);
    uint32_t token;
    uint32_t changed = 0;

    if ((int32_t)count > (int32_t)MEM32(edi + 0x14u)) {
        token = MEM32(MEM32(MEM32(edi) + 0x18u) + count * 4u - 4u);
    } else {
        token = 0;
    }

    PUSH32(esp, ebx);
    switch (token & 0x3Fu) {
    case 7u:
        token = (token & 0xFFFFFFCEu) | 0xEu;
        changed = 1;
        break;
    case 0xBu:
        token = (token & 0xFFFFFFCFu) | 0xFu;
        changed = 1;
        break;
    default:
        break;
    }

    MEM16(edi + 0x1Cu) = (uint16_t)(MEM16(edi + 0x1Cu) - 1u);
    dah_token_update_high_water();
    POP32(esp, ebx);

    if (changed) {
        eax = MEM32(edi);
        edx = MEM32(edi + 0x10u);
        ecx = MEM32(eax + 0x18u);
        MEM32(ecx + edx * 4u - 4u) = token;
    } else {
        dah_token_append(0xDu);
    }
    dah_token_parser_finish(frame);
}

void sub_001998F5(void)
{
    uint32_t saved_ebp;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0;
    POP32(esp, saved_ebp);
    g_seh_ebp = saved_ebp;
    esp += 8;
}

static void dah_script_dispatch_next(uint32_t frame)
{
    static uint32_t trace_count;
    static uint32_t invalid_trace_count;
    for (;;) {
        uint32_t stream = MEM32(esp + 0x10u);
        uint32_t observer;
        uint32_t opcode;
        uint32_t target;

        esi = MEM32(stream);
        MEM32(esp + 0x10u) = stream + 4u;
        observer = MEM32(esp + 0x1Cu);
        if (observer != 0) {
            ebx = MEM32(esp + 0x34u);
            edx = observer;
            PUSH32(esp, edx);
            PUSH32(esp, frame);
            PUSH32(esp, edi);
            PUSH32(esp, 0x00196804u);
            sub_00195EB0();
        }

        opcode = esi & 0x3Fu;
        if (opcode > 0x30u) {
            if (invalid_trace_count++ < 32u) {
                fprintf(stderr,
                        "[DAH-SCRIPT-INVALID] opcode=%02X token=%08X frame=%08X stream=%08X next=%08X\n",
                        opcode, esi, frame, stream, MEM32(stream + 4u));
            }
            continue;
        }
        target = MEM32(0x00197090u + opcode * 4u);
        if (dah_vm_axis_trace_budget > 0) {
            fprintf(stderr,
                    "[DAH-AXIS-VM] serial=%u left=%d input=%.9g opcode=%02X token=%08X target=%08X frame=%08X stream=%08X stack=%08X:%08X %08X:%08X %08X:%08X %08X:%08X\n",
                    dah_vm_axis_trace_serial, dah_vm_axis_trace_budget,
                    dah_vm_axis_trace_value, opcode, esi, target, frame, stream,
                    MEM32(frame - 8u), MEM32(frame - 4u),
                    MEM32(frame - 0x10u), MEM32(frame - 0x0Cu),
                    MEM32(frame - 0x18u), MEM32(frame - 0x14u),
                    MEM32(frame - 0x20u), MEM32(frame - 0x1Cu));
            --dah_vm_axis_trace_budget;
        }
        /* Intro opcode tracing is intentionally disabled after the handoff
         * was identified; leaving it hot makes the idle front-end spend its
         * time formatting the same script loop instead of presenting frames. */
        if (0 && frame >= 0x01458000u && frame < 0x01459000u) {
            fprintf(stderr,
                    "[DAH-SCRIPT-INTRO-OP] opcode=%02X token=%08X target=%08X frame=%08X stream=%08X next=%08X top=%08X:%08X\n",
                    opcode, esi, target, frame, stream, MEM32(esp + 0x10u),
                    MEM32(frame - 8u), MEM32(frame - 4u));
        }
        if (trace_count++ < 64) {
            fprintf(stderr,
                    "[DAH-SCRIPT] opcode=%02X token=%08X target=%08X frame=%08X stream=%08X\n",
                    opcode, esi, target, frame, stream);
        }
        g_seh_ebp = frame;
        RECOMP_ITAIL(target);
        return;
    }
}

static void dah_script_restore_and_return(uint32_t result, uint32_t frame)
{
    static uint32_t return_trace_count;
    uint32_t saved_ebp;
    if (return_trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-RETURN] result=%08X frame=%08X owner=%08X esp=%08X stream=%08X top=%08X:%08X\n",
                result, frame, edi, esp, MEM32(esp + 0x10u),
                frame >= 8u ? MEM32(frame - 8u) : 0u,
                frame >= 4u ? MEM32(frame - 4u) : 0u);
    }
    MEM32(edi) = frame;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = result;
    POP32(esp, saved_ebp);
    g_seh_ebp = saved_ebp;
    POP32(esp, ebx);
    esp += 0x20u;
    esp += 8u;
}

/* Startup script opcode 0x30 and the three terminal exits from the same
 * 49-way interior jump table in sub_00196760. */
void sub_00197006(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t table_owner = MEM32(esp + 0x18u);
    uint32_t bucket;

    MEM32(edi) = frame;
    ecx = MEM32(table_owner + 0x10u);
    eax = (esi >> 6) & 0x1FFu;
    edx = esi >> 15;
    bucket = MEM32(ecx + edx * 4u);
    PUSH32(esp, 0x00197026u);
    sub_00195F20();
    MEM32(eax) = bucket;
    MEM16(eax + 0xCu) = 0;
    frame = MEM32(edi);
    ecx = edi;
    PUSH32(esp, 0x00197037u);
    sub_00198840();
    dah_script_dispatch_next(frame);
}

void sub_00196A1E(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t constants = MEM32(esp + 0x14u);
    uint32_t index = esi >> 6;

    MEM32(edi) = frame;
    edx = MEM32(constants + index * 4u);
    ecx = edi;
    PUSH32(esp, 0x00196A31u);
    sub_00196200();
    frame -= 8u;
    dah_script_dispatch_next(frame);
}

void sub_00196A39(void)
{
    static uint32_t trace_count;
    uint32_t frame = g_seh_ebp;
    uint32_t depth = (esi >> 15) * 8u;
    uint32_t start = frame - depth;
    uint32_t count = (esi >> 6) & 0x1FFu;

    /* The original passes the first operand in EDX and the second by pointer
     * on the guest stack.  Losing EDX made engine_bootstrap's ProcessFunc
     * assignment operate on stale data and abort the ignition script. */
    PUSH32(esp, start + 8u);
    edx = start;
    ecx = edi;
    MEM32(edi) = frame;
    if (trace_count < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-ASSIGN] phase=enter token=%08X frame=%08X lhs=%08X:%08X rhs=%08X:%08X owner=%08X\n",
                esi, frame, MEM32(start), MEM32(start + 4u),
                MEM32(start + 8u), MEM32(start + 0xCu), edi);
    }
    PUSH32(esp, 0x00196A52u);
    sub_001960A0();
    if (trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-ASSIGN] phase=return token=%08X frame=%08X owner_top=%08X esp=%08X\n",
                esi, frame, MEM32(edi), esp);
    }
    frame -= count * 8u;
    dah_script_dispatch_next(frame);
}

void sub_00196917(void)
{
    static uint32_t trace_count;
    static uint32_t prebranch_trace_count;
    uint32_t frame = g_seh_ebp;
    uint32_t constants = MEM32(esp + 0x14u);
    uint32_t index = esi >> 6;
    uint32_t constant = MEM32(constants + index * 4u);

    MEM32(edi) = frame;
    edx = constant;
    ecx = edi;
    PUSH32(esp, 0x0019692Au);
    sub_00196170();
    if (MEM32(MEM32(esp + 0x10u)) == 0x800000E7u && prebranch_trace_count++ < 16u) {
        fprintf(stderr,
                "[DAH-SCRIPT-PREBRANCH-GLOBAL] key=%08X result=%08X value=%08X:%08X frame=%08X stream=%08X\n",
                constant, eax, MEM32(eax), MEM32(eax + 4u), frame,
                MEM32(esp + 0x10u));
        fprintf(stderr,
                "[DAH-SCRIPT-PREBRANCH-KEY] %08X: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                constant, MEM32(constant), MEM32(constant + 4u), MEM32(constant + 8u),
                MEM32(constant + 0xCu), MEM32(constant + 0x10u), MEM32(constant + 0x14u),
                MEM32(constant + 0x18u), MEM32(constant + 0x1Cu));
    }
    if (trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-GLOBAL] index=%u key=%08X result=%08X value=%08X:%08X frame=%08X\n",
                index, constant, eax, MEM32(eax), MEM32(eax + 4u), frame);
        fprintf(stderr,
                "[DAH-SCRIPT-GLOBAL-KEY] %08X: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                constant, MEM32(constant), MEM32(constant + 4u), MEM32(constant + 8u),
                MEM32(constant + 0xCu), MEM32(constant + 0x10u), MEM32(constant + 0x14u),
                MEM32(constant + 0x18u), MEM32(constant + 0x1Cu));
    }
    MEM32(frame) = MEM32(eax);
    MEM32(frame + 4u) = MEM32(eax + 4u);
    frame += 8u;
    dah_script_dispatch_next(frame);
}

void sub_0019695D(void)
{
    static uint32_t trace_count;
    static uint32_t intro_member_trace_count;
    uint32_t frame = g_seh_ebp;
    uint32_t constants = MEM32(esp + 0x14u);
    uint32_t index = esi >> 6;
    uint32_t value;

    MEM32(frame) = 3u;
    value = MEM32(constants + index * 4u);
    MEM32(frame + 4u) = value;
    MEM32(edi) = frame + 8u;

    /* Shared 0x00196942 continuation: fetch the preceding value into the
     * slot immediately below this constant, then continue interpretation. */
    esi = frame - 8u;
    edx = esi;
    ecx = edi;
    if (intro_member_trace_count < 256u && frame >= 0x01458000u && frame < 0x01459000u) {
        fprintf(stderr,
                "[DAH-SCRIPT-INTRO-MEMBER] index=%u member=%08X member_words=%08X:%08X:%08X:%08X:%08X:%08X:%08X:%08X:%08X:%08X:%08X:%08X source=%08X source_words=%08X:%08X:%08X:%08X:%08X:%08X:%08X:%08X\n",
                index, value,
                MEM32(value), MEM32(value + 4u), MEM32(value + 8u), MEM32(value + 0xCu),
                MEM32(value + 0x10u), MEM32(value + 0x14u), MEM32(value + 0x18u), MEM32(value + 0x1Cu),
                MEM32(value + 0x20u), MEM32(value + 0x24u), MEM32(value + 0x28u), MEM32(value + 0x2Cu),
                MEM32(esi + 4u), MEM32(MEM32(esi + 4u)), MEM32(MEM32(esi + 4u) + 4u),
                MEM32(MEM32(esi + 4u) + 8u), MEM32(MEM32(esi + 4u) + 0xCu),
                MEM32(MEM32(esi + 4u) + 0x10u), MEM32(MEM32(esi + 4u) + 0x14u),
                MEM32(MEM32(esi + 4u) + 0x18u));
        intro_member_trace_count++;
    }
    if (trace_count < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-MEMBER] phase=enter index=%u key=%08X source=%08X:%08X frame=%08X\n",
                index, value, MEM32(esi), MEM32(esi + 4u), frame);
        fprintf(stderr,
                "[DAH-SCRIPT-MEMBER-KEY] %08X: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                value, MEM32(value), MEM32(value + 4u), MEM32(value + 8u),
                MEM32(value + 0xCu), MEM32(value + 0x10u), MEM32(value + 0x14u),
                MEM32(value + 0x18u), MEM32(value + 0x1Cu));
        if (MEM32(esi + 4u) >= 0x00010000u && MEM32(esi + 4u) < 0x08000000u) {
            uint32_t object = MEM32(esi + 4u);
            fprintf(stderr,
                    "[DAH-SCRIPT-MEMBER-SOURCE] %08X: %08X %08X %08X %08X %08X %08X %08X %08X\n",
                    object, MEM32(object), MEM32(object + 4u), MEM32(object + 8u),
                    MEM32(object + 0xCu), MEM32(object + 0x10u), MEM32(object + 0x14u),
                    MEM32(object + 0x18u), MEM32(object + 0x1Cu));
        }
    }
    PUSH32(esp, 0x0019694Eu);
    sub_00195FD0();
    if (frame >= 0x01458000u && frame < 0x01459000u &&
        MEM32(esi + 4u) == 0x013C78B8u && value == 0x013E02C8u) {
        fprintf(stderr,
                "[DAH-SCRIPT-MISSION-CALL-RESOLVE] source=%08X member=%08X result=%08X result_words=%08X:%08X:%08X:%08X entry=%08X\n",
                MEM32(esi + 4u), value, eax, MEM32(eax), MEM32(eax + 4u),
                MEM32(eax + 8u), MEM32(eax + 0xCu), MEM32(eax + 4u) ? MEM32(MEM32(eax + 4u)) : 0u);
    }
    if (trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-MEMBER] phase=return result=%08X value=%08X:%08X owner=%08X\n",
                eax, MEM32(eax), MEM32(eax + 4u), edi);
    }
    MEM32(esi) = MEM32(eax);
    MEM32(esi + 4u) = MEM32(eax + 4u);
    dah_script_dispatch_next(frame);
}

void sub_001969DB(void)
{
    uint32_t frame = g_seh_ebp;
    ecx = edi;
    MEM32(edi) = frame;
    PUSH32(esp, 0x001969E4u);
    sub_00198840();
    edx = esi >> 6;
    ecx = edi;
    PUSH32(esp, 0x001969F0u);
    sub_00197CB0();
    MEM32(frame) = 4u;
    MEM32(frame + 4u) = eax;
    frame += 8u;
    dah_script_dispatch_next(frame);
}

void sub_0019683F(void)
{
    uint32_t frame = g_seh_ebp;
    int32_t count = (int32_t)(esi >> 6);
    do {
        MEM32(frame) = 1u;
        frame += 8u;
        count--;
    } while (count > 0);
    dah_script_dispatch_next(frame);
}

void sub_00196815(void)
{
    static uint32_t call_trace_count;
    static uint32_t main_handoff_trace_count;
    static int active_call_trace_enabled = -1;
    static uint32_t active_negative_count;
    static uint32_t active_positive_count;
    uint32_t frame = g_seh_ebp;
    uint32_t argument = (esi >> 6) & 0x1FFu;
    uint32_t base = MEM32(esp + 0x34u);
    uint32_t value = base + (esi >> 15) * 8u;
    if (argument == 0xFFu)
        argument = 0xFFFFFFFFu;
    if (active_call_trace_enabled < 0)
        active_call_trace_enabled = getenv("DAH_ACTIVE_SCRIPT_CALL_TRACE") ? 1 : 0;
    if (active_call_trace_enabled && dah_trace_input_ry) {
        uint32_t *count = dah_trace_input_ry < 0 ?
            &active_negative_count : &active_positive_count;
        if (*count < 4096u) {
            fprintf(stderr,
                    "[DAH-ACTIVE-SCRIPT-CALL] sign=%c n=%u sticks=%d,%d,%d,%d token=%08X frame=%08X owner=%08X base=%08X value=%08X words=%08X:%08X arg=%08X stream=%08X stack=%08X:%08X:%08X:%08X:%08X:%08X:%08X:%08X\n",
                    dah_trace_input_ry < 0 ? '-' : '+', (*count)++,
                    dah_trace_input_lx, dah_trace_input_ly,
                    dah_trace_input_rx, dah_trace_input_ry,
                    esi, frame, edi, base, value, MEM32(value),
                    MEM32(value + 4u), argument, MEM32(esp + 0x10u),
                    MEM32(frame - 0x20u), MEM32(frame - 0x1Cu),
                    MEM32(frame - 0x18u), MEM32(frame - 0x14u),
                    MEM32(frame - 0x10u), MEM32(frame - 0x0Cu),
                    MEM32(frame - 0x08u), MEM32(frame - 0x04u));
        }
    }
    if (MEM32(MEM32(esp + 0x10u)) == 0x00000044u && main_handoff_trace_count < 8u) {
        fprintf(stderr,
                "[DAH-MAIN-HANDOFF-CALL] phase=enter token=%08X frame=%08X owner=%08X value=%08X:%08X arg=%08X stream=%08X\n",
                esi, frame, edi, MEM32(value), MEM32(value + 4u), argument,
                MEM32(esp + 0x10u));
    }
    if (call_trace_count < 512u) {
        fprintf(stderr,
                "[DAH-SCRIPT-CALL] phase=enter token=%08X frame=%08X owner=%08X base=%08X value=%08X type=%u arg=%08X esp=%08X\n",
                esi, frame, edi, base, value, MEM32(value), argument, esp);
    }
    if (0 && frame >= 0x01458000u && frame < 0x01459000u) {
        fprintf(stderr,
                "[DAH-SCRIPT-INTRO-CALL] token=%08X frame=%08X owner=%08X base=%08X value=%08X:%08X arg=%08X\n",
                esi, frame, edi, base, MEM32(value), MEM32(value + 4u), argument);
    }
    PUSH32(esp, argument);
    edx = value;
    ecx = edi;
    MEM32(edi) = frame;
    PUSH32(esp, 0x0019683Du);
    sub_001928A0();
    frame = MEM32(edi);
    if (MEM32(MEM32(esp + 0x10u)) == 0x00000044u && main_handoff_trace_count++ < 8u) {
        fprintf(stderr,
                "[DAH-MAIN-HANDOFF-CALL] phase=return frame=%08X owner=%08X eax=%08X top=%08X:%08X esp=%08X\n",
                frame, edi, eax, frame >= 8u ? MEM32(frame - 8u) : 0u,
                frame >= 4u ? MEM32(frame - 4u) : 0u, esp);
    }
    if (call_trace_count++ < 512u) {
        fprintf(stderr,
                "[DAH-SCRIPT-CALL] phase=return token=%08X frame=%08X owner=%08X eax=%08X esp=%08X next_stream=%08X\n",
                esi, frame, edi, eax, esp, MEM32(esp + 0x10u));
    }
    if (0 && frame >= 0x01458000u && frame < 0x01459000u) {
        fprintf(stderr,
                "[DAH-SCRIPT-INTRO-CALL-RETURN] token=%08X frame=%08X owner=%08X eax=%08X next_stream=%08X\n",
                esi, frame, edi, eax, MEM32(esp + 0x10u));
    }
    dah_script_dispatch_next(frame);
}

void sub_00196853(void)
{
    uint32_t frame = g_seh_ebp;
    frame -= (esi >> 6) * 8u;
    dah_script_dispatch_next(frame);
}

void sub_0019685E(void)
{
    uint32_t frame = g_seh_ebp;
    int32_t immediate = (int32_t)((esi >> 6) - 0x01FFFFFFu);
    MEM32(frame) = 2u;
    MEMF(frame + 4u) = (float)immediate;
    frame += 8u;
    dah_script_dispatch_next(frame);
}

void sub_0019687F(void)
{
    static uint32_t trace_count;
    uint32_t frame = g_seh_ebp;
    uint32_t constants = MEM32(esp + 0x14u);
    uint32_t index = esi >> 6;
    uint32_t constant = MEM32(constants + index * 4u);
    if (trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-CONSTANT] index=%u value=%08X words=%08X %08X %08X %08X %08X %08X %08X %08X\n",
                index, constant, MEM32(constant), MEM32(constant + 4u),
                MEM32(constant + 8u), MEM32(constant + 0xCu), MEM32(constant + 0x10u),
                MEM32(constant + 0x14u), MEM32(constant + 0x18u), MEM32(constant + 0x1Cu));
    }
    MEM32(frame) = 3u;
    MEM32(frame + 4u) = constant;
    frame += 8u;
    dah_script_dispatch_next(frame);
}

void sub_0019689B(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t owner = MEM32(esp + 0x18u);
    uint32_t constants = MEM32(owner);
    uint32_t index = esi >> 6;
    MEM32(frame) = 2u;
    MEM32(frame + 4u) = MEM32(constants + index * 4u);
    frame += 8u;
    dah_script_dispatch_next(frame);
}

void sub_001968B9(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t owner = MEM32(esp + 0x18u);
    uint32_t constants = MEM32(owner);
    uint32_t index = esi >> 6;
    MEM32(frame) = 2u;
    MEMF(frame + 4u) = 0.0f - MEMF(constants + index * 4u);
    frame += 8u;
    dah_script_dispatch_next(frame);
}

void sub_001968DE(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t table = MEM32(esp + 0x24u);
    uint32_t index = esi >> 6;
    MEM32(frame) = MEM32(table + index * 8u + 0x10u);
    MEM32(frame + 4u) = MEM32(table + index * 8u + 0x14u);
    frame += 8u;
    dah_script_dispatch_next(frame);
}

void sub_001968FB(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t table = MEM32(esp + 0x34u);
    uint32_t index = esi >> 6;
    MEM32(frame) = MEM32(table + index * 8u);
    MEM32(frame + 4u) = MEM32(table + index * 8u + 4u);
    frame += 8u;
    dah_script_dispatch_next(frame);
}

/* Retail deleting destructor, 0x000BBA10..0x000BBA35. */
void sub_000BBA10(void)
{
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000BBA18u); sub_000BB5E0();
    if ((MEM8(esp + 8u) & 1u) != 0u) {
        uint32_t call_esp = esp;
        uint32_t target;
        ecx = MEM32(0x00270A80u);
        eax = MEM32(ecx);
        target = MEM32(eax + 0x14u);
        PUSH32(esp, 0x1Cu);
        PUSH32(esp, 4u);
        PUSH32(esp, esi);
        PUSH32(esp, 0x000BBA2Fu);
        RECOMP_ICALL_SAFE(target, call_esp);
    }
    eax = esi;
    POP32(esp, esi);
    esp += 8u; /* ret 4 */
}

/* Retail script native registered at 0x000FE9E5; 0x000FE7B0..0x000FE7B8. */
void sub_000FE7B0(void)
{
    PUSH32(esp, 0x000FE7B5u); sub_000FCFF0();
    eax = 0u;
    esp += 4u;
}

static int dah_dev_story_private_session(void)
{
    static const char *const aliases[] = {
        "farm", "rockwell", "santa", "area42", "union", "capitol", "cptlboss"
    };
    const char *level = getenv("DAH_DEV_LEVEL");
    const char *save_dir = getenv("DAH_SAVE_DIR");
    size_t i, size;
    if (!level || !save_dir || !*save_dir) return 0;
    for (i = 0; i < sizeof(aliases) / sizeof(aliases[0]); ++i)
        if (strcmp(level, aliases[i]) == 0) break;
    if (i == sizeof(aliases) / sizeof(aliases[0])) return 0;
    /* The launcher copies the profile into its own session before starting
     * the internal game. Refuse to unlock story rows for the ordinary save. */
    if (!strstr(save_dir, "\\dev_commands\\sessions\\") &&
        !strstr(save_dir, "/dev_commands/sessions/")) return 0;
    size = strlen(save_dir);
    return size >= 6u && (strcmp(save_dir + size - 6u, "\\saves") == 0 ||
                          strcmp(save_dir + size - 6u, "/saves") == 0);
}

/* Retail progress.FindKey Lua native, registered as data at 0x0008BF65 and therefore
 * absent from the original discovered function set (0x0008B9A0..0x0008B9D4). */
void sub_0008B9A0(void)
{
    static int story_cheat_added;
    PUSH32(esp, esi);
    PUSH32(esp, 1u);
    esi = ecx;
    PUSH32(esp, 0x0008B9AAu); sub_00139520();
    edx = 0u;
    ecx = eax;
    PUSH32(esp, 0x0008B9B3u); sub_000D54A0();
    if (eax == 0x16D57502u && !story_cheat_added &&
        dah_dev_story_private_session() && MEM32(0x249AE4u)) {
        uint32_t query_hash = eax;
        uint32_t callback_esp = esp;
        uint32_t descriptor;
        esp -= 8u;
        descriptor = esp;
        MEM32(descriptor) = query_hash;
        MEM32(descriptor + 4u) = 1u; /* original one-arg AddKey persistent flag */
        PUSH32(esp, descriptor);
        ecx = MEM32(0x249AE4u);
        PUSH32(esp, 0x0008B9B9u); sub_0008B230();
        if (esp == descriptor && LO8(eax)) {
            story_cheat_added = 1;
            fprintf(stderr, "[DAH-DEV-STORY] added story.cheat through original progress key store\n");
        }
        esp = callback_esp;
        eax = query_hash;
    }
    PUSH32(esp, eax);
    PUSH32(esp, 0x0008B9B9u); sub_00089840();
    ecx = eax;
    PUSH32(esp, 0x0008B9C0u); sub_0008AD10();
    SET_LO8(eax, eax != 0u);
    ecx = esi;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0008B9CDu); sub_001390D0();
    eax = 1u;
    POP32(esp, esi);
    esp += 4u;
}

/* Pop-and-branch-if-truthy opcode. Tag 1 is the VM's false/nil value;
 * 0x00196E42 continues for tag 1 and takes 0x00196D7B's relative branch for
 * other tags. Unlike a native call this reuses the interpreter stack frame. */
void sub_00196E42(void)
{
    static uint32_t trace_count;
    uint32_t frame = g_seh_ebp - 8u;
    uint32_t condition = MEM32(frame);

    if (condition != 1u) {
        uint32_t stream = MEM32(esp + 0x10u);
        stream += (esi >> 6) * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = stream;
    }
    if (trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-TRUE-BRANCH] token=%08X tag=%u frame=%08X stream=%08X\n",
                esi, condition, frame, MEM32(esp + 0x10u));
    }
    dah_script_dispatch_next(frame);
}

/* Conditional-branch entry inside sub_00196760's opcode jump table. */
void sub_00196E56(void)
{
    static uint32_t branch_trace_count;
    static uint32_t branch_window_dumps;
    static uint32_t branch_window_stream;
    uint32_t frame = g_seh_ebp;
    uint32_t condition = MEM32(frame - 8u);
    uint32_t sequential_stream = MEM32(esp + 0x10u);
    frame -= 8u;

    if (condition == 1u) {
        uint32_t stream = MEM32(esp + 0x10u);
        stream += (esi >> 6) * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = stream;
    }

    ++branch_trace_count;
    if (branch_window_dumps < 8u && esi == 0x800000E7u &&
        sequential_stream != branch_window_stream) {
        uint32_t p = sequential_stream - 0x20u;
        branch_window_stream = sequential_stream;
        ++branch_window_dumps;
        fprintf(stderr,
                "[DAH-SCRIPT-WINDOW] stream=%08X stack=%08X:%08X words="
                "%08X %08X %08X %08X %08X %08X %08X %08X "
                "%08X %08X %08X %08X %08X %08X %08X %08X\n",
                sequential_stream, MEM32(frame), MEM32(frame + 4u),
                MEM32(p + 0x00u), MEM32(p + 0x04u), MEM32(p + 0x08u), MEM32(p + 0x0Cu),
                MEM32(p + 0x10u), MEM32(p + 0x14u), MEM32(p + 0x18u), MEM32(p + 0x1Cu),
                MEM32(p + 0x20u), MEM32(p + 0x24u), MEM32(p + 0x28u), MEM32(p + 0x2Cu),
                MEM32(p + 0x30u), MEM32(p + 0x34u), MEM32(p + 0x38u), MEM32(p + 0x3Cu));
    }
    if (branch_trace_count <= 96u || (branch_trace_count % 100000u) == 0u) {
        fprintf(stderr,
                "[DAH-SCRIPT-BRANCH] call=%u token=%08X condition=%u frame=%08X stream=%08X\n",
                branch_trace_count, esi, condition, frame, MEM32(esp + 0x10u));
    }
    dah_script_dispatch_next(frame);
}

/* Unconditional relative-branch opcode.  The signed offset is encoded above
 * the low six opcode bits and is biased by 0x01FFFFFF dwords. */
void sub_00196DA7(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t stream = MEM32(esp + 0x10u);

    stream += (esi >> 6) * 4u - 0x07FFFFFCu;
    MEM32(esp + 0x10u) = stream;
    static unsigned jump_trace_count;
    if (jump_trace_count++ < 32u) fprintf(stderr,
            "[DAH-SCRIPT-JUMP] token=%08X frame=%08X stream=%08X\n",
            esi, frame, stream);
    dah_script_dispatch_next(frame);
}

/* Equality-test branch: consume two tagged values, compare them with the
 * VM's value comparator, and take the encoded relative branch when false. */
void sub_00196D66(void)
{
    static uint32_t equality_trace_count;
    uint32_t frame = g_seh_ebp - 0x10u;

    if (equality_trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-EQ-VALUES] call=%u token=%08X lhs=%08X:%08X rhs=%08X:%08X frame=%08X stream=%08X\n",
                equality_trace_count, esi,
                MEM32(frame), MEM32(frame + 4u), MEM32(frame + 8u), MEM32(frame + 0xCu),
                frame, MEM32(esp + 0x10u));
    }

    edx = frame + 8u;
    ecx = frame;
    PUSH32(esp, 0x00196D73u);
    sub_00195BB0();
    if (eax == 0u) {
        uint32_t stream = MEM32(esp + 0x10u);
        stream += (esi >> 6) * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = stream;
    }
    if (equality_trace_count <= 32u) fprintf(stderr,
            "[DAH-SCRIPT-EQ-BRANCH] token=%08X equal=%u frame=%08X stream=%08X\n",
            esi, eax != 0u, frame, MEM32(esp + 0x10u));
    if (equality_trace_count <= 32u) {
        uint32_t next_stream = MEM32(esp + 0x10u);
        fprintf(stderr, "[DAH-SCRIPT-EQ-NEXT]");
        for (uint32_t i = 0; i < 12u; ++i)
            fprintf(stderr, " %08X", MEM32(next_stream + i * 4u));
        fputc('\n', stderr);
    }
    dah_script_dispatch_next(frame);
}

/* Inequality-test branch: this is the sibling jump-table opcode immediately
 * after sub_00196D66.  The retail interpreter continues on a zero compare
 * result and takes the encoded relative branch when the values differ. */
void sub_00196D92(void)
{
    static uint32_t inequality_trace_count;
    uint32_t frame = g_seh_ebp - 0x10u;

    if (inequality_trace_count++ < 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-NE-VALUES] call=%u token=%08X lhs=%08X:%08X rhs=%08X:%08X frame=%08X stream=%08X\n",
                inequality_trace_count, esi,
                MEM32(frame), MEM32(frame + 4u), MEM32(frame + 8u), MEM32(frame + 0xCu),
                frame, MEM32(esp + 0x10u));
    }

    edx = frame + 8u;
    ecx = frame;
    PUSH32(esp, 0x00196D9Fu);
    sub_00195BB0();
    if (eax != 0u) {
        uint32_t stream = MEM32(esp + 0x10u);
        stream += (esi >> 6) * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = stream;
    }
    if (inequality_trace_count <= 32u) {
        fprintf(stderr,
                "[DAH-SCRIPT-NE-BRANCH] token=%08X different=%u frame=%08X stream=%08X\n",
                esi, eax != 0u, frame, MEM32(esp + 0x10u));
    }
    dah_script_dispatch_next(frame);
}

/* Arithmetic opcode 0x07 (multiply), an interior entry in the interpreter's
 * computed jump table.  Non-numeric operands take the retail operator-error
 * path; numeric/tag-convertible operands are multiplied in place. */
void sub_00196C0C(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t use_operator_path = 0u;

    if (MEM32(frame - 0x10u) != 2u) {
        ecx = frame - 0x10u;
        PUSH32(esp, 0x00196C1Cu);
        sub_00195E20();
        use_operator_path = eax != 0u;
    }
    if (!use_operator_path && MEM32(frame - 8u) != 2u) {
        ecx = frame - 8u;
        PUSH32(esp, 0x00196C30u);
        sub_00195E20();
        use_operator_path = eax != 0u;
    }

    if (use_operator_path) {
        ebx = 7u;
        esi = frame;
        eax = edi;
        PUSH32(esp, 0x00196C42u);
        sub_00196350();
    } else {
        MEMF(frame - 0x0Cu) *= MEMF(frame - 4u);
    }

    frame -= 8u;
    dah_script_dispatch_next(frame);
}

/* Arithmetic opcode 0x1E (unary negate), another interior interpreter entry. */
void sub_00196D04(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t use_operator_path = 0u;

    if (MEM32(frame - 8u) != 2u) {
        ecx = frame - 8u;
        PUSH32(esp, 0x00196D14u);
        sub_00195E20();
        use_operator_path = eax != 0u;
    }

    if (use_operator_path) {
        esi = frame + 8u;
        ebx = 0xAu;
        eax = edi;
        MEM32(frame) = 1u;
        PUSH32(esp, 0x00196D2Eu);
        sub_00196350();
    } else {
        MEMF(frame - 4u) = -MEMF(frame - 4u);
    }

    dah_script_dispatch_next(frame);
}

/* Build a VM aggregate from count 16-byte source records. */
void sub_00196AB8(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t count = esi >> 6;
    uint32_t destination_base = frame - count * 0x10u;
    uint32_t source_key = MEM32(destination_base - 4u);
    uint32_t source_cursor = frame + 8u;

    MEM32(edi) = destination_base;
    if (count == 0u) {
        dah_script_dispatch_next(frame);
        return;
    }

    MEM32(esp + 0x20u) = count;
    while (count-- != 0u) {
        frame -= 0x10u;
        source_cursor -= 0x10u;
        PUSH32(esp, frame);
        edx = source_key;
        ecx = edi;
        PUSH32(esp, 0x00196AF0u);
        sub_00197DF0();
        MEM32(eax) = MEM32(source_cursor);
        MEM32(eax + 4u) = MEM32(source_cursor + 4u);
    }
    fprintf(stderr,
            "[DAH-SCRIPT-AGGREGATE] token=%08X key=%08X frame=%08X owner=%08X\n",
            esi, source_key, frame, MEM32(edi));
    dah_script_dispatch_next(frame);
}

/* Remaining entries of the retail VM table at 0x00197090. These are basic
 * blocks, not native functions: dispatch with the updated value-stack frame
 * and never pop a native return address. Verified against original XBE bytes
 * 0x0019693D..0x00197006; call return PCs retain the retail ABI. */
void sub_0019693D(void)
{
    uint32_t frame = g_seh_ebp;
    MEM32(edi) = frame;
    frame -= 8u;
    esi = frame - 8u;
    edx = esi;
    ecx = edi;
    PUSH32(esp, 0x0019694Eu); sub_00195FD0();
    ecx = MEM32(eax);
    MEM32(esi) = ecx;
    edx = MEM32(eax + 4u);
    MEM32(esi + 4u) = edx;
    dah_script_dispatch_next(frame);
}

void sub_00196978(void)
{
    uint32_t frame = g_seh_ebp;
    eax = MEM32(esp + 0x34u);
    esi >>= 6;
    ecx = MEM32(eax + esi * 8u);
    MEM32(frame) = ecx;
    edx = MEM32(eax + esi * 8u + 4u);
    eax = frame + 8u;
    MEM32(frame + 4u) = edx;
    MEM32(edi) = eax;
    esi = frame - 8u;
    edx = esi;
    ecx = edi;
    PUSH32(esp, 0x0019694Eu); sub_00195FD0();
    ecx = MEM32(eax);
    MEM32(esi) = ecx;
    edx = MEM32(eax + 4u);
    MEM32(esi + 4u) = edx;
    dah_script_dispatch_next(frame);
}

void sub_00196993(void)
{
    uint32_t frame = g_seh_ebp;
    ecx = MEM32(esp + 0x14u);
    eax = MEM32(frame - 4u);
    ebx = MEM32(frame - 8u);
    MEM32(frame) = 3u;
    esi >>= 6;
    edx = MEM32(ecx + esi * 4u);
    MEM32(frame + 4u) = edx;
    frame += 8u;
    esi = frame - 0x10u;
    edx = esi;
    ecx = edi;
    MEM32(esp + 0x2Cu) = eax;
    MEM32(edi) = frame;
    PUSH32(esp, 0x001969C2u); sub_00195FD0();
    ecx = MEM32(eax);
    MEM32(esi) = ecx;
    edx = MEM32(eax + 4u);
    eax = MEM32(esp + 0x2Cu);
    MEM32(esi + 4u) = edx;
    MEM32(frame - 8u) = ebx;
    MEM32(frame - 4u) = eax;
    dah_script_dispatch_next(frame);
}

void sub_00196A02(void)
{
    uint32_t frame = g_seh_ebp;
    ecx = MEM32(frame - 8u);
    eax = MEM32(esp + 0x34u);
    frame -= 8u;
    esi >>= 6;
    MEM32(eax + esi * 8u) = ecx;
    edx = MEM32(frame + 4u);
    MEM32(eax + esi * 8u + 4u) = edx;
    dah_script_dispatch_next(frame);
}

void sub_00196A66(void)
{
    uint32_t frame = g_seh_ebp;
    ebx = esi;
    esi = (esi >> 6) & 0x1FFu;
    ecx = esi * 8u;
    eax = frame - ecx;
    edx = MEM32(eax - 4u);
    ebx = (ebx >> 15) * 0x3Eu;
    MEM32(esp + 0x20u) = edx;
    MEM32(edi) = eax;
    while (esi != 0u) {
        edx = MEM32(esp + 0x20u);
        eax = esi + ebx;
        PUSH32(esp, eax);
        ecx = edi;
        frame -= 8u;
        PUSH32(esp, 0x00196AA5u); sub_00197EE0();
        --esi;
        ecx = MEM32(frame);
        edx = MEM32(frame + 4u);
        MEM32(eax) = ecx;
        MEM32(eax + 4u) = edx;
        /* JNE at 196AB1 consumes DEC ESI flags, not an earlier TEST. */
    }
    dah_script_dispatch_next(frame);
}

void sub_00196B05(void)
{
    uint32_t frame = g_seh_ebp;
    eax = MEM32(frame - 0x10u);
    ecx = frame - 0x10u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196B15u); sub_00195E20();
        if (eax != 0u) goto add_operator;
    }
    eax = MEM32(frame - 8u);
    ecx = frame - 8u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196B29u); sub_00195E20();
        if (eax != 0u) goto add_operator;
    }
    xmm0 = XMM_SCALAR(MEMF(frame - 4u));
    xmm0.f[0] += MEMF(frame - 0xCu);
    MEMF(frame - 0xCu) = xmm0.f[0];
    dah_script_dispatch_next(frame - 8u);
    return;
add_operator:
    ebx = 5u;
    esi = frame;
    eax = edi;
    PUSH32(esp, 0x00196B3Bu); sub_00196350();
    dah_script_dispatch_next(frame - 8u);
}

void sub_00196B5A(void)
{
    uint32_t frame = g_seh_ebp;
    eax = MEM32(frame - 8u);
    ecx = frame - 8u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196B6Au); sub_00195E20();
        if (eax != 0u) {
            esi = (esi >> 6) - 0x01FFFFFFu;
            xmm0.f[0] = (float)(int32_t)esi;
            esi = frame + 8u;
            ebx = 5u;
            eax = edi;
            MEM32(frame) = 2u;
            MEMF(frame + 4u) = xmm0.f[0];
            PUSH32(esp, 0x00196B96u); sub_00196350();
            dah_script_dispatch_next(frame);
            return;
        }
    }
    esi = (esi >> 6) - 0x01FFFFFFu;
    xmm0.f[0] = (float)(int32_t)esi;
    xmm0.f[0] += MEMF(frame - 4u);
    MEMF(frame - 4u) = xmm0.f[0];
    dah_script_dispatch_next(frame);
}

void sub_00196BB7(void)
{
    uint32_t frame = g_seh_ebp;
    eax = MEM32(frame - 0x10u);
    ecx = frame - 0x10u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196BC7u); sub_00195E20();
        if (eax != 0u) goto subtract_operator;
    }
    eax = MEM32(frame - 8u);
    ecx = frame - 8u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196BDBu); sub_00195E20();
        if (eax != 0u) goto subtract_operator;
    }
    xmm0 = XMM_SCALAR(MEMF(frame - 0xCu));
    xmm0.f[0] -= MEMF(frame - 4u);
    MEMF(frame - 0xCu) = xmm0.f[0];
    dah_script_dispatch_next(frame - 8u);
    return;
subtract_operator:
    ebx = 6u;
    esi = frame;
    eax = edi;
    PUSH32(esp, 0x00196BEDu); sub_00196350();
    dah_script_dispatch_next(frame - 8u);
}

void sub_00196C61(void)
{
    uint32_t frame = g_seh_ebp;
    eax = MEM32(frame - 0x10u);
    ecx = frame - 0x10u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196C71u); sub_00195E20();
        if (eax != 0u) goto divide_operator;
    }
    eax = MEM32(frame - 8u);
    ecx = frame - 8u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196C85u); sub_00195E20();
        if (eax != 0u) goto divide_operator;
    }
    xmm0 = XMM_SCALAR(MEMF(frame - 0xCu));
    xmm0.f[0] /= MEMF(frame - 4u);
    MEMF(frame - 0xCu) = xmm0.f[0];
    dah_script_dispatch_next(frame - 8u);
    return;
divide_operator:
    ebx = 8u;
    esi = frame;
    eax = edi;
    PUSH32(esp, 0x00196C97u); sub_00196350();
    dah_script_dispatch_next(frame - 8u);
}

void sub_00196CB6(void)
{
    uint32_t frame = g_seh_ebp;
    PUSH32(esp, frame);
    ebx = 9u;
    PUSH32(esp, 0x00196CC1u); sub_001962E0();
    if (eax == 0u) {
        edx = 0x0023F474u;
        ecx = edi;
        PUSH32(esp, 0x00196CD1u); sub_001925A0();
    }
    dah_script_dispatch_next(frame - 8u);
}

void sub_00196CD9(void)
{
    uint32_t frame = g_seh_ebp;
    esi >>= 6;
    PUSH32(esp, frame);
    edx = esi;
    ecx = edi;
    PUSH32(esp, 0x00196CE6u); sub_001964A0();
    eax = esi * 8u;
    ecx = 8u - eax;
    frame += ecx;
    ecx = edi;
    MEM32(edi) = frame;
    PUSH32(esp, 0x00196CFFu); sub_00198840();
    dah_script_dispatch_next(frame);
}

void sub_00196D45(void)
{
    uint32_t frame = g_seh_ebp;
    ecx = MEM32(frame - 8u);
    xmm0 = XMM_SCALAR(MEMF(0x00225C28u));
    edx = (ecx == 1u) ? 1u : 0u;
    MEMF(frame - 4u) = xmm0.f[0];
    ++edx;
    MEM32(frame - 8u) = edx;
    dah_script_dispatch_next(frame);
}

void sub_00196DBE(void)
{
    uint32_t frame = g_seh_ebp - 0x10u;
    ecx = frame + 0x10u;
    PUSH32(esp, ecx);
    edx = frame + 8u;
    PUSH32(esp, edx);
    edx = frame;
    ecx = edi;
    PUSH32(esp, 0x00196DD2u); sub_001963E0();
    if (eax != 0u) {
        eax = MEM32(esp + 0x10u);
        esi >>= 6;
        ecx = eax + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = ecx;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196DDC(void)
{
    uint32_t frame = g_seh_ebp - 0x10u;
    edx = frame + 0x10u;
    PUSH32(esp, edx);
    PUSH32(esp, frame);
    edx = frame + 8u;
    ecx = edi;
    PUSH32(esp, 0x00196DEEu); sub_001963E0();
    if (eax == 0u) {
        eax = MEM32(esp + 0x10u);
        esi >>= 6;
        ecx = eax + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = ecx;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196DF0(void)
{
    uint32_t frame = g_seh_ebp - 0x10u;
    edx = frame + 0x10u;
    PUSH32(esp, edx);
    PUSH32(esp, frame);
    edx = frame + 8u;
    ecx = edi;
    PUSH32(esp, 0x00196E02u); sub_001963E0();
    if (eax != 0u) {
        eax = MEM32(esp + 0x10u);
        esi >>= 6;
        ecx = eax + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = ecx;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196E0F(void)
{
    uint32_t frame = g_seh_ebp - 0x10u;
    edx = frame + 0x10u;
    PUSH32(esp, edx);
    eax = frame + 8u;
    PUSH32(esp, eax);
    edx = frame;
    ecx = edi;
    PUSH32(esp, 0x00196E23u); sub_001963E0();
    if (eax == 0u) {
        ecx = MEM32(esp + 0x10u);
        esi >>= 6;
        edx = ecx + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = edx;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196E6A(void)
{
    uint32_t frame = g_seh_ebp;
    if (MEM32(frame - 8u) != 1u) {
        ecx = MEM32(esp + 0x10u);
        esi >>= 6;
        edx = ecx + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = edx;
    } else {
        frame -= 8u;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196E78(void)
{
    uint32_t frame = g_seh_ebp;
    if (MEM32(frame - 8u) == 1u) {
        eax = MEM32(esp + 0x10u);
        esi >>= 6;
        ecx = eax + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = ecx;
    } else {
        frame -= 8u;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196E8A(void)
{
    uint32_t frame = g_seh_ebp;
    MEM32(frame) = 1u;
    eax = MEM32(esp + 0x10u) + 4u;
    frame += 8u;
    MEM32(esp + 0x10u) = eax;
    dah_script_dispatch_next(frame);
}

void sub_00196EA4(void)
{
    uint32_t frame = g_seh_ebp;
    int exit_loop;
    eax = MEM32(frame - 8u);
    ecx = frame - 8u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196EB4u); sub_00195E20();
        if (eax != 0u) {
            edx = 0x0023F458u;
            ecx = edi;
            PUSH32(esp, 0x00196EC4u); sub_001925A0();
        }
    }
    eax = MEM32(frame - 0x10u);
    ecx = frame - 0x10u;
    if (eax != 2u) {
        PUSH32(esp, 0x00196ED4u); sub_00195E20();
        if (eax != 0u) {
            edx = 0x0023F438u;
            ecx = edi;
            PUSH32(esp, 0x00196EE4u); sub_001925A0();
        }
    }
    eax = MEM32(frame - 0x18u);
    ebx = frame - 0x18u;
    if (eax != 2u) {
        ecx = ebx;
        PUSH32(esp, 0x00196EF6u); sub_00195E20();
        if (eax != 0u) {
            edx = 0x0023F410u;
            ecx = edi;
            PUSH32(esp, 0x00196F06u); sub_001925A0();
        }
    }
    xmm0 = XMM_SCALAR(MEMF(frame - 4u));
    if (xmm0.f[0] > MEMF(0x00225C20u)) {
        xmm0 = XMM_SCALAR(MEMF(frame - 0x14u));
        exit_loop = xmm0.f[0] > MEMF(frame - 0xCu);
    } else {
        xmm0 = XMM_SCALAR(MEMF(frame - 0xCu));
        exit_loop = xmm0.f[0] > MEMF(frame - 0x14u);
    }
    /* COMISS/JBE includes unordered; only ordered greater exits the loop. */
    if (exit_loop) {
        frame = ebx;
        ecx = MEM32(esp + 0x10u);
        esi >>= 6;
        edx = ecx + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = edx;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196F35(void)
{
    uint32_t frame = g_seh_ebp;
    int positive_step;
    int exit_loop;
    if (MEM32(frame - 0x18u) != 2u) {
        edx = 0x0023F3F0u;
        ecx = edi;
        PUSH32(esp, 0x00196F47u); sub_001925A0();
    }
    xmm0 = XMM_SCALAR(MEMF(frame - 4u));
    xmm1 = XMM_SCALAR(MEMF(frame - 4u));
    positive_step = xmm1.f[0] > MEMF(0x00225C20u);
    xmm0.f[0] += MEMF(frame - 0x14u);
    MEMF(frame - 0x14u) = xmm0.f[0];
    if (positive_step) {
        exit_loop = xmm0.f[0] > MEMF(frame - 0xCu);
    } else {
        xmm1 = XMM_SCALAR(MEMF(frame - 0xCu));
        exit_loop = xmm1.f[0] > xmm0.f[0];
    }
    if (exit_loop) {
        frame -= 0x18u;
    } else {
        eax = MEM32(esp + 0x10u);
        esi >>= 6;
        ecx = eax + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = ecx;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196F85(void)
{
    uint32_t frame = g_seh_ebp;
    if (MEM32(frame - 8u) != 4u) {
        edx = 0x0023F3D4u;
        ecx = edi;
        PUSH32(esp, 0x00196F97u); sub_001925A0();
    }
    edx = MEM32(frame - 4u);
    PUSH32(esp, 0x0023F2F8u);
    ecx = edi;
    PUSH32(esp, 0x00196FA6u); sub_00197B00();
    if (eax == 0u) {
        frame -= 8u;
        edx = MEM32(esp + 0x10u);
        esi >>= 6;
        eax = edx + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = eax;
    } else {
        ecx = MEM32(eax);
        frame += 0x10u;
        MEM32(frame - 0x10u) = ecx;
        edx = MEM32(eax + 4u);
        MEM32(frame - 0xCu) = edx;
        ecx = MEM32(eax + 8u);
        MEM32(frame - 8u) = ecx;
        edx = MEM32(eax + 0xCu);
        MEM32(frame - 4u) = edx;
    }
    dah_script_dispatch_next(frame);
}

void sub_00196FD1(void)
{
    uint32_t frame = g_seh_ebp;
    edx = MEM32(frame - 0x14u);
    ebx = frame - 0x10u;
    PUSH32(esp, ebx);
    ecx = edi;
    PUSH32(esp, 0x00196FDFu); sub_00197B00();
    if (eax == 0u) {
        frame -= 0x18u;
    } else {
        ecx = MEM32(eax);
        MEM32(ebx) = ecx;
        edx = MEM32(eax + 4u);
        MEM32(ebx + 4u) = edx;
        ecx = MEM32(eax + 8u);
        MEM32(frame - 8u) = ecx;
        edx = MEM32(eax + 0xCu);
        MEM32(frame - 4u) = edx;
        eax = MEM32(esp + 0x10u);
        esi >>= 6;
        ecx = eax + esi * 4u - 0x07FFFFFCu;
        MEM32(esp + 0x10u) = ecx;
    }
    dah_script_dispatch_next(frame);
}

/* Tiny vtable targets that sit between discovered function boundaries in the
 * retail image.  They are reached only indirectly, so the static function
 * finder did not emit them. */
void sub_00139A80(void)
{
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x00139A88u);
    sub_0019F110();
    eax = esi;
    POP32(esp, esi);
    esp += 8u;
}

void sub_0005A530(void)
{
    ecx = MEM32(0x0024B87Cu);
    eax = MEM32(ecx);
    RECOMP_ITAIL(MEM32(eax + 0x20u));
}

void sub_0005A540(void)
{
    ecx = MEM32(0x0024B87Cu);
    eax = MEM32(ecx);
    RECOMP_ITAIL(MEM32(eax + 0x24u));
}

void sub_000E09F0(void)
{
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000E09F8u);
    sub_001DA870();
    eax = MEM32(esi + 0x484u);
    if (eax != 0u) {
        PUSH32(esp, eax);
        PUSH32(esp, 0x000E0A08u);
        sub_001DD3E0();
        MEM32(esi + 0x484u) = 0u;
    }
    POP32(esp, esi);
    esp += 4u;
}

void sub_00181780(void)
{
    uint32_t call_esp = esp;
    uint32_t target;

    ecx = MEM32(0x00270A80u);
    eax = MEM32(ecx);
    PUSH32(esp, 0x15u);
    PUSH32(esp, 8u);
    target = MEM32(eax + 0x10u);
    PUSH32(esp, 0x0018178Fu);
    RECOMP_ICALL_SAFE(target, call_esp);
    MEM16(eax + 4u) = 8u;
    MEM16(eax + 6u) = 1u;
    MEM32(eax) = 0x0023D880u;
    esp += 8u;
}

void sub_000E32E0(void)
{
    PUSH32(esp, 0xF0u);
    PUSH32(esp, 0x000E32EAu);
    sub_0006B6F0();
    esp += 4u;
    if (eax != 0u) {
        ecx = eax;
        sub_000E2300();
        return;
    }
    eax = 0u;
    esp += 4u;
}

void sub_000DB750(void)
{
    uint32_t key = MEM32(esp + 4u);
    uint32_t arena;

    if ((MEM8(ecx + 0x4A30u) & 0x20u) != 0u &&
        (key == 0xDCC321D2u || key == 0x270248B1u || key == 0x1520E7AFu)) {
        arena = ecx + 0x261Cu;
    } else {
        arena = MEM32(ecx + 0x4A28u);
    }

    PUSH32(esp, esi);
    if (arena != 0u) {
        uint32_t slot = MEM32(arena + 0xBA4u);
        esi = MEM32(arena + slot * 4u + 0xB9Cu);
        edx = key ^ MEM32(esp + 0xCu);
        ecx = MEM32(MEM32(esi + 0x240u) + 0x18u);
        MEM32(esp + 8u) = edx;
        edx = esp + 8u;
        esi += 0x104u;
        PUSH32(esp, edx);
        eax = esp + 0x10u;
        PUSH32(esp, eax);
        PUSH32(esp, 0x000DB7BBu);
        sub_0019E6E0();
        eax = MEM32(esp + 0xCu);
        if (eax != 0xA00FA00Fu) {
            uint32_t index = MEM32(eax + 4u);
            edx = index + index * 2u;
            eax = MEM32(esi + 0x13Cu);
            ecx = MEM32(eax + 0xCu);
            eax = ecx + edx * 8u + 4u;
            POP32(esp, esi);
            esp += 12u;
            return;
        }
    }

    eax = 0u;
    POP32(esp, esi);
    esp += 12u;
}

void sub_000F5700(void)
{
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xCu);
    PUSH32(esp, edi);
    esi = ecx;
    PUSH32(esp, 0x000F570Eu);
    sub_000E7860();

    eax = MEM32(edi + 0xC0u);
    ecx = MEM32(0x00250EF8u);
    PUSH32(esp, eax);
    PUSH32(esp, 0x000F5720u);
    sub_000E3500();

    xmm0 = XMM_SCALAR(0.0f);
    MEM32(esi + 0x44u) = eax;
    ecx = MEM32(edi + 0xB4u);
    MEM32(esi + 0x28u) = ecx;
    xmm1 = XMM_SCALAR(MEMF(edi + 0xB8u));
    if (xmm1.f[0] > xmm0.f[0]) {
        edx = MEM32(edi + 0xB8u);
        MEM32(esi + 0x2Cu) = edx;
    }

    eax = MEM32(edi + 0xBCu);
    MEM32(esi + 0x30u) = eax;
    eax = MEM32(esi + 0x14u) + 0x44u;
    MEMF(eax) = xmm0.f[0];
    MEMF(eax + 4u) = xmm0.f[0];
    MEMF(eax + 8u) = xmm0.f[0];
    xmm0 = XMM_SCALAR(MEMF(0x00226194u));
    MEMF(eax + 0xCu) = xmm0.f[0];
    esi = MEM32(esi + 0x14u);
    ecx = esi + 0x44u;
    PUSH32(esp, ecx);
    ecx = esi + 8u;
    PUSH32(esp, 0x000F577Eu);
    sub_000D6B40();

    POP32(esp, edi);
    POP32(esp, esi);
    esp += 8u;
}

void sub_000F32E0(void)
{
    uint32_t ebp = g_seh_ebp;

    PUSH32(esp, esi);
    esi = ecx;
    if (MEM16(esi + 0x58u) != 0u) {
        eax = MEM32(esi + 0x40u);
        if (eax != 0u) {
            PUSH32(esp, ebx);
            PUSH32(esp, ebp);
            ebp = MEM32(esp + 0x10u);
            ecx = eax;
            eax = MEM32(ecx);
            {
                uint32_t call_esp = esp;
                uint32_t target = MEM32(eax + 0x10u);
                PUSH32(esp, ebp);
                PUSH32(esp, 0x000F32FFu);
                RECOMP_ICALL_SAFE(target, call_esp);
            }

            ebx = 1u;
            if ((int16_t)MEM16(esi + 0x58u) > 1) {
                PUSH32(esp, edi);
                edi = esi + 0x44u;
                do {
                    ecx = MEM32(edi - 4u);
                    eax = MEM32(edi);
                    if (ecx != eax) {
                        uint32_t call_esp = esp;
                        uint32_t target;
                        ecx = eax;
                        edx = MEM32(ecx);
                        target = MEM32(edx + 0x10u);
                        PUSH32(esp, ebp);
                        PUSH32(esp, 0x000F3321u);
                        RECOMP_ICALL_SAFE(target, call_esp);
                    }
                    eax = (uint32_t)(int32_t)(int16_t)MEM16(esi + 0x58u);
                    ebx += 1u;
                    edi += 4u;
                } while ((int32_t)ebx < (int32_t)eax);
                POP32(esp, edi);
            }
            POP32(esp, ebp);
            POP32(esp, ebx);
        }
    }
    POP32(esp, esi);
    esp += 8u;
}

void sub_000E4E50(void)
{
    esp -= 0x3Cu;
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0x48u);
    eax = edi + 0x50u;
    esi = ecx;
    PUSH32(esp, eax);
    ecx = esp + 0x18u;
    PUSH32(esp, 0x000E4E68u);
    sub_000D7870();

    xmm0 = XMM_SCALAR(0.0f);
    ecx = esp + 0x14u;
    MEMF(esp + 8u) = xmm0.f[0];
    MEMF(esp + 0xCu) = xmm0.f[0];
    xmm0 = XMM_SCALAR(MEMF(0x00225C28u));
    esi += 0x28u;
    PUSH32(esp, ecx);
    edx = esp + 0xCu;
    ecx = esi;
    MEMF(esp + 0x14u) = xmm0.f[0];
    PUSH32(esp, 0x000E4E98u);
    sub_000D7900();

    edx = MEM32(edi + 0x38u);
    PUSH32(esp, edx);
    ecx = esi;
    PUSH32(esp, 0x000E4EA3u);
    sub_000D4A90();

    POP32(esp, edi);
    POP32(esp, esi);
    esp += 0x3Cu;
    esp += 8u;
}

void sub_00081300(void)
{
    PUSH32(esp, ebx);
    ebx = MEM32(esp + 8u);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;

    if (MEM32(ebx + 4u) == 0x6C7C139Fu) {
        PUSH32(esp, 0x70u);
        PUSH32(esp, 0x00081319u);
        sub_0006B6F0();
        esp += 4u;
        if (eax != 0u) {
            PUSH32(esp, 1u);
            ecx = eax;
            PUSH32(esp, 0x00081329u);
            sub_00083720();
        } else {
            eax = 0u;
        }

        ecx = eax;
        MEM32(esi + 0x38u) = eax;
        PUSH32(esp, 0x00081337u);
        sub_00083910();
        if (LO8(eax) != 0u) {
            eax = MEM32(esi + 0x38u);
            PUSH32(esp, eax);
            ecx = esi;
            PUSH32(esp, 0x00081346u);
            sub_0009E310();
        } else {
            ecx = MEM32(esi + 0x38u);
            if (ecx != 0u) {
                uint32_t call_esp = esp;
                edx = MEM32(ecx);
                PUSH32(esp, 1u);
                PUSH32(esp, 0x00081356u);
                RECOMP_ICALL_SAFE(MEM32(edx + 0x24u), call_esp);
            }
            MEM32(esi + 0x38u) = 0u;
        }
    }

    edi = esi + 0x10u;
    esi = MEM32(edi);
    while (esi != edi) {
        uint32_t call_esp = esp;
        ecx = MEM32(esi + 8u);
        eax = MEM32(ecx);
        PUSH32(esp, ebx);
        PUSH32(esp, 0x0008136Fu);
        RECOMP_ICALL_SAFE(MEM32(eax + 8u), call_esp);
        esi = MEM32(esi);
    }

    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 8u;
}

void sub_000838F0(void)
{
    PUSH32(esp, esi);
    esi = ecx;
    PUSH32(esp, 0x000838F8u);
    sub_00083870();
    if ((MEM8(esp + 8u) & 1u) != 0u) {
        PUSH32(esp, esi);
        PUSH32(esp, 0x00083905u);
        sub_0006B710();
        esp += 4u;
    }
    eax = esi;
    POP32(esp, esi);
    esp += 8u;
}

/* The retail disassembler did not promote this data-referenced callback to a
 * function, even though sub_000F8630 registers 0x000F85E0 directly.  Preserve
 * the original startup sequence exactly so the callback can be dispatched. */
void sub_000F85E0(void)
{
    PUSH32(esp, esi);
    PUSH32(esp, 2u);
    esi = ecx;
    PUSH32(esp, 0x000F85EAu);
    sub_00139450();
    if (LO8(eax) != 0u) {
        ecx = 2u;
        PUSH32(esp, 0x000F85F8u);
        sub_000FEE40();
    }

    PUSH32(esp, 1u);
    ecx = esi;
    PUSH32(esp, 0x000F8601u);
    sub_00139450();
    {
        uint32_t second_slot_present = LO8(eax) != 0u;
        POP32(esp, esi);
        if (second_slot_present) {
            ecx = 1u;
            PUSH32(esp, 0x000F8610u);
            sub_000FFDC0();
        }
    }

    PUSH32(esp, 0x000F8615u);
    sub_000FEE80();
    PUSH32(esp, 0x000F861Au);
    sub_000FFE00();
    eax = MEM32(0x002583B0u);
    MEM8(eax + 0x24u) = 1u;
    eax = 0u;
    esp += 4u;
}

/* Factory callback registered by sub_000FEDE0/sub_000FEE10.  The retail body
 * is a binary search over class IDs followed by allocation and the matching
 * constructor call.  Keep the table compact while retaining every retail
 * case, allocation size, constructor target, and guest return address. */
void sub_000FEA90(void)
{
    uint32_t class_id = ecx;
    uint32_t constructor_arg = edx;
    uint32_t allocation_size = 0u;
    uint32_t allocation_return = 0u;
    uint32_t constructor = 0u;
    uint32_t constructor_return = 0u;
    uint32_t first_arg;
    uint32_t second_arg;
    uint32_t call_esp;

    PUSH32(esp, esi);
    esi = constructor_arg;

    switch (class_id) {
    case 0x1B4FA1DFu:
        allocation_size = 0xB4u; allocation_return = 0x000FEADDu;
        constructor = 0x00104450u; constructor_return = 0x000FEAFAu; break;
    case 0x15346D8Cu:
        allocation_size = 0xC8u; allocation_return = 0x000FEB08u;
        constructor = 0x001040A0u; constructor_return = 0x000FEB25u; break;
    case 0x02F0D92Fu:
        allocation_size = 0x3E0u; allocation_return = 0x000FEB33u;
        constructor = 0x000FB060u; constructor_return = 0x000FEB50u; break;
    case 0x3BB141F2u:
        allocation_size = 0xB4u; allocation_return = 0x000FEB5Eu;
        constructor = 0x00103EF0u; constructor_return = 0x000FEB7Bu; break;
    case 0x6556609Cu:
        allocation_size = 0xB0u; allocation_return = 0x000FEBA5u;
        constructor = 0x000F9090u; constructor_return = 0x000FEBC2u; break;
    case 0x5CDED7EEu:
        allocation_size = 0x160u; allocation_return = 0x000FEBD0u;
        constructor = 0x000FC0B0u; constructor_return = 0x000FEBEDu; break;
    case 0x3BFCB234u:
        allocation_size = 0x19Cu; allocation_return = 0x000FEBFBu;
        constructor = 0x00103CF0u; constructor_return = 0x000FEC18u; break;
    case 0x6BE2929Bu:
        allocation_size = 0xB4u; allocation_return = 0x000FEC26u;
        constructor = 0x001023B0u; constructor_return = 0x000FEC43u; break;
    case 0x88816E2Eu:
        allocation_size = 0xC4u; allocation_return = 0x000FEC7Fu;
        constructor = 0x001020A0u; constructor_return = 0x000FEC9Cu; break;
    case 0x84AE3CE3u:
        allocation_size = 0x150u; allocation_return = 0x000FECAAu;
        constructor = 0x00101FB0u; constructor_return = 0x000FECC7u; break;
    case 0x76802A4Eu:
        allocation_size = 0x14Cu; allocation_return = 0x000FECD5u;
        constructor = 0x00100250u; constructor_return = 0x000FECF2u; break;
    case 0x989F2AC5u:
        allocation_size = 0xB4u; allocation_return = 0x000FED00u;
        constructor = 0x00101E30u; constructor_return = 0x000FED1Du; break;
    case 0xCB28D32Du:
        allocation_size = 0x22Cu; allocation_return = 0x000FED43u;
        constructor = 0x00101600u; constructor_return = 0x000FED5Cu; break;
    case 0xC1C49B00u:
        allocation_size = 0xB4u; allocation_return = 0x000FED6Au;
        constructor = 0x001011F0u; constructor_return = 0x000FED83u; break;
    case 0x9D71F205u:
        allocation_size = 0x154u; allocation_return = 0x000FED91u;
        constructor = 0x00100EE0u; constructor_return = 0x000FEDAAu; break;
    default:
        eax = 0u;
        POP32(esp, esi);
        esp += 12u;
        return;
    }

    PUSH32(esp, allocation_size);
    PUSH32(esp, allocation_return);
    sub_0006B6F0();
    esp += 4u;
    if (eax != 0u) {
        first_arg = MEM32(esp + 8u);
        second_arg = MEM32(esp + 0xCu);
        call_esp = esp;
        PUSH32(esp, second_arg);
        PUSH32(esp, first_arg);
        PUSH32(esp, esi);
        ecx = eax;
        PUSH32(esp, constructor_return);
        RECOMP_ICALL_SAFE(constructor, call_esp);
    }

    POP32(esp, esi);
    esp += 12u;
}

/* This vtable method starts immediately after sub_000705E0 without an
 * alignment marker, so it was omitted from generated dispatch.  It handles
 * the two timer options locally and delegates all others to the base event
 * processor.  Preserve its return value so unresolved Lua event callbacks
 * are registered by the caller instead of being mistaken for handled keys. */
void sub_00070610(void)
{
    uint32_t key = MEM32(esp + 4u);
    uint32_t value = MEM32(esp + 8u);

    PUSH32(esp, esi);
    esi = ecx;

    if (key == 0xF5315BF6u) {
        ecx = MEM32(esi + 0x50u);
        PUSH32(esp, value);
        PUSH32(esp, 0x00070643u);
        sub_00139510();
        MEMF(esi + 0x60u) = (float)g_fp_stack[g_fp_top];
        g_fp_top = (g_fp_top + 1u) & 7u;
        eax = 0u;
    } else if (key == 0x4DA20347u) {
        ecx = MEM32(esi + 0x50u);
        PUSH32(esp, value);
        PUSH32(esp, 0x00070659u);
        sub_00139490();
        MEM8(esi + 0x64u) = (LO8(eax) == 0u) ? 1u : 0u;
        eax = 0u;
    } else {
        PUSH32(esp, value);
        PUSH32(esp, key);
        ecx = esi;
        PUSH32(esp, 0x00070632u);
        sub_0006DCB0();
    }

    POP32(esp, esi);
    esp += 12u;
}

/* Resource/event hook beginning directly at the prior function's end. */
void sub_0005B8D0(void)
{
    uint32_t event = MEM32(esp + 4u);

    PUSH32(esp, esi);
    esi = ecx;
    if (MEM32(event + 4u) == 0xD2EB1B81u) {
        uint32_t payload = MEM32(event + 8u);
        PUSH32(esp, edi);
        edi = payload;
        PUSH32(esp, edi);
        ecx = esi;
        MEM32(esp + 0x10u) = payload;
        PUSH32(esp, 0x0005B8F2u);
        sub_0005B4F0();
        PUSH32(esp, edi);
        ecx = esi;
        PUSH32(esp, 0x0005B8FAu);
        sub_0005B6F0();
        POP32(esp, edi);
    }
    POP32(esp, esi);
    esp += 8u;
}

/* One-instruction vtable predicate omitted at a neighboring boundary. */
void sub_0004F540(void)
{
    SET_LO8(eax, 0u);
    esp += 4u;
}

/* Vtable traversal used while validating the newly built shell hierarchy. */
void sub_000E6E20(void)
{
    uint32_t object = ecx;
    uint32_t original_ecx = ecx;
    uint32_t saved_ebx = ebx;
    uint32_t saved_esi = esi;
    uint32_t saved_edi = edi;
    uint32_t pair = MEM32(esp + 4u);
    uint32_t query = MEM32(esp + 8u);
    uint32_t base = MEM32(object + 0x4Cu);
    uint32_t selected;
    int32_t outer_count;
    int32_t outer;
    uint32_t ok = 1u;

    if (base == 0u) {
        SET_LO8(eax, 0u);
        ecx = original_ecx;
        esp += 12u;
        return;
    }

    edx = MEM32(pair);
    selected = MEM32(pair + 4u);
    if (selected == 0u) {
        selected = (edx == 0u) ? MEM32(object + 0x3Cu) : MEM32(edx + 0x40u);
    }

    outer_count = (int32_t)MEM32(object + 0x50u);
    for (outer = 0; outer < outer_count && ok; ++outer) {
        uint32_t record = base + (uint32_t)outer * 0x20u;
        uint32_t cursor = MEM32(record + 0x1Cu) + 8u;
        int32_t inner = 0;
        int32_t inner_count = (int32_t)(int16_t)MEM16(record + 0x18u);

        for (; inner < inner_count; ++inner, cursor += 0xCu) {
            int32_t index = (int32_t)(int16_t)MEM16(cursor);
            ecx = MEM32(selected + (uint32_t)index * 4u);
            PUSH32(esp, query);
            PUSH32(esp, 0x000E6E94u);
            sub_000E6020();
            if (LO8(eax) == 0u) {
                ok = 0u;
                break;
            }
            base = MEM32(object + 0x4Cu);
            record = base + (uint32_t)outer * 0x20u;
            inner_count = (int32_t)(int16_t)MEM16(record + 0x18u);
        }
    }

    ebx = saved_ebx;
    esi = saved_esi;
    edi = saved_edi;
    ecx = original_ecx;
    SET_LO8(eax, ok ? 1u : 0u);
    esp += 12u;
}

/* Type-2 arm of sub_00195BB0's value-comparison jump table.  UCOMISS plus
 * the original LAHF/parity test is equivalent to an ordered equality test. */
void sub_00195BC7(void)
{
    eax = (MEMF(ecx + 4u) == MEMF(edx + 4u)) ? 1u : 0u;
    POP32(esp, esi);
    esp += 4u;
}

void sub_0019703C(void)
{
    dah_script_restore_and_return(g_seh_ebp, g_seh_ebp);
}

void sub_0019704A(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t base = MEM32(esp + 0x34u);
    uint32_t result = base + (esi >> 6) * 8u;
    dah_script_restore_and_return(result, frame);
}

void sub_00197060(void)
{
    uint32_t frame = g_seh_ebp;
    uint32_t base = MEM32(esp + 0x34u);
    uint32_t index = esi >> 15;
    uint32_t result;

    PUSH32(esp, 0xFFFFFFFFu);
    edx = base + index * 8u;
    ecx = edi;
    MEM32(edi) = frame;
    PUSH32(esp, 0x00197077u);
    sub_001928A0();
    result = base + ((esi >> 6) & 0x1FFu) * 8u;
    frame = MEM32(edi);
    dah_script_restore_and_return(result, frame);
}

void sub_000DCD40(void)
{
    static uint32_t trace_count;
    uint32_t key = MEM32(esp + 0x10);
    uint32_t value = MEM32(esp + 8);

    /* This is the stateful startup-block callback reached through the loader's
     * vtable.  The original uses a small byte dispatch table embedded in the
     * XBE, so read that table from guest memory instead of baking in guesses. */
    if ((key & 0x08000000u) == 0) {
        if (trace_count++ < 24) {
            fprintf(stderr,
                    "[DAH-BLOCK-CB] this=%08X key=%08X value=%08X direct\n",
                    ecx, key, value);
        }
        MEM32(ecx + key * 4u + 0xBA4u) = value;
        esp += 20;
        return;
    }

    {
        uint32_t state = MEM32(ecx + 0xCu);
        uint32_t adjusted = state - 2u;
        uint32_t action = 4u;

        if (adjusted <= 13u) {
            action = MEM8(0x000DCDC4u + adjusted);
        }

        if (trace_count++ < 24) {
            fprintf(stderr,
                    "[DAH-BLOCK-CB] this=%08X key=%08X value=%08X state=%u action=%u\n",
                    ecx, key, value, state, action);
        }

        switch (action) {
        case 0:
            MEM32(esp + 0x10) = key;
            ecx -= 4;
            sub_000DBFC0();
            return;
        case 1:
            MEM32(esp + 0x10) = key;
            ecx -= 4;
            sub_000DC910();
            return;
        case 2:
            MEM32(esp + 0x10) = key;
            ecx -= 4;
            sub_000DCA40();
            return;
        case 3:
            key &= 0x07FFFFFFu;
            MEM32(ecx + key * 4u + 0xBA4u) = value;
            MEM32(ecx + 0xCu) = 0xEu;
            esp += 20;
            return;
        default:
            esp += 20;
            return;
        }
    }
}

void sub_000DCDE0(void)
{
    static uint32_t trace_count;
    uint32_t key = MEM32(esp + 0x10);

    if ((key & 0x08000000u) == 0) {
        if (trace_count++ < 24) {
            fprintf(stderr,
                    "[DAH-STREAM-CB] this=%08X key=%08X owner=%08X direct\n",
                    ecx, key, MEM32(ecx + 0x4ACu));
        }
        ecx = MEM32(ecx + 0x4ACu);
        MEM32(esp + 0x10) = key;
        sub_000DE690();
        return;
    }

    {
        uint32_t state = MEM32(ecx + 8u);
        uint32_t adjusted = state - 3u;
        uint32_t action = 5u;

        if (adjusted <= 14u) {
            action = MEM8(0x000DCE74u + adjusted);
        }

        if (trace_count++ < 24) {
            fprintf(stderr,
                    "[DAH-STREAM-CB] this=%08X key=%08X state=%u action=%u arg3=%08X\n",
                    ecx, key, state, action, MEM32(esp + 0xCu));
        }

        switch (action) {
        case 0:
            MEM32(esp + 0x10) = key;
            ecx -= 8;
            sub_000DC050();
            return;
        case 1:
            MEM32(esp + 0x10) = key;
            ecx -= 8;
            sub_000DC970();
            return;
        case 2:
            MEM32(esp + 0x10) = key;
            ecx -= 8;
            sub_000DC090();
            return;
        case 3:
            MEM32(esp + 0x10) = key;
            ecx -= 8;
            sub_000DC0C0();
            return;
        case 4:
            MEM32(ecx + 8u) = ((int32_t)MEM32(esp + 0xCu) >= 0) ? 10u : 21u;
            esp += 20;
            return;
        default:
            esp += 20;
            return;
        }
    }
}

void sub_000DB540(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    esp -= 0x20;
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = ecx;
    PUSH32(esp, 0x000DB54Du); sub_000D9BE0();
    ecx = eax;
    PUSH32(esp, 0x000DB554u); sub_000D9C00();
    PUSH32(esp, 0x20);
    edx = eax;
    ecx = esp + 0x10;
    PUSH32(esp, 0x000DB561u); sub_000D52A0();
    PUSH32(esp, 0x000DB566u); sub_000D9C20();
    esi = eax;
    PUSH32(esp, 0x000DB56Du); sub_000D9BF0();
    edx = 1u << LO8(esi);
    if (!TEST_Z(edx, eax)) {
        PUSH32(esp, 0x000DB57Fu); sub_000D9C00();
        ebx = edi + 0x4A38;
        PUSH32(esp, 0x20);
        edx = eax;
        ecx = ebx;
        PUSH32(esp, 0x000DB590u); sub_000D52A0();
    } else {
        ebx = edi + 0x4A38;
        ecx = 8;
        esi = esp + 0xC;
        edi = ebx;
        memcpy((void *)XBOX_PTR(edi), (void *)XBOX_PTR(esi), ecx * 4);
        esi += ecx * 4; edi += ecx * 4; ecx = 0;
    }
    edx = 0;
    ecx = ebx;
    PUSH32(esp, 0x000DB5AEu); sub_000D54A0();
    ecx = eax;
    PUSH32(esp, 0x000DB5B5u); sub_000F8230();
    eax = (uint32_t)(int32_t)SMEM8(ebx);
    ecx = MEM32(esp + 0x30);
    PUSH32(esp, eax);
    PUSH32(esp, 0x233B9C);
    PUSH32(esp, 0x104);
    PUSH32(esp, ecx);
    PUSH32(esp, 0x000DB5CDu); sub_000D5410();
    esp += 0x10;
    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    esp += 0x20;
    esp += 8;
}

void sub_000E0F50(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    uint32_t saved_overlay_this;
    uint32_t entry_esp = esp;
    static uint32_t host_overlay_calls;
    uint32_t host_overlay_call = ++host_overlay_calls;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    esp -= 0x58;
    PUSH32(esp, esi);
    esi = ecx;
    saved_overlay_this = esi;
    {
        if (host_overlay_call <= 12 || (host_overlay_call % 30000u) == 0) {
            fprintf(stderr,
                    "[DAH-OVERLAY] call=%u entry=%08X caller=%08X this=%08X enabled=%u texture=%08X size=%ux%u color=%02X%02X%02X\n",
                    host_overlay_call, entry_esp, MEM32(entry_esp), esi,
                    MEM8(esi + 0x488),
                    MEM32(esi + 0x484), MEM32(esi + 0x228),
                    MEM32(esi + 0x22C), MEM8(esi + 0x234),
                    MEM8(esi + 0x235), MEM8(esi + 0x236));
            fflush(stderr);
        }
    }
    eax = ZX8(MEM8(esi + 0x234));
    ecx = ZX8(MEM8(esi + 0x235));
    edx = ZX8(MEM8(esi + 0x236));
    eax = ((eax | 0xFFFFFF00u) << 8) | ecx;
    PUSH32(esp, 0x80);
    PUSH32(esp, 0x3F800000);
    eax = (eax << 8) | edx;
    PUSH32(esp, eax);
    PUSH32(esp, 0xF3);
    PUSH32(esp, 0);
    PUSH32(esp, 0);
    PUSH32(esp, 0x000E0F93u); sub_001DC900();
    /* sub_001DC900 is contractually callee-saved for ESI.  Its generated
     * nested D3D path currently restores a clobbered spill slot; preserve the
     * retail caller's object register explicitly until that lifter issue is
     * fixed centrally. */
    esi = saved_overlay_this;
    if (host_overlay_call <= 12 || (host_overlay_call % 30000u) == 0) {
        fprintf(stderr, "[DAH-OVERLAY] after D3D state batch esi=%08X esp=%08X\n", esi, esp);
        fflush(stderr);
    }
    PUSH32(esp, 1);
    PUSH32(esp, 0x000E0F9Au); sub_001DA230();
    if (host_overlay_call <= 12 || (host_overlay_call % 30000u) == 0) {
        fprintf(stderr, "[DAH-OVERLAY] after D3D texture-stage state esi=%08X esp=%08X\n", esi, esp);
        fflush(stderr);
    }

    xmm0 = XMM_SCALAR(MEMF(0x233620));
    MEMF(esi + 0x44C) = xmm0.f[0];
    xmm0 = XMM_SCALAR(MEMF(0x225C28));
    edx = esp + 0x24; ecx = 0xBB;
    MEMF(esp + 0x24) = xmm0.f[0]; MEMF(esp + 0x28) = xmm0.f[0];
    MEMF(esp + 0x2C) = xmm0.f[0]; MEMF(esp + 0x30) = xmm0.f[0];
    PUSH32(esp, 0x000E0FD8u); sub_001D9E70();

    xmm0 = XMM_ZERO(); edx = esp + 0x24; ecx = 0xBD;
    MEMF(esp + 0x24) = xmm0.f[0]; MEMF(esp + 0x28) = xmm0.f[0];
    MEMF(esp + 0x2C) = xmm0.f[0]; MEMF(esp + 0x30) = xmm0.f[0];
    PUSH32(esp, 0x000E1001u); sub_001D9E70();

    xmm0 = XMM_SCALAR(MEMF(0x2342B4)); edx = esp + 0x24; ecx = 0xBC;
    MEMF(esp + 0x24) = xmm0.f[0]; MEMF(esp + 0x28) = xmm0.f[0];
    MEMF(esp + 0x2C) = xmm0.f[0]; MEMF(esp + 0x30) = xmm0.f[0];
    PUSH32(esp, 0x000E102Fu); sub_001D9E70();

    xmm0 = XMM_SCALAR(MEMF(0x225C3C)); edx = esp + 0x24; ecx = 0xBE;
    MEMF(esp + 0x24) = xmm0.f[0]; MEMF(esp + 0x28) = xmm0.f[0];
    MEMF(esp + 0x2C) = xmm0.f[0]; MEMF(esp + 0x30) = xmm0.f[0];
    PUSH32(esp, 0x000E105Du); sub_001D9E70();

    xmm0 = XMM_SCALAR(MEMF(0x2342B0)); edx = esp + 0x24; ecx = 0xBF;
    MEMF(esp + 0x24) = xmm0.f[0]; MEMF(esp + 0x28) = xmm0.f[0];
    MEMF(esp + 0x2C) = xmm0.f[0]; MEMF(esp + 0x30) = xmm0.f[0];
    PUSH32(esp, 0x000E108Bu); sub_001D9E70();

    ecx = MEM32(esi + 0x22C);
    xmm0 = XMM_ZERO();
    eax = MEM32(esi + 0x228);
    PUSH32(esp, 0x49800000);
    edx = esp + 0x48;
    MEM32(esp + 0x54) = ecx;
    ecx = MEM32(0x250E5C);
    MEMF(esp + 0x58) = xmm0.f[0];
    xmm0 = XMM_SCALAR(MEMF(0x225C28));
    PUSH32(esp, edx);
    MEM32(esp + 0x4C) = 0; MEM32(esp + 0x50) = 0;
    MEM32(esp + 0x54) = eax; MEMF(esp + 0x60) = xmm0.f[0];
    PUSH32(esp, 0x000E10DBu); sub_000E03F0();

    eax = MEM32(0x250E5C);
    xmm0.f[0] = (float)(int32_t)MEM32(eax + 0x228); MEMF(esp + 4) = xmm0.f[0];
    xmm0.f[0] = (float)(int32_t)MEM32(eax + 0x22C); MEMF(esp + 0xC) = xmm0.f[0];
    SET_LO8(eax, MEM8(esi + 0x488));
    if (TEST_NZ(LO8(eax), LO8(eax)) && MEM32(esi + 0x484)) {
        edx = 0; ecx = 0x4035C;
        PUSH32(esp, 0x000E1124u); sub_001D8150();
        edx = MEM32(0x1E84C8) | 1;
        eax = 3;
        MEM32(0x1E87D0) = 0; MEM32(0x1E84D0) = eax;
        MEM32(0x1E84C8) = edx; MEM32(0x1E84D4) = eax;
        eax = MEM32(esi + 0x484);
        PUSH32(esp, eax); PUSH32(esp, 0);
        PUSH32(esp, 0x000E115Au); sub_001DB110();
        ecx = MEM32(0x27DEFC); PUSH32(esp, ecx);
        PUSH32(esp, 0x000E1166u); sub_001DCD60();

        xmm0 = XMM_SCALAR(MEMF(0x225C3C));
        xmm1 = XMM_SCALAR(MEMF(0x225C28));
        edx = esp + 0x34; PUSH32(esp, edx);
        MEMF(esp + 0x44) = xmm1.f[0];
        xmm1 = XMM_SCALAR(MEMF(esp + 8));
        eax = esp + 8; PUSH32(esp, eax);
        xmm2 = xmm1; xmm2.f[0] -= xmm0.f[0];
        ecx = esp + 0x14; PUSH32(esp, ecx);
        MEMF(esp + 0x10) = xmm2.f[0];
        xmm2 = XMM_SCALAR(MEMF(esp + 0x18));
        edx = esp + 0x20; xmm3 = xmm2; xmm3.f[0] -= xmm0.f[0];
        PUSH32(esp, edx);
        eax = esp + 0x2C;
        MEMF(esp + 0x44) = xmm0.f[0]; MEMF(esp + 0x48) = xmm0.f[0];
        MEMF(esp + 0x4C) = xmm0.f[0]; MEMF(esp + 0x1C) = xmm0.f[0];
        MEMF(esp + 0x20) = xmm0.f[0];
        xmm0 = XMM_ZERO(); PUSH32(esp, eax); ecx = esi;
        MEMF(esp + 0x1C) = xmm3.f[0]; MEMF(esp + 0x28) = xmm1.f[0];
        MEMF(esp + 0x2C) = xmm2.f[0]; MEMF(esp + 0x30) = xmm0.f[0];
        MEMF(esp + 0x34) = xmm0.f[0];
        PUSH32(esp, 0x000E11FBu); sub_000E8DB0();
        edx = 1; ecx = 0x4035C;
        PUSH32(esp, 0x000E120Au); sub_001D8150();
        MEM32(0x1E87D0) = 1;
    }
    POP32(esp, esi);
    esp += 0x58;
    if (host_overlay_call <= 12 || (host_overlay_call % 30000u) == 0) {
        fprintf(stderr,
                "[DAH-OVERLAY] exit call=%u entry=%08X pre-ret=%08X delta=%d\n",
                host_overlay_call, entry_esp, esp, (int32_t)(esp - entry_esp));
        fflush(stderr);
    }
    esp += 4;
}

/* Retail vtable target omitted by the initial linear function split. */
void sub_000F1800(void)
{
    eax = (MEM32(ecx + 0x30) - 1u) & 1u;
    MEM32(ecx + 0x30) = eax;
    MEM32(ecx + 0x34) = 0;
    esp += 4;
}

/* Retail hierarchy validator at 0x000F0D10.  The initial linear function
 * split missed this vtable target even though its complete body is present in
 * the XBE. */
void sub_000F0D10(void)
{
    static uint32_t trace_count;
    uint32_t object = ecx;
    uint32_t saved_ebx = ebx;
    uint32_t saved_esi = esi;
    uint32_t saved_edi = edi;
    uint32_t pair = MEM32(esp + 4u);
    uint32_t query = MEM32(esp + 8u);
    uint32_t groups = MEM32(object + 0x24u);
    int32_t outer_count = (int32_t)MEM32(object + 0x28u);
    uint32_t ok = 1u;
    int32_t outer;

    if (groups == 0u) {
        ok = 0u;
    } else {
        uint32_t base = MEM32(pair);

        for (outer = 0; outer < outer_count && ok; ++outer) {
            uint32_t group = groups + (uint32_t)outer * 0x20u;
            uint32_t cursor = MEM32(group + 0x1Cu) + 0x8Cu;
            int32_t inner_count = (int32_t)(int16_t)MEM16(group + 0x1Au);
            int32_t inner;

            for (inner = 0; inner < inner_count; ++inner, cursor += 0x8Eu) {
                int32_t index = (int32_t)(int16_t)MEM16(cursor);
                uint32_t table = MEM32(base + 0x84u);

                ecx = MEM32(table + (uint32_t)index * 4u);
                PUSH32(esp, query);
                PUSH32(esp, 0x000F0D7Au);
                sub_000E6020();
                if (LO8(eax) == 0u) {
                    if (trace_count < 32u) {
                        fprintf(stderr,
                                "[DAH-HIERARCHY-VALIDATE] call=%u result=0 object=%08X groups=%08X count=%d pair=%08X base=%08X outer=%d inner=%d/%d index=%d target=%08X query=%08X\n",
                                trace_count + 1u, object, groups, outer_count, pair, base,
                                outer, inner, inner_count, index, ecx, query);
                    }
                    ok = 0u;
                    break;
                }
            }
        }
    }

    ebx = saved_ebx;
    esi = saved_esi;
    edi = saved_edi;
    ++trace_count;
    if (trace_count <= 8u && ok) {
        fprintf(stderr,
                "[DAH-HIERARCHY-VALIDATE] call=%u result=1 object=%08X groups=%08X count=%d pair=%08X query=%08X\n",
                trace_count, object, groups, outer_count, pair, query);
    }
    SET_LO8(eax, ok ? 1u : 0u);
    esp += 12u;
}

/* Retail vtable target omitted by the initial linear function split. */
void sub_001A18E0(void)
{
    eax = 0;
    MEM16(ecx + 0x1E) = 0;
    MEM16(ecx + 0x1C) = 0;
    esp += 4;
}

void sub_001EC7AC(void)
{
    eax = MEM32(esp + 4);
    MEM32(eax + 4)++;
    eax = MEM32(eax + 4);
    esp += 8;
}

/* DirectSound COM AddRef entry point. The retail virtual table points at this
 * address, but it falls between the original linear-sweep function splits. */
void sub_001ECE37(void)
{
    uint32_t lock_taken;

    PUSH32(esp, 0x001ECE3Cu);
    sub_001EC935();
    lock_taken = ZX8(LO8(eax));

    if (MEM32(0x20A1B4) != 0) {
        if (lock_taken != 0) {
            uint32_t call_esp = esp;
            uint32_t target = MEM32(0x225AC0);
            PUSH32(esp, 0x20A1C0);
            PUSH32(esp, 0x001ECE57u);
            RECOMP_ICALL_SAFE(target, call_esp);
        }
        eax = 0x80004005u;
        esp += 8;
        return;
    }

    eax = MEM32(esp + 4);
    MEM32(eax + 4)++;
    PUSH32(esp, esi);
    esi = MEM32(eax + 4);
    if (lock_taken != 0) {
        uint32_t call_esp = esp;
        uint32_t target = MEM32(0x225AC0);
        PUSH32(esp, 0x20A1C0);
        PUSH32(esp, 0x001ECE78u);
        RECOMP_ICALL_SAFE(target, call_esp);
    }
    eax = esi;
    POP32(esp, esi);
    esp += 8;
}

/* DirectSound voice-format refresh virtual method. Like sub_001ECE37, this is
 * a real retail entry point skipped by the initial function boundary pass. */
void sub_001F4FE5(void)
{
    uint32_t channel_count;

    PUSH32(esp, esi);
    esi = ecx;
    eax = ZX8(MEM8(esi + 0x12));
    PUSH32(esp, edi);
    edi = eax & 1u;

    if (edi != 0) {
        PUSH32(esp, 0);
        PUSH32(esp, 0x001F4FFCu);
        sub_001F4DD4();
        if ((int32_t)eax < 0)
            goto done;

        ecx = esi;
        PUSH32(esp, 0x001F5007u);
        sub_001F3F19();
        eax = MEM32(esi + 0x80);
        channel_count = ZX8(MEM8(eax + 0xE));
        channel_count--;
        channel_count = (uint32_t)((int32_t)channel_count >> 1);
        SET_LO8(channel_count, LO8(channel_count) + 1);
        if (LO8(channel_count) != MEM8(esi + 0x64)) {
            ecx = esi;
            PUSH32(esp, 0x001F5022u);
            sub_001F4F98();
        }
    }

    ecx = esi;
    PUSH32(esp, 0x001F5029u);
    sub_001F2CFF();
    if ((int32_t)eax < 0 || edi == 0)
        goto done;

    POP32(esp, edi);
    ecx = esi;
    POP32(esp, esi);
    sub_001F4CD6();
    return;

done:
    POP32(esp, edi);
    POP32(esp, esi);
    esp += 4;
}

/* The linear sweep skipped this 0x12-byte pool-element constructor. */
void sub_002206E2(void)
{
    eax = ecx;
    MEM8(eax) = 0xFF;
    MEM8(eax + 1) = 0x80;
    MEM8(eax + 2) = 0x80;
    MEM8(eax + 3) = 0x80;
    esp += 4;
}

/* USB/XPP request-pool initialization.  This real retail function occupies a
 * disassembly gap, so the generated direct-call stub previously skipped its
 * allocation and left the pool pointer at 0. */
void sub_0021FA38(void)
{
    uint32_t ebp = g_ebp;
    uint32_t allocation;

    PUSH32(esp, ebp);
    ebp = esp;
    g_ebp = ebp;
    SET_LO8(eax, MEM8(ebp + 8));
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    esi = ecx;
    edi = ZX8(LO8(eax));
    MEM8(esi + 0x7A) = LO8(eax);
    ebx = 0;
    eax = edi;
    PUSH32(esp, 0x44425355);
    eax <<= 5;
    PUSH32(esp, eax);
    MEM8(esi) = LO8(ebx);
    MEM8(esi + 0x79) = LO8(ebx);
    MEM32(esi + 0x7C) = ebx;
    MEM32(esi + 0x80) = ebx;
    g_ebp = ebp;
    PUSH32(esp, 0x0021FA69u);
    sub_0022175B();

    allocation = eax;
    MEM32(ebp + 8) = allocation;
    if (allocation != 0) {
        PUSH32(esp, 0x002206E2u);
        PUSH32(esp, edi);
        PUSH32(esp, 0x20);
        PUSH32(esp, allocation);
        g_ebp = ebp;
        PUSH32(esp, 0x0021FA7Eu);
        sub_00011030();
        eax = MEM32(ebp + 8);
    } else {
        eax = 0;
    }

    MEM32(esi + 0xE0) = eax;
    SET_LO8(eax, MEM8(ebp + 0xC));
    MEM8(esi + 0x7B) = LO8(eax);
    SET_LO8(eax, 0);
    ecx = ZX8(MEM8(esi + 0x7A));
    ecx--;
    if ((int32_t)ecx > 0) {
        ecx = 0;
        do {
            edx = MEM32(esi + 0xE0);
            SET_LO8(eax, LO8(eax) + 1);
            ecx <<= 5;
            MEM8(ecx + edx + 1) = LO8(eax);
            edx = ZX8(MEM8(esi + 0x7A));
            ecx = (uint32_t)(int32_t)(int8_t)LO8(eax);
            edx--;
        } while ((int32_t)ecx < (int32_t)edx);
    }

    {
        uint32_t call_esp = esp;
        uint32_t target = MEM32(0x225B3C);
        PUSH32(esp, ebx);
        PUSH32(esp, 0x002214E7u);
        eax = esi + 0x34;
        PUSH32(esp, eax);
        PUSH32(esp, 0x0021FAC9u);
        RECOMP_ICALL_SAFE(target, call_esp);
    }
    {
        uint32_t call_esp = esp;
        uint32_t target = MEM32(0x225B38);
        PUSH32(esp, ebx);
        esi += 0x50;
        PUSH32(esp, esi);
        PUSH32(esp, 0x0021FAD4u);
        RECOMP_ICALL_SAFE(target, call_esp);
    }

    POP32(esp, edi);
    POP32(esp, esi);
    POP32(esp, ebx);
    POP32(esp, ebp);
    g_ebp = ebp;
    esp += 12;
}

void sub_0021FADB(void)
{
    int _flags = 0;
    uint32_t _fa = 0, _fb = 0;
    int32_t _fas = 0, _fbs = 0;
    (void)_flags; (void)_fa; (void)_fb; (void)_fas; (void)_fbs;

    eax = 0;
    _fa = MEM8(0x21F924); _fb = LO8(eax);
    _fas = (int32_t)(int8_t)_fa; _fbs = (int32_t)(int8_t)_fb;
    PUSH32(esp, edi);
    SET_LO8(eax, CMP_NE(_fa, _fb) ? 1 : 0);
    MEM16(0x286D22) = 0;
    PUSH32(esp, 0x48425355);
    eax = eax * 8 + 6;
    MEM16(0x286D20) = LO16(eax);
    eax = ZX16(LO16(eax)) << 6;
    PUSH32(esp, eax);
    PUSH32(esp, 0x0021FB0Du); sub_0022175B();
    ecx = ZX16(MEM16(0x286D20)) << 6;
    edx = ecx;
    edi = eax;
    ecx >>= 2;
    MEM32(0x286D24) = edi;
    eax = 0;
    for (uint32_t i = 0; i < ecx; ++i) MEM32(edi + i * 4) = eax;
    edi += ecx * 4; ecx = 0;
    {
        uint32_t _icall_esp = g_esp;
        PUSH32(esp, 0);
        ecx = edx & 3;
        PUSH32(esp, 0x286CD0);
        memset((void *)XBOX_PTR(edi), (uint8_t)eax, ecx);
        edi += ecx; ecx = 0;
        { uint32_t _icall_target = MEM32(0x225B38);
          PUSH32(esp, 0x0021FB3Cu); RECOMP_ICALL_SAFE(_icall_target, _icall_esp); }
    }
    MEM32(0x286D18) = 0;
    POP32(esp, edi);
    esp += 8;
}

/**
 * sub_0020DB70
 * BINK codec frame-buffer setup function. Called via vtable ptr at bink_obj+4
 * from sub_0020AB70. Sets up bink->field_C8 and bink->field_CC (audio codec
 * function pointer slots) via sub_001EDCF5, then stores them through out_ptr1
 * and out_ptr2. Returns 1 if both slots were filled, 0 otherwise.
 * CC: stdcall, 3 args (bink_obj, out_ptr1, out_ptr2).
 * Translated from XBE VA 0x0020DB70 - 0x0020DBF7.
 */
void sub_0020DB70(void)
{
    PUSH32(esp, ebx);
    PUSH32(esp, esi);
    esi = MEM32(esp + 0xC);            /* arg1: bink_obj */
    edx = MEM32(esi + 0xAC);
    PUSH32(esp, edi);
    edi = MEM32(esi + 0xA8);

    /* build arg list for sub_001EDCF5 (stdcall, 8 args, ret 32) */
    PUSH32(esp, 0);
    PUSH32(esp, esi + 0xD0);
    ecx = esi + 0xC8;                  /* &bink->field_C8 */
    PUSH32(esp, esi + 0xD4);
    PUSH32(esp, ecx);
    eax = esi + 0xCC;                  /* &bink->field_CC */
    PUSH32(esp, eax);
    PUSH32(esp, edx);
    MEM32(eax) = 0;                    /* bink->field_CC = 0 */
    eax = MEM32(esi + 0x7C);
    PUSH32(esp, edi);
    PUSH32(esp, eax);
    MEM32(ecx) = 0;                    /* bink->field_C8 = 0 */
    PUSH32(esp, 0x0020DBB8u); sub_001EDCF5(); /* call 0x001EDCF5 */

loc_0020DBB8: ;
    /* store results through caller's output pointers */
    ecx = MEM32(esi + 0xCC);
    edx = MEM32(esp + 0x14);          /* arg2: out_ptr1 */
    MEM32(edx) = ecx;
    eax = MEM32(esi + 0xC8);
    ecx = MEM32(esp + 0x18);          /* arg3: out_ptr2 */
    MEM32(ecx) = eax;
    eax = MEM32(esi + 0xCC);
    if (eax == 0) goto loc_0020DBEF;
    eax = MEM32(esi + 0xC8);
    if (eax == 0) goto loc_0020DBEF;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 1;
    POP32(esp, ebx);
    esp += 0x10; return; /* ret 0xC: stdcall 3 args */

loc_0020DBEF: ;
    POP32(esp, edi);
    POP32(esp, esi);
    eax = 0;
    POP32(esp, ebx);
    esp += 0x10; return; /* ret 0xC: stdcall 3 args */
}

/**
 * sub_0020DCB0
 * BINK codec stream-advance function. Called via vtable ptr at bink_obj+8
 * from sub_0020AB70. Advances the stream read position (bink[0xA8]) by arg2,
 * wrapping at bink[0x84], and decrements bink[0xAC] by arg2. Zeros bink[0xCC].
 * Conditionally calls sub_0020DC00 when bink[0xA0]==0 && bink[0xAC]==0 && bink[0xA4]==0.
 * Always returns eax=1.
 * CC: stdcall, 2 args (bink_obj, advance_amount).
 * Translated from XBE VA 0x0020DCB0 - 0x0020DD36.
 */
void sub_0020DCB0(void)
{
    edx = MEM32(esp + 8);             /* arg2: advance_amount (read before saves) */
    PUSH32(esp, esi);
    PUSH32(esp, edi);
    edi = MEM32(esp + 0xC);           /* arg1: bink_obj */

    /* bink[0xA8] += arg2; if >= bink[0x84]: wrap */
    eax = MEM32(edi + 0xA8) + edx;
    MEM32(edi + 0xA8) = eax;
    if ((uint32_t)eax >= (uint32_t)MEM32(edi + 0x84)) {
        eax -= MEM32(edi + 0x84);
        MEM32(edi + 0xA8) = eax;
    }
    MEM32(edi + 0xAC) = MEM32(edi + 0xAC) - edx;

    /* call sub_001EC9D7(bink[0x7C], bink[0xCC], bink[0xC8], bink[0xD4], bink[0xD0]) */
    eax = MEM32(edi + 0xD0);
    ecx = MEM32(edi + 0xD4);
    edx = MEM32(edi + 0xC8);
    esi = edi + 0x7C;
    PUSH32(esp, eax);                 /* bink[0xD0] */
    eax = MEM32(esi + 0x50);         /* bink[0xCC] */
    PUSH32(esp, ecx);                 /* bink[0xD4] */
    ecx = MEM32(esi);                 /* bink[0x7C] */
    PUSH32(esp, edx);                 /* bink[0xC8] */
    PUSH32(esp, eax);                 /* bink[0xCC] */
    PUSH32(esp, ecx);                 /* bink[0x7C] */
    PUSH32(esp, 0x0020DD04u); sub_001EC9D7(); /* stdcall 5 args, ret 20 */

loc_0020DD04: ;
    eax = MEM32(edi + 0xA0);
    MEM32(edi + 0xCC) = 0;            /* always zero bink[0xCC] */
    if (eax != 0) goto loc_0020DD31;
    eax = MEM32(edi + 0xAC);
    if (eax != 0) goto loc_0020DD31;
    eax = MEM32(edi + 0xA4);
    if (eax != 0) goto loc_0020DD31;
    PUSH32(esp, 0x0020DD31u); sub_0020DC00(); /* conditional call */

loc_0020DD31: ;
    POP32(esp, edi);
    eax = 1;
    POP32(esp, esi);
    esp += 0xC; return; /* ret 0x8: stdcall 2 args */
}
