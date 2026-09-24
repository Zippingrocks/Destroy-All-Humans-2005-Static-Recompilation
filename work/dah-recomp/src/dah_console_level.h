#ifndef DAH_CONSOLE_LEVEL_H
#define DAH_CONSOLE_LEVEL_H

/* Runs only on the guest's main-loop frame boundary. The original driver.Load binding
 * (DCF20, Load arm DD2A3) queues DB0F0(0, path, driver.flags & 1).
 * WarmAssetHeap (same binding, DD3B5) calls DC680 on that pending backend.
 * Both copy their string arguments before returning. The retail mission menu
 * sets mission.forcelaunch and prerequisite progress keys before that request.
 * No loader state, scene objects, renderer data, or guest code is fabricated.
 */
extern void sub_000DB0F0(void);
extern void sub_000DC680(void);
extern void sub_000DCF20(void);
extern void sub_000D54A0(void);
extern void sub_0008B230(void);
extern void sub_0008B340(void);

#define DAH_CONSOLE_DRIVER 0x0025B1D0u

struct dah_console_level_route {
    const char *alias, *site, *mission;
    unsigned preceding_missions;
};
static const struct dah_console_level_route dah_console_level_routes[] = {
    {"farm", "farm", "t1", 0},
    {"rockwell", "rockwell", "m2", 1},
    {"santa", "santa", "m1", 4},
    {"area42", "area42", "m1", 11},
    {"union", "union", "m1", 15},
    {"capitol", "capitol", "m1", 16},
    {"cptlboss", "capitol", "m3", 22}
};

/* Original unlockableStoryProgressionTable keys and prerequisite keys. This
 * is the bounded AddKey recipe in common_unlockables.lua UnlockToMission.
 * Boss data lives in cptlboss, while its progression namespace is capitol.
 * The retail story handler passes data=cptlboss into UnlockToMission; its
 * cptlboss.mission.m3 lookup never matches and therefore visits all 22 rows. */
static const char *const dah_console_story_keys[][2] = {
    {"farm.mission.t1", "default"},
    {"rockwell.mission.m2", "farm.mission.t1.completed"},
    {"rockwell.mission.m3", "rockwell.mission.m2.completed"},
    {"santa.mission.b1", "rockwell.mission.m3.completed"},
    {"santa.mission.m1", "santa.mission.b1.completed"},
    {"santa.mission.b3", "santa.mission.m1.completed"},
    {"santa.mission.m2", "santa.mission.b3.completed"},
    {"rockwell.mission.m4", "santa.mission.m2.completed"},
    {"santa.mission.b6", "rockwell.mission.m4.completed"},
    {"santa.mission.m3", "santa.mission.b6.completed"},
    {"santa.mission.b7", "santa.mission.m3.completed"},
    {"area42.mission.m1", "santa.mission.b7.completed"},
    {"area42.mission.b1", "area42.mission.m1.completed"},
    {"area42.mission.m2", "area42.mission.b1.completed"},
    {"santa.mission.b8", "area42.mission.m2.completed"},
    {"union.mission.m1", "santa.mission.b8.completed"},
    {"capitol.mission.m1", "union.mission.m1.completed"},
    {"union.mission.m2", "capitol.mission.m1.completed"},
    {"capitol.mission.m2", "union.mission.m2.completed"},
    {"capitol.mission.sb4", "capitol.mission.m2.completed"},
    {"capitol.mission.sb3", "capitol.mission.sb4.completed"},
    {"capitol.mission.m3", "capitol.mission.sb3.completed"}
};

/* A command owns its whole transition, including the native shell hop. */
enum { DAH_CONSOLE_LEVEL_IDLE, DAH_CONSOLE_LEVEL_SITE,
       DAH_CONSOLE_TRANSIT_TO_SHELL, DAH_CONSOLE_WAIT_FOR_SHELL };
static int g_dah_console_level_phase;
static int dah_console_level_is_busy(void)
{
    uint32_t backend;
    if (g_dah_console_level_phase != DAH_CONSOLE_LEVEL_IDLE) return 1;
    if (MEM32(DAH_CONSOLE_DRIVER) != 0x0022B510u ||
        MEM32(DAH_CONSOLE_DRIVER + 0x4A2Cu) != 0u) return 1;
    backend = MEM32(DAH_CONSOLE_DRIVER + 0x4A28u);
    /* Finished retail backend state 22; states 0..21 include load/unload and
     * failed requests. Both backend slots are embedded in the static driver. */
    if (backend != DAH_CONSOLE_DRIVER + 0x1A18u &&
        backend != DAH_CONSOLE_DRIVER + 0x261Cu &&
        backend != DAH_CONSOLE_DRIVER + 0x3220u &&
        backend != DAH_CONSOLE_DRIVER + 0x3E24u) return 1;
    return MEM32(backend + 0x10u) != 22u;
}

struct dah_console_guest_registers {
    uint32_t integer[9];
    RecompXmm vector[8];
    double fp_stack[8];
    int fp_top, fp_cmp;
    uint16_t fp_control;
};
static void dah_console_level_save(struct dah_console_guest_registers *s)
{
    s->integer[0]=g_eax; s->integer[1]=g_ebx; s->integer[2]=g_ecx;
    s->integer[3]=g_edx; s->integer[4]=g_esi; s->integer[5]=g_edi;
    s->integer[6]=g_ebp; s->integer[7]=g_esp; s->integer[8]=g_seh_ebp;
    s->vector[0]=g_xmm0; s->vector[1]=g_xmm1; s->vector[2]=g_xmm2; s->vector[3]=g_xmm3;
    s->vector[4]=g_xmm4; s->vector[5]=g_xmm5; s->vector[6]=g_xmm6; s->vector[7]=g_xmm7;
    memcpy(s->fp_stack,g_fp_stack,sizeof(s->fp_stack));
    s->fp_top=g_fp_top; s->fp_cmp=g_fp_cmp; s->fp_control=g_fp_control_word;
}
static void dah_console_level_restore(const struct dah_console_guest_registers *s)
{
    g_eax=s->integer[0]; g_ebx=s->integer[1]; g_ecx=s->integer[2];
    g_edx=s->integer[3]; g_esi=s->integer[4]; g_edi=s->integer[5];
    g_ebp=s->integer[6]; g_esp=s->integer[7]; g_seh_ebp=s->integer[8];
    g_xmm0=s->vector[0]; g_xmm1=s->vector[1]; g_xmm2=s->vector[2]; g_xmm3=s->vector[3];
    g_xmm4=s->vector[4]; g_xmm5=s->vector[5]; g_xmm6=s->vector[6]; g_xmm7=s->vector[7];
    memcpy(g_fp_stack,s->fp_stack,sizeof(s->fp_stack));
    g_fp_top=s->fp_top; g_fp_cmp=s->fp_cmp; g_fp_control_word=s->fp_control;
}

static int dah_console_level_hash(uint32_t scratch, const char *text, uint32_t *hash)
{
    uint32_t stack = g_esp;
    size_t length = strlen(text);
    if (length >= 96u) return 0;
    memcpy(XBOX_PTR(scratch),text,length+1u);
    g_ecx=scratch; g_edx=0u;
    PUSH32(g_esp,0u); sub_000D54A0();
    *hash=g_eax;
    return g_esp==stack;
}
static int dah_console_level_add_key(uint32_t store,uint32_t scratch,const char *key)
{
    uint32_t hash,stack=g_esp;
    if (!dah_console_level_hash(scratch,key,&hash)) return 0;
    MEM32(scratch+0x80u)=hash;
    MEM32(scratch+0x84u)=1u;
    g_ecx=store;
    PUSH32(g_esp,scratch+0x80u); PUSH32(g_esp,0u); sub_0008B230();
    return g_esp==stack && (g_eax&255u)!=0u;
}

/* Exact key bundles and order from common_profile.lua UnlockSite (0x6ABAF).
 * The original wrapper adds every preceding site bundle plus the target. */
static const char *const dah_console_unlock_farm[] = {
    "farm",
    "farm.mission.t1",
    "rank.scout.alpha",
    "awareness.nolowlimit",
    "weapon.cortex",
    "ability.jetpack",
};
static const char *const dah_console_unlock_rockwell[] = {
    "rockwell",
    "rockwell.mission.m2",
    "weapon.brainextractor",
    "weapon.zapomatic",
    "weapon.analprobe",
    "weapon.mattermove",
    "weapon.abducto",
    "weapon.holobob",
    "weapon.holobobhelper",
    "weapon.hypnoray",
    "weapon.deathray",
};
static const char *const dah_console_unlock_santa[] = {
    "santa",
    "ability.land",
    "santa.mission.b1",
    "santa.landing.lz1",
};
static const char *const dah_console_unlock_area42[] = {
    "area42",
    "area42.mission.m1",
    "weapon.destructoray",
    "weapon.iondetonator",
    "rank.warrior.lambda",
    "rank.warrior.zeta",
    "rank.captain.sigma",
};
static const char *const dah_console_unlock_union[] = {
    "union",
    "ability.jetpack",
    "weapon.sonicboom",
    "weapon.quantum",
    "weapon.brainray",
    "union.mission.m1",
};
static const char *const dah_console_unlock_capitol[] = {
    "capitol",
    "capitol.mission.m1",
    "ability.jetpack",
    "weapon.zapomatic",
    "weapon.analprobe",
    "weapon.destructoray",
    "weapon.brainray",
    "weapon.iondetonator",
    "weapon.cortex",
    "weapon.mattermove",
    "weapon.holobob",
    "weapon.holobobhelper",
    "weapon.hypnoray",
    "weapon.deathray",
    "weapon.abducto",
};
static int dah_console_unlock_site(uint32_t store, uint32_t scratch, const char *site)
{
    static const struct {
        const char *site;
        const char *const *keys;
        unsigned count;
    } bundles[] = {
        {"farm", dah_console_unlock_farm, 6u},
        {"rockwell", dah_console_unlock_rockwell, 11u},
        {"santa", dah_console_unlock_santa, 4u},
        {"area42", dah_console_unlock_area42, 7u},
        {"union", dah_console_unlock_union, 6u},
        {"capitol", dah_console_unlock_capitol, 15u},
    };
    unsigned destination, i, j;
    for (destination=0; destination<sizeof(bundles)/sizeof(bundles[0]); ++destination)
        if (!strcmp(site,bundles[destination].site)) break;
    if (destination==sizeof(bundles)/sizeof(bundles[0])) return 0;
    for (i=0; i<=destination; ++i)
        for (j=0; j<bundles[i].count; ++j)
            if (!dah_console_level_add_key(store,scratch,bundles[i].keys[j])) return 0;
    return 1;
}

/* The two large site backends share an arena. Retail gameplay leaves via the
 * small blocks/system/transitn world, whose own ignition/process handler loads
 * and switches to the shell. Only after that fresh shell commits may a new
 * site's large stream and warm group replace the old site's storage.
 *
 * Transit ignition removes transition.destination before reading it, so use
 * its supported shell fallback, then queue the destination from that shell.
 * We never publish driver pointers, clear old actors, or write loader flags.
 */
static const struct dah_console_level_route *g_dah_console_level_route;
static uint32_t g_dah_console_level_pending, g_dah_console_level_source;
static uint32_t g_dah_console_level_shell, g_dah_console_level_polls;
static int g_dah_console_level_switch_requested, g_dah_console_level_shell_seen;
static char g_dah_console_level_source_path[260], g_dah_console_level_pending_path[64];

static int dah_console_level_backend(uint32_t backend)
{
    return backend == DAH_CONSOLE_DRIVER + 0x1A18u ||
           backend == DAH_CONSOLE_DRIVER + 0x261Cu ||
           backend == DAH_CONSOLE_DRIVER + 0x3220u ||
           backend == DAH_CONSOLE_DRIVER + 0x3E24u;
}

/* DBF40 -> 19E780 copies the block path into the embedded descriptor +50C.
 * Bounds and canonicalization also let us reject a replacement request that
 * reuses the very same backend slot with a different path. */
static int dah_console_level_backend_path(uint32_t backend, char out[260])
{
    unsigned i, start=0, n=0;
    char raw[260];
    if (!dah_console_level_backend(backend)) return 0;
    for (i=0; i<sizeof(raw); ++i) {
        unsigned c=MEM8(backend+0x50Cu+i);
        if (c>=0x80u || (c && c<32u)) return 0;
        raw[i]=(char)(c=='/' ? '\\' : c);
        if (!c) break;
    }
    if (i==sizeof(raw)) return 0;
    if (i>=3u && (raw[0]=='d' || raw[0]=='D') && raw[1]==':' && raw[2]=='\\') start=3u;
    while (start<i) {
        char c=raw[start++];
        out[n++]=(char)((c>='A' && c<='Z') ? c+('a'-'A') : c);
    }
    while(n && out[n-1]=='\\') --n;
    out[n]=0;
    return n!=0;
}

static int dah_console_level_path_is(uint32_t backend, const char *expected)
{
    char path[260];
    return dah_console_level_backend_path(backend,path) && !strcmp(path,expected);
}

static void dah_console_level_clear(void)
{
    g_dah_console_level_phase=DAH_CONSOLE_LEVEL_IDLE;
    g_dah_console_level_route=NULL;
    g_dah_console_level_pending=g_dah_console_level_source=g_dah_console_level_shell=0u;
    g_dah_console_level_polls=0u;
    g_dah_console_level_switch_requested=g_dah_console_level_shell_seen=0;
    g_dah_console_level_source_path[0]=g_dah_console_level_pending_path[0]=0;
}

static void dah_console_level_fail(const char *reason)
{
    fprintf(stderr,"[DAH-CONSOLE-LEVEL] handoff=cancelled stage=%d backend=%08X reason=%s\n",
        g_dah_console_level_phase,g_dah_console_level_pending,reason);
    dah_console_write("Level transition stopped: %s. See the game log.",reason);
    dah_console_level_clear();
}

/* Caller has saved guest registers and reserved 512 scratch bytes. */
static int dah_console_level_add_string(uint32_t store, uint32_t scratch,
                                        const char *key, const char *value, int persistent)
{
    uint32_t hash, stack=g_esp;
    if (strlen(value)>=64u || !dah_console_level_hash(scratch,key,&hash)) return 0;
    memset(XBOX_PTR(scratch+0x80u),0,0x48u);
    MEM32(scratch+0x80u)=hash;
    MEM8(scratch+0x84u)=(uint8_t)(persistent!=0);
    memcpy(XBOX_PTR(scratch+0x88u),value,strlen(value)+1u);
    g_ecx=store;
    PUSH32(g_esp,scratch+0x80u); PUSH32(g_esp,0u); sub_0008B340();
    return g_esp==stack && (g_eax&255u)!=0u;
}

static int dah_console_level_queue(uint32_t scratch, const char *path)
{
    uint32_t stack=g_esp, pending, current=MEM32(DAH_CONSOLE_DRIVER+0x4A28u);
    if (strlen(path)>=64u || MEM32(DAH_CONSOLE_DRIVER+0x4A2Cu)) return 0;
    if (!dah_console_level_backend_path(current,g_dah_console_level_source_path)) return 0;
    memcpy(XBOX_PTR(scratch),path,strlen(path)+1u);
    g_ecx=DAH_CONSOLE_DRIVER;
    PUSH32(g_esp,MEM8(DAH_CONSOLE_DRIVER+0x4A30u)&1u);
    PUSH32(g_esp,scratch); PUSH32(g_esp,0u); PUSH32(g_esp,0x000DD2D2u);
    sub_000DB0F0();
    pending=MEM32(DAH_CONSOLE_DRIVER+0x4A2Cu);
    if (g_esp!=stack || !(g_eax&255u) ||
        (pending!=DAH_CONSOLE_DRIVER+0x3220u && pending!=DAH_CONSOLE_DRIVER+0x3E24u) ||
        pending==current || !dah_console_level_path_is(pending,path)) return 0;
    g_dah_console_level_source=current;
    g_dah_console_level_pending=pending;
    strcpy(g_dah_console_level_pending_path,path);
    g_dah_console_level_switch_requested=0;
    g_dah_console_level_polls=0u;
    return 1;
}

static int dah_console_level_store_ready(uint32_t *store)
{
    *store=MEM32(0x00249AE4u);
    if (*store<0x10000u || *store>0x07FFB000u || g_esp<0x12000u || g_esp>0x07FFF000u) return 0;
    return MEM32(*store+0x3A50u)<=MEM32(*store+0x3A54u) &&
           MEM32(*store+0x3A80u)<=MEM32(*store+0x3A84u);
}

/* This routine is reached from an idle frontend, or a verified fresh shell
 * after the retail transit path. Destination progress is deliberately deferred
 * until now: shell startup is allowed to do its original progress cleanup. */
static int dah_console_level_queue_site(const struct dah_console_level_route *route)
{
    struct dah_console_guest_registers saved;
    uint32_t store,scratch,stack;
    unsigned i,j;
    int prepared,accepted=0;
    char path[64],group[32];
    if (!dah_console_level_store_ready(&store)) return 0;
    snprintf(path,sizeof(path),"blocks\\sites\\%s",route->alias);
    snprintf(group,sizeof(group),"%s_entry_xbox",route->mission);
    dah_console_level_save(&saved);
    g_esp-=0x200u; scratch=stack=g_esp;
    /* navicommission's retail advance handler publishes the forced mission
     * before UnlockSite and UnlockToMission.  Progress-key insertion can run
     * observers immediately, so preserving that order matters for Rockwell's
     * initial tutorial and mission startup state. */
    prepared=dah_console_level_add_string(store,scratch,"mission.forcelaunch",route->mission,1);
    if(prepared) prepared=dah_console_unlock_site(store,scratch,route->site);
    for(i=0; prepared && i<route->preceding_missions; ++i)
        for(j=0; prepared && j<2u; ++j)
            prepared=dah_console_level_add_key(store,scratch,dah_console_story_keys[i][j]);
    if(prepared) accepted=dah_console_level_queue(scratch,path);
    if(accepted) {
        memcpy(XBOX_PTR(scratch),group,strlen(group)+1u);
        g_ecx=g_dah_console_level_pending;
        PUSH32(g_esp,scratch); PUSH32(g_esp,0x000DD3D6u); sub_000DC680();
        if(g_esp!=stack) {
            fprintf(stderr,"[DAH-CONSOLE-LEVEL] warm stack mismatch expected=%08X actual=%08X\n",stack,g_esp);
            accepted=0;
        } else {
            int entered=dah_console_level_add_key(store,scratch,"site.entered");
            int active=entered && dah_console_level_add_key(store,scratch,"site.active");
            fprintf(stderr,"[DAH-CONSOLE-LEVEL] loading_progress entered=%d active=%d\n",entered,active);
            if(!active) accepted=0;
        }
    }
    fprintf(stderr,"[DAH-CONSOLE-LEVEL] alias=%s mission=%s path=%s prepared=%d accepted=%d pending=%08X\n",
        route->alias,route->mission,path,prepared,accepted,MEM32(DAH_CONSOLE_DRIVER+0x4A2Cu));
    dah_console_level_restore(&saved);
    if(!accepted) return -1;
    g_dah_console_level_phase=DAH_CONSOLE_LEVEL_SITE;
    dah_console_write("Loading %s (%s) through the original game. Close the console to play.",route->alias,route->mission);
    return 1;
}

/* Only the command-owned pending backend is switched. Shell loading/switching
 * belongs to transitn's original Lua ProcessFunc; we observe that middle hop. */
static void dah_console_level_poll_switch(void)
{
    struct dah_console_guest_registers saved;
    uint32_t pending,current,stack,state;
    const char *tag;
    if(g_dah_console_level_phase==DAH_CONSOLE_LEVEL_IDLE) return;
    if(MEM32(DAH_CONSOLE_DRIVER)!=0x0022B510u) { dah_console_level_fail("driver identity changed"); return; }
    if(++g_dah_console_level_polls>18000u) { dah_console_level_fail("original transition timed out"); return; }
    pending=MEM32(DAH_CONSOLE_DRIVER+0x4A2Cu);
    current=MEM32(DAH_CONSOLE_DRIVER+0x4A28u);

    if(g_dah_console_level_phase==DAH_CONSOLE_WAIT_FOR_SHELL) {
        if(current==g_dah_console_level_shell && !pending &&
           dah_console_level_path_is(current,"blocks\\shell\\main") && MEM32(current+0x10u)==22u) {
            int result;
            fprintf(stderr,"[DAH-CONSOLE-TRANSIT] shell_committed=1 backend=%08X\n",current);
            /* Keep ownership/busy set across all original calls; nested command
             * dispatch cannot start another load while progress is changing. */
            result=dah_console_level_queue_site(g_dah_console_level_route);
            if(result<=0) dah_console_level_fail("destination could not be queued from the fresh shell");
            return;
        }
        if(current!=g_dah_console_level_source ||
           !dah_console_level_path_is(current,"blocks\\system\\transitn")) {
            dah_console_level_fail("shell transition was replaced"); return;
        }
        if(pending) {
            if(pending!=g_dah_console_level_shell || !dah_console_level_path_is(pending,"blocks\\shell\\main") ||
               MEM32(pending+0x10u)>22u) {
                dah_console_level_fail("original shell load failed or was replaced"); return;
            }
            if(!g_dah_console_level_shell_seen)
                fprintf(stderr,"[DAH-CONSOLE-TRANSIT] shell_queued=1 backend=%08X\n",pending);
            g_dah_console_level_shell_seen=1;
        } else if(g_dah_console_level_shell_seen) dah_console_level_fail("original shell load was cancelled");
        return;
    }

    if(current==g_dah_console_level_pending &&
       dah_console_level_path_is(current,g_dah_console_level_pending_path) && MEM32(current+0x10u)==22u) {
        if(g_dah_console_level_phase==DAH_CONSOLE_TRANSIT_TO_SHELL) {
            /* Ignition may already have queued shell in the same driver tick
             * that commits transit, so pending need not be zero here. */
            g_dah_console_level_phase=DAH_CONSOLE_WAIT_FOR_SHELL;
            g_dah_console_level_shell=g_dah_console_level_source;
            g_dah_console_level_source=current;
            g_dah_console_level_pending=0u;
            g_dah_console_level_switch_requested=0;
            g_dah_console_level_polls=0u;
            fprintf(stderr,"[DAH-CONSOLE-TRANSIT] transit_committed=1 backend=%08X shell_expected=%08X\n",current,g_dah_console_level_shell);
            /* Validate an already queued shell immediately, without dispatching
             * another original operation from this observation. */
            if(pending && (pending!=g_dah_console_level_shell ||
                !dah_console_level_path_is(pending,"blocks\\shell\\main") || MEM32(pending+0x10u)>22u))
                dah_console_level_fail("transit queued an unexpected destination");
            else g_dah_console_level_shell_seen=pending!=0u;
            return;
        }
        if(pending) { dah_console_level_fail("another load replaced the completed level"); return; }
        fprintf(stderr,"[DAH-CONSOLE-LEVEL] handoff=committed backend=%08X current=%08X pending=00000000\n",current,current);
        dah_console_write("The original game has switched to the requested level.");
        dah_console_level_clear();
        return;
    }
    if(current!=g_dah_console_level_source ||
       !dah_console_level_path_is(current,g_dah_console_level_source_path) ||
       pending!=g_dah_console_level_pending ||
       !dah_console_level_path_is(pending,g_dah_console_level_pending_path)) {
        dah_console_level_fail("pending level load was cancelled or replaced"); return;
    }
    state=MEM32(pending+0x10u);
    if(state>22u) { dah_console_level_fail("original level load failed"); return; }
    if(g_dah_console_level_switch_requested || state!=22u ||
       g_esp<0x12000u || g_esp>0x07FFF000u) return;
    dah_console_level_save(&saved);
    stack=g_esp;
    g_ecx=DAH_CONSOLE_DRIVER;
    /* Original Switch arm rechecks ReadyToSwitch's exact state-22 condition. */
    PUSH32(g_esp,0u); PUSH32(g_esp,0x4BED1273u); PUSH32(g_esp,0u);
    sub_000DCF20();
    g_dah_console_level_switch_requested=g_esp==stack &&
        (MEM32(DAH_CONSOLE_DRIVER+0x4A30u)&2u)!=0u;
    tag=g_dah_console_level_phase==DAH_CONSOLE_LEVEL_SITE ? "DAH-CONSOLE-LEVEL" : "DAH-CONSOLE-TRANSIT";
    fprintf(stderr,"[%s] ready=1 switch_requested=%d backend=%08X flags=%08X stack_ok=%d\n",
        tag,g_dah_console_level_switch_requested,pending,MEM32(DAH_CONSOLE_DRIVER+0x4A30u),g_esp==stack);
    dah_console_level_restore(&saved);
    if(!g_dah_console_level_switch_requested) dah_console_level_fail("original Switch rejected a ready backend");
}

/* 1=request owned; 0=not ready; -1=invalid/handled error. Final mission
 * accepted=1 logging occurs only when the destination actually queues. */
static int dah_console_load_level(const char *alias)
{
    const struct dah_console_level_route *route=NULL;
    struct dah_console_guest_registers saved;
    uint32_t current,store,scratch;
    unsigned i;
    int result;
    char path[260];
    for(i=0;i<sizeof(dah_console_level_routes)/sizeof(dah_console_level_routes[0]);++i)
        if(alias && !_stricmp(alias,dah_console_level_routes[i].alias)) { route=&dah_console_level_routes[i]; break; }
    if(!route) {
        dah_console_write("Unknown level. Use farm, rockwell, santa, area42, union, capitol or cptlboss.");
        return -1;
    }
    if(dah_console_level_is_busy() || !dah_console_level_store_ready(&store)) return 0;
    /* Retail autosave uses the selected zero-based slot at 2637C4. Without
     * it, 89750(Auto) returns early while HUD::Progression remains busy forever.
     * Do not manufacture a slot, reset progression or overwrite existing saves.
     * The original New Game/Load Game UI establishes this prerequisite. */
    if(MEM32(0x002637C4u)>=3u) {
        fprintf(stderr,"[DAH-CONSOLE-PROFILE] required=1 selected_slot=%08X alias=%s\n",
            MEM32(0x002637C4u),route->alias);
        dah_console_write("Start New Game or Load Game once to select a save profile, then use load_level %s.",route->alias);
        return -1;
    }
    current=MEM32(DAH_CONSOLE_DRIVER+0x4A28u);
    if(!dah_console_level_backend_path(current,path)) {
        dah_console_write("The current block path is unavailable; no level load was started."); return -1;
    }
    if(!strncmp(path,"blocks\\sites\\",13u)) {
        if(current!=DAH_CONSOLE_DRIVER+0x3220u && current!=DAH_CONSOLE_DRIVER+0x3E24u) return 0;
        g_dah_console_level_phase=DAH_CONSOLE_TRANSIT_TO_SHELL;
        g_dah_console_level_route=route;
        dah_console_level_save(&saved);
        g_esp-=0x200u; scratch=g_esp;
        /* LoadShell's original default branch, including nonpersistent target. */
        result=dah_console_level_add_string(store,scratch,"transition.destination","blocks\\shell\\main",0);
        if(result) result=dah_console_level_queue(scratch,"blocks\\system\\transitn");
        dah_console_level_restore(&saved);
        if(!result) { dah_console_level_fail("original transit load was rejected"); return -1; }
        fprintf(stderr,"[DAH-CONSOLE-TRANSIT] queued=1 destination=%s source=%08X pending=%08X\n",route->alias,current,g_dah_console_level_pending);
        dah_console_write("Returning through the original mothership transition, then loading %s. Keep the console closed to play when ready.",route->alias);
        return 1;
    }
    if(strncmp(path,"blocks\\shell\\",13u)) {
        dah_console_write("Wait for gameplay or the main menu before loading a level."); return 0;
    }
    g_dah_console_level_phase=DAH_CONSOLE_LEVEL_SITE;
    g_dah_console_level_route=route;
    result=dah_console_level_queue_site(route);
    if(result<=0) dah_console_level_fail("original destination load was rejected");
    return result;
}

#endif
