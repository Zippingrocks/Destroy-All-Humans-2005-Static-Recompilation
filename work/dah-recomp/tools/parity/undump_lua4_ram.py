#!/usr/bin/env python3
"""Extract and disassemble a stock Lua 4 binary chunk embedded in a RAM dump."""

from __future__ import annotations

import argparse
import struct
from dataclasses import dataclass
from pathlib import Path


OPS = [
    "END", "RETURN", "CALL", "TAILCALL", "PUSHNIL", "POP", "PUSHINT",
    "PUSHSTRING", "PUSHNUM", "PUSHNEGNUM", "PUSHUPVALUE", "GETLOCAL",
    "GETGLOBAL", "GETTABLE", "GETDOTTED", "GETINDEXED", "PUSHSELF",
    "CREATETABLE", "SETLOCAL", "SETGLOBAL", "SETTABLE", "SETLIST",
    "SETMAP", "ADD", "ADDI", "SUB", "MULT", "DIV", "POW", "CONCAT",
    "MINUS", "NOT", "JMPNE", "JMPEQ", "JMPLT", "JMPLE", "JMPGT",
    "JMPGE", "JMPT", "JMPF", "JMPONT", "JMPONF", "JMP", "PUSHNILJMP",
    "FORPREP", "FORLOOP", "LFORPREP", "LFORLOOP", "CLOSURE",
]
AB_OPS = {2, 3, 20, 21, 48}
S_OPS = {6, 24, *range(32, 43), 44, 45, 46, 47}
STRING_OPS = {7, 12, 14, 16, 19}
NUMBER_OPS = {8, 9}
PROTO_OPS = {48}


@dataclass
class Proto:
    source: str | None
    line: int
    params: int
    vararg: int
    stack: int
    locals: list[tuple[str | None, int, int]]
    lines: list[int]
    strings: list[str | None]
    numbers: list[float]
    protos: list["Proto"]
    code: list[int]


class Reader:
    def __init__(self, data: bytes, pos: int):
        self.data = data
        self.pos = pos
        self.int_size = 4
        self.size_size = 4
        self.insn_size = 4
        self.num_size = 4
        self.endian = "<"

    def take(self, count: int) -> bytes:
        out = self.data[self.pos:self.pos + count]
        if len(out) != count:
            raise EOFError(f"truncated at 0x{self.pos:X}")
        self.pos += count
        return out

    def byte(self) -> int:
        return self.take(1)[0]

    def integer(self) -> int:
        fmt = {1: "b", 2: "h", 4: "i", 8: "q"}[self.int_size]
        return struct.unpack(self.endian + fmt, self.take(self.int_size))[0]

    def size(self) -> int:
        fmt = {1: "B", 2: "H", 4: "I", 8: "Q"}[self.size_size]
        return struct.unpack(self.endian + fmt, self.take(self.size_size))[0]

    def number(self) -> float:
        fmt = {4: "f", 8: "d"}[self.num_size]
        return struct.unpack(self.endian + fmt, self.take(self.num_size))[0]

    def string(self) -> str | None:
        count = self.size()
        if count == 0:
            return None
        raw = self.take(count)
        return raw[:-1].decode("latin-1", "replace")

    def header(self) -> None:
        if self.take(4) != b"\x1bLua":
            raise ValueError("not a Lua chunk")
        version = self.byte()
        endian = self.byte()
        self.endian = "<" if endian == 1 else ">"
        self.int_size = self.byte()
        self.size_size = self.byte()
        self.insn_size = self.byte()
        bits, op_bits, b_bits = self.byte(), self.byte(), self.byte()
        self.num_size = self.byte()
        self.take(self.num_size)
        if version != 0x40 or (bits, op_bits, b_bits) != (32, 6, 9):
            raise ValueError(f"unexpected Lua VM format {version=:x} {(bits, op_bits, b_bits)=}")

    def proto(self) -> Proto:
        source = self.string()
        line = self.integer()
        params = self.integer()
        vararg = self.byte()
        stack = self.integer()
        locals_ = [(self.string(), self.integer(), self.integer()) for _ in range(self.integer())]
        lines = [self.integer() for _ in range(self.integer())]
        strings = [self.string() for _ in range(self.integer())]
        numbers = [self.number() for _ in range(self.integer())]
        protos = [self.proto() for _ in range(self.integer())]
        count = self.integer()
        fmt = {2: "H", 4: "I", 8: "Q"}[self.insn_size]
        code = list(struct.unpack(self.endian + fmt * count, self.take(count * self.insn_size)))
        return Proto(source, line, params, vararg, stack, locals_, lines,
                     strings, numbers, protos, code)


def walk(proto: Proto, path: str = "0"):
    yield path, proto
    for index, child in enumerate(proto.protos):
        yield from walk(child, f"{path}.{index}")


def refs(proto: Proto) -> set[str]:
    return {s for s in proto.strings if s is not None}


def format_instruction(proto: Proto, pc: int, value: int) -> str:
    op = value & 0x3f
    name = OPS[op] if op < len(OPS) else f"OP_{op}"
    u = value >> 6
    a = value >> 15
    b = (value >> 6) & 0x1ff
    s = u - ((1 << 25) - 1)
    if op in AB_OPS:
        arg = f"{a} {b}"
        if op in PROTO_OPS and a < len(proto.protos):
            arg += f" ; proto {a}"
    elif op in S_OPS:
        arg = str(s)
        if 32 <= op <= 42 or 44 <= op <= 47:
            arg += f" ; -> {pc + 1 + s}"
    else:
        arg = str(u)
        if op in STRING_OPS and u < len(proto.strings):
            arg += f" ; {proto.strings[u]!r}"
        elif op in NUMBER_OPS and u < len(proto.numbers):
            arg += f" ; {proto.numbers[u]!r}"
    line = proto.lines[pc] if pc < len(proto.lines) else 0
    return f"{pc:04d} L{line:<4} {name:<14} {arg}"


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("ram", type=Path)
    parser.add_argument("--offset", required=True, type=lambda s: int(s, 0))
    parser.add_argument("--find", action="append", default=[])
    parser.add_argument(
        "--proto-path",
        action="append",
        default=[],
        help="only print an exact prototype path such as 0.2 (repeatable)",
    )
    args = parser.parse_args()
    reader = Reader(args.ram.read_bytes(), args.offset)
    reader.header()
    root = reader.proto()
    matches = []
    for path, proto in walk(root):
        if args.proto_path and path not in args.proto_path:
            continue
        if all(term in refs(proto) for term in args.find):
            matches.append((path, proto))
    for path, proto in matches:
        print(f"PROTO {path} source={proto.source!r} line={proto.line} params={proto.params} stack={proto.stack}")
        print("STRINGS", list(enumerate(proto.strings)))
        print("LOCALS", proto.locals)
        for pc, insn in enumerate(proto.code):
            print(format_instruction(proto, pc, insn))
        print()


if __name__ == "__main__":
    main()
