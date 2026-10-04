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

Version 2 also records the executable path and SHA-256, an every-second census
by class/resource/named AI state/life state, observed world-tick rate, and a
history summary for every actor. Histories include total movement, time in the
current AI state, time since movement, AI/life/target/physics/render transition
counts, last position, maximum height, verified retail body velocity, inner
physics quaternion, and maximum observed speed. A dead-to-alive transition and a
living pedestrian that disappears without an observed death are explicit
anomalies. This makes quiet, stuck, streamed, killed, and allocator-reused
objects distinguishable in the run report.

Example:

```powershell
python tools/parity/live_blanket_observer.py --pid 1234 `
  --output tools/parity/live-blanket-run.jsonl
```

The default follows that process until it exits and then emits actor summaries
and a `run-end` event. Use `--seconds N` only for a deliberately bounded probe.

For a test session containing several user-launched runs,
`watch_blanket_runs.py` can watch one exact executable path and start one hidden,
read-only observer per detected process. It does not launch, focus, control, or
terminate the game:

```powershell
python tools/parity/watch_blanket_runs.py `
  --executable C:\exact\path\DestroyAllHumans.exe `
  --output-dir build-internal\blanket-runs
```

Decode an existing atomic xemu RAM checkpoint into the same census fields:

```powershell
python tools/parity/xemu_blanket_snapshot.py checkpoint.ram.bin `
  --out checkpoint-blanket.jsonl --atomic
```

Compare only after the two captures have been aligned to the same level,
checkpoint, mission state, input edge, and world tick:

```powershell
python tools/parity/compare_blanket_census.py checkpoint-blanket.jsonl `
  native-run.jsonl --alignment verified --out census-comparison.json
```

Without `--alignment verified`, the comparison labels all differences as
diagnostic only. This prevents two different mission phases from being reported
as game bugs merely because their actor populations differ.

The next instrumentation layers should add stable event IDs at the retail
boundaries for damage application and attribution, AI task transitions, PK
target acquire/release and physics constraints, particle/effect ownership,
resource streaming, render visibility, audio cues, mission/objective state,
and cutscene/HUD gates. Those events should feed the same JSONL timeline from a
buffered writer so diagnostic output never blocks the game thread.

`DAH_EVENT_TRACE=<new-jsonl-path>` enables the first exact boundary layer in a
new build. The retail AI state-manager commit at `0001E870` pushes fixed-size
old/new state records into a 16,384-entry memory ring. A background writer
drains it every 50 ms; the game thread performs no file I/O and emits an
explicit `trace-overflow` record if the ring ever fills. Each event includes
world tick, manager, owning actor, old/new state pointers, IDs and names, plus
the retail caller. The variable is read only at startup and is unset for normal
play. It cannot be enabled retroactively in an already-running process.

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

The next additions are ordered by how much ambiguity they remove:

- instrument the central AI transition function with old/new descriptor IDs,
  state names, actor serial, caller address, and reason;
- instrument damage and death application with attacker, victim, weapon/power,
  hit part, amount, impulse, and the chosen death-state descriptor;
- track PK constraints from acquire through force, collision, release,
  ragdoll, recovery, and any resulting death;
- track effect emitters with template, owner, position, birth/death tick, live
  particle count, and termination reason;
- track streaming and renderer decisions for each scenery serial, including
  requested/ready/visible/LOD/cull state and the camera used for the decision;
- track animation clip/state/time and skeletal part visibility for people,
  cows, weapons, and vehicles;
- track mission, cinematic, camera, HUD, subtitle, and audio transitions on the
  same world-tick timeline;
- compute per-frame render fingerprints and only capture full images around the
  first divergent tick, limiting overhead while retaining pixel evidence.

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
