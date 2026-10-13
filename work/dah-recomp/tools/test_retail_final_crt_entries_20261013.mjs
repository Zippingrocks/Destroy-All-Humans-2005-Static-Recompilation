/* Run from a Visual Studio developer shell. No game process is started. */
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';

const here=path.dirname(fileURLToPath(import.meta.url));
const gen=path.join(here,'../src/recomp/gen');
const sourcePath=path.join(gen,'recomp_retail_final_crt_entries_20261013.c');
const evidencePath=path.join(here,'analysis/retail_final_crt_entries_20261013.json');
const source=fs.readFileSync(sourcePath,'utf8');
const audit=spawnSync('python',[path.join(here,'lift_retail_final_crt_entries_20261013.py'),
    '--evidence',evidencePath,'--check'],{encoding:'utf8',timeout:30000});
assert.equal(audit.status,0,audit.stdout+audit.stderr);
console.log(audit.stdout.trim());

const temp=fs.mkdtempSync(path.join(os.tmpdir(),'dah-final-crt-'));
function run(label,code,expected){
    const folder=path.join(temp,label);fs.mkdirSync(folder);
    fs.writeFileSync(path.join(folder,'final_crt_entries.inc'),
        code.replace('#include "recomp_funcs.h"',''));
    const exe=path.join(folder,'test.exe');
    const build=spawnSync('cl.exe',['/nologo','/W4','/WX','/wd4101','/wd4102','/wd4189',
        '/O2','/std:c11',`/I${folder}`,`/Fe:${exe}`,`/Fo:${path.join(folder,'test.obj')}`,
        path.join(here,'test_retail_final_crt_entries_20261013.c')],
        {cwd:folder,encoding:'utf8',timeout:30000});
    assert.equal(build.status,0,`${build.error||''}\n${build.stdout}\n${build.stderr}`);
    const test=spawnSync(exe,[],{cwd:folder,encoding:'utf8',timeout:30000});
    assert.equal(test.status,expected,`${test.error||''}\n${test.stdout}\n${test.stderr}`);
    console.log(expected?`PASS negative control ${label}: ${test.stderr.trim()}`:test.stdout.trim());
}
run('production',source,0);
run('lost-nonlocal-pop',source.replace('POP32(esp, eax);','eax = MEM32(esp);'),1);
run('wrong-infinity',source.replace('fp_push(INFINITY);','fp_push(0.0);'),1);
run('wrong-descriptor-count',source.replace('MEM32(0x00287C08u) += 0x20u;',
    'MEM32(0x00287C08u) += 1u;'),1);
run('lost-registration-failure',source.replace('if (eax == 0u) MEM32(ebp - 28u) = 0xFFFFFFFFu;',
    'if (0) MEM32(ebp - 28u) = 0xFFFFFFFFu;'),1);
console.log(`TEST_OUTPUT ${temp}`);
