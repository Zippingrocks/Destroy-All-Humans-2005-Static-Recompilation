#!/usr/bin/env python3
"""Timestamp xemu/native retail-loop edges independently and compare phase."""

from __future__ import annotations

import argparse
import collections
import json
import statistics
import threading
import time
from pathlib import Path

from live_dual_state_watch import NativeReader, XemuReader, u32, write_status


LOOP_ADDRESS = 0x0025B1DC


def append(path: Path, row: dict) -> None:
    with path.open("a", encoding="utf-8", buffering=1) as stream:
        stream.write(json.dumps(row, separators=(",", ":")) + "\n")


def state_alignment_ready(path: Path | None, maximum_age: float = 0.5) -> bool:
    if path is None or not path.exists():
        return False
    try:
        value = json.loads(path.read_text(encoding="utf-8-sig"))
        age = time.time() - float(value.get("at", 0))
        return bool(value.get("event") == "alignment" and
                    0 <= age <= maximum_age and
                    value.get("captureAligned") is True and
                    not value.get("divergent") and
                    not value.get("semanticDiff"))
    except (OSError, ValueError, json.JSONDecodeError):
        return False


class EdgeSampler(threading.Thread):
    def __init__(self, name: str, reader, interval: float):
        super().__init__(name=f"dah-phase-{name}", daemon=True)
        self.side = name
        self.reader = reader
        self.interval = interval
        self.stop_event = threading.Event()
        self.lock = threading.Lock()
        self.edges = collections.deque(maxlen=4096)
        self.read_errors = 0
        if isinstance(reader, XemuReader):
            physical = reader.physical(LOOP_ADDRESS)
            self.host_address = reader.ram_base + physical
        else:
            self.host_address = LOOP_ADDRESS + 0x10000

    def run(self) -> None:
        previous = None
        deadline = time.perf_counter()
        while not self.stop_event.is_set() and self.reader.running():
            try:
                value = u32(self.reader.read_host(self.host_address, 4))
                observed = time.perf_counter_ns()
                if previous is None:
                    previous = value
                elif value != previous:
                    with self.lock:
                        self.edges.append((value, observed,
                                           (value - previous) & 0xFFFFFFFF))
                    previous = value
            except OSError:
                self.read_errors += 1
            deadline += self.interval
            remaining = deadline - time.perf_counter()
            if remaining > 0:
                time.sleep(remaining)
            else:
                deadline = time.perf_counter()

    def snapshot(self) -> list[tuple[int, int, int]]:
        with self.lock:
            return list(self.edges)


def percentile(values: list[float], fraction: float) -> float | None:
    if not values:
        return None
    ordered = sorted(values)
    index = min(len(ordered) - 1, max(0, round((len(ordered) - 1) * fraction)))
    return ordered[index]


def signed_u32_delta(left: int, right: int) -> int:
    value = (left - right) & 0xFFFFFFFF
    return value - 0x100000000 if value & 0x80000000 else value


def choose_baseline_offset(reference, native, window_ns: int) -> tuple[int, dict] | None:
    """Choose the counter mapping whose matched edges are closest in time.

    Process attachment can briefly stall either target.  The two counters also
    have an arbitrary lifetime offset, so the first pair of reads is not a safe
    phase baseline.  Once both samplers have a useful edge window, search the
    adjacent mappings and choose the one with the smallest absolute phase.
    """
    now = time.perf_counter_ns()
    ref_recent = [(value, stamp, step) for value, stamp, step in reference
                  if now - stamp <= window_ns]
    nat_recent = [(value, stamp, step) for value, stamp, step in native
                  if now - stamp <= window_ns]
    if len(ref_recent) < 60 or len(nat_recent) < 60:
        return None
    # A baseline describes equivalent clocks.  If one side is already in a
    # movie, loading transition, or stall, preserve that as unaligned evidence
    # instead of blessing the mismatched cadences as a new baseline.
    if abs(len(ref_recent) - len(nat_recent)) > 2:
        return None
    center = signed_u32_delta(nat_recent[-1][0], ref_recent[-1][0])
    ref_map = {value: stamp for value, stamp, _ in ref_recent}
    nat_map = {value: stamp for value, stamp, _ in nat_recent}
    candidates = []
    for candidate in range(center - 2, center + 3):
        deltas, median, deviations = phase_statistics(ref_map, nat_map, candidate)
        if len(deltas) < 30 or median is None:
            continue
        candidates.append((abs(median),
                           percentile(deviations, 0.95) or 0.0,
                           -len(deltas), candidate, median))
    if not candidates:
        return None
    _, p95, neg_matches, candidate, median = min(candidates)
    if p95 > 4.0:
        return None
    return candidate, {
        "matchedEdges": -neg_matches,
        "phaseMedianMs": round(median, 6),
        "phaseP95DeviationMs": round(p95, 6),
        "observedLatestOffset": center,
    }


def phase_statistics(reference: dict[int, int], native: dict[int, int],
                     offset: int) -> tuple[list[float], float | None, list[float]]:
    deltas = []
    for ref_value, ref_stamp in reference.items():
        native_stamp = native.get((ref_value + offset) & 0xFFFFFFFF)
        if native_stamp is not None:
            deltas.append((native_stamp - ref_stamp) / 1_000_000.0)
    median = statistics.median(deltas) if deltas else None
    deviations = [abs(value - median) for value in deltas] if median is not None else []
    return deltas, median, deviations


def summarize(reference, native, offset: int, window_ns: int) -> dict:
    now = time.perf_counter_ns()
    ref = {value: stamp for value, stamp, _ in reference if now - stamp <= window_ns}
    nat = {value: stamp for value, stamp, _ in native if now - stamp <= window_ns}
    deltas, median, deviations = phase_statistics(ref, nat, offset)
    ref_recent = [(value, stamp, step) for value, stamp, step in reference
                  if now - stamp <= window_ns]
    nat_recent = [(value, stamp, step) for value, stamp, step in native
                  if now - stamp <= window_ns]
    def observed_rate(items) -> tuple[float, float]:
        if not items:
            return 0.0, 0.0
        coverage_ns = min(window_ns, max(1, now - items[0][1]))
        coverage = coverage_ns / 1_000_000_000.0
        return len(items) / coverage, coverage

    ref_rate, ref_coverage = observed_rate(ref_recent)
    nat_rate, nat_coverage = observed_rate(nat_recent)
    current_offset = offset
    if ref_recent and nat_recent:
        current_offset = signed_u32_delta(nat_recent[-1][0], ref_recent[-1][0])
    current_deltas, current_median, current_deviations = phase_statistics(
        ref, nat, current_offset)
    return {
        "matchedEdges": len(deltas),
        "referenceEdges": len(ref_recent),
        "nativeEdges": len(nat_recent),
        "referenceHz": round(ref_rate, 6),
        "nativeHz": round(nat_rate, 6),
        "referenceCoverageSeconds": round(ref_coverage, 6),
        "nativeCoverageSeconds": round(nat_coverage, 6),
        "phaseMedianMs": round(median, 6) if median is not None else None,
        "phaseP95DeviationMs": round(percentile(deviations, 0.95), 6)
        if deviations else None,
        "phaseMaxDeviationMs": round(max(deviations), 6) if deviations else None,
        "currentMatchedEdges": len(current_deltas),
        "currentPhaseMedianMs": (round(current_median, 6)
                                 if current_median is not None else None),
        "currentPhaseP95DeviationMs": (
            round(percentile(current_deviations, 0.95), 6)
            if current_deviations else None),
        "currentPhaseMaxDeviationMs": (
            round(max(current_deviations), 6) if current_deviations else None),
        "referenceSkippedEdges": sum(1 for _, _, step in ref_recent if step != 1),
        "nativeSkippedEdges": sum(1 for _, _, step in nat_recent if step != 1),
        "offset": offset,
        "currentOffset": current_offset,
        "offsetDriftFrames": signed_u32_delta(current_offset, offset),
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--xemu-pid", type=int, required=True)
    parser.add_argument("--native-pid", type=int, required=True)
    parser.add_argument("--xbe", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--state-status", type=Path, required=True,
                        help="fresh semantic-alignment status from the state watcher")
    parser.add_argument("--status-out", type=Path,
                        help="atomically replaced current phase record")
    parser.add_argument("--hz", type=float, default=500.0)
    parser.add_argument("--window-seconds", type=float, default=5.0)
    parser.add_argument("--seconds", type=float, default=0.0,
                        help="stop after this many seconds; zero runs until a game exits")
    args = parser.parse_args()
    if not 60 <= args.hz <= 2000:
        parser.error("--hz must be in [60,2000]")
    if not 1 <= args.window_seconds <= 30:
        parser.error("--window-seconds must be in [1,30]")
    if args.seconds < 0:
        parser.error("--seconds must be non-negative")
    args.out.parent.mkdir(parents=True, exist_ok=True)
    if args.status_out:
        args.status_out.parent.mkdir(parents=True, exist_ok=True)
    if args.out.exists():
        raise FileExistsError(args.out)
    reference_reader = XemuReader(args.xemu_pid, args.xbe)
    native_reader = NativeReader(args.native_pid)
    interval = 1.0 / args.hz
    reference = EdgeSampler("reference", reference_reader, interval)
    native = EdgeSampler("native", native_reader, interval)
    initial_reference = u32(reference_reader.read_host(reference.host_address, 4))
    initial_native = u32(native_reader.read_host(native.host_address, 4))
    initial_offset = signed_u32_delta(initial_native, initial_reference)
    offset = None
    append(args.out, {"event": "run-start", "at": time.time(),
                      "xemuPid": args.xemu_pid, "nativePid": args.native_pid,
                      "sampleHz": args.hz, "windowSeconds": args.window_seconds,
                      "initialObservedOffset": initial_offset,
                      "meaning": "phase is native edge timestamp minus matching reference edge timestamp"})
    reference.start()
    native.start()
    run_started = time.perf_counter()
    try:
        next_report = time.perf_counter() + 1.0
        while reference_reader.running() and native_reader.running():
            if args.seconds and time.perf_counter() - run_started >= args.seconds:
                break
            remaining = next_report - time.perf_counter()
            if remaining > 0:
                time.sleep(min(remaining, 0.25))
                continue
            if not state_alignment_ready(args.state_status):
                if offset is not None:
                    append(args.out, {"event": "phase-baseline-reset",
                                      "at": time.time(), "offset": offset,
                                      "reason": "semantic-state-divergence-or-stale-status"})
                    offset = None
                unavailable = {
                    "event": "phase", "at": time.time(),
                    "phaseAligned": False,
                    "reason": "semantic-state-divergence-or-stale-status",
                    "referenceReadErrors": reference.read_errors,
                    "nativeReadErrors": native.read_errors,
                }
                append(args.out, unavailable)
                write_status(args.status_out, unavailable)
                next_report += 1.0
                continue
            reference_edges = reference.snapshot()
            native_edges = native.snapshot()
            window_ns = int(args.window_seconds * 1_000_000_000)
            if offset is None:
                chosen = choose_baseline_offset(reference_edges, native_edges,
                                                window_ns)
                if chosen is None:
                    next_report += 1.0
                    continue
                offset, evidence = chosen
                append(args.out, {"event": "phase-baseline", "at": time.time(),
                                  "offset": offset, **evidence})
            report = summarize(reference_edges, native_edges, offset, window_ns)
            report.update({"event": "phase", "at": time.time(),
                           "referenceReadErrors": reference.read_errors,
                           "nativeReadErrors": native.read_errors})
            tolerance_ms = max(4.0, 2000.0 / args.hz)
            report["phaseToleranceMs"] = round(tolerance_ms, 6)
            phase_median = report.get("currentPhaseMedianMs")
            phase_jitter = report.get("currentPhaseP95DeviationMs")
            report["phaseAligned"] = bool(
                report.get("currentMatchedEdges", 0) >= 30 and
                report.get("offsetDriftFrames") == 0 and
                isinstance(phase_median, (int, float)) and
                abs(phase_median) <= tolerance_ms and
                isinstance(phase_jitter, (int, float)) and
                phase_jitter <= tolerance_ms and
                abs(report.get("referenceHz", 0) - report.get("nativeHz", 0)) <= 0.1 and
                reference.read_errors == 0 and native.read_errors == 0)
            append(args.out, report)
            write_status(args.status_out, report)
            next_report += 1.0
    finally:
        reference.stop_event.set()
        native.stop_event.set()
        reference.join(timeout=2.0)
        native.join(timeout=2.0)
        append(args.out, {"event": "run-end", "at": time.time(),
                          "referenceRunning": reference_reader.running(),
                          "nativeRunning": native_reader.running()})
        reference_reader.close()
        native_reader.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
