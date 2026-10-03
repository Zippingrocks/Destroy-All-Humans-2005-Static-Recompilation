/* Background-only logical pad adapter at the same XPP boundary as the recomp.
 * This tests retail menu/game logic, NOT USB/physical-controller fidelity.
 * Changes are confined to controller results and the corresponding function
 * returns. Never writes menu, save, progression, animation, or renderer state. */
import net from 'node:net';
import fs from 'node:fs';
import path from 'node:path';
import {spawnSync} from 'node:child_process';
import {performance} from 'node:perf_hooks';
import {RspClient} from './rsp_client.mjs';
import {readFarmState} from './xemu_farm_state.mjs';
import {readCinematicState,CINEMATIC_MAX_READS,CINEMATIC_MAX_BYTES} from './xemu_cinematic_state.mjs';
const args=process.argv.slice(2);
const option=(key,fallback)=>args.includes(key)?args[args.indexOf(key)+1]:fallback;
const script=option('--script'),out=option('--out');
const stateOut=option('--state-out'),stateInterval=Number(option('--state-interval','1'));
const holobobState=args.includes('--holobob-state');
const physicsQuatOut=option('--physics-quat-out');
const physicsQuatStart=Number(option('--physics-quat-start','7315'));
const physicsQuatEnd=Number(option('--physics-quat-end','7330'));
const velocityOut=option('--velocity-out');
const velocitySourceOut=option('--velocity-source-out');
const velocityStageOut=option('--velocity-stage-out');
const movementWatchOut=option('--movement-watch-out');
const velocityStart=Number(option('--velocity-start','7198'));
const velocityEnd=Number(option('--velocity-end','7225'));
const cinematicState=args.includes('--cinematic-state');
const captureCinematicRaw=option('--capture-cinematic-seconds');
const captureHelper=option('--capture-helper');
const captureIdent=Number(option('--capture-ident','0'));
const capturePid=Number(option('--capture-pid','0'));
const captureTimeout=Number(option('--capture-timeout-ms','30000'));
const captureInventoryMs=Number(option('--capture-inventory-ms','100'));
const captureCinematicSeconds=captureCinematicRaw?captureCinematicRaw.split(',').map(Number):[];
const stateLimit=30000;
const port=Number(option('--port','1235')),seconds=Number(option('--seconds','30'));
if(!script||!out||fs.existsSync(out))throw new Error('--script and new --out are required');
if(!Number.isFinite(seconds)||seconds<1||seconds>300)throw new Error('Invalid seconds');
if(!Number.isSafeInteger(stateInterval)||stateInterval<1||stateInterval>1000000)throw new Error('Invalid --state-interval');
if(args.includes('--state-interval')&&!stateOut)throw new Error('--state-interval requires --state-out');
if(holobobState&&!stateOut)throw new Error('--holobob-state requires --state-out');
if(cinematicState&&!stateOut)throw new Error('--cinematic-state requires --state-out');
if(captureCinematicSeconds.length){
 if(!cinematicState)throw new Error('--capture-cinematic-seconds requires --cinematic-state');
 if(!captureHelper||!fs.existsSync(captureHelper))throw new Error('--capture-helper must name the existing RenderDoc helper');
 if(!Number.isSafeInteger(captureIdent)||captureIdent<1||!Number.isSafeInteger(capturePid)||capturePid<1)throw new Error('Valid --capture-ident and --capture-pid are required');
 if(!Number.isSafeInteger(captureTimeout)||captureTimeout<1000||captureTimeout>120000)throw new Error('Invalid --capture-timeout-ms');
 if(!Number.isSafeInteger(captureInventoryMs)||captureInventoryMs<1||captureInventoryMs>1000)throw new Error('Invalid --capture-inventory-ms');
 if(captureCinematicSeconds.some((value,index)=>!Number.isFinite(value)||value<0||value>90||(index&&value<=captureCinematicSeconds[index-1])))throw new Error('Cinematic capture seconds must be strictly increasing values in 0..90');
}
if(args.includes('--state-out')&&!stateOut)throw new Error('--state-out requires a new JSONL path');
if(stateOut&&(fs.existsSync(stateOut)||path.resolve(stateOut).toLowerCase()===path.resolve(out).toLowerCase()))throw new Error('--state-out must be new and different from --out');
if(args.includes('--physics-quat-out')&&!physicsQuatOut)throw new Error('--physics-quat-out requires a new JSONL path');
if(!Number.isSafeInteger(physicsQuatStart)||!Number.isSafeInteger(physicsQuatEnd)||physicsQuatStart<0||physicsQuatEnd<=physicsQuatStart)throw new Error('Invalid physics quaternion window');
if(physicsQuatOut&&(fs.existsSync(physicsQuatOut)||[out,stateOut].filter(Boolean).some(value=>path.resolve(value).toLowerCase()===path.resolve(physicsQuatOut).toLowerCase())))throw new Error('--physics-quat-out must be new and different from other outputs');
if(args.includes('--velocity-out')&&!velocityOut)throw new Error('--velocity-out requires a new JSONL path');
if(!Number.isSafeInteger(velocityStart)||!Number.isSafeInteger(velocityEnd)||velocityStart<0||velocityEnd<=velocityStart)throw new Error('Invalid velocity window');
if(velocityOut&&(fs.existsSync(velocityOut)||[out,stateOut,physicsQuatOut].filter(Boolean).some(value=>path.resolve(value).toLowerCase()===path.resolve(velocityOut).toLowerCase())))throw new Error('--velocity-out must be new and different from other outputs');
if(args.includes('--velocity-source-out')&&!velocitySourceOut)throw new Error('--velocity-source-out requires a new JSONL path');
if(velocitySourceOut&&(fs.existsSync(velocitySourceOut)||[out,stateOut,physicsQuatOut,velocityOut].filter(Boolean).some(value=>path.resolve(value).toLowerCase()===path.resolve(velocitySourceOut).toLowerCase())))throw new Error('--velocity-source-out must be new and different from other outputs');
if(args.includes('--velocity-stage-out')&&!velocityStageOut)throw new Error('--velocity-stage-out requires a new JSONL path');
if(velocityStageOut&&(fs.existsSync(velocityStageOut)||[out,stateOut,physicsQuatOut,velocityOut,velocitySourceOut].filter(Boolean).some(value=>path.resolve(value).toLowerCase()===path.resolve(velocityStageOut).toLowerCase())))throw new Error('--velocity-stage-out must be new and different from other outputs');
if(args.includes('--movement-watch-out')&&!movementWatchOut)throw new Error('--movement-watch-out requires a new JSONL path');
if(movementWatchOut&&(fs.existsSync(movementWatchOut)||[out,stateOut,physicsQuatOut,velocityOut,velocitySourceOut,velocityStageOut].filter(Boolean).some(value=>path.resolve(value).toLowerCase()===path.resolve(movementWatchOut).toLowerCase())))throw new Error('--movement-watch-out must be new and different from other outputs');
const events=[];let clockMode='poll';
for(const raw of fs.readFileSync(script,'utf8').split(/\r?\n/)){
 const line=raw.trim();if(!line||line.startsWith('#'))continue;
 if(line==='@frame'){clockMode='frame';continue;}
 const fields=line.split(/\s+/);if(![9,10,15].includes(fields.length))throw new Error('Invalid input row');
 if(fields.some((v,i)=>!(i===2?/^(?:0x)?[0-9a-f]+$/i:/^-?\d+$/).test(v)))throw new Error('Invalid numeric token');
 const values=fields.map((v,i)=>parseInt(v,i===2?16:10));
 if(values.some(v=>!Number.isFinite(v)))throw new Error('Invalid number');
 const[start,duration,buttons,a,b,lx,ly,rx,ry,x=0,y=0,black=0,white=0,lt=0,rt=0]=values;
 if(start<0||duration<1||start>10000000||duration>100000||buttons<0||buttons>65535||
    [a,b,x,y,black,white,lt,rt].some(v=>v<0||v>255)||[lx,ly,rx,ry].some(v=>v< -32768||v>32767))throw new Error('Input outside controller range');
 events.push({clockMode,start,duration,buttons,analog:[a,b,x,y,black,white,lt,rt],sticks:[lx,ly,rx,ry]});
}
// Reserve the optional output before any connection/controller operation.
const stateFd=stateOut?fs.openSync(stateOut,'wx'):null;
const physicsQuatFd=physicsQuatOut?fs.openSync(physicsQuatOut,'wx'):null;
const velocityFd=velocityOut?fs.openSync(velocityOut,'wx'):null;
const velocitySourceFd=velocitySourceOut?fs.openSync(velocitySourceOut,'wx'):null;
const velocityStageFd=velocityStageOut?fs.openSync(velocityStageOut,'wx'):null;
const movementWatchFd=movementWatchOut?fs.openSync(movementWatchOut,'wx'):null;
const socket=net.createConnection({host:'127.0.0.1',port});socket.setNoDelay(true);
await new Promise((resolve,reject)=>{socket.once('connect',resolve);socket.once('error',reject);});
const rsp=new RspClient(socket);
// Keep native device enumeration, handles and close semantics intact. The
// isolated config binds a keyboard pad with background capture disabled.
const sites=new Map([[0x2216b5,['state',8]],[0x221728,['rumble',8]]]);
const physicsQuatSites=new Map([[0xd55d0,'constructor'],[0x129100,'input'],[0x129130,'normalized']]);
const velocitySite=0x12bb30;
const velocitySourceSite=0x52070;
const velocityStageSites=new Map([[0x5481f,'afterDirection'],[0x54836,'afterHeading'],[0x5487a,'afterAdjustment']]);
const armed=[];let running=false,anchor=0,packet=0,lastPad='',samples=0;
let stateSamples=0,lastStateLoop=null;
let physicsQuatArmed=false,physicsQuatSamples=0;
let velocityArmed=false,velocitySamples=0;
let velocitySourceArmed=false,velocitySourceSamples=0;
let velocityStageArmed=false,velocityStageSamples=0;
let movementWatchAddress=0,movementWatchArmed=false,movementWatchSamples=0;
let nextCinematicCapture=0;
const trace={schema:1,source:'xemu-logical-pad',script,port,startedAt:new Date().toISOString(),events:[],
 limitation:'Synthetic XPP API results; excludes hardware-controller fidelity and wall-clock timing due to debugger stops'};
if(stateOut)trace.stateObservation={path:stateOut,phase:'XInputGetState',timingPerturbed:true,
 interval:stateInterval,limit:stateLimit,inputSampling:'before-controller-result',
 cinematicState,cinematicAdditionalReadBudget:cinematicState?{reads:CINEMATIC_MAX_READS,bytes:CINEMATIC_MAX_BYTES}:null};
if(captureCinematicSeconds.length)trace.cinematicCaptures={targetsSeconds:captureCinematicSeconds,
 guestStopPhase:'XInputGetState',targetDrainBeforeTriggerMs:captureInventoryMs,records:[]};
if(physicsQuatOut)trace.physicsQuaternionObservation={path:physicsQuatOut,start:physicsQuatStart,end:physicsQuatEnd,
 addresses:{constructor:'0x000D55D0',input:'0x00129100',normalized:'0x00129130'},timingPerturbed:true};
if(velocityOut)trace.velocityObservation={path:velocityOut,start:velocityStart,end:velocityEnd,
 address:'0x0012BB30',timingPerturbed:true};
if(velocitySourceOut)trace.velocitySourceObservation={path:velocitySourceOut,start:velocityStart,end:velocityEnd,
 address:'0x00052070',timingPerturbed:true};
if(velocityStageOut)trace.velocityStageObservation={path:velocityStageOut,start:velocityStart,end:velocityEnd,
 addresses:{afterDirection:'0x0005481F',afterHeading:'0x00054836',afterAdjustment:'0x0005487A'},timingPerturbed:true};
if(movementWatchOut)trace.movementWatchObservation={path:movementWatchOut,timingPerturbed:true};
async function read(address,length){const value=await rsp.packet(`m${address.toString(16)},${length.toString(16)}`);if(!/^[0-9a-f]+$/i.test(value)||value.length!==length*2)throw new Error('Guest read failed');return Buffer.from(value,'hex');}
async function write(address,bytes){if(await rsp.packet(`M${address.toString(16)},${bytes.length.toString(16)}:${bytes.toString('hex')}`)!=='OK')throw new Error('Guest controller write failed');}
function float32(bits){const value=Buffer.allocUnsafe(4);value.writeUInt32LE(bits>>>0);return value.readFloatLE();}
function captureStoppedCinematic(observation,targetSeconds){
 const completed=spawnSync(captureHelper,['capture',String(captureIdent),String(capturePid),String(captureTimeout),String(captureInventoryMs)],{
  encoding:'utf8',windowsHide:true,timeout:captureTimeout+5000});
 if(completed.error)throw completed.error;
 if(completed.status!==0)throw new Error(`RenderDoc capture failed: ${(completed.stderr||completed.stdout||'').trim()}`);
 const records=(completed.stdout||'').split(/\r?\n/).filter(Boolean).map(line=>JSON.parse(line));
 const captured=records.find(record=>record.kind==='new_capture');
 if(!captured)throw new Error('RenderDoc capture returned no new_capture record');
 trace.cinematicCaptures.records.push({targetSeconds,loop:observation.loop,relativeFrame:observation.relativeFrame,
  cinematic:observation.cinematics[0],capture:captured,guestCpuStopped:true,observedAt:new Date().toISOString()});
}
try{
 let supported=await rsp.packet('qSupported:multiprocess+;swbreak+');
 const attachStopped=/^[ST]/.test(supported);
 if(attachStopped)supported=await rsp.packet('qSupported:multiprocess+;swbreak+');
 // Depending on the preceding client/QMP operation, qSupported can complete
 // with the CPU either already stopped or still running. Probe a harmless code
 // read first; interrupt only when the server rejects memory while running.
 let codeReply=await rsp.packet('mdaca0,5');
 if(!/^[0-9a-f]{10}$/i.test(codeReply)) {
  socket.write(Buffer.from([0x03]));
  const stop=await rsp.nextPacket(10000);
  if(!/^[ST]/.test(stop))throw new Error(`Could not stop xemu guest: ${stop}`);
  codeReply=await rsp.packet('mdaca0,5');
 }
 if(!/^[0-9a-f]{10}$/i.test(codeReply))throw new Error(`Guest code probe failed: ${codeReply}`);
 const code=Buffer.from(codeReply,'hex');
 if(code.toString('hex')!=='e85bd6ffff')throw new Error(`Unexpected retail loop bytes: ${code.toString('hex')}`);
 anchor=args.includes('--relative')?(await read(0x25b1dc,4)).readUInt32LE():0;
 trace.anchor=anchor;
 if(movementWatchFd!==null){
  const control=(await read(0x25fcec,4)).readUInt32LE();
  const player=control?(await read(control+0x38,4)).readUInt32LE():0;
  const actor=player?(await read(player+0x38,4)).readUInt32LE():0;
  const movement=actor?(await read(actor+0x130,4)).readUInt32LE():0;
  if(!movement)throw new Error('Movement watch could not resolve active Crypto movement object');
  movementWatchAddress=movement+0x48;
  if(await rsp.packet(`Z2,${movementWatchAddress.toString(16)},4`)!=='OK')throw new Error('Movement watchpoint rejected');
  movementWatchArmed=true;trace.movementWatchObservation.address=`0x${movementWatchAddress.toString(16)}`;
 }
 for(const address of sites.keys()){if(await rsp.packet(`Z0,${address.toString(16)},1`)!=='OK')throw new Error('Breakpoint rejected');armed.push(address);}
 const deadline=performance.now()+seconds*1000;
 rsp.resume();running=true;
 while(performance.now()<deadline){
  let stop;try{stop=await rsp.nextPacket(Math.max(1,deadline-performance.now()));}catch(error){if(error.message.includes('timed out'))break;throw error;}
  running=false;if(!/^[ST]/.test(stop))continue;
  const registers=Buffer.from(await rsp.packet('g'),'hex'),eip=registers.readUInt32LE(32),esp=registers.readUInt32LE(16);
  const physicsPhase=physicsQuatSites.get(eip);
  if(physicsPhase){
   const loop=(await read(0x25b1dc,4)).readUInt32LE(),relativeFrame=loop-anchor;
   const physicsStack=physicsPhase==='input'?await read(esp,32):
    physicsPhase==='constructor'?await read(esp,8):null;
   const constructorReturn=physicsPhase==='constructor'?physicsStack.readUInt32LE(0):null;
   if(physicsPhase!=='constructor'||constructorReturn===0x5855a){
    if(physicsPhase==='constructor'){
     fs.writeSync(physicsQuatFd,JSON.stringify({schema:1,source:'xemu',phase:physicsPhase,loop,relativeFrame,
      destination:registers.readUInt32LE(4),axis:registers.readUInt32LE(8),
      angleBits:physicsStack.readUInt32LE(4),guestReturn:constructorReturn,
      observedAt:new Date().toISOString()})+'\n');
    }else{
     const object=physicsPhase==='input'?registers.readUInt32LE(4):registers.readUInt32LE(24);
     const inputAddress=physicsPhase==='input'?physicsStack.readUInt32LE(4):0;
     const input=physicsPhase==='input'?await read(inputAddress,16):null;
     const stored=await read(object+0x38,16);
     fs.writeSync(physicsQuatFd,JSON.stringify({schema:1,source:'xemu',phase:physicsPhase,loop,relativeFrame,
      object,upstreamReturn:physicsStack?physicsStack.readUInt32LE(28):null,
      inputBits:input?[0,1,2,3].map(i=>input.readUInt32LE(i*4)):null,
      storedBits:[0,1,2,3].map(i=>stored.readUInt32LE(i*4)),observedAt:new Date().toISOString()})+'\n');
    }
    ++physicsQuatSamples;
   }
   let reply=await rsp.packet(`z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Physics quaternion breakpoint removal failed');
   rsp.step();const stepStop=await rsp.nextPacket(5000);if(!/^[ST]/.test(stepStop))throw new Error(`Unexpected physics quaternion step reply: ${stepStop}`);
   if(physicsQuatArmed){reply=await rsp.packet(`Z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Physics quaternion breakpoint reinsert failed');}
   rsp.resume();running=true;continue;
  }
  if(eip===velocitySite){
   const loop=(await read(0x25b1dc,4)).readUInt32LE(),relativeFrame=loop-anchor;
   const stack=await read(esp,8),object=registers.readUInt32LE(4),inputAddress=stack.readUInt32LE(4);
   const control=(await read(0x25fcec,4)).readUInt32LE();
   const player=control?(await read(control+0x38,4)).readUInt32LE():0;
   const actor=player?(await read(player+0x38,4)).readUInt32LE():0;
   const body=actor?(await read(actor+0x110,4)).readUInt32LE():0;
   if(body&&object===body){
    const input=await read(inputAddress,12);
    fs.writeSync(velocityFd,JSON.stringify({schema:1,source:'xemu',phase:'velocityInput',loop,relativeFrame,
     object,inputAddress,upstreamReturn:stack.readUInt32LE(0),
     inputBits:[0,1,2].map(i=>input.readUInt32LE(i*4)),observedAt:new Date().toISOString()})+'\n');
    ++velocitySamples;
   }
   let reply=await rsp.packet(`z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Velocity breakpoint removal failed');
   rsp.step();const stepStop=await rsp.nextPacket(5000);if(!/^[ST]/.test(stepStop))throw new Error(`Unexpected velocity step reply: ${stepStop}`);
   if(velocityArmed){reply=await rsp.packet(`Z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Velocity breakpoint reinsert failed');}
   rsp.resume();running=true;continue;
  }
  if(eip===velocitySourceSite){
   const loop=(await read(0x25b1dc,4)).readUInt32LE(),relativeFrame=loop-anchor;
   const stack=await read(esp,8),inputAddress=stack.readUInt32LE(4),input=await read(inputAddress,12);
   fs.writeSync(velocitySourceFd,JSON.stringify({schema:1,source:'xemu',phase:'velocitySource',loop,relativeFrame,
    object:registers.readUInt32LE(4),inputAddress,upstreamReturn:stack.readUInt32LE(0),
    inputBits:[0,1,2].map(i=>input.readUInt32LE(i*4)),observedAt:new Date().toISOString()})+'\n');
   ++velocitySourceSamples;
   let reply=await rsp.packet(`z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Velocity source breakpoint removal failed');
   rsp.step();const stepStop=await rsp.nextPacket(5000);if(!/^[ST]/.test(stepStop))throw new Error(`Unexpected velocity source step reply: ${stepStop}`);
   if(velocitySourceArmed){reply=await rsp.packet(`Z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Velocity source breakpoint reinsert failed');}
   rsp.resume();running=true;continue;
  }
  const velocityStage=velocityStageSites.get(eip);
  if(velocityStage){
   const loop=(await read(0x25b1dc,4)).readUInt32LE(),relativeFrame=loop-anchor;
   const inputAddress=velocityStage==='afterAdjustment'?registers.readUInt32LE(0):esp+0x14;
   const input=await read(inputAddress,12);
   fs.writeSync(velocityStageFd,JSON.stringify({schema:1,source:'xemu',phase:'velocityStage',stage:velocityStage,
    loop,relativeFrame,inputAddress,inputBits:[0,1,2].map(i=>input.readUInt32LE(i*4)),
    observedAt:new Date().toISOString()})+'\n');
   ++velocityStageSamples;
   let reply=await rsp.packet(`z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Velocity stage breakpoint removal failed');
   rsp.step();const stepStop=await rsp.nextPacket(5000);if(!/^[ST]/.test(stepStop))throw new Error(`Unexpected velocity stage step reply: ${stepStop}`);
   if(velocityStageArmed){reply=await rsp.packet(`Z0,${eip.toString(16)},1`);if(reply!=='OK')throw new Error('Velocity stage breakpoint reinsert failed');}
   rsp.resume();running=true;continue;
  }
  const site=sites.get(eip);
  if(!site&&movementWatchArmed){
   const loop=(await read(0x25b1dc,4)).readUInt32LE(),value=(await read(movementWatchAddress,4)).readUInt32LE();
   const stackAddress=esp>=0xd0000000?(esp&0x03ffffff):esp;
   const stack=await read(stackAddress,64);
   fs.writeSync(movementWatchFd,JSON.stringify({schema:1,source:'xemu',phase:'movementStateWrite',loop,
    relativeFrame:loop-anchor,eip,value,registers:[0,1,2,3,4,5,6,7,8,9].map(i=>registers.readUInt32LE(i*4)),
    esp,stackAddress,stackWords:Array.from({length:16},(_,i)=>stack.readUInt32LE(i*4)),observedAt:new Date().toISOString()})+'\n');
   ++movementWatchSamples;rsp.resume();running=true;continue;
  }
  if(!site)throw new Error(`Unexpected stop ${eip.toString(16)}`);
  const stack=await read(esp,20),ret=stack.readUInt32LE(0);let result=0;
  if(site[0]==='state'){
   const loop=(await read(0x25b1dc,4)).readUInt32LE(),pad=Buffer.alloc(22);
   const relativeFrame=loop-anchor;
   if(physicsQuatFd!==null&&!physicsQuatArmed&&relativeFrame>=physicsQuatStart&&relativeFrame<physicsQuatEnd){
    for(const address of physicsQuatSites.keys()){if(await rsp.packet(`Z0,${address.toString(16)},1`)!=='OK')throw new Error('Physics quaternion breakpoint rejected');armed.push(address);}
    physicsQuatArmed=true;
   }else if(physicsQuatArmed&&relativeFrame>=physicsQuatEnd){
    for(const address of physicsQuatSites.keys()){if(await rsp.packet(`z0,${address.toString(16)},1`)!=='OK')throw new Error('Physics quaternion breakpoint removal failed');}
    physicsQuatArmed=false;
   }
   if(velocityFd!==null&&!velocityArmed&&relativeFrame>=velocityStart&&relativeFrame<velocityEnd){
    if(await rsp.packet(`Z0,${velocitySite.toString(16)},1`)!=='OK')throw new Error('Velocity breakpoint rejected');
    armed.push(velocitySite);velocityArmed=true;
   }else if(velocityArmed&&relativeFrame>=velocityEnd){
    if(await rsp.packet(`z0,${velocitySite.toString(16)},1`)!=='OK')throw new Error('Velocity breakpoint removal failed');
    velocityArmed=false;
   }
   if(velocitySourceFd!==null&&!velocitySourceArmed&&relativeFrame>=velocityStart&&relativeFrame<velocityEnd){
    if(await rsp.packet(`Z0,${velocitySourceSite.toString(16)},1`)!=='OK')throw new Error('Velocity source breakpoint rejected');
    armed.push(velocitySourceSite);velocitySourceArmed=true;
   }else if(velocitySourceArmed&&relativeFrame>=velocityEnd){
    if(await rsp.packet(`z0,${velocitySourceSite.toString(16)},1`)!=='OK')throw new Error('Velocity source breakpoint removal failed');
    velocitySourceArmed=false;
   }
   if(velocityStageFd!==null&&!velocityStageArmed&&relativeFrame>=velocityStart&&relativeFrame<velocityEnd){
    for(const address of velocityStageSites.keys()){
     if(await rsp.packet(`Z0,${address.toString(16)},1`)!=='OK')throw new Error('Velocity stage breakpoint rejected');
     armed.push(address);
    }
    velocityStageArmed=true;
   }else if(velocityStageArmed&&relativeFrame>=velocityEnd){
    for(const address of velocityStageSites.keys()){
     if(await rsp.packet(`z0,${address.toString(16)},1`)!=='OK')throw new Error('Velocity stage breakpoint removal failed');
    }
    velocityStageArmed=false;
   }
   if(stateFd!==null&&loop!==lastStateLoop&&loop%stateInterval===0&&stateSamples<stateLimit){
    const observation=await readFarmState(read,loop,anchor);
    if(holobobState&&observation.actor){
     const manager=(await read(observation.actor+0x138,4)).readUInt32LE();
     const slots=manager?await read(manager+0x4c,16):Buffer.alloc(16);let holobob=0;
     for(let i=0;i<4;i++){const weapon=slots.readUInt32LE(i*4);if(weapon&&(await read(weapon,4)).readUInt32LE()===0x22fd50)holobob=weapon;}
     observation.holobobMain=holobob;
     if(holobob){const bytes=await read(holobob+0x34,0x14c);
      observation.holobobActive=bytes[0];observation.holobobState=bytes.readUInt32LE(0x10);
      observation.holobobTarget=bytes.readUInt32LE(0x144);observation.holobobToken=bytes.readUInt32LE(0x148);
     }
    }
    if(cinematicState)Object.assign(observation,await readCinematicState(read));
    if(nextCinematicCapture<captureCinematicSeconds.length&&observation.cinematicComplete&&
       observation.cinematics?.length===1&&observation.cinematics[0].state===2){
     const elapsed=float32(observation.cinematics[0].elapsedBits);
     while(nextCinematicCapture<captureCinematicSeconds.length&&elapsed>=captureCinematicSeconds[nextCinematicCapture]){
      captureStoppedCinematic(observation,captureCinematicSeconds[nextCinematicCapture]);
      ++nextCinematicCapture;
     }
    }
    fs.writeSync(stateFd,JSON.stringify({...observation,sample:stateSamples,observedAt:new Date().toISOString()})+'\n');
    lastStateLoop=loop;++stateSamples;
   }
   for(const event of events){
    const clock=event.clockMode==='poll'?samples:loop-anchor;
    if(clock<event.start||clock>=event.start+event.duration)continue;
    pad.writeUInt16LE(pad.readUInt16LE(4)|event.buttons,4);
    event.analog.forEach((v,i)=>{if(v)pad[6+i]=v;});
    event.sticks.forEach((v,i)=>{if(v)pad.writeInt16LE(v,14+i*2);});
   }
   const signature=pad.subarray(4).toString('hex');
   if(signature!==lastPad){lastPad=signature;++packet;trace.events.push({loop,relativeFrame:loop-anchor,pad:signature});}
   pad.writeUInt32LE(packet,0);await write(stack.readUInt32LE(8),pad);++samples;
  }
  registers.writeUInt32LE(result>>>0,0);registers.writeUInt32LE(esp+4+site[1],16);registers.writeUInt32LE(ret,32);
  if(await rsp.packet('G'+registers.toString('hex'))!=='OK')throw new Error('Controller return rejected');
  rsp.resume();running=true;
 }
 if(!samples)throw new Error('No controller polls observed; bind the isolated keyboard device before replay');
}catch(error){trace.error=error.message;process.exitCode=1;}
finally{
 if(running){socket.write(Buffer.from([3]));try{await rsp.nextPacket(3000);}catch{}}
 for(const address of armed)try{await rsp.packet(`z0,${address.toString(16)},1`);}catch{}
 if(movementWatchArmed)try{await rsp.packet(`z2,${movementWatchAddress.toString(16)},4`);}catch{}
 rsp.resume();rsp.close();trace.samples=samples;trace.finishedAt=new Date().toISOString();
 if(stateFd!==null){fs.closeSync(stateFd);trace.stateObservation.samples=stateSamples;trace.stateObservation.limitReached=stateSamples>=stateLimit;}
 if(physicsQuatFd!==null){fs.closeSync(physicsQuatFd);trace.physicsQuaternionObservation.samples=physicsQuatSamples;}
 if(velocityFd!==null){fs.closeSync(velocityFd);trace.velocityObservation.samples=velocitySamples;}
 if(velocitySourceFd!==null){fs.closeSync(velocitySourceFd);trace.velocitySourceObservation.samples=velocitySourceSamples;}
 if(velocityStageFd!==null){fs.closeSync(velocityStageFd);trace.velocityStageObservation.samples=velocityStageSamples;}
 if(movementWatchFd!==null){fs.closeSync(movementWatchFd);trace.movementWatchObservation.samples=movementWatchSamples;}
 fs.writeFileSync(out,JSON.stringify(trace,null,2)+'\n',{flag:'wx'});console.log(JSON.stringify(trace));
}
