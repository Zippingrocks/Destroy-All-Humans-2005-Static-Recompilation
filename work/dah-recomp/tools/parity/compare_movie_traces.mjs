#!/usr/bin/env node
import fs from "node:fs";

const [retailPath, recompPath, outPath] = process.argv.slice(2);
if (!retailPath || !recompPath || !outPath) {
  throw new Error("usage: node compare_movie_traces.mjs RETAIL.json RECOMP.log OUT.json");
}
const retailSource = JSON.parse(fs.readFileSync(retailPath, "utf8"));
const recompText = fs.readFileSync(recompPath, "utf8");
const retail = retailSource.milestones.map(event => ({
  stage: event.name === "movie_open" ? "OPEN" : "CLOSE",
  ms: Number(event.milliseconds),
  path: event.path || null
}));
const recomp = [];
for (const line of recompText.split(/\r?\n/)) {
  const match = /\[DAH-MIRROR\] ms=(\d+) stage=(OPEN|CLOSE)\b/.exec(line);
  if (!match) continue;
  const pathMatch = / path=(.*)$/.exec(line);
  recomp.push({ stage: match[2], ms: Number(match[1]), path: pathMatch ? pathMatch[1] : null });
}
const retailAnchor = retail.find(event => event.stage === "OPEN");
const recompAnchor = recomp.find(event => event.stage === "OPEN");
if (!retailAnchor || !recompAnchor) throw new Error("both traces need an OPEN anchor");
const count = Math.min(retail.length, recomp.length);
const events = [];
for (let index = 0; index < count; index++) {
  const left = retail[index];
  const right = recomp[index];
  const retailRelativeMs = left.ms - retailAnchor.ms;
  const recompRelativeMs = right.ms - recompAnchor.ms;
  events.push({
    index,
    retailStage: left.stage,
    recompStage: right.stage,
    retailPath: left.path,
    recompPath: right.path,
    retailRelativeMs: Number(retailRelativeMs.toFixed(3)),
    recompRelativeMs: Number(recompRelativeMs.toFixed(3)),
    deltaMs: Number((recompRelativeMs - retailRelativeMs).toFixed(3)),
    sequenceMatch: left.stage === right.stage &&
      (left.stage !== "OPEN" || (!!left.path && !!right.path && left.path.toLowerCase() === right.path.toLowerCase()))
  });
}
const postAnchor = events.filter(event => event.retailRelativeMs >= 0 && event.recompRelativeMs >= 0);
const report = {
  schema: 1,
  retailPath,
  recompPath,
  retailEvents: retail.length,
  recompEvents: recomp.length,
  comparedEvents: events.length,
  exactSequence: retail.length === recomp.length && events.every(event => event.sequenceMatch),
  maxPostAnchorAbsDeltaMs: Number(Math.max(...postAnchor.map(event => Math.abs(event.deltaMs))).toFixed(3)),
  withinOne30FpsFrame: postAnchor.every(event => Math.abs(event.deltaMs) <= 1000 / 30),
  events
};
fs.writeFileSync(outPath, `${JSON.stringify(report, null, 2)}\n`, { flag: "wx" });
console.log(JSON.stringify(report, null, 2));
