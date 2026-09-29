import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here = path.dirname(fileURLToPath(import.meta.url));
const manual = fs.readFileSync(path.join(here,'../src/recomp_manual.c'),'utf8');
const fixture = manual.match(/^uint32_t dah_monotonic_milliseconds\(void\)\r?\n\{[\s\S]*?^\}/m)?.[0];
assert(fixture);
const xbe = fs.readFileSync(path.join(here,'../../default.xbe'));
const table = xbe.readUInt32LE(0x120)-xbe.readUInt32LE(0x104);
let code;
for (let i=0;i<xbe.readUInt32LE(0x11c);i++) {
  const p=table+i*56, va=xbe.readUInt32LE(p+4), size=xbe.readUInt32LE(p+16);
  if (0xd83e0>=va && 0xd83fc<=va+size) {
    const offset=xbe.readUInt32LE(p+12)+0xd83e0-va;
    code=xbe.subarray(offset,offset+28);
  }
}
assert.equal(code?.toString('hex'),'0f316a006a035250e8b31906006a0068c09121005250e805220600c3');
const inputs=[0n,1n,733333n,733334n,1466666n,1466667n,2200000n,733333333n,
  3149642683000000n,3149642683733334n,9000000000000000n,0x7fffffffffffffffn,0xffffffffffffffffn];
for(let i=0;i<3000;i++)inputs.push(BigInt(i)*1234567890123n);
const cases=inputs.map(t=>`{${t}ULL,${((t*3n)&0xffffffffffffffffn)/2200000n&0xffffffffn}u}`).join(',\n');
const folder=fs.mkdtempSync(path.join(os.tmpdir(),'dah-retail-clock-'));
function run(name, body, expectedStatus) {
  const source=path.join(folder,name+'.c'), exe=path.join(folder,name+'.exe');
  fs.writeFileSync(source,`#include <stdint.h>\n#include <stdio.h>\nstatic uint64_t ticks;\nstatic uint64_t dah_read_tsc(void){return ticks;}\nstatic uint64_t GetTickCount64(void){return 123456;}\n${body}\nint main(void){struct {uint64_t ticks;uint32_t result;} cases[]={${cases}};for(unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);i++){ticks=cases[i].ticks;if(dah_monotonic_milliseconds()!=cases[i].result){fprintf(stderr,"clock mismatch case=%u\\n",i);return 1;}}printf("PASS %u byte-verified retail-clock cases\\n",(unsigned)(sizeof(cases)/sizeof(cases[0])));return 0;}\n`);
  const compile=spawnSync('cl.exe',['/nologo','/O2',source,`/Fe:${exe}`,`/Fo:${path.join(folder,name+'.obj')}`],{encoding:'utf8'});
  assert.equal(compile.status,0,compile.stdout+compile.stderr);
  const result=spawnSync(exe,[],{encoding:'utf8'});
  assert.equal(result.status,expectedStatus,result.stdout+result.stderr);
  console.log(name+': '+(result.stdout||result.stderr).trim());
}
run('production',fixture,0);
run('coarse-clock-negative-control','uint32_t dah_monotonic_milliseconds(void){return (uint32_t)GetTickCount64();}',1);
