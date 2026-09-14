/* Actual header versus an independent decoded-word interpreter; no game,
 * window, renderer bypass, generated image or host GPU dependency. */
import fs from 'node:fs';import path from 'node:path';import os from 'node:os';import assert from 'node:assert/strict';import {fileURLToPath}from'node:url';import{spawnSync}from'node:child_process';
const here=path.dirname(fileURLToPath(import.meta.url)),root=path.resolve(here,'../../..');
const header=fs.readFileSync(path.join(root,'Repos/xboxrecomp-main/src/nv2a/dah_menu_vertex.h'),'utf8');
const log=fs.readFileSync(path.join(here,'../build-internal/recomp-internal-16548.log'),'utf8');
const segment=log.slice(log.indexOf('[DAH-REJECTED-STATE] submit=771'),log.indexOf('[DAH-REJECTED-STATE] submit=772'));
const program=[...segment.matchAll(/\[DAH-REJECTED-SHADER\] instruction=(\d+) raw=([0-9A-F,]+)/g)].map((m,i)=>{assert.equal(+m[1],i);return m[2].split(',').map(n=>parseInt(n,16));});assert.equal(program.length,17);
const ref=fs.readFileSync(path.join(root,'Repos/xemu/hw/xbox/nv2a/pgraph/glsl/vsh-prog.c'),'utf8');
const fields=[...ref.matchAll(/\{\s*(FLD_\w+),\s*(\d+),\s*(\d+),\s*(\d+)\s*\}/g)].map(m=>[m[1],...m.slice(2).map(Number)]);
assert.equal(fields.length,35);const fieldMap=Object.fromEntries(fields.map(([n,...bits])=>[n,bits]));
function get(p,name){const[w,s,b]=fieldMap['FLD_'+name];return(p[w]>>>s)&((1<<b)-1);}
const referenced=new Set();const params=[[],['A'],['A','B'],['A','C'],['A','B','C'],['A','B'],['A','B'],['A','B']];
for(const p of program){const m=get(p,'MAC'),u=get(p,'ILU');assert(m<=7);for(const n of[...params[m],...(u?['C']:[])])if(get(p,n+'_MUX')===3)referenced.add(get(p,'CONST'));assert.equal(get(p,'A0X'),0);}
assert.deepEqual([...referenced].sort((a,b)=>a-b),[1,2,19,20,36,37,38,39,46,47,48,56,76,77,78,79]);
// Replay the captured pushbuffer's upload packets too. Logging supplies the
// retained complete program; each program word present in this particular
// packet range must agree with that retained state.
const capture=fs.readFileSync(path.join(here,'../build-internal/dah_pb_rejected_16548_000771.bin'));
const words=Array.from({length:capture.length/4},(_,i)=>capture.readUInt32LE(i*4));let upload=null,verified=0,constants=null;const capturedConst=new Map();
const resident=new Map();
for(let i=0;i<words.length;){
 const h=words[i];if(!h){++i;continue;}
 const kind=h>>>29;if(kind!==0&&kind!==2){++i;continue;}
 const count=(h>>>18)&0x7ff,start=h&0x1ffc;if(!count||i+count>=words.length){++i;continue;}
 for(let j=0;j<count;++j){
  const method=start+(kind===2?0:j*4),value=words[i+1+j];
  if(method===0x1e9c)upload=value*4;
  else if(method>=0xb00&&method<0xb80&&upload!==null)resident.set(upload++,value);
  else if(method===0x1ea4)constants=value*4;
  else if(method>=0xb80&&method<0xc00&&constants!==null)capturedConst.set(constants++,value);
  // The same ring contains later UI draws with a different program. Match
  // the shader at a draw boundary, not every subsequent upload in that ring.
  if(method===0x17fc&&value!==0){
   let matching=0,mismatch=false;
   for(let k=0;k<68;++k)if(resident.has(k)){
    if(resident.get(k)!==program[k>>2][k&3])mismatch=true;else matching++;
   }
   if(!mismatch)verified=Math.max(verified,matching);
  }
 }
 i+=count+1;
}
assert.equal(verified,68,'Complete original program must be present at a captured draw');
const original=`enum Field {${fields.map(f=>f[0]).join(',')}};\nstatic const unsigned field_map[][3]={${fields.map(f=>`{${f.slice(1)}}`).join(',')}};\n`+
`static const uint32_t original_program[17][4]={${program.map(p=>`{${p.map(w=>'0x'+w.toString(16)+'u')}}`).join(',')}};\n`+
`static const unsigned used_constants[]={${[...referenced].sort((a,b)=>a-b)}};\n`;
console.log(`PASS source:17 logged shader slots,${verified} captured upload words cross-checked,${capturedConst.size} captured constant words; local xemu35-field decoder`);
const temporary=fs.mkdtempSync(path.join(os.tmpdir(),'dah-menu-vertex-'));
function test(label,text,status){const dir=path.join(temporary,label);fs.mkdirSync(dir);fs.writeFileSync(path.join(dir,'dah_menu_vertex_fixture.h'),text);fs.writeFileSync(path.join(dir,'menu_vertex_original.inc'),original);const exe=path.join(dir,'test.exe'),build=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/fp:strict','/std:c11',`/I${dir}`,`/Fe:${exe}`,`/Fo:${path.join(dir,'test.obj')}`,path.join(here,'test_menu_vertex.c')],{cwd:dir,encoding:'utf8',timeout:30000});assert.equal(build.status,0,build.stdout+build.stderr);const run=spawnSync(exe,[],{cwd:dir,encoding:'utf8',timeout:30000});assert.equal(run.status,status,run.stdout+run.stderr);console.log(status?`PASS negative control ${label}: ${run.stderr.trim()}`:run.stdout.trim());}
test('production',header,0);
test('missing-perspective',header.replace('scaled*reciprocal+c[1][i]','scaled+c[1][i]+reciprocal*0.0f'),1);
test('wrong-dph-w',header.replace('dah_menu_dot3(pos,c[36+i])+c[36+i][3]','dah_menu_dot4(pos,c[36+i])'),1);
test('unclamped-lit',header.replace('fmaxf(dah_menu_dot3(normal,c[46]),0.0f)','dah_menu_dot3(normal,c[46])'),1);
test('wrong-alpha-mask',header.replace('if(i<3u)','if(i<4u)'),1);
test('wrong-texture-input',header.replaceAll('dah_menu_dot4(tex,','dah_menu_dot4(pos,'),1);
test('missing-program-validity',header.replace('!valid[i] || words[i]','words[i]'),1);
test('missing-constant-validity',header.replace('!valid[used[i]*4u+j] || !isfinite','!isfinite'),1);
test('missing-rcc-upper-clamp',header.replace('if(magnitude>0x1p64f) magnitude=0x1p64f;','/* omitted upper clamp */'),1);
console.log(`TEST_OUTPUT ${temporary}`);
