# Privacy-safe public reporting

The recompilation keeps two deliberately separate diagnostic stores:

- `debug-runs/` and `crashlog/` are private, local developer evidence. They can
  contain paths, registers, stack words, log text and minidumps. The reporter
  never uploads or copies these files wholesale.
- `reports/` contains a small public JSON record built from an allowlist. Only
  this format is eligible for submission.

Public reports contain an opaque random report ID, executable build hash,
coarse session duration, clean-exit state, aggregate event/anomaly counters,
frame-pacing counters, and stable crash identifiers. They do not contain a
Windows username, computer name, IP address, absolute path, process ID, exact
timestamp, save data, input history, raw log text, stack or memory contents,
screenshots, the XBE, movies, or extracted game assets.

The Normal release has no public reporter compiled into it and never asks for
reporting consent. The Debug-Reporter release explains the allowlist on first
launch and asks the player to opt in or decline. Declining is the default.
`reporting-settings.json` is then created beside the executable with separate
consent switches for crash reports and ordinary session summaries. Reports
created without consent stay under
`reports/local/`; enabling consent later does not retroactively make those
files eligible for submission. Eligible records are written to
`reports/pending/`.

The developer console supports:

```text
reporting status
reporting crashes on
reporting crashes off
reporting sessions on
reporting sessions off
report_bug
```

`report_bug` creates the sanitized record, opens the GitHub issue form and
opens the reports folder. The player can inspect and attach the JSON. Raw logs
and dumps must remain local unless a developer specifically requests a reviewed
excerpt.

Automatic delivery requires a separately operated HTTPS intake service. A
GitHub write token must never be embedded in the game. The intake service must
accept only this schema, reject unknown fields and oversized bodies, rate-limit
clients, group reports by build and stable signature, and hold the GitHub App
credential on the server. Until that service is configured, the game performs
no background network request.
