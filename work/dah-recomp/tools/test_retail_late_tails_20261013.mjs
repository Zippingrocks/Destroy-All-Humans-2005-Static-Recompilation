import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';

const here = path.dirname(fileURLToPath(import.meta.url));
const sourcePath = path.join(here, '../src/recomp/gen/recomp_retail_late_tails_20261013.c');
const evidencePath = path.join(here, 'parity/retail_late_tails_20261013.json');
const source = fs.readFileSync(sourcePath, 'utf8');
const check = spawnSync('python', [path.join(here, 'lift_retail_late_tails_20261013.py'),
    '--source', sourcePath, '--evidence', evidencePath, '--check'],
    { encoding: 'utf8', timeout: 30000 });
assert.equal(check.status, 0, `${check.stdout}\n${check.stderr}`);
console.log(check.stdout.trim());

const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'dah-retail-late-'));
function run(label, body, expected) {
    const folder = path.join(temporary, label); fs.mkdirSync(folder);
    fs.writeFileSync(path.join(folder, 'retail_late_tails.inc'),
        body.replace('#include "recomp_funcs.h"', ''));
    const executable = path.join(folder, 'test.exe');
    const build = spawnSync('cl.exe', ['/nologo', '/W4', '/WX', '/O2', '/std:c11',
        `/I${folder}`, `/Fe:${executable}`, `/Fo:${path.join(folder, 'test.obj')}`,
        path.join(here, 'test_retail_late_tails_20261013.c')],
        { cwd: folder, encoding: 'utf8', timeout: 30000 });
    assert.equal(build.status, 0, `${build.error || ''}\n${build.stdout}\n${build.stderr}`);
    const test = spawnSync(executable, [], { cwd: folder, encoding: 'utf8', timeout: 30000 });
    if (expected) assert.notEqual(test.status, 0, `${test.error || ''}\n${test.stdout}\n${test.stderr}`);
    else assert.equal(test.status, 0, `${test.error || ''}\n${test.stdout}\n${test.stderr}`);
    console.log(expected ? `PASS negative control ${label}` : test.stdout.trim());
}
run('production', source, 0);
run('wrong-table-band', source.replace('eax = edi + 9u;', 'eax = edi + 8u;'), 1);
run('wrong-decoder-cleanup', source.replace('esp += 20u; /* ret 16 */', 'esp += 16u; /* negative control */'), 1);
run('wrong-range-cleanup', source.replace('esp += 40u; /* ret 36 */', 'esp += 36u; /* negative control */'), 1);
run('lost-os-error-clear', source.replace('MEM32(eax) = 0u;', 'MEM32(eax) = 1u;'), 1);
console.log(`TEST_OUTPUT ${temporary}`);
