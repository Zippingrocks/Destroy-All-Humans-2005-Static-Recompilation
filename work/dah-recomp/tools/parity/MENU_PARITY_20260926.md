# Menu functional parity observations â€” 2026-09-26

The native menu run reproduces the reference controller option states, Audio and Display menu selection, Pox lab entry, the fresh-profile restricted upgrade screen, the return route, and Hangar entry in the semantic fields currently decoded. This is **functional state evidence only**. It does not certify pixels, animation phase, presented frames, input-to-display latency, audio, physical controllers, or equal timing between xemu and the recompile.

## Evidence and scope

- Native process: 36788; trace `build-internal/parity-menu-suite-state-20260926-009.jsonl`; input schedule `build-internal/parity-menu-suite-20260926.txt`; execution log `build-internal/parity-menu-suite-20260926-009.log`.
- This analysis fixes its trace cutoff at native `hostFrame=34661`. Frames 1â€“34661 are contiguous. The process and its appendable input schedule were still running; later rows are outside this report.
- Reference: `build-parity-xemu/*-20260926-012` through `*-20260926-024`, using their `.ram.bin`, `.ram.bin.json`, `.checkpoint.json`, and `.png` files. RAM was decoded in memory with `tools/parity/decode_xemu_ram.py`; the existing `.state.json` and other snapshots were not overwritten.
- Native state is sampled at phase `000DAD3C`. The `@frame` input schedule uses the retail main-loop counter at `0x0025B1DC`; execution logs confirm the listed logical input frames. Offsets below are the difference between that input frame and the first subsequent sampled state. A `+1` result is a sampling/loop observation, not proof of one-frame display latency.
- Reference checkpoints were paused after `savevm` flushed GPU surfaces. Their metadata explicitly says they are not frame-boundary or timing captures. Synthetic xemu controller injection also uses debugger stops. Reference loop numbers cannot be subtracted from native frame numbers to measure timing parity.

The comparison projects only: active top-level UI names (order ignored), decoded selector paths, `controllerOptions`, both decoder completeness flags, backend name/state, movie pointer zero/nonzero and movie mode/flags, and refresh/divisor/interval. Addresses, allocator layout, world step values, wall time, and cross-engine loop numbers are excluded. The recorded menu references and matching native rows have backend `blocks\shell\main`, state 22, movie 0, movie mode 2, movie flags 0, refresh 60, divisor 1, interval 1. These last three values establish matching configuration fields, not measured presentation cadence.

## Controller options: all four captured states match

These options belong to the progress-key table, not the absent shell gameplay player. Reading `[[0x25FCEC]+0x38]+0x50/54/58/5C` alone yields zeros in these shell menus and cannot establish their option values.

The menu script queries `settings.controller.invertPitch`, `settings.controller.invertYaw`, and `settings.controller.noVibration` through `progress.FindKey`. The source-proven store is `MEM32(0x249AE4)`, with count/capacity/array at `+0x3A50/+0x3A54/+0x3A58`. Sorted eight-byte entries contain a hash followed by the active byte at `+4`. The respective hashes are `26FBC240`, `A37AAC8D`, and `E54032BE`. Both decoders validate bounded counts, readable/aligned arrays, sorted keys, and active bytes. They preserve `present` and `active` separately; a missing key in a valid table is the script's default false, whereas invalid data is unknown. All 34661 native rows and all 13 reference checkpoints have `controllerOptionsComplete=true` and `selectorsComplete=true`.

In this table, **off** means `{present:false, active:false}` and **on** means `{present:true, active:true}`. The `noVibration` key being on means the displayed Vibration setting is Off.

| Reference capture stem | Pitch / yaw / no-vibration | Selected row | First matching native frame | Native input/change evidence |
|---|---|---|---:|---|
| `controls-20260926-012` | off / off / off | `optionsController/slots/slot1/bkgnd` | 3451 | A at 3450 opens Controls; +1 |
| `controls-pitch-inverted-20260926-013` | on / off / off | slot1 | 5478 | Right at 5477; pitch on at +1 |
| `controls-turn-inverted-20260926-014` | off / on / off | slot2 | 7260 | Pitch restored by Left 7079 at 7080; Down 7169 selects row 2 at 7170; Right 7259 turns yaw on at 7260 (+1 each) |
| `controls-vibration-off-20260926-015` | off / off / on | slot3 | 10276 | Yaw restored by Left 10095 at 10096; Down 10185 selects row 3 at 10186; Right 10275 disables vibration at 10276 (+1 each) |

Left at 11166 removes `noVibration` at 11167, restoring all three defaults before leaving Controls. The original `controlSettings` field remains in the trace for gameplay use; it is not used to certify these shell settings. This confirms persisted menu option semantics, not the resulting physical camera response or rumble output.

Native visual captures for these four checkpoints are `dah_frame_36788_0000004410.bmp`, `...0000006270.bmp`, `...0000009510.bmp`, and `...0000011085.bmp` under `build-internal`. Each also has a consecutive-frame partner ending in 4411, 6271, 9511, or 11086. Naming the captures does not imply pixel equality.

## Audio, Display, and autosave gate

| Logical native input | First observed result | Offset |
|---|---|---:|
| B 11256 from Controls | Options row 1 at 11257 | +1 |
| Down 11346 | Options row 2 at 11347 | +1 |
| A 11406 | `optionsAudio`, selector `optionsAudio/slots/slot1/bkgnd`, at 11407 | +1 |
| B 13525 | Options row 2 at 13526 | +1 |
| Down 13615 | Options row 3 at 13616 | +1 |
| A 13675 | `optionsDisplay`, selector `optionsDisplay/slots/slot1/bkgnd`, at 13676 | +1 |
| B 16076 | Options row 3 at 16077 | +1 |
| B 16166 | Options cleared 16167; `greyscale`, `startMenuBackground`, `progression` active16168 | +1 / +2 |
| Same exit sequence | `controllerlegend` becomes active16236 | +70 |
| A 21670 | Progression cleared 21671; hub with slot2 underline 21678 | +1 / +8 |

The semantic projection of Audio reference `audio-20260926-016` first matches native 11407 and remains matched through 13525. Display reference `display-20260926-017` first matches13676 and remains matched through 16076. Native screenshot pairs are 13290/13291 and 15840/15841 respectively.

The script also sends Audio Left 13375/Right 13465 and Display Right 15926/Left 16016. The current trace does not decode audio slider values or the subtitle setting, so those value changes are **not verified by this report**. Active menu/row matches alone do not prove a value changed and restored.

Native screenshot `dah_frame_36788_0000019470.bmp` (partner19471) reads **Autosave successful. / Continue A**. This explains why a fixed menu script cannot assume B from Options immediately returns to the hub: the native `progression` state remains through 21670 until A is supplied. The 68-loop gap from progression activation 16168 to legend activation 16236 and the eight-loop A-to-hub observation are native measurements only. References 012â€“024 contain no paired sample of this autosave confirmation; they establish the later hub state, not matching save duration or exact gate timing.

## Pox, restricted upgrades, return route, and Hangar

| Native logical input or transition | First observed UI/selection | Offset from listed input |
|---|---|---:|
| Down 23177 from hub slot2 | Hub slot3 underline 23178 | +1 |
| Down 23267 | Hub slot4 underline 23268 | +1 |
| A 23357 on slot4 | Hub cleared 23358; `tthubLab` plus controller legend23478 | +1 / +121 |
| First-visit sequence, no new input | `labAlien` and `lab` plus controller legend24949 | +1592 from A 23357; 1471 after `tthubLab` |
| A 25393 from alien hologram | Lab cleared 25394; `labUpgrade` and `lab` plus controller legend25404 | +1 / +11 |
| Right 28662 and Left 28782 in upgrade | No change in the decoded top-level UI/selector projection | Internal upgrade selection is not decoded |
| B 28902 | Upgrade cleared 28903; `labAlien` and `lab`28913 | +1 / +11 |
| B 29926 from settled hologram | Lab cleared 29927; `tthubLab`29938 | +1 / +12 |
| B 31683 from settled Pox entry | Cleared31684; hub slot2 underline 31705 | +1 / +22 |
| A 32853 on hub slot2 | Hub cleared 32854; `navicom` and controller legend32885 | +1 / +32 |

`MENU_ROUTE.md` documents the first-visit tutorial's progress key and animation-completion gate (`shell.upgradetute`, `shell_lab_upgradetute`, `PoxLipsynchAnimDone`). The trace above is consistent with that state sequence. It does not log the animation phase or prove that the 1471-loop wait matches xemu. Native screenshot 24825 shows Pox with the Pox's Lab A / Back B legend; the later transition to `labAlien` occurs before the A at 25393.

Reference filenames are labels, not state assertions. In particular:

| Reference stem | Actual decoded active UI / selection | Native matching evidence |
|---|---|---|
| `pox-entry-20260926-018` | `burn`, `tthubUFO`, `tthubMain`, `controllerlegend`; hub **slot2** | This is a hub capture, not Pox entry. It matches native hub states including21678 and31705. |
| `pox-lab-20260926-019` | `burn`, `tthubLab`, `controllerlegend` | Matches native 23478 and29938; native screenshot 24825/24826 depicts Pox. |
| `lab-hologram-20260926-020` | `burn`, `labUpgrade`, `lab`, `controllerlegend` | Already the upgrade screen; matches native 25404. It does not certify an alien/UFO hologram toggle. |
| `lab-upgrade-20260926-021` | Same upgrade UI as020 | Matches native 25404; native screenshot 27825/27826. |
| `lab-return-20260926-022` | `labAlien`, `burn`, `lab`, `controllerlegend` | Matches native 28913; native screenshot 29850/29851. |
| `hub-before-hangar-20260926-023` | Hub UI with slot2 underline | Matches native 31705. |
| `hangar-20260926-024` | `burn`, `navicom`, `controllerlegend` | Matches native 32885; native screenshot 34575/34576. |

The native 27825 and reference 021 images both display **Researching...**, **Researching New Weapon**, **Specification Unavailable**, **0 DNA**, and **Back B**, with no Purchase A prompt. This is matching visible fresh-profile restriction evidence, not a failed purchase or a usable upgrade catalog. No purchase was tested. Neither the current selector decoder nor the screenshots establish all locked/unlocked weapon choices. The native right/left pulses in this screen do not by themselves verify a weapon change because the trace has no upgrade item identifier.

The native 34575 and reference 024 Hangar images both show **Turnipseed Farm / Destination Earth!**, the New marker, and **Invade! A / Back B**. The `navicom` state agrees. The input at 34660 is a Right pulse, but no destination identifier is decoded; a top-level state that remains `navicom` cannot prove the destination changed. No mission launch, later destination unlock, successful DNA purchase, or UFO hologram switch is certified here.

## Remaining certification work

These captures establish useful state checkpoints for state-gated comparisons. They do not establish exact accuracy. The inspected Pox, upgrade, and Hangar images have visible rendering/animation differences, and they were not captured at a common animation phase. UI names and matching option bits are necessary but insufficient for pixel or frame parity.

A subsequent comparison needs matched input acceptance and update boundaries, the same save/progress state, explicit save/tutorial gates, decoded audio/display/upgrade/destination values, and equivalent image capture stages. Full boot and intro playback also remains outside this result: the native run skips its intro using Start at 2300. The state trace records movie removal 2301, movie flags clearing 2303, and fade ending 2329, but there is no synchronized unskipped reference sequence here.

Only this Markdown report was written for this analysis. No production code, running process, or reference snapshot was modified.
