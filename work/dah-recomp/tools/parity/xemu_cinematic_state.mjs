/* Read-only in-engine movie timeline observer; these are not Bink videos.
 * Manager constructor 00112D80/derived override 0005CD65, list update 00112BE0, movie constructor
 * 00112280/derived override 0005910E, start 00111EE0, elapsed update 00111CE0, finish 00111F90.
 * Supply the already-stopped RSP connection. Transport failures propagate.
 * Separate optional budget: <=34 reads / 2144 bytes, no writes or stops. */
export const CINEMATIC_MAX_READS=34, CINEMATIC_MAX_BYTES=2144;
export async function readCinematicState(read) {
 const s={cinematicManager:null,cinematicManagerVtable:null,cinematicDeclaredCount:null,
  cinematics:null,cinematicComplete:false,cinematicReason:null,cinematicMemoryReads:0,cinematicMemoryBytes:0};
 const fail=reason=>{if(s.cinematicReason===null)s.cinematicReason=reason;};
 const range=(a,n)=>Number.isInteger(a)&&!(a&3)&&n>0&&
  ((a>=0x10000&&a+n<=0x08000000)||(a>=0x80000000&&a+n<=0x88000000));
 async function get(a,n) {
  if(!range(a,n)){fail('invalid guest RAM address');return null;}
  if(s.cinematicMemoryReads+1>CINEMATIC_MAX_READS||s.cinematicMemoryBytes+n>CINEMATIC_MAX_BYTES){fail('cinematic read budget exceeded');return null;}
  ++s.cinematicMemoryReads;s.cinematicMemoryBytes+=n;
  try {const b=await read(a,n);if(!Buffer.isBuffer(b)||b.length!==n){fail('short guest memory read');return null;}return b;}
  catch(e){if(e.message!=='Guest read failed')throw e;fail('guest memory unavailable');return null;}
 }
 const p=await get(0x286784,4);if(!p)return s;
 const manager=s.cinematicManager=p.readUInt32LE();
 if(manager===0){s.cinematics=[];s.cinematicComplete=true;return s;}
 const h=await get(manager,0x1c);if(!h)return s;
 s.cinematicManagerVtable=h.readUInt32LE();
 if(![0x23611c,0x22a6b8].includes(s.cinematicManagerVtable)){fail('unexpected cinematic manager vtable');return s;}
 s.cinematicDeclaredCount=h.readUInt32LE(0x18);s.cinematics=[];
 const sentinel=manager+8,tail=h.readUInt32LE(12),seen=new Set(),objects=new Set();
 let node=h.readUInt32LE(8),previous=sentinel;
 while(node!==sentinel){
  if(!node){fail('null cinematic list link');break;}
  if(seen.has(node)){fail('cyclic cinematic list');break;}
  if(seen.size===16){fail('cinematic list exceeds 16 entries');break;}
  seen.add(node);const link=await get(node,12);if(!link)break;
  if(link.readUInt32LE(4)!==previous){fail('cinematic previous-link mismatch');break;}
  const object=link.readUInt32LE(8),entry={node,object,vtable:null,nameHash:null,durationBits:null,elapsedBits:null,flags:null,state:null,complete:false};
  s.cinematics.push(entry);
  if(objects.has(object)){fail('duplicate cinematic object');break;}objects.add(object);
  const movie=await get(object,0x78);
  if(movie){
   entry.vtable=movie.readUInt32LE();
   if(![0x236100,0x229fb4].includes(entry.vtable))fail('unexpected cinematic movie vtable');
   else {
    entry.nameHash=movie.readUInt32LE(0x20);entry.durationBits=movie.readUInt32LE(0x68);
    entry.elapsedBits=movie.readUInt32LE(0x6c);entry.flags=movie.readUInt32LE(0x70);entry.state=movie.readUInt32LE(0x74);
    entry.complete=entry.state<=3;if(!entry.complete)fail('invalid cinematic movie state');
   }
  }
  previous=node;node=link.readUInt32LE();
 }
 if(node===sentinel&&tail!==previous)fail('cinematic tail-link mismatch');
 if(s.cinematics.length!==s.cinematicDeclaredCount)fail('cinematic count mismatch');
 s.cinematicComplete=s.cinematicReason===null;return s;
}
