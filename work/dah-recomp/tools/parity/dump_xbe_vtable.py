#!/usr/bin/env python3
"""Print little-endian vtable entries from the verified retail XBE image."""
import argparse
import struct
from pathlib import Path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('xbe', type=Path)
    parser.add_argument('address', nargs='+', type=lambda value: int(value, 0))
    parser.add_argument('--bytes', type=lambda value: int(value, 0), default=0xA0)
    args = parser.parse_args()
    data = args.xbe.read_bytes()
    word = lambda offset: struct.unpack_from('<I', data, offset)[0]
    image_base = word(0x104)
    table = word(0x120) - image_base
    sections = []
    for index in range(word(0x11C)):
        record = table + index * 56
        sections.append((word(record + 4), word(record + 12), word(record + 16)))

    def read(address, size):
        for virtual, raw, length in sections:
            if virtual <= address and address + size <= virtual + length:
                offset = raw + address - virtual
                return data[offset:offset + size]
        raise ValueError(f'XBE address 0x{address:08X} is not file-backed')

    if args.bytes <= 0 or args.bytes % 4:
        raise ValueError('--bytes must be a positive multiple of four')
    for address in args.address:
        print(f'0x{address:08X}')
        for offset in range(0, args.bytes, 4):
            value = struct.unpack('<I', read(address + offset, 4))[0]
            print(f'  +0x{offset:02X} 0x{value:08X}')


if __name__ == '__main__':
    main()
