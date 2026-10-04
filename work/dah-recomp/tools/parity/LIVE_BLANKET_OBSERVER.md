# Live blanket observer

`live_blanket_observer.py` is a read-only observer for an already-running native
recomp. It uses `ReadProcessMemory`; it cannot control the game or alter Xbox
memory. It identifies ten retail entity-controller classes with six constructor
invariants, resolves names such as `h_male_farmer_shotgun`, `v_tractor`, and
`p_tree_large_farm` from retail resource records, then records compact JSONL
events instead of full object dumps.

The first coverage layer records actor spawn/despawn, raw lifecycle gate and render state,
raw state-word transitions, transforms, address reuse, invalid transforms,
large transform jumps, and actor removals. The `+0x140` byte is intentionally
named `stateByte140`: its constructor and update behavior are known, but it has
not been proven to mean alive/dead. The final `run-end` event marks semantic areas
that remain unobserved. This prevents a quiet log from being mistaken for
successful coverage.

Example:

```powershell
python tools/parity/live_blanket_observer.py --pid 1234 `
  --output tools/parity/live-blanket-run.jsonl --seconds 600
```

The next instrumentation layers should add stable event IDs at the retail
boundaries for damage application and attribution, AI task transitions, PK
target acquire/release and physics constraints, particle/effect ownership,
resource streaming, render visibility, audio cues, mission/objective state,
and cutscene/HUD gates. Those events should feed the same JSONL timeline from a
buffered writer so diagnostic output never blocks the game thread.

## The blanket

Every parity run should cover these layers and mark each one as **not
exercised**, **recomp captured**, **both captured**, or **matched**:

1. **Run identity:** executable SHA-256, Git commit, build profile, game assets,
   save slot/checkpoint, level, settings, and capture tick range.
2. **Clock and input:** world tick, simulation step, pause/focus state, raw and
   conditioned controller packets, input consumers, dropped/repeated packets,
   frame time, draw time, and presentation time.
3. **Mission and cinematics:** level/load phases, objective state, script/Lua
   events, cutscene camera, shot and animation transitions, skip requests, HUD
   gates, subtitles, and audio cues.
4. **Entity lifecycle:** type/name, stable serial, spawn/despawn reason,
   transform, visibility, LOD, streaming ownership, parent/child attachments,
   and allocator address reuse. This includes scenery, vehicles, projectiles,
   pickups, mission objects, Crypto, the saucer, and every NPC.
5. **AI:** alive/dead, health, faction, current high-level goal, current task,
   target, navigation path, awareness, animation state, ragdoll state, recovery
   attempt/result, and time stuck in a state.
6. **Combat and powers:** weapon selection, trigger edges, shot/projectile,
   collision, damage source/type/amount, death attribution, Cortex Scan target
   and result, PK acquire/constraint/force/release, and Holobob target/state.
7. **Physics:** bodies and constraints created/destroyed, ownership, transforms,
   linear/angular velocity, collision pairs, sleep/wake, contact impulses, and
   out-of-range or non-finite values.
8. **Rendering:** submitted and rejected models, meshes, submeshes, materials,
   textures, render targets, effects, particles, shadows, lights, cull/LOD
   decisions, per-pass draw order, and screen-space frame hashes.
9. **Resources and effects:** request/load/ready/unload, use-before-ready,
   emitter owner/template/count/lifetime/bounds, duplicate emitters, orphaned
   effects, and effect termination reason.
10. **Audio and persistence:** cue start/stop/owner, stream starvation, save
    creation/load result, checkpoint state, unlocks, inventory, and upgrades.

An anomaly pass should flag actors that vanish without a recognized unload or
death, health changes without a damage event, damage without a source, AI tasks
that exceed their retail duration, ragdolls that never recover, effects without
an owner, resources used before ready, visibility that flips while Xemu stays
stable, transforms that jump or become non-finite, and HUD/camera states that
precede their retail transition.

The external observer is suitable for the running session and coarse lifecycle
discovery. Exact frame attribution belongs at the retail boundaries inside the
recomp: callbacks write fixed-size events to a lock-free ring, and a host writer
flushes them asynchronously. Xemu should export the same fields from matching
guest addresses. Both streams can then align by world tick, mission state, and
input edge before screenshots are compared. This avoids synchronous logging on
the game thread, which previously caused visible stutter.

Each comparison run should also record the executable hash, Git commit, level,
save slot, checkpoint, input script, emulator/recomp settings, and capture
start/end ticks. A coverage report can then distinguish four states per system:
not exercised, exercised only on the recomp, exercised on both builds, and
compared with matching results.
