; ============================================================
; Section: XGRPH
; VA: 0x001EB180 - 0x001EC6F9
; Size: 5497 bytes (5.4 KB)
; Functions: 25
; Instructions: 2094
; ============================================================


; ============================================================
; Function: sub_001EB180
; Start: 0x001EB180  End: 0x001EB19C  Size: 28 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_001EB1A6, sub_001EB1B9
; ============================================================
sub_001EB180:
  0x001EB180  8b442404                mov      eax, dword ptr [esp + 4]       
  0x001EB184  83f80c                  cmp      eax, 0xc                       
  0x001EB187  740e                    je       0x1eb197                       
  0x001EB189  83f80d                  cmp      eax, 0xd                       
  0x001EB18C  7605                    jbe      0x1eb193                       
  0x001EB18E  83f80f                  cmp      eax, 0xf                       
  0x001EB191  7604                    jbe      0x1eb197                       
                                        ; XREF: 0x001EB18C (cond_jump)
  0x001EB193  32c0                    xor      al, al                         
  0x001EB195  eb02                    jmp      0x1eb199                       
                                        ; XREF: 0x001EB187 (cond_jump), 0x001EB191 (cond_jump)
  0x001EB197  b001                    mov      al, 1                          
                                        ; XREF: 0x001EB195 (jump)
  0x001EB199  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EB19C
; Start: 0x001EB19C  End: 0x001EB1A6  Size: 10 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_001EB1B9, sub_001EB7D8
; ============================================================
sub_001EB19C:
  0x001EB19C  51                      push     ecx                            
  0x001EB19D  890c24                  mov      dword ptr [esp], ecx           
  0x001EB1A0  0fbc0424                bsf      eax, dword ptr [esp]           
  0x001EB1A4  59                      pop      ecx                            
  0x001EB1A5  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_001EB1A6
; Start: 0x001EB1A6  End: 0x001EB1B9  Size: 19 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_001EB180
; Called by: sub_001EB1B9
; ============================================================
sub_001EB1A6:
  0x001EB1A6  ff742404                push     dword ptr [esp + 4]            
  0x001EB1AA  e8d1ffffff              call     0x1eb180                       ; -> sub_001EB180
  0x001EB1AF  f6d8                    neg      al                             
  0x001EB1B1  1bc0                    sbb      eax, eax                       
  0x001EB1B3  83e002                  and      eax, 2                         
  0x001EB1B6  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EB1B9
; Start: 0x001EB1B9  End: 0x001EB358  Size: 415 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB180, sub_001EB19C, sub_001EB1A6
; Called by: sub_001EB358, sub_001EB3A4
; ============================================================
sub_001EB1B9:
  0x001EB1B9  55                      push     ebp                            
  0x001EB1BA  8bec                    mov      ebp, esp                       
  0x001EB1BC  83ec14                  sub      esp, 0x14                      
  0x001EB1BF  8b4d18                  mov      ecx, dword ptr [ebp + 0x18]    
  0x001EB1C2  8a8190c61e00            mov      al, byte ptr [ecx + 0x1ec690]  
  0x001EB1C8  33d2                    xor      edx, edx                       
  0x001EB1CA  8ad0                    mov      dl, al                         
  0x001EB1CC  53                      push     ebx                            
  0x001EB1CD  8a5d20                  mov      bl, byte ptr [ebp + 0x20]      
  0x001EB1D0  56                      push     esi                            
  0x001EB1D1  57                      push     edi                            
  0x001EB1D2  33f6                    xor      esi, esi                       
  0x001EB1D4  8975fc                  mov      dword ptr [ebp - 4], esi       
  0x001EB1D7  83e23c                  and      edx, 0x3c                      
  0x001EB1DA  a801                    test     al, 1                          
  0x001EB1DC  8bfa                    mov      edi, edx                       
  0x001EB1DE  897dec                  mov      dword ptr [ebp - 0x14], edi    
  0x001EB1E1  7547                    jne      0x1eb22a                       
  0x001EB1E3  51                      push     ecx                            
  0x001EB1E4  e897ffffff              call     0x1eb180                       ; -> sub_001EB180
  0x001EB1E9  84c0                    test     al, al                         
  0x001EB1EB  753d                    jne      0x1eb22a                       
  0x001EB1ED  33c0                    xor      eax, eax                       
  0x001EB1EF  394514                  cmp      dword ptr [ebp + 0x14], eax    
  0x001EB1F2  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x001EB1F5  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x001EB1F8  7507                    jne      0x1eb201                       
  0x001EB1FA  c7451401000000          mov      dword ptr [ebp + 0x14], 1      
                                        ; XREF: 0x001EB1F8 (cond_jump)
  0x001EB201  8b4d1c                  mov      ecx, dword ptr [ebp + 0x1c]    
  0x001EB204  3bc8                    cmp      ecx, eax                       
  0x001EB206  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x001EB209  750e                    jne      0x1eb219                       
  0x001EB20B  0faff8                  imul     edi, eax                       
  0x001EB20E  c1ef03                  shr      edi, 3                         
  0x001EB211  83c73f                  add      edi, 0x3f                      
  0x001EB214  83e7c0                  and      edi, 0xffffffc0                
  0x001EB217  8bcf                    mov      ecx, edi                       
                                        ; XREF: 0x001EB209 (cond_jump)
  0x001EB219  894510                  mov      dword ptr [ebp + 0x10], eax    
  0x001EB21C  8b450c                  mov      eax, dword ptr [ebp + 0xc]     
  0x001EB21F  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x001EB222  0fafc1                  imul     eax, ecx                       
  0x001EB225  e9bf000000              jmp      0x1eb2e9                       
                                        ; XREF: 0x001EB1E1 (cond_jump), 0x001EB1EB (cond_jump)
  0x001EB22A  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x001EB22D  e86affffff              call     0x1eb19c                       ; -> sub_001EB19C
  0x001EB232  8b4d0c                  mov      ecx, dword ptr [ebp + 0xc]     
  0x001EB235  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x001EB238  e85fffffff              call     0x1eb19c                       ; -> sub_001EB19C
  0x001EB23D  8b4d10                  mov      ecx, dword ptr [ebp + 0x10]    
  0x001EB240  8bf8                    mov      edi, eax                       
  0x001EB242  897df4                  mov      dword ptr [ebp - 0xc], edi     
  0x001EB245  e852ffffff              call     0x1eb19c                       ; -> sub_001EB19C
  0x001EB24A  ff7518                  push     dword ptr [ebp + 0x18]         
  0x001EB24D  83651000                and      dword ptr [ebp + 0x10], 0      
  0x001EB251  8365f000                and      dword ptr [ebp - 0x10], 0      
  0x001EB255  8bf0                    mov      esi, eax                       
  0x001EB257  e84affffff              call     0x1eb1a6                       ; -> sub_001EB1A6
  0x001EB25C  837d1400                cmp      dword ptr [ebp + 0x14], 0      
  0x001EB260  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EB263  751e                    jne      0x1eb283                       
  0x001EB265  3bfe                    cmp      edi, esi                       
  0x001EB267  8bcf                    mov      ecx, edi                       
  0x001EB269  7702                    ja       0x1eb26d                       
  0x001EB26B  8bce                    mov      ecx, esi                       
                                        ; XREF: 0x001EB269 (cond_jump)
  0x001EB26D  394df8                  cmp      dword ptr [ebp - 8], ecx       
  0x001EB270  7605                    jbe      0x1eb277                       
  0x001EB272  8b4df8                  mov      ecx, dword ptr [ebp - 8]       
  0x001EB275  eb08                    jmp      0x1eb27f                       
                                        ; XREF: 0x001EB270 (cond_jump)
  0x001EB277  3bfe                    cmp      edi, esi                       
  0x001EB279  8bcf                    mov      ecx, edi                       
  0x001EB27B  7702                    ja       0x1eb27f                       
  0x001EB27D  8bce                    mov      ecx, esi                       
                                        ; XREF: 0x001EB275 (jump), 0x001EB27B (cond_jump)
  0x001EB27F  41                      inc      ecx                            
  0x001EB280  894d14                  mov      dword ptr [ebp + 0x14], ecx    
                                        ; XREF: 0x001EB263 (cond_jump)
  0x001EB283  8b4d14                  mov      ecx, dword ptr [ebp + 0x14]    
  0x001EB286  85c9                    test     ecx, ecx                       
  0x001EB288  8b45f8                  mov      eax, dword ptr [ebp - 8]       
  0x001EB28B  897d20                  mov      dword ptr [ebp + 0x20], edi    
  0x001EB28E  8bfe                    mov      edi, esi                       
  0x001EB290  7442                    je       0x1eb2d4                       
  0x001EB292  894d0c                  mov      dword ptr [ebp + 0xc], ecx     
                                        ; XREF: 0x001EB2D2 (cond_jump)
  0x001EB295  8b5508                  mov      edx, dword ptr [ebp + 8]       
  0x001EB298  3bc2                    cmp      eax, edx                       
  0x001EB29A  7602                    jbe      0x1eb29e                       
  0x001EB29C  8bd0                    mov      edx, eax                       
                                        ; XREF: 0x001EB29A (cond_jump)
  0x001EB29E  8b4d08                  mov      ecx, dword ptr [ebp + 8]       
  0x001EB2A1  394d20                  cmp      dword ptr [ebp + 0x20], ecx    
  0x001EB2A4  7603                    jbe      0x1eb2a9                       
  0x001EB2A6  8b4d20                  mov      ecx, dword ptr [ebp + 0x20]    
                                        ; XREF: 0x001EB2A4 (cond_jump)
  0x001EB2A9  03ca                    add      ecx, edx                       
  0x001EB2AB  33d2                    xor      edx, edx                       
  0x001EB2AD  42                      inc      edx                            
  0x001EB2AE  03cf                    add      ecx, edi                       
  0x001EB2B0  d3e2                    shl      edx, cl                        
  0x001EB2B2  0faf55ec                imul     edx, dword ptr [ebp - 0x14]    
  0x001EB2B6  c1ea03                  shr      edx, 3                         
  0x001EB2B9  0155fc                  add      dword ptr [ebp - 4], edx       
  0x001EB2BC  85c0                    test     eax, eax                       
  0x001EB2BE  7601                    jbe      0x1eb2c1                       
  0x001EB2C0  48                      dec      eax                            
                                        ; XREF: 0x001EB2BE (cond_jump)
  0x001EB2C1  837d2000                cmp      dword ptr [ebp + 0x20], 0      
  0x001EB2C5  7603                    jbe      0x1eb2ca                       
  0x001EB2C7  ff4d20                  dec      dword ptr [ebp + 0x20]         
                                        ; XREF: 0x001EB2C5 (cond_jump)
  0x001EB2CA  85ff                    test     edi, edi                       
  0x001EB2CC  7601                    jbe      0x1eb2cf                       
  0x001EB2CE  4f                      dec      edi                            
                                        ; XREF: 0x001EB2CC (cond_jump)
  0x001EB2CF  ff4d0c                  dec      dword ptr [ebp + 0xc]          
  0x001EB2D2  75c1                    jne      0x1eb295                       
                                        ; XREF: 0x001EB290 (cond_jump)
  0x001EB2D4  84db                    test     bl, bl                         
  0x001EB2D6  8b4d1c                  mov      ecx, dword ptr [ebp + 0x1c]    
  0x001EB2D9  7411                    je       0x1eb2ec                       
  0x001EB2DB  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EB2DE  83c07f                  add      eax, 0x7f                      
  0x001EB2E1  83e080                  and      eax, 0xffffff80                
  0x001EB2E4  8d0440                  lea      eax, [eax + eax*2]             
  0x001EB2E7  d1e0                    shl      eax, 1                         
                                        ; XREF: 0x001EB225 (jump)
  0x001EB2E9  8945fc                  mov      dword ptr [ebp - 4], eax       
                                        ; XREF: 0x001EB2D9 (cond_jump)
  0x001EB2EC  c1e604                  shl      esi, 4                         
  0x001EB2EF  0b75f4                  or       esi, dword ptr [ebp - 0xc]     
  0x001EB2F2  33c0                    xor      eax, eax                       
  0x001EB2F4  c1e604                  shl      esi, 4                         
  0x001EB2F7  0b75f8                  or       esi, dword ptr [ebp - 8]       
  0x001EB2FA  5f                      pop      edi                            
  0x001EB2FB  c1e604                  shl      esi, 4                         
  0x001EB2FE  0b7514                  or       esi, dword ptr [ebp + 0x14]    
  0x001EB301  c1e608                  shl      esi, 8                         
  0x001EB304  0b7518                  or       esi, dword ptr [ebp + 0x18]    
  0x001EB307  c1e604                  shl      esi, 4                         
  0x001EB30A  384524                  cmp      byte ptr [ebp + 0x24], al      
  0x001EB30D  0f95c0                  setne    al                             
  0x001EB310  40                      inc      eax                            
  0x001EB311  40                      inc      eax                            
  0x001EB312  0bf0                    or       esi, eax                       
  0x001EB314  8b4528                  mov      eax, dword ptr [ebp + 0x28]    
  0x001EB317  c1e604                  shl      esi, 4                         
  0x001EB31A  f6db                    neg      bl                             
  0x001EB31C  1bdb                    sbb      ebx, ebx                       
  0x001EB31E  83e304                  and      ebx, 4                         
  0x001EB321  0bf3                    or       esi, ebx                       
  0x001EB323  83ce09                  or       esi, 9                         
  0x001EB326  8930                    mov      dword ptr [eax], esi           
  0x001EB328  8b4510                  mov      eax, dword ptr [ebp + 0x10]    
  0x001EB32B  85c0                    test     eax, eax                       
  0x001EB32D  5e                      pop      esi                            
  0x001EB32E  5b                      pop      ebx                            
  0x001EB32F  741a                    je       0x1eb34b                       
  0x001EB331  8b55f0                  mov      edx, dword ptr [ebp - 0x10]    
  0x001EB334  c1e906                  shr      ecx, 6                         
  0x001EB337  49                      dec      ecx                            
  0x001EB338  c1e10c                  shl      ecx, 0xc                       
  0x001EB33B  4a                      dec      edx                            
  0x001EB33C  0bca                    or       ecx, edx                       
  0x001EB33E  c1e10c                  shl      ecx, 0xc                       
  0x001EB341  48                      dec      eax                            
  0x001EB342  0bc8                    or       ecx, eax                       
  0x001EB344  8b452c                  mov      eax, dword ptr [ebp + 0x2c]    
  0x001EB347  8908                    mov      dword ptr [eax], ecx           
  0x001EB349  eb06                    jmp      0x1eb351                       
                                        ; XREF: 0x001EB32F (cond_jump)
  0x001EB34B  8b452c                  mov      eax, dword ptr [ebp + 0x2c]    
  0x001EB34E  832000                  and      dword ptr [eax], 0             
                                        ; XREF: 0x001EB349 (jump)
  0x001EB351  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EB354  c9                      leave                                   
  0x001EB355  c22800                  ret      0x28                           
; end of function

; ============================================================
; Function: sub_001EB358
; Start: 0x001EB358  End: 0x001EB3A4  Size: 76 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB1B9
; Called by: sub_001EB3E5, sub_001EB40F
; ============================================================
sub_001EB358:
  0x001EB358  55                      push     ebp                            
  0x001EB359  8bec                    mov      ebp, esp                       
  0x001EB35B  56                      push     esi                            
  0x001EB35C  8b7530                  mov      esi, dword ptr [ebp + 0x30]    
  0x001EB35F  57                      push     edi                            
  0x001EB360  8d4610                  lea      eax, [esi + 0x10]              
  0x001EB363  50                      push     eax                            
  0x001EB364  8d7e0c                  lea      edi, [esi + 0xc]               
  0x001EB367  57                      push     edi                            
  0x001EB368  ff7528                  push     dword ptr [ebp + 0x28]         
  0x001EB36B  ff7524                  push     dword ptr [ebp + 0x24]         
  0x001EB36E  ff7520                  push     dword ptr [ebp + 0x20]         
  0x001EB371  ff751c                  push     dword ptr [ebp + 0x1c]         
  0x001EB374  ff7514                  push     dword ptr [ebp + 0x14]         
  0x001EB377  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EB37A  ff750c                  push     dword ptr [ebp + 0xc]          
  0x001EB37D  ff7508                  push     dword ptr [ebp + 8]            
  0x001EB380  e834feffff              call     0x1eb1b9                       ; -> sub_001EB1B9
  0x001EB385  f6451a01                test     byte ptr [ebp + 0x1a], 1       
  0x001EB389  7403                    je       0x1eb38e                       
  0x001EB38B  8327f7                  and      dword ptr [edi], 0xfffffff7    
                                        ; XREF: 0x001EB389 (cond_jump)
  0x001EB38E  8b4d2c                  mov      ecx, dword ptr [ebp + 0x2c]    
  0x001EB391  83660800                and      dword ptr [esi + 8], 0         
  0x001EB395  5f                      pop      edi                            
  0x001EB396  c70601000400            mov      dword ptr [esi], 0x40001       
  0x001EB39C  894e04                  mov      dword ptr [esi + 4], ecx       
  0x001EB39F  5e                      pop      esi                            
  0x001EB3A0  5d                      pop      ebp                            
  0x001EB3A1  c22c00                  ret      0x2c                           
; end of function

; ============================================================
; Function: sub_001EB3A4
; Start: 0x001EB3A4  End: 0x001EB3E5  Size: 65 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB1B9
; Called by: sub_000E0D40
; ============================================================
sub_001EB3A4:
  0x001EB3A4  55                      push     ebp                            
  0x001EB3A5  8bec                    mov      ebp, esp                       
  0x001EB3A7  56                      push     esi                            
  0x001EB3A8  8b7514                  mov      esi, dword ptr [ebp + 0x14]    
  0x001EB3AB  8d4610                  lea      eax, [esi + 0x10]              
  0x001EB3AE  50                      push     eax                            
  0x001EB3AF  8d460c                  lea      eax, [esi + 0xc]               
  0x001EB3B2  50                      push     eax                            
  0x001EB3B3  6a00                    push     0                              
  0x001EB3B5  6a00                    push     0                              
  0x001EB3B7  ff751c                  push     dword ptr [ebp + 0x1c]         
  0x001EB3BA  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EB3BD  6a01                    push     1                              
  0x001EB3BF  6a01                    push     1                              
  0x001EB3C1  ff750c                  push     dword ptr [ebp + 0xc]          
  0x001EB3C4  ff7508                  push     dword ptr [ebp + 8]            
  0x001EB3C7  e8edfdffff              call     0x1eb1b9                       ; -> sub_001EB1B9
  0x001EB3CC  83660800                and      dword ptr [esi + 8], 0         
  0x001EB3D0  8b4d18                  mov      ecx, dword ptr [ebp + 0x18]    
  0x001EB3D3  83661400                and      dword ptr [esi + 0x14], 0      
  0x001EB3D7  c70601000500            mov      dword ptr [esi], 0x50001       
  0x001EB3DD  894e04                  mov      dword ptr [esi + 4], ecx       
  0x001EB3E0  5e                      pop      esi                            
  0x001EB3E1  5d                      pop      ebp                            
  0x001EB3E2  c21800                  ret      0x18                           
; end of function

; ============================================================
; Function: sub_001EB3E5
; Start: 0x001EB3E5  End: 0x001EB40F  Size: 42 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB358
; Called by: sub_000E0A40, sub_000E0D40, sub_000E64F0
; ============================================================
sub_001EB3E5:
  0x001EB3E5  55                      push     ebp                            
  0x001EB3E6  8bec                    mov      ebp, esp                       
  0x001EB3E8  ff7520                  push     dword ptr [ebp + 0x20]         
  0x001EB3EB  ff7524                  push     dword ptr [ebp + 0x24]         
  0x001EB3EE  6a00                    push     0                              
  0x001EB3F0  6a00                    push     0                              
  0x001EB3F2  ff7528                  push     dword ptr [ebp + 0x28]         
  0x001EB3F5  ff7518                  push     dword ptr [ebp + 0x18]         
  0x001EB3F8  ff7514                  push     dword ptr [ebp + 0x14]         
  0x001EB3FB  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EB3FE  6a01                    push     1                              
  0x001EB400  ff750c                  push     dword ptr [ebp + 0xc]          
  0x001EB403  ff7508                  push     dword ptr [ebp + 8]            
  0x001EB406  e84dffffff              call     0x1eb358                       ; -> sub_001EB358
  0x001EB40B  5d                      pop      ebp                            
  0x001EB40C  c22400                  ret      0x24                           
; end of function

; ============================================================
; Function: sub_001EB40F
; Start: 0x001EB40F  End: 0x001EB439  Size: 42 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB358
; Called by: sub_000E64F0
; ============================================================
sub_001EB40F:
  0x001EB40F  55                      push     ebp                            
  0x001EB410  8bec                    mov      ebp, esp                       
  0x001EB412  ff751c                  push     dword ptr [ebp + 0x1c]         
  0x001EB415  ff7520                  push     dword ptr [ebp + 0x20]         
  0x001EB418  6a00                    push     0                              
  0x001EB41A  6a01                    push     1                              
  0x001EB41C  ff7524                  push     dword ptr [ebp + 0x24]         
  0x001EB41F  ff7514                  push     dword ptr [ebp + 0x14]         
  0x001EB422  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EB425  ff750c                  push     dword ptr [ebp + 0xc]          
  0x001EB428  6a01                    push     1                              
  0x001EB42A  ff7508                  push     dword ptr [ebp + 8]            
  0x001EB42D  ff7508                  push     dword ptr [ebp + 8]            
  0x001EB430  e823ffffff              call     0x1eb358                       ; -> sub_001EB358
  0x001EB435  5d                      pop      ebp                            
  0x001EB436  c22000                  ret      0x20                           
; end of function

; ============================================================
; Function: sub_001EB439
; Start: 0x001EB439  End: 0x001EB706  Size: 717 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_000B12F2, sub_000B1FEE, sub_000B200C, sub_000B282D, sub_000B2921, sub_000B29C1, sub_0013A3A9, sub_001DD5F0, sub_001DD610
; Called by: sub_000E8CE0
; ============================================================
sub_001EB439:
  0x001EB439  55                      push     ebp                            
  0x001EB43A  8bec                    mov      ebp, esp                       
  0x001EB43C  81ec6c030000            sub      esp, 0x36c                     
  0x001EB442  53                      push     ebx                            
  0x001EB443  56                      push     esi                            
  0x001EB444  57                      push     edi                            
  0x001EB445  8d45cc                  lea      eax, [ebp - 0x34]              
  0x001EB448  50                      push     eax                            
  0x001EB449  ff7508                  push     dword ptr [ebp + 8]            
  0x001EB44C  e89f21ffff              call     0x1dd5f0                       ; -> sub_001DD5F0
  0x001EB451  8b4de4                  mov      ecx, dword ptr [ebp - 0x1c]    
  0x001EB454  8b55e0                  mov      edx, dword ptr [ebp - 0x20]    
  0x001EB457  8bc1                    mov      eax, ecx                       
  0x001EB459  0fafc2                  imul     eax, edx                       
  0x001EB45C  8d1c40                  lea      ebx, [eax + eax*2]             
  0x001EB45F  8b45cc                  mov      eax, dword ptr [ebp - 0x34]    
  0x001EB462  83f811                  cmp      eax, 0x11                      
  0x001EB465  895df4                  mov      dword ptr [ebp - 0xc], ebx     
  0x001EB468  0f8c8e000000            jl       0x1eb4fc                       
  0x001EB46E  83f812                  cmp      eax, 0x12                      
  0x001EB471  7e0a                    jle      0x1eb47d                       
  0x001EB473  83f81c                  cmp      eax, 0x1c                      
  0x001EB476  7405                    je       0x1eb47d                       
  0x001EB478  83f81e                  cmp      eax, 0x1e                      
  0x001EB47B  757f                    jne      0x1eb4fc                       
                                        ; XREF: 0x001EB471 (cond_jump), 0x001EB476 (cond_jump)
  0x001EB47D  33ff                    xor      edi, edi                       
  0x001EB47F  6a28                    push     0x28                           
  0x001EB481  5e                      pop      esi                            
  0x001EB482  57                      push     edi                            
  0x001EB483  57                      push     edi                            
  0x001EB484  6a02                    push     2                              
  0x001EB486  57                      push     edi                            
  0x001EB487  57                      push     edi                            
  0x001EB488  6800000040              push     0x40000000                     
  0x001EB48D  ff750c                  push     dword ptr [ebp + 0xc]          
  0x001EB490  8d4336                  lea      eax, [ebx + 0x36]              
  0x001EB493  66c745a21800            mov      word ptr [ebp - 0x5e], 0x18    
  0x001EB499  897da4                  mov      dword ptr [ebp - 0x5c], edi    
  0x001EB49C  897594                  mov      dword ptr [ebp - 0x6c], esi    
  0x001EB49F  895598                  mov      dword ptr [ebp - 0x68], edx    
  0x001EB4A2  894d9c                  mov      dword ptr [ebp - 0x64], ecx    
  0x001EB4A5  66c745a00100            mov      word ptr [ebp - 0x60], 1       
  0x001EB4AB  895da8                  mov      dword ptr [ebp - 0x58], ebx    
  0x001EB4AE  897dac                  mov      dword ptr [ebp - 0x54], edi    
  0x001EB4B1  897db0                  mov      dword ptr [ebp - 0x50], edi    
  0x001EB4B4  897db4                  mov      dword ptr [ebp - 0x4c], edi    
  0x001EB4B7  897db8                  mov      dword ptr [ebp - 0x48], edi    
  0x001EB4BA  66c745bc424d            mov      word ptr [ebp - 0x44], 0x4d42  
  0x001EB4C0  8945be                  mov      dword ptr [ebp - 0x42], eax    
  0x001EB4C3  66897dc2                mov      word ptr [ebp - 0x3e], di      
  0x001EB4C7  66897dc4                mov      word ptr [ebp - 0x3c], di      
  0x001EB4CB  c745c636000000          mov      dword ptr [ebp - 0x3a], 0x36   
  0x001EB4D2  e8356becff              call     0xb200c                        ; -> sub_000B200C
  0x001EB4D7  83f8ff                  cmp      eax, -1                        
  0x001EB4DA  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x001EB4DD  7529                    jne      0x1eb508                       
  0x001EB4DF  e84973ecff              call     0xb282d                        ; -> sub_000B282D
  0x001EB4E4  50                      push     eax                            
  0x001EB4E5  ff750c                  push     dword ptr [ebp + 0xc]          
  0x001EB4E8  8d8594feffff            lea      eax, [ebp - 0x16c]             
  0x001EB4EE  68d4c61e00              push     0x1ec6d4                       
  0x001EB4F3  50                      push     eax                            
  0x001EB4F4  e8b0eef4ff              call     0x13a3a9                       ; -> sub_0013A3A9
  0x001EB4F9  83c410                  add      esp, 0x10                      
                                        ; XREF: 0x001EB468 (cond_jump), 0x001EB47B (cond_jump)
  0x001EB4FC  b805400080              mov      eax, 0x80004005                
                                        ; XREF: 0x001EB701 (jump)
  0x001EB501  5f                      pop      edi                            
  0x001EB502  5e                      pop      esi                            
  0x001EB503  5b                      pop      ebx                            
  0x001EB504  c9                      leave                                   
  0x001EB505  c20800                  ret      8                              
                                        ; XREF: 0x001EB4DD (cond_jump)
  0x001EB508  57                      push     edi                            
  0x001EB509  8d4df8                  lea      ecx, [ebp - 8]                 
  0x001EB50C  51                      push     ecx                            
  0x001EB50D  6a0e                    push     0xe                            
  0x001EB50F  8d4dbc                  lea      ecx, [ebp - 0x44]              
  0x001EB512  51                      push     ecx                            
  0x001EB513  50                      push     eax                            
  0x001EB514  e8d95decff              call     0xb12f2                        ; -> sub_000B12F2
  0x001EB519  57                      push     edi                            
  0x001EB51A  8d45f8                  lea      eax, [ebp - 8]                 
  0x001EB51D  50                      push     eax                            
  0x001EB51E  56                      push     esi                            
  0x001EB51F  8d4594                  lea      eax, [ebp - 0x6c]              
  0x001EB522  50                      push     eax                            
  0x001EB523  ff75fc                  push     dword ptr [ebp - 4]            
  0x001EB526  e8c75decff              call     0xb12f2                        ; -> sub_000B12F2
  0x001EB52B  68c0000000              push     0xc0                           
  0x001EB530  57                      push     edi                            
  0x001EB531  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EB534  50                      push     eax                            
  0x001EB535  ff7508                  push     dword ptr [ebp + 8]            
  0x001EB538  e8d320ffff              call     0x1dd610                       ; -> sub_001DD610
  0x001EB53D  6800008724              push     0x24870000                     
  0x001EB542  53                      push     ebx                            
  0x001EB543  33f6                    xor      esi, esi                       
  0x001EB545  e8d773ecff              call     0xb2921                        ; -> sub_000B2921
  0x001EB54A  3bc7                    cmp      eax, edi                       
  0x001EB54C  8945e8                  mov      dword ptr [ebp - 0x18], eax    
  0x001EB54F  740a                    je       0x1eb55b                       
  0x001EB551  8bd8                    mov      ebx, eax                       
  0x001EB553  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x001EB556  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x001EB559  eb0d                    jmp      0x1eb568                       
                                        ; XREF: 0x001EB54F (cond_jump)
  0x001EB55B  8d9d94fcffff            lea      ebx, [ebp - 0x36c]             
  0x001EB561  c745f400020000          mov      dword ptr [ebp - 0xc], 0x200   
                                        ; XREF: 0x001EB559 (jump)
  0x001EB568  8b45cc                  mov      eax, dword ptr [ebp - 0x34]    
  0x001EB56B  83e811                  sub      eax, 0x11                      
  0x001EB56E  0f84f3000000            je       0x1eb667                       
  0x001EB574  48                      dec      eax                            
  0x001EB575  740d                    je       0x1eb584                       
  0x001EB577  83e80a                  sub      eax, 0xa                       
  0x001EB57A  7473                    je       0x1eb5ef                       
  0x001EB57C  48                      dec      eax                            
  0x001EB57D  48                      dec      eax                            
  0x001EB57E  0f8561010000            jne      0x1eb6e5                       
                                        ; XREF: 0x001EB575 (cond_jump)
  0x001EB584  8b45e4                  mov      eax, dword ptr [ebp - 0x1c]    
  0x001EB587  48                      dec      eax                            
  0x001EB588  3bc7                    cmp      eax, edi                       
  0x001EB58A  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EB58D  0f8c43010000            jl       0x1eb6d6                       
                                        ; XREF: 0x001EB5E8 (cond_jump)
  0x001EB593  8b7dec                  mov      edi, dword ptr [ebp - 0x14]    
  0x001EB596  0faf7d08                imul     edi, dword ptr [ebp + 8]       
  0x001EB59A  037df0                  add      edi, dword ptr [ebp - 0x10]    
  0x001EB59D  83650c00                and      dword ptr [ebp + 0xc], 0       
  0x001EB5A1  837de000                cmp      dword ptr [ebp - 0x20], 0      
  0x001EB5A5  7e3e                    jle      0x1eb5e5                       
                                        ; XREF: 0x001EB5E3 (cond_jump)
  0x001EB5A7  8a07                    mov      al, byte ptr [edi]             
  0x001EB5A9  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB5AC  8a4701                  mov      al, byte ptr [edi + 1]         
  0x001EB5AF  46                      inc      esi                            
  0x001EB5B0  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB5B3  8a4702                  mov      al, byte ptr [edi + 2]         
  0x001EB5B6  46                      inc      esi                            
  0x001EB5B7  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB5BA  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x001EB5BD  46                      inc      esi                            
  0x001EB5BE  83c0fe                  add      eax, -2                        
  0x001EB5C1  83c704                  add      edi, 4                         
  0x001EB5C4  3bf0                    cmp      esi, eax                       
  0x001EB5C6  7212                    jb       0x1eb5da                       
  0x001EB5C8  6a00                    push     0                              
  0x001EB5CA  8d45f8                  lea      eax, [ebp - 8]                 
  0x001EB5CD  50                      push     eax                            
  0x001EB5CE  56                      push     esi                            
  0x001EB5CF  53                      push     ebx                            
  0x001EB5D0  ff75fc                  push     dword ptr [ebp - 4]            
  0x001EB5D3  e81a5decff              call     0xb12f2                        ; -> sub_000B12F2
  0x001EB5D8  33f6                    xor      esi, esi                       
                                        ; XREF: 0x001EB5C6 (cond_jump)
  0x001EB5DA  ff450c                  inc      dword ptr [ebp + 0xc]          
  0x001EB5DD  8b450c                  mov      eax, dword ptr [ebp + 0xc]     
  0x001EB5E0  3b45e0                  cmp      eax, dword ptr [ebp - 0x20]    
  0x001EB5E3  7cc2                    jl       0x1eb5a7                       
                                        ; XREF: 0x001EB5A5 (cond_jump)
  0x001EB5E5  ff4d08                  dec      dword ptr [ebp + 8]            
  0x001EB5E8  79a9                    jns      0x1eb593                       
  0x001EB5EA  e9e5000000              jmp      0x1eb6d4                       
                                        ; XREF: 0x001EB57A (cond_jump)
  0x001EB5EF  8b45e4                  mov      eax, dword ptr [ebp - 0x1c]    
  0x001EB5F2  48                      dec      eax                            
  0x001EB5F3  3bc7                    cmp      eax, edi                       
  0x001EB5F5  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EB5F8  0f8cd8000000            jl       0x1eb6d6                       
                                        ; XREF: 0x001EB663 (cond_jump)
  0x001EB5FE  8b7dec                  mov      edi, dword ptr [ebp - 0x14]    
  0x001EB601  0faf7d08                imul     edi, dword ptr [ebp + 8]       
  0x001EB605  037df0                  add      edi, dword ptr [ebp - 0x10]    
  0x001EB608  83650c00                and      dword ptr [ebp + 0xc], 0       
  0x001EB60C  837de000                cmp      dword ptr [ebp - 0x20], 0      
  0x001EB610  7e4e                    jle      0x1eb660                       
                                        ; XREF: 0x001EB65E (cond_jump)
  0x001EB612  8a07                    mov      al, byte ptr [edi]             
  0x001EB614  c0e003                  shl      al, 3                          
  0x001EB617  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB61A  33c0                    xor      eax, eax                       
  0x001EB61C  668b07                  mov      ax, word ptr [edi]             
  0x001EB61F  46                      inc      esi                            
  0x001EB620  c1e802                  shr      eax, 2                         
  0x001EB623  24f8                    and      al, 0xf8                       
  0x001EB625  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB628  33c0                    xor      eax, eax                       
  0x001EB62A  668b07                  mov      ax, word ptr [edi]             
  0x001EB62D  46                      inc      esi                            
  0x001EB62E  c1e807                  shr      eax, 7                         
  0x001EB631  24f8                    and      al, 0xf8                       
  0x001EB633  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB636  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x001EB639  46                      inc      esi                            
  0x001EB63A  47                      inc      edi                            
  0x001EB63B  83c0fe                  add      eax, -2                        
  0x001EB63E  47                      inc      edi                            
  0x001EB63F  3bf0                    cmp      esi, eax                       
  0x001EB641  7212                    jb       0x1eb655                       
  0x001EB643  6a00                    push     0                              
  0x001EB645  8d45f8                  lea      eax, [ebp - 8]                 
  0x001EB648  50                      push     eax                            
  0x001EB649  56                      push     esi                            
  0x001EB64A  53                      push     ebx                            
  0x001EB64B  ff75fc                  push     dword ptr [ebp - 4]            
  0x001EB64E  e89f5cecff              call     0xb12f2                        ; -> sub_000B12F2
  0x001EB653  33f6                    xor      esi, esi                       
                                        ; XREF: 0x001EB641 (cond_jump)
  0x001EB655  ff450c                  inc      dword ptr [ebp + 0xc]          
  0x001EB658  8b450c                  mov      eax, dword ptr [ebp + 0xc]     
  0x001EB65B  3b45e0                  cmp      eax, dword ptr [ebp - 0x20]    
  0x001EB65E  7cb2                    jl       0x1eb612                       
                                        ; XREF: 0x001EB610 (cond_jump)
  0x001EB660  ff4d08                  dec      dword ptr [ebp + 8]            
  0x001EB663  7999                    jns      0x1eb5fe                       
  0x001EB665  eb6d                    jmp      0x1eb6d4                       
                                        ; XREF: 0x001EB56E (cond_jump)
  0x001EB667  8b45e4                  mov      eax, dword ptr [ebp - 0x1c]    
  0x001EB66A  48                      dec      eax                            
  0x001EB66B  3bc7                    cmp      eax, edi                       
  0x001EB66D  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EB670  7c64                    jl       0x1eb6d6                       
                                        ; XREF: 0x001EB6D2 (cond_jump)
  0x001EB672  8b7dec                  mov      edi, dword ptr [ebp - 0x14]    
  0x001EB675  0faf7d08                imul     edi, dword ptr [ebp + 8]       
  0x001EB679  037df0                  add      edi, dword ptr [ebp - 0x10]    
  0x001EB67C  83650c00                and      dword ptr [ebp + 0xc], 0       
  0x001EB680  837de000                cmp      dword ptr [ebp - 0x20], 0      
  0x001EB684  7e49                    jle      0x1eb6cf                       
                                        ; XREF: 0x001EB6CD (cond_jump)
  0x001EB686  8a07                    mov      al, byte ptr [edi]             
  0x001EB688  c0e003                  shl      al, 3                          
  0x001EB68B  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB68E  33c0                    xor      eax, eax                       
  0x001EB690  668b07                  mov      ax, word ptr [edi]             
  0x001EB693  46                      inc      esi                            
  0x001EB694  c1e803                  shr      eax, 3                         
  0x001EB697  24fc                    and      al, 0xfc                       
  0x001EB699  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB69C  8a4701                  mov      al, byte ptr [edi + 1]         
  0x001EB69F  24f8                    and      al, 0xf8                       
  0x001EB6A1  46                      inc      esi                            
  0x001EB6A2  880433                  mov      byte ptr [ebx + esi], al       
  0x001EB6A5  8b45f4                  mov      eax, dword ptr [ebp - 0xc]     
  0x001EB6A8  46                      inc      esi                            
  0x001EB6A9  47                      inc      edi                            
  0x001EB6AA  83c0fe                  add      eax, -2                        
  0x001EB6AD  47                      inc      edi                            
  0x001EB6AE  3bf0                    cmp      esi, eax                       
  0x001EB6B0  7212                    jb       0x1eb6c4                       
  0x001EB6B2  6a00                    push     0                              
  0x001EB6B4  8d45f8                  lea      eax, [ebp - 8]                 
  0x001EB6B7  50                      push     eax                            
  0x001EB6B8  56                      push     esi                            
  0x001EB6B9  53                      push     ebx                            
  0x001EB6BA  ff75fc                  push     dword ptr [ebp - 4]            
  0x001EB6BD  e8305cecff              call     0xb12f2                        ; -> sub_000B12F2
  0x001EB6C2  33f6                    xor      esi, esi                       
                                        ; XREF: 0x001EB6B0 (cond_jump)
  0x001EB6C4  ff450c                  inc      dword ptr [ebp + 0xc]          
  0x001EB6C7  8b450c                  mov      eax, dword ptr [ebp + 0xc]     
  0x001EB6CA  3b45e0                  cmp      eax, dword ptr [ebp - 0x20]    
  0x001EB6CD  7cb7                    jl       0x1eb686                       
                                        ; XREF: 0x001EB684 (cond_jump)
  0x001EB6CF  ff4d08                  dec      dword ptr [ebp + 8]            
  0x001EB6D2  799e                    jns      0x1eb672                       
                                        ; XREF: 0x001EB5EA (jump), 0x001EB665 (jump)
  0x001EB6D4  33ff                    xor      edi, edi                       
                                        ; XREF: 0x001EB58D (cond_jump), 0x001EB5F8 (cond_jump), 0x001EB670 (cond_jump)
  0x001EB6D6  57                      push     edi                            
  0x001EB6D7  8d45f8                  lea      eax, [ebp - 8]                 
  0x001EB6DA  50                      push     eax                            
  0x001EB6DB  56                      push     esi                            
  0x001EB6DC  53                      push     ebx                            
  0x001EB6DD  ff75fc                  push     dword ptr [ebp - 4]            
  0x001EB6E0  e80d5cecff              call     0xb12f2                        ; -> sub_000B12F2
                                        ; XREF: 0x001EB57E (cond_jump)
  0x001EB6E5  ff75fc                  push     dword ptr [ebp - 4]            
  0x001EB6E8  e80169ecff              call     0xb1fee                        ; -> sub_000B1FEE
  0x001EB6ED  397de8                  cmp      dword ptr [ebp - 0x18], edi    
  0x001EB6F0  740d                    je       0x1eb6ff                       
  0x001EB6F2  6800008724              push     0x24870000                     
  0x001EB6F7  ff75e8                  push     dword ptr [ebp - 0x18]         
  0x001EB6FA  e8c272ecff              call     0xb29c1                        ; -> sub_000B29C1
                                        ; XREF: 0x001EB6F0 (cond_jump)
  0x001EB6FF  33c0                    xor      eax, eax                       
  0x001EB701  e9fbfdffff              jmp      0x1eb501                       
; end of function

; ============================================================
; Function: sub_001EB706
; Start: 0x001EB706  End: 0x001EB725  Size: 31 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_001EBF3E
; ============================================================
sub_001EB706:
  0x001EB706  8bc1                    mov      eax, ecx                       
  0x001EB708  33c9                    xor      ecx, ecx                       
  0x001EB70A  8908                    mov      dword ptr [eax], ecx           
  0x001EB70C  894804                  mov      dword ptr [eax + 4], ecx       
  0x001EB70F  894808                  mov      dword ptr [eax + 8], ecx       
  0x001EB712  89480c                  mov      dword ptr [eax + 0xc], ecx     
  0x001EB715  894810                  mov      dword ptr [eax + 0x10], ecx    
  0x001EB718  894814                  mov      dword ptr [eax + 0x14], ecx    
  0x001EB71B  894818                  mov      dword ptr [eax + 0x18], ecx    
  0x001EB71E  89481c                  mov      dword ptr [eax + 0x1c], ecx    
  0x001EB721  894820                  mov      dword ptr [eax + 0x20], ecx    
  0x001EB724  c3                      ret                                     
; end of function

; ============================================================
; Function: sub_001EB725
; Start: 0x001EB725  End: 0x001EB786  Size: 97 bytes
; Detection: prologue (confidence: 0.95)
; Called by: sub_001EBF3E
; ============================================================
sub_001EB725:
  0x001EB725  55                      push     ebp                            
  0x001EB726  8bec                    mov      ebp, esp                       
  0x001EB728  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x001EB72B  8901                    mov      dword ptr [ecx], eax           
  0x001EB72D  8b450c                  mov      eax, dword ptr [ebp + 0xc]     
  0x001EB730  894104                  mov      dword ptr [ecx + 4], eax       
  0x001EB733  8b4510                  mov      eax, dword ptr [ebp + 0x10]    
  0x001EB736  33d2                    xor      edx, edx                       
  0x001EB738  894108                  mov      dword ptr [ecx + 8], eax       
  0x001EB73B  33c0                    xor      eax, eax                       
  0x001EB73D  56                      push     esi                            
  0x001EB73E  40                      inc      eax                            
  0x001EB73F  57                      push     edi                            
  0x001EB740  89510c                  mov      dword ptr [ecx + 0xc], edx     
  0x001EB743  895110                  mov      dword ptr [ecx + 0x10], edx    
  0x001EB746  895114                  mov      dword ptr [ecx + 0x14], edx    
  0x001EB749  895118                  mov      dword ptr [ecx + 0x18], edx    
  0x001EB74C  89511c                  mov      dword ptr [ecx + 0x1c], edx    
  0x001EB74F  895120                  mov      dword ptr [ecx + 0x20], edx    
  0x001EB752  8bf8                    mov      edi, eax                       
                                        ; XREF: 0x001EB77E (cond_jump)
  0x001EB754  33f6                    xor      esi, esi                       
  0x001EB756  3b7d08                  cmp      edi, dword ptr [ebp + 8]       
  0x001EB759  7307                    jae      0x1eb762                       
  0x001EB75B  09410c                  or       dword ptr [ecx + 0xc], eax     
  0x001EB75E  d1e0                    shl      eax, 1                         
  0x001EB760  8bf0                    mov      esi, eax                       
                                        ; XREF: 0x001EB759 (cond_jump)
  0x001EB762  3b7d0c                  cmp      edi, dword ptr [ebp + 0xc]     
  0x001EB765  7307                    jae      0x1eb76e                       
  0x001EB767  094110                  or       dword ptr [ecx + 0x10], eax    
  0x001EB76A  d1e0                    shl      eax, 1                         
  0x001EB76C  8bf0                    mov      esi, eax                       
                                        ; XREF: 0x001EB765 (cond_jump)
  0x001EB76E  3b7d10                  cmp      edi, dword ptr [ebp + 0x10]    
  0x001EB771  7307                    jae      0x1eb77a                       
  0x001EB773  094114                  or       dword ptr [ecx + 0x14], eax    
  0x001EB776  d1e0                    shl      eax, 1                         
  0x001EB778  8bf0                    mov      esi, eax                       
                                        ; XREF: 0x001EB771 (cond_jump)
  0x001EB77A  d1e7                    shl      edi, 1                         
  0x001EB77C  3bf2                    cmp      esi, edx                       
  0x001EB77E  75d4                    jne      0x1eb754                       
  0x001EB780  5f                      pop      edi                            
  0x001EB781  5e                      pop      esi                            
  0x001EB782  5d                      pop      ebp                            
  0x001EB783  c20c00                  ret      0xc                            
; end of function

; ============================================================
; Function: sub_001EB786
; Start: 0x001EB786  End: 0x001EB7AF  Size: 41 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_001EBB43, sub_001EBBC4, sub_001EBC98, sub_001EBD1B, sub_001EBDE7, sub_001EBE62, sub_001EBF3E
; ============================================================
sub_001EB786:
  0x001EB786  8b490c                  mov      ecx, dword ptr [ecx + 0xc]     
  0x001EB789  33d2                    xor      edx, edx                       
  0x001EB78B  42                      inc      edx                            
  0x001EB78C  33c0                    xor      eax, eax                       
  0x001EB78E  3bca                    cmp      ecx, edx                       
  0x001EB790  721a                    jb       0x1eb7ac                       
  0x001EB792  56                      push     esi                            
                                        ; XREF: 0x001EB7A9 (cond_jump)
  0x001EB793  85ca                    test     edx, ecx                       
  0x001EB795  740a                    je       0x1eb7a1                       
  0x001EB797  8bf2                    mov      esi, edx                       
  0x001EB799  23742408                and      esi, dword ptr [esp + 8]       
  0x001EB79D  0bc6                    or       eax, esi                       
  0x001EB79F  eb04                    jmp      0x1eb7a5                       
                                        ; XREF: 0x001EB795 (cond_jump)
  0x001EB7A1  d1642408                shl      dword ptr [esp + 8], 1         
                                        ; XREF: 0x001EB79F (jump)
  0x001EB7A5  d1e2                    shl      edx, 1                         
  0x001EB7A7  3bd1                    cmp      edx, ecx                       
  0x001EB7A9  76e8                    jbe      0x1eb793                       
  0x001EB7AB  5e                      pop      esi                            
                                        ; XREF: 0x001EB790 (cond_jump)
  0x001EB7AC  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EB7AF
; Start: 0x001EB7AF  End: 0x001EB7D8  Size: 41 bytes
; Detection: call_target (confidence: 0.90)
; Called by: sub_001EBB43, sub_001EBBC4, sub_001EBC98, sub_001EBD1B, sub_001EBDE7, sub_001EBE62, sub_001EBF3E
; ============================================================
sub_001EB7AF:
  0x001EB7AF  8b4910                  mov      ecx, dword ptr [ecx + 0x10]    
  0x001EB7B2  33d2                    xor      edx, edx                       
  0x001EB7B4  42                      inc      edx                            
  0x001EB7B5  33c0                    xor      eax, eax                       
  0x001EB7B7  3bca                    cmp      ecx, edx                       
  0x001EB7B9  721a                    jb       0x1eb7d5                       
  0x001EB7BB  56                      push     esi                            
                                        ; XREF: 0x001EB7D2 (cond_jump)
  0x001EB7BC  85ca                    test     edx, ecx                       
  0x001EB7BE  740a                    je       0x1eb7ca                       
  0x001EB7C0  8bf2                    mov      esi, edx                       
  0x001EB7C2  23742408                and      esi, dword ptr [esp + 8]       
  0x001EB7C6  0bc6                    or       eax, esi                       
  0x001EB7C8  eb04                    jmp      0x1eb7ce                       
                                        ; XREF: 0x001EB7BE (cond_jump)
  0x001EB7CA  d1642408                shl      dword ptr [esp + 8], 1         
                                        ; XREF: 0x001EB7C8 (jump)
  0x001EB7CE  d1e2                    shl      edx, 1                         
  0x001EB7D0  3bd1                    cmp      edx, ecx                       
  0x001EB7D2  76e8                    jbe      0x1eb7bc                       
  0x001EB7D4  5e                      pop      esi                            
                                        ; XREF: 0x001EB7B9 (cond_jump)
  0x001EB7D5  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EB7D8
; Start: 0x001EB7D8  End: 0x001EB84C  Size: 116 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_001EB19C
; Called by: sub_001EB84C, sub_001EB94C, sub_001EBA4A
; ============================================================
sub_001EB7D8:
  0x001EB7D8  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x001EB7DC  56                      push     esi                            
  0x001EB7DD  57                      push     edi                            
  0x001EB7DE  e8b9f9ffff              call     0x1eb19c                       ; -> sub_001EB19C
  0x001EB7E3  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x001EB7E7  8bf8                    mov      edi, eax                       
  0x001EB7E9  e8aef9ffff              call     0x1eb19c                       ; -> sub_001EB19C
  0x001EB7EE  3bf8                    cmp      edi, eax                       
  0x001EB7F0  8bcf                    mov      ecx, edi                       
  0x001EB7F2  7202                    jb       0x1eb7f6                       
  0x001EB7F4  8bc8                    mov      ecx, eax                       
                                        ; XREF: 0x001EB7F2 (cond_jump)
  0x001EB7F6  33d2                    xor      edx, edx                       
  0x001EB7F8  03c9                    add      ecx, ecx                       
  0x001EB7FA  42                      inc      edx                            
  0x001EB7FB  d3e2                    shl      edx, cl                        
  0x001EB7FD  4a                      dec      edx                            
  0x001EB7FE  3bf8                    cmp      edi, eax                       
  0x001EB800  8bca                    mov      ecx, edx                       
  0x001EB802  f7d1                    not      ecx                            
  0x001EB804  760a                    jbe      0x1eb810                       
  0x001EB806  8bf1                    mov      esi, ecx                       
  0x001EB808  81ce55555555            or       esi, 0x55555555                
  0x001EB80E  eb08                    jmp      0x1eb818                       
                                        ; XREF: 0x001EB804 (cond_jump)
  0x001EB810  8bf2                    mov      esi, edx                       
  0x001EB812  81e655555555            and      esi, 0x55555555                
                                        ; XREF: 0x001EB80E (jump)
  0x001EB818  3bf8                    cmp      edi, eax                       
  0x001EB81A  730a                    jae      0x1eb826                       
  0x001EB81C  81c9aaaaaaaa            or       ecx, 0xaaaaaaaa                
  0x001EB822  8bd1                    mov      edx, ecx                       
  0x001EB824  eb06                    jmp      0x1eb82c                       
                                        ; XREF: 0x001EB81A (cond_jump)
  0x001EB826  81e2aaaaaaaa            and      edx, 0xaaaaaaaa                
                                        ; XREF: 0x001EB824 (jump)
  0x001EB82C  8d0c38                  lea      ecx, [eax + edi]               
  0x001EB82F  33c0                    xor      eax, eax                       
  0x001EB831  40                      inc      eax                            
  0x001EB832  d3e0                    shl      eax, cl                        
  0x001EB834  5f                      pop      edi                            
  0x001EB835  48                      dec      eax                            
  0x001EB836  8bc8                    mov      ecx, eax                       
  0x001EB838  23ce                    and      ecx, esi                       
  0x001EB83A  8b742410                mov      esi, dword ptr [esp + 0x10]    
  0x001EB83E  890e                    mov      dword ptr [esi], ecx           
  0x001EB840  8b4c2414                mov      ecx, dword ptr [esp + 0x14]    
  0x001EB844  23c2                    and      eax, edx                       
  0x001EB846  8901                    mov      dword ptr [ecx], eax           
  0x001EB848  5e                      pop      esi                            
  0x001EB849  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_001EB84C
; Start: 0x001EB84C  End: 0x001EB94C  Size: 256 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB7D8
; Called by: sub_001EBF3E
; ============================================================
sub_001EB84C:
  0x001EB84C  55                      push     ebp                            
  0x001EB84D  8bec                    mov      ebp, esp                       
  0x001EB84F  83ec0c                  sub      esp, 0xc                       
  0x001EB852  53                      push     ebx                            
  0x001EB853  56                      push     esi                            
  0x001EB854  57                      push     edi                            
  0x001EB855  8d4514                  lea      eax, [ebp + 0x14]              
  0x001EB858  50                      push     eax                            
  0x001EB859  8d45fc                  lea      eax, [ebp - 4]                 
  0x001EB85C  50                      push     eax                            
  0x001EB85D  ff7514                  push     dword ptr [ebp + 0x14]         
  0x001EB860  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EB863  e870ffffff              call     0x1eb7d8                       ; -> sub_001EB7D8
  0x001EB868  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EB86B  83e0c0                  and      eax, 0xffffffc0                
  0x001EB86E  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x001EB871  8b4514                  mov      eax, dword ptr [ebp + 0x14]    
  0x001EB874  83e080                  and      eax, 0xffffff80                
  0x001EB877  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x001EB87A  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EB87D  8b7d0c                  mov      edi, dword ptr [ebp + 0xc]     
  0x001EB880  8b5510                  mov      edx, dword ptr [ebp + 0x10]    
  0x001EB883  33db                    xor      ebx, ebx                       
  0x001EB885  33c9                    xor      ecx, ecx                       
  0x001EB887  eb03                    jmp      0x1eb88c                       
  0x001EB889  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x001EB887 (jump), 0x001EB92C (cond_jump), 0x001EB93D (cond_jump)
  0x001EB88C  0f6f06                  movq     mm0, qword ptr [esi]           
  0x001EB88F  0f6f0c16                movq     mm1, qword ptr [esi + edx]     
  0x001EB893  03f2                    add      esi, edx                       
  0x001EB895  8bc3                    mov      eax, ebx                       
  0x001EB897  0f6f2416                movq     mm4, qword ptr [esi + edx]     
  0x001EB89B  0f6f2c56                movq     mm5, qword ptr [esi + edx*2]   
  0x001EB89F  0bc1                    or       eax, ecx                       
  0x001EB8A1  0f7fe6                  movq     mm6, mm4                       
  0x001EB8A4  0f7fc2                  movq     mm2, mm0                       
  0x001EB8A7  0f69f5                  punpckhwd mm6, mm5                       
  0x001EB8AA  8d3496                  lea      esi, [esi + edx*4]             
  0x001EB8AD  0f69d1                  punpckhwd mm2, mm1                       
  0x001EB8B0  0f61e5                  punpcklwd mm4, mm5                       
  0x001EB8B3  0f6f1e                  movq     mm3, qword ptr [esi]           
  0x001EB8B6  0f6f2c16                movq     mm5, qword ptr [esi + edx]     
  0x001EB8BA  0f6f3c56                movq     mm7, qword ptr [esi + edx*2]   
  0x001EB8BE  2bf2                    sub      esi, edx                       
  0x001EB8C0  0f61c1                  punpcklwd mm0, mm1                       
  0x001EB8C3  0f6f0e                  movq     mm1, qword ptr [esi]           
  0x001EB8C6  0f7f0407                movq     qword ptr [edi + eax], mm0     
  0x001EB8CA  0f7f640708              movq     qword ptr [edi + eax + 8], mm4 
  0x001EB8CF  0f7f540710              movq     qword ptr [edi + eax + 0x10], mm2 
  0x001EB8D4  0f7f740718              movq     qword ptr [edi + eax + 0x18], mm6 
  0x001EB8D9  0f7fc8                  movq     mm0, mm1                       
  0x001EB8DC  0f7fec                  movq     mm4, mm5                       
  0x001EB8DF  0f61c3                  punpcklwd mm0, mm3                       
  0x001EB8E2  0f61e7                  punpcklwd mm4, mm7                       
  0x001EB8E5  0f69cb                  punpckhwd mm1, mm3                       
  0x001EB8E8  0f69ef                  punpckhwd mm5, mm7                       
  0x001EB8EB  0f7f440720              movq     qword ptr [edi + eax + 0x20], mm0 
  0x001EB8F0  0f7f640728              movq     qword ptr [edi + eax + 0x28], mm4 
  0x001EB8F5  0f7f4c0730              movq     qword ptr [edi + eax + 0x30], mm1 
  0x001EB8FA  0f7f6c0738              movq     qword ptr [edi + eax + 0x38], mm5 
  0x001EB8FF  2bf2                    sub      esi, edx                       
  0x001EB901  2bf2                    sub      esi, edx                       
  0x001EB903  2bf2                    sub      esi, edx                       
  0x001EB905  2bf2                    sub      esi, edx                       
  0x001EB907  2b5df4                  sub      ebx, dword ptr [ebp - 0xc]     
  0x001EB90A  90                      nop                                     
  0x001EB90B  90                      nop                                     
  0x001EB90C  90                      nop                                     
  0x001EB90D  90                      nop                                     
  0x001EB90E  90                      nop                                     
  0x001EB90F  90                      nop                                     
  0x001EB910  90                      nop                                     
  0x001EB911  90                      nop                                     
  0x001EB912  90                      nop                                     
  0x001EB913  90                      nop                                     
  0x001EB914  90                      nop                                     
  0x001EB915  90                      nop                                     
  0x001EB916  90                      nop                                     
  0x001EB917  90                      nop                                     
  0x001EB918  90                      nop                                     
  0x001EB919  90                      nop                                     
  0x001EB91A  90                      nop                                     
  0x001EB91B  90                      nop                                     
  0x001EB91C  90                      nop                                     
  0x001EB91D  90                      nop                                     
  0x001EB91E  90                      nop                                     
  0x001EB91F  90                      nop                                     
  0x001EB920  90                      nop                                     
  0x001EB921  90                      nop                                     
  0x001EB922  90                      nop                                     
  0x001EB923  90                      nop                                     
  0x001EB924  90                      nop                                     
  0x001EB925  90                      nop                                     
  0x001EB926  83c608                  add      esi, 8                         
  0x001EB929  235dfc                  and      ebx, dword ptr [ebp - 4]       
  0x001EB92C  0f855affffff            jne      0x1eb88c                       
  0x001EB932  2b4df8                  sub      ecx, dword ptr [ebp - 8]       
  0x001EB935  8d34d6                  lea      esi, [esi + edx*8]             
  0x001EB938  2bf2                    sub      esi, edx                       
  0x001EB93A  234d14                  and      ecx, dword ptr [ebp + 0x14]    
  0x001EB93D  0f8549ffffff            jne      0x1eb88c                       
  0x001EB943  0f77                    emms                                    
  0x001EB945  5f                      pop      edi                            
  0x001EB946  5e                      pop      esi                            
  0x001EB947  5b                      pop      ebx                            
  0x001EB948  c9                      leave                                   
  0x001EB949  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_001EB94C
; Start: 0x001EB94C  End: 0x001EBA4A  Size: 254 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB7D8
; Called by: sub_001EBF3E
; ============================================================
sub_001EB94C:
  0x001EB94C  55                      push     ebp                            
  0x001EB94D  8bec                    mov      ebp, esp                       
  0x001EB94F  83ec0c                  sub      esp, 0xc                       
  0x001EB952  53                      push     ebx                            
  0x001EB953  56                      push     esi                            
  0x001EB954  57                      push     edi                            
  0x001EB955  8d4514                  lea      eax, [ebp + 0x14]              
  0x001EB958  50                      push     eax                            
  0x001EB959  8d45fc                  lea      eax, [ebp - 4]                 
  0x001EB95C  50                      push     eax                            
  0x001EB95D  ff7514                  push     dword ptr [ebp + 0x14]         
  0x001EB960  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EB963  e870feffff              call     0x1eb7d8                       ; -> sub_001EB7D8
  0x001EB968  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EB96B  83e0c0                  and      eax, 0xffffffc0                
  0x001EB96E  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x001EB971  8b4514                  mov      eax, dword ptr [ebp + 0x14]    
  0x001EB974  83e080                  and      eax, 0xffffff80                
  0x001EB977  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x001EB97A  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EB97D  8b7d0c                  mov      edi, dword ptr [ebp + 0xc]     
  0x001EB980  8b5510                  mov      edx, dword ptr [ebp + 0x10]    
  0x001EB983  33db                    xor      ebx, ebx                       
  0x001EB985  33c9                    xor      ecx, ecx                       
  0x001EB987  03d2                    add      edx, edx                       
  0x001EB989  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x001EBA2C (cond_jump), 0x001EBA3D (cond_jump)
  0x001EB98C  0f1006                  movups   xmm0, xmmword ptr [esi]        
  0x001EB98F  0f100c16                movups   xmm1, xmmword ptr [esi + edx]  
  0x001EB993  03f2                    add      esi, edx                       
  0x001EB995  8bc3                    mov      eax, ebx                       
  0x001EB997  0f102416                movups   xmm4, xmmword ptr [esi + edx]  
  0x001EB99B  0f102c56                movups   xmm5, xmmword ptr [esi + edx*2] 
  0x001EB99F  0bc1                    or       eax, ecx                       
  0x001EB9A1  0f28f4                  movaps   xmm6, xmm4                     
  0x001EB9A4  0f28d0                  movaps   xmm2, xmm0                     
  0x001EB9A7  0f15f5                  unpckhps xmm6, xmm5                     
  0x001EB9AA  8d3496                  lea      esi, [esi + edx*4]             
  0x001EB9AD  0f15d1                  unpckhps xmm2, xmm1                     
  0x001EB9B0  0f14e5                  unpcklps xmm4, xmm5                     
  0x001EB9B3  0f101e                  movups   xmm3, xmmword ptr [esi]        
  0x001EB9B6  0f102c16                movups   xmm5, xmmword ptr [esi + edx]  
  0x001EB9BA  0f103c56                movups   xmm7, xmmword ptr [esi + edx*2] 
  0x001EB9BE  2bf2                    sub      esi, edx                       
  0x001EB9C0  0f14c1                  unpcklps xmm0, xmm1                     
  0x001EB9C3  0f100e                  movups   xmm1, xmmword ptr [esi]        
  0x001EB9C6  0f2b0447                movntps  xmmword ptr [edi + eax*2], xmm0 
  0x001EB9CA  0f2b644710              movntps  xmmword ptr [edi + eax*2 + 0x10], xmm4 
  0x001EB9CF  0f2b544720              movntps  xmmword ptr [edi + eax*2 + 0x20], xmm2 
  0x001EB9D4  0f2b744730              movntps  xmmword ptr [edi + eax*2 + 0x30], xmm6 
  0x001EB9D9  0f28c1                  movaps   xmm0, xmm1                     
  0x001EB9DC  0f28e5                  movaps   xmm4, xmm5                     
  0x001EB9DF  0f14c3                  unpcklps xmm0, xmm3                     
  0x001EB9E2  0f14e7                  unpcklps xmm4, xmm7                     
  0x001EB9E5  0f15cb                  unpckhps xmm1, xmm3                     
  0x001EB9E8  0f15ef                  unpckhps xmm5, xmm7                     
  0x001EB9EB  0f2b444740              movntps  xmmword ptr [edi + eax*2 + 0x40], xmm0 
  0x001EB9F0  0f2b644750              movntps  xmmword ptr [edi + eax*2 + 0x50], xmm4 
  0x001EB9F5  0f2b4c4760              movntps  xmmword ptr [edi + eax*2 + 0x60], xmm1 
  0x001EB9FA  0f2b6c4770              movntps  xmmword ptr [edi + eax*2 + 0x70], xmm5 
  0x001EB9FF  2bf2                    sub      esi, edx                       
  0x001EBA01  2bf2                    sub      esi, edx                       
  0x001EBA03  2bf2                    sub      esi, edx                       
  0x001EBA05  2bf2                    sub      esi, edx                       
  0x001EBA07  2b5df4                  sub      ebx, dword ptr [ebp - 0xc]     
  0x001EBA0A  90                      nop                                     
  0x001EBA0B  90                      nop                                     
  0x001EBA0C  90                      nop                                     
  0x001EBA0D  90                      nop                                     
  0x001EBA0E  90                      nop                                     
  0x001EBA0F  90                      nop                                     
  0x001EBA10  90                      nop                                     
  0x001EBA11  90                      nop                                     
  0x001EBA12  90                      nop                                     
  0x001EBA13  90                      nop                                     
  0x001EBA14  90                      nop                                     
  0x001EBA15  90                      nop                                     
  0x001EBA16  90                      nop                                     
  0x001EBA17  90                      nop                                     
  0x001EBA18  90                      nop                                     
  0x001EBA19  90                      nop                                     
  0x001EBA1A  90                      nop                                     
  0x001EBA1B  90                      nop                                     
  0x001EBA1C  90                      nop                                     
  0x001EBA1D  90                      nop                                     
  0x001EBA1E  90                      nop                                     
  0x001EBA1F  90                      nop                                     
  0x001EBA20  90                      nop                                     
  0x001EBA21  90                      nop                                     
  0x001EBA22  90                      nop                                     
  0x001EBA23  90                      nop                                     
  0x001EBA24  90                      nop                                     
  0x001EBA25  90                      nop                                     
  0x001EBA26  83c610                  add      esi, 0x10                      
  0x001EBA29  235dfc                  and      ebx, dword ptr [ebp - 4]       
  0x001EBA2C  0f855affffff            jne      0x1eb98c                       
  0x001EBA32  2b4df8                  sub      ecx, dword ptr [ebp - 8]       
  0x001EBA35  8d34d6                  lea      esi, [esi + edx*8]             
  0x001EBA38  2bf2                    sub      esi, edx                       
  0x001EBA3A  234d14                  and      ecx, dword ptr [ebp + 0x14]    
  0x001EBA3D  0f8549ffffff            jne      0x1eb98c                       
  0x001EBA43  5f                      pop      edi                            
  0x001EBA44  5e                      pop      esi                            
  0x001EBA45  5b                      pop      ebx                            
  0x001EBA46  c9                      leave                                   
  0x001EBA47  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_001EBA4A
; Start: 0x001EBA4A  End: 0x001EBB43  Size: 249 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB7D8
; Called by: sub_001EBF3E
; ============================================================
sub_001EBA4A:
  0x001EBA4A  55                      push     ebp                            
  0x001EBA4B  8bec                    mov      ebp, esp                       
  0x001EBA4D  83ec0c                  sub      esp, 0xc                       
  0x001EBA50  53                      push     ebx                            
  0x001EBA51  56                      push     esi                            
  0x001EBA52  57                      push     edi                            
  0x001EBA53  8d4514                  lea      eax, [ebp + 0x14]              
  0x001EBA56  50                      push     eax                            
  0x001EBA57  8d45fc                  lea      eax, [ebp - 4]                 
  0x001EBA5A  50                      push     eax                            
  0x001EBA5B  ff7514                  push     dword ptr [ebp + 0x14]         
  0x001EBA5E  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EBA61  e872fdffff              call     0x1eb7d8                       ; -> sub_001EB7D8
  0x001EBA66  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EBA69  83e0c0                  and      eax, 0xffffffc0                
  0x001EBA6C  8945f4                  mov      dword ptr [ebp - 0xc], eax     
  0x001EBA6F  8b4514                  mov      eax, dword ptr [ebp + 0x14]    
  0x001EBA72  83e0e0                  and      eax, 0xffffffe0                
  0x001EBA75  8945f8                  mov      dword ptr [ebp - 8], eax       
  0x001EBA78  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EBA7B  8b7d0c                  mov      edi, dword ptr [ebp + 0xc]     
  0x001EBA7E  8b5510                  mov      edx, dword ptr [ebp + 0x10]    
  0x001EBA81  33db                    xor      ebx, ebx                       
  0x001EBA83  33c9                    xor      ecx, ecx                       
  0x001EBA85  c1e202                  shl      edx, 2                         
  0x001EBA88  8bff                    mov      edi, edi                       
                                        ; XREF: 0x001EBB25 (cond_jump), 0x001EBB36 (cond_jump)
  0x001EBA8A  8bc3                    mov      eax, ebx                       
  0x001EBA8C  0f1006                  movups   xmm0, xmmword ptr [esi]        
  0x001EBA8F  0f106610                movups   xmm4, xmmword ptr [esi + 0x10] 
  0x001EBA93  0f101416                movups   xmm2, xmmword ptr [esi + edx]  
  0x001EBA97  0f10741610              movups   xmm6, xmmword ptr [esi + edx + 0x10] 
  0x001EBA9C  0f28c8                  movaps   xmm1, xmm0                     
  0x001EBA9F  0f28ec                  movaps   xmm5, xmm4                     
  0x001EBAA2  8d3456                  lea      esi, [esi + edx*2]             
  0x001EBAA5  0bc1                    or       eax, ecx                       
  0x001EBAA7  0f16c2                  movlhps  xmm0, xmm2                     
  0x001EBAAA  0f12d1                  movhlps  xmm2, xmm1                     
  0x001EBAAD  0f16e6                  movlhps  xmm4, xmm6                     
  0x001EBAB0  0f12f5                  movhlps  xmm6, xmm5                     
  0x001EBAB3  0f100e                  movups   xmm1, xmmword ptr [esi]        
  0x001EBAB6  0f106e10                movups   xmm5, xmmword ptr [esi + 0x10] 
  0x001EBABA  0f101c16                movups   xmm3, xmmword ptr [esi + edx]  
  0x001EBABE  0f107c1610              movups   xmm7, xmmword ptr [esi + edx + 0x10] 
  0x001EBAC3  0f2b0487                movntps  xmmword ptr [edi + eax*4], xmm0 
  0x001EBAC7  0f2b548710              movntps  xmmword ptr [edi + eax*4 + 0x10], xmm2 
  0x001EBACC  0f2b648740              movntps  xmmword ptr [edi + eax*4 + 0x40], xmm4 
  0x001EBAD1  0f2b748750              movntps  xmmword ptr [edi + eax*4 + 0x50], xmm6 
  0x001EBAD6  0f28c1                  movaps   xmm0, xmm1                     
  0x001EBAD9  0f28e5                  movaps   xmm4, xmm5                     
  0x001EBADC  0f16cb                  movlhps  xmm1, xmm3                     
  0x001EBADF  0f12d8                  movhlps  xmm3, xmm0                     
  0x001EBAE2  0f16ef                  movlhps  xmm5, xmm7                     
  0x001EBAE5  0f12fc                  movhlps  xmm7, xmm4                     
  0x001EBAE8  0f2b4c8720              movntps  xmmword ptr [edi + eax*4 + 0x20], xmm1 
  0x001EBAED  0f2b5c8730              movntps  xmmword ptr [edi + eax*4 + 0x30], xmm3 
  0x001EBAF2  0f2b6c8760              movntps  xmmword ptr [edi + eax*4 + 0x60], xmm5 
  0x001EBAF7  0f2b7c8770              movntps  xmmword ptr [edi + eax*4 + 0x70], xmm7 
  0x001EBAFC  2bf2                    sub      esi, edx                       
  0x001EBAFE  2bf2                    sub      esi, edx                       
  0x001EBB00  90                      nop                                     
  0x001EBB01  90                      nop                                     
  0x001EBB02  90                      nop                                     
  0x001EBB03  90                      nop                                     
  0x001EBB04  90                      nop                                     
  0x001EBB05  90                      nop                                     
  0x001EBB06  90                      nop                                     
  0x001EBB07  90                      nop                                     
  0x001EBB08  90                      nop                                     
  0x001EBB09  90                      nop                                     
  0x001EBB0A  90                      nop                                     
  0x001EBB0B  90                      nop                                     
  0x001EBB0C  90                      nop                                     
  0x001EBB0D  90                      nop                                     
  0x001EBB0E  90                      nop                                     
  0x001EBB0F  90                      nop                                     
  0x001EBB10  90                      nop                                     
  0x001EBB11  90                      nop                                     
  0x001EBB12  90                      nop                                     
  0x001EBB13  90                      nop                                     
  0x001EBB14  90                      nop                                     
  0x001EBB15  90                      nop                                     
  0x001EBB16  90                      nop                                     
  0x001EBB17  90                      nop                                     
  0x001EBB18  90                      nop                                     
  0x001EBB19  90                      nop                                     
  0x001EBB1A  90                      nop                                     
  0x001EBB1B  90                      nop                                     
  0x001EBB1C  2b5df4                  sub      ebx, dword ptr [ebp - 0xc]     
  0x001EBB1F  83c620                  add      esi, 0x20                      
  0x001EBB22  235dfc                  and      ebx, dword ptr [ebp - 4]       
  0x001EBB25  0f855fffffff            jne      0x1eba8a                       
  0x001EBB2B  2b4df8                  sub      ecx, dword ptr [ebp - 8]       
  0x001EBB2E  8d3496                  lea      esi, [esi + edx*4]             
  0x001EBB31  2bf2                    sub      esi, edx                       
  0x001EBB33  234d14                  and      ecx, dword ptr [ebp + 0x14]    
  0x001EBB36  0f854effffff            jne      0x1eba8a                       
  0x001EBB3C  5f                      pop      edi                            
  0x001EBB3D  5e                      pop      esi                            
  0x001EBB3E  5b                      pop      ebx                            
  0x001EBB3F  c9                      leave                                   
  0x001EBB40  c21000                  ret      0x10                           
; end of function

; ============================================================
; Function: sub_001EBB43
; Start: 0x001EBB43  End: 0x001EBBC4  Size: 129 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB786, sub_001EB7AF
; Called by: sub_001EBF3E
; ============================================================
sub_001EBB43:
  0x001EBB43  55                      push     ebp                            
  0x001EBB44  8bec                    mov      ebp, esp                       
  0x001EBB46  53                      push     ebx                            
  0x001EBB47  56                      push     esi                            
  0x001EBB48  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EBB4B  8b5e2c                  mov      ebx, dword ptr [esi + 0x2c]    
  0x001EBB4E  8b4628                  mov      eax, dword ptr [esi + 0x28]    
  0x001EBB51  57                      push     edi                            
  0x001EBB52  03c3                    add      eax, ebx                       
  0x001EBB54  8d7e40                  lea      edi, [esi + 0x40]              
  0x001EBB57  50                      push     eax                            
  0x001EBB58  8bcf                    mov      ecx, edi                       
  0x001EBB5A  e827fcffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EBB5F  8b4e24                  mov      ecx, dword ptr [esi + 0x24]    
  0x001EBB62  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EBB65  8b4630                  mov      eax, dword ptr [esi + 0x30]    
  0x001EBB68  03c8                    add      ecx, eax                       
  0x001EBB6A  51                      push     ecx                            
  0x001EBB6B  8bcf                    mov      ecx, edi                       
  0x001EBB6D  e83dfcffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EBB72  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x001EBB75  8b5508                  mov      edx, dword ptr [ebp + 8]       
  0x001EBB78  83665800                and      dword ptr [esi + 0x58], 0      
  0x001EBB7C  89465c                  mov      dword ptr [esi + 0x5c], eax    
  0x001EBB7F  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x001EBB82  034630                  add      eax, dword ptr [esi + 0x30]    
  0x001EBB85  03cb                    add      ecx, ebx                       
  0x001EBB87  0faf4604                imul     eax, dword ptr [esi + 4]       
  0x001EBB8B  8d0488                  lea      eax, [eax + ecx*4]             
  0x001EBB8E  8b4e18                  mov      ecx, dword ptr [esi + 0x18]    
  0x001EBB91  0306                    add      eax, dword ptr [esi]           
  0x001EBB93  8d0c91                  lea      ecx, [ecx + edx*4]             
  0x001EBB96  8b5638                  mov      edx, dword ptr [esi + 0x38]    
  0x001EBB99  85d2                    test     edx, edx                       
  0x001EBB9B  7420                    je       0x1ebbbd                       
  0x001EBB9D  895508                  mov      dword ptr [ebp + 8], edx       
                                        ; XREF: 0x001EBBBB (cond_jump)
  0x001EBBA0  8b18                    mov      ebx, dword ptr [eax]           
  0x001EBBA2  8b565c                  mov      edx, dword ptr [esi + 0x5c]    
  0x001EBBA5  891c91                  mov      dword ptr [ecx + edx*4], ebx   
  0x001EBBA8  8b5710                  mov      edx, dword ptr [edi + 0x10]    
  0x001EBBAB  8b5f1c                  mov      ebx, dword ptr [edi + 0x1c]    
  0x001EBBAE  2bda                    sub      ebx, edx                       
  0x001EBBB0  23da                    and      ebx, edx                       
  0x001EBBB2  895f1c                  mov      dword ptr [edi + 0x1c], ebx    
  0x001EBBB5  034604                  add      eax, dword ptr [esi + 4]       
  0x001EBBB8  ff4d08                  dec      dword ptr [ebp + 8]            
  0x001EBBBB  75e3                    jne      0x1ebba0                       
                                        ; XREF: 0x001EBB9B (cond_jump)
  0x001EBBBD  5f                      pop      edi                            
  0x001EBBBE  5e                      pop      esi                            
  0x001EBBBF  5b                      pop      ebx                            
  0x001EBBC0  5d                      pop      ebp                            
  0x001EBBC1  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EBBC4
; Start: 0x001EBBC4  End: 0x001EBC98  Size: 212 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB786, sub_001EB7AF
; Called by: sub_001EBF3E
; ============================================================
sub_001EBBC4:
  0x001EBBC4  55                      push     ebp                            
  0x001EBBC5  8bec                    mov      ebp, esp                       
  0x001EBBC7  51                      push     ecx                            
  0x001EBBC8  51                      push     ecx                            
  0x001EBBC9  53                      push     ebx                            
  0x001EBBCA  56                      push     esi                            
  0x001EBBCB  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EBBCE  8b462c                  mov      eax, dword ptr [esi + 0x2c]    
  0x001EBBD1  8b5628                  mov      edx, dword ptr [esi + 0x28]    
  0x001EBBD4  8b5e50                  mov      ebx, dword ptr [esi + 0x50]    
  0x001EBBD7  57                      push     edi                            
  0x001EBBD8  8b7e4c                  mov      edi, dword ptr [esi + 0x4c]    
  0x001EBBDB  03d0                    add      edx, eax                       
  0x001EBBDD  8d4e40                  lea      ecx, [esi + 0x40]              
  0x001EBBE0  52                      push     edx                            
  0x001EBBE1  897e64                  mov      dword ptr [esi + 0x64], edi    
  0x001EBBE4  895e68                  mov      dword ptr [esi + 0x68], ebx    
  0x001EBBE7  e89afbffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EBBEC  8b4e24                  mov      ecx, dword ptr [esi + 0x24]    
  0x001EBBEF  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EBBF2  8b4630                  mov      eax, dword ptr [esi + 0x30]    
  0x001EBBF5  03c8                    add      ecx, eax                       
  0x001EBBF7  51                      push     ecx                            
  0x001EBBF8  8d4e40                  lea      ecx, [esi + 0x40]              
  0x001EBBFB  e8affbffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EBC00  8b5634                  mov      edx, dword ptr [esi + 0x34]    
  0x001EBC03  8b4e04                  mov      ecx, dword ptr [esi + 4]       
  0x001EBC06  d16d08                  shr      dword ptr [ebp + 8], 1         
  0x001EBC09  d1ef                    shr      edi, 1                         
  0x001EBC0B  897e4c                  mov      dword ptr [esi + 0x4c], edi    
  0x001EBC0E  d1e2                    shl      edx, 1                         
  0x001EBC10  8bfa                    mov      edi, edx                       
  0x001EBC12  8bd1                    mov      edx, ecx                       
  0x001EBC14  2bd7                    sub      edx, edi                       
  0x001EBC16  8b7e0c                  mov      edi, dword ptr [esi + 0xc]     
  0x001EBC19  037e30                  add      edi, dword ptr [esi + 0x30]    
  0x001EBC1C  d1e8                    shr      eax, 1                         
  0x001EBC1E  0faff9                  imul     edi, ecx                       
  0x001EBC21  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x001EBC24  034e2c                  add      ecx, dword ptr [esi + 0x2c]    
  0x001EBC27  89465c                  mov      dword ptr [esi + 0x5c], eax    
  0x001EBC2A  8b4638                  mov      eax, dword ptr [esi + 0x38]    
  0x001EBC2D  8d0c4f                  lea      ecx, [edi + ecx*2]             
  0x001EBC30  030e                    add      ecx, dword ptr [esi]           
  0x001EBC32  8b7e18                  mov      edi, dword ptr [esi + 0x18]    
  0x001EBC35  d1eb                    shr      ebx, 1                         
  0x001EBC37  85c0                    test     eax, eax                       
  0x001EBC39  895e50                  mov      dword ptr [esi + 0x50], ebx    
  0x001EBC3C  7447                    je       0x1ebc85                       
  0x001EBC3E  8945f8                  mov      dword ptr [ebp - 8], eax       
                                        ; XREF: 0x001EBC83 (cond_jump)
  0x001EBC41  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x001EBC44  894658                  mov      dword ptr [esi + 0x58], eax    
  0x001EBC47  8b4634                  mov      eax, dword ptr [esi + 0x34]    
  0x001EBC4A  d1f8                    sar      eax, 1                         
  0x001EBC4C  7423                    je       0x1ebc71                       
  0x001EBC4E  8945fc                  mov      dword ptr [ebp - 4], eax       
                                        ; XREF: 0x001EBC6F (cond_jump)
  0x001EBC51  8b465c                  mov      eax, dword ptr [esi + 0x5c]    
  0x001EBC54  0b4658                  or       eax, dword ptr [esi + 0x58]    
  0x001EBC57  8b19                    mov      ebx, dword ptr [ecx]           
  0x001EBC59  891c87                  mov      dword ptr [edi + eax*4], ebx   
  0x001EBC5C  8b464c                  mov      eax, dword ptr [esi + 0x4c]    
  0x001EBC5F  8b5e58                  mov      ebx, dword ptr [esi + 0x58]    
  0x001EBC62  2bd8                    sub      ebx, eax                       
  0x001EBC64  23d8                    and      ebx, eax                       
  0x001EBC66  83c104                  add      ecx, 4                         
  0x001EBC69  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EBC6C  895e58                  mov      dword ptr [esi + 0x58], ebx    
  0x001EBC6F  75e0                    jne      0x1ebc51                       
                                        ; XREF: 0x001EBC4C (cond_jump)
  0x001EBC71  8b4650                  mov      eax, dword ptr [esi + 0x50]    
  0x001EBC74  8b5e5c                  mov      ebx, dword ptr [esi + 0x5c]    
  0x001EBC77  2bd8                    sub      ebx, eax                       
  0x001EBC79  23d8                    and      ebx, eax                       
  0x001EBC7B  03ca                    add      ecx, edx                       
  0x001EBC7D  ff4df8                  dec      dword ptr [ebp - 8]            
  0x001EBC80  895e5c                  mov      dword ptr [esi + 0x5c], ebx    
  0x001EBC83  75bc                    jne      0x1ebc41                       
                                        ; XREF: 0x001EBC3C (cond_jump)
  0x001EBC85  8b4664                  mov      eax, dword ptr [esi + 0x64]    
  0x001EBC88  89464c                  mov      dword ptr [esi + 0x4c], eax    
  0x001EBC8B  8b4668                  mov      eax, dword ptr [esi + 0x68]    
  0x001EBC8E  5f                      pop      edi                            
  0x001EBC8F  894650                  mov      dword ptr [esi + 0x50], eax    
  0x001EBC92  5e                      pop      esi                            
  0x001EBC93  5b                      pop      ebx                            
  0x001EBC94  c9                      leave                                   
  0x001EBC95  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EBC98
; Start: 0x001EBC98  End: 0x001EBD1B  Size: 131 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB786, sub_001EB7AF
; Called by: sub_001EBF3E
; ============================================================
sub_001EBC98:
  0x001EBC98  55                      push     ebp                            
  0x001EBC99  8bec                    mov      ebp, esp                       
  0x001EBC9B  53                      push     ebx                            
  0x001EBC9C  56                      push     esi                            
  0x001EBC9D  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EBCA0  8b5e2c                  mov      ebx, dword ptr [esi + 0x2c]    
  0x001EBCA3  8b4628                  mov      eax, dword ptr [esi + 0x28]    
  0x001EBCA6  57                      push     edi                            
  0x001EBCA7  03c3                    add      eax, ebx                       
  0x001EBCA9  8d7e40                  lea      edi, [esi + 0x40]              
  0x001EBCAC  50                      push     eax                            
  0x001EBCAD  8bcf                    mov      ecx, edi                       
  0x001EBCAF  e8d2faffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EBCB4  8b4e24                  mov      ecx, dword ptr [esi + 0x24]    
  0x001EBCB7  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EBCBA  8b4630                  mov      eax, dword ptr [esi + 0x30]    
  0x001EBCBD  03c8                    add      ecx, eax                       
  0x001EBCBF  51                      push     ecx                            
  0x001EBCC0  8bcf                    mov      ecx, edi                       
  0x001EBCC2  e8e8faffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EBCC7  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x001EBCCA  8b5508                  mov      edx, dword ptr [ebp + 8]       
  0x001EBCCD  83665800                and      dword ptr [esi + 0x58], 0      
  0x001EBCD1  89465c                  mov      dword ptr [esi + 0x5c], eax    
  0x001EBCD4  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x001EBCD7  034630                  add      eax, dword ptr [esi + 0x30]    
  0x001EBCDA  03cb                    add      ecx, ebx                       
  0x001EBCDC  0faf4604                imul     eax, dword ptr [esi + 4]       
  0x001EBCE0  8d0448                  lea      eax, [eax + ecx*2]             
  0x001EBCE3  8b4e18                  mov      ecx, dword ptr [esi + 0x18]    
  0x001EBCE6  0306                    add      eax, dword ptr [esi]           
  0x001EBCE8  8d0c51                  lea      ecx, [ecx + edx*2]             
  0x001EBCEB  8b5638                  mov      edx, dword ptr [esi + 0x38]    
  0x001EBCEE  85d2                    test     edx, edx                       
  0x001EBCF0  7422                    je       0x1ebd14                       
  0x001EBCF2  895508                  mov      dword ptr [ebp + 8], edx       
                                        ; XREF: 0x001EBD12 (cond_jump)
  0x001EBCF5  668b18                  mov      bx, word ptr [eax]             
  0x001EBCF8  8b565c                  mov      edx, dword ptr [esi + 0x5c]    
  0x001EBCFB  66891c51                mov      word ptr [ecx + edx*2], bx     
  0x001EBCFF  8b5710                  mov      edx, dword ptr [edi + 0x10]    
  0x001EBD02  8b5f1c                  mov      ebx, dword ptr [edi + 0x1c]    
  0x001EBD05  2bda                    sub      ebx, edx                       
  0x001EBD07  23da                    and      ebx, edx                       
  0x001EBD09  895f1c                  mov      dword ptr [edi + 0x1c], ebx    
  0x001EBD0C  034604                  add      eax, dword ptr [esi + 4]       
  0x001EBD0F  ff4d08                  dec      dword ptr [ebp + 8]            
  0x001EBD12  75e1                    jne      0x1ebcf5                       
                                        ; XREF: 0x001EBCF0 (cond_jump)
  0x001EBD14  5f                      pop      edi                            
  0x001EBD15  5e                      pop      esi                            
  0x001EBD16  5b                      pop      ebx                            
  0x001EBD17  5d                      pop      ebp                            
  0x001EBD18  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EBD1B
; Start: 0x001EBD1B  End: 0x001EBDE7  Size: 204 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB786, sub_001EB7AF
; Called by: sub_001EBF3E
; ============================================================
sub_001EBD1B:
  0x001EBD1B  55                      push     ebp                            
  0x001EBD1C  8bec                    mov      ebp, esp                       
  0x001EBD1E  51                      push     ecx                            
  0x001EBD1F  51                      push     ecx                            
  0x001EBD20  53                      push     ebx                            
  0x001EBD21  56                      push     esi                            
  0x001EBD22  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EBD25  8b462c                  mov      eax, dword ptr [esi + 0x2c]    
  0x001EBD28  8b5628                  mov      edx, dword ptr [esi + 0x28]    
  0x001EBD2B  8b5e50                  mov      ebx, dword ptr [esi + 0x50]    
  0x001EBD2E  57                      push     edi                            
  0x001EBD2F  8b7e4c                  mov      edi, dword ptr [esi + 0x4c]    
  0x001EBD32  03d0                    add      edx, eax                       
  0x001EBD34  8d4e40                  lea      ecx, [esi + 0x40]              
  0x001EBD37  52                      push     edx                            
  0x001EBD38  897e64                  mov      dword ptr [esi + 0x64], edi    
  0x001EBD3B  895e68                  mov      dword ptr [esi + 0x68], ebx    
  0x001EBD3E  e843faffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EBD43  8b4e24                  mov      ecx, dword ptr [esi + 0x24]    
  0x001EBD46  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EBD49  8b4630                  mov      eax, dword ptr [esi + 0x30]    
  0x001EBD4C  03c8                    add      ecx, eax                       
  0x001EBD4E  51                      push     ecx                            
  0x001EBD4F  8d4e40                  lea      ecx, [esi + 0x40]              
  0x001EBD52  e858faffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EBD57  8b4e0c                  mov      ecx, dword ptr [esi + 0xc]     
  0x001EBD5A  034e30                  add      ecx, dword ptr [esi + 0x30]    
  0x001EBD5D  d16d08                  shr      dword ptr [ebp + 8], 1         
  0x001EBD60  d1ef                    shr      edi, 1                         
  0x001EBD62  897e4c                  mov      dword ptr [esi + 0x4c], edi    
  0x001EBD65  8b7e04                  mov      edi, dword ptr [esi + 4]       
  0x001EBD68  0fafcf                  imul     ecx, edi                       
  0x001EBD6B  034e08                  add      ecx, dword ptr [esi + 8]       
  0x001EBD6E  d1e8                    shr      eax, 1                         
  0x001EBD70  034e2c                  add      ecx, dword ptr [esi + 0x2c]    
  0x001EBD73  8bd7                    mov      edx, edi                       
  0x001EBD75  2b5634                  sub      edx, dword ptr [esi + 0x34]    
  0x001EBD78  030e                    add      ecx, dword ptr [esi]           
  0x001EBD7A  8b7e18                  mov      edi, dword ptr [esi + 0x18]    
  0x001EBD7D  89465c                  mov      dword ptr [esi + 0x5c], eax    
  0x001EBD80  8b4638                  mov      eax, dword ptr [esi + 0x38]    
  0x001EBD83  d1eb                    shr      ebx, 1                         
  0x001EBD85  85c0                    test     eax, eax                       
  0x001EBD87  895e50                  mov      dword ptr [esi + 0x50], ebx    
  0x001EBD8A  7448                    je       0x1ebdd4                       
  0x001EBD8C  8945f8                  mov      dword ptr [ebp - 8], eax       
                                        ; XREF: 0x001EBDD2 (cond_jump)
  0x001EBD8F  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x001EBD92  894658                  mov      dword ptr [esi + 0x58], eax    
  0x001EBD95  8b4634                  mov      eax, dword ptr [esi + 0x34]    
  0x001EBD98  d1f8                    sar      eax, 1                         
  0x001EBD9A  7424                    je       0x1ebdc0                       
  0x001EBD9C  8945fc                  mov      dword ptr [ebp - 4], eax       
                                        ; XREF: 0x001EBDBE (cond_jump)
  0x001EBD9F  8b465c                  mov      eax, dword ptr [esi + 0x5c]    
  0x001EBDA2  0b4658                  or       eax, dword ptr [esi + 0x58]    
  0x001EBDA5  668b19                  mov      bx, word ptr [ecx]             
  0x001EBDA8  66891c47                mov      word ptr [edi + eax*2], bx     
  0x001EBDAC  8b464c                  mov      eax, dword ptr [esi + 0x4c]    
  0x001EBDAF  8b5e58                  mov      ebx, dword ptr [esi + 0x58]    
  0x001EBDB2  41                      inc      ecx                            
  0x001EBDB3  2bd8                    sub      ebx, eax                       
  0x001EBDB5  23d8                    and      ebx, eax                       
  0x001EBDB7  41                      inc      ecx                            
  0x001EBDB8  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EBDBB  895e58                  mov      dword ptr [esi + 0x58], ebx    
  0x001EBDBE  75df                    jne      0x1ebd9f                       
                                        ; XREF: 0x001EBD9A (cond_jump)
  0x001EBDC0  8b4650                  mov      eax, dword ptr [esi + 0x50]    
  0x001EBDC3  8b5e5c                  mov      ebx, dword ptr [esi + 0x5c]    
  0x001EBDC6  2bd8                    sub      ebx, eax                       
  0x001EBDC8  23d8                    and      ebx, eax                       
  0x001EBDCA  03ca                    add      ecx, edx                       
  0x001EBDCC  ff4df8                  dec      dword ptr [ebp - 8]            
  0x001EBDCF  895e5c                  mov      dword ptr [esi + 0x5c], ebx    
  0x001EBDD2  75bb                    jne      0x1ebd8f                       
                                        ; XREF: 0x001EBD8A (cond_jump)
  0x001EBDD4  8b4664                  mov      eax, dword ptr [esi + 0x64]    
  0x001EBDD7  89464c                  mov      dword ptr [esi + 0x4c], eax    
  0x001EBDDA  8b4668                  mov      eax, dword ptr [esi + 0x68]    
  0x001EBDDD  5f                      pop      edi                            
  0x001EBDDE  894650                  mov      dword ptr [esi + 0x50], eax    
  0x001EBDE1  5e                      pop      esi                            
  0x001EBDE2  5b                      pop      ebx                            
  0x001EBDE3  c9                      leave                                   
  0x001EBDE4  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EBDE7
; Start: 0x001EBDE7  End: 0x001EBE62  Size: 123 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB786, sub_001EB7AF
; Called by: sub_001EBF3E
; ============================================================
sub_001EBDE7:
  0x001EBDE7  55                      push     ebp                            
  0x001EBDE8  8bec                    mov      ebp, esp                       
  0x001EBDEA  53                      push     ebx                            
  0x001EBDEB  56                      push     esi                            
  0x001EBDEC  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EBDEF  8b5e2c                  mov      ebx, dword ptr [esi + 0x2c]    
  0x001EBDF2  8b4628                  mov      eax, dword ptr [esi + 0x28]    
  0x001EBDF5  57                      push     edi                            
  0x001EBDF6  03c3                    add      eax, ebx                       
  0x001EBDF8  8d7e40                  lea      edi, [esi + 0x40]              
  0x001EBDFB  50                      push     eax                            
  0x001EBDFC  8bcf                    mov      ecx, edi                       
  0x001EBDFE  e883f9ffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EBE03  8b4e24                  mov      ecx, dword ptr [esi + 0x24]    
  0x001EBE06  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EBE09  8b4630                  mov      eax, dword ptr [esi + 0x30]    
  0x001EBE0C  03c8                    add      ecx, eax                       
  0x001EBE0E  51                      push     ecx                            
  0x001EBE0F  8bcf                    mov      ecx, edi                       
  0x001EBE11  e899f9ffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EBE16  8b4e18                  mov      ecx, dword ptr [esi + 0x18]    
  0x001EBE19  8b5638                  mov      edx, dword ptr [esi + 0x38]    
  0x001EBE1C  83665800                and      dword ptr [esi + 0x58], 0      
  0x001EBE20  034d08                  add      ecx, dword ptr [ebp + 8]       
  0x001EBE23  89465c                  mov      dword ptr [esi + 0x5c], eax    
  0x001EBE26  8b460c                  mov      eax, dword ptr [esi + 0xc]     
  0x001EBE29  034630                  add      eax, dword ptr [esi + 0x30]    
  0x001EBE2C  0faf4604                imul     eax, dword ptr [esi + 4]       
  0x001EBE30  034608                  add      eax, dword ptr [esi + 8]       
  0x001EBE33  03c3                    add      eax, ebx                       
  0x001EBE35  0306                    add      eax, dword ptr [esi]           
  0x001EBE37  85d2                    test     edx, edx                       
  0x001EBE39  7420                    je       0x1ebe5b                       
  0x001EBE3B  895508                  mov      dword ptr [ebp + 8], edx       
                                        ; XREF: 0x001EBE59 (cond_jump)
  0x001EBE3E  8a18                    mov      bl, byte ptr [eax]             
  0x001EBE40  8b565c                  mov      edx, dword ptr [esi + 0x5c]    
  0x001EBE43  881c11                  mov      byte ptr [ecx + edx], bl       
  0x001EBE46  8b5710                  mov      edx, dword ptr [edi + 0x10]    
  0x001EBE49  8b5f1c                  mov      ebx, dword ptr [edi + 0x1c]    
  0x001EBE4C  2bda                    sub      ebx, edx                       
  0x001EBE4E  23da                    and      ebx, edx                       
  0x001EBE50  895f1c                  mov      dword ptr [edi + 0x1c], ebx    
  0x001EBE53  034604                  add      eax, dword ptr [esi + 4]       
  0x001EBE56  ff4d08                  dec      dword ptr [ebp + 8]            
  0x001EBE59  75e3                    jne      0x1ebe3e                       
                                        ; XREF: 0x001EBE39 (cond_jump)
  0x001EBE5B  5f                      pop      edi                            
  0x001EBE5C  5e                      pop      esi                            
  0x001EBE5D  5b                      pop      ebx                            
  0x001EBE5E  5d                      pop      ebp                            
  0x001EBE5F  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EBE62
; Start: 0x001EBE62  End: 0x001EBF3E  Size: 220 bytes
; Detection: prologue (confidence: 0.95)
; Calls: sub_001EB786, sub_001EB7AF
; Called by: sub_001EBF3E
; ============================================================
sub_001EBE62:
  0x001EBE62  55                      push     ebp                            
  0x001EBE63  8bec                    mov      ebp, esp                       
  0x001EBE65  51                      push     ecx                            
  0x001EBE66  51                      push     ecx                            
  0x001EBE67  53                      push     ebx                            
  0x001EBE68  56                      push     esi                            
  0x001EBE69  8b7508                  mov      esi, dword ptr [ebp + 8]       
  0x001EBE6C  8b462c                  mov      eax, dword ptr [esi + 0x2c]    
  0x001EBE6F  8b5628                  mov      edx, dword ptr [esi + 0x28]    
  0x001EBE72  8b5e50                  mov      ebx, dword ptr [esi + 0x50]    
  0x001EBE75  57                      push     edi                            
  0x001EBE76  8b7e4c                  mov      edi, dword ptr [esi + 0x4c]    
  0x001EBE79  03d0                    add      edx, eax                       
  0x001EBE7B  8d4e40                  lea      ecx, [esi + 0x40]              
  0x001EBE7E  52                      push     edx                            
  0x001EBE7F  897e64                  mov      dword ptr [esi + 0x64], edi    
  0x001EBE82  895e68                  mov      dword ptr [esi + 0x68], ebx    
  0x001EBE85  e8fcf8ffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EBE8A  8b4e24                  mov      ecx, dword ptr [esi + 0x24]    
  0x001EBE8D  894508                  mov      dword ptr [ebp + 8], eax       
  0x001EBE90  8b4630                  mov      eax, dword ptr [esi + 0x30]    
  0x001EBE93  03c8                    add      ecx, eax                       
  0x001EBE95  51                      push     ecx                            
  0x001EBE96  8d4e40                  lea      ecx, [esi + 0x40]              
  0x001EBE99  e811f9ffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EBE9E  8b5634                  mov      edx, dword ptr [esi + 0x34]    
  0x001EBEA1  8b4e04                  mov      ecx, dword ptr [esi + 4]       
  0x001EBEA4  d16d08                  shr      dword ptr [ebp + 8], 1         
  0x001EBEA7  d1ef                    shr      edi, 1                         
  0x001EBEA9  897e4c                  mov      dword ptr [esi + 0x4c], edi    
  0x001EBEAC  c1e202                  shl      edx, 2                         
  0x001EBEAF  8bfa                    mov      edi, edx                       
  0x001EBEB1  8bd1                    mov      edx, ecx                       
  0x001EBEB3  2bd7                    sub      edx, edi                       
  0x001EBEB5  8b7e0c                  mov      edi, dword ptr [esi + 0xc]     
  0x001EBEB8  037e30                  add      edi, dword ptr [esi + 0x30]    
  0x001EBEBB  d1e8                    shr      eax, 1                         
  0x001EBEBD  0faff9                  imul     edi, ecx                       
  0x001EBEC0  8b4e08                  mov      ecx, dword ptr [esi + 8]       
  0x001EBEC3  034e2c                  add      ecx, dword ptr [esi + 0x2c]    
  0x001EBEC6  89465c                  mov      dword ptr [esi + 0x5c], eax    
  0x001EBEC9  8b4638                  mov      eax, dword ptr [esi + 0x38]    
  0x001EBECC  8d0c8f                  lea      ecx, [edi + ecx*4]             
  0x001EBECF  030e                    add      ecx, dword ptr [esi]           
  0x001EBED1  8b7e18                  mov      edi, dword ptr [esi + 0x18]    
  0x001EBED4  d1eb                    shr      ebx, 1                         
  0x001EBED6  85c0                    test     eax, eax                       
  0x001EBED8  895e50                  mov      dword ptr [esi + 0x50], ebx    
  0x001EBEDB  744e                    je       0x1ebf2b                       
  0x001EBEDD  8945f8                  mov      dword ptr [ebp - 8], eax       
                                        ; XREF: 0x001EBF29 (cond_jump)
  0x001EBEE0  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x001EBEE3  894658                  mov      dword ptr [esi + 0x58], eax    
  0x001EBEE6  8b4634                  mov      eax, dword ptr [esi + 0x34]    
  0x001EBEE9  d1f8                    sar      eax, 1                         
  0x001EBEEB  742a                    je       0x1ebf17                       
  0x001EBEED  8945fc                  mov      dword ptr [ebp - 4], eax       
                                        ; XREF: 0x001EBF15 (cond_jump)
  0x001EBEF0  8b465c                  mov      eax, dword ptr [esi + 0x5c]    
  0x001EBEF3  0b4658                  or       eax, dword ptr [esi + 0x58]    
  0x001EBEF6  8b19                    mov      ebx, dword ptr [ecx]           
  0x001EBEF8  891cc7                  mov      dword ptr [edi + eax*8], ebx   
  0x001EBEFB  8b5904                  mov      ebx, dword ptr [ecx + 4]       
  0x001EBEFE  895cc704                mov      dword ptr [edi + eax*8 + 4], ebx 
  0x001EBF02  8b464c                  mov      eax, dword ptr [esi + 0x4c]    
  0x001EBF05  8b5e58                  mov      ebx, dword ptr [esi + 0x58]    
  0x001EBF08  2bd8                    sub      ebx, eax                       
  0x001EBF0A  23d8                    and      ebx, eax                       
  0x001EBF0C  83c108                  add      ecx, 8                         
  0x001EBF0F  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EBF12  895e58                  mov      dword ptr [esi + 0x58], ebx    
  0x001EBF15  75d9                    jne      0x1ebef0                       
                                        ; XREF: 0x001EBEEB (cond_jump)
  0x001EBF17  8b4650                  mov      eax, dword ptr [esi + 0x50]    
  0x001EBF1A  8b5e5c                  mov      ebx, dword ptr [esi + 0x5c]    
  0x001EBF1D  2bd8                    sub      ebx, eax                       
  0x001EBF1F  23d8                    and      ebx, eax                       
  0x001EBF21  03ca                    add      ecx, edx                       
  0x001EBF23  ff4df8                  dec      dword ptr [ebp - 8]            
  0x001EBF26  895e5c                  mov      dword ptr [esi + 0x5c], ebx    
  0x001EBF29  75b5                    jne      0x1ebee0                       
                                        ; XREF: 0x001EBEDB (cond_jump)
  0x001EBF2B  8b4664                  mov      eax, dword ptr [esi + 0x64]    
  0x001EBF2E  89464c                  mov      dword ptr [esi + 0x4c], eax    
  0x001EBF31  8b4668                  mov      eax, dword ptr [esi + 0x68]    
  0x001EBF34  5f                      pop      edi                            
  0x001EBF35  894650                  mov      dword ptr [esi + 0x50], eax    
  0x001EBF38  5e                      pop      esi                            
  0x001EBF39  5b                      pop      ebx                            
  0x001EBF3A  c9                      leave                                   
  0x001EBF3B  c20400                  ret      4                              
; end of function

; ============================================================
; Function: sub_001EBF3E
; Start: 0x001EBF3E  End: 0x001EC68F  Size: 1873 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_001EB706, sub_001EB725, sub_001EB786, sub_001EB7AF, sub_001EB84C, sub_001EB94C, sub_001EBA4A, sub_001EBB43, sub_001EBBC4, sub_001EBC98 ... (+3 more)
; Called by: sub_00123390
; ============================================================
sub_001EBF3E:
  0x001EBF3E  55                      push     ebp                            
  0x001EBF3F  8d6c24a8                lea      ebp, [esp - 0x58]              
  0x001EBF43  81ec9c000000            sub      esp, 0x9c                      
  0x001EBF49  53                      push     ebx                            
  0x001EBF4A  56                      push     esi                            
  0x001EBF4B  57                      push     edi                            
  0x001EBF4C  8b7d70                  mov      edi, dword ptr [ebp + 0x70]    
  0x001EBF4F  83ff02                  cmp      edi, 2                         
  0x001EBF52  6a10                    push     0x10                           
  0x001EBF54  5a                      pop      edx                            
  0x001EBF55  6a08                    push     8                              
  0x001EBF57  59                      pop      ecx                            
  0x001EBF58  6a07                    push     7                              
  0x001EBF5A  58                      pop      eax                            
  0x001EBF5B  6a03                    push     3                              
  0x001EBF5D  8945c8                  mov      dword ptr [ebp - 0x38], eax    
  0x001EBF60  8945cc                  mov      dword ptr [ebp - 0x34], eax    
  0x001EBF63  8945d0                  mov      dword ptr [ebp - 0x30], eax    
  0x001EBF66  8945bc                  mov      dword ptr [ebp - 0x44], eax    
  0x001EBF69  8945c0                  mov      dword ptr [ebp - 0x40], eax    
  0x001EBF6C  58                      pop      eax                            
  0x001EBF6D  8955e0                  mov      dword ptr [ebp - 0x20], edx    
  0x001EBF70  8955e4                  mov      dword ptr [ebp - 0x1c], edx    
  0x001EBF73  894de8                  mov      dword ptr [ebp - 0x18], ecx    
  0x001EBF76  894dd4                  mov      dword ptr [ebp - 0x2c], ecx    
  0x001EBF79  894dd8                  mov      dword ptr [ebp - 0x28], ecx    
  0x001EBF7C  894ddc                  mov      dword ptr [ebp - 0x24], ecx    
  0x001EBF7F  8945c4                  mov      dword ptr [ebp - 0x3c], eax    
  0x001EBF82  0f86e0060000            jbe      0x1ec668                       
  0x001EBF88  837d7401                cmp      dword ptr [ebp + 0x74], 1      
  0x001EBF8C  0f86d6060000            jbe      0x1ec668                       
  0x001EBF92  8b5d68                  mov      ebx, dword ptr [ebp + 0x68]    
  0x001EBF95  85db                    test     ebx, ebx                       
  0x001EBF97  8b757c                  mov      esi, dword ptr [ebp + 0x7c]    
  0x001EBF9A  756d                    jne      0x1ec009                       
  0x001EBF9C  837d7800                cmp      dword ptr [ebp + 0x78], 0      
  0x001EBFA0  7567                    jne      0x1ec009                       
  0x001EBFA2  837d6400                cmp      dword ptr [ebp + 0x64], 0      
  0x001EBFA6  7561                    jne      0x1ec009                       
  0x001EBFA8  83fe04                  cmp      esi, 4                         
  0x001EBFAB  751d                    jne      0x1ebfca                       
  0x001EBFAD  3bf9                    cmp      edi, ecx                       
  0x001EBFAF  7258                    jb       0x1ec009                       
  0x001EBFB1  394d74                  cmp      dword ptr [ebp + 0x74], ecx    
  0x001EBFB4  7253                    jb       0x1ec009                       
  0x001EBFB6  ff7574                  push     dword ptr [ebp + 0x74]         
  0x001EBFB9  57                      push     edi                            
  0x001EBFBA  ff756c                  push     dword ptr [ebp + 0x6c]         
  0x001EBFBD  ff7560                  push     dword ptr [ebp + 0x60]         
  0x001EBFC0  e885faffff              call     0x1eba4a                       ; -> sub_001EBA4A
  0x001EBFC5  e9bb060000              jmp      0x1ec685                       
                                        ; XREF: 0x001EBFAB (cond_jump)
  0x001EBFCA  83fe02                  cmp      esi, 2                         
  0x001EBFCD  751d                    jne      0x1ebfec                       
  0x001EBFCF  3bfa                    cmp      edi, edx                       
  0x001EBFD1  7236                    jb       0x1ec009                       
  0x001EBFD3  394d74                  cmp      dword ptr [ebp + 0x74], ecx    
  0x001EBFD6  7231                    jb       0x1ec009                       
  0x001EBFD8  ff7574                  push     dword ptr [ebp + 0x74]         
  0x001EBFDB  57                      push     edi                            
  0x001EBFDC  ff756c                  push     dword ptr [ebp + 0x6c]         
  0x001EBFDF  ff7560                  push     dword ptr [ebp + 0x60]         
  0x001EBFE2  e865f9ffff              call     0x1eb94c                       ; -> sub_001EB94C
  0x001EBFE7  e999060000              jmp      0x1ec685                       
                                        ; XREF: 0x001EBFCD (cond_jump)
  0x001EBFEC  3bfa                    cmp      edi, edx                       
  0x001EBFEE  7219                    jb       0x1ec009                       
  0x001EBFF0  394d74                  cmp      dword ptr [ebp + 0x74], ecx    
  0x001EBFF3  7214                    jb       0x1ec009                       
  0x001EBFF5  ff7574                  push     dword ptr [ebp + 0x74]         
  0x001EBFF8  57                      push     edi                            
  0x001EBFF9  ff756c                  push     dword ptr [ebp + 0x6c]         
  0x001EBFFC  ff7560                  push     dword ptr [ebp + 0x60]         
  0x001EBFFF  e848f8ffff              call     0x1eb84c                       ; -> sub_001EB84C
  0x001EC004  e97c060000              jmp      0x1ec685                       
                                        ; XREF: 0x001EBF9A (cond_jump), 0x001EBFA0 (cond_jump), 0x001EBFA6 (cond_jump), 0x001EBFAF (cond_jump), 0x001EBFB4 (cond_jump), ... (+4 more)
  0x001EC009  8d4d2c                  lea      ecx, [ebp + 0x2c]              
  0x001EC00C  e8f5f6ffff              call     0x1eb706                       ; -> sub_001EB706
  0x001EC011  8b4578                  mov      eax, dword ptr [ebp + 0x78]    
  0x001EC014  85c0                    test     eax, eax                       
  0x001EC016  8b5574                  mov      edx, dword ptr [ebp + 0x74]    
  0x001EC019  897528                  mov      dword ptr [ebp + 0x28], esi    
  0x001EC01C  89550c                  mov      dword ptr [ebp + 0xc], edx     
  0x001EC01F  897d08                  mov      dword ptr [ebp + 8], edi       
  0x001EC022  7508                    jne      0x1ec02c                       
  0x001EC024  214514                  and      dword ptr [ebp + 0x14], eax    
  0x001EC027  214510                  and      dword ptr [ebp + 0x10], eax    
  0x001EC02A  eb0b                    jmp      0x1ec037                       
                                        ; XREF: 0x001EC022 (cond_jump)
  0x001EC02C  8b08                    mov      ecx, dword ptr [eax]           
  0x001EC02E  8b4004                  mov      eax, dword ptr [eax + 4]       
  0x001EC031  894d14                  mov      dword ptr [ebp + 0x14], ecx    
  0x001EC034  894510                  mov      dword ptr [ebp + 0x10], eax    
                                        ; XREF: 0x001EC02A (jump)
  0x001EC037  85db                    test     ebx, ebx                       
  0x001EC039  8b456c                  mov      eax, dword ptr [ebp + 0x6c]    
  0x001EC03C  894504                  mov      dword ptr [ebp + 4], eax       
  0x001EC03F  8b4560                  mov      eax, dword ptr [ebp + 0x60]    
  0x001EC042  8945ec                  mov      dword ptr [ebp - 0x14], eax    
  0x001EC045  750e                    jne      0x1ec055                       
  0x001EC047  215df4                  and      dword ptr [ebp - 0xc], ebx     
  0x001EC04A  215df8                  and      dword ptr [ebp - 8], ebx       
  0x001EC04D  895500                  mov      dword ptr [ebp], edx           
  0x001EC050  897dfc                  mov      dword ptr [ebp - 4], edi       
  0x001EC053  eb1b                    jmp      0x1ec070                       
                                        ; XREF: 0x001EC045 (cond_jump)
  0x001EC055  8b4304                  mov      eax, dword ptr [ebx + 4]       
  0x001EC058  8b4b0c                  mov      ecx, dword ptr [ebx + 0xc]     
  0x001EC05B  2bc8                    sub      ecx, eax                       
  0x001EC05D  894d00                  mov      dword ptr [ebp], ecx           
  0x001EC060  8b0b                    mov      ecx, dword ptr [ebx]           
  0x001EC062  8b5b08                  mov      ebx, dword ptr [ebx + 8]       
  0x001EC065  2bd9                    sub      ebx, ecx                       
  0x001EC067  895dfc                  mov      dword ptr [ebp - 4], ebx       
  0x001EC06A  894df4                  mov      dword ptr [ebp - 0xc], ecx     
  0x001EC06D  8945f8                  mov      dword ptr [ebp - 8], eax       
                                        ; XREF: 0x001EC053 (jump)
  0x001EC070  8b4564                  mov      eax, dword ptr [ebp + 0x64]    
  0x001EC073  85c0                    test     eax, eax                       
  0x001EC075  7505                    jne      0x1ec07c                       
  0x001EC077  8bc7                    mov      eax, edi                       
  0x001EC079  0fafc6                  imul     eax, esi                       
                                        ; XREF: 0x001EC075 (cond_jump)
  0x001EC07C  6a00                    push     0                              
  0x001EC07E  52                      push     edx                            
  0x001EC07F  57                      push     edi                            
  0x001EC080  8d4d2c                  lea      ecx, [ebp + 0x2c]              
  0x001EC083  8945f0                  mov      dword ptr [ebp - 0x10], eax    
  0x001EC086  e89af6ffff              call     0x1eb725                       ; -> sub_001EB725
  0x001EC08B  8b4538                  mov      eax, dword ptr [ebp + 0x38]    
  0x001EC08E  894550                  mov      dword ptr [ebp + 0x50], eax    
  0x001EC091  8b453c                  mov      eax, dword ptr [ebp + 0x3c]    
  0x001EC094  894554                  mov      dword ptr [ebp + 0x54], eax    
  0x001EC097  8b4500                  mov      eax, dword ptr [ebp]           
  0x001EC09A  33c9                    xor      ecx, ecx                       
  0x001EC09C  3bc1                    cmp      eax, ecx                       
  0x001EC09E  0f84e1050000            je       0x1ec685                       
  0x001EC0A4  394dfc                  cmp      dword ptr [ebp - 4], ecx       
  0x001EC0A7  0f84d8050000            je       0x1ec685                       
  0x001EC0AD  d1ee                    shr      esi, 1                         
  0x001EC0AF  c1e602                  shl      esi, 2                         
  0x001EC0B2  f6451401                test     byte ptr [ebp + 0x14], 1       
  0x001EC0B6  8b5c35c8                mov      ebx, dword ptr [ebp + esi - 0x38] 
  0x001EC0BA  8b7c35bc                mov      edi, dword ptr [ebp + esi - 0x44] 
  0x001EC0BE  895d74                  mov      dword ptr [ebp + 0x74], ebx    
  0x001EC0C1  7445                    je       0x1ec108                       
  0x001EC0C3  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC0C7  894524                  mov      dword ptr [ebp + 0x24], eax    
  0x001EC0CA  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EC0CD  894d18                  mov      dword ptr [ebp + 0x18], ecx    
  0x001EC0D0  894d1c                  mov      dword ptr [ebp + 0x1c], ecx    
  0x001EC0D3  c7452001000000          mov      dword ptr [ebp + 0x20], 1      
  0x001EC0DA  50                      push     eax                            
  0x001EC0DB  7507                    jne      0x1ec0e4                       
  0x001EC0DD  e861faffff              call     0x1ebb43                       ; -> sub_001EBB43
  0x001EC0E2  eb12                    jmp      0x1ec0f6                       
                                        ; XREF: 0x001EC0DB (cond_jump)
  0x001EC0E4  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC0E8  7507                    jne      0x1ec0f1                       
  0x001EC0EA  e8a9fbffff              call     0x1ebc98                       ; -> sub_001EBC98
  0x001EC0EF  eb05                    jmp      0x1ec0f6                       
                                        ; XREF: 0x001EC0E8 (cond_jump)
  0x001EC0F1  e8f1fcffff              call     0x1ebde7                       ; -> sub_001EBDE7
                                        ; XREF: 0x001EC0E2 (jump), 0x001EC0EF (jump)
  0x001EC0F6  ff45f4                  inc      dword ptr [ebp - 0xc]          
  0x001EC0F9  ff4514                  inc      dword ptr [ebp + 0x14]         
  0x001EC0FC  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EC0FF  0f8480050000            je       0x1ec685                       
  0x001EC105  8b4500                  mov      eax, dword ptr [ebp]           
                                        ; XREF: 0x001EC0C1 (cond_jump)
  0x001EC108  f645fc01                test     byte ptr [ebp - 4], 1          
  0x001EC10C  7444                    je       0x1ec152                       
  0x001EC10E  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EC111  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x001EC114  83651c00                and      dword ptr [ebp + 0x1c], 0      
  0x001EC118  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC11C  894524                  mov      dword ptr [ebp + 0x24], eax    
  0x001EC11F  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EC122  894d18                  mov      dword ptr [ebp + 0x18], ecx    
  0x001EC125  c7452001000000          mov      dword ptr [ebp + 0x20], 1      
  0x001EC12C  50                      push     eax                            
  0x001EC12D  7507                    jne      0x1ec136                       
  0x001EC12F  e80ffaffff              call     0x1ebb43                       ; -> sub_001EBB43
  0x001EC134  eb12                    jmp      0x1ec148                       
                                        ; XREF: 0x001EC12D (cond_jump)
  0x001EC136  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC13A  7507                    jne      0x1ec143                       
  0x001EC13C  e857fbffff              call     0x1ebc98                       ; -> sub_001EBC98
  0x001EC141  eb05                    jmp      0x1ec148                       
                                        ; XREF: 0x001EC13A (cond_jump)
  0x001EC143  e89ffcffff              call     0x1ebde7                       ; -> sub_001EBDE7
                                        ; XREF: 0x001EC134 (jump), 0x001EC141 (jump)
  0x001EC148  837dfc00                cmp      dword ptr [ebp - 4], 0         
  0x001EC14C  0f8433050000            je       0x1ec685                       
                                        ; XREF: 0x001EC10C (cond_jump)
  0x001EC152  8b4d14                  mov      ecx, dword ptr [ebp + 0x14]    
  0x001EC155  8b55fc                  mov      edx, dword ptr [ebp - 4]       
  0x001EC158  8bc3                    mov      eax, ebx                       
  0x001EC15A  f7d0                    not      eax                            
  0x001EC15C  03d9                    add      ebx, ecx                       
  0x001EC15E  03d1                    add      edx, ecx                       
  0x001EC160  23d8                    and      ebx, eax                       
  0x001EC162  23d0                    and      edx, eax                       
  0x001EC164  3bda                    cmp      ebx, edx                       
  0x001EC166  0f83c3040000            jae      0x1ec62f                       
  0x001EC16C  8b4d10                  mov      ecx, dword ptr [ebp + 0x10]    
  0x001EC16F  8b5d00                  mov      ebx, dword ptr [ebp]           
  0x001EC172  8bc7                    mov      eax, edi                       
  0x001EC174  f7d0                    not      eax                            
  0x001EC176  03d9                    add      ebx, ecx                       
  0x001EC178  8d140f                  lea      edx, [edi + ecx]               
  0x001EC17B  23d0                    and      edx, eax                       
  0x001EC17D  23d8                    and      ebx, eax                       
  0x001EC17F  3bd3                    cmp      edx, ebx                       
  0x001EC181  0f83a8040000            jae      0x1ec62f                       
  0x001EC187  8b4508                  mov      eax, dword ptr [ebp + 8]       
  0x001EC18A  3b4435e0                cmp      eax, dword ptr [ebp + esi - 0x20] 
  0x001EC18E  0f829b040000            jb       0x1ec62f                       
  0x001EC194  8b450c                  mov      eax, dword ptr [ebp + 0xc]     
  0x001EC197  3b4435d4                cmp      eax, dword ptr [ebp + esi - 0x2c] 
  0x001EC19B  0f828e040000            jb       0x1ec62f                       
  0x001EC1A1  33db                    xor      ebx, ebx                       
  0x001EC1A3  85f9                    test     ecx, edi                       
  0x001EC1A5  7441                    je       0x1ec1e8                       
  0x001EC1A7  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EC1AA  f7d9                    neg      ecx                            
  0x001EC1AC  23cf                    and      ecx, edi                       
  0x001EC1AE  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC1B2  894520                  mov      dword ptr [ebp + 0x20], eax    
  0x001EC1B5  8bf1                    mov      esi, ecx                       
  0x001EC1B7  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EC1BA  895d18                  mov      dword ptr [ebp + 0x18], ebx    
  0x001EC1BD  895d1c                  mov      dword ptr [ebp + 0x1c], ebx    
  0x001EC1C0  897524                  mov      dword ptr [ebp + 0x24], esi    
  0x001EC1C3  50                      push     eax                            
  0x001EC1C4  7507                    jne      0x1ec1cd                       
  0x001EC1C6  e897fcffff              call     0x1ebe62                       ; -> sub_001EBE62
  0x001EC1CB  eb12                    jmp      0x1ec1df                       
                                        ; XREF: 0x001EC1C4 (cond_jump)
  0x001EC1CD  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC1D1  7507                    jne      0x1ec1da                       
  0x001EC1D3  e8ecf9ffff              call     0x1ebbc4                       ; -> sub_001EBBC4
  0x001EC1D8  eb05                    jmp      0x1ec1df                       
                                        ; XREF: 0x001EC1D1 (cond_jump)
  0x001EC1DA  e83cfbffff              call     0x1ebd1b                       ; -> sub_001EBD1B
                                        ; XREF: 0x001EC1CB (jump), 0x001EC1D8 (jump)
  0x001EC1DF  0175f8                  add      dword ptr [ebp - 8], esi       
  0x001EC1E2  017510                  add      dword ptr [ebp + 0x10], esi    
  0x001EC1E5  297500                  sub      dword ptr [ebp], esi           
                                        ; XREF: 0x001EC1A5 (cond_jump)
  0x001EC1E8  8bc7                    mov      eax, edi                       
  0x001EC1EA  234500                  and      eax, dword ptr [ebp]           
  0x001EC1ED  7438                    je       0x1ec227                       
  0x001EC1EF  294500                  sub      dword ptr [ebp], eax           
  0x001EC1F2  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC1F6  8b4d00                  mov      ecx, dword ptr [ebp]           
  0x001EC1F9  894d1c                  mov      dword ptr [ebp + 0x1c], ecx    
  0x001EC1FC  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x001EC1FF  894524                  mov      dword ptr [ebp + 0x24], eax    
  0x001EC202  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EC205  895d18                  mov      dword ptr [ebp + 0x18], ebx    
  0x001EC208  894d20                  mov      dword ptr [ebp + 0x20], ecx    
  0x001EC20B  50                      push     eax                            
  0x001EC20C  7507                    jne      0x1ec215                       
  0x001EC20E  e84ffcffff              call     0x1ebe62                       ; -> sub_001EBE62
  0x001EC213  eb12                    jmp      0x1ec227                       
                                        ; XREF: 0x001EC20C (cond_jump)
  0x001EC215  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC219  7507                    jne      0x1ec222                       
  0x001EC21B  e8a4f9ffff              call     0x1ebbc4                       ; -> sub_001EBBC4
  0x001EC220  eb05                    jmp      0x1ec227                       
                                        ; XREF: 0x001EC219 (cond_jump)
  0x001EC222  e8f4faffff              call     0x1ebd1b                       ; -> sub_001EBD1B
                                        ; XREF: 0x001EC1ED (cond_jump), 0x001EC213 (jump), 0x001EC220 (jump)
  0x001EC227  8b7514                  mov      esi, dword ptr [ebp + 0x14]    
  0x001EC22A  857574                  test     dword ptr [ebp + 0x74], esi    
  0x001EC22D  7447                    je       0x1ec276                       
  0x001EC22F  8b4500                  mov      eax, dword ptr [ebp]           
  0x001EC232  f7de                    neg      esi                            
  0x001EC234  237574                  and      esi, dword ptr [ebp + 0x74]    
  0x001EC237  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC23B  894524                  mov      dword ptr [ebp + 0x24], eax    
  0x001EC23E  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EC241  895d18                  mov      dword ptr [ebp + 0x18], ebx    
  0x001EC244  895d1c                  mov      dword ptr [ebp + 0x1c], ebx    
  0x001EC247  897520                  mov      dword ptr [ebp + 0x20], esi    
  0x001EC24A  50                      push     eax                            
  0x001EC24B  7507                    jne      0x1ec254                       
  0x001EC24D  e810fcffff              call     0x1ebe62                       ; -> sub_001EBE62
  0x001EC252  eb12                    jmp      0x1ec266                       
                                        ; XREF: 0x001EC24B (cond_jump)
  0x001EC254  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC258  7507                    jne      0x1ec261                       
  0x001EC25A  e865f9ffff              call     0x1ebbc4                       ; -> sub_001EBBC4
  0x001EC25F  eb05                    jmp      0x1ec266                       
                                        ; XREF: 0x001EC258 (cond_jump)
  0x001EC261  e8b5faffff              call     0x1ebd1b                       ; -> sub_001EBD1B
                                        ; XREF: 0x001EC252 (jump), 0x001EC25F (jump)
  0x001EC266  8b7df4                  mov      edi, dword ptr [ebp - 0xc]     
  0x001EC269  017514                  add      dword ptr [ebp + 0x14], esi    
  0x001EC26C  03fe                    add      edi, esi                       
  0x001EC26E  2975fc                  sub      dword ptr [ebp - 4], esi       
  0x001EC271  897df4                  mov      dword ptr [ebp - 0xc], edi     
  0x001EC274  eb03                    jmp      0x1ec279                       
                                        ; XREF: 0x001EC22D (cond_jump)
  0x001EC276  8b7df4                  mov      edi, dword ptr [ebp - 0xc]     
                                        ; XREF: 0x001EC274 (jump)
  0x001EC279  8b4574                  mov      eax, dword ptr [ebp + 0x74]    
  0x001EC27C  2345fc                  and      eax, dword ptr [ebp - 4]       
  0x001EC27F  743b                    je       0x1ec2bc                       
  0x001EC281  2945fc                  sub      dword ptr [ebp - 4], eax       
  0x001EC284  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC288  8b4dfc                  mov      ecx, dword ptr [ebp - 4]       
  0x001EC28B  894520                  mov      dword ptr [ebp + 0x20], eax    
  0x001EC28E  8b4500                  mov      eax, dword ptr [ebp]           
  0x001EC291  894524                  mov      dword ptr [ebp + 0x24], eax    
  0x001EC294  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EC297  894d18                  mov      dword ptr [ebp + 0x18], ecx    
  0x001EC29A  895d1c                  mov      dword ptr [ebp + 0x1c], ebx    
  0x001EC29D  50                      push     eax                            
  0x001EC29E  7507                    jne      0x1ec2a7                       
  0x001EC2A0  e8bdfbffff              call     0x1ebe62                       ; -> sub_001EBE62
  0x001EC2A5  eb12                    jmp      0x1ec2b9                       
                                        ; XREF: 0x001EC29E (cond_jump)
  0x001EC2A7  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC2AB  7507                    jne      0x1ec2b4                       
  0x001EC2AD  e812f9ffff              call     0x1ebbc4                       ; -> sub_001EBBC4
  0x001EC2B2  eb05                    jmp      0x1ec2b9                       
                                        ; XREF: 0x001EC2AB (cond_jump)
  0x001EC2B4  e862faffff              call     0x1ebd1b                       ; -> sub_001EBD1B
                                        ; XREF: 0x001EC2A5 (jump), 0x001EC2B2 (jump)
  0x001EC2B9  8b7df4                  mov      edi, dword ptr [ebp - 0xc]     
                                        ; XREF: 0x001EC27F (cond_jump)
  0x001EC2BC  8b4538                  mov      eax, dword ptr [ebp + 0x38]    
  0x001EC2BF  ff7514                  push     dword ptr [ebp + 0x14]         
  0x001EC2C2  83e0c0                  and      eax, 0xffffffc0                
  0x001EC2C5  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC2C9  89456c                  mov      dword ptr [ebp + 0x6c], eax    
  0x001EC2CC  8b453c                  mov      eax, dword ptr [ebp + 0x3c]    
  0x001EC2CF  8d4d2c                  lea      ecx, [ebp + 0x2c]              
  0x001EC2D2  0f8523010000            jne      0x1ec3fb                       
  0x001EC2D8  83e0e0                  and      eax, 0xffffffe0                
  0x001EC2DB  894574                  mov      dword ptr [ebp + 0x74], eax    
  0x001EC2DE  e8a3f4ffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EC2E3  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EC2E6  8d4d2c                  lea      ecx, [ebp + 0x2c]              
  0x001EC2E9  894564                  mov      dword ptr [ebp + 0x64], eax    
  0x001EC2EC  e8bef4ffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EC2F1  c16dfc03                shr      dword ptr [ebp - 4], 3         
  0x001EC2F5  894578                  mov      dword ptr [ebp + 0x78], eax    
  0x001EC2F8  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x001EC2FB  0faf45f8                imul     eax, dword ptr [ebp - 8]       
  0x001EC2FF  0345ec                  add      eax, dword ptr [ebp - 0x14]    
  0x001EC302  c16d0002                shr      dword ptr [ebp], 2             
  0x001EC306  8d04b8                  lea      eax, [eax + edi*4]             
  0x001EC309  8945ec                  mov      dword ptr [ebp - 0x14], eax    
  0x001EC30C  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EC30F  894560                  mov      dword ptr [ebp + 0x60], eax    
  0x001EC312  8b75ec                  mov      esi, dword ptr [ebp - 0x14]    
  0x001EC315  8b7d04                  mov      edi, dword ptr [ebp + 4]       
  0x001EC318  8b5508                  mov      edx, dword ptr [ebp + 8]       
  0x001EC31B  c1e202                  shl      edx, 2                         
  0x001EC31E  8b5d64                  mov      ebx, dword ptr [ebp + 0x64]    
  0x001EC321  8b4d78                  mov      ecx, dword ptr [ebp + 0x78]    
  0x001EC324  89757c                  mov      dword ptr [ebp + 0x7c], esi    
  0x001EC327  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x001EC3CC (cond_jump), 0x001EC3F0 (cond_jump)
  0x001EC32E  8bc3                    mov      eax, ebx                       
  0x001EC330  0f1006                  movups   xmm0, xmmword ptr [esi]        
  0x001EC333  0f106610                movups   xmm4, xmmword ptr [esi + 0x10] 
  0x001EC337  0f101416                movups   xmm2, xmmword ptr [esi + edx]  
  0x001EC33B  0f10741610              movups   xmm6, xmmword ptr [esi + edx + 0x10] 
  0x001EC340  0f28c8                  movaps   xmm1, xmm0                     
  0x001EC343  0f28ec                  movaps   xmm5, xmm4                     
  0x001EC346  8d3456                  lea      esi, [esi + edx*2]             
  0x001EC349  0bc1                    or       eax, ecx                       
  0x001EC34B  0f16c2                  movlhps  xmm0, xmm2                     
  0x001EC34E  0f12d1                  movhlps  xmm2, xmm1                     
  0x001EC351  0f16e6                  movlhps  xmm4, xmm6                     
  0x001EC354  0f12f5                  movhlps  xmm6, xmm5                     
  0x001EC357  0f100e                  movups   xmm1, xmmword ptr [esi]        
  0x001EC35A  0f106e10                movups   xmm5, xmmword ptr [esi + 0x10] 
  0x001EC35E  0f101c16                movups   xmm3, xmmword ptr [esi + edx]  
  0x001EC362  0f107c1610              movups   xmm7, xmmword ptr [esi + edx + 0x10] 
  0x001EC367  0f2b0487                movntps  xmmword ptr [edi + eax*4], xmm0 
  0x001EC36B  0f2b548710              movntps  xmmword ptr [edi + eax*4 + 0x10], xmm2 
  0x001EC370  0f2b648740              movntps  xmmword ptr [edi + eax*4 + 0x40], xmm4 
  0x001EC375  0f2b748750              movntps  xmmword ptr [edi + eax*4 + 0x50], xmm6 
  0x001EC37A  0f28c1                  movaps   xmm0, xmm1                     
  0x001EC37D  0f28e5                  movaps   xmm4, xmm5                     
  0x001EC380  0f16cb                  movlhps  xmm1, xmm3                     
  0x001EC383  0f12d8                  movhlps  xmm3, xmm0                     
  0x001EC386  0f16ef                  movlhps  xmm5, xmm7                     
  0x001EC389  0f12fc                  movhlps  xmm7, xmm4                     
  0x001EC38C  0f2b4c8720              movntps  xmmword ptr [edi + eax*4 + 0x20], xmm1 
  0x001EC391  0f2b5c8730              movntps  xmmword ptr [edi + eax*4 + 0x30], xmm3 
  0x001EC396  0f2b6c8760              movntps  xmmword ptr [edi + eax*4 + 0x60], xmm5 
  0x001EC39B  0f2b7c8770              movntps  xmmword ptr [edi + eax*4 + 0x70], xmm7 
  0x001EC3A0  2bf2                    sub      esi, edx                       
  0x001EC3A2  2bf2                    sub      esi, edx                       
  0x001EC3A4  90                      nop                                     
  0x001EC3A5  90                      nop                                     
  0x001EC3A6  90                      nop                                     
  0x001EC3A7  90                      nop                                     
  0x001EC3A8  90                      nop                                     
  0x001EC3A9  90                      nop                                     
  0x001EC3AA  90                      nop                                     
  0x001EC3AB  90                      nop                                     
  0x001EC3AC  90                      nop                                     
  0x001EC3AD  90                      nop                                     
  0x001EC3AE  90                      nop                                     
  0x001EC3AF  90                      nop                                     
  0x001EC3B0  90                      nop                                     
  0x001EC3B1  90                      nop                                     
  0x001EC3B2  90                      nop                                     
  0x001EC3B3  90                      nop                                     
  0x001EC3B4  90                      nop                                     
  0x001EC3B5  90                      nop                                     
  0x001EC3B6  90                      nop                                     
  0x001EC3B7  90                      nop                                     
  0x001EC3B8  90                      nop                                     
  0x001EC3B9  90                      nop                                     
  0x001EC3BA  90                      nop                                     
  0x001EC3BB  90                      nop                                     
  0x001EC3BC  90                      nop                                     
  0x001EC3BD  90                      nop                                     
  0x001EC3BE  90                      nop                                     
  0x001EC3BF  90                      nop                                     
  0x001EC3C0  2b5d6c                  sub      ebx, dword ptr [ebp + 0x6c]    
  0x001EC3C3  83c620                  add      esi, 0x20                      
  0x001EC3C6  235d38                  and      ebx, dword ptr [ebp + 0x38]    
  0x001EC3C9  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EC3CC  0f855cffffff            jne      0x1ec32e                       
  0x001EC3D2  8b7560                  mov      esi, dword ptr [ebp + 0x60]    
  0x001EC3D5  8b5d64                  mov      ebx, dword ptr [ebp + 0x64]    
  0x001EC3D8  8975fc                  mov      dword ptr [ebp - 4], esi       
  0x001EC3DB  8b757c                  mov      esi, dword ptr [ebp + 0x7c]    
  0x001EC3DE  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x001EC3E1  2b4d74                  sub      ecx, dword ptr [ebp + 0x74]    
  0x001EC3E4  8d3486                  lea      esi, [esi + eax*4]             
  0x001EC3E7  234d3c                  and      ecx, dword ptr [ebp + 0x3c]    
  0x001EC3EA  89757c                  mov      dword ptr [ebp + 0x7c], esi    
  0x001EC3ED  ff4d00                  dec      dword ptr [ebp]                
  0x001EC3F0  0f8538ffffff            jne      0x1ec32e                       
  0x001EC3F6  e98a020000              jmp      0x1ec685                       
                                        ; XREF: 0x001EC2D2 (cond_jump)
  0x001EC3FB  83e080                  and      eax, 0xffffff80                
  0x001EC3FE  894574                  mov      dword ptr [ebp + 0x74], eax    
  0x001EC401  e880f3ffff              call     0x1eb786                       ; -> sub_001EB786
  0x001EC406  ff7510                  push     dword ptr [ebp + 0x10]         
  0x001EC409  8d4d2c                  lea      ecx, [ebp + 0x2c]              
  0x001EC40C  894564                  mov      dword ptr [ebp + 0x64], eax    
  0x001EC40F  e89bf3ffff              call     0x1eb7af                       ; -> sub_001EB7AF
  0x001EC414  c16dfc03                shr      dword ptr [ebp - 4], 3         
  0x001EC418  894578                  mov      dword ptr [ebp + 0x78], eax    
  0x001EC41B  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x001EC41E  0faf45f8                imul     eax, dword ptr [ebp - 8]       
  0x001EC422  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC426  0f8504010000            jne      0x1ec530                       
  0x001EC42C  0345ec                  add      eax, dword ptr [ebp - 0x14]    
  0x001EC42F  c16d0003                shr      dword ptr [ebp], 3             
  0x001EC433  8d0478                  lea      eax, [eax + edi*2]             
  0x001EC436  8945ec                  mov      dword ptr [ebp - 0x14], eax    
  0x001EC439  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EC43C  894560                  mov      dword ptr [ebp + 0x60], eax    
  0x001EC43F  8b75ec                  mov      esi, dword ptr [ebp - 0x14]    
  0x001EC442  8b7d04                  mov      edi, dword ptr [ebp + 4]       
  0x001EC445  8b5508                  mov      edx, dword ptr [ebp + 8]       
  0x001EC448  d1e2                    shl      edx, 1                         
  0x001EC44A  8b5d64                  mov      ebx, dword ptr [ebp + 0x64]    
  0x001EC44D  8b4d78                  mov      ecx, dword ptr [ebp + 0x78]    
  0x001EC450  89757c                  mov      dword ptr [ebp + 0x7c], esi    
  0x001EC453  eb09                    jmp      0x1ec45e                       
  0x001EC455  8da42400000000          lea      esp, [esp]                     
  0x001EC45C  8bff                    mov      edi, edi                       
                                        ; XREF: 0x001EC453 (jump), 0x001EC501 (cond_jump), 0x001EC525 (cond_jump)
  0x001EC45E  0f1006                  movups   xmm0, xmmword ptr [esi]        
  0x001EC461  0f100c16                movups   xmm1, xmmword ptr [esi + edx]  
  0x001EC465  03f2                    add      esi, edx                       
  0x001EC467  8bc3                    mov      eax, ebx                       
  0x001EC469  0f102416                movups   xmm4, xmmword ptr [esi + edx]  
  0x001EC46D  0f102c56                movups   xmm5, xmmword ptr [esi + edx*2] 
  0x001EC471  0bc1                    or       eax, ecx                       
  0x001EC473  0f28d0                  movaps   xmm2, xmm0                     
  0x001EC476  0f28f4                  movaps   xmm6, xmm4                     
  0x001EC479  0f15f5                  unpckhps xmm6, xmm5                     
  0x001EC47C  8d3496                  lea      esi, [esi + edx*4]             
  0x001EC47F  0f15d1                  unpckhps xmm2, xmm1                     
  0x001EC482  0f14e5                  unpcklps xmm4, xmm5                     
  0x001EC485  0f101e                  movups   xmm3, xmmword ptr [esi]        
  0x001EC488  0f102c16                movups   xmm5, xmmword ptr [esi + edx]  
  0x001EC48C  0f103c56                movups   xmm7, xmmword ptr [esi + edx*2] 
  0x001EC490  2bf2                    sub      esi, edx                       
  0x001EC492  0f14c1                  unpcklps xmm0, xmm1                     
  0x001EC495  0f100e                  movups   xmm1, xmmword ptr [esi]        
  0x001EC498  0f2b0447                movntps  xmmword ptr [edi + eax*2], xmm0 
  0x001EC49C  0f2b644710              movntps  xmmword ptr [edi + eax*2 + 0x10], xmm4 
  0x001EC4A1  0f2b544720              movntps  xmmword ptr [edi + eax*2 + 0x20], xmm2 
  0x001EC4A6  0f2b744730              movntps  xmmword ptr [edi + eax*2 + 0x30], xmm6 
  0x001EC4AB  0f28c1                  movaps   xmm0, xmm1                     
  0x001EC4AE  0f28e5                  movaps   xmm4, xmm5                     
  0x001EC4B1  0f14c3                  unpcklps xmm0, xmm3                     
  0x001EC4B4  0f14e7                  unpcklps xmm4, xmm7                     
  0x001EC4B7  0f15cb                  unpckhps xmm1, xmm3                     
  0x001EC4BA  0f15ef                  unpckhps xmm5, xmm7                     
  0x001EC4BD  0f2b444740              movntps  xmmword ptr [edi + eax*2 + 0x40], xmm0 
  0x001EC4C2  0f2b644750              movntps  xmmword ptr [edi + eax*2 + 0x50], xmm4 
  0x001EC4C7  0f2b4c4760              movntps  xmmword ptr [edi + eax*2 + 0x60], xmm1 
  0x001EC4CC  0f2b6c4770              movntps  xmmword ptr [edi + eax*2 + 0x70], xmm5 
  0x001EC4D1  2bf2                    sub      esi, edx                       
  0x001EC4D3  2bf2                    sub      esi, edx                       
  0x001EC4D5  2bf2                    sub      esi, edx                       
  0x001EC4D7  2bf2                    sub      esi, edx                       
  0x001EC4D9  2b5d6c                  sub      ebx, dword ptr [ebp + 0x6c]    
  0x001EC4DC  90                      nop                                     
  0x001EC4DD  90                      nop                                     
  0x001EC4DE  90                      nop                                     
  0x001EC4DF  90                      nop                                     
  0x001EC4E0  90                      nop                                     
  0x001EC4E1  90                      nop                                     
  0x001EC4E2  90                      nop                                     
  0x001EC4E3  90                      nop                                     
  0x001EC4E4  90                      nop                                     
  0x001EC4E5  90                      nop                                     
  0x001EC4E6  90                      nop                                     
  0x001EC4E7  90                      nop                                     
  0x001EC4E8  90                      nop                                     
  0x001EC4E9  90                      nop                                     
  0x001EC4EA  90                      nop                                     
  0x001EC4EB  90                      nop                                     
  0x001EC4EC  90                      nop                                     
  0x001EC4ED  90                      nop                                     
  0x001EC4EE  90                      nop                                     
  0x001EC4EF  90                      nop                                     
  0x001EC4F0  90                      nop                                     
  0x001EC4F1  90                      nop                                     
  0x001EC4F2  90                      nop                                     
  0x001EC4F3  90                      nop                                     
  0x001EC4F4  90                      nop                                     
  0x001EC4F5  90                      nop                                     
  0x001EC4F6  90                      nop                                     
  0x001EC4F7  90                      nop                                     
  0x001EC4F8  83c610                  add      esi, 0x10                      
  0x001EC4FB  235d38                  and      ebx, dword ptr [ebp + 0x38]    
  0x001EC4FE  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EC501  0f8557ffffff            jne      0x1ec45e                       
  0x001EC507  8b7560                  mov      esi, dword ptr [ebp + 0x60]    
  0x001EC50A  8b5d64                  mov      ebx, dword ptr [ebp + 0x64]    
  0x001EC50D  8975fc                  mov      dword ptr [ebp - 4], esi       
  0x001EC510  8b757c                  mov      esi, dword ptr [ebp + 0x7c]    
  0x001EC513  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x001EC516  2b4d74                  sub      ecx, dword ptr [ebp + 0x74]    
  0x001EC519  8d34c6                  lea      esi, [esi + eax*8]             
  0x001EC51C  234d3c                  and      ecx, dword ptr [ebp + 0x3c]    
  0x001EC51F  89757c                  mov      dword ptr [ebp + 0x7c], esi    
  0x001EC522  ff4d00                  dec      dword ptr [ebp]                
  0x001EC525  0f8533ffffff            jne      0x1ec45e                       
  0x001EC52B  e955010000              jmp      0x1ec685                       
                                        ; XREF: 0x001EC426 (cond_jump)
  0x001EC530  0faf7d28                imul     edi, dword ptr [ebp + 0x28]    
  0x001EC534  037dec                  add      edi, dword ptr [ebp - 0x14]    
  0x001EC537  03f8                    add      edi, eax                       
  0x001EC539  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EC53C  c16d0003                shr      dword ptr [ebp], 3             
  0x001EC540  897dec                  mov      dword ptr [ebp - 0x14], edi    
  0x001EC543  894560                  mov      dword ptr [ebp + 0x60], eax    
  0x001EC546  8b75ec                  mov      esi, dword ptr [ebp - 0x14]    
  0x001EC549  8b7d04                  mov      edi, dword ptr [ebp + 4]       
  0x001EC54C  8b5508                  mov      edx, dword ptr [ebp + 8]       
  0x001EC54F  8b5d64                  mov      ebx, dword ptr [ebp + 0x64]    
  0x001EC552  8b4d78                  mov      ecx, dword ptr [ebp + 0x78]    
  0x001EC555  89757c                  mov      dword ptr [ebp + 0x7c], esi    
  0x001EC558  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x001EC601 (cond_jump), 0x001EC625 (cond_jump)
  0x001EC55E  0f6f06                  movq     mm0, qword ptr [esi]           
  0x001EC561  0f6f0c16                movq     mm1, qword ptr [esi + edx]     
  0x001EC565  03f2                    add      esi, edx                       
  0x001EC567  8bc3                    mov      eax, ebx                       
  0x001EC569  0f6f2416                movq     mm4, qword ptr [esi + edx]     
  0x001EC56D  0f6f2c56                movq     mm5, qword ptr [esi + edx*2]   
  0x001EC571  0bc1                    or       eax, ecx                       
  0x001EC573  0f7fc2                  movq     mm2, mm0                       
  0x001EC576  0f7fe6                  movq     mm6, mm4                       
  0x001EC579  0f69f5                  punpckhwd mm6, mm5                       
  0x001EC57C  8d3496                  lea      esi, [esi + edx*4]             
  0x001EC57F  0f69d1                  punpckhwd mm2, mm1                       
  0x001EC582  0f61e5                  punpcklwd mm4, mm5                       
  0x001EC585  0f6f1e                  movq     mm3, qword ptr [esi]           
  0x001EC588  0f6f2c16                movq     mm5, qword ptr [esi + edx]     
  0x001EC58C  0f6f3c56                movq     mm7, qword ptr [esi + edx*2]   
  0x001EC590  2bf2                    sub      esi, edx                       
  0x001EC592  0f61c1                  punpcklwd mm0, mm1                       
  0x001EC595  0f6f0e                  movq     mm1, qword ptr [esi]           
  0x001EC598  0f7f0407                movq     qword ptr [edi + eax], mm0     
  0x001EC59C  0f7f640708              movq     qword ptr [edi + eax + 8], mm4 
  0x001EC5A1  0f7f540710              movq     qword ptr [edi + eax + 0x10], mm2 
  0x001EC5A6  0f7f740718              movq     qword ptr [edi + eax + 0x18], mm6 
  0x001EC5AB  0f7fc8                  movq     mm0, mm1                       
  0x001EC5AE  0f7fec                  movq     mm4, mm5                       
  0x001EC5B1  0f61c3                  punpcklwd mm0, mm3                       
  0x001EC5B4  0f61e7                  punpcklwd mm4, mm7                       
  0x001EC5B7  0f69cb                  punpckhwd mm1, mm3                       
  0x001EC5BA  0f69ef                  punpckhwd mm5, mm7                       
  0x001EC5BD  0f7f440720              movq     qword ptr [edi + eax + 0x20], mm0 
  0x001EC5C2  0f7f640728              movq     qword ptr [edi + eax + 0x28], mm4 
  0x001EC5C7  0f7f4c0730              movq     qword ptr [edi + eax + 0x30], mm1 
  0x001EC5CC  0f7f6c0738              movq     qword ptr [edi + eax + 0x38], mm5 
  0x001EC5D1  2bf2                    sub      esi, edx                       
  0x001EC5D3  2bf2                    sub      esi, edx                       
  0x001EC5D5  2bf2                    sub      esi, edx                       
  0x001EC5D7  2bf2                    sub      esi, edx                       
  0x001EC5D9  2b5d6c                  sub      ebx, dword ptr [ebp + 0x6c]    
  0x001EC5DC  90                      nop                                     
  0x001EC5DD  90                      nop                                     
  0x001EC5DE  90                      nop                                     
  0x001EC5DF  90                      nop                                     
  0x001EC5E0  90                      nop                                     
  0x001EC5E1  90                      nop                                     
  0x001EC5E2  90                      nop                                     
  0x001EC5E3  90                      nop                                     
  0x001EC5E4  90                      nop                                     
  0x001EC5E5  90                      nop                                     
  0x001EC5E6  90                      nop                                     
  0x001EC5E7  90                      nop                                     
  0x001EC5E8  90                      nop                                     
  0x001EC5E9  90                      nop                                     
  0x001EC5EA  90                      nop                                     
  0x001EC5EB  90                      nop                                     
  0x001EC5EC  90                      nop                                     
  0x001EC5ED  90                      nop                                     
  0x001EC5EE  90                      nop                                     
  0x001EC5EF  90                      nop                                     
  0x001EC5F0  90                      nop                                     
  0x001EC5F1  90                      nop                                     
  0x001EC5F2  90                      nop                                     
  0x001EC5F3  90                      nop                                     
  0x001EC5F4  90                      nop                                     
  0x001EC5F5  90                      nop                                     
  0x001EC5F6  90                      nop                                     
  0x001EC5F7  90                      nop                                     
  0x001EC5F8  83c608                  add      esi, 8                         
  0x001EC5FB  235d38                  and      ebx, dword ptr [ebp + 0x38]    
  0x001EC5FE  ff4dfc                  dec      dword ptr [ebp - 4]            
  0x001EC601  0f8557ffffff            jne      0x1ec55e                       
  0x001EC607  8b4560                  mov      eax, dword ptr [ebp + 0x60]    
  0x001EC60A  8b5d64                  mov      ebx, dword ptr [ebp + 0x64]    
  0x001EC60D  8945fc                  mov      dword ptr [ebp - 4], eax       
  0x001EC610  8b757c                  mov      esi, dword ptr [ebp + 0x7c]    
  0x001EC613  8b45f0                  mov      eax, dword ptr [ebp - 0x10]    
  0x001EC616  2b4d74                  sub      ecx, dword ptr [ebp + 0x74]    
  0x001EC619  8d34c6                  lea      esi, [esi + eax*8]             
  0x001EC61C  234d3c                  and      ecx, dword ptr [ebp + 0x3c]    
  0x001EC61F  89757c                  mov      dword ptr [ebp + 0x7c], esi    
  0x001EC622  ff4d00                  dec      dword ptr [ebp]                
  0x001EC625  0f8533ffffff            jne      0x1ec55e                       
  0x001EC62B  0f77                    emms                                    
  0x001EC62D  eb56                    jmp      0x1ec685                       
                                        ; XREF: 0x001EC166 (cond_jump), 0x001EC181 (cond_jump), 0x001EC18E (cond_jump), 0x001EC19B (cond_jump)
  0x001EC62F  8b4500                  mov      eax, dword ptr [ebp]           
  0x001EC632  83651800                and      dword ptr [ebp + 0x18], 0      
  0x001EC636  83651c00                and      dword ptr [ebp + 0x1c], 0      
  0x001EC63A  837d2804                cmp      dword ptr [ebp + 0x28], 4      
  0x001EC63E  894524                  mov      dword ptr [ebp + 0x24], eax    
  0x001EC641  8b45fc                  mov      eax, dword ptr [ebp - 4]       
  0x001EC644  894520                  mov      dword ptr [ebp + 0x20], eax    
  0x001EC647  8d45ec                  lea      eax, [ebp - 0x14]              
  0x001EC64A  50                      push     eax                            
  0x001EC64B  7507                    jne      0x1ec654                       
  0x001EC64D  e810f8ffff              call     0x1ebe62                       ; -> sub_001EBE62
  0x001EC652  eb31                    jmp      0x1ec685                       
                                        ; XREF: 0x001EC64B (cond_jump)
  0x001EC654  837d2802                cmp      dword ptr [ebp + 0x28], 2      
  0x001EC658  7507                    jne      0x1ec661                       
  0x001EC65A  e865f5ffff              call     0x1ebbc4                       ; -> sub_001EBBC4
  0x001EC65F  eb24                    jmp      0x1ec685                       
                                        ; XREF: 0x001EC658 (cond_jump)
  0x001EC661  e8b5f6ffff              call     0x1ebd1b                       ; -> sub_001EBD1B
  0x001EC666  eb1d                    jmp      0x1ec685                       
                                        ; XREF: 0x001EBF82 (cond_jump), 0x001EBF8C (cond_jump)
  0x001EC668  8b7560                  mov      esi, dword ptr [ebp + 0x60]    
  0x001EC66B  8bcf                    mov      ecx, edi                       
  0x001EC66D  0faf4d74                imul     ecx, dword ptr [ebp + 0x74]    
  0x001EC671  0faf4d7c                imul     ecx, dword ptr [ebp + 0x7c]    
  0x001EC675  8b7d6c                  mov      edi, dword ptr [ebp + 0x6c]    
  0x001EC678  8bd1                    mov      edx, ecx                       
  0x001EC67A  c1e902                  shr      ecx, 2                         
  0x001EC67D  f3a5                    rep movsd dword ptr es:[edi], dword ptr [esi] 
  0x001EC67F  8bca                    mov      ecx, edx                       
  0x001EC681  23c8                    and      ecx, eax                       
  0x001EC683  f3a4                    rep movsb byte ptr es:[edi], byte ptr [esi] 
                                        ; XREF: 0x001EBFC5 (jump), 0x001EBFE7 (jump), 0x001EC004 (jump), 0x001EC09E (cond_jump), 0x001EC0A7 (cond_jump), ... (+8 more)
  0x001EC685  5f                      pop      edi                            
  0x001EC686  5e                      pop      esi                            
  0x001EC687  5b                      pop      ebx                            
  0x001EC688  83c558                  add      ebp, 0x58                      
  0x001EC68B  c9                      leave                                   
  0x001EC68C  c22000                  ret      0x20                           
; end of function
  0x001EC68F  cc                      int3                                    

; ============================================================
; Function: sub_001EC690
; Start: 0x001EC690  End: 0x001EC6F5  Size: 101 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_001EC690:
  0x001EC690  0909                    or       dword ptr [ecx], ecx           
  0x001EC692  11911191a1a1            adc      dword ptr [ecx - 0x5e5e6eef], edx 
  0x001EC698  0000                    add      byte ptr [eax], al             
  0x001EC69A  0009                    add      byte ptr [ecx], cl             
  0x001EC69C  0400                    add      al, 0                          
  0x001EC69E  0808                    or       byte ptr [eax], cl             
  0x001EC6A0  1292a20a0000            adc      dl, byte ptr [edx + 0xaa2]     
  0x001EC6A6  1212                    adc      dl, byte ptr [edx]             
  0x001EC6A8  0009                    add      byte ptr [ecx], cl             
  0x001EC6AA  110a                    adc      dword ptr [edx], ecx           
  0x001EC6AC  92                      xchg     edx, eax                       
  0x001EC6AD  12a20a120000            adc      ah, byte ptr [edx + 0x120a]    
  0x001EC6B3  0010                    add      byte ptr [eax], dl             
  0x001EC6B5  1000                    adc      byte ptr [eax], al             
  0x001EC6B7  1111                    adc      dword ptr [ecx], edx           
  0x001EC6B9  116161                  adc      dword ptr [ecx + 0x61], esp    
  0x001EC6BC  51                      push     ecx                            
  0x001EC6BD  51                      push     ecx                            
  0x001EC6BE  626252                  bound    esp, qword ptr [edx + 0x52]    
  0x001EC6C1  52                      push     edx                            
  0x001EC6C2  1121                    adc      dword ptr [ecx], esp           
  0x001EC6C4  0012                    add      byte ptr [edx], dl             
  0x001EC6C6  0012                    add      byte ptr [edx], dl             
  0x001EC6C8  1111                    adc      dword ptr [ecx], edx           
  0x001EC6CA  2121                    and      dword ptr [ecx], esp           
  0x001EC6CC  2112                    and      dword ptr [edx], edx           
  0x001EC6CE  1222                    adc      ah, byte ptr [edx]             
  0x001EC6D0  2222                    and      ah, byte ptr [edx]             
  0x001EC6D2  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x001EB4EE (data_imm)
  0x001EC6D4  55                      push     ebp                            
  0x001EC6D5  6e                      outsb    dx, byte ptr [esi]             
  0x001EC6D6  61                      popal                                   
  0x001EC6D7  626c6520                bound    ebp, qword ptr [ebp + 0x20]    
  0x001EC6DB  746f                    je       0x1ec74c                       
  0x001EC6DD  206f70                  and      byte ptr [edi + 0x70], ch      
  0x001EC6E0  656e                    outsb    dx, byte ptr gs:[esi]          
  0x001EC6E2  206669                  and      byte ptr [esi + 0x69], ah      
  0x001EC6E5  6c                      insb     byte ptr es:[edi], dx          
  0x001EC6E6  652028                  and      byte ptr gs:[eax], ch          
  0x001EC6E9  2573293a20              and      eax, 0x203a2973                
  0x001EC6EE  206572                  and      byte ptr [ebp + 0x72], ah      
  0x001EC6F1  726f                    jb       0x1ec762                       
  0x001EC6F3  7220                    jb       0x1ec715                       
; end of function
  0x001EC6F6  780a                    js       0x1ec702                       
