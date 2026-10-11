"""Run the console helper without ever creating a console window.

For live capture, the caller must provide the ident and PID of its own diagnostic
process, which must already have RenderDoc loaded before graphics initialization.
This runner does not launch or inject the game/emulator or run qrenderdoc.
"""
import pathlib
import subprocess
import sys

HELPER = pathlib.Path(__file__).resolve().parent / "renderdoc-helper-build" / "renderdoc_headless.exe"

if __name__ == "__main__":
    try:
        result = subprocess.run([str(HELPER), *sys.argv[1:]],
            creationflags=subprocess.CREATE_NO_WINDOW, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, timeout=120)
        sys.stdout.buffer.write(result.stdout)
        sys.stderr.buffer.write(result.stderr)
        raise SystemExit(result.returncode)
    except subprocess.TimeoutExpired:
        # subprocess.run kills only the helper process it started. It never
        # terminates the target application that the helper may be connected to.
        print("RenderDoc helper exceeded 120-second bound", file=sys.stderr)
        raise SystemExit(124)
