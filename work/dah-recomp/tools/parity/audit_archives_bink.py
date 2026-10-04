#!/usr/bin/env python3
"""Validate every packaged Bink movie without needing the proprietary decoder."""

from __future__ import annotations

import argparse
import json
import struct
from pathlib import Path


HEADER_SIZE = 44


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def audit_movie(path: Path) -> dict[str, object]:
    size = path.stat().st_size
    with path.open("rb") as stream:
        header = stream.read(HEADER_SIZE)
        if len(header) != HEADER_SIZE:
            return {"file": path.name, "size_bytes": size, "ok": False,
                    "errors": ["truncated Bink header"]}

        signature = header[:4].decode("ascii", errors="replace")
        declared_size = u32(header, 4) + 8
        frame_count = u32(header, 8)
        largest_frame = u32(header, 12)
        secondary_frame_count = u32(header, 16)
        width = u32(header, 20)
        height = u32(header, 24)
        fps_numerator = u32(header, 28)
        fps_denominator = u32(header, 32)
        flags = u32(header, 36)
        audio_tracks = u32(header, 40)

        errors: list[str] = []
        if not signature.startswith("BIK"):
            errors.append(f"unexpected signature {signature!r}")
        if declared_size != size:
            errors.append(f"declared size {declared_size} != file size {size}")
        if frame_count == 0 or secondary_frame_count == 0:
            errors.append("zero frame count")
        if not (1 <= width <= 8192 and 1 <= height <= 8192):
            errors.append(f"invalid dimensions {width}x{height}")
        if fps_numerator == 0 or fps_denominator == 0:
            errors.append("invalid frame rate")
        if audio_tracks > 256:
            errors.append(f"implausible audio-track count {audio_tracks}")

        index_offset = HEADER_SIZE + audio_tracks * 12
        index_bytes = (frame_count + 1) * 4
        index_end = index_offset + index_bytes
        if index_end > size:
            errors.append("frame index extends past end of file")
            offsets: list[int] = []
        else:
            stream.seek(index_offset)
            raw_index = stream.read(index_bytes)
            offsets = [value & ~1 for value in struct.unpack(
                f"<{frame_count + 1}I", raw_index)]
            if offsets[0] < index_end:
                errors.append(
                    f"first frame offset {offsets[0]} precedes index end {index_end}")
            elif offsets[0] > index_end:
                stream.seek(index_end)
                if any(stream.read(offsets[0] - index_end)):
                    errors.append("nonzero data between frame index and first frame")
            if offsets[-1] != size:
                errors.append(f"final frame offset {offsets[-1]} != file size {size}")
            if any(left > right for left, right in zip(offsets, offsets[1:])):
                errors.append("frame offsets are not monotonic")
            if offsets and max(
                    (right - left for left, right in zip(offsets, offsets[1:])),
                    default=0) > largest_frame:
                errors.append("frame payload exceeds declared largest-frame size")

    return {
        "file": path.name,
        "signature": signature,
        "size_bytes": size,
        "declared_size_bytes": declared_size,
        "frame_count": frame_count,
        "secondary_frame_count": secondary_frame_count,
        "largest_frame_bytes": largest_frame,
        "width": width,
        "height": height,
        "fps_numerator": fps_numerator,
        "fps_denominator": fps_denominator,
        "fps": round(fps_numerator / fps_denominator, 6)
        if fps_denominator else None,
        "flags": flags,
        "audio_tracks": audio_tracks,
        "indexed_payload_bytes": offsets[-1] - offsets[0] if offsets else None,
        "ok": not errors,
        "errors": errors,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("movie_dir", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()

    movies = [audit_movie(path) for path in sorted(args.movie_dir.glob("*.bik"))]
    report = {
        "movie_directory": str(args.movie_dir),
        "movie_count": len(movies),
        "passed": sum(bool(movie["ok"]) for movie in movies),
        "failed": sum(not bool(movie["ok"]) for movie in movies),
        "movies": movies,
    }
    rendered = json.dumps(report, indent=2) + "\n"
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(rendered, encoding="utf-8")
    print(rendered, end="")
    return 0 if movies and report["failed"] == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
