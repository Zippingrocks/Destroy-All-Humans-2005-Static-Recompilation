"""Fetch only RenderDoc replay API headers, pinned to the installed v1.43 build."""
import hashlib
import json
import pathlib
import re
import urllib.request

COMMIT = "286e07140d96bf3acda4059e085e8f5eb0e92608"
BASE = "https://raw.githubusercontent.com/baldurk/renderdoc/" + COMMIT + "/"
DEST = pathlib.Path(__file__).resolve().parent / "vendor" / "renderdoc-v1.43"


def main():
    pending = ["renderdoc/api/replay/renderdoc_replay.h", "renderdoc/api/app/renderdoc_app.h"]
    seen = {}
    while pending:
        rel = pending.pop(0)
        if rel in seen:
            continue
        if ".." in pathlib.PurePosixPath(rel).parts or not rel.endswith((".h", ".inl")):
            raise ValueError("Unexpected header path: " + rel)
        url = BASE + rel
        with urllib.request.urlopen(url, timeout=30) as response:
            data = response.read()
        target = DEST / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
        seen[rel] = {"url": url, "sha256": hashlib.sha256(data).hexdigest()}
        print(rel, len(data), flush=True)
        for inc in re.findall(r'^\s*#include\s+"([^"]+)"', data.decode("utf-8"), re.M):
            # Public replay headers refer to sibling headers, plus api/app.h
            # by relative paths. Resolve lexical parents within the repository.
            parts = list(pathlib.PurePosixPath(rel).parent.parts)
            for part in pathlib.PurePosixPath(inc).parts:
                if part == "..":
                    parts.pop()
                elif part != ".":
                    parts.append(part)
            dependency = "/".join(parts)
            if dependency not in seen:
                pending.append(dependency)
    (DEST / "PROVENANCE.json").write_text(json.dumps({
        "upstream": "https://github.com/baldurk/renderdoc",
        "commit": COMMIT,
        "license": "MIT; original copyright/license notices retained in every header",
        "files": seen,
    }, indent=2) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
