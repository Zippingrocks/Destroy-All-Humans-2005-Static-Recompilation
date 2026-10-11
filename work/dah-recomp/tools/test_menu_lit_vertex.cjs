const fs=require('fs'),path=require('path'),{spawnSync}=require('child_process');
const root=path.resolve(__dirname,'../../..');
const dir=fs.mkdtempSync(path.join(require('os').tmpdir(),'dah-lit-vertex-'));
const h=fs.readFileSync(root+'/Repos/xboxrecomp-main/src/nv2a/dah_menu_vertex.h','utf8');
const log=fs.readFileSync(root+'/work/dah-recomp/build-internal/recomp-internal-32784.log','utf8');
const words=[...log.matchAll(/\[DAH-3D-PROG\] k=\d+ got=([0-9A-F]+)/g)].slice(0,68).map(m=>m[1]);
const ref=fs.readFileSync(root+'/Repos/xemu/hw/xbox/nv2a/pgraph/glsl/vsh-prog.c','utf8');
const fields=[...ref.matchAll(/\{\s*(FLD_\w+),\s*(\d+),\s*(\d+),\s*(\d+)\s*\}/g)].map(m=>[m[1],...m.slice(2).map(Number)]);
fs.writeFileSync(dir+'/menu_vertex_original.inc',`enum Field {${fields.map(f=>f[0])}};\nstatic const unsigned field_map[][3]={${fields.map(f=>`{${f.slice(1)}}`)}};\nstatic const uint32_t original_program[17][4]={${Array.from({length:17},(_,i)=>'{'+words.slice(i*4,i*4+4).map(w=>'0x'+w+'u').join(',')+'}')}};\nstatic const unsigned used_constants[]={1,2,19,20,36,37,38,39,46,47,48,56,76,77,78,79};`);
let c=fs.readFileSync(root+'/work/dah-recomp/tools/test_menu_vertex.c','utf8').replaceAll('v[3][4]','v[4][4]').replaceAll('FLD_V)<3','FLD_V)<4').replaceAll('j<12','j<16').replaceAll('i<12;','i<16;').replaceAll('dah_menu_program_matches(', 'dah_menu_program_kind(').replaceAll('dah_menu_vertex(v[0],v[1],v[2],c,','dah_menu_vertex_impl(v[0],v[1],v[2],c,v[3],');
fs.writeFileSync(dir+'/test.c',c);fs.writeFileSync(dir+'/dah_menu_vertex_fixture.h',h);
for(const negative of [false,true]){
if(negative)fs.writeFileSync(dir+'/dah_menu_vertex_fixture.h',h.replace('color=color+extra[i]','color=color+0.0f*extra[i]'));
let r=spawnSync('cl.exe',['/nologo','/W4','/WX','/O2','/fp:strict','/std:c11','test.c','/Fe:test.exe'],{cwd:dir,encoding:'utf8'});if(r.status!==0)throw Error(r.stdout+r.stderr);
r=spawnSync(dir+'/test.exe',[],{encoding:'utf8'});console.log(negative?'Negative control:':'Production:',r.stdout,r.stderr);if(r.status!==(negative?1:0))process.exit(1);
}
fs.writeFileSync(dir+'/dah_menu_vertex_fixture.h',h);

