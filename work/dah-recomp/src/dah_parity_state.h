#ifndef DAH_PARITY_STATE_H
#define DAH_PARITY_STATE_H

/* Read-only retail state at 000DAD3C (end of main loop). Heap addresses are
 * evidence, not comparable identities. Use vtables/names and field values.
 * DAH_PARITY_STATE_TRACE names a new JSONL file; unset has no per-frame I/O.
 * Debug tracing/readback runs must not be used as capture-free timing proof. */
static uint32_t dah_parity_word(uint32_t address)
{
    uint32_t value = 0;
    if (address >= 0x10000u && address <= 0x08000000u - 4u)
        memcpy(&value, (const void *)((uintptr_t)g_xbox_mem_offset + address), 4u);
    return value;
}

static void dah_parity_text(FILE *output, uint32_t address, unsigned limit)
{
    unsigned i;
    fputc('"', output);
    if (address >= 0x10000u && address <= 0x08000000u - limit) {
        const unsigned char *text = (const unsigned char *)((uintptr_t)g_xbox_mem_offset + address);
        for (i = 0; i < limit && text[i]; ++i) {
            unsigned char c = text[i];
            if (c == '"' || c == '\\') fputc('\\', output);
            if (c >= 32u && c < 127u) fputc(c, output);
            else fprintf(output, "\\u%04x", c);
        }
    }
    fputc('"', output);
}

/* Comparable selector identities, never heap pointers. Only the verified menu
 * hierarchies are traversed, and an inactive ancestor suppresses its highlights.
 * All limits describe this diagnostic, not retail UI limits. */
struct dah_parity_selectors {
    char paths[32][256];
    uint32_t objects[512];
    unsigned count, object_count, node_count;
    int complete;
};

static int dah_parity_range(uint32_t address, unsigned size)
{
    return address >= 0x10000u && size <= 0x08000000u &&
        address <= 0x08000000u - size && !(address & 3u);
}

/* gui_site_input_options_controller.lua derives its labels from progress
 * FindKey, not the gameplay player (which is absent in the shell). Retail
 * 00089840 returns [00249AE4]; 0008AD10/0008A540 search its sorted eight-byte
 * key records. Only byte +4 is the active flag; the remaining bytes are
 * padding and can contain stale pointer bits. Keep presence and activity
 * separate rather than interpreting an unavailable table as default options. */
static void dah_parity_write_controller_options(FILE *output)
{
    static const uint32_t hashes[3] = {0x26FBC240u, 0xA37AAC8Du, 0xE54032BEu};
    static const char *names[3] = {"invertPitch", "invertYaw", "noVibration"};
    unsigned present[3] = {0}, active[3] = {0};
    uint32_t store = dah_parity_word(0x249AE4u), count = 0, capacity = 0, array = 0;
    uint32_t previous = 0;
    unsigned i, j;
    int complete = dah_parity_range(store, 0x3A5Cu);
    if (complete) {
        count = dah_parity_word(store + 0x3A50u);
        capacity = dah_parity_word(store + 0x3A54u);
        array = dah_parity_word(store + 0x3A58u);
        complete = capacity > 0u && capacity <= 1024u && count <= capacity &&
            dah_parity_range(array, count ? count * 8u : 4u);
    }
    for (i = 0; complete && i < count; ++i) {
        uint32_t hash = dah_parity_word(array + i * 8u);
        unsigned flag = dah_parity_word(array + i * 8u + 4u) & 255u;
        if ((i && hash <= previous) || flag > 1u) { complete = 0; break; }
        previous = hash;
        for (j = 0; j < 3u; ++j) {
            if (hash == hashes[j]) { present[j] = 1u; active[j] = flag; }
        }
    }
    fputs(",\"controllerOptions\":{", output);
    for (j = 0; j < 3u; ++j)
        fprintf(output, "%s\"%s\":{\"present\":%s,\"active\":%s}",
            j ? "," : "", names[j],
            complete ? (present[j] ? "true" : "false") : "null",
            complete ? (active[j] ? "true" : "false") : "null");
    fprintf(output, "},\"controllerOptionsComplete\":%s", complete ? "true" : "false");
}

static int dah_parity_menu_name(const char *name)
{
    return !strcmp(name, "tthubMain") || !strcmp(name, "options") ||
        !strcmp(name, "optionsController") || !strcmp(name, "optionsAudio") ||
        !strcmp(name, "optionsDisplay") || !strcmp(name, "labUpgrade");
}

static int dah_parity_selector_match(const char *path)
{
    static const struct { const char *prefix, *suffix; char maximum; } patterns[] = {
        { "tthubMain/slot", "/underline", '4' },
        { "options/slot", "bkgnd", '4' },
        { "optionsController/slots/slot", "/bkgnd", '8' },
        { "optionsAudio/slots/slot", "/bkgnd", '8' },
        { "optionsDisplay/slots/slot", "/bkgnd", '8' },
        { "labUpgrade/slots/slot", "/selected", '3' }
    };
    unsigned i;
    for (i = 0; i < sizeof(patterns) / sizeof(patterns[0]); ++i) {
        size_t length = strlen(patterns[i].prefix);
        if (!strncmp(path, patterns[i].prefix, length) &&
            path[length] >= '1' && path[length] <= patterns[i].maximum &&
            !strcmp(path + length + 1u, patterns[i].suffix)) return 1;
    }
    return 0;
}

static void dah_parity_walk_selectors(struct dah_parity_selectors *result,
    uint32_t object, uint32_t parent, const char *parent_path, unsigned depth)
{
    uint32_t sentinel, node, list_nodes[64];
    char name[41], path[256];
    unsigned i, length = 0, list_count = 0;
    if (!dah_parity_range(object, 0x60u) ||
        (parent && dah_parity_word(object + 8u) != parent)) {
        result->complete = 0; return;
    }
    for (i = 0; i < result->object_count; ++i) {
        if (result->objects[i] == object) { result->complete = 0; return; }
    }
    if (result->object_count == 512u) { result->complete = 0; return; }
    result->objects[result->object_count++] = object;
    if (!(dah_parity_word(object + 4u) & 255u)) return;
    path[0] = 0;
    if (depth) {
        const unsigned char *source = (const unsigned char *)
            ((uintptr_t)g_xbox_mem_offset + object + 0xCu);
        while (length < 40u && source[length]) {
            unsigned char c = source[length];
            if (c < 32u || c >= 127u || c == '/' || c == '\\' || c == '"') {
                result->complete = 0; return;
            }
            name[length++] = (char)c;
        }
        if (!length || length == 40u) { result->complete = 0; return; }
        name[length] = 0;
        if (depth == 1u && !dah_parity_menu_name(name)) return;
        if (strlen(parent_path) + length + 2u > sizeof(path)) {
            result->complete = 0; return;
        }
        snprintf(path, sizeof(path), "%s%s%s", parent_path,
            *parent_path ? "/" : "", name);
        if (dah_parity_selector_match(path)) {
            if (result->count == 32u) { result->complete = 0; return; }
            strcpy(result->paths[result->count++], path);
            return;
        }
    }
    if (depth == 4u) return; /* Deepest verified selector is menu/slots/slotN/leaf. */
    sentinel = object + 0x44u;
    node = dah_parity_word(sentinel);
    while (node && node != sentinel) {
        uint32_t child;
        if (!dah_parity_range(node, 12u) || list_count == 64u ||
            result->node_count == 512u) { result->complete = 0; return; }
        for (i = 0; i < list_count; ++i) {
            if (list_nodes[i] == node) { result->complete = 0; return; }
        }
        list_nodes[list_count++] = node;
        ++result->node_count;
        child = dah_parity_word(node + 8u);
        if (child) dah_parity_walk_selectors(result, child, object, path, depth + 1u);
        else result->complete = 0;
        node = dah_parity_word(node);
    }
    if (!node) result->complete = 0; /* Retail lists terminate at their sentinel. */
}

static void dah_parity_write_selectors(FILE *output, uint32_t root)
{
    struct dah_parity_selectors result = {0};
    unsigned i, j;
    result.complete = 1;
    if (root) dah_parity_walk_selectors(&result, root, 0u, "", 0u);
    /* List ordering changes when Lua calls SortFront/SortBack. */
    for (i = 1u; i < result.count; ++i) {
        char path[256];
        strcpy(path, result.paths[i]);
        for (j = i; j && strcmp(result.paths[j - 1u], path) > 0; --j)
            strcpy(result.paths[j], result.paths[j - 1u]);
        strcpy(result.paths[j], path);
    }
    fputs(",\"selectors\":[", output);
    for (i = 0; i < result.count; ++i)
        fprintf(output, "%s\"%s\"", i ? "," : "", result.paths[i]);
    fprintf(output, "],\"selectorsComplete\":%s", result.complete ? "true" : "false");
}

/* Farm diagnostics: original world update/getters 00105280/00115388/00115208,
 * RNG 000D4270, player getters 00082550/00082560, move state 000817C0.
 * These reads never align, seed, pause or otherwise write gameplay state. */
static int dah_parity_farm_range(uint32_t address, unsigned size)
{
    MEMORY_BASIC_INFORMATION memory;
    uintptr_t native = (uintptr_t)g_xbox_mem_offset + address;
    if (!size || (address & 3u) ||
        !((address >= 0x10000u && address < 0x08000000u && size <= 0x08000000u-address) ||
          (address >= 0x80000000u && address < 0x88000000u && size <= 0x88000000u-address))) return 0;
    if (!VirtualQuery((const void *)native, &memory, sizeof(memory)) ||
        memory.State != MEM_COMMIT || (memory.Protect & (PAGE_NOACCESS|PAGE_GUARD))) return 0;
    return native >= (uintptr_t)memory.BaseAddress &&
        size <= memory.RegionSize - (native-(uintptr_t)memory.BaseAddress);
}
static uint32_t dah_parity_farm_word(uint32_t address)
{
    uint32_t value;
    memcpy(&value,(const void *)((uintptr_t)g_xbox_mem_offset+address),4);
    return value; /* Caller validates the entire object before reading fields. */
}
static void dah_parity_farm_scalar(FILE *output,const char *name,int valid,uint32_t value)
{
    fprintf(output,",\"%s\":",name);
    if(valid)fprintf(output,"%u",value);else fputs("null",output);
}
static void dah_parity_farm_words(FILE *output,const char *name,int valid,uint32_t address,unsigned count)
{
    fprintf(output,",\"%s\":",name);
    if(!valid){fputs("null",output);return;}
    fputc('[',output);
    for(unsigned i=0;i<count;++i)fprintf(output,"%s%u",i?",":"",dah_parity_farm_word(address+i*4u));
    fputc(']',output);
}
#include "dah_cinematic_state.h"
static uint32_t dah_parity_find_hud(const char *const *path,unsigned path_count,int *active,int *complete)
{
    uint32_t root_link=dah_parity_word(0x258470u),object=0;
    unsigned total=0;
    *active=1;*complete=1;
    if(!root_link)return 0;
    if(!dah_parity_farm_range(root_link,4u)){*complete=0;return 0;}
    object=dah_parity_farm_word(root_link);
    if(!object)return 0;
    for(unsigned depth=0;depth<path_count;++depth){
        uint32_t found=0,seen[64],sentinel,node;unsigned count=0;
        if(!dah_parity_farm_range(object,0x60u)){*complete=0;return 0;}
        *active&=(dah_parity_farm_word(object+4u)&255u)!=0;
        sentinel=object+0x44u;node=dah_parity_farm_word(sentinel);
        while(node&&node!=sentinel){
            if(count==64u||total==256u||!dah_parity_farm_range(node,12u)){*complete=0;return 0;}
            for(unsigned i=0;i<count;++i)if(seen[i]==node){*complete=0;return 0;}
            seen[count++]=node;++total;
            uint32_t child=dah_parity_farm_word(node+8u);
            if(!dah_parity_farm_range(child,0x34u)||dah_parity_farm_word(child+8u)!=object){*complete=0;return 0;}
            const char *name=(const char *)((uintptr_t)g_xbox_mem_offset+child+12u);
            if(memchr(name,0,40u)&&!strcmp(name,path[depth])){
                if(found){*complete=0;return 0;}found=child;
            }
            node=dah_parity_farm_word(node);
        }
        if(!node){*complete=0;return 0;}
        if(!found)return 0;
        object=found;
    }
    return object;
}
static void dah_parity_write_hud(FILE *output,uint32_t actor,int actor_valid)
{
    static const char *const shield_path[]={"main","alien","healthandconcentration","change","bar"};
    static const char *const enemy_path[]={"main","enemyhealth","bar"};
    int active=0,traversal=0;
    uint32_t shield=dah_parity_find_hud(shield_path,5u,&active,&traversal);
    int valid=shield&&dah_parity_farm_range(shield,0x538u)&&dah_parity_farm_word(shield)==0x0022A8D8u;
    unsigned positive=0;int segments_valid=valid;
    float threshold;uint32_t threshold_bits=dah_parity_word(0x226E38u);
    memcpy(&threshold,&threshold_bits,4);
    if(valid){
        active&=(dah_parity_farm_word(shield+4u)&255u)!=0;
        for(unsigned i=0;i<60u;++i){
            uint32_t bits=dah_parity_farm_word(shield+0x40Cu+i*4u);float value;memcpy(&value,&bits,4);
            if(!isfinite(value)){segments_valid=0;break;}
            if(value>threshold)++positive;
        }
    }
    dah_parity_farm_scalar(output,"hudShield",traversal,shield);
    fprintf(output,",\"hudShieldActive\":%s,\"hudShieldVisible\":%s",
        valid?(active?"true":"false"):"null",valid?((dah_parity_farm_word(shield+0x534u)&255u)?"true":"false"):"null");
    dah_parity_farm_words(output,"hudShieldFillBits",valid,shield+0x3F0u,2);
    dah_parity_farm_scalar(output,"hudShieldPositiveSegments",segments_valid,positive);
    fprintf(output,",\"hudShieldTraversalComplete\":%s,\"hudShieldComplete\":%s",traversal?"true":"false",valid&&segments_valid?"true":"false");
    int health_valid=actor_valid&&dah_parity_farm_range(actor,0x374u);
    dah_parity_farm_scalar(output,"hudActorCurrentBits",health_valid,health_valid?dah_parity_farm_word(actor+0x370u):0);
    /* 00060101 divides actor +370 by +368 to obtain the shield tick count. */
    dah_parity_farm_scalar(output,"hudActorDivisorBits",health_valid,health_valid?dah_parity_farm_word(actor+0x368u):0);
    fprintf(output,",\"hudActorHealthComplete\":%s",health_valid?"true":"false");
    /* Generic fill-bar callback FC120/FC370: direction +14C, interpolated
     * and requested fill +150/+154. Retail paused RAM confirms class23511C
     * at main/enemyhealth/bar; +B0 is its rectangle. The four raw words at
     * +D0..+DC are RGB endpoint 1 plus endpoint 2 red, not an RGBA tuple. */
    uint32_t enemy=dah_parity_find_hud(enemy_path,3u,&active,&traversal);
    int enemy_header=enemy&&dah_parity_farm_range(enemy,0x158u);
    uint32_t enemy_vt=enemy_header?dah_parity_farm_word(enemy):0;
    int enemy_ok=enemy_header&&enemy_vt==0x0023511Cu;
    int own=enemy_ok&&(dah_parity_farm_word(enemy+4u)&255u)!=0;
    dah_parity_farm_scalar(output,"hudEnemyBar",traversal&&enemy!=0,enemy);
    dah_parity_farm_scalar(output,"hudEnemyBarVtable",enemy_header,enemy_vt);
    fprintf(output,",\"hudEnemyBarOwnActive\":%s,\"hudEnemyBarAncestorsActive\":%s,\"hudEnemyBarActive\":%s",
        enemy_ok?(own?"true":"false"):"null",enemy_ok?(active?"true":"false"):"null",
        enemy_ok?(own&&active?"true":"false"):"null");
    dah_parity_farm_words(output,"hudEnemyBarRectBits",enemy_ok,enemy+0xB0u,4);
    dah_parity_farm_words(output,"hudEnemyBarColorBits",enemy_ok,enemy+0xD0u,4);
    dah_parity_farm_words(output,"hudEnemyBarFillBits",enemy_ok,enemy+0x150u,2);
    dah_parity_farm_scalar(output,"hudEnemyBarDirection",enemy_ok,enemy_ok?dah_parity_farm_word(enemy+0x14Cu):0);
    fprintf(output,",\"hudEnemyBarTraversalComplete\":%s,\"hudEnemyBarComplete\":%s",
        traversal?"true":"false",enemy_ok?"true":"false");
}
/* Rotation setter 00081B70 receives actor+18, stores quaternion into
 * [actor+28]+38..44 and dirties +4C. The scene transform used by the retail
 * actor and movement compatibility code is [actor+4A0], class 00234308.
 * Body 002376E8 inherits vtable+90=0012BB30, which writes velocity +84..8C.
 * Its +0C inner body has class 00237968; vtable+2C=00129100 copies the
 * physics quaternion into inner+38..44 before propagating its transform. */
static void dah_parity_write_actor_motion(FILE *output,uint32_t actor,int actor_ok)
{
    uint32_t object=actor_ok?dah_parity_farm_word(actor+0x28u):0;
    int object_ok=actor_ok&&dah_parity_farm_range(object,0x50u);
    dah_parity_farm_scalar(output,"actorObject",actor_ok,object);
    dah_parity_farm_words(output,"actorObjectPositionBits",object_ok,object+0x2Cu,3);
    dah_parity_farm_words(output,"actorObjectQuatBits",object_ok,object+0x38u,4);
    dah_parity_farm_scalar(output,"actorObjectFlags",object_ok,object_ok?dah_parity_farm_word(object+0x4Cu):0);
    fprintf(output,",\"actorObjectComplete\":%s",object_ok?"true":"false");
    int node_link=actor_ok&&dah_parity_farm_range(actor+0x4A0u,4u);
    uint32_t node=node_link?dah_parity_farm_word(actor+0x4A0u):0;
    int node_header=node_link&&dah_parity_farm_range(node,0x90u);
    uint32_t node_vt=node_header?dah_parity_farm_word(node):0;
    int node_ok=node_header&&node_vt==0x00234308u;
    dah_parity_farm_scalar(output,"actorSceneNode",node_link,node);
    dah_parity_farm_scalar(output,"actorSceneNodeVtable",node_header,node_vt);
    dah_parity_farm_scalar(output,"actorSceneNodeParent",node_ok,node_ok?dah_parity_farm_word(node+8u):0);
    dah_parity_farm_words(output,"actorSceneQuatBits",node_ok,node+0x40u,4);
    dah_parity_farm_words(output,"actorSceneWorldBits",node_ok,node+0x50u,16);
    fprintf(output,",\"actorSceneNodeComplete\":%s",node_ok?"true":"false");
    uint32_t body=actor_ok?dah_parity_farm_word(actor+0x110u):0;
    int body_header=actor_ok&&dah_parity_farm_range(body,0x90u);
    uint32_t body_vt=body_header?dah_parity_farm_word(body):0;
    int setter_ok=body_header&&body_vt==0x002376E8u&&dah_parity_farm_range(body_vt+0x90u,4u);
    uint32_t setter=setter_ok?dah_parity_farm_word(body_vt+0x90u):0;
    int body_ok=setter_ok&&setter==0x0012BB30u;
    dah_parity_farm_scalar(output,"physicsBody",actor_ok,body);
    dah_parity_farm_scalar(output,"physicsBodyVtable",body_header,body_vt);
    dah_parity_farm_scalar(output,"physicsVelocitySetter",setter_ok,setter);
    dah_parity_farm_words(output,"physicsVelocityBits",body_ok,body+0x84u,3);
    fprintf(output,",\"physicsBodyComplete\":%s",body_ok?"true":"false");
    uint32_t inner=body_header?dah_parity_farm_word(body+0x0Cu):0;
    int inner_header=body_header&&body_vt==0x002376E8u&&dah_parity_farm_range(inner,0x48u);
    uint32_t inner_vt=inner_header?dah_parity_farm_word(inner):0;
    int inner_ok=inner_header&&inner_vt==0x00237968u;
    dah_parity_farm_scalar(output,"physicsInner",body_header,inner);
    dah_parity_farm_scalar(output,"physicsInnerVtable",inner_header,inner_vt);
    dah_parity_farm_words(output,"physicsInnerQuatBits",inner_ok,inner+0x38u,4);
    fprintf(output,",\"physicsInnerComplete\":%s",inner_ok?"true":"false");
}
static void dah_parity_write_farm(FILE *output,uint32_t world,uint32_t renderer)
{
    int world_header=dah_parity_farm_range(world,0x14u);
    uint32_t world_vt=world_header?dah_parity_farm_word(world):0;
    int world_ok=world_header&&world_vt==0x00235780u&&dah_parity_farm_range(world+0x303Cu,4u);
    uint32_t pending=dah_parity_word(0x25FBFCu);
    int pending_ok=dah_parity_farm_range(pending,0x14u),name_ok=0;
    if(pending_ok&&dah_parity_farm_range(pending+0x50Cu,128u)){
        const unsigned char *s=(const unsigned char *)((uintptr_t)g_xbox_mem_offset+pending+0x50Cu);
        for(unsigned i=0;i<128u;++i){if(!s[i]){name_ok=1;break;}if(s[i]<32u||s[i]>126u)break;}
    }
    dah_parity_farm_scalar(output,"pendingBackendState",pending_ok,pending_ok?dah_parity_farm_word(pending+0x10u):0);
    fputs(",\"pendingBackendName\":",output);
    if(name_ok){
        const char *s=(const char *)((uintptr_t)g_xbox_mem_offset+pending+0x50Cu);
        fputc('"',output);for(;*s;++s){if(*s=='"'||*s=='\\')fputc('\\',output);fputc(*s,output);}fputc('"',output);
    }else fputs("null",output);
    fprintf(output,",\"pendingBackendComplete\":%s",pending_ok&&name_ok?"true":"false");
    dah_parity_farm_scalar(output,"worldVtable",world_header,world_vt);
    dah_parity_farm_scalar(output,"worldTick",world_ok,world_ok?dah_parity_farm_word(world+8u):0);
    dah_parity_farm_scalar(output,"worldElapsedBits",world_ok,world_ok?dah_parity_farm_word(world+12u):0);
    dah_parity_farm_scalar(output,"worldStepBits",world_ok,world_ok?dah_parity_farm_word(world+16u):0);
    dah_parity_farm_scalar(output,"worldPaused",world_ok,world_ok?*(const uint8_t *)((uintptr_t)g_xbox_mem_offset+world+0x303Cu):0);
    dah_parity_farm_scalar(output,"worldRealtime",world_ok,world_ok?*(const uint8_t *)((uintptr_t)g_xbox_mem_offset+world+0x303Du):0);
    fprintf(output,",\"worldComplete\":%s",world_ok?"true":"false");
    dah_parity_farm_scalar(output,"rngState",1,dah_parity_word(0x278A58u));
    dah_parity_farm_scalar(output,"cameraUpdate",1,dah_parity_word(0x258B48u)&255u);
    fputs(",\"rngStateComplete\":true,\"cameraUpdateComplete\":true",output);
    uint32_t control=dah_parity_word(0x25FCECu);
    int control_ok=dah_parity_farm_range(control,0x3Cu);
    uint32_t player=control_ok?dah_parity_farm_word(control+0x38u):0;
    int player_ok=control_ok&&dah_parity_farm_range(player,0x3Cu);
    uint32_t ship=player_ok?dah_parity_farm_word(player+0x34u):0;
    int ship_ok=player_ok&&dah_parity_farm_range(ship,0x280u);
    uint32_t actor=player_ok?dah_parity_farm_word(player+0x38u):0;
    int actor_header=player_ok&&dah_parity_farm_range(actor,0x158u);
    uint32_t actor_vt=actor_header?dah_parity_farm_word(actor):0;
    int actor_ok=actor_header&&actor_vt==0x0022C9F8u;
    uint32_t ship_weapon_manager=ship_ok?dah_parity_farm_word(ship+0x138u):0;
    int ship_weapon_manager_ok=ship_ok&&dah_parity_farm_range(ship_weapon_manager,0x100u);
    uint32_t ship_active_weapon=ship_weapon_manager_ok?
        dah_parity_farm_word(ship_weapon_manager+0x58u):0;
    int ship_active_weapon_ok=ship_weapon_manager_ok&&
        dah_parity_farm_range(ship_active_weapon,4u);
    uint32_t movement=actor_ok?dah_parity_farm_word(actor+0x130u):0;
    int movement_ok=actor_ok&&dah_parity_farm_range(movement,0x4Cu);
    int movement_steering_ok=movement_ok&&dah_parity_farm_range(movement+0x2ACu,8u);
    uint32_t weapon_manager=actor_ok?dah_parity_farm_word(actor+0x138u):0;
    int weapon_manager_ok=actor_ok&&dah_parity_farm_range(weapon_manager,0x5Cu);
    uint32_t active_weapon=weapon_manager_ok?dah_parity_farm_word(weapon_manager+0x58u):0;
    int active_weapon_ok=weapon_manager_ok&&dah_parity_farm_range(active_weapon,4u);
    uint32_t weapon_slot_vtables[4]={0,0,0,0};
    uint32_t holobob_main=0;
    int weapon_slot_vtables_ok=weapon_manager_ok;
    unsigned weapon_slot_index;
    if (weapon_manager_ok) {
        for (weapon_slot_index=0;weapon_slot_index<4u;++weapon_slot_index) {
            uint32_t slot=dah_parity_farm_word(weapon_manager+0x4Cu+weapon_slot_index*4u);
            if (slot&&dah_parity_farm_range(slot,4u)) {
                weapon_slot_vtables[weapon_slot_index]=dah_parity_farm_word(slot);
                if (weapon_slot_vtables[weapon_slot_index]==0x0022FD50u) holobob_main=slot;
            }
            else if (slot) weapon_slot_vtables_ok=0;
        }
    }
    dah_parity_farm_scalar(output,"controlSystem",1,control);
    dah_parity_farm_scalar(output,"player",control_ok,player);
    dah_parity_farm_scalar(output,"playerVtable",player_ok,player_ok?dah_parity_farm_word(player):0);
    dah_parity_farm_scalar(output,"playerFocus",player_ok,player_ok?dah_parity_farm_word(player+0x30u):0);
    dah_parity_farm_scalar(output,"playerShip",player_ok,ship);
    dah_parity_farm_scalar(output,"playerShipVtable",ship_ok,ship_ok?dah_parity_farm_word(ship):0);
    if (ship_ok&&getenv("DAH_PARITY_WEAPON_DETAIL"))
        dah_parity_farm_words(output,"playerShipWords",1,ship,0xA0u);
    dah_parity_farm_scalar(output,"shipWeaponManager",ship_ok,ship_weapon_manager);
    dah_parity_farm_words(output,"shipWeaponSlots",ship_weapon_manager_ok,
        ship_weapon_manager+0x4Cu,4u);
    dah_parity_farm_scalar(output,"shipActiveWeapon",ship_weapon_manager_ok,
        ship_active_weapon);
    dah_parity_farm_scalar(output,"shipActiveWeaponVtable",ship_active_weapon_ok,
        ship_active_weapon_ok?dah_parity_farm_word(ship_active_weapon):0);
    if (ship_weapon_manager_ok&&getenv("DAH_PARITY_WEAPON_DETAIL"))
        dah_parity_farm_words(output,"shipWeaponManagerWords",1,
            ship_weapon_manager,0x40u);
    if (ship_active_weapon_ok&&getenv("DAH_PARITY_WEAPON_DETAIL"))
        dah_parity_farm_words(output,"shipActiveWeaponWords",
            dah_parity_farm_range(ship_active_weapon,0x1A0u),
            ship_active_weapon,0x68u);
    dah_parity_farm_scalar(output,"playerCrypto",player_ok,actor);
    dah_parity_farm_scalar(output,"actor",player_ok,actor);
    dah_parity_farm_scalar(output,"actorVtable",actor_header,actor_vt);
    dah_parity_farm_words(output,"actorPositionBits",actor_ok,actor+0x14Cu,3);
    dah_parity_farm_scalar(output,"movement",actor_ok,movement);
    dah_parity_farm_scalar(output,"moveState",movement_ok,movement_ok?dah_parity_farm_word(movement+0x48u):0);
    /* 00054200 writes angular velocity +14, normalized heading +18,
     * smoothed heading +2AC and target heading +2B0. Preserve raw bits. */
    dah_parity_farm_scalar(output,"movementAngularVelocityBits",movement_ok,
        movement_ok?dah_parity_farm_word(movement+0x14u):0);
    dah_parity_farm_scalar(output,"movementHeadingBits",movement_ok,
        movement_ok?dah_parity_farm_word(movement+0x18u):0);
    dah_parity_farm_words(output,"movementSteeringBits",movement_steering_ok,movement+0x2ACu,2);
    dah_parity_farm_scalar(output,"weaponManager",actor_ok,weapon_manager);
    dah_parity_farm_words(output,"weaponSlots",weapon_manager_ok,weapon_manager+0x4Cu,4);
    fprintf(output,",\"weaponSlotVtables\":[%u,%u,%u,%u]",
        weapon_slot_vtables[0],weapon_slot_vtables[1],weapon_slot_vtables[2],weapon_slot_vtables[3]);
    dah_parity_farm_scalar(output,"activeWeapon",weapon_manager_ok,active_weapon);
    dah_parity_farm_scalar(output,"activeWeaponVtable",active_weapon_ok,
        active_weapon_ok?dah_parity_farm_word(active_weapon):0);
    if (active_weapon_ok&&getenv("DAH_PARITY_WEAPON_DETAIL"))
        dah_parity_farm_words(output,"activeWeaponWords",dah_parity_farm_range(active_weapon,0x1A0u),active_weapon,0x68u);
    dah_parity_farm_scalar(output,"holobobMain",weapon_manager_ok,holobob_main);
    if (holobob_main&&getenv("DAH_PARITY_WEAPON_DETAIL"))
        dah_parity_farm_words(output,"holobobMainWords",dah_parity_farm_range(holobob_main,0x1A0u),holobob_main,0x68u);
    fprintf(output,",\"weaponManagerComplete\":%s",weapon_manager_ok&&active_weapon_ok&&weapon_slot_vtables_ok?"true":"false");
    fprintf(output,",\"playerComplete\":%s,\"actorComplete\":%s,\"moveStateComplete\":%s,\"movementMotionComplete\":%s",
        player_ok?"true":"false",actor_ok?"true":"false",movement_ok?"true":"false",
        movement_steering_ok?"true":"false");
    dah_parity_write_actor_motion(output,actor,actor_ok);
    int camera_header=dah_parity_farm_range(renderer,0xF0u);
    uint32_t node=camera_header?dah_parity_farm_word(renderer+0xECu):0;
    int camera_ok=camera_header&&dah_parity_farm_range(node,0x90u);
    uint32_t global_camera=dah_parity_word(0x250E60u);
    int global_camera_ok=dah_parity_farm_range(global_camera,0x90u);
    dah_parity_farm_scalar(output,"cameraNode",camera_header,node);
    dah_parity_farm_scalar(output,"cameraNodeParent",camera_ok,camera_ok?dah_parity_farm_word(node+8u):0);
    dah_parity_farm_words(output,"cameraViewPositionBits",camera_header,renderer+0x80u,3);
    dah_parity_farm_words(output,"cameraViewForwardBits",camera_header,renderer+0x70u,3);
    dah_parity_farm_words(output,"cameraLocalBits",camera_ok,node+0x20u,3);
    dah_parity_farm_words(output,"cameraQuatBits",camera_ok,node+0x40u,4);
    dah_parity_farm_words(output,"cameraWorldBits",camera_ok,node+0x50u,16);
    dah_parity_farm_scalar(output,"globalCamera",1,global_camera);
    dah_parity_farm_words(output,"globalCameraProjectionBits",global_camera_ok,global_camera+0x10u,16);
    dah_parity_farm_words(output,"globalCameraViewBits",global_camera_ok,global_camera+0x50u,16);
    fprintf(output,",\"cameraComplete\":%s,\"observer\":{\"source\":\"native-host\",\"presentationHeld\":%s}",
        camera_ok&&global_camera_ok?"true":"false",dah_frame_presentation_held()?"true":"false");
    dah_parity_write_hud(output,actor,actor_ok);
}

static void dah_parity_trace_state(uint64_t host_frame)
{
    static int initialized;
    static FILE *output;
    static unsigned interval = 1;
    static uint64_t start_frame;
    static uint64_t end_frame = UINT64_MAX;
    uint32_t renderer, world, movie, backend, root, node, sentinel, control, player;
    unsigned i, first = 1;
    if (!initialized) {
        const char *path = getenv("DAH_PARITY_STATE_TRACE");
        const char *every = getenv("DAH_PARITY_STATE_INTERVAL");
        const char *start = getenv("DAH_PARITY_STATE_START");
        const char *end = getenv("DAH_PARITY_STATE_END");
        initialized = 1;
        if (!path || !*path) return;
        if (every && atoi(every) > 0) interval = (unsigned)atoi(every);
        if (start && *start) start_frame = (uint64_t)strtoull(start, NULL, 10);
        if (end && *end) end_frame = (uint64_t)strtoull(end, NULL, 10);
        /* Never silently overwrite an earlier capture. */
        output = fopen(path, "wx");
        if (!output) {
            fprintf(stderr, "[DAH-PARITY] cannot create trace %s\n", path);
            return;
        }
        fprintf(stderr, "[DAH-PARITY] state=%s interval=%u range=%llu..%llu phase=000DAD3C\n",
            path, interval, (unsigned long long)start_frame,
            (unsigned long long)end_frame);
    }
    if (!output || host_frame < start_frame || host_frame >= end_frame ||
        (host_frame - 1u) % interval) return;
    renderer = dah_parity_word(0x250E60u);
    world = dah_parity_word(0x286768u);
    movie = dah_parity_word(0x28681Cu);
    backend = dah_parity_word(0x25B1D0u + 0x4A28u);
    root = dah_parity_word(dah_parity_word(0x258470u));
    control = dah_parity_word(0x25FCECu);
    player = control ? dah_parity_word(control + 0x38u) : 0;
    fprintf(output, "{\"schema\":1,\"source\":\"recomp\",\"phase\":\"000DAD3C\",\"hostFrame\":%llu,\"wallMs\":%llu,\"loop\":%u,\"renderer\":%u,\"refresh\":%u,\"divisor\":%u,\"interval\":%u,\"world\":%u,\"movie\":%u,\"movieMode\":%u,\"movieFlags\":%u,\"movieLifecycle\":%u,\"movieHeader\":[",
        (unsigned long long)host_frame, (unsigned long long)GetTickCount64(),
        dah_parity_word(0x25B1DCu), renderer,
        renderer ? (dah_parity_word(renderer + 0x238u) ? 60u : 50u) : 0u,
        renderer ? dah_parity_word(renderer + 0x27Cu) : 0u,
        renderer ? dah_parity_word(renderer + 0x2C8u) : 0u,
        world,
        movie, dah_parity_word(0x2867F8u), dah_parity_word(0x2867F4u) & 255u,
        dah_parity_word(0x286804u));
    for (i = 0; i < 6; ++i) fprintf(output, "%s%u", i ? "," : "", movie ? dah_parity_word(movie + i * 4u) : 0u);
    fprintf(output, "],\"backend\":%u,\"backendState\":%u,\"backendName\":", backend, backend ? dah_parity_word(backend + 0x10u) : 0u);
    dah_parity_text(output, backend ? backend + 0x50Cu : 0u, 128u);
    fprintf(output, ",\"pendingBackend\":%u,\"controlSettings\":[", dah_parity_word(0x25B1D0u + 0x4A2Cu));
    for (i = 0; i < 4; ++i) fprintf(output, "%s%u", i ? "," : "", player ? dah_parity_word(player + 0x50u + 4u * i) : 0u);
    fprintf(output, "],\"uiRoot\":%u,\"ui\":[", root);
    sentinel = root ? root + 0x44u : 0u;
    node = dah_parity_word(sentinel);
    for (i = 0; root && node && node != sentinel && i < 64u; ++i) {
        uint32_t child = dah_parity_word(node + 8u);
        if (child) {
            fprintf(output, "%s{\"address\":%u,\"vtable\":%u,\"active\":%u,\"name\":", first ? "" : ",", child, dah_parity_word(child), dah_parity_word(child + 4u) & 255u);
            dah_parity_text(output, child + 0xCu, 40u);
            fputc('}', output);
            first = 0;
        }
        node = dah_parity_word(node);
    }
    fputc(']', output);
    dah_parity_write_selectors(output, root);
    dah_parity_write_controller_options(output);
    dah_parity_write_farm(output,world,renderer);
    dah_parity_write_cinematic(output);
    fputs("}\n", output);
    /* The bounded diagnostic runner can terminate the game at any time. */
    fflush(output);
}
#endif
