param(
    [Parameter(Mandatory=$true)][int]$ProcessId,
    [Parameter(Mandatory=$true)][string]$OutputPath
)

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class DahWindowCaptureNative {
    public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
    [StructLayout(LayoutKind.Sequential)] public struct RECT {
        public int Left, Top, Right, Bottom;
    }
    [StructLayout(LayoutKind.Sequential)] public struct POINT {
        public int X, Y;
    }
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr hWnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr hWnd, ref POINT point);
    [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr hWnd, IntPtr hdc, uint flags);
    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumWindowsProc callback, IntPtr lParam);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint processId);
}
'@

$process = Get-Process -Id $ProcessId -ErrorAction Stop
$handle = $process.MainWindowHandle
if ($handle -eq [IntPtr]::Zero) {
    $candidate = [IntPtr]::Zero
    $largestArea = 0L
    $callback = [DahWindowCaptureNative+EnumWindowsProc]{
        param([IntPtr]$hWnd, [IntPtr]$unused)
        [uint32]$ownerPid = 0
        [void][DahWindowCaptureNative]::GetWindowThreadProcessId($hWnd, [ref]$ownerPid)
        if ($ownerPid -eq [uint32]$ProcessId) {
            $rect = New-Object DahWindowCaptureNative+RECT
            if ([DahWindowCaptureNative]::GetWindowRect($hWnd, [ref]$rect)) {
                $area = [int64]($rect.Right - $rect.Left) * [int64]($rect.Bottom - $rect.Top)
                if ($area -gt $largestArea) { $script:largestArea = $area; $script:candidate = $hWnd }
            }
        }
        return $true
    }
    [void][DahWindowCaptureNative]::EnumWindows($callback, [IntPtr]::Zero)
    $handle = $candidate
}
if ($handle -eq [IntPtr]::Zero) { throw "Process $ProcessId has no top-level window." }

$window = New-Object DahWindowCaptureNative+RECT
$client = New-Object DahWindowCaptureNative+RECT
$origin = New-Object DahWindowCaptureNative+POINT
if (![DahWindowCaptureNative]::GetWindowRect($handle, [ref]$window)) { throw 'GetWindowRect failed.' }
if (![DahWindowCaptureNative]::GetClientRect($handle, [ref]$client)) { throw 'GetClientRect failed.' }
if (![DahWindowCaptureNative]::ClientToScreen($handle, [ref]$origin)) { throw 'ClientToScreen failed.' }

$windowWidth = $window.Right - $window.Left
$windowHeight = $window.Bottom - $window.Top
$clientWidth = $client.Right - $client.Left
$clientHeight = $client.Bottom - $client.Top
if ($windowWidth -le 0 -or $windowHeight -le 0 -or $clientWidth -le 0 -or $clientHeight -le 0) {
    throw 'Window or client rectangle is empty.'
}

$bitmap = New-Object Drawing.Bitmap $windowWidth, $windowHeight, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$graphics = [Drawing.Graphics]::FromImage($bitmap)
$hdc = $graphics.GetHdc()
try {
    $ok = [DahWindowCaptureNative]::PrintWindow($handle, $hdc, 2)
} finally {
    $graphics.ReleaseHdc($hdc)
    $graphics.Dispose()
}
if (!$ok) { $bitmap.Dispose(); throw 'PrintWindow failed.' }

$clientX = $origin.X - $window.Left
$clientY = $origin.Y - $window.Top
$clientBitmap = New-Object Drawing.Bitmap $clientWidth, $clientHeight, ([Drawing.Imaging.PixelFormat]::Format32bppArgb)
$clientGraphics = [Drawing.Graphics]::FromImage($clientBitmap)
try {
    $source = New-Object Drawing.Rectangle $clientX, $clientY, $clientWidth, $clientHeight
    $destination = New-Object Drawing.Rectangle 0, 0, $clientWidth, $clientHeight
    $clientGraphics.DrawImage($bitmap, $destination, $source, [Drawing.GraphicsUnit]::Pixel)
} finally {
    $clientGraphics.Dispose()
    $bitmap.Dispose()
}

$absoluteOutput = [IO.Path]::GetFullPath($OutputPath)
$directory = [IO.Path]::GetDirectoryName($absoluteOutput)
[IO.Directory]::CreateDirectory($directory) | Out-Null
$clientBitmap.Save($absoluteOutput, [Drawing.Imaging.ImageFormat]::Png)
$clientBitmap.Dispose()
Write-Output "CAPTURED pid=$ProcessId client=${clientWidth}x${clientHeight} path=$absoluteOutput"
