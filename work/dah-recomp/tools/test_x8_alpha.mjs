/* Run from a VS x64 developer shell: node tools/test_x8_alpha.mjs */
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const runtime=path.resolve(here,'../../../third_party/xboxrecomp');
const directory=fs.mkdtempSync(path.join(os.tmpdir(),'dah-x8-alpha-'));
const executable=path.join(directory,'x8-alpha.exe');
const args=['/nologo','/O2','/Gy','/Gw','/std:c11','/DWIN32_LEAN_AND_MEAN','/DNOMINMAX',
  ...['src','include','src/kernel','templates/runtime'].map(p=>`/I${path.join(runtime,p)}`),
  `/Fo:${path.join(directory,'x8-alpha.obj')}`,`/Fe:${executable}`,path.join(here,'test_x8_alpha.c'),
  '/link','/OPT:REF','d3d11.lib','dxgi.lib','dxguid.lib','d3dcompiler.lib'];
const compile=spawnSync('cl.exe',args,{cwd:directory,encoding:'utf8',timeout:60000});
assert.equal(compile.status,0,compile.error||compile.stdout+compile.stderr);
for(const negative of ['', '--old-stored-alpha']){
  const result=spawnSync(executable,negative?[negative]:[],{cwd:directory,encoding:'utf8',timeout:30000});
  assert.equal(result.status,negative?1:0,result.error||result.stdout+result.stderr);
  console.log(negative?`PASS: negative control ${negative}: ${result.stderr.trim()}`:result.stdout.trim());
}
console.log(`TEST_OUTPUT ${directory}`);
