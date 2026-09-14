/* Run in a VS x64 developer prompt; no game launch. */
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
const here = path.dirname(fileURLToPath(import.meta.url));
const regenerated = spawnSync('python', [path.join(here, 'lift_audio_cleanup.py')], { encoding: 'utf8' });
assert.equal(regenerated.status, 0, regenerated.stderr);
const checked = JSON.parse(regenerated.stdout);
const source = fs.readFileSync(path.join(here, '../src/recomp/gen/recomp_audio_cleanup.c'), 'utf8');
assert.equal(source.replace(/\r/g, '').trim(), checked.code.trim(), 'Production source differs from byte-validated exact lift');
console.log(`PASS: byte-validated original callbacks ${JSON.stringify(checked.details)}`);
const fixture = source.replace(/^#define RECOMP_GENERATED_CODE\r?$/m, '').replace(/^#include "recomp_funcs.h"\r?$/m, '');
const temp = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-audio-cleanup-'));
function run(label, code, expectedStatus) {
  const directory = path.join(temp, label);
  fs.mkdirSync(directory);
  fs.writeFileSync(path.join(directory, 'audio_cleanup_fixture.inc'), code);
  const executable = path.join(directory, 'test.exe');
  const compile = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11',
    `/I${directory}`, `/Fe:${executable}`, `/Fo:${path.join(directory, 'test.obj')}`,
    path.join(here, 'test_audio_cleanup.c')], { cwd: directory, encoding: 'utf8', timeout: 30000 });
  assert.equal(compile.status, 0, compile.error || compile.stdout || compile.stderr);
  const result = spawnSync(executable, [], { cwd: directory, encoding: 'utf8', timeout: 30000 });
  assert.equal(result.status, expectedStatus, result.error || result.stderr);
  console.log(expectedStatus ? `PASS: rejected ${label}: ${result.stderr.trim()}` : result.stdout.trim());
}
run('current', fixture, 0);
run('incorrect-release-argument', fixture.replace('PUSH32(esp, MEM32(esp + 0xC));', 'PUSH32(esp, MEM32(esp + 8));'), 1);
run('incorrect-action-stack-cleanup', fixture.replace('esp += 12; return; /* ret 8 */', 'esp += 8; return; /* incorrect ret 4 */'), 1);
run('missing-reference-clear', fixture.replace('MEM32(ecx + 4) = MEM32(ecx + 4) & 0;', '/* regression control: reference count not cleared */'), 1);
run('incorrect-stop-result', fixture.replace('eax = ebx;', 'eax = 0; /* regression control: lost queue result */'), 1);
run('incorrect-stream-format-mask', fixture.replace('ebx = ebx & 0xFFFEFFFFu;', 'ebx = ebx & 0xFFFDFFFFu;'), 1);
run('incorrect-stream-negative-status', fixture.replace('if (TEST_S(_fas, _fbs)) goto loc_001F2349;', 'if (TEST_Z(_fa, _fb)) goto loc_001F2349;'), 1);
run('incorrect-packet-stack-cleanup', fixture.replace('esp += 20; return; /* ret 16 */', 'esp += 16; return; /* incorrect ret 12 */'), 1);
run('incorrect-packet-argument-order', fixture.replace('MEM32(eax + 0x18) = edx;', 'MEM32(eax + 0x1C) = edx;'), 1);
run('incorrect-stream-action-forwarding', fixture.replace(
  'PUSH32(esp, 0x001F24C9u); sub_001F241A();', 'PUSH32(esp, 0x001F24C9u); sub_001F18C5();'), 1);
run('incorrect-stream-release-this-adjustment', fixture.replace(
  'eax = eax + 4;\n    PUSH32(esp, eax);', 'eax = eax + 8;\n    PUSH32(esp, eax);'), 1);
run('incorrect-stream-query-argument', fixture.replace(
  'PUSH32(esp, MEM32(esp + 0x10));\n    PUSH32(esp, 0x001ED3F6u);',
  'PUSH32(esp, MEM32(esp + 0xC));\n    PUSH32(esp, 0x001ED3F6u);'), 1);
run('incorrect-stream-stop-return', fixture.replace(
  'loc_001ED3B7: ;\n    eax = 0; /* xor self */',
  'loc_001ED3B7: ;\n    eax = release_result; /* regression control */'), 1);
console.log(`TEST_OUTPUT ${temp}`);
