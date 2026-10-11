#!/usr/bin/env python3
"""Measure whether a reference image lies between two adjacent captures."""

import argparse

import numpy as np
from PIL import Image


def load(path: str) -> np.ndarray:
    return np.asarray(Image.open(path).convert("RGB"), dtype=np.float32)


def report(name: str, target: np.ndarray, before: np.ndarray,
           after: np.ndarray, mask: np.ndarray) -> None:
    target = target[mask]
    before = before[mask]
    after = after[mask]
    delta = after - before
    denominator = float(np.sum(delta * delta))
    alpha = float(np.sum((target - before) * delta) / denominator)
    alpha = min(1.0, max(0.0, alpha))
    best_alpha = 0.0
    best_mae = float("inf")
    for candidate in np.linspace(0.0, 1.0, 1001):
        blended = before + candidate * delta
        mae = float(np.mean(np.abs(blended - target)))
        if mae < best_mae:
            best_mae = mae
            best_alpha = float(candidate)
    before_mae = float(np.mean(np.abs(before - target)))
    after_mae = float(np.mean(np.abs(after - target)))
    print(f"{name}: least-squares alpha={alpha:.6f}; "
          f"MAE-best alpha={best_alpha:.3f} MAE={best_mae:.6f}; "
          f"before={before_mae:.6f} after={after_mae:.6f}")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("reference")
    parser.add_argument("before")
    parser.add_argument("after")
    args = parser.parse_args()
    reference, before, after = map(load,
                                   (args.reference, args.before, args.after))
    if reference.shape != before.shape or reference.shape != after.shape:
        raise SystemExit(f"image dimensions differ: {reference.shape}, "
                         f"{before.shape}, {after.shape}")
    height, width, _ = reference.shape
    all_pixels = np.ones((height, width), dtype=bool)
    center = np.zeros((height, width), dtype=bool)
    center[height // 6:height * 5 // 6, width // 6:width * 5 // 6] = True
    report("full", reference, before, after, all_pixels)
    report("center", reference, before, after, center)
    report("outer", reference, before, after, ~center)


if __name__ == "__main__":
    main()
