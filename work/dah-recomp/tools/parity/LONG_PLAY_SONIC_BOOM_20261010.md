# Long-play Sonic Boom callback — retail repair

The October 10 long play observed five unresolved calls to retail address
`0x000A6AF0`, all through vtable `0x002300C8` and returning to `0x0009F218`.
The retail vtable stores `0x000A6AF0` at slot `0x00230124` (`+0x5C`).

Retail instructions show a state-sequence callback. It starts an attached
effect while state is zero, waits for readiness in state one, advances to
state two with a cleared timer, and resets the firing state when the sequence
does not advance. Skipping it leaves the weapon state unchanged.

The callback is lifted from retail bytes `0x000A6AF0..0x000A6B58`. Its table
slot, boundary, and hash are recorded in
`tools/analysis/results/sonic-boom-retail-callback-evidence.json`. No symbols
or pre-release executable participate in the repair.

The same session also reported invisible actors and damaged text after death
and respawn. Those symptoms are tracked separately because this callback is a
weapon state repair and does not by itself prove a global visibility or UI
lifecycle cause.

## Long-session renderer boundary

The host color-target cache already evicted the least recently used resource
after eight distinct guest offsets. The matching depth-surface cache did not:
its ninth distinct offset returned `E_OUTOFMEMORY` before rebinding a DSV, and
the PGRAPH caller did not consume that failure. A long session containing
site loads, deaths, and checkpoint restores could therefore continue with the
previous level's depth surface. Incorrect occlusion and missing geometry are a
direct consequence of that host-only state leak.

The depth cache now uses the same bounded least-recently-used policy as color
targets, preserves the currently bound DSV, and records every creation and
eviction. This removes the deterministic eight-offset exhaustion. The saved
October 10 log predates depth creation telemetry, so the invisible-NPC report
still requires a new long-run negative test before it is closed.

The always-on asynchronous event trace now also emits
`player-render-state` whenever Crypto's retail player pointer, render word,
state byte, scene object, or scene flags change, including world-clock resets.
That captures the first invisible-Crypto boundary even when the separate
read-only blanket observer was not running. It changes no guest state.
