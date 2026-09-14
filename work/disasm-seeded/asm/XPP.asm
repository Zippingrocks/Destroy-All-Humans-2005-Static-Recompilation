; ============================================================
; Section: XPP
; VA: 0x0021F900 - 0x00225A04
; Size: 24836 bytes (24.3 KB)
; Functions: 161
; Instructions: 8393
; ============================================================

  0x0021F900  0000                    add      byte ptr [eax], al             
  0x0021F902  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0021FEEB (data_imm), 0x002215F3 (data_imm), 0x00221628 (data_imm)
  0x0021F904  64f9                    stc                                     
  0x0021F906  2100                    and      dword ptr [eax], eax           
  0x0021F908  ac                      lodsb    al, byte ptr [esi]             
  0x0021F909  f9                      stc                                     
  0x0021F90A  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0021FEF0 (data_imm), 0x002215FB (data_imm), 0x00221630 (data_imm)
  0x0021F90C  0000                    add      byte ptr [eax], al             
  0x0021F90E  0000                    add      byte ptr [eax], al             
  0x0021F910  0000                    add      byte ptr [eax], al             
  0x0021F912  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0021FDDB (data_imm), 0x00223202 (data_imm)
  0x0021F914  f8                      clc                                     
  0x0021F915  f9                      stc                                     
  0x0021F916  2100                    and      dword ptr [eax], eax           
  0x0021F918  10fa                    adc      dl, bh                         
  0x0021F91A  2100                    and      dword ptr [eax], eax           
  0x0021F91C  e0f9                    loopne   0x21f917                       
  0x0021F91E  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0021FDE0 (data_imm), 0x00223207 (data_imm)
  0x0021F920  0000                    add      byte ptr [eax], al             
  0x0021F922  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0021FADD (data_read), 0x00220319 (data_read), 0x002203FA (data_read), 0x00221AE3 (data_read)
  0x0021F924  0000                    add      byte ptr [eax], al             
  0x0021F926  0000                    add      byte ptr [eax], al             
  0x0021F928  0000                    add      byte ptr [eax], al             
  0x0021F92A  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x000F8589 (data_imm), 0x000FF46C (data_imm), 0x000FF501 (data_imm), 0x000FFB7E (data_imm)
  0x0021F92C  0000                    add      byte ptr [eax], al             
  0x0021F92E  0000                    add      byte ptr [eax], al             
  0x0021F930  0000                    add      byte ptr [eax], al             
  0x0021F932  0000                    add      byte ptr [eax], al             
  0x0021F934  0000                    add      byte ptr [eax], al             
  0x0021F936  0000                    add      byte ptr [eax], al             
  0x0021F938  0000                    add      byte ptr [eax], al             
  0x0021F93A  0000                    add      byte ptr [eax], al             
  0x0021F93C  0000                    add      byte ptr [eax], al             
  0x0021F93E  0000                    add      byte ptr [eax], al             
  0x0021F940  0000                    add      byte ptr [eax], al             
  0x0021F942  0000                    add      byte ptr [eax], al             
  0x0021F944  0000                    add      byte ptr [eax], al             
  0x0021F946  0000                    add      byte ptr [eax], al             
  0x0021F948  0000                    add      byte ptr [eax], al             
  0x0021F94A  0000                    add      byte ptr [eax], al             
  0x0021F94C  1238                    adc      bh, byte ptr [eax]             
  0x0021F94E  f9                      stc                                     
  0x0021F94F  2100                    and      dword ptr [eax], eax           
  0x0021F951  0000                    add      byte ptr [eax], al             
  0x0021F953  0000                    add      byte ptr [eax], al             
  0x0021F955  0000                    add      byte ptr [eax], al             
  0x0021F957  000454                  add      byte ptr [esp + edx*2], al     
  0x0021F95A  f9                      stc                                     
  0x0021F95B  2100                    and      dword ptr [eax], eax           
  0x0021F95D  0000                    add      byte ptr [eax], al             
  0x0021F95F  0001                    add      byte ptr [ecx], al             
  0x0021F961  0800                    or       byte ptr [eax], al             
  0x0021F963  0001                    add      byte ptr [ecx], al             
  0x0021F965  0400                    add      al, 0                          
  0x0021F967  002cf9                  add      byte ptr [ecx + edi*8], ch     
  0x0021F96A  2100                    and      dword ptr [eax], eax           
  0x0021F96C  4c                      dec      esp                            
  0x0021F96D  f9                      stc                                     
  0x0021F96E  2100                    and      dword ptr [eax], eax           
  0x0021F970  58                      pop      eax                            
  0x0021F971  f9                      stc                                     
  0x0021F972  2100                    and      dword ptr [eax], eax           
  0x0021F974  60                      pushal                                  
  0x0021F975  f9                      stc                                     
  0x0021F976  2100                    and      dword ptr [eax], eax           
  0x0021F978  0000                    add      byte ptr [eax], al             
  0x0021F97A  0000                    add      byte ptr [eax], al             
  0x0021F97C  0000                    add      byte ptr [eax], al             
  0x0021F97E  0000                    add      byte ptr [eax], al             
  0x0021F980  0000                    add      byte ptr [eax], al             
  0x0021F982  0000                    add      byte ptr [eax], al             
  0x0021F984  0000                    add      byte ptr [eax], al             
  0x0021F986  0000                    add      byte ptr [eax], al             
  0x0021F988  91                      xchg     ecx, eax                       
  0x0021F989  3522000000              xor      eax, 0x22                      
  0x0021F98E  0000                    add      byte ptr [eax], al             
  0x0021F990  0000                    add      byte ptr [eax], al             
  0x0021F992  0000                    add      byte ptr [eax], al             
  0x0021F994  0000                    add      byte ptr [eax], al             
  0x0021F996  0000                    add      byte ptr [eax], al             
  0x0021F998  0000                    add      byte ptr [eax], al             
  0x0021F99A  0000                    add      byte ptr [eax], al             
  0x0021F99C  0000                    add      byte ptr [eax], al             
  0x0021F99E  0000                    add      byte ptr [eax], al             
  0x0021F9A0  049c                    add      al, 0x9c                       
  0x0021F9A2  f9                      stc                                     
  0x0021F9A3  2100                    and      dword ptr [eax], eax           
  0x0021F9A5  0000                    add      byte ptr [eax], al             
  0x0021F9A7  0001                    add      byte ptr [ecx], al             
  0x0021F9A9  1000                    adc      byte ptr [eax], al             
  0x0021F9AB  0003                    add      byte ptr [ebx], al             
  0x0021F9AD  0100                    add      dword ptr [eax], eax           
  0x0021F9AF  0090f92100a0            add      byte ptr [eax - 0x5fffde07], dl 
  0x0021F9B5  f9                      stc                                     
  0x0021F9B6  2100                    and      dword ptr [eax], eax           
  0x0021F9B8  0000                    add      byte ptr [eax], al             
  0x0021F9BA  0000                    add      byte ptr [eax], al             
  0x0021F9BC  a8f9                    test     al, 0xf9                       
  0x0021F9BE  2100                    and      dword ptr [eax], eax           
  0x0021F9C0  0000                    add      byte ptr [eax], al             
  0x0021F9C2  0000                    add      byte ptr [eax], al             
  0x0021F9C4  0000                    add      byte ptr [eax], al             
  0x0021F9C6  0000                    add      byte ptr [eax], al             
  0x0021F9C8  0000                    add      byte ptr [eax], al             
  0x0021F9CA  0000                    add      byte ptr [eax], al             
  0x0021F9CC  0000                    add      byte ptr [eax], al             
  0x0021F9CE  0000                    add      byte ptr [eax], al             
  0x0021F9D0  e335                    jecxz    0x21fa07                       
  0x0021F9D2  2200                    and      al, byte ptr [eax]             
  0x0021F9D4  0000                    add      byte ptr [eax], al             
  0x0021F9D6  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0022176E (data_read), 0x0022177D (data_read), 0x00221783 (data_read)
  0x0021F9D8  e00f                    loopne   0x21f9e9                       
  0x0021F9DA  0000                    add      byte ptr [eax], al             
  0x0021F9DC  0000                    add      byte ptr [eax], al             
  0x0021F9DE  0000                    add      byte ptr [eax], al             
  0x0021F9E0  81090000dbfa            or       dword ptr [ecx], 0xfadb0000    
  0x0021F9E6  2100                    and      dword ptr [eax], eax           
  0x0021F9E8  97                      xchg     edi, eax                       
                                        ; XREF: 0x0021F9D8 (cond_jump)
  0x0021F9E9  2822                    sub      byte ptr [edx], ah             
  0x0021F9EB  008022220001            add      byte ptr [eax + 0x1002222], al 
  0x0021F9F1  0000                    add      byte ptr [eax], al             
  0x0021F9F3  00dc                    add      ah, bl                         
  0x0021F9F5  f9                      stc                                     
  0x0021F9F6  2100                    and      dword ptr [eax], eax           
  0x0021F9F8  8258ffff                sbb      byte ptr [eax - 1], 0xff       
  0x0021F9FC  b6fe                    mov      dh, 0xfe                       
  0x0021F9FE  2100                    and      dword ptr [eax], eax           
  0x0021FA00  f63f                    idiv     byte ptr [edi]                 
  0x0021FA02  2200                    and      al, byte ptr [eax]             
  0x0021FA04  d7                      xlatb                                   
  0x0021FA05  3922                    cmp      dword ptr [edx], esp           
                                        ; XREF: 0x0021F9D0 (cond_jump)
  0x0021FA07  0001                    add      byte ptr [ecx], al             
  0x0021FA09  0000                    add      byte ptr [eax], al             
  0x0021FA0B  0000                    add      byte ptr [eax], al             
  0x0021FA0D  0000                    add      byte ptr [eax], al             
  0x0021FA0F  008203ffffb6            add      byte ptr [edx - 0x490000fd], al 
  0x0021FA16  2100                    and      dword ptr [eax], eax           
  0x0021FA18  f63f                    idiv     byte ptr [edi]                 
  0x0021FA1A  2200                    and      al, byte ptr [eax]             
  0x0021FA1C  d7                      xlatb                                   
  0x0021FA1D  3922                    cmp      dword ptr [edx], esp           
  0x0021FA1F  0001                    add      byte ptr [ecx], al             
  0x0021FA21  0000                    add      byte ptr [eax], al             
  0x0021FA23  0000                    add      byte ptr [eax], al             
  0x0021FA25  0000                    add      byte ptr [eax], al             
  0x0021FA27  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0022006C (data_read), 0x00220088 (data_read), 0x002200A4 (data_read)
  0x0021FA29  0000                    add      byte ptr [eax], al             
  0x0021FA2B  0100                    add      dword ptr [eax], eax           
  0x0021FA2D  020a                    add      cl, byte ptr [edx]             
  0x0021FA2F  0000                    add      byte ptr [eax], al             
  0x0021FA31  0000                    add      byte ptr [eax], al             
  0x0021FA33  0000                    add      byte ptr [eax], al             
  0x0021FA35  0000                    add      byte ptr [eax], al             
  0x0021FA37  00558b                  add      byte ptr [ebp - 0x75], dl      
  0x0021FA3A  ec                      in       al, dx                         
  0x0021FA3B  8a4508                  mov      al, byte ptr [ebp + 8]         
  0x0021FA3E  53                      push     ebx                            
  0x0021FA3F  56                      push     esi                            
  0x0021FA40  57                      push     edi                            
  0x0021FA41  8bf1                    mov      esi, ecx                       
  0x0021FA43  0fb6f8                  movzx    edi, al                        
  0x0021FA46  88467a                  mov      byte ptr [esi + 0x7a], al      
  0x0021FA49  33db                    xor      ebx, ebx                       
  0x0021FA4B  8bc7                    mov      eax, edi                       
  0x0021FA4D  6855534244              push     0x44425355                     
  0x0021FA52  c1e005                  shl      eax, 5                         
  0x0021FA55  50                      push     eax                            
  0x0021FA56  881e                    mov      byte ptr [esi], bl             
  0x0021FA58  885e79                  mov      byte ptr [esi + 0x79], bl      
  0x0021FA5B  895e7c                  mov      dword ptr [esi + 0x7c], ebx    
  0x0021FA5E  899e80000000            mov      dword ptr [esi + 0x80], ebx    
  0x0021FA64  e8f21c0000              call     0x22175b                       ; -> sub_0022175B
  0x0021FA69  3bc3                    cmp      eax, ebx                       
  0x0021FA6B  894508                  mov      dword ptr [ebp + 8], eax       
  0x0021FA6E  7413                    je       0x21fa83                       
  0x0021FA70  68e2062200              push     0x2206e2                       
  0x0021FA75  57                      push     edi                            
  0x0021FA76  6a20                    push     0x20                           
  0x0021FA78  50                      push     eax                            
  0x0021FA79  e8b215dfff              call     0x11030                        ; -> sub_00011030
  0x0021FA7E  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x0021FA81  eb02                    jmp      0x21fa85                       
                                        ; XREF: 0x0021FA6E (cond_jump)
  0x0021FA83  33c0                    xor      eax, eax                       
                                        ; XREF: 0x0021FA81 (jump)
  0x0021FA85  0fb64e7a                movzx    ecx, byte ptr [esi + 0x7a]     
  0x0021FA89  8986e0000000            mov      dword ptr [esi + 0xe0], eax    
  0x0021FA8F  8a450c                  mov      al, byte ptr [ebp + 0xc]       
  0x0021FA92  88467b                  mov      byte ptr [esi + 0x7b], al      
  0x0021FA95  32c0                    xor      al, al                         
  0x0021FA97  49                      dec      ecx                            
  0x0021FA98  85c9                    test     ecx, ecx                       
  0x0021FA9A  7e1d                    jle      0x21fab9                       
  0x0021FA9C  33c9                    xor      ecx, ecx                       
                                        ; XREF: 0x0021FAB7 (cond_jump)
  0x0021FA9E  8b96e0000000            mov      edx, dword ptr [esi + 0xe0]    
  0x0021FAA4  fec0                    inc      al                             
  0x0021FAA6  c1e105                  shl      ecx, 5                         
  0x0021FAA9  88441101                mov      byte ptr [ecx + edx + 1], al   
  0x0021FAAD  0fb6567a                movzx    edx, byte ptr [esi + 0x7a]     
  0x0021FAB1  0fbec8                  movsx    ecx, al                        
  0x0021FAB4  4a                      dec      edx                            
  0x0021FAB5  3bca                    cmp      ecx, edx                       
  0x0021FAB7  7ce5                    jl       0x21fa9e                       
                                        ; XREF: 0x0021FA9A (cond_jump)
  0x0021FAB9  53                      push     ebx                            
  0x0021FABA  68e7142200              push     0x2214e7                       
  0x0021FABF  8d4634                  lea      eax, [esi + 0x34]              
  0x0021FAC2  50                      push     eax                            
  0x0021FAC3  ff153c5b2200            call     dword ptr [0x225b3c]           ; -> xbox_KeInitializeDpc
  0x0021FAC9  53                      push     ebx                            
  0x0021FACA  83c650                  add      esi, 0x50                      
  0x0021FACD  56                      push     esi                            
  0x0021FACE  ff15385b2200            call     dword ptr [0x225b38]           ; -> xbox_KeInitializeTimerEx
  0x0021FAD4  5f                      pop      edi                            
  0x0021FAD5  5e                      pop      esi                            
  0x0021FAD6  5b                      pop      ebx                            
  0x0021FAD7  5d                      pop      ebp                            
  0x0021FAD8  c20800                  ret      8                              

; ============================================================
; Function: sub_0021FADB
; Start: 0x0021FADB  End: 0x0021FB47  Size: 108 bytes
; Detection: seed_vtable_thunk (confidence: 0.95)
; Calls: sub_0022175B
; ============================================================
sub_0021FADB:
  0x0021FADB  33c0                    xor      eax, eax                       
  0x0021FADD  380524f92100            cmp      byte ptr [0x21f924], al        
  0x0021FAE3  57                      push     edi                            
  0x0021FAE4  0f95c0                  setne    al                             
  0x0021FAE7  668325226d280000        and      word ptr [0x286d22], 0         
  0x0021FAEF  6855534248              push     0x48425355                     
  0x0021FAF4  8d04c506000000          lea      eax, [eax*8 + 6]               
  0x0021FAFB  66a3206d2800            mov      word ptr [0x286d20], ax        
  0x0021FB01  0fb7c0                  movzx    eax, ax                        
  0x0021FB04  c1e006                  shl      eax, 6                         
  0x0021FB07  50                      push     eax                            
  0x0021FB08  e84e1c0000              call     0x22175b                       ; -> sub_0022175B
  0x0021FB0D  0fb70d206d2800          movzx    ecx, word ptr [0x286d20]       
  0x0021FB14  c1e106                  shl      ecx, 6                         
  0x0021FB17  8bd1                    mov      edx, ecx                       
  0x0021FB19  8bf8                    mov      edi, eax                       
  0x0021FB1B  c1e902                  shr      ecx, 2                         
  0x0021FB1E  893d246d2800            mov      dword ptr [0x286d24], edi      
  0x0021FB24  33c0                    xor      eax, eax                       
  0x0021FB26  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x0021FB28  8bca                    mov      ecx, edx                       
  0x0021FB2A  6a00                    push     0                              
  0x0021FB2C  83e103                  and      ecx, 3                         
  0x0021FB2F  68d06c2800              push     0x286cd0                       
  0x0021FB34  f3aa                    rep stosb byte ptr es:[edi], al          
  0x0021FB36  ff15385b2200            call     dword ptr [0x225b38]           ; -> xbox_KeInitializeTimerEx
  0x0021FB3C  8325186d280000          and      dword ptr [0x286d18], 0        
  0x0021FB43  5f                      pop      edi                            
  0x0021FB44  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_0021FB47
; Start: 0x0021FB47  End: 0x0021FBF7  Size: 176 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00222979
; Called by: sub_0021FC45
; ============================================================
sub_0021FB47:
  0x0021FB47  55                      push     ebp                            
  0x0021FB48  8bec                    mov      ebp, esp                       
  0x0021FB4A  51                      push     ecx                            
  0x0021FB4B  51                      push     ecx                            
  0x0021FB4C  53                      push     ebx                            
  0x0021FB4D  56                      push     esi                            
  0x0021FB4E  57                      push     edi                            
  0x0021FB4F  8bf1                    mov      esi, ecx                       
  0x0021FB51  8b1e                    mov      ebx, dword ptr [esi]           
  0x0021FB53  6a00                    push     0                              
  0x0021FB55  8d8678040000            lea      eax, [esi + 0x478]             
  0x0021FB5B  50                      push     eax                            
  0x0021FB5C  ff15385b2200            call     dword ptr [0x225b38]           ; -> xbox_KeInitializeTimerEx
  0x0021FB62  56                      push     esi                            
  0x0021FB63  68722a2200              push     0x222a72                       
  0x0021FB68  8d86a0040000            lea      eax, [esi + 0x4a0]             
  0x0021FB6E  50                      push     eax                            
  0x0021FB6F  ff153c5b2200            call     dword ptr [0x225b3c]           ; -> xbox_KeInitializeDpc
  0x0021FB75  c6866004000004          mov      byte ptr [esi + 0x460], 4      
  0x0021FB7C  8b4350                  mov      eax, dword ptr [ebx + 0x50]    
  0x0021FB7F  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x0021FB82  668365f800              and      word ptr [ebp - 8], 0          
  0x0021FB87  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x0021FB8A  33c9                    xor      ecx, ecx                       
  0x0021FB8C  894350                  mov      dword ptr [ebx + 0x50], eax    
  0x0021FB8F  33c0                    xor      eax, eax                       
  0x0021FB91  33d2                    xor      edx, edx                       
  0x0021FB93  8d7dfc                  lea      edi, [ebp - 4]                 
  0x0021FB96  41                      inc      ecx                            
  0x0021FB97  389660040000            cmp      byte ptr [esi + 0x460], dl     
  0x0021FB9D  ab                      stosd    dword ptr es:[edi], eax        
  0x0021FB9E  7631                    jbe      0x21fbd1                       
  0x0021FBA0  8d4354                  lea      eax, [ebx + 0x54]              
                                        ; XREF: 0x0021FBCF (cond_jump)
  0x0021FBA3  8b38                    mov      edi, dword ptr [eax]           
  0x0021FBA5  897df8                  mov      dword ptr [ebp - 8], edi       
  0x0021FBA8  f645f801                test     byte ptr [ebp - 8], 1          
  0x0021FBAC  7408                    je       0x21fbb6                       
  0x0021FBAE  66094dfe                or       word ptr [ebp - 2], cx         
  0x0021FBB2  66094dfc                or       word ptr [ebp - 4], cx         
                                        ; XREF: 0x0021FBAC (cond_jump)
  0x0021FBB6  668365f800              and      word ptr [ebp - 8], 0          
  0x0021FBBB  8b7df8                  mov      edi, dword ptr [ebp - 8]       
  0x0021FBBE  8938                    mov      dword ptr [eax], edi           
  0x0021FBC0  0fb6be60040000          movzx    edi, byte ptr [esi + 0x460]    
  0x0021FBC7  42                      inc      edx                            
  0x0021FBC8  83c004                  add      eax, 4                         
  0x0021FBCB  d1e1                    shl      ecx, 1                         
  0x0021FBCD  3bd7                    cmp      edx, edi                       
  0x0021FBCF  72d2                    jb       0x21fba3                       
                                        ; XREF: 0x0021FB9E (cond_jump)
  0x0021FBD1  c7431040000000          mov      dword ptr [ebx + 0x10], 0x40   
  0x0021FBD8  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x0021FBDE  8d55fc                  lea      edx, [ebp - 4]                 
  0x0021FBE1  8bce                    mov      ecx, esi                       
  0x0021FBE3  8ad8                    mov      bl, al                         
  0x0021FBE5  e88f2d0000              call     0x222979                       ; -> sub_00222979
  0x0021FBEA  8acb                    mov      cl, bl                         
  0x0021FBEC  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x0021FBF2  5f                      pop      edi                            
  0x0021FBF3  5e                      pop      esi                            
  0x0021FBF4  5b                      pop      ebx                            
  0x0021FBF5  c9                      leave                                   
  0x0021FBF6  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0021FBF7
; Start: 0x0021FBF7  End: 0x0021FC03  Size: 12 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022044F
; Called by: sub_0021FDC0
; ============================================================
sub_0021FBF7:
  0x0021FBF7  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021FBFB  e84f080000              call     0x22044f                       ; -> sub_0022044F
  0x0021FC00  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_0021FC03
; Start: 0x0021FC03  End: 0x0021FC45  Size: 66 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0021FE39
; Called by: sub_0021FDC0
; ============================================================
sub_0021FC03:
  0x0021FC03  55                      push     ebp                            
  0x0021FC04  8bec                    mov      ebp, esp                       
  0x0021FC06  83ec28                  sub      esp, 0x28                      
  0x0021FC09  a1a85a2200              mov      eax, dword ptr [0x225aa8]      
  0x0021FC0E  807805a1                cmp      byte ptr [eax + 5], 0xa1       
  0x0021FC12  742f                    je       0x21fc43                       
  0x0021FC14  8d45fc                  lea      eax, [ebp - 4]                 
  0x0021FC17  50                      push     eax                            
  0x0021FC18  6a01                    push     1                              
  0x0021FC1A  c645e803                mov      byte ptr [ebp - 0x18], 3       
  0x0021FC1E  c745f000100000          mov      dword ptr [ebp - 0x10], 0x1000 
  0x0021FC25  c745ec0000d0fe          mov      dword ptr [ebp - 0x14], 0xfed00000 
  0x0021FC2C  ff15745b2200            call     dword ptr [0x225b74]           ; -> xbox_HalGetInterruptVector
  0x0021FC32  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x0021FC35  68e0040000              push     0x4e0                          
  0x0021FC3A  8d45d8                  lea      eax, [ebp - 0x28]              
  0x0021FC3D  50                      push     eax                            
  0x0021FC3E  e8f6010000              call     0x21fe39                       ; -> sub_0021FE39
                                        ; XREF: 0x0021FC12 (cond_jump)
  0x0021FC43  c9                      leave                                   
  0x0021FC44  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0021FC45
; Start: 0x0021FC45  End: 0x0021FDC0  Size: 379 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0021FB47, sub_00220614, sub_00220675, sub_00220680, sub_00222B5C, sub_00224167
; Called by: sub_0021FE39
; ============================================================
sub_0021FC45:
  0x0021FC45  55                      push     ebp                            
  0x0021FC46  8bec                    mov      ebp, esp                       
  0x0021FC48  51                      push     ecx                            
  0x0021FC49  fe4d0c                  dec      byte ptr [ebp + 0xc]           
  0x0021FC4C  8b4510                  mov      eax, dword ptr [ebp + 0x10]    
  0x0021FC4F  53                      push     ebx                            
  0x0021FC50  56                      push     esi                            
  0x0021FC51  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x0021FC54  57                      push     edi                            
  0x0021FC55  0fb67d0c                movzx    edi, byte ptr [ebp + 0xc]      
  0x0021FC59  89be5c040000            mov      dword ptr [esi + 0x45c], edi   
  0x0021FC5F  8b4818                  mov      ecx, dword ptr [eax + 0x18]    
  0x0021FC62  894e04                  mov      dword ptr [esi + 4], ecx       
  0x0021FC65  8b4014                  mov      eax, dword ptr [eax + 0x14]    
  0x0021FC68  56                      push     esi                            
  0x0021FC69  897dfc                  mov      dword ptr [ebp - 4], edi       
  0x0021FC6C  8906                    mov      dword ptr [esi], eax           
  0x0021FC6E  e8020a0000              call     0x220675                       ; -> sub_00220675
  0x0021FC73  56                      push     esi                            
  0x0021FC74  e8070a0000              call     0x220680                       ; -> sub_00220680
  0x0021FC79  8b1e                    mov      ebx, dword ptr [esi]           
  0x0021FC7B  56                      push     esi                            
  0x0021FC7C  68aa4c2200              push     0x224caa                       
  0x0021FC81  8d8640040000            lea      eax, [esi + 0x440]             
  0x0021FC87  c7434800120000          mov      dword ptr [ebx + 0x48], 0x1200 
  0x0021FC8E  c7434c00000000          mov      dword ptr [ebx + 0x4c], 0      
  0x0021FC95  c7435000000080          mov      dword ptr [ebx + 0x50], 0x80000000 
  0x0021FC9C  50                      push     eax                            
  0x0021FC9D  ff153c5b2200            call     dword ptr [0x225b3c]           ; -> xbox_KeInitializeDpc
  0x0021FCA3  8b04bd84782800          mov      eax, dword ptr [edi*4 + 0x287884] 
  0x0021FCAA  894608                  mov      dword ptr [esi + 8], eax       
  0x0021FCAD  8b4308                  mov      eax, dword ptr [ebx + 8]       
  0x0021FCB0  894508                  mov      dword ptr [ebp + 8], eax       
  0x0021FCB3  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x0021FCB9  88450f                  mov      byte ptr [ebp + 0xf], al       
  0x0021FCBC  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x0021FCBF  83c801                  or       eax, 1                         
  0x0021FCC2  894308                  mov      dword ptr [ebx + 8], eax       
  0x0021FCC5  6a0a                    push     0xa                            
  0x0021FCC7  ff15845b2200            call     dword ptr [0x225b84]           ; -> xbox_KeStallExecutionProcessor
  0x0021FCCD  8bce                    mov      ecx, esi                       
  0x0021FCCF  e840090000              call     0x220614                       ; -> sub_00220614
  0x0021FCD4  c74304be000000          mov      dword ptr [ebx + 4], 0xbe      
  0x0021FCDB  8b4334                  mov      eax, dword ptr [ebx + 0x34]    
  0x0021FCDE  25d8ee72a7              and      eax, 0xa772eed8                
  0x0021FCE3  0dd82e7227              or       eax, 0x27722ed8                
  0x0021FCE8  8bc8                    mov      ecx, eax                       
  0x0021FCEA  f7d1                    not      ecx                            
  0x0021FCEC  33c8                    xor      ecx, eax                       
  0x0021FCEE  81e1ffffff7f            and      ecx, 0x7fffffff                
  0x0021FCF4  f7d0                    not      eax                            
  0x0021FCF6  33c8                    xor      ecx, eax                       
  0x0021FCF8  894b34                  mov      dword ptr [ebx + 0x34], ecx    
  0x0021FCFB  a1a85a2200              mov      eax, dword ptr [0x225aa8]      
  0x0021FD00  f60001                  test     byte ptr [eax], 1              
  0x0021FD03  7543                    jne      0x21fd48                       
  0x0021FD05  c7450802000000          mov      dword ptr [ebp + 8], 2         
                                        ; XREF: 0x0021FD43 (cond_jump)
  0x0021FD0C  e84b2e0000              call     0x222b5c                       ; -> sub_00222B5C
  0x0021FD11  8bd0                    mov      edx, eax                       
  0x0021FD13  33c0                    xor      eax, eax                       
  0x0021FD15  6a0c                    push     0xc                            
  0x0021FD17  59                      pop      ecx                            
  0x0021FD18  8bfa                    mov      edi, edx                       
  0x0021FD1A  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x0021FD1C  8bc2                    mov      eax, edx                       
  0x0021FD1E  2b0580782800            sub      eax, dword ptr [0x287880]      
  0x0021FD24  8bce                    mov      ecx, esi                       
  0x0021FD26  894214                  mov      dword ptr [edx + 0x14], eax    
  0x0021FD29  8b02                    mov      eax, dword ptr [edx]           
  0x0021FD2B  25ffff08f8              and      eax, 0xf808ffff                
  0x0021FD30  0d00000800              or       eax, 0x80000                   
  0x0021FD35  c6421100                mov      byte ptr [edx + 0x11], 0       
  0x0021FD39  8902                    mov      dword ptr [edx], eax           
  0x0021FD3B  e827440000              call     0x224167                       ; -> sub_00224167
  0x0021FD40  ff4d08                  dec      dword ptr [ebp + 8]            
  0x0021FD43  75c7                    jne      0x21fd0c                       
  0x0021FD45  8b7dfc                  mov      edi, dword ptr [ebp - 4]       
                                        ; XREF: 0x0021FD03 (cond_jump)
  0x0021FD48  8a4d0f                  mov      cl, byte ptr [ebp + 0xf]       
  0x0021FD4B  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x0021FD51  6bff70                  imul     edi, edi, 0x70                 
  0x0021FD54  8b4510                  mov      eax, dword ptr [ebp + 0x10]    
  0x0021FD57  33c9                    xor      ecx, ecx                       
  0x0021FD59  8a4824                  mov      cl, byte ptr [eax + 0x24]      
  0x0021FD5C  6a00                    push     0                              
  0x0021FD5E  6a00                    push     0                              
  0x0021FD60  8dbfc0782800            lea      edi, [edi + 0x2878c0]          
  0x0021FD66  51                      push     ecx                            
  0x0021FD67  ff701c                  push     dword ptr [eax + 0x1c]         
  0x0021FD6A  56                      push     esi                            
  0x0021FD6B  68d6452200              push     0x2245d6                       
  0x0021FD70  57                      push     edi                            
  0x0021FD71  ff15805b2200            call     dword ptr [0x225b80]           ; -> xbox_KeInitializeInterrupt
  0x0021FD77  57                      push     edi                            
  0x0021FD78  ff157c5b2200            call     dword ptr [0x225b7c]           ; -> xbox_KeConnectInterrupt
  0x0021FD7E  33d2                    xor      edx, edx                       
  0x0021FD80  42                      inc      edx                            
  0x0021FD81  8d8ec0040000            lea      ecx, [esi + 0x4c0]             
  0x0021FD87  8d86c8040000            lea      eax, [esi + 0x4c8]             
  0x0021FD8D  52                      push     edx                            
  0x0021FD8E  51                      push     ecx                            
  0x0021FD8F  c701862e2200            mov      dword ptr [ecx], 0x222e86      
  0x0021FD95  8996c4040000            mov      dword ptr [esi + 0x4c4], edx   
  0x0021FD9B  8986cc040000            mov      dword ptr [esi + 0x4cc], eax   
  0x0021FDA1  8900                    mov      dword ptr [eax], eax           
  0x0021FDA3  ff15ac5a2200            call     dword ptr [0x225aac]           ; -> xbox_HalRegisterShutdownNotification
  0x0021FDA9  8bce                    mov      ecx, esi                       
  0x0021FDAB  c7431033000080          mov      dword ptr [ebx + 0x10], 0x80000033 
  0x0021FDB2  e890fdffff              call     0x21fb47                       ; -> sub_0021FB47
  0x0021FDB7  5f                      pop      edi                            
  0x0021FDB8  5e                      pop      esi                            
  0x0021FDB9  33c0                    xor      eax, eax                       
  0x0021FDBB  5b                      pop      ebx                            
  0x0021FDBC  c9                      leave                                   
  0x0021FDBD  c20c00                  ret      0xc                            
; end of function

; ============================================================
; Function: sub_0021FDC0
; Start: 0x0021FDC0  End: 0x0021FE39  Size: 121 bytes
; Detection: tail_jump_target (confidence: 0.88)
; Calls: 0x0021FA38, sub_0021FBF7, sub_0021FC03, sub_00220306, sub_0022314A
; ============================================================
sub_0021FDC0:
  0x0021FDC0  55                      push     ebp                            
  0x0021FDC1  8d6c2490                lea      ebp, [esp - 0x70]              
  0x0021FDC5  81ecb4000000            sub      esp, 0xb4                      
  0x0021FDCB  56                      push     esi                            
  0x0021FDCC  57                      push     edi                            
  0x0021FDCD  ff757c                  push     dword ptr [ebp + 0x7c]         
  0x0021FDD0  8d4dbc                  lea      ecx, [ebp - 0x44]              
  0x0021FDD3  ff7578                  push     dword ptr [ebp + 0x78]         
  0x0021FDD6  e86f330000              call     0x22314a                       ; -> sub_0022314A
  0x0021FDDB  b814f92100              mov      eax, 0x21f914                  
  0x0021FDE0  be20f92100              mov      esi, 0x21f920                  
  0x0021FDE5  3bc6                    cmp      eax, esi                       
  0x0021FDE7  8bf8                    mov      edi, eax                       
  0x0021FDE9  7314                    jae      0x21fdff                       
                                        ; XREF: 0x0021FDFD (cond_jump)
  0x0021FDEB  8b07                    mov      eax, dword ptr [edi]           
  0x0021FDED  85c0                    test     eax, eax                       
  0x0021FDEF  7407                    je       0x21fdf8                       
  0x0021FDF1  8d4dbc                  lea      ecx, [ebp - 0x44]              
  0x0021FDF4  51                      push     ecx                            
  0x0021FDF5  ff5004                  call     dword ptr [eax + 4]            
                                        ; XREF: 0x0021FDEF (cond_jump)
  0x0021FDF8  83c704                  add      edi, 4                         
  0x0021FDFB  3bfe                    cmp      edi, esi                       
  0x0021FDFD  72ec                    jb       0x21fdeb                       
                                        ; XREF: 0x0021FDE9 (cond_jump)
  0x0021FDFF  8d4dbc                  lea      ecx, [ebp - 0x44]              
  0x0021FE02  e8ff040000              call     0x220306                       ; -> sub_00220306
  0x0021FE07  8d4560                  lea      eax, [ebp + 0x60]              
  0x0021FE0A  50                      push     eax                            
  0x0021FE0B  e8e7fdffff              call     0x21fbf7                       ; -> sub_0021FBF7
  0x0021FE10  0fb6455d                movzx    eax, byte ptr [ebp + 0x5d]     
  0x0021FE14  50                      push     eax                            
  0x0021FE15  0fb6455c                movzx    eax, byte ptr [ebp + 0x5c]     
  0x0021FE19  50                      push     eax                            
  0x0021FE1A  b9806b2800              mov      ecx, 0x286b80                  
  0x0021FE1F  e814fcffff              call     0x21fa38                       
  0x0021FE24  c6052c6d280000          mov      byte ptr [0x286d2c], 0         
  0x0021FE2B  e8d3fdffff              call     0x21fc03                       ; -> sub_0021FC03
  0x0021FE30  5f                      pop      edi                            
  0x0021FE31  5e                      pop      esi                            
  0x0021FE32  83c570                  add      ebp, 0x70                      
  0x0021FE35  c9                      leave                                   
  0x0021FE36  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_0021FE39
; Start: 0x0021FE39  End: 0x0021FEB6  Size: 125 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0021FC45, sub_002206F4, sub_0022175B
; Called by: sub_0021FC03
; ============================================================
sub_0021FE39:
  0x0021FE39  56                      push     esi                            
  0x0021FE3A  57                      push     edi                            
  0x0021FE3B  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x0021FE3F  6855534244              push     0x44425355                     
  0x0021FE44  83c718                  add      edi, 0x18                      
  0x0021FE47  57                      push     edi                            
  0x0021FE48  e80e190000              call     0x22175b                       ; -> sub_0022175B
  0x0021FE4D  8bf0                    mov      esi, eax                       
  0x0021FE4F  85f6                    test     esi, esi                       
  0x0021FE51  745e                    je       0x21feb1                       
  0x0021FE53  8bcf                    mov      ecx, edi                       
  0x0021FE55  8bd1                    mov      edx, ecx                       
  0x0021FE57  c1e902                  shr      ecx, 2                         
  0x0021FE5A  33c0                    xor      eax, eax                       
  0x0021FE5C  8bfe                    mov      edi, esi                       
  0x0021FE5E  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x0021FE60  8bca                    mov      ecx, edx                       
  0x0021FE62  83e103                  and      ecx, 3                         
  0x0021FE65  f3aa                    rep stosb byte ptr es:[edi], al          
  0x0021FE67  fe052c6d2800            inc      byte ptr [0x286d2c]            
  0x0021FE6D  0fb6052c6d2800          movzx    eax, byte ptr [0x286d2c]       
  0x0021FE74  b9806b2800              mov      ecx, 0x286b80                  
  0x0021FE79  8906                    mov      dword ptr [esi], eax           
  0x0021FE7B  e874080000              call     0x2206f4                       ; -> sub_002206F4
  0x0021FE80  ff74240c                push     dword ptr [esp + 0xc]          
  0x0021FE84  8d4e04                  lea      ecx, [esi + 4]                 
  0x0021FE87  8901                    mov      dword ptr [ecx], eax           
  0x0021FE89  c60000                  mov      byte ptr [eax], 0              
  0x0021FE8C  8b01                    mov      eax, dword ptr [ecx]           
  0x0021FE8E  c6400280                mov      byte ptr [eax + 2], 0x80       
  0x0021FE92  8b01                    mov      eax, dword ptr [ecx]           
  0x0021FE94  c6400180                mov      byte ptr [eax + 1], 0x80       
  0x0021FE98  8b01                    mov      eax, dword ptr [ecx]           
  0x0021FE9A  c6400380                mov      byte ptr [eax + 3], 0x80       
  0x0021FE9E  8b01                    mov      eax, dword ptr [ecx]           
  0x0021FEA0  89700c                  mov      dword ptr [eax + 0xc], esi     
  0x0021FEA3  33c0                    xor      eax, eax                       
  0x0021FEA5  8a06                    mov      al, byte ptr [esi]             
  0x0021FEA7  83c618                  add      esi, 0x18                      
  0x0021FEAA  50                      push     eax                            
  0x0021FEAB  56                      push     esi                            
  0x0021FEAC  e894fdffff              call     0x21fc45                       ; -> sub_0021FC45
                                        ; XREF: 0x0021FE51 (cond_jump)
  0x0021FEB1  5f                      pop      edi                            
  0x0021FEB2  5e                      pop      esi                            
  0x0021FEB3  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_0021FEB6
; Start: 0x0021FEB6  End: 0x002200C1  Size: 523 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002200C1, sub_002200F8, sub_00220104, sub_0022175B
; ============================================================
sub_0021FEB6:
  0x0021FEB6  55                      push     ebp                            
  0x0021FEB7  8bec                    mov      ebp, esp                       
  0x0021FEB9  83ec60                  sub      esp, 0x60                      
  0x0021FEBC  56                      push     esi                            
  0x0021FEBD  33f6                    xor      esi, esi                       
  0x0021FEBF  393534fa2100            cmp      dword ptr [0x21fa34], esi      
  0x0021FEC5  8975f8                  mov      dword ptr [ebp - 8], esi       
  0x0021FEC8  8975fc                  mov      dword ptr [ebp - 4], esi       
  0x0021FECB  8975f4                  mov      dword ptr [ebp - 0xc], esi     
  0x0021FECE  0f85e8010000            jne      0x2200bc                       
  0x0021FED4  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x0021FED7  53                      push     ebx                            
  0x0021FED8  57                      push     edi                            
  0x0021FED9  c70534fa210001000000    mov      dword ptr [0x21fa34], 1        
  0x0021FEE3  e810020000              call     0x2200f8                       ; -> sub_002200F8
  0x0021FEE8  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x0021FEEB  b804f92100              mov      eax, 0x21f904                  
  0x0021FEF0  bb0cf92100              mov      ebx, 0x21f90c                  
  0x0021FEF5  3bc3                    cmp      eax, ebx                       
  0x0021FEF7  8bf8                    mov      edi, eax                       
  0x0021FEF9  7374                    jae      0x21ff6f                       
                                        ; XREF: 0x0021FF4D (cond_jump)
  0x0021FEFB  8b07                    mov      eax, dword ptr [edi]           
  0x0021FEFD  85c0                    test     eax, eax                       
  0x0021FEFF  7447                    je       0x21ff48                       
  0x0021FF01  8b4004                  mov      eax, dword ptr [eax + 4]       
  0x0021FF04  8944b5a0                mov      dword ptr [ebp + esi*4 - 0x60], eax 
  0x0021FF08  46                      inc      esi                            
  0x0021FF09  837df000                cmp      dword ptr [ebp - 0x10], 0      
  0x0021FF0D  750e                    jne      0x21ff1d                       
  0x0021FF0F  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x0021FF12  50                      push     eax                            
  0x0021FF13  e8a9010000              call     0x2200c1                       ; -> sub_002200C1
  0x0021FF18  8b0f                    mov      ecx, dword ptr [edi]           
  0x0021FF1A  884101                  mov      byte ptr [ecx + 1], al         
                                        ; XREF: 0x0021FF0D (cond_jump)
  0x0021FF1D  8b07                    mov      eax, dword ptr [edi]           
  0x0021FF1F  8b4014                  mov      eax, dword ptr [eax + 0x14]    
  0x0021FF22  85c0                    test     eax, eax                       
  0x0021FF24  7402                    je       0x21ff28                       
  0x0021FF26  ffd0                    call     eax                            
                                        ; XREF: 0x0021FF24 (cond_jump)
  0x0021FF28  8b07                    mov      eax, dword ptr [edi]           
  0x0021FF2A  8b4828                  mov      ecx, dword ptr [eax + 0x28]    
  0x0021FF2D  f6c104                  test     cl, 4                          
  0x0021FF30  0fb64001                movzx    eax, byte ptr [eax + 1]        
  0x0021FF34  7405                    je       0x21ff3b                       
  0x0021FF36  0145fc                  add      dword ptr [ebp - 4], eax       
  0x0021FF39  eb0d                    jmp      0x21ff48                       
                                        ; XREF: 0x0021FF34 (cond_jump)
  0x0021FF3B  f6c108                  test     cl, 8                          
  0x0021FF3E  7405                    je       0x21ff45                       
  0x0021FF40  0145f4                  add      dword ptr [ebp - 0xc], eax     
  0x0021FF43  eb03                    jmp      0x21ff48                       
                                        ; XREF: 0x0021FF3E (cond_jump)
  0x0021FF45  0145f8                  add      dword ptr [ebp - 8], eax       
                                        ; XREF: 0x0021FEFF (cond_jump), 0x0021FF39 (jump), 0x0021FF43 (jump)
  0x0021FF48  83c704                  add      edi, 4                         
  0x0021FF4B  3bfb                    cmp      edi, ebx                       
  0x0021FF4D  72ac                    jb       0x21fefb                       
  0x0021FF4F  837df400                cmp      dword ptr [ebp - 0xc], 0       
  0x0021FF53  740b                    je       0x21ff60                       
  0x0021FF55  66c705306d28000c00      mov      word ptr [0x286d30], 0xc       
  0x0021FF5E  eb18                    jmp      0x21ff78                       
                                        ; XREF: 0x0021FF53 (cond_jump)
  0x0021FF60  837dfc00                cmp      dword ptr [ebp - 4], 0         
  0x0021FF64  66c705306d28000800      mov      word ptr [0x286d30], 8         
  0x0021FF6D  7509                    jne      0x21ff78                       
                                        ; XREF: 0x0021FEF9 (cond_jump)
  0x0021FF6F  66c705306d28000400      mov      word ptr [0x286d30], 4         
                                        ; XREF: 0x0021FF5E (jump), 0x0021FF6D (cond_jump)
  0x0021FF78  6a04                    push     4                              
  0x0021FF7A  58                      pop      eax                            
  0x0021FF7B  3945f8                  cmp      dword ptr [ebp - 8], eax       
  0x0021FF7E  7603                    jbe      0x21ff83                       
  0x0021FF80  8945f8                  mov      dword ptr [ebp - 8], eax       
                                        ; XREF: 0x0021FF7E (cond_jump)
  0x0021FF83  3945fc                  cmp      dword ptr [ebp - 4], eax       
  0x0021FF86  7603                    jbe      0x21ff8b                       
  0x0021FF88  8945fc                  mov      dword ptr [ebp - 4], eax       
                                        ; XREF: 0x0021FF86 (cond_jump)
  0x0021FF8B  8b4df4                  mov      ecx, dword ptr [ebp - 0xc]     
  0x0021FF8E  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x0021FF91  03c1                    add      eax, ecx                       
  0x0021FF93  6a08                    push     8                              
  0x0021FF95  59                      pop      ecx                            
  0x0021FF96  3bc1                    cmp      eax, ecx                       
  0x0021FF98  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x0021FF9B  7603                    jbe      0x21ffa0                       
  0x0021FF9D  894df0                  mov      dword ptr [ebp - 0x10], ecx    
                                        ; XREF: 0x0021FF9B (cond_jump)
  0x0021FFA0  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x0021FFA3  0345f8                  add      eax, dword ptr [ebp - 8]       
  0x0021FFA6  0fb70d306d2800          movzx    ecx, word ptr [0x286d30]       
  0x0021FFAD  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x0021FFB0  6bc916                  imul     ecx, ecx, 0x16                 
  0x0021FFB3  69c0ab000000            imul     eax, eax, 0xab                 
  0x0021FFB9  8bde                    mov      ebx, esi                       
  0x0021FFBB  c1e302                  shl      ebx, 2                         
  0x0021FFBE  03cb                    add      ecx, ebx                       
  0x0021FFC0  03c1                    add      eax, ecx                       
  0x0021FFC2  685849445f              push     0x5f444958                     
  0x0021FFC7  50                      push     eax                            
  0x0021FFC8  e88e170000              call     0x22175b                       ; -> sub_0022175B
  0x0021FFCD  8bcb                    mov      ecx, ebx                       
  0x0021FFCF  8bd1                    mov      edx, ecx                       
  0x0021FFD1  c1e902                  shr      ecx, 2                         
  0x0021FFD4  893508fa2100            mov      dword ptr [0x21fa08], esi      
  0x0021FFDA  893520fa2100            mov      dword ptr [0x21fa20], esi      
  0x0021FFE0  a30cfa2100              mov      dword ptr [0x21fa0c], eax      
  0x0021FFE5  a324fa2100              mov      dword ptr [0x21fa24], eax      
  0x0021FFEA  8bf8                    mov      edi, eax                       
  0x0021FFEC  8d75a0                  lea      esi, [ebp - 0x60]              
  0x0021FFEF  f3a5                    rep movsd dword ptr es:[edi], dword ptr [esi] 
  0x0021FFF1  8bca                    mov      ecx, edx                       
  0x0021FFF3  8b55f0                  mov      edx, dword ptr [ebp - 0x10]    
  0x0021FFF6  83e103                  and      ecx, 3                         
  0x0021FFF9  f3a4                    rep movsb byte ptr es:[edi], byte ptr [esi] 
  0x0021FFFB  33ff                    xor      edi, edi                       
  0x0021FFFD  33c9                    xor      ecx, ecx                       
  0x0021FFFF  03c3                    add      eax, ebx                       
  0x00220001  3bd7                    cmp      edx, edi                       
  0x00220003  890d386d2800            mov      dword ptr [0x286d38], ecx      
  0x00220009  7616                    jbe      0x220021                       
                                        ; XREF: 0x00220019 (cond_jump)
  0x0022000B  8988a7000000            mov      dword ptr [eax + 0xa7], ecx    
  0x00220011  8bc8                    mov      ecx, eax                       
  0x00220013  05ab000000              add      eax, 0xab                      
  0x00220018  4a                      dec      edx                            
  0x00220019  75f0                    jne      0x22000b                       
  0x0022001B  890d386d2800            mov      dword ptr [0x286d38], ecx      
                                        ; XREF: 0x00220009 (cond_jump)
  0x00220021  33d2                    xor      edx, edx                       
  0x00220023  66393d306d2800          cmp      word ptr [0x286d30], di        
  0x0022002A  a3346d2800              mov      dword ptr [0x286d34], eax      
  0x0022002F  66893d326d2800          mov      word ptr [0x286d32], di        
  0x00220036  761d                    jbe      0x220055                       
  0x00220038  33c9                    xor      ecx, ecx                       
                                        ; XREF: 0x00220053 (cond_jump)
  0x0022003A  a1346d2800              mov      eax, dword ptr [0x286d34]      
  0x0022003F  8d440104                lea      eax, [ecx + eax + 4]           
  0x00220043  8020fe                  and      byte ptr [eax], 0xfe           
  0x00220046  0fb705306d2800          movzx    eax, word ptr [0x286d30]       
  0x0022004D  42                      inc      edx                            
  0x0022004E  83c116                  add      ecx, 0x16                      
  0x00220051  3bd0                    cmp      edx, eax                       
  0x00220053  72e5                    jb       0x22003a                       
                                        ; XREF: 0x00220036 (cond_jump)
  0x00220055  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00220058  3bc7                    cmp      eax, edi                       
  0x0022005A  be28fa2100              mov      esi, 0x21fa28                  
  0x0022005F  7415                    je       0x220076                       
  0x00220061  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00220064  56                      push     esi                            
  0x00220065  c60528fa210000          mov      byte ptr [0x21fa28], 0         
  0x0022006C  a229fa2100              mov      byte ptr [0x21fa29], al        
  0x00220071  e88e000000              call     0x220104                       ; -> sub_00220104
                                        ; XREF: 0x0022005F (cond_jump)
  0x00220076  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x00220079  3bc7                    cmp      eax, edi                       
  0x0022007B  7415                    je       0x220092                       
  0x0022007D  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00220080  56                      push     esi                            
  0x00220081  c60528fa210002          mov      byte ptr [0x21fa28], 2         
  0x00220088  a229fa2100              mov      byte ptr [0x21fa29], al        
  0x0022008D  e872000000              call     0x220104                       ; -> sub_00220104
                                        ; XREF: 0x0022007B (cond_jump)
  0x00220092  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x00220095  3bc7                    cmp      eax, edi                       
  0x00220097  7415                    je       0x2200ae                       
  0x00220099  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x0022009C  56                      push     esi                            
  0x0022009D  c60528fa210001          mov      byte ptr [0x21fa28], 1         
  0x002200A4  a229fa2100              mov      byte ptr [0x21fa29], al        
  0x002200A9  e856000000              call     0x220104                       ; -> sub_00220104
                                        ; XREF: 0x00220097 (cond_jump)
  0x002200AE  57                      push     edi                            
  0x002200AF  68886d2800              push     0x286d88                       
  0x002200B4  ff15385b2200            call     dword ptr [0x225b38]           ; -> xbox_KeInitializeTimerEx
  0x002200BA  5f                      pop      edi                            
  0x002200BB  5b                      pop      ebx                            
                                        ; XREF: 0x0021FECE (cond_jump)
  0x002200BC  5e                      pop      esi                            
  0x002200BD  c9                      leave                                   
  0x002200BE  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002200C1
; Start: 0x002200C1  End: 0x002200F8  Size: 55 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FEB6
; ============================================================
sub_002200C1:
  0x002200C1  8b919c000000            mov      edx, dword ptr [ecx + 0x9c]    
  0x002200C7  33c0                    xor      eax, eax                       
  0x002200C9  85d2                    test     edx, edx                       
  0x002200CB  7422                    je       0x2200ef                       
  0x002200CD  8b8998000000            mov      ecx, dword ptr [ecx + 0x98]    
  0x002200D3  85c9                    test     ecx, ecx                       
  0x002200D5  56                      push     esi                            
  0x002200D6  57                      push     edi                            
  0x002200D7  7612                    jbe      0x2200eb                       
  0x002200D9  8bf2                    mov      esi, edx                       
                                        ; XREF: 0x002200E9 (cond_jump)
  0x002200DB  8b3e                    mov      edi, dword ptr [esi]           
  0x002200DD  3b7c240c                cmp      edi, dword ptr [esp + 0xc]     
  0x002200E1  740f                    je       0x2200f2                       
  0x002200E3  40                      inc      eax                            
  0x002200E4  83c608                  add      esi, 8                         
  0x002200E7  3bc1                    cmp      eax, ecx                       
  0x002200E9  72f0                    jb       0x2200db                       
                                        ; XREF: 0x002200D7 (cond_jump)
  0x002200EB  33c0                    xor      eax, eax                       
                                        ; XREF: 0x002200F6 (jump)
  0x002200ED  5f                      pop      edi                            
  0x002200EE  5e                      pop      esi                            
                                        ; XREF: 0x002200CB (cond_jump)
  0x002200EF  c20400                  ret      4                              
                                        ; XREF: 0x002200E1 (cond_jump)
  0x002200F2  8b44c204                mov      eax, dword ptr [edx + eax*8 + 4] 
  0x002200F6  ebf5                    jmp      0x2200ed                       
; end of function

; ============================================================
; Function: sub_002200F8
; Start: 0x002200F8  End: 0x00220104  Size: 12 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FEB6
; ============================================================
sub_002200F8:
  0x002200F8  33c0                    xor      eax, eax                       
  0x002200FA  39819c000000            cmp      dword ptr [ecx + 0x9c], eax    
  0x00220100  0f94c0                  sete     al                             
  0x00220103  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220104
; Start: 0x00220104  End: 0x00220306  Size: 514 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220104
; Called by: sub_0021FEB6, sub_00220104
; ============================================================
sub_00220104:
  0x00220104  55                      push     ebp                            
  0x00220105  8bec                    mov      ebp, esp                       
  0x00220107  83ec0c                  sub      esp, 0xc                       
  0x0022010A  53                      push     ebx                            
  0x0022010B  56                      push     esi                            
  0x0022010C  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x0022010F  0fb64601                movzx    eax, byte ptr [esi + 1]        
  0x00220113  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x00220116  0fb606                  movzx    eax, byte ptr [esi]            
  0x00220119  83e800                  sub      eax, 0                         
  0x0022011C  8bd1                    mov      edx, ecx                       
  0x0022011E  57                      push     edi                            
  0x0022011F  8955f4                  mov      dword ptr [ebp - 0xc], edx     
  0x00220122  7440                    je       0x220164                       
  0x00220124  48                      dec      eax                            
  0x00220125  7438                    je       0x22015f                       
  0x00220127  48                      dec      eax                            
  0x00220128  753e                    jne      0x220168                       
  0x0022012A  8a4602                  mov      al, byte ptr [esi + 2]         
  0x0022012D  3a4234                  cmp      al, byte ptr [edx + 0x34]      
  0x00220130  8d5a64                  lea      ebx, [edx + 0x64]              
  0x00220133  7603                    jbe      0x220138                       
  0x00220135  884234                  mov      byte ptr [edx + 0x34], al      
                                        ; XREF: 0x00220133 (cond_jump)
  0x00220138  8a4601                  mov      al, byte ptr [esi + 1]         
  0x0022013B  3c04                    cmp      al, 4                          
  0x0022013D  762c                    jbe      0x22016b                       
  0x0022013F  2c04                    sub      al, 4                          
  0x00220141  56                      push     esi                            
  0x00220142  8bca                    mov      ecx, edx                       
  0x00220144  884601                  mov      byte ptr [esi + 1], al         
  0x00220147  c60601                  mov      byte ptr [esi], 1              
  0x0022014A  e8b5ffffff              call     0x220104                       ; -> sub_00220104
  0x0022014F  80460104                add      byte ptr [esi + 1], 4          
  0x00220153  836df804                sub      dword ptr [ebp - 8], 4         
  0x00220157  8b55f4                  mov      edx, dword ptr [ebp - 0xc]     
  0x0022015A  c60602                  mov      byte ptr [esi], 2              
  0x0022015D  eb0c                    jmp      0x22016b                       
                                        ; XREF: 0x00220125 (cond_jump)
  0x0022015F  8d5a32                  lea      ebx, [edx + 0x32]              
  0x00220162  eb07                    jmp      0x22016b                       
                                        ; XREF: 0x00220122 (cond_jump)
  0x00220164  8bda                    mov      ebx, edx                       
  0x00220166  eb03                    jmp      0x22016b                       
                                        ; XREF: 0x00220128 (cond_jump)
  0x00220168  8b5d08                  mov      ebx, dword ptr [ebp + 8]       
                                        ; XREF: 0x0022013D (cond_jump), 0x0022015D (jump), 0x00220162 (jump), 0x00220166 (jump)
  0x0022016B  8a4602                  mov      al, byte ptr [esi + 2]         
  0x0022016E  3a4302                  cmp      al, byte ptr [ebx + 2]         
  0x00220171  7603                    jbe      0x220176                       
  0x00220173  884302                  mov      byte ptr [ebx + 2], al         
                                        ; XREF: 0x00220171 (cond_jump)
  0x00220176  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00220179  83650800                and      dword ptr [ebp + 8], 0         
  0x0022017D  85c0                    test     eax, eax                       
  0x0022017F  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x00220182  7449                    je       0x2201cd                       
  0x00220184  8d7b03                  lea      edi, [ebx + 3]                 
                                        ; XREF: 0x002201CB (cond_jump)
  0x00220187  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x0022018B  7340                    jae      0x2201cd                       
  0x0022018D  8a07                    mov      al, byte ptr [edi]             
  0x0022018F  3a4603                  cmp      al, byte ptr [esi + 3]         
  0x00220192  7608                    jbe      0x22019c                       
  0x00220194  ff4508                  inc      dword ptr [ebp + 8]            
  0x00220197  83c70a                  add      edi, 0xa                       
  0x0022019A  eb2b                    jmp      0x2201c7                       
                                        ; XREF: 0x00220192 (cond_jump)
  0x0022019C  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x002201A0  7317                    jae      0x2201b9                       
  0x002201A2  6a04                    push     4                              
  0x002201A4  58                      pop      eax                            
  0x002201A5  2b4508                  sub      eax, dword ptr [ebp + 8]       
  0x002201A8  8d4b2b                  lea      ecx, [ebx + 0x2b]              
                                        ; XREF: 0x002201B4 (cond_jump)
  0x002201AB  8a51f6                  mov      dl, byte ptr [ecx - 0xa]       
  0x002201AE  8811                    mov      byte ptr [ecx], dl             
  0x002201B0  83e90a                  sub      ecx, 0xa                       
  0x002201B3  48                      dec      eax                            
  0x002201B4  75f5                    jne      0x2201ab                       
  0x002201B6  8b55f4                  mov      edx, dword ptr [ebp - 0xc]     
                                        ; XREF: 0x002201A0 (cond_jump)
  0x002201B9  8a4603                  mov      al, byte ptr [esi + 3]         
  0x002201BC  ff4508                  inc      dword ptr [ebp + 8]            
  0x002201BF  8807                    mov      byte ptr [edi], al             
  0x002201C1  83c70a                  add      edi, 0xa                       
  0x002201C4  ff4dfc                  dec      dword ptr [ebp - 4]            
                                        ; XREF: 0x0022019A (jump)
  0x002201C7  837dfc00                cmp      dword ptr [ebp - 4], 0         
  0x002201CB  75ba                    jne      0x220187                       
                                        ; XREF: 0x00220182 (cond_jump), 0x0022018B (cond_jump)
  0x002201CD  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x002201D0  83650800                and      dword ptr [ebp + 8], 0         
  0x002201D4  85c0                    test     eax, eax                       
  0x002201D6  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x002201D9  7449                    je       0x220224                       
  0x002201DB  8d7b04                  lea      edi, [ebx + 4]                 
                                        ; XREF: 0x00220222 (cond_jump)
  0x002201DE  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x002201E2  7340                    jae      0x220224                       
  0x002201E4  8a07                    mov      al, byte ptr [edi]             
  0x002201E6  3a4604                  cmp      al, byte ptr [esi + 4]         
  0x002201E9  7608                    jbe      0x2201f3                       
  0x002201EB  ff4508                  inc      dword ptr [ebp + 8]            
  0x002201EE  83c70a                  add      edi, 0xa                       
  0x002201F1  eb2b                    jmp      0x22021e                       
                                        ; XREF: 0x002201E9 (cond_jump)
  0x002201F3  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x002201F7  7317                    jae      0x220210                       
  0x002201F9  6a04                    push     4                              
  0x002201FB  58                      pop      eax                            
  0x002201FC  2b4508                  sub      eax, dword ptr [ebp + 8]       
  0x002201FF  8d4b2c                  lea      ecx, [ebx + 0x2c]              
                                        ; XREF: 0x0022020B (cond_jump)
  0x00220202  8a51f6                  mov      dl, byte ptr [ecx - 0xa]       
  0x00220205  8811                    mov      byte ptr [ecx], dl             
  0x00220207  83e90a                  sub      ecx, 0xa                       
  0x0022020A  48                      dec      eax                            
  0x0022020B  75f5                    jne      0x220202                       
  0x0022020D  8b55f4                  mov      edx, dword ptr [ebp - 0xc]     
                                        ; XREF: 0x002201F7 (cond_jump)
  0x00220210  8a4604                  mov      al, byte ptr [esi + 4]         
  0x00220213  ff4508                  inc      dword ptr [ebp + 8]            
  0x00220216  8807                    mov      byte ptr [edi], al             
  0x00220218  83c70a                  add      edi, 0xa                       
  0x0022021B  ff4dfc                  dec      dword ptr [ebp - 4]            
                                        ; XREF: 0x002201F1 (jump)
  0x0022021E  837dfc00                cmp      dword ptr [ebp - 4], 0         
  0x00220222  75ba                    jne      0x2201de                       
                                        ; XREF: 0x002201D9 (cond_jump), 0x002201E2 (cond_jump)
  0x00220224  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00220227  83650800                and      dword ptr [ebp + 8], 0         
  0x0022022B  85c0                    test     eax, eax                       
  0x0022022D  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x00220230  7449                    je       0x22027b                       
  0x00220232  8d7b05                  lea      edi, [ebx + 5]                 
                                        ; XREF: 0x00220279 (cond_jump)
  0x00220235  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x00220239  7340                    jae      0x22027b                       
  0x0022023B  8a07                    mov      al, byte ptr [edi]             
  0x0022023D  3a4605                  cmp      al, byte ptr [esi + 5]         
  0x00220240  7608                    jbe      0x22024a                       
  0x00220242  ff4508                  inc      dword ptr [ebp + 8]            
  0x00220245  83c70a                  add      edi, 0xa                       
  0x00220248  eb2b                    jmp      0x220275                       
                                        ; XREF: 0x00220240 (cond_jump)
  0x0022024A  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x0022024E  7317                    jae      0x220267                       
  0x00220250  6a04                    push     4                              
  0x00220252  58                      pop      eax                            
  0x00220253  2b4508                  sub      eax, dword ptr [ebp + 8]       
  0x00220256  8d4b2d                  lea      ecx, [ebx + 0x2d]              
                                        ; XREF: 0x00220262 (cond_jump)
  0x00220259  8a51f6                  mov      dl, byte ptr [ecx - 0xa]       
  0x0022025C  8811                    mov      byte ptr [ecx], dl             
  0x0022025E  83e90a                  sub      ecx, 0xa                       
  0x00220261  48                      dec      eax                            
  0x00220262  75f5                    jne      0x220259                       
  0x00220264  8b55f4                  mov      edx, dword ptr [ebp - 0xc]     
                                        ; XREF: 0x0022024E (cond_jump)
  0x00220267  8a4605                  mov      al, byte ptr [esi + 5]         
  0x0022026A  ff4508                  inc      dword ptr [ebp + 8]            
  0x0022026D  8807                    mov      byte ptr [edi], al             
  0x0022026F  83c70a                  add      edi, 0xa                       
  0x00220272  ff4dfc                  dec      dword ptr [ebp - 4]            
                                        ; XREF: 0x00220248 (jump)
  0x00220275  837dfc00                cmp      dword ptr [ebp - 4], 0         
  0x00220279  75ba                    jne      0x220235                       
                                        ; XREF: 0x00220230 (cond_jump), 0x00220239 (cond_jump)
  0x0022027B  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x0022027E  83650800                and      dword ptr [ebp + 8], 0         
  0x00220282  85c0                    test     eax, eax                       
  0x00220284  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x00220287  7449                    je       0x2202d2                       
  0x00220289  8d7b08                  lea      edi, [ebx + 8]                 
                                        ; XREF: 0x002202D0 (cond_jump)
  0x0022028C  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x00220290  7340                    jae      0x2202d2                       
  0x00220292  8a07                    mov      al, byte ptr [edi]             
  0x00220294  3a4608                  cmp      al, byte ptr [esi + 8]         
  0x00220297  7608                    jbe      0x2202a1                       
  0x00220299  ff4508                  inc      dword ptr [ebp + 8]            
  0x0022029C  83c70a                  add      edi, 0xa                       
  0x0022029F  eb2b                    jmp      0x2202cc                       
                                        ; XREF: 0x00220297 (cond_jump)
  0x002202A1  837d0804                cmp      dword ptr [ebp + 8], 4         
  0x002202A5  7317                    jae      0x2202be                       
  0x002202A7  6a04                    push     4                              
  0x002202A9  58                      pop      eax                            
  0x002202AA  2b4508                  sub      eax, dword ptr [ebp + 8]       
  0x002202AD  8d4b30                  lea      ecx, [ebx + 0x30]              
                                        ; XREF: 0x002202B9 (cond_jump)
  0x002202B0  8a51f6                  mov      dl, byte ptr [ecx - 0xa]       
  0x002202B3  8811                    mov      byte ptr [ecx], dl             
  0x002202B5  83e90a                  sub      ecx, 0xa                       
  0x002202B8  48                      dec      eax                            
  0x002202B9  75f5                    jne      0x2202b0                       
  0x002202BB  8b55f4                  mov      edx, dword ptr [ebp - 0xc]     
                                        ; XREF: 0x002202A5 (cond_jump)
  0x002202BE  8a4608                  mov      al, byte ptr [esi + 8]         
  0x002202C1  ff4508                  inc      dword ptr [ebp + 8]            
  0x002202C4  8807                    mov      byte ptr [edi], al             
  0x002202C6  83c70a                  add      edi, 0xa                       
  0x002202C9  ff4dfc                  dec      dword ptr [ebp - 4]            
                                        ; XREF: 0x0022029F (jump)
  0x002202CC  837dfc00                cmp      dword ptr [ebp - 4], 0         
  0x002202D0  75ba                    jne      0x22028c                       
                                        ; XREF: 0x00220287 (cond_jump), 0x00220290 (cond_jump)
  0x002202D2  8a4606                  mov      al, byte ptr [esi + 6]         
  0x002202D5  8d8ab0000000            lea      ecx, [edx + 0xb0]              
  0x002202DB  3a01                    cmp      al, byte ptr [ecx]             
  0x002202DD  7602                    jbe      0x2202e1                       
  0x002202DF  8801                    mov      byte ptr [ecx], al             
                                        ; XREF: 0x002202DD (cond_jump)
  0x002202E1  8a4607                  mov      al, byte ptr [esi + 7]         
  0x002202E4  8d8ab1000000            lea      ecx, [edx + 0xb1]              
  0x002202EA  3a01                    cmp      al, byte ptr [ecx]             
  0x002202EC  7602                    jbe      0x2202f0                       
  0x002202EE  8801                    mov      byte ptr [ecx], al             
                                        ; XREF: 0x002202EC (cond_jump)
  0x002202F0  8a4609                  mov      al, byte ptr [esi + 9]         
  0x002202F3  5f                      pop      edi                            
  0x002202F4  8d8ab2000000            lea      ecx, [edx + 0xb2]              
  0x002202FA  3a01                    cmp      al, byte ptr [ecx]             
  0x002202FC  5e                      pop      esi                            
  0x002202FD  5b                      pop      ebx                            
  0x002202FE  7602                    jbe      0x220302                       
  0x00220300  8801                    mov      byte ptr [ecx], al             
                                        ; XREF: 0x002202FE (cond_jump)
  0x00220302  c9                      leave                                   
  0x00220303  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00220306
; Start: 0x00220306  End: 0x0022044F  Size: 329 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_0021FDC0
; ============================================================
sub_00220306:
  0x00220306  55                      push     ebp                            
  0x00220307  8bec                    mov      ebp, esp                       
  0x00220309  83ec0c                  sub      esp, 0xc                       
  0x0022030C  53                      push     ebx                            
  0x0022030D  33c0                    xor      eax, eax                       
  0x0022030F  56                      push     esi                            
  0x00220310  33f6                    xor      esi, esi                       
  0x00220312  c681a000000010          mov      byte ptr [ecx + 0xa0], 0x10    
  0x00220319  380524f92100            cmp      byte ptr [0x21f924], al        
  0x0022031F  57                      push     edi                            
  0x00220320  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x00220323  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x00220326  7407                    je       0x22032f                       
  0x00220328  c681a000000030          mov      byte ptr [ecx + 0xa0], 0x30    
                                        ; XREF: 0x00220326 (cond_jump)
  0x0022032F  8a4102                  mov      al, byte ptr [ecx + 2]         
  0x00220332  8a5134                  mov      dl, byte ptr [ecx + 0x34]      
  0x00220335  02d0                    add      dl, al                         
  0x00220337  025166                  add      dl, byte ptr [ecx + 0x66]      
  0x0022033A  c0e202                  shl      dl, 2                          
  0x0022033D  80c203                  add      dl, 3                          
  0x00220340  0091a0000000            add      byte ptr [ecx + 0xa0], dl      
  0x00220346  3a81a1000000            cmp      al, byte ptr [ecx + 0xa1]      
  0x0022034C  7606                    jbe      0x220354                       
  0x0022034E  8881a1000000            mov      byte ptr [ecx + 0xa1], al      
                                        ; XREF: 0x0022034C (cond_jump)
  0x00220354  8a4166                  mov      al, byte ptr [ecx + 0x66]      
  0x00220357  3a81a1000000            cmp      al, byte ptr [ecx + 0xa1]      
  0x0022035D  7606                    jbe      0x220365                       
  0x0022035F  8881a1000000            mov      byte ptr [ecx + 0xa1], al      
                                        ; XREF: 0x0022035D (cond_jump)
  0x00220365  8a4134                  mov      al, byte ptr [ecx + 0x34]      
  0x00220368  3a81a1000000            cmp      al, byte ptr [ecx + 0xa1]      
  0x0022036E  7606                    jbe      0x220376                       
  0x00220370  8881a1000000            mov      byte ptr [ecx + 0xa1], al      
                                        ; XREF: 0x0022036E (cond_jump)
  0x00220376  8a81a1000000            mov      al, byte ptr [ecx + 0xa1]      
  0x0022037C  0081a0000000            add      byte ptr [ecx + 0xa0], al      
  0x00220382  8d4137                  lea      eax, [ecx + 0x37]              
  0x00220385  c745f404000000          mov      dword ptr [ebp - 0xc], 4       
                                        ; XREF: 0x002203F8 (cond_jump)
  0x0022038C  0fb67832                movzx    edi, byte ptr [eax + 0x32]     
  0x00220390  0fb650ce                movzx    edx, byte ptr [eax - 0x32]     
  0x00220394  03d7                    add      edx, edi                       
  0x00220396  0fb638                  movzx    edi, byte ptr [eax]            
  0x00220399  03fe                    add      edi, esi                       
  0x0022039B  8d3417                  lea      esi, [edi + edx]               
  0x0022039E  0fb67830                movzx    edi, byte ptr [eax + 0x30]     
  0x002203A2  0fb650cc                movzx    edx, byte ptr [eax - 0x34]     
  0x002203A6  03d7                    add      edx, edi                       
  0x002203A8  0fb678fe                movzx    edi, byte ptr [eax - 2]        
  0x002203AC  037dfc                  add      edi, dword ptr [ebp - 4]       
  0x002203AF  83c00a                  add      eax, 0xa                       
  0x002203B2  03fa                    add      edi, edx                       
  0x002203B4  0fb650c3                movzx    edx, byte ptr [eax - 0x3d]     
  0x002203B8  897dfc                  mov      dword ptr [ebp - 4], edi       
  0x002203BB  0fb67827                movzx    edi, byte ptr [eax + 0x27]     
  0x002203BF  03d7                    add      edx, edi                       
  0x002203C1  0fb678f5                movzx    edi, byte ptr [eax - 0xb]      
  0x002203C5  037df8                  add      edi, dword ptr [ebp - 8]       
  0x002203C8  03fa                    add      edi, edx                       
  0x002203CA  0fb650c7                movzx    edx, byte ptr [eax - 0x39]     
  0x002203CE  0191a8000000            add      dword ptr [ecx + 0xa8], edx    
  0x002203D4  0fb6582b                movzx    ebx, byte ptr [eax + 0x2b]     
  0x002203D8  8b91a8000000            mov      edx, dword ptr [ecx + 0xa8]    
  0x002203DE  03d3                    add      edx, ebx                       
  0x002203E0  8991a8000000            mov      dword ptr [ecx + 0xa8], edx    
  0x002203E6  0fb658f9                movzx    ebx, byte ptr [eax - 7]        
  0x002203EA  03da                    add      ebx, edx                       
  0x002203EC  ff4df4                  dec      dword ptr [ebp - 0xc]          
  0x002203EF  897df8                  mov      dword ptr [ebp - 8], edi       
  0x002203F2  8999a8000000            mov      dword ptr [ecx + 0xa8], ebx    
  0x002203F8  7592                    jne      0x22038c                       
  0x002203FA  803d24f9210000          cmp      byte ptr [0x21f924], 0         
  0x00220401  7409                    je       0x22040c                       
  0x00220403  83c60d                  add      esi, 0xd                       
  0x00220406  8345fc0d                add      dword ptr [ebp - 4], 0xd       
  0x0022040A  eb07                    jmp      0x220413                       
                                        ; XREF: 0x00220401 (cond_jump)
  0x0022040C  83c605                  add      esi, 5                         
  0x0022040F  8345fc05                add      dword ptr [ebp - 4], 5         
                                        ; XREF: 0x0022040A (jump)
  0x00220413  ff45fc                  inc      dword ptr [ebp - 4]            
  0x00220416  8d91b0000000            lea      edx, [ecx + 0xb0]              
  0x0022041C  803a0d                  cmp      byte ptr [edx], 0xd            
  0x0022041F  7303                    jae      0x220424                       
  0x00220421  c6020d                  mov      byte ptr [edx], 0xd            
                                        ; XREF: 0x0022041F (cond_jump)
  0x00220424  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x00220427  0fb612                  movzx    edx, byte ptr [edx]            
  0x0022042A  03c7                    add      eax, edi                       
  0x0022042C  0fb6b9b1000000          movzx    edi, byte ptr [ecx + 0xb1]     
  0x00220433  8d1c70                  lea      ebx, [eax + esi*2]             
  0x00220436  03de                    add      ebx, esi                       
  0x00220438  03df                    add      ebx, edi                       
  0x0022043A  03d3                    add      edx, ebx                       
  0x0022043C  5f                      pop      edi                            
  0x0022043D  03c6                    add      eax, esi                       
  0x0022043F  5e                      pop      esi                            
  0x00220440  8991ac000000            mov      dword ptr [ecx + 0xac], edx    
  0x00220446  8981a4000000            mov      dword ptr [ecx + 0xa4], eax    
  0x0022044C  5b                      pop      ebx                            
  0x0022044D  c9                      leave                                   
  0x0022044E  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022044F
; Start: 0x0022044F  End: 0x00220614  Size: 453 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022414A
; Called by: sub_0021FBF7
; ============================================================
sub_0022044F:
  0x0022044F  55                      push     ebp                            
  0x00220450  8bec                    mov      ebp, esp                       
  0x00220452  83ec0c                  sub      esp, 0xc                       
  0x00220455  53                      push     ebx                            
  0x00220456  8bd9                    mov      ebx, ecx                       
  0x00220458  0fb64b0e                movzx    ecx, byte ptr [ebx + 0xe]      
  0x0022045C  8b4304                  mov      eax, dword ptr [ebx + 4]       
  0x0022045F  c1e106                  shl      ecx, 6                         
  0x00220462  83c130                  add      ecx, 0x30                      
  0x00220465  3903                    cmp      dword ptr [ebx], eax           
  0x00220467  56                      push     esi                            
  0x00220468  894df8                  mov      dword ptr [ebp - 8], ecx       
  0x0022046B  7302                    jae      0x22046f                       
  0x0022046D  8903                    mov      dword ptr [ebx], eax           
                                        ; XREF: 0x0022046B (cond_jump)
  0x0022046F  0fafc1                  imul     eax, ecx                       
  0x00220472  8b4b08                  mov      ecx, dword ptr [ebx + 8]       
  0x00220475  83c108                  add      ecx, 8                         
  0x00220478  c1e105                  shl      ecx, 5                         
  0x0022047B  03c1                    add      eax, ecx                       
  0x0022047D  8b0b                    mov      ecx, dword ptr [ebx]           
  0x0022047F  8d0c49                  lea      ecx, [ecx + ecx*2]             
  0x00220482  c1e104                  shl      ecx, 4                         
  0x00220485  03c1                    add      eax, ecx                       
  0x00220487  8bc8                    mov      ecx, eax                       
  0x00220489  8d81ff0f0000            lea      eax, [ecx + 0xfff]             
  0x0022048F  c1e80c                  shr      eax, 0xc                       
  0x00220492  8bd0                    mov      edx, eax                       
  0x00220494  c1e204                  shl      edx, 4                         
  0x00220497  03d1                    add      edx, ecx                       
  0x00220499  8bc8                    mov      ecx, eax                       
  0x0022049B  c1e10c                  shl      ecx, 0xc                       
  0x0022049E  3bca                    cmp      ecx, edx                       
  0x002204A0  7301                    jae      0x2204a3                       
  0x002204A2  40                      inc      eax                            
                                        ; XREF: 0x002204A0 (cond_jump)
  0x002204A3  57                      push     edi                            
  0x002204A4  c1e00c                  shl      eax, 0xc                       
  0x002204A7  8bf8                    mov      edi, eax                       
  0x002204A9  57                      push     edi                            
  0x002204AA  897dfc                  mov      dword ptr [ebp - 4], edi       
  0x002204AD  ff158c5a2200            call     dword ptr [0x225a8c]           ; -> xbox_MmAllocateContiguousMemory
  0x002204B3  6a00                    push     0                              
  0x002204B5  8bf0                    mov      esi, eax                       
  0x002204B7  57                      push     edi                            
  0x002204B8  56                      push     esi                            
  0x002204B9  ff158c5b2200            call     dword ptr [0x225b8c]           ; -> xbox_MmLockUnlockBufferPages
  0x002204BF  56                      push     esi                            
  0x002204C0  ff15885b2200            call     dword ptr [0x225b88]           ; -> xbox_MmGetPhysicalAddress
  0x002204C6  8bce                    mov      ecx, esi                       
  0x002204C8  2bc8                    sub      ecx, eax                       
  0x002204CA  890d80782800            mov      dword ptr [0x287880], ecx      
  0x002204D0  8bcf                    mov      ecx, edi                       
  0x002204D2  8bd1                    mov      edx, ecx                       
  0x002204D4  c1e902                  shr      ecx, 2                         
  0x002204D7  33c0                    xor      eax, eax                       
  0x002204D9  8bfe                    mov      edi, esi                       
  0x002204DB  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x002204DD  8bca                    mov      ecx, edx                       
  0x002204DF  83e103                  and      ecx, 3                         
  0x002204E2  f3aa                    rep stosb byte ptr es:[edi], al          
  0x002204E4  8bc2                    mov      eax, edx                       
  0x002204E6  33d2                    xor      edx, edx                       
  0x002204E8  893584782800            mov      dword ptr [0x287884], esi      
  0x002204EE  891588782800            mov      dword ptr [0x287888], edx      
  0x002204F4  0fb67b0e                movzx    edi, byte ptr [ebx + 0xe]      
  0x002204F8  8d0c06                  lea      ecx, [esi + eax]               
  0x002204FB  81c600010000            add      esi, 0x100                     
  0x00220501  33c0                    xor      eax, eax                       
  0x00220503  893dac782800            mov      dword ptr [0x2878ac], edi      
  0x00220509  8915a8782800            mov      dword ptr [0x2878a8], edx      
  0x0022050F  395304                  cmp      dword ptr [ebx + 4], edx       
  0x00220512  894df4                  mov      dword ptr [ebp - 0xc], ecx     
  0x00220515  763e                    jbe      0x220555                       
                                        ; XREF: 0x0022053E (cond_jump)
  0x00220517  8b3da8782800            mov      edi, dword ptr [0x2878a8]      
  0x0022051D  893e                    mov      dword ptr [esi], edi           
  0x0022051F  8b3d88782800            mov      edi, dword ptr [0x287888]      
  0x00220525  8935a8782800            mov      dword ptr [0x2878a8], esi      
  0x0022052B  0375f8                  add      esi, dword ptr [ebp - 8]       
  0x0022052E  897e18                  mov      dword ptr [esi + 0x18], edi    
  0x00220531  893588782800            mov      dword ptr [0x287888], esi      
  0x00220537  83c630                  add      esi, 0x30                      
  0x0022053A  40                      inc      eax                            
  0x0022053B  3b4304                  cmp      eax, dword ptr [ebx + 4]       
  0x0022053E  72d7                    jb       0x220517                       
  0x00220540  eb13                    jmp      0x220555                       
                                        ; XREF: 0x00220557 (cond_jump)
  0x00220542  8b3d88782800            mov      edi, dword ptr [0x287888]      
  0x00220548  897e18                  mov      dword ptr [esi + 0x18], edi    
  0x0022054B  893588782800            mov      dword ptr [0x287888], esi      
  0x00220551  83c630                  add      esi, 0x30                      
  0x00220554  40                      inc      eax                            
                                        ; XREF: 0x00220515 (cond_jump), 0x00220540 (jump)
  0x00220555  3b03                    cmp      eax, dword ptr [ebx]           
  0x00220557  72e9                    jb       0x220542                       
  0x00220559  8d7e20                  lea      edi, [esi + 0x20]              
  0x0022055C  3bf9                    cmp      edi, ecx                       
  0x0022055E  8955fc                  mov      dword ptr [ebp - 4], edx       
  0x00220561  89158c782800            mov      dword ptr [0x28788c], edx      
  0x00220567  893590782800            mov      dword ptr [0x287890], esi      
  0x0022056D  7724                    ja       0x220593                       
                                        ; XREF: 0x0022058F (cond_jump)
  0x0022056F  8bc6                    mov      eax, esi                       
  0x00220571  2b0580782800            sub      eax, dword ptr [0x287880]      
  0x00220577  56                      push     esi                            
  0x00220578  8975f8                  mov      dword ptr [ebp - 8], esi       
  0x0022057B  8947f0                  mov      dword ptr [edi - 0x10], eax    
  0x0022057E  e8c73b0000              call     0x22414a                       ; -> sub_0022414A
  0x00220583  83c620                  add      esi, 0x20                      
  0x00220586  83c720                  add      edi, 0x20                      
  0x00220589  ff45fc                  inc      dword ptr [ebp - 4]            
  0x0022058C  3b7df4                  cmp      edi, dword ptr [ebp - 0xc]     
  0x0022058F  76de                    jbe      0x22056f                       
  0x00220591  33d2                    xor      edx, edx                       
                                        ; XREF: 0x0022056D (cond_jump)
  0x00220593  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00220596  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x00220599  a394782800              mov      dword ptr [0x287894], eax      
  0x0022059E  891598782800            mov      dword ptr [0x287898], edx      
  0x002205A4  c7059c782800e8030000    mov      dword ptr [0x28789c], 0x3e8    
  0x002205AE  660fb6430c              movzx    ax, byte ptr [ebx + 0xc]       
  0x002205B3  66a3a0782800            mov      word ptr [0x2878a0], ax        
  0x002205B9  660fb6430d              movzx    ax, byte ptr [ebx + 0xd]       
  0x002205BE  66a3a4782800            mov      word ptr [0x2878a4], ax        
  0x002205C4  3b4b08                  cmp      ecx, dword ptr [ebx + 8]       
  0x002205C7  5f                      pop      edi                            
  0x002205C8  7632                    jbe      0x2205fc                       
  0x002205CA  2a4b08                  sub      cl, byte ptr [ebx + 8]         
  0x002205CD  663bc2                  cmp      ax, dx                         
  0x002205D0  7413                    je       0x2205e5                       
  0x002205D2  8ad1                    mov      dl, cl                         
  0x002205D4  d0ea                    shr      dl, 1                          
  0x002205D6  660fb6f2                movzx    si, dl                         
  0x002205DA  6603c6                  add      ax, si                         
  0x002205DD  66a3a4782800            mov      word ptr [0x2878a4], ax        
  0x002205E3  2aca                    sub      cl, dl                         
                                        ; XREF: 0x002205D0 (cond_jump)
  0x002205E5  660fb6c1                movzx    ax, cl                         
  0x002205E9  660105a0782800          add      word ptr [0x2878a0], ax        
  0x002205F0  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x002205F3  894308                  mov      dword ptr [ebx + 8], eax       
  0x002205F6  66a1a4782800            mov      ax, word ptr [0x2878a4]        
                                        ; XREF: 0x002205C8 (cond_jump)
  0x002205FC  668b0da0782800          mov      cx, word ptr [0x2878a0]        
  0x00220603  5e                      pop      esi                            
  0x00220604  66890da2782800          mov      word ptr [0x2878a2], cx        
  0x0022060B  66a3a6782800            mov      word ptr [0x2878a6], ax        
  0x00220611  5b                      pop      ebx                            
  0x00220612  c9                      leave                                   
  0x00220613  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220614
; Start: 0x00220614  End: 0x00220675  Size: 97 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002231B8
; Called by: sub_0021FC45
; ============================================================
sub_00220614:
  0x00220614  56                      push     esi                            
  0x00220615  8bf1                    mov      esi, ecx                       
  0x00220617  8b4608                  mov      eax, dword ptr [esi + 8]       
  0x0022061A  2b0580782800            sub      eax, dword ptr [0x287880]      
  0x00220620  8b0e                    mov      ecx, dword ptr [esi]           
  0x00220622  894118                  mov      dword ptr [ecx + 0x18], eax    
  0x00220625  8b0e                    mov      ecx, dword ptr [esi]           
  0x00220627  33c0                    xor      eax, eax                       
  0x00220629  89411c                  mov      dword ptr [ecx + 0x1c], eax    
  0x0022062C  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022062E  894120                  mov      dword ptr [ecx + 0x20], eax    
  0x00220631  8b0e                    mov      ecx, dword ptr [esi]           
  0x00220633  894124                  mov      dword ptr [ecx + 0x24], eax    
  0x00220636  8b0e                    mov      ecx, dword ptr [esi]           
  0x00220638  894128                  mov      dword ptr [ecx + 0x28], eax    
  0x0022063B  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022063D  89412c                  mov      dword ptr [ecx + 0x2c], eax    
  0x00220640  8b0e                    mov      ecx, dword ptr [esi]           
  0x00220642  894130                  mov      dword ptr [ecx + 0x30], eax    
  0x00220645  6a01                    push     1                              
  0x00220647  66c786160400007227      mov      word ptr [esi + 0x416], 0x2772 
  0x00220650  8b06                    mov      eax, dword ptr [esi]           
  0x00220652  6a03                    push     3                              
  0x00220654  c74040292a0000          mov      dword ptr [eax + 0x40], 0x2a29 
  0x0022065B  6a08                    push     8                              
  0x0022065D  66c786140400006f23      mov      word ptr [esi + 0x414], 0x236f 
  0x00220666  e84d2b0000              call     0x2231b8                       ; -> sub_002231B8
  0x0022066B  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022066D  0fb7c0                  movzx    eax, ax                        
  0x00220670  894144                  mov      dword ptr [ecx + 0x44], eax    
  0x00220673  5e                      pop      esi                            
  0x00220674  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220675
; Start: 0x00220675  End: 0x00220680  Size: 11 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FC45
; ============================================================
sub_00220675:
  0x00220675  8b442404                mov      eax, dword ptr [esp + 4]       
  0x00220679  8b00                    mov      eax, dword ptr [eax]           
  0x0022067B  8b00                    mov      eax, dword ptr [eax]           
  0x0022067D  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00220680
; Start: 0x00220680  End: 0x002206E2  Size: 98 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_0021FC45
; ============================================================
sub_00220680:
  0x00220680  55                      push     ebp                            
  0x00220681  8bec                    mov      ebp, esp                       
  0x00220683  51                      push     ecx                            
  0x00220684  51                      push     ecx                            
  0x00220685  8b5508                  mov      edx, dword ptr [ebp + 8]       
  0x00220688  8b02                    mov      eax, dword ptr [edx]           
  0x0022068A  8b4804                  mov      ecx, dword ptr [eax + 4]       
  0x0022068D  56                      push     esi                            
  0x0022068E  be00010000              mov      esi, 0x100                     
  0x00220693  85ce                    test     esi, ecx                       
  0x00220695  7412                    je       0x2206a9                       
  0x00220697  8b4808                  mov      ecx, dword ptr [eax + 8]       
  0x0022069A  83c908                  or       ecx, 8                         
  0x0022069D  894808                  mov      dword ptr [eax + 8], ecx       
  0x002206A0  8b12                    mov      edx, dword ptr [edx]           
                                        ; XREF: 0x002206A5 (cond_jump)
  0x002206A2  857204                  test     dword ptr [edx + 4], esi       
  0x002206A5  75fb                    jne      0x2206a2                       
  0x002206A7  eb34                    jmp      0x2206dd                       
                                        ; XREF: 0x00220695 (cond_jump)
  0x002206A9  8bd1                    mov      edx, ecx                       
  0x002206AB  c1ea06                  shr      edx, 6                         
  0x002206AE  83e203                  and      edx, 3                         
  0x002206B1  742a                    je       0x2206dd                       
  0x002206B3  83fa02                  cmp      edx, 2                         
  0x002206B6  7425                    je       0x2206dd                       
  0x002206B8  81e17fffffff            and      ecx, 0xffffff7f                
  0x002206BE  83c940                  or       ecx, 0x40                      
  0x002206C1  894804                  mov      dword ptr [eax + 4], ecx       
  0x002206C4  834dfcff                or       dword ptr [ebp - 4], 0xffffffff 
  0x002206C8  8d45f8                  lea      eax, [ebp - 8]                 
  0x002206CB  50                      push     eax                            
  0x002206CC  6a00                    push     0                              
  0x002206CE  6a00                    push     0                              
  0x002206D0  c745f8c0f2fcff          mov      dword ptr [ebp - 8], 0xfffcf2c0 
  0x002206D7  ff15fc5a2200            call     dword ptr [0x225afc]           ; -> xbox_KeDelayExecutionThread
                                        ; XREF: 0x002206A7 (jump), 0x002206B1 (cond_jump), 0x002206B6 (cond_jump)
  0x002206DD  5e                      pop      esi                            
  0x002206DE  c9                      leave                                   
  0x002206DF  c20400                  ret      4                              
; end of function
                                        ; XREF: 0x0021FA70 (data_imm)
  0x002206E2  8bc1                    mov      eax, ecx                       
  0x002206E4  c600ff                  mov      byte ptr [eax], 0xff           
  0x002206E7  c6400180                mov      byte ptr [eax + 1], 0x80       
  0x002206EB  c6400280                mov      byte ptr [eax + 2], 0x80       
  0x002206EF  c6400380                mov      byte ptr [eax + 3], 0x80       
  0x002206F3  c3                      ret                                     

; ============================================================
; Function: sub_002206F4
; Start: 0x002206F4  End: 0x00220744  Size: 80 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FE39, sub_002207BB, sub_0022109C
; ============================================================
sub_002206F4:
  0x002206F4  0fb65179                movzx    edx, byte ptr [ecx + 0x79]     
  0x002206F8  8b81e0000000            mov      eax, dword ptr [ecx + 0xe0]    
  0x002206FE  c1e205                  shl      edx, 5                         
  0x00220701  56                      push     esi                            
  0x00220702  8d741001                lea      esi, [eax + edx + 1]           
  0x00220706  8a06                    mov      al, byte ptr [esi]             
  0x00220708  884179                  mov      byte ptr [ecx + 0x79], al      
  0x0022070B  c60680                  mov      byte ptr [esi], 0x80           
  0x0022070E  8b81e0000000            mov      eax, dword ptr [ecx + 0xe0]    
  0x00220714  c644100280              mov      byte ptr [eax + edx + 2], 0x80 
  0x00220719  8b81e0000000            mov      eax, dword ptr [ecx + 0xe0]    
  0x0022071F  c644100380              mov      byte ptr [eax + edx + 3], 0x80 
  0x00220724  8b81e0000000            mov      eax, dword ptr [ecx + 0xe0]    
  0x0022072A  8364101c00              and      dword ptr [eax + edx + 0x1c], 0 
  0x0022072F  8b81e0000000            mov      eax, dword ptr [ecx + 0xe0]    
  0x00220735  c6441007ff              mov      byte ptr [eax + edx + 7], 0xff 
  0x0022073A  8b81e0000000            mov      eax, dword ptr [ecx + 0xe0]    
  0x00220740  03c2                    add      eax, edx                       
  0x00220742  5e                      pop      esi                            
  0x00220743  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220744
; Start: 0x00220744  End: 0x00220776  Size: 50 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00220A35, sub_00220BAC, sub_00220C68, sub_00220E01
; ============================================================
sub_00220744:
  0x00220744  8b442404                mov      eax, dword ptr [esp + 4]       
  0x00220748  53                      push     ebx                            
  0x00220749  56                      push     esi                            
  0x0022074A  8bf1                    mov      esi, ecx                       
  0x0022074C  8b8ee0000000            mov      ecx, dword ptr [esi + 0xe0]    
  0x00220752  2bc1                    sub      eax, ecx                       
  0x00220754  c1f805                  sar      eax, 5                         
  0x00220757  0fb6d0                  movzx    edx, al                        
  0x0022075A  c1e205                  shl      edx, 5                         
  0x0022075D  c6040aff                mov      byte ptr [edx + ecx], 0xff     
  0x00220761  8a5e79                  mov      bl, byte ptr [esi + 0x79]      
  0x00220764  8b8ee0000000            mov      ecx, dword ptr [esi + 0xe0]    
  0x0022076A  885c0a01                mov      byte ptr [edx + ecx + 1], bl   
  0x0022076E  884679                  mov      byte ptr [esi + 0x79], al      
  0x00220771  5e                      pop      esi                            
  0x00220772  5b                      pop      ebx                            
  0x00220773  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00220776
; Start: 0x00220776  End: 0x0022078D  Size: 23 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_002209CE, sub_00220A35, sub_00220C23, sub_00220C68, sub_00220D2F, sub_00220E01, sub_002218E3, sub_00221969, sub_00221C4B
; ============================================================
sub_00220776:
  0x00220776  8a4101                  mov      al, byte ptr [ecx + 1]         
  0x00220779  3c80                    cmp      al, 0x80                       
  0x0022077B  740d                    je       0x22078a                       
  0x0022077D  0fb6c0                  movzx    eax, al                        
  0x00220780  c1e005                  shl      eax, 5                         
  0x00220783  0305606c2800            add      eax, dword ptr [0x286c60]      
  0x00220789  c3                      ret                                     
                                        ; XREF: 0x0022077B (cond_jump)
  0x0022078A  33c0                    xor      eax, eax                       
  0x0022078C  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022078D
; Start: 0x0022078D  End: 0x002207A4  Size: 23 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00220AAB, sub_00220E01, sub_0022109C, sub_00221969, sub_002219D5, sub_00221A06, sub_00221A4E
; ============================================================
sub_0022078D:
  0x0022078D  8a4102                  mov      al, byte ptr [ecx + 2]         
  0x00220790  3c80                    cmp      al, 0x80                       
  0x00220792  740d                    je       0x2207a1                       
  0x00220794  0fb6c0                  movzx    eax, al                        
  0x00220797  c1e005                  shl      eax, 5                         
  0x0022079A  0305606c2800            add      eax, dword ptr [0x286c60]      
  0x002207A0  c3                      ret                                     
                                        ; XREF: 0x00220792 (cond_jump)
  0x002207A1  33c0                    xor      eax, eax                       
  0x002207A3  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002207A4
; Start: 0x002207A4  End: 0x002207BB  Size: 23 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00220AAB, sub_00220E01, sub_00221969, sub_002219D5, sub_00221A06, sub_00221A4E
; ============================================================
sub_002207A4:
  0x002207A4  8a4103                  mov      al, byte ptr [ecx + 3]         
  0x002207A7  3c80                    cmp      al, 0x80                       
  0x002207A9  740d                    je       0x2207b8                       
  0x002207AB  0fb6c0                  movzx    eax, al                        
  0x002207AE  c1e005                  shl      eax, 5                         
  0x002207B1  0305606c2800            add      eax, dword ptr [0x286c60]      
  0x002207B7  c3                      ret                                     
                                        ; XREF: 0x002207A9 (cond_jump)
  0x002207B8  33c0                    xor      eax, eax                       
  0x002207BA  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002207BB
; Start: 0x002207BB  End: 0x0022087F  Size: 196 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002206F4, sub_00221A06
; Called by: sub_002209B9, sub_00220C23, sub_00220C68
; ============================================================
sub_002207BB:
  0x002207BB  53                      push     ebx                            
  0x002207BC  56                      push     esi                            
  0x002207BD  57                      push     edi                            
  0x002207BE  8bf9                    mov      edi, ecx                       
  0x002207C0  b9806b2800              mov      ecx, 0x286b80                  
  0x002207C5  e82affffff              call     0x2206f4                       ; -> sub_002206F4
  0x002207CA  8bf0                    mov      esi, eax                       
  0x002207CC  33db                    xor      ebx, ebx                       
  0x002207CE  3bf3                    cmp      esi, ebx                       
  0x002207D0  0f84a3000000            je       0x220879                       
  0x002207D6  8a442410                mov      al, byte ptr [esp + 0x10]      
  0x002207DA  c606fe                  mov      byte ptr [esi], 0xfe           
  0x002207DD  884604                  mov      byte ptr [esi + 4], al         
  0x002207E0  895e10                  mov      dword ptr [esi + 0x10], ebx    
  0x002207E3  8b470c                  mov      eax, dword ptr [edi + 0xc]     
  0x002207E6  56                      push     esi                            
  0x002207E7  8bcf                    mov      ecx, edi                       
  0x002207E9  89460c                  mov      dword ptr [esi + 0xc], eax     
  0x002207EC  e815120000              call     0x221a06                       ; -> sub_00221A06
  0x002207F1  381d806b2800            cmp      byte ptr [0x286b80], bl        
  0x002207F7  8a442414                mov      al, byte ptr [esp + 0x14]      
  0x002207FB  7437                    je       0x220834                       
  0x002207FD  8d7e18                  lea      edi, [esi + 0x18]              
  0x00220800  57                      push     edi                            
  0x00220801  884605                  mov      byte ptr [esi + 5], al         
  0x00220804  ff15a05a2200            call     dword ptr [0x225aa0]           ; -> xbox_KeQuerySystemTime
  0x0022080A  810740420f00            add      dword ptr [edi], 0xf4240       
  0x00220810  895e10                  mov      dword ptr [esi + 0x10], ebx    
  0x00220813  115f04                  adc      dword ptr [edi + 4], ebx       
  0x00220816  a1fc6b2800              mov      eax, dword ptr [0x286bfc]      
  0x0022081B  3bc3                    cmp      eax, ebx                       
  0x0022081D  750b                    jne      0x22082a                       
  0x0022081F  8935fc6b2800            mov      dword ptr [0x286bfc], esi      
  0x00220825  eb52                    jmp      0x220879                       
                                        ; XREF: 0x0022082D (cond_jump)
  0x00220827  8b4010                  mov      eax, dword ptr [eax + 0x10]    
                                        ; XREF: 0x0022081D (cond_jump)
  0x0022082A  395810                  cmp      dword ptr [eax + 0x10], ebx    
  0x0022082D  75f8                    jne      0x220827                       
  0x0022082F  897010                  mov      dword ptr [eax + 0x10], esi    
  0x00220832  eb45                    jmp      0x220879                       
                                        ; XREF: 0x002207FB (cond_jump)
  0x00220834  c606fd                  mov      byte ptr [esi], 0xfd           
  0x00220837  68b46b2800              push     0x286bb4                       
  0x0022083C  a2826b2800              mov      byte ptr [0x286b82], al        
  0x00220841  83c9ff                  or       ecx, 0xffffffff                
  0x00220844  51                      push     ecx                            
  0x00220845  b8c0bdf0ff              mov      eax, 0xfff0bdc0                
  0x0022084A  50                      push     eax                            
  0x0022084B  c605806b280001          mov      byte ptr [0x286b80], 1         
  0x00220852  881d816b2800            mov      byte ptr [0x286b81], bl        
  0x00220858  8935006c2800            mov      dword ptr [0x286c00], esi      
  0x0022085E  c605836b280080          mov      byte ptr [0x286b83], 0x80      
  0x00220865  885e05                  mov      byte ptr [esi + 5], bl         
  0x00220868  68d06b2800              push     0x286bd0                       
  0x0022086D  881df86b2800            mov      byte ptr [0x286bf8], bl        
  0x00220873  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
                                        ; XREF: 0x002207D0 (cond_jump), 0x00220825 (jump), 0x00220832 (jump)
  0x00220879  5f                      pop      edi                            
  0x0022087A  5e                      pop      esi                            
  0x0022087B  5b                      pop      ebx                            
  0x0022087C  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_0022087F
; Start: 0x0022087F  End: 0x002208A1  Size: 34 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_002211E3, sub_002212E3, sub_0022139C
; ============================================================
sub_0022087F:
  0x0022087F  68b46b2800              push     0x286bb4                       
  0x00220884  83c9ff                  or       ecx, 0xffffffff                
  0x00220887  51                      push     ecx                            
  0x00220888  b8800f05fd              mov      eax, 0xfd050f80                
  0x0022088D  50                      push     eax                            
  0x0022088E  68d06b2800              push     0x286bd0                       
  0x00220893  c605f86b280001          mov      byte ptr [0x286bf8], 1         
  0x0022089A  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
  0x002208A0  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002208A1
; Start: 0x002208A1  End: 0x002208F2  Size: 81 bytes
; Detection: tail_jump_target (confidence: 0.88)
; Calls: sub_00220D2F
; ============================================================
sub_002208A1:
  0x002208A1  837c240400              cmp      dword ptr [esp + 4], 0         
  0x002208A6  c605836b280081          mov      byte ptr [0x286b83], 0x81      
  0x002208AD  7d0d                    jge      0x2208bc                       
  0x002208AF  ff742408                push     dword ptr [esp + 8]            
  0x002208B3  6a00                    push     0                              
  0x002208B5  e875040000              call     0x220d2f                       ; -> sub_00220D2F
  0x002208BA  eb33                    jmp      0x2208ef                       
                                        ; XREF: 0x002208AD (cond_jump)
  0x002208BC  817c240400000001        cmp      dword ptr [esp + 4], 0x1000000 
  0x002208C4  7508                    jne      0x2208ce                       
  0x002208C6  8b442408                mov      eax, dword ptr [esp + 8]       
  0x002208CA  80480480                or       byte ptr [eax + 4], 0x80       
                                        ; XREF: 0x002208C4 (cond_jump)
  0x002208CE  68b46b2800              push     0x286bb4                       
  0x002208D3  83c9ff                  or       ecx, 0xffffffff                
  0x002208D6  51                      push     ecx                            
  0x002208D7  b86079feff              mov      eax, 0xfffe7960                
  0x002208DC  50                      push     eax                            
  0x002208DD  68d06b2800              push     0x286bd0                       
  0x002208E2  c605f86b280002          mov      byte ptr [0x286bf8], 2         
  0x002208E9  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
                                        ; XREF: 0x002208BA (jump)
  0x002208EF  c20800                  ret      8                              
; end of function
                                        ; XREF: 0x00220DBF (data_imm)
  0x002208F2  68b46b2800              push     0x286bb4                       
  0x002208F7  83c9ff                  or       ecx, 0xffffffff                
  0x002208FA  51                      push     ecx                            
  0x002208FB  b8e0b1ffff              mov      eax, 0xffffb1e0                
  0x00220900  50                      push     eax                            
  0x00220901  68d06b2800              push     0x286bd0                       
  0x00220906  c605836b280084          mov      byte ptr [0x286b83], 0x84      
  0x0022090D  c605f86b280003          mov      byte ptr [0x286bf8], 3         
  0x00220914  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
  0x0022091A  c20800                  ret      8                              

; ============================================================
; Function: sub_0022091D
; Start: 0x0022091D  End: 0x0022094E  Size: 49 bytes
; Detection: call_target (confidence: 0.90)
; ============================================================
sub_0022091D:
  0x0022091D  53                      push     ebx                            
  0x0022091E  33d2                    xor      edx, edx                       
  0x00220920  32db                    xor      bl, bl                         
  0x00220922  42                      inc      edx                            
  0x00220923  56                      push     esi                            
  0x00220924  8ac2                    mov      al, dl                         
                                        ; XREF: 0x0022093C (cond_jump)
  0x00220926  0fb6f3                  movzx    esi, bl                        
  0x00220929  8554b108                test     dword ptr [ecx + esi*4 + 8], edx 
  0x0022092D  7411                    je       0x220940                       
  0x0022092F  d1e2                    shl      edx, 1                         
  0x00220931  7505                    jne      0x220938                       
  0x00220933  33d2                    xor      edx, edx                       
  0x00220935  fec3                    inc      bl                             
  0x00220937  42                      inc      edx                            
                                        ; XREF: 0x00220931 (cond_jump)
  0x00220938  fec0                    inc      al                             
  0x0022093A  3c80                    cmp      al, 0x80                       
  0x0022093C  72e8                    jb       0x220926                       
  0x0022093E  eb09                    jmp      0x220949                       
                                        ; XREF: 0x0022092D (cond_jump)
  0x00220940  0fb6f3                  movzx    esi, bl                        
  0x00220943  8d4cb108                lea      ecx, [ecx + esi*4 + 8]         
  0x00220947  0911                    or       dword ptr [ecx], edx           
                                        ; XREF: 0x0022093E (jump)
  0x00220949  5e                      pop      esi                            
  0x0022094A  247f                    and      al, 0x7f                       
  0x0022094C  5b                      pop      ebx                            
  0x0022094D  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022094E
; Start: 0x0022094E  End: 0x00220982  Size: 52 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00220A35, sub_00220C68
; ============================================================
sub_0022094E:
  0x0022094E  53                      push     ebx                            
  0x0022094F  32db                    xor      bl, bl                         
  0x00220951  feca                    dec      dl                             
  0x00220953  80fa1f                  cmp      dl, 0x1f                       
  0x00220956  56                      push     esi                            
  0x00220957  7614                    jbe      0x22096d                       
  0x00220959  8ac2                    mov      al, dl                         
  0x0022095B  2c20                    sub      al, 0x20                       
  0x0022095D  c0e805                  shr      al, 5                          
  0x00220960  fec0                    inc      al                             
  0x00220962  0fb6c0                  movzx    eax, al                        
  0x00220965  8ad8                    mov      bl, al                         
                                        ; XREF: 0x0022096B (cond_jump)
  0x00220967  80c2e0                  add      dl, 0xe0                       
  0x0022096A  48                      dec      eax                            
  0x0022096B  75fa                    jne      0x220967                       
                                        ; XREF: 0x00220957 (cond_jump)
  0x0022096D  0fb6c3                  movzx    eax, bl                        
  0x00220970  33f6                    xor      esi, esi                       
  0x00220972  8d448108                lea      eax, [ecx + eax*4 + 8]         
  0x00220976  46                      inc      esi                            
  0x00220977  8aca                    mov      cl, dl                         
  0x00220979  d3e6                    shl      esi, cl                        
  0x0022097B  f7d6                    not      esi                            
  0x0022097D  2130                    and      dword ptr [eax], esi           
  0x0022097F  5e                      pop      esi                            
  0x00220980  5b                      pop      ebx                            
  0x00220981  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220982
; Start: 0x00220982  End: 0x00220989  Size: 7 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00221D43
; ============================================================
sub_00220982:
  0x00220982  ff05646c2800            inc      dword ptr [0x286c64]           
  0x00220988  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220989
; Start: 0x00220989  End: 0x00220990  Size: 7 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00221D43
; ============================================================
sub_00220989:
  0x00220989  ff0d646c2800            dec      dword ptr [0x286c64]           
  0x0022098F  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220990
; Start: 0x00220990  End: 0x002209B9  Size: 41 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_000F8580
; ============================================================
sub_00220990:
  0x00220990  56                      push     esi                            
  0x00220991  33f6                    xor      esi, esi                       
  0x00220993  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00220999  3935646c2800            cmp      dword ptr [0x286c64], esi      
  0x0022099F  7509                    jne      0x2209aa                       
  0x002209A1  803d806b280000          cmp      byte ptr [0x286b80], 0         
  0x002209A8  7403                    je       0x2209ad                       
                                        ; XREF: 0x0022099F (cond_jump)
  0x002209AA  33f6                    xor      esi, esi                       
  0x002209AC  46                      inc      esi                            
                                        ; XREF: 0x002209A8 (cond_jump)
  0x002209AD  8ac8                    mov      cl, al                         
  0x002209AF  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x002209B5  8bc6                    mov      eax, esi                       
  0x002209B7  5e                      pop      esi                            
  0x002209B8  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002209B9
; Start: 0x002209B9  End: 0x002209CE  Size: 21 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002207BB
; Called by: sub_00222979
; ============================================================
sub_002209B9:
  0x002209B9  8b442404                mov      eax, dword ptr [esp + 4]       
  0x002209BD  8b48ec                  mov      ecx, dword ptr [eax - 0x14]    
  0x002209C0  6a05                    push     5                              
  0x002209C2  ff74240c                push     dword ptr [esp + 0xc]          
  0x002209C6  e8f0fdffff              call     0x2207bb                       ; -> sub_002207BB
  0x002209CB  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_002209CE
; Start: 0x002209CE  End: 0x00220A30  Size: 98 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220776, sub_00220D2F, sub_00221FFE, sub_00222A08
; Called by: sub_00220AFD
; ============================================================
sub_002209CE:
  0x002209CE  53                      push     ebx                            
  0x002209CF  56                      push     esi                            
  0x002209D0  8b35006c2800            mov      esi, dword ptr [0x286c00]      
  0x002209D6  57                      push     edi                            
  0x002209D7  8b7e0c                  mov      edi, dword ptr [esi + 0xc]     
  0x002209DA  33db                    xor      ebx, ebx                       
  0x002209DC  83c718                  add      edi, 0x18                      
  0x002209DF  381d816b2800            cmp      byte ptr [0x286b81], bl        
  0x002209E5  7409                    je       0x2209f0                       
  0x002209E7  56                      push     esi                            
  0x002209E8  53                      push     ebx                            
  0x002209E9  e841030000              call     0x220d2f                       ; -> sub_00220D2F
  0x002209EE  eb3c                    jmp      0x220a2c                       
                                        ; XREF: 0x002209E5 (cond_jump)
  0x002209F0  8bce                    mov      ecx, esi                       
  0x002209F2  881d836b2800            mov      byte ptr [0x286b83], bl        
  0x002209F8  e879fdffff              call     0x220776                       ; -> sub_00220776
  0x002209FD  3818                    cmp      byte ptr [eax], bl             
  0x002209FF  7517                    jne      0x220a18                       
  0x00220A01  33c0                    xor      eax, eax                       
  0x00220A03  8a4604                  mov      al, byte ptr [esi + 4]         
  0x00220A06  56                      push     esi                            
  0x00220A07  68a1082200              push     0x2208a1                       
  0x00220A0C  83e07f                  and      eax, 0x7f                      
  0x00220A0F  50                      push     eax                            
  0x00220A10  57                      push     edi                            
  0x00220A11  e8f21f0000              call     0x222a08                       ; -> sub_00222A08
  0x00220A16  eb14                    jmp      0x220a2c                       
                                        ; XREF: 0x002209FF (cond_jump)
  0x00220A18  33c9                    xor      ecx, ecx                       
  0x00220A1A  8a4e04                  mov      cl, byte ptr [esi + 4]         
  0x00220A1D  53                      push     ebx                            
  0x00220A1E  56                      push     esi                            
  0x00220A1F  81e17fffffff            and      ecx, 0xffffff7f                
  0x00220A25  51                      push     ecx                            
  0x00220A26  50                      push     eax                            
  0x00220A27  e8d2150000              call     0x221ffe                       ; -> sub_00221FFE
                                        ; XREF: 0x002209EE (jump), 0x00220A16 (jump)
  0x00220A2C  5f                      pop      edi                            
  0x00220A2D  5e                      pop      esi                            
  0x00220A2E  5b                      pop      ebx                            
  0x00220A2F  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220A30
; Start: 0x00220A30  End: 0x00220A35  Size: 5 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00221E4D, sub_00221FFE
; ============================================================
sub_00220A30:
  0x00220A30  e96cfeffff              jmp      0x2208a1                       ; -> sub_002208A1
; end of function

; ============================================================
; Function: sub_00220A35
; Start: 0x00220A35  End: 0x00220AAB  Size: 118 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220744, sub_00220776, sub_0022094E, sub_0022153B, sub_00221A4E
; Called by: sub_00220AAB, sub_00223262
; ============================================================
sub_00220A35:
  0x00220A35  53                      push     ebx                            
  0x00220A36  56                      push     esi                            
  0x00220A37  8bf1                    mov      esi, ecx                       
  0x00220A39  8a4607                  mov      al, byte ptr [esi + 7]         
  0x00220A3C  3cff                    cmp      al, 0xff                       
  0x00220A3E  57                      push     edi                            
  0x00220A3F  741b                    je       0x220a5c                       
  0x00220A41  8b4e10                  mov      ecx, dword ptr [esi + 0x10]    
  0x00220A44  8b4914                  mov      ecx, dword ptr [ecx + 0x14]    
  0x00220A47  0fb6c0                  movzx    eax, al                        
  0x00220A4A  8b0481                  mov      eax, dword ptr [ecx + eax*4]   
  0x00220A4D  85c0                    test     eax, eax                       
  0x00220A4F  740b                    je       0x220a5c                       
  0x00220A51  6a00                    push     0                              
  0x00220A53  ff7614                  push     dword ptr [esi + 0x14]         
  0x00220A56  50                      push     eax                            
  0x00220A57  e8df0a0000              call     0x22153b                       ; -> sub_0022153B
                                        ; XREF: 0x00220A3F (cond_jump), 0x00220A4F (cond_jump)
  0x00220A5C  803e05                  cmp      byte ptr [esi], 5              
  0x00220A5F  bb806b2800              mov      ebx, 0x286b80                  
  0x00220A64  752a                    jne      0x220a90                       
  0x00220A66  8bce                    mov      ecx, esi                       
  0x00220A68  e809fdffff              call     0x220776                       ; -> sub_00220776
  0x00220A6D  8bf8                    mov      edi, eax                       
  0x00220A6F  56                      push     esi                            
  0x00220A70  8bcf                    mov      ecx, edi                       
  0x00220A72  e8d70f0000              call     0x221a4e                       ; -> sub_00221A4E
  0x00220A77  84c0                    test     al, al                         
  0x00220A79  7524                    jne      0x220a9f                       
  0x00220A7B  8a5705                  mov      dl, byte ptr [edi + 5]         
  0x00220A7E  8b4f0c                  mov      ecx, dword ptr [edi + 0xc]     
  0x00220A81  e8c8feffff              call     0x22094e                       ; -> sub_0022094E
  0x00220A86  57                      push     edi                            
  0x00220A87  8bcb                    mov      ecx, ebx                       
  0x00220A89  e8b6fcffff              call     0x220744                       ; -> sub_00220744
  0x00220A8E  eb0f                    jmp      0x220a9f                       
                                        ; XREF: 0x00220A64 (cond_jump)
  0x00220A90  8a5605                  mov      dl, byte ptr [esi + 5]         
  0x00220A93  84d2                    test     dl, dl                         
  0x00220A95  7408                    je       0x220a9f                       
  0x00220A97  8b4e0c                  mov      ecx, dword ptr [esi + 0xc]     
  0x00220A9A  e8affeffff              call     0x22094e                       ; -> sub_0022094E
                                        ; XREF: 0x00220A79 (cond_jump), 0x00220A8E (jump), 0x00220A95 (cond_jump)
  0x00220A9F  56                      push     esi                            
  0x00220AA0  8bcb                    mov      ecx, ebx                       
  0x00220AA2  e89dfcffff              call     0x220744                       ; -> sub_00220744
  0x00220AA7  5f                      pop      edi                            
  0x00220AA8  5e                      pop      esi                            
  0x00220AA9  5b                      pop      ebx                            
  0x00220AAA  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220AAB
; Start: 0x00220AAB  End: 0x00220AFD  Size: 82 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022078D, sub_002207A4, sub_00220A35
; Called by: sub_00220AFD, sub_00220BAC
; ============================================================
sub_00220AAB:
  0x00220AAB  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00220AAF  803904                  cmp      byte ptr [ecx], 4              
  0x00220AB2  56                      push     esi                            
  0x00220AB3  7532                    jne      0x220ae7                       
  0x00220AB5  e8d3fcffff              call     0x22078d                       ; -> sub_0022078D
  0x00220ABA  8bf0                    mov      esi, eax                       
  0x00220ABC  85f6                    test     esi, esi                       
  0x00220ABE  7439                    je       0x220af9                       
  0x00220AC0  57                      push     edi                            
                                        ; XREF: 0x00220AE2 (cond_jump)
  0x00220AC1  8bce                    mov      ecx, esi                       
  0x00220AC3  e8dcfcffff              call     0x2207a4                       ; -> sub_002207A4
  0x00220AC8  8bf8                    mov      edi, eax                       
  0x00220ACA  8b4610                  mov      eax, dword ptr [esi + 0x10]    
  0x00220ACD  85c0                    test     eax, eax                       
  0x00220ACF  7406                    je       0x220ad7                       
  0x00220AD1  56                      push     esi                            
  0x00220AD2  ff500c                  call     dword ptr [eax + 0xc]          
  0x00220AD5  eb07                    jmp      0x220ade                       
                                        ; XREF: 0x00220ACF (cond_jump)
  0x00220AD7  8bce                    mov      ecx, esi                       
  0x00220AD9  e857ffffff              call     0x220a35                       ; -> sub_00220A35
                                        ; XREF: 0x00220AD5 (jump)
  0x00220ADE  85ff                    test     edi, edi                       
  0x00220AE0  8bf7                    mov      esi, edi                       
  0x00220AE2  75dd                    jne      0x220ac1                       
  0x00220AE4  5f                      pop      edi                            
  0x00220AE5  eb12                    jmp      0x220af9                       
                                        ; XREF: 0x00220AB3 (cond_jump)
  0x00220AE7  8b4110                  mov      eax, dword ptr [ecx + 0x10]    
  0x00220AEA  85c0                    test     eax, eax                       
  0x00220AEC  7406                    je       0x220af4                       
  0x00220AEE  51                      push     ecx                            
  0x00220AEF  ff500c                  call     dword ptr [eax + 0xc]          
  0x00220AF2  eb05                    jmp      0x220af9                       
                                        ; XREF: 0x00220AEC (cond_jump)
  0x00220AF4  e83cffffff              call     0x220a35                       ; -> sub_00220A35
                                        ; XREF: 0x00220ABE (cond_jump), 0x00220AE5 (jump), 0x00220AF2 (jump)
  0x00220AF9  5e                      pop      esi                            
  0x00220AFA  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00220AFD
; Start: 0x00220AFD  End: 0x00220BAC  Size: 175 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002209CE, sub_00220AAB
; Called by: sub_00220C68, sub_00220E01
; ============================================================
sub_00220AFD:
  0x00220AFD  55                      push     ebp                            
  0x00220AFE  8bec                    mov      ebp, esp                       
  0x00220B00  51                      push     ecx                            
  0x00220B01  51                      push     ecx                            
  0x00220B02  53                      push     ebx                            
  0x00220B03  33db                    xor      ebx, ebx                       
  0x00220B05  381d816b2800            cmp      byte ptr [0x286b81], bl        
  0x00220B0B  7408                    je       0x220b15                       
  0x00220B0D  ff750c                  push     dword ptr [ebp + 0xc]          
  0x00220B10  e896ffffff              call     0x220aab                       ; -> sub_00220AAB
                                        ; XREF: 0x00220B0B (cond_jump)
  0x00220B15  a1fc6b2800              mov      eax, dword ptr [0x286bfc]      
  0x00220B1A  3bc3                    cmp      eax, ebx                       
  0x00220B1C  881d816b2800            mov      byte ptr [0x286b81], bl        
  0x00220B22  750e                    jne      0x220b32                       
  0x00220B24  891d006c2800            mov      dword ptr [0x286c00], ebx      
  0x00220B2A  881d806b2800            mov      byte ptr [0x286b80], bl        
  0x00220B30  eb75                    jmp      0x220ba7                       
                                        ; XREF: 0x00220B22 (cond_jump)
  0x00220B32  a3006c2800              mov      dword ptr [0x286c00], eax      
  0x00220B37  8b4810                  mov      ecx, dword ptr [eax + 0x10]    
  0x00220B3A  890dfc6b2800            mov      dword ptr [0x286bfc], ecx      
  0x00220B40  8a4805                  mov      cl, byte ptr [eax + 5]         
  0x00220B43  880d826b2800            mov      byte ptr [0x286b82], cl        
  0x00220B49  c605836b280080          mov      byte ptr [0x286b83], 0x80      
  0x00220B50  c600fd                  mov      byte ptr [eax], 0xfd           
  0x00220B53  a1006c2800              mov      eax, dword ptr [0x286c00]      
  0x00220B58  895810                  mov      dword ptr [eax + 0x10], ebx    
  0x00220B5B  a1006c2800              mov      eax, dword ptr [0x286c00]      
  0x00220B60  885805                  mov      byte ptr [eax + 5], bl         
  0x00220B63  8d45f8                  lea      eax, [ebp - 8]                 
  0x00220B66  50                      push     eax                            
  0x00220B67  ff15a05a2200            call     dword ptr [0x225aa0]           ; -> xbox_KeQuerySystemTime
  0x00220B6D  a1006c2800              mov      eax, dword ptr [0x286c00]      
  0x00220B72  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x00220B75  3b481c                  cmp      ecx, dword ptr [eax + 0x1c]    
  0x00220B78  7c11                    jl       0x220b8b                       
  0x00220B7A  7f08                    jg       0x220b84                       
  0x00220B7C  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x00220B7F  3b4818                  cmp      ecx, dword ptr [eax + 0x18]    
  0x00220B82  7607                    jbe      0x220b8b                       
                                        ; XREF: 0x00220B7A (cond_jump)
  0x00220B84  e845feffff              call     0x2209ce                       ; -> sub_002209CE
  0x00220B89  eb1c                    jmp      0x220ba7                       
                                        ; XREF: 0x00220B78 (cond_jump), 0x00220B82 (cond_jump)
  0x00220B8B  68b46b2800              push     0x286bb4                       
  0x00220B90  881df86b2800            mov      byte ptr [0x286bf8], bl        
  0x00220B96  ff701c                  push     dword ptr [eax + 0x1c]         
  0x00220B99  ff7018                  push     dword ptr [eax + 0x18]         
  0x00220B9C  68d06b2800              push     0x286bd0                       
  0x00220BA1  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
                                        ; XREF: 0x00220B30 (jump), 0x00220B89 (jump)
  0x00220BA7  5b                      pop      ebx                            
  0x00220BA8  c9                      leave                                   
  0x00220BA9  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00220BAC
; Start: 0x00220BAC  End: 0x00220C23  Size: 119 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220744, sub_00220AAB, sub_002219D5, sub_00221A4E
; Called by: sub_00220C23, sub_00220CE9, sub_00221E4D, sub_00222280
; ============================================================
sub_00220BAC:
  0x00220BAC  56                      push     esi                            
  0x00220BAD  57                      push     edi                            
  0x00220BAE  ff74240c                push     dword ptr [esp + 0xc]          
  0x00220BB2  8bf9                    mov      edi, ecx                       
  0x00220BB4  e81c0e0000              call     0x2219d5                       ; -> sub_002219D5
  0x00220BB9  8bf0                    mov      esi, eax                       
  0x00220BBB  85f6                    test     esi, esi                       
  0x00220BBD  745f                    je       0x220c1e                       
  0x00220BBF  56                      push     esi                            
  0x00220BC0  8bcf                    mov      ecx, edi                       
  0x00220BC2  e8870e0000              call     0x221a4e                       ; -> sub_00221A4E
  0x00220BC7  803efe                  cmp      byte ptr [esi], 0xfe           
  0x00220BCA  7532                    jne      0x220bfe                       
  0x00220BCC  a1fc6b2800              mov      eax, dword ptr [0x286bfc]      
  0x00220BD1  3bc6                    cmp      eax, esi                       
  0x00220BD3  750d                    jne      0x220be2                       
  0x00220BD5  8b4610                  mov      eax, dword ptr [esi + 0x10]    
  0x00220BD8  a3fc6b2800              mov      dword ptr [0x286bfc], eax      
  0x00220BDD  eb0e                    jmp      0x220bed                       
                                        ; XREF: 0x00220BE5 (cond_jump)
  0x00220BDF  8b4010                  mov      eax, dword ptr [eax + 0x10]    
                                        ; XREF: 0x00220BD3 (cond_jump)
  0x00220BE2  3b7010                  cmp      esi, dword ptr [eax + 0x10]    
  0x00220BE5  75f8                    jne      0x220bdf                       
  0x00220BE7  8b4e10                  mov      ecx, dword ptr [esi + 0x10]    
  0x00220BEA  894810                  mov      dword ptr [eax + 0x10], ecx    
                                        ; XREF: 0x00220BDD (jump)
  0x00220BED  83661000                and      dword ptr [esi + 0x10], 0      
  0x00220BF1  56                      push     esi                            
  0x00220BF2  b9806b2800              mov      ecx, 0x286b80                  
  0x00220BF7  e848fbffff              call     0x220744                       ; -> sub_00220744
  0x00220BFC  eb20                    jmp      0x220c1e                       
                                        ; XREF: 0x00220BCA (cond_jump)
  0x00220BFE  803d806b280000          cmp      byte ptr [0x286b80], 0         
  0x00220C05  7411                    je       0x220c18                       
  0x00220C07  3935006c2800            cmp      dword ptr [0x286c00], esi      
  0x00220C0D  7509                    jne      0x220c18                       
  0x00220C0F  c605816b280001          mov      byte ptr [0x286b81], 1         
  0x00220C16  eb06                    jmp      0x220c1e                       
                                        ; XREF: 0x00220C05 (cond_jump), 0x00220C0D (cond_jump)
  0x00220C18  56                      push     esi                            
  0x00220C19  e88dfeffff              call     0x220aab                       ; -> sub_00220AAB
                                        ; XREF: 0x00220BBD (cond_jump), 0x00220BFC (jump), 0x00220C16 (jump)
  0x00220C1E  5f                      pop      edi                            
  0x00220C1F  5e                      pop      esi                            
  0x00220C20  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00220C23
; Start: 0x00220C23  End: 0x00220C68  Size: 69 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220776, sub_002207BB, sub_00220BAC
; ============================================================
sub_00220C23:
  0x00220C23  55                      push     ebp                            
  0x00220C24  8bec                    mov      ebp, esp                       
  0x00220C26  51                      push     ecx                            
  0x00220C27  803905                  cmp      byte ptr [ecx], 5              
  0x00220C2A  56                      push     esi                            
  0x00220C2B  57                      push     edi                            
  0x00220C2C  7509                    jne      0x220c37                       
  0x00220C2E  e843fbffff              call     0x220776                       ; -> sub_00220776
  0x00220C33  8bf0                    mov      esi, eax                       
  0x00220C35  eb02                    jmp      0x220c39                       
                                        ; XREF: 0x00220C2C (cond_jump)
  0x00220C37  8bf1                    mov      esi, ecx                       
                                        ; XREF: 0x00220C35 (jump)
  0x00220C39  8bce                    mov      ecx, esi                       
  0x00220C3B  e836fbffff              call     0x220776                       ; -> sub_00220776
  0x00220C40  8bf8                    mov      edi, eax                       
  0x00220C42  85ff                    test     edi, edi                       
  0x00220C44  741e                    je       0x220c64                       
  0x00220C46  8a4604                  mov      al, byte ptr [esi + 4]         
  0x00220C49  247f                    and      al, 0x7f                       
  0x00220C4B  8845fc                  mov      byte ptr [ebp - 4], al         
  0x00220C4E  ff75fc                  push     dword ptr [ebp - 4]            
  0x00220C51  8bcf                    mov      ecx, edi                       
  0x00220C53  e854ffffff              call     0x220bac                       ; -> sub_00220BAC
  0x00220C58  6a05                    push     5                              
  0x00220C5A  ff75fc                  push     dword ptr [ebp - 4]            
  0x00220C5D  8bcf                    mov      ecx, edi                       
  0x00220C5F  e857fbffff              call     0x2207bb                       ; -> sub_002207BB
                                        ; XREF: 0x00220C44 (cond_jump)
  0x00220C64  5f                      pop      edi                            
  0x00220C65  5e                      pop      esi                            
  0x00220C66  c9                      leave                                   
  0x00220C67  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220C68
; Start: 0x00220C68  End: 0x00220CE9  Size: 129 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220744, sub_00220776, sub_002207BB, sub_0022094E, sub_00220AFD, sub_00221A4E
; Called by: sub_00220CFC, sub_00220D2F
; ============================================================
sub_00220C68:
  0x00220C68  55                      push     ebp                            
  0x00220C69  8bec                    mov      ebp, esp                       
  0x00220C6B  51                      push     ecx                            
  0x00220C6C  53                      push     ebx                            
  0x00220C6D  56                      push     esi                            
  0x00220C6E  57                      push     edi                            
  0x00220C6F  32db                    xor      bl, bl                         
  0x00220C71  33ff                    xor      edi, edi                       
  0x00220C73  803d816b280000          cmp      byte ptr [0x286b81], 0         
  0x00220C7A  8bf1                    mov      esi, ecx                       
  0x00220C7C  885dfc                  mov      byte ptr [ebp - 4], bl         
  0x00220C7F  c605836b28000a          mov      byte ptr [0x286b83], 0xa       
  0x00220C86  7522                    jne      0x220caa                       
  0x00220C88  e8e9faffff              call     0x220776                       ; -> sub_00220776
  0x00220C8D  8bf8                    mov      edi, eax                       
  0x00220C8F  56                      push     esi                            
  0x00220C90  8bcf                    mov      ecx, edi                       
  0x00220C92  e8b70d0000              call     0x221a4e                       ; -> sub_00221A4E
  0x00220C97  a0826b2800              mov      al, byte ptr [0x286b82]        
  0x00220C9C  84c0                    test     al, al                         
  0x00220C9E  740a                    je       0x220caa                       
  0x00220CA0  8ad8                    mov      bl, al                         
  0x00220CA2  8a4604                  mov      al, byte ptr [esi + 4]         
  0x00220CA5  247f                    and      al, 0x7f                       
  0x00220CA7  8845fc                  mov      byte ptr [ebp - 4], al         
                                        ; XREF: 0x00220C86 (cond_jump), 0x00220C9E (cond_jump)
  0x00220CAA  8a5605                  mov      dl, byte ptr [esi + 5]         
  0x00220CAD  84d2                    test     dl, dl                         
  0x00220CAF  7408                    je       0x220cb9                       
  0x00220CB1  8b4e0c                  mov      ecx, dword ptr [esi + 0xc]     
  0x00220CB4  e895fcffff              call     0x22094e                       ; -> sub_0022094E
                                        ; XREF: 0x00220CAF (cond_jump)
  0x00220CB9  56                      push     esi                            
  0x00220CBA  b9806b2800              mov      ecx, 0x286b80                  
  0x00220CBF  e880faffff              call     0x220744                       ; -> sub_00220744
  0x00220CC4  84db                    test     bl, bl                         
  0x00220CC6  740d                    je       0x220cd5                       
  0x00220CC8  fecb                    dec      bl                             
  0x00220CCA  8bcf                    mov      ecx, edi                       
  0x00220CCC  53                      push     ebx                            
  0x00220CCD  ff75fc                  push     dword ptr [ebp - 4]            
  0x00220CD0  e8e6faffff              call     0x2207bb                       ; -> sub_002207BB
                                        ; XREF: 0x00220CC6 (cond_jump)
  0x00220CD5  56                      push     esi                            
  0x00220CD6  6a00                    push     0                              
  0x00220CD8  c605816b280000          mov      byte ptr [0x286b81], 0         
  0x00220CDF  e819feffff              call     0x220afd                       ; -> sub_00220AFD
  0x00220CE4  5f                      pop      edi                            
  0x00220CE5  5e                      pop      esi                            
  0x00220CE6  5b                      pop      ebx                            
  0x00220CE7  c9                      leave                                   
  0x00220CE8  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00220CE9
; Start: 0x00220CE9  End: 0x00220CFC  Size: 19 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220BAC
; Called by: sub_00222979
; ============================================================
sub_00220CE9:
  0x00220CE9  8b442404                mov      eax, dword ptr [esp + 4]       
  0x00220CED  ff742408                push     dword ptr [esp + 8]            
  0x00220CF1  8b48ec                  mov      ecx, dword ptr [eax - 0x14]    
  0x00220CF4  e8b3feffff              call     0x220bac                       ; -> sub_00220BAC
  0x00220CF9  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00220CFC
; Start: 0x00220CFC  End: 0x00220D2F  Size: 51 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220C68
; Called by: sub_00220D2F
; ============================================================
sub_00220CFC:
  0x00220CFC  8b4c2408                mov      ecx, dword ptr [esp + 8]       
  0x00220D00  33c0                    xor      eax, eax                       
  0x00220D02  39442404                cmp      dword ptr [esp + 4], eax       
  0x00220D06  c605836b280009          mov      byte ptr [0x286b83], 9         
  0x00220D0D  7d0b                    jge      0x220d1a                       
  0x00220D0F  3805816b2800            cmp      byte ptr [0x286b81], al        
  0x00220D15  750b                    jne      0x220d22                       
  0x00220D17  884105                  mov      byte ptr [ecx + 5], al         
                                        ; XREF: 0x00220D0D (cond_jump)
  0x00220D1A  3805816b2800            cmp      byte ptr [0x286b81], al        
  0x00220D20  7405                    je       0x220d27                       
                                        ; XREF: 0x00220D15 (cond_jump)
  0x00220D22  a2826b2800              mov      byte ptr [0x286b82], al        
                                        ; XREF: 0x00220D20 (cond_jump)
  0x00220D27  e83cffffff              call     0x220c68                       ; -> sub_00220C68
  0x00220D2C  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00220D2F
; Start: 0x00220D2F  End: 0x00220D9C  Size: 109 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220776, sub_00220C68, sub_00220CFC, sub_00221FFE, sub_00222A55
; Called by: sub_002208A1, sub_002209CE, sub_00220E01, sub_002211E3, sub_0022139C
; ============================================================
sub_00220D2F:
  0x00220D2F  803d816b280000          cmp      byte ptr [0x286b81], 0         
  0x00220D36  56                      push     esi                            
  0x00220D37  c605836b280008          mov      byte ptr [0x286b83], 8         
  0x00220D3E  7548                    jne      0x220d88                       
  0x00220D40  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00220D44  8bce                    mov      ecx, esi                       
  0x00220D46  e82bfaffff              call     0x220776                       ; -> sub_00220776
  0x00220D4B  803800                  cmp      byte ptr [eax], 0              
  0x00220D4E  7521                    jne      0x220d71                       
  0x00220D50  33c0                    xor      eax, eax                       
  0x00220D52  8a4604                  mov      al, byte ptr [esi + 4]         
  0x00220D55  83e07f                  and      eax, 0x7f                      
  0x00220D58  50                      push     eax                            
  0x00220D59  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x00220D5C  83c018                  add      eax, 0x18                      
  0x00220D5F  50                      push     eax                            
  0x00220D60  e8f01c0000              call     0x222a55                       ; -> sub_00222A55
  0x00220D65  56                      push     esi                            
  0x00220D66  6a00                    push     0                              
  0x00220D68  8bce                    mov      ecx, esi                       
  0x00220D6A  e88dffffff              call     0x220cfc                       ; -> sub_00220CFC
  0x00220D6F  eb27                    jmp      0x220d98                       
                                        ; XREF: 0x00220D4E (cond_jump)
  0x00220D71  33c9                    xor      ecx, ecx                       
  0x00220D73  8a4e04                  mov      cl, byte ptr [esi + 4]         
  0x00220D76  6a01                    push     1                              
  0x00220D78  56                      push     esi                            
  0x00220D79  81e17fffffff            and      ecx, 0xffffff7f                
  0x00220D7F  51                      push     ecx                            
  0x00220D80  50                      push     eax                            
  0x00220D81  e878120000              call     0x221ffe                       ; -> sub_00221FFE
  0x00220D86  eb10                    jmp      0x220d98                       
                                        ; XREF: 0x00220D3E (cond_jump)
  0x00220D88  8b4c240c                mov      ecx, dword ptr [esp + 0xc]     
  0x00220D8C  c605826b280000          mov      byte ptr [0x286b82], 0         
  0x00220D93  e8d0feffff              call     0x220c68                       ; -> sub_00220C68
                                        ; XREF: 0x00220D6F (jump), 0x00220D86 (jump)
  0x00220D98  5e                      pop      esi                            
  0x00220D99  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00220D9C
; Start: 0x00220D9C  End: 0x00220E01  Size: 101 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00223032
; Called by: sub_0022109C, sub_002212E3
; ============================================================
sub_00220D9C:
  0x00220D9C  68d06b2800              push     0x286bd0                       
  0x00220DA1  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00220DA7  8b442404                mov      eax, dword ptr [esp + 4]       
  0x00220DAB  c605836b280003          mov      byte ptr [0x286b83], 3         
  0x00220DB2  83780400                cmp      dword ptr [eax + 4], 0         
  0x00220DB6  7c13                    jl       0x220dcb                       
  0x00220DB8  803d816b280000          cmp      byte ptr [0x286b81], 0         
  0x00220DBF  c7058c6b2800f2082200    mov      dword ptr [0x286b8c], 0x2208f2 
  0x00220DC9  740a                    je       0x220dd5                       
                                        ; XREF: 0x00220DB6 (cond_jump)
  0x00220DCB  c7058c6b28002f0d2200    mov      dword ptr [0x286b8c], 0x220d2f 
                                        ; XREF: 0x00220DC9 (cond_jump)
  0x00220DD5  56                      push     esi                            
  0x00220DD6  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00220DDA  c605846b28001c          mov      byte ptr [0x286b84], 0x1c      
  0x00220DE1  c605856b280043          mov      byte ptr [0x286b85], 0x43      
  0x00220DE8  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x00220DEB  68846b2800              push     0x286b84                       
  0x00220DF0  83c018                  add      eax, 0x18                      
  0x00220DF3  50                      push     eax                            
  0x00220DF4  e839220000              call     0x223032                       ; -> sub_00223032
  0x00220DF9  83660800                and      dword ptr [esi + 8], 0         
  0x00220DFD  5e                      pop      esi                            
  0x00220DFE  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00220E01
; Start: 0x00220E01  End: 0x00220F8D  Size: 396 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220744, sub_00220776, sub_0022078D, sub_002207A4, sub_00220AFD, sub_00220D2F, sub_00220F8D, sub_0022153B, sub_00221A4E, sub_00223032
; Called by: sub_00220F8D, sub_00223BD4
; ============================================================
sub_00220E01:
  0x00220E01  55                      push     ebp                            
  0x00220E02  8bec                    mov      ebp, esp                       
  0x00220E04  83ec0c                  sub      esp, 0xc                       
  0x00220E07  53                      push     ebx                            
  0x00220E08  56                      push     esi                            
  0x00220E09  8bf1                    mov      esi, ecx                       
  0x00220E0B  33c9                    xor      ecx, ecx                       
  0x00220E0D  41                      inc      ecx                            
  0x00220E0E  33db                    xor      ebx, ebx                       
  0x00220E10  395d08                  cmp      dword ptr [ebp + 8], ebx       
  0x00220E13  57                      push     edi                            
  0x00220E14  894dfc                  mov      dword ptr [ebp - 4], ecx       
  0x00220E17  c605836b280007          mov      byte ptr [0x286b83], 7         
  0x00220E1E  7d11                    jge      0x220e31                       
  0x00220E20  817d0800040080          cmp      dword ptr [ebp + 8], 0x80000400 
  0x00220E27  7503                    jne      0x220e2c                       
  0x00220E29  895dfc                  mov      dword ptr [ebp - 4], ebx       
                                        ; XREF: 0x00220E27 (cond_jump)
  0x00220E2C  895e10                  mov      dword ptr [esi + 0x10], ebx    
  0x00220E2F  eb21                    jmp      0x220e52                       
                                        ; XREF: 0x00220E1E (cond_jump)
  0x00220E31  8a4607                  mov      al, byte ptr [esi + 7]         
  0x00220E34  3cff                    cmp      al, 0xff                       
  0x00220E36  741a                    je       0x220e52                       
  0x00220E38  8b5610                  mov      edx, dword ptr [esi + 0x10]    
  0x00220E3B  8b5214                  mov      edx, dword ptr [edx + 0x14]    
  0x00220E3E  0fb6c0                  movzx    eax, al                        
  0x00220E41  8b0482                  mov      eax, dword ptr [edx + eax*4]   
  0x00220E44  3bc3                    cmp      eax, ebx                       
  0x00220E46  740a                    je       0x220e52                       
  0x00220E48  51                      push     ecx                            
  0x00220E49  ff7614                  push     dword ptr [esi + 0x14]         
  0x00220E4C  50                      push     eax                            
  0x00220E4D  e8e9060000              call     0x22153b                       ; -> sub_0022153B
                                        ; XREF: 0x00220E2F (jump), 0x00220E36 (cond_jump), 0x00220E46 (cond_jump)
  0x00220E52  8a06                    mov      al, byte ptr [esi]             
  0x00220E54  3c02                    cmp      al, 2                          
  0x00220E56  0f840b010000            je       0x220f67                       
  0x00220E5C  3c01                    cmp      al, 1                          
  0x00220E5E  0f8403010000            je       0x220f67                       
  0x00220E64  3c05                    cmp      al, 5                          
  0x00220E66  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x00220E69  8bfe                    mov      edi, esi                       
  0x00220E6B  894df4                  mov      dword ptr [ebp - 0xc], ecx     
  0x00220E6E  895e08                  mov      dword ptr [esi + 8], ebx       
  0x00220E71  c745f8fd0a2200          mov      dword ptr [ebp - 8], 0x220afd  
  0x00220E78  0f859a000000            jne      0x220f18                       
  0x00220E7E  8bce                    mov      ecx, esi                       
  0x00220E80  e81ff9ffff              call     0x2207a4                       ; -> sub_002207A4
  0x00220E85  8bce                    mov      ecx, esi                       
  0x00220E87  8bd8                    mov      ebx, eax                       
  0x00220E89  e8e8f8ffff              call     0x220776                       ; -> sub_00220776
  0x00220E8E  803d816b280000          cmp      byte ptr [0x286b81], 0         
  0x00220E95  8bf8                    mov      edi, eax                       
  0x00220E97  0f8593000000            jne      0x220f30                       
  0x00220E9D  837e1000                cmp      dword ptr [esi + 0x10], 0      
  0x00220EA1  752f                    jne      0x220ed2                       
  0x00220EA3  56                      push     esi                            
  0x00220EA4  8bcf                    mov      ecx, edi                       
  0x00220EA6  e8a30b0000              call     0x221a4e                       ; -> sub_00221A4E
  0x00220EAB  56                      push     esi                            
  0x00220EAC  b9806b2800              mov      ecx, 0x286b80                  
  0x00220EB1  e88ef8ffff              call     0x220744                       ; -> sub_00220744
  0x00220EB6  8bcf                    mov      ecx, edi                       
  0x00220EB8  e8d0f8ffff              call     0x22078d                       ; -> sub_0022078D
  0x00220EBD  85c0                    test     eax, eax                       
  0x00220EBF  7511                    jne      0x220ed2                       
  0x00220EC1  57                      push     edi                            
  0x00220EC2  a2826b2800              mov      byte ptr [0x286b82], al        
  0x00220EC7  50                      push     eax                            
                                        ; XREF: 0x00220F7A (jump)
  0x00220EC8  e862feffff              call     0x220d2f                       ; -> sub_00220D2F
  0x00220ECD  e9b4000000              jmp      0x220f86                       
                                        ; XREF: 0x00220EA1 (cond_jump), 0x00220EBF (cond_jump)
  0x00220ED2  85db                    test     ebx, ebx                       
  0x00220ED4  745a                    je       0x220f30                       
  0x00220ED6  a15c6c2800              mov      eax, dword ptr [0x286c5c]      
                                        ; XREF: 0x00220EE4 (cond_jump)
  0x00220EDB  0fb608                  movzx    ecx, byte ptr [eax]            
  0x00220EDE  03c1                    add      eax, ecx                       
  0x00220EE0  80780104                cmp      byte ptr [eax + 1], 4          
  0x00220EE4  75f5                    jne      0x220edb                       
  0x00220EE6  a35c6c2800              mov      dword ptr [0x286c5c], eax      
  0x00220EEB  8a4002                  mov      al, byte ptr [eax + 2]         
  0x00220EEE  884302                  mov      byte ptr [ebx + 2], al         
  0x00220EF1  a15c6c2800              mov      eax, dword ptr [0x286c5c]      
  0x00220EF6  8a4805                  mov      cl, byte ptr [eax + 5]         
  0x00220EF9  884d09                  mov      byte ptr [ebp + 9], cl         
  0x00220EFC  8a4806                  mov      cl, byte ptr [eax + 6]         
  0x00220EFF  8a4007                  mov      al, byte ptr [eax + 7]         
  0x00220F02  884d0a                  mov      byte ptr [ebp + 0xa], cl       
  0x00220F05  88450b                  mov      byte ptr [ebp + 0xb], al       
  0x00220F08  c6450882                mov      byte ptr [ebp + 8], 0x82       
  0x00220F0C  ff7508                  push     dword ptr [ebp + 8]            
  0x00220F0F  8bcb                    mov      ecx, ebx                       
  0x00220F11  e877000000              call     0x220f8d                       ; -> sub_00220F8D
  0x00220F16  eb6e                    jmp      0x220f86                       
                                        ; XREF: 0x00220E78 (cond_jump)
  0x00220F18  395d08                  cmp      dword ptr [ebp + 8], ebx       
  0x00220F1B  7d13                    jge      0x220f30                       
  0x00220F1D  395dfc                  cmp      dword ptr [ebp - 4], ebx       
  0x00220F20  7507                    jne      0x220f29                       
  0x00220F22  c605826b280000          mov      byte ptr [0x286b82], 0         
                                        ; XREF: 0x00220F20 (cond_jump)
  0x00220F29  c745f82f0d2200          mov      dword ptr [ebp - 8], 0x220d2f  
                                        ; XREF: 0x00220E97 (cond_jump), 0x00220ED4 (cond_jump), 0x00220F1B (cond_jump)
  0x00220F30  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00220F33  a38c6b2800              mov      dword ptr [0x286b8c], eax      
  0x00220F38  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x00220F3B  a3946b2800              mov      dword ptr [0x286b94], eax      
  0x00220F40  c605846b28001c          mov      byte ptr [0x286b84], 0x1c      
  0x00220F47  c605856b280043          mov      byte ptr [0x286b85], 0x43      
  0x00220F4E  893d906b2800            mov      dword ptr [0x286b90], edi      
  0x00220F54  8b470c                  mov      eax, dword ptr [edi + 0xc]     
  0x00220F57  68846b2800              push     0x286b84                       
  0x00220F5C  83c018                  add      eax, 0x18                      
  0x00220F5F  50                      push     eax                            
  0x00220F60  e8cd200000              call     0x223032                       ; -> sub_00223032
  0x00220F65  eb1f                    jmp      0x220f86                       
                                        ; XREF: 0x00220E56 (cond_jump), 0x00220E5E (cond_jump)
  0x00220F67  395d08                  cmp      dword ptr [ebp + 8], ebx       
  0x00220F6A  7d13                    jge      0x220f7f                       
  0x00220F6C  395dfc                  cmp      dword ptr [ebp - 4], ebx       
  0x00220F6F  7507                    jne      0x220f78                       
  0x00220F71  c605826b280000          mov      byte ptr [0x286b82], 0         
                                        ; XREF: 0x00220F6F (cond_jump)
  0x00220F78  56                      push     esi                            
  0x00220F79  53                      push     ebx                            
  0x00220F7A  e949ffffff              jmp      0x220ec8                       
                                        ; XREF: 0x00220F6A (cond_jump)
  0x00220F7F  56                      push     esi                            
  0x00220F80  53                      push     ebx                            
  0x00220F81  e877fbffff              call     0x220afd                       ; -> sub_00220AFD
                                        ; XREF: 0x00220ECD (jump), 0x00220F16 (jump), 0x00220F65 (jump)
  0x00220F86  5f                      pop      edi                            
  0x00220F87  5e                      pop      esi                            
  0x00220F88  5b                      pop      ebx                            
  0x00220F89  c9                      leave                                   
  0x00220F8A  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00220F8D
; Start: 0x00220F8D  End: 0x00220FC1  Size: 52 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220E01, sub_00221C4B, sub_00223201
; Called by: sub_00220E01, sub_0022109C, sub_0022139C
; ============================================================
sub_00220F8D:
  0x00220F8D  56                      push     esi                            
  0x00220F8E  8bf1                    mov      esi, ecx                       
  0x00220F90  e8b60c0000              call     0x221c4b                       ; -> sub_00221C4B
  0x00220F95  837e1420                cmp      dword ptr [esi + 0x14], 0x20   
  0x00220F99  7416                    je       0x220fb1                       
  0x00220F9B  ff742408                push     dword ptr [esp + 8]            
  0x00220F9F  e85d220000              call     0x223201                       ; -> sub_00223201
  0x00220FA4  85c0                    test     eax, eax                       
  0x00220FA6  894610                  mov      dword ptr [esi + 0x10], eax    
  0x00220FA9  7406                    je       0x220fb1                       
  0x00220FAB  56                      push     esi                            
  0x00220FAC  ff5008                  call     dword ptr [eax + 8]            
  0x00220FAF  eb0c                    jmp      0x220fbd                       
                                        ; XREF: 0x00220F99 (cond_jump), 0x00220FA9 (cond_jump)
  0x00220FB1  8bce                    mov      ecx, esi                       
  0x00220FB3  6800040080              push     0x80000400                     
  0x00220FB8  e844feffff              call     0x220e01                       ; -> sub_00220E01
                                        ; XREF: 0x00220FAF (jump)
  0x00220FBD  5e                      pop      esi                            
  0x00220FBE  c20400                  ret      4                              
; end of function
                                        ; XREF: 0x00221271 (data_imm)
  0x00220FC1  53                      push     ebx                            
  0x00220FC2  68d06b2800              push     0x286bd0                       
  0x00220FC7  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00220FCD  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00220FD1  33db                    xor      ebx, ebx                       
  0x00220FD3  c605836b280002          mov      byte ptr [0x286b83], 2         
  0x00220FDA  395a04                  cmp      dword ptr [edx + 4], ebx       
  0x00220FDD  0f8cab000000            jl       0x22108e                       
  0x00220FE3  381d816b2800            cmp      byte ptr [0x286b81], bl        
  0x00220FE9  0f859f000000            jne      0x22108e                       
  0x00220FEF  837a1408                cmp      dword ptr [edx + 0x14], 8      
  0x00220FF3  0f828e000000            jb       0x221087                       
  0x00220FF9  a00b6c2800              mov      al, byte ptr [0x286c0b]        
  0x00220FFE  3c40                    cmp      al, 0x40                       
  0x00221000  0f8781000000            ja       0x221087                       
  0x00221006  803d056c280001          cmp      byte ptr [0x286c05], 1         
  0x0022100D  7578                    jne      0x221087                       
  0x0022100F  8a0d046c2800            mov      cl, byte ptr [0x286c04]        
  0x00221015  80f908                  cmp      cl, 8                          
  0x00221018  7405                    je       0x22101f                       
  0x0022101A  80f912                  cmp      cl, 0x12                       
  0x0022101D  7568                    jne      0x221087                       
                                        ; XREF: 0x00221018 (cond_jump)
  0x0022101F  56                      push     esi                            
  0x00221020  8b742410                mov      esi, dword ptr [esp + 0x10]    
  0x00221024  8b4e0c                  mov      ecx, dword ptr [esi + 0xc]     
  0x00221027  884606                  mov      byte ptr [esi + 6], al         
  0x0022102A  e8eef8ffff              call     0x22091d                       ; -> sub_0022091D
  0x0022102F  884605                  mov      byte ptr [esi + 5], al         
  0x00221032  c7058c6b28009c0d2200    mov      dword ptr [0x286b8c], 0x220d9c 
  0x0022103C  891d9c6b2800            mov      dword ptr [0x286b9c], ebx      
  0x00221042  891d986b2800            mov      dword ptr [0x286b98], ebx      
  0x00221048  881dac6b2800            mov      byte ptr [0x286bac], bl        
  0x0022104E  c605ad6b280005          mov      byte ptr [0x286bad], 5         
  0x00221055  660fb64605              movzx    ax, byte ptr [esi + 5]         
  0x0022105A  66a3ae6b2800            mov      word ptr [0x286bae], ax        
  0x00221060  66891db06b2800          mov      word ptr [0x286bb0], bx        
  0x00221067  66891db26b2800          mov      word ptr [0x286bb2], bx        
  0x0022106E  e80cf8ffff              call     0x22087f                       ; -> sub_0022087F
  0x00221073  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x00221076  68846b2800              push     0x286b84                       
  0x0022107B  83c018                  add      eax, 0x18                      
  0x0022107E  50                      push     eax                            
  0x0022107F  e8ae1f0000              call     0x223032                       ; -> sub_00223032
  0x00221084  5e                      pop      esi                            
  0x00221085  eb11                    jmp      0x221098                       
                                        ; XREF: 0x00220FF3 (cond_jump), 0x00221000 (cond_jump), 0x0022100D (cond_jump), 0x0022101D (cond_jump)
  0x00221087  c7420400060080          mov      dword ptr [edx + 4], 0x80000600 
                                        ; XREF: 0x00220FDD (cond_jump), 0x00220FE9 (cond_jump)
  0x0022108E  ff74240c                push     dword ptr [esp + 0xc]          
  0x00221092  52                      push     edx                            
  0x00221093  e804fdffff              call     0x220d9c                       ; -> sub_00220D9C
                                        ; XREF: 0x00221085 (jump)
  0x00221098  5b                      pop      ebx                            
  0x00221099  c20800                  ret      8                              

; ============================================================
; Function: sub_0022109C
; Start: 0x0022109C  End: 0x002211E3  Size: 327 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002206F4, sub_0022078D, sub_00220D9C, sub_00220F8D, sub_00221A06
; ============================================================
sub_0022109C:
  0x0022109C  55                      push     ebp                            
  0x0022109D  8bec                    mov      ebp, esp                       
  0x0022109F  53                      push     ebx                            
  0x002210A0  56                      push     esi                            
  0x002210A1  68d06b2800              push     0x286bd0                       
  0x002210A6  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x002210AC  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002210AF  33db                    xor      ebx, ebx                       
  0x002210B1  c605836b280006          mov      byte ptr [0x286b83], 6         
  0x002210B8  395904                  cmp      dword ptr [ecx + 4], ebx       
  0x002210BB  0f8c13010000            jl       0x2211d4                       
  0x002210C1  381d816b2800            cmp      byte ptr [0x286b81], bl        
  0x002210C7  0f8507010000            jne      0x2211d4                       
  0x002210CD  8b750c                  mov      esi, dword ptr [ebp + 0xc]     
  0x002210D0  895e18                  mov      dword ptr [esi + 0x18], ebx    
  0x002210D3  b80c6c2800              mov      eax, 0x286c0c                  
                                        ; XREF: 0x002210F5 (cond_jump)
  0x002210D8  0fb610                  movzx    edx, byte ptr [eax]            
  0x002210DB  03c2                    add      eax, edx                       
  0x002210DD  3d5c6c2800              cmp      eax, 0x286c5c                  
  0x002210E2  0f83db000000            jae      0x2211c3                       
  0x002210E8  803800                  cmp      byte ptr [eax], 0              
  0x002210EB  0f84d2000000            je       0x2211c3                       
  0x002210F1  80780104                cmp      byte ptr [eax + 1], 4          
  0x002210F5  75e1                    jne      0x2210d8                       
  0x002210F7  803d106c280001          cmp      byte ptr [0x286c10], 1         
  0x002210FE  a35c6c2800              mov      dword ptr [0x286c5c], eax      
  0x00221103  0f8485000000            je       0x22118e                       
  0x00221109  803dfb6b280000          cmp      byte ptr [0x286bfb], 0         
  0x00221110  747c                    je       0x22118e                       
  0x00221112  c60604                  mov      byte ptr [esi], 4              
  0x00221115  c6460280                mov      byte ptr [esi + 2], 0x80       
  0x00221119  803d106c280000          cmp      byte ptr [0x286c10], 0         
  0x00221120  765d                    jbe      0x22117f                       
                                        ; XREF: 0x0022117D (cond_jump)
  0x00221122  0fb605fb6b2800          movzx    eax, byte ptr [0x286bfb]       
  0x00221129  3bc3                    cmp      eax, ebx                       
  0x0022112B  7652                    jbe      0x22117f                       
  0x0022112D  b9806b2800              mov      ecx, 0x286b80                  
  0x00221132  e8bdf5ffff              call     0x2206f4                       ; -> sub_002206F4
  0x00221137  85c0                    test     eax, eax                       
  0x00221139  7444                    je       0x22117f                       
  0x0022113B  c60005                  mov      byte ptr [eax], 5              
  0x0022113E  8a4e04                  mov      cl, byte ptr [esi + 4]         
  0x00221141  80e180                  and      cl, 0x80                       
  0x00221144  8ad3                    mov      dl, bl                         
  0x00221146  fec2                    inc      dl                             
  0x00221148  0aca                    or       cl, dl                         
  0x0022114A  884804                  mov      byte ptr [eax + 4], cl         
  0x0022114D  8a4e05                  mov      cl, byte ptr [esi + 5]         
  0x00221150  884805                  mov      byte ptr [eax + 5], cl         
  0x00221153  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x00221156  894808                  mov      dword ptr [eax + 8], ecx       
  0x00221159  8b4e0c                  mov      ecx, dword ptr [esi + 0xc]     
  0x0022115C  89480c                  mov      dword ptr [eax + 0xc], ecx     
  0x0022115F  8a4e06                  mov      cl, byte ptr [esi + 6]         
  0x00221162  884806                  mov      byte ptr [eax + 6], cl         
  0x00221165  8b4e18                  mov      ecx, dword ptr [esi + 0x18]    
  0x00221168  894818                  mov      dword ptr [eax + 0x18], ecx    
  0x0022116B  50                      push     eax                            
  0x0022116C  8bce                    mov      ecx, esi                       
  0x0022116E  e893080000              call     0x221a06                       ; -> sub_00221A06
  0x00221173  0fb605106c2800          movzx    eax, byte ptr [0x286c10]       
  0x0022117A  43                      inc      ebx                            
  0x0022117B  3bd8                    cmp      ebx, eax                       
  0x0022117D  72a3                    jb       0x221122                       
                                        ; XREF: 0x00221120 (cond_jump), 0x0022112B (cond_jump), 0x00221139 (cond_jump)
  0x0022117F  83660800                and      dword ptr [esi + 8], 0         
  0x00221183  8bce                    mov      ecx, esi                       
  0x00221185  e803f6ffff              call     0x22078d                       ; -> sub_0022078D
  0x0022118A  8bf0                    mov      esi, eax                       
  0x0022118C  eb03                    jmp      0x221191                       
                                        ; XREF: 0x00221103 (cond_jump), 0x00221110 (cond_jump)
  0x0022118E  c60603                  mov      byte ptr [esi], 3              
                                        ; XREF: 0x0022118C (jump)
  0x00221191  a15c6c2800              mov      eax, dword ptr [0x286c5c]      
  0x00221196  8a4002                  mov      al, byte ptr [eax + 2]         
  0x00221199  884602                  mov      byte ptr [esi + 2], al         
  0x0022119C  a15c6c2800              mov      eax, dword ptr [0x286c5c]      
  0x002211A1  8a4805                  mov      cl, byte ptr [eax + 5]         
  0x002211A4  884d0d                  mov      byte ptr [ebp + 0xd], cl       
  0x002211A7  8a4806                  mov      cl, byte ptr [eax + 6]         
  0x002211AA  8a4007                  mov      al, byte ptr [eax + 7]         
  0x002211AD  884d0e                  mov      byte ptr [ebp + 0xe], cl       
  0x002211B0  88450f                  mov      byte ptr [ebp + 0xf], al       
  0x002211B3  c6450c82                mov      byte ptr [ebp + 0xc], 0x82     
  0x002211B7  ff750c                  push     dword ptr [ebp + 0xc]          
  0x002211BA  8bce                    mov      ecx, esi                       
  0x002211BC  e8ccfdffff              call     0x220f8d                       ; -> sub_00220F8D
  0x002211C1  eb1a                    jmp      0x2211dd                       
                                        ; XREF: 0x002210E2 (cond_jump), 0x002210EB (cond_jump)
  0x002211C3  c605826b280000          mov      byte ptr [0x286b82], 0         
  0x002211CA  c7410400040080          mov      dword ptr [ecx + 4], 0x80000400 
  0x002211D1  56                      push     esi                            
  0x002211D2  eb03                    jmp      0x2211d7                       
                                        ; XREF: 0x002210BB (cond_jump), 0x002210C7 (cond_jump)
  0x002211D4  ff750c                  push     dword ptr [ebp + 0xc]          
                                        ; XREF: 0x002211D2 (jump)
  0x002211D7  51                      push     ecx                            
  0x002211D8  e8bffbffff              call     0x220d9c                       ; -> sub_00220D9C
                                        ; XREF: 0x002211C1 (jump)
  0x002211DD  5e                      pop      esi                            
  0x002211DE  5b                      pop      ebx                            
  0x002211DF  5d                      pop      ebp                            
  0x002211E0  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_002211E3
; Start: 0x002211E3  End: 0x002212E3  Size: 256 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022087F, sub_00220D2F, sub_00223032
; ============================================================
sub_002211E3:
  0x002211E3  53                      push     ebx                            
  0x002211E4  56                      push     esi                            
  0x002211E5  57                      push     edi                            
  0x002211E6  8bf1                    mov      esi, ecx                       
  0x002211E8  8b7e0c                  mov      edi, dword ptr [esi + 0xc]     
  0x002211EB  33db                    xor      ebx, ebx                       
  0x002211ED  83c718                  add      edi, 0x18                      
  0x002211F0  381d816b2800            cmp      byte ptr [0x286b81], bl        
  0x002211F6  c605836b280001          mov      byte ptr [0x286b83], 1         
  0x002211FD  740c                    je       0x22120b                       
  0x002211FF  56                      push     esi                            
  0x00221200  53                      push     ebx                            
  0x00221201  e829fbffff              call     0x220d2f                       ; -> sub_00220D2F
  0x00221206  e9d4000000              jmp      0x2212df                       
                                        ; XREF: 0x002211FD (cond_jump)
  0x0022120B  895e18                  mov      dword ptr [esi + 0x18], ebx    
  0x0022120E  55                      push     ebp                            
  0x0022120F  c605846b280020          mov      byte ptr [0x286b84], 0x20      
  0x00221216  c605856b280002          mov      byte ptr [0x286b85], 2         
  0x0022121D  891d8c6b2800            mov      dword ptr [0x286b8c], ebx      
  0x00221223  881d996b2800            mov      byte ptr [0x286b99], bl        
  0x00221229  881d9a6b2800            mov      byte ptr [0x286b9a], bl        
  0x0022122F  881d9b6b2800            mov      byte ptr [0x286b9b], bl        
  0x00221235  66c705a06b28000800      mov      word ptr [0x286ba0], 8         
  0x0022123E  8a4604                  mov      al, byte ptr [esi + 4]         
  0x00221241  bd846b2800              mov      ebp, 0x286b84                  
  0x00221246  55                      push     ebp                            
  0x00221247  c0e807                  shr      al, 7                          
  0x0022124A  57                      push     edi                            
  0x0022124B  a2a26b2800              mov      byte ptr [0x286ba2], al        
  0x00221250  881d986b2800            mov      byte ptr [0x286b98], bl        
  0x00221256  e8d71d0000              call     0x223032                       ; -> sub_00223032
  0x0022125B  a1946b2800              mov      eax, dword ptr [0x286b94]      
  0x00221260  894608                  mov      dword ptr [esi + 8], eax       
  0x00221263  c605846b280030          mov      byte ptr [0x286b84], 0x30      
  0x0022126A  c605856b280040          mov      byte ptr [0x286b85], 0x40      
  0x00221271  c7058c6b2800c10f2200    mov      dword ptr [0x286b8c], 0x220fc1 
  0x0022127B  8935906b2800            mov      dword ptr [0x286b90], esi      
  0x00221281  8b4608                  mov      eax, dword ptr [esi + 8]       
  0x00221284  6a08                    push     8                              
  0x00221286  a3946b2800              mov      dword ptr [0x286b94], eax      
  0x0022128B  58                      pop      eax                            
  0x0022128C  c7059c6b2800046c2800    mov      dword ptr [0x286b9c], 0x286c04 
  0x00221296  a3986b2800              mov      dword ptr [0x286b98], eax      
  0x0022129B  c605a06b280002          mov      byte ptr [0x286ba0], 2         
  0x002212A2  881da16b2800            mov      byte ptr [0x286ba1], bl        
  0x002212A8  881da26b2800            mov      byte ptr [0x286ba2], bl        
  0x002212AE  c605ac6b280080          mov      byte ptr [0x286bac], 0x80      
  0x002212B5  c605ad6b280006          mov      byte ptr [0x286bad], 6         
  0x002212BC  66c705ae6b28000001      mov      word ptr [0x286bae], 0x100     
  0x002212C5  66891db06b2800          mov      word ptr [0x286bb0], bx        
  0x002212CC  66a3b26b2800            mov      word ptr [0x286bb2], ax        
  0x002212D2  e8a8f5ffff              call     0x22087f                       ; -> sub_0022087F
  0x002212D7  55                      push     ebp                            
  0x002212D8  57                      push     edi                            
  0x002212D9  e8541d0000              call     0x223032                       ; -> sub_00223032
  0x002212DE  5d                      pop      ebp                            
                                        ; XREF: 0x00221206 (jump)
  0x002212DF  5f                      pop      edi                            
  0x002212E0  5e                      pop      esi                            
  0x002212E1  5b                      pop      ebx                            
  0x002212E2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002212E3
; Start: 0x002212E3  End: 0x0022139C  Size: 185 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022087F, sub_00220D9C, sub_00223032
; ============================================================
sub_002212E3:
  0x002212E3  55                      push     ebp                            
  0x002212E4  8bec                    mov      ebp, esp                       
  0x002212E6  68d06b2800              push     0x286bd0                       
  0x002212EB  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x002212F1  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x002212F4  33d2                    xor      edx, edx                       
  0x002212F6  c605836b280005          mov      byte ptr [0x286b83], 5         
  0x002212FD  395004                  cmp      dword ptr [eax + 4], edx       
  0x00221300  7c22                    jl       0x221324                       
  0x00221302  3815816b2800            cmp      byte ptr [0x286b81], dl        
  0x00221308  751a                    jne      0x221324                       
  0x0022130A  668b0d0e6c2800          mov      cx, word ptr [0x286c0e]        
  0x00221311  6683f950                cmp      cx, 0x50                       
  0x00221315  761a                    jbe      0x221331                       
  0x00221317  8815826b2800            mov      byte ptr [0x286b82], dl        
  0x0022131D  c7400400040080          mov      dword ptr [eax + 4], 0x80000400 
                                        ; XREF: 0x00221300 (cond_jump), 0x00221308 (cond_jump), 0x00221340 (jump)
  0x00221324  ff750c                  push     dword ptr [ebp + 0xc]          
  0x00221327  50                      push     eax                            
  0x00221328  e86ffaffff              call     0x220d9c                       ; -> sub_00220D9C
                                        ; XREF: 0x0022139A (jump)
  0x0022132D  5d                      pop      ebp                            
  0x0022132E  c20800                  ret      8                              
                                        ; XREF: 0x00221315 (cond_jump)
  0x00221331  0fb7c9                  movzx    ecx, cx                        
  0x00221334  3b4814                  cmp      ecx, dword ptr [eax + 0x14]    
  0x00221337  7409                    je       0x221342                       
  0x00221339  c7400400000080          mov      dword ptr [eax + 4], 0x80000000 
  0x00221340  ebe2                    jmp      0x221324                       
                                        ; XREF: 0x00221337 (cond_jump)
  0x00221342  660fb605116c2800        movzx    ax, byte ptr [0x286c11]        
  0x0022134A  c7058c6b28009c102200    mov      dword ptr [0x286b8c], 0x22109c 
  0x00221354  89159c6b2800            mov      dword ptr [0x286b9c], edx      
  0x0022135A  8915986b2800            mov      dword ptr [0x286b98], edx      
  0x00221360  8815ac6b2800            mov      byte ptr [0x286bac], dl        
  0x00221366  c605ad6b280009          mov      byte ptr [0x286bad], 9         
  0x0022136D  66a3ae6b2800            mov      word ptr [0x286bae], ax        
  0x00221373  668915b06b2800          mov      word ptr [0x286bb0], dx        
  0x0022137A  668915b26b2800          mov      word ptr [0x286bb2], dx        
  0x00221381  e8f9f4ffff              call     0x22087f                       ; -> sub_0022087F
  0x00221386  8b450c                  mov      eax, dword ptr [ebp + 0xc]     
  0x00221389  8b400c                  mov      eax, dword ptr [eax + 0xc]     
  0x0022138C  68846b2800              push     0x286b84                       
  0x00221391  83c018                  add      eax, 0x18                      
  0x00221394  50                      push     eax                            
  0x00221395  e8981c0000              call     0x223032                       ; -> sub_00223032
  0x0022139A  eb91                    jmp      0x22132d                       
; end of function

; ============================================================
; Function: sub_0022139C
; Start: 0x0022139C  End: 0x002214E7  Size: 331 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022087F, sub_00220D2F, sub_00220F8D, sub_00223032
; ============================================================
sub_0022139C:
  0x0022139C  55                      push     ebp                            
  0x0022139D  8bec                    mov      ebp, esp                       
  0x0022139F  51                      push     ecx                            
  0x002213A0  53                      push     ebx                            
  0x002213A1  33db                    xor      ebx, ebx                       
  0x002213A3  381d816b2800            cmp      byte ptr [0x286b81], bl        
  0x002213A9  56                      push     esi                            
  0x002213AA  8bf2                    mov      esi, edx                       
  0x002213AC  c605836b280004          mov      byte ptr [0x286b83], 4         
  0x002213B3  740c                    je       0x2213c1                       
  0x002213B5  56                      push     esi                            
  0x002213B6  53                      push     ebx                            
  0x002213B7  e873f9ffff              call     0x220d2f                       ; -> sub_00220D2F
  0x002213BC  e922010000              jmp      0x2214e3                       
                                        ; XREF: 0x002213B3 (cond_jump)
  0x002213C1  a0086c2800              mov      al, byte ptr [0x286c08]        
  0x002213C6  3ac3                    cmp      al, bl                         
  0x002213C8  7434                    je       0x2213fe                       
  0x002213CA  3c09                    cmp      al, 9                          
  0x002213CC  0f95c0                  setne    al                             
  0x002213CF  fec0                    inc      al                             
  0x002213D1  8806                    mov      byte ptr [esi], al             
  0x002213D3  a0086c2800              mov      al, byte ptr [0x286c08]        
  0x002213D8  8845fd                  mov      byte ptr [ebp - 3], al         
  0x002213DB  a0096c2800              mov      al, byte ptr [0x286c09]        
  0x002213E0  8845fe                  mov      byte ptr [ebp - 2], al         
  0x002213E3  a00a6c2800              mov      al, byte ptr [0x286c0a]        
  0x002213E8  8845ff                  mov      byte ptr [ebp - 1], al         
  0x002213EB  c645fc81                mov      byte ptr [ebp - 4], 0x81       
  0x002213EF  ff75fc                  push     dword ptr [ebp - 4]            
  0x002213F2  8bce                    mov      ecx, esi                       
  0x002213F4  e894fbffff              call     0x220f8d                       ; -> sub_00220F8D
  0x002213F9  e9e5000000              jmp      0x2214e3                       
                                        ; XREF: 0x002213C8 (cond_jump)
  0x002213FE  660fb6050b6c2800        movzx    ax, byte ptr [0x286c0b]        
  0x00221406  66a3a06b2800            mov      word ptr [0x286ba0], ax        
  0x0022140C  c605846b280020          mov      byte ptr [0x286b84], 0x20      
  0x00221413  c605856b280002          mov      byte ptr [0x286b85], 2         
  0x0022141A  891d8c6b2800            mov      dword ptr [0x286b8c], ebx      
  0x00221420  881d996b2800            mov      byte ptr [0x286b99], bl        
  0x00221426  881d9a6b2800            mov      byte ptr [0x286b9a], bl        
  0x0022142C  881d9b6b2800            mov      byte ptr [0x286b9b], bl        
  0x00221432  8a4604                  mov      al, byte ptr [esi + 4]         
  0x00221435  c0e807                  shr      al, 7                          
  0x00221438  a2a26b2800              mov      byte ptr [0x286ba2], al        
  0x0022143D  8a4605                  mov      al, byte ptr [esi + 5]         
  0x00221440  57                      push     edi                            
  0x00221441  a2986b2800              mov      byte ptr [0x286b98], al        
  0x00221446  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x00221449  bf846b2800              mov      edi, 0x286b84                  
  0x0022144E  57                      push     edi                            
  0x0022144F  83c018                  add      eax, 0x18                      
  0x00221452  50                      push     eax                            
  0x00221453  e8da1b0000              call     0x223032                       ; -> sub_00223032
  0x00221458  a1946b2800              mov      eax, dword ptr [0x286b94]      
  0x0022145D  894608                  mov      dword ptr [esi + 8], eax       
  0x00221460  c605846b280030          mov      byte ptr [0x286b84], 0x30      
  0x00221467  c605856b280040          mov      byte ptr [0x286b85], 0x40      
  0x0022146E  c7058c6b2800e3122200    mov      dword ptr [0x286b8c], 0x2212e3 
  0x00221478  8935906b2800            mov      dword ptr [0x286b90], esi      
  0x0022147E  8b4608                  mov      eax, dword ptr [esi + 8]       
  0x00221481  6a50                    push     0x50                           
  0x00221483  a3946b2800              mov      dword ptr [0x286b94], eax      
  0x00221488  58                      pop      eax                            
  0x00221489  c7059c6b28000c6c2800    mov      dword ptr [0x286b9c], 0x286c0c 
  0x00221493  a3986b2800              mov      dword ptr [0x286b98], eax      
  0x00221498  c605a06b280002          mov      byte ptr [0x286ba0], 2         
  0x0022149F  c605a16b280001          mov      byte ptr [0x286ba1], 1         
  0x002214A6  881da26b2800            mov      byte ptr [0x286ba2], bl        
  0x002214AC  c605ac6b280080          mov      byte ptr [0x286bac], 0x80      
  0x002214B3  c605ad6b280006          mov      byte ptr [0x286bad], 6         
  0x002214BA  66c705ae6b28000002      mov      word ptr [0x286bae], 0x200     
  0x002214C3  66891db06b2800          mov      word ptr [0x286bb0], bx        
  0x002214CA  66a3b26b2800            mov      word ptr [0x286bb2], ax        
  0x002214D0  e8aaf3ffff              call     0x22087f                       ; -> sub_0022087F
  0x002214D5  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x002214D8  57                      push     edi                            
  0x002214D9  83c018                  add      eax, 0x18                      
  0x002214DC  50                      push     eax                            
  0x002214DD  e8501b0000              call     0x223032                       ; -> sub_00223032
  0x002214E2  5f                      pop      edi                            
                                        ; XREF: 0x002213BC (jump), 0x002213F9 (jump)
  0x002214E3  5e                      pop      esi                            
  0x002214E4  5b                      pop      ebx                            
  0x002214E5  c9                      leave                                   
  0x002214E6  c3                      ret                                     
; end of function
                                        ; XREF: 0x0021FABA (data_imm)
  0x002214E7  0fb605f86b2800          movzx    eax, byte ptr [0x286bf8]       
  0x002214EE  83e800                  sub      eax, 0                         
  0x002214F1  7440                    je       0x221533                       
  0x002214F3  48                      dec      eax                            
  0x002214F4  7425                    je       0x22151b                       
  0x002214F6  48                      dec      eax                            
  0x002214F7  7415                    je       0x22150e                       
  0x002214F9  48                      dec      eax                            
  0x002214FA  753c                    jne      0x221538                       
  0x002214FC  8b15006c2800            mov      edx, dword ptr [0x286c00]      
  0x00221502  b9846b2800              mov      ecx, 0x286b84                  
  0x00221507  e890feffff              call     0x22139c                       ; -> sub_0022139C
  0x0022150C  eb2a                    jmp      0x221538                       
                                        ; XREF: 0x002214F7 (cond_jump)
  0x0022150E  8b0d006c2800            mov      ecx, dword ptr [0x286c00]      
  0x00221514  e8cafcffff              call     0x2211e3                       ; -> sub_002211E3
  0x00221519  eb1d                    jmp      0x221538                       
                                        ; XREF: 0x002214F4 (cond_jump)
  0x0022151B  a1006c2800              mov      eax, dword ptr [0x286c00]      
  0x00221520  8b400c                  mov      eax, dword ptr [eax + 0xc]     
  0x00221523  68846b2800              push     0x286b84                       
  0x00221528  83c018                  add      eax, 0x18                      
  0x0022152B  50                      push     eax                            
  0x0022152C  e890190000              call     0x222ec1                       ; -> sub_00222EC1
  0x00221531  eb05                    jmp      0x221538                       
                                        ; XREF: 0x002214F1 (cond_jump)
  0x00221533  e896f4ffff              call     0x2209ce                       ; -> sub_002209CE
                                        ; XREF: 0x002214FA (cond_jump), 0x0022150C (jump), 0x00221519 (jump), 0x00221531 (jump)
  0x00221538  c21000                  ret      0x10                           

; ============================================================
; Function: sub_0022153B
; Start: 0x0022153B  End: 0x0022155D  Size: 34 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00220A35, sub_00220E01
; ============================================================
sub_0022153B:
  0x0022153B  8b4c2408                mov      ecx, dword ptr [esp + 8]       
  0x0022153F  33c0                    xor      eax, eax                       
  0x00221541  40                      inc      eax                            
  0x00221542  d3e0                    shl      eax, cl                        
  0x00221544  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00221548  094104                  or       dword ptr [ecx + 4], eax       
  0x0022154B  807c240c00              cmp      byte ptr [esp + 0xc], 0        
  0x00221550  7404                    je       0x221556                       
  0x00221552  0901                    or       dword ptr [ecx], eax           
  0x00221554  eb04                    jmp      0x22155a                       
                                        ; XREF: 0x00221550 (cond_jump)
  0x00221556  f7d0                    not      eax                            
  0x00221558  2101                    and      dword ptr [ecx], eax           
                                        ; XREF: 0x00221554 (jump)
  0x0022155A  c20c00                  ret      0xc                            
; end of function

; ============================================================
; Function: sub_0022155D
; Start: 0x0022155D  End: 0x00221562  Size: 5 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_000F8580
; ============================================================
sub_0022155D:
  0x0022155D  e95ee8ffff              jmp      0x21fdc0                       ; -> sub_0021FDC0
; end of function

; ============================================================
; Function: sub_00221562
; Start: 0x00221562  End: 0x00221584  Size: 34 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_000FF4F0
; ============================================================
sub_00221562:
  0x00221562  56                      push     esi                            
  0x00221563  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00221569  8b542408                mov      edx, dword ptr [esp + 8]       
  0x0022156D  8b32                    mov      esi, dword ptr [edx]           
  0x0022156F  83620400                and      dword ptr [edx + 4], 0         
  0x00221573  8ac8                    mov      cl, al                         
  0x00221575  897208                  mov      dword ptr [edx + 8], esi       
  0x00221578  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x0022157E  8bc6                    mov      eax, esi                       
  0x00221580  5e                      pop      esi                            
  0x00221581  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221584
; Start: 0x00221584  End: 0x002215F1  Size: 109 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_000FFB50
; ============================================================
sub_00221584:
  0x00221584  55                      push     ebp                            
  0x00221585  8bec                    mov      ebp, esp                       
  0x00221587  56                      push     esi                            
  0x00221588  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x0022158B  33c0                    xor      eax, eax                       
  0x0022158D  394604                  cmp      dword ptr [esi + 4], eax       
  0x00221590  750c                    jne      0x22159e                       
  0x00221592  8b4d0c                  mov      ecx, dword ptr [ebp + 0xc]     
  0x00221595  8901                    mov      dword ptr [ecx], eax           
  0x00221597  8b4d10                  mov      ecx, dword ptr [ebp + 0x10]    
  0x0022159A  8901                    mov      dword ptr [ecx], eax           
  0x0022159C  eb4e                    jmp      0x2215ec                       
                                        ; XREF: 0x00221590 (cond_jump)
  0x0022159E  53                      push     ebx                            
  0x0022159F  57                      push     edi                            
  0x002215A0  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x002215A6  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x002215A9  8b5d0c                  mov      ebx, dword ptr [ebp + 0xc]     
  0x002215AC  f7d1                    not      ecx                            
  0x002215AE  230e                    and      ecx, dword ptr [esi]           
  0x002215B0  890b                    mov      dword ptr [ebx], ecx           
  0x002215B2  8b16                    mov      edx, dword ptr [esi]           
  0x002215B4  8b4d10                  mov      ecx, dword ptr [ebp + 0x10]    
  0x002215B7  f7d2                    not      edx                            
  0x002215B9  235608                  and      edx, dword ptr [esi + 8]       
  0x002215BC  8911                    mov      dword ptr [ecx], edx           
  0x002215BE  8b7e04                  mov      edi, dword ptr [esi + 4]       
  0x002215C1  237e08                  and      edi, dword ptr [esi + 8]       
  0x002215C4  233e                    and      edi, dword ptr [esi]           
  0x002215C6  0bd7                    or       edx, edi                       
  0x002215C8  8911                    mov      dword ptr [ecx], edx           
  0x002215CA  093b                    or       dword ptr [ebx], edi           
  0x002215CC  8b0e                    mov      ecx, dword ptr [esi]           
  0x002215CE  83660400                and      dword ptr [esi + 4], 0         
  0x002215D2  894e08                  mov      dword ptr [esi + 8], ecx       
  0x002215D5  8ac8                    mov      cl, al                         
  0x002215D7  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x002215DD  8b03                    mov      eax, dword ptr [ebx]           
  0x002215DF  8b4d10                  mov      ecx, dword ptr [ebp + 0x10]    
  0x002215E2  0b01                    or       eax, dword ptr [ecx]           
  0x002215E4  5f                      pop      edi                            
  0x002215E5  f7d8                    neg      eax                            
  0x002215E7  1bc0                    sbb      eax, eax                       
  0x002215E9  f7d8                    neg      eax                            
  0x002215EB  5b                      pop      ebx                            
                                        ; XREF: 0x0022159C (jump)
  0x002215EC  5e                      pop      esi                            
  0x002215ED  5d                      pop      ebp                            
  0x002215EE  c20c00                  ret      0xc                            
; end of function

; ============================================================
; Function: sub_002215F1
; Start: 0x002215F1  End: 0x00221628  Size: 55 bytes
; Detection: call_target (confidence: 0.90)
; ============================================================
sub_002215F1:
  0x002215F1  53                      push     ebx                            
  0x002215F2  56                      push     esi                            
  0x002215F3  b804f92100              mov      eax, 0x21f904                  
  0x002215F8  57                      push     edi                            
  0x002215F9  8bf8                    mov      edi, eax                       
  0x002215FB  be0cf92100              mov      esi, 0x21f90c                  
  0x00221600  32db                    xor      bl, bl                         
  0x00221602  3bfe                    cmp      edi, esi                       
  0x00221604  c60200                  mov      byte ptr [edx], 0              
  0x00221607  7313                    jae      0x22161c                       
                                        ; XREF: 0x0022161A (cond_jump)
  0x00221609  8b38                    mov      edi, dword ptr [eax]           
  0x0022160B  85ff                    test     edi, edi                       
  0x0022160D  7406                    je       0x221615                       
  0x0022160F  380f                    cmp      byte ptr [edi], cl             
  0x00221611  740f                    je       0x221622                       
  0x00221613  fec3                    inc      bl                             
                                        ; XREF: 0x0022160D (cond_jump)
  0x00221615  83c004                  add      eax, 4                         
  0x00221618  3bc6                    cmp      eax, esi                       
  0x0022161A  72ed                    jb       0x221609                       
                                        ; XREF: 0x00221607 (cond_jump)
  0x0022161C  33c0                    xor      eax, eax                       
                                        ; XREF: 0x00221626 (jump)
  0x0022161E  5f                      pop      edi                            
  0x0022161F  5e                      pop      esi                            
  0x00221620  5b                      pop      ebx                            
  0x00221621  c3                      ret                                     
                                        ; XREF: 0x00221611 (cond_jump)
  0x00221622  881a                    mov      byte ptr [edx], bl             
  0x00221624  8b00                    mov      eax, dword ptr [eax]           
  0x00221626  ebf6                    jmp      0x22161e                       
; end of function

; ============================================================
; Function: sub_00221628
; Start: 0x00221628  End: 0x00221653  Size: 43 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00221653
; ============================================================
sub_00221628:
  0x00221628  b804f92100              mov      eax, 0x21f904                  
  0x0022162D  56                      push     esi                            
  0x0022162E  8bd0                    mov      edx, eax                       
  0x00221630  be0cf92100              mov      esi, 0x21f90c                  
  0x00221635  3bd6                    cmp      edx, esi                       
  0x00221637  7312                    jae      0x22164b                       
                                        ; XREF: 0x00221649 (cond_jump)
  0x00221639  8b10                    mov      edx, dword ptr [eax]           
  0x0022163B  85d2                    test     edx, edx                       
  0x0022163D  7405                    je       0x221644                       
  0x0022163F  394a04                  cmp      dword ptr [edx + 4], ecx       
  0x00221642  740b                    je       0x22164f                       
                                        ; XREF: 0x0022163D (cond_jump)
  0x00221644  83c004                  add      eax, 4                         
  0x00221647  3bc6                    cmp      eax, esi                       
  0x00221649  72ee                    jb       0x221639                       
                                        ; XREF: 0x00221637 (cond_jump)
  0x0022164B  33c0                    xor      eax, eax                       
  0x0022164D  5e                      pop      esi                            
  0x0022164E  c3                      ret                                     
                                        ; XREF: 0x00221642 (cond_jump)
  0x0022164F  8b00                    mov      eax, dword ptr [eax]           
  0x00221651  5e                      pop      esi                            
  0x00221652  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00221653
; Start: 0x00221653  End: 0x002216A9  Size: 86 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_000B2855, sub_00221628, sub_00223DA6
; Called by: sub_000FF430
; ============================================================
sub_00221653:
  0x00221653  55                      push     ebp                            
  0x00221654  8bec                    mov      ebp, esp                       
  0x00221656  51                      push     ecx                            
  0x00221657  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x0022165A  8365fc00                and      dword ptr [ebp - 4], 0         
  0x0022165E  e8c5ffffff              call     0x221628                       ; -> sub_00221628
  0x00221663  85c0                    test     eax, eax                       
  0x00221665  750b                    jne      0x221672                       
  0x00221667  6a57                    push     0x57                           
  0x00221669  e8e711e9ff              call     0xb2855                        ; -> sub_000B2855
  0x0022166E  33c0                    xor      eax, eax                       
  0x00221670  eb33                    jmp      0x2216a5                       
                                        ; XREF: 0x00221665 (cond_jump)
  0x00221672  56                      push     esi                            
  0x00221673  8b7514                  mov      esi, dword ptr [ebp + 0x14]    
  0x00221676  85f6                    test     esi, esi                       
  0x00221678  7503                    jne      0x22167d                       
  0x0022167A  8b7010                  mov      esi, dword ptr [eax + 0x10]    
                                        ; XREF: 0x00221678 (cond_jump)
  0x0022167D  837d1001                cmp      dword ptr [ebp + 0x10], 1      
  0x00221681  8b550c                  mov      edx, dword ptr [ebp + 0xc]     
  0x00221684  7503                    jne      0x221689                       
  0x00221686  83c210                  add      edx, 0x10                      
                                        ; XREF: 0x00221684 (cond_jump)
  0x00221689  56                      push     esi                            
  0x0022168A  8d4dfc                  lea      ecx, [ebp - 4]                 
  0x0022168D  51                      push     ecx                            
  0x0022168E  8bc8                    mov      ecx, eax                       
  0x00221690  e811270000              call     0x223da6                       ; -> sub_00223DA6
  0x00221695  837dfc00                cmp      dword ptr [ebp - 4], 0         
  0x00221699  5e                      pop      esi                            
  0x0022169A  7506                    jne      0x2216a2                       
  0x0022169C  50                      push     eax                            
  0x0022169D  e8b311e9ff              call     0xb2855                        ; -> sub_000B2855
                                        ; XREF: 0x0022169A (cond_jump)
  0x002216A2  8b45fc                  mov      eax, dword ptr [ebp - 4]       
                                        ; XREF: 0x00221670 (jump)
  0x002216A5  c9                      leave                                   
  0x002216A6  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_002216A9
; Start: 0x002216A9  End: 0x002216B5  Size: 12 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00223A12
; Called by: sub_000FF430, sub_000FFAF0
; ============================================================
sub_002216A9:
  0x002216A9  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x002216AD  e860230000              call     0x223a12                       ; -> sub_00223A12
  0x002216B2  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002216B5
; Start: 0x002216B5  End: 0x00221728  Size: 115 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_000FF520
; ============================================================
sub_002216B5:
  0x002216B5  53                      push     ebx                            
  0x002216B6  56                      push     esi                            
  0x002216B7  33db                    xor      ebx, ebx                       
  0x002216B9  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x002216BF  8b54240c                mov      edx, dword ptr [esp + 0xc]     
  0x002216C3  8b8aa3000000            mov      ecx, dword ptr [edx + 0xa3]    
  0x002216C9  f6412810                test     byte ptr [ecx + 0x28], 0x10    
  0x002216CD  7405                    je       0x2216d4                       
  0x002216CF  6a57                    push     0x57                           
  0x002216D1  5e                      pop      esi                            
  0x002216D2  eb45                    jmp      0x221719                       
                                        ; XREF: 0x002216CD (cond_jump)
  0x002216D4  8b0a                    mov      ecx, dword ptr [edx]           
  0x002216D6  85c9                    test     ecx, ecx                       
  0x002216D8  7406                    je       0x2216e0                       
  0x002216DA  f6410402                test     byte ptr [ecx + 4], 2          
  0x002216DE  7405                    je       0x2216e5                       
                                        ; XREF: 0x002216D8 (cond_jump)
  0x002216E0  bb8f040000              mov      ebx, 0x48f                     
                                        ; XREF: 0x002216DE (cond_jump)
  0x002216E5  8b4a08                  mov      ecx, dword ptr [edx + 8]       
  0x002216E8  57                      push     edi                            
  0x002216E9  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x002216ED  890f                    mov      dword ptr [edi], ecx           
  0x002216EF  80a2a2000000ef          and      byte ptr [edx + 0xa2], 0xef    
  0x002216F6  8b8aa3000000            mov      ecx, dword ptr [edx + 0xa3]    
  0x002216FC  8b4908                  mov      ecx, dword ptr [ecx + 8]       
  0x002216FF  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00221702  8d7214                  lea      esi, [edx + 0x14]              
  0x00221705  8bd1                    mov      edx, ecx                       
  0x00221707  83c704                  add      edi, 4                         
  0x0022170A  c1e902                  shr      ecx, 2                         
  0x0022170D  f3a5                    rep movsd dword ptr es:[edi], dword ptr [esi] 
  0x0022170F  8bca                    mov      ecx, edx                       
  0x00221711  83e103                  and      ecx, 3                         
  0x00221714  f3a4                    rep movsb byte ptr es:[edi], byte ptr [esi] 
  0x00221716  8bf3                    mov      esi, ebx                       
  0x00221718  5f                      pop      edi                            
                                        ; XREF: 0x002216D2 (jump)
  0x00221719  8ac8                    mov      cl, al                         
  0x0022171B  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00221721  8bc6                    mov      eax, esi                       
  0x00221723  5e                      pop      esi                            
  0x00221724  5b                      pop      ebx                            
  0x00221725  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00221728
; Start: 0x00221728  End: 0x0022175B  Size: 51 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00223AA6
; Called by: sub_000FF520
; ============================================================
sub_00221728:
  0x00221728  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0022172C  8d81a3000000            lea      eax, [ecx + 0xa3]              
  0x00221732  8b10                    mov      edx, dword ptr [eax]           
  0x00221734  f6422820                test     byte ptr [edx + 0x28], 0x20    
  0x00221738  7405                    je       0x22173f                       
  0x0022173A  6a57                    push     0x57                           
  0x0022173C  58                      pop      eax                            
  0x0022173D  eb19                    jmp      0x221758                       
                                        ; XREF: 0x00221738 (cond_jump)
  0x0022173F  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00221743  c6424000                mov      byte ptr [edx + 0x40], 0       
  0x00221747  8b00                    mov      eax, dword ptr [eax]           
  0x00221749  8b400c                  mov      eax, dword ptr [eax + 0xc]     
  0x0022174C  8a00                    mov      al, byte ptr [eax]             
  0x0022174E  0402                    add      al, 2                          
  0x00221750  884241                  mov      byte ptr [edx + 0x41], al      
  0x00221753  e84e230000              call     0x223aa6                       ; -> sub_00223AA6
                                        ; XREF: 0x0022173D (jump)
  0x00221758  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_0022175B
; Start: 0x0022175B  End: 0x002217C3  Size: 104 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FADB, sub_0021FE39, sub_0021FEB6
; ============================================================
sub_0022175B:
  0x0022175B  53                      push     ebx                            
  0x0022175C  56                      push     esi                            
  0x0022175D  57                      push     edi                            
  0x0022175E  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x00221762  8d7703                  lea      esi, [edi + 3]                 
  0x00221765  83e6fc                  and      esi, 0xfffffffc                
  0x00221768  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x0022176E  3935d8f92100            cmp      dword ptr [0x21f9d8], esi      
  0x00221774  8ac8                    mov      cl, al                         
  0x00221776  7230                    jb       0x2217a8                       
  0x00221778  bb00100080              mov      ebx, 0x80001000                
  0x0022177D  2b1dd8f92100            sub      ebx, dword ptr [0x21f9d8]      
  0x00221783  2935d8f92100            sub      dword ptr [0x21f9d8], esi      
  0x00221789  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x0022178F  8bce                    mov      ecx, esi                       
  0x00221791  8bd1                    mov      edx, ecx                       
  0x00221793  c1e902                  shr      ecx, 2                         
  0x00221796  b8cccccccc              mov      eax, 0xcccccccc                
  0x0022179B  8bfb                    mov      edi, ebx                       
  0x0022179D  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x0022179F  8bca                    mov      ecx, edx                       
  0x002217A1  83e103                  and      ecx, 3                         
  0x002217A4  f3aa                    rep stosb byte ptr es:[edi], al          
  0x002217A6  eb13                    jmp      0x2217bb                       
                                        ; XREF: 0x00221776 (cond_jump)
  0x002217A8  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x002217AE  ff742414                push     dword ptr [esp + 0x14]         
  0x002217B2  57                      push     edi                            
  0x002217B3  ff156c5b2200            call     dword ptr [0x225b6c]           ; -> xbox_ExAllocatePoolWithTag
  0x002217B9  8bd8                    mov      ebx, eax                       
                                        ; XREF: 0x002217A6 (jump)
  0x002217BB  5f                      pop      edi                            
  0x002217BC  5e                      pop      esi                            
  0x002217BD  8bc3                    mov      eax, ebx                       
  0x002217BF  5b                      pop      ebx                            
  0x002217C0  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_002217C3
; Start: 0x002217C3  End: 0x002217D6  Size: 19 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00222EC1
; Called by: sub_002236AB
; ============================================================
sub_002217C3:
  0x002217C3  8b410c                  mov      eax, dword ptr [ecx + 0xc]     
  0x002217C6  ff742404                push     dword ptr [esp + 4]            
  0x002217CA  83c018                  add      eax, 0x18                      
  0x002217CD  50                      push     eax                            
  0x002217CE  e8ee160000              call     0x222ec1                       ; -> sub_00222EC1
  0x002217D3  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002217D6
; Start: 0x002217D6  End: 0x002217DA  Size: 4 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00221CE6, sub_00221E4D, sub_00221FFE, sub_00222107, sub_00222280, sub_002224C7, sub_0022259A, sub_00222771
; ============================================================
sub_002217D6:
  0x002217D6  8b411c                  mov      eax, dword ptr [ecx + 0x1c]    
  0x002217D9  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002217DA
; Start: 0x002217DA  End: 0x002217E7  Size: 13 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00223262, sub_00223BD4
; ============================================================
sub_002217DA:
  0x002217DA  8b542404                mov      edx, dword ptr [esp + 4]       
  0x002217DE  8b411c                  mov      eax, dword ptr [ecx + 0x1c]    
  0x002217E1  89511c                  mov      dword ptr [ecx + 0x1c], edx    
  0x002217E4  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002217E7
; Start: 0x002217E7  End: 0x002217EB  Size: 4 bytes
; Detection: call_target (confidence: 0.90)
; ============================================================
sub_002217E7:
  0x002217E7  8a4102                  mov      al, byte ptr [ecx + 2]         
  0x002217EA  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002217EB
; Start: 0x002217EB  End: 0x002217F5  Size: 10 bytes
; Detection: call_target (confidence: 0.90)
; ============================================================
sub_002217EB:
  0x002217EB  8a442404                mov      al, byte ptr [esp + 4]         
  0x002217EF  884107                  mov      byte ptr [ecx + 7], al         
  0x002217F2  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002217F5
; Start: 0x002217F5  End: 0x00221863  Size: 110 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00223607, sub_00223AA6, sub_00223DA6
; ============================================================
sub_002217F5:
  0x002217F5  8b442404                mov      eax, dword ptr [esp + 4]       
  0x002217F9  b90f0000c0              mov      ecx, 0xc000000f                
  0x002217FE  3bc1                    cmp      eax, ecx                       
  0x00221800  7f40                    jg       0x221842                       
  0x00221802  7437                    je       0x22183b                       
  0x00221804  3d00000080              cmp      eax, 0x80000000                
  0x00221809  741c                    je       0x221827                       
  0x0022180B  3d00010080              cmp      eax, 0x80000100                
  0x00221810  7424                    je       0x221836                       
  0x00221812  3d00080080              cmp      eax, 0x80000800                
  0x00221817  7416                    je       0x22182f                       
  0x00221819  3dffffffbf              cmp      eax, 0xbfffffff                
  0x0022181E  7e34                    jle      0x221854                       
  0x00221820  3d0e0000c0              cmp      eax, 0xc000000e                
  0x00221825  7f2d                    jg       0x221854                       
                                        ; XREF: 0x00221809 (cond_jump), 0x00221847 (cond_jump)
  0x00221827  b85d040000              mov      eax, 0x45d                     
                                        ; XREF: 0x00221834 (jump), 0x00221839 (jump), 0x00221840 (jump), 0x0022185D (jump), 0x00221861 (jump)
  0x0022182C  c20400                  ret      4                              
                                        ; XREF: 0x00221817 (cond_jump)
  0x0022182F  b8aa050000              mov      eax, 0x5aa                     
  0x00221834  ebf6                    jmp      0x22182c                       
                                        ; XREF: 0x00221810 (cond_jump)
  0x00221836  6a0e                    push     0xe                            
                                        ; XREF: 0x00221856 (jump)
  0x00221838  58                      pop      eax                            
  0x00221839  ebf1                    jmp      0x22182c                       
                                        ; XREF: 0x00221802 (cond_jump)
  0x0022183B  b8c7040000              mov      eax, 0x4c7                     
  0x00221840  ebea                    jmp      0x22182c                       
                                        ; XREF: 0x00221800 (cond_jump)
  0x00221842  3d100000c0              cmp      eax, 0xc0000010                
  0x00221847  74de                    je       0x221827                       
  0x00221849  85c0                    test     eax, eax                       
  0x0022184B  7412                    je       0x22185f                       
  0x0022184D  3d00000040              cmp      eax, 0x40000000                
  0x00221852  7404                    je       0x221858                       
                                        ; XREF: 0x0022181E (cond_jump), 0x00221825 (cond_jump)
  0x00221854  6a1f                    push     0x1f                           
  0x00221856  ebe0                    jmp      0x221838                       
                                        ; XREF: 0x00221852 (cond_jump)
  0x00221858  b8e5030000              mov      eax, 0x3e5                     
  0x0022185D  ebcd                    jmp      0x22182c                       
                                        ; XREF: 0x0022184B (cond_jump)
  0x0022185F  33c0                    xor      eax, eax                       
  0x00221861  ebc9                    jmp      0x22182c                       
; end of function

; ============================================================
; Function: sub_00221863
; Start: 0x00221863  End: 0x00221869  Size: 6 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00223BD4
; ============================================================
sub_00221863:
  0x00221863  a15c6c2800              mov      eax, dword ptr [0x286c5c]      
  0x00221868  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00221869
; Start: 0x00221869  End: 0x002218DF  Size: 118 bytes
; Detection: prologue (confidence: 0.95)
; ============================================================
sub_00221869:
  0x00221869  55                      push     ebp                            
  0x0022186A  8bec                    mov      ebp, esp                       
  0x0022186C  8b0d5c6c2800            mov      ecx, dword ptr [0x286c5c]      
  0x00221872  53                      push     ebx                            
  0x00221873  56                      push     esi                            
  0x00221874  0fb7350e6c2800          movzx    esi, word ptr [0x286c0e]       
  0x0022187B  57                      push     edi                            
  0x0022187C  81c60c6c2800            add      esi, 0x286c0c                  
  0x00221882  33ff                    xor      edi, edi                       
                                        ; XREF: 0x002218D0 (cond_jump)
  0x00221884  8a11                    mov      dl, byte ptr [ecx]             
  0x00221886  84d2                    test     dl, dl                         
  0x00221888  744c                    je       0x2218d6                       
  0x0022188A  0fb6c2                  movzx    eax, dl                        
  0x0022188D  03c8                    add      ecx, eax                       
  0x0022188F  3bce                    cmp      ecx, esi                       
  0x00221891  7343                    jae      0x2218d6                       
  0x00221893  8a4101                  mov      al, byte ptr [ecx + 1]         
  0x00221896  3c05                    cmp      al, 5                          
  0x00221898  7534                    jne      0x2218ce                       
  0x0022189A  8a5103                  mov      dl, byte ptr [ecx + 3]         
  0x0022189D  80e203                  and      dl, 3                          
  0x002218A0  3a5508                  cmp      dl, byte ptr [ebp + 8]         
  0x002218A3  7529                    jne      0x2218ce                       
  0x002218A5  807d0800                cmp      byte ptr [ebp + 8], 0          
  0x002218A9  7423                    je       0x2218ce                       
  0x002218AB  33d2                    xor      edx, edx                       
  0x002218AD  8a5102                  mov      dl, byte ptr [ecx + 2]         
  0x002218B0  33db                    xor      ebx, ebx                       
  0x002218B2  c1ea07                  shr      edx, 7                         
  0x002218B5  f7d2                    not      edx                            
  0x002218B7  83e201                  and      edx, 1                         
  0x002218BA  385d0c                  cmp      byte ptr [ebp + 0xc], bl       
  0x002218BD  0f94c3                  sete     bl                             
  0x002218C0  3bd3                    cmp      edx, ebx                       
  0x002218C2  750a                    jne      0x2218ce                       
  0x002218C4  8a5510                  mov      dl, byte ptr [ebp + 0x10]      
  0x002218C7  fe4d10                  dec      byte ptr [ebp + 0x10]          
  0x002218CA  84d2                    test     dl, dl                         
  0x002218CC  7406                    je       0x2218d4                       
                                        ; XREF: 0x00221898 (cond_jump), 0x002218A3 (cond_jump), 0x002218A9 (cond_jump), 0x002218C2 (cond_jump)
  0x002218CE  3c04                    cmp      al, 4                          
  0x002218D0  75b2                    jne      0x221884                       
  0x002218D2  eb02                    jmp      0x2218d6                       
                                        ; XREF: 0x002218CC (cond_jump)
  0x002218D4  8bf9                    mov      edi, ecx                       
                                        ; XREF: 0x00221888 (cond_jump), 0x00221891 (cond_jump), 0x002218D2 (jump)
  0x002218D6  8bc7                    mov      eax, edi                       
  0x002218D8  5f                      pop      edi                            
  0x002218D9  5e                      pop      esi                            
  0x002218DA  5b                      pop      ebx                            
  0x002218DB  5d                      pop      ebp                            
  0x002218DC  c20c00                  ret      0xc                            
; end of function

; ============================================================
; Function: sub_002218DF
; Start: 0x002218DF  End: 0x002218E3  Size: 4 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00223285
; ============================================================
sub_002218DF:
  0x002218DF  8b4114                  mov      eax, dword ptr [ecx + 0x14]    
  0x002218E2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002218E3
; Start: 0x002218E3  End: 0x00221969  Size: 134 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220776, sub_00223032, sub_002231A4
; Called by: sub_00221B1F
; ============================================================
sub_002218E3:
  0x002218E3  53                      push     ebx                            
  0x002218E4  57                      push     edi                            
  0x002218E5  8bf9                    mov      edi, ecx                       
  0x002218E7  33db                    xor      ebx, ebx                       
  0x002218E9  803f05                  cmp      byte ptr [edi], 5              
  0x002218EC  7523                    jne      0x221911                       
  0x002218EE  e883eeffff              call     0x220776                       ; -> sub_00220776
  0x002218F3  8bd8                    mov      ebx, eax                       
  0x002218F5  8b4308                  mov      eax, dword ptr [ebx + 8]       
  0x002218F8  85c0                    test     eax, eax                       
  0x002218FA  7415                    je       0x221911                       
  0x002218FC  894708                  mov      dword ptr [edi + 8], eax       
  0x002218FF  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x00221903  83600400                and      dword ptr [eax + 4], 0         
  0x00221907  50                      push     eax                            
  0x00221908  e897180000              call     0x2231a4                       ; -> sub_002231A4
  0x0022190D  33c0                    xor      eax, eax                       
  0x0022190F  eb53                    jmp      0x221964                       
                                        ; XREF: 0x002218EC (cond_jump), 0x002218FA (cond_jump)
  0x00221911  8a4705                  mov      al, byte ptr [edi + 5]         
  0x00221914  56                      push     esi                            
  0x00221915  8b742410                mov      esi, dword ptr [esp + 0x10]    
  0x00221919  884614                  mov      byte ptr [esi + 0x14], al      
  0x0022191C  c6461500                mov      byte ptr [esi + 0x15], 0       
  0x00221920  c6461600                mov      byte ptr [esi + 0x16], 0       
  0x00221924  660fb64706              movzx    ax, byte ptr [edi + 6]         
  0x00221929  6689461c                mov      word ptr [esi + 0x1c], ax      
  0x0022192D  8a4704                  mov      al, byte ptr [edi + 4]         
  0x00221930  83661800                and      dword ptr [esi + 0x18], 0      
  0x00221934  c0e807                  shr      al, 7                          
  0x00221937  88461e                  mov      byte ptr [esi + 0x1e], al      
  0x0022193A  c6460102                mov      byte ptr [esi + 1], 2          
  0x0022193E  8b470c                  mov      eax, dword ptr [edi + 0xc]     
  0x00221941  56                      push     esi                            
  0x00221942  83c018                  add      eax, 0x18                      
  0x00221945  50                      push     eax                            
  0x00221946  e8e7160000              call     0x223032                       ; -> sub_00223032
  0x0022194B  85c0                    test     eax, eax                       
  0x0022194D  7c10                    jl       0x22195f                       
  0x0022194F  85db                    test     ebx, ebx                       
  0x00221951  8b4e10                  mov      ecx, dword ptr [esi + 0x10]    
  0x00221954  894f08                  mov      dword ptr [edi + 8], ecx       
  0x00221957  7406                    je       0x22195f                       
  0x00221959  8b4e10                  mov      ecx, dword ptr [esi + 0x10]    
  0x0022195C  894b08                  mov      dword ptr [ebx + 8], ecx       
                                        ; XREF: 0x0022194D (cond_jump), 0x00221957 (cond_jump)
  0x0022195F  83661000                and      dword ptr [esi + 0x10], 0      
  0x00221963  5e                      pop      esi                            
                                        ; XREF: 0x0022190F (jump)
  0x00221964  5f                      pop      edi                            
  0x00221965  5b                      pop      ebx                            
  0x00221966  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221969
; Start: 0x00221969  End: 0x002219D5  Size: 108 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220776, sub_0022078D, sub_002207A4, sub_00223032, sub_002231A4
; Called by: sub_00221B1F
; ============================================================
sub_00221969:
  0x00221969  56                      push     esi                            
  0x0022196A  8bf1                    mov      esi, ecx                       
  0x0022196C  57                      push     edi                            
  0x0022196D  8b7e08                  mov      edi, dword ptr [esi + 8]       
  0x00221970  83660800                and      dword ptr [esi + 8], 0         
  0x00221974  803e05                  cmp      byte ptr [esi], 5              
  0x00221977  7529                    jne      0x2219a2                       
  0x00221979  e8f8edffff              call     0x220776                       ; -> sub_00220776
  0x0022197E  8bc8                    mov      ecx, eax                       
  0x00221980  e808eeffff              call     0x22078d                       ; -> sub_0022078D
  0x00221985  eb0c                    jmp      0x221993                       
                                        ; XREF: 0x00221995 (cond_jump)
  0x00221987  397808                  cmp      dword ptr [eax + 8], edi       
  0x0022198A  7437                    je       0x2219c3                       
  0x0022198C  8bc8                    mov      ecx, eax                       
  0x0022198E  e811eeffff              call     0x2207a4                       ; -> sub_002207A4
                                        ; XREF: 0x00221985 (jump)
  0x00221993  85c0                    test     eax, eax                       
  0x00221995  75f0                    jne      0x221987                       
  0x00221997  8bce                    mov      ecx, esi                       
  0x00221999  e8d8edffff              call     0x220776                       ; -> sub_00220776
  0x0022199E  83600800                and      dword ptr [eax + 8], 0         
                                        ; XREF: 0x00221977 (cond_jump)
  0x002219A2  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x002219A6  83601800                and      dword ptr [eax + 0x18], 0      
  0x002219AA  50                      push     eax                            
  0x002219AB  c6400143                mov      byte ptr [eax + 1], 0x43       
  0x002219AF  897810                  mov      dword ptr [eax + 0x10], edi    
  0x002219B2  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x002219B5  83c018                  add      eax, 0x18                      
  0x002219B8  50                      push     eax                            
  0x002219B9  e874160000              call     0x223032                       ; -> sub_00223032
                                        ; XREF: 0x002219D3 (jump)
  0x002219BE  5f                      pop      edi                            
  0x002219BF  5e                      pop      esi                            
  0x002219C0  c20400                  ret      4                              
                                        ; XREF: 0x0022198A (cond_jump)
  0x002219C3  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x002219C7  83600400                and      dword ptr [eax + 4], 0         
  0x002219CB  50                      push     eax                            
  0x002219CC  e8d3170000              call     0x2231a4                       ; -> sub_002231A4
  0x002219D1  33c0                    xor      eax, eax                       
  0x002219D3  ebe9                    jmp      0x2219be                       
; end of function

; ============================================================
; Function: sub_002219D5
; Start: 0x002219D5  End: 0x00221A06  Size: 49 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022078D, sub_002207A4
; Called by: sub_00220BAC
; ============================================================
sub_002219D5:
  0x002219D5  e8b3edffff              call     0x22078d                       ; -> sub_0022078D
  0x002219DA  85c0                    test     eax, eax                       
  0x002219DC  7425                    je       0x221a03                       
  0x002219DE  56                      push     esi                            
  0x002219DF  57                      push     edi                            
  0x002219E0  0fb67c240c              movzx    edi, byte ptr [esp + 0xc]      
  0x002219E5  be7fffffff              mov      esi, 0xffffff7f                
  0x002219EA  23fe                    and      edi, esi                       
                                        ; XREF: 0x002219FF (cond_jump)
  0x002219EC  0fb64804                movzx    ecx, byte ptr [eax + 4]        
  0x002219F0  23ce                    and      ecx, esi                       
  0x002219F2  3bcf                    cmp      ecx, edi                       
  0x002219F4  740b                    je       0x221a01                       
  0x002219F6  8bc8                    mov      ecx, eax                       
  0x002219F8  e8a7edffff              call     0x2207a4                       ; -> sub_002207A4
  0x002219FD  85c0                    test     eax, eax                       
  0x002219FF  75eb                    jne      0x2219ec                       
                                        ; XREF: 0x002219F4 (cond_jump)
  0x00221A01  5f                      pop      edi                            
  0x00221A02  5e                      pop      esi                            
                                        ; XREF: 0x002219DC (cond_jump)
  0x00221A03  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221A06
; Start: 0x00221A06  End: 0x00221A4E  Size: 72 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022078D, sub_002207A4
; Called by: sub_002207BB, sub_0022109C
; ============================================================
sub_00221A06:
  0x00221A06  8b442404                mov      eax, dword ptr [esp + 4]       
  0x00221A0A  53                      push     ebx                            
  0x00221A0B  8bd8                    mov      ebx, eax                       
  0x00221A0D  2b1d606c2800            sub      ebx, dword ptr [0x286c60]      
  0x00221A13  56                      push     esi                            
  0x00221A14  8bf1                    mov      esi, ecx                       
  0x00221A16  c6400380                mov      byte ptr [eax + 3], 0x80       
  0x00221A1A  2b0d606c2800            sub      ecx, dword ptr [0x286c60]      
  0x00221A20  c1fb05                  sar      ebx, 5                         
  0x00221A23  c1f905                  sar      ecx, 5                         
  0x00221A26  884801                  mov      byte ptr [eax + 1], cl         
  0x00221A29  8bce                    mov      ecx, esi                       
  0x00221A2B  e85dedffff              call     0x22078d                       ; -> sub_0022078D
  0x00221A30  85c0                    test     eax, eax                       
  0x00221A32  750c                    jne      0x221a40                       
  0x00221A34  885e02                  mov      byte ptr [esi + 2], bl         
  0x00221A37  eb10                    jmp      0x221a49                       
                                        ; XREF: 0x00221A44 (cond_jump)
  0x00221A39  8bc8                    mov      ecx, eax                       
  0x00221A3B  e864edffff              call     0x2207a4                       ; -> sub_002207A4
                                        ; XREF: 0x00221A32 (cond_jump)
  0x00221A40  80780380                cmp      byte ptr [eax + 3], 0x80       
  0x00221A44  75f3                    jne      0x221a39                       
  0x00221A46  885803                  mov      byte ptr [eax + 3], bl         
                                        ; XREF: 0x00221A37 (jump)
  0x00221A49  5e                      pop      esi                            
  0x00221A4A  5b                      pop      ebx                            
  0x00221A4B  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221A4E
; Start: 0x00221A4E  End: 0x00221AAA  Size: 92 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022078D, sub_002207A4
; Called by: sub_00220A35, sub_00220BAC, sub_00220C68, sub_00220E01
; ============================================================
sub_00221A4E:
  0x00221A4E  53                      push     ebx                            
  0x00221A4F  55                      push     ebp                            
  0x00221A50  56                      push     esi                            
  0x00221A51  57                      push     edi                            
  0x00221A52  8be9                    mov      ebp, ecx                       
  0x00221A54  e834edffff              call     0x22078d                       ; -> sub_0022078D
  0x00221A59  8b742414                mov      esi, dword ptr [esp + 0x14]    
  0x00221A5D  8bf8                    mov      edi, eax                       
  0x00221A5F  3bfe                    cmp      edi, esi                       
  0x00221A61  b301                    mov      bl, 1                          
  0x00221A63  750e                    jne      0x221a73                       
  0x00221A65  8a4603                  mov      al, byte ptr [esi + 3]         
  0x00221A68  3c80                    cmp      al, 0x80                       
  0x00221A6A  884502                  mov      byte ptr [ebp + 2], al         
  0x00221A6D  752a                    jne      0x221a99                       
  0x00221A6F  32db                    xor      bl, bl                         
  0x00221A71  eb26                    jmp      0x221a99                       
                                        ; XREF: 0x00221A63 (cond_jump)
  0x00221A73  85ff                    test     edi, edi                       
  0x00221A75  7422                    je       0x221a99                       
                                        ; XREF: 0x00221A8D (cond_jump)
  0x00221A77  8bcf                    mov      ecx, edi                       
  0x00221A79  e826edffff              call     0x2207a4                       ; -> sub_002207A4
  0x00221A7E  3bc6                    cmp      eax, esi                       
  0x00221A80  740d                    je       0x221a8f                       
  0x00221A82  8bcf                    mov      ecx, edi                       
  0x00221A84  e81bedffff              call     0x2207a4                       ; -> sub_002207A4
  0x00221A89  8bf8                    mov      edi, eax                       
  0x00221A8B  85ff                    test     edi, edi                       
  0x00221A8D  75e8                    jne      0x221a77                       
                                        ; XREF: 0x00221A80 (cond_jump)
  0x00221A8F  85ff                    test     edi, edi                       
  0x00221A91  7406                    je       0x221a99                       
  0x00221A93  8a4603                  mov      al, byte ptr [esi + 3]         
  0x00221A96  884703                  mov      byte ptr [edi + 3], al         
                                        ; XREF: 0x00221A6D (cond_jump), 0x00221A71 (jump), 0x00221A75 (cond_jump), 0x00221A91 (cond_jump)
  0x00221A99  5f                      pop      edi                            
  0x00221A9A  c6460380                mov      byte ptr [esi + 3], 0x80       
  0x00221A9E  c6460180                mov      byte ptr [esi + 1], 0x80       
  0x00221AA2  5e                      pop      esi                            
  0x00221AA3  5d                      pop      ebp                            
  0x00221AA4  8ac3                    mov      al, bl                         
  0x00221AA6  5b                      pop      ebx                            
  0x00221AA7  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221AAA
; Start: 0x00221AAA  End: 0x00221B1F  Size: 117 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00221C09, sub_00221C4B
; ============================================================
sub_00221AAA:
  0x00221AAA  8b442404                mov      eax, dword ptr [esp + 4]       
  0x00221AAE  8b5004                  mov      edx, dword ptr [eax + 4]       
  0x00221AB1  0fb65204                movzx    edx, byte ptr [edx + 4]        
  0x00221AB5  83e27f                  and      edx, 0x7f                      
  0x00221AB8  4a                      dec      edx                            
  0x00221AB9  83fa04                  cmp      edx, 4                         
  0x00221ABC  895114                  mov      dword ptr [ecx + 0x14], edx    
  0x00221ABF  7c09                    jl       0x221aca                       
  0x00221AC1  c7411420000000          mov      dword ptr [ecx + 0x14], 0x20   
  0x00221AC8  eb52                    jmp      0x221b1c                       
                                        ; XREF: 0x00221ABF (cond_jump)
  0x00221ACA  56                      push     esi                            
  0x00221ACB  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00221ACF  83f202                  xor      edx, 2                         
  0x00221AD2  895114                  mov      dword ptr [ecx + 0x14], edx    
  0x00221AD5  57                      push     edi                            
  0x00221AD6  8b3cb0                  mov      edi, dword ptr [eax + esi*4]   
  0x00221AD9  803f01                  cmp      byte ptr [edi], 1              
  0x00221ADC  751c                    jne      0x221afa                       
  0x00221ADE  83fe01                  cmp      esi, 1                         
  0x00221AE1  7437                    je       0x221b1a                       
  0x00221AE3  803d24f9210000          cmp      byte ptr [0x21f924], 0         
  0x00221AEA  7405                    je       0x221af1                       
  0x00221AEC  83fe02                  cmp      esi, 2                         
  0x00221AEF  7429                    je       0x221b1a                       
                                        ; XREF: 0x00221AEA (cond_jump), 0x00221B0D (cond_jump)
  0x00221AF1  c7411420000000          mov      dword ptr [ecx + 0x14], 0x20   
  0x00221AF8  eb20                    jmp      0x221b1a                       
                                        ; XREF: 0x00221ADC (cond_jump)
  0x00221AFA  83fe01                  cmp      esi, 1                         
  0x00221AFD  761b                    jbe      0x221b1a                       
  0x00221AFF  8b4008                  mov      eax, dword ptr [eax + 8]       
  0x00221B02  0fb64004                movzx    eax, byte ptr [eax + 4]        
  0x00221B06  83e07f                  and      eax, 0x7f                      
  0x00221B09  48                      dec      eax                            
  0x00221B0A  83f803                  cmp      eax, 3                         
  0x00221B0D  77e2                    ja       0x221af1                       
  0x00221B0F  83f802                  cmp      eax, 2                         
  0x00221B12  7506                    jne      0x221b1a                       
  0x00221B14  83c210                  add      edx, 0x10                      
  0x00221B17  895114                  mov      dword ptr [ecx + 0x14], edx    
                                        ; XREF: 0x00221AE1 (cond_jump), 0x00221AEF (cond_jump), 0x00221AF8 (jump), 0x00221AFD (cond_jump), 0x00221B12 (cond_jump)
  0x00221B1A  5f                      pop      edi                            
  0x00221B1B  5e                      pop      esi                            
                                        ; XREF: 0x00221AC8 (jump)
  0x00221B1C  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00221B1F
; Start: 0x00221B1F  End: 0x00221C09  Size: 234 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002218E3, sub_00221969, sub_00223032
; Called by: sub_00221CE6, sub_00221E4D, sub_00221FFE, sub_002220E5, sub_00222107, sub_002224C7, sub_00222771, sub_002232EF, sub_0022339A, sub_0022394C ... (+3 more)
; ============================================================
sub_00221B1F:
  0x00221B1F  55                      push     ebp                            
  0x00221B20  8bec                    mov      ebp, esp                       
  0x00221B22  83ec14                  sub      esp, 0x14                      
  0x00221B25  53                      push     ebx                            
  0x00221B26  56                      push     esi                            
  0x00221B27  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x00221B2A  8a4601                  mov      al, byte ptr [esi + 1]         
  0x00221B2D  33db                    xor      ebx, ebx                       
  0x00221B2F  a840                    test     al, 0x40                       
  0x00221B31  885dff                  mov      byte ptr [ebp - 1], bl         
  0x00221B34  7429                    je       0x221b5f                       
  0x00221B36  395e08                  cmp      dword ptr [esi + 8], ebx       
  0x00221B39  7524                    jne      0x221b5f                       
  0x00221B3B  8d55f4                  lea      edx, [ebp - 0xc]               
  0x00221B3E  8955f8                  mov      dword ptr [ebp - 8], edx       
  0x00221B41  8955f4                  mov      dword ptr [ebp - 0xc], edx     
  0x00221B44  8d55ec                  lea      edx, [ebp - 0x14]              
  0x00221B47  c645ff01                mov      byte ptr [ebp - 1], 1          
  0x00221B4B  885dec                  mov      byte ptr [ebp - 0x14], bl      
  0x00221B4E  c645ee04                mov      byte ptr [ebp - 0x12], 4       
  0x00221B52  895df0                  mov      dword ptr [ebp - 0x10], ebx    
  0x00221B55  c746089a362200          mov      dword ptr [esi + 8], 0x22369a  
  0x00221B5C  89560c                  mov      dword ptr [esi + 0xc], edx     
                                        ; XREF: 0x00221B34 (cond_jump), 0x00221B39 (cond_jump)
  0x00221B5F  0fb6c0                  movzx    eax, al                        
  0x00221B62  48                      dec      eax                            
  0x00221B63  48                      dec      eax                            
  0x00221B64  744f                    je       0x221bb5                       
  0x00221B66  83e807                  sub      eax, 7                         
  0x00221B69  7442                    je       0x221bad                       
  0x00221B6B  83e837                  sub      eax, 0x37                      
  0x00221B6E  7427                    je       0x221b97                       
  0x00221B70  83e803                  sub      eax, 3                         
  0x00221B73  741a                    je       0x221b8f                       
  0x00221B75  83e83f                  sub      eax, 0x3f                      
  0x00221B78  740d                    je       0x221b87                       
  0x00221B7A  83e841                  sub      eax, 0x41                      
  0x00221B7D  754b                    jne      0x221bca                       
  0x00221B7F  56                      push     esi                            
  0x00221B80  e8e4fdffff              call     0x221969                       ; -> sub_00221969
  0x00221B85  eb50                    jmp      0x221bd7                       
                                        ; XREF: 0x00221B78 (cond_jump)
  0x00221B87  56                      push     esi                            
  0x00221B88  e856fdffff              call     0x2218e3                       ; -> sub_002218E3
  0x00221B8D  eb48                    jmp      0x221bd7                       
                                        ; XREF: 0x00221B73 (cond_jump)
  0x00221B8F  8d4118                  lea      eax, [ecx + 0x18]              
  0x00221B92  894618                  mov      dword ptr [esi + 0x18], eax    
  0x00221B95  eb33                    jmp      0x221bca                       
                                        ; XREF: 0x00221B6E (cond_jump)
  0x00221B97  395e10                  cmp      dword ptr [esi + 0x10], ebx    
  0x00221B9A  7506                    jne      0x221ba2                       
  0x00221B9C  8b4108                  mov      eax, dword ptr [ecx + 8]       
  0x00221B9F  894610                  mov      dword ptr [esi + 0x10], eax    
                                        ; XREF: 0x00221B9A (cond_jump)
  0x00221BA2  807e2909                cmp      byte ptr [esi + 0x29], 9       
  0x00221BA6  7522                    jne      0x221bca                       
  0x00221BA8  895918                  mov      dword ptr [ecx + 0x18], ebx    
  0x00221BAB  eb1d                    jmp      0x221bca                       
                                        ; XREF: 0x00221B69 (cond_jump)
  0x00221BAD  8a4105                  mov      al, byte ptr [ecx + 5]         
  0x00221BB0  884614                  mov      byte ptr [esi + 0x14], al      
  0x00221BB3  eb15                    jmp      0x221bca                       
                                        ; XREF: 0x00221B64 (cond_jump)
  0x00221BB5  8a4105                  mov      al, byte ptr [ecx + 5]         
  0x00221BB8  884614                  mov      byte ptr [esi + 0x14], al      
  0x00221BBB  8d4118                  lea      eax, [ecx + 0x18]              
  0x00221BBE  894618                  mov      dword ptr [esi + 0x18], eax    
  0x00221BC1  8a4104                  mov      al, byte ptr [ecx + 4]         
  0x00221BC4  c0e807                  shr      al, 7                          
  0x00221BC7  88461e                  mov      byte ptr [esi + 0x1e], al      
                                        ; XREF: 0x00221B7D (cond_jump), 0x00221B95 (jump), 0x00221BA6 (cond_jump), 0x00221BAB (jump), 0x00221BB3 (jump)
  0x00221BCA  8b410c                  mov      eax, dword ptr [ecx + 0xc]     
  0x00221BCD  56                      push     esi                            
  0x00221BCE  83c018                  add      eax, 0x18                      
  0x00221BD1  50                      push     eax                            
  0x00221BD2  e85b140000              call     0x223032                       ; -> sub_00223032
                                        ; XREF: 0x00221B85 (jump), 0x00221B8D (jump)
  0x00221BD7  385dff                  cmp      byte ptr [ebp - 1], bl         
  0x00221BDA  7427                    je       0x221c03                       
  0x00221BDC  8bc8                    mov      ecx, eax                       
  0x00221BDE  81e1000000c0            and      ecx, 0xc0000000                
  0x00221BE4  81f900000040            cmp      ecx, 0x40000000                
  0x00221BEA  7511                    jne      0x221bfd                       
  0x00221BEC  53                      push     ebx                            
  0x00221BED  53                      push     ebx                            
  0x00221BEE  53                      push     ebx                            
  0x00221BEF  53                      push     ebx                            
  0x00221BF0  8d45ec                  lea      eax, [ebp - 0x14]              
  0x00221BF3  50                      push     eax                            
  0x00221BF4  ff15485b2200            call     dword ptr [0x225b48]           ; -> xbox_KeWaitForSingleObject
  0x00221BFA  8b4604                  mov      eax, dword ptr [esi + 4]       
                                        ; XREF: 0x00221BEA (cond_jump)
  0x00221BFD  895e08                  mov      dword ptr [esi + 8], ebx       
  0x00221C00  895e0c                  mov      dword ptr [esi + 0xc], ebx     
                                        ; XREF: 0x00221BDA (cond_jump)
  0x00221C03  5e                      pop      esi                            
  0x00221C04  5b                      pop      ebx                            
  0x00221C05  c9                      leave                                   
  0x00221C06  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221C09
; Start: 0x00221C09  End: 0x00221C4B  Size: 66 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00221AAA
; Called by: sub_00221C4B
; ============================================================
sub_00221C09:
  0x00221C09  56                      push     esi                            
  0x00221C0A  8b742408                mov      esi, dword ptr [esp + 8]       
  0x00221C0E  8d4604                  lea      eax, [esi + 4]                 
  0x00221C11  8b10                    mov      edx, dword ptr [eax]           
  0x00221C13  803a01                  cmp      byte ptr [edx], 1              
  0x00221C16  750b                    jne      0x221c23                       
  0x00221C18  8a5204                  mov      dl, byte ptr [edx + 4]         
  0x00221C1B  80e27f                  and      dl, 0x7f                       
  0x00221C1E  80fa01                  cmp      dl, 1                          
  0x00221C21  7409                    je       0x221c2c                       
                                        ; XREF: 0x00221C16 (cond_jump)
  0x00221C23  c7411420000000          mov      dword ptr [ecx + 0x14], 0x20   
  0x00221C2A  eb1b                    jmp      0x221c47                       
                                        ; XREF: 0x00221C21 (cond_jump)
  0x00221C2C  8b54240c                mov      edx, dword ptr [esp + 0xc]     
  0x00221C30  83fa01                  cmp      edx, 1                         
  0x00221C33  7506                    jne      0x221c3b                       
  0x00221C35  83611400                and      dword ptr [ecx + 0x14], 0      
  0x00221C39  eb0c                    jmp      0x221c47                       
                                        ; XREF: 0x00221C33 (cond_jump)
  0x00221C3B  8b36                    mov      esi, dword ptr [esi]           
  0x00221C3D  4a                      dec      edx                            
  0x00221C3E  52                      push     edx                            
  0x00221C3F  50                      push     eax                            
  0x00221C40  8930                    mov      dword ptr [eax], esi           
  0x00221C42  e863feffff              call     0x221aaa                       ; -> sub_00221AAA
                                        ; XREF: 0x00221C2A (jump), 0x00221C39 (jump)
  0x00221C47  5e                      pop      esi                            
  0x00221C48  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00221C4B
; Start: 0x00221C4B  End: 0x00221C96  Size: 75 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220776, sub_00221AAA, sub_00221C09
; Called by: sub_00220F8D
; ============================================================
sub_00221C4B:
  0x00221C4B  55                      push     ebp                            
  0x00221C4C  8bec                    mov      ebp, esp                       
  0x00221C4E  83ec18                  sub      esp, 0x18                      
  0x00221C51  56                      push     esi                            
  0x00221C52  57                      push     edi                            
  0x00221C53  8bf9                    mov      edi, ecx                       
  0x00221C55  6a05                    push     5                              
  0x00221C57  5e                      pop      esi                            
  0x00221C58  897dfc                  mov      dword ptr [ebp - 4], edi       
                                        ; XREF: 0x00221C6C (cond_jump)
  0x00221C5B  8b4cb5e8                mov      ecx, dword ptr [ebp + esi*4 - 0x18] 
  0x00221C5F  4e                      dec      esi                            
  0x00221C60  e811ebffff              call     0x220776                       ; -> sub_00220776
  0x00221C65  803800                  cmp      byte ptr [eax], 0              
  0x00221C68  8944b5e8                mov      dword ptr [ebp + esi*4 - 0x18], eax 
  0x00221C6C  75ed                    jne      0x221c5b                       
  0x00221C6E  8b15a85a2200            mov      edx, dword ptr [0x225aa8]      
  0x00221C74  6a05                    push     5                              
  0x00221C76  58                      pop      eax                            
  0x00221C77  2bc6                    sub      eax, esi                       
  0x00221C79  f60201                  test     byte ptr [edx], 1              
  0x00221C7C  8d4cb5e8                lea      ecx, [ebp + esi*4 - 0x18]      
  0x00221C80  50                      push     eax                            
  0x00221C81  51                      push     ecx                            
  0x00221C82  8bcf                    mov      ecx, edi                       
  0x00221C84  7407                    je       0x221c8d                       
  0x00221C86  e87effffff              call     0x221c09                       ; -> sub_00221C09
  0x00221C8B  eb05                    jmp      0x221c92                       
                                        ; XREF: 0x00221C84 (cond_jump)
  0x00221C8D  e818feffff              call     0x221aaa                       ; -> sub_00221AAA
                                        ; XREF: 0x00221C8B (jump)
  0x00221C92  5f                      pop      edi                            
  0x00221C93  5e                      pop      esi                            
  0x00221C94  c9                      leave                                   
  0x00221C95  c3                      ret                                     
; end of function
                                        ; XREF: 0x0022201D (data_imm)
  0x00221C96  56                      push     esi                            
  0x00221C97  8b742408                mov      esi, dword ptr [esp + 8]       
  0x00221C9B  837e0400                cmp      dword ptr [esi + 4], 0         
  0x00221C9F  7d1d                    jge      0x221cbe                       
  0x00221CA1  68d06c2800              push     0x286cd0                       
  0x00221CA6  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00221CAC  ff35c86c2800            push     dword ptr [0x286cc8]           
  0x00221CB2  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x00221CB6  ff7604                  push     dword ptr [esi + 4]            
  0x00221CB9  e872edffff              call     0x220a30                       ; -> sub_00220A30
                                        ; XREF: 0x00221C9F (cond_jump)
  0x00221CBE  5e                      pop      esi                            
  0x00221CBF  c20800                  ret      8                              
                                        ; XREF: 0x00222046 (data_imm)
  0x00221CC2  68d06c2800              push     0x286cd0                       
  0x00221CC7  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00221CCD  ff35c86c2800            push     dword ptr [0x286cc8]           
  0x00221CD3  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00221CD7  ff7004                  push     dword ptr [eax + 4]            
  0x00221CDA  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x00221CDE  e819f0ffff              call     0x220cfc                       ; -> sub_00220CFC
  0x00221CE3  c20800                  ret      8                              

; ============================================================
; Function: sub_00221CE6
; Start: 0x00221CE6  End: 0x00221D43  Size: 93 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002217D6, sub_00221B1F
; Called by: sub_00221E4D
; ============================================================
sub_00221CE6:
  0x00221CE6  56                      push     esi                            
  0x00221CE7  8b742408                mov      esi, dword ptr [esp + 8]       
  0x00221CEB  57                      push     edi                            
  0x00221CEC  8bce                    mov      ecx, esi                       
  0x00221CEE  e8e3faffff              call     0x2217d6                       ; -> sub_002217D6
  0x00221CF3  660fb67803              movzx    di, byte ptr [eax + 3]         
  0x00221CF8  33d2                    xor      edx, edx                       
  0x00221CFA  8d4808                  lea      ecx, [eax + 8]                 
  0x00221CFD  c60130                  mov      byte ptr [ecx], 0x30           
  0x00221D00  51                      push     ecx                            
  0x00221D01  8bce                    mov      ecx, esi                       
  0x00221D03  c6400940                mov      byte ptr [eax + 9], 0x40       
  0x00221D07  c74010ca252200          mov      dword ptr [eax + 0x10], 0x2225ca 
  0x00221D0E  897014                  mov      dword ptr [eax + 0x14], esi    
  0x00221D11  895018                  mov      dword ptr [eax + 0x18], edx    
  0x00221D14  895020                  mov      dword ptr [eax + 0x20], edx    
  0x00221D17  89501c                  mov      dword ptr [eax + 0x1c], edx    
  0x00221D1A  885024                  mov      byte ptr [eax + 0x24], dl      
  0x00221D1D  885025                  mov      byte ptr [eax + 0x25], dl      
  0x00221D20  885026                  mov      byte ptr [eax + 0x26], dl      
  0x00221D23  c6403023                mov      byte ptr [eax + 0x30], 0x23    
  0x00221D27  c6403101                mov      byte ptr [eax + 0x31], 1       
  0x00221D2B  66c740320100            mov      word ptr [eax + 0x32], 1       
  0x00221D31  66897834                mov      word ptr [eax + 0x34], di      
  0x00221D35  66895036                mov      word ptr [eax + 0x36], dx      
  0x00221D39  e8e1fdffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00221D3E  5f                      pop      edi                            
  0x00221D3F  5e                      pop      esi                            
  0x00221D40  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221D43
; Start: 0x00221D43  End: 0x00221D79  Size: 54 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220982, sub_00220989
; Called by: sub_00221DEA, sub_002224C7
; ============================================================
sub_00221D43:
  0x00221D43  56                      push     esi                            
  0x00221D44  8b742408                mov      esi, dword ptr [esp + 8]       
  0x00221D48  8a06                    mov      al, byte ptr [esi]             
  0x00221D4A  c0e804                  shr      al, 4                          
  0x00221D4D  2401                    and      al, 1                          
  0x00221D4F  7411                    je       0x221d62                       
  0x00221D51  837c240c00              cmp      dword ptr [esp + 0xc], 0       
  0x00221D56  750a                    jne      0x221d62                       
  0x00221D58  e82cecffff              call     0x220989                       ; -> sub_00220989
  0x00221D5D  8026ef                  and      byte ptr [esi], 0xef           
  0x00221D60  eb13                    jmp      0x221d75                       
                                        ; XREF: 0x00221D4F (cond_jump), 0x00221D56 (cond_jump)
  0x00221D62  84c0                    test     al, al                         
  0x00221D64  750f                    jne      0x221d75                       
  0x00221D66  837c240c00              cmp      dword ptr [esp + 0xc], 0       
  0x00221D6B  7408                    je       0x221d75                       
  0x00221D6D  e810ecffff              call     0x220982                       ; -> sub_00220982
  0x00221D72  800e10                  or       byte ptr [esi], 0x10           
                                        ; XREF: 0x00221D60 (jump), 0x00221D64 (cond_jump), 0x00221D6B (cond_jump)
  0x00221D75  5e                      pop      esi                            
  0x00221D76  c20800                  ret      8                              
; end of function
                                        ; XREF: 0x00222906 (data_imm)
  0x00221D79  56                      push     esi                            
  0x00221D7A  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00221D7E  8bce                    mov      ecx, esi                       
  0x00221D80  e851faffff              call     0x2217d6                       ; -> sub_002217D6
  0x00221D85  8b0d146d2800            mov      ecx, dword ptr [0x286d14]      
  0x00221D8B  83e900                  sub      ecx, 0                         
  0x00221D8E  744b                    je       0x221ddb                       
  0x00221D90  49                      dec      ecx                            
  0x00221D91  7434                    je       0x221dc7                       
  0x00221D93  49                      dec      ecx                            
  0x00221D94  741d                    je       0x221db3                       
  0x00221D96  49                      dec      ecx                            
  0x00221D97  754d                    jne      0x221de6                       
  0x00221D99  a1186d2800              mov      eax, dword ptr [0x286d18]      
  0x00221D9E  85c0                    test     eax, eax                       
  0x00221DA0  7444                    je       0x221de6                       
  0x00221DA2  6a00                    push     0                              
  0x00221DA4  50                      push     eax                            
  0x00221DA5  e899ffffff              call     0x221d43                       ; -> sub_00221D43
  0x00221DAA  8325186d280000          and      dword ptr [0x286d18], 0        
  0x00221DB1  eb33                    jmp      0x221de6                       
                                        ; XREF: 0x00221D94 (cond_jump)
  0x00221DB3  ff35c86c2800            push     dword ptr [0x286cc8]           
  0x00221DB9  8bce                    mov      ecx, esi                       
  0x00221DBB  6800060080              push     0x80000600                     
  0x00221DC0  e837efffff              call     0x220cfc                       ; -> sub_00220CFC
  0x00221DC5  eb1f                    jmp      0x221de6                       
                                        ; XREF: 0x00221D91 (cond_jump)
  0x00221DC7  ff35c86c2800            push     dword ptr [0x286cc8]           
  0x00221DCD  8bce                    mov      ecx, esi                       
  0x00221DCF  6800060080              push     0x80000600                     
  0x00221DD4  e857ecffff              call     0x220a30                       ; -> sub_00220A30
  0x00221DD9  eb0b                    jmp      0x221de6                       
                                        ; XREF: 0x00221D8E (cond_jump)
  0x00221DDB  83c008                  add      eax, 8                         
  0x00221DDE  50                      push     eax                            
  0x00221DDF  8bce                    mov      ecx, esi                       
  0x00221DE1  e8ddf9ffff              call     0x2217c3                       ; -> sub_002217C3
                                        ; XREF: 0x00221D97 (cond_jump), 0x00221DA0 (cond_jump), 0x00221DB1 (jump), 0x00221DC5 (jump), 0x00221DD9 (jump)
  0x00221DE6  5e                      pop      esi                            
  0x00221DE7  c21000                  ret      0x10                           

; ============================================================
; Function: sub_00221DEA
; Start: 0x00221DEA  End: 0x00221E4D  Size: 99 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00221D43
; Called by: sub_00221FFE, sub_00222771
; ============================================================
sub_00221DEA:
  0x00221DEA  833d186d280000          cmp      dword ptr [0x286d18], 0        
  0x00221DF1  56                      push     esi                            
  0x00221DF2  bed06c2800              mov      esi, 0x286cd0                  
  0x00221DF7  741b                    je       0x221e14                       
  0x00221DF9  56                      push     esi                            
  0x00221DFA  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00221E00  6a00                    push     0                              
  0x00221E02  ff35186d2800            push     dword ptr [0x286d18]           
  0x00221E08  e836ffffff              call     0x221d43                       ; -> sub_00221D43
  0x00221E0D  8325186d280000          and      dword ptr [0x286d18], 0        
                                        ; XREF: 0x00221DF7 (cond_jump)
  0x00221E14  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00221E18  85d2                    test     edx, edx                       
  0x00221E1A  7507                    jne      0x221e23                       
  0x00221E1C  b8001f0afa              mov      eax, 0xfa0a1f00                
  0x00221E21  eb0f                    jmp      0x221e32                       
                                        ; XREF: 0x00221E1A (cond_jump)
  0x00221E23  83fa03                  cmp      edx, 3                         
  0x00221E26  b8508ef4ff              mov      eax, 0xfff48e50                
  0x00221E2B  7405                    je       0x221e32                       
  0x00221E2D  b8c0b4b3ff              mov      eax, 0xffb3b4c0                
                                        ; XREF: 0x00221E21 (jump), 0x00221E2B (cond_jump)
  0x00221E32  68f86c2800              push     0x286cf8                       
  0x00221E37  83c9ff                  or       ecx, 0xffffffff                
  0x00221E3A  51                      push     ecx                            
  0x00221E3B  50                      push     eax                            
  0x00221E3C  56                      push     esi                            
  0x00221E3D  8915146d2800            mov      dword ptr [0x286d14], edx      
  0x00221E43  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
  0x00221E49  5e                      pop      esi                            
  0x00221E4A  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00221E4D
; Start: 0x00221E4D  End: 0x00221F9B  Size: 334 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220A30, sub_00220BAC, sub_002217D6, sub_00221B1F, sub_00221CE6, sub_0022259A
; Called by: sub_0022259A
; ============================================================
sub_00221E4D:
  0x00221E4D  55                      push     ebp                            
  0x00221E4E  8bec                    mov      ebp, esp                       
  0x00221E50  53                      push     ebx                            
  0x00221E51  56                      push     esi                            
  0x00221E52  57                      push     edi                            
  0x00221E53  8b7d08                  mov      edi, dword ptr [ebp + 8]       
  0x00221E56  8bcf                    mov      ecx, edi                       
  0x00221E58  e879f9ffff              call     0x2217d6                       ; -> sub_002217D6
  0x00221E5D  8bf0                    mov      esi, eax                       
  0x00221E5F  668b463a                mov      ax, word ptr [esi + 0x3a]      
  0x00221E63  33db                    xor      ebx, ebx                       
  0x00221E65  a810                    test     al, 0x10                       
  0x00221E67  745b                    je       0x221ec4                       
  0x00221E69  833d146d280001          cmp      dword ptr [0x286d14], 1        
  0x00221E70  754a                    jne      0x221ebc                       
  0x00221E72  391dc86c2800            cmp      dword ptr [0x286cc8], ebx      
  0x00221E78  7442                    je       0x221ebc                       
  0x00221E7A  68d06c2800              push     0x286cd0                       
  0x00221E7F  33ff                    xor      edi, edi                       
  0x00221E81  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00221E87  668b4638                mov      ax, word ptr [esi + 0x38]      
  0x00221E8B  a802                    test     al, 2                          
  0x00221E8D  7410                    je       0x221e9f                       
  0x00221E8F  a810                    test     al, 0x10                       
  0x00221E91  750c                    jne      0x221e9f                       
  0x00221E93  f6c402                  test     ah, 2                          
  0x00221E96  740c                    je       0x221ea4                       
  0x00221E98  bf00000001              mov      edi, 0x1000000                 
  0x00221E9D  eb05                    jmp      0x221ea4                       
                                        ; XREF: 0x00221E8D (cond_jump), 0x00221E91 (cond_jump)
  0x00221E9F  bf00060080              mov      edi, 0x80000600                
                                        ; XREF: 0x00221E96 (cond_jump), 0x00221E9D (jump)
  0x00221EA4  a1c86c2800              mov      eax, dword ptr [0x286cc8]      
  0x00221EA9  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00221EAC  50                      push     eax                            
  0x00221EAD  57                      push     edi                            
  0x00221EAE  891dc86c2800            mov      dword ptr [0x286cc8], ebx      
  0x00221EB4  e877ebffff              call     0x220a30                       ; -> sub_00220A30
  0x00221EB9  8b7d08                  mov      edi, dword ptr [ebp + 8]       
                                        ; XREF: 0x00221E70 (cond_jump), 0x00221E78 (cond_jump)
  0x00221EBC  80663aef                and      byte ptr [esi + 0x3a], 0xef    
  0x00221EC0  6a14                    push     0x14                           
  0x00221EC2  eb77                    jmp      0x221f3b                       
                                        ; XREF: 0x00221E67 (cond_jump)
  0x00221EC4  a801                    test     al, 1                          
  0x00221EC6  744d                    je       0x221f15                       
  0x00221EC8  33c9                    xor      ecx, ecx                       
  0x00221ECA  8a4e03                  mov      cl, byte ptr [esi + 3]         
  0x00221ECD  884d08                  mov      byte ptr [ebp + 8], cl         
  0x00221ED0  b001                    mov      al, 1                          
  0x00221ED2  49                      dec      ecx                            
  0x00221ED3  d2e0                    shl      al, cl                         
  0x00221ED5  f6463801                test     byte ptr [esi + 0x38], 1       
  0x00221ED9  741a                    je       0x221ef5                       
  0x00221EDB  844605                  test     byte ptr [esi + 5], al         
  0x00221EDE  740a                    je       0x221eea                       
  0x00221EE0  ff7508                  push     dword ptr [ebp + 8]            
  0x00221EE3  8bcf                    mov      ecx, edi                       
  0x00221EE5  e8c2ecffff              call     0x220bac                       ; -> sub_00220BAC
                                        ; XREF: 0x00221EDE (cond_jump)
  0x00221EEA  57                      push     edi                            
  0x00221EEB  e8f6fdffff              call     0x221ce6                       ; -> sub_00221CE6
  0x00221EF0  e99f000000              jmp      0x221f94                       
                                        ; XREF: 0x00221ED9 (cond_jump)
  0x00221EF5  8a4e05                  mov      cl, byte ptr [esi + 5]         
  0x00221EF8  84c8                    test     al, cl                         
  0x00221EFA  7411                    je       0x221f0d                       
  0x00221EFC  ff7508                  push     dword ptr [ebp + 8]            
  0x00221EFF  f6d0                    not      al                             
  0x00221F01  22c1                    and      al, cl                         
  0x00221F03  8bcf                    mov      ecx, edi                       
  0x00221F05  884605                  mov      byte ptr [esi + 5], al         
  0x00221F08  e89fecffff              call     0x220bac                       ; -> sub_00220BAC
                                        ; XREF: 0x00221EFA (cond_jump)
  0x00221F0D  80663afe                and      byte ptr [esi + 0x3a], 0xfe    
  0x00221F11  6a10                    push     0x10                           
  0x00221F13  eb26                    jmp      0x221f3b                       
                                        ; XREF: 0x00221EC6 (cond_jump)
  0x00221F15  a802                    test     al, 2                          
  0x00221F17  7408                    je       0x221f21                       
  0x00221F19  6625fdff                and      ax, 0xfffd                     
  0x00221F1D  6a11                    push     0x11                           
  0x00221F1F  eb16                    jmp      0x221f37                       
                                        ; XREF: 0x00221F17 (cond_jump)
  0x00221F21  a804                    test     al, 4                          
  0x00221F23  7408                    je       0x221f2d                       
  0x00221F25  6625fbff                and      ax, 0xfffb                     
  0x00221F29  6a12                    push     0x12                           
  0x00221F2B  eb0a                    jmp      0x221f37                       
                                        ; XREF: 0x00221F23 (cond_jump)
  0x00221F2D  a808                    test     al, 8                          
  0x00221F2F  7454                    je       0x221f85                       
  0x00221F31  6625f7ff                and      ax, 0xfff7                     
  0x00221F35  6a13                    push     0x13                           
                                        ; XREF: 0x00221F1F (jump), 0x00221F2B (jump)
  0x00221F37  6689463a                mov      word ptr [esi + 0x3a], ax      
                                        ; XREF: 0x00221EC2 (jump), 0x00221F13 (jump)
  0x00221F3B  59                      pop      ecx                            
  0x00221F3C  66894e32                mov      word ptr [esi + 0x32], cx      
  0x00221F40  660fb64e03              movzx    cx, byte ptr [esi + 3]         
  0x00221F45  8d4608                  lea      eax, [esi + 8]                 
  0x00221F48  66894e34                mov      word ptr [esi + 0x34], cx      
  0x00221F4C  50                      push     eax                            
  0x00221F4D  8bcf                    mov      ecx, edi                       
  0x00221F4F  c60030                  mov      byte ptr [eax], 0x30           
  0x00221F52  c6460940                mov      byte ptr [esi + 9], 0x40       
  0x00221F56  c746109a252200          mov      dword ptr [esi + 0x10], 0x22259a 
  0x00221F5D  897e14                  mov      dword ptr [esi + 0x14], edi    
  0x00221F60  895e18                  mov      dword ptr [esi + 0x18], ebx    
  0x00221F63  895e20                  mov      dword ptr [esi + 0x20], ebx    
  0x00221F66  895e1c                  mov      dword ptr [esi + 0x1c], ebx    
  0x00221F69  885e24                  mov      byte ptr [esi + 0x24], bl      
  0x00221F6C  885e25                  mov      byte ptr [esi + 0x25], bl      
  0x00221F6F  885e26                  mov      byte ptr [esi + 0x26], bl      
  0x00221F72  c6463023                mov      byte ptr [esi + 0x30], 0x23    
  0x00221F76  c6463101                mov      byte ptr [esi + 0x31], 1       
  0x00221F7A  66895e36                mov      word ptr [esi + 0x36], bx      
  0x00221F7E  e89cfbffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00221F83  eb0f                    jmp      0x221f94                       
                                        ; XREF: 0x00221F2F (cond_jump)
  0x00221F85  6683663a00              and      word ptr [esi + 0x3a], 0       
  0x00221F8A  57                      push     edi                            
  0x00221F8B  83c608                  add      esi, 8                         
  0x00221F8E  56                      push     esi                            
  0x00221F8F  e806060000              call     0x22259a                       ; -> sub_0022259A
                                        ; XREF: 0x00221EF0 (jump), 0x00221F83 (jump)
  0x00221F94  5f                      pop      edi                            
  0x00221F95  5e                      pop      esi                            
  0x00221F96  5b                      pop      ebx                            
  0x00221F97  5d                      pop      ebp                            
  0x00221F98  c20400                  ret      4                              
; end of function
                                        ; XREF: 0x002220F5 (data_imm)
  0x00221F9B  56                      push     esi                            
  0x00221F9C  57                      push     edi                            
  0x00221F9D  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x00221FA1  8bcf                    mov      ecx, edi                       
  0x00221FA3  e82ef8ffff              call     0x2217d6                       ; -> sub_002217D6
  0x00221FA8  6a00                    push     0                              
  0x00221FAA  8bcf                    mov      ecx, edi                       
  0x00221FAC  8bf0                    mov      esi, eax                       
  0x00221FAE  e827f8ffff              call     0x2217da                       ; -> sub_002217DA
  0x00221FB3  8026fe                  and      byte ptr [esi], 0xfe           
  0x00221FB6  66ff0d226d2800          dec      word ptr [0x286d22]            
  0x00221FBD  f60602                  test     byte ptr [esi], 2              
  0x00221FC0  742b                    je       0x221fed                       
  0x00221FC2  6a00                    push     0                              
  0x00221FC4  56                      push     esi                            
  0x00221FC5  e879fdffff              call     0x221d43                       ; -> sub_00221D43
  0x00221FCA  3b35186d2800            cmp      esi, dword ptr [0x286d18]      
  0x00221FD0  7512                    jne      0x221fe4                       
  0x00221FD2  68d06c2800              push     0x286cd0                       
  0x00221FD7  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00221FDD  8325186d280000          and      dword ptr [0x286d18], 0        
                                        ; XREF: 0x00221FD0 (cond_jump)
  0x00221FE4  8bcf                    mov      ecx, edi                       
  0x00221FE6  e84aeaffff              call     0x220a35                       ; -> sub_00220A35
  0x00221FEB  eb0c                    jmp      0x221ff9                       
                                        ; XREF: 0x00221FC0 (cond_jump)
  0x00221FED  6800010080              push     0x80000100                     
  0x00221FF2  8bcf                    mov      ecx, edi                       
  0x00221FF4  e808eeffff              call     0x220e01                       ; -> sub_00220E01
                                        ; XREF: 0x00221FEB (jump)
  0x00221FF9  5f                      pop      edi                            
  0x00221FFA  5e                      pop      esi                            
  0x00221FFB  c20800                  ret      8                              

; ============================================================
; Function: sub_00221FFE
; Start: 0x00221FFE  End: 0x002220E5  Size: 231 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220A30, sub_002217D6, sub_00221B1F, sub_00221DEA
; Called by: sub_002209CE, sub_00220D2F
; ============================================================
sub_00221FFE:
  0x00221FFE  55                      push     ebp                            
  0x00221FFF  8bec                    mov      ebp, esp                       
  0x00222001  51                      push     ecx                            
  0x00222002  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00222005  53                      push     ebx                            
  0x00222006  56                      push     esi                            
  0x00222007  57                      push     edi                            
  0x00222008  e8c9f7ffff              call     0x2217d6                       ; -> sub_002217D6
  0x0022200D  33c9                    xor      ecx, ecx                       
  0x0022200F  3bc1                    cmp      eax, ecx                       
  0x00222011  6a04                    push     4                              
  0x00222013  b203                    mov      dl, 3                          
  0x00222015  5e                      pop      esi                            
  0x00222016  c745fc01000000          mov      dword ptr [ebp - 4], 1         
  0x0022201D  bf961c2200              mov      edi, 0x221c96                  
  0x00222022  0f84a6000000            je       0x2220ce                       
  0x00222028  8a5d0c                  mov      bl, byte ptr [ebp + 0xc]       
  0x0022202B  385802                  cmp      byte ptr [eax + 2], bl         
  0x0022202E  0f829a000000            jb       0x2220ce                       
  0x00222034  384d14                  cmp      byte ptr [ebp + 0x14], cl      
  0x00222037  8b4510                  mov      eax, dword ptr [ebp + 0x10]    
  0x0022203A  a3c86c2800              mov      dword ptr [0x286cc8], eax      
  0x0022203F  7411                    je       0x222052                       
  0x00222041  33d2                    xor      edx, edx                       
  0x00222043  42                      inc      edx                            
  0x00222044  8bf2                    mov      esi, edx                       
  0x00222046  bfc21c2200              mov      edi, 0x221cc2                  
  0x0022204B  c745fc02000000          mov      dword ptr [ebp - 4], 2         
                                        ; XREF: 0x0022203F (cond_jump)
  0x00222052  ff75fc                  push     dword ptr [ebp - 4]            
  0x00222055  660fb6c3                movzx    ax, bl                         
  0x00222059  893da06c2800            mov      dword ptr [0x286ca0], edi      
  0x0022205F  8b7d08                  mov      edi, dword ptr [ebp + 8]       
  0x00222062  c605986c280030          mov      byte ptr [0x286c98], 0x30      
  0x00222069  c605996c280040          mov      byte ptr [0x286c99], 0x40      
  0x00222070  893da46c2800            mov      dword ptr [0x286ca4], edi      
  0x00222076  890da86c2800            mov      dword ptr [0x286ca8], ecx      
  0x0022207C  890db06c2800            mov      dword ptr [0x286cb0], ecx      
  0x00222082  890dac6c2800            mov      dword ptr [0x286cac], ecx      
  0x00222088  880db46c2800            mov      byte ptr [0x286cb4], cl        
  0x0022208E  880db56c2800            mov      byte ptr [0x286cb5], cl        
  0x00222094  880db66c2800            mov      byte ptr [0x286cb6], cl        
  0x0022209A  c605c06c280023          mov      byte ptr [0x286cc0], 0x23      
  0x002220A1  8815c16c2800            mov      byte ptr [0x286cc1], dl        
  0x002220A7  668935c26c2800          mov      word ptr [0x286cc2], si        
  0x002220AE  66a3c46c2800            mov      word ptr [0x286cc4], ax        
  0x002220B4  66890dc66c2800          mov      word ptr [0x286cc6], cx        
  0x002220BB  e82afdffff              call     0x221dea                       ; -> sub_00221DEA
  0x002220C0  68986c2800              push     0x286c98                       
  0x002220C5  8bcf                    mov      ecx, edi                       
  0x002220C7  e853faffff              call     0x221b1f                       ; -> sub_00221B1F
  0x002220CC  eb10                    jmp      0x2220de                       
                                        ; XREF: 0x00222022 (cond_jump), 0x0022202E (cond_jump)
  0x002220CE  ff7510                  push     dword ptr [ebp + 0x10]         
  0x002220D1  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002220D4  6800030080              push     0x80000300                     
  0x002220D9  e852e9ffff              call     0x220a30                       ; -> sub_00220A30
                                        ; XREF: 0x002220CC (jump)
  0x002220DE  5f                      pop      edi                            
  0x002220DF  5e                      pop      esi                            
  0x002220E0  5b                      pop      ebx                            
  0x002220E1  c9                      leave                                   
  0x002220E2  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_002220E5
; Start: 0x002220E5  End: 0x00222107  Size: 34 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00221B1F
; Called by: sub_00222771
; ============================================================
sub_002220E5:
  0x002220E5  8b442404                mov      eax, dword ptr [esp + 4]       
  0x002220E9  8b4c2408                mov      ecx, dword ptr [esp + 8]       
  0x002220ED  50                      push     eax                            
  0x002220EE  c6001c                  mov      byte ptr [eax], 0x1c           
  0x002220F1  c64001c3                mov      byte ptr [eax + 1], 0xc3       
  0x002220F5  c740089b1f2200          mov      dword ptr [eax + 8], 0x221f9b  
  0x002220FC  89480c                  mov      dword ptr [eax + 0xc], ecx     
  0x002220FF  e81bfaffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222104  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00222107
; Start: 0x00222107  End: 0x00222139  Size: 50 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002217D6, sub_00221B1F
; Called by: sub_00222280, sub_0022259A
; ============================================================
sub_00222107:
  0x00222107  56                      push     esi                            
  0x00222108  8b742408                mov      esi, dword ptr [esp + 8]       
  0x0022210C  8bce                    mov      ecx, esi                       
  0x0022210E  e8c3f6ffff              call     0x2217d6                       ; -> sub_002217D6
  0x00222113  8b503c                  mov      edx, dword ptr [eax + 0x3c]    
  0x00222116  8d4808                  lea      ecx, [eax + 8]                 
  0x00222119  c6011c                  mov      byte ptr [ecx], 0x1c           
  0x0022211C  51                      push     ecx                            
  0x0022211D  8bce                    mov      ecx, esi                       
  0x0022211F  c6400943                mov      byte ptr [eax + 9], 0x43       
  0x00222123  c74010e5202200          mov      dword ptr [eax + 0x10], 0x2220e5 
  0x0022212A  897014                  mov      dword ptr [eax + 0x14], esi    
  0x0022212D  895018                  mov      dword ptr [eax + 0x18], edx    
  0x00222130  e8eaf9ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222135  5e                      pop      esi                            
  0x00222136  c20400                  ret      4                              
; end of function
                                        ; XREF: 0x00222359 (data_imm)
  0x00222139  53                      push     ebx                            
  0x0022213A  8b5c240c                mov      ebx, dword ptr [esp + 0xc]     
  0x0022213E  57                      push     edi                            
  0x0022213F  8bcb                    mov      ecx, ebx                       
  0x00222141  e890f6ffff              call     0x2217d6                       ; -> sub_002217D6
  0x00222146  8bf8                    mov      edi, eax                       
  0x00222148  8a07                    mov      al, byte ptr [edi]             
  0x0022214A  a802                    test     al, 2                          
  0x0022214C  7408                    je       0x222156                       
  0x0022214E  53                      push     ebx                            
  0x0022214F  e8b3ffffff              call     0x222107                       ; -> sub_00222107
  0x00222154  eb6f                    jmp      0x2221c5                       
                                        ; XREF: 0x0022214C (cond_jump)
  0x00222156  56                      push     esi                            
  0x00222157  8b742410                mov      esi, dword ptr [esp + 0x10]    
  0x0022215B  837e0400                cmp      dword ptr [esi + 4], 0         
  0x0022215F  8bcb                    mov      ecx, ebx                       
  0x00222161  7d0b                    jge      0x22216e                       
  0x00222163  0c08                    or       al, 8                          
  0x00222165  8807                    mov      byte ptr [edi], al             
  0x00222167  e8b7eaffff              call     0x220c23                       ; -> sub_00220C23
  0x0022216C  eb56                    jmp      0x2221c4                       
                                        ; XREF: 0x00222161 (cond_jump)
  0x0022216E  83660800                and      dword ptr [esi + 8], 0         
  0x00222172  c60618                  mov      byte ptr [esi], 0x18           
  0x00222175  c6460105                mov      byte ptr [esi + 1], 5          
  0x00222179  8b473c                  mov      eax, dword ptr [edi + 0x3c]    
  0x0022217C  56                      push     esi                            
  0x0022217D  894610                  mov      dword ptr [esi + 0x10], eax    
  0x00222180  c7461404000000          mov      dword ptr [esi + 0x14], 4      
  0x00222187  e893f9ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x0022218C  c60628                  mov      byte ptr [esi], 0x28           
  0x0022218F  c6460141                mov      byte ptr [esi + 1], 0x41       
  0x00222193  c74608d0222200          mov      dword ptr [esi + 8], 0x2222d0  
  0x0022219A  895e0c                  mov      dword ptr [esi + 0xc], ebx     
  0x0022219D  8b473c                  mov      eax, dword ptr [edi + 0x3c]    
  0x002221A0  894610                  mov      dword ptr [esi + 0x10], eax    
  0x002221A3  8d4738                  lea      eax, [edi + 0x38]              
  0x002221A6  894618                  mov      dword ptr [esi + 0x18], eax    
  0x002221A9  0fb64707                movzx    eax, byte ptr [edi + 7]        
  0x002221AD  56                      push     esi                            
  0x002221AE  8bcb                    mov      ecx, ebx                       
  0x002221B0  894614                  mov      dword ptr [esi + 0x14], eax    
  0x002221B3  c6461c02                mov      byte ptr [esi + 0x1c], 2       
  0x002221B7  c6461d01                mov      byte ptr [esi + 0x1d], 1       
  0x002221BB  c6461e00                mov      byte ptr [esi + 0x1e], 0       
  0x002221BF  e85bf9ffff              call     0x221b1f                       ; -> sub_00221B1F
                                        ; XREF: 0x0022216C (jump)
  0x002221C4  5e                      pop      esi                            
                                        ; XREF: 0x00222154 (jump)
  0x002221C5  5f                      pop      edi                            
  0x002221C6  5b                      pop      ebx                            
  0x002221C7  c20800                  ret      8                              
                                        ; XREF: 0x00222578 (data_imm)
  0x002221CA  56                      push     esi                            
  0x002221CB  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x002221CF  8bce                    mov      ecx, esi                       
  0x002221D1  e800f6ffff              call     0x2217d6                       ; -> sub_002217D6
  0x002221D6  8a08                    mov      cl, byte ptr [eax]             
  0x002221D8  f6c102                  test     cl, 2                          
  0x002221DB  7408                    je       0x2221e5                       
  0x002221DD  56                      push     esi                            
  0x002221DE  e824ffffff              call     0x222107                       ; -> sub_00222107
  0x002221E3  eb3c                    jmp      0x222221                       
                                        ; XREF: 0x002221DB (cond_jump)
  0x002221E5  8b542408                mov      edx, dword ptr [esp + 8]       
  0x002221E9  837a0400                cmp      dword ptr [edx + 4], 0         
  0x002221ED  7c0c                    jl       0x2221fb                       
  0x002221EF  56                      push     esi                            
  0x002221F0  c6400600                mov      byte ptr [eax + 6], 0          
  0x002221F4  e854fcffff              call     0x221e4d                       ; -> sub_00221E4D
  0x002221F9  eb26                    jmp      0x222221                       
                                        ; XREF: 0x002221ED (cond_jump)
  0x002221FB  fe4006                  inc      byte ptr [eax + 6]             
  0x002221FE  80780603                cmp      byte ptr [eax + 6], 3          
  0x00222202  760e                    jbe      0x222212                       
  0x00222204  80c908                  or       cl, 8                          
  0x00222207  8808                    mov      byte ptr [eax], cl             
  0x00222209  8bce                    mov      ecx, esi                       
  0x0022220B  e813eaffff              call     0x220c23                       ; -> sub_00220C23
  0x00222210  eb0f                    jmp      0x222221                       
                                        ; XREF: 0x00222202 (cond_jump)
  0x00222212  52                      push     edx                            
  0x00222213  8bce                    mov      ecx, esi                       
  0x00222215  c7421404000000          mov      dword ptr [edx + 0x14], 4      
  0x0022221C  e8fef8ffff              call     0x221b1f                       ; -> sub_00221B1F
                                        ; XREF: 0x002221E3 (jump), 0x002221F9 (jump), 0x00222210 (jump)
  0x00222221  5e                      pop      esi                            
  0x00222222  c20800                  ret      8                              
                                        ; XREF: 0x0022241E (data_imm)
  0x00222225  56                      push     esi                            
  0x00222226  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0022222A  8bce                    mov      ecx, esi                       
  0x0022222C  e8a5f5ffff              call     0x2217d6                       ; -> sub_002217D6
  0x00222231  8a08                    mov      cl, byte ptr [eax]             
  0x00222233  f6c102                  test     cl, 2                          
  0x00222236  7408                    je       0x222240                       
  0x00222238  56                      push     esi                            
  0x00222239  e8c9feffff              call     0x222107                       ; -> sub_00222107
  0x0022223E  eb3c                    jmp      0x22227c                       
                                        ; XREF: 0x00222236 (cond_jump)
  0x00222240  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00222244  837a0400                cmp      dword ptr [edx + 4], 0         
  0x00222248  7d28                    jge      0x222272                       
  0x0022224A  fe4006                  inc      byte ptr [eax + 6]             
  0x0022224D  80780603                cmp      byte ptr [eax + 6], 3          
  0x00222251  760e                    jbe      0x222261                       
  0x00222253  80c908                  or       cl, 8                          
  0x00222256  8808                    mov      byte ptr [eax], cl             
  0x00222258  8bce                    mov      ecx, esi                       
  0x0022225A  e8c4e9ffff              call     0x220c23                       ; -> sub_00220C23
  0x0022225F  eb1b                    jmp      0x22227c                       
                                        ; XREF: 0x00222251 (cond_jump)
  0x00222261  52                      push     edx                            
  0x00222262  8bce                    mov      ecx, esi                       
  0x00222264  c7421404000000          mov      dword ptr [edx + 0x14], 4      
  0x0022226B  e8aff8ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222270  eb0a                    jmp      0x22227c                       
                                        ; XREF: 0x00222248 (cond_jump)
  0x00222272  56                      push     esi                            
  0x00222273  c6400600                mov      byte ptr [eax + 6], 0          
  0x00222277  e84b020000              call     0x2224c7                       ; -> sub_002224C7
                                        ; XREF: 0x0022223E (jump), 0x0022225F (jump), 0x00222270 (jump)
  0x0022227C  5e                      pop      esi                            
  0x0022227D  c20800                  ret      8                              

; ============================================================
; Function: sub_00222280
; Start: 0x00222280  End: 0x002222D0  Size: 80 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00220BAC, sub_002217D6, sub_00222107
; ============================================================
sub_00222280:
  0x00222280  55                      push     ebp                            
  0x00222281  8bec                    mov      ebp, esp                       
  0x00222283  51                      push     ecx                            
  0x00222284  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00222287  53                      push     ebx                            
  0x00222288  56                      push     esi                            
  0x00222289  e848f5ffff              call     0x2217d6                       ; -> sub_002217D6
  0x0022228E  8bf0                    mov      esi, eax                       
  0x00222290  800e02                  or       byte ptr [esi], 2              
  0x00222293  33db                    xor      ebx, ebx                       
  0x00222295  43                      inc      ebx                            
  0x00222296  885dfc                  mov      byte ptr [ebp - 4], bl         
                                        ; XREF: 0x002222BB (cond_jump)
  0x00222299  845e05                  test     byte ptr [esi + 5], bl         
  0x0022229C  7412                    je       0x2222b0                       
  0x0022229E  ff75fc                  push     dword ptr [ebp - 4]            
  0x002222A1  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002222A4  e803e9ffff              call     0x220bac                       ; -> sub_00220BAC
  0x002222A9  8ac3                    mov      al, bl                         
  0x002222AB  f6d0                    not      al                             
  0x002222AD  204605                  and      byte ptr [esi + 5], al         
                                        ; XREF: 0x0022229C (cond_jump)
  0x002222B0  d1e3                    shl      ebx, 1                         
  0x002222B2  fe45fc                  inc      byte ptr [ebp - 4]             
  0x002222B5  8a45fc                  mov      al, byte ptr [ebp - 4]         
  0x002222B8  3a4602                  cmp      al, byte ptr [esi + 2]         
  0x002222BB  76dc                    jbe      0x222299                       
  0x002222BD  f60608                  test     byte ptr [esi], 8              
  0x002222C0  5e                      pop      esi                            
  0x002222C1  5b                      pop      ebx                            
  0x002222C2  7408                    je       0x2222cc                       
  0x002222C4  ff7508                  push     dword ptr [ebp + 8]            
  0x002222C7  e83bfeffff              call     0x222107                       ; -> sub_00222107
                                        ; XREF: 0x002222C2 (cond_jump)
  0x002222CC  c9                      leave                                   
  0x002222CD  c20400                  ret      4                              
; end of function
                                        ; XREF: 0x00222193 (data_imm), 0x0022248C (data_imm), 0x0022252E (data_imm)
  0x002222D0  56                      push     esi                            
  0x002222D1  57                      push     edi                            
  0x002222D2  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x002222D6  8bcf                    mov      ecx, edi                       
  0x002222D8  e8f9f4ffff              call     0x2217d6                       ; -> sub_002217D6
  0x002222DD  8bf0                    mov      esi, eax                       
  0x002222DF  8a0e                    mov      cl, byte ptr [esi]             
  0x002222E1  f6c102                  test     cl, 2                          
  0x002222E4  740b                    je       0x2222f1                       
  0x002222E6  57                      push     edi                            
  0x002222E7  e81bfeffff              call     0x222107                       ; -> sub_00222107
  0x002222EC  e9a6000000              jmp      0x222397                       
                                        ; XREF: 0x002222E4 (cond_jump)
  0x002222F1  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x002222F5  53                      push     ebx                            
  0x002222F6  33db                    xor      ebx, ebx                       
  0x002222F8  395804                  cmp      dword ptr [eax + 4], ebx       
  0x002222FB  7c3e                    jl       0x22233b                       
  0x002222FD  3b35186d2800            cmp      esi, dword ptr [0x286d18]      
  0x00222303  7511                    jne      0x222316                       
  0x00222305  68d06c2800              push     0x286cd0                       
  0x0022230A  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00222310  891d186d2800            mov      dword ptr [0x286d18], ebx      
                                        ; XREF: 0x00222303 (cond_jump)
  0x00222316  6a01                    push     1                              
  0x00222318  56                      push     esi                            
  0x00222319  e825faffff              call     0x221d43                       ; -> sub_00221D43
  0x0022231E  33c9                    xor      ecx, ecx                       
  0x00222320  8a4e02                  mov      cl, byte ptr [esi + 2]         
  0x00222323  b001                    mov      al, 1                          
  0x00222325  57                      push     edi                            
  0x00222326  885e06                  mov      byte ptr [esi + 6], bl         
  0x00222329  41                      inc      ecx                            
  0x0022232A  d2e0                    shl      al, cl                         
  0x0022232C  fec8                    dec      al                             
  0x0022232E  224638                  and      al, byte ptr [esi + 0x38]      
  0x00222331  884604                  mov      byte ptr [esi + 4], al         
  0x00222334  e88e010000              call     0x2224c7                       ; -> sub_002224C7
  0x00222339  eb5b                    jmp      0x222396                       
                                        ; XREF: 0x002222FB (cond_jump)
  0x0022233B  fe4606                  inc      byte ptr [esi + 6]             
  0x0022233E  807e0603                cmp      byte ptr [esi + 6], 3          
  0x00222342  760e                    jbe      0x222352                       
  0x00222344  80c908                  or       cl, 8                          
  0x00222347  880e                    mov      byte ptr [esi], cl             
  0x00222349  8bcf                    mov      ecx, edi                       
  0x0022234B  e8d3e8ffff              call     0x220c23                       ; -> sub_00220C23
  0x00222350  eb44                    jmp      0x222396                       
                                        ; XREF: 0x00222342 (cond_jump)
  0x00222352  c60030                  mov      byte ptr [eax], 0x30           
  0x00222355  c6400140                mov      byte ptr [eax + 1], 0x40       
  0x00222359  c7400839212200          mov      dword ptr [eax + 8], 0x222139  
  0x00222360  89780c                  mov      dword ptr [eax + 0xc], edi     
  0x00222363  895810                  mov      dword ptr [eax + 0x10], ebx    
  0x00222366  895818                  mov      dword ptr [eax + 0x18], ebx    
  0x00222369  895814                  mov      dword ptr [eax + 0x14], ebx    
  0x0022236C  88581c                  mov      byte ptr [eax + 0x1c], bl      
  0x0022236F  88581d                  mov      byte ptr [eax + 0x1d], bl      
  0x00222372  88581e                  mov      byte ptr [eax + 0x1e], bl      
  0x00222375  c6402802                mov      byte ptr [eax + 0x28], 2       
  0x00222379  c6402901                mov      byte ptr [eax + 0x29], 1       
  0x0022237D  6689582a                mov      word ptr [eax + 0x2a], bx      
  0x00222381  660fb64e01              movzx    cx, byte ptr [esi + 1]         
  0x00222386  6689482c                mov      word ptr [eax + 0x2c], cx      
  0x0022238A  50                      push     eax                            
  0x0022238B  8bcf                    mov      ecx, edi                       
  0x0022238D  6689582e                mov      word ptr [eax + 0x2e], bx      
  0x00222391  e889f7ffff              call     0x221b1f                       ; -> sub_00221B1F
                                        ; XREF: 0x00222339 (jump), 0x00222350 (jump)
  0x00222396  5b                      pop      ebx                            
                                        ; XREF: 0x002222EC (jump)
  0x00222397  5f                      pop      edi                            
  0x00222398  5e                      pop      esi                            
  0x00222399  c20800                  ret      8                              
                                        ; XREF: 0x0022256B (data_imm)
  0x0022239C  57                      push     edi                            
  0x0022239D  8b7c240c                mov      edi, dword ptr [esp + 0xc]     
  0x002223A1  8bcf                    mov      ecx, edi                       
  0x002223A3  e82ef4ffff              call     0x2217d6                       ; -> sub_002217D6
  0x002223A8  8a08                    mov      cl, byte ptr [eax]             
  0x002223AA  f6c102                  test     cl, 2                          
  0x002223AD  740b                    je       0x2223ba                       
  0x002223AF  57                      push     edi                            
  0x002223B0  e852fdffff              call     0x222107                       ; -> sub_00222107
  0x002223B5  e99e000000              jmp      0x222458                       
                                        ; XREF: 0x002223AD (cond_jump)
  0x002223BA  56                      push     esi                            
  0x002223BB  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x002223BF  33d2                    xor      edx, edx                       
  0x002223C1  395604                  cmp      dword ptr [esi + 4], edx       
  0x002223C4  7d28                    jge      0x2223ee                       
  0x002223C6  fe4006                  inc      byte ptr [eax + 6]             
  0x002223C9  80780603                cmp      byte ptr [eax + 6], 3          
  0x002223CD  760e                    jbe      0x2223dd                       
  0x002223CF  80c908                  or       cl, 8                          
  0x002223D2  8808                    mov      byte ptr [eax], cl             
  0x002223D4  8bcf                    mov      ecx, edi                       
  0x002223D6  e848e8ffff              call     0x220c23                       ; -> sub_00220C23
  0x002223DB  eb7a                    jmp      0x222457                       
                                        ; XREF: 0x002223CD (cond_jump)
  0x002223DD  c7461404000000          mov      dword ptr [esi + 0x14], 4      
  0x002223E4  56                      push     esi                            
                                        ; XREF: 0x0022244F (jump)
  0x002223E5  8bcf                    mov      ecx, edi                       
  0x002223E7  e833f7ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x002223EC  eb69                    jmp      0x222457                       
                                        ; XREF: 0x002223C4 (cond_jump)
  0x002223EE  668b483a                mov      cx, word ptr [eax + 0x3a]      
  0x002223F2  f6c101                  test     cl, 1                          
  0x002223F5  885006                  mov      byte ptr [eax + 6], dl         
  0x002223F8  7409                    je       0x222403                       
  0x002223FA  33f6                    xor      esi, esi                       
  0x002223FC  6681e1feff              and      cx, 0xfffe                     
  0x00222401  eb0d                    jmp      0x222410                       
                                        ; XREF: 0x002223F8 (cond_jump)
  0x00222403  f6c102                  test     cl, 2                          
  0x00222406  7449                    je       0x222451                       
  0x00222408  33f6                    xor      esi, esi                       
  0x0022240A  46                      inc      esi                            
  0x0022240B  6681e1fdff              and      cx, 0xfffd                     
                                        ; XREF: 0x00222401 (jump)
  0x00222410  6689483a                mov      word ptr [eax + 0x3a], cx      
  0x00222414  8d4808                  lea      ecx, [eax + 8]                 
  0x00222417  c60130                  mov      byte ptr [ecx], 0x30           
  0x0022241A  c6400940                mov      byte ptr [eax + 9], 0x40       
  0x0022241E  c7401025222200          mov      dword ptr [eax + 0x10], 0x222225 
  0x00222425  897814                  mov      dword ptr [eax + 0x14], edi    
  0x00222428  895018                  mov      dword ptr [eax + 0x18], edx    
  0x0022242B  895020                  mov      dword ptr [eax + 0x20], edx    
  0x0022242E  89501c                  mov      dword ptr [eax + 0x1c], edx    
  0x00222431  885024                  mov      byte ptr [eax + 0x24], dl      
  0x00222434  885025                  mov      byte ptr [eax + 0x25], dl      
  0x00222437  885026                  mov      byte ptr [eax + 0x26], dl      
  0x0022243A  c6403020                mov      byte ptr [eax + 0x30], 0x20    
  0x0022243E  c6403101                mov      byte ptr [eax + 0x31], 1       
  0x00222442  66897032                mov      word ptr [eax + 0x32], si      
  0x00222446  66895034                mov      word ptr [eax + 0x34], dx      
  0x0022244A  66895036                mov      word ptr [eax + 0x36], dx      
  0x0022244E  51                      push     ecx                            
  0x0022244F  eb94                    jmp      0x2223e5                       
                                        ; XREF: 0x00222406 (cond_jump)
  0x00222451  57                      push     edi                            
  0x00222452  e870000000              call     0x2224c7                       ; -> sub_002224C7
                                        ; XREF: 0x002223DB (jump), 0x002223EC (jump)
  0x00222457  5e                      pop      esi                            
                                        ; XREF: 0x002223B5 (jump)
  0x00222458  5f                      pop      edi                            
  0x00222459  c20800                  ret      8                              
                                        ; XREF: 0x002226B6 (data_imm)
  0x0022245C  56                      push     esi                            
  0x0022245D  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00222461  8bce                    mov      ecx, esi                       
  0x00222463  e86ef3ffff              call     0x2217d6                       ; -> sub_002217D6
  0x00222468  8a4803                  mov      cl, byte ptr [eax + 3]         
  0x0022246B  3a4802                  cmp      cl, byte ptr [eax + 2]         
  0x0022246E  7537                    jne      0x2224a7                       
  0x00222470  8b483c                  mov      ecx, dword ptr [eax + 0x3c]    
  0x00222473  894818                  mov      dword ptr [eax + 0x18], ecx    
  0x00222476  8d4838                  lea      ecx, [eax + 0x38]              
  0x00222479  894820                  mov      dword ptr [eax + 0x20], ecx    
  0x0022247C  0fb64807                movzx    ecx, byte ptr [eax + 7]        
  0x00222480  c6400300                mov      byte ptr [eax + 3], 0          
  0x00222484  c6400828                mov      byte ptr [eax + 8], 0x28       
  0x00222488  c6400941                mov      byte ptr [eax + 9], 0x41       
  0x0022248C  c74010d0222200          mov      dword ptr [eax + 0x10], 0x2222d0 
  0x00222493  897014                  mov      dword ptr [eax + 0x14], esi    
  0x00222496  89481c                  mov      dword ptr [eax + 0x1c], ecx    
  0x00222499  c6402402                mov      byte ptr [eax + 0x24], 2       
  0x0022249D  c6402501                mov      byte ptr [eax + 0x25], 1       
  0x002224A1  c6402600                mov      byte ptr [eax + 0x26], 0       
  0x002224A5  eb11                    jmp      0x2224b8                       
                                        ; XREF: 0x0022246E (cond_jump)
  0x002224A7  8b542408                mov      edx, dword ptr [esp + 8]       
  0x002224AB  fec1                    inc      cl                             
  0x002224AD  884803                  mov      byte ptr [eax + 3], cl         
  0x002224B0  660fb6c9                movzx    cx, cl                         
  0x002224B4  66894a2c                mov      word ptr [edx + 0x2c], cx      
                                        ; XREF: 0x002224A5 (jump)
  0x002224B8  83c008                  add      eax, 8                         
  0x002224BB  50                      push     eax                            
  0x002224BC  8bce                    mov      ecx, esi                       
  0x002224BE  e85cf6ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x002224C3  5e                      pop      esi                            
  0x002224C4  c20800                  ret      8                              

; ============================================================
; Function: sub_002224C7
; Start: 0x002224C7  End: 0x0022259A  Size: 211 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002217D6, sub_00221B1F, sub_00221D43
; Called by: sub_0022259A
; ============================================================
sub_002224C7:
  0x002224C7  55                      push     ebp                            
  0x002224C8  8bec                    mov      ebp, esp                       
  0x002224CA  53                      push     ebx                            
  0x002224CB  56                      push     esi                            
  0x002224CC  57                      push     edi                            
  0x002224CD  8b7d08                  mov      edi, dword ptr [ebp + 8]       
  0x002224D0  8bcf                    mov      ecx, edi                       
  0x002224D2  e8fff2ffff              call     0x2217d6                       ; -> sub_002217D6
  0x002224D7  8a5804                  mov      bl, byte ptr [eax + 4]         
  0x002224DA  33c9                    xor      ecx, ecx                       
  0x002224DC  b201                    mov      dl, 1                          
  0x002224DE  884803                  mov      byte ptr [eax + 3], cl         
  0x002224E1  885d0b                  mov      byte ptr [ebp + 0xb], bl       
                                        ; XREF: 0x002224F4 (cond_jump)
  0x002224E4  84550b                  test     byte ptr [ebp + 0xb], dl       
  0x002224E7  750f                    jne      0x2224f8                       
  0x002224E9  fe4003                  inc      byte ptr [eax + 3]             
  0x002224EC  8a5803                  mov      bl, byte ptr [eax + 3]         
  0x002224EF  d0e2                    shl      dl, 1                          
  0x002224F1  3a5802                  cmp      bl, byte ptr [eax + 2]         
  0x002224F4  76ee                    jbe      0x2224e4                       
  0x002224F6  eb08                    jmp      0x222500                       
                                        ; XREF: 0x002224E7 (cond_jump)
  0x002224F8  f6d2                    not      dl                             
  0x002224FA  225004                  and      dl, byte ptr [eax + 4]         
  0x002224FD  885004                  mov      byte ptr [eax + 4], dl         
                                        ; XREF: 0x002224F6 (jump)
  0x00222500  8a5803                  mov      bl, byte ptr [eax + 3]         
  0x00222503  3a5802                  cmp      bl, byte ptr [eax + 2]         
  0x00222506  884826                  mov      byte ptr [eax + 0x26], cl      
  0x00222509  c6402402                mov      byte ptr [eax + 0x24], 2       
  0x0022250D  897814                  mov      dword ptr [eax + 0x14], edi    
  0x00222510  8d7008                  lea      esi, [eax + 8]                 
  0x00222513  762e                    jbe      0x222543                       
  0x00222515  8b503c                  mov      edx, dword ptr [eax + 0x3c]    
  0x00222518  895018                  mov      dword ptr [eax + 0x18], edx    
  0x0022251B  8d5038                  lea      edx, [eax + 0x38]              
  0x0022251E  895020                  mov      dword ptr [eax + 0x20], edx    
  0x00222521  0fb65007                movzx    edx, byte ptr [eax + 7]        
  0x00222525  51                      push     ecx                            
  0x00222526  50                      push     eax                            
  0x00222527  c60628                  mov      byte ptr [esi], 0x28           
  0x0022252A  c6400941                mov      byte ptr [eax + 9], 0x41       
  0x0022252E  c74010d0222200          mov      dword ptr [eax + 0x10], 0x2222d0 
  0x00222535  89501c                  mov      dword ptr [eax + 0x1c], edx    
  0x00222538  c6402501                mov      byte ptr [eax + 0x25], 1       
  0x0022253C  e802f8ffff              call     0x221d43                       ; -> sub_00221D43
  0x00222541  eb48                    jmp      0x22258b                       
                                        ; XREF: 0x00222513 (cond_jump)
  0x00222543  3ad9                    cmp      bl, cl                         
  0x00222545  8d5038                  lea      edx, [eax + 0x38]              
  0x00222548  6a04                    push     4                              
  0x0022254A  895020                  mov      dword ptr [eax + 0x20], edx    
  0x0022254D  5a                      pop      edx                            
  0x0022254E  66894832                mov      word ptr [eax + 0x32], cx      
  0x00222552  884831                  mov      byte ptr [eax + 0x31], cl      
  0x00222555  884825                  mov      byte ptr [eax + 0x25], cl      
  0x00222558  894818                  mov      dword ptr [eax + 0x18], ecx    
  0x0022255B  c6400940                mov      byte ptr [eax + 9], 0x40       
  0x0022255F  c60630                  mov      byte ptr [esi], 0x30           
  0x00222562  66895036                mov      word ptr [eax + 0x36], dx      
  0x00222566  89501c                  mov      dword ptr [eax + 0x1c], edx    
  0x00222569  750d                    jne      0x222578                       
  0x0022256B  c740109c232200          mov      dword ptr [eax + 0x10], 0x22239c 
  0x00222572  c64030a0                mov      byte ptr [eax + 0x30], 0xa0    
  0x00222576  eb0f                    jmp      0x222587                       
                                        ; XREF: 0x00222569 (cond_jump)
  0x00222578  c74010ca212200          mov      dword ptr [eax + 0x10], 0x2221ca 
  0x0022257F  c64030a3                mov      byte ptr [eax + 0x30], 0xa3    
  0x00222583  660fb6cb                movzx    cx, bl                         
                                        ; XREF: 0x00222576 (jump)
  0x00222587  66894834                mov      word ptr [eax + 0x34], cx      
                                        ; XREF: 0x00222541 (jump)
  0x0022258B  56                      push     esi                            
  0x0022258C  8bcf                    mov      ecx, edi                       
  0x0022258E  e88cf5ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222593  5f                      pop      edi                            
  0x00222594  5e                      pop      esi                            
  0x00222595  5b                      pop      ebx                            
  0x00222596  5d                      pop      ebp                            
  0x00222597  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_0022259A
; Start: 0x0022259A  End: 0x002225CA  Size: 48 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002217D6, sub_00221E4D, sub_00222107, sub_002224C7
; Called by: sub_00221E4D
; ============================================================
sub_0022259A:
  0x0022259A  56                      push     esi                            
  0x0022259B  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0022259F  8bce                    mov      ecx, esi                       
  0x002225A1  e830f2ffff              call     0x2217d6                       ; -> sub_002217D6
  0x002225A6  f60002                  test     byte ptr [eax], 2              
  0x002225A9  56                      push     esi                            
  0x002225AA  7407                    je       0x2225b3                       
  0x002225AC  e856fbffff              call     0x222107                       ; -> sub_00222107
  0x002225B1  eb13                    jmp      0x2225c6                       
                                        ; XREF: 0x002225AA (cond_jump)
  0x002225B3  6683783a00              cmp      word ptr [eax + 0x3a], 0       
  0x002225B8  7407                    je       0x2225c1                       
  0x002225BA  e88ef8ffff              call     0x221e4d                       ; -> sub_00221E4D
  0x002225BF  eb05                    jmp      0x2225c6                       
                                        ; XREF: 0x002225B8 (cond_jump)
  0x002225C1  e801ffffff              call     0x2224c7                       ; -> sub_002224C7
                                        ; XREF: 0x002225B1 (jump), 0x002225BF (jump)
  0x002225C6  5e                      pop      esi                            
  0x002225C7  c20800                  ret      8                              
; end of function
                                        ; XREF: 0x00221D07 (data_imm)
  0x002225CA  53                      push     ebx                            
  0x002225CB  56                      push     esi                            
  0x002225CC  57                      push     edi                            
  0x002225CD  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x002225D1  8bcf                    mov      ecx, edi                       
  0x002225D3  e8fef1ffff              call     0x2217d6                       ; -> sub_002217D6
  0x002225D8  8bf0                    mov      esi, eax                       
  0x002225DA  80663afe                and      byte ptr [esi + 0x3a], 0xfe    
  0x002225DE  33c0                    xor      eax, eax                       
  0x002225E0  8a4603                  mov      al, byte ptr [esi + 3]         
  0x002225E3  33c9                    xor      ecx, ecx                       
  0x002225E5  8ac8                    mov      cl, al                         
  0x002225E7  b301                    mov      bl, 1                          
  0x002225E9  6a05                    push     5                              
  0x002225EB  50                      push     eax                            
  0x002225EC  49                      dec      ecx                            
  0x002225ED  d2e3                    shl      bl, cl                         
  0x002225EF  8bcf                    mov      ecx, edi                       
  0x002225F1  e8c5e1ffff              call     0x2207bb                       ; -> sub_002207BB
  0x002225F6  660fb65603              movzx    dx, byte ptr [esi + 3]         
  0x002225FB  085e05                  or       byte ptr [esi + 5], bl         
  0x002225FE  33c9                    xor      ecx, ecx                       
  0x00222600  8d4608                  lea      eax, [esi + 8]                 
  0x00222603  894e18                  mov      dword ptr [esi + 0x18], ecx    
  0x00222606  894e20                  mov      dword ptr [esi + 0x20], ecx    
  0x00222609  894e1c                  mov      dword ptr [esi + 0x1c], ecx    
  0x0022260C  884e24                  mov      byte ptr [esi + 0x24], cl      
  0x0022260F  884e25                  mov      byte ptr [esi + 0x25], cl      
  0x00222612  884e26                  mov      byte ptr [esi + 0x26], cl      
  0x00222615  66894e36                mov      word ptr [esi + 0x36], cx      
  0x00222619  50                      push     eax                            
  0x0022261A  8bcf                    mov      ecx, edi                       
  0x0022261C  c60030                  mov      byte ptr [eax], 0x30           
  0x0022261F  c6460940                mov      byte ptr [esi + 9], 0x40       
  0x00222623  c746109a252200          mov      dword ptr [esi + 0x10], 0x22259a 
  0x0022262A  897e14                  mov      dword ptr [esi + 0x14], edi    
  0x0022262D  c6463023                mov      byte ptr [esi + 0x30], 0x23    
  0x00222631  c6463101                mov      byte ptr [esi + 0x31], 1       
  0x00222635  66c746321000            mov      word ptr [esi + 0x32], 0x10    
  0x0022263B  66895634                mov      word ptr [esi + 0x34], dx      
  0x0022263F  e8dbf4ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222644  5f                      pop      edi                            
  0x00222645  5e                      pop      esi                            
  0x00222646  5b                      pop      ebx                            
  0x00222647  c20800                  ret      8                              
                                        ; XREF: 0x00222727 (data_imm)
  0x0022264A  53                      push     ebx                            
  0x0022264B  56                      push     esi                            
  0x0022264C  57                      push     edi                            
  0x0022264D  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x00222651  8bcf                    mov      ecx, edi                       
  0x00222653  e87ef1ffff              call     0x2217d6                       ; -> sub_002217D6
  0x00222658  68d06c2800              push     0x286cd0                       
  0x0022265D  8bf0                    mov      esi, eax                       
  0x0022265F  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00222665  8b442410                mov      eax, dword ptr [esp + 0x10]    
  0x00222669  33db                    xor      ebx, ebx                       
  0x0022266B  395804                  cmp      dword ptr [eax + 4], ebx       
  0x0022266E  7d08                    jge      0x222678                       
  0x00222670  57                      push     edi                            
  0x00222671  e891faffff              call     0x222107                       ; -> sub_00222107
  0x00222676  eb77                    jmp      0x2226ef                       
                                        ; XREF: 0x0022266E (cond_jump)
  0x00222678  a06a6c2800              mov      al, byte ptr [0x286c6a]        
  0x0022267D  3c07                    cmp      al, 7                          
  0x0022267F  884602                  mov      byte ptr [esi + 2], al         
  0x00222682  7604                    jbe      0x222688                       
  0x00222684  c6460207                mov      byte ptr [esi + 2], 7          
                                        ; XREF: 0x00222682 (cond_jump)
  0x00222688  6a03                    push     3                              
  0x0022268A  e85bf7ffff              call     0x221dea                       ; -> sub_00221DEA
  0x0022268F  6a01                    push     1                              
  0x00222691  56                      push     esi                            
  0x00222692  8935186d2800            mov      dword ptr [0x286d18], esi      
  0x00222698  e8a6f6ffff              call     0x221d43                       ; -> sub_00221D43
  0x0022269D  53                      push     ebx                            
  0x0022269E  8bcf                    mov      ecx, edi                       
  0x002226A0  e85ce7ffff              call     0x220e01                       ; -> sub_00220E01
  0x002226A5  8d4608                  lea      eax, [esi + 8]                 
  0x002226A8  50                      push     eax                            
  0x002226A9  8bcf                    mov      ecx, edi                       
  0x002226AB  c6460301                mov      byte ptr [esi + 3], 1          
  0x002226AF  c60030                  mov      byte ptr [eax], 0x30           
  0x002226B2  c6460940                mov      byte ptr [esi + 9], 0x40       
  0x002226B6  c746105c242200          mov      dword ptr [esi + 0x10], 0x22245c 
  0x002226BD  897e14                  mov      dword ptr [esi + 0x14], edi    
  0x002226C0  895e18                  mov      dword ptr [esi + 0x18], ebx    
  0x002226C3  895e20                  mov      dword ptr [esi + 0x20], ebx    
  0x002226C6  895e1c                  mov      dword ptr [esi + 0x1c], ebx    
  0x002226C9  885e24                  mov      byte ptr [esi + 0x24], bl      
  0x002226CC  885e25                  mov      byte ptr [esi + 0x25], bl      
  0x002226CF  885e26                  mov      byte ptr [esi + 0x26], bl      
  0x002226D2  c6463023                mov      byte ptr [esi + 0x30], 0x23    
  0x002226D6  c6463103                mov      byte ptr [esi + 0x31], 3       
  0x002226DA  66c746320800            mov      word ptr [esi + 0x32], 8       
  0x002226E0  66c746340100            mov      word ptr [esi + 0x34], 1       
  0x002226E6  66895e36                mov      word ptr [esi + 0x36], bx      
  0x002226EA  e830f4ffff              call     0x221b1f                       ; -> sub_00221B1F
                                        ; XREF: 0x00222676 (jump)
  0x002226EF  5f                      pop      edi                            
  0x002226F0  5e                      pop      esi                            
  0x002226F1  5b                      pop      ebx                            
  0x002226F2  c20800                  ret      8                              
                                        ; XREF: 0x00222840 (data_imm)
  0x002226F5  56                      push     esi                            
  0x002226F6  68d06c2800              push     0x286cd0                       
  0x002226FB  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00222701  8b742408                mov      esi, dword ptr [esp + 8]       
  0x00222705  33c0                    xor      eax, eax                       
  0x00222707  394604                  cmp      dword ptr [esi + 4], eax       
  0x0022270A  7d0b                    jge      0x222717                       
  0x0022270C  ff74240c                push     dword ptr [esp + 0xc]          
  0x00222710  e8f2f9ffff              call     0x222107                       ; -> sub_00222107
  0x00222715  eb56                    jmp      0x22276d                       
                                        ; XREF: 0x0022270A (cond_jump)
  0x00222717  57                      push     edi                            
  0x00222718  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x0022271C  6a08                    push     8                              
  0x0022271E  59                      pop      ecx                            
  0x0022271F  50                      push     eax                            
  0x00222720  c60630                  mov      byte ptr [esi], 0x30           
  0x00222723  c6460140                mov      byte ptr [esi + 1], 0x40       
  0x00222727  c746084a262200          mov      dword ptr [esi + 8], 0x22264a  
  0x0022272E  897e0c                  mov      dword ptr [esi + 0xc], edi     
  0x00222731  894610                  mov      dword ptr [esi + 0x10], eax    
  0x00222734  c74618686c2800          mov      dword ptr [esi + 0x18], 0x286c68 
  0x0022273B  894e14                  mov      dword ptr [esi + 0x14], ecx    
  0x0022273E  c6461c02                mov      byte ptr [esi + 0x1c], 2       
  0x00222742  c6461d01                mov      byte ptr [esi + 0x1d], 1       
  0x00222746  88461e                  mov      byte ptr [esi + 0x1e], al      
  0x00222749  c64628a0                mov      byte ptr [esi + 0x28], 0xa0    
  0x0022274D  c6462906                mov      byte ptr [esi + 0x29], 6       
  0x00222751  66c7462a0029            mov      word ptr [esi + 0x2a], 0x2900  
  0x00222757  6689462c                mov      word ptr [esi + 0x2c], ax      
  0x0022275B  66894e2e                mov      word ptr [esi + 0x2e], cx      
  0x0022275F  e886f6ffff              call     0x221dea                       ; -> sub_00221DEA
  0x00222764  56                      push     esi                            
  0x00222765  8bcf                    mov      ecx, edi                       
  0x00222767  e8b3f3ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x0022276C  5f                      pop      edi                            
                                        ; XREF: 0x00222715 (jump)
  0x0022276D  5e                      pop      esi                            
  0x0022276E  c20800                  ret      8                              

; ============================================================
; Function: sub_00222771
; Start: 0x00222771  End: 0x00222897  Size: 294 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002217D6, sub_00221B1F, sub_00221DEA, sub_002220E5
; ============================================================
sub_00222771:
  0x00222771  55                      push     ebp                            
  0x00222772  8bec                    mov      ebp, esp                       
  0x00222774  8b4d0c                  mov      ecx, dword ptr [ebp + 0xc]     
  0x00222777  53                      push     ebx                            
  0x00222778  56                      push     esi                            
  0x00222779  57                      push     edi                            
  0x0022277A  e857f0ffff              call     0x2217d6                       ; -> sub_002217D6
  0x0022277F  68d06c2800              push     0x286cd0                       
  0x00222784  8bf8                    mov      edi, eax                       
  0x00222786  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x0022278C  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x0022278F  33db                    xor      ebx, ebx                       
  0x00222791  395e04                  cmp      dword ptr [esi + 4], ebx       
  0x00222794  0f8ced000000            jl       0x222887                       
  0x0022279A  668b0d6a6c2800          mov      cx, word ptr [0x286c6a]        
  0x002227A1  33d2                    xor      edx, edx                       
  0x002227A3  6683f930                cmp      cx, 0x30                       
  0x002227A7  b8686c2800              mov      eax, 0x286c68                  
  0x002227AC  0f87d5000000            ja       0x222887                       
  0x002227B2  0fb7c9                  movzx    ecx, cx                        
  0x002227B5  394e14                  cmp      dword ptr [esi + 0x14], ecx    
  0x002227B8  894d08                  mov      dword ptr [ebp + 8], ecx       
  0x002227BB  0f82c6000000            jb       0x222887                       
                                        ; XREF: 0x002227E3 (cond_jump)
  0x002227C1  8a00                    mov      al, byte ptr [eax]             
  0x002227C3  0fb6c8                  movzx    ecx, al                        
  0x002227C6  03d1                    add      edx, ecx                       
  0x002227C8  3ac3                    cmp      al, bl                         
  0x002227CA  0f84b7000000            je       0x222887                       
  0x002227D0  3b5508                  cmp      edx, dword ptr [ebp + 8]       
  0x002227D3  0f83ae000000            jae      0x222887                       
  0x002227D9  8d82686c2800            lea      eax, [edx + 0x286c68]          
  0x002227DF  80780105                cmp      byte ptr [eax + 1], 5          
  0x002227E3  75dc                    jne      0x2227c1                       
  0x002227E5  6683780404              cmp      word ptr [eax + 4], 4          
  0x002227EA  7708                    ja       0x2227f4                       
  0x002227EC  8a4804                  mov      cl, byte ptr [eax + 4]         
  0x002227EF  884f07                  mov      byte ptr [edi + 7], cl         
  0x002227F2  eb04                    jmp      0x2227f8                       
                                        ; XREF: 0x002227EA (cond_jump)
  0x002227F4  c6470704                mov      byte ptr [edi + 7], 4          
                                        ; XREF: 0x002227F2 (jump)
  0x002227F8  8a4802                  mov      cl, byte ptr [eax + 2]         
  0x002227FB  884f01                  mov      byte ptr [edi + 1], cl         
  0x002227FE  c60620                  mov      byte ptr [esi], 0x20           
  0x00222801  c6460102                mov      byte ptr [esi + 1], 2          
  0x00222805  895e08                  mov      dword ptr [esi + 8], ebx       
  0x00222808  8a4802                  mov      cl, byte ptr [eax + 2]         
  0x0022280B  884e15                  mov      byte ptr [esi + 0x15], cl      
  0x0022280E  8a4003                  mov      al, byte ptr [eax + 3]         
  0x00222811  8b4d0c                  mov      ecx, dword ptr [ebp + 0xc]     
  0x00222814  2403                    and      al, 3                          
  0x00222816  884616                  mov      byte ptr [esi + 0x16], al      
  0x00222819  c6461710                mov      byte ptr [esi + 0x17], 0x10    
  0x0022281D  660fb64707              movzx    ax, byte ptr [edi + 7]         
  0x00222822  56                      push     esi                            
  0x00222823  6689461c                mov      word ptr [esi + 0x1c], ax      
  0x00222827  e8f3f2ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x0022282C  85c0                    test     eax, eax                       
  0x0022282E  7c57                    jl       0x222887                       
  0x00222830  8b4610                  mov      eax, dword ptr [esi + 0x10]    
  0x00222833  89473c                  mov      dword ptr [edi + 0x3c], eax    
  0x00222836  8b7d0c                  mov      edi, dword ptr [ebp + 0xc]     
  0x00222839  c60630                  mov      byte ptr [esi], 0x30           
  0x0022283C  c6460140                mov      byte ptr [esi + 1], 0x40       
  0x00222840  c74608f5262200          mov      dword ptr [esi + 8], 0x2226f5  
  0x00222847  897e0c                  mov      dword ptr [esi + 0xc], edi     
  0x0022284A  895e10                  mov      dword ptr [esi + 0x10], ebx    
  0x0022284D  895e18                  mov      dword ptr [esi + 0x18], ebx    
  0x00222850  895e14                  mov      dword ptr [esi + 0x14], ebx    
  0x00222853  885e1c                  mov      byte ptr [esi + 0x1c], bl      
  0x00222856  885e1d                  mov      byte ptr [esi + 0x1d], bl      
  0x00222859  885e1e                  mov      byte ptr [esi + 0x1e], bl      
  0x0022285C  885e28                  mov      byte ptr [esi + 0x28], bl      
  0x0022285F  c6462909                mov      byte ptr [esi + 0x29], 9       
  0x00222863  660fb6056d6c2800        movzx    ax, byte ptr [0x286c6d]        
  0x0022286B  53                      push     ebx                            
  0x0022286C  6689462a                mov      word ptr [esi + 0x2a], ax      
  0x00222870  66895e2c                mov      word ptr [esi + 0x2c], bx      
  0x00222874  66895e2e                mov      word ptr [esi + 0x2e], bx      
  0x00222878  e86df5ffff              call     0x221dea                       ; -> sub_00221DEA
  0x0022287D  56                      push     esi                            
  0x0022287E  8bcf                    mov      ecx, edi                       
  0x00222880  e89af2ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222885  eb09                    jmp      0x222890                       
                                        ; XREF: 0x00222794 (cond_jump), 0x002227AC (cond_jump), 0x002227BB (cond_jump), 0x002227CA (cond_jump), 0x002227D3 (cond_jump), ... (+1 more)
  0x00222887  ff750c                  push     dword ptr [ebp + 0xc]          
  0x0022288A  56                      push     esi                            
  0x0022288B  e855f8ffff              call     0x2220e5                       ; -> sub_002220E5
                                        ; XREF: 0x00222885 (jump)
  0x00222890  5f                      pop      edi                            
  0x00222891  5e                      pop      esi                            
  0x00222892  5b                      pop      ebx                            
  0x00222893  5d                      pop      ebp                            
  0x00222894  c20800                  ret      8                              
; end of function
  0x00222897  66a1226d2800            mov      ax, word ptr [0x286d22]        
  0x0022289D  53                      push     ebx                            
  0x0022289E  56                      push     esi                            
  0x0022289F  33db                    xor      ebx, ebx                       
  0x002228A1  33f6                    xor      esi, esi                       
  0x002228A3  663b05206d2800          cmp      ax, word ptr [0x286d20]        
  0x002228AA  0f83b6000000            jae      0x222966                       
  0x002228B0  a1246d2800              mov      eax, dword ptr [0x286d24]      
  0x002228B5  f60001                  test     byte ptr [eax], 1              
  0x002228B8  740b                    je       0x2228c5                       
  0x002228BA  8bc8                    mov      ecx, eax                       
                                        ; XREF: 0x002228C3 (cond_jump)
  0x002228BC  83c140                  add      ecx, 0x40                      
  0x002228BF  46                      inc      esi                            
  0x002228C0  f60101                  test     byte ptr [ecx], 1              
  0x002228C3  75f7                    jne      0x2228bc                       
                                        ; XREF: 0x002228B8 (cond_jump)
  0x002228C5  66ff05226d2800          inc      word ptr [0x286d22]            
  0x002228CC  55                      push     ebp                            
  0x002228CD  8b6c2410                mov      ebp, dword ptr [esp + 0x10]    
  0x002228D1  c1e606                  shl      esi, 6                         
  0x002228D4  57                      push     edi                            
  0x002228D5  03f0                    add      esi, eax                       
  0x002228D7  56                      push     esi                            
  0x002228D8  8bcd                    mov      ecx, ebp                       
  0x002228DA  e8fbeeffff              call     0x2217da                       ; -> sub_002217DA
  0x002228DF  8a06                    mov      al, byte ptr [esi]             
  0x002228E1  24f5                    and      al, 0xf5                       
  0x002228E3  8d7e08                  lea      edi, [esi + 8]                 
  0x002228E6  0c01                    or       al, 1                          
  0x002228E8  57                      push     edi                            
  0x002228E9  8bcd                    mov      ecx, ebp                       
  0x002228EB  8806                    mov      byte ptr [esi], al             
  0x002228ED  885e05                  mov      byte ptr [esi + 5], bl         
  0x002228F0  885e06                  mov      byte ptr [esi + 6], bl         
  0x002228F3  c60720                  mov      byte ptr [edi], 0x20           
  0x002228F6  c6460982                mov      byte ptr [esi + 9], 0x82       
  0x002228FA  895e10                  mov      dword ptr [esi + 0x10], ebx    
  0x002228FD  e81df2ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222902  6a30                    push     0x30                           
  0x00222904  58                      pop      eax                            
  0x00222905  55                      push     ebp                            
  0x00222906  68791d2200              push     0x221d79                       
  0x0022290B  68f86c2800              push     0x286cf8                       
  0x00222910  8807                    mov      byte ptr [edi], al             
  0x00222912  c6460940                mov      byte ptr [esi + 9], 0x40       
  0x00222916  c7461071272200          mov      dword ptr [esi + 0x10], 0x222771 
  0x0022291D  896e14                  mov      dword ptr [esi + 0x14], ebp    
  0x00222920  895e18                  mov      dword ptr [esi + 0x18], ebx    
  0x00222923  c74620686c2800          mov      dword ptr [esi + 0x20], 0x286c68 
  0x0022292A  89461c                  mov      dword ptr [esi + 0x1c], eax    
  0x0022292D  c6462402                mov      byte ptr [esi + 0x24], 2       
  0x00222931  c6462501                mov      byte ptr [esi + 0x25], 1       
  0x00222935  885e26                  mov      byte ptr [esi + 0x26], bl      
  0x00222938  c6463080                mov      byte ptr [esi + 0x30], 0x80    
  0x0022293C  c6463106                mov      byte ptr [esi + 0x31], 6       
  0x00222940  66c746320002            mov      word ptr [esi + 0x32], 0x200   
  0x00222946  66895e34                mov      word ptr [esi + 0x34], bx      
  0x0022294A  66894636                mov      word ptr [esi + 0x36], ax      
  0x0022294E  ff153c5b2200            call     dword ptr [0x225b3c]           ; -> xbox_KeInitializeDpc
  0x00222954  53                      push     ebx                            
  0x00222955  e890f4ffff              call     0x221dea                       ; -> sub_00221DEA
  0x0022295A  57                      push     edi                            
  0x0022295B  8bcd                    mov      ecx, ebp                       
  0x0022295D  e8bdf1ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00222962  5f                      pop      edi                            
  0x00222963  5d                      pop      ebp                            
  0x00222964  eb0e                    jmp      0x222974                       
                                        ; XREF: 0x002228AA (cond_jump)
  0x00222966  8b4c240c                mov      ecx, dword ptr [esp + 0xc]     
  0x0022296A  6800010080              push     0x80000100                     
  0x0022296F  e88de4ffff              call     0x220e01                       ; -> sub_00220E01
                                        ; XREF: 0x00222964 (jump)
  0x00222974  5e                      pop      esi                            
  0x00222975  5b                      pop      ebx                            
  0x00222976  c20400                  ret      4                              

; ============================================================
; Function: sub_00222979
; Start: 0x00222979  End: 0x00222A08  Size: 143 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002209B9, sub_00220CE9
; Called by: sub_0021FB47, sub_00222A9D
; ============================================================
sub_00222979:
  0x00222979  51                      push     ecx                            
  0x0022297A  53                      push     ebx                            
  0x0022297B  55                      push     ebp                            
  0x0022297C  56                      push     esi                            
  0x0022297D  8bf1                    mov      esi, ecx                       
  0x0022297F  80be6004000000          cmp      byte ptr [esi + 0x460], 0      
  0x00222986  8bea                    mov      ebp, edx                       
  0x00222988  b301                    mov      bl, 1                          
  0x0022298A  7677                    jbe      0x222a03                       
  0x0022298C  885c240c                mov      byte ptr [esp + 0xc], bl       
  0x00222990  57                      push     edi                            
                                        ; XREF: 0x00222A00 (cond_jump)
  0x00222991  660fb6c3                movzx    ax, bl                         
  0x00222995  66854500                test     word ptr [ebp], ax             
  0x00222999  7453                    je       0x2229ee                       
  0x0022299B  33c9                    xor      ecx, ecx                       
  0x0022299D  668b4d02                mov      cx, word ptr [ebp + 2]         
  0x002229A1  23c8                    and      ecx, eax                       
  0x002229A3  6685c9                  test     cx, cx                         
  0x002229A6  7428                    je       0x2229d0                       
  0x002229A8  8d8e61040000            lea      ecx, [esi + 0x461]             
  0x002229AE  8a01                    mov      al, byte ptr [ecx]             
  0x002229B0  84c3                    test     bl, al                         
  0x002229B2  740c                    je       0x2229c0                       
  0x002229B4  ff742410                push     dword ptr [esp + 0x10]         
  0x002229B8  56                      push     esi                            
  0x002229B9  e82be3ffff              call     0x220ce9                       ; -> sub_00220CE9
  0x002229BE  eb04                    jmp      0x2229c4                       
                                        ; XREF: 0x002229B2 (cond_jump)
  0x002229C0  0ac3                    or       al, bl                         
  0x002229C2  8801                    mov      byte ptr [ecx], al             
                                        ; XREF: 0x002229BE (jump)
  0x002229C4  ff742410                push     dword ptr [esp + 0x10]         
  0x002229C8  56                      push     esi                            
  0x002229C9  e8ebdfffff              call     0x2209b9                       ; -> sub_002209B9
  0x002229CE  eb1e                    jmp      0x2229ee                       
                                        ; XREF: 0x002229A6 (cond_jump)
  0x002229D0  8dbe61040000            lea      edi, [esi + 0x461]             
  0x002229D6  8a07                    mov      al, byte ptr [edi]             
  0x002229D8  84c3                    test     bl, al                         
  0x002229DA  7412                    je       0x2229ee                       
  0x002229DC  ff742410                push     dword ptr [esp + 0x10]         
  0x002229E0  8acb                    mov      cl, bl                         
  0x002229E2  f6d1                    not      cl                             
  0x002229E4  22c8                    and      cl, al                         
  0x002229E6  56                      push     esi                            
  0x002229E7  880f                    mov      byte ptr [edi], cl             
  0x002229E9  e8fbe2ffff              call     0x220ce9                       ; -> sub_00220CE9
                                        ; XREF: 0x00222999 (cond_jump), 0x002229CE (jump), 0x002229DA (cond_jump)
  0x002229EE  fe442410                inc      byte ptr [esp + 0x10]          
  0x002229F2  8a442410                mov      al, byte ptr [esp + 0x10]      
  0x002229F6  d0e3                    shl      bl, 1                          
  0x002229F8  fec8                    dec      al                             
  0x002229FA  3a8660040000            cmp      al, byte ptr [esi + 0x460]     
  0x00222A00  728f                    jb       0x222991                       
  0x00222A02  5f                      pop      edi                            
                                        ; XREF: 0x0022298A (cond_jump)
  0x00222A03  5e                      pop      esi                            
  0x00222A04  5d                      pop      ebp                            
  0x00222A05  5b                      pop      ebx                            
  0x00222A06  59                      pop      ecx                            
  0x00222A07  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222A08
; Start: 0x00222A08  End: 0x00222A55  Size: 77 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_002209CE
; ============================================================
sub_00222A08:
  0x00222A08  55                      push     ebp                            
  0x00222A09  8bec                    mov      ebp, esp                       
  0x00222A0B  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x00222A0E  8b4d10                  mov      ecx, dword ptr [ebp + 0x10]    
  0x00222A11  8b550c                  mov      edx, dword ptr [ebp + 0xc]     
  0x00222A14  898870040000            mov      dword ptr [eax + 0x470], ecx   
  0x00222A1A  8b4d14                  mov      ecx, dword ptr [ebp + 0x14]    
  0x00222A1D  56                      push     esi                            
  0x00222A1E  898874040000            mov      dword ptr [eax + 0x474], ecx   
  0x00222A24  8b08                    mov      ecx, dword ptr [eax]           
  0x00222A26  66c745081000            mov      word ptr [ebp + 8], 0x10       
  0x00222A2C  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x00222A2F  89749150                mov      dword ptr [ecx + edx*4 + 0x50], esi 
  0x00222A33  8db0a0040000            lea      esi, [eax + 0x4a0]             
  0x00222A39  56                      push     esi                            
  0x00222A3A  83caff                  or       edx, 0xffffffff                
  0x00222A3D  52                      push     edx                            
  0x00222A3E  b9c0bdf0ff              mov      ecx, 0xfff0bdc0                
  0x00222A43  51                      push     ecx                            
  0x00222A44  0578040000              add      eax, 0x478                     
  0x00222A49  50                      push     eax                            
  0x00222A4A  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
  0x00222A50  5e                      pop      esi                            
  0x00222A51  5d                      pop      ebp                            
  0x00222A52  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_00222A55
; Start: 0x00222A55  End: 0x00222A72  Size: 29 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_00220D2F
; ============================================================
sub_00222A55:
  0x00222A55  55                      push     ebp                            
  0x00222A56  8bec                    mov      ebp, esp                       
  0x00222A58  51                      push     ecx                            
  0x00222A59  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x00222A5C  8b00                    mov      eax, dword ptr [eax]           
  0x00222A5E  8b4d0c                  mov      ecx, dword ptr [ebp + 0xc]     
  0x00222A61  66c745fc0100            mov      word ptr [ebp - 4], 1          
  0x00222A67  8b55fc                  mov      edx, dword ptr [ebp - 4]       
  0x00222A6A  89548850                mov      dword ptr [eax + ecx*4 + 0x50], edx 
  0x00222A6E  c9                      leave                                   
  0x00222A6F  c20800                  ret      8                              
; end of function
                                        ; XREF: 0x0021FB63 (data_imm)
  0x00222A72  8b4c2408                mov      ecx, dword ptr [esp + 8]       
  0x00222A76  8d8170040000            lea      eax, [ecx + 0x470]             
  0x00222A7C  8b10                    mov      edx, dword ptr [eax]           
  0x00222A7E  81c174040000            add      ecx, 0x474                     
  0x00222A84  85d2                    test     edx, edx                       
  0x00222A86  56                      push     esi                            
  0x00222A87  8b31                    mov      esi, dword ptr [ecx]           
  0x00222A89  740e                    je       0x222a99                       
  0x00222A8B  832000                  and      dword ptr [eax], 0             
  0x00222A8E  832100                  and      dword ptr [ecx], 0             
  0x00222A91  56                      push     esi                            
  0x00222A92  6800060080              push     0x80000600                     
  0x00222A97  ffd2                    call     edx                            
                                        ; XREF: 0x00222A89 (cond_jump)
  0x00222A99  5e                      pop      esi                            
  0x00222A9A  c21000                  ret      0x10                           

; ============================================================
; Function: sub_00222A9D
; Start: 0x00222A9D  End: 0x00222B5C  Size: 191 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00222979
; Called by: sub_00224CAA
; ============================================================
sub_00222A9D:
  0x00222A9D  55                      push     ebp                            
  0x00222A9E  8bec                    mov      ebp, esp                       
  0x00222AA0  83ec1c                  sub      esp, 0x1c                      
  0x00222AA3  56                      push     esi                            
  0x00222AA4  8bf1                    mov      esi, ecx                       
  0x00222AA6  8b06                    mov      eax, dword ptr [esi]           
  0x00222AA8  0fb69660040000          movzx    edx, byte ptr [esi + 0x460]    
  0x00222AAF  8d4854                  lea      ecx, [eax + 0x54]              
  0x00222AB2  8b01                    mov      eax, dword ptr [ecx]           
  0x00222AB4  57                      push     edi                            
  0x00222AB5  33c0                    xor      eax, eax                       
  0x00222AB7  85d2                    test     edx, edx                       
  0x00222AB9  8d7df8                  lea      edi, [ebp - 8]                 
  0x00222ABC  ab                      stosd    dword ptr es:[edi], eax        
  0x00222ABD  c745f401000000          mov      dword ptr [ebp - 0xc], 1       
  0x00222AC4  0f8684000000            jbe      0x222b4e                       
  0x00222ACA  894df0                  mov      dword ptr [ebp - 0x10], ecx    
  0x00222ACD  8955ec                  mov      dword ptr [ebp - 0x14], edx    
  0x00222AD0  53                      push     ebx                            
                                        ; XREF: 0x00222B4B (cond_jump)
  0x00222AD1  8b39                    mov      edi, dword ptr [ecx]           
  0x00222AD3  897dfc                  mov      dword ptr [ebp - 4], edi       
  0x00222AD6  f645fe10                test     byte ptr [ebp - 2], 0x10       
  0x00222ADA  743f                    je       0x222b1b                       
  0x00222ADC  8b8e74040000            mov      ecx, dword ptr [esi + 0x474]   
  0x00222AE2  8d9e70040000            lea      ebx, [esi + 0x470]             
  0x00222AE8  8b03                    mov      eax, dword ptr [ebx]           
  0x00222AEA  85c0                    test     eax, eax                       
  0x00222AEC  8945e4                  mov      dword ptr [ebp - 0x1c], eax    
  0x00222AEF  894de8                  mov      dword ptr [ebp - 0x18], ecx    
  0x00222AF2  7427                    je       0x222b1b                       
  0x00222AF4  8d8678040000            lea      eax, [esi + 0x478]             
  0x00222AFA  50                      push     eax                            
  0x00222AFB  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00222B01  ff75e8                  push     dword ptr [ebp - 0x18]         
  0x00222B04  832300                  and      dword ptr [ebx], 0             
  0x00222B07  83a67404000000          and      dword ptr [esi + 0x474], 0     
  0x00222B0E  81e700020000            and      edi, 0x200                     
  0x00222B14  c1e70f                  shl      edi, 0xf                       
  0x00222B17  57                      push     edi                            
  0x00222B18  ff55e4                  call     dword ptr [ebp - 0x1c]         
                                        ; XREF: 0x00222ADA (cond_jump), 0x00222AF2 (cond_jump)
  0x00222B1B  f645fe01                test     byte ptr [ebp - 2], 1          
  0x00222B1F  7411                    je       0x222b32                       
  0x00222B21  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x00222B24  660945f8                or       word ptr [ebp - 8], ax         
  0x00222B28  f645fc01                test     byte ptr [ebp - 4], 1          
  0x00222B2C  7404                    je       0x222b32                       
  0x00222B2E  660945fa                or       word ptr [ebp - 6], ax         
                                        ; XREF: 0x00222B1F (cond_jump), 0x00222B2C (cond_jump)
  0x00222B32  668365fc00              and      word ptr [ebp - 4], 0          
  0x00222B37  8b4df0                  mov      ecx, dword ptr [ebp - 0x10]    
  0x00222B3A  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x00222B3D  d165f4                  shl      dword ptr [ebp - 0xc], 1       
  0x00222B40  8901                    mov      dword ptr [ecx], eax           
  0x00222B42  83c104                  add      ecx, 4                         
  0x00222B45  ff4dec                  dec      dword ptr [ebp - 0x14]         
  0x00222B48  894df0                  mov      dword ptr [ebp - 0x10], ecx    
  0x00222B4B  7584                    jne      0x222ad1                       
  0x00222B4D  5b                      pop      ebx                            
                                        ; XREF: 0x00222AC4 (cond_jump)
  0x00222B4E  8d55f8                  lea      edx, [ebp - 8]                 
  0x00222B51  8bce                    mov      ecx, esi                       
  0x00222B53  e821feffff              call     0x222979                       ; -> sub_00222979
  0x00222B58  5f                      pop      edi                            
  0x00222B59  5e                      pop      esi                            
  0x00222B5A  c9                      leave                                   
  0x00222B5B  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222B5C
; Start: 0x00222B5C  End: 0x00222B6F  Size: 19 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FC45, sub_00222B6F
; ============================================================
sub_00222B5C:
  0x00222B5C  a188782800              mov      eax, dword ptr [0x287888]      
  0x00222B61  85c0                    test     eax, eax                       
  0x00222B63  7409                    je       0x222b6e                       
  0x00222B65  8b4818                  mov      ecx, dword ptr [eax + 0x18]    
  0x00222B68  890d88782800            mov      dword ptr [0x287888], ecx      
                                        ; XREF: 0x00222B63 (cond_jump)
  0x00222B6E  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222B6F
; Start: 0x00222B6F  End: 0x00222CE3  Size: 372 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00222B5C, sub_002231B8, sub_00224167, sub_00224281
; Called by: sub_00223032
; ============================================================
sub_00222B6F:
  0x00222B6F  55                      push     ebp                            
  0x00222B70  8bec                    mov      ebp, esp                       
  0x00222B72  83ec0c                  sub      esp, 0xc                       
  0x00222B75  8365f800                and      dword ptr [ebp - 8], 0         
  0x00222B79  53                      push     ebx                            
  0x00222B7A  56                      push     esi                            
  0x00222B7B  8bda                    mov      ebx, edx                       
  0x00222B7D  894df4                  mov      dword ptr [ebp - 0xc], ecx     
  0x00222B80  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00222B86  8845ff                  mov      byte ptr [ebp - 1], al         
  0x00222B89  e8ceffffff              call     0x222b5c                       ; -> sub_00222B5C
  0x00222B8E  8bf0                    mov      esi, eax                       
  0x00222B90  85f6                    test     esi, esi                       
  0x00222B92  750c                    jne      0x222ba0                       
  0x00222B94  c745f800010080          mov      dword ptr [ebp - 8], 0x80000100 
  0x00222B9B  e92e010000              jmp      0x222cce                       
                                        ; XREF: 0x00222B92 (cond_jump)
  0x00222BA0  57                      push     edi                            
  0x00222BA1  33c0                    xor      eax, eax                       
  0x00222BA3  6a0c                    push     0xc                            
  0x00222BA5  59                      pop      ecx                            
  0x00222BA6  8bfe                    mov      edi, esi                       
  0x00222BA8  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x00222BAA  8bc6                    mov      eax, esi                       
  0x00222BAC  2b0580782800            sub      eax, dword ptr [0x287880]      
  0x00222BB2  894614                  mov      dword ptr [esi + 0x14], eax    
  0x00222BB5  8a4316                  mov      al, byte ptr [ebx + 0x16]      
  0x00222BB8  884611                  mov      byte ptr [esi + 0x11], al      
  0x00222BBB  8a4317                  mov      al, byte ptr [ebx + 0x17]      
  0x00222BBE  884613                  mov      byte ptr [esi + 0x13], al      
  0x00222BC1  33c0                    xor      eax, eax                       
  0x00222BC3  8a431e                  mov      al, byte ptr [ebx + 0x1e]      
  0x00222BC6  50                      push     eax                            
  0x00222BC7  33c0                    xor      eax, eax                       
  0x00222BC9  8a4611                  mov      al, byte ptr [esi + 0x11]      
  0x00222BCC  50                      push     eax                            
  0x00222BCD  33c0                    xor      eax, eax                       
  0x00222BCF  668b431c                mov      ax, word ptr [ebx + 0x1c]      
  0x00222BD3  50                      push     eax                            
  0x00222BD4  e8df050000              call     0x2231b8                       ; -> sub_002231B8
  0x00222BD9  66894622                mov      word ptr [esi + 0x22], ax      
  0x00222BDD  33c0                    xor      eax, eax                       
  0x00222BDF  8a4314                  mov      al, byte ptr [ebx + 0x14]      
  0x00222BE2  3306                    xor      eax, dword ptr [esi]           
  0x00222BE4  83e07f                  and      eax, 0x7f                      
  0x00222BE7  3106                    xor      dword ptr [esi], eax           
  0x00222BE9  0fb64315                movzx    eax, byte ptr [ebx + 0x15]     
  0x00222BED  8b0e                    mov      ecx, dword ptr [esi]           
  0x00222BEF  c1e007                  shl      eax, 7                         
  0x00222BF2  33c1                    xor      eax, ecx                       
  0x00222BF4  2580070000              and      eax, 0x780                     
  0x00222BF9  33c1                    xor      eax, ecx                       
  0x00222BFB  807e1100                cmp      byte ptr [esi + 0x11], 0       
  0x00222BFF  8906                    mov      dword ptr [esi], eax           
  0x00222C01  7509                    jne      0x222c0c                       
  0x00222C03  25ffe7ffff              and      eax, 0xffffe7ff                
  0x00222C08  8906                    mov      dword ptr [esi], eax           
  0x00222C0A  eb1a                    jmp      0x222c26                       
                                        ; XREF: 0x00222C01 (cond_jump)
  0x00222C0C  f6431580                test     byte ptr [ebx + 0x15], 0x80    
  0x00222C10  6a00                    push     0                              
  0x00222C12  59                      pop      ecx                            
  0x00222C13  0f95c1                  setne    cl                             
  0x00222C16  41                      inc      ecx                            
  0x00222C17  c1e10b                  shl      ecx, 0xb                       
  0x00222C1A  33c8                    xor      ecx, eax                       
  0x00222C1C  81e100180000            and      ecx, 0x1800                    
  0x00222C22  33c8                    xor      ecx, eax                       
  0x00222C24  890e                    mov      dword ptr [esi], ecx           
                                        ; XREF: 0x00222C0A (jump)
  0x00222C26  8b0e                    mov      ecx, dword ptr [esi]           
  0x00222C28  33c0                    xor      eax, eax                       
  0x00222C2A  8a431e                  mov      al, byte ptr [ebx + 0x1e]      
  0x00222C2D  81e1ff5fffff            and      ecx, 0xffff5fff                
  0x00222C33  83e001                  and      eax, 1                         
  0x00222C36  83c802                  or       eax, 2                         
  0x00222C39  c1e00d                  shl      eax, 0xd                       
  0x00222C3C  0bc1                    or       eax, ecx                       
  0x00222C3E  8906                    mov      dword ptr [esi], eax           
  0x00222C40  0fb74b1c                movzx    ecx, word ptr [ebx + 0x1c]     
  0x00222C44  c1e110                  shl      ecx, 0x10                      
  0x00222C47  33c8                    xor      ecx, eax                       
  0x00222C49  81e10000ff07            and      ecx, 0x7ff0000                 
  0x00222C4F  33c8                    xor      ecx, eax                       
  0x00222C51  33c0                    xor      eax, eax                       
  0x00222C53  890e                    mov      dword ptr [esi], ecx           
  0x00222C55  89460c                  mov      dword ptr [esi + 0xc], eax     
  0x00222C58  894608                  mov      dword ptr [esi + 8], eax       
  0x00222C5B  894604                  mov      dword ptr [esi + 4], eax       
  0x00222C5E  8b5318                  mov      edx, dword ptr [ebx + 0x18]    
  0x00222C61  3bd0                    cmp      edx, eax                       
  0x00222C63  7427                    je       0x222c8c                       
  0x00222C65  8bc1                    mov      eax, ecx                       
  0x00222C67  33ff                    xor      edi, edi                       
  0x00222C69  c1e907                  shr      ecx, 7                         
  0x00222C6C  83e10f                  and      ecx, 0xf                       
  0x00222C6F  47                      inc      edi                            
  0x00222C70  2500180000              and      eax, 0x1800                    
  0x00222C75  d3e7                    shl      edi, cl                        
  0x00222C77  3d00100000              cmp      eax, 0x1000                    
  0x00222C7C  7503                    jne      0x222c81                       
  0x00222C7E  c1e710                  shl      edi, 0x10                      
                                        ; XREF: 0x00222C7C (cond_jump)
  0x00222C81  853a                    test     dword ptr [edx], edi           
  0x00222C83  7407                    je       0x222c8c                       
  0x00222C85  c7460802000000          mov      dword ptr [esi + 8], 2         
                                        ; XREF: 0x00222C63 (cond_jump), 0x00222C83 (cond_jump)
  0x00222C8C  8a4611                  mov      al, byte ptr [esi + 0x11]      
  0x00222C8F  84c0                    test     al, al                         
  0x00222C91  5f                      pop      edi                            
  0x00222C92  7413                    je       0x222ca7                       
  0x00222C94  3c02                    cmp      al, 2                          
  0x00222C96  740f                    je       0x222ca7                       
  0x00222C98  8b4df4                  mov      ecx, dword ptr [ebp - 0xc]     
  0x00222C9B  8bd6                    mov      edx, esi                       
  0x00222C9D  e8df150000              call     0x224281                       ; -> sub_00224281
  0x00222CA2  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x00222CA5  eb0a                    jmp      0x222cb1                       
                                        ; XREF: 0x00222C92 (cond_jump), 0x00222C96 (cond_jump)
  0x00222CA7  8b4df4                  mov      ecx, dword ptr [ebp - 0xc]     
  0x00222CAA  8bd6                    mov      edx, esi                       
  0x00222CAC  e8b6140000              call     0x224167                       ; -> sub_00224167
                                        ; XREF: 0x00222CA5 (jump)
  0x00222CB1  837df800                cmp      dword ptr [ebp - 8], 0         
  0x00222CB5  7c05                    jl       0x222cbc                       
  0x00222CB7  897310                  mov      dword ptr [ebx + 0x10], esi    
  0x00222CBA  eb12                    jmp      0x222cce                       
                                        ; XREF: 0x00222CB5 (cond_jump)
  0x00222CBC  83631000                and      dword ptr [ebx + 0x10], 0      
  0x00222CC0  a188782800              mov      eax, dword ptr [0x287888]      
  0x00222CC5  894618                  mov      dword ptr [esi + 0x18], eax    
  0x00222CC8  893588782800            mov      dword ptr [0x287888], esi      
                                        ; XREF: 0x00222B9B (jump), 0x00222CBA (jump)
  0x00222CCE  8b75f8                  mov      esi, dword ptr [ebp - 8]       
  0x00222CD1  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x00222CD4  897304                  mov      dword ptr [ebx + 4], esi       
  0x00222CD7  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00222CDD  8bc6                    mov      eax, esi                       
  0x00222CDF  5e                      pop      esi                            
  0x00222CE0  5b                      pop      ebx                            
  0x00222CE1  c9                      leave                                   
  0x00222CE2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222CE3
; Start: 0x00222CE3  End: 0x00222D04  Size: 33 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00223032
; ============================================================
sub_00222CE3:
  0x00222CE3  8b4a10                  mov      ecx, dword ptr [edx + 0x10]    
  0x00222CE6  8b4108                  mov      eax, dword ptr [ecx + 8]       
  0x00222CE9  83e001                  and      eax, 1                         
  0x00222CEC  894214                  mov      dword ptr [edx + 0x14], eax    
  0x00222CEF  80792600                cmp      byte ptr [ecx + 0x26], 0       
  0x00222CF3  7506                    jne      0x222cfb                       
  0x00222CF5  80792700                cmp      byte ptr [ecx + 0x27], 0       
  0x00222CF9  7406                    je       0x222d01                       
                                        ; XREF: 0x00222CF3 (cond_jump)
  0x00222CFB  83c802                  or       eax, 2                         
  0x00222CFE  894214                  mov      dword ptr [edx + 0x14], eax    
                                        ; XREF: 0x00222CF9 (cond_jump)
  0x00222D01  33c0                    xor      eax, eax                       
  0x00222D03  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222D04
; Start: 0x00222D04  End: 0x00222D32  Size: 46 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00223032
; ============================================================
sub_00222D04:
  0x00222D04  8b4210                  mov      eax, dword ptr [edx + 0x10]    
  0x00222D07  8b5214                  mov      edx, dword ptr [edx + 0x14]    
  0x00222D0A  f6c204                  test     dl, 4                          
  0x00222D0D  7404                    je       0x222d13                       
  0x00222D0F  836008fd                and      dword ptr [eax + 8], 0xfffffffd 
                                        ; XREF: 0x00222D0D (cond_jump)
  0x00222D13  f6c208                  test     dl, 8                          
  0x00222D16  7404                    je       0x222d1c                       
  0x00222D18  83480802                or       dword ptr [eax + 8], 2         
                                        ; XREF: 0x00222D16 (cond_jump)
  0x00222D1C  f6c201                  test     dl, 1                          
  0x00222D1F  750e                    jne      0x222d2f                       
  0x00222D21  8b4808                  mov      ecx, dword ptr [eax + 8]       
  0x00222D24  f6c101                  test     cl, 1                          
  0x00222D27  7406                    je       0x222d2f                       
  0x00222D29  83e1fe                  and      ecx, 0xfffffffe                
  0x00222D2C  894808                  mov      dword ptr [eax + 8], ecx       
                                        ; XREF: 0x00222D1F (cond_jump), 0x00222D27 (cond_jump)
  0x00222D2F  33c0                    xor      eax, eax                       
  0x00222D31  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222D32
; Start: 0x00222D32  End: 0x00222D6B  Size: 57 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00222EC1
; ============================================================
sub_00222D32:
  0x00222D32  8b811c040000            mov      eax, dword ptr [ecx + 0x41c]   
  0x00222D38  56                      push     esi                            
  0x00222D39  33f6                    xor      esi, esi                       
  0x00222D3B  3bc2                    cmp      eax, edx                       
  0x00222D3D  740d                    je       0x222d4c                       
                                        ; XREF: 0x00222D46 (cond_jump)
  0x00222D3F  8bf0                    mov      esi, eax                       
  0x00222D41  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222D44  3bc2                    cmp      eax, edx                       
  0x00222D46  75f7                    jne      0x222d3f                       
  0x00222D48  85f6                    test     esi, esi                       
  0x00222D4A  750b                    jne      0x222d57                       
                                        ; XREF: 0x00222D3D (cond_jump)
  0x00222D4C  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222D4F  89811c040000            mov      dword ptr [ecx + 0x41c], eax   
  0x00222D55  eb06                    jmp      0x222d5d                       
                                        ; XREF: 0x00222D4A (cond_jump)
  0x00222D57  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222D5A  894624                  mov      dword ptr [esi + 0x24], eax    
                                        ; XREF: 0x00222D55 (jump)
  0x00222D5D  8d8120040000            lea      eax, [ecx + 0x420]             
  0x00222D63  3b10                    cmp      edx, dword ptr [eax]           
  0x00222D65  7502                    jne      0x222d69                       
  0x00222D67  8930                    mov      dword ptr [eax], esi           
                                        ; XREF: 0x00222D65 (cond_jump)
  0x00222D69  5e                      pop      esi                            
  0x00222D6A  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222D6B
; Start: 0x00222D6B  End: 0x00222DA4  Size: 57 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00222EC1
; ============================================================
sub_00222D6B:
  0x00222D6B  8b8124040000            mov      eax, dword ptr [ecx + 0x424]   
  0x00222D71  56                      push     esi                            
  0x00222D72  33f6                    xor      esi, esi                       
  0x00222D74  3bc2                    cmp      eax, edx                       
  0x00222D76  740d                    je       0x222d85                       
                                        ; XREF: 0x00222D7F (cond_jump)
  0x00222D78  8bf0                    mov      esi, eax                       
  0x00222D7A  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222D7D  3bc2                    cmp      eax, edx                       
  0x00222D7F  75f7                    jne      0x222d78                       
  0x00222D81  85f6                    test     esi, esi                       
  0x00222D83  750b                    jne      0x222d90                       
                                        ; XREF: 0x00222D76 (cond_jump)
  0x00222D85  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222D88  898124040000            mov      dword ptr [ecx + 0x424], eax   
  0x00222D8E  eb06                    jmp      0x222d96                       
                                        ; XREF: 0x00222D83 (cond_jump)
  0x00222D90  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222D93  894624                  mov      dword ptr [esi + 0x24], eax    
                                        ; XREF: 0x00222D8E (jump)
  0x00222D96  8d8128040000            lea      eax, [ecx + 0x428]             
  0x00222D9C  3b10                    cmp      edx, dword ptr [eax]           
  0x00222D9E  7502                    jne      0x222da2                       
  0x00222DA0  8930                    mov      dword ptr [eax], esi           
                                        ; XREF: 0x00222D9E (cond_jump)
  0x00222DA2  5e                      pop      esi                            
  0x00222DA3  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222DA4
; Start: 0x00222DA4  End: 0x00222DD3  Size: 47 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00222EC1
; ============================================================
sub_00222DA4:
  0x00222DA4  8b4128                  mov      eax, dword ptr [ecx + 0x28]    
  0x00222DA7  56                      push     esi                            
  0x00222DA8  33f6                    xor      esi, esi                       
  0x00222DAA  3bc2                    cmp      eax, edx                       
  0x00222DAC  740d                    je       0x222dbb                       
                                        ; XREF: 0x00222DB5 (cond_jump)
  0x00222DAE  8bf0                    mov      esi, eax                       
  0x00222DB0  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222DB3  3bc2                    cmp      eax, edx                       
  0x00222DB5  75f7                    jne      0x222dae                       
  0x00222DB7  85f6                    test     esi, esi                       
  0x00222DB9  7508                    jne      0x222dc3                       
                                        ; XREF: 0x00222DAC (cond_jump)
  0x00222DBB  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222DBE  894128                  mov      dword ptr [ecx + 0x28], eax    
  0x00222DC1  eb06                    jmp      0x222dc9                       
                                        ; XREF: 0x00222DB9 (cond_jump)
  0x00222DC3  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x00222DC6  894624                  mov      dword ptr [esi + 0x24], eax    
                                        ; XREF: 0x00222DC1 (jump)
  0x00222DC9  3b512c                  cmp      edx, dword ptr [ecx + 0x2c]    
  0x00222DCC  7503                    jne      0x222dd1                       
  0x00222DCE  89712c                  mov      dword ptr [ecx + 0x2c], esi    
                                        ; XREF: 0x00222DCC (cond_jump)
  0x00222DD1  5e                      pop      esi                            
  0x00222DD2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222DD3
; Start: 0x00222DD3  End: 0x00222E49  Size: 118 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002231A4
; Called by: sub_00222F78, sub_00222FDF
; ============================================================
sub_00222DD3:
  0x00222DD3  51                      push     ecx                            
  0x00222DD4  57                      push     edi                            
  0x00222DD5  8bfa                    mov      edi, edx                       
  0x00222DD7  807f2600                cmp      byte ptr [edi + 0x26], 0       
  0x00222DDB  7469                    je       0x222e46                       
  0x00222DDD  0fb64711                movzx    eax, byte ptr [edi + 0x11]     
  0x00222DE1  83e800                  sub      eax, 0                         
  0x00222DE4  53                      push     ebx                            
  0x00222DE5  55                      push     ebp                            
  0x00222DE6  741d                    je       0x222e05                       
  0x00222DE8  48                      dec      eax                            
  0x00222DE9  48                      dec      eax                            
  0x00222DEA  740b                    je       0x222df7                       
  0x00222DEC  48                      dec      eax                            
  0x00222DED  7555                    jne      0x222e44                       
  0x00222DEF  8d5f28                  lea      ebx, [edi + 0x28]              
  0x00222DF2  8d6f2c                  lea      ebp, [edi + 0x2c]              
  0x00222DF5  eb1a                    jmp      0x222e11                       
                                        ; XREF: 0x00222DEA (cond_jump)
  0x00222DF7  8d9924040000            lea      ebx, [ecx + 0x424]             
  0x00222DFD  8da928040000            lea      ebp, [ecx + 0x428]             
  0x00222E03  eb0c                    jmp      0x222e11                       
                                        ; XREF: 0x00222DE6 (cond_jump)
  0x00222E05  8d991c040000            lea      ebx, [ecx + 0x41c]             
  0x00222E0B  8da920040000            lea      ebp, [ecx + 0x420]             
                                        ; XREF: 0x00222DF5 (jump), 0x00222E03 (jump)
  0x00222E11  56                      push     esi                            
                                        ; XREF: 0x00222E3A (cond_jump)
  0x00222E12  8b33                    mov      esi, dword ptr [ebx]           
  0x00222E14  397e10                  cmp      dword ptr [esi + 0x10], edi    
  0x00222E17  7517                    jne      0x222e30                       
  0x00222E19  8b4624                  mov      eax, dword ptr [esi + 0x24]    
  0x00222E1C  8903                    mov      dword ptr [ebx], eax           
  0x00222E1E  c746040f0000c0          mov      dword ptr [esi + 4], 0xc000000f 
  0x00222E25  fe4f26                  dec      byte ptr [edi + 0x26]          
  0x00222E28  56                      push     esi                            
  0x00222E29  e876030000              call     0x2231a4                       ; -> sub_002231A4
  0x00222E2E  eb07                    jmp      0x222e37                       
                                        ; XREF: 0x00222E17 (cond_jump)
  0x00222E30  89742410                mov      dword ptr [esp + 0x10], esi    
  0x00222E34  8d5e24                  lea      ebx, [esi + 0x24]              
                                        ; XREF: 0x00222E2E (jump)
  0x00222E37  397500                  cmp      dword ptr [ebp], esi           
  0x00222E3A  75d6                    jne      0x222e12                       
  0x00222E3C  8b442410                mov      eax, dword ptr [esp + 0x10]    
  0x00222E40  894500                  mov      dword ptr [ebp], eax           
  0x00222E43  5e                      pop      esi                            
                                        ; XREF: 0x00222DED (cond_jump)
  0x00222E44  5d                      pop      ebp                            
  0x00222E45  5b                      pop      ebx                            
                                        ; XREF: 0x00222DDB (cond_jump)
  0x00222E46  5f                      pop      edi                            
  0x00222E47  59                      pop      ecx                            
  0x00222E48  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222E49
; Start: 0x00222E49  End: 0x00222E86  Size: 61 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022466C
; Called by: sub_00222EC1, sub_00222F78, sub_00222FDF, sub_00224F7F
; ============================================================
sub_00222E49:
  0x00222E49  56                      push     esi                            
  0x00222E4A  8bf2                    mov      esi, edx                       
  0x00222E4C  fe4620                  inc      byte ptr [esi + 0x20]          
  0x00222E4F  f6461020                test     byte ptr [esi + 0x10], 0x20    
  0x00222E53  57                      push     edi                            
  0x00222E54  8bf9                    mov      edi, ecx                       
  0x00222E56  752b                    jne      0x222e83                       
  0x00222E58  804e0140                or       byte ptr [esi + 1], 0x40       
  0x00222E5C  e80b180000              call     0x22466c                       ; -> sub_0022466C
  0x00222E61  40                      inc      eax                            
  0x00222E62  89461c                  mov      dword ptr [esi + 0x1c], eax    
  0x00222E65  83bf3804000000          cmp      dword ptr [edi + 0x438], 0     
  0x00222E6C  7404                    je       0x222e72                       
  0x00222E6E  804e1040                or       byte ptr [esi + 0x10], 0x40    
                                        ; XREF: 0x00222E6C (cond_jump)
  0x00222E72  8b0f                    mov      ecx, dword ptr [edi]           
  0x00222E74  6a04                    push     4                              
  0x00222E76  58                      pop      eax                            
  0x00222E77  89410c                  mov      dword ptr [ecx + 0xc], eax     
  0x00222E7A  8b0f                    mov      ecx, dword ptr [edi]           
  0x00222E7C  894110                  mov      dword ptr [ecx + 0x10], eax    
  0x00222E7F  804e1020                or       byte ptr [esi + 0x10], 0x20    
                                        ; XREF: 0x00222E56 (cond_jump)
  0x00222E83  5f                      pop      edi                            
  0x00222E84  5e                      pop      esi                            
  0x00222E85  c3                      ret                                     
; end of function
                                        ; XREF: 0x0021FD8F (data_imm)
  0x00222E86  56                      push     esi                            
  0x00222E87  8b742408                mov      esi, dword ptr [esp + 8]       
  0x00222E8B  8b469c                  mov      eax, dword ptr [esi - 0x64]    
  0x00222E8E  81c640fbffff            add      esi, 0xfffffb40                
  0x00222E94  6bc070                  imul     eax, eax, 0x70                 
  0x00222E97  8a88cc782800            mov      cl, byte ptr [eax + 0x2878cc]  
  0x00222E9D  ff15785b2200            call     dword ptr [0x225b78]           ; -> xbox_KfRaiseIrql
  0x00222EA3  8b0e                    mov      ecx, dword ptr [esi]           
  0x00222EA5  c7411433000080          mov      dword ptr [ecx + 0x14], 0x80000033 
  0x00222EAC  8b0e                    mov      ecx, dword ptr [esi]           
  0x00222EAE  c7410402000000          mov      dword ptr [ecx + 4], 2         
  0x00222EB5  8ac8                    mov      cl, al                         
  0x00222EB7  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00222EBD  5e                      pop      esi                            
  0x00222EBE  c20400                  ret      4                              

; ============================================================
; Function: sub_00222EC1
; Start: 0x00222EC1  End: 0x00222F78  Size: 183 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00222D32, sub_00222D6B, sub_00222DA4, sub_00222E49, sub_002231A4
; Called by: sub_002217C3
; ============================================================
sub_00222EC1:
  0x00222EC1  56                      push     esi                            
  0x00222EC2  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00222EC6  f6462201                test     byte ptr [esi + 0x22], 1       
  0x00222ECA  740a                    je       0x222ed6                       
  0x00222ECC  b800000240              mov      eax, 0x40020000                
  0x00222ED1  e99e000000              jmp      0x222f74                       
                                        ; XREF: 0x00222ECA (cond_jump)
  0x00222ED6  53                      push     ebx                            
  0x00222ED7  57                      push     edi                            
  0x00222ED8  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00222EDE  8b7e10                  mov      edi, dword ptr [esi + 0x10]    
  0x00222EE1  f6471010                test     byte ptr [edi + 0x10], 0x10    
  0x00222EE5  8ad8                    mov      bl, al                         
  0x00222EE7  757a                    jne      0x222f63                       
  0x00222EE9  668b4622                mov      ax, word ptr [esi + 0x22]      
  0x00222EED  a802                    test     al, 2                          
  0x00222EEF  7452                    je       0x222f43                       
  0x00222EF1  0fb64711                movzx    eax, byte ptr [edi + 0x11]     
  0x00222EF5  83e800                  sub      eax, 0                         
  0x00222EF8  7426                    je       0x222f20                       
  0x00222EFA  48                      dec      eax                            
  0x00222EFB  48                      dec      eax                            
  0x00222EFC  7415                    je       0x222f13                       
  0x00222EFE  48                      dec      eax                            
  0x00222EFF  7407                    je       0x222f08                       
  0x00222F01  be00060080              mov      esi, 0x80000600                
  0x00222F06  eb60                    jmp      0x222f68                       
                                        ; XREF: 0x00222EFF (cond_jump)
  0x00222F08  8bd6                    mov      edx, esi                       
  0x00222F0A  8bcf                    mov      ecx, edi                       
  0x00222F0C  e893feffff              call     0x222da4                       ; -> sub_00222DA4
  0x00222F11  eb18                    jmp      0x222f2b                       
                                        ; XREF: 0x00222EFC (cond_jump)
  0x00222F13  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x00222F17  8bd6                    mov      edx, esi                       
  0x00222F19  e84dfeffff              call     0x222d6b                       ; -> sub_00222D6B
  0x00222F1E  eb0b                    jmp      0x222f2b                       
                                        ; XREF: 0x00222EF8 (cond_jump)
  0x00222F20  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x00222F24  8bd6                    mov      edx, esi                       
  0x00222F26  e807feffff              call     0x222d32                       ; -> sub_00222D32
                                        ; XREF: 0x00222F11 (jump), 0x00222F1E (jump)
  0x00222F2B  fe4f26                  dec      byte ptr [edi + 0x26]          
  0x00222F2E  804e2201                or       byte ptr [esi + 0x22], 1       
  0x00222F32  56                      push     esi                            
  0x00222F33  c746040f0000c0          mov      dword ptr [esi + 4], 0xc000000f 
  0x00222F3A  e865020000              call     0x2231a4                       ; -> sub_002231A4
  0x00222F3F  33f6                    xor      esi, esi                       
  0x00222F41  eb25                    jmp      0x222f68                       
                                        ; XREF: 0x00222EEF (cond_jump)
  0x00222F43  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x00222F47  660d0100                or       ax, 1                          
  0x00222F4B  66894622                mov      word ptr [esi + 0x22], ax      
  0x00222F4F  8d812c040000            lea      eax, [ecx + 0x42c]             
  0x00222F55  8b10                    mov      edx, dword ptr [eax]           
  0x00222F57  895624                  mov      dword ptr [esi + 0x24], edx    
  0x00222F5A  8bd7                    mov      edx, edi                       
  0x00222F5C  8930                    mov      dword ptr [eax], esi           
  0x00222F5E  e8e6feffff              call     0x222e49                       ; -> sub_00222E49
                                        ; XREF: 0x00222EE7 (cond_jump)
  0x00222F63  be00000240              mov      esi, 0x40020000                
                                        ; XREF: 0x00222F06 (jump), 0x00222F41 (jump)
  0x00222F68  8acb                    mov      cl, bl                         
  0x00222F6A  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00222F70  5f                      pop      edi                            
  0x00222F71  8bc6                    mov      eax, esi                       
  0x00222F73  5b                      pop      ebx                            
                                        ; XREF: 0x00222ED1 (jump)
  0x00222F74  5e                      pop      esi                            
  0x00222F75  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_00222F78
; Start: 0x00222F78  End: 0x00222FDF  Size: 103 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00222DD3, sub_00222E49, sub_002241A4, sub_0022445D
; Called by: sub_00223032
; ============================================================
sub_00222F78:
  0x00222F78  53                      push     ebx                            
  0x00222F79  55                      push     ebp                            
  0x00222F7A  56                      push     esi                            
  0x00222F7B  57                      push     edi                            
  0x00222F7C  8bfa                    mov      edi, edx                       
  0x00222F7E  8b7710                  mov      esi, dword ptr [edi + 0x10]    
  0x00222F81  8be9                    mov      ebp, ecx                       
  0x00222F83  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00222F89  804e1010                or       byte ptr [esi + 0x10], 0x10    
  0x00222F8D  8bd6                    mov      edx, esi                       
  0x00222F8F  8bcd                    mov      ecx, ebp                       
  0x00222F91  8ad8                    mov      bl, al                         
  0x00222F93  e83bfeffff              call     0x222dd3                       ; -> sub_00222DD3
  0x00222F98  8a4611                  mov      al, byte ptr [esi + 0x11]      
  0x00222F9B  84c0                    test     al, al                         
  0x00222F9D  740f                    je       0x222fae                       
  0x00222F9F  3c02                    cmp      al, 2                          
  0x00222FA1  740b                    je       0x222fae                       
  0x00222FA3  8bd6                    mov      edx, esi                       
  0x00222FA5  8bcd                    mov      ecx, ebp                       
  0x00222FA7  e8b1140000              call     0x22445d                       ; -> sub_0022445D
  0x00222FAC  eb09                    jmp      0x222fb7                       
                                        ; XREF: 0x00222F9D (cond_jump), 0x00222FA1 (cond_jump)
  0x00222FAE  8bd6                    mov      edx, esi                       
  0x00222FB0  8bcd                    mov      ecx, ebp                       
  0x00222FB2  e8ed110000              call     0x2241a4                       ; -> sub_002241A4
                                        ; XREF: 0x00222FAC (jump)
  0x00222FB7  8bd6                    mov      edx, esi                       
  0x00222FB9  8bcd                    mov      ecx, ebp                       
  0x00222FBB  e889feffff              call     0x222e49                       ; -> sub_00222E49
  0x00222FC0  8d8534040000            lea      eax, [ebp + 0x434]             
  0x00222FC6  8b08                    mov      ecx, dword ptr [eax]           
  0x00222FC8  894f14                  mov      dword ptr [edi + 0x14], ecx    
  0x00222FCB  8acb                    mov      cl, bl                         
  0x00222FCD  8938                    mov      dword ptr [eax], edi           
  0x00222FCF  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00222FD5  5f                      pop      edi                            
  0x00222FD6  5e                      pop      esi                            
  0x00222FD7  5d                      pop      ebp                            
  0x00222FD8  b800000040              mov      eax, 0x40000000                
  0x00222FDD  5b                      pop      ebx                            
  0x00222FDE  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00222FDF
; Start: 0x00222FDF  End: 0x00223032  Size: 83 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00222DD3, sub_00222E49
; Called by: sub_00223032
; ============================================================
sub_00222FDF:
  0x00222FDF  51                      push     ecx                            
  0x00222FE0  53                      push     ebx                            
  0x00222FE1  55                      push     ebp                            
  0x00222FE2  56                      push     esi                            
  0x00222FE3  8bf2                    mov      esi, edx                       
  0x00222FE5  57                      push     edi                            
  0x00222FE6  8b7e10                  mov      edi, dword ptr [esi + 0x10]    
  0x00222FE9  8be9                    mov      ebp, ecx                       
  0x00222FEB  33db                    xor      ebx, ebx                       
  0x00222FED  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00222FF3  8bd7                    mov      edx, edi                       
  0x00222FF5  8bcd                    mov      ecx, ebp                       
  0x00222FF7  88442413                mov      byte ptr [esp + 0x13], al      
  0x00222FFB  e8d3fdffff              call     0x222dd3                       ; -> sub_00222DD3
  0x00223000  385f27                  cmp      byte ptr [edi + 0x27], bl      
  0x00223003  741b                    je       0x223020                       
  0x00223005  8d8530040000            lea      eax, [ebp + 0x430]             
  0x0022300B  8b08                    mov      ecx, dword ptr [eax]           
  0x0022300D  894e14                  mov      dword ptr [esi + 0x14], ecx    
  0x00223010  8bd7                    mov      edx, edi                       
  0x00223012  8bcd                    mov      ecx, ebp                       
  0x00223014  8930                    mov      dword ptr [eax], esi           
  0x00223016  e82efeffff              call     0x222e49                       ; -> sub_00222E49
  0x0022301B  bb00000040              mov      ebx, 0x40000000                
                                        ; XREF: 0x00223003 (cond_jump)
  0x00223020  8a4c2413                mov      cl, byte ptr [esp + 0x13]      
  0x00223024  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x0022302A  5f                      pop      edi                            
  0x0022302B  5e                      pop      esi                            
  0x0022302C  5d                      pop      ebp                            
  0x0022302D  8bc3                    mov      eax, ebx                       
  0x0022302F  5b                      pop      ebx                            
  0x00223030  59                      pop      ecx                            
  0x00223031  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00223032
; Start: 0x00223032  End: 0x0022314A  Size: 280 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00222B6F, sub_00222CE3, sub_00222D04, sub_00222F78, sub_00222FDF, sub_002231A4, sub_0022466C, sub_00224DD2, sub_00224F7F, sub_0022504C ... (+3 more)
; Called by: sub_00220D9C, sub_00220E01, sub_002211E3, sub_002212E3, sub_0022139C, sub_002218E3, sub_00221969, sub_00221B1F
; ============================================================
sub_00223032:
  0x00223032  55                      push     ebp                            
  0x00223033  8bec                    mov      ebp, esp                       
  0x00223035  56                      push     esi                            
  0x00223036  57                      push     edi                            
  0x00223037  8b7d0c                  mov      edi, dword ptr [ebp + 0xc]     
  0x0022303A  0fb64701                movzx    eax, byte ptr [edi + 1]        
  0x0022303E  83f80c                  cmp      eax, 0xc                       
  0x00223041  0f8f83000000            jg       0x2230ca                       
  0x00223047  7475                    je       0x2230be                       
  0x00223049  6a02                    push     2                              
  0x0022304B  59                      pop      ecx                            
  0x0022304C  2bc1                    sub      eax, ecx                       
  0x0022304E  7462                    je       0x2230b2                       
  0x00223050  2bc1                    sub      eax, ecx                       
  0x00223052  7452                    je       0x2230a6                       
  0x00223054  48                      dec      eax                            
  0x00223055  7440                    je       0x223097                       
  0x00223057  2bc1                    sub      eax, ecx                       
  0x00223059  742a                    je       0x223085                       
  0x0022305B  2bc1                    sub      eax, ecx                       
  0x0022305D  7417                    je       0x223076                       
  0x0022305F  2bc1                    sub      eax, ecx                       
  0x00223061  0f85b1000000            jne      0x223118                       
  0x00223067  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x0022306A  8bd7                    mov      edx, edi                       
  0x0022306C  e8db1f0000              call     0x22504c                       ; -> sub_0022504C
  0x00223071  e9b3000000              jmp      0x223129                       
                                        ; XREF: 0x0022305D (cond_jump)
  0x00223076  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00223079  8bd7                    mov      edx, edi                       
  0x0022307B  e8521d0000              call     0x224dd2                       ; -> sub_00224DD2
  0x00223080  e9a4000000              jmp      0x223129                       
                                        ; XREF: 0x00223059 (cond_jump)
  0x00223085  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00223088  e8df150000              call     0x22466c                       ; -> sub_0022466C
  0x0022308D  894714                  mov      dword ptr [edi + 0x14], eax    
  0x00223090  33f6                    xor      esi, esi                       
  0x00223092  e994000000              jmp      0x22312b                       
                                        ; XREF: 0x00223055 (cond_jump)
  0x00223097  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x0022309A  8bd7                    mov      edx, edi                       
  0x0022309C  e863fcffff              call     0x222d04                       ; -> sub_00222D04
  0x002230A1  e983000000              jmp      0x223129                       
                                        ; XREF: 0x00223052 (cond_jump)
  0x002230A6  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002230A9  8bd7                    mov      edx, edi                       
  0x002230AB  e833fcffff              call     0x222ce3                       ; -> sub_00222CE3
  0x002230B0  eb77                    jmp      0x223129                       
                                        ; XREF: 0x0022304E (cond_jump)
  0x002230B2  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002230B5  8bd7                    mov      edx, edi                       
  0x002230B7  e8b3faffff              call     0x222b6f                       ; -> sub_00222B6F
  0x002230BC  eb6b                    jmp      0x223129                       
                                        ; XREF: 0x00223047 (cond_jump)
  0x002230BE  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002230C1  8bd7                    mov      edx, edi                       
  0x002230C3  e8eb200000              call     0x2251b3                       ; -> sub_002251B3
  0x002230C8  eb5f                    jmp      0x223129                       
                                        ; XREF: 0x00223041 (cond_jump)
  0x002230CA  83f80d                  cmp      eax, 0xd                       
  0x002230CD  7450                    je       0x22311f                       
  0x002230CF  83f83f                  cmp      eax, 0x3f                      
  0x002230D2  7e44                    jle      0x223118                       
  0x002230D4  83f841                  cmp      eax, 0x41                      
  0x002230D7  7e33                    jle      0x22310c                       
  0x002230D9  83f843                  cmp      eax, 0x43                      
  0x002230DC  7422                    je       0x223100                       
  0x002230DE  83f846                  cmp      eax, 0x46                      
  0x002230E1  7411                    je       0x2230f4                       
  0x002230E3  83f84a                  cmp      eax, 0x4a                      
  0x002230E6  7530                    jne      0x223118                       
  0x002230E8  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002230EB  8bd7                    mov      edx, edi                       
  0x002230ED  e88d1e0000              call     0x224f7f                       ; -> sub_00224F7F
  0x002230F2  eb35                    jmp      0x223129                       
                                        ; XREF: 0x002230E1 (cond_jump)
  0x002230F4  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x002230F7  8bd7                    mov      edx, edi                       
  0x002230F9  e8e1feffff              call     0x222fdf                       ; -> sub_00222FDF
  0x002230FE  eb29                    jmp      0x223129                       
                                        ; XREF: 0x002230DC (cond_jump)
  0x00223100  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00223103  8bd7                    mov      edx, edi                       
  0x00223105  e86efeffff              call     0x222f78                       ; -> sub_00222F78
  0x0022310A  eb1d                    jmp      0x223129                       
                                        ; XREF: 0x002230D7 (cond_jump)
  0x0022310C  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x0022310F  8bd7                    mov      edx, edi                       
  0x00223111  e866280000              call     0x22597c                       ; -> sub_0022597C
  0x00223116  eb11                    jmp      0x223129                       
                                        ; XREF: 0x00223061 (cond_jump), 0x002230D2 (cond_jump), 0x002230E6 (cond_jump)
  0x00223118  be00020080              mov      esi, 0x80000200                
  0x0022311D  eb0c                    jmp      0x22312b                       
                                        ; XREF: 0x002230CD (cond_jump)
  0x0022311F  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x00223122  8bd7                    mov      edx, edi                       
  0x00223124  e8a9210000              call     0x2252d2                       ; -> sub_002252D2
                                        ; XREF: 0x00223071 (jump), 0x00223080 (jump), 0x002230A1 (jump), 0x002230B0 (jump), 0x002230BC (jump), ... (+5 more)
  0x00223129  8bf0                    mov      esi, eax                       
                                        ; XREF: 0x00223092 (jump), 0x0022311D (jump)
  0x0022312B  8bc6                    mov      eax, esi                       
  0x0022312D  25000000c0              and      eax, 0xc0000000                
  0x00223132  3d00000040              cmp      eax, 0x40000000                
  0x00223137  7409                    je       0x223142                       
  0x00223139  57                      push     edi                            
  0x0022313A  897704                  mov      dword ptr [edi + 4], esi       
  0x0022313D  e862000000              call     0x2231a4                       ; -> sub_002231A4
                                        ; XREF: 0x00223137 (cond_jump)
  0x00223142  5f                      pop      edi                            
  0x00223143  8bc6                    mov      eax, esi                       
  0x00223145  5e                      pop      esi                            
  0x00223146  5d                      pop      ebp                            
  0x00223147  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_0022314A
; Start: 0x0022314A  End: 0x002231A4  Size: 90 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FDC0
; ============================================================
sub_0022314A:
  0x0022314A  8b442404                mov      eax, dword ptr [esp + 4]       
  0x0022314E  57                      push     edi                            
  0x0022314F  8bd1                    mov      edx, ecx                       
  0x00223151  898298000000            mov      dword ptr [edx + 0x98], eax    
  0x00223157  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x0022315B  89829c000000            mov      dword ptr [edx + 0x9c], eax    
  0x00223161  33c0                    xor      eax, eax                       
  0x00223163  c682a000000000          mov      byte ptr [edx + 0xa0], 0       
  0x0022316A  c682a100000000          mov      byte ptr [edx + 0xa1], 0       
  0x00223171  6a0c                    push     0xc                            
  0x00223173  59                      pop      ecx                            
  0x00223174  8bfa                    mov      edi, edx                       
  0x00223176  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x00223178  66ab                    stosw    word ptr es:[edi], ax          
  0x0022317A  33c0                    xor      eax, eax                       
  0x0022317C  6a0c                    push     0xc                            
  0x0022317E  59                      pop      ecx                            
  0x0022317F  8d7a32                  lea      edi, [edx + 0x32]              
  0x00223182  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x00223184  66ab                    stosw    word ptr es:[edi], ax          
  0x00223186  33c0                    xor      eax, eax                       
  0x00223188  6a0c                    push     0xc                            
  0x0022318A  59                      pop      ecx                            
  0x0022318B  8d7a64                  lea      edi, [edx + 0x64]              
  0x0022318E  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x00223190  66ab                    stosw    word ptr es:[edi], ax          
  0x00223192  33c0                    xor      eax, eax                       
  0x00223194  8dbaa4000000            lea      edi, [edx + 0xa4]              
  0x0022319A  ab                      stosd    dword ptr es:[edi], eax        
  0x0022319B  ab                      stosd    dword ptr es:[edi], eax        
  0x0022319C  ab                      stosd    dword ptr es:[edi], eax        
  0x0022319D  ab                      stosd    dword ptr es:[edi], eax        
  0x0022319E  8bc2                    mov      eax, edx                       
  0x002231A0  5f                      pop      edi                            
  0x002231A1  c20800                  ret      8                              
; end of function

; ============================================================
; Function: sub_002231A4
; Start: 0x002231A4  End: 0x002231B8  Size: 20 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_002218E3, sub_00221969, sub_00222DD3, sub_00222EC1, sub_00223032, sub_002247A3, sub_00224B49, sub_00224BD0, sub_00224FC3, sub_0022504C ... (+2 more)
; ============================================================
sub_002231A4:
  0x002231A4  8b442404                mov      eax, dword ptr [esp + 4]       
  0x002231A8  8b4808                  mov      ecx, dword ptr [eax + 8]       
  0x002231AB  85c9                    test     ecx, ecx                       
  0x002231AD  7406                    je       0x2231b5                       
  0x002231AF  ff700c                  push     dword ptr [eax + 0xc]          
  0x002231B2  50                      push     eax                            
  0x002231B3  ffd1                    call     ecx                            
                                        ; XREF: 0x002231AD (cond_jump)
  0x002231B5  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002231B8
; Start: 0x002231B8  End: 0x00223201  Size: 73 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_00220614, sub_00222B6F, sub_00224DD2
; ============================================================
sub_002231B8:
  0x002231B8  55                      push     ebp                            
  0x002231B9  8bec                    mov      ebp, esp                       
  0x002231BB  83ec10                  sub      esp, 0x10                      
  0x002231BE  0fb6450c                movzx    eax, byte ptr [ebp + 0xc]      
  0x002231C2  8365f000                and      dword ptr [ebp - 0x10], 0      
  0x002231C6  8365f800                and      dword ptr [ebp - 8], 0         
  0x002231CA  c745f409000000          mov      dword ptr [ebp - 0xc], 9       
  0x002231D1  c745fc0d000000          mov      dword ptr [ebp - 4], 0xd       
  0x002231D8  8b4c85f0                mov      ecx, dword ptr [ebp + eax*4 - 0x10] 
  0x002231DC  0fb74508                movzx    eax, word ptr [ebp + 8]        
  0x002231E0  03c1                    add      eax, ecx                       
  0x002231E2  6bc038                  imul     eax, eax, 0x38                 
  0x002231E5  56                      push     esi                            
  0x002231E6  6a06                    push     6                              
  0x002231E8  33d2                    xor      edx, edx                       
  0x002231EA  5e                      pop      esi                            
  0x002231EB  f7f6                    div      esi                            
  0x002231ED  85c9                    test     ecx, ecx                       
  0x002231EF  5e                      pop      esi                            
  0x002231F0  7502                    jne      0x2231f4                       
  0x002231F2  33c0                    xor      eax, eax                       
                                        ; XREF: 0x002231F0 (cond_jump)
  0x002231F4  807d1000                cmp      byte ptr [ebp + 0x10], 0       
  0x002231F8  7403                    je       0x2231fd                       
  0x002231FA  c1e003                  shl      eax, 3                         
                                        ; XREF: 0x002231F8 (cond_jump)
  0x002231FD  c9                      leave                                   
  0x002231FE  c20c00                  ret      0xc                            
; end of function

; ============================================================
; Function: sub_00223201
; Start: 0x00223201  End: 0x00223236  Size: 53 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00220F8D
; ============================================================
sub_00223201:
  0x00223201  56                      push     esi                            
  0x00223202  b814f92100              mov      eax, 0x21f914                  
  0x00223207  be20f92100              mov      esi, 0x21f920                  
  0x0022320C  3bc6                    cmp      eax, esi                       
  0x0022320E  8bc8                    mov      ecx, eax                       
  0x00223210  731a                    jae      0x22322c                       
  0x00223212  8b542408                mov      edx, dword ptr [esp + 8]       
                                        ; XREF: 0x0022322A (cond_jump)
  0x00223216  8b01                    mov      eax, dword ptr [ecx]           
  0x00223218  85c0                    test     eax, eax                       
  0x0022321A  7409                    je       0x223225                       
  0x0022321C  3a7001                  cmp      dh, byte ptr [eax + 1]         
  0x0022321F  7504                    jne      0x223225                       
  0x00223221  3a10                    cmp      dl, byte ptr [eax]             
  0x00223223  740d                    je       0x223232                       
                                        ; XREF: 0x0022321A (cond_jump), 0x0022321F (cond_jump)
  0x00223225  83c104                  add      ecx, 4                         
  0x00223228  3bce                    cmp      ecx, esi                       
  0x0022322A  72ea                    jb       0x223216                       
                                        ; XREF: 0x00223210 (cond_jump)
  0x0022322C  33c0                    xor      eax, eax                       
                                        ; XREF: 0x00223234 (jump)
  0x0022322E  5e                      pop      esi                            
  0x0022322F  c20400                  ret      4                              
                                        ; XREF: 0x00223223 (cond_jump)
  0x00223232  8b01                    mov      eax, dword ptr [ecx]           
  0x00223234  ebf8                    jmp      0x22322e                       
; end of function

; ============================================================
; Function: sub_00223236
; Start: 0x00223236  End: 0x00223251  Size: 27 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0022394C, sub_00223BD4
; ============================================================
sub_00223236:
  0x00223236  68b06d2800              push     0x286db0                       
  0x0022323B  83c9ff                  or       ecx, 0xffffffff                
  0x0022323E  51                      push     ecx                            
  0x0022323F  b8800f05fd              mov      eax, 0xfd050f80                
  0x00223244  50                      push     eax                            
  0x00223245  68886d2800              push     0x286d88                       
  0x0022324A  ff15285b2200            call     dword ptr [0x225b28]           ; -> xbox_KeSetTimer
  0x00223250  c3                      ret                                     
; end of function
                                        ; XREF: 0x00224106 (data_imm)
  0x00223251  8b4c2408                mov      ecx, dword ptr [esp + 8]       
  0x00223255  68506d2800              push     0x286d50                       
  0x0022325A  e864e5ffff              call     0x2217c3                       ; -> sub_002217C3
  0x0022325F  c21000                  ret      0x10                           

; ============================================================
; Function: sub_00223262
; Start: 0x00223262  End: 0x00223285  Size: 35 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220A35, sub_002217DA
; Called by: sub_0022339A
; ============================================================
sub_00223262:
  0x00223262  56                      push     esi                            
  0x00223263  8bf1                    mov      esi, ecx                       
  0x00223265  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223267  6a00                    push     0                              
  0x00223269  e86ce5ffff              call     0x2217da                       ; -> sub_002217DA
  0x0022326E  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223270  e8c0d7ffff              call     0x220a35                       ; -> sub_00220A35
  0x00223275  832600                  and      dword ptr [esi], 0             
  0x00223278  806604fe                and      byte ptr [esi + 4], 0xfe       
  0x0022327C  66ff0d326d2800          dec      word ptr [0x286d32]            
  0x00223283  5e                      pop      esi                            
  0x00223284  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00223285
; Start: 0x00223285  End: 0x002232EF  Size: 106 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002218DF
; Called by: sub_00223DA6
; ============================================================
sub_00223285:
  0x00223285  51                      push     ecx                            
  0x00223286  53                      push     ebx                            
  0x00223287  55                      push     ebp                            
  0x00223288  33db                    xor      ebx, ebx                       
  0x0022328A  33ed                    xor      ebp, ebp                       
  0x0022328C  66391d306d2800          cmp      word ptr [0x286d30], bx        
  0x00223293  57                      push     edi                            
  0x00223294  8954240c                mov      dword ptr [esp + 0xc], edx     
  0x00223298  8bf9                    mov      edi, ecx                       
  0x0022329A  764c                    jbe      0x2232e8                       
  0x0022329C  56                      push     esi                            
                                        ; XREF: 0x002232E5 (cond_jump)
  0x0022329D  a1346d2800              mov      eax, dword ptr [0x286d34]      
  0x002232A2  0fb6f3                  movzx    esi, bl                        
  0x002232A5  6bf616                  imul     esi, esi, 0x16                 
  0x002232A8  03c6                    add      eax, esi                       
  0x002232AA  f6400401                test     byte ptr [eax + 4], 1          
  0x002232AE  7428                    je       0x2232d8                       
  0x002232B0  8b08                    mov      ecx, dword ptr [eax]           
  0x002232B2  e828e6ffff              call     0x2218df                       ; -> sub_002218DF
  0x002232B7  3b442410                cmp      eax, dword ptr [esp + 0x10]    
  0x002232BB  751b                    jne      0x2232d8                       
  0x002232BD  a1346d2800              mov      eax, dword ptr [0x286d34]      
  0x002232C2  03c6                    add      eax, esi                       
  0x002232C4  39780e                  cmp      dword ptr [eax + 0xe], edi     
  0x002232C7  750f                    jne      0x2232d8                       
  0x002232C9  8a4804                  mov      cl, byte ptr [eax + 4]         
  0x002232CC  f6c108                  test     cl, 8                          
  0x002232CF  7407                    je       0x2232d8                       
  0x002232D1  f6c102                  test     cl, 2                          
  0x002232D4  7502                    jne      0x2232d8                       
  0x002232D6  8be8                    mov      ebp, eax                       
                                        ; XREF: 0x002232AE (cond_jump), 0x002232BB (cond_jump), 0x002232C7 (cond_jump), 0x002232CF (cond_jump), 0x002232D4 (cond_jump)
  0x002232D8  fec3                    inc      bl                             
  0x002232DA  660fb6c3                movzx    ax, bl                         
  0x002232DE  663b05306d2800          cmp      ax, word ptr [0x286d30]        
  0x002232E5  72b6                    jb       0x22329d                       
  0x002232E7  5e                      pop      esi                            
                                        ; XREF: 0x0022329A (cond_jump)
  0x002232E8  5f                      pop      edi                            
  0x002232E9  8bc5                    mov      eax, ebp                       
  0x002232EB  5d                      pop      ebp                            
  0x002232EC  5b                      pop      ebx                            
  0x002232ED  59                      pop      ecx                            
  0x002232EE  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002232EF
; Start: 0x002232EF  End: 0x0022339A  Size: 171 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00221B1F
; Called by: sub_00223DA6
; ============================================================
sub_002232EF:
  0x002232EF  55                      push     ebp                            
  0x002232F0  8bec                    mov      ebp, esp                       
  0x002232F2  51                      push     ecx                            
  0x002232F3  53                      push     ebx                            
  0x002232F4  56                      push     esi                            
  0x002232F5  8bf1                    mov      esi, ecx                       
  0x002232F7  83665a00                and      dword ptr [esi + 0x5a], 0      
  0x002232FB  57                      push     edi                            
  0x002232FC  8b3e                    mov      edi, dword ptr [esi]           
  0x002232FE  8d5e52                  lea      ebx, [esi + 0x52]              
  0x00223301  c60320                  mov      byte ptr [ebx], 0x20           
  0x00223304  c6465382                mov      byte ptr [esi + 0x53], 0x82    
  0x00223308  8b0f                    mov      ecx, dword ptr [edi]           
  0x0022330A  53                      push     ebx                            
  0x0022330B  8955fc                  mov      dword ptr [ebp - 4], edx       
  0x0022330E  e80ce8ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00223313  85c0                    test     eax, eax                       
  0x00223315  7c7e                    jl       0x223395                       
  0x00223317  808ea200000002          or       byte ptr [esi + 0xa2], 2       
  0x0022331E  83665a00                and      dword ptr [esi + 0x5a], 0      
  0x00223322  c60320                  mov      byte ptr [ebx], 0x20           
  0x00223325  c6465302                mov      byte ptr [esi + 0x53], 2       
  0x00223329  8a4708                  mov      al, byte ptr [edi + 8]         
  0x0022332C  884667                  mov      byte ptr [esi + 0x67], al      
  0x0022332F  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x00223332  c6466803                mov      byte ptr [esi + 0x68], 3       
  0x00223336  8a4001                  mov      al, byte ptr [eax + 1]         
  0x00223339  884669                  mov      byte ptr [esi + 0x69], al      
  0x0022333C  66c7466e2000            mov      word ptr [esi + 0x6e], 0x20    
  0x00223342  8b0f                    mov      ecx, dword ptr [edi]           
  0x00223344  53                      push     ebx                            
  0x00223345  e8d5e7ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x0022334A  85c0                    test     eax, eax                       
  0x0022334C  7c47                    jl       0x223395                       
  0x0022334E  8b4e62                  mov      ecx, dword ptr [esi + 0x62]    
  0x00223351  894e0c                  mov      dword ptr [esi + 0xc], ecx     
  0x00223354  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x00223357  f60102                  test     byte ptr [ecx], 2              
  0x0022335A  7439                    je       0x223395                       
  0x0022335C  807f0900                cmp      byte ptr [edi + 9], 0          
  0x00223360  7433                    je       0x223395                       
  0x00223362  83665a00                and      dword ptr [esi + 0x5a], 0      
  0x00223366  c60320                  mov      byte ptr [ebx], 0x20           
  0x00223369  c6465302                mov      byte ptr [esi + 0x53], 2       
  0x0022336D  8a4709                  mov      al, byte ptr [edi + 9]         
  0x00223370  884667                  mov      byte ptr [esi + 0x67], al      
  0x00223373  c6466803                mov      byte ptr [esi + 0x68], 3       
  0x00223377  8a4102                  mov      al, byte ptr [ecx + 2]         
  0x0022337A  884669                  mov      byte ptr [esi + 0x69], al      
  0x0022337D  66c7466e2000            mov      word ptr [esi + 0x6e], 0x20    
  0x00223383  8b0f                    mov      ecx, dword ptr [edi]           
  0x00223385  53                      push     ebx                            
  0x00223386  e894e7ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x0022338B  85c0                    test     eax, eax                       
  0x0022338D  7c06                    jl       0x223395                       
  0x0022338F  8b4e62                  mov      ecx, dword ptr [esi + 0x62]    
  0x00223392  894e10                  mov      dword ptr [esi + 0x10], ecx    
                                        ; XREF: 0x00223315 (cond_jump), 0x0022334C (cond_jump), 0x0022335A (cond_jump), 0x00223360 (cond_jump), 0x0022338D (cond_jump)
  0x00223395  5f                      pop      edi                            
  0x00223396  5e                      pop      esi                            
  0x00223397  5b                      pop      ebx                            
  0x00223398  c9                      leave                                   
  0x00223399  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022339A
; Start: 0x0022339A  End: 0x0022344B  Size: 177 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00221B1F, sub_00223262
; Called by: sub_0022381F
; ============================================================
sub_0022339A:
  0x0022339A  56                      push     esi                            
  0x0022339B  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0022339F  f686a200000002          test     byte ptr [esi + 0xa2], 2       
  0x002233A6  8b06                    mov      eax, dword ptr [esi]           
  0x002233A8  8b08                    mov      ecx, dword ptr [eax]           
  0x002233AA  57                      push     edi                            
  0x002233AB  741e                    je       0x2233cb                       
  0x002233AD  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x002233B1  c6001c                  mov      byte ptr [eax], 0x1c           
  0x002233B4  c64001c3                mov      byte ptr [eax + 1], 0xc3       
  0x002233B8  c740089a332200          mov      dword ptr [eax + 8], 0x22339a  
  0x002233BF  89700c                  mov      dword ptr [eax + 0xc], esi     
  0x002233C2  80a6a2000000fd          and      byte ptr [esi + 0xa2], 0xfd    
  0x002233C9  eb4a                    jmp      0x223415                       
                                        ; XREF: 0x002233AB (cond_jump)
  0x002233CB  33ff                    xor      edi, edi                       
  0x002233CD  397e0c                  cmp      dword ptr [esi + 0xc], edi     
  0x002233D0  7420                    je       0x2233f2                       
  0x002233D2  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x002233D6  c6001c                  mov      byte ptr [eax], 0x1c           
  0x002233D9  c6400143                mov      byte ptr [eax + 1], 0x43       
  0x002233DD  c740089a332200          mov      dword ptr [eax + 8], 0x22339a  
  0x002233E4  89700c                  mov      dword ptr [eax + 0xc], esi     
  0x002233E7  8b560c                  mov      edx, dword ptr [esi + 0xc]     
  0x002233EA  895010                  mov      dword ptr [eax + 0x10], edx    
  0x002233ED  897e0c                  mov      dword ptr [esi + 0xc], edi     
  0x002233F0  eb23                    jmp      0x223415                       
                                        ; XREF: 0x002233D0 (cond_jump)
  0x002233F2  397e10                  cmp      dword ptr [esi + 0x10], edi    
  0x002233F5  7426                    je       0x22341d                       
  0x002233F7  8b44240c                mov      eax, dword ptr [esp + 0xc]     
  0x002233FB  c6001c                  mov      byte ptr [eax], 0x1c           
  0x002233FE  c6400143                mov      byte ptr [eax + 1], 0x43       
  0x00223402  c740089a332200          mov      dword ptr [eax + 8], 0x22339a  
  0x00223409  89700c                  mov      dword ptr [eax + 0xc], esi     
  0x0022340C  8b5610                  mov      edx, dword ptr [esi + 0x10]    
  0x0022340F  895010                  mov      dword ptr [eax + 0x10], edx    
  0x00223412  897e10                  mov      dword ptr [esi + 0x10], edi    
                                        ; XREF: 0x002233C9 (jump), 0x002233F0 (jump)
  0x00223415  50                      push     eax                            
  0x00223416  e804e7ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x0022341B  eb29                    jmp      0x223446                       
                                        ; XREF: 0x002233F5 (cond_jump)
  0x0022341D  897812                  mov      dword ptr [eax + 0x12], edi    
  0x00223420  893e                    mov      dword ptr [esi], edi           
  0x00223422  f6400402                test     byte ptr [eax + 4], 2          
  0x00223426  7407                    je       0x22342f                       
  0x00223428  8bc8                    mov      ecx, eax                       
  0x0022342A  e833feffff              call     0x223262                       ; -> sub_00223262
                                        ; XREF: 0x00223426 (cond_jump)
  0x0022342F  f686a200000001          test     byte ptr [esi + 0xa2], 1       
  0x00223436  740e                    je       0x223446                       
  0x00223438  57                      push     edi                            
  0x00223439  57                      push     edi                            
  0x0022343A  ffb69e000000            push     dword ptr [esi + 0x9e]         
  0x00223440  ff15405b2200            call     dword ptr [0x225b40]           ; -> xbox_KeSetEvent
                                        ; XREF: 0x0022341B (jump), 0x00223436 (cond_jump)
  0x00223446  5f                      pop      edi                            
  0x00223447  5e                      pop      esi                            
  0x00223448  c20800                  ret      8                              
; end of function
                                        ; XREF: 0x0022355A (data_imm), 0x00223F8C (data_imm)
  0x0022344B  53                      push     ebx                            
  0x0022344C  8b5c240c                mov      ebx, dword ptr [esp + 0xc]     
  0x00223450  f683a200000001          test     byte ptr [ebx + 0xa2], 1       
  0x00223457  57                      push     edi                            
  0x00223458  8b3b                    mov      edi, dword ptr [ebx]           
  0x0022345A  7547                    jne      0x2234a3                       
  0x0022345C  8a4704                  mov      al, byte ptr [edi + 4]         
  0x0022345F  a802                    test     al, 2                          
  0x00223461  7540                    jne      0x2234a3                       
  0x00223463  56                      push     esi                            
  0x00223464  8b742410                mov      esi, dword ptr [esp + 0x10]    
  0x00223468  33c9                    xor      ecx, ecx                       
  0x0022346A  394e04                  cmp      dword ptr [esi + 4], ecx       
  0x0022346D  7c39                    jl       0x2234a8                       
  0x0022346F  240f                    and      al, 0xf                        
  0x00223471  884704                  mov      byte ptr [edi + 4], al         
  0x00223474  8b470e                  mov      eax, dword ptr [edi + 0xe]     
  0x00223477  8bcb                    mov      ecx, ebx                       
  0x00223479  ff5024                  call     dword ptr [eax + 0x24]         
  0x0022347C  808ba200000010          or       byte ptr [ebx + 0xa2], 0x10    
  0x00223483  ff4308                  inc      dword ptr [ebx + 8]            
  0x00223486  83630400                and      dword ptr [ebx + 4], 0         
  0x0022348A  0fb6470c                movzx    eax, byte ptr [edi + 0xc]      
  0x0022348E  894614                  mov      dword ptr [esi + 0x14], eax    
  0x00223491  f683a200000008          test     byte ptr [ebx + 0xa2], 8       
  0x00223498  7408                    je       0x2234a2                       
                                        ; XREF: 0x002234FC (cond_jump)
  0x0022349A  8b0f                    mov      ecx, dword ptr [edi]           
  0x0022349C  56                      push     esi                            
  0x0022349D  e87de6ffff              call     0x221b1f                       ; -> sub_00221B1F
                                        ; XREF: 0x00223498 (cond_jump), 0x00223505 (jump)
  0x002234A2  5e                      pop      esi                            
                                        ; XREF: 0x0022345A (cond_jump), 0x00223461 (cond_jump)
  0x002234A3  5f                      pop      edi                            
  0x002234A4  5b                      pop      ebx                            
  0x002234A5  c20800                  ret      8                              
                                        ; XREF: 0x0022346D (cond_jump)
  0x002234A8  894e10                  mov      dword ptr [esi + 0x10], ecx    
  0x002234AB  894e18                  mov      dword ptr [esi + 0x18], ecx    
  0x002234AE  894e14                  mov      dword ptr [esi + 0x14], ecx    
  0x002234B1  66894e2a                mov      word ptr [esi + 0x2a], cx      
  0x002234B5  c60630                  mov      byte ptr [esi], 0x30           
  0x002234B8  c6460140                mov      byte ptr [esi + 1], 0x40       
  0x002234BC  c7460807352200          mov      dword ptr [esi + 8], 0x223507  
  0x002234C3  895e0c                  mov      dword ptr [esi + 0xc], ebx     
  0x002234C6  c6461c00                mov      byte ptr [esi + 0x1c], 0       
  0x002234CA  c6461d00                mov      byte ptr [esi + 0x1d], 0       
  0x002234CE  c6461e00                mov      byte ptr [esi + 0x1e], 0       
  0x002234D2  c6462802                mov      byte ptr [esi + 0x28], 2       
  0x002234D6  c6462901                mov      byte ptr [esi + 0x29], 1       
  0x002234DA  660fb64708              movzx    ax, byte ptr [edi + 8]         
  0x002234DF  6689462c                mov      word ptr [esi + 0x2c], ax      
  0x002234E3  66894e2e                mov      word ptr [esi + 0x2e], cx      
  0x002234E7  8a4f04                  mov      cl, byte ptr [edi + 4]         
  0x002234EA  8ac1                    mov      al, cl                         
  0x002234EC  24f0                    and      al, 0xf0                       
  0x002234EE  0410                    add      al, 0x10                       
  0x002234F0  80e10f                  and      cl, 0xf                        
  0x002234F3  32c1                    xor      al, cl                         
  0x002234F5  884704                  mov      byte ptr [edi + 4], al         
  0x002234F8  24f0                    and      al, 0xf0                       
  0x002234FA  3c40                    cmp      al, 0x40                       
  0x002234FC  759c                    jne      0x22349a                       
  0x002234FE  8b0f                    mov      ecx, dword ptr [edi]           
  0x00223500  e81ed7ffff              call     0x220c23                       ; -> sub_00220C23
  0x00223505  eb9b                    jmp      0x2234a2                       
                                        ; XREF: 0x002234BC (data_imm)
  0x00223507  53                      push     ebx                            
  0x00223508  56                      push     esi                            
  0x00223509  8b742410                mov      esi, dword ptr [esp + 0x10]    
  0x0022350D  8b1e                    mov      ebx, dword ptr [esi]           
  0x0022350F  f6430402                test     byte ptr [ebx + 4], 2          
  0x00223513  7577                    jne      0x22358c                       
  0x00223515  f686a200000001          test     byte ptr [esi + 0xa2], 1       
  0x0022351C  756e                    jne      0x22358c                       
  0x0022351E  57                      push     edi                            
  0x0022351F  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x00223523  837f0400                cmp      dword ptr [edi + 4], 0         
  0x00223527  7c5b                    jl       0x223584                       
  0x00223529  83670800                and      dword ptr [edi + 8], 0         
  0x0022352D  c60718                  mov      byte ptr [edi], 0x18           
  0x00223530  c6470105                mov      byte ptr [edi + 1], 5          
  0x00223534  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x00223537  894710                  mov      dword ptr [edi + 0x10], eax    
  0x0022353A  c7471404000000          mov      dword ptr [edi + 0x14], 4      
  0x00223541  8b0b                    mov      ecx, dword ptr [ebx]           
  0x00223543  57                      push     edi                            
  0x00223544  e8d6e5ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00223549  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x0022354C  894662                  mov      dword ptr [esi + 0x62], eax    
  0x0022354F  8d4632                  lea      eax, [esi + 0x32]              
  0x00223552  c6465228                mov      byte ptr [esi + 0x52], 0x28    
  0x00223556  c6465341                mov      byte ptr [esi + 0x53], 0x41    
  0x0022355A  c7465a4b342200          mov      dword ptr [esi + 0x5a], 0x22344b 
  0x00223561  89765e                  mov      dword ptr [esi + 0x5e], esi    
  0x00223564  89466a                  mov      dword ptr [esi + 0x6a], eax    
  0x00223567  0fb6430c                movzx    eax, byte ptr [ebx + 0xc]      
  0x0022356B  894666                  mov      dword ptr [esi + 0x66], eax    
  0x0022356E  c6466e02                mov      byte ptr [esi + 0x6e], 2       
  0x00223572  c6466f01                mov      byte ptr [esi + 0x6f], 1       
  0x00223576  c6467000                mov      byte ptr [esi + 0x70], 0       
  0x0022357A  8b0b                    mov      ecx, dword ptr [ebx]           
  0x0022357C  57                      push     edi                            
  0x0022357D  e89de5ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00223582  eb07                    jmp      0x22358b                       
                                        ; XREF: 0x00223527 (cond_jump)
  0x00223584  8b0b                    mov      ecx, dword ptr [ebx]           
  0x00223586  e898d6ffff              call     0x220c23                       ; -> sub_00220C23
                                        ; XREF: 0x00223582 (jump)
  0x0022358B  5f                      pop      edi                            
                                        ; XREF: 0x00223513 (cond_jump), 0x0022351C (cond_jump)
  0x0022358C  5e                      pop      esi                            
  0x0022358D  5b                      pop      ebx                            
  0x0022358E  c20800                  ret      8                              
  0x00223591  8bc1                    mov      eax, ecx                       
  0x00223593  8b4866                  mov      ecx, dword ptr [eax + 0x66]    
  0x00223596  53                      push     ebx                            
  0x00223597  33db                    xor      ebx, ebx                       
  0x00223599  83f902                  cmp      ecx, 2                         
  0x0022359C  8d5014                  lea      edx, [eax + 0x14]              
  0x0022359F  7240                    jb       0x2235e1                       
  0x002235A1  56                      push     esi                            
  0x002235A2  83c1fe                  add      ecx, -2                        
  0x002235A5  57                      push     edi                            
  0x002235A6  8d7034                  lea      esi, [eax + 0x34]              
  0x002235A9  8bc1                    mov      eax, ecx                       
  0x002235AB  c1e902                  shr      ecx, 2                         
  0x002235AE  8bfa                    mov      edi, edx                       
  0x002235B0  f3a5                    rep movsd dword ptr es:[edi], dword ptr [esi] 
  0x002235B2  8bc8                    mov      ecx, eax                       
  0x002235B4  83e103                  and      ecx, 3                         
  0x002235B7  6a08                    push     8                              
  0x002235B9  f3a4                    rep movsb byte ptr es:[edi], byte ptr [esi] 
  0x002235BB  59                      pop      ecx                            
  0x002235BC  5f                      pop      edi                            
  0x002235BD  8d4202                  lea      eax, [edx + 2]                 
  0x002235C0  5e                      pop      esi                            
                                        ; XREF: 0x002235D0 (cond_jump)
  0x002235C1  803820                  cmp      byte ptr [eax], 0x20           
  0x002235C4  7305                    jae      0x2235cb                       
  0x002235C6  c60000                  mov      byte ptr [eax], 0              
  0x002235C9  eb03                    jmp      0x2235ce                       
                                        ; XREF: 0x002235C4 (cond_jump)
  0x002235CB  33db                    xor      ebx, ebx                       
  0x002235CD  43                      inc      ebx                            
                                        ; XREF: 0x002235C9 (jump)
  0x002235CE  40                      inc      eax                            
  0x002235CF  49                      dec      ecx                            
  0x002235D0  75ef                    jne      0x2235c1                       
  0x002235D2  85db                    test     ebx, ebx                       
  0x002235D4  7505                    jne      0x2235db                       
  0x002235D6  f6023f                  test     byte ptr [edx], 0x3f           
  0x002235D9  7406                    je       0x2235e1                       
                                        ; XREF: 0x002235D4 (cond_jump)
  0x002235DB  5b                      pop      ebx                            
  0x002235DC  e97a34e9ff              jmp      0xb6a5b                        ; -> sub_000B6A5B
                                        ; XREF: 0x0022359F (cond_jump), 0x002235D9 (cond_jump)
  0x002235E1  5b                      pop      ebx                            
  0x002235E2  c3                      ret                                     
  0x002235E3  8bc1                    mov      eax, ecx                       
  0x002235E5  8b4866                  mov      ecx, dword ptr [eax + 0x66]    
  0x002235E8  49                      dec      ecx                            
  0x002235E9  56                      push     esi                            
  0x002235EA  49                      dec      ecx                            
  0x002235EB  57                      push     edi                            
  0x002235EC  8d7034                  lea      esi, [eax + 0x34]              
  0x002235EF  8d7814                  lea      edi, [eax + 0x14]              
  0x002235F2  8bc1                    mov      eax, ecx                       
  0x002235F4  c1e902                  shr      ecx, 2                         
  0x002235F7  f3a5                    rep movsd dword ptr es:[edi], dword ptr [esi] 
  0x002235F9  8bc8                    mov      ecx, eax                       
  0x002235FB  83e103                  and      ecx, 3                         
  0x002235FE  f3a4                    rep movsb byte ptr es:[edi], byte ptr [esi] 
  0x00223600  5f                      pop      edi                            
  0x00223601  5e                      pop      esi                            
  0x00223602  e95434e9ff              jmp      0xb6a5b                        ; -> sub_000B6A5B

; ============================================================
; Function: sub_00223607
; Start: 0x00223607  End: 0x00223634  Size: 45 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002217F5
; ============================================================
sub_00223607:
  0x00223607  56                      push     esi                            
  0x00223608  57                      push     edi                            
  0x00223609  ff7104                  push     dword ptr [ecx + 4]            
  0x0022360C  8bf2                    mov      esi, edx                       
  0x0022360E  8b7e0c                  mov      edi, dword ptr [esi + 0xc]     
  0x00223611  e8dfe1ffff              call     0x2217f5                       ; -> sub_002217F5
  0x00223616  85ff                    test     edi, edi                       
  0x00223618  8906                    mov      dword ptr [esi], eax           
  0x0022361A  7415                    je       0x223631                       
  0x0022361C  6a00                    push     0                              
  0x0022361E  6a00                    push     0                              
  0x00223620  57                      push     edi                            
  0x00223621  ff15405b2200            call     dword ptr [0x225b40]           ; -> xbox_KeSetEvent
  0x00223627  8bcf                    mov      ecx, edi                       
  0x00223629  5f                      pop      edi                            
  0x0022362A  5e                      pop      esi                            
  0x0022362B  ff25445a2200            jmp      dword ptr [0x225a44]           
                                        ; XREF: 0x0022361A (cond_jump)
  0x00223631  5f                      pop      edi                            
  0x00223632  5e                      pop      esi                            
  0x00223633  c3                      ret                                     
; end of function
                                        ; XREF: 0x0022387C (data_imm)
  0x00223634  56                      push     esi                            
  0x00223635  57                      push     edi                            
  0x00223636  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x0022363A  8b4708                  mov      eax, dword ptr [edi + 8]       
  0x0022363D  f680a200000001          test     byte ptr [eax + 0xa2], 1       
  0x00223644  8b08                    mov      ecx, dword ptr [eax]           
  0x00223646  7539                    jne      0x223681                       
  0x00223648  f6410402                test     byte ptr [ecx + 4], 2          
  0x0022364C  7533                    jne      0x223681                       
  0x0022364E  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00223652  837e0400                cmp      dword ptr [esi + 4], 0         
  0x00223656  7c20                    jl       0x223678                       
  0x00223658  83660800                and      dword ptr [esi + 8], 0         
  0x0022365C  c60618                  mov      byte ptr [esi], 0x18           
  0x0022365F  c6460105                mov      byte ptr [esi + 1], 5          
  0x00223663  8b4010                  mov      eax, dword ptr [eax + 0x10]    
  0x00223666  894610                  mov      dword ptr [esi + 0x10], eax    
  0x00223669  c7461404000000          mov      dword ptr [esi + 0x14], 4      
  0x00223670  8b09                    mov      ecx, dword ptr [ecx]           
  0x00223672  56                      push     esi                            
  0x00223673  e8a7e4ffff              call     0x221b1f                       ; -> sub_00221B1F
                                        ; XREF: 0x00223656 (cond_jump)
  0x00223678  c74604040000c0          mov      dword ptr [esi + 4], 0xc0000004 
  0x0022367F  eb0b                    jmp      0x22368c                       
                                        ; XREF: 0x00223646 (cond_jump), 0x0022364C (cond_jump)
  0x00223681  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00223685  c7460400070080          mov      dword ptr [esi + 4], 0x80000700 
                                        ; XREF: 0x0022367F (jump)
  0x0022368C  8bd7                    mov      edx, edi                       
  0x0022368E  8bce                    mov      ecx, esi                       
  0x00223690  e872ffffff              call     0x223607                       ; -> sub_00223607
  0x00223695  5f                      pop      edi                            
  0x00223696  5e                      pop      esi                            
  0x00223697  c20800                  ret      8                              
                                        ; XREF: 0x00221B55 (data_imm), 0x00223EF2 (data_imm)
  0x0022369A  6a00                    push     0                              
  0x0022369C  6a00                    push     0                              
  0x0022369E  ff742410                push     dword ptr [esp + 0x10]         
  0x002236A2  ff15405b2200            call     dword ptr [0x225b40]           ; -> xbox_KeSetEvent
  0x002236A8  c20800                  ret      8                              

; ============================================================
; Function: sub_002236AB
; Start: 0x002236AB  End: 0x002236F8  Size: 77 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002217C3
; Called by: sub_00223DA6
; ============================================================
sub_002236AB:
  0x002236AB  55                      push     ebp                            
  0x002236AC  8bec                    mov      ebp, esp                       
  0x002236AE  83ec0c                  sub      esp, 0xc                       
  0x002236B1  834df8ff                or       dword ptr [ebp - 8], 0xffffffff 
  0x002236B5  53                      push     ebx                            
  0x002236B6  56                      push     esi                            
  0x002236B7  8b35485b2200            mov      esi, dword ptr [0x225b48]      
  0x002236BD  57                      push     edi                            
  0x002236BE  8d45f4                  lea      eax, [ebp - 0xc]               
  0x002236C1  50                      push     eax                            
  0x002236C2  33ff                    xor      edi, edi                       
  0x002236C4  57                      push     edi                            
  0x002236C5  57                      push     edi                            
  0x002236C6  57                      push     edi                            
  0x002236C7  ff7508                  push     dword ptr [ebp + 8]            
  0x002236CA  8bda                    mov      ebx, edx                       
  0x002236CC  894dfc                  mov      dword ptr [ebp - 4], ecx       
  0x002236CF  c745f4e05ef8ff          mov      dword ptr [ebp - 0xc], 0xfff85ee0 
  0x002236D6  ffd6                    call     esi                            
  0x002236D8  3d02010000              cmp      eax, 0x102                     
  0x002236DD  7512                    jne      0x2236f1                       
  0x002236DF  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x002236E2  53                      push     ebx                            
  0x002236E3  e8dbe0ffff              call     0x2217c3                       ; -> sub_002217C3
  0x002236E8  57                      push     edi                            
  0x002236E9  57                      push     edi                            
  0x002236EA  57                      push     edi                            
  0x002236EB  57                      push     edi                            
  0x002236EC  ff7508                  push     dword ptr [ebp + 8]            
  0x002236EF  ffd6                    call     esi                            
                                        ; XREF: 0x002236DD (cond_jump)
  0x002236F1  5f                      pop      edi                            
  0x002236F2  5e                      pop      esi                            
  0x002236F3  5b                      pop      ebx                            
  0x002236F4  c9                      leave                                   
  0x002236F5  c20400                  ret      4                              
; end of function
                                        ; XREF: 0x002238E1 (data_imm)
  0x002236F8  53                      push     ebx                            
  0x002236F9  56                      push     esi                            
  0x002236FA  57                      push     edi                            
  0x002236FB  68886d2800              push     0x286d88                       
  0x00223700  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00223706  8b742414                mov      esi, dword ptr [esp + 0x14]    
  0x0022370A  8d7e0a                  lea      edi, [esi + 0xa]               
  0x0022370D  8bd7                    mov      edx, edi                       
  0x0022370F  b102                    mov      cl, 2                          
  0x00223711  e8dbdeffff              call     0x2215f1                       ; -> sub_002215F1
  0x00223716  8bd8                    mov      ebx, eax                       
  0x00223718  85db                    test     ebx, ebx                       
  0x0022371A  743b                    je       0x223757                       
  0x0022371C  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022371E  e8bce1ffff              call     0x2218df                       ; -> sub_002218DF
  0x00223723  8bd0                    mov      edx, eax                       
  0x00223725  8bcb                    mov      ecx, ebx                       
  0x00223727  e859fbffff              call     0x223285                       ; -> sub_00223285
  0x0022372C  85c0                    test     eax, eax                       
  0x0022372E  7527                    jne      0x223757                       
  0x00223730  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223732  88460b                  mov      byte ptr [esi + 0xb], al       
  0x00223735  8a07                    mov      al, byte ptr [edi]             
  0x00223737  895e0e                  mov      dword ptr [esi + 0xe], ebx     
  0x0022373A  c6460c08                mov      byte ptr [esi + 0xc], 8        
  0x0022373E  c6460d01                mov      byte ptr [esi + 0xd], 1        
  0x00223742  50                      push     eax                            
  0x00223743  e8a3e0ffff              call     0x2217eb                       ; -> sub_002217EB
  0x00223748  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022374A  6a00                    push     0                              
  0x0022374C  e8b0d6ffff              call     0x220e01                       ; -> sub_00220E01
  0x00223751  804e0408                or       byte ptr [esi + 4], 8          
  0x00223755  eb25                    jmp      0x22377c                       
                                        ; XREF: 0x0022371A (cond_jump), 0x0022372E (cond_jump)
  0x00223757  8b3e                    mov      edi, dword ptr [esi]           
  0x00223759  832600                  and      dword ptr [esi], 0             
  0x0022375C  806604fe                and      byte ptr [esi + 4], 0xfe       
  0x00223760  66ff0d326d2800          dec      word ptr [0x286d32]            
  0x00223767  6a00                    push     0                              
  0x00223769  8bcf                    mov      ecx, edi                       
  0x0022376B  e86ae0ffff              call     0x2217da                       ; -> sub_002217DA
  0x00223770  6800040080              push     0x80000400                     
  0x00223775  8bcf                    mov      ecx, edi                       
  0x00223777  e885d6ffff              call     0x220e01                       ; -> sub_00220E01
                                        ; XREF: 0x00223755 (jump)
  0x0022377C  5f                      pop      edi                            
  0x0022377D  5e                      pop      esi                            
  0x0022377E  5b                      pop      ebx                            
  0x0022377F  c20800                  ret      8                              
                                        ; XREF: 0x0022396C (data_imm)
  0x00223782  53                      push     ebx                            
  0x00223783  55                      push     ebp                            
  0x00223784  56                      push     esi                            
  0x00223785  57                      push     edi                            
  0x00223786  68886d2800              push     0x286d88                       
  0x0022378B  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00223791  8b742418                mov      esi, dword ptr [esp + 0x18]    
  0x00223795  8d6e0a                  lea      ebp, [esi + 0xa]               
  0x00223798  8bd5                    mov      edx, ebp                       
  0x0022379A  b104                    mov      cl, 4                          
  0x0022379C  e850deffff              call     0x2215f1                       ; -> sub_002215F1
  0x002237A1  8bf8                    mov      edi, eax                       
  0x002237A3  33db                    xor      ebx, ebx                       
  0x002237A5  3bfb                    cmp      edi, ebx                       
  0x002237A7  744c                    je       0x2237f5                       
  0x002237A9  8b0e                    mov      ecx, dword ptr [esi]           
  0x002237AB  e82fe1ffff              call     0x2218df                       ; -> sub_002218DF
  0x002237B0  8bd0                    mov      edx, eax                       
  0x002237B2  8bcf                    mov      ecx, edi                       
  0x002237B4  e8ccfaffff              call     0x223285                       ; -> sub_00223285
  0x002237B9  85c0                    test     eax, eax                       
  0x002237BB  7538                    jne      0x2237f5                       
  0x002237BD  8a4e06                  mov      cl, byte ptr [esi + 6]         
  0x002237C0  897e0e                  mov      dword ptr [esi + 0xe], edi     
  0x002237C3  885e0b                  mov      byte ptr [esi + 0xb], bl       
  0x002237C6  8b4708                  mov      eax, dword ptr [edi + 8]       
  0x002237C9  8a00                    mov      al, byte ptr [eax]             
  0x002237CB  3ac8                    cmp      cl, al                         
  0x002237CD  7305                    jae      0x2237d4                       
  0x002237CF  884e0c                  mov      byte ptr [esi + 0xc], cl       
  0x002237D2  eb03                    jmp      0x2237d7                       
                                        ; XREF: 0x002237CD (cond_jump)
  0x002237D4  88460c                  mov      byte ptr [esi + 0xc], al       
                                        ; XREF: 0x002237D2 (jump)
  0x002237D7  8b0e                    mov      ecx, dword ptr [esi]           
  0x002237D9  33c0                    xor      eax, eax                       
  0x002237DB  8a4500                  mov      al, byte ptr [ebp]             
  0x002237DE  885e0d                  mov      byte ptr [esi + 0xd], bl       
  0x002237E1  50                      push     eax                            
  0x002237E2  e804e0ffff              call     0x2217eb                       ; -> sub_002217EB
  0x002237E7  8b0e                    mov      ecx, dword ptr [esi]           
  0x002237E9  53                      push     ebx                            
  0x002237EA  e812d6ffff              call     0x220e01                       ; -> sub_00220E01
  0x002237EF  804e0408                or       byte ptr [esi + 4], 8          
  0x002237F3  eb23                    jmp      0x223818                       
                                        ; XREF: 0x002237A7 (cond_jump), 0x002237BB (cond_jump)
  0x002237F5  8b3e                    mov      edi, dword ptr [esi]           
  0x002237F7  806604fe                and      byte ptr [esi + 4], 0xfe       
  0x002237FB  891e                    mov      dword ptr [esi], ebx           
  0x002237FD  66ff0d326d2800          dec      word ptr [0x286d32]            
  0x00223804  53                      push     ebx                            
  0x00223805  8bcf                    mov      ecx, edi                       
  0x00223807  e8cedfffff              call     0x2217da                       ; -> sub_002217DA
  0x0022380C  6800040080              push     0x80000400                     
  0x00223811  8bcf                    mov      ecx, edi                       
  0x00223813  e8e9d5ffff              call     0x220e01                       ; -> sub_00220E01
                                        ; XREF: 0x002237F3 (jump)
  0x00223818  5f                      pop      edi                            
  0x00223819  5e                      pop      esi                            
  0x0022381A  5d                      pop      ebp                            
  0x0022381B  5b                      pop      ebx                            
  0x0022381C  c20800                  ret      8                              

; ============================================================
; Function: sub_0022381F
; Start: 0x0022381F  End: 0x0022383D  Size: 30 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022339A
; Called by: sub_00223A12
; ============================================================
sub_0022381F:
  0x0022381F  8d91a2000000            lea      edx, [ecx + 0xa2]              
  0x00223825  8a02                    mov      al, byte ptr [edx]             
  0x00223827  a804                    test     al, 4                          
  0x00223829  7511                    jne      0x22383c                       
  0x0022382B  51                      push     ecx                            
  0x0022382C  81c182000000            add      ecx, 0x82                      
  0x00223832  0c04                    or       al, 4                          
  0x00223834  51                      push     ecx                            
  0x00223835  8802                    mov      byte ptr [edx], al             
  0x00223837  e85efbffff              call     0x22339a                       ; -> sub_0022339A
                                        ; XREF: 0x00223829 (cond_jump)
  0x0022383C  c3                      ret                                     
; end of function
                                        ; XREF: 0x00223B33 (data_imm)
  0x0022383D  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00223841  8b4a08                  mov      ecx, dword ptr [edx + 8]       
  0x00223844  8b01                    mov      eax, dword ptr [ecx]           
  0x00223846  f681a200000001          test     byte ptr [ecx + 0xa2], 1       
  0x0022384D  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00223851  7506                    jne      0x223859                       
  0x00223853  f6400402                test     byte ptr [eax + 4], 2          
  0x00223857  7407                    je       0x223860                       
                                        ; XREF: 0x00223851 (cond_jump)
  0x00223859  c7410400070080          mov      dword ptr [ecx + 4], 0x80000700 
                                        ; XREF: 0x00223857 (cond_jump)
  0x00223860  817904040000c0          cmp      dword ptr [ecx + 4], 0xc0000004 
  0x00223867  7550                    jne      0x2238b9                       
  0x00223869  80790141                cmp      byte ptr [ecx + 1], 0x41       
  0x0022386D  754a                    jne      0x2238b9                       
  0x0022386F  89510c                  mov      dword ptr [ecx + 0xc], edx     
  0x00223872  33d2                    xor      edx, edx                       
  0x00223874  56                      push     esi                            
  0x00223875  c60130                  mov      byte ptr [ecx], 0x30           
  0x00223878  c6410140                mov      byte ptr [ecx + 1], 0x40       
  0x0022387C  c7410834362200          mov      dword ptr [ecx + 8], 0x223634  
  0x00223883  895110                  mov      dword ptr [ecx + 0x10], edx    
  0x00223886  895118                  mov      dword ptr [ecx + 0x18], edx    
  0x00223889  895114                  mov      dword ptr [ecx + 0x14], edx    
  0x0022388C  88511c                  mov      byte ptr [ecx + 0x1c], dl      
  0x0022388F  88511d                  mov      byte ptr [ecx + 0x1d], dl      
  0x00223892  88511e                  mov      byte ptr [ecx + 0x1e], dl      
  0x00223895  c6412802                mov      byte ptr [ecx + 0x28], 2       
  0x00223899  c6412901                mov      byte ptr [ecx + 0x29], 1       
  0x0022389D  6689512a                mov      word ptr [ecx + 0x2a], dx      
  0x002238A1  660fb67009              movzx    si, byte ptr [eax + 9]         
  0x002238A6  6689712c                mov      word ptr [ecx + 0x2c], si      
  0x002238AA  6689512e                mov      word ptr [ecx + 0x2e], dx      
  0x002238AE  51                      push     ecx                            
  0x002238AF  8b08                    mov      ecx, dword ptr [eax]           
  0x002238B1  e869e2ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x002238B6  5e                      pop      esi                            
  0x002238B7  eb05                    jmp      0x2238be                       
                                        ; XREF: 0x00223867 (cond_jump), 0x0022386D (cond_jump)
  0x002238B9  e849fdffff              call     0x223607                       ; -> sub_00223607
                                        ; XREF: 0x002238B7 (jump)
  0x002238BE  c20800                  ret      8                              
                                        ; XREF: 0x00223C02 (data_imm)
  0x002238C1  56                      push     esi                            
  0x002238C2  68886d2800              push     0x286d88                       
  0x002238C7  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x002238CD  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x002238D1  33c0                    xor      eax, eax                       
  0x002238D3  c605506d280030          mov      byte ptr [0x286d50], 0x30      
  0x002238DA  c605516d280040          mov      byte ptr [0x286d51], 0x40      
  0x002238E1  c705586d2800f8362200    mov      dword ptr [0x286d58], 0x2236f8 
  0x002238EB  89355c6d2800            mov      dword ptr [0x286d5c], esi      
  0x002238F1  a3606d2800              mov      dword ptr [0x286d60], eax      
  0x002238F6  a3686d2800              mov      dword ptr [0x286d68], eax      
  0x002238FB  a3646d2800              mov      dword ptr [0x286d64], eax      
  0x00223900  a26c6d2800              mov      byte ptr [0x286d6c], al        
  0x00223905  c6056d6d280001          mov      byte ptr [0x286d6d], 1         
  0x0022390C  a26e6d2800              mov      byte ptr [0x286d6e], al        
  0x00223911  c605786d280021          mov      byte ptr [0x286d78], 0x21      
  0x00223918  c605796d28000a          mov      byte ptr [0x286d79], 0xa       
  0x0022391F  66a37a6d2800            mov      word ptr [0x286d7a], ax        
  0x00223925  660fb64e05              movzx    cx, byte ptr [esi + 5]         
  0x0022392A  66890d7c6d2800          mov      word ptr [0x286d7c], cx        
  0x00223931  66a37e6d2800            mov      word ptr [0x286d7e], ax        
  0x00223937  e8faf8ffff              call     0x223236                       ; -> sub_00223236
  0x0022393C  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022393E  68506d2800              push     0x286d50                       
  0x00223943  e8d7e1ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00223948  5e                      pop      esi                            
  0x00223949  c20800                  ret      8                              

; ============================================================
; Function: sub_0022394C
; Start: 0x0022394C  End: 0x002239D7  Size: 139 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00221B1F, sub_00223236
; Called by: sub_00223BD4
; ============================================================
sub_0022394C:
  0x0022394C  56                      push     esi                            
  0x0022394D  68886d2800              push     0x286d88                       
  0x00223952  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00223958  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0022395C  33c0                    xor      eax, eax                       
  0x0022395E  c605506d280030          mov      byte ptr [0x286d50], 0x30      
  0x00223965  c605516d280040          mov      byte ptr [0x286d51], 0x40      
  0x0022396C  c705586d280082372200    mov      dword ptr [0x286d58], 0x223782 
  0x00223976  89355c6d2800            mov      dword ptr [0x286d5c], esi      
  0x0022397C  a3606d2800              mov      dword ptr [0x286d60], eax      
  0x00223981  a3686d2800              mov      dword ptr [0x286d68], eax      
  0x00223986  a3646d2800              mov      dword ptr [0x286d64], eax      
  0x0022398B  a26c6d2800              mov      byte ptr [0x286d6c], al        
  0x00223990  c6056d6d280001          mov      byte ptr [0x286d6d], 1         
  0x00223997  a26e6d2800              mov      byte ptr [0x286d6e], al        
  0x0022399C  c605786d280021          mov      byte ptr [0x286d78], 0x21      
  0x002239A3  c605796d28000a          mov      byte ptr [0x286d79], 0xa       
  0x002239AA  66a37a6d2800            mov      word ptr [0x286d7a], ax        
  0x002239B0  660fb64e05              movzx    cx, byte ptr [esi + 5]         
  0x002239B5  66890d7c6d2800          mov      word ptr [0x286d7c], cx        
  0x002239BC  66a37e6d2800            mov      word ptr [0x286d7e], ax        
  0x002239C2  e86ff8ffff              call     0x223236                       ; -> sub_00223236
  0x002239C7  8b0e                    mov      ecx, dword ptr [esi]           
  0x002239C9  68506d2800              push     0x286d50                       
  0x002239CE  e84ce1ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x002239D3  5e                      pop      esi                            
  0x002239D4  c20800                  ret      8                              
; end of function
  0x002239D7  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x002239DB  56                      push     esi                            
  0x002239DC  e8f5ddffff              call     0x2217d6                       ; -> sub_002217D6
  0x002239E1  8bf0                    mov      esi, eax                       
  0x002239E3  8b4e12                  mov      ecx, dword ptr [esi + 0x12]    
  0x002239E6  804e0402                or       byte ptr [esi + 4], 2          
  0x002239EA  85c9                    test     ecx, ecx                       
  0x002239EC  7419                    je       0x223a07                       
  0x002239EE  8b81a3000000            mov      eax, dword ptr [ecx + 0xa3]    
  0x002239F4  8b4020                  mov      eax, dword ptr [eax + 0x20]    
  0x002239F7  85c0                    test     eax, eax                       
  0x002239F9  7402                    je       0x2239fd                       
  0x002239FB  ffd0                    call     eax                            
                                        ; XREF: 0x002239F9 (cond_jump)
  0x002239FD  8b4e12                  mov      ecx, dword ptr [esi + 0x12]    
  0x00223A00  e81afeffff              call     0x22381f                       ; -> sub_0022381F
  0x00223A05  eb07                    jmp      0x223a0e                       
                                        ; XREF: 0x002239EC (cond_jump)
  0x00223A07  8bce                    mov      ecx, esi                       
  0x00223A09  e854f8ffff              call     0x223262                       ; -> sub_00223262
                                        ; XREF: 0x00223A05 (jump)
  0x00223A0E  5e                      pop      esi                            
  0x00223A0F  c20400                  ret      4                              

; ============================================================
; Function: sub_00223A12
; Start: 0x00223A12  End: 0x00223AA6  Size: 148 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022381F
; Called by: sub_002216A9, sub_00223DA6
; ============================================================
sub_00223A12:
  0x00223A12  55                      push     ebp                            
  0x00223A13  8bec                    mov      ebp, esp                       
  0x00223A15  83ec14                  sub      esp, 0x14                      
  0x00223A18  53                      push     ebx                            
  0x00223A19  56                      push     esi                            
  0x00223A1A  8bf1                    mov      esi, ecx                       
  0x00223A1C  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00223A22  8845ff                  mov      byte ptr [ebp - 1], al         
  0x00223A25  8b86a3000000            mov      eax, dword ptr [esi + 0xa3]    
  0x00223A2B  8b401c                  mov      eax, dword ptr [eax + 0x1c]    
  0x00223A2E  33db                    xor      ebx, ebx                       
  0x00223A30  3bc3                    cmp      eax, ebx                       
  0x00223A32  7404                    je       0x223a38                       
  0x00223A34  8bce                    mov      ecx, esi                       
  0x00223A36  ffd0                    call     eax                            
                                        ; XREF: 0x00223A32 (cond_jump)
  0x00223A38  391e                    cmp      dword ptr [esi], ebx           
  0x00223A3A  7443                    je       0x223a7f                       
  0x00223A3C  808ea200000001          or       byte ptr [esi + 0xa2], 1       
  0x00223A43  8d45f4                  lea      eax, [ebp - 0xc]               
  0x00223A46  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x00223A49  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x00223A4C  8d45ec                  lea      eax, [ebp - 0x14]              
  0x00223A4F  8bce                    mov      ecx, esi                       
  0x00223A51  885dec                  mov      byte ptr [ebp - 0x14], bl      
  0x00223A54  c645ee04                mov      byte ptr [ebp - 0x12], 4       
  0x00223A58  895df0                  mov      dword ptr [ebp - 0x10], ebx    
  0x00223A5B  89869e000000            mov      dword ptr [esi + 0x9e], eax    
  0x00223A61  e8b9fdffff              call     0x22381f                       ; -> sub_0022381F
  0x00223A66  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x00223A69  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00223A6F  53                      push     ebx                            
  0x00223A70  53                      push     ebx                            
  0x00223A71  53                      push     ebx                            
  0x00223A72  53                      push     ebx                            
  0x00223A73  8d45ec                  lea      eax, [ebp - 0x14]              
  0x00223A76  50                      push     eax                            
  0x00223A77  ff15485b2200            call     dword ptr [0x225b48]           ; -> xbox_KeWaitForSingleObject
  0x00223A7D  eb09                    jmp      0x223a88                       
                                        ; XREF: 0x00223A3A (cond_jump)
  0x00223A7F  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x00223A82  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
                                        ; XREF: 0x00223A7D (jump)
  0x00223A88  8b86a3000000            mov      eax, dword ptr [esi + 0xa3]    
  0x00223A8E  fe4001                  inc      byte ptr [eax + 1]             
  0x00223A91  a1386d2800              mov      eax, dword ptr [0x286d38]      
  0x00223A96  8986a7000000            mov      dword ptr [esi + 0xa7], eax    
  0x00223A9C  8935386d2800            mov      dword ptr [0x286d38], esi      
  0x00223AA2  5e                      pop      esi                            
  0x00223AA3  5b                      pop      ebx                            
  0x00223AA4  c9                      leave                                   
  0x00223AA5  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00223AA6
; Start: 0x00223AA6  End: 0x00223BD4  Size: 302 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002217F5, sub_00221B1F
; Called by: sub_00221728
; ============================================================
sub_00223AA6:
  0x00223AA6  55                      push     ebp                            
  0x00223AA7  8bec                    mov      ebp, esp                       
  0x00223AA9  51                      push     ecx                            
  0x00223AAA  51                      push     ecx                            
  0x00223AAB  53                      push     ebx                            
  0x00223AAC  56                      push     esi                            
  0x00223AAD  57                      push     edi                            
  0x00223AAE  8b39                    mov      edi, dword ptr [ecx]           
  0x00223AB0  8bf2                    mov      esi, edx                       
  0x00223AB2  894df8                  mov      dword ptr [ebp - 8], ecx       
  0x00223AB5  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00223ABB  33db                    xor      ebx, ebx                       
  0x00223ABD  3bfb                    cmp      edi, ebx                       
  0x00223ABF  8845fe                  mov      byte ptr [ebp - 2], al         
  0x00223AC2  0f84f6000000            je       0x223bbe                       
  0x00223AC8  f6470402                test     byte ptr [edi + 4], 2          
  0x00223ACC  0f85ec000000            jne      0x223bbe                       
  0x00223AD2  385f0d                  cmp      byte ptr [edi + 0xd], bl       
  0x00223AD5  750b                    jne      0x223ae2                       
  0x00223AD7  c70632000000            mov      dword ptr [esi], 0x32          
  0x00223ADD  e9e2000000              jmp      0x223bc4                       
                                        ; XREF: 0x00223AD5 (cond_jump)
  0x00223AE2  8b4604                  mov      eax, dword ptr [esi + 4]       
  0x00223AE5  3bc3                    cmp      eax, ebx                       
  0x00223AE7  7418                    je       0x223b01                       
  0x00223AE9  8d4e0c                  lea      ecx, [esi + 0xc]               
  0x00223AEC  51                      push     ecx                            
  0x00223AED  ff35e45a2200            push     dword ptr [0x225ae4]           
  0x00223AF3  50                      push     eax                            
  0x00223AF4  ff15485a2200            call     dword ptr [0x225a48]           ; -> xbox_ObReferenceObjectByHandle
  0x00223AFA  85c0                    test     eax, eax                       
  0x00223AFC  7d06                    jge      0x223b04                       
  0x00223AFE  895e04                  mov      dword ptr [esi + 4], ebx       
                                        ; XREF: 0x00223AE7 (cond_jump)
  0x00223B01  895e0c                  mov      dword ptr [esi + 0xc], ebx     
                                        ; XREF: 0x00223AFC (cond_jump)
  0x00223B04  8d4e40                  lea      ecx, [esi + 0x40]              
  0x00223B07  8a01                    mov      al, byte ptr [ecx]             
  0x00223B09  3ac3                    cmp      al, bl                         
  0x00223B0B  8845ff                  mov      byte ptr [ebp - 1], al         
  0x00223B0E  750b                    jne      0x223b1b                       
  0x00223B10  8a470d                  mov      al, byte ptr [edi + 0xd]       
  0x00223B13  3a4641                  cmp      al, byte ptr [esi + 0x41]      
  0x00223B16  7303                    jae      0x223b1b                       
  0x00223B18  884641                  mov      byte ptr [esi + 0x41], al      
                                        ; XREF: 0x00223B0E (cond_jump), 0x00223B16 (cond_jump)
  0x00223B1B  8b470e                  mov      eax, dword ptr [edi + 0xe]     
  0x00223B1E  f6402802                test     byte ptr [eax + 0x28], 2       
  0x00223B22  7403                    je       0x223b27                       
  0x00223B24  8d4e42                  lea      ecx, [esi + 0x42]              
                                        ; XREF: 0x00223B22 (cond_jump)
  0x00223B27  8b55f8                  mov      edx, dword ptr [ebp - 8]       
  0x00223B2A  395a10                  cmp      dword ptr [edx + 0x10], ebx    
  0x00223B2D  8d4610                  lea      eax, [esi + 0x10]              
  0x00223B30  89761c                  mov      dword ptr [esi + 0x1c], esi    
  0x00223B33  c746183d382200          mov      dword ptr [esi + 0x18], 0x22383d 
  0x00223B3A  7423                    je       0x223b5f                       
  0x00223B3C  c60028                  mov      byte ptr [eax], 0x28           
  0x00223B3F  c6461141                mov      byte ptr [esi + 0x11], 0x41    
  0x00223B43  8b5210                  mov      edx, dword ptr [edx + 0x10]    
  0x00223B46  894e28                  mov      dword ptr [esi + 0x28], ecx    
  0x00223B49  0fb64e41                movzx    ecx, byte ptr [esi + 0x41]     
  0x00223B4D  895620                  mov      dword ptr [esi + 0x20], edx    
  0x00223B50  894e24                  mov      dword ptr [esi + 0x24], ecx    
  0x00223B53  c6462c01                mov      byte ptr [esi + 0x2c], 1       
  0x00223B57  885e2d                  mov      byte ptr [esi + 0x2d], bl      
  0x00223B5A  885e2e                  mov      byte ptr [esi + 0x2e], bl      
  0x00223B5D  eb47                    jmp      0x223ba6                       
                                        ; XREF: 0x00223B3A (cond_jump)
  0x00223B5F  894e28                  mov      dword ptr [esi + 0x28], ecx    
  0x00223B62  8a4e41                  mov      cl, byte ptr [esi + 0x41]      
  0x00223B65  0fb6d1                  movzx    edx, cl                        
  0x00223B68  895624                  mov      dword ptr [esi + 0x24], edx    
  0x00223B6B  660fb655ff              movzx    dx, byte ptr [ebp - 1]         
  0x00223B70  6681ca0002              or       dx, 0x200                      
  0x00223B75  c60030                  mov      byte ptr [eax], 0x30           
  0x00223B78  c6461140                mov      byte ptr [esi + 0x11], 0x40    
  0x00223B7C  895e20                  mov      dword ptr [esi + 0x20], ebx    
  0x00223B7F  c6462c01                mov      byte ptr [esi + 0x2c], 1       
  0x00223B83  885e2d                  mov      byte ptr [esi + 0x2d], bl      
  0x00223B86  885e2e                  mov      byte ptr [esi + 0x2e], bl      
  0x00223B89  c6463821                mov      byte ptr [esi + 0x38], 0x21    
  0x00223B8D  c6463909                mov      byte ptr [esi + 0x39], 9       
  0x00223B91  6689563a                mov      word ptr [esi + 0x3a], dx      
  0x00223B95  660fb65705              movzx    dx, byte ptr [edi + 5]         
  0x00223B9A  660fb6c9                movzx    cx, cl                         
  0x00223B9E  6689563c                mov      word ptr [esi + 0x3c], dx      
  0x00223BA2  66894e3e                mov      word ptr [esi + 0x3e], cx      
                                        ; XREF: 0x00223B5D (jump)
  0x00223BA6  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x00223BA9  894e08                  mov      dword ptr [esi + 8], ecx       
  0x00223BAC  8b0f                    mov      ecx, dword ptr [edi]           
  0x00223BAE  50                      push     eax                            
  0x00223BAF  e86bdfffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00223BB4  50                      push     eax                            
  0x00223BB5  e83bdcffff              call     0x2217f5                       ; -> sub_002217F5
  0x00223BBA  8906                    mov      dword ptr [esi], eax           
  0x00223BBC  eb06                    jmp      0x223bc4                       
                                        ; XREF: 0x00223AC2 (cond_jump), 0x00223ACC (cond_jump)
  0x00223BBE  c7068f040000            mov      dword ptr [esi], 0x48f         
                                        ; XREF: 0x00223ADD (jump), 0x00223BBC (jump)
  0x00223BC4  8a4dfe                  mov      cl, byte ptr [ebp - 2]         
  0x00223BC7  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00223BCD  8b06                    mov      eax, dword ptr [esi]           
  0x00223BCF  5f                      pop      edi                            
  0x00223BD0  5e                      pop      esi                            
  0x00223BD1  5b                      pop      ebx                            
  0x00223BD2  c9                      leave                                   
  0x00223BD3  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00223BD4
; Start: 0x00223BD4  End: 0x00223CB2  Size: 222 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00220E01, sub_002217DA, sub_00221863, sub_00221B1F, sub_00223236, sub_0022394C
; ============================================================
sub_00223BD4:
  0x00223BD4  56                      push     esi                            
  0x00223BD5  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00223BD9  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223BDB  e883dcffff              call     0x221863                       ; -> sub_00221863
  0x00223BE0  8a4805                  mov      cl, byte ptr [eax + 5]         
  0x00223BE3  80f903                  cmp      cl, 3                          
  0x00223BE6  0f859b000000            jne      0x223c87                       
  0x00223BEC  80780701                cmp      byte ptr [eax + 7], 1          
  0x00223BF0  7579                    jne      0x223c6b                       
  0x00223BF2  33c0                    xor      eax, eax                       
  0x00223BF4  c605506d280030          mov      byte ptr [0x286d50], 0x30      
  0x00223BFB  c605516d280040          mov      byte ptr [0x286d51], 0x40      
  0x00223C02  c705586d2800c1382200    mov      dword ptr [0x286d58], 0x2238c1 
  0x00223C0C  89355c6d2800            mov      dword ptr [0x286d5c], esi      
  0x00223C12  a3606d2800              mov      dword ptr [0x286d60], eax      
  0x00223C17  a3686d2800              mov      dword ptr [0x286d68], eax      
  0x00223C1C  a3646d2800              mov      dword ptr [0x286d64], eax      
  0x00223C21  a26c6d2800              mov      byte ptr [0x286d6c], al        
  0x00223C26  c6056d6d280001          mov      byte ptr [0x286d6d], 1         
  0x00223C2D  a26e6d2800              mov      byte ptr [0x286d6e], al        
  0x00223C32  c605786d280021          mov      byte ptr [0x286d78], 0x21      
  0x00223C39  c605796d28000b          mov      byte ptr [0x286d79], 0xb       
  0x00223C40  66a37a6d2800            mov      word ptr [0x286d7a], ax        
  0x00223C46  660fb64e05              movzx    cx, byte ptr [esi + 5]         
  0x00223C4B  66890d7c6d2800          mov      word ptr [0x286d7c], cx        
  0x00223C52  66a37e6d2800            mov      word ptr [0x286d7e], ax        
  0x00223C58  e8d9f5ffff              call     0x223236                       ; -> sub_00223236
  0x00223C5D  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223C5F  68506d2800              push     0x286d50                       
  0x00223C64  e8b6deffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00223C69  eb43                    jmp      0x223cae                       
                                        ; XREF: 0x00223BF0 (cond_jump)
  0x00223C6B  80f903                  cmp      cl, 3                          
  0x00223C6E  7517                    jne      0x223c87                       
  0x00223C70  80780702                cmp      byte ptr [eax + 7], 2          
  0x00223C74  7511                    jne      0x223c87                       
  0x00223C76  e8bbf5ffff              call     0x223236                       ; -> sub_00223236
  0x00223C7B  56                      push     esi                            
  0x00223C7C  ff74240c                push     dword ptr [esp + 0xc]          
  0x00223C80  e8c7fcffff              call     0x22394c                       ; -> sub_0022394C
  0x00223C85  eb27                    jmp      0x223cae                       
                                        ; XREF: 0x00223BE6 (cond_jump), 0x00223C6E (cond_jump), 0x00223C74 (cond_jump)
  0x00223C87  806604fe                and      byte ptr [esi + 4], 0xfe       
  0x00223C8B  57                      push     edi                            
  0x00223C8C  8b3e                    mov      edi, dword ptr [esi]           
  0x00223C8E  33c0                    xor      eax, eax                       
  0x00223C90  8906                    mov      dword ptr [esi], eax           
  0x00223C92  66ff0d326d2800          dec      word ptr [0x286d32]            
  0x00223C99  50                      push     eax                            
  0x00223C9A  8bcf                    mov      ecx, edi                       
  0x00223C9C  e839dbffff              call     0x2217da                       ; -> sub_002217DA
  0x00223CA1  6800040080              push     0x80000400                     
  0x00223CA6  8bcf                    mov      ecx, edi                       
  0x00223CA8  e854d1ffff              call     0x220e01                       ; -> sub_00220E01
  0x00223CAD  5f                      pop      edi                            
                                        ; XREF: 0x00223C69 (jump), 0x00223C85 (jump)
  0x00223CAE  5e                      pop      esi                            
  0x00223CAF  c20800                  ret      8                              
; end of function
                                        ; XREF: 0x002240B1 (data_imm)
  0x00223CB2  53                      push     ebx                            
  0x00223CB3  56                      push     esi                            
  0x00223CB4  57                      push     edi                            
  0x00223CB5  68886d2800              push     0x286d88                       
  0x00223CBA  ff15585b2200            call     dword ptr [0x225b58]           ; -> xbox_KeCancelTimer
  0x00223CC0  8b442410                mov      eax, dword ptr [esp + 0x10]    
  0x00223CC4  33db                    xor      ebx, ebx                       
  0x00223CC6  395804                  cmp      dword ptr [eax + 4], ebx       
  0x00223CC9  0f8cc7000000            jl       0x223d96                       
  0x00223CCF  83781408                cmp      dword ptr [eax + 0x14], 8      
  0x00223CD3  0f82bd000000            jb       0x223d96                       
  0x00223CD9  803d3c6d280008          cmp      byte ptr [0x286d3c], 8         
  0x00223CE0  0f82b0000000            jb       0x223d96                       
  0x00223CE6  803d3d6d280042          cmp      byte ptr [0x286d3d], 0x42      
  0x00223CED  0f85a3000000            jne      0x223d96                       
  0x00223CF3  66391d3e6d2800          cmp      word ptr [0x286d3e], bx        
  0x00223CFA  0f8496000000            je       0x223d96                       
  0x00223D00  8b742414                mov      esi, dword ptr [esp + 0x14]    
  0x00223D04  8a0d406d2800            mov      cl, byte ptr [0x286d40]        
  0x00223D0A  8d7e0a                  lea      edi, [esi + 0xa]               
  0x00223D0D  8bd7                    mov      edx, edi                       
  0x00223D0F  e8ddd8ffff              call     0x2215f1                       ; -> sub_002215F1
  0x00223D14  3bc3                    cmp      eax, ebx                       
  0x00223D16  89460e                  mov      dword ptr [esi + 0xe], eax     
  0x00223D19  8a0d416d2800            mov      cl, byte ptr [0x286d41]        
  0x00223D1F  884e0b                  mov      byte ptr [esi + 0xb], cl       
  0x00223D22  8a0d426d2800            mov      cl, byte ptr [0x286d42]        
  0x00223D28  884e0c                  mov      byte ptr [esi + 0xc], cl       
  0x00223D2B  8a0d436d2800            mov      cl, byte ptr [0x286d43]        
  0x00223D31  884e0d                  mov      byte ptr [esi + 0xd], cl       
  0x00223D34  743b                    je       0x223d71                       
  0x00223D36  a0426d2800              mov      al, byte ptr [0x286d42]        
  0x00223D3B  3c02                    cmp      al, 2                          
  0x00223D3D  7232                    jb       0x223d71                       
  0x00223D3F  3c20                    cmp      al, 0x20                       
  0x00223D41  772e                    ja       0x223d71                       
  0x00223D43  8a460c                  mov      al, byte ptr [esi + 0xc]       
  0x00223D46  3a4606                  cmp      al, byte ptr [esi + 6]         
  0x00223D49  7726                    ja       0x223d71                       
  0x00223D4B  385e09                  cmp      byte ptr [esi + 9], bl         
  0x00223D4E  7407                    je       0x223d57                       
  0x00223D50  8ac1                    mov      al, cl                         
  0x00223D52  3a4607                  cmp      al, byte ptr [esi + 7]         
  0x00223D55  771a                    ja       0x223d71                       
                                        ; XREF: 0x00223D4E (cond_jump)
  0x00223D57  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223D59  33c0                    xor      eax, eax                       
  0x00223D5B  8a07                    mov      al, byte ptr [edi]             
  0x00223D5D  50                      push     eax                            
  0x00223D5E  e888daffff              call     0x2217eb                       ; -> sub_002217EB
  0x00223D63  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223D65  53                      push     ebx                            
  0x00223D66  e896d0ffff              call     0x220e01                       ; -> sub_00220E01
  0x00223D6B  804e0408                or       byte ptr [esi + 4], 8          
  0x00223D6F  eb2f                    jmp      0x223da0                       
                                        ; XREF: 0x00223D34 (cond_jump), 0x00223D3D (cond_jump), 0x00223D41 (cond_jump), 0x00223D49 (cond_jump), 0x00223D55 (cond_jump)
  0x00223D71  8b3e                    mov      edi, dword ptr [esi]           
  0x00223D73  806604fe                and      byte ptr [esi + 4], 0xfe       
  0x00223D77  891e                    mov      dword ptr [esi], ebx           
  0x00223D79  66ff0d326d2800          dec      word ptr [0x286d32]            
  0x00223D80  53                      push     ebx                            
  0x00223D81  8bcf                    mov      ecx, edi                       
  0x00223D83  e852daffff              call     0x2217da                       ; -> sub_002217DA
  0x00223D88  6800040080              push     0x80000400                     
  0x00223D8D  8bcf                    mov      ecx, edi                       
  0x00223D8F  e86dd0ffff              call     0x220e01                       ; -> sub_00220E01
  0x00223D94  eb0a                    jmp      0x223da0                       
                                        ; XREF: 0x00223CC9 (cond_jump), 0x00223CD3 (cond_jump), 0x00223CE0 (cond_jump), 0x00223CED (cond_jump), 0x00223CFA (cond_jump)
  0x00223D96  ff742414                push     dword ptr [esp + 0x14]         
  0x00223D9A  50                      push     eax                            
  0x00223D9B  e834feffff              call     0x223bd4                       ; -> sub_00223BD4
                                        ; XREF: 0x00223D6F (jump), 0x00223D94 (jump)
  0x00223DA0  5f                      pop      edi                            
  0x00223DA1  5e                      pop      esi                            
  0x00223DA2  5b                      pop      ebx                            
  0x00223DA3  c20800                  ret      8                              

; ============================================================
; Function: sub_00223DA6
; Start: 0x00223DA6  End: 0x00223FF6  Size: 592 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002217F5, sub_00221B1F, sub_00223285, sub_002232EF, sub_002236AB, sub_00223A12
; Called by: sub_00221653
; ============================================================
sub_00223DA6:
  0x00223DA6  55                      push     ebp                            
  0x00223DA7  8bec                    mov      ebp, esp                       
  0x00223DA9  83ec28                  sub      esp, 0x28                      
  0x00223DAC  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x00223DAF  53                      push     ebx                            
  0x00223DB0  56                      push     esi                            
  0x00223DB1  33db                    xor      ebx, ebx                       
  0x00223DB3  8bf1                    mov      esi, ecx                       
  0x00223DB5  57                      push     edi                            
  0x00223DB6  8bfa                    mov      edi, edx                       
  0x00223DB8  8975f0                  mov      dword ptr [ebp - 0x10], esi    
  0x00223DBB  895df8                  mov      dword ptr [ebp - 8], ebx       
  0x00223DBE  895df4                  mov      dword ptr [ebp - 0xc], ebx     
  0x00223DC1  8918                    mov      dword ptr [eax], ebx           
  0x00223DC3  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00223DC9  8bd7                    mov      edx, edi                       
  0x00223DCB  8bce                    mov      ecx, esi                       
  0x00223DCD  8845ff                  mov      byte ptr [ebp - 1], al         
  0x00223DD0  e8b0f4ffff              call     0x223285                       ; -> sub_00223285
  0x00223DD5  8bd0                    mov      edx, eax                       
  0x00223DD7  3bd3                    cmp      edx, ebx                       
  0x00223DD9  8955ec                  mov      dword ptr [ebp - 0x14], edx    
  0x00223DDC  750c                    jne      0x223dea                       
                                        ; XREF: 0x00223F5B (cond_jump), 0x00223F65 (cond_jump)
  0x00223DDE  c745f88f040000          mov      dword ptr [ebp - 8], 0x48f     
  0x00223DE5  e9eb010000              jmp      0x223fd5                       
                                        ; XREF: 0x00223DDC (cond_jump)
  0x00223DEA  395a12                  cmp      dword ptr [edx + 0x12], ebx    
  0x00223DED  740c                    je       0x223dfb                       
  0x00223DEF  c745f820000000          mov      dword ptr [ebp - 8], 0x20      
  0x00223DF6  e9da010000              jmp      0x223fd5                       
                                        ; XREF: 0x00223DED (cond_jump)
  0x00223DFB  8a4601                  mov      al, byte ptr [esi + 1]         
  0x00223DFE  84c0                    test     al, al                         
  0x00223E00  750c                    jne      0x223e0e                       
  0x00223E02  c745f80e000000          mov      dword ptr [ebp - 8], 0xe       
  0x00223E09  e9c7010000              jmp      0x223fd5                       
                                        ; XREF: 0x00223E00 (cond_jump)
  0x00223E0E  fec8                    dec      al                             
  0x00223E10  884601                  mov      byte ptr [esi + 1], al         
  0x00223E13  8b1d386d2800            mov      ebx, dword ptr [0x286d38]      
  0x00223E19  8b83a7000000            mov      eax, dword ptr [ebx + 0xa7]    
  0x00223E1F  a3386d2800              mov      dword ptr [0x286d38], eax      
  0x00223E24  33c0                    xor      eax, eax                       
  0x00223E26  6a2a                    push     0x2a                           
  0x00223E28  59                      pop      ecx                            
  0x00223E29  8bfb                    mov      edi, ebx                       
  0x00223E2B  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x00223E2D  66ab                    stosw    word ptr es:[edi], ax          
  0x00223E2F  aa                      stosb    byte ptr es:[edi], al          
  0x00223E30  8b7d0c                  mov      edi, dword ptr [ebp + 0xc]     
  0x00223E33  8a8ba2000000            mov      cl, byte ptr [ebx + 0xa2]      
  0x00223E39  8913                    mov      dword ptr [ebx], edx           
  0x00223E3B  89b3a3000000            mov      dword ptr [ebx + 0xa3], esi    
  0x00223E41  8a07                    mov      al, byte ptr [edi]             
  0x00223E43  2401                    and      al, 1                          
  0x00223E45  80e1e7                  and      cl, 0xe7                       
  0x00223E48  c0e003                  shl      al, 3                          
  0x00223E4B  0ac1                    or       al, cl                         
  0x00223E4D  8883a2000000            mov      byte ptr [ebx + 0xa2], al      
  0x00223E53  895a12                  mov      dword ptr [edx + 0x12], ebx    
  0x00223E56  8bd7                    mov      edx, edi                       
  0x00223E58  8bcb                    mov      ecx, ebx                       
  0x00223E5A  895de8                  mov      dword ptr [ebp - 0x18], ebx    
  0x00223E5D  c745f401000000          mov      dword ptr [ebp - 0xc], 1       
  0x00223E64  e886f4ffff              call     0x2232ef                       ; -> sub_002232EF
  0x00223E69  85c0                    test     eax, eax                       
  0x00223E6B  0f8c5b010000            jl       0x223fcc                       
  0x00223E71  8b5618                  mov      edx, dword ptr [esi + 0x18]    
  0x00223E74  85d2                    test     edx, edx                       
  0x00223E76  7412                    je       0x223e8a                       
  0x00223E78  8bcb                    mov      ecx, ebx                       
  0x00223E7A  ffd2                    call     edx                            
  0x00223E7C  f7d8                    neg      eax                            
  0x00223E7E  1bc0                    sbb      eax, eax                       
  0x00223E80  2500ffff7f              and      eax, 0x7fffff00                
  0x00223E85  0500010080              add      eax, 0x80000100                
                                        ; XREF: 0x00223E76 (cond_jump)
  0x00223E8A  85c0                    test     eax, eax                       
  0x00223E8C  0f8c3a010000            jl       0x223fcc                       
  0x00223E92  8b7608                  mov      esi, dword ptr [esi + 8]       
  0x00223E95  0fb60e                  movzx    ecx, byte ptr [esi]            
  0x00223E98  8b7601                  mov      esi, dword ptr [esi + 1]       
  0x00223E9B  8bd1                    mov      edx, ecx                       
  0x00223E9D  c1e902                  shr      ecx, 2                         
  0x00223EA0  8d4334                  lea      eax, [ebx + 0x34]              
  0x00223EA3  8bf8                    mov      edi, eax                       
  0x00223EA5  f3a5                    rep movsd dword ptr es:[edi], dword ptr [esi] 
  0x00223EA7  8bca                    mov      ecx, edx                       
  0x00223EA9  83e103                  and      ecx, 3                         
  0x00223EAC  f3a4                    rep movsb byte ptr es:[edi], byte ptr [esi] 
  0x00223EAE  6a07                    push     7                              
  0x00223EB0  8bf0                    mov      esi, eax                       
  0x00223EB2  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x00223EB5  8d7b14                  lea      edi, [ebx + 0x14]              
  0x00223EB8  59                      pop      ecx                            
  0x00223EB9  f3a5                    rep movsd dword ptr es:[edi], dword ptr [esi] 
  0x00223EBB  66a5                    movsw    word ptr es:[edi], word ptr [esi] 
  0x00223EBD  f6402840                test     byte ptr [eax + 0x28], 0x40    
  0x00223EC1  8b75ec                  mov      esi, dword ptr [ebp - 0x14]    
  0x00223EC4  0f85af000000            jne      0x223f79                       
  0x00223ECA  8365dc00                and      dword ptr [ebp - 0x24], 0      
  0x00223ECE  8d45e0                  lea      eax, [ebp - 0x20]              
  0x00223ED1  8945e4                  mov      dword ptr [ebp - 0x1c], eax    
  0x00223ED4  8945e0                  mov      dword ptr [ebp - 0x20], eax    
  0x00223ED7  0fb6460c                movzx    eax, byte ptr [esi + 0xc]      
  0x00223EDB  83636200                and      dword ptr [ebx + 0x62], 0      
  0x00223EDF  8d4dd8                  lea      ecx, [ebp - 0x28]              
  0x00223EE2  894b5e                  mov      dword ptr [ebx + 0x5e], ecx    
  0x00223EE5  8d4b32                  lea      ecx, [ebx + 0x32]              
  0x00223EE8  8d7b52                  lea      edi, [ebx + 0x52]              
  0x00223EEB  c60730                  mov      byte ptr [edi], 0x30           
  0x00223EEE  c6435340                mov      byte ptr [ebx + 0x53], 0x40    
  0x00223EF2  c7435a9a362200          mov      dword ptr [ebx + 0x5a], 0x22369a 
  0x00223EF9  894b6a                  mov      dword ptr [ebx + 0x6a], ecx    
  0x00223EFC  894366                  mov      dword ptr [ebx + 0x66], eax    
  0x00223EFF  c6436e02                mov      byte ptr [ebx + 0x6e], 2       
  0x00223F03  c6436f01                mov      byte ptr [ebx + 0x6f], 1       
  0x00223F07  c6437000                mov      byte ptr [ebx + 0x70], 0       
  0x00223F0B  c6437aa1                mov      byte ptr [ebx + 0x7a], 0xa1    
  0x00223F0F  c6437b01                mov      byte ptr [ebx + 0x7b], 1       
  0x00223F13  66c7437c0001            mov      word ptr [ebx + 0x7c], 0x100   
  0x00223F19  660fb64e05              movzx    cx, byte ptr [esi + 5]         
  0x00223F1E  66894b7e                mov      word ptr [ebx + 0x7e], cx      
  0x00223F22  66898380000000          mov      word ptr [ebx + 0x80], ax      
  0x00223F29  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223F2B  57                      push     edi                            
  0x00223F2C  c645d801                mov      byte ptr [ebp - 0x28], 1       
  0x00223F30  c645da04                mov      byte ptr [ebp - 0x26], 4       
  0x00223F34  e8e6dbffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00223F39  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x00223F3C  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00223F42  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223F44  8d45d8                  lea      eax, [ebp - 0x28]              
  0x00223F47  50                      push     eax                            
  0x00223F48  8bd7                    mov      edx, edi                       
  0x00223F4A  e85cf7ffff              call     0x2236ab                       ; -> sub_002236AB
  0x00223F4F  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00223F55  833b00                  cmp      dword ptr [ebx], 0             
  0x00223F58  8845ff                  mov      byte ptr [ebp - 1], al         
  0x00223F5B  0f847dfeffff            je       0x223dde                       
  0x00223F61  f6460402                test     byte ptr [esi + 4], 2          
  0x00223F65  0f8573feffff            jne      0x223dde                       
  0x00223F6B  837b5600                cmp      dword ptr [ebx + 0x56], 0      
  0x00223F6F  7c08                    jl       0x223f79                       
  0x00223F71  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x00223F74  8bcb                    mov      ecx, ebx                       
  0x00223F76  ff5024                  call     dword ptr [eax + 0x24]         
                                        ; XREF: 0x00223EC4 (cond_jump), 0x00223F6F (cond_jump)
  0x00223F79  8b4b0c                  mov      ecx, dword ptr [ebx + 0xc]     
  0x00223F7C  894b62                  mov      dword ptr [ebx + 0x62], ecx    
  0x00223F7F  8d4b32                  lea      ecx, [ebx + 0x32]              
  0x00223F82  8d4352                  lea      eax, [ebx + 0x52]              
  0x00223F85  c60028                  mov      byte ptr [eax], 0x28           
  0x00223F88  c6435341                mov      byte ptr [ebx + 0x53], 0x41    
  0x00223F8C  c7435a4b342200          mov      dword ptr [ebx + 0x5a], 0x22344b 
  0x00223F93  895b5e                  mov      dword ptr [ebx + 0x5e], ebx    
  0x00223F96  894b6a                  mov      dword ptr [ebx + 0x6a], ecx    
  0x00223F99  0fb64e0c                movzx    ecx, byte ptr [esi + 0xc]      
  0x00223F9D  894b66                  mov      dword ptr [ebx + 0x66], ecx    
  0x00223FA0  c6436e02                mov      byte ptr [ebx + 0x6e], 2       
  0x00223FA4  c6436f01                mov      byte ptr [ebx + 0x6f], 1       
  0x00223FA8  c6437000                mov      byte ptr [ebx + 0x70], 0       
  0x00223FAC  8066040f                and      byte ptr [esi + 4], 0xf        
  0x00223FB0  f683a200000008          test     byte ptr [ebx + 0xa2], 8       
  0x00223FB7  7408                    je       0x223fc1                       
  0x00223FB9  8b0e                    mov      ecx, dword ptr [esi]           
  0x00223FBB  50                      push     eax                            
  0x00223FBC  e85edbffff              call     0x221b1f                       ; -> sub_00221B1F
                                        ; XREF: 0x00223FB7 (cond_jump)
  0x00223FC1  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x00223FC4  8365f400                and      dword ptr [ebp - 0xc], 0       
  0x00223FC8  8918                    mov      dword ptr [eax], ebx           
  0x00223FCA  eb09                    jmp      0x223fd5                       
                                        ; XREF: 0x00223E6B (cond_jump), 0x00223E8C (cond_jump)
  0x00223FCC  50                      push     eax                            
  0x00223FCD  e823d8ffff              call     0x2217f5                       ; -> sub_002217F5
  0x00223FD2  8945f8                  mov      dword ptr [ebp - 8], eax       
                                        ; XREF: 0x00223DE5 (jump), 0x00223DF6 (jump), 0x00223E09 (jump), 0x00223FCA (jump)
  0x00223FD5  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x00223FD8  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00223FDE  837df400                cmp      dword ptr [ebp - 0xc], 0       
  0x00223FE2  5f                      pop      edi                            
  0x00223FE3  5e                      pop      esi                            
  0x00223FE4  5b                      pop      ebx                            
  0x00223FE5  7408                    je       0x223fef                       
  0x00223FE7  8b4de8                  mov      ecx, dword ptr [ebp - 0x18]    
  0x00223FEA  e823faffff              call     0x223a12                       ; -> sub_00223A12
                                        ; XREF: 0x00223FE5 (cond_jump)
  0x00223FEF  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00223FF2  c9                      leave                                   
  0x00223FF3  c20800                  ret      8                              
; end of function
  0x00223FF6  66a1326d2800            mov      ax, word ptr [0x286d32]        
  0x00223FFC  53                      push     ebx                            
  0x00223FFD  33db                    xor      ebx, ebx                       
  0x00223FFF  32c9                    xor      cl, cl                         
  0x00224001  663b05306d2800          cmp      ax, word ptr [0x286d30]        
  0x00224008  0f832a010000            jae      0x224138                       
  0x0022400E  a1346d2800              mov      eax, dword ptr [0x286d34]      
  0x00224013  f6400401                test     byte ptr [eax + 4], 1          
  0x00224017  740f                    je       0x224028                       
                                        ; XREF: 0x00224026 (cond_jump)
  0x00224019  fec1                    inc      cl                             
  0x0022401B  0fb6d1                  movzx    edx, cl                        
  0x0022401E  6bd216                  imul     edx, edx, 0x16                 
  0x00224021  f644020401              test     byte ptr [edx + eax + 4], 1    
  0x00224026  75f1                    jne      0x224019                       
                                        ; XREF: 0x00224017 (cond_jump)
  0x00224028  66ff05326d2800          inc      word ptr [0x286d32]            
  0x0022402F  56                      push     esi                            
  0x00224030  0fb6f1                  movzx    esi, cl                        
  0x00224033  6bf616                  imul     esi, esi, 0x16                 
  0x00224036  57                      push     edi                            
  0x00224037  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x0022403B  03f0                    add      esi, eax                       
  0x0022403D  880d806d2800            mov      byte ptr [0x286d80], cl        
  0x00224043  56                      push     esi                            
  0x00224044  8bcf                    mov      ecx, edi                       
  0x00224046  e88fd7ffff              call     0x2217da                       ; -> sub_002217DA
  0x0022404B  8a4604                  mov      al, byte ptr [esi + 4]         
  0x0022404E  24f1                    and      al, 0xf1                       
  0x00224050  0c01                    or       al, 1                          
  0x00224052  8bcf                    mov      ecx, edi                       
  0x00224054  893e                    mov      dword ptr [esi], edi           
  0x00224056  884604                  mov      byte ptr [esi + 4], al         
  0x00224059  e889d7ffff              call     0x2217e7                       ; -> sub_002217E7
  0x0022405E  53                      push     ebx                            
  0x0022405F  6a01                    push     1                              
  0x00224061  6a03                    push     3                              
  0x00224063  8bcf                    mov      ecx, edi                       
  0x00224065  884605                  mov      byte ptr [esi + 5], al         
  0x00224068  895e12                  mov      dword ptr [esi + 0x12], ebx    
  0x0022406B  e8f9d7ffff              call     0x221869                       ; -> sub_00221869
  0x00224070  8a4802                  mov      cl, byte ptr [eax + 2]         
  0x00224073  53                      push     ebx                            
  0x00224074  884e08                  mov      byte ptr [esi + 8], cl         
  0x00224077  8a4004                  mov      al, byte ptr [eax + 4]         
  0x0022407A  53                      push     ebx                            
  0x0022407B  6a03                    push     3                              
  0x0022407D  8bcf                    mov      ecx, edi                       
  0x0022407F  884606                  mov      byte ptr [esi + 6], al         
  0x00224082  e8e2d7ffff              call     0x221869                       ; -> sub_00221869
  0x00224087  3bc3                    cmp      eax, ebx                       
  0x00224089  740e                    je       0x224099                       
  0x0022408B  8a4802                  mov      cl, byte ptr [eax + 2]         
  0x0022408E  884e09                  mov      byte ptr [esi + 9], cl         
  0x00224091  8a4004                  mov      al, byte ptr [eax + 4]         
  0x00224094  884607                  mov      byte ptr [esi + 7], al         
  0x00224097  eb06                    jmp      0x22409f                       
                                        ; XREF: 0x00224089 (cond_jump)
  0x00224099  885e09                  mov      byte ptr [esi + 9], bl         
  0x0022409C  885e07                  mov      byte ptr [esi + 7], bl         
                                        ; XREF: 0x00224097 (jump)
  0x0022409F  6a10                    push     0x10                           
  0x002240A1  58                      pop      eax                            
  0x002240A2  57                      push     edi                            
  0x002240A3  c605506d280030          mov      byte ptr [0x286d50], 0x30      
  0x002240AA  c605516d280040          mov      byte ptr [0x286d51], 0x40      
  0x002240B1  c705586d2800b23c2200    mov      dword ptr [0x286d58], 0x223cb2 
  0x002240BB  89355c6d2800            mov      dword ptr [0x286d5c], esi      
  0x002240C1  891d606d2800            mov      dword ptr [0x286d60], ebx      
  0x002240C7  c705686d28003c6d2800    mov      dword ptr [0x286d68], 0x286d3c 
  0x002240D1  a3646d2800              mov      dword ptr [0x286d64], eax      
  0x002240D6  c6056c6d280002          mov      byte ptr [0x286d6c], 2         
  0x002240DD  c6056d6d280001          mov      byte ptr [0x286d6d], 1         
  0x002240E4  881d6e6d2800            mov      byte ptr [0x286d6e], bl        
  0x002240EA  c605786d2800c1          mov      byte ptr [0x286d78], 0xc1      
  0x002240F1  c605796d280006          mov      byte ptr [0x286d79], 6         
  0x002240F8  66c7057a6d28000042      mov      word ptr [0x286d7a], 0x4200    
  0x00224101  660fb64e05              movzx    cx, byte ptr [esi + 5]         
  0x00224106  6851322200              push     0x223251                       
  0x0022410B  68b06d2800              push     0x286db0                       
  0x00224110  66890d7c6d2800          mov      word ptr [0x286d7c], cx        
  0x00224117  66a37e6d2800            mov      word ptr [0x286d7e], ax        
  0x0022411D  ff153c5b2200            call     dword ptr [0x225b3c]           ; -> xbox_KeInitializeDpc
  0x00224123  e80ef1ffff              call     0x223236                       ; -> sub_00223236
  0x00224128  68506d2800              push     0x286d50                       
  0x0022412D  8bcf                    mov      ecx, edi                       
  0x0022412F  e8ebd9ffff              call     0x221b1f                       ; -> sub_00221B1F
  0x00224134  5f                      pop      edi                            
  0x00224135  5e                      pop      esi                            
  0x00224136  eb0e                    jmp      0x224146                       
                                        ; XREF: 0x00224008 (cond_jump)
  0x00224138  8b4c2408                mov      ecx, dword ptr [esp + 8]       
  0x0022413C  6800010080              push     0x80000100                     
  0x00224141  e8bbccffff              call     0x220e01                       ; -> sub_00220E01
                                        ; XREF: 0x00224136 (jump)
  0x00224146  5b                      pop      ebx                            
  0x00224147  c20400                  ret      4                              

; ============================================================
; Function: sub_0022414A
; Start: 0x0022414A  End: 0x00224167  Size: 29 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0022044F, sub_00224851, sub_00224945, sub_00224AF3
; ============================================================
sub_0022414A:
  0x0022414A  8b442404                mov      eax, dword ptr [esp + 4]       
  0x0022414E  834808ff                or       dword ptr [eax + 8], 0xffffffff 
  0x00224152  c6401fff                mov      byte ptr [eax + 0x1f], 0xff    
  0x00224156  8b0d8c782800            mov      ecx, dword ptr [0x28788c]      
  0x0022415C  894814                  mov      dword ptr [eax + 0x14], ecx    
  0x0022415F  a38c782800              mov      dword ptr [0x28788c], eax      
  0x00224164  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00224167
; Start: 0x00224167  End: 0x002241A4  Size: 61 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0021FC45, sub_00222B6F
; ============================================================
sub_00224167:
  0x00224167  807a1100                cmp      byte ptr [edx + 0x11], 0       
  0x0022416B  8b01                    mov      eax, dword ptr [ecx]           
  0x0022416D  56                      push     esi                            
  0x0022416E  750b                    jne      0x22417b                       
  0x00224170  8db10c040000            lea      esi, [ecx + 0x40c]             
  0x00224176  83c020                  add      eax, 0x20                      
  0x00224179  eb09                    jmp      0x224184                       
                                        ; XREF: 0x0022416E (cond_jump)
  0x0022417B  8db110040000            lea      esi, [ecx + 0x410]             
  0x00224181  83c028                  add      eax, 0x28                      
                                        ; XREF: 0x00224179 (jump)
  0x00224184  8b0e                    mov      ecx, dword ptr [esi]           
  0x00224186  894a18                  mov      dword ptr [edx + 0x18], ecx    
  0x00224189  8916                    mov      dword ptr [esi], edx           
  0x0022418B  8b4a18                  mov      ecx, dword ptr [edx + 0x18]    
  0x0022418E  85c9                    test     ecx, ecx                       
  0x00224190  5e                      pop      esi                            
  0x00224191  7505                    jne      0x224198                       
  0x00224193  214a0c                  and      dword ptr [edx + 0xc], ecx     
  0x00224196  eb06                    jmp      0x22419e                       
                                        ; XREF: 0x00224191 (cond_jump)
  0x00224198  8b4914                  mov      ecx, dword ptr [ecx + 0x14]    
  0x0022419B  894a0c                  mov      dword ptr [edx + 0xc], ecx     
                                        ; XREF: 0x00224196 (jump)
  0x0022419E  8b4a14                  mov      ecx, dword ptr [edx + 0x14]    
  0x002241A1  8908                    mov      dword ptr [eax], ecx           
  0x002241A3  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002241A4
; Start: 0x002241A4  End: 0x002241F4  Size: 80 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00222F78
; ============================================================
sub_002241A4:
  0x002241A4  807a1100                cmp      byte ptr [edx + 0x11], 0       
  0x002241A8  56                      push     esi                            
  0x002241A9  57                      push     edi                            
  0x002241AA  750d                    jne      0x2241b9                       
  0x002241AC  8db10c040000            lea      esi, [ecx + 0x40c]             
  0x002241B2  8b09                    mov      ecx, dword ptr [ecx]           
  0x002241B4  83c120                  add      ecx, 0x20                      
  0x002241B7  eb0b                    jmp      0x2241c4                       
                                        ; XREF: 0x002241AA (cond_jump)
  0x002241B9  8db110040000            lea      esi, [ecx + 0x410]             
  0x002241BF  8b09                    mov      ecx, dword ptr [ecx]           
  0x002241C1  83c128                  add      ecx, 0x28                      
                                        ; XREF: 0x002241B7 (jump)
  0x002241C4  8b06                    mov      eax, dword ptr [esi]           
  0x002241C6  33ff                    xor      edi, edi                       
                                        ; XREF: 0x002241D3 (cond_jump)
  0x002241C8  3bd0                    cmp      edx, eax                       
  0x002241CA  7409                    je       0x2241d5                       
  0x002241CC  8bf8                    mov      edi, eax                       
  0x002241CE  8b4018                  mov      eax, dword ptr [eax + 0x18]    
  0x002241D1  85c0                    test     eax, eax                       
  0x002241D3  75f3                    jne      0x2241c8                       
                                        ; XREF: 0x002241CA (cond_jump)
  0x002241D5  85ff                    test     edi, edi                       
  0x002241D7  740e                    je       0x2241e7                       
  0x002241D9  8b4818                  mov      ecx, dword ptr [eax + 0x18]    
  0x002241DC  894f18                  mov      dword ptr [edi + 0x18], ecx    
  0x002241DF  8b400c                  mov      eax, dword ptr [eax + 0xc]     
  0x002241E2  89470c                  mov      dword ptr [edi + 0xc], eax     
  0x002241E5  eb0a                    jmp      0x2241f1                       
                                        ; XREF: 0x002241D7 (cond_jump)
  0x002241E7  8b5018                  mov      edx, dword ptr [eax + 0x18]    
  0x002241EA  8916                    mov      dword ptr [esi], edx           
  0x002241EC  8b400c                  mov      eax, dword ptr [eax + 0xc]     
  0x002241EF  8901                    mov      dword ptr [ecx], eax           
                                        ; XREF: 0x002241E5 (jump)
  0x002241F1  5f                      pop      edi                            
  0x002241F2  5e                      pop      esi                            
  0x002241F3  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002241F4
; Start: 0x002241F4  End: 0x0022420A  Size: 22 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0022420A
; ============================================================
sub_002241F4:
  0x002241F4  33c0                    xor      eax, eax                       
  0x002241F6  85c9                    test     ecx, ecx                       
  0x002241F8  760f                    jbe      0x224209                       
  0x002241FA  56                      push     esi                            
                                        ; XREF: 0x00224206 (cond_jump)
  0x002241FB  8bf2                    mov      esi, edx                       
  0x002241FD  83e601                  and      esi, 1                         
  0x00224200  d1ea                    shr      edx, 1                         
  0x00224202  49                      dec      ecx                            
  0x00224203  8d0446                  lea      eax, [esi + eax*2]             
  0x00224206  75f3                    jne      0x2241fb                       
  0x00224208  5e                      pop      esi                            
                                        ; XREF: 0x002241F8 (cond_jump)
  0x00224209  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022420A
; Start: 0x0022420A  End: 0x00224281  Size: 119 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002241F4, sub_0022420A
; Called by: sub_0022420A, sub_00224281, sub_0022445D
; ============================================================
sub_0022420A:
  0x0022420A  55                      push     ebp                            
  0x0022420B  8bec                    mov      ebp, esp                       
  0x0022420D  51                      push     ecx                            
  0x0022420E  56                      push     esi                            
  0x0022420F  8bf1                    mov      esi, ecx                       
  0x00224211  8a4d08                  mov      cl, byte ptr [ebp + 8]         
  0x00224214  80f920                  cmp      cl, 0x20                       
  0x00224217  57                      push     edi                            
  0x00224218  8bfa                    mov      edi, edx                       
  0x0022421A  7216                    jb       0x224232                       
  0x0022421C  0fb6d1                  movzx    edx, cl                        
  0x0022421F  6a05                    push     5                              
  0x00224221  83ea20                  sub      edx, 0x20                      
  0x00224224  59                      pop      ecx                            
  0x00224225  e8caffffff              call     0x2241f4                       ; -> sub_002241F4
  0x0022422A  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x0022422D  893c81                  mov      dword ptr [ecx + eax*4], edi   
  0x00224230  eb49                    jmp      0x22427b                       
                                        ; XREF: 0x0022421A (cond_jump)
  0x00224232  8ac1                    mov      al, cl                         
  0x00224234  d0e0                    shl      al, 1                          
  0x00224236  53                      push     ebx                            
  0x00224237  fec0                    inc      al                             
  0x00224239  8ad9                    mov      bl, cl                         
  0x0022423B  8845fc                  mov      byte ptr [ebp - 4], al         
  0x0022423E  c6450b00                mov      byte ptr [ebp + 0xb], 0        
  0x00224242  d0e3                    shl      bl, 1                          
                                        ; XREF: 0x00224278 (cond_jump)
  0x00224244  0fb6c0                  movzx    eax, al                        
  0x00224247  c1e004                  shl      eax, 4                         
  0x0022424A  8d44300c                lea      eax, [eax + esi + 0xc]         
  0x0022424E  83780800                cmp      dword ptr [eax + 8], 0         
  0x00224252  750e                    jne      0x224262                       
  0x00224254  ff75fc                  push     dword ptr [ebp - 4]            
  0x00224257  8bd7                    mov      edx, edi                       
  0x00224259  8bce                    mov      ecx, esi                       
  0x0022425B  e8aaffffff              call     0x22420a                       ; -> sub_0022420A
  0x00224260  eb06                    jmp      0x224268                       
                                        ; XREF: 0x00224252 (cond_jump)
  0x00224262  8b400c                  mov      eax, dword ptr [eax + 0xc]     
  0x00224265  89780c                  mov      dword ptr [eax + 0xc], edi     
                                        ; XREF: 0x00224260 (jump)
  0x00224268  8ac3                    mov      al, bl                         
  0x0022426A  84c0                    test     al, al                         
  0x0022426C  8845fc                  mov      byte ptr [ebp - 4], al         
  0x0022426F  7409                    je       0x22427a                       
  0x00224271  fe450b                  inc      byte ptr [ebp + 0xb]           
  0x00224274  807d0b02                cmp      byte ptr [ebp + 0xb], 2        
  0x00224278  72ca                    jb       0x224244                       
                                        ; XREF: 0x0022426F (cond_jump)
  0x0022427A  5b                      pop      ebx                            
                                        ; XREF: 0x00224230 (jump)
  0x0022427B  5f                      pop      edi                            
  0x0022427C  5e                      pop      esi                            
  0x0022427D  c9                      leave                                   
  0x0022427E  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00224281
; Start: 0x00224281  End: 0x0022445D  Size: 476 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022420A
; Called by: sub_00222B6F, sub_00224DD2
; ============================================================
sub_00224281:
  0x00224281  55                      push     ebp                            
  0x00224282  8bec                    mov      ebp, esp                       
  0x00224284  83ec10                  sub      esp, 0x10                      
  0x00224287  53                      push     ebx                            
  0x00224288  56                      push     esi                            
  0x00224289  8bf2                    mov      esi, edx                       
  0x0022428B  807e1103                cmp      byte ptr [esi + 0x11], 3       
  0x0022428F  57                      push     edi                            
  0x00224290  7553                    jne      0x2242e5                       
  0x00224292  b020                    mov      al, 0x20                       
  0x00224294  384613                  cmp      byte ptr [esi + 0x13], al      
  0x00224297  7309                    jae      0x2242a2                       
  0x00224299  8a5613                  mov      dl, byte ptr [esi + 0x13]      
                                        ; XREF: 0x002242A0 (cond_jump)
  0x0022429C  d0e8                    shr      al, 1                          
  0x0022429E  3ac2                    cmp      al, dl                         
  0x002242A0  77fa                    ja       0x22429c                       
                                        ; XREF: 0x00224297 (cond_jump)
  0x002242A2  8ad8                    mov      bl, al                         
  0x002242A4  d0e3                    shl      bl, 1                          
  0x002242A6  fecb                    dec      bl                             
  0x002242A8  3ac3                    cmp      al, bl                         
  0x002242AA  bfe02e0000              mov      edi, 0x2ee0                    
  0x002242AF  8845ff                  mov      byte ptr [ebp - 1], al         
  0x002242B2  773d                    ja       0x2242f1                       
  0x002242B4  0fb6c0                  movzx    eax, al                        
  0x002242B7  c1e004                  shl      eax, 4                         
  0x002242BA  8d540810                lea      edx, [eax + ecx + 0x10]        
                                        ; XREF: 0x002242E1 (cond_jump)
  0x002242BE  33c0                    xor      eax, eax                       
  0x002242C0  668b42fe                mov      ax, word ptr [edx - 2]         
  0x002242C4  66034202                add      ax, word ptr [edx + 2]         
  0x002242C8  660302                  add      ax, word ptr [edx]             
  0x002242CB  663bc7                  cmp      ax, di                         
  0x002242CE  7308                    jae      0x2242d8                       
  0x002242D0  8bf8                    mov      edi, eax                       
  0x002242D2  8a45ff                  mov      al, byte ptr [ebp - 1]         
  0x002242D5  8845fb                  mov      byte ptr [ebp - 5], al         
                                        ; XREF: 0x002242CE (cond_jump)
  0x002242D8  fe45ff                  inc      byte ptr [ebp - 1]             
  0x002242DB  83c210                  add      edx, 0x10                      
  0x002242DE  385dff                  cmp      byte ptr [ebp - 1], bl         
  0x002242E1  76db                    jbe      0x2242be                       
  0x002242E3  eb0c                    jmp      0x2242f1                       
                                        ; XREF: 0x00224290 (cond_jump)
  0x002242E5  668b7910                mov      di, word ptr [ecx + 0x10]      
  0x002242E9  6603790e                add      di, word ptr [ecx + 0xe]       
  0x002242ED  c645fb00                mov      byte ptr [ebp - 5], 0          
                                        ; XREF: 0x002242B2 (cond_jump), 0x002242E3 (jump)
  0x002242F1  668b4622                mov      ax, word ptr [esi + 0x22]      
  0x002242F5  0fb7ff                  movzx    edi, di                        
  0x002242F8  0fb7d0                  movzx    edx, ax                        
  0x002242FB  03d7                    add      edx, edi                       
  0x002242FD  0fb7b914040000          movzx    edi, word ptr [ecx + 0x414]    
  0x00224304  3bd7                    cmp      edx, edi                       
  0x00224306  7e0a                    jle      0x224312                       
  0x00224308  b800080080              mov      eax, 0x80000800                
  0x0022430D  e946010000              jmp      0x224458                       
                                        ; XREF: 0x00224306 (cond_jump)
  0x00224312  8a55fb                  mov      dl, byte ptr [ebp - 5]         
  0x00224315  0fb6fa                  movzx    edi, dl                        
  0x00224318  c1e704                  shl      edi, 4                         
  0x0022431B  8d7c0f0c                lea      edi, [edi + ecx + 0xc]         
  0x0022431F  885612                  mov      byte ptr [esi + 0x12], dl      
  0x00224322  66014702                add      word ptr [edi + 2], ax         
  0x00224326  84d2                    test     dl, dl                         
  0x00224328  7507                    jne      0x224331                       
  0x0022432A  b001                    mov      al, 1                          
  0x0022432C  8845ff                  mov      byte ptr [ebp - 1], al         
  0x0022432F  eb11                    jmp      0x224342                       
                                        ; XREF: 0x00224328 (cond_jump)
  0x00224331  8ac2                    mov      al, dl                         
  0x00224333  d0e0                    shl      al, 1                          
  0x00224335  8845ff                  mov      byte ptr [ebp - 1], al         
  0x00224338  8ac2                    mov      al, dl                         
  0x0022433A  d0e0                    shl      al, 1                          
  0x0022433C  fec0                    inc      al                             
  0x0022433E  3c40                    cmp      al, 0x40                       
  0x00224340  7740                    ja       0x224382                       
                                        ; XREF: 0x0022432F (jump), 0x0022437D (cond_jump)
  0x00224342  3845ff                  cmp      byte ptr [ebp - 1], al         
  0x00224345  772d                    ja       0x224374                       
  0x00224347  0fb655ff                movzx    edx, byte ptr [ebp - 1]        
  0x0022434B  c1e204                  shl      edx, 4                         
  0x0022434E  8d540a12                lea      edx, [edx + ecx + 0x12]        
  0x00224352  8955f0                  mov      dword ptr [ebp - 0x10], edx    
  0x00224355  8ad0                    mov      dl, al                         
  0x00224357  2a55ff                  sub      dl, byte ptr [ebp - 1]         
  0x0022435A  fec2                    inc      dl                             
  0x0022435C  0fb6d2                  movzx    edx, dl                        
  0x0022435F  8955f4                  mov      dword ptr [ebp - 0xc], edx     
  0x00224362  8b55f0                  mov      edx, dword ptr [ebp - 0x10]    
                                        ; XREF: 0x00224372 (cond_jump)
  0x00224365  668b5e22                mov      bx, word ptr [esi + 0x22]      
  0x00224369  66011a                  add      word ptr [edx], bx             
  0x0022436C  83c210                  add      edx, 0x10                      
  0x0022436F  ff4df4                  dec      dword ptr [ebp - 0xc]          
  0x00224372  75f1                    jne      0x224365                       
                                        ; XREF: 0x00224345 (cond_jump)
  0x00224374  d065ff                  shl      byte ptr [ebp - 1], 1          
  0x00224377  d0e0                    shl      al, 1                          
  0x00224379  fec0                    inc      al                             
  0x0022437B  3c40                    cmp      al, 0x40                       
  0x0022437D  76c3                    jbe      0x224342                       
  0x0022437F  8a55fb                  mov      dl, byte ptr [ebp - 5]         
                                        ; XREF: 0x00224340 (cond_jump)
  0x00224382  80fa01                  cmp      dl, 1                          
  0x00224385  8855ff                  mov      byte ptr [ebp - 1], dl         
  0x00224388  7661                    jbe      0x2243eb                       
                                        ; XREF: 0x002243E9 (cond_jump)
  0x0022438A  8a45ff                  mov      al, byte ptr [ebp - 1]         
  0x0022438D  0fb655ff                movzx    edx, byte ptr [ebp - 1]        
  0x00224391  3401                    xor      al, 1                          
  0x00224393  0fb6c0                  movzx    eax, al                        
  0x00224396  c1e204                  shl      edx, 4                         
  0x00224399  8d540a0c                lea      edx, [edx + ecx + 0xc]         
  0x0022439D  c1e004                  shl      eax, 4                         
  0x002243A0  33db                    xor      ebx, ebx                       
  0x002243A2  668b5a04                mov      bx, word ptr [edx + 4]         
  0x002243A6  668b5202                mov      dx, word ptr [edx + 2]         
  0x002243AA  8d44080c                lea      eax, [eax + ecx + 0xc]         
  0x002243AE  668955f4                mov      word ptr [ebp - 0xc], dx       
  0x002243B2  0fb75004                movzx    edx, word ptr [eax + 4]        
  0x002243B6  0fb74002                movzx    eax, word ptr [eax + 2]        
  0x002243BA  03d0                    add      edx, eax                       
  0x002243BC  0fb745f4                movzx    eax, word ptr [ebp - 0xc]      
  0x002243C0  895df0                  mov      dword ptr [ebp - 0x10], ebx    
  0x002243C3  0fb7db                  movzx    ebx, bx                        
  0x002243C6  03c3                    add      eax, ebx                       
  0x002243C8  3bc2                    cmp      eax, edx                       
  0x002243CA  7e1f                    jle      0x2243eb                       
  0x002243CC  8a45ff                  mov      al, byte ptr [ebp - 1]         
  0x002243CF  8b5df0                  mov      ebx, dword ptr [ebp - 0x10]    
  0x002243D2  8b55f4                  mov      edx, dword ptr [ebp - 0xc]     
  0x002243D5  d0e8                    shr      al, 1                          
  0x002243D7  03d3                    add      edx, ebx                       
  0x002243D9  0fb6d8                  movzx    ebx, al                        
  0x002243DC  c1e304                  shl      ebx, 4                         
  0x002243DF  3c01                    cmp      al, 1                          
  0x002243E1  6689540b10              mov      word ptr [ebx + ecx + 0x10], dx 
  0x002243E6  8845ff                  mov      byte ptr [ebp - 1], al         
  0x002243E9  779f                    ja       0x22438a                       
                                        ; XREF: 0x00224388 (cond_jump), 0x002243CA (cond_jump)
  0x002243EB  807dff01                cmp      byte ptr [ebp - 1], 1          
  0x002243EF  750c                    jne      0x2243fd                       
  0x002243F1  668b4120                mov      ax, word ptr [ecx + 0x20]      
  0x002243F5  6603411e                add      ax, word ptr [ecx + 0x1e]      
  0x002243F9  66894110                mov      word ptr [ecx + 0x10], ax      
                                        ; XREF: 0x002243EF (cond_jump)
  0x002243FD  8b4708                  mov      eax, dword ptr [edi + 8]       
  0x00224400  33d2                    xor      edx, edx                       
  0x00224402  3bc2                    cmp      eax, edx                       
  0x00224404  7536                    jne      0x22443c                       
  0x00224406  8a45fb                  mov      al, byte ptr [ebp - 5]         
  0x00224409  eb04                    jmp      0x22440f                       
                                        ; XREF: 0x0022441B (cond_jump)
  0x0022440B  84c0                    test     al, al                         
  0x0022440D  740e                    je       0x22441d                       
                                        ; XREF: 0x00224409 (jump)
  0x0022440F  d0e8                    shr      al, 1                          
  0x00224411  0fb6d8                  movzx    ebx, al                        
  0x00224414  c1e304                  shl      ebx, 4                         
  0x00224417  39540b14                cmp      dword ptr [ebx + ecx + 0x14], edx 
  0x0022441B  74ee                    je       0x22440b                       
                                        ; XREF: 0x0022440D (cond_jump)
  0x0022441D  0fb6c0                  movzx    eax, al                        
  0x00224420  c1e004                  shl      eax, 4                         
  0x00224423  8b440814                mov      eax, dword ptr [eax + ecx + 0x14] 
  0x00224427  3bc2                    cmp      eax, edx                       
  0x00224429  7406                    je       0x224431                       
  0x0022442B  8b4014                  mov      eax, dword ptr [eax + 0x14]    
  0x0022442E  89460c                  mov      dword ptr [esi + 0xc], eax     
                                        ; XREF: 0x00224429 (cond_jump)
  0x00224431  897708                  mov      dword ptr [edi + 8], esi       
  0x00224434  89770c                  mov      dword ptr [edi + 0xc], esi     
  0x00224437  895618                  mov      dword ptr [esi + 0x18], edx    
  0x0022443A  eb0f                    jmp      0x22444b                       
                                        ; XREF: 0x00224404 (cond_jump)
  0x0022443C  894618                  mov      dword ptr [esi + 0x18], eax    
  0x0022443F  897708                  mov      dword ptr [edi + 8], esi       
  0x00224442  8b4618                  mov      eax, dword ptr [esi + 0x18]    
  0x00224445  8b4014                  mov      eax, dword ptr [eax + 0x14]    
  0x00224448  89460c                  mov      dword ptr [esi + 0xc], eax     
                                        ; XREF: 0x0022443A (jump)
  0x0022444B  ff75fb                  push     dword ptr [ebp - 5]            
  0x0022444E  8b5614                  mov      edx, dword ptr [esi + 0x14]    
  0x00224451  e8b4fdffff              call     0x22420a                       ; -> sub_0022420A
  0x00224456  33c0                    xor      eax, eax                       
                                        ; XREF: 0x0022430D (jump)
  0x00224458  5f                      pop      edi                            
  0x00224459  5e                      pop      esi                            
  0x0022445A  5b                      pop      ebx                            
  0x0022445B  c9                      leave                                   
  0x0022445C  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022445D
; Start: 0x0022445D  End: 0x002245D6  Size: 377 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022420A
; Called by: sub_00222F78, sub_00224F7F
; ============================================================
sub_0022445D:
  0x0022445D  55                      push     ebp                            
  0x0022445E  8bec                    mov      ebp, esp                       
  0x00224460  83ec14                  sub      esp, 0x14                      
  0x00224463  668b4222                mov      ax, word ptr [edx + 0x22]      
  0x00224467  8365fc00                and      dword ptr [ebp - 4], 0         
  0x0022446B  53                      push     ebx                            
  0x0022446C  8a5a12                  mov      bl, byte ptr [edx + 0x12]      
  0x0022446F  668945f0                mov      word ptr [ebp - 0x10], ax      
  0x00224473  0fb6c3                  movzx    eax, bl                        
  0x00224476  56                      push     esi                            
  0x00224477  c1e004                  shl      eax, 4                         
  0x0022447A  8bf1                    mov      esi, ecx                       
  0x0022447C  57                      push     edi                            
  0x0022447D  8d7c300c                lea      edi, [eax + esi + 0xc]         
  0x00224481  8b4708                  mov      eax, dword ptr [edi + 8]       
  0x00224484  8955ec                  mov      dword ptr [ebp - 0x14], edx    
  0x00224487  885df4                  mov      byte ptr [ebp - 0xc], bl       
                                        ; XREF: 0x00224496 (cond_jump)
  0x0022448A  3bc2                    cmp      eax, edx                       
  0x0022448C  740a                    je       0x224498                       
  0x0022448E  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x00224491  8b4018                  mov      eax, dword ptr [eax + 0x18]    
  0x00224494  85c0                    test     eax, eax                       
  0x00224496  75f2                    jne      0x22448a                       
                                        ; XREF: 0x0022448C (cond_jump)
  0x00224498  8b4818                  mov      ecx, dword ptr [eax + 0x18]    
  0x0022449B  85c9                    test     ecx, ecx                       
  0x0022449D  7534                    jne      0x2244d3                       
  0x0022449F  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x002244A2  33d2                    xor      edx, edx                       
  0x002244A4  84db                    test     bl, bl                         
  0x002244A6  894f0c                  mov      dword ptr [edi + 0xc], ecx     
  0x002244A9  8955f8                  mov      dword ptr [ebp - 8], edx       
  0x002244AC  742d                    je       0x2244db                       
  0x002244AE  8ad3                    mov      dl, bl                         
  0x002244B0  eb04                    jmp      0x2244b6                       
                                        ; XREF: 0x002244C3 (cond_jump)
  0x002244B2  84d2                    test     dl, dl                         
  0x002244B4  740f                    je       0x2244c5                       
                                        ; XREF: 0x002244B0 (jump)
  0x002244B6  d0ea                    shr      dl, 1                          
  0x002244B8  0fb6ca                  movzx    ecx, dl                        
  0x002244BB  c1e104                  shl      ecx, 4                         
  0x002244BE  837c311400              cmp      dword ptr [ecx + esi + 0x14], 0 
  0x002244C3  74ed                    je       0x2244b2                       
                                        ; XREF: 0x002244B4 (cond_jump)
  0x002244C5  0fb6ca                  movzx    ecx, dl                        
  0x002244C8  c1e104                  shl      ecx, 4                         
  0x002244CB  8b4c3114                mov      ecx, dword ptr [ecx + esi + 0x14] 
  0x002244CF  85c9                    test     ecx, ecx                       
  0x002244D1  7405                    je       0x2244d8                       
                                        ; XREF: 0x0022449D (cond_jump)
  0x002244D3  8b5114                  mov      edx, dword ptr [ecx + 0x14]    
  0x002244D6  eb03                    jmp      0x2244db                       
                                        ; XREF: 0x002244D1 (cond_jump)
  0x002244D8  8b55f8                  mov      edx, dword ptr [ebp - 8]       
                                        ; XREF: 0x002244AC (cond_jump), 0x002244D6 (jump)
  0x002244DB  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x002244DE  85c9                    test     ecx, ecx                       
  0x002244E0  8b4018                  mov      eax, dword ptr [eax + 0x18]    
  0x002244E3  750f                    jne      0x2244f4                       
  0x002244E5  ff75f4                  push     dword ptr [ebp - 0xc]          
  0x002244E8  8bce                    mov      ecx, esi                       
  0x002244EA  894708                  mov      dword ptr [edi + 8], eax       
  0x002244ED  e818fdffff              call     0x22420a                       ; -> sub_0022420A
  0x002244F2  eb06                    jmp      0x2244fa                       
                                        ; XREF: 0x002244E3 (cond_jump)
  0x002244F4  894118                  mov      dword ptr [ecx + 0x18], eax    
  0x002244F7  89510c                  mov      dword ptr [ecx + 0xc], edx     
                                        ; XREF: 0x002244F2 (jump)
  0x002244FA  668b45f0                mov      ax, word ptr [ebp - 0x10]      
  0x002244FE  66294702                sub      word ptr [edi + 2], ax         
  0x00224502  84db                    test     bl, bl                         
  0x00224504  0f85c3000000            jne      0x2245cd                       
  0x0022450A  b001                    mov      al, 1                          
  0x0022450C  8ac8                    mov      cl, al                         
                                        ; XREF: 0x00224542 (cond_jump)
  0x0022450E  3ac8                    cmp      cl, al                         
  0x00224510  7728                    ja       0x22453a                       
  0x00224512  0fb6d1                  movzx    edx, cl                        
  0x00224515  c1e204                  shl      edx, 4                         
  0x00224518  8d7c3212                lea      edi, [edx + esi + 0x12]        
  0x0022451C  8ad0                    mov      dl, al                         
  0x0022451E  2ad1                    sub      dl, cl                         
  0x00224520  fec2                    inc      dl                             
  0x00224522  0fb6d2                  movzx    edx, dl                        
  0x00224525  8955fc                  mov      dword ptr [ebp - 4], edx       
                                        ; XREF: 0x00224538 (cond_jump)
  0x00224528  8b55ec                  mov      edx, dword ptr [ebp - 0x14]    
  0x0022452B  668b5222                mov      dx, word ptr [edx + 0x22]      
  0x0022452F  662917                  sub      word ptr [edi], dx             
  0x00224532  83c710                  add      edi, 0x10                      
  0x00224535  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x00224538  75ee                    jne      0x224528                       
                                        ; XREF: 0x00224510 (cond_jump), 0x002245D1 (jump)
  0x0022453A  d0e0                    shl      al, 1                          
  0x0022453C  d0e1                    shl      cl, 1                          
  0x0022453E  fec0                    inc      al                             
  0x00224540  3c40                    cmp      al, 0x40                       
  0x00224542  76ca                    jbe      0x22450e                       
  0x00224544  80fb01                  cmp      bl, 1                          
  0x00224547  7671                    jbe      0x2245ba                       
                                        ; XREF: 0x002245B5 (cond_jump)
  0x00224549  8ad3                    mov      dl, bl                         
  0x0022454B  80f201                  xor      dl, 1                          
  0x0022454E  0fb6ca                  movzx    ecx, dl                        
  0x00224551  c1e104                  shl      ecx, 4                         
  0x00224554  8d4c310c                lea      ecx, [ecx + esi + 0xc]         
  0x00224558  0fb77904                movzx    edi, word ptr [ecx + 4]        
  0x0022455C  0fb74902                movzx    ecx, word ptr [ecx + 2]        
  0x00224560  03f9                    add      edi, ecx                       
  0x00224562  0fb6cb                  movzx    ecx, bl                        
  0x00224565  c1e104                  shl      ecx, 4                         
  0x00224568  897dfc                  mov      dword ptr [ebp - 4], edi       
  0x0022456B  8d4c310c                lea      ecx, [ecx + esi + 0xc]         
  0x0022456F  0fb77904                movzx    edi, word ptr [ecx + 4]        
  0x00224573  0fb74902                movzx    ecx, word ptr [ecx + 2]        
  0x00224577  8ac3                    mov      al, bl                         
  0x00224579  03f9                    add      edi, ecx                       
  0x0022457B  d0e8                    shr      al, 1                          
  0x0022457D  3b7dfc                  cmp      edi, dword ptr [ebp - 4]       
  0x00224580  7f12                    jg       0x224594                       
  0x00224582  0fb6c8                  movzx    ecx, al                        
  0x00224585  c1e104                  shl      ecx, 4                         
  0x00224588  0fb74c3110              movzx    ecx, word ptr [ecx + esi + 0x10] 
  0x0022458D  394dfc                  cmp      dword ptr [ebp - 4], ecx       
  0x00224590  7425                    je       0x2245b7                       
  0x00224592  8ada                    mov      bl, dl                         
                                        ; XREF: 0x00224580 (cond_jump)
  0x00224594  0fb6cb                  movzx    ecx, bl                        
  0x00224597  c1e104                  shl      ecx, 4                         
  0x0022459A  8d4c310c                lea      ecx, [ecx + esi + 0xc]         
  0x0022459E  668b5104                mov      dx, word ptr [ecx + 4]         
  0x002245A2  66035102                add      dx, word ptr [ecx + 2]         
  0x002245A6  0fb6c8                  movzx    ecx, al                        
  0x002245A9  c1e104                  shl      ecx, 4                         
  0x002245AC  3c01                    cmp      al, 1                          
  0x002245AE  6689543110              mov      word ptr [ecx + esi + 0x10], dx 
  0x002245B3  8ad8                    mov      bl, al                         
  0x002245B5  7792                    ja       0x224549                       
                                        ; XREF: 0x00224590 (cond_jump)
  0x002245B7  80fb01                  cmp      bl, 1                          
                                        ; XREF: 0x00224547 (cond_jump)
  0x002245BA  750c                    jne      0x2245c8                       
  0x002245BC  668b4620                mov      ax, word ptr [esi + 0x20]      
  0x002245C0  6603461e                add      ax, word ptr [esi + 0x1e]      
  0x002245C4  66894610                mov      word ptr [esi + 0x10], ax      
                                        ; XREF: 0x002245BA (cond_jump)
  0x002245C8  5f                      pop      edi                            
  0x002245C9  5e                      pop      esi                            
  0x002245CA  5b                      pop      ebx                            
  0x002245CB  c9                      leave                                   
  0x002245CC  c3                      ret                                     
                                        ; XREF: 0x00224504 (cond_jump)
  0x002245CD  8acb                    mov      cl, bl                         
  0x002245CF  8ac3                    mov      al, bl                         
  0x002245D1  e964ffffff              jmp      0x22453a                       
; end of function
                                        ; XREF: 0x0021FD6B (data_imm)
  0x002245D6  56                      push     esi                            
  0x002245D7  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x002245DB  8b0e                    mov      ecx, dword ptr [esi]           
  0x002245DD  ff05d06d2800            inc      dword ptr [0x286dd0]           
  0x002245E3  8b4110                  mov      eax, dword ptr [ecx + 0x10]    
  0x002245E6  8b510c                  mov      edx, dword ptr [ecx + 0xc]     
  0x002245E9  23d0                    and      edx, eax                       
  0x002245EB  57                      push     edi                            
  0x002245EC  7477                    je       0x224665                       
  0x002245EE  bf00000080              mov      edi, 0x80000000                
  0x002245F3  85c7                    test     edi, eax                       
  0x002245F5  746e                    je       0x224665                       
  0x002245F7  33c0                    xor      eax, eax                       
  0x002245F9  40                      inc      eax                            
  0x002245FA  84d0                    test     al, dl                         
  0x002245FC  897914                  mov      dword ptr [ecx + 0x14], edi    
  0x002245FF  7406                    je       0x224607                       
  0x00224601  89410c                  mov      dword ptr [ecx + 0xc], eax     
  0x00224604  83e2fe                  and      edx, 0xfffffffe                
                                        ; XREF: 0x002245FF (cond_jump)
  0x00224607  f6c220                  test     dl, 0x20                       
  0x0022460A  742f                    je       0x22463b                       
  0x0022460C  53                      push     ebx                            
  0x0022460D  8b5e08                  mov      ebx, dword ptr [esi + 8]       
  0x00224610  0fb79b80000000          movzx    ebx, word ptr [ebx + 0x80]     
  0x00224617  8dbe18040000            lea      edi, [esi + 0x418]             
  0x0022461D  8b07                    mov      eax, dword ptr [edi]           
  0x0022461F  33d8                    xor      ebx, eax                       
  0x00224621  81e300800000            and      ebx, 0x8000                    
  0x00224627  2bc3                    sub      eax, ebx                       
  0x00224629  0500000100              add      eax, 0x10000                   
  0x0022462E  8907                    mov      dword ptr [edi], eax           
  0x00224630  c7410c20000000          mov      dword ptr [ecx + 0xc], 0x20    
  0x00224637  83e2df                  and      edx, 0xffffffdf                
  0x0022463A  5b                      pop      ebx                            
                                        ; XREF: 0x0022460A (cond_jump)
  0x0022463B  85d2                    test     edx, edx                       
  0x0022463D  7419                    je       0x224658                       
  0x0022463F  6a00                    push     0                              
  0x00224641  899638040000            mov      dword ptr [esi + 0x438], edx   
  0x00224647  6a00                    push     0                              
  0x00224649  81c640040000            add      esi, 0x440                     
  0x0022464F  56                      push     esi                            
  0x00224650  ff15905b2200            call     dword ptr [0x225b90]           ; -> xbox_KeInsertQueueDpc
  0x00224656  eb09                    jmp      0x224661                       
                                        ; XREF: 0x0022463D (cond_jump)
  0x00224658  8b06                    mov      eax, dword ptr [esi]           
  0x0022465A  c7401000000080          mov      dword ptr [eax + 0x10], 0x80000000 
                                        ; XREF: 0x00224656 (jump)
  0x00224661  b001                    mov      al, 1                          
  0x00224663  eb02                    jmp      0x224667                       
                                        ; XREF: 0x002245EC (cond_jump), 0x002245F5 (cond_jump)
  0x00224665  32c0                    xor      al, al                         
                                        ; XREF: 0x00224663 (jump)
  0x00224667  5f                      pop      edi                            
  0x00224668  5e                      pop      esi                            
  0x00224669  c20800                  ret      8                              

; ============================================================
; Function: sub_0022466C
; Start: 0x0022466C  End: 0x00224690  Size: 36 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00222E49, sub_00223032, sub_00224CAA, sub_0022504C, sub_002251B3, sub_002252D2, sub_0022532C
; ============================================================
sub_0022466C:
  0x0022466C  8b4108                  mov      eax, dword ptr [ecx + 8]       
  0x0022466F  8b9118040000            mov      edx, dword ptr [ecx + 0x418]   
  0x00224675  0fb78880000000          movzx    ecx, word ptr [eax + 0x80]     
  0x0022467C  8bc1                    mov      eax, ecx                       
  0x0022467E  33c2                    xor      eax, edx                       
  0x00224680  81e1ff7f0000            and      ecx, 0x7fff                    
  0x00224686  2500800000              and      eax, 0x8000                    
  0x0022468B  0bca                    or       ecx, edx                       
  0x0022468D  03c1                    add      eax, ecx                       
  0x0022468F  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224690
; Start: 0x00224690  End: 0x002247A3  Size: 275 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_00224CAA
; ============================================================
sub_00224690:
  0x00224690  55                      push     ebp                            
  0x00224691  8bec                    mov      ebp, esp                       
  0x00224693  51                      push     ecx                            
  0x00224694  8b9118040000            mov      edx, dword ptr [ecx + 0x418]   
  0x0022469A  53                      push     ebx                            
  0x0022469B  56                      push     esi                            
  0x0022469C  fa                      cli                                     
  0x0022469D  8b4108                  mov      eax, dword ptr [ecx + 8]       
  0x002246A0  0fb78080000000          movzx    eax, word ptr [eax + 0x80]     
  0x002246A7  8b1d0c2080fe            mov      ebx, dword ptr [0xfe80200c]    
  0x002246AD  fb                      sti                                     
  0x002246AE  8bf0                    mov      esi, eax                       
  0x002246B0  25ff7f0000              and      eax, 0x7fff                    
  0x002246B5  33f2                    xor      esi, edx                       
  0x002246B7  0bc2                    or       eax, edx                       
  0x002246B9  81e600800000            and      esi, 0x8000                    
  0x002246BF  03f0                    add      esi, eax                       
  0x002246C1  8bc6                    mov      eax, esi                       
  0x002246C3  2b81d8040000            sub      eax, dword ptr [ecx + 0x4d8]   
  0x002246C9  83f814                  cmp      eax, 0x14                      
  0x002246CC  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x002246CF  0f82ca000000            jb       0x22479f                       
  0x002246D5  8b91d0040000            mov      edx, dword ptr [ecx + 0x4d0]   
  0x002246DB  57                      push     edi                            
  0x002246DC  8d3c76                  lea      edi, [esi + esi*2]             
  0x002246DF  c1e704                  shl      edi, 4                         
  0x002246E2  2bfb                    sub      edi, ebx                       
  0x002246E4  85d2                    test     edx, edx                       
  0x002246E6  7518                    jne      0x224700                       
                                        ; XREF: 0x0022473F (cond_jump), 0x00224744 (cond_jump)
  0x002246E8  83a1d404000000          and      dword ptr [ecx + 0x4d4], 0     
  0x002246EF  89b9d0040000            mov      dword ptr [ecx + 0x4d0], edi   
  0x002246F5  89b1d8040000            mov      dword ptr [ecx + 0x4d8], esi   
  0x002246FB  e99e000000              jmp      0x22479e                       
                                        ; XREF: 0x002246E6 (cond_jump)
  0x00224700  8bc7                    mov      eax, edi                       
  0x00224702  2bc2                    sub      eax, edx                       
  0x00224704  7903                    jns      0x224709                       
  0x00224706  83c02f                  add      eax, 0x2f                      
                                        ; XREF: 0x00224704 (cond_jump)
  0x00224709  6a30                    push     0x30                           
  0x0022470B  99                      cdq                                     
  0x0022470C  5b                      pop      ebx                            
  0x0022470D  f7fb                    idiv     ebx                            
  0x0022470F  8b99d4040000            mov      ebx, dword ptr [ecx + 0x4d4]   
  0x00224715  8bd0                    mov      edx, eax                       
  0x00224717  2bd3                    sub      edx, ebx                       
  0x00224719  7515                    jne      0x224730                       
  0x0022471B  85c0                    test     eax, eax                       
  0x0022471D  747f                    je       0x22479e                       
  0x0022471F  817dfca8610000          cmp      dword ptr [ebp - 4], 0x61a8    
  0x00224726  7676                    jbe      0x22479e                       
  0x00224728  89b1d8040000            mov      dword ptr [ecx + 0x4d8], esi   
  0x0022472E  eb2a                    jmp      0x22475a                       
                                        ; XREF: 0x00224719 (cond_jump)
  0x00224730  83fa03                  cmp      edx, 3                         
  0x00224733  8981d4040000            mov      dword ptr [ecx + 0x4d4], eax   
  0x00224739  89b1d8040000            mov      dword ptr [ecx + 0x4d8], esi   
  0x0022473F  7fa7                    jg       0x2246e8                       
  0x00224741  83fafd                  cmp      edx, -3                        
  0x00224744  7ca2                    jl       0x2246e8                       
  0x00224746  85c0                    test     eax, eax                       
  0x00224748  7454                    je       0x22479e                       
  0x0022474A  85d2                    test     edx, edx                       
  0x0022474C  7e06                    jle      0x224754                       
  0x0022474E  85db                    test     ebx, ebx                       
  0x00224750  7d08                    jge      0x22475a                       
  0x00224752  85d2                    test     edx, edx                       
                                        ; XREF: 0x0022474C (cond_jump)
  0x00224754  7d48                    jge      0x22479e                       
  0x00224756  85db                    test     ebx, ebx                       
  0x00224758  7f44                    jg       0x22479e                       
                                        ; XREF: 0x0022472E (jump), 0x00224750 (cond_jump)
  0x0022475A  8b09                    mov      ecx, dword ptr [ecx]           
  0x0022475C  8b5134                  mov      edx, dword ptr [ecx + 0x34]    
  0x0022475F  85c0                    test     eax, eax                       
  0x00224761  8bf2                    mov      esi, edx                       
  0x00224763  b8ff3f0000              mov      eax, 0x3fff                    
  0x00224768  7e0f                    jle      0x224779                       
  0x0022476A  23f0                    and      esi, eax                       
  0x0022476C  81fee12e0000            cmp      esi, 0x2ee1                    
  0x00224772  7318                    jae      0x22478c                       
  0x00224774  8d7201                  lea      esi, [edx + 1]                 
  0x00224777  eb0d                    jmp      0x224786                       
                                        ; XREF: 0x00224768 (cond_jump)
  0x00224779  23f0                    and      esi, eax                       
  0x0022477B  81fed12e0000            cmp      esi, 0x2ed1                    
  0x00224781  7609                    jbe      0x22478c                       
  0x00224783  8d72ff                  lea      esi, [edx - 1]                 
                                        ; XREF: 0x00224777 (jump)
  0x00224786  33f2                    xor      esi, edx                       
  0x00224788  23f0                    and      esi, eax                       
  0x0022478A  33d6                    xor      edx, esi                       
                                        ; XREF: 0x00224772 (cond_jump), 0x00224781 (cond_jump)
  0x0022478C  8bc2                    mov      eax, edx                       
  0x0022478E  f7d0                    not      eax                            
  0x00224790  33c2                    xor      eax, edx                       
  0x00224792  25ffffff7f              and      eax, 0x7fffffff                
  0x00224797  f7d2                    not      edx                            
  0x00224799  33c2                    xor      eax, edx                       
  0x0022479B  894134                  mov      dword ptr [ecx + 0x34], eax    
                                        ; XREF: 0x002246FB (jump), 0x0022471D (cond_jump), 0x00224726 (cond_jump), 0x00224748 (cond_jump), 0x00224754 (cond_jump), ... (+1 more)
  0x0022479E  5f                      pop      edi                            
                                        ; XREF: 0x002246CF (cond_jump)
  0x0022479F  5e                      pop      esi                            
  0x002247A0  5b                      pop      ebx                            
  0x002247A1  c9                      leave                                   
  0x002247A2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002247A3
; Start: 0x002247A3  End: 0x0022481F  Size: 124 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002231A4
; Called by: sub_00224851, sub_00224945
; ============================================================
sub_002247A3:
  0x002247A3  53                      push     ebx                            
  0x002247A4  56                      push     esi                            
  0x002247A5  57                      push     edi                            
  0x002247A6  8b7c2410                mov      edi, dword ptr [esp + 0x10]    
  0x002247AA  8bf2                    mov      esi, edx                       
  0x002247AC  fe4e27                  dec      byte ptr [esi + 0x27]          
  0x002247AF  8b4718                  mov      eax, dword ptr [edi + 0x18]    
  0x002247B2  85c0                    test     eax, eax                       
  0x002247B4  8bd9                    mov      ebx, ecx                       
  0x002247B6  740e                    je       0x2247c6                       
  0x002247B8  0fb74f20                movzx    ecx, word ptr [edi + 0x20]     
  0x002247BC  6a01                    push     1                              
  0x002247BE  51                      push     ecx                            
  0x002247BF  50                      push     eax                            
  0x002247C0  ff158c5b2200            call     dword ptr [0x225b8c]           ; -> xbox_MmLockUnlockBufferPages
                                        ; XREF: 0x002247B6 (cond_jump)
  0x002247C6  f6472201                test     byte ptr [edi + 0x22], 1       
  0x002247CA  7443                    je       0x22480f                       
  0x002247CC  8b832c040000            mov      eax, dword ptr [ebx + 0x42c]   
  0x002247D2  33c9                    xor      ecx, ecx                       
  0x002247D4  85c0                    test     eax, eax                       
  0x002247D6  7437                    je       0x22480f                       
                                        ; XREF: 0x002247E3 (cond_jump)
  0x002247D8  3bf8                    cmp      edi, eax                       
  0x002247DA  7409                    je       0x2247e5                       
  0x002247DC  8bc8                    mov      ecx, eax                       
  0x002247DE  8b4024                  mov      eax, dword ptr [eax + 0x24]    
  0x002247E1  85c0                    test     eax, eax                       
  0x002247E3  75f3                    jne      0x2247d8                       
                                        ; XREF: 0x002247DA (cond_jump)
  0x002247E5  85c0                    test     eax, eax                       
  0x002247E7  7426                    je       0x22480f                       
  0x002247E9  85c9                    test     ecx, ecx                       
  0x002247EB  750b                    jne      0x2247f8                       
  0x002247ED  8b4824                  mov      ecx, dword ptr [eax + 0x24]    
  0x002247F0  898b2c040000            mov      dword ptr [ebx + 0x42c], ecx   
  0x002247F6  eb06                    jmp      0x2247fe                       
                                        ; XREF: 0x002247EB (cond_jump)
  0x002247F8  8b5024                  mov      edx, dword ptr [eax + 0x24]    
  0x002247FB  895124                  mov      dword ptr [ecx + 0x24], edx    
                                        ; XREF: 0x002247F6 (jump)
  0x002247FE  83602400                and      dword ptr [eax + 0x24], 0      
  0x00224802  fe4e20                  dec      byte ptr [esi + 0x20]          
  0x00224805  7508                    jne      0x22480f                       
  0x00224807  806610df                and      byte ptr [esi + 0x10], 0xdf    
  0x0022480B  806601bf                and      byte ptr [esi + 1], 0xbf       
                                        ; XREF: 0x002247CA (cond_jump), 0x002247D6 (cond_jump), 0x002247E7 (cond_jump), 0x00224805 (cond_jump)
  0x0022480F  804f2208                or       byte ptr [edi + 0x22], 8       
  0x00224813  57                      push     edi                            
  0x00224814  e88be9ffff              call     0x2231a4                       ; -> sub_002231A4
  0x00224819  5f                      pop      edi                            
  0x0022481A  5e                      pop      esi                            
  0x0022481B  5b                      pop      ebx                            
  0x0022481C  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_0022481F
; Start: 0x0022481F  End: 0x00224851  Size: 50 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00224851, sub_00224945
; ============================================================
sub_0022481F:
  0x0022481F  0fb64211                movzx    eax, byte ptr [edx + 0x11]     
  0x00224823  83e800                  sub      eax, 0                         
  0x00224826  741c                    je       0x224844                       
  0x00224828  48                      dec      eax                            
  0x00224829  48                      dec      eax                            
  0x0022482A  740c                    je       0x224838                       
  0x0022482C  48                      dec      eax                            
  0x0022482D  7521                    jne      0x224850                       
  0x0022482F  66ff4a24                dec      word ptr [edx + 0x24]          
  0x00224833  e9ac0f0000              jmp      0x2257e4                       ; -> sub_002257E4
                                        ; XREF: 0x0022482A (cond_jump)
  0x00224838  66ff05a6782800          inc      word ptr [0x2878a6]            
  0x0022483F  e9f30f0000              jmp      0x225837                       ; -> sub_00225837
                                        ; XREF: 0x00224826 (cond_jump)
  0x00224844  66ff05a2782800          inc      word ptr [0x2878a2]            
  0x0022484B  e934100000              jmp      0x225884                       ; -> sub_00225884
                                        ; XREF: 0x0022482D (cond_jump)
  0x00224850  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224851
; Start: 0x00224851  End: 0x00224945  Size: 244 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022414A, sub_002247A3, sub_0022481F
; Called by: sub_00224945
; ============================================================
sub_00224851:
  0x00224851  55                      push     ebp                            
  0x00224852  8bec                    mov      ebp, esp                       
  0x00224854  83ec10                  sub      esp, 0x10                      
  0x00224857  8b02                    mov      eax, dword ptr [edx]           
  0x00224859  53                      push     ebx                            
  0x0022485A  8b5a18                  mov      ebx, dword ptr [edx + 0x18]    
  0x0022485D  56                      push     esi                            
  0x0022485E  c1e81c                  shr      eax, 0x1c                      
  0x00224861  83f809                  cmp      eax, 9                         
  0x00224864  57                      push     edi                            
  0x00224865  8b7a14                  mov      edi, dword ptr [edx + 0x14]    
  0x00224868  894df8                  mov      dword ptr [ebp - 8], ecx       
  0x0022486B  895df0                  mov      dword ptr [ebp - 0x10], ebx    
  0x0022486E  c645ff01                mov      byte ptr [ebp - 1], 1          
  0x00224872  754c                    jne      0x2248c0                       
  0x00224874  807b1d00                cmp      byte ptr [ebx + 0x1d], 0       
  0x00224878  7446                    je       0x2248c0                       
  0x0022487A  8b4204                  mov      eax, dword ptr [edx + 4]       
  0x0022487D  85c0                    test     eax, eax                       
  0x0022487F  742e                    je       0x2248af                       
  0x00224881  8b4a0c                  mov      ecx, dword ptr [edx + 0xc]     
  0x00224884  beff0f0000              mov      esi, 0xfff                     
  0x00224889  23c6                    and      eax, esi                       
  0x0022488B  23ce                    and      ecx, esi                       
  0x0022488D  3bc8                    cmp      ecx, eax                       
  0x0022488F  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x00224892  7c0b                    jl       0x22489f                       
  0x00224894  0fb6421d                movzx    eax, byte ptr [edx + 0x1d]     
  0x00224898  2bc1                    sub      eax, ecx                       
  0x0022489A  0345f4                  add      eax, dword ptr [ebp - 0xc]     
  0x0022489D  eb0d                    jmp      0x2248ac                       
                                        ; XREF: 0x00224892 (cond_jump)
  0x0022489F  0fb6721d                movzx    esi, byte ptr [edx + 0x1d]     
  0x002248A3  2bf1                    sub      esi, ecx                       
  0x002248A5  8d840600f0ffff          lea      eax, [esi + eax - 0x1000]      
                                        ; XREF: 0x0022489D (jump)
  0x002248AC  48                      dec      eax                            
  0x002248AD  eb04                    jmp      0x2248b3                       
                                        ; XREF: 0x0022487F (cond_jump)
  0x002248AF  0fb6421d                movzx    eax, byte ptr [edx + 0x1d]     
                                        ; XREF: 0x002248AD (jump)
  0x002248B3  014314                  add      dword ptr [ebx + 0x14], eax    
  0x002248B6  83630400                and      dword ptr [ebx + 4], 0         
  0x002248BA  c645ff00                mov      byte ptr [ebp - 1], 0          
  0x002248BE  eb19                    jmp      0x2248d9                       
                                        ; XREF: 0x00224872 (cond_jump), 0x00224878 (cond_jump)
  0x002248C0  83f80f                  cmp      eax, 0xf                       
  0x002248C3  7507                    jne      0x2248cc                       
  0x002248C5  c743040f0000c0          mov      dword ptr [ebx + 4], 0xc000000f 
                                        ; XREF: 0x002248C3 (cond_jump)
  0x002248CC  8b02                    mov      eax, dword ptr [edx]           
  0x002248CE  c1e81c                  shr      eax, 0x1c                      
  0x002248D1  0d000000c0              or       eax, 0xc0000000                
  0x002248D6  894304                  mov      dword ptr [ebx + 4], eax       
                                        ; XREF: 0x002248BE (jump)
  0x002248D9  8b7708                  mov      esi, dword ptr [edi + 8]       
  0x002248DC  83e6f0                  and      esi, 0xfffffff0                
                                        ; XREF: 0x0022490E (cond_jump)
  0x002248DF  8a5a1c                  mov      bl, byte ptr [edx + 0x1c]      
  0x002248E2  52                      push     edx                            
  0x002248E3  80e302                  and      bl, 2                          
  0x002248E6  e85ff8ffff              call     0x22414a                       ; -> sub_0022414A
  0x002248EB  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x002248EE  8bd7                    mov      edx, edi                       
  0x002248F0  e82affffff              call     0x22481f                       ; -> sub_0022481F
  0x002248F5  a180782800              mov      eax, dword ptr [0x287880]      
  0x002248FA  8d1430                  lea      edx, [eax + esi]               
  0x002248FD  807a1e02                cmp      byte ptr [edx + 0x1e], 2       
  0x00224901  8b7208                  mov      esi, dword ptr [edx + 8]       
  0x00224904  7506                    jne      0x22490c                       
  0x00224906  807dff00                cmp      byte ptr [ebp - 1], 0          
  0x0022490A  7404                    je       0x224910                       
                                        ; XREF: 0x00224904 (cond_jump)
  0x0022490C  84db                    test     bl, bl                         
  0x0022490E  74cf                    je       0x2248df                       
                                        ; XREF: 0x0022490A (cond_jump)
  0x00224910  8b4210                  mov      eax, dword ptr [edx + 0x10]    
  0x00224913  334708                  xor      eax, dword ptr [edi + 8]       
  0x00224916  83e00f                  and      eax, 0xf                       
  0x00224919  334210                  xor      eax, dword ptr [edx + 0x10]    
  0x0022491C  84db                    test     bl, bl                         
  0x0022491E  894708                  mov      dword ptr [edi + 8], eax       
  0x00224921  740d                    je       0x224930                       
  0x00224923  ff75f0                  push     dword ptr [ebp - 0x10]         
  0x00224926  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x00224929  8bd7                    mov      edx, edi                       
  0x0022492B  e873feffff              call     0x2247a3                       ; -> sub_002247A3
                                        ; XREF: 0x00224921 (cond_jump)
  0x00224930  807f1100                cmp      byte ptr [edi + 0x11], 0       
  0x00224934  7406                    je       0x22493c                       
  0x00224936  807dff00                cmp      byte ptr [ebp - 1], 0          
  0x0022493A  7504                    jne      0x224940                       
                                        ; XREF: 0x00224934 (cond_jump)
  0x0022493C  836708fe                and      dword ptr [edi + 8], 0xfffffffe 
                                        ; XREF: 0x0022493A (cond_jump)
  0x00224940  5f                      pop      edi                            
  0x00224941  5e                      pop      esi                            
  0x00224942  5b                      pop      ebx                            
  0x00224943  c9                      leave                                   
  0x00224944  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224945
; Start: 0x00224945  End: 0x002249F1  Size: 172 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022414A, sub_002247A3, sub_0022481F, sub_00224851
; Called by: sub_002249F1, sub_00224AF3, sub_00224CAA
; ============================================================
sub_00224945:
  0x00224945  55                      push     ebp                            
  0x00224946  8bec                    mov      ebp, esp                       
  0x00224948  51                      push     ecx                            
  0x00224949  51                      push     ecx                            
  0x0022494A  56                      push     esi                            
  0x0022494B  8bf2                    mov      esi, edx                       
  0x0022494D  807e1e01                cmp      byte ptr [esi + 0x1e], 1       
  0x00224951  8b4614                  mov      eax, dword ptr [esi + 0x14]    
  0x00224954  57                      push     edi                            
  0x00224955  8b7e18                  mov      edi, dword ptr [esi + 0x18]    
  0x00224958  894dfc                  mov      dword ptr [ebp - 4], ecx       
  0x0022495B  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x0022495E  751a                    jne      0x22497a                       
  0x00224960  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x00224963  8b0d80782800            mov      ecx, dword ptr [0x287880]      
  0x00224969  8d4408f9                lea      eax, [eax + ecx - 7]           
  0x0022496D  50                      push     eax                            
  0x0022496E  e8d7f7ffff              call     0x22414a                       ; -> sub_0022414A
  0x00224973  66ff05a2782800          inc      word ptr [0x2878a2]            
                                        ; XREF: 0x0022495E (cond_jump)
  0x0022497A  f64603f0                test     byte ptr [esi + 3], 0xf0       
  0x0022497E  740c                    je       0x22498c                       
  0x00224980  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x00224983  8bd6                    mov      edx, esi                       
  0x00224985  e8c7feffff              call     0x224851                       ; -> sub_00224851
  0x0022498A  eb61                    jmp      0x2249ed                       
                                        ; XREF: 0x0022497E (cond_jump)
  0x0022498C  8b4604                  mov      eax, dword ptr [esi + 4]       
  0x0022498F  85c0                    test     eax, eax                       
  0x00224991  53                      push     ebx                            
  0x00224992  7426                    je       0x2249ba                       
  0x00224994  8b4e0c                  mov      ecx, dword ptr [esi + 0xc]     
  0x00224997  baff0f0000              mov      edx, 0xfff                     
  0x0022499C  23c2                    and      eax, edx                       
  0x0022499E  8bd8                    mov      ebx, eax                       
  0x002249A0  0fb6461d                movzx    eax, byte ptr [esi + 0x1d]     
  0x002249A4  23ca                    and      ecx, edx                       
  0x002249A6  2bc1                    sub      eax, ecx                       
  0x002249A8  3bcb                    cmp      ecx, ebx                       
  0x002249AA  7c04                    jl       0x2249b0                       
  0x002249AC  03c3                    add      eax, ebx                       
  0x002249AE  eb07                    jmp      0x2249b7                       
                                        ; XREF: 0x002249AA (cond_jump)
  0x002249B0  8d841800f0ffff          lea      eax, [eax + ebx - 0x1000]      
                                        ; XREF: 0x002249AE (jump)
  0x002249B7  48                      dec      eax                            
  0x002249B8  eb04                    jmp      0x2249be                       
                                        ; XREF: 0x00224992 (cond_jump)
  0x002249BA  0fb6461d                movzx    eax, byte ptr [esi + 0x1d]     
                                        ; XREF: 0x002249B8 (jump)
  0x002249BE  014714                  add      dword ptr [edi + 0x14], eax    
  0x002249C1  8a5e1c                  mov      bl, byte ptr [esi + 0x1c]      
  0x002249C4  56                      push     esi                            
  0x002249C5  80e302                  and      bl, 2                          
  0x002249C8  e87df7ffff              call     0x22414a                       ; -> sub_0022414A
  0x002249CD  8b55f8                  mov      edx, dword ptr [ebp - 8]       
  0x002249D0  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x002249D3  e847feffff              call     0x22481f                       ; -> sub_0022481F
  0x002249D8  84db                    test     bl, bl                         
  0x002249DA  5b                      pop      ebx                            
  0x002249DB  7410                    je       0x2249ed                       
  0x002249DD  8b55f8                  mov      edx, dword ptr [ebp - 8]       
  0x002249E0  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x002249E3  83670400                and      dword ptr [edi + 4], 0         
  0x002249E7  57                      push     edi                            
  0x002249E8  e8b6fdffff              call     0x2247a3                       ; -> sub_002247A3
                                        ; XREF: 0x0022498A (jump), 0x002249DB (cond_jump)
  0x002249ED  5f                      pop      edi                            
  0x002249EE  5e                      pop      esi                            
  0x002249EF  c9                      leave                                   
  0x002249F0  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002249F1
; Start: 0x002249F1  End: 0x00224AF3  Size: 258 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00224945
; Called by: sub_00224CAA
; ============================================================
sub_002249F1:
  0x002249F1  55                      push     ebp                            
  0x002249F2  8bec                    mov      ebp, esp                       
  0x002249F4  83ec18                  sub      esp, 0x18                      
  0x002249F7  53                      push     ebx                            
  0x002249F8  57                      push     edi                            
  0x002249F9  8bfa                    mov      edi, edx                       
  0x002249FB  8bd9                    mov      ebx, ecx                       
  0x002249FD  33d2                    xor      edx, edx                       
  0x002249FF  39932c040000            cmp      dword ptr [ebx + 0x42c], edx   
  0x00224A05  897dec                  mov      dword ptr [ebp - 0x14], edi    
  0x00224A08  895df8                  mov      dword ptr [ebp - 8], ebx       
  0x00224A0B  8955fc                  mov      dword ptr [ebp - 4], edx       
  0x00224A0E  0f84ce000000            je       0x224ae2                       
  0x00224A14  56                      push     esi                            
  0x00224A15  eb03                    jmp      0x224a1a                       
                                        ; XREF: 0x00224ADB (cond_jump)
  0x00224A17  8b7dec                  mov      edi, dword ptr [ebp - 0x14]    
                                        ; XREF: 0x00224A15 (jump)
  0x00224A1A  8b8b2c040000            mov      ecx, dword ptr [ebx + 0x42c]   
  0x00224A20  8b4124                  mov      eax, dword ptr [ecx + 0x24]    
  0x00224A23  89832c040000            mov      dword ptr [ebx + 0x42c], eax   
  0x00224A29  8b7110                  mov      esi, dword ptr [ecx + 0x10]    
  0x00224A2C  3b7e1c                  cmp      edi, dword ptr [esi + 0x1c]    
  0x00224A2F  730b                    jae      0x224a3c                       
                                        ; XREF: 0x00224A4C (jump)
  0x00224A31  895124                  mov      dword ptr [ecx + 0x24], edx    
  0x00224A34  894dfc                  mov      dword ptr [ebp - 4], ecx       
  0x00224A37  e995000000              jmp      0x224ad1                       
                                        ; XREF: 0x00224A2F (cond_jump)
  0x00224A3C  8a4610                  mov      al, byte ptr [esi + 0x10]      
  0x00224A3F  a840                    test     al, 0x40                       
  0x00224A41  740b                    je       0x224a4e                       
  0x00224A43  47                      inc      edi                            
  0x00224A44  24bf                    and      al, 0xbf                       
  0x00224A46  897e1c                  mov      dword ptr [esi + 0x1c], edi    
  0x00224A49  884610                  mov      byte ptr [esi + 0x10], al      
  0x00224A4C  ebe3                    jmp      0x224a31                       
                                        ; XREF: 0x00224A41 (cond_jump)
  0x00224A4E  8b4608                  mov      eax, dword ptr [esi + 8]       
  0x00224A51  8b3d80782800            mov      edi, dword ptr [0x287880]      
  0x00224A57  8365f400                and      dword ptr [ebp - 0xc], 0       
  0x00224A5B  8945e8                  mov      dword ptr [ebp - 0x18], eax    
  0x00224A5E  83e0f0                  and      eax, 0xfffffff0                
  0x00224A61  8d1407                  lea      edx, [edi + eax]               
  0x00224A64  3b4a18                  cmp      ecx, dword ptr [edx + 0x18]    
  0x00224A67  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x00224A6A  7418                    je       0x224a84                       
  0x00224A6C  8b5e04                  mov      ebx, dword ptr [esi + 4]       
                                        ; XREF: 0x00224A7F (cond_jump)
  0x00224A6F  3bc3                    cmp      eax, ebx                       
  0x00224A71  740e                    je       0x224a81                       
  0x00224A73  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x00224A76  8b4208                  mov      eax, dword ptr [edx + 8]       
  0x00224A79  8d1407                  lea      edx, [edi + eax]               
  0x00224A7C  3b4a18                  cmp      ecx, dword ptr [edx + 0x18]    
  0x00224A7F  75ee                    jne      0x224a6f                       
                                        ; XREF: 0x00224A71 (cond_jump)
  0x00224A81  8b5df8                  mov      ebx, dword ptr [ebp - 8]       
                                        ; XREF: 0x00224A6A (cond_jump)
  0x00224A84  8b4208                  mov      eax, dword ptr [edx + 8]       
  0x00224A87  3345e8                  xor      eax, dword ptr [ebp - 0x18]    
  0x00224A8A  8bcb                    mov      ecx, ebx                       
  0x00224A8C  83e00f                  and      eax, 0xf                       
  0x00224A8F  334208                  xor      eax, dword ptr [edx + 8]       
  0x00224A92  894608                  mov      dword ptr [esi + 8], eax       
  0x00224A95  804a03f0                or       byte ptr [edx + 3], 0xf0       
  0x00224A99  e8a7feffff              call     0x224945                       ; -> sub_00224945
  0x00224A9E  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x00224AA1  85c0                    test     eax, eax                       
  0x00224AA3  741f                    je       0x224ac4                       
  0x00224AA5  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x00224AA8  8b1580782800            mov      edx, dword ptr [0x287880]      
  0x00224AAE  83e1f0                  and      ecx, 0xfffffff0                
  0x00224AB1  894c0208                mov      dword ptr [edx + eax + 8], ecx 
  0x00224AB5  8b4608                  mov      eax, dword ptr [esi + 8]       
  0x00224AB8  3345f0                  xor      eax, dword ptr [ebp - 0x10]    
  0x00224ABB  83e00f                  and      eax, 0xf                       
  0x00224ABE  3345f0                  xor      eax, dword ptr [ebp - 0x10]    
  0x00224AC1  894608                  mov      dword ptr [esi + 8], eax       
                                        ; XREF: 0x00224AA3 (cond_jump)
  0x00224AC4  fe4e20                  dec      byte ptr [esi + 0x20]          
  0x00224AC7  7508                    jne      0x224ad1                       
  0x00224AC9  806610df                and      byte ptr [esi + 0x10], 0xdf    
  0x00224ACD  806601bf                and      byte ptr [esi + 1], 0xbf       
                                        ; XREF: 0x00224A37 (jump), 0x00224AC7 (cond_jump)
  0x00224AD1  83bb2c04000000          cmp      dword ptr [ebx + 0x42c], 0     
  0x00224AD8  8b55fc                  mov      edx, dword ptr [ebp - 4]       
  0x00224ADB  0f8536ffffff            jne      0x224a17                       
  0x00224AE1  5e                      pop      esi                            
                                        ; XREF: 0x00224A0E (cond_jump)
  0x00224AE2  33c0                    xor      eax, eax                       
  0x00224AE4  85d2                    test     edx, edx                       
  0x00224AE6  5f                      pop      edi                            
  0x00224AE7  89932c040000            mov      dword ptr [ebx + 0x42c], edx   
  0x00224AED  0f95c0                  setne    al                             
  0x00224AF0  5b                      pop      ebx                            
  0x00224AF1  c9                      leave                                   
  0x00224AF2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224AF3
; Start: 0x00224AF3  End: 0x00224B49  Size: 86 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022414A, sub_00224945
; Called by: sub_00224B49, sub_00224BD0
; ============================================================
sub_00224AF3:
  0x00224AF3  53                      push     ebx                            
  0x00224AF4  56                      push     esi                            
  0x00224AF5  57                      push     edi                            
  0x00224AF6  8bf2                    mov      esi, edx                       
  0x00224AF8  8bf9                    mov      edi, ecx                       
  0x00224AFA  32db                    xor      bl, bl                         
                                        ; XREF: 0x00224B43 (cond_jump)
  0x00224AFC  8b4608                  mov      eax, dword ptr [esi + 8]       
  0x00224AFF  8bc8                    mov      ecx, eax                       
  0x00224B01  83e1f0                  and      ecx, 0xfffffff0                
  0x00224B04  743f                    je       0x224b45                       
  0x00224B06  8b1580782800            mov      edx, dword ptr [0x287880]      
  0x00224B0C  03d1                    add      edx, ecx                       
  0x00224B0E  3b4e04                  cmp      ecx, dword ptr [esi + 4]       
  0x00224B11  741c                    je       0x224b2f                       
  0x00224B13  8b4208                  mov      eax, dword ptr [edx + 8]       
  0x00224B16  804a03f0                or       byte ptr [edx + 3], 0xf0       
  0x00224B1A  334608                  xor      eax, dword ptr [esi + 8]       
  0x00224B1D  8bcf                    mov      ecx, edi                       
  0x00224B1F  83e00f                  and      eax, 0xf                       
  0x00224B22  334208                  xor      eax, dword ptr [edx + 8]       
  0x00224B25  894608                  mov      dword ptr [esi + 8], eax       
  0x00224B28  e818feffff              call     0x224945                       ; -> sub_00224945
  0x00224B2D  eb12                    jmp      0x224b41                       
                                        ; XREF: 0x00224B11 (cond_jump)
  0x00224B2F  83660400                and      dword ptr [esi + 4], 0         
  0x00224B33  83e00f                  and      eax, 0xf                       
  0x00224B36  52                      push     edx                            
  0x00224B37  894608                  mov      dword ptr [esi + 8], eax       
  0x00224B3A  e80bf6ffff              call     0x22414a                       ; -> sub_0022414A
  0x00224B3F  b301                    mov      bl, 1                          
                                        ; XREF: 0x00224B2D (jump)
  0x00224B41  84db                    test     bl, bl                         
  0x00224B43  74b7                    je       0x224afc                       
                                        ; XREF: 0x00224B04 (cond_jump)
  0x00224B45  5f                      pop      edi                            
  0x00224B46  5e                      pop      esi                            
  0x00224B47  5b                      pop      ebx                            
  0x00224B48  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224B49
; Start: 0x00224B49  End: 0x00224BD0  Size: 135 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002231A4, sub_00224AF3
; Called by: sub_00224CAA
; ============================================================
sub_00224B49:
  0x00224B49  51                      push     ecx                            
  0x00224B4A  53                      push     ebx                            
  0x00224B4B  55                      push     ebp                            
  0x00224B4C  8bd9                    mov      ebx, ecx                       
  0x00224B4E  33ed                    xor      ebp, ebp                       
  0x00224B50  39ab30040000            cmp      dword ptr [ebx + 0x430], ebp   
  0x00224B56  89542408                mov      dword ptr [esp + 8], edx       
  0x00224B5A  7463                    je       0x224bbf                       
  0x00224B5C  56                      push     esi                            
  0x00224B5D  57                      push     edi                            
                                        ; XREF: 0x00224BBB (cond_jump)
  0x00224B5E  8bbb30040000            mov      edi, dword ptr [ebx + 0x430]   
  0x00224B64  8b4724                  mov      eax, dword ptr [edi + 0x24]    
  0x00224B67  898330040000            mov      dword ptr [ebx + 0x430], eax   
  0x00224B6D  8b7710                  mov      esi, dword ptr [edi + 0x10]    
  0x00224B70  3b561c                  cmp      edx, dword ptr [esi + 0x1c]    
  0x00224B73  7307                    jae      0x224b7c                       
                                        ; XREF: 0x00224B8E (jump)
  0x00224B75  896f14                  mov      dword ptr [edi + 0x14], ebp    
  0x00224B78  8bef                    mov      ebp, edi                       
  0x00224B7A  eb38                    jmp      0x224bb4                       
                                        ; XREF: 0x00224B73 (cond_jump)
  0x00224B7C  8a4610                  mov      al, byte ptr [esi + 0x10]      
  0x00224B7F  a840                    test     al, 0x40                       
  0x00224B81  740d                    je       0x224b90                       
  0x00224B83  8d4a01                  lea      ecx, [edx + 1]                 
  0x00224B86  24bf                    and      al, 0xbf                       
  0x00224B88  894e1c                  mov      dword ptr [esi + 0x1c], ecx    
  0x00224B8B  884610                  mov      byte ptr [esi + 0x10], al      
  0x00224B8E  ebe5                    jmp      0x224b75                       
                                        ; XREF: 0x00224B81 (cond_jump)
  0x00224B90  8bd6                    mov      edx, esi                       
  0x00224B92  8bcb                    mov      ecx, ebx                       
  0x00224B94  e85affffff              call     0x224af3                       ; -> sub_00224AF3
  0x00224B99  fe4e20                  dec      byte ptr [esi + 0x20]          
  0x00224B9C  7508                    jne      0x224ba6                       
  0x00224B9E  806610df                and      byte ptr [esi + 0x10], 0xdf    
  0x00224BA2  806601bf                and      byte ptr [esi + 1], 0xbf       
                                        ; XREF: 0x00224B9C (cond_jump)
  0x00224BA6  83670400                and      dword ptr [edi + 4], 0         
  0x00224BAA  57                      push     edi                            
  0x00224BAB  e8f4e5ffff              call     0x2231a4                       ; -> sub_002231A4
  0x00224BB0  8b542410                mov      edx, dword ptr [esp + 0x10]    
                                        ; XREF: 0x00224B7A (jump)
  0x00224BB4  83bb3004000000          cmp      dword ptr [ebx + 0x430], 0     
  0x00224BBB  75a1                    jne      0x224b5e                       
  0x00224BBD  5f                      pop      edi                            
  0x00224BBE  5e                      pop      esi                            
                                        ; XREF: 0x00224B5A (cond_jump)
  0x00224BBF  33c0                    xor      eax, eax                       
  0x00224BC1  89ab30040000            mov      dword ptr [ebx + 0x430], ebp   
  0x00224BC7  85ed                    test     ebp, ebp                       
  0x00224BC9  5d                      pop      ebp                            
  0x00224BCA  0f95c0                  setne    al                             
  0x00224BCD  5b                      pop      ebx                            
  0x00224BCE  59                      pop      ecx                            
  0x00224BCF  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224BD0
; Start: 0x00224BD0  End: 0x00224CAA  Size: 218 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002231A4, sub_00224AF3, sub_00224FC3
; Called by: sub_00224CAA
; ============================================================
sub_00224BD0:
  0x00224BD0  55                      push     ebp                            
  0x00224BD1  8bec                    mov      ebp, esp                       
  0x00224BD3  83ec0c                  sub      esp, 0xc                       
  0x00224BD6  53                      push     ebx                            
  0x00224BD7  8bd9                    mov      ebx, ecx                       
  0x00224BD9  33c9                    xor      ecx, ecx                       
  0x00224BDB  398b34040000            cmp      dword ptr [ebx + 0x434], ecx   
  0x00224BE1  8955f8                  mov      dword ptr [ebp - 8], edx       
  0x00224BE4  894dfc                  mov      dword ptr [ebp - 4], ecx       
  0x00224BE7  0f84ad000000            je       0x224c9a                       
  0x00224BED  56                      push     esi                            
  0x00224BEE  57                      push     edi                            
                                        ; XREF: 0x00224C92 (cond_jump)
  0x00224BEF  8bb334040000            mov      esi, dword ptr [ebx + 0x434]   
  0x00224BF5  8b4614                  mov      eax, dword ptr [esi + 0x14]    
  0x00224BF8  898334040000            mov      dword ptr [ebx + 0x434], eax   
  0x00224BFE  8b7e10                  mov      edi, dword ptr [esi + 0x10]    
  0x00224C01  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00224C04  3b471c                  cmp      eax, dword ptr [edi + 0x1c]    
  0x00224C07  7308                    jae      0x224c11                       
                                        ; XREF: 0x00224C1D (jump)
  0x00224C09  894e14                  mov      dword ptr [esi + 0x14], ecx    
  0x00224C0C  8975fc                  mov      dword ptr [ebp - 4], esi       
  0x00224C0F  eb77                    jmp      0x224c88                       
                                        ; XREF: 0x00224C07 (cond_jump)
  0x00224C11  8a4710                  mov      al, byte ptr [edi + 0x10]      
  0x00224C14  a840                    test     al, 0x40                       
  0x00224C16  7407                    je       0x224c1f                       
  0x00224C18  24bf                    and      al, 0xbf                       
  0x00224C1A  884710                  mov      byte ptr [edi + 0x10], al      
  0x00224C1D  ebea                    jmp      0x224c09                       
                                        ; XREF: 0x00224C16 (cond_jump)
  0x00224C1F  807e014a                cmp      byte ptr [esi + 1], 0x4a       
  0x00224C23  8bcb                    mov      ecx, ebx                       
  0x00224C25  7509                    jne      0x224c30                       
  0x00224C27  8bd6                    mov      edx, esi                       
  0x00224C29  e895030000              call     0x224fc3                       ; -> sub_00224FC3
  0x00224C2E  eb58                    jmp      0x224c88                       
                                        ; XREF: 0x00224C25 (cond_jump)
  0x00224C30  8bd7                    mov      edx, edi                       
  0x00224C32  e8bcfeffff              call     0x224af3                       ; -> sub_00224AF3
  0x00224C37  8b5618                  mov      edx, dword ptr [esi + 0x18]    
  0x00224C3A  85d2                    test     edx, edx                       
  0x00224C3C  7432                    je       0x224c70                       
  0x00224C3E  8b0f                    mov      ecx, dword ptr [edi]           
  0x00224C40  894df4                  mov      dword ptr [ebp - 0xc], ecx     
  0x00224C43  c1e907                  shr      ecx, 7                         
  0x00224C46  33c0                    xor      eax, eax                       
  0x00224C48  83e10f                  and      ecx, 0xf                       
  0x00224C4B  40                      inc      eax                            
  0x00224C4C  d3e0                    shl      eax, cl                        
  0x00224C4E  8b4df4                  mov      ecx, dword ptr [ebp - 0xc]     
  0x00224C51  81e100180000            and      ecx, 0x1800                    
  0x00224C57  81f900100000            cmp      ecx, 0x1000                    
  0x00224C5D  7503                    jne      0x224c62                       
  0x00224C5F  c1e010                  shl      eax, 0x10                      
                                        ; XREF: 0x00224C5D (cond_jump)
  0x00224C62  f6470802                test     byte ptr [edi + 8], 2          
  0x00224C66  7404                    je       0x224c6c                       
  0x00224C68  0902                    or       dword ptr [edx], eax           
  0x00224C6A  eb04                    jmp      0x224c70                       
                                        ; XREF: 0x00224C66 (cond_jump)
  0x00224C6C  f7d0                    not      eax                            
  0x00224C6E  2102                    and      dword ptr [edx], eax           
                                        ; XREF: 0x00224C3C (cond_jump), 0x00224C6A (jump)
  0x00224C70  a188782800              mov      eax, dword ptr [0x287888]      
  0x00224C75  894718                  mov      dword ptr [edi + 0x18], eax    
  0x00224C78  893d88782800            mov      dword ptr [0x287888], edi      
  0x00224C7E  83660400                and      dword ptr [esi + 4], 0         
  0x00224C82  56                      push     esi                            
  0x00224C83  e81ce5ffff              call     0x2231a4                       ; -> sub_002231A4
                                        ; XREF: 0x00224C0F (jump), 0x00224C2E (jump)
  0x00224C88  83bb3404000000          cmp      dword ptr [ebx + 0x434], 0     
  0x00224C8F  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x00224C92  0f8557ffffff            jne      0x224bef                       
  0x00224C98  5f                      pop      edi                            
  0x00224C99  5e                      pop      esi                            
                                        ; XREF: 0x00224BE7 (cond_jump)
  0x00224C9A  33c0                    xor      eax, eax                       
  0x00224C9C  85c9                    test     ecx, ecx                       
  0x00224C9E  898b34040000            mov      dword ptr [ebx + 0x434], ecx   
  0x00224CA4  0f95c0                  setne    al                             
  0x00224CA7  5b                      pop      ebx                            
  0x00224CA8  c9                      leave                                   
  0x00224CA9  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224CAA
; Start: 0x00224CAA  End: 0x00224DC0  Size: 278 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_00222A9D, sub_0022466C, sub_00224690, sub_00224945, sub_002249F1, sub_00224B49, sub_00224BD0, sub_0022532C
; ============================================================
sub_00224CAA:
  0x00224CAA  55                      push     ebp                            
  0x00224CAB  8bec                    mov      ebp, esp                       
  0x00224CAD  51                      push     ecx                            
  0x00224CAE  51                      push     ecx                            
  0x00224CAF  53                      push     ebx                            
  0x00224CB0  56                      push     esi                            
  0x00224CB1  8b750c                  mov      esi, dword ptr [ebp + 0xc]     
  0x00224CB4  8b1e                    mov      ebx, dword ptr [esi]           
  0x00224CB6  8d8638040000            lea      eax, [esi + 0x438]             
  0x00224CBC  8b08                    mov      ecx, dword ptr [eax]           
  0x00224CBE  57                      push     edi                            
  0x00224CBF  894dfc                  mov      dword ptr [ebp - 4], ecx       
  0x00224CC2  33ff                    xor      edi, edi                       
  0x00224CC4  8bce                    mov      ecx, esi                       
  0x00224CC6  c6450f00                mov      byte ptr [ebp + 0xf], 0        
  0x00224CCA  8938                    mov      dword ptr [eax], edi           
  0x00224CCC  e8bff9ffff              call     0x224690                       ; -> sub_00224690
  0x00224CD1  f645fc02                test     byte ptr [ebp - 4], 2          
  0x00224CD5  7457                    je       0x224d2e                       
  0x00224CD7  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x00224CDA  81c184000000            add      ecx, 0x84                      
  0x00224CE0  8b01                    mov      eax, dword ptr [ecx]           
  0x00224CE2  83e0f0                  and      eax, 0xfffffff0                
  0x00224CE5  8939                    mov      dword ptr [ecx], edi           
  0x00224CE7  7431                    je       0x224d1a                       
                                        ; XREF: 0x00224CFB (cond_jump)
  0x00224CE9  8b0d80782800            mov      ecx, dword ptr [0x287880]      
  0x00224CEF  03c8                    add      ecx, eax                       
  0x00224CF1  8b4108                  mov      eax, dword ptr [ecx + 8]       
  0x00224CF4  85c0                    test     eax, eax                       
  0x00224CF6  897908                  mov      dword ptr [ecx + 8], edi       
  0x00224CF9  8bf9                    mov      edi, ecx                       
  0x00224CFB  75ec                    jne      0x224ce9                       
                                        ; XREF: 0x00224D18 (cond_jump)
  0x00224CFD  8bd7                    mov      edx, edi                       
  0x00224CFF  f6420201                test     byte ptr [edx + 2], 1          
  0x00224D03  8b7f08                  mov      edi, dword ptr [edi + 8]       
  0x00224D06  8bce                    mov      ecx, esi                       
  0x00224D08  7407                    je       0x224d11                       
  0x00224D0A  e81d060000              call     0x22532c                       ; -> sub_0022532C
  0x00224D0F  eb05                    jmp      0x224d16                       
                                        ; XREF: 0x00224D08 (cond_jump)
  0x00224D11  e82ffcffff              call     0x224945                       ; -> sub_00224945
                                        ; XREF: 0x00224D0F (jump)
  0x00224D16  85ff                    test     edi, edi                       
  0x00224D18  75e3                    jne      0x224cfd                       
                                        ; XREF: 0x00224CE7 (cond_jump)
  0x00224D1A  8365fcfd                and      dword ptr [ebp - 4], 0xfffffffd 
  0x00224D1E  c7430c02000000          mov      dword ptr [ebx + 0xc], 2       
  0x00224D25  8b06                    mov      eax, dword ptr [esi]           
  0x00224D27  c7400806000000          mov      dword ptr [eax + 8], 6         
                                        ; XREF: 0x00224CD5 (cond_jump)
  0x00224D2E  f645fc04                test     byte ptr [ebp - 4], 4          
  0x00224D32  6a04                    push     4                              
  0x00224D34  5f                      pop      edi                            
  0x00224D35  740a                    je       0x224d41                       
  0x00224D37  8365fcfb                and      dword ptr [ebp - 4], 0xfffffffb 
  0x00224D3B  897b0c                  mov      dword ptr [ebx + 0xc], edi     
  0x00224D3E  897b14                  mov      dword ptr [ebx + 0x14], edi    
                                        ; XREF: 0x00224D35 (cond_jump)
  0x00224D41  8bce                    mov      ecx, esi                       
  0x00224D43  e824f9ffff              call     0x22466c                       ; -> sub_0022466C
  0x00224D48  8bd0                    mov      edx, eax                       
  0x00224D4A  8bce                    mov      ecx, esi                       
  0x00224D4C  8955f8                  mov      dword ptr [ebp - 8], edx       
  0x00224D4F  e89dfcffff              call     0x2249f1                       ; -> sub_002249F1
  0x00224D54  84c0                    test     al, al                         
  0x00224D56  7404                    je       0x224d5c                       
  0x00224D58  c6450f01                mov      byte ptr [ebp + 0xf], 1        
                                        ; XREF: 0x00224D56 (cond_jump)
  0x00224D5C  8b55f8                  mov      edx, dword ptr [ebp - 8]       
  0x00224D5F  8bce                    mov      ecx, esi                       
  0x00224D61  e8e3fdffff              call     0x224b49                       ; -> sub_00224B49
  0x00224D66  84c0                    test     al, al                         
  0x00224D68  7404                    je       0x224d6e                       
  0x00224D6A  c6450f01                mov      byte ptr [ebp + 0xf], 1        
                                        ; XREF: 0x00224D68 (cond_jump)
  0x00224D6E  8b55f8                  mov      edx, dword ptr [ebp - 8]       
  0x00224D71  8bce                    mov      ecx, esi                       
  0x00224D73  e858feffff              call     0x224bd0                       ; -> sub_00224BD0
  0x00224D78  84c0                    test     al, al                         
  0x00224D7A  7404                    je       0x224d80                       
  0x00224D7C  c6450f01                mov      byte ptr [ebp + 0xf], 1        
                                        ; XREF: 0x00224D7A (cond_jump)
  0x00224D80  807d0f00                cmp      byte ptr [ebp + 0xf], 0        
  0x00224D84  740a                    je       0x224d90                       
  0x00224D86  8b06                    mov      eax, dword ptr [esi]           
  0x00224D88  89780c                  mov      dword ptr [eax + 0xc], edi     
  0x00224D8B  8b06                    mov      eax, dword ptr [esi]           
  0x00224D8D  897810                  mov      dword ptr [eax + 0x10], edi    
                                        ; XREF: 0x00224D84 (cond_jump)
  0x00224D90  f645fc40                test     byte ptr [ebp - 4], 0x40       
  0x00224D94  7412                    je       0x224da8                       
  0x00224D96  8bce                    mov      ecx, esi                       
  0x00224D98  e800ddffff              call     0x222a9d                       ; -> sub_00222A9D
  0x00224D9D  8365fcbf                and      dword ptr [ebp - 4], 0xffffffbf 
  0x00224DA1  c7430c40000000          mov      dword ptr [ebx + 0xc], 0x40    
                                        ; XREF: 0x00224D94 (cond_jump)
  0x00224DA8  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x00224DAB  85c0                    test     eax, eax                       
  0x00224DAD  7403                    je       0x224db2                       
  0x00224DAF  89430c                  mov      dword ptr [ebx + 0xc], eax     
                                        ; XREF: 0x00224DAD (cond_jump)
  0x00224DB2  5f                      pop      edi                            
  0x00224DB3  5e                      pop      esi                            
  0x00224DB4  c7431000000080          mov      dword ptr [ebx + 0x10], 0x80000000 
  0x00224DBB  5b                      pop      ebx                            
  0x00224DBC  c9                      leave                                   
  0x00224DBD  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_00224DC0
; Start: 0x00224DC0  End: 0x00224DD2  Size: 18 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00224DD2
; ============================================================
sub_00224DC0:
  0x00224DC0  a1a8782800              mov      eax, dword ptr [0x2878a8]      
  0x00224DC5  85c0                    test     eax, eax                       
  0x00224DC7  7408                    je       0x224dd1                       
  0x00224DC9  8b08                    mov      ecx, dword ptr [eax]           
  0x00224DCB  890da8782800            mov      dword ptr [0x2878a8], ecx      
                                        ; XREF: 0x00224DC7 (cond_jump)
  0x00224DD1  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224DD2
; Start: 0x00224DD2  End: 0x00224F7F  Size: 429 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002231B8, sub_00224281, sub_00224DC0
; Called by: sub_00223032
; ============================================================
sub_00224DD2:
  0x00224DD2  55                      push     ebp                            
  0x00224DD3  8bec                    mov      ebp, esp                       
  0x00224DD5  83ec14                  sub      esp, 0x14                      
  0x00224DD8  a1ac782800              mov      eax, dword ptr [0x2878ac]      
  0x00224DDD  53                      push     ebx                            
  0x00224DDE  57                      push     edi                            
  0x00224DDF  8bda                    mov      ebx, edx                       
  0x00224DE1  894dec                  mov      dword ptr [ebp - 0x14], ecx    
  0x00224DE4  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x00224DE7  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00224DED  8845fe                  mov      byte ptr [ebp - 2], al         
  0x00224DF0  e8cbffffff              call     0x224dc0                       ; -> sub_00224DC0
  0x00224DF5  8bf8                    mov      edi, eax                       
  0x00224DF7  85ff                    test     edi, edi                       
  0x00224DF9  897df4                  mov      dword ptr [ebp - 0xc], edi     
  0x00224DFC  750a                    jne      0x224e08                       
  0x00224DFE  bf00010080              mov      edi, 0x80000100                
  0x00224E03  e965010000              jmp      0x224f6d                       
                                        ; XREF: 0x00224DFC (cond_jump)
  0x00224E08  56                      push     esi                            
  0x00224E09  8b75f8                  mov      esi, dword ptr [ebp - 8]       
  0x00224E0C  c1e606                  shl      esi, 6                         
  0x00224E0F  33c0                    xor      eax, eax                       
  0x00224E11  8d4e30                  lea      ecx, [esi + 0x30]              
  0x00224E14  8bd1                    mov      edx, ecx                       
  0x00224E16  c1e902                  shr      ecx, 2                         
  0x00224E19  f3ab                    rep stosd dword ptr es:[edi], eax        
  0x00224E1B  8bca                    mov      ecx, edx                       
  0x00224E1D  83e103                  and      ecx, 3                         
  0x00224E20  f3aa                    rep stosb byte ptr es:[edi], al          
  0x00224E22  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x00224E25  03f0                    add      esi, eax                       
  0x00224E27  89462c                  mov      dword ptr [esi + 0x2c], eax    
  0x00224E2A  8bc6                    mov      eax, esi                       
  0x00224E2C  2b0580782800            sub      eax, dword ptr [0x287880]      
  0x00224E32  c6461101                mov      byte ptr [esi + 0x11], 1       
  0x00224E36  894614                  mov      dword ptr [esi + 0x14], eax    
  0x00224E39  33c0                    xor      eax, eax                       
  0x00224E3B  c6461301                mov      byte ptr [esi + 0x13], 1       
  0x00224E3F  668b4316                mov      ax, word ptr [ebx + 0x16]      
  0x00224E43  6a00                    push     0                              
  0x00224E45  6a01                    push     1                              
  0x00224E47  50                      push     eax                            
  0x00224E48  e86be3ffff              call     0x2231b8                       ; -> sub_002231B8
  0x00224E4D  8b55f8                  mov      edx, dword ptr [ebp - 8]       
  0x00224E50  66894622                mov      word ptr [esi + 0x22], ax      
  0x00224E54  885624                  mov      byte ptr [esi + 0x24], dl      
  0x00224E57  8a4318                  mov      al, byte ptr [ebx + 0x18]      
  0x00224E5A  2401                    and      al, 1                          
  0x00224E5C  884610                  mov      byte ptr [esi + 0x10], al      
  0x00224E5F  33c0                    xor      eax, eax                       
  0x00224E61  8a4314                  mov      al, byte ptr [ebx + 0x14]      
  0x00224E64  6a00                    push     0                              
  0x00224E66  3306                    xor      eax, dword ptr [esi]           
  0x00224E68  83e07f                  and      eax, 0x7f                      
  0x00224E6B  3106                    xor      dword ptr [esi], eax           
  0x00224E6D  0fb64315                movzx    eax, byte ptr [ebx + 0x15]     
  0x00224E71  8b0e                    mov      ecx, dword ptr [esi]           
  0x00224E73  c1e007                  shl      eax, 7                         
  0x00224E76  33c1                    xor      eax, ecx                       
  0x00224E78  2580070000              and      eax, 0x780                     
  0x00224E7D  33c1                    xor      eax, ecx                       
  0x00224E7F  8906                    mov      dword ptr [esi], eax           
  0x00224E81  f6431580                test     byte ptr [ebx + 0x15], 0x80    
  0x00224E85  59                      pop      ecx                            
  0x00224E86  0f95c1                  setne    cl                             
  0x00224E89  25ffc7ffff              and      eax, 0xffffc7ff                
  0x00224E8E  41                      inc      ecx                            
  0x00224E8F  83e103                  and      ecx, 3                         
  0x00224E92  83c918                  or       ecx, 0x18                      
  0x00224E95  c1e10b                  shl      ecx, 0xb                       
  0x00224E98  0bc8                    or       ecx, eax                       
  0x00224E9A  890e                    mov      dword ptr [esi], ecx           
  0x00224E9C  0fb74316                movzx    eax, word ptr [ebx + 0x16]     
  0x00224EA0  c1e010                  shl      eax, 0x10                      
  0x00224EA3  33c1                    xor      eax, ecx                       
  0x00224EA5  250000ff07              and      eax, 0x7ff0000                 
  0x00224EAA  33c1                    xor      eax, ecx                       
  0x00224EAC  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x00224EAF  8906                    mov      dword ptr [esi], eax           
  0x00224EB1  8b462c                  mov      eax, dword ptr [esi + 0x2c]    
  0x00224EB4  2b0580782800            sub      eax, dword ptr [0x287880]      
  0x00224EBA  33c8                    xor      ecx, eax                       
  0x00224EBC  83e10f                  and      ecx, 0xf                       
  0x00224EBF  33c8                    xor      ecx, eax                       
  0x00224EC1  894e08                  mov      dword ptr [esi + 8], ecx       
  0x00224EC4  32c9                    xor      cl, cl                         
  0x00224EC6  85d2                    test     edx, edx                       
  0x00224EC8  894604                  mov      dword ptr [esi + 4], eax       
  0x00224ECB  884dff                  mov      byte ptr [ebp - 1], cl         
  0x00224ECE  765d                    jbe      0x224f2d                       
  0x00224ED0  33c0                    xor      eax, eax                       
                                        ; XREF: 0x00224F2B (cond_jump)
  0x00224ED2  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224ED5  c1e006                  shl      eax, 6                         
  0x00224ED8  8d3c10                  lea      edi, [eax + edx]               
  0x00224EDB  897df0                  mov      dword ptr [ebp - 0x10], edi    
  0x00224EDE  2b3d80782800            sub      edi, dword ptr [0x287880]      
  0x00224EE4  8b55f0                  mov      edx, dword ptr [ebp - 0x10]    
  0x00224EE7  83c740                  add      edi, 0x40                      
  0x00224EEA  fec9                    dec      cl                             
  0x00224EEC  884a2d                  mov      byte ptr [edx + 0x2d], cl      
  0x00224EEF  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224EF2  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x00224EF5  884c102c                mov      byte ptr [eax + edx + 0x2c], cl 
  0x00224EF9  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224EFC  89741020                mov      dword ptr [eax + edx + 0x20], esi 
  0x00224F00  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224F03  8364102800              and      dword ptr [eax + edx + 0x28], 0 
  0x00224F08  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224F0B  8364102400              and      dword ptr [eax + edx + 0x24], 0 
  0x00224F10  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224F13  03d0                    add      edx, eax                       
  0x00224F15  804a0201                or       byte ptr [edx + 2], 1          
  0x00224F19  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224F1C  fec1                    inc      cl                             
  0x00224F1E  897c1008                mov      dword ptr [eax + edx + 8], edi 
  0x00224F22  0fb6c1                  movzx    eax, cl                        
  0x00224F25  3b45f8                  cmp      eax, dword ptr [ebp - 8]       
  0x00224F28  884dff                  mov      byte ptr [ebp - 1], cl         
  0x00224F2B  72a5                    jb       0x224ed2                       
                                        ; XREF: 0x00224ECE (cond_jump)
  0x00224F2D  8b562c                  mov      edx, dword ptr [esi + 0x2c]    
  0x00224F30  0fb6c1                  movzx    eax, cl                        
  0x00224F33  c1e006                  shl      eax, 6                         
  0x00224F36  836410c800              and      dword ptr [eax + edx - 0x38], 0 
  0x00224F3B  8b462c                  mov      eax, dword ptr [esi + 0x2c]    
  0x00224F3E  fec9                    dec      cl                             
  0x00224F40  88482d                  mov      byte ptr [eax + 0x2d], cl      
  0x00224F43  8b4dec                  mov      ecx, dword ptr [ebp - 0x14]    
  0x00224F46  8bd6                    mov      edx, esi                       
  0x00224F48  e834f3ffff              call     0x224281                       ; -> sub_00224281
  0x00224F4D  8bf8                    mov      edi, eax                       
  0x00224F4F  85ff                    test     edi, edi                       
  0x00224F51  7c05                    jl       0x224f58                       
  0x00224F53  897310                  mov      dword ptr [ebx + 0x10], esi    
  0x00224F56  eb14                    jmp      0x224f6c                       
                                        ; XREF: 0x00224F51 (cond_jump)
  0x00224F58  83631000                and      dword ptr [ebx + 0x10], 0      
  0x00224F5C  8b0da8782800            mov      ecx, dword ptr [0x2878a8]      
  0x00224F62  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x00224F65  8908                    mov      dword ptr [eax], ecx           
  0x00224F67  a3a8782800              mov      dword ptr [0x2878a8], eax      
                                        ; XREF: 0x00224F56 (jump)
  0x00224F6C  5e                      pop      esi                            
                                        ; XREF: 0x00224E03 (jump)
  0x00224F6D  8a4dfe                  mov      cl, byte ptr [ebp - 2]         
  0x00224F70  897b04                  mov      dword ptr [ebx + 4], edi       
  0x00224F73  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00224F79  8bc7                    mov      eax, edi                       
  0x00224F7B  5f                      pop      edi                            
  0x00224F7C  5b                      pop      ebx                            
  0x00224F7D  c9                      leave                                   
  0x00224F7E  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224F7F
; Start: 0x00224F7F  End: 0x00224FC3  Size: 68 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00222E49, sub_0022445D
; Called by: sub_00223032
; ============================================================
sub_00224F7F:
  0x00224F7F  53                      push     ebx                            
  0x00224F80  55                      push     ebp                            
  0x00224F81  56                      push     esi                            
  0x00224F82  8bf2                    mov      esi, edx                       
  0x00224F84  8b6e10                  mov      ebp, dword ptr [esi + 0x10]    
  0x00224F87  57                      push     edi                            
  0x00224F88  8bf9                    mov      edi, ecx                       
  0x00224F8A  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x00224F90  8bd5                    mov      edx, ebp                       
  0x00224F92  8bcf                    mov      ecx, edi                       
  0x00224F94  8ad8                    mov      bl, al                         
  0x00224F96  e8c2f4ffff              call     0x22445d                       ; -> sub_0022445D
  0x00224F9B  8bd5                    mov      edx, ebp                       
  0x00224F9D  8bcf                    mov      ecx, edi                       
  0x00224F9F  e8a5deffff              call     0x222e49                       ; -> sub_00222E49
  0x00224FA4  8d8734040000            lea      eax, [edi + 0x434]             
  0x00224FAA  8b08                    mov      ecx, dword ptr [eax]           
  0x00224FAC  894e14                  mov      dword ptr [esi + 0x14], ecx    
  0x00224FAF  8acb                    mov      cl, bl                         
  0x00224FB1  8930                    mov      dword ptr [eax], esi           
  0x00224FB3  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x00224FB9  5f                      pop      edi                            
  0x00224FBA  5e                      pop      esi                            
  0x00224FBB  5d                      pop      ebp                            
  0x00224FBC  b800000040              mov      eax, 0x40000000                
  0x00224FC1  5b                      pop      ebx                            
  0x00224FC2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00224FC3
; Start: 0x00224FC3  End: 0x0022504C  Size: 137 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002231A4
; Called by: sub_00224BD0
; ============================================================
sub_00224FC3:
  0x00224FC3  53                      push     ebx                            
  0x00224FC4  55                      push     ebp                            
  0x00224FC5  8bea                    mov      ebp, edx                       
  0x00224FC7  56                      push     esi                            
  0x00224FC8  8b7510                  mov      esi, dword ptr [ebp + 0x10]    
  0x00224FCB  8a4625                  mov      al, byte ptr [esi + 0x25]      
  0x00224FCE  0fb65e26                movzx    ebx, byte ptr [esi + 0x26]     
  0x00224FD2  0fb6c8                  movzx    ecx, al                        
  0x00224FD5  2bd9                    sub      ebx, ecx                       
  0x00224FD7  0fb64e24                movzx    ecx, byte ptr [esi + 0x24]     
  0x00224FDB  03d9                    add      ebx, ecx                       
  0x00224FDD  84c0                    test     al, al                         
  0x00224FDF  7444                    je       0x225025                       
  0x00224FE1  57                      push     edi                            
                                        ; XREF: 0x00225022 (cond_jump)
  0x00224FE2  0fb64e24                movzx    ecx, byte ptr [esi + 0x24]     
  0x00224FE6  8bc3                    mov      eax, ebx                       
  0x00224FE8  33d2                    xor      edx, edx                       
  0x00224FEA  f7f1                    div      ecx                            
  0x00224FEC  fe4e25                  dec      byte ptr [esi + 0x25]          
  0x00224FEF  6a01                    push     1                              
  0x00224FF1  8bda                    mov      ebx, edx                       
  0x00224FF3  8bfb                    mov      edi, ebx                       
  0x00224FF5  c1e706                  shl      edi, 6                         
  0x00224FF8  037e2c                  add      edi, dword ptr [esi + 0x2c]    
  0x00224FFB  43                      inc      ebx                            
  0x00224FFC  ff7704                  push     dword ptr [edi + 4]            
  0x00224FFF  ff15945b2200            call     dword ptr [0x225b94]           ; -> xbox_MmLockUnlockPhysicalPage
  0x00225005  8b470c                  mov      eax, dword ptr [edi + 0xc]     
  0x00225008  8b4f04                  mov      ecx, dword ptr [edi + 4]       
  0x0022500B  33c8                    xor      ecx, eax                       
  0x0022500D  f7c100f0ffff            test     ecx, 0xfffff000                
  0x00225013  7409                    je       0x22501e                       
  0x00225015  6a01                    push     1                              
  0x00225017  50                      push     eax                            
  0x00225018  ff15945b2200            call     dword ptr [0x225b94]           ; -> xbox_MmLockUnlockPhysicalPage
                                        ; XREF: 0x00225013 (cond_jump)
  0x0022501E  807e2500                cmp      byte ptr [esi + 0x25], 0       
  0x00225022  75be                    jne      0x224fe2                       
  0x00225024  5f                      pop      edi                            
                                        ; XREF: 0x00224FDF (cond_jump)
  0x00225025  0fb64624                movzx    eax, byte ptr [esi + 0x24]     
  0x00225029  fe4e25                  dec      byte ptr [esi + 0x25]          
  0x0022502C  c1e006                  shl      eax, 6                         
  0x0022502F  2bf0                    sub      esi, eax                       
  0x00225031  a1a8782800              mov      eax, dword ptr [0x2878a8]      
  0x00225036  8906                    mov      dword ptr [esi], eax           
  0x00225038  8935a8782800            mov      dword ptr [0x2878a8], esi      
  0x0022503E  83650400                and      dword ptr [ebp + 4], 0         
  0x00225042  55                      push     ebp                            
  0x00225043  e85ce1ffff              call     0x2231a4                       ; -> sub_002231A4
  0x00225048  5e                      pop      esi                            
  0x00225049  5d                      pop      ebp                            
  0x0022504A  5b                      pop      ebx                            
  0x0022504B  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022504C
; Start: 0x0022504C  End: 0x002251B3  Size: 359 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002231A4, sub_0022466C
; Called by: sub_00223032
; ============================================================
sub_0022504C:
  0x0022504C  55                      push     ebp                            
  0x0022504D  8bec                    mov      ebp, esp                       
  0x0022504F  83ec24                  sub      esp, 0x24                      
  0x00225052  8365ec00                and      dword ptr [ebp - 0x14], 0      
  0x00225056  56                      push     esi                            
  0x00225057  8bf2                    mov      esi, edx                       
  0x00225059  57                      push     edi                            
  0x0022505A  8b7e10                  mov      edi, dword ptr [esi + 0x10]    
  0x0022505D  8975f0                  mov      dword ptr [ebp - 0x10], esi    
  0x00225060  894ddc                  mov      dword ptr [ebp - 0x24], ecx    
  0x00225063  897de0                  mov      dword ptr [ebp - 0x20], edi    
  0x00225066  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x0022506C  8a4f24                  mov      cl, byte ptr [edi + 0x24]      
  0x0022506F  3a4f25                  cmp      cl, byte ptr [edi + 0x25]      
  0x00225072  8845ff                  mov      byte ptr [ebp - 1], al         
  0x00225075  750c                    jne      0x225083                       
  0x00225077  c745ec000d00c0          mov      dword ptr [ebp - 0x14], 0xc0000d00 
  0x0022507E  e915010000              jmp      0x225198                       
                                        ; XREF: 0x00225075 (cond_jump)
  0x00225083  0fb64726                movzx    eax, byte ptr [edi + 0x26]     
  0x00225087  53                      push     ebx                            
  0x00225088  8bd8                    mov      ebx, eax                       
  0x0022508A  c1e306                  shl      ebx, 6                         
  0x0022508D  035f2c                  add      ebx, dword ptr [edi + 0x2c]    
  0x00225090  40                      inc      eax                            
  0x00225091  99                      cdq                                     
  0x00225092  0fb6c9                  movzx    ecx, cl                        
  0x00225095  f7f9                    idiv     ecx                            
  0x00225097  8b7618                  mov      esi, dword ptr [esi + 0x18]    
  0x0022509A  8365f400                and      dword ptr [ebp - 0xc], 0       
  0x0022509E  8975e4                  mov      dword ptr [ebp - 0x1c], esi    
  0x002250A1  885726                  mov      byte ptr [edi + 0x26], dl      
  0x002250A4  8b4618                  mov      eax, dword ptr [esi + 0x18]    
  0x002250A7  894324                  mov      dword ptr [ebx + 0x24], eax    
  0x002250AA  8b461c                  mov      eax, dword ptr [esi + 0x1c]    
  0x002250AD  894328                  mov      dword ptr [ebx + 0x28], eax    
  0x002250B0  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x002250B3  897b20                  mov      dword ptr [ebx + 0x20], edi    
  0x002250B6  0fb64014                movzx    eax, byte ptr [eax + 0x14]     
  0x002250BA  c1e015                  shl      eax, 0x15                      
  0x002250BD  3303                    xor      eax, dword ptr [ebx]           
  0x002250BF  250000e000              and      eax, 0xe00000                  
  0x002250C4  3103                    xor      dword ptr [ebx], eax           
  0x002250C6  8b0e                    mov      ecx, dword ptr [esi]           
  0x002250C8  8b03                    mov      eax, dword ptr [ebx]           
  0x002250CA  49                      dec      ecx                            
  0x002250CB  c1e118                  shl      ecx, 0x18                      
  0x002250CE  33c8                    xor      ecx, eax                       
  0x002250D0  81e100000007            and      ecx, 0x7000000                 
  0x002250D6  33c8                    xor      ecx, eax                       
  0x002250D8  890b                    mov      dword ptr [ebx], ecx           
  0x002250DA  8b4604                  mov      eax, dword ptr [esi + 4]       
  0x002250DD  25ff0f0000              and      eax, 0xfff                     
  0x002250E2  833e00                  cmp      dword ptr [esi], 0             
  0x002250E5  8945e8                  mov      dword ptr [ebp - 0x18], eax    
  0x002250E8  762b                    jbe      0x225115                       
  0x002250EA  8d4e08                  lea      ecx, [esi + 8]                 
  0x002250ED  894df8                  mov      dword ptr [ebp - 8], ecx       
  0x002250F0  8d4b10                  lea      ecx, [ebx + 0x10]              
                                        ; XREF: 0x00225113 (cond_jump)
  0x002250F3  8bd0                    mov      edx, eax                       
  0x002250F5  6681ca00e0              or       dx, 0xe000                     
  0x002250FA  668911                  mov      word ptr [ecx], dx             
  0x002250FD  8b55f8                  mov      edx, dword ptr [ebp - 8]       
  0x00225100  0fb712                  movzx    edx, word ptr [edx]            
  0x00225103  8345f802                add      dword ptr [ebp - 8], 2         
  0x00225107  03c2                    add      eax, edx                       
  0x00225109  ff45f4                  inc      dword ptr [ebp - 0xc]          
  0x0022510C  8b55f4                  mov      edx, dword ptr [ebp - 0xc]     
  0x0022510F  41                      inc      ecx                            
  0x00225110  41                      inc      ecx                            
  0x00225111  3b16                    cmp      edx, dword ptr [esi]           
  0x00225113  72de                    jb       0x2250f3                       
                                        ; XREF: 0x002250E8 (cond_jump)
  0x00225115  2b45e8                  sub      eax, dword ptr [ebp - 0x18]    
  0x00225118  6a00                    push     0                              
  0x0022511A  50                      push     eax                            
  0x0022511B  ff7604                  push     dword ptr [esi + 4]            
  0x0022511E  8945e8                  mov      dword ptr [ebp - 0x18], eax    
  0x00225121  ff158c5b2200            call     dword ptr [0x225b8c]           ; -> xbox_MmLockUnlockBufferPages
  0x00225127  ff7604                  push     dword ptr [esi + 4]            
  0x0022512A  ff15885b2200            call     dword ptr [0x225b88]           ; -> xbox_MmGetPhysicalAddress
  0x00225130  8b4de8                  mov      ecx, dword ptr [ebp - 0x18]    
  0x00225133  894304                  mov      dword ptr [ebx + 4], eax       
  0x00225136  8b4604                  mov      eax, dword ptr [esi + 4]       
  0x00225139  8d4408ff                lea      eax, [eax + ecx - 1]           
  0x0022513D  50                      push     eax                            
  0x0022513E  ff15885b2200            call     dword ptr [0x225b88]           ; -> xbox_MmGetPhysicalAddress
  0x00225144  89430c                  mov      dword ptr [ebx + 0xc], eax     
  0x00225147  f6471001                test     byte ptr [edi + 0x10], 1       
  0x0022514B  7410                    je       0x22515d                       
  0x0022514D  8d7310                  lea      esi, [ebx + 0x10]              
  0x00225150  8d7b30                  lea      edi, [ebx + 0x30]              
  0x00225153  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00225154  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00225155  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00225156  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00225157  8b75e4                  mov      esi, dword ptr [ebp - 0x1c]    
  0x0022515A  8b7de0                  mov      edi, dword ptr [ebp - 0x20]    
                                        ; XREF: 0x0022514B (cond_jump)
  0x0022515D  f6471002                test     byte ptr [edi + 0x10], 2       
  0x00225161  7420                    je       0x225183                       
  0x00225163  8b4ddc                  mov      ecx, dword ptr [ebp - 0x24]    
  0x00225166  e801f5ffff              call     0x22466c                       ; -> sub_0022466C
  0x0022516B  8b4f28                  mov      ecx, dword ptr [edi + 0x28]    
  0x0022516E  40                      inc      eax                            
  0x0022516F  8bd1                    mov      edx, ecx                       
  0x00225171  2bd0                    sub      edx, eax                       
  0x00225173  85d2                    test     edx, edx                       
  0x00225175  7e02                    jle      0x225179                       
  0x00225177  8bc1                    mov      eax, ecx                       
                                        ; XREF: 0x00225175 (cond_jump)
  0x00225179  668903                  mov      word ptr [ebx], ax             
  0x0022517C  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022517E  03c8                    add      ecx, eax                       
  0x00225180  894f28                  mov      dword ptr [edi + 0x28], ecx    
                                        ; XREF: 0x00225161 (cond_jump)
  0x00225183  fe4725                  inc      byte ptr [edi + 0x25]          
  0x00225186  8a4725                  mov      al, byte ptr [edi + 0x25]      
  0x00225189  3a4724                  cmp      al, byte ptr [edi + 0x24]      
  0x0022518C  8b75f0                  mov      esi, dword ptr [ebp - 0x10]    
  0x0022518F  7406                    je       0x225197                       
  0x00225191  8b4308                  mov      eax, dword ptr [ebx + 8]       
  0x00225194  894704                  mov      dword ptr [edi + 4], eax       
                                        ; XREF: 0x0022518F (cond_jump)
  0x00225197  5b                      pop      ebx                            
                                        ; XREF: 0x0022507E (jump)
  0x00225198  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x0022519B  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x002251A1  8b7dec                  mov      edi, dword ptr [ebp - 0x14]    
  0x002251A4  56                      push     esi                            
  0x002251A5  897e04                  mov      dword ptr [esi + 4], edi       
  0x002251A8  e8f7dfffff              call     0x2231a4                       ; -> sub_002231A4
  0x002251AD  8bc7                    mov      eax, edi                       
  0x002251AF  5f                      pop      edi                            
  0x002251B0  5e                      pop      esi                            
  0x002251B1  c9                      leave                                   
  0x002251B2  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002251B3
; Start: 0x002251B3  End: 0x002252D2  Size: 287 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002231A4, sub_0022466C
; Called by: sub_00223032
; ============================================================
sub_002251B3:
  0x002251B3  55                      push     ebp                            
  0x002251B4  8bec                    mov      ebp, esp                       
  0x002251B6  83ec18                  sub      esp, 0x18                      
  0x002251B9  8365f000                and      dword ptr [ebp - 0x10], 0      
  0x002251BD  53                      push     ebx                            
  0x002251BE  8b1d305b2200            mov      ebx, dword ptr [0x225b30]      
  0x002251C4  56                      push     esi                            
  0x002251C5  57                      push     edi                            
  0x002251C6  8bfa                    mov      edi, edx                       
  0x002251C8  8b7710                  mov      esi, dword ptr [edi + 0x10]    
  0x002251CB  897df4                  mov      dword ptr [ebp - 0xc], edi     
  0x002251CE  894df8                  mov      dword ptr [ebp - 8], ecx       
  0x002251D1  ffd3                    call     ebx                            
  0x002251D3  f6461002                test     byte ptr [esi + 0x10], 2       
  0x002251D7  8845ff                  mov      byte ptr [ebp - 1], al         
  0x002251DA  740a                    je       0x2251e6                       
  0x002251DC  be000e00c0              mov      esi, 0xc0000e00                
  0x002251E1  e9cc000000              jmp      0x2252b2                       
                                        ; XREF: 0x002251DA (cond_jump)
  0x002251E6  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x002251E9  e87ef4ffff              call     0x22466c                       ; -> sub_0022466C
  0x002251EE  8a5610                  mov      dl, byte ptr [esi + 0x10]      
  0x002251F1  f6c204                  test     dl, 4                          
  0x002251F4  743a                    je       0x225230                       
  0x002251F6  80e2fb                  and      dl, 0xfb                       
  0x002251F9  39461c                  cmp      dword ptr [esi + 0x1c], eax    
  0x002251FC  885610                  mov      byte ptr [esi + 0x10], dl      
  0x002251FF  7527                    jne      0x225228                       
  0x00225201  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x00225204  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x0022520A  834decff                or       dword ptr [ebp - 0x14], 0xffffffff 
  0x0022520E  8d45e8                  lea      eax, [ebp - 0x18]              
  0x00225211  50                      push     eax                            
  0x00225212  6a00                    push     0                              
  0x00225214  6a00                    push     0                              
  0x00225216  c745e8f0d8ffff          mov      dword ptr [ebp - 0x18], 0xffffd8f0 
  0x0022521D  ff15fc5a2200            call     dword ptr [0x225afc]           ; -> xbox_KeDelayExecutionThread
  0x00225223  ffd3                    call     ebx                            
  0x00225225  8845ff                  mov      byte ptr [ebp - 1], al         
                                        ; XREF: 0x002251FF (cond_jump)
  0x00225228  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x0022522B  e83cf4ffff              call     0x22466c                       ; -> sub_0022466C
                                        ; XREF: 0x002251F4 (cond_jump)
  0x00225230  f6461001                test     byte ptr [esi + 0x10], 1       
  0x00225234  740f                    je       0x225245                       
  0x00225236  8a4e24                  mov      cl, byte ptr [esi + 0x24]      
  0x00225239  3a4e25                  cmp      cl, byte ptr [esi + 0x25]      
  0x0022523C  7407                    je       0x225245                       
  0x0022523E  be001000c0              mov      esi, 0xc0001000                
  0x00225243  eb6d                    jmp      0x2252b2                       
                                        ; XREF: 0x00225234 (cond_jump), 0x0022523C (cond_jump)
  0x00225245  f6471801                test     byte ptr [edi + 0x18], 1       
  0x00225249  8d4801                  lea      ecx, [eax + 1]                 
  0x0022524C  7512                    jne      0x225260                       
  0x0022524E  8b5714                  mov      edx, dword ptr [edi + 0x14]    
  0x00225251  8bc2                    mov      eax, edx                       
  0x00225253  2bc1                    sub      eax, ecx                       
  0x00225255  7874                    js       0x2252cb                       
  0x00225257  3d00040000              cmp      eax, 0x400                     
  0x0022525C  7f6d                    jg       0x2252cb                       
  0x0022525E  8bca                    mov      ecx, edx                       
                                        ; XREF: 0x0022524C (cond_jump)
  0x00225260  8a5624                  mov      dl, byte ptr [esi + 0x24]      
  0x00225263  8ac2                    mov      al, dl                         
  0x00225265  2a4625                  sub      al, byte ptr [esi + 0x25]      
  0x00225268  0fb6fa                  movzx    edi, dl                        
  0x0022526B  024626                  add      al, byte ptr [esi + 0x26]      
  0x0022526E  0fb6c0                  movzx    eax, al                        
  0x00225271  99                      cdq                                     
  0x00225272  f7ff                    idiv     edi                            
  0x00225274  8b7e2c                  mov      edi, dword ptr [esi + 0x2c]    
                                        ; XREF: 0x0022529F (cond_jump)
  0x00225277  0fb6d2                  movzx    edx, dl                        
  0x0022527A  8bc2                    mov      eax, edx                       
  0x0022527C  c1e006                  shl      eax, 6                         
  0x0022527F  66890c07                mov      word ptr [edi + eax], cx       
  0x00225283  8b7e2c                  mov      edi, dword ptr [esi + 0x2c]    
  0x00225286  0fb6440703              movzx    eax, byte ptr [edi + eax + 3]  
  0x0022528B  0fb65e24                movzx    ebx, byte ptr [esi + 0x24]     
  0x0022528F  83e007                  and      eax, 7                         
  0x00225292  8d4c0101                lea      ecx, [ecx + eax + 1]           
  0x00225296  8d4201                  lea      eax, [edx + 1]                 
  0x00225299  99                      cdq                                     
  0x0022529A  f7fb                    idiv     ebx                            
  0x0022529C  3a5626                  cmp      dl, byte ptr [esi + 0x26]      
  0x0022529F  75d6                    jne      0x225277                       
  0x002252A1  806601bf                and      byte ptr [esi + 1], 0xbf       
  0x002252A5  804e1002                or       byte ptr [esi + 0x10], 2       
  0x002252A9  8b7df4                  mov      edi, dword ptr [ebp - 0xc]     
  0x002252AC  894e28                  mov      dword ptr [esi + 0x28], ecx    
  0x002252AF  8b75f0                  mov      esi, dword ptr [ebp - 0x10]    
                                        ; XREF: 0x002251E1 (jump), 0x00225243 (jump), 0x002252D0 (jump)
  0x002252B2  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x002252B5  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x002252BB  57                      push     edi                            
  0x002252BC  897704                  mov      dword ptr [edi + 4], esi       
  0x002252BF  e8e0deffff              call     0x2231a4                       ; -> sub_002231A4
  0x002252C4  5f                      pop      edi                            
  0x002252C5  8bc6                    mov      eax, esi                       
  0x002252C7  5e                      pop      esi                            
  0x002252C8  5b                      pop      ebx                            
  0x002252C9  c9                      leave                                   
  0x002252CA  c3                      ret                                     
                                        ; XREF: 0x00225255 (cond_jump), 0x0022525C (cond_jump)
  0x002252CB  be000b00c0              mov      esi, 0xc0000b00                
  0x002252D0  ebe0                    jmp      0x2252b2                       
; end of function

; ============================================================
; Function: sub_002252D2
; Start: 0x002252D2  End: 0x0022532C  Size: 90 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002231A4, sub_0022466C
; Called by: sub_00223032
; ============================================================
sub_002252D2:
  0x002252D2  51                      push     ecx                            
  0x002252D3  53                      push     ebx                            
  0x002252D4  55                      push     ebp                            
  0x002252D5  56                      push     esi                            
  0x002252D6  57                      push     edi                            
  0x002252D7  8bfa                    mov      edi, edx                       
  0x002252D9  8b7710                  mov      esi, dword ptr [edi + 0x10]    
  0x002252DC  8bd9                    mov      ebx, ecx                       
  0x002252DE  33ed                    xor      ebp, ebp                       
  0x002252E0  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x002252E6  f6461002                test     byte ptr [esi + 0x10], 2       
  0x002252EA  88442413                mov      byte ptr [esp + 0x13], al      
  0x002252EE  741c                    je       0x22530c                       
  0x002252F0  804e0140                or       byte ptr [esi + 1], 0x40       
  0x002252F4  8bcb                    mov      ecx, ebx                       
  0x002252F6  e871f3ffff              call     0x22466c                       ; -> sub_0022466C
  0x002252FB  40                      inc      eax                            
  0x002252FC  40                      inc      eax                            
  0x002252FD  89461c                  mov      dword ptr [esi + 0x1c], eax    
  0x00225300  8a4610                  mov      al, byte ptr [esi + 0x10]      
  0x00225303  24fd                    and      al, 0xfd                       
  0x00225305  0c04                    or       al, 4                          
  0x00225307  884610                  mov      byte ptr [esi + 0x10], al      
  0x0022530A  eb05                    jmp      0x225311                       
                                        ; XREF: 0x002252EE (cond_jump)
  0x0022530C  bd000f00c0              mov      ebp, 0xc0000f00                
                                        ; XREF: 0x0022530A (jump)
  0x00225311  8a4c2413                mov      cl, byte ptr [esp + 0x13]      
  0x00225315  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x0022531B  57                      push     edi                            
  0x0022531C  896f04                  mov      dword ptr [edi + 4], ebp       
  0x0022531F  e880deffff              call     0x2231a4                       ; -> sub_002231A4
  0x00225324  5f                      pop      edi                            
  0x00225325  5e                      pop      esi                            
  0x00225326  8bc5                    mov      eax, ebp                       
  0x00225328  5d                      pop      ebp                            
  0x00225329  5b                      pop      ebx                            
  0x0022532A  59                      pop      ecx                            
  0x0022532B  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022532C
; Start: 0x0022532C  End: 0x0022541C  Size: 240 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022466C
; Called by: sub_00224CAA
; ============================================================
sub_0022532C:
  0x0022532C  55                      push     ebp                            
  0x0022532D  8bec                    mov      ebp, esp                       
  0x0022532F  83ec2c                  sub      esp, 0x2c                      
  0x00225332  53                      push     ebx                            
  0x00225333  8bda                    mov      ebx, edx                       
  0x00225335  8b03                    mov      eax, dword ptr [ebx]           
  0x00225337  56                      push     esi                            
  0x00225338  8b5320                  mov      edx, dword ptr [ebx + 0x20]    
  0x0022533B  83630800                and      dword ptr [ebx + 8], 0         
  0x0022533F  8bf0                    mov      esi, eax                       
  0x00225341  c1ee1c                  shr      esi, 0x1c                      
  0x00225344  8975d4                  mov      dword ptr [ebp - 0x2c], esi    
  0x00225347  c1e818                  shr      eax, 0x18                      
  0x0022534A  83e007                  and      eax, 7                         
  0x0022534D  57                      push     edi                            
  0x0022534E  40                      inc      eax                            
  0x0022534F  8945d8                  mov      dword ptr [ebp - 0x28], eax    
  0x00225352  8b4328                  mov      eax, dword ptr [ebx + 0x28]    
  0x00225355  8d7310                  lea      esi, [ebx + 0x10]              
  0x00225358  8975f8                  mov      dword ptr [ebp - 8], esi       
  0x0022535B  8d7ddc                  lea      edi, [ebp - 0x24]              
  0x0022535E  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x0022535F  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00225360  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00225361  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x00225364  8b4324                  mov      eax, dword ptr [ebx + 0x24]    
  0x00225367  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00225368  8b7a2c                  mov      edi, dword ptr [edx + 0x2c]    
  0x0022536B  8945ec                  mov      dword ptr [ebp - 0x14], eax    
  0x0022536E  0fb6432d                movzx    eax, byte ptr [ebx + 0x2d]     
  0x00225372  8bf3                    mov      esi, ebx                       
  0x00225374  2b3580782800            sub      esi, dword ptr [0x287880]      
  0x0022537A  c1e006                  shl      eax, 6                         
  0x0022537D  89743808                mov      dword ptr [eax + edi + 8], esi 
  0x00225381  f6421001                test     byte ptr [edx + 0x10], 1       
  0x00225385  8955fc                  mov      dword ptr [ebp - 4], edx       
  0x00225388  8975f4                  mov      dword ptr [ebp - 0xc], esi     
  0x0022538B  7446                    je       0x2253d3                       
  0x0022538D  e8daf2ffff              call     0x22466c                       ; -> sub_0022466C
  0x00225392  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x00225395  8bf0                    mov      esi, eax                       
  0x00225397  8b4128                  mov      eax, dword ptr [ecx + 0x28]    
  0x0022539A  46                      inc      esi                            
  0x0022539B  8bd0                    mov      edx, eax                       
  0x0022539D  2bd6                    sub      edx, esi                       
  0x0022539F  7802                    js       0x2253a3                       
  0x002253A1  8bf0                    mov      esi, eax                       
                                        ; XREF: 0x0022539F (cond_jump)
  0x002253A3  8b7df8                  mov      edi, dword ptr [ebp - 8]       
  0x002253A6  668933                  mov      word ptr [ebx], si             
  0x002253A9  33c0                    xor      eax, eax                       
  0x002253AB  8a4303                  mov      al, byte ptr [ebx + 3]         
  0x002253AE  83e007                  and      eax, 7                         
  0x002253B1  8d443001                lea      eax, [eax + esi + 1]           
  0x002253B5  894128                  mov      dword ptr [ecx + 0x28], eax    
  0x002253B8  8d7330                  lea      esi, [ebx + 0x30]              
  0x002253BB  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x002253BC  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x002253BD  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x002253BE  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x002253BF  0fb64126                movzx    eax, byte ptr [ecx + 0x26]     
  0x002253C3  0fb67124                movzx    esi, byte ptr [ecx + 0x24]     
  0x002253C7  40                      inc      eax                            
  0x002253C8  99                      cdq                                     
  0x002253C9  f7fe                    idiv     esi                            
  0x002253CB  8b75f4                  mov      esi, dword ptr [ebp - 0xc]     
  0x002253CE  885126                  mov      byte ptr [ecx + 0x26], dl      
  0x002253D1  eb37                    jmp      0x22540a                       
                                        ; XREF: 0x0022538B (cond_jump)
  0x002253D3  8b3d945b2200            mov      edi, dword ptr [0x225b94]      
  0x002253D9  6a01                    push     1                              
  0x002253DB  ff7304                  push     dword ptr [ebx + 4]            
  0x002253DE  ffd7                    call     edi                            
  0x002253E0  8b430c                  mov      eax, dword ptr [ebx + 0xc]     
  0x002253E3  8b4b04                  mov      ecx, dword ptr [ebx + 4]       
  0x002253E6  33c8                    xor      ecx, eax                       
  0x002253E8  f7c100f0ffff            test     ecx, 0xfffff000                
  0x002253EE  7405                    je       0x2253f5                       
  0x002253F0  6a01                    push     1                              
  0x002253F2  50                      push     eax                            
  0x002253F3  ffd7                    call     edi                            
                                        ; XREF: 0x002253EE (cond_jump)
  0x002253F5  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x002253F8  8a4125                  mov      al, byte ptr [ecx + 0x25]      
  0x002253FB  3a4124                  cmp      al, byte ptr [ecx + 0x24]      
  0x002253FE  0f94c2                  sete     dl                             
  0x00225401  fec8                    dec      al                             
  0x00225403  84d2                    test     dl, dl                         
  0x00225405  884125                  mov      byte ptr [ecx + 0x25], al      
  0x00225408  7403                    je       0x22540d                       
                                        ; XREF: 0x002253D1 (jump)
  0x0022540A  897104                  mov      dword ptr [ecx + 4], esi       
                                        ; XREF: 0x00225408 (cond_jump)
  0x0022540D  ff75f0                  push     dword ptr [ebp - 0x10]         
  0x00225410  8d45d4                  lea      eax, [ebp - 0x2c]              
  0x00225413  50                      push     eax                            
  0x00225414  ff55ec                  call     dword ptr [ebp - 0x14]         
  0x00225417  5f                      pop      edi                            
  0x00225418  5e                      pop      esi                            
  0x00225419  5b                      pop      ebx                            
  0x0022541A  c9                      leave                                   
  0x0022541B  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022541C
; Start: 0x0022541C  End: 0x0022543C  Size: 32 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_002254E6
; ============================================================
sub_0022541C:
  0x0022541C  a18c782800              mov      eax, dword ptr [0x28788c]      
  0x00225421  85c0                    test     eax, eax                       
  0x00225423  7409                    je       0x22542e                       
  0x00225425  8b4814                  mov      ecx, dword ptr [eax + 0x14]    
  0x00225428  890d8c782800            mov      dword ptr [0x28788c], ecx      
                                        ; XREF: 0x00225423 (cond_jump)
  0x0022542E  8a4c2404                mov      cl, byte ptr [esp + 4]         
  0x00225432  806002fe                and      byte ptr [eax + 2], 0xfe       
  0x00225436  88481f                  mov      byte ptr [eax + 0x1f], cl      
  0x00225439  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_0022543C
; Start: 0x0022543C  End: 0x0022545B  Size: 31 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00225884
; ============================================================
sub_0022543C:
  0x0022543C  668b442404              mov      ax, word ptr [esp + 4]         
  0x00225441  663905a2782800          cmp      word ptr [0x2878a2], ax        
  0x00225448  7304                    jae      0x22544e                       
  0x0022544A  33c0                    xor      eax, eax                       
  0x0022544C  eb0a                    jmp      0x225458                       
                                        ; XREF: 0x00225448 (cond_jump)
  0x0022544E  662905a2782800          sub      word ptr [0x2878a2], ax        
  0x00225455  33c0                    xor      eax, eax                       
  0x00225457  40                      inc      eax                            
                                        ; XREF: 0x0022544C (jump)
  0x00225458  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_0022545B
; Start: 0x0022545B  End: 0x0022547A  Size: 31 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_00225837
; ============================================================
sub_0022545B:
  0x0022545B  668b442404              mov      ax, word ptr [esp + 4]         
  0x00225460  663905a6782800          cmp      word ptr [0x2878a6], ax        
  0x00225467  7304                    jae      0x22546d                       
  0x00225469  33c0                    xor      eax, eax                       
  0x0022546B  eb0a                    jmp      0x225477                       
                                        ; XREF: 0x00225467 (cond_jump)
  0x0022546D  662905a6782800          sub      word ptr [0x2878a6], ax        
  0x00225474  33c0                    xor      eax, eax                       
  0x00225476  40                      inc      eax                            
                                        ; XREF: 0x0022546B (jump)
  0x00225477  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_0022547A
; Start: 0x0022547A  End: 0x002254AC  Size: 50 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_0022597C
; ============================================================
sub_0022547A:
  0x0022547A  57                      push     edi                            
  0x0022547B  8bfa                    mov      edi, edx                       
  0x0022547D  33d2                    xor      edx, edx                       
  0x0022547F  668b5702                mov      dx, word ptr [edi + 2]         
  0x00225483  33c0                    xor      eax, eax                       
  0x00225485  81e2ff070000            and      edx, 0x7ff                     
  0x0022548B  394114                  cmp      dword ptr [ecx + 0x14], eax    
  0x0022548E  7411                    je       0x2254a1                       
  0x00225490  8b4114                  mov      eax, dword ptr [ecx + 0x14]    
  0x00225493  56                      push     esi                            
  0x00225494  0fb7f2                  movzx    esi, dx                        
  0x00225497  33d2                    xor      edx, edx                       
  0x00225499  f7f6                    div      esi                            
  0x0022549B  5e                      pop      esi                            
  0x0022549C  85d2                    test     edx, edx                       
  0x0022549E  7401                    je       0x2254a1                       
  0x002254A0  40                      inc      eax                            
                                        ; XREF: 0x0022548E (cond_jump), 0x0022549E (cond_jump)
  0x002254A1  807f1100                cmp      byte ptr [edi + 0x11], 0       
  0x002254A5  5f                      pop      edi                            
  0x002254A6  7503                    jne      0x2254ab                       
  0x002254A8  83c003                  add      eax, 3                         
                                        ; XREF: 0x002254A6 (cond_jump)
  0x002254AB  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002254AC
; Start: 0x002254AC  End: 0x002254E6  Size: 58 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_002254E6
; ============================================================
sub_002254AC:
  0x002254AC  53                      push     ebx                            
  0x002254AD  56                      push     esi                            
  0x002254AE  57                      push     edi                            
  0x002254AF  8bf1                    mov      esi, ecx                       
  0x002254B1  ff36                    push     dword ptr [esi]                
  0x002254B3  8bfa                    mov      edi, edx                       
  0x002254B5  ff15885b2200            call     dword ptr [0x225b88]           ; -> xbox_MmGetPhysicalAddress
  0x002254BB  8b0e                    mov      ecx, dword ptr [esi]           
  0x002254BD  81e1ff0f0000            and      ecx, 0xfff                     
  0x002254C3  ba00100000              mov      edx, 0x1000                    
  0x002254C8  2bd1                    sub      edx, ecx                       
  0x002254CA  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x002254CE  8911                    mov      dword ptr [ecx], edx           
  0x002254D0  8b1f                    mov      ebx, dword ptr [edi]           
  0x002254D2  3bd3                    cmp      edx, ebx                       
  0x002254D4  7602                    jbe      0x2254d8                       
  0x002254D6  8919                    mov      dword ptr [ecx], ebx           
                                        ; XREF: 0x002254D4 (cond_jump)
  0x002254D8  8b11                    mov      edx, dword ptr [ecx]           
  0x002254DA  2917                    sub      dword ptr [edi], edx           
  0x002254DC  8b09                    mov      ecx, dword ptr [ecx]           
  0x002254DE  010e                    add      dword ptr [esi], ecx           
  0x002254E0  5f                      pop      edi                            
  0x002254E1  5e                      pop      esi                            
  0x002254E2  5b                      pop      ebx                            
  0x002254E3  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002254E6
; Start: 0x002254E6  End: 0x002257E4  Size: 766 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022541C, sub_002254AC
; Called by: sub_002257E4, sub_00225837, sub_00225884
; ============================================================
sub_002254E6:
  0x002254E6  55                      push     ebp                            
  0x002254E7  8bec                    mov      ebp, esp                       
  0x002254E9  83ec28                  sub      esp, 0x28                      
  0x002254EC  33c0                    xor      eax, eax                       
  0x002254EE  53                      push     ebx                            
  0x002254EF  8bda                    mov      ebx, edx                       
  0x002254F1  668b4302                mov      ax, word ptr [ebx + 2]         
  0x002254F5  56                      push     esi                            
  0x002254F6  57                      push     edi                            
  0x002254F7  8b7d08                  mov      edi, dword ptr [ebp + 8]       
  0x002254FA  894de0                  mov      dword ptr [ebp - 0x20], ecx    
  0x002254FD  8a895c040000            mov      cl, byte ptr [ecx + 0x45c]     
  0x00225503  884de8                  mov      byte ptr [ebp - 0x18], cl      
  0x00225506  25ff070000              and      eax, 0x7ff                     
  0x0022550B  8945d8                  mov      dword ptr [ebp - 0x28], eax    
  0x0022550E  8b4714                  mov      eax, dword ptr [edi + 0x14]    
  0x00225511  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x00225514  33c0                    xor      eax, eax                       
  0x00225516  fe4b26                  dec      byte ptr [ebx + 0x26]          
  0x00225519  fe4327                  inc      byte ptr [ebx + 0x27]          
  0x0022551C  668b4f22                mov      cx, word ptr [edi + 0x22]      
  0x00225520  6681e1fdff              and      cx, 0xfffd                     
  0x00225525  6683c904                or       cx, 4                          
  0x00225529  66894f22                mov      word ptr [edi + 0x22], cx      
  0x0022552D  8b7304                  mov      esi, dword ptr [ebx + 4]       
  0x00225530  3bf0                    cmp      esi, eax                       
  0x00225532  8945ec                  mov      dword ptr [ebp - 0x14], eax    
  0x00225535  88450b                  mov      byte ptr [ebp + 0xb], al       
  0x00225538  8945e4                  mov      dword ptr [ebp - 0x1c], eax    
  0x0022553B  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x0022553E  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x00225541  7409                    je       0x22554c                       
  0x00225543  a180782800              mov      eax, dword ptr [0x287880]      
  0x00225548  03f0                    add      esi, eax                       
  0x0022554A  eb19                    jmp      0x225565                       
                                        ; XREF: 0x00225541 (cond_jump)
  0x0022554C  ff75e8                  push     dword ptr [ebp - 0x18]         
  0x0022554F  e8c8feffff              call     0x22541c                       ; -> sub_0022541C
  0x00225554  8bf0                    mov      esi, eax                       
  0x00225556  8b4610                  mov      eax, dword ptr [esi + 0x10]    
  0x00225559  334308                  xor      eax, dword ptr [ebx + 8]       
  0x0022555C  83e00f                  and      eax, 0xf                       
  0x0022555F  334610                  xor      eax, dword ptr [esi + 0x10]    
  0x00225562  894308                  mov      dword ptr [ebx + 8], eax       
                                        ; XREF: 0x0022554A (jump)
  0x00225565  807b1100                cmp      byte ptr [ebx + 0x11], 0       
  0x00225569  8975fc                  mov      dword ptr [ebp - 4], esi       
  0x0022556C  7566                    jne      0x2255d4                       
  0x0022556E  33c0                    xor      eax, eax                       
  0x00225570  b0fe                    mov      al, 0xfe                       
  0x00225572  2a45e8                  sub      al, byte ptr [ebp - 0x18]      
  0x00225575  50                      push     eax                            
  0x00225576  e8a1feffff              call     0x22541c                       ; -> sub_0022541C
  0x0022557B  8b4f28                  mov      ecx, dword ptr [edi + 0x28]    
  0x0022557E  ff75e8                  push     dword ptr [ebp - 0x18]         
  0x00225581  8908                    mov      dword ptr [eax], ecx           
  0x00225583  8b4f2c                  mov      ecx, dword ptr [edi + 0x2c]    
  0x00225586  8945dc                  mov      dword ptr [ebp - 0x24], eax    
  0x00225589  894804                  mov      dword ptr [eax + 4], ecx       
  0x0022558C  e88bfeffff              call     0x22541c                       ; -> sub_0022541C
  0x00225591  8bf0                    mov      esi, eax                       
  0x00225593  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x00225596  8b08                    mov      ecx, dword ptr [eax]           
  0x00225598  81e1ffff0300            and      ecx, 0x3ffff                   
  0x0022559E  81c90000e0e2            or       ecx, 0xe2e00000                
  0x002255A4  8908                    mov      dword ptr [eax], ecx           
  0x002255A6  8b4ddc                  mov      ecx, dword ptr [ebp - 0x24]    
  0x002255A9  8b5110                  mov      edx, dword ptr [ecx + 0x10]    
  0x002255AC  895004                  mov      dword ptr [eax + 4], edx       
  0x002255AF  8b5610                  mov      edx, dword ptr [esi + 0x10]    
  0x002255B2  895008                  mov      dword ptr [eax + 8], edx       
  0x002255B5  8b4910                  mov      ecx, dword ptr [ecx + 0x10]    
  0x002255B8  83c107                  add      ecx, 7                         
  0x002255BB  c6450b02                mov      byte ptr [ebp + 0xb], 2        
  0x002255BF  89480c                  mov      dword ptr [eax + 0xc], ecx     
  0x002255C2  895814                  mov      dword ptr [eax + 0x14], ebx    
  0x002255C5  c6401c00                mov      byte ptr [eax + 0x1c], 0       
  0x002255C9  c6401e01                mov      byte ptr [eax + 0x1e], 1       
  0x002255CD  c6401d00                mov      byte ptr [eax + 0x1d], 0       
  0x002255D1  897818                  mov      dword ptr [eax + 0x18], edi    
                                        ; XREF: 0x0022556C (cond_jump)
  0x002255D4  837df000                cmp      dword ptr [ebp - 0x10], 0      
  0x002255D8  7416                    je       0x2255f0                       
  0x002255DA  6a00                    push     0                              
  0x002255DC  ff75f0                  push     dword ptr [ebp - 0x10]         
  0x002255DF  ff7718                  push     dword ptr [edi + 0x18]         
  0x002255E2  ff158c5b2200            call     dword ptr [0x225b8c]           ; -> xbox_MmLockUnlockBufferPages
  0x002255E8  8b4718                  mov      eax, dword ptr [edi + 0x18]    
  0x002255EB  8945dc                  mov      dword ptr [ebp - 0x24], eax    
  0x002255EE  eb04                    jmp      0x2255f4                       
                                        ; XREF: 0x002255D8 (cond_jump)
  0x002255F0  c6471c01                mov      byte ptr [edi + 0x1c], 1       
                                        ; XREF: 0x002255EE (jump)
  0x002255F4  837df000                cmp      dword ptr [ebp - 0x10], 0      
  0x002255F8  0f8411010000            je       0x22570f                       
                                        ; XREF: 0x002256F6 (cond_jump)
  0x002255FE  8d45ec                  lea      eax, [ebp - 0x14]              
  0x00225601  50                      push     eax                            
  0x00225602  8d55f0                  lea      edx, [ebp - 0x10]              
  0x00225605  8d4ddc                  lea      ecx, [ebp - 0x24]              
  0x00225608  e89ffeffff              call     0x2254ac                       ; -> sub_002254AC
  0x0022560D  8945fc                  mov      dword ptr [ebp - 4], eax       
                                        ; XREF: 0x002256E4 (jump)
  0x00225610  8b55ec                  mov      edx, dword ptr [ebp - 0x14]    
  0x00225613  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x00225616  8b4dd8                  mov      ecx, dword ptr [ebp - 0x28]    
  0x00225619  03c2                    add      eax, edx                       
  0x0022561B  3bc1                    cmp      eax, ecx                       
  0x0022561D  7312                    jae      0x225631                       
  0x0022561F  85d2                    test     edx, edx                       
  0x00225621  0f84c2000000            je       0x2256e9                       
  0x00225627  837df000                cmp      dword ptr [ebp - 0x10], 0      
  0x0022562B  0f85b8000000            jne      0x2256e9                       
                                        ; XREF: 0x0022561D (cond_jump)
  0x00225631  837df400                cmp      dword ptr [ebp - 0xc], 0       
  0x00225635  7422                    je       0x225659                       
  0x00225637  2b4df4                  sub      ecx, dword ptr [ebp - 0xc]     
  0x0022563A  8b45e4                  mov      eax, dword ptr [ebp - 0x1c]    
  0x0022563D  3bd1                    cmp      edx, ecx                       
  0x0022563F  894604                  mov      dword ptr [esi + 4], eax       
  0x00225642  7302                    jae      0x225646                       
  0x00225644  8bca                    mov      ecx, edx                       
                                        ; XREF: 0x00225642 (cond_jump)
  0x00225646  8a45f4                  mov      al, byte ptr [ebp - 0xc]       
  0x00225649  014dfc                  add      dword ptr [ebp - 4], ecx       
  0x0022564C  02c1                    add      al, cl                         
  0x0022564E  2bd1                    sub      edx, ecx                       
  0x00225650  8365f400                and      dword ptr [ebp - 0xc], 0       
  0x00225654  88461d                  mov      byte ptr [esi + 0x1d], al      
  0x00225657  eb1e                    jmp      0x225677                       
                                        ; XREF: 0x00225635 (cond_jump)
  0x00225659  3bd1                    cmp      edx, ecx                       
  0x0022565B  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x0022565E  894604                  mov      dword ptr [esi + 4], eax       
  0x00225661  730c                    jae      0x22566f                       
  0x00225663  0155fc                  add      dword ptr [ebp - 4], edx       
  0x00225666  8365ec00                and      dword ptr [ebp - 0x14], 0      
  0x0022566A  88561d                  mov      byte ptr [esi + 0x1d], dl      
  0x0022566D  eb0b                    jmp      0x22567a                       
                                        ; XREF: 0x00225661 (cond_jump)
  0x0022566F  014dfc                  add      dword ptr [ebp - 4], ecx       
  0x00225672  884e1d                  mov      byte ptr [esi + 0x1d], cl      
  0x00225675  2bd1                    sub      edx, ecx                       
                                        ; XREF: 0x00225657 (jump)
  0x00225677  8955ec                  mov      dword ptr [ebp - 0x14], edx    
                                        ; XREF: 0x0022566D (jump)
  0x0022567A  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x0022567D  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022567F  80750b01                xor      byte ptr [ebp + 0xb], 1        
  0x00225683  48                      dec      eax                            
  0x00225684  89460c                  mov      dword ptr [esi + 0xc], eax     
  0x00225687  0fb6450b                movzx    eax, byte ptr [ebp + 0xb]      
  0x0022568B  ff75e8                  push     dword ptr [ebp - 0x18]         
  0x0022568E  81e1fffffb0f            and      ecx, 0xffbffff                 
  0x00225694  81c9000000e0            or       ecx, 0xe0000000                
  0x0022569A  c1e018                  shl      eax, 0x18                      
  0x0022569D  33c1                    xor      eax, ecx                       
  0x0022569F  2500000003              and      eax, 0x3000000                 
  0x002256A4  33c1                    xor      eax, ecx                       
  0x002256A6  890e                    mov      dword ptr [esi], ecx           
  0x002256A8  0d0000e000              or       eax, 0xe00000                  
  0x002256AD  33c9                    xor      ecx, ecx                       
  0x002256AF  8906                    mov      dword ptr [esi], eax           
  0x002256B1  895e14                  mov      dword ptr [esi + 0x14], ebx    
  0x002256B4  c6461c00                mov      byte ptr [esi + 0x1c], 0       
  0x002256B8  c6461e00                mov      byte ptr [esi + 0x1e], 0       
  0x002256BC  8a4f1c                  mov      cl, byte ptr [edi + 0x1c]      
  0x002256BF  25ffffe7f3              and      eax, 0xf3e7ffff                
  0x002256C4  897e18                  mov      dword ptr [esi + 0x18], edi    
  0x002256C7  8975f8                  mov      dword ptr [ebp - 8], esi       
  0x002256CA  83e103                  and      ecx, 3                         
  0x002256CD  c1e113                  shl      ecx, 0x13                      
  0x002256D0  0bc8                    or       ecx, eax                       
  0x002256D2  890e                    mov      dword ptr [esi], ecx           
  0x002256D4  e843fdffff              call     0x22541c                       ; -> sub_0022541C
  0x002256D9  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x002256DC  8bf0                    mov      esi, eax                       
  0x002256DE  8b4610                  mov      eax, dword ptr [esi + 0x10]    
  0x002256E1  894108                  mov      dword ptr [ecx + 8], eax       
  0x002256E4  e927ffffff              jmp      0x225610                       
                                        ; XREF: 0x00225621 (cond_jump), 0x0022562B (cond_jump)
  0x002256E9  837df000                cmp      dword ptr [ebp - 0x10], 0      
  0x002256ED  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x002256F0  8945e4                  mov      dword ptr [ebp - 0x1c], eax    
  0x002256F3  8955f4                  mov      dword ptr [ebp - 0xc], edx     
  0x002256F6  0f8502ffffff            jne      0x2255fe                       
  0x002256FC  837df800                cmp      dword ptr [ebp - 8], 0         
  0x00225700  740d                    je       0x22570f                       
  0x00225702  807f1d00                cmp      byte ptr [edi + 0x1d], 0       
  0x00225706  7407                    je       0x22570f                       
  0x00225708  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x0022570B  80480204                or       byte ptr [eax + 2], 4          
                                        ; XREF: 0x002255F8 (cond_jump), 0x00225700 (cond_jump), 0x00225706 (cond_jump)
  0x0022570F  807b1100                cmp      byte ptr [ebx + 0x11], 0       
  0x00225713  756a                    jne      0x22577f                       
  0x00225715  806602fb                and      byte ptr [esi + 2], 0xfb       
  0x00225719  8b0e                    mov      ecx, dword ptr [esi]           
  0x0022571B  33c0                    xor      eax, eax                       
  0x0022571D  807f1c02                cmp      byte ptr [edi + 0x1c], 2       
  0x00225721  ff75e8                  push     dword ptr [ebp - 0x18]         
  0x00225724  0f95c0                  setne    al                             
  0x00225727  8975f8                  mov      dword ptr [ebp - 8], esi       
  0x0022572A  40                      inc      eax                            
  0x0022572B  c1e013                  shl      eax, 0x13                      
  0x0022572E  33c1                    xor      eax, ecx                       
  0x00225730  2500001800              and      eax, 0x180000                  
  0x00225735  33c1                    xor      eax, ecx                       
  0x00225737  33c9                    xor      ecx, ecx                       
  0x00225739  8906                    mov      dword ptr [esi], eax           
  0x0022573B  8a4f1e                  mov      cl, byte ptr [edi + 0x1e]      
  0x0022573E  83660400                and      dword ptr [esi + 4], 0         
  0x00225742  83660c00                and      dword ptr [esi + 0xc], 0       
  0x00225746  25ffff1f00              and      eax, 0x1fffff                  
  0x0022574B  895e14                  mov      dword ptr [esi + 0x14], ebx    
  0x0022574E  c6461c02                mov      byte ptr [esi + 0x1c], 2       
  0x00225752  c6461e02                mov      byte ptr [esi + 0x1e], 2       
  0x00225756  83e107                  and      ecx, 7                         
  0x00225759  81c918ffffff            or       ecx, 0xffffff18                
  0x0022575F  c1e115                  shl      ecx, 0x15                      
  0x00225762  0bc8                    or       ecx, eax                       
  0x00225764  890e                    mov      dword ptr [esi], ecx           
  0x00225766  897e18                  mov      dword ptr [esi + 0x18], edi    
  0x00225769  c6461d00                mov      byte ptr [esi + 0x1d], 0       
  0x0022576D  e8aafcffff              call     0x22541c                       ; -> sub_0022541C
  0x00225772  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x00225775  8bf0                    mov      esi, eax                       
  0x00225777  8b4610                  mov      eax, dword ptr [esi + 0x10]    
  0x0022577A  894108                  mov      dword ptr [ecx + 8], eax       
  0x0022577D  eb18                    jmp      0x225797                       
                                        ; XREF: 0x00225713 (cond_jump)
  0x0022577F  0fb64f1e                movzx    ecx, byte ptr [edi + 0x1e]     
  0x00225783  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x00225786  c1e115                  shl      ecx, 0x15                      
  0x00225789  3308                    xor      ecx, dword ptr [eax]           
  0x0022578B  c6401c02                mov      byte ptr [eax + 0x1c], 2       
  0x0022578F  81e10000e000            and      ecx, 0xe00000                  
  0x00225795  3108                    xor      dword ptr [eax], ecx           
                                        ; XREF: 0x0022577D (jump)
  0x00225797  c6461e03                mov      byte ptr [esi + 0x1e], 3       
  0x0022579B  668b4714                mov      ax, word ptr [edi + 0x14]      
  0x0022579F  83671400                and      dword ptr [edi + 0x14], 0      
  0x002257A3  66894720                mov      word ptr [edi + 0x20], ax      
  0x002257A7  807b2000                cmp      byte ptr [ebx + 0x20], 0       
  0x002257AB  8b4610                  mov      eax, dword ptr [esi + 0x10]    
  0x002257AE  894304                  mov      dword ptr [ebx + 4], eax       
  0x002257B1  7504                    jne      0x2257b7                       
  0x002257B3  806301bf                and      byte ptr [ebx + 1], 0xbf       
                                        ; XREF: 0x002257B1 (cond_jump)
  0x002257B7  8a5b11                  mov      bl, byte ptr [ebx + 0x11]      
  0x002257BA  84db                    test     bl, bl                         
  0x002257BC  750e                    jne      0x2257cc                       
  0x002257BE  8b45e0                  mov      eax, dword ptr [ebp - 0x20]    
  0x002257C1  8b00                    mov      eax, dword ptr [eax]           
  0x002257C3  c7400802000000          mov      dword ptr [eax + 8], 2         
  0x002257CA  eb11                    jmp      0x2257dd                       
                                        ; XREF: 0x002257BC (cond_jump)
  0x002257CC  80fb02                  cmp      bl, 2                          
  0x002257CF  750c                    jne      0x2257dd                       
  0x002257D1  8b45e0                  mov      eax, dword ptr [ebp - 0x20]    
  0x002257D4  8b00                    mov      eax, dword ptr [eax]           
  0x002257D6  c7400804000000          mov      dword ptr [eax + 8], 4         
                                        ; XREF: 0x002257CA (jump), 0x002257CF (cond_jump)
  0x002257DD  5f                      pop      edi                            
  0x002257DE  5e                      pop      esi                            
  0x002257DF  5b                      pop      ebx                            
  0x002257E0  c9                      leave                                   
  0x002257E1  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_002257E4
; Start: 0x002257E4  End: 0x00225837  Size: 83 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_002254E6
; Called by: sub_002258D1
; ============================================================
sub_002257E4:
  0x002257E4  55                      push     ebp                            
  0x002257E5  8bec                    mov      ebp, esp                       
  0x002257E7  51                      push     ecx                            
  0x002257E8  56                      push     esi                            
  0x002257E9  8bf2                    mov      esi, edx                       
  0x002257EB  837e2800                cmp      dword ptr [esi + 0x28], 0      
  0x002257EF  894dfc                  mov      dword ptr [ebp - 4], ecx       
  0x002257F2  7440                    je       0x225834                       
  0x002257F4  53                      push     ebx                            
                                        ; XREF: 0x00225831 (cond_jump)
  0x002257F5  8b4628                  mov      eax, dword ptr [esi + 0x28]    
  0x002257F8  668b5624                mov      dx, word ptr [esi + 0x24]      
  0x002257FC  0fb75820                movzx    ebx, word ptr [eax + 0x20]     
  0x00225800  0fb7ca                  movzx    ecx, dx                        
  0x00225803  03cb                    add      ecx, ebx                       
  0x00225805  83f903                  cmp      ecx, 3                         
  0x00225808  7f29                    jg       0x225833                       
  0x0022580A  8b4824                  mov      ecx, dword ptr [eax + 0x24]    
  0x0022580D  85c9                    test     ecx, ecx                       
  0x0022580F  894e28                  mov      dword ptr [esi + 0x28], ecx    
  0x00225812  7503                    jne      0x225817                       
  0x00225814  214e2c                  and      dword ptr [esi + 0x2c], ecx    
                                        ; XREF: 0x00225812 (cond_jump)
  0x00225817  668b4820                mov      cx, word ptr [eax + 0x20]      
  0x0022581B  6603ca                  add      cx, dx                         
  0x0022581E  66894e24                mov      word ptr [esi + 0x24], cx      
  0x00225822  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x00225825  50                      push     eax                            
  0x00225826  8bd6                    mov      edx, esi                       
  0x00225828  e8b9fcffff              call     0x2254e6                       ; -> sub_002254E6
  0x0022582D  837e2800                cmp      dword ptr [esi + 0x28], 0      
  0x00225831  75c2                    jne      0x2257f5                       
                                        ; XREF: 0x00225808 (cond_jump)
  0x00225833  5b                      pop      ebx                            
                                        ; XREF: 0x002257F2 (cond_jump)
  0x00225834  5e                      pop      esi                            
  0x00225835  c9                      leave                                   
  0x00225836  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00225837
; Start: 0x00225837  End: 0x00225884  Size: 77 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022545B, sub_002254E6
; Called by: sub_00225904
; ============================================================
sub_00225837:
  0x00225837  56                      push     esi                            
  0x00225838  8bf1                    mov      esi, ecx                       
  0x0022583A  83be2404000000          cmp      dword ptr [esi + 0x424], 0     
  0x00225841  743f                    je       0x225882                       
  0x00225843  57                      push     edi                            
                                        ; XREF: 0x0022587F (cond_jump)
  0x00225844  8bbe24040000            mov      edi, dword ptr [esi + 0x424]   
  0x0022584A  33c0                    xor      eax, eax                       
  0x0022584C  668b4720                mov      ax, word ptr [edi + 0x20]      
  0x00225850  50                      push     eax                            
  0x00225851  e805fcffff              call     0x22545b                       ; -> sub_0022545B
  0x00225856  84c0                    test     al, al                         
  0x00225858  7427                    je       0x225881                       
  0x0022585A  8b4724                  mov      eax, dword ptr [edi + 0x24]    
  0x0022585D  85c0                    test     eax, eax                       
  0x0022585F  898624040000            mov      dword ptr [esi + 0x424], eax   
  0x00225865  7506                    jne      0x22586d                       
  0x00225867  218628040000            and      dword ptr [esi + 0x428], eax   
                                        ; XREF: 0x00225865 (cond_jump)
  0x0022586D  8b5710                  mov      edx, dword ptr [edi + 0x10]    
  0x00225870  57                      push     edi                            
  0x00225871  8bce                    mov      ecx, esi                       
  0x00225873  e86efcffff              call     0x2254e6                       ; -> sub_002254E6
  0x00225878  83be2404000000          cmp      dword ptr [esi + 0x424], 0     
  0x0022587F  75c3                    jne      0x225844                       
                                        ; XREF: 0x00225858 (cond_jump)
  0x00225881  5f                      pop      edi                            
                                        ; XREF: 0x00225841 (cond_jump)
  0x00225882  5e                      pop      esi                            
  0x00225883  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00225884
; Start: 0x00225884  End: 0x002258D1  Size: 77 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_0022543C, sub_002254E6
; Called by: sub_00225940
; ============================================================
sub_00225884:
  0x00225884  56                      push     esi                            
  0x00225885  8bf1                    mov      esi, ecx                       
  0x00225887  83be1c04000000          cmp      dword ptr [esi + 0x41c], 0     
  0x0022588E  743f                    je       0x2258cf                       
  0x00225890  57                      push     edi                            
                                        ; XREF: 0x002258CC (cond_jump)
  0x00225891  8bbe1c040000            mov      edi, dword ptr [esi + 0x41c]   
  0x00225897  33c0                    xor      eax, eax                       
  0x00225899  668b4720                mov      ax, word ptr [edi + 0x20]      
  0x0022589D  50                      push     eax                            
  0x0022589E  e899fbffff              call     0x22543c                       ; -> sub_0022543C
  0x002258A3  84c0                    test     al, al                         
  0x002258A5  7427                    je       0x2258ce                       
  0x002258A7  8b4724                  mov      eax, dword ptr [edi + 0x24]    
  0x002258AA  85c0                    test     eax, eax                       
  0x002258AC  89861c040000            mov      dword ptr [esi + 0x41c], eax   
  0x002258B2  7506                    jne      0x2258ba                       
  0x002258B4  218620040000            and      dword ptr [esi + 0x420], eax   
                                        ; XREF: 0x002258B2 (cond_jump)
  0x002258BA  8b5710                  mov      edx, dword ptr [edi + 0x10]    
  0x002258BD  57                      push     edi                            
  0x002258BE  8bce                    mov      ecx, esi                       
  0x002258C0  e821fcffff              call     0x2254e6                       ; -> sub_002254E6
  0x002258C5  83be1c04000000          cmp      dword ptr [esi + 0x41c], 0     
  0x002258CC  75c3                    jne      0x225891                       
                                        ; XREF: 0x002258A5 (cond_jump)
  0x002258CE  5f                      pop      edi                            
                                        ; XREF: 0x0022588E (cond_jump)
  0x002258CF  5e                      pop      esi                            
  0x002258D0  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_002258D1
; Start: 0x002258D1  End: 0x00225904  Size: 51 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_002257E4
; Called by: sub_0022597C
; ============================================================
sub_002258D1:
  0x002258D1  8b442404                mov      eax, dword ptr [esp + 4]       
  0x002258D5  6683782003              cmp      word ptr [eax + 0x20], 3       
  0x002258DA  7607                    jbe      0x2258e3                       
  0x002258DC  b800050080              mov      eax, 0x80000500                
  0x002258E1  eb1e                    jmp      0x225901                       
                                        ; XREF: 0x002258DA (cond_jump)
  0x002258E3  56                      push     esi                            
  0x002258E4  8b722c                  mov      esi, dword ptr [edx + 0x2c]    
  0x002258E7  85f6                    test     esi, esi                       
  0x002258E9  7405                    je       0x2258f0                       
  0x002258EB  894624                  mov      dword ptr [esi + 0x24], eax    
  0x002258EE  eb03                    jmp      0x2258f3                       
                                        ; XREF: 0x002258E9 (cond_jump)
  0x002258F0  894228                  mov      dword ptr [edx + 0x28], eax    
                                        ; XREF: 0x002258EE (jump)
  0x002258F3  89422c                  mov      dword ptr [edx + 0x2c], eax    
  0x002258F6  e8e9feffff              call     0x2257e4                       ; -> sub_002257E4
  0x002258FB  b800000040              mov      eax, 0x40000000                
  0x00225900  5e                      pop      esi                            
                                        ; XREF: 0x002258E1 (jump)
  0x00225901  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_00225904
; Start: 0x00225904  End: 0x00225940  Size: 60 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00225837
; Called by: sub_0022597C
; ============================================================
sub_00225904:
  0x00225904  668b4220                mov      ax, word ptr [edx + 0x20]      
  0x00225908  663b05a4782800          cmp      ax, word ptr [0x2878a4]        
  0x0022590F  7606                    jbe      0x225917                       
  0x00225911  b800050080              mov      eax, 0x80000500                
  0x00225916  c3                      ret                                     
                                        ; XREF: 0x0022590F (cond_jump)
  0x00225917  8d8124040000            lea      eax, [ecx + 0x424]             
  0x0022591D  833800                  cmp      dword ptr [eax], 0             
  0x00225920  740b                    je       0x22592d                       
  0x00225922  8b8128040000            mov      eax, dword ptr [ecx + 0x428]   
  0x00225928  895024                  mov      dword ptr [eax + 0x24], edx    
  0x0022592B  eb02                    jmp      0x22592f                       
                                        ; XREF: 0x00225920 (cond_jump)
  0x0022592D  8910                    mov      dword ptr [eax], edx           
                                        ; XREF: 0x0022592B (jump)
  0x0022592F  899128040000            mov      dword ptr [ecx + 0x428], edx   
  0x00225935  e8fdfeffff              call     0x225837                       ; -> sub_00225837
  0x0022593A  b800000040              mov      eax, 0x40000000                
  0x0022593F  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_00225940
; Start: 0x00225940  End: 0x0022597C  Size: 60 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00225884
; Called by: sub_0022597C
; ============================================================
sub_00225940:
  0x00225940  668b4220                mov      ax, word ptr [edx + 0x20]      
  0x00225944  663b05a0782800          cmp      ax, word ptr [0x2878a0]        
  0x0022594B  7606                    jbe      0x225953                       
  0x0022594D  b800050080              mov      eax, 0x80000500                
  0x00225952  c3                      ret                                     
                                        ; XREF: 0x0022594B (cond_jump)
  0x00225953  8d811c040000            lea      eax, [ecx + 0x41c]             
  0x00225959  833800                  cmp      dword ptr [eax], 0             
  0x0022595C  740b                    je       0x225969                       
  0x0022595E  8b8120040000            mov      eax, dword ptr [ecx + 0x420]   
  0x00225964  895024                  mov      dword ptr [eax + 0x24], edx    
  0x00225967  eb02                    jmp      0x22596b                       
                                        ; XREF: 0x0022595C (cond_jump)
  0x00225969  8910                    mov      dword ptr [eax], edx           
                                        ; XREF: 0x00225967 (jump)
  0x0022596B  899120040000            mov      dword ptr [ecx + 0x420], edx   
  0x00225971  e80effffff              call     0x225884                       ; -> sub_00225884
  0x00225976  b800000040              mov      eax, 0x40000000                
  0x0022597B  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_0022597C
; Start: 0x0022597C  End: 0x00225A02  Size: 134 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_0022547A, sub_002258D1, sub_00225904, sub_00225940
; Called by: sub_00223032
; ============================================================
sub_0022597C:
  0x0022597C  55                      push     ebp                            
  0x0022597D  8bec                    mov      ebp, esp                       
  0x0022597F  51                      push     ecx                            
  0x00225980  53                      push     ebx                            
  0x00225981  56                      push     esi                            
  0x00225982  8bf2                    mov      esi, edx                       
  0x00225984  57                      push     edi                            
  0x00225985  8b7e10                  mov      edi, dword ptr [esi + 0x10]    
  0x00225988  8bd9                    mov      ebx, ecx                       
  0x0022598A  8bd7                    mov      edx, edi                       
  0x0022598C  8bce                    mov      ecx, esi                       
  0x0022598E  e8e7faffff              call     0x22547a                       ; -> sub_0022547A
  0x00225993  66894620                mov      word ptr [esi + 0x20], ax      
  0x00225997  ff15305b2200            call     dword ptr [0x225b30]           ; -> xbox_KeRaiseIrqlToDpcLevel
  0x0022599D  fe4726                  inc      byte ptr [edi + 0x26]          
  0x002259A0  83662400                and      dword ptr [esi + 0x24], 0      
  0x002259A4  8845ff                  mov      byte ptr [ebp - 1], al         
  0x002259A7  66c746220200            mov      word ptr [esi + 0x22], 2       
  0x002259AD  0fb64711                movzx    eax, byte ptr [edi + 0x11]     
  0x002259B1  83e800                  sub      eax, 0                         
  0x002259B4  7425                    je       0x2259db                       
  0x002259B6  48                      dec      eax                            
  0x002259B7  48                      dec      eax                            
  0x002259B8  7416                    je       0x2259d0                       
  0x002259BA  48                      dec      eax                            
  0x002259BB  7407                    je       0x2259c4                       
  0x002259BD  bb00060080              mov      ebx, 0x80000600                
  0x002259C2  eb26                    jmp      0x2259ea                       
                                        ; XREF: 0x002259BB (cond_jump)
  0x002259C4  56                      push     esi                            
  0x002259C5  8bd7                    mov      edx, edi                       
  0x002259C7  8bcb                    mov      ecx, ebx                       
  0x002259C9  e803ffffff              call     0x2258d1                       ; -> sub_002258D1
  0x002259CE  eb14                    jmp      0x2259e4                       
                                        ; XREF: 0x002259B8 (cond_jump)
  0x002259D0  8bd6                    mov      edx, esi                       
  0x002259D2  8bcb                    mov      ecx, ebx                       
  0x002259D4  e82bffffff              call     0x225904                       ; -> sub_00225904
  0x002259D9  eb09                    jmp      0x2259e4                       
                                        ; XREF: 0x002259B4 (cond_jump)
  0x002259DB  8bd6                    mov      edx, esi                       
  0x002259DD  8bcb                    mov      ecx, ebx                       
  0x002259DF  e85cffffff              call     0x225940                       ; -> sub_00225940
                                        ; XREF: 0x002259CE (jump), 0x002259D9 (jump)
  0x002259E4  8bd8                    mov      ebx, eax                       
  0x002259E6  85db                    test     ebx, ebx                       
  0x002259E8  7d08                    jge      0x2259f2                       
                                        ; XREF: 0x002259C2 (jump)
  0x002259EA  6683662200              and      word ptr [esi + 0x22], 0       
  0x002259EF  fe4f26                  dec      byte ptr [edi + 0x26]          
                                        ; XREF: 0x002259E8 (cond_jump)
  0x002259F2  8a4dff                  mov      cl, byte ptr [ebp - 1]         
  0x002259F5  ff152c5b2200            call     dword ptr [0x225b2c]           ; -> xbox_KfLowerIrql
  0x002259FB  5f                      pop      edi                            
  0x002259FC  5e                      pop      esi                            
  0x002259FD  8bc3                    mov      eax, ebx                       
  0x002259FF  5b                      pop      ebx                            
  0x00225A00  c9                      leave                                   
  0x00225A01  c3                      ret                                     
; end of function
  0x00225A02  0000                    add      byte ptr [eax], al             
