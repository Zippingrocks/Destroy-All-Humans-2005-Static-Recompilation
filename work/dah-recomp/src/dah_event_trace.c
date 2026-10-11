#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xbox/xboxrecomp.h>
#include "dah_event_trace.h"

enum { DAH_EVENT_CAPACITY = 16384, DAH_EVENT_NAME = 64 };
enum { DAH_EVENT_AI_STATE = 1, DAH_EVENT_FRAME = 2,
       DAH_EVENT_ABILITY_FLAG = 3, DAH_EVENT_TAG_ABILITY = 4,
       DAH_EVENT_PHYSICS_BODY_COMMAND = 5,
       DAH_EVENT_PLAYER_RENDER = 6, DAH_EVENT_SCENE_FLASH = 7,
       DAH_EVENT_UI_STATE = 8 };

typedef struct DahTraceEvent {
    uint64_t sequence;
    uint32_t world_tick;
    uint32_t type;
    union {
        struct {
            uint32_t manager, owner;
            uint32_t old_state, new_state;
            uint32_t old_id, new_id;
            uint32_t old_name_pointer, new_name_pointer;
            uint32_t caller;
            char old_name[DAH_EVENT_NAME];
            char new_name[DAH_EVENT_NAME];
        } ai;
        struct {
            uint64_t host_frame;
            uint32_t loop;
            uint32_t interval_us, target_us;
            uint32_t logic_us, render_us, present_us, total_us;
            uint32_t draw_count, draw_delta;
            uint32_t present_result, flags;
        } frame;
        struct {
            uint32_t command, owner, offset;
            uint32_t old_value, new_value, caller;
        } ability;
        struct {
            uint32_t ability_hash, actor, offset;
            uint32_t old_value, new_value, caller;
        } tag_ability;
        struct {
            uint32_t tag_hash, filter_hash, actor, forceable;
            uint32_t requested_enable, caller;
        } physics_body_command;
        struct {
            uint32_t control, player, crypto, render, gate140;
            uint32_t health_bits, maximum_health_bits, damage_gate;
            uint32_t global_damage_disable;
            uint32_t scene, scene_flags;
            uint32_t previous_crypto, previous_render, previous_gate140;
            uint32_t previous_health_bits, previous_damage_gate;
            uint32_t previous_global_damage_disable;
            uint32_t previous_scene, previous_scene_flags, changes;
        } player_render;
        struct {
            uint32_t frame, object, model, object_flags;
            uint32_t model_type, model_flags;
            uint32_t visible, previous_visible, transition_gap;
            float x, y, z;
        } scene_flash;
        struct {
            uint32_t root, active_mask, previous_active_mask;
            uint32_t mission_defeat, mission_complete, titlecard;
            uint32_t start_menu_background, messages, cinematic, main, fade;
        } ui_state;
    } payload;
} DahTraceEvent;

static DahTraceEvent events[DAH_EVENT_CAPACITY];
static volatile LONG write_index;
static volatile LONG read_index;
static volatile LONG dropped_events;
static volatile LONG running;
static volatile LONG enabled;
static HANDLE wake_event;
static HANDLE writer_thread;
static FILE *output;

static int guest_range(uint32_t address, uint32_t size)
{
    return address >= 0x10000u && address < 0x04000000u &&
           size <= 0x04000000u - address;
}

static uint32_t guest_u32(uint32_t address)
{
    ptrdiff_t offset = xbox_GetMemoryOffset();
    if (!guest_range(address, 4u)) return 0u;
    return *(const uint32_t *)((uintptr_t)offset + address);
}

static void guest_name(uint32_t address, char destination[DAH_EVENT_NAME])
{
    ptrdiff_t offset = xbox_GetMemoryOffset();
    unsigned index;
    destination[0] = '\0';
    if (!guest_range(address, 1u)) return;
    for (index = 0; index + 1u < DAH_EVENT_NAME; ++index) {
        unsigned char value;
        if (!guest_range(address + index, 1u)) break;
        value = *(const unsigned char *)((uintptr_t)offset + address + index);
        if (!value) break;
        destination[index] = value >= 32u && value < 127u && value != '"' &&
                             value != '\\' ? (char)value : '?';
    }
    destination[index] = '\0';
}

static DWORD WINAPI writer_main(void *unused)
{
    DWORD last_flush = GetTickCount();
    (void)unused;
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
    while (InterlockedCompareExchange(&running, 0, 0) ||
           InterlockedCompareExchange(&read_index, 0, 0) !=
           InterlockedCompareExchange(&write_index, 0, 0)) {
        LONG read = InterlockedCompareExchange(&read_index, 0, 0);
        LONG write = InterlockedCompareExchange(&write_index, 0, 0);
        while (read != write) {
            const DahTraceEvent *event = &events[(uint32_t)read &
                                                  (DAH_EVENT_CAPACITY - 1u)];
            if (event->type == DAH_EVENT_AI_STATE) fprintf(output,
                    "{\"event\":\"ai-state-commit\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"manager\":\"%08X\","
                    "\"owner\":\"%08X\",\"oldState\":\"%08X\","
                    "\"newState\":\"%08X\",\"oldStateId\":\"%08X\","
                    "\"newStateId\":\"%08X\",\"oldStateName\":\"%s\","
                    "\"newStateName\":\"%s\",\"oldNamePointer\":\"%08X\","
                    "\"newNamePointer\":\"%08X\",\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.ai.manager, event->payload.ai.owner,
                    event->payload.ai.old_state, event->payload.ai.new_state,
                    event->payload.ai.old_id, event->payload.ai.new_id,
                    event->payload.ai.old_name, event->payload.ai.new_name,
                    event->payload.ai.old_name_pointer,
                    event->payload.ai.new_name_pointer,
                    event->payload.ai.caller);
            else if (event->type == DAH_EVENT_FRAME) fprintf(output,
                    "{\"event\":\"frame\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"hostFrame\":%llu,\"loop\":%u,"
                    "\"intervalUs\":%u,\"targetUs\":%u,\"logicUs\":%u,"
                    "\"renderUs\":%u,\"presentUs\":%u,\"totalUs\":%u,"
                    "\"drawCount\":%u,\"drawDelta\":%u,"
                    "\"presentResult\":\"%08X\",\"flags\":%u}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    (unsigned long long)event->payload.frame.host_frame,
                    event->payload.frame.loop, event->payload.frame.interval_us,
                    event->payload.frame.target_us, event->payload.frame.logic_us,
                    event->payload.frame.render_us, event->payload.frame.present_us,
                    event->payload.frame.total_us, event->payload.frame.draw_count,
                    event->payload.frame.draw_delta,
                    event->payload.frame.present_result, event->payload.frame.flags);
            else if (event->type == DAH_EVENT_ABILITY_FLAG) fprintf(output,
                    "{\"event\":\"ability-flag\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"ability\":\"jetpack-enabled\","
                    "\"command\":\"%08X\",\"owner\":\"%08X\","
                    "\"offset\":\"%X\",\"oldStoredDisable\":%u,"
                    "\"newStoredDisable\":%u,\"oldEnabled\":%u,"
                    "\"newEnabled\":%u,\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.ability.command, event->payload.ability.owner,
                    event->payload.ability.offset,
                    event->payload.ability.old_value,
                    event->payload.ability.new_value,
                    event->payload.ability.old_value ? 0u : 1u,
                    event->payload.ability.new_value ? 0u : 1u,
                    event->payload.ability.caller);
            else if (event->type == DAH_EVENT_TAG_ABILITY) fprintf(output,
                    "{\"event\":\"tag-alien-ability\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"abilityHash\":\"%08X\","
                    "\"actor\":\"%08X\",\"offset\":\"%X\","
                    "\"oldStoredDisable\":%u,\"newStoredDisable\":%u,"
                    "\"oldEnabled\":%u,\"newEnabled\":%u,"
                    "\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.tag_ability.ability_hash,
                    event->payload.tag_ability.actor,
                    event->payload.tag_ability.offset,
                    event->payload.tag_ability.old_value,
                    event->payload.tag_ability.new_value,
                    event->payload.tag_ability.old_value ? 0u : 1u,
                    event->payload.tag_ability.new_value ? 0u : 1u,
                    event->payload.tag_ability.caller);
            else if (event->type == DAH_EVENT_PHYSICS_BODY_COMMAND) fprintf(output,
                    "{\"event\":\"physics-body-command\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"tagHash\":\"%08X\","
                    "\"filterHash\":\"%08X\",\"actor\":\"%08X\","
                    "\"forceable\":\"%08X\",\"requestedEnable\":%u,"
                    "\"caller\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.physics_body_command.tag_hash,
                    event->payload.physics_body_command.filter_hash,
                    event->payload.physics_body_command.actor,
                    event->payload.physics_body_command.forceable,
                    event->payload.physics_body_command.requested_enable,
                    event->payload.physics_body_command.caller);
            else if (event->type == DAH_EVENT_PLAYER_RENDER) fprintf(output,
                    "{\"event\":\"player-render-state\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"control\":\"%08X\","
                    "\"player\":\"%08X\",\"crypto\":\"%08X\","
                    "\"render\":\"%08X\",\"stateByte140\":%u,"
                    "\"healthBits\":\"%08X\",\"maximumHealthBits\":\"%08X\","
                    "\"damageGate\":\"%08X\",\"globalDamageDisable\":%u,"
                    "\"scene\":\"%08X\",\"sceneFlags\":\"%08X\","
                    "\"previousCrypto\":\"%08X\","
                    "\"previousRender\":\"%08X\","
                    "\"previousStateByte140\":%u,"
                    "\"previousHealthBits\":\"%08X\","
                    "\"previousDamageGate\":\"%08X\","
                    "\"previousGlobalDamageDisable\":%u,"
                    "\"previousScene\":\"%08X\","
                    "\"previousSceneFlags\":\"%08X\","
                    "\"changes\":%u}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.player_render.control,
                    event->payload.player_render.player,
                    event->payload.player_render.crypto,
                    event->payload.player_render.render,
                    event->payload.player_render.gate140,
                    event->payload.player_render.health_bits,
                    event->payload.player_render.maximum_health_bits,
                    event->payload.player_render.damage_gate,
                    event->payload.player_render.global_damage_disable,
                    event->payload.player_render.scene,
                    event->payload.player_render.scene_flags,
                    event->payload.player_render.previous_crypto,
                    event->payload.player_render.previous_render,
                    event->payload.player_render.previous_gate140,
                    event->payload.player_render.previous_health_bits,
                    event->payload.player_render.previous_damage_gate,
                    event->payload.player_render.previous_global_damage_disable,
                    event->payload.player_render.previous_scene,
                    event->payload.player_render.previous_scene_flags,
                    event->payload.player_render.changes);
            else if (event->type == DAH_EVENT_SCENE_FLASH) fprintf(output,
                    "{\"event\":\"scene-cull-flash\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"frame\":%u,"
                    "\"object\":\"%08X\",\"model\":\"%08X\","
                    "\"objectFlags\":\"%08X\",\"modelType\":%u,"
                    "\"modelFlags\":\"%08X\",\"visible\":%u,"
                    "\"previousVisible\":%u,\"transitionGap\":%u,"
                    "\"position\":[%.9g,%.9g,%.9g]}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.scene_flash.frame,
                    event->payload.scene_flash.object,
                    event->payload.scene_flash.model,
                    event->payload.scene_flash.object_flags,
                    event->payload.scene_flash.model_type,
                    event->payload.scene_flash.model_flags,
                    event->payload.scene_flash.visible,
                    event->payload.scene_flash.previous_visible,
                    event->payload.scene_flash.transition_gap,
                    event->payload.scene_flash.x,
                    event->payload.scene_flash.y,
                    event->payload.scene_flash.z);
            else if (event->type == DAH_EVENT_UI_STATE) fprintf(output,
                    "{\"event\":\"ui-active-state\",\"sequence\":%llu,"
                    "\"worldTick\":%u,\"root\":\"%08X\","
                    "\"activeMask\":\"%08X\","
                    "\"previousActiveMask\":\"%08X\","
                    "\"missionDefeat\":\"%08X\","
                    "\"missionComplete\":\"%08X\","
                    "\"titlecard\":\"%08X\","
                    "\"startMenuBackground\":\"%08X\","
                    "\"messages\":\"%08X\",\"cinematic\":\"%08X\","
                    "\"main\":\"%08X\",\"fade\":\"%08X\"}\n",
                    (unsigned long long)event->sequence, event->world_tick,
                    event->payload.ui_state.root,
                    event->payload.ui_state.active_mask,
                    event->payload.ui_state.previous_active_mask,
                    event->payload.ui_state.mission_defeat,
                    event->payload.ui_state.mission_complete,
                    event->payload.ui_state.titlecard,
                    event->payload.ui_state.start_menu_background,
                    event->payload.ui_state.messages,
                    event->payload.ui_state.cinematic,
                    event->payload.ui_state.main,
                    event->payload.ui_state.fade);
            ++read;
            InterlockedExchange(&read_index, read);
        }
        if (GetTickCount() - last_flush >= 1000u) {
            fflush(output);
            last_flush = GetTickCount();
        }
        if (InterlockedCompareExchange(&running, 0, 0))
            WaitForSingleObject(wake_event, 50u);
    }
    return 0;
}

void dah_event_trace_initialize(const char *run_id, const char *started_utc,
                                uint64_t executable_hash)
{
    const char *path = getenv("DAH_EVENT_TRACE");
    /* Always retain the most recent run so a one-frame hitch or transient AI
     * state is available after the fact. A custom path is useful for parity
     * sessions; DAH_EVENT_TRACE=0 is the explicit opt-out. */
    if (path && !strcmp(path, "0")) return;
    if (!path || !*path) path = "dah_event_trace.jsonl";
    output = fopen(path, "wb");
    if (!output) return;
    setvbuf(output, NULL, _IOFBF, 64u * 1024u);
    fprintf(output,
            "{\"event\":\"run-start\",\"schema\":1,\"runId\":\"%s\","
            "\"pid\":%lu,\"startedUtc\":\"%s\","
            "\"executableFnv1a64\":\"%016llX\"}\n",
            run_id, GetCurrentProcessId(), started_utc,
            (unsigned long long)executable_hash);
    fflush(output);
    wake_event = CreateEventA(NULL, FALSE, FALSE, NULL);
    if (!wake_event) {
        fclose(output);
        output = NULL;
        return;
    }
    InterlockedExchange(&running, 1);
    writer_thread = CreateThread(NULL, 0, writer_main, NULL, 0, NULL);
    if (!writer_thread) {
        InterlockedExchange(&running, 0);
        CloseHandle(wake_event);
        wake_event = NULL;
        fclose(output);
        output = NULL;
        return;
    }
    InterlockedExchange(&enabled, 1);
}

void dah_event_trace_ai_state(uint32_t manager, uint32_t owner,
                              uint32_t old_state, uint32_t new_state,
                              uint32_t old_id, uint32_t new_id,
                              uint32_t old_name, uint32_t new_name,
                              uint32_t caller)
{
    LONG write, read;
    DahTraceEvent *event;
    uint32_t world;
    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->type = DAH_EVENT_AI_STATE;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.ai.manager = manager;
    event->payload.ai.owner = owner;
    event->payload.ai.old_state = old_state;
    event->payload.ai.new_state = new_state;
    event->payload.ai.old_id = old_id;
    event->payload.ai.new_id = new_id;
    event->payload.ai.old_name_pointer = old_name;
    event->payload.ai.new_name_pointer = new_name;
    event->payload.ai.caller = caller;
    guest_name(old_name, event->payload.ai.old_name);
    guest_name(new_name, event->payload.ai.new_name);
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_frame(uint64_t host_frame, uint32_t loop,
                           uint32_t interval_us, uint32_t target_us,
                           uint32_t logic_us, uint32_t render_us,
                           uint32_t present_us, uint32_t total_us,
                           uint32_t draw_count, uint32_t draw_delta,
                           uint32_t present_result, uint32_t flags)
{
    LONG write, read;
    DahTraceEvent *event;
    uint32_t world;
    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->type = DAH_EVENT_FRAME;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.frame.host_frame = host_frame;
    event->payload.frame.loop = loop;
    event->payload.frame.interval_us = interval_us;
    event->payload.frame.target_us = target_us;
    event->payload.frame.logic_us = logic_us;
    event->payload.frame.render_us = render_us;
    event->payload.frame.present_us = present_us;
    event->payload.frame.total_us = total_us;
    event->payload.frame.draw_count = draw_count;
    event->payload.frame.draw_delta = draw_delta;
    event->payload.frame.present_result = present_result;
    event->payload.frame.flags = flags;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_player_render_sample(void)
{
    static uint32_t previous_crypto, previous_render, previous_gate140;
    static uint32_t previous_health_bits, previous_damage_gate;
    static uint32_t previous_global_damage_disable;
    static uint32_t previous_scene, previous_scene_flags, previous_world;
    static int sampled;
    LONG write, read;
    DahTraceEvent *event;
    uint32_t world, world_tick, control, player, crypto, render, gate140;
    uint32_t health_bits, maximum_health_bits, damage_gate;
    uint32_t global_damage_disable;
    uint32_t scene, scene_flags, changes = 0u;

    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    world = guest_u32(0x00286768u);
    world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    control = guest_u32(0x0025FCECu);
    player = guest_range(control, 0x3Cu) ? guest_u32(control + 0x38u) : 0u;
    crypto = guest_range(player, 0x3Cu) ? guest_u32(player + 0x38u) : 0u;
    if (!guest_range(crypto, 0x148u) || guest_u32(crypto) != 0x0022C9F8u)
        crypto = 0u;
    render = crypto ? guest_u32(crypto + 0x144u) : 0u;
    gate140 = crypto ? *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() +
                                           crypto + 0x140u) : 0u;
    health_bits = crypto ? guest_u32(crypto + 0x370u) : 0u;
    maximum_health_bits = crypto ? guest_u32(crypto + 0x374u) : 0u;
    damage_gate = crypto ? guest_u32(crypto + 0x378u) : 0u;
    global_damage_disable = *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() +
                                               0x002867ACu);
    scene = crypto ? guest_u32(crypto + 0x28u) : 0u;
    scene_flags = guest_range(scene, 0x50u) ? guest_u32(scene + 0x4Cu) : 0u;

    if (!sampled) changes |= 1u;
    if (crypto != previous_crypto) changes |= 2u;
    if (render != previous_render) changes |= 4u;
    if (gate140 != previous_gate140) changes |= 8u;
    if (scene != previous_scene) changes |= 16u;
    if (scene_flags != previous_scene_flags) changes |= 32u;
    if (sampled && world_tick < previous_world) changes |= 64u;
    if (health_bits != previous_health_bits) changes |= 128u;
    if (damage_gate != previous_damage_gate) changes |= 256u;
    if (global_damage_disable != previous_global_damage_disable) changes |= 512u;
    if (!changes) {
        previous_world = world_tick;
        return;
    }

    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->world_tick = world_tick;
    event->type = DAH_EVENT_PLAYER_RENDER;
    event->payload.player_render.control = control;
    event->payload.player_render.player = player;
    event->payload.player_render.crypto = crypto;
    event->payload.player_render.render = render;
    event->payload.player_render.gate140 = gate140;
    event->payload.player_render.health_bits = health_bits;
    event->payload.player_render.maximum_health_bits = maximum_health_bits;
    event->payload.player_render.damage_gate = damage_gate;
    event->payload.player_render.global_damage_disable = global_damage_disable;
    event->payload.player_render.scene = scene;
    event->payload.player_render.scene_flags = scene_flags;
    event->payload.player_render.previous_crypto = previous_crypto;
    event->payload.player_render.previous_render = previous_render;
    event->payload.player_render.previous_gate140 = previous_gate140;
    event->payload.player_render.previous_health_bits = previous_health_bits;
    event->payload.player_render.previous_damage_gate = previous_damage_gate;
    event->payload.player_render.previous_global_damage_disable =
        previous_global_damage_disable;
    event->payload.player_render.previous_scene = previous_scene;
    event->payload.player_render.previous_scene_flags = previous_scene_flags;
    event->payload.player_render.changes = changes;
    previous_crypto = crypto;
    previous_render = render;
    previous_gate140 = gate140;
    previous_health_bits = health_bits;
    previous_damage_gate = damage_gate;
    previous_global_damage_disable = global_damage_disable;
    previous_scene = scene;
    previous_scene_flags = scene_flags;
    previous_world = world_tick;
    sampled = 1;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

static int guest_inline_name_is(uint32_t object, const char *name)
{
    size_t index, length = strlen(name);
    ptrdiff_t offset = xbox_GetMemoryOffset();
    if (!guest_range(object + 0x0Cu, (uint32_t)length + 1u)) return 0;
    for (index = 0; index < length; ++index)
        if (*(const char *)((uintptr_t)offset + object + 0x0Cu + index) != name[index])
            return 0;
    return *(const unsigned char *)((uintptr_t)offset + object + 0x0Cu + length) == 0u;
}

void dah_event_trace_ui_state_sample(void)
{
    static uint32_t cached_root;
    static uint32_t reported_root;
    static uint32_t mission_defeat, mission_complete, titlecard;
    static uint32_t start_menu_background, messages, cinematic, main_ui, fade;
    static uint32_t previous_active_mask;
    static int sampled;
    uint32_t owner, root, sentinel, node, active_mask = 0u;
    uint32_t world, world_tick;
    unsigned count = 0u;
    LONG write, read;
    DahTraceEvent *event;

    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    owner = guest_u32(0x00258470u);
    root = guest_range(owner, 4u) ? guest_u32(owner) : 0u;
    if (!guest_range(root, 0x48u)) root = 0u;
    if (root != cached_root) {
        cached_root = root;
        mission_defeat = mission_complete = titlecard = 0u;
        start_menu_background = messages = cinematic = main_ui = fade = 0u;
        if (root) {
            sentinel = root + 0x44u;
            node = guest_u32(sentinel);
            while (node && node != sentinel && count++ < 64u) {
                uint32_t object = guest_range(node, 12u) ? guest_u32(node + 8u) : 0u;
                if (guest_range(object, 0x0Du)) {
                    if (guest_inline_name_is(object, "missiondefeat")) mission_defeat = object;
                    else if (guest_inline_name_is(object, "missioncomplete")) mission_complete = object;
                    else if (guest_inline_name_is(object, "titlecard")) titlecard = object;
                    else if (guest_inline_name_is(object, "startMenuBackground")) start_menu_background = object;
                    else if (guest_inline_name_is(object, "messages")) messages = object;
                    else if (guest_inline_name_is(object, "cinematic")) cinematic = object;
                    else if (guest_inline_name_is(object, "main")) main_ui = object;
                    else if (guest_inline_name_is(object, "fade")) fade = object;
                }
                node = guest_range(node, 4u) ? guest_u32(node) : 0u;
            }
        }
    }
    if (guest_range(mission_defeat, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + mission_defeat + 4u)) active_mask |= 1u;
    if (guest_range(mission_complete, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + mission_complete + 4u)) active_mask |= 2u;
    if (guest_range(titlecard, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + titlecard + 4u)) active_mask |= 4u;
    if (guest_range(start_menu_background, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + start_menu_background + 4u)) active_mask |= 8u;
    if (guest_range(messages, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + messages + 4u)) active_mask |= 16u;
    if (guest_range(cinematic, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + cinematic + 4u)) active_mask |= 32u;
    if (guest_range(main_ui, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + main_ui + 4u)) active_mask |= 64u;
    if (guest_range(fade, 5u) &&
        *(const uint8_t *)((uintptr_t)xbox_GetMemoryOffset() + fade + 4u)) active_mask |= 128u;
    if (sampled && root == reported_root && active_mask == previous_active_mask) return;

    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    world = guest_u32(0x00286768u);
    world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->world_tick = world_tick;
    event->type = DAH_EVENT_UI_STATE;
    event->payload.ui_state.root = root;
    event->payload.ui_state.active_mask = active_mask;
    event->payload.ui_state.previous_active_mask = previous_active_mask;
    event->payload.ui_state.mission_defeat = mission_defeat;
    event->payload.ui_state.mission_complete = mission_complete;
    event->payload.ui_state.titlecard = titlecard;
    event->payload.ui_state.start_menu_background = start_menu_background;
    event->payload.ui_state.messages = messages;
    event->payload.ui_state.cinematic = cinematic;
    event->payload.ui_state.main = main_ui;
    event->payload.ui_state.fade = fade;
    reported_root = root;
    previous_active_mask = active_mask;
    sampled = 1;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_ability_flag(uint32_t command, uint32_t owner,
                                  uint32_t offset, uint32_t old_value,
                                  uint32_t new_value, uint32_t caller)
{
    LONG write, read;
    DahTraceEvent *event;
    uint32_t world;
    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->type = DAH_EVENT_ABILITY_FLAG;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.ability.command = command;
    event->payload.ability.owner = owner;
    event->payload.ability.offset = offset;
    event->payload.ability.old_value = old_value;
    event->payload.ability.new_value = new_value;
    event->payload.ability.caller = caller;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_tag_ability(uint32_t ability_hash, uint32_t actor,
                                 uint32_t offset, uint32_t old_value,
                                 uint32_t new_value, uint32_t caller)
{
    LONG write, read;
    DahTraceEvent *event;
    uint32_t world;
    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->type = DAH_EVENT_TAG_ABILITY;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.tag_ability.ability_hash = ability_hash;
    event->payload.tag_ability.actor = actor;
    event->payload.tag_ability.offset = offset;
    event->payload.tag_ability.old_value = old_value;
    event->payload.tag_ability.new_value = new_value;
    event->payload.tag_ability.caller = caller;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_physics_body_command(uint32_t tag_hash,
                                          uint32_t filter_hash,
                                          uint32_t actor,
                                          uint32_t forceable,
                                          uint32_t requested_enable,
                                          uint32_t caller)
{
    LONG write, read;
    DahTraceEvent *event;
    uint32_t world;
    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->type = DAH_EVENT_PHYSICS_BODY_COMMAND;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.physics_body_command.tag_hash = tag_hash;
    event->payload.physics_body_command.filter_hash = filter_hash;
    event->payload.physics_body_command.actor = actor;
    event->payload.physics_body_command.forceable = forceable;
    event->payload.physics_body_command.requested_enable = requested_enable;
    event->payload.physics_body_command.caller = caller;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_scene_flash(uint32_t frame, uint32_t object,
                                 uint32_t model, uint32_t object_flags,
                                 uint32_t model_type, uint32_t model_flags,
                                 uint32_t visible, uint32_t previous_visible,
                                 uint32_t transition_gap,
                                 float x, float y, float z)
{
    LONG write, read;
    DahTraceEvent *event;
    uint32_t world;
    if (!InterlockedCompareExchange(&enabled, 0, 0)) return;
    write = InterlockedCompareExchange(&write_index, 0, 0);
    read = InterlockedCompareExchange(&read_index, 0, 0);
    if ((uint32_t)(write - read) >= DAH_EVENT_CAPACITY) {
        InterlockedIncrement(&dropped_events);
        return;
    }
    event = &events[(uint32_t)write & (DAH_EVENT_CAPACITY - 1u)];
    memset(event, 0, sizeof(*event));
    event->sequence = (uint32_t)write;
    event->type = DAH_EVENT_SCENE_FLASH;
    world = guest_u32(0x00286768u);
    event->world_tick = guest_range(world, 12u) ? guest_u32(world + 8u) : 0u;
    event->payload.scene_flash.frame = frame;
    event->payload.scene_flash.object = object;
    event->payload.scene_flash.model = model;
    event->payload.scene_flash.object_flags = object_flags;
    event->payload.scene_flash.model_type = model_type;
    event->payload.scene_flash.model_flags = model_flags;
    event->payload.scene_flash.visible = visible;
    event->payload.scene_flash.previous_visible = previous_visible;
    event->payload.scene_flash.transition_gap = transition_gap;
    event->payload.scene_flash.x = x;
    event->payload.scene_flash.y = y;
    event->payload.scene_flash.z = z;
    MemoryBarrier();
    InterlockedExchange(&write_index, write + 1);
}

void dah_event_trace_shutdown(void)
{
    LONG dropped;
    if (!InterlockedExchange(&enabled, 0)) return;
    InterlockedExchange(&running, 0);
    SetEvent(wake_event);
    WaitForSingleObject(writer_thread, 5000u);
    dropped = InterlockedCompareExchange(&dropped_events, 0, 0);
    if (dropped)
        fprintf(output, "{\"event\":\"trace-overflow\",\"dropped\":%ld}\n",
                (long)dropped);
    fflush(output);
    fclose(output);
    output = NULL;
    CloseHandle(writer_thread);
    writer_thread = NULL;
    CloseHandle(wake_event);
    wake_event = NULL;
}
