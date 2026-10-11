# Menu work paused for Farm gameplay parity

At the user's request on 2026-09-26, prioritize the normal Hangar Invade!
transition into Turnipseed Farm, loading, first playable state, and gameplay.
Return to menu work afterward; do not treat the current menu state as complete.

Preserved results: retail millisecond clock, dependent color-table sampling,
NV2A blend equations, and X8 sampled-alpha semantics. The latest live run
53636 confirms the red Pox/upgrade glow is gone. Exact-frame native RenderDoc
capture and headless offline export work. See README.md, MENU_PARITY_20260926.md,
and RENDERDOC_HEADLESS.md for evidence and limits.

Remaining menu issues include a red strip at right/bottom edges, unmatched
animation/noise phase, exact transition/movie sequences, and equivalent final
xemu display capture. Raw VRAM snapshots are not final post-gamma pixels.
Physical controller fidelity and pixel/timing equality remain uncertified.
