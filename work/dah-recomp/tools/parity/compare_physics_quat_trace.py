#!/usr/bin/env python3
"""Correlate setter events with the player inner body and compare paired traces."""
import argparse
import json
from pathlib import Path


def rows(path):
    result = []
    for line in Path(path).read_text(encoding='utf-8').splitlines():
        try:
            result.append(json.loads(line))
        except json.JSONDecodeError:
            pass
    return result


def selected(trace_path, state_path, index):
    inner = {row.get(index): row.get('physicsInner') for row in rows(state_path)
             if isinstance(row.get(index), int) and row.get('physicsInnerComplete')}
    result = {}
    for row in rows(trace_path):
        key = row.get(index, row.get('loop'))
        if isinstance(key, int) and row.get('object') == inner.get(key):
            result[(key, row.get('phase'))] = row
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('reference_trace')
    parser.add_argument('reference_state')
    parser.add_argument('native_trace')
    parser.add_argument('native_state')
    parser.add_argument('--reference-index', default='relativeFrame')
    parser.add_argument('--native-index', default='loop')
    parser.add_argument('--out')
    args = parser.parse_args()
    reference = selected(args.reference_trace, args.reference_state, args.reference_index)
    native = selected(args.native_trace, args.native_state, args.native_index)
    phases = {}
    for phase in ('input', 'normalized'):
        common = sorted(key for key, item_phase in reference if item_phase == phase and (key, phase) in native)
        field = 'inputBits' if phase == 'input' else 'storedBits'
        matches = [key for key in common if reference[(key, phase)].get(field) == native[(key, phase)].get(field)]
        first = next((key for key in common if key not in matches), None)
        phases[phase] = {
            'compared': len(common), 'bitExact': len(matches), 'firstMismatch': None if first is None else {
                'loop': first, 'reference': reference[(first, phase)].get(field),
                'native': native[(first, phase)].get(field)}}
    report = {'schema': 1, 'phases': phases,
              'referencePlayerEvents': len(reference), 'nativePlayerEvents': len(native)}
    text = json.dumps(report, indent=2) + '\n'
    if args.out:
        Path(args.out).write_text(text, encoding='utf-8')
    print(text, end='')


if __name__ == '__main__':
    main()
