/* Run from a VS x64 developer shell. Both binaries use the production PGRAPH
 * translation unit; the negative build restores the actual old window choice. */
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import assert from 'node:assert/strict';
import {fileURLToPath} from 'node:url';
import {spawnSync} from 'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url));
const runtime=path.resolve(here,'../../../third_party/xboxrecomp');
const source=path.join(runtime,'src/nv2a/nv2a_pgraph_d3d11.c');
const directory=fs.mkdtempSync(path.join(os.tmpdir(),'dah-unlit-backing-'));
const before='int contiguous = program_kind == 14u || program_kind == 17u || program_kind == 18u;';
const after='int contiguous = program_kind == 17u || program_kind == 18u;';
const production=fs.readFileSync(source,'utf8');
assert.equal(production.split(before).length,2,'negative control must replace exactly one production window choice');
const oldSource=path.join(directory,'pgraph_old_window.c');
fs.writeFileSync(oldSource,production.replace(before,after));
for(const [label,input,expected] of [['fixed',source,0],['old-window',oldSource,1]]){
  const executable=path.join(directory,`${label}.exe`);
  const args=['/nologo','/O2','/Gy','/Gw','/std:c11','/DWIN32_LEAN_AND_MEAN','/DNOMINMAX',
    `/DDAH_PGRAPH_TEST_SOURCE="${input.replaceAll('\\','/')}"`,
    ...['src','include','src/kernel','src/nv2a','templates/runtime'].map(p=>`/I${path.join(runtime,p)}`),
    `/Fo:${path.join(directory,`${label}.obj`)}`,`/Fe:${executable}`,
    path.join(here,'test_unlit_backing.c'),'/link','/OPT:REF','d3d11.lib','dxgi.lib','dxguid.lib','d3dcompiler.lib'];
  const compile=spawnSync('cl.exe',args,{cwd:directory,encoding:'utf8',timeout:60000,windowsHide:true});
  assert.equal(compile.status,0,compile.error||compile.stdout+compile.stderr);
  const result=spawnSync(executable,[],{cwd:directory,encoding:'utf8',timeout:30000,windowsHide:true});
  assert.equal(result.status,expected,result.error||result.stdout+result.stderr);
  if(expected)assert.match(result.stderr,/wrong vertex backing:/,'old production code must fail at vertex output');
  console.log(expected?`PASS: old production window rejected: ${result.stderr.trim().split('\n').at(-1)}`:result.stdout.trim());
}
console.log(`TEST_OUTPUT ${directory}`);
