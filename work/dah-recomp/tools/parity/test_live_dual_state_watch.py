#!/usr/bin/env python3
"""Semantic-gate checks for exact live visual comparisons."""

from live_dual_state_watch import animation_tick, optional_rate, semantic_diff


def base_state() -> dict:
    return {
        "movieActive": False,
        "uiRootPresent": True,
        "activeUiRoots": ["burn", "startmenu"],
        "activeMenus": [],
        "selectors": [],
        "selectorsComplete": True,
        "rngState": 123,
        "worldAnimationTick": 600,
    }


def main() -> int:
    assert animation_tick(0x3F800000) == 60
    reference = base_state()
    native = base_state()
    native["worldAnimationTick"] += 1
    assert not semantic_diff(reference, native)
    native["worldAnimationTick"] += 1
    assert "worldAnimationTick" in semantic_diff(reference, native)
    native = base_state()
    native["activeUiRoots"] = ["burn", "fade", "startmenu"]
    assert "activeUiRoots" in semantic_diff(reference, native)
    native = base_state()
    native["rngState"] += 1
    assert "rngState" in semantic_diff(reference, native)
    assert optional_rate(120, 60, 2.0) == 30.0
    assert optional_rate(None, 60, 2.0) is None
    assert optional_rate(120, None, 2.0) is None
    assert optional_rate(120, 60, 0.0) is None
    print("live dual state semantic tests passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
