param(
    [Parameter(Mandatory)][int]$XemuPid,
    [Parameter(Mandatory)][string]$Out,
    [UInt64]$GuestAddress = 0,
    [ValidateRange(1,67108864)][int]$Length = 67108864,
    [UInt64]$RamBase = 0,
    [UInt32]$Cr3 = 0xF000,
    [string]$Xbe = (Join-Path $PSScriptRoot '..\..\..\default.xbe')
)
$ErrorActionPreference = 'Stop'
# This is process-memory debugging, not desktop automation. Only read rights
# are requested. Discovery walks the Xbox page tables and matches retail code.
$dahProcess = Get-Process -Id $XemuPid
if ($dahProcess.ProcessName -ne 'xemu') { throw 'Target is not xemu' }
$dahOut = [IO.Path]::GetFullPath($Out)
if (Test-Path -LiteralPath $dahOut) { throw 'Output already exists' }
if ($GuestAddress + $Length -gt 67108864) { throw 'Read exceeds 64 MiB Xbox RAM' }
if (!('DahParity.ReadMemory' -as [type])) {
Add-Type -TypeDefinition @'
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
namespace DahParity {
 public static class ReadMemory {
  [StructLayout(LayoutKind.Sequential)] struct Region {
   public ulong BaseAddress, AllocationBase; public uint AllocationProtect;
   public ushort PartitionId; public ushort Padding;
   public ulong RegionSize; public uint State, Protect, Type; public uint Padding2;
  }
  [DllImport("kernel32.dll", SetLastError=true)] static extern IntPtr OpenProcess(uint access, bool inherit, int pid);
  [DllImport("kernel32.dll", SetLastError=true)] static extern bool ReadProcessMemory(IntPtr process, ulong address, byte[] data, UIntPtr size, out UIntPtr read);
  [DllImport("kernel32.dll", SetLastError=true)] static extern UIntPtr VirtualQueryEx(IntPtr process, ulong address, out Region region, UIntPtr size);
  [DllImport("kernel32.dll")] static extern bool CloseHandle(IntPtr handle);
  static byte[] Read(IntPtr handle, ulong address, int length) {
   var bytes=new byte[length]; UIntPtr actual;
   if (!ReadProcessMemory(handle,address,bytes,(UIntPtr)length,out actual) || actual.ToUInt64()!=(ulong)length)
    throw new Win32Exception(Marshal.GetLastWin32Error(),"ReadProcessMemory");
   return bytes;
  }
  static uint Physical(byte[] ram, uint cr3, uint va) {
   uint pde=BitConverter.ToUInt32(ram,(int)((cr3&0xfffff000)+(va>>22)*4));
   if((pde&1)==0) return uint.MaxValue;
   if((pde&128)!=0) return (pde&0xffc00000)+(va&0x3fffff);
   uint table=pde&0xfffff000;
   if(table>ram.Length-4096) return uint.MaxValue;
   uint pte=BitConverter.ToUInt32(ram,(int)(table+((va>>12)&1023)*4));
   return (pte&1)!=0 ? (pte&0xfffff000)+(va&4095) : uint.MaxValue;
  }
  public static byte[] Capture(int pid, ulong ramBase, ulong offset, int length, uint cr3, byte[] expected, out ulong found) {
   IntPtr handle=OpenProcess(0x410,false,pid);
   if(handle==IntPtr.Zero) throw new Win32Exception(Marshal.GetLastWin32Error(),"OpenProcess read only");
   try {
    found=ramBase;
    if(found==0) {
     ulong address=0;
     while(address<0x00007fffffffffff) {
      Region region;
      if(VirtualQueryEx(handle,address,out region,(UIntPtr)Marshal.SizeOf<Region>())==UIntPtr.Zero) break;
      if(region.State==0x1000 && region.RegionSize==0x4000000 && (region.Protect&0x101)==0) {
       try {
        var ram=Read(handle,region.BaseAddress,0x4000000);
        uint physical=Physical(ram,cr3,0x000daca0);
        if(physical<ram.Length-expected.Length) {
         int p=(int)physical;
         bool match=true;
         for(int i=0;i<expected.Length;i++) if(ram[p+i]!=expected[i]) { match=false; break; }
         if(match) {
          if(found!=0 && found!=region.BaseAddress) throw new InvalidOperationException("Multiple Xbox RAM candidates");
          found=region.BaseAddress;
          Console.Error.WriteLine("XBE_CODE_MATCH va=0xdaca0 physical=0x{0:x} ram=0x{1:x}",p,found);
         }
        }
       } catch(Win32Exception) {}
      }
      ulong next=region.BaseAddress+region.RegionSize;
      if(next<=address) break;
      address=next;
     }
    }
    if(found==0) throw new InvalidOperationException("No validated Xbox RAM allocation found");
    var validation=Read(handle,found,0x4000000);
    uint checkAddress=Physical(validation,cr3,0x000daca0);
    if(checkAddress>validation.Length-expected.Length) throw new InvalidOperationException("RAM code mapping invalid");
    for(int i=0;i<expected.Length;i++) if(validation[checkAddress+i]!=expected[i])
     throw new InvalidOperationException("RAM code signature mismatch");
    return Read(handle,found+offset,length);
   } finally { CloseHandle(handle); }
  }
 }
}
'@
}
$dahFound = [UInt64]0
$dahXbeBytes = [IO.File]::ReadAllBytes([IO.Path]::GetFullPath($Xbe))
$dahImageBase = [BitConverter]::ToUInt32($dahXbeBytes,0x104)
$dahSectionTable = [BitConverter]::ToUInt32($dahXbeBytes,0x120) - $dahImageBase
$dahExpected = $null
for ($dahI=0; $dahI -lt [BitConverter]::ToUInt32($dahXbeBytes,0x11C); $dahI++) {
    $dahSection = $dahSectionTable + $dahI*56
    $dahVa = [BitConverter]::ToUInt32($dahXbeBytes,$dahSection+4)
    $dahSize = [BitConverter]::ToUInt32($dahXbeBytes,$dahSection+16)
    if (0xDACA0 -ge $dahVa -and 0xDACA0+32 -le $dahVa+$dahSize) {
        $dahOffset = [BitConverter]::ToUInt32($dahXbeBytes,$dahSection+12) + 0xDACA0 - $dahVa
        $dahExpected = [byte[]]$dahXbeBytes[$dahOffset..($dahOffset+31)]
    }
}
if (!$dahExpected) { throw 'Missing retail main-loop code in XBE' }
$dahBytes = [DahParity.ReadMemory]::Capture($XemuPid,$RamBase,$GuestAddress,$Length,$Cr3,$dahExpected,[ref]$dahFound)
$dahFile = [IO.File]::Open($dahOut,[IO.FileMode]::CreateNew)
try { $dahFile.Write($dahBytes,0,$dahBytes.Length) } finally { $dahFile.Dispose() }
[ordered]@{ source='xemu-host-ram'; pid=$XemuPid; ramBase=('0x{0:x}' -f $dahFound); cr3=$Cr3; guestAddress=$GuestAddress; length=$Length; capturedAt=[DateTime]::UtcNow.ToString('o'); output=$dahOut; xbeSha256=(Get-FileHash -LiteralPath $Xbe -Algorithm SHA256).Hash; consistency='Caller must pause and flush GPU before capture; live captures are not atomic' } | ConvertTo-Json | Tee-Object -FilePath "$dahOut.json"
