# DAH xboxrecomp runtime snapshot

This directory is a source snapshot derived from:

- Upstream: https://github.com/sp00nznet/xboxrecomp
- Release: `v0.6.0`
- Commit: `8541026a4c1bc1cd789ff560559aed9e2af32601`
- License: MIT (see `LICENSE`)

It includes the exact project-local runtime changes currently required by the
Destroy All Humans! recompilation. Important modified areas include D3D11/NV2A
translation, Xbox kernel compatibility, XInput conditioning, and APU behavior.

Large generated analysis outputs under `tools/**/output/`, local build trees,
and caches are intentionally excluded. Keep upstream provenance in this file
when updating the runtime, and review DAH-specific changes before rebasing onto
a newer upstream release.
