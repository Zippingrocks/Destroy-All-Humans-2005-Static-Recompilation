#!/usr/bin/env python3
"""Capture two DAH client windows in memory and retain deduplicated mismatches."""

from __future__ import annotations

import argparse
import ctypes
import json
import time
from pathlib import Path

from PIL import Image

from frame_pair_metrics import compare_arrays, difference_image, image_array


PW_RENDERFULLCONTENT = 2
DIB_RGB_COLORS = 0
BI_RGB = 0


class Rect(ctypes.Structure):
    _fields_ = [("left", ctypes.c_long), ("top", ctypes.c_long),
                ("right", ctypes.c_long), ("bottom", ctypes.c_long)]


class Point(ctypes.Structure):
    _fields_ = [("x", ctypes.c_long), ("y", ctypes.c_long)]


class BitmapInfoHeader(ctypes.Structure):
    _fields_ = [
        ("size", ctypes.c_uint32), ("width", ctypes.c_long),
        ("height", ctypes.c_long), ("planes", ctypes.c_uint16),
        ("bitCount", ctypes.c_uint16), ("compression", ctypes.c_uint32),
        ("sizeImage", ctypes.c_uint32), ("xPelsPerMeter", ctypes.c_long),
        ("yPelsPerMeter", ctypes.c_long), ("clrUsed", ctypes.c_uint32),
        ("clrImportant", ctypes.c_uint32),
    ]


class BitmapInfo(ctypes.Structure):
    _fields_ = [("header", BitmapInfoHeader), ("colors", ctypes.c_uint32 * 3)]


user32 = ctypes.WinDLL("user32", use_last_error=True)
gdi32 = ctypes.WinDLL("gdi32", use_last_error=True)
EnumProc = ctypes.WINFUNCTYPE(ctypes.c_bool, ctypes.c_void_p, ctypes.c_void_p)
user32.EnumWindows.argtypes = [EnumProc, ctypes.c_void_p]
user32.EnumWindows.restype = ctypes.c_bool
user32.GetWindowThreadProcessId.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_uint32)]
user32.GetWindowThreadProcessId.restype = ctypes.c_uint32
user32.IsWindowVisible.argtypes = [ctypes.c_void_p]
user32.IsWindowVisible.restype = ctypes.c_bool
user32.GetWindowRect.argtypes = [ctypes.c_void_p, ctypes.POINTER(Rect)]
user32.GetWindowRect.restype = ctypes.c_bool
user32.GetClientRect.argtypes = [ctypes.c_void_p, ctypes.POINTER(Rect)]
user32.GetClientRect.restype = ctypes.c_bool
user32.ClientToScreen.argtypes = [ctypes.c_void_p, ctypes.POINTER(Point)]
user32.ClientToScreen.restype = ctypes.c_bool
user32.PrintWindow.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_uint32]
user32.PrintWindow.restype = ctypes.c_bool
user32.GetDC.argtypes = [ctypes.c_void_p]
user32.GetDC.restype = ctypes.c_void_p
user32.ReleaseDC.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
user32.ReleaseDC.restype = ctypes.c_int
gdi32.CreateCompatibleDC.argtypes = [ctypes.c_void_p]
gdi32.CreateCompatibleDC.restype = ctypes.c_void_p
gdi32.CreateDIBSection.argtypes = [ctypes.c_void_p, ctypes.POINTER(BitmapInfo),
                                   ctypes.c_uint32, ctypes.POINTER(ctypes.c_void_p),
                                   ctypes.c_void_p, ctypes.c_uint32]
gdi32.CreateDIBSection.restype = ctypes.c_void_p
gdi32.SelectObject.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
gdi32.SelectObject.restype = ctypes.c_void_p
gdi32.DeleteObject.argtypes = [ctypes.c_void_p]
gdi32.DeleteDC.argtypes = [ctypes.c_void_p]


def process_window(pid: int) -> int:
    candidates = []

    @EnumProc
    def visit(hwnd, _):
        owner = ctypes.c_uint32()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(owner))
        if owner.value == pid:
            rect = Rect()
            if user32.GetWindowRect(hwnd, ctypes.byref(rect)):
                area = max(0, rect.right - rect.left) * max(0, rect.bottom - rect.top)
                candidates.append((int(bool(user32.IsWindowVisible(hwnd))),
                                   area, int(hwnd)))
        return True

    if not user32.EnumWindows(visit, None) or not candidates:
        raise RuntimeError(f"process {pid} has no top-level window")
    return max(candidates)[2]


def capture(hwnd: int) -> Image.Image:
    window = Rect()
    client = Rect()
    origin = Point()
    if not user32.GetWindowRect(hwnd, ctypes.byref(window)):
        raise OSError(ctypes.get_last_error(), "GetWindowRect")
    if not user32.GetClientRect(hwnd, ctypes.byref(client)):
        raise OSError(ctypes.get_last_error(), "GetClientRect")
    if not user32.ClientToScreen(hwnd, ctypes.byref(origin)):
        raise OSError(ctypes.get_last_error(), "ClientToScreen")
    width, height = window.right - window.left, window.bottom - window.top
    client_width, client_height = client.right, client.bottom
    screen = user32.GetDC(None)
    memory = gdi32.CreateCompatibleDC(screen)
    bits = ctypes.c_void_p()
    info = BitmapInfo()
    info.header = BitmapInfoHeader(ctypes.sizeof(BitmapInfoHeader), width, -height,
                                   1, 32, BI_RGB, width * height * 4,
                                   0, 0, 0, 0)
    bitmap = gdi32.CreateDIBSection(screen, ctypes.byref(info), DIB_RGB_COLORS,
                                    ctypes.byref(bits), None, 0)
    if not memory or not bitmap:
        raise OSError(ctypes.get_last_error(), "CreateDIBSection")
    previous = gdi32.SelectObject(memory, bitmap)
    try:
        if not user32.PrintWindow(hwnd, memory, PW_RENDERFULLCONTENT):
            raise OSError(ctypes.get_last_error(), "PrintWindow")
        raw = ctypes.string_at(bits, width * height * 4)
        image = Image.frombuffer("RGBA", (width, height), raw, "raw", "BGRA", 0, 1).convert("RGB")
        x = origin.x - window.left
        y = origin.y - window.top
        return image.crop((x, y, x + client_width, y + client_height))
    finally:
        gdi32.SelectObject(memory, previous)
        gdi32.DeleteObject(bitmap)
        gdi32.DeleteDC(memory)
        user32.ReleaseDC(None, screen)


def latest_alignment(path: Path | None) -> dict | None:
    if not path or not path.exists():
        return None
    last = None
    with path.open(encoding="utf-8") as stream:
        for line in stream:
            try:
                row = json.loads(line)
            except json.JSONDecodeError:
                continue
            if row.get("event") == "heartbeat":
                last = row
    return last


def current_alignment(path: Path | None) -> dict | None:
    if not path or not path.exists():
        return None
    try:
        row = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None
    return row if row.get("event") == "alignment" else None


def current_phase(path: Path | None) -> dict | None:
    if not path or not path.exists():
        return None
    try:
        row = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None
    return row if row.get("event") == "phase" else None


def append(path: Path, row: dict) -> None:
    with path.open("a", encoding="utf-8", buffering=1) as stream:
        stream.write(json.dumps(row, separators=(",", ":")) + "\n")


def alignment_age_ms(alignment: dict | None) -> float | None:
    if not alignment or not isinstance(alignment.get("at"), (int, float)):
        return None
    return (time.time() - alignment["at"]) * 1000.0


def alignment_ready(alignment: dict | None, maximum_age_ms: float) -> bool:
    age = alignment_age_ms(alignment)
    return bool(alignment and alignment.get("baseline") and
                alignment.get("presentationAligned",
                              alignment.get("captureAligned",
                                            not alignment.get("divergent"))) and
                age is not None and 0 <= age <= maximum_age_ms)


def phase_ready(phase: dict | None, maximum_age_ms: float) -> bool:
    age = alignment_age_ms(phase)
    return bool(phase and phase.get("phaseAligned") is True and
                age is not None and 0 <= age <= maximum_age_ms)


def alignment_signature(alignment: dict | None) -> str | None:
    if not alignment:
        return None
    def identity(value: dict | None) -> dict:
        value = value or {}
        return {key: value.get(key) for key in (
            "backendName", "activeUiRoots", "activeMenus", "selectors",
            "selectorsComplete")}

    payload = {
        "captureAligned": alignment.get("captureAligned"),
        "presentationAligned": alignment.get("presentationAligned"),
        "semanticFields": sorted((alignment.get("semanticDiff") or {}).keys()),
        "driftFields": sorted((alignment.get("drift") or {}).keys()),
        "referenceIdentity": identity(alignment.get("referenceIdentity")),
        "nativeIdentity": identity(alignment.get("nativeIdentity")),
    }
    return json.dumps(payload, sort_keys=True, separators=(",", ":"))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-pid", type=int, required=True)
    parser.add_argument("--native-pid", type=int, required=True)
    parser.add_argument("--out-dir", type=Path, required=True)
    parser.add_argument("--state-log", type=Path)
    parser.add_argument("--state-status", type=Path,
                        help="atomic live alignment record from state watcher")
    parser.add_argument("--phase-status", type=Path,
                        help="atomic live phase record from phase watcher")
    parser.add_argument("--max-state-age-ms", type=float, default=250.0)
    parser.add_argument("--max-phase-age-ms", type=float, default=1500.0)
    parser.add_argument("--hz", type=float, default=2.0)
    parser.add_argument("--burst-hz", type=float, default=6.0)
    parser.add_argument("--burst-seconds", type=float, default=2.0)
    parser.add_argument("--seconds", type=float, default=0.0)
    parser.add_argument("--max-incidents", type=int, default=20)
    args = parser.parse_args()
    if not 0.1 <= args.hz <= 30:
        parser.error("--hz must be in [0.1,30]")
    if not args.hz <= args.burst_hz <= 30:
        parser.error("--burst-hz must be in [--hz,30]")
    if not 0 <= args.burst_seconds <= 30:
        parser.error("--burst-seconds must be in [0,30]")
    args.out_dir.mkdir(parents=True, exist_ok=True)
    log = args.out_dir / "visual-incidents.jsonl"
    if log.exists():
        parser.error(f"output log already exists: {log}")
    reference_window = process_window(args.reference_pid)
    native_window = process_window(args.native_pid)
    started = time.perf_counter()
    next_sample = started
    fingerprints = set()
    incidents = 0
    burst_until = 0.0
    last_alignment_signature = None
    last_heartbeat = 0.0
    append(log, {"event": "run-start", "at": time.time(),
                 "referencePid": args.reference_pid, "nativePid": args.native_pid,
                 "hz": args.hz, "burstHz": args.burst_hz,
                 "burstSeconds": args.burst_seconds,
                 "capture": "sequential PrintWindow client-area; no resampling",
                 "limitation": "not a shared presentation latch"})
    while not args.seconds or time.perf_counter() - started < args.seconds:
        now = time.perf_counter()
        alignment_probe = (current_alignment(args.state_status)
                           if args.state_status else latest_alignment(args.state_log))
        phase_probe = current_phase(args.phase_status)
        signature = json.dumps({"state": alignment_signature(alignment_probe),
                                "phaseAligned": (phase_probe or {}).get("phaseAligned"),
                                "phaseOffsetDriftPresent": bool(
                                    (phase_probe or {}).get("offsetDriftFrames"))},
                               sort_keys=True, separators=(",", ":"))
        if (last_alignment_signature is not None and signature != last_alignment_signature and
                args.burst_seconds):
            burst_until = now + args.burst_seconds
            next_sample = min(next_sample, now)
        if signature is not None:
            last_alignment_signature = signature
        active_hz = args.burst_hz if now < burst_until else args.hz
        if now < next_sample:
            time.sleep(min(next_sample - now, 0.02))
            continue
        next_sample = now + 1 / active_hz
        alignment_before = alignment_probe
        phase_before = phase_probe
        capture_start = time.perf_counter_ns()
        reference_image = capture(reference_window)
        split = time.perf_counter_ns()
        native_image = capture(native_window)
        capture_end = time.perf_counter_ns()
        report = compare_arrays(image_array(reference_image), image_array(native_image))
        alignment = (current_alignment(args.state_status)
                     if args.state_status else latest_alignment(args.state_log))
        phase = current_phase(args.phase_status)
        before_age_ms = alignment_age_ms(alignment_before)
        after_age_ms = alignment_age_ms(alignment)
        phase_before_age_ms = alignment_age_ms(phase_before)
        phase_after_age_ms = alignment_age_ms(phase)
        aligned = bool(alignment_ready(alignment_before, args.max_state_age_ms) and
                       alignment_ready(alignment, args.max_state_age_ms) and
                       phase_ready(phase_before, args.max_phase_age_ms) and
                       phase_ready(phase, args.max_phase_age_ms) and
                       alignment_before.get("referenceIdentity") == alignment.get("referenceIdentity") and
                       alignment_before.get("nativeIdentity") == alignment.get("nativeIdentity") and
                       alignment_before.get("offsets") == alignment.get("offsets"))
        state_failure = bool(
            (alignment_before and (alignment_before.get("divergent") or
                                   alignment_before.get("semanticDiff") or
                                   alignment_before.get("drift"))) or
            (alignment and (alignment.get("divergent") or
                            alignment.get("semanticDiff") or
                            alignment.get("drift"))))
        phase_failure = bool(
            (phase_before and (phase_before.get("offsetDriftFrames") or
                               phase_before.get("phaseAligned") is False)) or
            (phase and (phase.get("offsetDriftFrames") or
                        phase.get("phaseAligned") is False)))
        if state_failure or phase_failure:
            # Once state or phase has diverged, changing pixels are a symptom
            # of the same timing incident.  Key the evidence by failure class
            # so an animated scene produces one bounded capture instead of a
            # new image set for every luma bucket.
            fingerprint_payload = {
                "category": "state-or-phase-divergence",
                "stateSemanticFields": sorted(set(
                    (alignment_before or {}).get("semanticDiff", {})) |
                    set((alignment or {}).get("semanticDiff", {}))),
                "stateDriftFields": sorted(set(
                    (alignment_before or {}).get("drift", {})) |
                    set((alignment or {}).get("drift", {}))),
                "phaseOffsetDriftPresent": bool((phase or phase_before or {}).get(
                    "offsetDriftFrames")),
            }
        elif not report.get("comparable", False):
            fingerprint_payload = {
                "category": report.get("reason"),
                "referenceShape": report.get("referenceShape"),
                "nativeShape": report.get("nativeShape"),
                "aligned": aligned,
            }
        else:
            fingerprint_payload = {
                "category": report.get("category"),
                "dimensions": [report.get("width"), report.get("height")],
                "lumaBiasBucket": round(float(report.get("lumaBias", 0)) / 5),
                "saturationBiasBucket": round(float(report.get("saturationBias", 0)) / 0.02),
                "edgeRatioBucket": round(float(report.get("edgeEnergyRatio", 0)) / 0.1),
                "aligned": aligned,
            }
        fingerprint = __import__("hashlib").sha256(json.dumps(
            fingerprint_payload, sort_keys=True).encode()).hexdigest()[:16]
        serious = not report.get("comparable", False) or state_failure or phase_failure
        serious = serious or (aligned and not report.get("pixelExact", False))
        if serious and fingerprint not in fingerprints and incidents < args.max_incidents:
            fingerprints.add(fingerprint)
            incidents += 1
            stem = args.out_dir / f"incident-{incidents:03d}-{fingerprint}"
            reference_image.save(f"{stem}-reference.png")
            native_image.save(f"{stem}-native.png")
            if report.get("comparable") and not report.get("pixelExact"):
                difference_image(image_array(reference_image), image_array(native_image)).save(
                    f"{stem}-difference-3x.png")
            append(log, {"event": "incident", "incident": incidents,
                         "at": time.time(), "fingerprint": fingerprint,
                         "stateAligned": aligned,
                         "stateFailure": state_failure,
                         "phaseFailure": phase_failure,
                         "stateAgeBeforeMs": round(before_age_ms, 3) if before_age_ms is not None else None,
                         "stateAgeAfterMs": round(after_age_ms, 3) if after_age_ms is not None else None,
                         "phaseAgeBeforeMs": (round(phase_before_age_ms, 3)
                                              if phase_before_age_ms is not None else None),
                         "phaseAgeAfterMs": (round(phase_after_age_ms, 3)
                                             if phase_after_age_ms is not None else None),
                         "phase": phase,
                         "stateBefore": alignment_before,
                         "stateAfter": alignment,
                         "captureHz": active_hz,
                         "stateIdentity": ({
                             "reference": alignment.get("referenceIdentity"),
                             "native": alignment.get("nativeIdentity"),
                         } if alignment else None),
                         "pairCaptureUs": round((capture_end - capture_start) / 1000, 3),
                         "splitCaptureUs": round((capture_end - split) / 1000, 3),
                         "report": report, "stem": str(stem)})
        elif now - last_heartbeat >= 1.0:
            append(log, {"event": "heartbeat", "at": time.time(),
                         "stateAligned": aligned, "category": report.get("category"),
                         "stateAgeBeforeMs": round(before_age_ms, 3) if before_age_ms is not None else None,
                         "stateAgeAfterMs": round(after_age_ms, 3) if after_age_ms is not None else None,
                         "phaseAgeBeforeMs": (round(phase_before_age_ms, 3)
                                              if phase_before_age_ms is not None else None),
                         "phaseAgeAfterMs": (round(phase_after_age_ms, 3)
                                             if phase_after_age_ms is not None else None),
                         "phaseAligned": phase_ready(phase, args.max_phase_age_ms),
                         "captureHz": active_hz,
                         "comparable": report.get("comparable"),
                         "reason": report.get("reason"),
                         "referenceShape": report.get("referenceShape"),
                         "nativeShape": report.get("nativeShape"),
                         "lumaBias": report.get("lumaBias"),
                         "saturationBias": report.get("saturationBias"),
                         "changedFraction": report.get("changedFraction"),
                         "pairCaptureUs": round((capture_end - capture_start) / 1000, 3)})
            last_heartbeat = now
    append(log, {"event": "run-end", "at": time.time(), "incidents": incidents})
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
