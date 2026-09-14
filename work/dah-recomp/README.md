# Destroy All Humans! (2005) static recompilation

This is an early Windows-native static-recomp bring-up generated from the
original Xbox executable. It is not yet a finished playable port.

## Build

Open a Visual Studio developer prompt, then run:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

The output is `build/Release/DestroyAllHumans.exe` for the Visual Studio
generator, or `build-ninja/DestroyAllHumans.exe` for the local Ninja build.
The build copies the locally extracted `default.xbe` beside it. Game data
remains user-supplied and must not be redistributed.

## Current bring-up status

- More than 9,700 Xbox functions compile and link into a 64-bit Windows executable.
- Xbox memory, the kernel bridge, and the CRT thread entry initialize.
- The title's real START path now reaches the shell/front-end script loop; a
  missing script inequality dispatch (`0x00196D92`) and the host window
  lifetime issue have been repaired.
- This is still an engineering build, not yet a playable release. Internal
  tests now render the real THQ and Pandemic movies, with the observed block
  artifacts repaired, and progress into main-menu setup. Missing native
  callbacks during that setup are still being restored. Neither an interactive
  main menu nor stable 30 FPS menu rendering has been verified.
- A static saucer-image presentation probe exists but is disabled by default.
  It is not the game menu and must never count as a successful boot.

Each run writes `recomp.log` beside the executable.

## Runtime bring-up modes

Active tests use `build-internal/DestroyAllHumans.exe`, with separate copies
of game data and separate saves/logs. The user's `build-ninja` binary is not
updated by internal builds. A reversible frame-rate setting is available:

```powershell
$env:DAH_FPS = '30'
.\DestroyAllHumans.exe
```

`DAH_FPS=60` selects the explicit 60 Hz path. Both paths set the retail world
divisor, but correct cutscene/gameplay speed still needs verification. The keyboard
fallback maps WASD/arrows to movement, Enter/Space to A, Q to B, F to X, R to
Y, and Escape to Back; a physical XInput controller is still preferred when
available.

`DAH_HOST_FRAME=1` explicitly enables the static presentation probe if
`movies\\saucer_frame_030.raw` is beside the executable. Leave it unset or
set to `0` for real boot/render verification.

The stack-sampling watchdog and KPCR/mirror page watcher are disabled during
normal runs because they intentionally suspend or trap the frame thread. They
can be re-enabled for diagnostics with `DAH_WATCHDOG=1` and
`DAH_KPCR_WATCH=1`.

For controlled front-end probes only, `DAH_AUTOSTART=1` injects the retail
START input once, `DAH_AUTOSTART2=1` can inject a later START for the shell
intro gate, and `DAH_AUTOA=1` injects A after a configurable input-call delay.

## Isolated verification

After building `build-internal` and copying user-supplied `blocks` and `movies`
beside that executable, run `tools/run_internal.ps1`. This bounded runner sets
`DAH_INTERNAL_RUN=1` and `DAH_FPS=30`, hides the game window, supplies neutral
physical input, silences output after audio mixing, and archives a PID-specific
log. It stops only the process it launched. Do not run it against user builds.

`DAH_FRAME_CAPTURE` saves actual swapchain frames to PID-specific BMP files;
`DAH_FRAME_CAPTURE_INTERVAL` controls spacing. Synchronous readback adds cost,
so final pacing verification must be a separate capture-free run. A ticking
30 Hz loop, occluded presents, a solid-color frame, or the static image probe
is not evidence of a working menu. Success requires recognizable native menu
frames, interaction, and a sustained measured 30 FPS run.
