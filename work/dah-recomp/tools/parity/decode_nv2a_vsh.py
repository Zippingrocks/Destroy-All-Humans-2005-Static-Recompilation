#!/usr/bin/env python3
"""Decode captured NV2A vertex microcode using xemu's documented bit layout."""

import argparse
import re
from pathlib import Path

MAC = ["NOP", "MOV", "MUL", "ADD", "MAD", "DP3", "DPH", "DP4",
       "DST", "MIN", "MAX", "SLT", "SGE", "ARL"]
ILU = ["NOP", "MOV", "RCP", "RCC", "RSQ", "EXP", "LOG", "LIT"]
OUT = ["oPos", "?1", "?2", "oD0", "oD1", "oFog", "oPts", "oB0",
       "oB1", "oT0", "oT1", "oT2", "oT3", "?13", "?14", "A0.x"]
MAC_ARGS = [0, 1, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1]


def bits(word, start, count):
    return (word >> start) & ((1 << count) - 1)


def creg(encoded):
    return ((((encoded >> 5) & 7) - 3) * 32) + (encoded & 31) + 96


def swizzle(values, scalar=False):
    chars = "xyzw"
    if scalar:
        values = [values[0]] * 4
    text = "".join(chars[x] for x in values)
    if text == "xyzw":
        return ""
    if len(set(text)) == 1:
        return "." + text[0]
    while len(text) > 1 and text[-1] == text[-2]:
        text = text[:-1]
    return "." + text


def mask(value):
    return "." + "".join(c for bit, c in zip((8, 4, 2, 1), "xyzw") if value & bit)


def decode_source(words, which, ilu_scalar=False):
    w1, w2, w3 = words[1], words[2], words[3]
    const = bits(w1, 13, 8)
    vertex = bits(w1, 9, 4)
    if which == "A":
        neg = bits(w1, 8, 1)
        swz = [bits(w1, 6, 2), bits(w1, 4, 2), bits(w1, 2, 2), bits(w1, 0, 2)]
        reg, mux = bits(w2, 28, 4), bits(w2, 26, 2)
    elif which == "B":
        neg = bits(w2, 25, 1)
        swz = [bits(w2, 23, 2), bits(w2, 21, 2), bits(w2, 19, 2), bits(w2, 17, 2)]
        reg, mux = bits(w2, 13, 4), bits(w2, 11, 2)
    else:
        neg = bits(w2, 10, 1)
        swz = [bits(w2, 8, 2), bits(w2, 6, 2), bits(w2, 4, 2), bits(w2, 2, 2)]
        reg = (bits(w2, 0, 2) << 2) | bits(w3, 30, 2)
        mux = bits(w3, 28, 2)
    names = {1: f"R{reg}", 2: f"v{vertex}", 3: f"c[{creg(const)}]"}
    name = names.get(mux, f"?mux{mux}")
    return ("-" if neg else "") + name + swizzle(swz, ilu_scalar)


def destination(words, pipe):
    w3 = words[3]
    r = bits(w3, 20, 4)
    omask = bits(w3, 12, 4)
    rm = bits(w3, 24 if pipe == "MAC" else 16, 4)
    mux = bits(w3, 2, 1)
    outputs = []
    if rm:
        rr = 1 if pipe == "ILU" and bits(words[1], 21, 4) else r
        outputs.append(f"R{rr}{mask(rm)}")
    if omask and mux == (0 if pipe == "MAC" else 1):
        if bits(w3, 11, 1):
            outputs.append(f"{OUT[bits(w3, 3, 8) & 15]}{mask(omask)}")
        else:
            outputs.append(f"c[{creg(bits(w3, 3, 8))}]{mask(omask)}")
    return ", ".join(outputs) or "_"


def decode_instruction(index, words):
    w1, w3 = words[1], words[3]
    mac = bits(w1, 21, 4)
    ilu = bits(w1, 25, 3)
    lines = []
    a = decode_source(words, "A")
    b = decode_source(words, "B")
    c = decode_source(words, "C")
    if mac:
        args = [a, b, c][:MAC_ARGS[mac]]
        if mac == 3:
            args = [a, c]
        lines.append(f"{MAC[mac]} {destination(words, 'MAC')}, " + ", ".join(args))
    if ilu:
        scalar = ilu in (2, 3, 4, 5, 6)
        lines.append(f"{ILU[ilu]} {destination(words, 'ILU')}, " + decode_source(words, "C", scalar))
    flag = " END" if bits(w3, 0, 1) else ""
    return f"{index:02d}: " + " | ".join(lines) + flag


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("path", nargs="?", type=Path)
    args = parser.parse_args()
    if args.path:
        text = args.path.read_text(encoding="utf-8", errors="replace")
        captures = re.findall(
            r"word=([0-9A-Fa-f]{8}),([0-9A-Fa-f]{8}),([0-9A-Fa-f]{8}),([0-9A-Fa-f]{8})",
            text,
        )
        values = ([int(x, 16) for row in captures for x in row] if captures else
                  [int(x, 16) for x in re.findall(r"\b[0-9A-Fa-f]{8}\b", text)])
    else:
        values = [
            0x00000000,0x0048421B,0x2C003000,0x2F000000,0x00000000,0x00C4801B,0x08369800,0x28B00000,
            0x00000000,0x0088221B,0x1CAA306C,0x1F000000,0x00000000,0x0088021B,0x0D54306C,0x1F000000,
            0x00000000,0x00C4A01B,0x0836B800,0x24B00000,0x00000000,0x0337601B,0x04377BFE,0xFF003854,
            0x00000000,0x00C4C01B,0x0836D800,0x22B00000,0x00000000,0x0157A01B,0x0437B800,0x2F000000,
            0x00000000,0x0046201B,0x1C000800,0x2FA00000,0x00000000,0x0086401B,0x2CAA086E,0x9FA00000,
            0x00000000,0x0086601B,0x3D54086E,0x9FA00000,0x00000000,0x0085E01B,0xFDFE086E,0x9FA00000,
            0x00000000,0x00C4E01B,0x0836F800,0x21B01800,0x00000000,0x0066001B,0xA400106C,0x3FA00000,
            0x00000000,0x0040401A,0xB4345800,0x2090E800,0x00000000,0x0649801B,0xA4379BFE,0xDF080000,
            0x00000000,0x00A3021A,0x18351800,0x28400000,0x00000000,0x0069A01B,0x0400106F,0x7F200000,
            0x00000000,0x00A3221A,0x18353800,0x24400000,0x00000000,0x0242801A,0x2434986C,0x9E20181C,
            0x00000000,0x0080201A,0xC4002868,0x70B0E800,0x00000000,0x00E9C41B,0x2837D800,0x20B08848,
            0x00000000,0x00E9E41B,0x2837F800,0x20B04848,0x00000000,0x00E7001B,0x08371800,0x20B0F828,
            0x00000000,0x0097C015,0x442BD857,0xB0B0C850,0x00000000,0x0062601A,0x24001068,0xF0B0E819,
        ]
    if len(values) % 4:
        raise SystemExit(f"expected a multiple of four DWORDs, got {len(values)}")
    for i in range(len(values) // 4):
        print(decode_instruction(i, values[i*4:i*4+4]))


if __name__ == "__main__":
    main()
