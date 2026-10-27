#!/usr/bin/env python3
"""Deterministic checks for live phase-baseline selection."""

from __future__ import annotations

import time

from live_dual_phase_watch import choose_baseline_offset


def edge_series(first_value: int, count: int, period_ns: int,
                phase_ns: int = 0) -> list[tuple[int, int, int]]:
    end = time.perf_counter_ns() - 10_000_000
    first_stamp = end - (count - 1) * period_ns + phase_ns
    return [(first_value + index, first_stamp + index * period_ns, 1)
            for index in range(count)]


def main() -> int:
    period = 16_666_667
    reference = edge_series(1_000, 120, period)
    native = [(5_000 + index, stamp + 2_000_000, step)
              for index, (_, stamp, step) in enumerate(reference)]
    chosen = choose_baseline_offset(reference, native, 5_000_000_000)
    assert chosen is not None
    offset, evidence = chosen
    assert offset == 4_000, chosen
    assert evidence["matchedEdges"] == 120, evidence
    assert evidence["phaseMedianMs"] == 2.0, evidence

    # Equal-looking counter values must not establish a baseline when one side
    # is already running at a different cadence.
    movie_reference = edge_series(2_000, 60, 40_000_000)
    shell_native = edge_series(8_000, 120, period)
    assert choose_baseline_offset(movie_reference, shell_native,
                                  5_000_000_000) is None
    print("live dual phase baseline tests passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
