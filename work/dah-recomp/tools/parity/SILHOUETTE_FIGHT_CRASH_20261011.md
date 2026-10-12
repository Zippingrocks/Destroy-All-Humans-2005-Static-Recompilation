# Silhouette fight crash DAH-192507A8B0B8C19F

The October 11 playthrough crashed immediately after the AI transition from
`script_silhouette_path_follow_run` to `pedestrian_engage_silhouette`.
`crashlog` recorded an invalid read in the retail deferred-callback destructor
at guest return `0x00104D56`.

The preceding indirect-call evidence identifies the first causal omission:
vtable `0x00227A50` dispatched to `0x00025060` from retail call site
`0x0001AE4D`. The verified retail XBE contains a complete 195-byte event
handler at `0x00025060`, but automatic function discovery ended the adjacent
`0x00025040` function at that exact address and did not translate the handler.
Returning from that unresolved call skipped Silhouette's event state changes;
the same frame's temporary callback cleanup subsequently encountered invalid
records and crashed in `0x00111520`.

`recomp_silhouette_event_callback.c` is a direct translation of retail bytes
`0x00025060..0x00025123` and the five-entry retail jump table at `0x00025124`.
It restores event kinds 5 through 9, both hashed action calls, the four
state-dependent object callbacks, the `+0xD0` object tail dispatch, and the
original default tail call to `0x00022270`. No guessed Silhouette state or
crash-only pointer suppression is introduced.

The later logged values `0x00023899`, `0x0002389F`, and `0x0025F060` are not
missing retail function starts: the first two are continuations inside retail
function `0x000237C0`, while the last lies in retail data. They appeared only
after cleanup was already consuming invalid records and are retained by the
callback audit as rejected crash fallout rather than being turned into fake
functions.
