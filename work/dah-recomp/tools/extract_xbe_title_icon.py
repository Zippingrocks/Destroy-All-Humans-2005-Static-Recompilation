#!/usr/bin/env python3
"""Extract an original-Xbox XBE title image and write a Windows .ico file.

Retail Xbox title images are stored in the XBE's $$XTIMAGE section as a
128x128 DXT1 XPR0 resource.  This tool deliberately derives the Windows icon
from the user's own XBE instead of distributing the copyrighted image.
"""

from __future__ import annotations

import argparse
import struct
import zlib
from pathlib import Path


XBE_MAGIC = b"XBEH"
XPR_MAGIC = b"XPR0"
XBE_BASE_OFFSET = 0x104
XBE_SECTION_COUNT_OFFSET = 0x11C
XBE_SECTION_HEADERS_OFFSET = 0x120
XBE_SECTION_HEADER_SIZE = 56
XPR_IMAGE_HEADER_SIZE = 2048
TITLE_WIDTH = 128
TITLE_HEIGHT = 128


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def read_c_string(data: bytes, offset: int) -> str:
    end = data.find(b"\0", offset)
    if end < 0:
        raise ValueError("unterminated XBE section name")
    return data[offset:end].decode("ascii")


def extract_xtimage(xbe: bytes) -> bytes:
    if xbe[:4] != XBE_MAGIC:
        raise ValueError("input is not an Xbox XBE")

    base = u32(xbe, XBE_BASE_OFFSET)
    section_count = u32(xbe, XBE_SECTION_COUNT_OFFSET)
    table_offset = u32(xbe, XBE_SECTION_HEADERS_OFFSET) - base
    if section_count == 0 or section_count > 512:
        raise ValueError(f"invalid XBE section count: {section_count}")

    for index in range(section_count):
        entry = table_offset + index * XBE_SECTION_HEADER_SIZE
        if entry < 0 or entry + XBE_SECTION_HEADER_SIZE > len(xbe):
            raise ValueError("XBE section table is outside the file")
        raw_offset = u32(xbe, entry + 12)
        raw_size = u32(xbe, entry + 16)
        name_offset = u32(xbe, entry + 20) - base
        name = read_c_string(xbe, name_offset)
        if name == "$$XTIMAGE":
            end = raw_offset + raw_size
            if end > len(xbe):
                raise ValueError("$$XTIMAGE section is truncated")
            return xbe[raw_offset:end]

    raise ValueError("XBE has no $$XTIMAGE section")


def decode_dxt1_block(block: bytes) -> list[tuple[int, int, int, int]]:
    color0, color1, indices = struct.unpack("<HHI", block)

    def rgb565(value: int) -> tuple[int, int, int, int]:
        r5 = (value >> 11) & 31
        g6 = (value >> 5) & 63
        b5 = value & 31
        return (
            (r5 << 3) | (r5 >> 2),
            (g6 << 2) | (g6 >> 4),
            (b5 << 3) | (b5 >> 2),
            255,
        )

    c0 = rgb565(color0)
    c1 = rgb565(color1)
    if color0 > color1:
        c2 = tuple((2 * c0[i] + c1[i]) // 3 for i in range(3)) + (255,)
        c3 = tuple((c0[i] + 2 * c1[i]) // 3 for i in range(3)) + (255,)
    else:
        c2 = tuple((c0[i] + c1[i]) // 2 for i in range(3)) + (255,)
        c3 = (0, 0, 0, 0)
    palette = (c0, c1, c2, c3)
    return [palette[(indices >> (2 * i)) & 3] for i in range(16)]


def decode_title_xpr(xpr: bytes) -> bytes:
    if len(xpr) < XPR_IMAGE_HEADER_SIZE or xpr[:4] != XPR_MAGIC:
        raise ValueError("$$XTIMAGE is not an XPR0 resource")
    total_size = u32(xpr, 4)
    header_size = u32(xpr, 8)
    expected_data_size = TITLE_WIDTH * TITLE_HEIGHT // 2
    if total_size > len(xpr) or header_size != XPR_IMAGE_HEADER_SIZE:
        raise ValueError("unsupported or truncated title-image XPR0 header")
    payload = xpr[header_size:total_size]
    if len(payload) != expected_data_size:
        raise ValueError(
            f"unsupported title image payload size {len(payload)}; "
            f"expected {expected_data_size} bytes of 128x128 DXT1"
        )

    rgba = bytearray(TITLE_WIDTH * TITLE_HEIGHT * 4)
    cursor = 0
    for block_y in range(TITLE_HEIGHT // 4):
        for block_x in range(TITLE_WIDTH // 4):
            pixels = decode_dxt1_block(payload[cursor:cursor + 8])
            cursor += 8
            for py in range(4):
                for px in range(4):
                    x = block_x * 4 + px
                    y = block_y * 4 + py
                    dst = (y * TITLE_WIDTH + x) * 4
                    rgba[dst:dst + 4] = bytes(pixels[py * 4 + px])
    return bytes(rgba)


def resize_rgba(source: bytes, width: int, height: int, size: int) -> bytes:
    if width == size and height == size:
        return source
    result = bytearray(size * size * 4)
    for y in range(size):
        sy = ((y + 0.5) * height / size) - 0.5
        y0 = max(0, min(height - 1, int(sy)))
        y1 = min(height - 1, y0 + 1)
        fy = max(0.0, sy - y0)
        for x in range(size):
            sx = ((x + 0.5) * width / size) - 0.5
            x0 = max(0, min(width - 1, int(sx)))
            x1 = min(width - 1, x0 + 1)
            fx = max(0.0, sx - x0)
            for channel in range(4):
                p00 = source[(y0 * width + x0) * 4 + channel]
                p10 = source[(y0 * width + x1) * 4 + channel]
                p01 = source[(y1 * width + x0) * 4 + channel]
                p11 = source[(y1 * width + x1) * 4 + channel]
                top = p00 + (p10 - p00) * fx
                bottom = p01 + (p11 - p01) * fx
                result[(y * size + x) * 4 + channel] = round(
                    top + (bottom - top) * fy
                )
    return bytes(result)


def png_chunk(kind: bytes, payload: bytes) -> bytes:
    return (
        struct.pack(">I", len(payload))
        + kind
        + payload
        + struct.pack(">I", zlib.crc32(kind + payload) & 0xFFFFFFFF)
    )


def encode_png(rgba: bytes, size: int) -> bytes:
    rows = bytearray()
    stride = size * 4
    for y in range(size):
        rows.append(0)
        rows.extend(rgba[y * stride:(y + 1) * stride])
    header = struct.pack(">IIBBBBB", size, size, 8, 6, 0, 0, 0)
    return (
        b"\x89PNG\r\n\x1a\n"
        + png_chunk(b"IHDR", header)
        + png_chunk(b"IDAT", zlib.compress(bytes(rows), 9))
        + png_chunk(b"IEND", b"")
    )


def make_ico(source: bytes) -> bytes:
    sizes = (16, 20, 24, 32, 40, 48, 64, 128, 256)
    images = [
        encode_png(resize_rgba(source, TITLE_WIDTH, TITLE_HEIGHT, size), size)
        for size in sizes
    ]
    directory_size = 6 + len(sizes) * 16
    entries = bytearray(struct.pack("<HHH", 0, 1, len(sizes)))
    offset = directory_size
    for size, image in zip(sizes, images):
        encoded_size = 0 if size == 256 else size
        entries.extend(
            struct.pack(
                "<BBBBHHII",
                encoded_size,
                encoded_size,
                0,
                0,
                1,
                32,
                len(image),
                offset,
            )
        )
        offset += len(image)
    return bytes(entries) + b"".join(images)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("xbe", type=Path, help="path to the original default.xbe")
    parser.add_argument("ico", type=Path, help="output Windows icon path")
    parser.add_argument("--png", type=Path, help="optional 128x128 preview PNG")
    args = parser.parse_args()

    source = decode_title_xpr(extract_xtimage(args.xbe.read_bytes()))
    args.ico.parent.mkdir(parents=True, exist_ok=True)
    args.ico.write_bytes(make_ico(source))
    if args.png:
        args.png.parent.mkdir(parents=True, exist_ok=True)
        args.png.write_bytes(encode_png(source, TITLE_WIDTH))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
