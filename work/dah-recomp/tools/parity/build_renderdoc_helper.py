"""Build the console helper with installed MSVC, without opening a console window."""
import pathlib
import re
import subprocess

ROOT = pathlib.Path(__file__).resolve().parent
BUILD = ROOT / "renderdoc-helper-build"
VS = pathlib.Path(r"C:\Program Files\Microsoft Visual Studio\2022\Community")
VC = VS / "VC" / "Tools" / "MSVC" / "14.44.35207" / "bin" / "Hostx64" / "x64"
DLL = pathlib.Path(r"C:\Program Files\RenderDoc\renderdoc.dll")


def run(args, **kwargs):
    return subprocess.run(args, check=True, creationflags=subprocess.CREATE_NO_WINDOW,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, **kwargs)


def main():
    BUILD.mkdir(exist_ok=True)
    exports = run([str(VC / "dumpbin.exe"), "/nologo", "/exports", str(DLL)]).stdout
    names = re.findall(r"^\s+\d+\s+[0-9A-F]+\s+[0-9A-F]+\s+(RENDERDOC_\w+)\s*$", exports, re.M)
    if not names:
        raise RuntimeError("No RenderDoc API exports found")
    definition = BUILD / "renderdoc.def"
    definition.write_text("LIBRARY renderdoc.dll\nEXPORTS\n" + "\n".join(names) + "\n", encoding="ascii")
    print(run([str(VC / "lib.exe"), "/nologo", "/machine:x64", "/def:" + str(definition),
               "/out:" + str(BUILD / "renderdoc.lib")]).stdout)
    # Only this generated fixed build batch is sent through cmd; all paths are quoted.
    batch = BUILD / "build.cmd"
    include = ROOT / "vendor" / "renderdoc-v1.43" / "renderdoc" / "api" / "replay"
    batch.write_text('@echo off\ncall "' + str(VS / "VC" / "Auxiliary" / "Build" / "vcvars64.bat") +
        '" >nul\ncl /nologo /EHsc /std:c++17 /O2 /W3 /D_CRT_SECURE_NO_WARNINGS /I"' + str(include) +
        '" "' + str(ROOT / "renderdoc_headless.cpp") + '" /Fo"' + str(BUILD / "renderdoc_headless.obj") +
        '" /Fe"' + str(BUILD / "renderdoc_headless.exe") + '" /link "' + str(BUILD / "renderdoc.lib") +
        '" delayimp.lib user32.lib /DELAYLOAD:renderdoc.dll\n', encoding="ascii")
    completed = subprocess.run(["cmd.exe", "/d", "/c", str(batch)], cwd=BUILD,
        creationflags=subprocess.CREATE_NO_WINDOW, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    print(completed.stdout)
    completed.check_returncode()
    print(run([str(BUILD / "renderdoc_headless.exe"), "probe"], cwd=BUILD).stdout)


if __name__ == "__main__":
    main()
