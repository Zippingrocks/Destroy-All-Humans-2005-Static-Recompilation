/* Read-only top-level GUI observer for transition parity. The linked-list
 * layout and names are validated by the retail paused-RAM decoder. */
export const UI_STATE_MAX_READS=512;
export const UI_STATE_MAX_BYTES=32768;

const nestedRoots=new Set(['burn','cinematic','fade','titlecard']);

export async function readUiState(read){
 const result={uiRoot:null,ui:[],uiTree:[],uiComplete:false,uiReason:null,uiMemoryReads:0,uiMemoryBytes:0};
 const range=(address,size)=>Number.isInteger(address)&&Number.isInteger(size)&&size>0&&
  ((address>=0x10000&&address+size<=0x08000000)||(address>=0x80000000&&address+size<=0x88000000));
 async function get(address,size){
  if(!range(address,size))throw new Error('invalid UI guest RAM address');
  if(++result.uiMemoryReads>UI_STATE_MAX_READS||(result.uiMemoryBytes+=size)>UI_STATE_MAX_BYTES)
   throw new Error('UI read budget exceeded');
  const data=await read(address,size);
  if(!Buffer.isBuffer(data)||data.length!==size)throw new Error('short UI guest memory read');
  return data;
 }
 try{
  const rootLink=(await get(0x258470,4)).readUInt32LE();
  if(!rootLink){result.uiReason='UI root link absent';return result;}
  const root=(await get(rootLink,4)).readUInt32LE();result.uiRoot=root;
  if(!root){result.uiReason='UI root absent';return result;}
  const sentinel=root+0x44;let node=(await get(sentinel,4)).readUInt32LE();
  const seen=new Set();
  async function walkChildren(parent,parentPath,parentActive,depth){
   if(depth>10)return;
   const childSentinel=parent+0x44;
   let childNode=(await get(childSentinel,4)).readUInt32LE();
   const links=new Set();
   while(childNode&&childNode!==childSentinel){
    if(links.has(childNode)||links.size>=128)throw new Error('invalid or oversized nested UI list');
    links.add(childNode);
    const link=await get(childNode,12),child=link.readUInt32LE(8);
    if(child){
     if(seen.has(child))throw new Error('cyclic nested UI tree');
     seen.add(child);
     const header=await get(child,0x50);
     if(header.readUInt32LE(8)!==parent)throw new Error('nested UI child parent mismatch');
     const raw=header.subarray(12,52),end=raw.indexOf(0);
     if(end<0||raw.subarray(0,end).some(value=>value<32||value>126))throw new Error('invalid nested UI name');
     const name=raw.subarray(0,end).toString('ascii');
     const active=header[4]!==0,effective=parentActive&&active;
     const path=`${parentPath}/${name}`;
     result.uiTree.push({address:child,vtable:header.readUInt32LE(),active:header[4],effectiveActive:effective,name,path});
     await walkChildren(child,path,effective,depth+1);
    }
    childNode=link.readUInt32LE();
   }
   if(childNode!==childSentinel)throw new Error('unterminated nested UI list');
  }
  while(node&&node!==sentinel){
   if(seen.has(node)||seen.size>=128)throw new Error('invalid or oversized UI list');
   seen.add(node);
   const link=await get(node,12),child=link.readUInt32LE(8);
   if(child){
    const header=await get(child,52);
    if(header.readUInt32LE(8)!==root)throw new Error('UI child parent mismatch');
    const raw=header.subarray(12,52),end=raw.indexOf(0);
    if(end<0||raw.subarray(0,end).some(value=>value<32||value>126))throw new Error('invalid UI name');
    const name=raw.subarray(0,end).toString('ascii');
    result.ui.push({address:child,vtable:header.readUInt32LE(),active:header[4],name});
    if(nestedRoots.has(name.toLowerCase()))await walkChildren(child,name,header[4]!==0,1);
   }
   node=link.readUInt32LE();
  }
  if(node!==sentinel)throw new Error('unterminated UI list');
  result.uiComplete=true;
 }catch(error){
  result.uiReason=error.message;
 }
 return result;
}
