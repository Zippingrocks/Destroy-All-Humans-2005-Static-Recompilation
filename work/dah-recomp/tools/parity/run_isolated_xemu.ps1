param(
    [ValidateRange(1024, 65535)][int]$GdbPort = 1235,
    [ValidateRange(1024, 65535)][int]$QmpPort = 4445,
    [switch]$Start,
    [switch]$Paused,
    [switch]$Rendered
)
$ErrorActionPreference = 'Stop'

$xemuSource = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\xemu.exe'
$bootrom = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\Boot ROM image\mcpx_1.0.bin'
$bios = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\BIOS\Complex_4627v1.03.bin'
$hdd = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\Xemu Halo 2 E3 2003 Map Test 8-8-26\xbox_hdd.qcow2'
$xbe = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\ROMs\Destroy All Humans! (USA).xiso\default.xbe'
$xiso = 'C:\Users\Bilbo\Desktop\Emulation\XEMU\ROMs\Destroy All Humans! (USA).xiso.iso'
$sourceEeprom = 'C:\Users\Bilbo\AppData\Roaming\xemu\xemu\eeprom.bin'
$expectedXbeHash = 'B9491B30EAEE82AF6C805D9B0036EC1119059B0660A0923803EBDB6219FA02EB'
$expectedXisoHash = 'DA61C36C235EAB4111DD540FB237EAC01DB5B2138451FA422B74E6AA9147C9B5'
$runtime = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..\build-parity-xemu'))
$xemu = $xemuSource
$isolatedEeprom = Join-Path $runtime 'eeprom.bin'
$configTemplate = Join-Path $PSScriptRoot 'xemu-isolated.toml'
$isolatedConfig = Join-Path $runtime 'xemu.toml'
$stdoutLog = Join-Path $runtime 'xemu.stdout.log'
$stderrLog = Join-Path $runtime 'xemu.stderr.log'

foreach ($required in @($xemuSource, $bootrom, $bios, $hdd, $xbe, $xiso, $sourceEeprom, $configTemplate)) {
    if (!(Test-Path -LiteralPath $required)) { throw "Missing reference dependency: $required" }
}
$actualXbeHash = (Get-FileHash -LiteralPath $xbe -Algorithm SHA256).Hash
if ($actualXbeHash -ne $expectedXbeHash) {
    throw "Refusing mismatched XBE: expected $expectedXbeHash, got $actualXbeHash"
}
$actualXisoHash = (Get-FileHash -LiteralPath $xiso -Algorithm SHA256).Hash
if ($actualXisoHash -ne $expectedXisoHash) {
    throw "Refusing mismatched XISO: expected $expectedXisoHash, got $actualXisoHash"
}
foreach ($port in @($GdbPort, $QmpPort)) {
    if (Get-NetTCPConnection -State Listen -LocalPort $port -ErrorAction SilentlyContinue) {
        throw "TCP port $port is already in use"
    }
}

$arguments = @(
    '-config_path', $isolatedConfig,
    '-snapshot',
    '-net', 'none',
    '-gdb', "tcp:127.0.0.1:$GdbPort",
    '-qmp', "tcp:127.0.0.1:$QmpPort,server=on,wait=off"
)
if (!$Rendered) { $arguments += @('-display', 'none') }
if ($Paused) { $arguments += '-S' }

Write-Output "REFERENCE_XBE_SHA256 $actualXbeHash"
Write-Output "REFERENCE_XISO_SHA256 $actualXisoHash"
Write-Output "REFERENCE_COMMAND `"$xemu`" $($arguments -join ' ')"
if (!$Start) {
    Write-Output 'DRY_RUN_ONLY pass -Start to launch the isolated hidden reference'
    return
}

New-Item -ItemType Directory -Path $runtime -Force | Out-Null
Copy-Item -LiteralPath $sourceEeprom -Destination $isolatedEeprom -Force
Copy-Item -LiteralPath $configTemplate -Destination $isolatedConfig -Force
$argumentString = (($arguments | ForEach-Object {
    if ($_ -match '[\s"]') { '"' + ($_ -replace '(\\*)"', '$1$1\"' -replace '(\\+)$', '$1$1') + '"' }
    else { $_ }
}) -join ' ')
# xemu stores UI settings beneath APPDATA. Temporarily override only this
# launcher's environment; the parent/user environment is restored immediately.
$previousAppData = $env:APPDATA
try {
    $env:APPDATA = $runtime
    if ($Rendered) {
        if (!('DahParity.HiddenDesktop' -as [type])) {
            Add-Type -TypeDefinition @'
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Text;
namespace DahParity {
  public static class HiddenDesktop {
    [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode)]
    struct STARTUPINFO { public int cb; public string lpReserved, lpDesktop, lpTitle; public int dwX,dwY,dwXSize,dwYSize,dwXCountChars,dwYCountChars,dwFillAttribute,dwFlags; public short wShowWindow,cbReserved2; public IntPtr lpReserved2,hStdInput,hStdOutput,hStdError; }
    [StructLayout(LayoutKind.Sequential)]
    struct PROCESS_INFORMATION { public IntPtr hProcess,hThread; public int dwProcessId,dwThreadId; }
    [DllImport("user32.dll", CharSet=CharSet.Unicode, SetLastError=true)] static extern IntPtr CreateDesktop(string name, IntPtr device, IntPtr devmode, int flags, uint access, IntPtr security);
    [DllImport("kernel32.dll", CharSet=CharSet.Unicode, SetLastError=true)] static extern bool CreateProcess(string app, StringBuilder command, IntPtr pa, IntPtr ta, bool inherit, uint flags, IntPtr env, string cwd, ref STARTUPINFO si, out PROCESS_INFORMATION pi);
    [DllImport("kernel32.dll")] static extern bool CloseHandle(IntPtr handle);
    static IntPtr desktop;
    public static int Start(string desktopName, string app, string commandLine, string cwd) {
      desktop = CreateDesktop(desktopName, IntPtr.Zero, IntPtr.Zero, 0, 0x10000000, IntPtr.Zero);
      if (desktop == IntPtr.Zero) throw new Win32Exception(Marshal.GetLastWin32Error(), "CreateDesktop failed");
      var si = new STARTUPINFO(); si.cb = Marshal.SizeOf(si); si.lpDesktop = desktopName;
      PROCESS_INFORMATION pi;
      if (!CreateProcess(app, new StringBuilder(commandLine), IntPtr.Zero, IntPtr.Zero, false, 0, IntPtr.Zero, cwd, ref si, out pi))
        throw new Win32Exception(Marshal.GetLastWin32Error(), "CreateProcess failed");
      CloseHandle(pi.hThread); CloseHandle(pi.hProcess); return pi.dwProcessId;
    }
  }
}
'@
        }
        $commandLine = '"' + $xemu + '" ' + $argumentString
        $processId = [DahParity.HiddenDesktop]::Start('DAHParityDesktop', $xemu, $commandLine, (Split-Path -Parent $xemu))
        $process = Get-Process -Id $processId
    } else {
        $process = Start-Process -FilePath $xemu -ArgumentList $argumentString `
            -WorkingDirectory (Split-Path -Parent $xemu) -WindowStyle Hidden `
            -RedirectStandardOutput $stdoutLog -RedirectStandardError $stderrLog -PassThru
    }
} finally {
    $env:APPDATA = $previousAppData
}
Start-Sleep -Milliseconds 750
if ($process.HasExited) {
    $stderrText = if (Test-Path -LiteralPath $stderrLog) { Get-Content -LiteralPath $stderrLog -Raw } else { '' }
    throw "Isolated xemu exited immediately with code $($process.ExitCode). $stderrText"
}
Write-Output "REFERENCE_START pid=$($process.Id) gdb=$GdbPort qmp=$QmpPort paused=$Paused rendered=$Rendered desktop=$(if ($Rendered) { 'DAHParityDesktop' } else { 'none' })"
Write-Output "REFERENCE_STDERR $stderrLog"
Write-Output "REFERENCE_STOP Stop-Process -Id $($process.Id)"
