"""Measure captured movie transition frames and reject white-frame regressions."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

import numpy as np
from PIL import Image


FRAME_NUMBER = re.compile(r"_(\d+)\.bmp$", re.IGNORECASE)


def frame_number(path: Path) -> int:
    match = FRAME_NUMBER.search(path.name)
    if not match:
        raise ValueError(f"frame filename has no numeric suffix: {path.name}")
    return int(match.group(1))


def classify(rgb: np.ndarray) -> tuple[str, float, float]:
    black_fraction = float(np.mean(np.max(rgb, axis=2) <= 2))
    white_fraction = float(np.mean(np.min(rgb, axis=2) >= 253))
    if black_fraction >= 0.999:
        return "black", black_fraction, white_fraction
    if white_fraction >= 0.999:
        return "white", black_fraction, white_fraction
    return "content", black_fraction, white_fraction


def longest_run(records: list[dict[str, object]], label: str) -> list[dict[str, object]]:
    best: list[dict[str, object]] = []
    current: list[dict[str, object]] = []
    for record in records:
        if record["class"] == label:
            current.append(record)
            if len(current) > len(best):
                best = current.copy()
        else:
            current.clear()
    return best


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("directory", type=Path)
    parser.add_argument("pattern", help="frame glob, for example dah_frame_59036_*.bmp")
    parser.add_argument("--expected-black-run", type=int)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()

    paths = sorted(args.directory.glob(args.pattern), key=frame_number)
    if not paths:
        raise SystemExit(f"no frames matched {args.directory / args.pattern}")

    records: list[dict[str, object]] = []
    for path in paths:
        rgb = np.asarray(Image.open(path).convert("RGB"), dtype=np.uint8)
        label, black_fraction, white_fraction = classify(rgb)
        records.append(
            {
                "frame": frame_number(path),
                "file": path.name,
                "class": label,
                "blackFraction": round(black_fraction, 9),
                "whiteFraction": round(white_fraction, 9),
                "meanRgb": [round(float(value), 4) for value in rgb.mean(axis=(0, 1))],
                "rgbSha256": hashlib.sha256(rgb.tobytes()).hexdigest(),
            }
        )

    black_run = longest_run(records, "black")
    white_frames = [record["frame"] for record in records if record["class"] == "white"]
    transitions = [
        {
            "frame": records[index]["frame"],
            "from": records[index - 1]["class"],
            "to": records[index]["class"],
        }
        for index in range(1, len(records))
        if records[index]["class"] != records[index - 1]["class"]
    ]
    report = {
        "frames": records,
        "longestBlackRun": {
            "count": len(black_run),
            "first": black_run[0]["frame"] if black_run else None,
            "last": black_run[-1]["frame"] if black_run else None,
        },
        "whiteFrames": white_frames,
        "transitions": transitions,
    }
    encoded = json.dumps(report, indent=2) + "\n"
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(encoded, encoding="utf-8")
    print(encoded, end="")

    failed = bool(white_frames)
    if args.expected_black_run is not None:
        failed |= len(black_run) != args.expected_black_run
    if failed:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
