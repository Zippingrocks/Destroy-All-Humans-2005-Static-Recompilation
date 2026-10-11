# Santa `b7` retail event map

This document reconstructs the retail mission state machine for Santa Modesta
mission `b7`, **Suburb Of The Damned**, from the Lua 4 chunks resident in a
running retail-derived session. It separates script-proven behavior from
presentation details that still require synchronized xemu/native capture.

## Evidence

Retail chunk sources and RAM offsets in the captured session:

| Chunk | RAM offset |
|---|---:|
| `input\\blocks\\sites\\santa\\scripts\\missions\\b7\\b7_cinematics.lua` | `0x34C5FB4` |
| `input\\blocks\\sites\\santa\\scripts\\missions\\b7\\b7_functions.lua` | `0x34C61F4` |
| `input\\blocks\\sites\\santa\\scripts\\missions\\b7\\b7_ignition.lua` | `0x34C89BC` |
| `input\\blocks\\sites\\santa\\scripts\\missions\\b7\\b7_objectives.lua` | `0x34C9C2C` |
| `input\\shared\\scripts\\common\\mission\\common_mission_flow.lua` | `0x358E4E8` |
| `input\\shared\\scripts\\common\\mission\\common_mission_interface.lua` | `0x358FF6C` |
| `input\\shared\\gui\\site\\input\\gui_site_input_missioncomplete.lua` | `0x3553754` |
| `input\\shared\\gui\\site\\input\\gui_site_input_progression.lua` | `0x35670C0` |

The symbolic names below are original strings in those retail chunks. They are
not names invented by the recomp project.

## Top-level flow

```mermaid
flowchart TD
    A[Mission b7 selected] --> B[Common mission start]
    B --> C[Register b7_zone and load b7_base]
    C --> D[Play AUTOINTRO]
    D --> E[b7_start: 0.25 s]
    E --> F[Intro newspaper]
    F --> G[Armquist arrival cinematic]
    G --> H[b7_delaywaves: 0.05 s]
    H --> I[attackwaves_control]
    I --> J[Waves 1 through 4]
    J --> K[Robot arrival cinematic]
    K --> L[restartWave: 1 s]
    L --> M[Wave 5 phases]
    M --> N[Bert signoff]
    N --> O[Win newspaper queued]
    O --> P[mission.Win nil true]
    P --> Q[Mission Complete overlay]
    Q --> R[Win newspaper]
    R --> S[Progression and autosave]
    S --> T[Continue and original site-to-mothership transition]

    I -. TV station destroyed .-> X[Loss 002]
    I -. Either defended tower below 2.5% .-> Y[Loss 003]
```

## 1. Mission construction and entry

The mission table identifies itself as `b7`, has description
`Suburb Of The Damned`, uses progression key `santa.mission.b7`, registers as a
story mission, and owns `b7_zone`.

When `Start()` runs, retail performs these actions in order:

1. Calls `mission.CommonStart()` and starts `common_missionStart`.
2. Starts the common objective set.
3. Clears the settings tables belonging to the other Santa missions so their
   state cannot leak into this mission.
4. Registers `b7_zone` with the landing system.
5. makes mission zones inactive initially.
6. Starts layer `b7_base` with a `0.0001` start argument.
7. Disables directed spawning.
8. Culls ambient population through the `ambience` layer.
9. Plays AUTOINTRO `#site.santa.b7.furocom.intro.000`.
10. Installs `b7_start` as the completion objective.

The UFO entry placement is explicitly scripted at `(654.2, 615.5, 50)` with
heading `-45`, and `nofadeout=true`. Therefore entry parity must validate the
ship transform, camera/fade behavior, base layer visibility, ambient culling,
and the AUTOINTRO completion edge separately. The mission script proves the
placement and callback order, but the camera shots and animation tracks live in
the referenced cinematic resources and still need frame comparison.

## 2. Post-entry handoff

`b7_start` is a timer objective with a 0.25-second delay.

At its start, retail removes `ability.land` and presents the intro newspaper
`site_santa_b7_news_01` with `nofadein=true`. When the objective completes, it
plays the minor cinematic `site_santa_m3_cin_armqist_01`. The next completion
objective is `b7_delaywaves`. This is the event described by the script as
Armquist and the army arriving.

`b7_delaywaves` waits 0.05 seconds. Its true completion starts
`attackwaves_control` and restores `ability.land`. This small gap is a useful
parity boundary: HUD, control, landing ability, enemies, and music must not
become active before the cinematic callback and this delay have completed.

## 3. Defense initialization

`attackwaves_control` is a custom objective processed every 0.5 seconds. Its
start handler:

1. Starts `b7_army_base`.
2. Records current game time in `b7Settings.WaveTime`.
3. Registers `b7_zone` again for the active defense.
4. Displays objective `#site.santa.b7.furocom.003`.
5. Activates enemy-health HUD controls `|main.enemyhealthx1` and
   `|main.enemyhealthx2`, each initialized to 1.0.
6. Adds radar tags for `b7_tower_01` and `b7_tower_02`.
7. Starts the independent saucer watcher `b7_playerInUFO`.
8. Starts the TV-station destruction watcher `destroy_tvstation`.
9. Enables directed spawning.
10. Sets fear range to 3..3 and fear level to 3.
11. Teleports Crypto to `(680.54, 575.072, 25.84)`.
12. Sets player heading to 0, then camera heading to 0.
13. Registers behavior-complete callbacks that keep soldiers and tanks
    attacking their assigned transmitter/tower targets.
14. Calls `b7.StartWave()`.

The soldier pairs `b7_atsold_t1` and `b7_atsold_t2` engage
`b7_transmitter_01` and `b7_transmitter_02` through
`pedestrian_engage_soldier`. Tank pairs `b7_attank_t1` and `b7_attank_t2`
engage `b7_tower_01` and `b7_tower_02` through `tank_engage`. Robot callbacks
are registered later and use `powersuit_engage` against the transmitters.

## 4. Tower synchronization and failure checks

Each defended position consists of two script-visible parts: a transmitter and
a tower. Every 0.5 seconds, `CheckOneTowerHealth` reads both. Retail treats the
lower value as authoritative and damages the healthier partner until both
represent the same logical health. That prevents the visible structure and its
functional target from drifting apart.

The HUD bar is updated only when the effective value falls. Threshold events:

| Effective health | Tower 1 message | Tower 2 message |
|---|---|---|
| crosses below 50% | suffix `002` | suffix `003` |
| crosses below 20% | suffix `004` | suffix `005` |
| below 2.5% | mission loss `003` | mission loss `003` |

Additional hit reactions choose from suffixes `006`, `008`, `011`, `012`,
`014` for tower 1 and `007`, `009`, `010`, `013`, `015` for tower 2. They use
subtitle root `#site.santa.m3.furocom.tvdefend.` and VO root
`site_santa_m3_furocom_tvdefend_`. Random warnings are rate-limited by
`lastVoTime`, with roughly ten game-time units required between them.

When a logical tower is depleted, `CheckTowers` destroys the paired transmitter
objects and stops `attackwaves_control` as a true/failure completion. That
stops one-shot music and calls `Lose_Start('003')`.

The TV station is monitored independently by a `TagDestroyed` objective on
`m3_tvstation`. Destruction stops dynamic music and calls
`Lose_Start('002')`.

Both loss paths deactivate the two health bars, queue a two-second loss
notification and VO, show `site_santa_b7_news_lose_01`, and call
`mission.Lose(...)`. Loss 002 and loss 003 are therefore distinct and should
remain distinguishable in traces.

## 5. Saucer state branch

`b7_playerInUFO` continuously tests whether the player's focus equals
`FocusState.SHIP`. On the first true result, it plays
`site_santa_m3_armquist_behavior_002` and starts the `b7_tanks` layer.

The saucer is therefore a reactive escalation branch, not the condition that
begins or completes the defense. If the player is already in the ship when the
robot cinematic ends, `restartWave` also starts `b7_tanks`. A parity watcher
should record the focus transition, VO start, layer start, and first spawned
tank independently; merging these into one “entered saucer” event would hide
one-frame or one-tick ordering errors.

## 6. Wave scheduler

The source declares a 12-entry table but consumes it with `tremove(waveTable)`
without an index, so retail executes the declaration in reverse. For each
normal entry, it restarts the named layer, optionally plays Armquist VO,
optionally installs a directed-spawn replacement set at level 3, optionally
plays a Bert broadcast, and starts either a timer or score objective.

Score values are soldier 1, army truck 2, tank 4, and powersuit 6. The score
watchers are group-destruction objectives over groups `army`, `Truck`,
`Military`, and `Robot`. They update the total whenever a group count changes.
Reaching the score limit or expiring the timer calls `EndWave()`.

`EndWave()` stops all score trackers and the timer. An entry with `stop=true`
stops its current layer plus all accumulated active wave layers. An entry
without `stop=true` is retained in `activeLayers`, allowing successive buildup
until the paired cleanup phase.

Actual execution order:

| Step | Entry | Completion | Additions and speech |
|---:|---|---|---|
| 1 | `b7_wave01` | 8 s | One army truck using `vehicle_engage`, parameters `1,10,15,DIRECTED`; Armquist `...behavior_003` |
| 2 | `b7_wave01a` | 45 s; `stop=true` | Bert `...bert_behavior_001` |
| 3 | `b7_wave02` | 8 s | One army truck, `1,10,15,DIRECTED`; Armquist `...behavior_010` |
| 4 | `b7_wave02a` | 45 s; `stop=true` | Bert `...bert_behavior_002` |
| 5 | `b7_wave03` | 8 s | One tagged army truck `1,13,25,DIRECTED`; two tagged tanks `2,15,20,DIRECTED`; Armquist `...behavior_001` |
| 6 | `b7_wave03a` | score 12; `stop=true` | Bert `...bert_behavior_003` |
| 7 | `b7_wave04` | 8 s | Layer buildup |
| 8 | `b7_wave04a` | score 18; `stop=true` | Layer cleanup at completion |
| 9 | event | cinematic callback | Cull wave 3/4 layers and `b7_tanks`; disable directed spawn; destroy `b7_dirspawn`; play `site_santa_m3_cin_armqist_02` |
| 10 | `restartWave` | 1 s | Re-enable directed spawn; restore fear 3..3/level 3; restore `b7_tanks` if player is in ship |
| 11 | `b7_wave05` | 8 s | One army truck `1,15,20,DIRECTED`; one powersuit `1,10,15,DIRECTED`; Armquist `...behavior_009` |
| 12 | first `b7_wave05a` | 30 s; `stop=true` | Bert `...bert_behavior_005` |
| 13 | second `b7_wave05a` | score 15; `stop=true` | Final scored defense phase |

The robot-arrival event also registers `b7_atrobo_t1` and `b7_atrobo_t2` to
attack the two transmitters through `powersuit_engage`.

## 7. Holowatch/cinematic text timing

The `furocom_army` holowatch sequence has explicit subtitle edges:

| Time | Action |
|---:|---|
| 0.000 s | clear/blank text |
| 0.000 s | show `#site.santa.m3.furocom.army.001` on the left |
| 8.202 s | replace with `.002` |
| 16.068 s | replace with `.003` |
| 22.000 s | end holowatch text |

These timestamps should be compared against game time and rendered frame time.
The script may fire correctly while the UI renders a frame early, late, or
under the wrong cinematic mask.

## 8. Success, newspaper, autosave, and return

When the wave table is empty, retail queues notification objective
`bw_signoff`. The notification uses Capitol strings
`#site.capitol.sb3.furocom.08` and `site_capitol_sb3_furocom_08`; this odd reuse
is present in retail data and should not be “corrected” without contrary retail
evidence. `attackwaves_control` is stopped false and both tower-health bars are
deactivated.

`bw_signoff` waits one second and plays Bert broadcast
`site_santa_b7_bert_behavior_006`. On true completion it stops the wave 5
layers, queues `site_santa_b7_news_win`, calls `mission.Win(nil, true)`, and
resets fear range to 1..4 with fear level 1.

The shared retail `mission.Win` path then:

1. Adds the first-completion key
   `santa.mission.b7.completed`, or the repeat-completion key
   `santa.mission.b7.again.completed` after story completion.
2. Increments `stat_missions_complete`.
3. Adds `flow.storycompleted` because the call's second argument is true.
4. Clears the mission-complete reward description because no DNA argument was
   passed.
5. Plays one-shot `mission_victory`.
6. Sets global `finishing=true`.
7. Pushes the GUI input stack and selects state `missioncomplete`.
8. Starts `mission.CompleteFlow` after 0.1 seconds.

The mission-complete GUI pauses simulation plus Ambience and Effects, activates
the mission-complete panel, greyscale and start-menu background, and displays
the success/continue prompt. Meanwhile `CompleteFlow` clears counters and the
current objective, sets `playerLocal.finishedMission=true`, and starts the
`sandbox` mission state so the world remains in a controlled post-mission
condition behind the overlay.

Pressing the confirm input on the mission-complete screen first checks
`playerLocal.queuedNewspaper`. For this mission it is set, so retail opens
`site_santa_b7_news_win`. Closing that newspaper clears the queued value,
switches input to `progression`, requests an automatic save, restores the
start-menu background, and fades back in.

The progression state presents the autosave/result flow. Its completion pops
the progression input state and clears `finishing`. Confirming the successful
autosave then allows the original site-exit transition to unload Santa and
return to the mothership hub. The Lua evidence exposes the progression request,
save mode `Auto`, UI stack changes, and completion callback. The final world
stream/unload is below this Lua layer, so its exact loading frames and timing
must be measured in paired xemu/native traces rather than inferred from these
chunks.

Finally, the mission's `Stop()` calls `mission.CommonStop()`, stops
`b7_army_base` and `b7_tanks`, resets directed spawning, restores fear range
1..4, and ensures `ability.land` is present.

## 9. Recommended event trace

For a deterministic parity run, emit one timestamped row whenever any of these
changes:

- active mission/objective and objective result;
- cinematic ID, cinematic callback, skip request, and skip completion;
- player focus, player transform, camera transform, input-lock state, and
  `ability.land` state;
- layer start/stop/cull and directed-spawn enable/replacement set;
- tagged object spawn/despawn, model/LOD identity, visibility, animation state,
  health, collision, and behavior target;
- transmitter and tower raw health plus synchronized effective health;
- wave index, timer, score-group counts, score total, and stop flag;
- radar-tag lifetime, HUD control activation, bar value, objective text, and
  notification queue;
- audio/VO start and stop, subtitle ID, holowatch state, and music state;
- fear settings, pause state, GUI input stack, fade/greyscale state, newspaper,
  progression state, save start/result, and site transition;
- rendered frame number, simulation tick, CPU frame time, GPU present time,
  asset-stream request/completion, and screenshot hash.

The trace should record both the event-request edge and the first frame where
the result is visible. That distinction is what reveals pop-in, one-frame HUD
leaks, T-poses, missing effects, delayed LOD swaps, and transitions that are
logically correct but visually late.

## Confidence boundary

The ordering, IDs, timer values, thresholds, score weights, progression keys,
callbacks, and GUI/save calls above are directly supported by retail Lua
bytecode. Exact camera cuts, skeletal poses, particles, materials, object LODs,
audio sample alignment, loading-screen duration, and the native world-stream
transition are referenced by the scripts but implemented in other assets or
native systems. Those require synchronized xemu/recomp capture before they can
be called pixel- or frame-accurate.

## Playtest disposition: provisional pass

The October 10 live playtest is recorded as a **provisional gameplay pass** at
the player's request. The defense waves were completed and the run reached the
post-wave state without a crash. This designation means the player completed
the playable mission challenge; it does not close visual parity or completion
flow work.

Open defects observed or supported by the live trace:

- soldiers can intermittently render invisible;
- vehicles can intermittently render invisible, with tanks reported most
  often;
- Crypto's scene flags pulse between `0x00000000` and `0x00000010` for short
  intervals, a visibility/flicker lead that still needs exact flag semantics
  and an xemu comparison;
- the wave controller, timer, score trackers, and signoff objective disappeared
  while `santa.mission.b7` remained active and the simulation later resumed;
- the Mission Complete, victory newspaper, autosave, and mothership-return
  chain was therefore not proven by this run and may be stalled or orphaned;
- measurable gameplay hitches remain, including approximately 180 ms, 98 ms,
  and 51 ms frames plus smaller 34--38 ms misses.

Do not promote this mission to a parity pass until the missing-character and
missing-vehicle cases have negative coverage, the final flow returns to the
mothership, and a paired xemu run confirms event and presentation timing.

## Post-wave stall diagnosis and correction

The live objective list after the final wave contained `common_notifySetText`
but no wave controller and no `bw_signoff`. Retail's notification objective
does not start its `msgObjective` until the associated VO handle reports that
it has stopped. The DirectSound bridge cached `DSBSTATUS_PLAYING` when playback
began but did not clear it when the non-looping APU mixer voice naturally
reached its end. Empty or unavailable cues could acquire the same stale state.
That made retail `sound.IsPlaying()` remain true and held the notification open
forever, so `bw_signoff` was never started.

Commit `1666102` synchronizes `IDirectSoundBuffer::GetStatus` with the active
mixer voice and immediately reports a failed/empty playback attempt as stopped.
This corrects the host audio lifecycle used by every retail script rather than
bypassing mission `b7`. The release build and hidden smoke run passed. A live
replay still needs to prove the complete `bw_signoff` through mothership-return
chain.

Commit `d8a23a8` adds a constant-time, always-on trace event for rapid
visible/culled/visible oscillation of dynamic type-7 scene models. Each event
records the object and model pointers, both flag words, transition timing, and
world position. This supplies the missing evidence needed to distinguish a
whole soldier or vehicle from an independently culled animated part before a
targeted retention change is attempted.

### Live completion recovery and font-resource evidence

The later b7 replay reached the same final notification with
`attackwaves_control`, `b7_wave_timer`, and `b7_score_start` complete and
`bw_signoff` waiting. The retail sound-manager list was already empty, so this
instance was not held by an active DirectSound buffer. Activating the prepared
`bw_signoff` timer allowed its unchanged retail `StopTrue` callback to run:
the save slot was written and the game returned to Pox's Lab on the mothership.
The notification scheduler still needs a root-cause fix; the live recovery is
evidence, not the production implementation.

The mission-complete panel initially had blank and exploded text. Both live
1,024-glyph font renderers had valid index-buffer descriptors but missing
vertex-buffer descriptors after the long session. Supplying isolated backing
pages immediately restored readable UI text. The player build now reserves a
bounded four MiB of the already-mapped devkit address space for recomp host GPU
resource overhead. Gameplay continues to use the retail allocation model; the
reserve prevents required double-buffered UI/font pages from failing at the
64 MiB accounting edge.
