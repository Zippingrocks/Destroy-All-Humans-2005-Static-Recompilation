#!/usr/bin/env python3
"""Validate a DAH player recording and emit the shared native/xemu route."""

from __future__ import annotations

import argparse
from dataclasses import dataclass
from pathlib import Path
import struct


MAGIC = b"DAHREC1\0"
VERSION = 1
HEADER = struct.Struct("<8s6I3f5I")
# The C recording sample has two bytes of tail padding for its uint32_t
# alignment in addition to the explicit three-byte reserved field.
SAMPLE = struct.Struct("<IIH8BhhhhB3x2x")
CHECKSUM_SEED = 2166136261
EVENT_LIMIT = 4096


@dataclass(frozen=True, slots=True)
class Recording:
    samples: tuple[tuple[int, ...], ...]
    start_position: tuple[float, float, float]
    checksum: int


def _checksum(payload: bytes) -> int:
    value = CHECKSUM_SEED
    for byte in payload:
        value ^= byte
        value = (value * 16777619) & 0xFFFFFFFF
    return value


def read_recording(path: Path) -> Recording:
    payload = path.read_bytes()
    if len(payload) < HEADER.size:
        raise ValueError(f"{path}: truncated header")
    fields = HEADER.unpack_from(payload)
    magic, version, header_size, sample_size, sample_count, checksum, flags = fields[:7]
    if magic != MAGIC:
        raise ValueError(f"{path}: invalid DAHREC1 magic")
    if version != VERSION or header_size != HEADER.size or sample_size != SAMPLE.size:
        raise ValueError(
            f"{path}: unsupported layout version={version} header={header_size} sample={sample_size}"
        )
    if flags != 0:
        raise ValueError(f"{path}: unsupported recording flags 0x{flags:08X}")
    if not 1 <= sample_count <= 5_000_000:
        raise ValueError(f"{path}: invalid sample count {sample_count}")
    samples_end = header_size + sample_count * sample_size
    if len(payload) < samples_end:
        raise ValueError(f"{path}: truncated samples ({len(payload)} < {samples_end})")
    sample_bytes = payload[header_size:samples_end]
    actual_checksum = _checksum(sample_bytes)
    if actual_checksum != checksum:
        raise ValueError(
            f"{path}: checksum mismatch expected={checksum:08X} actual={actual_checksum:08X}"
        )
    samples = tuple(SAMPLE.iter_unpack(sample_bytes))
    previous = -1
    for index, sample in enumerate(samples):
        loop_delta, _packet, buttons, *rest = sample
        port = rest[-1]
        if loop_delta <= previous:
            raise ValueError(
                f"{path}: sample {index} loop {loop_delta} is not strictly increasing"
            )
        if buttons > 0xFFFF or port > 3:
            raise ValueError(f"{path}: sample {index} contains an invalid pad state")
        previous = loop_delta
    return Recording(samples, tuple(fields[7:10]), checksum)


def _pad(sample: tuple[int, ...]) -> tuple[int, ...]:
    # Exclude loop, packet, and port. The remaining order is the common route
    # contract: buttons; A/B/X/Y/black/white/LT/RT; LX/LY/RX/RY.
    return (sample[2], *sample[3:15])


def _neutral(pad: tuple[int, ...]) -> bool:
    return all(value == 0 for value in pad)


def convert(recording: Recording) -> str:
    samples = recording.samples
    spans: list[tuple[int, int, tuple[int, ...]]] = []
    span_start = samples[0][0]
    span_pad = _pad(samples[0])
    previous_loop = samples[0][0]
    for sample in samples[1:]:
        loop = sample[0]
        pad = _pad(sample)
        if pad != span_pad or loop != previous_loop + 1:
            spans.append((span_start, previous_loop + 1, span_pad))
            span_start, span_pad = loop, pad
        previous_loop = loop
    spans.append((span_start, previous_loop + 1, span_pad))

    active = [(start, end, pad) for start, end, pad in spans if not _neutral(pad)]
    if len(active) > EVENT_LIMIT:
        raise ValueError(
            f"recording needs {len(active)} non-neutral spans; adapter limit is {EVENT_LIMIT}"
        )
    origin = samples[0][0]
    x, y, z = recording.start_position
    lines = [
        "# Generated losslessly from a validated DAHREC1 recording.",
        f"# samples={len(samples)} checksum={recording.checksum:08X} origin_loop={origin}",
        f"# recorded_start_position={x:.9g},{y:.9g},{z:.9g}",
        "# start duration hex_buttons A B LX LY RX RY X Y BLACK WHITE LT RT",
        "@relative-frame",
    ]
    for start, end, pad in active:
        buttons, a, b, x_button, y_button, black, white, lt, rt, lx, ly, rx, ry = pad
        lines.append(
            f"{start - origin} {end - start} {buttons:X} {a} {b} "
            f"{lx} {ly} {rx} {ry} {x_button} {y_button} {black} {white} {lt} {rt}"
        )
    return "\n".join(lines) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("recording", type=Path)
    parser.add_argument("out", type=Path)
    args = parser.parse_args()
    if args.out.exists():
        parser.error("output must be new")
    recording = read_recording(args.recording)
    route = convert(recording)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(route, encoding="utf-8")
    print(
        f"wrote {args.out} samples={len(recording.samples)} "
        f"events={max(0, route.count(chr(10)) - 5)} checksum={recording.checksum:08X}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
