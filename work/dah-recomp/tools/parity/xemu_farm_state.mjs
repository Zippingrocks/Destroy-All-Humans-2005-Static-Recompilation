/* Bounded read-only observer. The supplied read function must share the input
 * adapter's stopped RSP connection. No writes or extra breakpoint operations. */
export const FARM_STATE_MAX_READS=29;
export const FARM_STATE_MAX_BYTES=2048;
export async function readFarmState(read, loop, anchor) {
 const state={schema:1,source:'xemu',phase:'XInputGetState',phaseAddress:'0x002216b5',
  timingPerturbed:true,inputSampling:'before-controller-result',loop,relativeFrame:loop-anchor,
  backend:null,backendState:null,backendName:null,pendingBackend:null,pendingBackendState:null,
  pendingBackendName:null,renderer:null,refresh:null,divisor:null,interval:null,
  world:null,worldVtable:null,worldTick:null,worldElapsedBits:null,worldStepBits:null,
  worldPaused:null,worldRealtime:null,rngState:null,movie:null,movieMode:null,movieFlags:null,
  movieLifecycle:null,movieHeader:null,cameraUpdate:null,controlSystem:null,
  player:null,playerVtable:null,playerFocus:null,playerShip:null,playerCrypto:null,
  actor:null,actorVtable:null,actorPositionBits:null,movement:null,moveState:null,
  movementAngularVelocityBits:null,movementHeadingBits:null,movementSteeringBits:null,
  actorObject:null,actorObjectPositionBits:null,actorObjectQuatBits:null,actorObjectFlags:null,
  actorSceneNode:null,actorSceneNodeVtable:null,actorSceneNodeParent:null,
  actorSceneQuatBits:null,actorSceneWorldBits:null,physicsBody:null,physicsBodyVtable:null,
  physicsVelocitySetter:null,physicsVelocityBits:null,physicsInner:null,physicsInnerVtable:null,
  physicsInnerQuatBits:null,
  cameraNode:null,cameraNodeParent:null,cameraViewPositionBits:null,cameraViewForwardBits:null,
  cameraLocalBits:null,cameraQuatBits:null,cameraWorldBits:null,
  worldComplete:false,pendingBackendComplete:false,rngStateComplete:false,cameraUpdateComplete:false,
  playerComplete:false,actorComplete:false,moveStateComplete:false,movementMotionComplete:false,cameraComplete:false,
  actorObjectComplete:false,actorSceneNodeComplete:false,physicsBodyComplete:false,physicsInnerComplete:false,
  unknown:{},absent:[]};
 let reads=0,bytes=0;
 const range=(address,size)=>Number.isInteger(address)&&Number.isInteger(size)&&size>0&&
  ((address>=0x10000&&address+size<=0x08000000)||(address>=0x80000000&&address+size<=0x88000000));
 const issue=(keys,why)=>{for(const key of keys)state.unknown[key]=why;};
 async function get(address,size,keys){
  if(!range(address,size)){issue(keys,'invalid guest RAM address');return null;}
  if(++reads>FARM_STATE_MAX_READS||(bytes+=size)>FARM_STATE_MAX_BYTES){issue(keys,'sample read budget exceeded');return null;}
  try{
   const data=await read(address,size);
   if(!Buffer.isBuffer(data)||data.length!==size){issue(keys,'short guest memory read');return null;}
   return data;
  }catch(error){
   // An explicit memory-read error is an unknown field. A transport timeout or
   // disconnect must abort the adapter rather than desynchronize RSP replies.
   if(error.message!=='Guest read failed')throw error;
   issue(keys,'guest memory unavailable');return null;
  }
 }
 async function pointer(address,key){const b=await get(address,4,[key]);if(b)state[key]=b.readUInt32LE();return state[key];}
 async function backend(pointerKey,stateKey,nameKey){
  const p=state[pointerKey];
  if(p===null){issue([stateKey,nameKey],'backend pointer unavailable');return;}
  if(p===0){state.absent.push(pointerKey);return;}
  if((p&3)||!range(p,0x58c)){issue([stateKey,nameKey],'invalid backend pointer');return;}
  const value=await get(p+0x10,4,[stateKey]);if(value)state[stateKey]=value.readUInt32LE();
  const name=await get(p+0x50c,128,[nameKey]);
  if(name){
   const end=name.indexOf(0);
   if(end<0||name.subarray(0,end).some(v=>v<32||v>126))issue([nameKey],'unterminated or non-ASCII backend path');
   else state[nameKey]=name.subarray(0,end).toString('ascii');
  }
 }
 const identity=await get(0x25b1d0,4,['backend','pendingBackend']);
 if(identity&&identity.readUInt32LE()===0x22b510){
  const b=await get(0x25b1d0+0x4a28,8,['backend','pendingBackend']);
  if(b){state.backend=b.readUInt32LE(0);state.pendingBackend=b.readUInt32LE(4);}
 }else if(identity)issue(['backend','pendingBackend'],'unexpected driver vtable');
 await backend('backend','backendState','backendName');
 await backend('pendingBackend','pendingBackendState','pendingBackendName');
 const r=await pointer(0x250e60,'renderer');
 if(r===0)state.absent.push('renderer');
 else if(r!==null){
  if((r&3)||!range(r,0x2cc))issue(['refresh','divisor','interval'],'invalid renderer pointer');
  else{
   const b=await get(r+0x238,0x94,['refresh','divisor','interval']);
   if(b){state.refresh=b.readUInt32LE(0)?60:50;state.divisor=b.readUInt32LE(0x44);state.interval=b.readUInt32LE(0x90);}
  }
 }else issue(['refresh','divisor','interval'],'renderer pointer unavailable');
 const w=await pointer(0x286768,'world');
 const worldKeys=['worldVtable','worldTick','worldElapsedBits','worldStepBits','worldPaused','worldRealtime'];
 if(w===0)state.absent.push('world');
 else if(w!==null){
  if((w&3)||!range(w,0x303e))issue(worldKeys,'invalid world pointer');
  else{
   const b=await get(w,0x14,worldKeys);
   if(b){
    state.worldVtable=b.readUInt32LE();
    // Verified constructor/update/GetTime/GetFrameTime sites: 00105460,
    // 00105280, 00115388, 00115208. Do not decode a different class.
    if(state.worldVtable!==0x235780)issue(worldKeys.slice(1),'unexpected world vtable');
    else{
     state.worldTick=b.readUInt32LE(8);state.worldElapsedBits=b.readUInt32LE(12);state.worldStepBits=b.readUInt32LE(16);
     const flags=await get(w+0x303c,2,['worldPaused','worldRealtime']);
     if(flags){state.worldPaused=flags[0];state.worldRealtime=flags[1];}
    }
   }
  }
 }else issue(worldKeys,'world pointer unavailable');
 const rng=await get(0x278a58,4,['rngState']);if(rng)state.rngState=rng.readUInt32LE();
 const movie=await get(0x2867f4,0x2c,['movie','movieMode','movieFlags','movieLifecycle']);
 if(movie){
  state.movieFlags=movie[0];state.movieMode=movie.readUInt32LE(4);
  state.movieLifecycle=movie.readUInt32LE(0x10);state.movie=movie.readUInt32LE(0x28);
  if(state.movie===0)state.absent.push('movie');
  else if((state.movie&3)||!range(state.movie,24))issue(['movieHeader'],'invalid movie pointer');
  else{const h=await get(state.movie,24,['movieHeader']);if(h)state.movieHeader=Array.from({length:6},(_,i)=>h.readUInt32LE(i*4));}
 }else issue(['movieHeader'],'movie pointer unavailable');
 // Same source-validated fields and raw float bits as native/paused-RAM traces.
 // Full populated chains, including movie/pending backend and the separate
 // actor object, scene node, physics body and movement steering use the full
 // 29-read budget and 1911 bytes. There are no extra CPU stops.
 const words=(b,offset,count)=>Array.from({length:count},(_,i)=>b.readUInt32LE(offset+4*i));
 async function object(p,size,keys,name){
  if(p===0){state.absent.push(name);return null;}
  if(p===null){issue(keys,`${name} pointer unavailable`);return null;}
  if((p&3)||!range(p,size)){issue(keys,`invalid ${name} pointer`);return null;}
  return get(p,size,keys);
 }
 const cameraUpdate=await get(0x258b48,1,['cameraUpdate']);
 if(cameraUpdate)state.cameraUpdate=cameraUpdate[0];
 const control=await pointer(0x25fcec,'controlSystem');
 const controlHeader=await object(control,0x3c,['player'],'controlSystem');
 if(controlHeader){
  state.player=controlHeader.readUInt32LE(0x38);
  const playerKeys=['playerVtable','playerFocus','playerShip','playerCrypto','actor'];
  const p=await object(state.player,0x3c,playerKeys,'player');
  if(p){
   state.playerVtable=p.readUInt32LE();state.playerFocus=p.readUInt32LE(0x30);
   state.playerShip=p.readUInt32LE(0x34);state.playerCrypto=state.actor=p.readUInt32LE(0x38);
   state.playerComplete=true;
   const motionKeys=['actorObject','actorObjectPositionBits','actorObjectQuatBits','actorObjectFlags',
    'actorSceneNode','actorSceneNodeVtable','actorSceneNodeParent','actorSceneQuatBits','actorSceneWorldBits',
    'physicsBody','physicsBodyVtable','physicsVelocitySetter','physicsVelocityBits',
    'physicsInner','physicsInnerVtable','physicsInnerQuatBits'];
   const a=await object(state.actor,0x158,['actorVtable','actorPositionBits','movement','moveState',...motionKeys],'actor');
   if(a){
    state.actorVtable=a.readUInt32LE();
    if(state.actorVtable!==0x22c9f8)issue(['actorPositionBits','movement','moveState',...motionKeys],'unexpected Crypto actor vtable');
    else{
     state.actorPositionBits=words(a,0x14c,3);state.actorComplete=true;
     state.movement=a.readUInt32LE(0x130);
     const movementKeys=['moveState','movementAngularVelocityBits','movementHeadingBits',
      'movementSteeringBits'];
     const m=await object(state.movement,0x4c,movementKeys,'movement');
     if(m){
      state.moveState=m.readUInt32LE(0x48);
      state.movementAngularVelocityBits=m.readUInt32LE(0x14);
      state.movementHeadingBits=m.readUInt32LE(0x18);
      state.moveStateComplete=true;
      const steering=await get(state.movement+0x2ac,8,['movementSteeringBits']);
      if(steering){state.movementSteeringBits=words(steering,0,2);state.movementMotionComplete=true;}
     }
     // 00081B70 receives actor+18, stores quaternion through [actor+28],
     // then dirties object+4C. This object starts with a node pointer, not a vtable.
     state.actorObject=a.readUInt32LE(0x28);
     const o=await object(state.actorObject,0x50,
      ['actorObjectPositionBits','actorObjectQuatBits','actorObjectFlags'],'actorObject');
     if(o){state.actorObjectPositionBits=words(o,0x2c,3);state.actorObjectQuatBits=words(o,0x38,4);
      state.actorObjectFlags=o.readUInt32LE(0x4c);state.actorObjectComplete=true;}
     const nodeKeys=['actorSceneNodeVtable','actorSceneNodeParent','actorSceneQuatBits','actorSceneWorldBits'];
     const nodeLink=await get(state.actor+0x4a0,4,['actorSceneNode',...nodeKeys]);
     if(nodeLink){
      state.actorSceneNode=nodeLink.readUInt32LE();
      const n=await object(state.actorSceneNode,0x90,nodeKeys,'actorSceneNode');
      if(n){state.actorSceneNodeVtable=n.readUInt32LE();
       if(state.actorSceneNodeVtable!==0x234308)issue(nodeKeys.slice(1),'unexpected actor scene node vtable');
       else{state.actorSceneNodeParent=n.readUInt32LE(8);state.actorSceneQuatBits=words(n,0x40,4);
        state.actorSceneWorldBits=words(n,0x50,16);state.actorSceneNodeComplete=true;}
      }
     }
     state.physicsBody=a.readUInt32LE(0x110);
     const bodyKeys=['physicsBodyVtable','physicsVelocitySetter','physicsVelocityBits',
      'physicsInner','physicsInnerVtable','physicsInnerQuatBits'];
     const b=await object(state.physicsBody,0x90,bodyKeys,'physicsBody');
     if(b){state.physicsBodyVtable=b.readUInt32LE();state.physicsInner=b.readUInt32LE(0x0c);
      if(state.physicsBodyVtable!==0x2376e8)issue(bodyKeys.slice(1),'unexpected physics body vtable');
      else{
       const setter=await get(state.physicsBodyVtable+0x90,4,['physicsVelocitySetter','physicsVelocityBits']);
       if(setter){state.physicsVelocitySetter=setter.readUInt32LE();
        // Wrapper 2376E8 inherits 12BB30, which stores velocity +84/+88/+8C.
        if(state.physicsVelocitySetter!==0x12bb30)issue(['physicsVelocityBits'],'unexpected physics velocity setter');
        else{state.physicsVelocityBits=words(b,0x84,3);state.physicsBodyComplete=true;}
       }
       const innerKeys=['physicsInnerVtable','physicsInnerQuatBits'];
       const inner=await object(state.physicsInner,0x48,innerKeys,'physicsInner');
       if(inner){state.physicsInnerVtable=inner.readUInt32LE();
        if(state.physicsInnerVtable!==0x237968)issue(['physicsInnerQuatBits'],'unexpected physics inner vtable');
        else{state.physicsInnerQuatBits=words(inner,0x38,4);state.physicsInnerComplete=true;}
       }
      }
     }
    }
   }
  }
 }
 const cameraKeys=['cameraNode','cameraNodeParent','cameraViewPositionBits','cameraViewForwardBits',
  'cameraLocalBits','cameraQuatBits','cameraWorldBits'];
 if(r!==0){
  const camera=await object(r,0xf0,cameraKeys,'renderer');
  if(camera){
   state.cameraNode=camera.readUInt32LE(0xec);
   state.cameraViewPositionBits=words(camera,0x80,3);state.cameraViewForwardBits=words(camera,0x70,3);
   const n=await object(state.cameraNode,0x90,cameraKeys.slice(1).filter(k=>!k.startsWith('cameraView')),'cameraNode');
   if(n){
    state.cameraNodeParent=n.readUInt32LE(8);state.cameraLocalBits=words(n,0x20,3);
    state.cameraQuatBits=words(n,0x40,4);state.cameraWorldBits=words(n,0x50,16);state.cameraComplete=true;
   }
  }
 }
 state.worldComplete=worldKeys.every(k=>state[k]!==null);
 state.pendingBackendComplete=state.pendingBackendState!==null&&state.pendingBackendName!==null;
 state.rngStateComplete=state.rngState!==null;state.cameraUpdateComplete=state.cameraUpdate!==null;
 state.complete=Object.keys(state.unknown).length===0;
 state.memoryReads=reads;state.memoryBytes=bytes;
 return state;
}
