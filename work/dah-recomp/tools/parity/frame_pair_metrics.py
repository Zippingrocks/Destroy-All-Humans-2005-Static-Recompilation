#!/usr/bin/env python3
"""Measure an exact-size pair of displayed DAH frames without resampling."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import numpy as np
from PIL import Image


def image_array(image: Image.Image) -> np.ndarray:
    return np.asarray(image.convert("RGB"), dtype=np.uint8)


def summary(pixels: np.ndarray) -> dict:
    values = pixels.astype(np.float64)
    maximum = values.max(axis=2)
    minimum = values.min(axis=2)
    saturation = np.divide(maximum - minimum, maximum,
                           out=np.zeros_like(maximum), where=maximum != 0)
    luma = values[:, :, 0] * 0.2126 + values[:, :, 1] * 0.7152 + values[:, :, 2] * 0.0722
    dx = np.abs(np.diff(luma, axis=1)).mean() if luma.shape[1] > 1 else 0.0
    dy = np.abs(np.diff(luma, axis=0)).mean() if luma.shape[0] > 1 else 0.0
    return {
        "sha256": hashlib.sha256(pixels.tobytes()).hexdigest(),
        "meanRgb": [round(float(x), 6) for x in values.mean(axis=(0, 1))],
        "lumaMean": round(float(luma.mean()), 6),
        "lumaStd": round(float(luma.std()), 6),
        "saturationMean": round(float(saturation.mean()), 8),
        "blackFraction": round(float(np.all(pixels <= 3, axis=2).mean()), 8),
        "darkFraction": round(float(np.all(pixels <= 20, axis=2).mean()), 8),
        "whiteFraction": round(float(np.all(pixels >= 252, axis=2).mean()), 8),
        "edgeEnergy": round(float((dx + dy) * 0.5), 6),
    }


def structural_metrics(reference: np.ndarray, native: np.ndarray) -> dict:
    reference_f = reference.astype(np.float64)
    native_f = native.astype(np.float64)
    ref_luma = (reference_f[:, :, 0] * 0.2126 + reference_f[:, :, 1] * 0.7152 +
                reference_f[:, :, 2] * 0.0722)
    native_luma = (native_f[:, :, 0] * 0.2126 + native_f[:, :, 1] * 0.7152 +
                   native_f[:, :, 2] * 0.0722)
    ref_z = (ref_luma - ref_luma.mean()) / max(ref_luma.std(), 1e-9)
    native_z = (native_luma - native_luma.mean()) / max(native_luma.std(), 1e-9)
    normalized_luma_mae = float(np.abs(native_z - ref_z).mean())

    ref_edges = np.concatenate((np.diff(ref_luma, axis=1).ravel(),
                                np.diff(ref_luma, axis=0).ravel()))
    native_edges = np.concatenate((np.diff(native_luma, axis=1).ravel(),
                                   np.diff(native_luma, axis=0).ravel()))
    ref_edges -= ref_edges.mean()
    native_edges -= native_edges.mean()
    denominator = float(np.linalg.norm(ref_edges) * np.linalg.norm(native_edges))
    edge_correlation = (float(np.dot(ref_edges, native_edges) / denominator)
                        if denominator > 1e-9 else None)

    gains, offsets = [], []
    corrected = np.empty_like(native_f)
    for channel in range(3):
        x = reference_f[:, :, channel].ravel()
        y = native_f[:, :, channel].ravel()
        variance = float(np.dot(x - x.mean(), x - x.mean()))
        gain = (float(np.dot(x - x.mean(), y - y.mean()) / variance)
                if variance > 1e-9 else 1.0)
        offset = float(y.mean() - gain * x.mean())
        gains.append(gain)
        offsets.append(offset)
        corrected[:, :, channel] = np.clip((native_f[:, :, channel] - offset) /
                                           (gain if abs(gain) > 1e-9 else 1.0), 0, 255)
    corrected_mae = np.abs(corrected - reference_f).mean(axis=(0, 1))
    raw_mae = np.abs(native_f - reference_f).mean()
    corrected_total = float(corrected_mae.mean())
    return {
        "normalizedLumaMae": round(normalized_luma_mae, 8),
        "edgeCorrelation": (round(edge_correlation, 8)
                            if edge_correlation is not None else None),
        "linearColorFit": {
            "nativeFromReferenceGainRgb": [round(value, 8) for value in gains],
            "nativeFromReferenceOffsetRgb": [round(value, 6) for value in offsets],
            "correctedMaeRgb": [round(float(value), 6) for value in corrected_mae],
            "explainedErrorFraction": round(max(0.0, 1.0 - corrected_total /
                                                  max(raw_mae, 1e-9)), 8),
        },
    }


def compare_arrays(reference: np.ndarray, native: np.ndarray) -> dict:
    if reference.shape != native.shape:
        return {
            "comparable": False,
            "reason": "dimension-mismatch",
            "referenceShape": list(reference.shape),
            "nativeShape": list(native.shape),
        }
    signed = native.astype(np.int16) - reference.astype(np.int16)
    absolute = np.abs(signed)
    changed = np.any(absolute != 0, axis=2)
    coordinates = np.argwhere(changed)
    reference_summary = summary(reference)
    native_summary = summary(native)
    structure = structural_metrics(reference, native)
    bbox = None
    if len(coordinates):
        y0, x0 = coordinates.min(axis=0)
        y1, x1 = coordinates.max(axis=0)
        bbox = [int(x0), int(y0), int(x1 + 1), int(y1 + 1)]
    category = "pixel-exact"
    native_dark_blank = (native_summary["darkFraction"] >= 0.95 and
                         native_summary["lumaStd"] < 8.0 and
                         reference_summary["lumaMean"] >= 20.0)
    reference_dark_blank = (reference_summary["darkFraction"] >= 0.95 and
                            reference_summary["lumaStd"] < 8.0 and
                            native_summary["lumaMean"] >= 20.0)
    if ((native_summary["blackFraction"] >= 0.95 and
         reference_summary["blackFraction"] < 0.95) or native_dark_blank):
        category = "native-blank"
    elif ((reference_summary["blackFraction"] >= 0.95 and
           native_summary["blackFraction"] < 0.95) or reference_dark_blank):
        category = "reference-blank"
    elif changed.any():
        luma_bias = native_summary["lumaMean"] - reference_summary["lumaMean"]
        saturation_bias = native_summary["saturationMean"] - reference_summary["saturationMean"]
        if structure["edgeCorrelation"] is not None and structure["edgeCorrelation"] < 0.85:
            category = "content-or-timing"
        elif abs(luma_bias) >= 4.0:
            category = "brightness"
        elif abs(saturation_bias) >= 0.025:
            category = "saturation"
        else:
            category = "pixels"
    return {
        "comparable": True,
        "width": int(reference.shape[1]),
        "height": int(reference.shape[0]),
        "category": category,
        "pixelExact": not changed.any(),
        "changedPixels": int(changed.sum()),
        "changedFraction": round(float(changed.mean()), 8),
        "mismatchBounds": bbox,
        "maeRgb": [round(float(x), 6) for x in absolute.mean(axis=(0, 1))],
        "biasRgb": [round(float(x), 6) for x in signed.mean(axis=(0, 1))],
        "maxChannelError": int(absolute.max()),
        "reference": reference_summary,
        "native": native_summary,
        "lumaBias": round(native_summary["lumaMean"] - reference_summary["lumaMean"], 6),
        "saturationBias": round(native_summary["saturationMean"] - reference_summary["saturationMean"], 8),
        "edgeEnergyRatio": round((native_summary["edgeEnergy"] + 1e-9) /
                                 (reference_summary["edgeEnergy"] + 1e-9), 8),
        **structure,
    }


def difference_image(reference: np.ndarray, native: np.ndarray) -> Image.Image:
    absolute = np.abs(native.astype(np.int16) - reference.astype(np.int16))
    return Image.fromarray(np.uint8(np.clip(absolute * 3, 0, 255)), "RGB")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("reference", type=Path)
    parser.add_argument("native", type=Path)
    parser.add_argument("--out", type=Path)
    parser.add_argument("--diff", type=Path)
    args = parser.parse_args()
    reference = image_array(Image.open(args.reference))
    native = image_array(Image.open(args.native))
    report = compare_arrays(reference, native)
    text = json.dumps(report, indent=2) + "\n"
    if args.out:
        args.out.parent.mkdir(parents=True, exist_ok=True)
        args.out.write_text(text, encoding="utf-8")
    else:
        print(text, end="")
    if args.diff and report.get("comparable") and not report.get("pixelExact"):
        args.diff.parent.mkdir(parents=True, exist_ok=True)
        difference_image(reference, native).save(args.diff)
    return 0 if report.get("pixelExact") else 1


if __name__ == "__main__":
    raise SystemExit(main())
