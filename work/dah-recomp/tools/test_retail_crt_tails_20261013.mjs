/* Run from a Visual Studio developer shell. No game process is started. */
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const root=path.resolve(here,'../../..');
const gen=path.join(here,'../src/recomp/gen');
const source=fs.readFileSync(path.join(gen,'recomp_retail_crt_tails_20261013.c'),'utf8');
const xbe=fs.readFileSync(path.join(root,'default.xbe'));
const table=xbe.readUInt32LE(0x120)-xbe.readUInt32LE(0x104);
const sections=Array.from({length:xbe.readUInt32LE(0x11C)},(_,i)=>{const p=table+i*56;return{va:xbe.readUInt32LE(p+4),raw:xbe.readUInt32LE(p+12),size:xbe.readUInt32LE(p+16)};});
function raw(va,size){const s=sections.find(s=>va>=s.va&&va+size<=s.va+s.size);assert(s);return xbe.subarray(s.raw+va-s.va,s.raw+va-s.va+size);}
function body(text,address){const m=text.match(new RegExp(`^void sub_${address}\\(void\\)\\r?\\n\\{[\\s\\S]*?^\\}`,'m'));assert(m,address);return m[0];}
const original14=fs.readFileSync(path.join(gen,'recomp_0014.c'),'utf8');
const original15=fs.readFileSync(path.join(gen,'recomp_0015.c'),'utf8');
const helpers=['0013A120','0013A15B','0013F6C8','0013F6D1'].map(a=>body(original14,a)).concat(['001425CA','0014272A'].map(a=>body(original15,a))).join('\n');
// Original bytes explicitly anchor the real production SEH helpers used here.
assert.equal(raw(0x13A120,59).toString('hex'),'6874a1130064a100000000508b442410896c24108d6c24102be05356578b45f88965e8508b45fcc745fcffffffff8945f88d45f064a300000000c3');
assert.equal(raw(0x13A15B,17).toString('hex'),'8b4df064890d00000000595f5e5bc951c3');
let calls=0;
for(const m of (source+'\n'+helpers).matchAll(/PUSH32\(esp, 0x([0-9A-F]+)u\); sub_([0-9A-F]+)\(\);/g)){
    const ret=parseInt(m[1],16),ins=raw(ret-5,5);assert.equal(ins[0],0xE8);
    assert.equal((ret+ins.readInt32LE(1))>>>0,parseInt(m[2],16));++calls;
}
const generate=spawnSync('python',[path.join(here,'lift_retail_crt_tails_20261013.py'),'--source',path.join(gen,'recomp_retail_crt_tails_20261013.c'),'--evidence',path.join(here,'analysis/retail_crt_tails_20261013.json'),'--check'],{encoding:'utf8',timeout:30000});
assert.equal(generate.status,0,generate.stdout+generate.stderr);
console.log(generate.stdout.trim());
console.log(`PASS: ${calls} direct-call target/return PCs and production SEH bytes checked`);
const temp=fs.mkdtempSync(path.join(os.tmpdir(),'dah-crt-tails-'));
function run(label,code,expected){
    const folder=path.join(temp,label);fs.mkdirSync(folder);
    fs.writeFileSync(path.join(folder,'crt_helpers.inc'),helpers);
    fs.writeFileSync(path.join(folder,'crt_tails.inc'),code.replace('#include "recomp_funcs.h"',''));
    const exe=path.join(folder,'test.exe');
    const build=spawnSync('cl.exe',['/nologo','/W4','/WX','/wd4101','/wd4102','/wd4189','/O2','/std:c11',`/I${folder}`,`/Fe:${exe}`,`/Fo:${path.join(folder,'test.obj')}`,path.join(here,'test_retail_crt_tails_20261013.c')],{cwd:folder,encoding:'utf8',timeout:30000});
    assert.equal(build.status,0,`${build.error||''}\n${build.stdout}\n${build.stderr}`);
    const test=spawnSync(exe,[],{cwd:folder,encoding:'utf8',timeout:30000});
    assert.equal(test.status,expected,`${test.error||''}\n${test.stdout}\n${test.stderr}`);
    console.log(expected?`PASS: negative control ${label}: ${test.stderr.trim()}`:test.stdout.trim());
}
run('production',source,0);
run('wrong-os-error',source.replaceAll('MEM32(eax) = MEM32(eax) & 0;','MEM32(eax) = 1;'),1);
run('lost-seh-frame',source.replaceAll('g_seh_ebp = ebp; /* publish frame to SEH helper */','/* negative control: frame not published */'),1);
run('wrong-flush-result',source.replace('if (CMP_EQ(_fa, _fb)) goto loc_00142724;','if (CMP_NE(_fa, _fb)) goto loc_00142724;'),1);
run('free-static-stream',source.replace('(uint32_t)(0x14) & 0xFFFFFFFFu','(uint32_t)(0x13) & 0xFFFFFFFFu'),1);
console.log(`TEST_OUTPUT ${temp}`);
