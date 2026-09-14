# Godzilla recompilation reference repositories

Downloaded as shallow working trees on 2026-08-31. Submodules were initialized
recursively where supported.

| Directory | Revision | Upstream |
|---|---:|---|
| `burnout3` | `306ba597eebe` | https://github.com/sp00nznet/burnout3.git |
| `xemu` | `d73326b62199` | https://github.com/xemu-project/xemu.git |
| `Cxbx-Reloaded` | `585c49a50af1` | https://github.com/Cxbx-Reloaded/Cxbx-Reloaded.git |
| `ghidra-xbe` | `1928314b23f9` | https://github.com/XboxDev/ghidra-xbe.git |
| `nxdk` | `29638d0b001f` | https://github.com/XboxDev/nxdk.git |
| `nv2a-trace` | `65bdd2369a5b` | https://github.com/XboxDev/nv2a-trace.git |
| `xboxpy` | `51ee241f71b2` | https://github.com/XboxDev/xboxpy.git |
| `xbdm_gdb_bridge` | `a89fbcde7113` | https://github.com/abaire/xbdm_gdb_bridge.git |
| `extract-xiso` | `b72e5b60d598` | https://github.com/XboxDev/extract-xiso.git |
| `reccmp` | `fbd0a1611d6c` | https://github.com/isledecomp/reccmp.git |

## Windows path-length note

The first `xemu` checkout encountered the Windows path limit in deeply nested
EDK2/OpenSSL test data. It was retried with `core.longpaths=true`; recursive
`git submodule status` now confirms that every declared submodule is checked out
at its recorded revision.
