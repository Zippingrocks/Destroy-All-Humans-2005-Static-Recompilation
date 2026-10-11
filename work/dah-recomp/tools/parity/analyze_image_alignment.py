#!/usr/bin/env python3
"""Find the integer translation that minimizes RGB MAE between two images."""

import argparse

import numpy as np
from PIL import Image


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("reference")
    parser.add_argument("candidate")
    parser.add_argument("--flip-candidate-y", action="store_true")
    parser.add_argument("--radius", type=int, default=40)
    parser.add_argument("--step", type=int, default=1)
    args = parser.parse_args()
    reference = np.asarray(Image.open(args.reference).convert("RGB"),
                           dtype=np.float32)
    candidate = np.asarray(Image.open(args.candidate).convert("RGB"),
                           dtype=np.float32)
    if args.flip_candidate_y:
        candidate = np.flipud(candidate)
    if reference.shape != candidate.shape:
        raise SystemExit("image dimensions differ")
    height, width, _ = reference.shape
    best = (float("inf"), 0, 0)
    for dy in range(-args.radius, args.radius + 1, args.step):
        for dx in range(-args.radius, args.radius + 1, args.step):
            left = reference[max(0, dy):min(height, height + dy),
                             max(0, dx):min(width, width + dx)]
            right = candidate[max(0, -dy):min(height, height - dy),
                              max(0, -dx):min(width, width - dx)]
            mae = float(np.mean(np.abs(left - right)))
            best = min(best, (mae, dx, dy))
    print(f"best MAE={best[0]:.6f} dx={best[1]} dy={best[2]}")


if __name__ == "__main__":
    main()
