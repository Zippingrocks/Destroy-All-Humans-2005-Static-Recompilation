# Contributing

Thank you for helping improve the *Destroy All Humans!* (2005) static
recompilation. The project values small, evidence-backed changes that move the
native build closer to the retail Xbox game.

## Before opening an issue

Search existing issues and read the known issues in the main README. For a new
bug, record the build or commit, hardware, mission and objective, reproduction
steps, expected retail behavior, and any relevant logs or captures.

Never upload an XBE, ISO, extracted game asset, movie, save, memory dump, or
other copyrighted game data. Review logs before posting because they may
contain local paths.

## Development setup

1. Install Visual Studio 2022 Build Tools with Desktop development with C++ and
   a current Windows SDK.
2. Supply `work/default.xbe` from your own legally obtained copy.
3. Run `work/dah-recomp/tools/build_release.ps1` from PowerShell.
4. Run the CTest targets described in the main README.

Internal tracing and unattended test instructions live in
`work/dah-recomp/INTERNAL_BRINGUP.md`. Many of those switches intentionally do
not exist in the ordinary player build.

## Behavioral changes

A gameplay or rendering fix should answer four questions:

1. What exact retail scenario establishes the intended behavior?
2. Where does the recompilation first diverge?
3. Why is the proposed change at the responsible layer?
4. Which original and neighboring scenarios were retested?

Prefer retail executable evidence, xemu traces, repeatable input sequences and
frame captures over assumptions. Clearly label inferred function names. Do not
present alpha-build symbols as retail names unless their identity has been
validated against the retail executable.

Avoid broad symptom patches, state-specific exceptions and changes that make a
single screenshot match while damaging other scenes. Keep diagnostic features
behind development gates.

Read the [port completion standard](work/dah-recomp/tools/parity/PORT_COMPLETION_STANDARD.md)
before adding native code or generated-code hooks. Every `dah_*` intervention
must be classified in `port_integrity_manifest.json`; provisional mitigations,
compatibility code and developer tools do not count as restored game behavior.
Run:

```powershell
python work/dah-recomp/tools/audit_port_integrity.py `
  --json work/dah-recomp/tools/parity/port_integrity_report.json `
  --markdown work/dah-recomp/tools/parity/PORT_INTEGRITY_LEDGER.md
python work/dah-recomp/tools/audit_crash_callbacks.py
```

Commit the regenerated integrity ledger when its inputs change. Repository CI
rejects unclassified hooks, unclassified manual dispatch overrides, seeded
no-op recovery stubs and stale ledger output.

## Pull requests

- Keep each pull request focused.
- Explain the trigger, previous behavior and resulting behavior.
- Include the validation commands and results.
- Document material limitations or untested areas.
- Do not add generated logs, build output, local paths or game data.
- Preserve upstream notices for files derived from another project.

Documentation-only corrections are welcome and do not require gameplay tests.
