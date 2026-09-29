#!/usr/bin/env python3
"""Disassemble a file-backed x86 range from the verified retail XBE."""
import argparse
import struct
from pathlib import Path

from capstone import Cs, CS_ARCH_X86, CS_MODE_32


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("xbe", type=Path)
    parser.add_argument("address", type=lambda value: int(value, 0))
    parser.add_argument("--bytes", type=lambda value: int(value, 0), default=0x80)
    args = parser.parse_args()
    data = args.xbe.read_bytes()
    word = lambda offset: struct.unpack_from("<I", data, offset)[0]
    image_base = word(0x104)
    table = word(0x120) - image_base
    for index in range(word(0x11C)):
        record = table + index * 56
        virtual, raw, length = word(record + 4), word(record + 12), word(record + 16)
        if virtual <= args.address and args.address + args.bytes <= virtual + length:
            code = data[raw + args.address - virtual:raw + args.address - virtual + args.bytes]
            disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
            for instruction in disassembler.disasm(code, args.address):
                print(f"{instruction.address:08X}: {instruction.bytes.hex(' ').upper():<24} {instruction.mnemonic:<8} {instruction.op_str}")
            return
    raise ValueError(f"XBE address 0x{args.address:08X} is not file-backed")


if __name__ == "__main__":
    main()
