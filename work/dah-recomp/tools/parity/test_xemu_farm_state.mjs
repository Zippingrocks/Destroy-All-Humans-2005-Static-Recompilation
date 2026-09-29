import assert from 'node:assert/strict';
import test from 'node:test';
import {readFarmState,FARM_STATE_MAX_READS,FARM_STATE_MAX_BYTES} from './xemu_farm_state.mjs';

function fixture(){
 const memory=new Map();
 const set=(address,bytes)=>{for(let i=0;i<bytes.length;i++)memory.set(address+i,bytes[i]);};
 const word=(a,n)=>{const b=Buffer.alloc(4);b.writeUInt32LE(n);set(a,b);};
 const current=0x25e3f4,world=0x83000100,renderer=0x260000;
 word(0x25b1d0,0x22b510);word(0x25b1d0+0x4a28,current);word(0x25b1d0+0x4a2c,0);
 word(current+0x10,22);const name=Buffer.alloc(128);name.write('blocks\\sites\\farm');set(current+0x50c,name);
 word(0x250e60,renderer);set(renderer+0x238,Buffer.alloc(0x94));word(renderer+0x238,1);word(renderer+0x27c,2);word(renderer+0x2c8,2);
 word(0x286768,world);set(world,Buffer.alloc(20));word(world,0x235780);word(world+8,456);word(world+12,0x42c80000);word(world+16,0x3d088889);set(world+0x303c,Buffer.from([0,1]));
 word(0x278a58,0xabcdef01);set(0x2867f4,Buffer.alloc(0x2c));word(0x2867f8,2);
 word(0x25fcec,0);set(0x258b48,Buffer.from([1]));set(renderer,Buffer.alloc(0xf0));
 let reads=0;
 const read=async(a,n)=>{++reads;const b=Buffer.alloc(n);for(let i=0;i<n;i++){if(!memory.has(a+i))throw Error('Guest read failed');b[i]=memory.get(a+i);}return b;};
 return {read,word,set,memory,world,renderer,reads:()=>reads};
}

test('high guest world address, absent movie/backend, exact float bits, bounded reads',async()=>{
 const f=fixture(),s=await readFarmState(f.read,800,700);
 assert.equal(s.phase,'XInputGetState');assert.equal(s.timingPerturbed,true);assert.equal(s.relativeFrame,100);
 assert.equal(s.backendName,'blocks\\sites\\farm');assert.equal(s.backendState,22);assert.equal(s.worldElapsedBits,0x42c80000);
 assert.equal(s.worldTick,456);assert.equal(s.worldRealtime,1);assert.equal(s.refresh,60);assert.equal(s.divisor,2);
 assert.equal(s.rngState,0xabcdef01);assert.equal(s.complete,true);assert.equal(s.movieHeader,null);
 assert.deepEqual(s.absent,['pendingBackend','movie','controlSystem','cameraNode']);
 assert.equal(s.worldComplete,true);assert.equal(s.playerComplete,false);assert.equal(s.cameraComplete,false);
 assert.ok(s.memoryReads<=FARM_STATE_MAX_READS&&s.memoryBytes<=FARM_STATE_MAX_BYTES);
});
test('invalid pointer stays unknown and is never dereferenced',async()=>{
 const f=fixture();f.word(0x286768,0xfd000000);const s=await readFarmState(f.read,1,0);
 assert.equal(s.worldTick,null);assert.equal(s.unknown.worldTick,'invalid world pointer');assert.equal(s.complete,false);
});
test('unexpected world class does not invent elapsed values',async()=>{
 const f=fixture();f.word(f.world,0x123456);const s=await readFarmState(f.read,1,0);
 assert.equal(s.worldVtable,0x123456);assert.equal(s.worldElapsedBits,null);assert.equal(s.unknown.worldElapsedBits,'unexpected world vtable');
});
test('unavailable memory is explicit while transport failures abort',async()=>{
 const f=fixture();f.memory.delete(0x278a58);const s=await readFarmState(f.read,1,0);
 assert.equal(s.rngState,null);assert.equal(s.unknown.rngState,'guest memory unavailable');
 await assert.rejects(readFarmState(async()=>{throw Error('GDB response timed out');},1,0),/timed out/);
});

function populated(){
 const f=fixture(),control=0x300000,player=0x300100,actor=0x310000,movement=0x320000,node=0x330000;
 f.word(0x25fcec,control);f.set(control,Buffer.alloc(0x3c));f.word(control+0x38,player);
 f.set(player,Buffer.alloc(0x3c));f.word(player,0x123400);f.word(player+0x30,actor);
 f.word(player+0x34,0x345600);f.word(player+0x38,actor);
 f.set(actor,Buffer.alloc(0x158));f.word(actor,0x22c9f8);f.word(actor+0x130,movement);
 const position=[0x3f800000,0xbf800000,0x80000000];position.forEach((v,i)=>f.word(actor+0x14c+4*i,v));
 f.set(movement,Buffer.alloc(0x4c));f.word(movement+0x14,0x3dcccccd);
 f.word(movement+0x18,0x40000000);f.word(movement+0x48,7);
 f.set(movement+0x2ac,Buffer.alloc(8));f.word(movement+0x2ac,0x40400000);
 f.word(movement+0x2b0,0x40800000);
 const actorObject=0x360000,actorNode=0x370000,body=0x380000,physicsInner=0x390000;
 f.word(actor+0x28,actorObject);f.word(actor+0x4a0,actorNode);f.word(actor+0x110,body);
 f.set(actorObject,Buffer.alloc(0x50));f.word(actorObject,actorNode);f.word(actorObject+0x4c,3);
 f.set(actorNode,Buffer.alloc(0x90));f.word(actorNode,0x234308);f.word(actorNode+8,0x11223344);
 f.set(body,Buffer.alloc(0x90));f.word(body,0x2376e8);f.word(body+0x0c,physicsInner);
 f.word(0x2376e8+0x90,0x12bb30);f.set(physicsInner,Buffer.alloc(0x48));f.word(physicsInner,0x237968);
 for(const [p,offset,count,base] of [[actorObject,0x2c,3,0x40000000],[actorObject,0x38,4,0x3e800000],
  [actorNode,0x40,4,0x3e000000],[actorNode,0x50,16,0x3f000000],[body,0x84,3,0xbea74000],
  [physicsInner,0x38,4,0x3d800000]])
  for(let i=0;i<count;i++)f.word(p+offset+4*i,base+i);
 f.word(f.renderer+0xec,node);f.set(node,Buffer.alloc(0x90));f.word(node+8,0x334400);
 for(let i=0;i<16;i++)f.word(node+0x50+4*i,0x3f000000+i);
 for(let i=0;i<4;i++)f.word(node+0x40+4*i,0x3e000000+i);
 for(let i=0;i<3;i++){f.word(node+0x20+4*i,0x40000000+i);f.word(f.renderer+0x80+4*i,0x41000000+i);f.word(f.renderer+0x70+4*i,0x42000000+i);}
 const pending=0x340000;f.word(0x25b1d0+0x4a2c,pending);f.word(pending+0x10,19);
 const name=Buffer.alloc(128);name.write('blocks\\sites\\farm');f.set(pending+0x50c,name);
 const movie=0x350000;f.word(0x28681c,movie);f.set(movie,Buffer.alloc(24));
 return {...f,control,player,actor,movement,node,position,actorObject,actorNode,body,physicsInner};
}
test('all source-proven trajectory and motion fields fit the explicit read/byte budget',async()=>{
 const f=populated(),s=await readFarmState(f.read,900,700);
 assert.equal(s.complete,true);assert.equal(s.playerFocus,f.actor);assert.equal(s.playerCrypto,f.actor);
 assert.equal(s.playerShip,0x345600);assert.equal(s.actor,f.actor);assert.equal(s.moveState,7);
 assert.equal(s.movementAngularVelocityBits,0x3dcccccd);
 assert.equal(s.movementHeadingBits,0x40000000);
 assert.deepEqual(s.movementSteeringBits,[0x40400000,0x40800000]);
 assert.equal(s.movementMotionComplete,true);
 assert.deepEqual(s.actorPositionBits,f.position);assert.equal(s.cameraNodeParent,0x334400);
 assert.deepEqual(s.cameraQuatBits,[0x3e000000,0x3e000001,0x3e000002,0x3e000003]);
 assert.deepEqual(s.cameraWorldBits,Array.from({length:16},(_,i)=>0x3f000000+i));
 assert.deepEqual(s.cameraLocalBits,[0x40000000,0x40000001,0x40000002]);
 assert.deepEqual(s.cameraViewPositionBits,[0x41000000,0x41000001,0x41000002]);
 assert.deepEqual(s.cameraViewForwardBits,[0x42000000,0x42000001,0x42000002]);
 for(const key of ['world','pendingBackend','rngState','cameraUpdate','player','actor','moveState','camera',
  'actorObject','actorSceneNode','physicsBody'])assert.equal(s[key+'Complete'],true,key);
 assert.equal(s.actorObject,f.actorObject);assert.equal(s.actorObjectFlags,3);
 assert.deepEqual(s.actorObjectPositionBits,[0x40000000,0x40000001,0x40000002]);
 assert.deepEqual(s.actorObjectQuatBits,[0x3e800000,0x3e800001,0x3e800002,0x3e800003]);
 assert.equal(s.actorSceneNode,f.actorNode);assert.equal(s.actorSceneNodeVtable,0x234308);
 assert.equal(s.actorSceneNodeParent,0x11223344);
 assert.deepEqual(s.actorSceneQuatBits,[0x3e000000,0x3e000001,0x3e000002,0x3e000003]);
 assert.deepEqual(s.actorSceneWorldBits,Array.from({length:16},(_,i)=>0x3f000000+i));
 assert.equal(s.physicsBody,f.body);assert.equal(s.physicsBodyVtable,0x2376e8);
 assert.equal(s.physicsVelocitySetter,0x12bb30);
 assert.deepEqual(s.physicsVelocityBits,[0xbea74000,0xbea74001,0xbea74002]);
 assert.equal(s.physicsInner,f.physicsInner);assert.equal(s.physicsInnerVtable,0x237968);
 assert.deepEqual(s.physicsInnerQuatBits,[0x3d800000,0x3d800001,0x3d800002,0x3d800003]);
 assert.equal(s.physicsInnerComplete,true);
 assert.equal(FARM_STATE_MAX_READS,29);assert.equal(FARM_STATE_MAX_BYTES,2048);
 assert.equal(s.memoryReads,29);assert.equal(s.memoryBytes,1911);assert.equal(f.reads(),29);
 assert.equal('observer' in s,false); // presentationHeld is a native host observation.
});
test('wrong Crypto class never supplies position or dereferences movement',async()=>{
 const f=populated();f.word(f.actor,0x123456);const s=await readFarmState(f.read,1,0);
 assert.equal(s.actorVtable,0x123456);assert.equal(s.actorPositionBits,null);assert.equal(s.movement,null);
 assert.equal(s.moveState,null);assert.equal(s.actorComplete,false);assert.equal(s.moveStateComplete,false);
 assert.equal(s.unknown.actorPositionBits,'unexpected Crypto actor vtable');assert.equal(s.memoryReads,21);
});
test('null and invalid movement or camera nodes cannot masquerade as valid zero state',async()=>{
 const f=populated();f.word(f.actor+0x130,0);f.word(f.renderer+0xec,0xfd000000);
 const s=await readFarmState(f.read,1,0);
 assert.equal(s.movement,0);assert.equal(s.moveState,null);assert.equal(s.moveStateComplete,false);
 assert.ok(s.absent.includes('movement'));assert.equal(s.cameraNode,0xfd000000);
 assert.equal(s.cameraWorldBits,null);assert.equal(s.cameraComplete,false);
 assert.equal(s.unknown.cameraWorldBits,'invalid cameraNode pointer');assert.equal(s.complete,false);
});

test('motion null, invalid and unavailable pointers preserve per-object uncertainty',async()=>{
 for(const [offset,pointer,complete,value] of [[0x28,'actorObject','actorObjectComplete','actorObjectQuatBits'],
  [0x4a0,'actorSceneNode','actorSceneNodeComplete','actorSceneWorldBits'],
  [0x110,'physicsBody','physicsBodyComplete','physicsVelocityBits']]){
  for(const bad of [0,3,0xfd000000,0x600000]){
   const f=populated();f.word(f.actor+offset,bad);const s=await readFarmState(f.read,1,0);
   assert.equal(s[pointer],bad);assert.equal(s[complete],false);assert.equal(s[value],null);
   if(bad===0)assert.ok(s.absent.includes(pointer));else assert.ok(s.unknown[value]);
  }
 }
});
test('motion class and setter guards reject incompatible layouts without inventing vectors',async()=>{
 const f=populated();f.word(f.actorNode,0x123456);f.word(f.body,0x123456);
 let s=await readFarmState(f.read,1,0);
 assert.equal(s.actorSceneNodeVtable,0x123456);assert.equal(s.actorSceneQuatBits,null);
 assert.equal(s.physicsBodyVtable,0x123456);assert.equal(s.physicsVelocityBits,null);
 assert.equal(s.physicsVelocitySetter,null);assert.equal(s.actorObjectComplete,true);
 f.word(f.body,0x2376e8);f.word(0x2376e8+0x90,0x123456);s=await readFarmState(f.read,1,0);
 assert.equal(s.physicsVelocitySetter,0x123456);assert.equal(s.physicsVelocityBits,null);
 assert.equal(s.physicsBodyComplete,false);
});
test('orientation and velocity retain raw signed-zero and nonfinite bits',async()=>{
 const f=populated();f.word(f.actorObject+0x38,0x80000000);f.word(f.actorNode+0x40,0x7fc00001);
 f.word(f.body+0x84,0xff800000);f.word(f.physicsInner+0x38,0x80000000);
 const s=await readFarmState(f.read,1,0);
 assert.equal(s.actorObjectQuatBits[0],0x80000000);assert.equal(s.actorSceneQuatBits[0],0x7fc00001);
 assert.equal(s.physicsVelocityBits[0],0xff800000);
 assert.equal(s.physicsInnerQuatBits[0],0x80000000);
});
