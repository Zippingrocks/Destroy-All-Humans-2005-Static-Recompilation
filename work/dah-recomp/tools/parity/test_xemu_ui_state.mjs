import assert from 'node:assert/strict';
import test from 'node:test';
import {readUiState,UI_STATE_MAX_BYTES,UI_STATE_MAX_READS} from './xemu_ui_state.mjs';

const memory=Buffer.alloc(0x400000);
const u32=(address,value)=>memory.writeUInt32LE(value>>>0,address);
const object=(address,parent,name,active=1)=>{
 u32(address,0x002350f8); memory[address+4]=active; u32(address+8,parent);
 memory.write(name,address+0x0c,'ascii'); memory[address+0x0c+name.length]=0;
 u32(address+0x44,address+0x44);
};
const append=(parent,node,child,next=parent+0x44)=>{
 u32(parent+0x44,node); u32(node,next); u32(node+8,child);
};

test('reads watched nested transition UI without expanding ordinary branches',async()=>{
 const rootLink=0x260000,root=0x270000,fade=0x272000;
 const loading=0x274000,text=0x276000,main=0x278000;
 u32(0x258470,rootLink);u32(rootLink,root);object(root,0,'',1);
 object(fade,root,'fade',1);object(loading,fade,'loading',1);
 object(text,loading,'loadingText',0);object(main,root,'main',1);
 append(root,0x271000,fade,0x277000);u32(0x277000,root+0x44);u32(0x277008,main);
 append(fade,0x273000,loading);append(loading,0x275000,text);
 const state=await readUiState(async(address,size)=>Buffer.from(memory.subarray(address,address+size)));
 assert.equal(state.uiComplete,true,state.uiReason);
 assert.deepEqual(state.ui.map(({name})=>name),['fade','main']);
 assert.deepEqual(state.uiTree.map(({path,effectiveActive})=>[path,effectiveActive]),[
  ['fade/loading',true],['fade/loading/loadingText',false]
 ]);
 assert.ok(state.uiMemoryReads<=UI_STATE_MAX_READS);
 assert.ok(state.uiMemoryBytes<=UI_STATE_MAX_BYTES);
});

test('rejects a nested child whose parent pointer does not match',async()=>{
 const rootLink=0x260000,root=0x270000,fade=0x272000,loading=0x274000;
 u32(0x258470,rootLink);u32(rootLink,root);object(root,0,'',1);
 object(fade,root,'fade',1);object(loading,root,'loading',1);
 append(root,0x271000,fade);append(fade,0x273000,loading);
 const state=await readUiState(async(address,size)=>Buffer.from(memory.subarray(address,address+size)));
 assert.equal(state.uiComplete,false);
 assert.equal(state.uiReason,'nested UI child parent mismatch');
});
