"""Decode a paused 64 MiB retail RAM capture using its real x86 page tables."""
import argparse
import json
import math
import struct
from pathlib import Path
from cinematic_state import read_cinematic_state


class XboxRam:
    def __init__(self, data, cr3):
        if len(data) != 64 * 1024 * 1024:
            raise ValueError('Expected a complete 64 MiB physical RAM capture')
        self.data, self.cr3 = data, cr3

    def physical_word(self, address):
        if not 0 <= address <= len(self.data) - 4:
            raise ValueError(f'Physical address out of range: {address:#x}')
        return struct.unpack_from('<I', self.data, address)[0]

    def translate(self, address):
        pde = self.physical_word((self.cr3 & ~4095) + (address >> 22) * 4)
        if not pde & 1:
            raise ValueError(f'Unmapped PDE for {address:#x}')
        if pde & 128:
            return (pde & 0xFFC00000) + (address & 0x3FFFFF)
        pte = self.physical_word((pde & ~4095) + ((address >> 12) & 1023) * 4)
        if not pte & 1:
            raise ValueError(f'Unmapped PTE for {address:#x}')
        return (pte & ~4095) + (address & 4095)

    def read(self, address, length):
        if not 0 <= address <= 0xFFFFFFFF or not 0 <= length <= 0x100000000 - address:
            raise ValueError('Invalid virtual address range')
        result = bytearray()
        while length:
            count = min(length, 4096 - (address & 4095))
            physical = self.translate(address)
            if physical + count > len(self.data):
                raise ValueError('Virtual address maps outside captured RAM')
            result.extend(self.data[physical:physical + count])
            address += count
            length -= count
        return bytes(result)

    def word(self, address):
        return struct.unpack('<I', self.read(address, 4))[0] if address else 0

    def text(self, address, limit):
        return self.read(address, limit).split(b'\0', 1)[0].decode('latin1') if address else ''

    def selectors(self, root):
        """Return sorted, pointer-independent active highlight paths.

        Walk only verified menu trees, requiring every ancestor to be active.
        A malformed or truncated tree is reported separately from no selection.
        No animation offsets are inferred from the underlying raw UI words.
        """
        menus = {'tthubMain', 'options', 'optionsController', 'optionsAudio',
                 'optionsDisplay', 'labUpgrade'}
        patterns = (('tthubMain/slot', '/underline', 4),
                    ('options/slot', 'bkgnd', 4),
                    ('optionsController/slots/slot', '/bkgnd', 8),
                    ('optionsAudio/slots/slot', '/bkgnd', 8),
                    ('optionsDisplay/slots/slot', '/bkgnd', 8),
                    ('labUpgrade/slots/slot', '/selected', 3))
        matches = set()
        for prefix, suffix, maximum in patterns:
            matches.update(f'{prefix}{slot}{suffix}' for slot in range(1, maximum + 1))
        paths, objects = [], set()
        complete, node_count = True, 0

        def checked(address, size):
            if address < 0x10000 or address & 3:
                raise ValueError('Invalid UI address')
            return self.read(address, size)  # Validates every mapped page and RAM span.

        def walk(obj, parent, parent_path, depth):
            nonlocal complete, node_count
            try:
                header = checked(obj, 0x60)
                if parent and struct.unpack_from('<I', header, 8)[0] != parent:
                    raise ValueError('UI parent mismatch')
                if obj in objects or len(objects) >= 512:
                    raise ValueError('Cyclic or oversized UI tree')
                objects.add(obj)
                if not header[4]:
                    return
                path = ''
                if depth:
                    raw_name = header[0xC:0x34]
                    if b'\0' not in raw_name:
                        raise ValueError('Unterminated UI name')
                    raw_name = raw_name.split(b'\0', 1)[0]
                    if not raw_name or any(c < 32 or c >= 127 or c in b'/\\"' for c in raw_name):
                        raise ValueError('Invalid UI path component')
                    name = raw_name.decode('ascii')
                    if depth == 1 and name not in menus:
                        return
                    path = f'{parent_path}/{name}' if parent_path else name
                    if len(parent_path) + len(name) + 2 > 256:
                        raise ValueError('Oversized UI path')
                    if path in matches:
                        if len(paths) >= 32:
                            raise ValueError('Too many selectors')
                        paths.append(path)
                        return
                if depth == 4:
                    return
                sentinel = obj + 0x44
                node = struct.unpack_from('<I', header, 0x44)[0]
                visited = set()
                while node and node != sentinel:
                    if node in visited or len(visited) >= 64 or node_count >= 512:
                        raise ValueError('Cyclic or oversized UI list')
                    visited.add(node)
                    node_count += 1
                    link = checked(node, 12)
                    child = struct.unpack_from('<I', link, 8)[0]
                    if child:
                        walk(child, obj, path, depth + 1)
                    else:
                        complete = False
                    node = struct.unpack_from('<I', link)[0]
                if not node:
                    complete = False
            except (ValueError, struct.error):
                complete = False

        if root:
            walk(root, 0, '', 0)
        return sorted(paths), complete

    def controller_options(self):
        """Read the progress keys used by the retail Controls label functions.

        00089840 returns [00249AE4]; 0008AD10/0008A540 search sorted eight-byte
        records at store+3A58, with count/capacity at +3A50/+3A54. Byte +4 is
        the active flag, not a DWORD. A missing key is the script's default;
        a malformed or unavailable table remains unknown instead of default.
        """
        hashes = {'invertPitch': 0x26FBC240, 'invertYaw': 0xA37AAC8D,
                  'noVibration': 0xE54032BE}
        unknown = {name: dict(present=None, active=None) for name in hashes}
        result = {name: dict(present=False, active=False) for name in hashes}
        try:
            store = self.word(0x249AE4)
            if store < 0x10000 or store & 3 or store > 0xFFFFFFFF - 0x3A5C:
                raise ValueError('Invalid progress store')
            count, capacity, array = struct.unpack('<III', self.read(store + 0x3A50, 12))
            if not 0 < capacity <= 1024 or count > capacity or array < 0x10000 or array & 3:
                raise ValueError('Invalid progress key table')
            records = self.read(array, count * 8 if count else 4)
            previous = -1
            for offset in range(0, count * 8, 8):
                key = struct.unpack_from('<I', records, offset)[0]
                active = records[offset + 4]
                if key <= previous or active > 1:
                    raise ValueError('Invalid progress key record')
                previous = key
                for name, expected in hashes.items():
                    if key == expected:
                        result[name] = dict(present=True, active=bool(active))
            return result, True
        except (ValueError, struct.error):
            return unknown, False

    def farm_state(self):
        """Bounded source-proven fields; missing/invalid objects stay unknown.

        World: 00105280/00115388/00115208; RNG: 000D4270; player focus:
        00082550/00082560; move state: 000817C0. Camera/actor transforms match
        the existing retail-field pose trace. These are raw float bits, not
        transformed coordinates. No gameplay data is changed by this decoder.
        """
        def block(address, size):
            if address is None or address & 3 or not (
                    0x10000 <= address and address + size <= 0x08000000 or
                    0x80000000 <= address and address + size <= 0x88000000):
                return None
            try:
                return self.read(address, size)
            except (ValueError, struct.error):
                return None

        def word(data, offset=0):
            return struct.unpack_from('<I', data, offset)[0] if data is not None else None

        def words(data, offset, count):
            return list(struct.unpack_from(f'<{count}I', data, offset)) if data is not None else None

        world = word(block(0x286768, 4))
        wh = block(world, 0x14)
        world_vtable = word(wh)
        # Validate flags separately instead of reading the whole 12 KiB object.
        flags = block(world + 0x303C, 4) if world_vtable == 0x235780 else None
        world_ok = wh is not None and world_vtable == 0x235780 and flags is not None
        pending = word(block(0x25FBFC, 4))
        ph = block(pending, 0x14)
        pn = block(pending + 0x50C, 128) if ph is not None else None
        name = None
        if pn is not None and b'\0' in pn:
            raw = pn.split(b'\0', 1)[0]
            if all(32 <= c <= 126 for c in raw):
                name = raw.decode('ascii')
        rng = word(block(0x278A58, 4))
        camera_update = block(0x258B48, 4)
        control = word(block(0x25FCEC, 4))
        ch = block(control, 0x3C)
        player = word(ch, 0x38)
        player_header = block(player, 0x3C)
        actor = word(player_header, 0x38)
        actor_header = block(actor, 0x158)
        actor_vtable = word(actor_header)
        actor_ok = actor_header is not None and actor_vtable == 0x22C9F8
        movement = word(actor_header, 0x130) if actor_ok else None
        mh = block(movement, 0x4C)
        msh = block(movement + 0x2AC, 8) if mh is not None else None
        weapon_manager = word(actor_header, 0x138) if actor_ok else None
        weapon_manager_header = block(weapon_manager, 0x5C)
        weapon_slots = words(weapon_manager_header, 0x4C, 4)
        weapon_slot_vtables = []
        holobob_main = None
        if weapon_slots is not None:
            for weapon in weapon_slots:
                weapon_vtable = word(block(weapon, 4)) if weapon else None
                weapon_slot_vtables.append(weapon_vtable)
                if weapon_vtable == 0x22FD50:
                    holobob_main = weapon
        active_weapon = word(weapon_manager_header, 0x58)
        active_weapon_header = block(active_weapon, 0x1A0)
        holobob_main_header = block(holobob_main, 0x1A0)
        renderer = word(block(0x250E60, 4))
        rh = block(renderer, 0xF0)
        node = word(rh, 0xEC)
        nh = block(node, 0x90)
        result = dict(
            worldVtable=world_vtable, worldTick=word(wh, 8) if world_ok else None,
            worldElapsedBits=word(wh, 12) if world_ok else None,
            worldStepBits=word(wh, 16) if world_ok else None,
            worldPaused=flags[0] if world_ok else None,
            worldRealtime=flags[1] if world_ok else None, worldComplete=world_ok,
            pendingBackendState=word(ph, 0x10), pendingBackendName=name,
            pendingBackendComplete=ph is not None and name is not None,
            rngState=rng, rngStateComplete=rng is not None,
            cameraUpdate=camera_update[0] if camera_update is not None else None,
            cameraUpdateComplete=camera_update is not None,
            controlSystem=control, player=player, playerVtable=word(player_header),
            playerFocus=word(player_header, 0x30), playerShip=word(player_header, 0x34),
            playerCrypto=actor, playerComplete=player_header is not None,
            actor=actor, actorVtable=actor_vtable,
            actorPositionBits=words(actor_header, 0x14C, 3) if actor_ok else None,
            actorComplete=actor_ok, movement=movement, moveState=word(mh, 0x48),
            movementAngularVelocityBits=word(mh, 0x14),
            movementHeadingBits=word(mh, 0x18),
            movementSteeringBits=words(msh, 0, 2),
            moveStateComplete=mh is not None,
            movementMotionComplete=mh is not None and msh is not None,
            weaponManager=weapon_manager, weaponSlots=weapon_slots,
            weaponSlotVtables=weapon_slot_vtables,
            activeWeapon=active_weapon,
            activeWeaponVtable=word(active_weapon_header),
            activeWeaponWords=words(active_weapon_header, 0, 0x68),
            holobobMain=holobob_main,
            holobobActive=holobob_main_header[0x34] if holobob_main_header is not None else None,
            holobobState=word(holobob_main_header, 0x44),
            holobobTarget=word(holobob_main_header, 0x178),
            holobobToken=word(holobob_main_header, 0x17C),
            holobobMainWords=words(holobob_main_header, 0, 0x68),
            weaponManagerComplete=(weapon_manager_header is not None and
                                   active_weapon_header is not None and
                                   len(weapon_slot_vtables) == 4 and
                                   all(v is not None for v in weapon_slot_vtables)),
            cameraNode=node, cameraNodeParent=word(nh, 8),
            cameraViewPositionBits=words(rh, 0x80, 3),
            cameraViewForwardBits=words(rh, 0x70, 3),
            cameraLocalBits=words(nh, 0x20, 3), cameraQuatBits=words(nh, 0x40, 4),
            cameraWorldBits=words(nh, 0x50, 16), cameraComplete=nh is not None)

        # 00081B70 stores object quaternion +38..44 and dirty flags +4C.
        # 0012BB30 is the verified velocity setter inherited by body 2376E8.
        obj = word(actor_header, 0x28) if actor_ok else None
        oh = block(obj, 0x50)
        node_link = block(actor + 0x4A0, 4) if actor_ok else None
        actor_node = word(node_link)
        anh = block(actor_node, 0x90)
        actor_node_vtable = word(anh)
        actor_node_ok = anh is not None and actor_node_vtable == 0x234308
        body = word(actor_header, 0x110) if actor_ok else None
        bh = block(body, 0x90)
        body_vtable = word(bh)
        setter = word(block(body_vtable + 0x90, 4)) if body_vtable == 0x2376E8 else None
        body_ok = bh is not None and body_vtable == 0x2376E8 and setter == 0x12BB30
        physics_inner = word(bh, 0x0C)
        pih = block(physics_inner, 0x48) if body_vtable == 0x2376E8 else None
        physics_inner_vtable = word(pih)
        physics_inner_ok = pih is not None and physics_inner_vtable == 0x237968
        result.update(
            actorObject=obj, actorObjectPositionBits=words(oh, 0x2C, 3),
            actorObjectQuatBits=words(oh, 0x38, 4), actorObjectFlags=word(oh, 0x4C),
            actorObjectComplete=oh is not None, actorSceneNode=actor_node,
            actorSceneNodeVtable=actor_node_vtable,
            actorSceneNodeParent=word(anh, 8) if actor_node_ok else None,
            actorSceneQuatBits=words(anh, 0x40, 4) if actor_node_ok else None,
            actorSceneWorldBits=words(anh, 0x50, 16) if actor_node_ok else None,
            actorSceneNodeComplete=actor_node_ok, physicsBody=body,
            physicsBodyVtable=body_vtable, physicsVelocitySetter=setter,
            physicsVelocityBits=words(bh, 0x84, 3) if body_ok else None,
            physicsBodyComplete=body_ok, physicsInner=physics_inner,
            physicsInnerVtable=physics_inner_vtable,
            physicsInnerQuatBits=words(pih, 0x38, 4) if physics_inner_ok else None,
            physicsInnerComplete=physics_inner_ok)

        # Retail shield render 0005FF00/0005FBD0, updated from the Crypto
        # health ratio by 000600B0. Follow only the verified named path;
        # do not recursively scan arbitrary UI or actor memory.
        def hud_object(path):
            root_link = word(block(0x258470, 4))
            root = word(block(root_link, 4)) if root_link else 0
            obj, active, traversal, total = root, True, root is not None, 0
            if obj:
                for part in path:
                    header = block(obj, 0x60)
                    if header is None:
                        traversal = False
                        break
                    active = active and bool(header[4])
                    sentinel, link = obj + 0x44, word(header, 0x44)
                    seen, found = set(), 0
                    while link and link != sentinel:
                        if link in seen or len(seen) == 64 or total == 256:
                            traversal = False
                            break
                        seen.add(link)
                        total += 1
                        entry = block(link, 12)
                        child = word(entry, 8)
                        child_header = block(child, 0x34)
                        if child_header is None or word(child_header, 8) != obj:
                            traversal = False
                            break
                        name = child_header[12:52]
                        if b'\0' in name and name.split(b'\0', 1)[0] == part:
                            if found:
                                traversal = False
                                break
                            found = child
                        link = word(entry)
                    if not link:
                        traversal = False
                    if not traversal:
                        break
                    obj = found
                    if not obj:
                        break
            return (obj if traversal else None), active, traversal

        shield, active, traversal = hud_object(
            (b'main', b'alien', b'healthandconcentration', b'change', b'bar'))
        sh = block(shield, 0x538)
        valid = sh is not None and word(sh) == 0x22A8D8
        positive = None
        if valid:
            active = active and bool(sh[4])
            values = struct.unpack_from('<60f', sh, 0x40C)
            threshold_data = block(0x226E38, 4)
            if threshold_data is not None and all(math.isfinite(v) for v in values):
                threshold = struct.unpack('<f', threshold_data)[0]
                positive = sum(v > threshold for v in values)
        ah = block(actor, 0x374) if actor_ok else None
        result.update(
            hudShield=shield, hudShieldActive=active if valid else None,
            hudShieldVisible=bool(sh[0x534]) if valid else None,
            hudShieldFillBits=words(sh, 0x3F0, 2) if valid else None,
            hudShieldPositiveSegments=positive,
            hudShieldTraversalComplete=traversal,
            hudShieldComplete=valid and positive is not None,
            hudActorCurrentBits=word(ah, 0x370),
            # 00060101 divides actor +370 by +368 to obtain shield ticks.
            hudActorDivisorBits=word(ah, 0x368),
            hudActorHealthComplete=ah is not None)
        enemy, ancestors_active, traversal = hud_object((b'main', b'enemyhealth', b'bar'))
        eh = block(enemy, 0x158)
        enemy_vtable = word(eh)
        valid = eh is not None and enemy_vtable == 0x23511C
        own_active = bool(eh[4]) if valid else None
        result.update(
            hudEnemyBar=enemy or None, hudEnemyBarVtable=enemy_vtable,
            hudEnemyBarOwnActive=own_active,
            hudEnemyBarAncestorsActive=ancestors_active if valid else None,
            hudEnemyBarActive=own_active and ancestors_active if valid else None,
            hudEnemyBarRectBits=words(eh, 0xB0, 4) if valid else None,
            hudEnemyBarColorBits=words(eh, 0xD0, 4) if valid else None,
            hudEnemyBarFillBits=words(eh, 0x150, 2) if valid else None,
            hudEnemyBarDirection=word(eh, 0x14C) if valid else None,
            hudEnemyBarTraversalComplete=traversal, hudEnemyBarComplete=valid)
        return result

    def state(self):
        word = self.word
        renderer, world, movie = (word(a) for a in (0x250E60, 0x286768, 0x28681C))
        backend = word(0x25B1D0 + 0x4A28)
        root = word(word(0x258470))
        control = word(0x25FCEC)
        player = word(control + 0x38) if control else 0
        state = dict(schema=1, source='xemu', phase='paused-checkpoint',
                     loop=word(0x25B1DC), renderer=renderer,
                     refresh=(60 if word(renderer + 0x238) else 50) if renderer else 0,
                     divisor=word(renderer + 0x27C) if renderer else 0,
                     interval=word(renderer + 0x2C8) if renderer else 0,
                     world=world, worldStepBits=word(world + 0x10) if world else 0,
                     movie=movie, movieMode=word(0x2867F8), movieFlags=word(0x2867F4) & 255,
                     movieLifecycle=word(0x286804),
                     movieHeader=[word(movie + i * 4) if movie else 0 for i in range(6)],
                     backend=backend, backendState=word(backend + 0x10) if backend else 0,
                     backendName=self.text(backend + 0x50C, 128) if backend else '',
                     pendingBackend=word(0x25B1D0 + 0x4A2C),
                     controlSettings=[word(player + 0x50 + i * 4) if player else 0 for i in range(4)],
                     uiRoot=root, ui=[])
        sentinel = root + 0x44 if root else 0
        node, visited = word(sentinel), set()
        while node and node != sentinel:
            if node in visited or len(visited) >= 64:
                raise ValueError('Invalid or oversized UI list')
            visited.add(node)
            child = word(node + 8)
            if child:
                state['ui'].append(dict(address=child, vtable=word(child),
                                        active=word(child + 4) & 255,
                                        name=self.text(child + 0xC, 40)))
            node = word(node)
        state['selectors'], state['selectorsComplete'] = self.selectors(root)
        state['controllerOptions'], state['controllerOptionsComplete'] = self.controller_options()
        state.update(self.farm_state())
        state.update(read_cinematic_state(self))
        return state


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('ram', type=Path)
    parser.add_argument('--metadata', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--image', type=Path)
    parser.add_argument('--width', type=int, default=640)
    parser.add_argument('--height', type=int, default=480)
    parser.add_argument('--pitch', type=int, default=2560)
    args = parser.parse_args()
    metadata = json.loads(args.metadata.read_text(encoding='utf-8-sig'))
    ram = XboxRam(args.ram.read_bytes(), metadata['cr3'])
    state = ram.state()
    state['checkpoint'] = str(args.metadata)
    with args.out.open('x', encoding='utf-8') as stream:
        json.dump(state, stream, indent=2)
        stream.write('\n')
    if args.image:
        from PIL import Image
        if min(args.width, args.height) <= 0 or args.pitch < args.width * 4:
            raise ValueError('Invalid BGRX surface dimensions or pitch')
        address = metadata['pcrtcStart']
        surface = ram.data[address:address + args.pitch * args.height]
        if len(surface) != args.pitch * args.height:
            raise ValueError('Scanout exceeds RAM')
        image = Image.frombytes('RGB', (args.width, args.height), surface, 'raw', 'BGRX', args.pitch)
        if args.image.exists():
            raise FileExistsError(args.image)
        image.save(args.image)
        print(json.dumps(dict(image=str(args.image), extrema=image.getextrema(),
                              geometry='Caller-specified BGRX scanout layout; verify before exact pixel assertions')))
    print(json.dumps(dict(out=str(args.out), loop=state['loop'], backend=state['backendName'],
                          activeUi=[c['name'] for c in state['ui'] if c['active']])))


if __name__ == '__main__':
    main()
