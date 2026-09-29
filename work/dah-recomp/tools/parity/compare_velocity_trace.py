"""Compare player velocity-setter inputs by retail loop number."""
import argparse
import json
from pathlib import Path


def load(path, phase):
    rows = {}
    with Path(path).open(encoding='utf-8') as stream:
        for line in stream:
            row = json.loads(line)
            if row.get('phase') != phase:
                continue
            loop = row['loop']
            rows.setdefault(loop, []).append(row)
    return rows


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('reference_trace')
    parser.add_argument('native_trace')
    parser.add_argument('--phase', choices=('velocityInput', 'velocitySource',
                                            'velocityStage'),
                        default='velocityInput')
    parser.add_argument('--out', required=True)
    args = parser.parse_args()
    reference = load(args.reference_trace, args.phase)
    native = load(args.native_trace, args.phase)
    common = sorted(reference.keys() & native.keys())
    pairs = [(loop, index, left, right)
             for loop in common
             for index, (left, right) in enumerate(zip(reference[loop], native[loop]))]
    mismatches = [(loop, index, left, right)
                  for loop, index, left, right in pairs
                  if left['inputBits'] != right['inputBits']]
    first = None
    if mismatches:
        loop, index, left, right = mismatches[0]
        first = {'loop': loop, 'eventIndex': index,
                 'stage': left.get('stage'),
                 'reference': left['inputBits'],
                 'native': right['inputBits'],
                 'referenceReturn': left.get('upstreamReturn'),
                 'nativeReturn': right.get('upstreamReturn')}
    count_mismatches = sorted(loop for loop in common
                              if len(reference[loop]) != len(native[loop]))
    report = {'schema': 1, 'phase': args.phase, 'compared': len(pairs),
              'bitExact': len(pairs) - len(mismatches),
              'firstMismatch': first,
              'eventCountMismatchLoops': count_mismatches,
              'missingReferenceLoops': sorted(native.keys() - reference.keys()),
              'missingNativeLoops': sorted(reference.keys() - native.keys())}
    with Path(args.out).open('x', encoding='utf-8') as stream:
        json.dump(report, stream, indent=2)
        stream.write('\n')
    print(json.dumps(report, indent=2))
