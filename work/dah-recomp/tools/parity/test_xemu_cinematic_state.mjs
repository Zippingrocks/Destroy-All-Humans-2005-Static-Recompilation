import assert from 'node:assert/strict';
import test from 'node:test';
import {spawnSync} from 'node:child_process';
import {randomUUID} from 'node:crypto';
import {fileURLToPath} from 'node:url';
import os from 'node:os';
import path from 'node:path';
import {readCinematicState} from './xemu_cinematic_state.mjs';

function fixture(count=1,high=false){
 const bytes=Buffer.alloc(4*1024*1024),base=high?0x80000000:0;
 const manager=base+0x300000,sentinel=manager+8;
 const movies=Array.from({length:count},(_,i)=>base+0x310000+i*0x100);
 const nodes=movies.map(p=>p+4),word=(a,v)=>bytes.writeUInt32LE(v,a&0x7fffffff);
 word(0x286784,manager);word(manager,0x22a6b8);word(sentinel,nodes[0]??sentinel);
 word(manager+12,nodes.at(-1)??sentinel);word(manager+0x18,count);
 movies.forEach((p,i)=>{
  word(p,0x236100);word(p+4,nodes[i+1]??sentinel);word(p+8,nodes[i-1]??sentinel);word(p+12,p);
  word(p+0x20,0x98760000+i);word(p+0x68,0x42c60000);word(p+0x6c,0x3f000001+i);word(p+0x70,2);word(p+0x74,2);
 });
 const read=async(a,n)=>{const offset=a&0x7fffffff;if(offset+n>bytes.length)throw Error('Guest read failed');return bytes.subarray(offset,offset+n);};
 return {bytes,manager,sentinel,movies,nodes,word,read};
}
test('one high-address cinematic retains exact elapsed bits and identity',async()=>{
 const f=fixture(1,true),s=await readCinematicState(f.read);
 assert.equal(s.cinematicComplete,true);assert.equal(s.cinematicReason,null);
 assert.deepEqual(s.cinematics[0],{node:f.nodes[0],object:f.movies[0],vtable:0x236100,
  nameHash:0x98760000,durationBits:0x42c60000,elapsedBits:0x3f000001,flags:2,state:2,complete:true});
 assert.equal(s.cinematicMemoryReads,4);assert.equal(s.cinematicMemoryBytes,164);
});
test('null manager and empty manager are explicitly empty',async()=>{
 const f=fixture(0);let s=await readCinematicState(f.read);
 assert.equal(s.cinematicComplete,true);assert.deepEqual(s.cinematics,[]);assert.equal(s.cinematicDeclaredCount,0);
 f.word(0x286784,0);s=await readCinematicState(f.read);
 assert.equal(s.cinematicComplete,true);assert.deepEqual(s.cinematics,[]);assert.equal(s.cinematicDeclaredCount,null);
});
test('base manager constructor layout is accepted alongside derived game manager',async()=>{
 const f=fixture();f.word(f.manager,0x23611c);const s=await readCinematicState(f.read);
 assert.equal(s.cinematicComplete,true);assert.equal(s.cinematicManagerVtable,0x23611c);
});
test('derived movie constructor retains the proven timeline prefix',async()=>{
 const f=fixture();f.word(f.movies[0],0x229fb4);const s=await readCinematicState(f.read);
 assert.equal(s.cinematicComplete,true);assert.equal(s.cinematics[0].vtable,0x229fb4);
 assert.equal(s.cinematics[0].elapsedBits,0x3f000001);
});
test('unmapped and invalid pointers are unknown, never invented zeros',async()=>{
 const f=fixture();f.word(0x286784,0xf0000000);let s=await readCinematicState(f.read);
 assert.equal(s.cinematicReason,'invalid guest RAM address');assert.equal(s.cinematics,null);assert.equal(s.cinematicMemoryReads,1);
 f.word(0x286784,0x500000);s=await readCinematicState(f.read);
 assert.equal(s.cinematicReason,'guest memory unavailable');assert.equal(s.cinematics,null);
});
test('class mismatches keep dependent fields null',async()=>{
 const f=fixture();f.word(f.movies[0],0x123456);let s=await readCinematicState(f.read);
 assert.equal(s.cinematicComplete,false);assert.equal(s.cinematicReason,'unexpected cinematic movie vtable');
 assert.equal(s.cinematics[0].elapsedBits,null);assert.equal(s.cinematics[0].vtable,0x123456);
 f.word(f.manager,0x123456);s=await readCinematicState(f.read);assert.equal(s.cinematics,null);
 assert.equal(s.cinematicDeclaredCount,null);assert.equal(s.cinematicReason,'unexpected cinematic manager vtable');
});
test('cycles, inconsistent links/counts, and duplicate objects stay incomplete',async()=>{
 for(const [edit,reason] of [
  [f=>f.word(f.nodes[0],f.nodes[0]),'cyclic cinematic list'],
  [f=>f.word(f.nodes[0],0),'null cinematic list link'],
  [f=>f.word(f.nodes[0]+4,0),'cinematic previous-link mismatch'],
  [f=>f.word(f.manager+12,f.sentinel),'cinematic tail-link mismatch'],
  [f=>f.word(f.manager+0x18,2),'cinematic count mismatch']]){
  const f=fixture();edit(f);const s=await readCinematicState(f.read);assert.equal(s.cinematicComplete,false);assert.equal(s.cinematicReason,reason);
 }
 const f=fixture(2);f.word(f.nodes[1]+8,f.movies[0]);const s=await readCinematicState(f.read);
 assert.equal(s.cinematicReason,'duplicate cinematic object');assert.equal(s.cinematics[1].elapsedBits,null);
});
test('16-entry hard bound and 34-read/2144-byte maximum',async()=>{
 for(const count of [16,17]){const f=fixture(count),s=await readCinematicState(f.read);
  assert.equal(s.cinematics.length,16);assert.equal(s.cinematicMemoryReads,34);assert.equal(s.cinematicMemoryBytes,2144);
  assert.equal(s.cinematicComplete,count===16);assert.equal(s.cinematicReason,count===16?null:'cinematic list exceeds 16 entries');
 }
});
test('all lifecycle values retained; invalid lifecycle explicit',async()=>{
 const f=fixture();for(let state=0;state<=4;++state){f.word(f.movies[0]+0x74,state);const s=await readCinematicState(f.read);
  assert.equal(s.cinematics[0].state,state);assert.equal(s.cinematics[0].complete,state<=3);assert.equal(s.cinematicComplete,state<=3);
 }
});
test('short reads remain unknown; transport timeout aborts',async()=>{
 const s=await readCinematicState(async()=>Buffer.alloc(3));assert.equal(s.cinematicReason,'short guest memory read');assert.equal(s.cinematicManager,null);
 await assert.rejects(readCinematicState(async()=>{throw Error('GDB response timed out');}),/timed out/);
});
test('CLI cinematic flag without state output rejects before reading script or connecting',()=>{
 const replay=fileURLToPath(new URL('./xemu_input_replay.mjs',import.meta.url));
 const result=spawnSync(process.execPath,[replay,'--script','unused-not-read.txt',
  '--out',path.join(os.tmpdir(),randomUUID()+'.json'),'--cinematic-state'],{encoding:'utf8',windowsHide:true});
 assert.notEqual(result.status,0);assert.match(result.stderr,/--cinematic-state requires --state-out/);
 assert.doesNotMatch(result.stderr,/ENOENT|ECONNREFUSED/);
});
