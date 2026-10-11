"""Plan, or explicitly start, a NEW paused xemu on an inactive Windows desktop.

Default mode performs read-only validation. --start is intentionally required.
No existing emulator PID is accepted, opened, or controlled.
"""
import argparse
import ctypes
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import socket
import struct
import subprocess
import sys
import tomllib

HERE = Path(__file__).resolve().parent
PROJECT = HERE.parent.parent
SOURCE = Path(r"C:\Users\Bilbo\Desktop\Emulation\XEMU")
FILES = {
    # Keep one stable executable path. Windows keys firewall/reputation prompts
    # partly by image path; copying xemu into every capture directory can show
    # a new Yes/No dialog even though the binary is identical.
    "xemu": SOURCE / "xemu.exe",
    "bootrom": SOURCE / "Boot ROM image" / "mcpx_1.0.bin",
    "bios": SOURCE / "BIOS" / "Complex_4627v1.03.bin",
    "hdd": SOURCE / "Xemu Halo 2 E3 2003 Map Test 8-8-26" / "xbox_hdd.qcow2",
    "xbe": SOURCE / "ROMs" / "Destroy All Humans! (USA).xiso" / "default.xbe",
    "xiso": SOURCE / "ROMs" / "Destroy All Humans! (USA).xiso.iso",
    "eeprom": Path(r"C:\Users\Bilbo\AppData\Roaming\xemu\xemu\eeprom.bin"),
    "helper": HERE / "renderdoc-helper-build" / "renderdoc_headless.exe",
    "renderdoc": Path(r"C:\Program Files\RenderDoc\renderdoc.dll"),
}
EXPECTED_XBE = "b9491b30eaee82af6c805d9b0036ec1119059b0660a0923803ebdb6219fa02eb"
EXPECTED_XISO = "da61c36c235eab4111dd540fb237eac01db5b2138451fa422b74e6aa9147c9b5"


def sha256(path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(8 * 1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def tcp_listeners():
    """Read the Windows listener tables; never connect to or bind a port."""
    function = ctypes.WinDLL("iphlpapi", use_last_error=True).GetExtendedTcpTable
    function.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_ulong),
                         ctypes.c_int, ctypes.c_ulong, ctypes.c_int, ctypes.c_ulong]
    function.restype = ctypes.c_ulong
    rows = []
    for family, stride, port_offset, pid_offset in [(2, 24, 8, 20), (23, 56, 20, 52)]:
        size = ctypes.c_ulong(0)
        result = function(None, ctypes.byref(size), False, family, 3, 0)
        if result not in (0, 122):
            raise RuntimeError(f"Cannot inspect TCP listener table: Windows {result}")
        for _ in range(3):
            buffer = ctypes.create_string_buffer(max(size.value, 4))
            result = function(buffer, ctypes.byref(size), False, family, 3, 0)
            if result != 122:
                break
        if result:
            raise RuntimeError(f"Cannot inspect TCP listener table: Windows {result}")
        raw = buffer.raw
        count = struct.unpack_from("<I", raw)[0]
        if count > (len(raw) - 4) // stride:
            raise RuntimeError("Invalid TCP listener table size")
        for i in range(count):
            offset = 4 + i * stride
            port = socket.ntohs(struct.unpack_from("<I", raw, offset + port_offset)[0] & 65535)
            pid = struct.unpack_from("<I", raw, offset + pid_offset)[0]
            rows.append({"family": family, "port": port, "pid": pid})
    return rows


def check_ports(ports):
    occupied = [row for row in tcp_listeners() if row["port"] in ports]
    if occupied:
        raise RuntimeError("Requested ports already have listeners: " + json.dumps(occupied))


def config_text(run):
    # JSON double-quoted path strings are also valid TOML basic strings.
    quote = lambda path: json.dumps(str(path))
    return f"""# Dedicated RenderDoc reference: generated for this unique run only.
[general]
show_welcome = false
screenshot_dir = {quote(run / 'screenshots')}
[general.updates]
check = false
[input]
background_input_capture = false
auto_bind = false
allow_vibration = false
[input.bindings]
port1_driver = 'usb-xbox-gamepad'
port1 = 'keyboard'
# Keep a real neutral guest USB pad, but map every host key to UNKNOWN.
# XInputGetState injection supplies logical pad values, never host events.
[input.keyboard_controller_scancode_map]
a = 0
b = 0
x = 0
y = 0
dpad_left = 0
dpad_up = 0
dpad_right = 0
dpad_down = 0
back = 0
start = 0
white = 0
black = 0
lstick_btn = 0
rstick_btn = 0
guide = 0
lstick_up = 0
lstick_left = 0
lstick_right = 0
lstick_down = 0
ltrigger = 0
rstick_up = 0
rstick_left = 0
rstick_right = 0
rstick_down = 0
rtrigger = 0
[display]
renderer = 'OPENGL'
setup_nvidia_profile = false
[display.quality]
surface_scale = 1
[display.window]
startup_size = '640x480'
vsync = false
fullscreen_on_startup = false
fullscreen_exclusive = false
[display.ui]
aspect_ratio = '4x3'
fit = 'scale'
[audio]
volume_limit = 0.0
[net]
enable = false
[sys]
mem_limit = '64'
[sys.files]
bootrom_path = {quote(FILES['bootrom'])}
flashrom_path = {quote(FILES['bios'])}
eeprom_path = {quote(run / 'eeprom.bin')}
hdd_path = {quote(FILES['hdd'])}
dvd_path = {quote(FILES['xiso'])}
"""


def write_new(path, value):
    with path.open("x", encoding="utf-8", newline="\n") as stream:
        stream.write(value)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--run-name", required=True, help="Unique ASCII slug; existing runs are refused")
    parser.add_argument("--gdb-port", type=int, default=1237)
    parser.add_argument("--qmp-port", type=int, default=4447)
    parser.add_argument("--verify-media", action="store_true", help="Also hash the full XISO during a dry plan")
    parser.add_argument("--start", action="store_true", help="Actually create the NEW isolated paused emulator")
    args = parser.parse_args(argv)
    if os.name != "nt":
        raise RuntimeError("This launcher requires Windows")
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9_-]{0,47}", args.run_name):
        raise RuntimeError("Run name must be 1..48 ASCII letters, digits, underscores or hyphens")
    ports = [args.gdb_port, args.qmp_port]
    if len(set(ports)) != 2 or any(not 1024 <= port <= 65535 for port in ports):
        raise RuntimeError("GDB and QMP ports must be distinct and in 1024..65535")
    run = PROJECT / "build-parity-xemu" / "renderdoc-runs" / args.run_name
    if run.exists():
        raise RuntimeError(f"Run directory already exists; refusing reuse: {run}")
    for label, path in FILES.items():
        if not path.is_file():
            raise RuntimeError(f"Missing {label}: {path}")
    check_ports(ports)
    xbe_hash = sha256(FILES["xbe"])
    if xbe_hash != EXPECTED_XBE:
        raise RuntimeError(f"Retail XBE identity mismatch: {xbe_hash}")
    xiso_hash = sha256(FILES["xiso"]) if args.start or args.verify_media else None
    if xiso_hash is not None and xiso_hash != EXPECTED_XISO:
        raise RuntimeError(f"Retail XISO identity mismatch: {xiso_hash}")
    config = config_text(run)
    tomllib.loads(config)
    command = ["-config_path", str(run / "xemu.toml"), "-snapshot", "-net", "none",
               "-gdb", f"tcp:127.0.0.1:{args.gdb_port}",
               "-qmp", f"tcp:127.0.0.1:{args.qmp_port},server=on,wait=off", "-S"]
    desktop = "DAHRenderdoc_" + args.run_name
    plan = {
        "schema": 1, "kind": "launch_plan", "startRequested": args.start,
        "runDirectory": str(run), "desktop": desktop, "guestPausedAtStartup": True,
        "newProcessOnly": True, "existingProcessAccess": False,
        "gdbPort": args.gdb_port, "qmpPort": args.qmp_port,
        "portsFreeAtPreflight": True, "renderer": "OPENGL", "surfaceScale": 1,
        "hostAspectRatio": "4x3", "hostWindowSize": "640x480", "hostFit": "scale",
        "processPriority": "below-normal", "hostAudioVolume": 0.0,
        "physicalControllerAutoBinding": False, "backgroundKeyboardCapture": False,
        "physicalKeyboardMappings": "all 25 SDL_SCANCODE_UNKNOWN",
        "referenceXbeSha256": xbe_hash, "referenceXisoSha256": xiso_hash,
        "referenceXisoVerification": "verified" if xiso_hash else "pending; required before --start",
        "expectedReferenceXisoSha256": EXPECTED_XISO,
        "xemuSourceSha256": sha256(FILES["xemu"]),
        "command": [str(FILES["xemu"]), *command],
        "capturePrefix": str(run / "capture"),
        "isolation": ["inactive desktop", "snapshot HDD overlay", "copied EEPROM",
                      "dedicated config", "private APPDATA/LOCALAPPDATA/TEMP/TMP",
                      "network disabled", "host audio muted", "NVIDIA profile setup disabled"],
        "sourceFiles": {key: str(value) for key, value in FILES.items()},
    }
    print(json.dumps(plan), flush=True)
    if not args.start:
        return 0
    # All mutations are confined to an exclusively created directory. No source
    # media, original config, environment, or existing process is modified.
    run.mkdir(parents=True, exist_ok=False)
    for name in ("appdata", "localappdata", "temp", "screenshots"):
        (run / name).mkdir()
    shutil.copyfile(FILES["eeprom"], run / "eeprom.bin")
    write_new(run / "xemu.toml", config)
    write_new(run / "launch-plan.json", json.dumps(plan, indent=2) + "\n")
    environment = os.environ.copy()
    environment.update(APPDATA=str(run / "appdata"), LOCALAPPDATA=str(run / "localappdata"),
                       TEMP=str(run / "temp"), TMP=str(run / "temp"))
    check_ports(ports)
    helper_args = [str(FILES["helper"]), "launch-xemu", str(FILES["xemu"]), str(run),
                   subprocess.list2cmdline(command), str(run / "capture"), desktop]
    try:
        with (run / "launcher.stdout.jsonl").open("xb") as output, (run / "launcher.stderr.log").open("xb") as error:
            completed = subprocess.run(helper_args, cwd=run, env=environment,
                stdin=subprocess.DEVNULL, stdout=output, stderr=error,
                creationflags=subprocess.CREATE_NO_WINDOW, timeout=120, check=False)
    except subprocess.TimeoutExpired:
        # The helper guards its newly created child with a kill-on-close job
        # during setup. Never resolve or terminate another process by name/PID.
        raise RuntimeError(f"Launcher timed out. Inspect {run}; do not retry this run name.") from None
    records = []
    for line in (run / "launcher.stdout.jsonl").read_text(encoding="utf-8", errors="replace").splitlines():
        try:
            records.append(json.loads(line))
        except json.JSONDecodeError:
            pass
    launched = next((record for record in records if record.get("kind") == "launched"), None)
    result = {"schema": 1, "launcherExitCode": completed.returncode, "launched": launched,
              "runDirectory": str(run), "guestPausedAtStartup": True,
              "frameCaptureVerified": False, "exactGuestFrameAssociationVerified": False}
    write_new(run / "launch-result.json", json.dumps(result, indent=2) + "\n")
    print(json.dumps(result), flush=True)
    if completed.returncode or not launched:
        raise RuntimeError(f"Launch did not report success. Inspect logs in {run}; no existing target was controlled.")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as error:
        print(str(error), file=sys.stderr)
        sys.exit(1)
