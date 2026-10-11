<div align="center">

# Destroy All Humans! (2005) — Static Recompilation

**A work-in-progress native Windows port of the original Xbox release, built with XboxRecomp.**

[![Platform](https://img.shields.io/badge/platform-Windows%20x64-0078D4?style=flat-square)](#requirements)
[![Target](https://img.shields.io/badge/target-Original%20Xbox-107C10?style=flat-square)](#how-it-works)
[![Frame rate](https://img.shields.io/badge/accuracy%20target-30%20FPS-734F96?style=flat-square)](#status)
[![Repository checks](https://img.shields.io/github/actions/workflow/status/Zippingrocks/Destroy-All-Humans-2005-Static-Recompilation/repository-checks.yml?branch=main&style=flat-square&label=checks)](https://github.com/Zippingrocks/Destroy-All-Humans-2005-Static-Recompilation/actions)

[Status](#status) · [Requirements](#requirements) · [Building](#building-from-source) · [Known issues](#known-issues) · [Contributing](#contributing) · [Coverage dashboard](https://zippingrocks.github.io/Destroy-All-Humans-2005-Static-Recompilation/)

</div>

This project statically translates the original Xbox executable for *Destroy
All Humans!* (2005) into native x86-64 code. A modified XboxRecomp runtime
provides the Xbox kernel, Direct3D 8/NV2A, audio and input services expected by
the game.

The project does **not** contain the game or its assets. You must supply files
from your own legally obtained copy of the original Xbox release.

> [!IMPORTANT]
> This is active reverse-engineering work, not a finished PC release. There is
> currently no stable public player package. Builds made from source are for
> development and compatibility testing.

## Contents

- [Status](#status)
- [Features](#features)
- [Requirements](#requirements)
- [Game files](#game-files)
- [Building from source](#building-from-source)
- [Controls and configuration](#controls-and-configuration)
- [Known issues](#known-issues)
- [Reporting bugs](#reporting-bugs)
- [How it works](#how-it-works)
- [Project layout](#project-layout)
- [Accuracy and validation](#accuracy-and-validation)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [Legal](#legal)
- [Credits](#credits)

## Status

| Area | Current state |
|---|---|
| Windows x86-64 | Development build |
| Boot and front end | Boots through the original title screen and menus |
| Profiles and saves | Profile creation, save selection and autosave are functional, with more long-session testing needed |
| Movies | Original Bink movies play; the archive is under compatibility testing |
| Gameplay | Farm, Rockwell and Santa Modesta paths have been exercised; the complete campaign is not yet validated |
| Graphics | D3D11 rendering is functional; effects, visibility, shadows and presentation parity remain active work |
| Input | XInput controller support and keyboard fallback are available |
| Audio | Runtime support is incomplete |
| Timing | Original 30 FPS behavior is the compatibility target; higher frame rates are experimental |

The project is being validated scene by scene against the retail game running
in xemu. A green build indicates that public source checks pass; it does not
mean that the entire game has reached retail accuracy.

## Features

- Native x86-64 executable produced from statically translated Xbox machine code.
- A DAH-specific XboxRecomp runtime with Direct3D 11, XInput, kernel and APU compatibility work.
- Original title screen, front end, profile flow, saves and game movies.
- Controller input conditioning modeled after the original Xbox controller.
- A keyboard fallback for development and accessibility testing.
- Crash logging, event tracing, frame timing, scripted input and unattended parity tools.
- An interactive [recompilation coverage dashboard](https://zippingrocks.github.io/Destroy-All-Humans-2005-Static-Recompilation/).
- Retail-versus-xemu capture and state comparison workflows for graphical and behavioral accuracy.

## Requirements

### Playing a development build

- Windows 10 or Windows 11, 64-bit.
- A 64-bit x86 processor.
- A Direct3D 11-capable GPU with current drivers.
- An XInput-compatible controller is strongly recommended.
- A legally obtained original Xbox copy of *Destroy All Humans!* (2005).

### Building

- Visual Studio 2022 Build Tools with **Desktop development with C++**.
- A Windows 10 or Windows 11 SDK.
- CMake 3.20 or newer.
- Ninja, supplied by a standard Visual Studio installation.
- PowerShell 5.1 or newer.

The project currently targets Windows because the DAH runtime path uses
Direct3D 11, XInput and Windows platform services.

## Game files

No copyrighted game data is distributed here. Extract your own copy and place
`default.xbe` at:

```text
work/default.xbe
```

Keep the extracted game directories beside the player executable in the same
layout expected by the original title. Game executables, movies, saves,
extracted files and runtime captures are excluded by `.gitignore`.

## Building from source

The recommended build script loads the installed Visual C++ and Windows SDK
environment, verifies the required headers and libraries, configures CMake and
builds the game:

```powershell
cd work\dah-recomp
powershell -NoProfile -ExecutionPolicy Bypass -File tools\build_release.ps1
```

The working binary is normally written to:

```text
work/dah-recomp/build-ninja/dah_recomp_working.exe
```

The repository root may contain `DestroyAllHumans.exe` during local testing,
but compiled executables are intentionally not tracked. Release packaging will
provide a single player-facing executable when the project is ready for public
builds.

Manual Visual Studio developer-shell build:

```powershell
cmake -S work/dah-recomp -B work/dah-recomp/build -G "Visual Studio 17 2022" -A x64
cmake --build work/dah-recomp/build --config Release --target DestroyAllHumans
```

Run the public unit checks with:

```powershell
cmake --build work/dah-recomp/build --config Release --target dah_keyboard_mapping_test dah_stick_conditioner_test
ctest --test-dir work/dah-recomp/build -C Release --output-on-failure
```

## Controls and configuration

An XInput controller is the reference input device. The development keyboard
fallback currently maps:

| Action | Key |
|---|---|
| Move | `W` `A` `S` `D` |
| Menu navigation | Arrow keys |
| A / Confirm | `Enter` or `Space` |
| B / Back | `Q` |
| X | `F` |
| Y | `R` |
| Back / Pause fallback | `Escape` |

These bindings support development when a controller is unavailable. They are
not yet a complete keyboard-and-mouse control scheme.

Developer diagnostics and internal automation are documented in
[`work/dah-recomp/INTERNAL_BRINGUP.md`](work/dah-recomp/INTERNAL_BRINGUP.md).
They are intentionally kept out of ordinary player operation.

## Known issues

- The complete campaign has not received end-to-end validation.
- Some effects, visibility transitions, shadows, attachments and cutscene presentation can differ from the original Xbox renderer.
- Audio output and synchronization remain incomplete.
- Long sessions, death and respawn sequences, and later missions need more stability testing.
- Higher-than-retail frame rates can change game timing and are not considered accurate yet.
- Some diagnostic and recovery systems are development-only and are not suitable for public builds.

The detailed working record lives in the issue tracker and project evidence,
rather than being presented as a claim that every observed bug is still
reproducible. See [Reporting bugs](#reporting-bugs) before filing a report.

## Reporting bugs

Search the existing issues first. If the problem has not been reported, use
the appropriate GitHub issue form and include:

- The exact build or commit.
- Windows version, CPU, GPU and graphics driver.
- The mission, objective and location.
- Clear reproduction steps, including whether Crypto had died or respawned.
- What happened and what the retail game does instead.
- A screenshot or short capture for visual problems.
- `furonlog.log`, `recomp_crash.log` or a crash dump when one was produced.

Do not upload the original XBE, extracted game assets, saves containing private
information, or disc images. Logs can contain local paths, so review them
before posting.

## How it works

XboxRecomp translates the retail Xbox executable's x86 machine code into C.
That generated code is compiled into a native 64-bit Windows program. The
runtime supplies the Xbox APIs and hardware behavior that the translated game
expects, including kernel calls, memory layout, graphics, input and audio.

Game-specific corrections live separately from the generated translation
where possible. Runtime behavior is restored from retail evidence: executable
analysis, traces, controlled captures, xemu comparison and repeatable tests.
Names inferred during reverse engineering are labeled as such; an inferred
name is not presented as an original developer symbol.

The vendored runtime is derived from
[`sp00nznet/xboxrecomp`](https://github.com/sp00nznet/xboxrecomp), release
`v0.6.0`, commit `8541026a4c1bc1cd789ff560559aed9e2af32601`. DAH-specific
changes and provenance are recorded in
[`third_party/xboxrecomp/DAH_RUNTIME_NOTES.md`](third_party/xboxrecomp/DAH_RUNTIME_NOTES.md).

## Project layout

```text
.github/                       GitHub workflows and issue forms
docs/                          Public coverage dashboard
third_party/xboxrecomp/        Pinned runtime plus DAH-specific changes
work/dah-recomp/               Main game project
  src/                         Host integration and manual behavior
  src/recomp/gen/              Statically translated game code
  tools/                       Build, analysis and parity tooling
  docs/evidence/               Machine-readable investigation evidence
Repos/RECOMP_REFERENCE_REPOS.md
                               External research provenance
```

Local game files, builds, logs, captures, saves and reference checkouts are not
part of the source repository.

## Accuracy and validation

The goal is behavioral and visual parity with the original Xbox release at its
retail timing. Work is evaluated with several complementary checks:

1. Reproduce a scene or input sequence in the recompilation and xemu.
2. Capture frames, timing, game state, callback targets and relevant resource activity.
3. Identify the earliest meaningful divergence.
4. Correct the responsible translated function or runtime behavior.
5. Repeat the original scenario and nearby regression scenarios.
6. Preserve the evidence and automated check when practical.

Function and callback coverage can be explored through the
[coverage dashboard](https://zippingrocks.github.io/Destroy-All-Humans-2005-Static-Recompilation/).
Coverage is one measurement; completion also requires correct rendering,
timing, audio, input, saves, AI, scripting and full-campaign behavior.

## Roadmap

- Complete stable retail-speed playthroughs of every story mission and side mission.
- Eliminate unresolved indirect calls reached during normal gameplay.
- Match cutscene visibility, effects, animation, LOD and transition timing.
- Complete saucer weapons, projections and vehicle presentation.
- Stabilize death, respawn and long-session resource behavior.
- Complete audio output and synchronization.
- Turn repeatable parity scenarios into unattended regression checks.
- Package a clean installer or launcher around user-supplied game data.
- Establish a stable compatibility release before pursuing optional PC enhancements and mod support.

## Contributing

Bug reports, retail-behavior evidence, documentation and focused fixes are
welcome. Read [`CONTRIBUTING.md`](CONTRIBUTING.md) before opening a pull
request. Changes that affect game behavior should explain their retail
evidence and include a repeatable validation path.

Please follow the [`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md). Security-sensitive
reports should follow [`SECURITY.md`](SECURITY.md). Current accessibility
support and limitations are documented in [`ACCESSIBILITY.md`](ACCESSIBILITY.md),
and release-facing changes are recorded in [`CHANGELOG.md`](CHANGELOG.md).

## Legal

This is an unofficial community project. It is not affiliated with or endorsed
by THQ, Pandemic Studios, Sony, Microsoft, Black Forest Games or the current
owners of the *Destroy All Humans!* intellectual property.

*Destroy All Humans!* and related names, characters, artwork and assets belong
to their respective owners. This repository does not grant rights to the
original game or its content. Contributors must not submit copyrighted game
data, disc images, executable files, extracted assets, movies or other material
they do not have permission to distribute.

Third-party components retain their own licenses. See [`NOTICE.md`](NOTICE.md)
and the license files within `third_party/`.

## Credits

- Pandemic Studios — original game.
- The XboxRecomp contributors — static recompilation toolchain and runtime.
- The xemu contributors — original Xbox emulation and reference testing.
- The wider Xbox reverse-engineering community — documentation and tooling.
- Project contributors and testers — analysis, validation and compatibility work.
