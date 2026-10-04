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
  const empty = document.querySelector("#empty");
  let rects = [], selected = null;

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

  // Squarified treemap. Values are area-normalized; output order remains tied
  // to the filtered function objects for fast canvas hit testing.
  function squarify(items, x, y, w, h) {
    const total = items.reduce((s,i)=>s+i.size,0); if(!total) return [];
    const scale = w*h/total;
    const pending = items.slice().sort((a,b)=>b.size-a.size).map(i=>({item:i,area:i.size*scale}));
    const out=[]; let row=[];
    function worst(test, side) {
      const sum=test.reduce((s,a)=>s+a.area,0), max=Math.max(...test.map(a=>a.area)), min=Math.min(...test.map(a=>a.area));
      return Math.max(side*side*max/(sum*sum), sum*sum/(side*side*min));
    }
    function layoutRow() {
      const area=row.reduce((s,a)=>s+a.area,0);
      if(w>=h){ const rh=area/w; let rx=x; row.forEach(a=>{const rw=a.area/rh; out.push({...a.item,x:rx,y,w:rw,h:rh});rx+=rw;}); y+=rh;h-=rh; }
      else { const rw=area/h; let ry=y; row.forEach(a=>{const rh=a.area/rw;out.push({...a.item,x,y:ry,w:rw,h:rh});ry+=rh;}); x+=rw;w-=rw; }
      row=[];
    }
    while(pending.length){ const next=pending[0], side=Math.min(w,h); if(!row.length||worst(row.concat(next),side)<=worst(row,side)) row.push(pending.shift()); else layoutRow(); }
    if(row.length) layoutRow(); return out;
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
    rects=squarify(items,0,0,box.width,box.height); empty.hidden=!!items.length;
    ctx.clearRect(0,0,box.width,box.height);ctx.fillStyle="#0b111a";ctx.fillRect(0,0,box.width,box.height);
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
  function showDetails(fn){selected=fn;details.innerHTML=`<p class="eyebrow">Selected function</p><h2>${fn.name}</h2><p><span class="badge" style="border-left:3px solid ${colors[fn.status]}">${labels[fn.status]}</span>${fn.evidence?'<span class="badge">Parity evidence linked</span>':''}</p><div class="detail-grid"><div><strong>0x${fn.address.toString(16).padStart(8,"0").toUpperCase()}</strong><span>Xbox address</span></div><div><strong>${formatBytes(fn.size)}</strong><span>Original size</span></div><div><strong>${fn.instructions||"—"}</strong><span>Instructions</span></div><div><strong>${Math.round(fn.confidence*100)}%</strong><span>Discovery confidence</span></div><div><strong>${fn.calls}</strong><span>Direct calls</span></div><div><strong>${fn.callers}</strong><span>Known callers</span></div></div>${fn.source?`<p>Recovered in <code>${fn.source}</code>.</p>`:""}`;draw();}
  canvas.addEventListener("mousemove",e=>{const fn=at(e);if(!fn){tooltip.hidden=true;return;}tooltip.hidden=false;tooltip.innerHTML=`<strong>${fn.name}</strong>0x${fn.address.toString(16).padStart(8,"0").toUpperCase()} · ${formatBytes(fn.size)} · ${labels[fn.status]}${fn.evidence?" · evidence":""}`;const b=wrap.getBoundingClientRect();tooltip.style.left=Math.min(e.clientX-b.left+14,b.width-330)+"px";tooltip.style.top=Math.max(8,e.clientY-b.top-58)+"px";});
  canvas.addEventListener("mouseleave",()=>tooltip.hidden=true);
  canvas.addEventListener("click",e=>{const fn=at(e);if(fn)showDetails(fn);});
  [search,statusFilter].forEach(el=>el.addEventListener("input",()=>{selected=null;draw();}));
  new ResizeObserver(resize).observe(wrap); resize();
})();
