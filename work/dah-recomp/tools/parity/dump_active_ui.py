"""List active retail UI object paths from a paused xemu RAM capture."""
import argparse
import json
import struct
from pathlib import Path
from decode_xemu_ram import XboxRam


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("ram", type=Path)
    parser.add_argument("--metadata", type=Path, required=True)
    args = parser.parse_args()
    metadata = json.loads(args.metadata.read_text(encoding="utf-8-sig"))
    ram = XboxRam(args.ram.read_bytes(), metadata["cr3"])
    root = ram.word(ram.word(0x258470))
    seen = set()
    paths = []

    def walk(obj, parent, parent_path, depth):
        if not obj or obj in seen or len(seen) >= 4096 or depth > 12:
            return
        seen.add(obj)
        header = ram.read(obj, 0x60)
        if parent and struct.unpack_from("<I", header, 8)[0] != parent:
            return
        if not header[4]:
            return
        raw = header[0xC:0x34].split(b"\0", 1)[0]
        name = raw.decode("latin1") if raw else "<root>"
        path = f"{parent_path}/{name}" if parent_path else name
        paths.append({"address": obj, "path": path, "depth": depth})
        sentinel = obj + 0x44
        node = struct.unpack_from("<I", header, 0x44)[0]
        links = set()
        while node and node != sentinel and node not in links and len(links) < 256:
            links.add(node)
            link = ram.read(node, 12)
            walk(struct.unpack_from("<I", link, 8)[0], obj, path, depth + 1)
            node = struct.unpack_from("<I", link)[0]

    walk(root, 0, "", 0)
    print(json.dumps({"root": root, "count": len(paths), "paths": paths}, indent=2))


if __name__ == "__main__":
    main()
