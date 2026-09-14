import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const code=fs.readFileSync(path.join(here,'../src/recomp/gen/recomp_frontend_callbacks.c'),'utf8');
const fixture=code.match(/^void sub_00104480\(void\)\r?\n\{[\s\S]*?^\}/m)?.[0]; assert(fixture);
const directory=fs.mkdtempSync(path.join(os.tmpdir(),'dah-frontend-vector-'));
for(const [name,body,expected] of [['current',fixture,0],['wrong-vector-address',fixture.replace('edx = esp + 0x14u;','edx = esp + 0x18u;'),1]]) {
    fs.writeFileSync(path.join(directory,'frontend_vector_fixture.inc'),body);
    const exe=path.join(directory,`${name}.exe`);
    const compile=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/std:c11',`/I${directory}`,`/Fe:${exe}`,`/Fo:${path.join(directory,name+'.obj')}`,path.join(here,'test_frontend_vector.c')],{cwd:directory,encoding:'utf8',timeout:30000});
    assert.equal(compile.status,0,compile.stdout+compile.stderr);
    const run=spawnSync(exe,[],{cwd:directory,encoding:'utf8',timeout:30000}); assert.equal(run.status,expected,run.stdout+run.stderr);
    console.log(expected?`PASS: rejected ${name}: ${run.stderr.trim()}`:run.stdout.trim());
}
console.log(`TEST_OUTPUT ${directory}`);
