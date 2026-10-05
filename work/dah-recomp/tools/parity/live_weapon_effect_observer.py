#!/usr/bin/env python3
"""Read-only live Crypto/Zap-O-Matic state observer."""
import argparse,ctypes,json,struct,time
from pathlib import Path
RMIN,RMAX,OFF=0x10000,0x08000000,0x10000
k=ctypes.WinDLL("kernel32",use_last_error=True)
k.OpenProcess.argtypes=[ctypes.c_uint32,ctypes.c_bool,ctypes.c_uint32];k.OpenProcess.restype=ctypes.c_void_p
k.ReadProcessMemory.argtypes=[ctypes.c_void_p,ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t,ctypes.POINTER(ctypes.c_size_t)];k.ReadProcessMemory.restype=ctypes.c_bool
k.GetExitCodeProcess.argtypes=[ctypes.c_void_p,ctypes.POINTER(ctypes.c_uint32)];k.GetExitCodeProcess.restype=ctypes.c_bool
class Reader:
 def __init__(s,pid):s.h=k.OpenProcess(0x1010,False,pid)
 def read(s,a,n):
  if not RMIN<=a<RMAX:return None
  d=(ctypes.c_ubyte*n)();c=ctypes.c_size_t();return bytes(d) if k.ReadProcessMemory(s.h,ctypes.c_void_p(a+OFF),d,n,ctypes.byref(c)) and c.value==n else None
 def u32(s,a):
  d=s.read(a,4);return struct.unpack("<I",d)[0] if d else 0
 def u8(s,a):
  d=s.read(a,1);return d[0] if d else 0
 def running(s):
  c=ctypes.c_uint32();return bool(k.GetExitCodeProcess(s.h,ctypes.byref(c))) and c.value==259
def ptr(v):return RMIN<=v<RMAX and v%4==0
def bind(r):
 c=r.u32(0x25FCEC);p=r.u32(c+0x38) if ptr(c) else 0;a=r.u32(p+0x38) if ptr(p) else 0;m=r.u32(a+0x138) if ptr(a) else 0
 return {"control":c,"player":p,"actor":a,"manager":m,"zap":r.u32(m+0x4C) if ptr(m) else 0,"active":r.u32(m+0x58) if ptr(m) else 0,"world":r.u32(0x286768)}
def state(r,z):
 if not ptr(z):return None
 cs=[r.u32(z+o) for o in (0x718,0x71C,0x720,0x724)]
 return {"weaponState":r.u32(z+0x1C0),"stateTimeBits":f"{r.u32(z+0x1C4):08X}","effectObject":f"{r.u32(z+0x1C8):08X}","targetCount":r.u32(z+0x1CC),"selectedTarget":f"{r.u32(z+0x204):08X}","activationByte":r.u8(z+0x34),"attachmentObjects":[f"{r.u32(z+o):08X}" for o in (0x2C,0x30)],"effectHandles":[f"{r.u32(z+o):08X}" for o in (0x194,0x198,0x19C,0x1A0,0x1A4,0x1A8)],"channels":[{"address":f"{c:08X}","active115":r.u8(c+0x115) if ptr(c) else None,"endpoint118":r.u8(c+0x118) if ptr(c) else None,"endpoint128":r.u8(c+0x128) if ptr(c) else None} for c in cs]}
def emit(o,t,r,b,**x):
 q={"type":t,"time":time.time(),"worldTick":r.u32(b["world"]+8) if ptr(b["world"]) else None};q.update(x);o.write(json.dumps(q,separators=(",",":"))+"\n")
def main():
 p=argparse.ArgumentParser();p.add_argument("--pid",type=int,required=True);p.add_argument("--output",type=Path,required=True);p.add_argument("--hz",type=float,default=30);p.add_argument("--root",default="zap");p.add_argument("--depth",default=0);p.add_argument("--max-nodes",default=8);p.add_argument("--child-bytes",default=0x180);p.add_argument("--root-bytes");p.add_argument("--capture-trigger",type=Path);a=p.parse_args();r=Reader(a.pid);a.output.parent.mkdir(parents=True,exist_ok=True);pb=ps=None;n=0;dt=1/a.hz;capture_armed=True
 with a.output.open("x",encoding="utf-8",buffering=1) as o:
  b=bind(r);emit(o,"run-start",r,b,pid=a.pid,sampleHz=a.hz);deadline=time.perf_counter()
  while r.running():
   b=bind(r)
   if b!=pb:emit(o,"bindings",r,b,bindings={x:f"{y:08X}" for x,y in b.items()},actorVtable=f"{r.u32(b['actor']):08X}",zapVtable=f"{r.u32(b['zap']):08X}",activeVtable=f"{r.u32(b['active']):08X}");pb=b.copy()
   s=state(r,b["zap"])
   if s!=ps:
    emit(o,"zap-state",r,b,address=f"{b['zap']:08X}",state=s)
    active=bool(s and (s["weaponState"] or s["effectObject"]!="00000000" or s["targetCount"] or any(c["active115"] for c in s["channels"])))
    if not active:capture_armed=True
    if a.capture_trigger and capture_armed and active:
     a.capture_trigger.touch()
     emit(o,"capture-trigger",r,b,path=str(a.capture_trigger))
     capture_armed=False
    ps=s
   n+=1
   if n%max(1,round(a.hz))==0:emit(o,"heartbeat",r,b,samples=n)
   deadline+=dt;time.sleep(max(0,deadline-time.perf_counter()))
 return 0
if __name__=="__main__":raise SystemExit(main())
