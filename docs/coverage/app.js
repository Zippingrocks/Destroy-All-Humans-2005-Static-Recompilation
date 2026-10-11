(() => {
  "use strict";
  const payload = window.DAH_COVERAGE;
  const rows = payload.functions.map(r => ({
    address:r[0], size:r[1], name:r[2], status:r[3], confidence:r[4],
    instructions:r[5], calls:r[6], callers:r[7], evidence:!!r[8], source:r[9]
  }));
  const colors = {recovered:"#19dc59", seeded:"#11b8c9", translated:"#087eb5", stubbed:"#f0952b", missing:"#303844"};
  const labels = {recovered:"Recovered", seeded:"Observed seed", translated:"Auto translated", stubbed:"Explicit stub", missing:"Missing"};
  const canvas = document.querySelector("#treemap");
  const wrap = document.querySelector("#canvasWrap");
  const ctx = canvas.getContext("2d");
  const tooltip = document.querySelector("#tooltip");
  const details = document.querySelector("#details");
  const search = document.querySelector("#search");
  const statusFilter = document.querySelector("#statusFilter");
  const layoutMode = document.querySelector("#layoutMode");
  const empty = document.querySelector("#empty");
  let rects = [], groupRects = [], selected = null;

  function formatBytes(n) {
    return n >= 1048576 ? (n/1048576).toFixed(2)+" MB" : n >= 1024 ? (n/1024).toFixed(2)+" kB" : n+" B";
  }
  function pct(n,d) { return d ? (100*n/d).toFixed(1)+"%" : "0%"; }
  function statusBytes(status) { return rows.filter(x=>x.status===status).reduce((s,x)=>s+x.size,0); }

  const translatedBytes = rows.filter(x=>x.status==="translated"||x.status==="recovered").reduce((s,x)=>s+x.size,0);
  document.querySelector("#stats").innerHTML = [
    [payload.meta.functionCount.toLocaleString(),"Tracked entry points"],
    [pct(translatedBytes,payload.meta.totalBytes),"Translated bytes"],
    [payload.meta.recoveredCount.toLocaleString(),"Recovered callbacks"],
    [payload.meta.stubCount.toLocaleString(),"Explicit stubs"],
    [payload.meta.evidenceCount.toLocaleString(),"Evidence-linked"]
  ].map(([v,l])=>`<div class="stat"><strong>${v}</strong><span>${l}</span></div>`).join("");
  document.querySelector("#legend").innerHTML = Object.keys(colors).map(k=>`<span><i style="background:${colors[k]};color:${colors[k]}"></i>${labels[k]}</span>`).join("");

  function parseSize(value) {
    const m = value.match(/^([0-9.]+)(kb|mb|b)?$/i); if(!m) return NaN;
    return +m[1] * (m[2]?.toLowerCase()==="mb"?1048576:m[2]?.toLowerCase()==="kb"?1024:1);
  }
  function matches(fn, query) {
    const tokens = query.trim().toLowerCase().split(/\s+/).filter(Boolean);
    return tokens.every(t => {
      let m;
      if ((m=t.match(/^size([<>])(.+)$/))) return m[1]===">" ? fn.size>parseSize(m[2]) : fn.size<parseSize(m[2]);
      if ((m=t.match(/^([<>])(.+)$/))) return m[1]===">" ? fn.size>parseSize(m[2]) : fn.size<parseSize(m[2]);
      if ((m=t.match(/^confidence([<>])([0-9.]+)%?$/))) { const v=+m[2]/(+m[2]>1?100:1); return m[1]===">"?fn.confidence>v:fn.confidence<v; }
      return fn.name.toLowerCase().includes(t) || fn.address.toString(16).padStart(8,"0").includes(t.replace(/^0x/,"")) || fn.status.includes(t) || (fn.source||"").toLowerCase().includes(t);
    });
  }

  // Balanced binary treemap. Every split consumes its full rectangle, avoiding
  // the thin stripe tail produced by the earlier row-based layout.
  function squarify(items, x, y, w, h) {
    const pending=items.slice().filter(i=>i.size>0).sort((a,b)=>b.size-a.size), out=[];
    function place(list,px,py,pw,ph) {
      if(!list.length||pw<=0||ph<=0) return;
      if(list.length===1){out.push({...list[0],x:px,y:py,w:pw,h:ph});return;}
      const total=list.reduce((sum,item)=>sum+item.size,0), half=total/2;
      let running=0, cut=1, best=Infinity;
      for(let i=1;i<list.length;i++){
        running+=list[i-1].size;
        const distance=Math.abs(half-running);
        if(distance<=best){best=distance;cut=i;}else break;
      }
      const left=list.slice(0,cut), right=list.slice(cut);
      const leftSize=left.reduce((sum,item)=>sum+item.size,0), ratio=leftSize/total;
      if(pw>=ph){const split=pw*ratio;place(left,px,py,split,ph);place(right,px+split,py,pw-split,ph);}
      else {const split=ph*ratio;place(left,px,py,pw,split);place(right,px,py+split,pw,ph-split);}
    }
    place(pending,x,y,w,h);return out;
  }

  function regionLabel(address) {
    const start=Math.floor(address/0x10000)*0x10000, end=start+0xffff;
    return `0x${start.toString(16).padStart(8,"0").toUpperCase()}–0x${end.toString(16).padStart(8,"0").toUpperCase()}`;
  }
  function organize(items,w,h) {
    if(layoutMode.value==="flat") {
      groupRects=[];
      return squarify(items,0,0,w,h).map(r=>({...r,group:"All functions"}));
    }
    const groups=new Map();
    for(const fn of items) {
      const key=layoutMode.value==="status"?fn.status:Math.floor(fn.address/0x10000);
      if(!groups.has(key)) groups.set(key,[]);
      groups.get(key).push(fn);
    }
    const summaries=[...groups].map(([key,members])=>({
      key,
      label:layoutMode.value==="status"?labels[key]:regionLabel(members[0].address),
      size:members.reduce((sum,fn)=>sum+fn.size,0),
      members
    }));
    if(layoutMode.value==="region") summaries.sort((a,b)=>a.key-b.key);
    else summaries.sort((a,b)=>b.size-a.size);
    groupRects=squarify(summaries,0,0,w,h);
    const result=[];
    for(const group of groupRects) {
      const margin=3, header=group.w>100&&group.h>40?22:0;
      const gx=group.x+margin, gy=group.y+margin+header;
      const gw=Math.max(0,group.w-margin*2), gh=Math.max(0,group.h-margin*2-header);
      if(gw<1||gh<1) continue;
      for(const tile of squarify(group.members,gx,gy,gw,gh)) result.push({...tile,group:group.label});
    }
    return result;
  }

  function filtered() {
    const status=statusFilter.value, q=search.value;
    return rows.filter(fn => (status==="all" || (status==="evidence"?fn.evidence:fn.status===status)) && matches(fn,q));
  }
  function resize() {
    const dpr=Math.min(devicePixelRatio||1,2), box=canvas.getBoundingClientRect();
    canvas.width=Math.round(box.width*dpr);canvas.height=Math.round(box.height*dpr);ctx.setTransform(dpr,0,0,dpr,0,0);draw();
  }
  function draw() {
    const box=canvas.getBoundingClientRect(), items=filtered();
    rects=organize(items,box.width,box.height); empty.hidden=!!items.length;
    ctx.clearRect(0,0,box.width,box.height);ctx.fillStyle="#0b111a";ctx.fillRect(0,0,box.width,box.height);
    for(const group of groupRects){
      ctx.fillStyle="rgba(22,32,45,.72)";ctx.fillRect(group.x+1,group.y+1,Math.max(0,group.w-2),Math.max(0,group.h-2));
      ctx.strokeStyle="#354257";ctx.lineWidth=1;ctx.strokeRect(group.x+1.5,group.y+1.5,Math.max(0,group.w-3),Math.max(0,group.h-3));
      if(group.w>100&&group.h>40){ctx.fillStyle="#aebcd0";ctx.font="600 10px ui-monospace,Consolas,monospace";ctx.fillText(group.label,group.x+7,group.y+16,group.w-14);}
    }
    for(const r of rects){
      const pad=.7, active=selected&&selected.address===r.address;
      ctx.fillStyle=colors[r.status];ctx.globalAlpha=r.status==="translated"?.72:.9;
      ctx.fillRect(r.x+pad,r.y+pad,Math.max(0,r.w-pad*2),Math.max(0,r.h-pad*2));ctx.globalAlpha=1;
      if(r.evidence&&r.w>5&&r.h>5){ctx.fillStyle="rgba(255,255,255,.7)";ctx.fillRect(r.x+2,r.y+2,Math.min(4,r.w-3),Math.min(4,r.h-3));}
      if(active){ctx.strokeStyle="#fff";ctx.lineWidth=2;ctx.strokeRect(r.x+1,r.y+1,r.w-2,r.h-2);}
      if(r.w>90&&r.h>28){ctx.fillStyle="rgba(255,255,255,.88)";ctx.font="11px ui-monospace,Consolas,monospace";ctx.fillText(r.name,r.x+6,r.y+17,r.w-12);}
    }
  }
  function at(e){const b=canvas.getBoundingClientRect(),x=e.clientX-b.left,y=e.clientY-b.top;return rects.find(r=>x>=r.x&&x<=r.x+r.w&&y>=r.y&&y<=r.y+r.h);}
  function showDetails(fn){selected=fn;details.innerHTML=`<p class="eyebrow">Selected function</p><h2>${fn.name}</h2><p><span class="badge" style="border-left:3px solid ${colors[fn.status]}">${labels[fn.status]}</span>${fn.evidence?'<span class="badge">Parity evidence linked</span>':''}</p><div class="detail-grid"><div><strong>0x${fn.address.toString(16).padStart(8,"0").toUpperCase()}</strong><span>Xbox address</span></div><div><strong>${formatBytes(fn.size)}</strong><span>Original size</span></div><div><strong>${fn.instructions||"—"}</strong><span>Instructions</span></div><div><strong>${Math.round(fn.confidence*100)}%</strong><span>Discovery confidence</span></div><div><strong>${fn.calls}</strong><span>Direct calls</span></div><div><strong>${fn.callers}</strong><span>Known callers</span></div></div><p>Group: <code>${fn.group}</code>.</p>${fn.source?`<p>Recovered in <code>${fn.source}</code>.</p>`:""}`;draw();}
  canvas.addEventListener("mousemove",e=>{const fn=at(e);if(!fn){tooltip.hidden=true;return;}tooltip.hidden=false;tooltip.innerHTML=`<strong>${fn.name}</strong>0x${fn.address.toString(16).padStart(8,"0").toUpperCase()} · ${formatBytes(fn.size)} · ${labels[fn.status]}${fn.evidence?" · evidence":""}`;const b=wrap.getBoundingClientRect();tooltip.style.left=Math.min(e.clientX-b.left+14,b.width-330)+"px";tooltip.style.top=Math.max(8,e.clientY-b.top-58)+"px";});
  canvas.addEventListener("mouseleave",()=>tooltip.hidden=true);
  canvas.addEventListener("click",e=>{const fn=at(e);if(fn)showDetails(fn);});
  [search,statusFilter,layoutMode].forEach(el=>el.addEventListener("input",()=>{selected=null;draw();}));
  new ResizeObserver(resize).observe(wrap); resize();
})();
