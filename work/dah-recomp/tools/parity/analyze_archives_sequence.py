"""Measure persistent Archives material differences across live frame sequences."""

from __future__ import annotations

import argparse
from pathlib import Path

import numpy as np
from PIL import Image, ImageDraw


def load(path: Path, size: tuple[int, int]) -> np.ndarray:
    return np.asarray(Image.open(path).convert("RGB").resize(size, Image.Resampling.LANCZOS))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("directory", type=Path)
    args = parser.parse_args()
    recomp_paths = sorted(args.directory.glob("recomp-*.png"))
    xemu_paths = sorted(args.directory.glob("xemu-*.png"))
    if not recomp_paths or len(recomp_paths) != len(xemu_paths):
        raise SystemExit("Need paired recomp and xemu captures.")
    size = Image.open(xemu_paths[0]).size
    panels = []
    print("frame side left_red right_red mean_rgb")
    for index, (recomp_path, xemu_path) in enumerate(zip(recomp_paths, xemu_paths), 1):
        for side, path in (("recomp", recomp_path), ("xemu", xemu_path)):
            pixels = load(path, size)
            left = pixels[300:410, 300:450]
            right = pixels[300:410, 830:980]
            red = lambda crop: int(
                ((crop[:, :, 0] > 100) &
                 (crop[:, :, 0] > crop[:, :, 1] * 1.45) &
                 (crop[:, :, 0] > crop[:, :, 2] * 1.45)).sum()
            )
            print(
                f"{index} {side} {red(left)} {red(right)} "
                f"{pixels.mean(axis=(0,1))[0]:.3f},"
                f"{pixels.mean(axis=(0,1))[1]:.3f},"
                f"{pixels.mean(axis=(0,1))[2]:.3f}"
            )
            image = Image.fromarray(pixels)
            draw = ImageDraw.Draw(image)
            draw.text((8, 8), f"{side} {index}", fill=(255, 255, 0))
            panels.append(image)
    sheet = Image.new("RGB", (size[0] * 2, size[1] * len(recomp_paths)))
    for row in range(len(recomp_paths)):
        sheet.paste(panels[row * 2], (0, row * size[1]))
        sheet.paste(panels[row * 2 + 1], (size[0], row * size[1]))
    sheet.save(args.directory / "contact-sheet.png")


if __name__ == "__main__":
    main()
