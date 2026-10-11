#!/usr/bin/env python3
"""Compare the player axis-angle constructor input from paired xemu/recomp runs."""
import argparse
import json
from pathlib import Path


def rows(path):
    result = []
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        try:
            result.append(json.loads(line))
        except json.JSONDecodeError:
            pass
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("reference_trace")
    parser.add_argument("native_trace")
    parser.add_argument("--out")
    args = parser.parse_args()
    reference = {row["relativeFrame"]: row for row in rows(args.reference_trace)
                 if row.get("phase") == "constructor" and
                 isinstance(row.get("relativeFrame"), int)}
    native = {row["loop"]: row for row in rows(args.native_trace)
              if row.get("phase") == "constructor" and
              isinstance(row.get("loop"), int)}
    common = sorted(reference.keys() & native.keys())
    exact = [key for key in common
             if reference[key].get("angleBits") == native[key].get("angleBits")]
    first = next((key for key in common if key not in exact), None)
    report = {
        "schema": 1,
        "compared": len(common),
        "bitExact": len(exact),
        "firstMismatch": None if first is None else {
            "loop": first,
            "reference": reference[first].get("angleBits"),
            "native": native[first].get("angleBits"),
        },
    }
    text = json.dumps(report, indent=2) + "\n"
    if args.out:
        Path(args.out).write_text(text, encoding="utf-8")
    print(text, end="")


if __name__ == "__main__":
    main()
