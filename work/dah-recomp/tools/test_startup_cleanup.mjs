// Run from a Visual Studio x64 developer prompt. No game or desktop activity.
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import { fileURLToPath } from 'node:url';
import { spawnSync } from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const original=spawnSync('python',[path.join(here,'lift_startup_cleanup.py')],{encoding:'utf8'});
assert.equal(original.status,0,original.stderr);
const verified=JSON.parse(original.stdout);
const source=fs.readFileSync(path.join(here,'../src/recomp/gen/recomp_startup_cleanup.c'),'utf8');
assert.equal(source.replace(/\r/g,'').trim(),verified.code.trim(),'Production source differs from byte-checked lift');
console.log(`PASS: ${verified.details.reduce((n,x)=>n+x.bytes,0)} original XBE bytes; ${verified.details.length} complete retail cleanup lifts`);
const fixture=source.replace(/^#include "recomp_funcs.h"\r?\n/m,'');
const temp=fs.mkdtempSync(path.join(os.tmpdir(),'dah-cleanup-test-'));
for(const [label,body,expected] of [['current',fixture,0],['wrong-ret',fixture.replaceAll('esp += 8; return; /* ret 4 */','esp += 4; return; /* ret 4 */'),1],['signed-event-clock',fixture.replace('CMP_B(_fa, _fb)','((int32_t)_fa < (int32_t)_fb)'),1]]) {
    const directory=path.join(temp,label); fs.mkdirSync(directory);
    fs.writeFileSync(path.join(directory,'startup_cleanup_fixture.inc'),body);
    const exe=path.join(directory,'test.exe');
    const compile=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11',`/I${directory}`,`/Fe:${exe}`,`/Fo:${path.join(directory,'test.obj')}`,path.join(here,'test_startup_cleanup.c')],{cwd:directory,encoding:'utf8',timeout:30000});
    assert.equal(compile.status,0,compile.stdout+compile.stderr);
    const run=spawnSync(exe,[],{cwd:directory,encoding:'utf8',timeout:30000});
    assert.equal(run.status,expected,run.stdout+run.stderr);
    console.log(label==='current'?run.stdout.trim():`PASS: rejected ${label}: ${run.stderr.trim()}`);
}
console.log(`TEST_OUTPUT ${temp}`);
