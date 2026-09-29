# Rockwell parity audit — 2026-09-27 (updated 2026-09-28)

## Retail route

The internal route in `rockwell_hangar_invasion_probe.txt` creates a fresh
profile, enters the original mothership Hangar, selects Rockwell on the retail
navicom, launches the invasion site, leaves the opening presentation unskipped,
and then exercises gameplay and Holobob. `DAH_CONSOLE_AUTO_UNLOCK_SITE=rockwell`
only publishes the retail progression keys after profile selection; it does not
force a level load or bypass the Hangar UI.

The matching xemu reference stayed in the same process (PID 11348, started at
14:30:57). Rockwell was unlocked through the original XBE hash and
`Progress::AddKey` functions, then selected and launched through logical Xbox
controller input. Reference artifacts include:

- `build-parity-xemu/rockwell-hangar-selected-001.png`
- `build-parity-xemu/rockwell-alert-tutorial-001.png`
- `build-parity-xemu/rockwell-holobob-002.png`
- `build-parity-xemu/rockwell-holobob-activate-002.png`

## Recovered Rockwell callback

The first full Rockwell gameplay run reached an indirect target that static
discovery had omitted:

```text
[ICALL] unresolved Xbox target 0x00085FE0 ret=0x00085AC4
```

The retail XBE bytes are:

```text
00085FE0: 8B 49 04 E9 48 FF FF FF
```

This is the alternate vtable thunk paired with `sub_00085FD0`: load the
embedded object from `[ecx+4]` and tail-jump to `sub_00085F30`. The exact thunk
was added as `sub_00085FE0`, registered in the sorted dispatch table, declared
in `recomp_funcs.h`, and retained in `icall_seeds.json`.

Validation run `rockwell-hangar-005` crossed both observed failure points,
including the B-button Holobob windows at frames 7580 and 8000, with zero
unresolved indirect calls. Its principal evidence is:

- `build-internal/rockwell-hangar-005.log`
- `build-internal/rockwell-hangar-005-state.jsonl`
- `build-internal/dah_frame_33068_0000006000.bmp` (Alert Levels)
- `build-internal/dah_frame_33068_0000006125.bmp` (landing)
- `build-internal/dah_frame_33068_0000006700.bmp` (Rockwell gameplay)
- `build-internal/dah_frame_33068_0000007600.bmp` (Holobob path)

Both internal and release configurations built successfully and passed the two
CTest input targets. That intermediate verified release was published as the
repository's single root `DestroyAllHumans.exe` with SHA-256:

```text
C7586D7DE99223D1A1FFA5B010333AB30AFC5570748B58CB9A30D190FEEBF8F5
```

## Vehicle and environment shader coverage

The Rockwell comparison subsequently recovered three missing fixed-function
vertex paths used by gameplay scenery:

- kind 26: vehicle paint
- kind 27: vehicle reflection
- kind 28: static lit environment

These paths removed the large fallback-rendering errors seen on Rockwell cars
and nearby world geometry. A remaining dark-body/pink-glass car comparison is
not yet treated as a color-correction target because the available native and
xemu frames do not prove that they show the same vehicle instance and material
state.

## Measured Holobob parity

The retail selector was measured directly in the existing xemu process. A
valid nearby actor resolved to `0x81F7E120`, with metadata `0x836880C4` and the
retail Holobob-allowed byte set. The successful retail selector used an origin
near `[-179.9843, -353.0118, 5.3585]`, forward vector
`[0.9875653, 0.0970905, -0.1236459]`, spread `0.0490145`, step `5`, and limit
`34.8584`.

The measured xemu state trace entered Holobob state 2 at relative frame 116 and
state 3 at relative frame 178: exactly 62 frames. The deterministic native
route in `rockwell_holobob_targeted_probe.txt` enters state 2 at host frame
3976 and state 3 at host frame 4038: also exactly 62 frames. Relevant evidence
includes:

- `build-parity-xemu/rockwell-holobob-measured-018.json`
- `build-parity-xemu/rockwell-holobob-measured-018-state.jsonl`
- `build-internal/rockwell-holobob-focus-036-state.jsonl`
- `build-ninja/release-holobob-037-state.jsonl`

The disguise update exposed one additional retail indirect target:

```text
[ICALL] unresolved Xbox target 0x00041540
```

The recovered retail routine copies the incoming byte to `[ecx+0x122]`, clears
or preserves the stack argument according to `[ecx+0x120]`, and tail-jumps to
`sub_00109710`. It is now implemented as `sub_00041540`, declared and added to
the sorted dispatch table, and retained in `icall_seeds.json`. Internal run 036
and release run 037 both acquired and committed a valid target, preserved the
62-frame transition, and recorded zero unresolved indirect calls.

The release build passed `dah_keyboard_mapping` and
`dah_stick_conditioner`. It was published as the repository's only root
`DestroyAllHumans.exe` with SHA-256:

```text
89547B7B12E2731DA8FF3598A60F3E6572DC03255F83C7D2E20F3EFD03C73E14
```

## Current visual result and remaining gate

The recomp now reproduces the retail Hangar destination, Rockwell loading,
Alert Levels panel, landing scene, mission objective, gameplay HUD, lighting,
fair geometry, Crypto animation, Holobob selection, activation, projected
disguise and activation timing without missing callback fallbacks. The
captured Alert Levels panel differs from the nearest xemu raw scanout by about
3.73 mean RGB levels at the best adjacent native frame; moving post-process
scanlines and raw-scanout timing still prevent a literal same-frame pixel
identity claim. The next visual gate is a synchronized camera and world-state
capture of the projected disguise and nearby vehicle so that mesh visibility,
material color and remaining flicker can be compared on the same objects.
