"""Read-only retail in-engine movie timelines from XboxRam.read.

Manager 00112D80/derived override 0005CD65/list update 00112BE0;
movie constructor 00112280/derived override 0005910E,
start 00111EE0, elapsed update 00111CE0, finish 00111F90. Raw IEEE754 bits
are preserved, including pre-ready values; they are not host timestamps.
"""
import struct


def read_cinematic_state(ram):
    s = dict(cinematicManager=None, cinematicManagerVtable=None,
             cinematicDeclaredCount=None, cinematics=None,
             cinematicComplete=False, cinematicReason=None,
             cinematicMemoryReads=0, cinematicMemoryBytes=0)

    def fail(reason):
        if s['cinematicReason'] is None:
            s['cinematicReason'] = reason

    def get(address, size):
        if not isinstance(address, int) or address & 3 or not (
                0x10000 <= address and address + size <= 0x08000000 or
                0x80000000 <= address and address + size <= 0x88000000):
            fail('invalid guest RAM address')
            return None
        if s['cinematicMemoryReads'] + 1 > 34 or s['cinematicMemoryBytes'] + size > 2144:
            fail('cinematic read budget exceeded')
            return None
        s['cinematicMemoryReads'] += 1
        s['cinematicMemoryBytes'] += size
        try:
            data = ram.read(address, size)
        except (ValueError, struct.error):
            fail('guest memory unavailable')
            return None
        if not isinstance(data, (bytes, bytearray)) or len(data) != size:
            fail('short guest memory read')
            return None
        return data

    def word(data, offset=0):
        return struct.unpack_from('<I', data, offset)[0]

    p = get(0x286784, 4)
    if p is None:
        return s
    manager = s['cinematicManager'] = word(p)
    if manager == 0:
        s.update(cinematics=[], cinematicComplete=True)
        return s
    header = get(manager, 0x1c)
    if header is None:
        return s
    s['cinematicManagerVtable'] = word(header)
    if s['cinematicManagerVtable'] not in (0x23611c, 0x22a6b8):
        fail('unexpected cinematic manager vtable')
        return s
    s['cinematicDeclaredCount'] = word(header, 0x18)
    s['cinematics'] = []
    sentinel, tail, node = manager + 8, word(header, 12), word(header, 8)
    previous, seen, objects = sentinel, set(), set()
    while node != sentinel:
        if not node:
            fail('null cinematic list link')
            break
        if node in seen:
            fail('cyclic cinematic list')
            break
        if len(seen) == 16:
            fail('cinematic list exceeds 16 entries')
            break
        seen.add(node)
        link = get(node, 12)
        if link is None:
            break
        if word(link, 4) != previous:
            fail('cinematic previous-link mismatch')
            break
        obj = word(link, 8)
        entry = dict(node=node, object=obj, vtable=None, nameHash=None,
                     durationBits=None, elapsedBits=None, flags=None,
                     state=None, complete=False)
        s['cinematics'].append(entry)
        if obj in objects:
            fail('duplicate cinematic object')
            break
        objects.add(obj)
        movie = get(obj, 0x78)
        if movie is not None:
            entry['vtable'] = word(movie)
            if entry['vtable'] not in (0x236100, 0x229fb4):
                fail('unexpected cinematic movie vtable')
            else:
                entry.update(nameHash=word(movie, 0x20), durationBits=word(movie, 0x68),
                             elapsedBits=word(movie, 0x6c), flags=word(movie, 0x70),
                             state=word(movie, 0x74))
                entry['complete'] = entry['state'] <= 3
                if not entry['complete']:
                    fail('invalid cinematic movie state')
        previous, node = node, word(link)
    if node == sentinel and tail != previous:
        fail('cinematic tail-link mismatch')
    if len(s['cinematics']) != s['cinematicDeclaredCount']:
        fail('cinematic count mismatch')
    s['cinematicComplete'] = s['cinematicReason'] is None
    return s
