"""Compare a common scripted-input loop window; do not infer timing parity."""
import argparse
import json
import math
from pathlib import Path
import struct


FIELDS = (
    'actorPositionBits', 'actorObjectPositionBits', 'actorObjectQuatBits',
    'actorSceneQuatBits', 'actorSceneWorldBits', 'physicsVelocityBits',
    'physicsInnerQuatBits',
    'moveState', 'movementAngularVelocityBits', 'movementHeadingBits',
    'movementSteeringBits', 'cameraLocalBits', 'cameraQuatBits', 'cameraWorldBits',
    'worldStepBits', 'worldPaused', 'worldRealtime', 'cameraUpdate',
)


def read_window(path, start, end, index_field='loop'):
    result = {}
    with Path(path).open(encoding='utf-8') as stream:
        for line in stream:
            try:
                row = json.loads(line)
            except json.JSONDecodeError:
                if not line.endswith('\n'):
                    break  # Running logs may have an unfinished final write.
                raise
            loop = row.get(index_field)
            if isinstance(loop, int) and start <= loop <= end:
                if loop in result:
                    raise ValueError(f'Duplicate {index_field} {loop}: {path}')
                result[loop] = row
    return result


def floats(bits):
    if bits is None:
        return None
    if isinstance(bits, list):
        return [floats(x) for x in bits]
    value = struct.unpack('<f', struct.pack('<I', bits))[0]
    return value if math.isfinite(value) else str(value)


def compare(reference, native, start, end, alignment):
    common = sorted(reference.keys() & native.keys())
    results = {}
    for field in FIELDS:
        pairs = [(loop, reference[loop][field], native[loop][field])
                 for loop in common if reference[loop].get(field) is not None
                 and native[loop].get(field) is not None]
        different = [(loop, left, right) for loop, left, right in pairs if left != right]
        item = {'compared': len(pairs), 'bitExact': len(pairs) - len(different),
                'firstMismatch': None}
        if different:
            loop, left, right = different[0]
            item['firstMismatch'] = {'loop': loop, 'reference': left, 'native': right}
            if field.endswith('Bits'):
                item['firstMismatch'].update(referenceFloat=floats(left), nativeFloat=floats(right))
        if field.endswith('Bits') and pairs:
            deltas = []
            for _, left, right in pairs:
                left, right = floats(left), floats(right)
                left = left if isinstance(left, list) else [left]
                right = right if isinstance(right, list) else [right]
                deltas.extend(abs(a - b) for a, b in zip(left, right)
                              if isinstance(a, float) and isinstance(b, float))
            item['maxAbsoluteFloatDifference'] = max(deltas, default=None)
        results[field] = item
    endpoints = {}
    for name, rows in [('reference', reference), ('native', native)]:
        endpoints[name] = {str(loop): {
            'phase': rows[loop].get('phase'), 'worldTick': rows[loop].get('worldTick'),
            'actorPosition': floats(rows[loop].get('actorPositionBits')),
            'actorQuaternion': floats(rows[loop].get('actorObjectQuatBits')),
        } for loop in (start, end) if loop in rows}
    return {'schema': 1, 'alignment': alignment,
            'phaseAlignmentVerified': False, 'wallClockParityVerified': False,
            'pixelParityVerified': False, 'requestedWindow': [start, end],
            'commonLoops': len(common), 'missingReferenceLoops': sorted(set(range(start, end+1)) - reference.keys()),
            'missingNativeLoops': sorted(set(range(start, end+1)) - native.keys()),
            'fields': results, 'endpoints': endpoints}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('reference')
    parser.add_argument('native')
    parser.add_argument('--start', type=int, default=7198)
    parser.add_argument('--end', type=int, default=7260)
    parser.add_argument('--reference-index', choices=('loop', 'relativeFrame'), default='loop')
    parser.add_argument('--native-index', choices=('loop', 'relativeFrame'), default='loop')
    parser.add_argument('--out', required=True)
    args = parser.parse_args()
    if args.end < args.start:
        parser.error('--end must be at least --start')
    alignment = (f'reference {args.reference_index} versus native {args.native_index} '
                 'in shared @frame input script')
    report = compare(read_window(args.reference, args.start, args.end, args.reference_index),
                     read_window(args.native, args.start, args.end, args.native_index),
                     args.start, args.end, alignment)
    report['inputs'] = {'reference': str(Path(args.reference).resolve()),
                        'native': str(Path(args.native).resolve()),
                        'referenceIndex': args.reference_index,
                        'nativeIndex': args.native_index}
    with Path(args.out).open('x', encoding='utf-8') as stream:
        json.dump(report, stream, indent=2, allow_nan=False)
        stream.write('\n')
    print(json.dumps({'out': args.out, 'commonLoops': report['commonLoops'],
                      'fields': report['fields'], 'endpoints': report['endpoints']}))
