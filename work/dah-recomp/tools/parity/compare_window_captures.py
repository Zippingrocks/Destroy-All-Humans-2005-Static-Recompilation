"""Align two game-window captures and emit quantitative and visual diffs."""

from __future__ import annotations

import argparse
from pathlib import Path

import numpy as np
from PIL import Image


def shifted(image: np.ndarray, dx: int, dy: int) -> np.ndarray:
    result = np.zeros_like(image)
    height, width = image.shape[:2]
    source_x0, source_x1 = max(0, -dx), min(width, width - dx)
    source_y0, source_y1 = max(0, -dy), min(height, height - dy)
    destination_x0, destination_x1 = max(0, dx), min(width, width + dx)
    destination_y0, destination_y1 = max(0, dy), min(height, height + dy)
    result[destination_y0:destination_y1, destination_x0:destination_x1] = image[
        source_y0:source_y1, source_x0:source_x1
    ]
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("recomp", type=Path)
    parser.add_argument("reference", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    reference_image = Image.open(args.reference).convert("RGB")
    recomp_image = Image.open(args.recomp).convert("RGB").resize(
        reference_image.size, Image.Resampling.LANCZOS
    )
    reference = np.asarray(reference_image, dtype=np.int16)
    recomp = np.asarray(recomp_image, dtype=np.int16)
    height, width = reference.shape[:2]

    # Stable room geometry, excluding both animated figures and button glyphs.
    mask = np.zeros((height, width), dtype=bool)
    mask[:250, :] = True
    mask[520:585, :] = True
    mask[250:520, :220] = True
    mask[250:520, 1080:] = True

    best = None
    for dy in range(-8, 9):
        for dx in range(-8, 9):
            candidate = shifted(recomp, dx, dy)
            valid = mask.copy()
            if dx > 0:
                valid[:, :dx] = False
            elif dx < 0:
                valid[:, dx:] = False
            if dy > 0:
                valid[:dy, :] = False
            elif dy < 0:
                valid[dy:, :] = False
            score = np.abs(candidate - reference)[valid].mean()
            if best is None or score < best[0]:
                best = (float(score), dx, dy, candidate)

    assert best is not None
    score, dx, dy, aligned = best
    delta = aligned - reference
    absolute = np.abs(delta)
    args.output.mkdir(parents=True, exist_ok=True)
    Image.fromarray(np.uint8(np.clip(aligned, 0, 255))).save(args.output / "recomp-aligned.png")
    Image.fromarray(np.uint8(np.clip(absolute * 3, 0, 255))).save(args.output / "difference-3x.png")
    overlay = np.uint8(np.clip(reference * 0.45 + aligned * 0.55, 0, 255))
    Image.fromarray(overlay).save(args.output / "overlay.png")

    regions = {
        "all": np.ones((height, width), dtype=bool),
        "room": mask,
        "left_figure": np.pad(
            np.ones((270, 350), dtype=bool), ((250, height - 520), (220, width - 570))
        ),
        "right_figure": np.pad(
            np.ones((270, 510), dtype=bool), ((250, height - 520), (570, width - 1080))
        ),
    }
    lines = [f"alignment dx={dx} dy={dy} room_mae={score:.4f}"]
    for name, region in regions.items():
        values = delta[region]
        mae = np.abs(values).mean(axis=0)
        bias = values.mean(axis=0)
        lines.append(
            f"{name} mae_rgb={mae[0]:.4f},{mae[1]:.4f},{mae[2]:.4f} "
            f"bias_rgb={bias[0]:+.4f},{bias[1]:+.4f},{bias[2]:+.4f}"
        )
    room_recomp = aligned[mask].astype(np.float64)
    room_reference = reference[mask].astype(np.float64)
    corrected_image = aligned.astype(np.float64).copy()
    for channel, label in enumerate("rgb"):
        design = np.column_stack((room_recomp[:, channel], np.ones(len(room_recomp))))
        slope, intercept = np.linalg.lstsq(design, room_reference[:, channel], rcond=None)[0]
        corrected = room_recomp[:, channel] * slope + intercept
        lines.append(
            f"room_fit_{label} reference={slope:.7f}*recomp{intercept:+.5f} "
            f"mae={np.abs(corrected-room_reference[:, channel]).mean():.4f}"
        )
        corrected_image[:, :, channel] = corrected_image[:, :, channel] * slope + intercept
    corrected_u8 = np.uint8(np.clip(corrected_image, 0, 255))
    Image.fromarray(corrected_u8).save(args.output / "recomp-room-color-fit.png")
    corrected_diff = np.abs(corrected_image-reference.astype(np.float64))
    Image.fromarray(np.uint8(np.clip(corrected_diff * 3, 0, 255))).save(
        args.output / "difference-after-room-fit-3x.png"
    )
    report = "\n".join(lines) + "\n"
    (args.output / "metrics.txt").write_text(report, encoding="utf-8")
    print(report, end="")


if __name__ == "__main__":
    main()
