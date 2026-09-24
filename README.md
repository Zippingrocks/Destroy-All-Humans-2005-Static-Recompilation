# Destroy All Humans! (2005) Static Recompilation

An experimental native Windows recompilation of the original Xbox release of
*Destroy All Humans!* (2005). The project aims for accurate behavior, stable
frame pacing, and a mod-friendly native PC build.

## Current state

- Native boot through the original title screen and front end
- Profile creation, saves, menu navigation, and Bink movie playback
- Playable Farm, Rockwell, and Santa Modesta paths using original assets
- D3D11 rendering through a DAH-specific `xboxrecomp` runtime
- XInput controller support under active compatibility work
- 30 FPS is the current compatibility target; 60 FPS remains experimental

This is active reverse-engineering work, not a finished release. Audio output,
later-level reliability, controller fidelity, and end-to-end gameplay stability
remain incomplete.

## Repository layout

- `work/dah-recomp/` — game recompilation source, generated translation units,
  tests, probes, and project documentation
- `third_party/xboxrecomp/` — pinned runtime snapshot with DAH-specific graphics,
  input, kernel, and APU changes
- `work/disasm-seeded/` — generated analysis metadata used by the recompilation
- `Repos/RECOMP_REFERENCE_REPOS.md` — references used during development

## Required game files

This repository does not distribute the original game, executable, movies, or
other copyrighted assets. Supply files from a legally obtained copy of the
original Xbox game.

Place `default.xbe` at `work/default.xbe`. At runtime, keep the required game
data beside the built executable using the same layout expected by the original
project. These local files are ignored by Git.

## Build

Use a Visual Studio developer shell with CMake 3.20 or newer:

```powershell
cmake -S work/dah-recomp -B work/dah-recomp/build-ninja -G Ninja
cmake --build work/dah-recomp/build-ninja --config Release
```

The resulting executable is normally
`work/dah-recomp/build-ninja/DestroyAllHumans.exe`. See
`work/dah-recomp/README.md` and `work/dah-recomp/INTERNAL_BRINGUP.md` for current
runtime switches, probes, known issues, and bring-up notes.

## Runtime provenance

The vendored runtime is derived from `sp00nznet/xboxrecomp` v0.6.0 at commit
`8541026a4c1bc1cd789ff560559aed9e2af32601`, plus the project-specific changes
documented in `third_party/xboxrecomp/DAH_RUNTIME_NOTES.md`. Its upstream MIT
license is retained.

## Legal

No original game data is intended to be committed. Contributors must use their
own legally obtained copy and must not submit XBE files, disc images, movies,
extracted game data, saves, crash dumps, or compiled binaries.
