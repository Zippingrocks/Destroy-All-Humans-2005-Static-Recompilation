#!/usr/bin/env python3
"""Align RenderDoc draw sequences by primitive count and report unmatched runs."""

import argparse
import json


def draws(path: str, end_event: int) -> list[tuple[int, int]]:
    result = []
    with open(path, encoding="utf-8-sig") as source:
        for line in source:
            item = json.loads(line)
            if (item.get("kind") == "action" and item.get("event", 0) < end_event
                    and item.get("flags", 0) & 2):
                result.append((item["event"], item.get("numIndices", 0)))
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("left")
    parser.add_argument("left_end", type=int)
    parser.add_argument("right")
    parser.add_argument("right_end", type=int)
    args = parser.parse_args()
    left = draws(args.left, args.left_end)
    right = draws(args.right, args.right_end)
    table = [[0] * (len(right) + 1) for _ in range(len(left) + 1)]
    for i in range(len(left) - 1, -1, -1):
        for j in range(len(right) - 1, -1, -1):
            table[i][j] = (table[i + 1][j + 1] + 1 if left[i][1] == right[j][1]
                           else max(table[i + 1][j], table[i][j + 1]))
    i = j = 0
    unmatched_left = []
    unmatched_right = []
    while i < len(left) or j < len(right):
        if i < len(left) and j < len(right) and left[i][1] == right[j][1]:
            i += 1
            j += 1
        elif j < len(right) and (i == len(left) or
                                  table[i][j + 1] >= table[i + 1][j]):
            unmatched_right.append((j, *right[j]))
            j += 1
        else:
            unmatched_left.append((i, *left[i]))
            i += 1
    print(f"left draws={len(left)} right draws={len(right)} "
          f"matched={table[0][0]}")
    print("left-only ordinal,event,count:")
    print(" ".join(f"{o},{e},{c}" for o, e, c in unmatched_left) or "none")
    print("right-only ordinal,event,count:")
    print(" ".join(f"{o},{e},{c}" for o, e, c in unmatched_right) or "none")


if __name__ == "__main__":
    main()
