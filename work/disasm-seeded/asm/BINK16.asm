; ============================================================
; Section: BINK16
; VA: 0x00219C80 - 0x0021AECC
; Size: 4684 bytes (4.6 KB)
; Functions: 16
; Instructions: 1260
; ============================================================

  0x00219C80  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00219C84  85d2                    test     edx, edx                       
  0x00219C86  744c                    je       0x219cd4                       
  0x00219C88  56                      push     esi                            
  0x00219C89  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x00219CD1 (cond_jump)
  0x00219C90  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00219C96  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219C99  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219CA1  41                      inc      ecx                            
  0x00219CA2  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00219CA8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219CAE  668901                  mov      word ptr [ecx], ax             
  0x00219CB1  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219CB7  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00219CBD  6689040e                mov      word ptr [esi + ecx], ax       
  0x00219CC1  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219CC7  83c102                  add      ecx, 2                         
  0x00219CCA  4a                      dec      edx                            
  0x00219CCB  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x00219CD1  75bd                    jne      0x219c90                       
  0x00219CD3  5e                      pop      esi                            
                                        ; XREF: 0x00219C86 (cond_jump)
  0x00219CD4  c3                      ret                                     
  0x00219CD5  cc                      int3                                    
  0x00219CD6  cc                      int3                                    
  0x00219CD7  cc                      int3                                    
  0x00219CD8  cc                      int3                                    
  0x00219CD9  cc                      int3                                    
  0x00219CDA  cc                      int3                                    
  0x00219CDB  cc                      int3                                    
  0x00219CDC  cc                      int3                                    
  0x00219CDD  cc                      int3                                    
  0x00219CDE  cc                      int3                                    
  0x00219CDF  cc                      int3                                    

; ============================================================
; Function: sub_00219CE0
; Start: 0x00219CE0  End: 0x00219D80  Size: 160 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00219CE0:
  0x00219CE0  53                      push     ebx                            
  0x00219CE1  56                      push     esi                            
  0x00219CE2  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00219CE6  57                      push     edi                            
  0x00219CE7  8bd6                    mov      edx, esi                       
  0x00219CE9  bf02000000              mov      edi, 2                         
  0x00219CEE  8bff                    mov      edi, edi                       
                                        ; XREF: 0x00219D6F (cond_jump)
  0x00219CF0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00219CF6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219CF9  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219D01  41                      inc      ecx                            
  0x00219D02  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00219D08  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219D0E  668901                  mov      word ptr [ecx], ax             
  0x00219D11  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00219D17  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00219D1D  66890419                mov      word ptr [ecx + ebx], ax       
  0x00219D21  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00219D27  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219D2A  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219D32  41                      inc      ecx                            
  0x00219D33  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00219D39  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219D3F  668901                  mov      word ptr [ecx], ax             
  0x00219D42  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219D48  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x00219D4E  66890419                mov      word ptr [ecx + ebx], ax       
  0x00219D52  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00219D58  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219D5E  03df                    add      ebx, edi                       
  0x00219D60  03cf                    add      ecx, edi                       
  0x00219D62  4a                      dec      edx                            
  0x00219D63  891d109f2900            mov      dword ptr [0x299f10], ebx      
  0x00219D69  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x00219D6F  0f857bffffff            jne      0x219cf0                       
  0x00219D75  8b542414                mov      edx, dword ptr [esp + 0x14]    
  0x00219D79  5f                      pop      edi                            
  0x00219D7A  8d0416                  lea      eax, [esi + edx]               
  0x00219D7D  5e                      pop      esi                            
  0x00219D7E  5b                      pop      ebx                            
  0x00219D7F  c3                      ret                                     
; end of function
  0x00219D80  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00219D84  85d2                    test     edx, edx                       
  0x00219D86  7445                    je       0x219dcd                       
  0x00219D88  eb06                    jmp      0x219d90                       
  0x00219D8A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x00219D88 (jump), 0x00219DCB (cond_jump)
  0x00219D90  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00219D96  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219D99  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219DA1  41                      inc      ecx                            
  0x00219DA2  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00219DA8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219DAE  668901                  mov      word ptr [ecx], ax             
  0x00219DB1  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219DB7  66894102                mov      word ptr [ecx + 2], ax         
  0x00219DBB  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219DC1  83c104                  add      ecx, 4                         
  0x00219DC4  4a                      dec      edx                            
  0x00219DC5  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x00219DCB  75c3                    jne      0x219d90                       
                                        ; XREF: 0x00219D86 (cond_jump)
  0x00219DCD  c3                      ret                                     
  0x00219DCE  cc                      int3                                    
  0x00219DCF  cc                      int3                                    

; ============================================================
; Function: sub_00219DD0
; Start: 0x00219DD0  End: 0x00219E5D  Size: 141 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00219DD0:
  0x00219DD0  56                      push     esi                            
  0x00219DD1  8b742408                mov      esi, dword ptr [esp + 8]       
  0x00219DD5  57                      push     edi                            
  0x00219DD6  8bd6                    mov      edx, esi                       
  0x00219DD8  bf04000000              mov      edi, 4                         
  0x00219DDD  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x00219E51 (cond_jump)
  0x00219DE0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00219DE6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219DE9  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219DF1  41                      inc      ecx                            
  0x00219DF2  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00219DF8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219DFE  668901                  mov      word ptr [ecx], ax             
  0x00219E01  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219E07  66894102                mov      word ptr [ecx + 2], ax         
  0x00219E0B  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00219E11  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219E14  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219E1C  41                      inc      ecx                            
  0x00219E1D  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00219E23  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219E29  668901                  mov      word ptr [ecx], ax             
  0x00219E2C  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219E32  66894102                mov      word ptr [ecx + 2], ax         
  0x00219E36  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x00219E3B  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219E41  03c7                    add      eax, edi                       
  0x00219E43  03cf                    add      ecx, edi                       
  0x00219E45  4a                      dec      edx                            
  0x00219E46  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x00219E4B  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x00219E51  758d                    jne      0x219de0                       
  0x00219E53  8b542410                mov      edx, dword ptr [esp + 0x10]    
  0x00219E57  5f                      pop      edi                            
  0x00219E58  8d0416                  lea      eax, [esi + edx]               
  0x00219E5B  5e                      pop      esi                            
  0x00219E5C  c3                      ret                                     
; end of function
  0x00219E5D  cc                      int3                                    
  0x00219E5E  cc                      int3                                    
  0x00219E5F  cc                      int3                                    

; ============================================================
; Function: sub_00219E60
; Start: 0x00219E60  End: 0x00219ED0  Size: 112 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00219E60:
  0x00219E60  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00219E64  85d2                    test     edx, edx                       
  0x00219E66  7467                    je       0x219ecf                       
  0x00219E68  56                      push     esi                            
  0x00219E69  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x00219ECC (cond_jump)
  0x00219E70  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00219E76  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219E79  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219E81  41                      inc      ecx                            
  0x00219E82  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00219E88  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219E8E  668901                  mov      word ptr [ecx], ax             
  0x00219E91  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219E97  66894102                mov      word ptr [ecx + 2], ax         
  0x00219E9B  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x00219EA1  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00219EA7  66890431                mov      word ptr [ecx + esi], ax       
  0x00219EAB  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219EB1  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00219EB7  6689440e02              mov      word ptr [esi + ecx + 2], ax   
  0x00219EBC  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219EC2  83c104                  add      ecx, 4                         
  0x00219EC5  4a                      dec      edx                            
  0x00219EC6  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x00219ECC  75a2                    jne      0x219e70                       
  0x00219ECE  5e                      pop      esi                            
                                        ; XREF: 0x00219E66 (cond_jump)
  0x00219ECF  c3                      ret                                     
; end of function
  0x00219ED0  53                      push     ebx                            
  0x00219ED1  56                      push     esi                            
  0x00219ED2  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00219ED6  57                      push     edi                            
  0x00219ED7  8bd6                    mov      edx, esi                       
  0x00219ED9  bf04000000              mov      edi, 4                         
  0x00219EDE  8bff                    mov      edi, edi                       
                                        ; XREF: 0x00219F95 (cond_jump)
  0x00219EE0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00219EE6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219EE9  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219EF1  41                      inc      ecx                            
  0x00219EF2  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00219EF8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219EFE  668901                  mov      word ptr [ecx], ax             
  0x00219F01  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219F07  66894102                mov      word ptr [ecx + 2], ax         
  0x00219F0B  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00219F11  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00219F17  66890419                mov      word ptr [ecx + ebx], ax       
  0x00219F1B  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00219F21  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00219F27  6689441902              mov      word ptr [ecx + ebx + 2], ax   
  0x00219F2C  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00219F32  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219F35  668b048510932900        mov      ax, word ptr [eax*4 + 0x299310] 
  0x00219F3D  41                      inc      ecx                            
  0x00219F3E  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00219F44  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219F4A  668901                  mov      word ptr [ecx], ax             
  0x00219F4D  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219F53  66894102                mov      word ptr [ecx + 2], ax         
  0x00219F57  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219F5D  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x00219F63  66890419                mov      word ptr [ecx + ebx], ax       
  0x00219F67  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219F6D  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x00219F73  6689441902              mov      word ptr [ecx + ebx + 2], ax   
  0x00219F78  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00219F7E  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00219F84  03df                    add      ebx, edi                       
  0x00219F86  03cf                    add      ecx, edi                       
  0x00219F88  4a                      dec      edx                            
  0x00219F89  891d109f2900            mov      dword ptr [0x299f10], ebx      
  0x00219F8F  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x00219F95  0f8545ffffff            jne      0x219ee0                       
  0x00219F9B  8b542414                mov      edx, dword ptr [esp + 0x14]    
  0x00219F9F  5f                      pop      edi                            
  0x00219FA0  8d0416                  lea      eax, [esi + edx]               
  0x00219FA3  5e                      pop      esi                            
  0x00219FA4  5b                      pop      ebx                            
  0x00219FA5  c3                      ret                                     
  0x00219FA6  cc                      int3                                    
  0x00219FA7  cc                      int3                                    
  0x00219FA8  cc                      int3                                    
  0x00219FA9  cc                      int3                                    
  0x00219FAA  cc                      int3                                    
  0x00219FAB  cc                      int3                                    
  0x00219FAC  cc                      int3                                    
  0x00219FAD  cc                      int3                                    
  0x00219FAE  cc                      int3                                    
  0x00219FAF  cc                      int3                                    

; ============================================================
; Function: sub_00219FB0
; Start: 0x00219FB0  End: 0x0021A088  Size: 216 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00219FB0:
  0x00219FB0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00219FB4  85c0                    test     eax, eax                       
  0x00219FB6  53                      push     ebx                            
  0x00219FB7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x00219FBB  0f84c5000000            je       0x21a086                       
  0x00219FC1  55                      push     ebp                            
  0x00219FC2  56                      push     esi                            
  0x00219FC3  57                      push     edi                            
  0x00219FC4  8be8                    mov      ebp, eax                       
  0x00219FC6  eb08                    jmp      0x219fd0                       
  0x00219FC8  8da42400000000          lea      esp, [esp]                     
  0x00219FCF  90                      nop                                     
                                        ; XREF: 0x00219FC6 (jump), 0x0021A07D (cond_jump)
  0x00219FD0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x00219FD5  0fb600                  movzx    eax, byte ptr [eax]            
  0x00219FD8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00219FDE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00219FE1  c1e002                  shl      eax, 2                         
  0x00219FE4  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x00219FEA  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x00219FF0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x00219FF5  c1e102                  shl      ecx, 2                         
  0x00219FF8  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x00219FFE  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021A004  03d6                    add      edx, esi                       
  0x0021A006  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021A009  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021A010  40                      inc      eax                            
  0x0021A011  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021A016  8d040e                  lea      eax, [esi + ecx]               
  0x0021A019  668b0485a0522900        mov      ax, word ptr [eax*4 + 0x2952a0] 
  0x0021A021  8d0c16                  lea      ecx, [esi + edx]               
  0x0021A024  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021A02C  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A032  03f7                    add      esi, edi                       
  0x0021A034  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021A03C  668902                  mov      word ptr [edx], ax             
  0x0021A03F  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021A045  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021A04B  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021A04F  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A055  83c202                  add      edx, 2                         
  0x0021A058  43                      inc      ebx                            
  0x0021A059  f6c301                  test     bl, 1                          
  0x0021A05C  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021A062  7518                    jne      0x21a07c                       
  0x0021A064  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021A06A  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021A06F  41                      inc      ecx                            
  0x0021A070  40                      inc      eax                            
  0x0021A071  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021A077  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021A062 (cond_jump)
  0x0021A07C  4d                      dec      ebp                            
  0x0021A07D  0f854dffffff            jne      0x219fd0                       
  0x0021A083  5f                      pop      edi                            
  0x0021A084  5e                      pop      esi                            
  0x0021A085  5d                      pop      ebp                            
                                        ; XREF: 0x00219FBB (cond_jump)
  0x0021A086  5b                      pop      ebx                            
  0x0021A087  c3                      ret                                     
; end of function
  0x0021A088  cc                      int3                                    
  0x0021A089  cc                      int3                                    
  0x0021A08A  cc                      int3                                    
  0x0021A08B  cc                      int3                                    
  0x0021A08C  cc                      int3                                    
  0x0021A08D  cc                      int3                                    
  0x0021A08E  cc                      int3                                    
  0x0021A08F  cc                      int3                                    

; ============================================================
; Function: sub_0021A090
; Start: 0x0021A090  End: 0x0021A1BF  Size: 303 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A090:
  0x0021A090  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021A094  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021A098  53                      push     ebx                            
  0x0021A099  55                      push     ebp                            
  0x0021A09A  56                      push     esi                            
  0x0021A09B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021A09F  57                      push     edi                            
                                        ; XREF: 0x0021A1B4 (cond_jump)
  0x0021A0A0  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A0A6  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021A0A9  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021A0AF  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021A0B2  c1e102                  shl      ecx, 2                         
  0x0021A0B5  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x0021A0BB  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021A0C1  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021A0C7  c1e202                  shl      edx, 2                         
  0x0021A0CA  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021A0D0  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021A0D6  03f7                    add      esi, edi                       
  0x0021A0D8  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021A0DB  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021A0E2  41                      inc      ecx                            
  0x0021A0E3  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021A0E9  8d0c17                  lea      ecx, [edi + edx]               
  0x0021A0EC  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021A0F4  8d2c37                  lea      ebp, [edi + esi]               
  0x0021A0F7  660b0cad90462900        or       cx, word ptr [ebp*4 + 0x294690] 
  0x0021A0FF  03fb                    add      edi, ebx                       
  0x0021A101  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021A109  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A10F  66890f                  mov      word ptr [edi], cx             
  0x0021A112  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x0021A118  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x0021A11E  66890c2f                mov      word ptr [edi + ebp], cx       
  0x0021A122  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021A128  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021A12B  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021A132  41                      inc      ecx                            
  0x0021A133  03d7                    add      edx, edi                       
  0x0021A135  03f7                    add      esi, edi                       
  0x0021A137  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021A13D  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021A145  660b0cb590462900        or       cx, word ptr [esi*4 + 0x294690] 
  0x0021A14D  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A153  03fb                    add      edi, ebx                       
  0x0021A155  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021A15D  66890a                  mov      word ptr [edx], cx             
  0x0021A160  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A166  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x0021A16C  66890c32                mov      word ptr [edx + esi], cx       
  0x0021A170  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A176  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021A17C  b902000000              mov      ecx, 2                         
  0x0021A181  03f9                    add      edi, ecx                       
  0x0021A183  03f1                    add      esi, ecx                       
  0x0021A185  40                      inc      eax                            
  0x0021A186  a801                    test     al, 1                          
  0x0021A188  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021A18E  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021A194  751a                    jne      0x21a1b0                       
  0x0021A196  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A19C  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021A1A2  42                      inc      edx                            
  0x0021A1A3  41                      inc      ecx                            
  0x0021A1A4  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021A1AA  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021A194 (cond_jump)
  0x0021A1B0  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021A1B4  0f85e6feffff            jne      0x21a0a0                       
  0x0021A1BA  5f                      pop      edi                            
  0x0021A1BB  5e                      pop      esi                            
  0x0021A1BC  5d                      pop      ebp                            
  0x0021A1BD  5b                      pop      ebx                            
  0x0021A1BE  c3                      ret                                     
; end of function
  0x0021A1BF  cc                      int3                                    

; ============================================================
; Function: sub_0021A1C0
; Start: 0x0021A1C0  End: 0x0021A292  Size: 210 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A1C0:
  0x0021A1C0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021A1C4  85c0                    test     eax, eax                       
  0x0021A1C6  53                      push     ebx                            
  0x0021A1C7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021A1CB  0f84bf000000            je       0x21a290                       
  0x0021A1D1  55                      push     ebp                            
  0x0021A1D2  56                      push     esi                            
  0x0021A1D3  57                      push     edi                            
  0x0021A1D4  8be8                    mov      ebp, eax                       
  0x0021A1D6  eb08                    jmp      0x21a1e0                       
  0x0021A1D8  8da42400000000          lea      esp, [esp]                     
  0x0021A1DF  90                      nop                                     
                                        ; XREF: 0x0021A1D6 (jump), 0x0021A287 (cond_jump)
  0x0021A1E0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021A1E5  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021A1E8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021A1EE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021A1F1  c1e002                  shl      eax, 2                         
  0x0021A1F4  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021A1FA  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021A200  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021A205  c1e102                  shl      ecx, 2                         
  0x0021A208  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021A20E  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021A214  03d6                    add      edx, esi                       
  0x0021A216  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021A219  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021A220  40                      inc      eax                            
  0x0021A221  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021A226  8d040e                  lea      eax, [esi + ecx]               
  0x0021A229  668b0485a0522900        mov      ax, word ptr [eax*4 + 0x2952a0] 
  0x0021A231  8d0c16                  lea      ecx, [esi + edx]               
  0x0021A234  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021A23C  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A242  03f7                    add      esi, edi                       
  0x0021A244  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021A24C  668902                  mov      word ptr [edx], ax             
  0x0021A24F  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021A255  66894102                mov      word ptr [ecx + 2], ax         
  0x0021A259  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A25F  83c204                  add      edx, 4                         
  0x0021A262  43                      inc      ebx                            
  0x0021A263  f6c301                  test     bl, 1                          
  0x0021A266  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021A26C  7518                    jne      0x21a286                       
  0x0021A26E  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021A274  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021A279  41                      inc      ecx                            
  0x0021A27A  40                      inc      eax                            
  0x0021A27B  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021A281  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021A26C (cond_jump)
  0x0021A286  4d                      dec      ebp                            
  0x0021A287  0f8553ffffff            jne      0x21a1e0                       
  0x0021A28D  5f                      pop      edi                            
  0x0021A28E  5e                      pop      esi                            
  0x0021A28F  5d                      pop      ebp                            
                                        ; XREF: 0x0021A1CB (cond_jump)
  0x0021A290  5b                      pop      ebx                            
  0x0021A291  c3                      ret                                     
; end of function
  0x0021A292  cc                      int3                                    
  0x0021A293  cc                      int3                                    
  0x0021A294  cc                      int3                                    
  0x0021A295  cc                      int3                                    
  0x0021A296  cc                      int3                                    
  0x0021A297  cc                      int3                                    
  0x0021A298  cc                      int3                                    
  0x0021A299  cc                      int3                                    
  0x0021A29A  cc                      int3                                    
  0x0021A29B  cc                      int3                                    
  0x0021A29C  cc                      int3                                    
  0x0021A29D  cc                      int3                                    
  0x0021A29E  cc                      int3                                    
  0x0021A29F  cc                      int3                                    

; ============================================================
; Function: sub_0021A2A0
; Start: 0x0021A2A0  End: 0x0021A3C3  Size: 291 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A2A0:
  0x0021A2A0  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021A2A4  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021A2A8  53                      push     ebx                            
  0x0021A2A9  55                      push     ebp                            
  0x0021A2AA  56                      push     esi                            
  0x0021A2AB  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021A2AF  57                      push     edi                            
                                        ; XREF: 0x0021A3B8 (cond_jump)
  0x0021A2B0  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A2B6  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021A2B9  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021A2BF  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021A2C2  c1e102                  shl      ecx, 2                         
  0x0021A2C5  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x0021A2CB  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021A2D1  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021A2D7  c1e202                  shl      edx, 2                         
  0x0021A2DA  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021A2E0  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021A2E6  03f7                    add      esi, edi                       
  0x0021A2E8  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021A2EB  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021A2F2  41                      inc      ecx                            
  0x0021A2F3  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021A2F9  8d0c17                  lea      ecx, [edi + edx]               
  0x0021A2FC  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021A304  8d2c37                  lea      ebp, [edi + esi]               
  0x0021A307  660b0cad90462900        or       cx, word ptr [ebp*4 + 0x294690] 
  0x0021A30F  03fb                    add      edi, ebx                       
  0x0021A311  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021A319  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A31F  66890f                  mov      word ptr [edi], cx             
  0x0021A322  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A328  66894f02                mov      word ptr [edi + 2], cx         
  0x0021A32C  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021A332  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021A335  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021A33C  41                      inc      ecx                            
  0x0021A33D  03d7                    add      edx, edi                       
  0x0021A33F  03f7                    add      esi, edi                       
  0x0021A341  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021A347  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021A34F  660b0cb590462900        or       cx, word ptr [esi*4 + 0x294690] 
  0x0021A357  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A35D  03fb                    add      edi, ebx                       
  0x0021A35F  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021A367  66890a                  mov      word ptr [edx], cx             
  0x0021A36A  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A370  66894a02                mov      word ptr [edx + 2], cx         
  0x0021A374  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A37A  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021A380  b904000000              mov      ecx, 4                         
  0x0021A385  03f9                    add      edi, ecx                       
  0x0021A387  03f1                    add      esi, ecx                       
  0x0021A389  40                      inc      eax                            
  0x0021A38A  a801                    test     al, 1                          
  0x0021A38C  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021A392  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021A398  751a                    jne      0x21a3b4                       
  0x0021A39A  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A3A0  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021A3A6  42                      inc      edx                            
  0x0021A3A7  41                      inc      ecx                            
  0x0021A3A8  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021A3AE  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021A398 (cond_jump)
  0x0021A3B4  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021A3B8  0f85f2feffff            jne      0x21a2b0                       
  0x0021A3BE  5f                      pop      edi                            
  0x0021A3BF  5e                      pop      esi                            
  0x0021A3C0  5d                      pop      ebp                            
  0x0021A3C1  5b                      pop      ebx                            
  0x0021A3C2  c3                      ret                                     
; end of function
  0x0021A3C3  cc                      int3                                    
  0x0021A3C4  cc                      int3                                    
  0x0021A3C5  cc                      int3                                    
  0x0021A3C6  cc                      int3                                    
  0x0021A3C7  cc                      int3                                    
  0x0021A3C8  cc                      int3                                    
  0x0021A3C9  cc                      int3                                    
  0x0021A3CA  cc                      int3                                    
  0x0021A3CB  cc                      int3                                    
  0x0021A3CC  cc                      int3                                    
  0x0021A3CD  cc                      int3                                    
  0x0021A3CE  cc                      int3                                    
  0x0021A3CF  cc                      int3                                    

; ============================================================
; Function: sub_0021A3D0
; Start: 0x0021A3D0  End: 0x0021A4C3  Size: 243 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A3D0:
  0x0021A3D0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021A3D4  85c0                    test     eax, eax                       
  0x0021A3D6  53                      push     ebx                            
  0x0021A3D7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021A3DB  0f84e0000000            je       0x21a4c1                       
  0x0021A3E1  55                      push     ebp                            
  0x0021A3E2  56                      push     esi                            
  0x0021A3E3  57                      push     edi                            
  0x0021A3E4  8be8                    mov      ebp, eax                       
  0x0021A3E6  eb08                    jmp      0x21a3f0                       
  0x0021A3E8  8da42400000000          lea      esp, [esp]                     
  0x0021A3EF  90                      nop                                     
                                        ; XREF: 0x0021A3E6 (jump), 0x0021A4B8 (cond_jump)
  0x0021A3F0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021A3F5  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021A3F8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021A3FE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021A401  c1e002                  shl      eax, 2                         
  0x0021A404  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021A40A  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021A410  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021A415  c1e102                  shl      ecx, 2                         
  0x0021A418  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021A41E  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021A424  03d6                    add      edx, esi                       
  0x0021A426  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021A429  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021A430  40                      inc      eax                            
  0x0021A431  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021A436  8d040e                  lea      eax, [esi + ecx]               
  0x0021A439  668b0485a0522900        mov      ax, word ptr [eax*4 + 0x2952a0] 
  0x0021A441  8d0c16                  lea      ecx, [esi + edx]               
  0x0021A444  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021A44C  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A452  03f7                    add      esi, edi                       
  0x0021A454  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021A45C  668902                  mov      word ptr [edx], ax             
  0x0021A45F  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021A465  66894102                mov      word ptr [ecx + 2], ax         
  0x0021A469  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021A46F  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021A475  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021A479  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A47F  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021A485  6689441102              mov      word ptr [ecx + edx + 2], ax   
  0x0021A48A  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A490  83c204                  add      edx, 4                         
  0x0021A493  43                      inc      ebx                            
  0x0021A494  f6c301                  test     bl, 1                          
  0x0021A497  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021A49D  7518                    jne      0x21a4b7                       
  0x0021A49F  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021A4A5  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021A4AA  41                      inc      ecx                            
  0x0021A4AB  40                      inc      eax                            
  0x0021A4AC  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021A4B2  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021A49D (cond_jump)
  0x0021A4B7  4d                      dec      ebp                            
  0x0021A4B8  0f8532ffffff            jne      0x21a3f0                       
  0x0021A4BE  5f                      pop      edi                            
  0x0021A4BF  5e                      pop      esi                            
  0x0021A4C0  5d                      pop      ebp                            
                                        ; XREF: 0x0021A3DB (cond_jump)
  0x0021A4C1  5b                      pop      ebx                            
  0x0021A4C2  c3                      ret                                     
; end of function
  0x0021A4C3  cc                      int3                                    
  0x0021A4C4  cc                      int3                                    
  0x0021A4C5  cc                      int3                                    
  0x0021A4C6  cc                      int3                                    
  0x0021A4C7  cc                      int3                                    
  0x0021A4C8  cc                      int3                                    
  0x0021A4C9  cc                      int3                                    
  0x0021A4CA  cc                      int3                                    
  0x0021A4CB  cc                      int3                                    
  0x0021A4CC  cc                      int3                                    
  0x0021A4CD  cc                      int3                                    
  0x0021A4CE  cc                      int3                                    
  0x0021A4CF  cc                      int3                                    

; ============================================================
; Function: sub_0021A4D0
; Start: 0x0021A4D0  End: 0x0021A635  Size: 357 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A4D0:
  0x0021A4D0  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021A4D4  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021A4D8  53                      push     ebx                            
  0x0021A4D9  55                      push     ebp                            
  0x0021A4DA  56                      push     esi                            
  0x0021A4DB  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021A4DF  57                      push     edi                            
                                        ; XREF: 0x0021A62A (cond_jump)
  0x0021A4E0  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A4E6  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021A4E9  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021A4EF  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021A4F2  c1e102                  shl      ecx, 2                         
  0x0021A4F5  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x0021A4FB  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021A501  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021A507  c1e202                  shl      edx, 2                         
  0x0021A50A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021A510  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021A516  03f7                    add      esi, edi                       
  0x0021A518  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021A51B  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021A522  41                      inc      ecx                            
  0x0021A523  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021A529  8d0c17                  lea      ecx, [edi + edx]               
  0x0021A52C  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021A534  8d2c37                  lea      ebp, [edi + esi]               
  0x0021A537  660b0cad90462900        or       cx, word ptr [ebp*4 + 0x294690] 
  0x0021A53F  03fb                    add      edi, ebx                       
  0x0021A541  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021A549  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A54F  66890f                  mov      word ptr [edi], cx             
  0x0021A552  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A558  66894f02                mov      word ptr [edi + 2], cx         
  0x0021A55C  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x0021A562  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x0021A568  66890c2f                mov      word ptr [edi + ebp], cx       
  0x0021A56C  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x0021A572  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x0021A578  66894c2f02              mov      word ptr [edi + ebp + 2], cx   
  0x0021A57D  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021A583  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021A586  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021A58D  03d7                    add      edx, edi                       
  0x0021A58F  41                      inc      ecx                            
  0x0021A590  03f7                    add      esi, edi                       
  0x0021A592  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021A598  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021A5A0  660b0cb590462900        or       cx, word ptr [esi*4 + 0x294690] 
  0x0021A5A8  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A5AE  03fb                    add      edi, ebx                       
  0x0021A5B0  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021A5B8  66890a                  mov      word ptr [edx], cx             
  0x0021A5BB  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A5C1  66894a02                mov      word ptr [edx + 2], cx         
  0x0021A5C5  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A5CB  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x0021A5D1  66890c32                mov      word ptr [edx + esi], cx       
  0x0021A5D5  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021A5DB  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x0021A5E1  66894c3202              mov      word ptr [edx + esi + 2], cx   
  0x0021A5E6  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A5EC  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021A5F2  b904000000              mov      ecx, 4                         
  0x0021A5F7  03f9                    add      edi, ecx                       
  0x0021A5F9  03f1                    add      esi, ecx                       
  0x0021A5FB  40                      inc      eax                            
  0x0021A5FC  a801                    test     al, 1                          
  0x0021A5FE  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021A604  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021A60A  751a                    jne      0x21a626                       
  0x0021A60C  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A612  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021A618  42                      inc      edx                            
  0x0021A619  41                      inc      ecx                            
  0x0021A61A  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021A620  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021A60A (cond_jump)
  0x0021A626  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021A62A  0f85b0feffff            jne      0x21a4e0                       
  0x0021A630  5f                      pop      edi                            
  0x0021A631  5e                      pop      esi                            
  0x0021A632  5d                      pop      ebp                            
  0x0021A633  5b                      pop      ebx                            
  0x0021A634  c3                      ret                                     
; end of function
  0x0021A635  cc                      int3                                    
  0x0021A636  cc                      int3                                    
  0x0021A637  cc                      int3                                    
  0x0021A638  cc                      int3                                    
  0x0021A639  cc                      int3                                    
  0x0021A63A  cc                      int3                                    
  0x0021A63B  cc                      int3                                    
  0x0021A63C  cc                      int3                                    
  0x0021A63D  cc                      int3                                    
  0x0021A63E  cc                      int3                                    
  0x0021A63F  cc                      int3                                    

; ============================================================
; Function: sub_0021A640
; Start: 0x0021A640  End: 0x0021A681  Size: 65 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A640:
  0x0021A640  8b542408                mov      edx, dword ptr [esp + 8]       
  0x0021A644  85d2                    test     edx, edx                       
  0x0021A646  7438                    je       0x21a680                       
  0x0021A648  eb06                    jmp      0x21a650                       
  0x0021A64A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021A648 (jump), 0x0021A67E (cond_jump)
  0x0021A650  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021A655  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021A658  668b0c8d10932900        mov      cx, word ptr [ecx*4 + 0x299310] 
  0x0021A660  40                      inc      eax                            
  0x0021A661  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021A666  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021A66B  668908                  mov      word ptr [eax], cx             
  0x0021A66E  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021A674  83c102                  add      ecx, 2                         
  0x0021A677  4a                      dec      edx                            
  0x0021A678  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021A67E  75d0                    jne      0x21a650                       
                                        ; XREF: 0x0021A646 (cond_jump)
  0x0021A680  c3                      ret                                     
; end of function
  0x0021A681  cc                      int3                                    
  0x0021A682  cc                      int3                                    
  0x0021A683  cc                      int3                                    
  0x0021A684  cc                      int3                                    
  0x0021A685  cc                      int3                                    
  0x0021A686  cc                      int3                                    
  0x0021A687  cc                      int3                                    
  0x0021A688  cc                      int3                                    
  0x0021A689  cc                      int3                                    
  0x0021A68A  cc                      int3                                    
  0x0021A68B  cc                      int3                                    
  0x0021A68C  cc                      int3                                    
  0x0021A68D  cc                      int3                                    
  0x0021A68E  cc                      int3                                    
  0x0021A68F  cc                      int3                                    

; ============================================================
; Function: sub_0021A690
; Start: 0x0021A690  End: 0x0021A703  Size: 115 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A690:
  0x0021A690  56                      push     esi                            
  0x0021A691  8b742408                mov      esi, dword ptr [esp + 8]       
  0x0021A695  57                      push     edi                            
  0x0021A696  8bd6                    mov      edx, esi                       
  0x0021A698  bf02000000              mov      edi, 2                         
  0x0021A69D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021A6F7 (cond_jump)
  0x0021A6A0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021A6A5  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021A6A8  668b0c8d10932900        mov      cx, word ptr [ecx*4 + 0x299310] 
  0x0021A6B0  40                      inc      eax                            
  0x0021A6B1  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021A6B6  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021A6BB  668908                  mov      word ptr [eax], cx             
  0x0021A6BE  a11c9f2900              mov      eax, dword ptr [0x299f1c]      
  0x0021A6C3  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021A6C6  668b0c8d10932900        mov      cx, word ptr [ecx*4 + 0x299310] 
  0x0021A6CE  40                      inc      eax                            
  0x0021A6CF  a31c9f2900              mov      dword ptr [0x299f1c], eax      
  0x0021A6D4  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021A6D9  668908                  mov      word ptr [eax], cx             
  0x0021A6DC  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021A6E1  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021A6E7  03c7                    add      eax, edi                       
  0x0021A6E9  03cf                    add      ecx, edi                       
  0x0021A6EB  4a                      dec      edx                            
  0x0021A6EC  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021A6F1  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021A6F7  75a7                    jne      0x21a6a0                       
  0x0021A6F9  8b4c2410                mov      ecx, dword ptr [esp + 0x10]    
  0x0021A6FD  5f                      pop      edi                            
  0x0021A6FE  8d040e                  lea      eax, [esi + ecx]               
  0x0021A701  5e                      pop      esi                            
  0x0021A702  c3                      ret                                     
; end of function
  0x0021A703  cc                      int3                                    
  0x0021A704  cc                      int3                                    
  0x0021A705  cc                      int3                                    
  0x0021A706  cc                      int3                                    
  0x0021A707  cc                      int3                                    
  0x0021A708  cc                      int3                                    
  0x0021A709  cc                      int3                                    
  0x0021A70A  cc                      int3                                    
  0x0021A70B  cc                      int3                                    
  0x0021A70C  cc                      int3                                    
  0x0021A70D  cc                      int3                                    
  0x0021A70E  cc                      int3                                    
  0x0021A70F  cc                      int3                                    

; ============================================================
; Function: sub_0021A710
; Start: 0x0021A710  End: 0x0021A7D8  Size: 200 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A710:
  0x0021A710  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021A714  85c0                    test     eax, eax                       
  0x0021A716  53                      push     ebx                            
  0x0021A717  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021A71B  0f84b5000000            je       0x21a7d6                       
  0x0021A721  55                      push     ebp                            
  0x0021A722  56                      push     esi                            
  0x0021A723  57                      push     edi                            
  0x0021A724  8be8                    mov      ebp, eax                       
  0x0021A726  eb08                    jmp      0x21a730                       
  0x0021A728  8da42400000000          lea      esp, [esp]                     
  0x0021A72F  90                      nop                                     
                                        ; XREF: 0x0021A726 (jump), 0x0021A7CD (cond_jump)
  0x0021A730  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021A735  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021A738  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021A73E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021A741  c1e102                  shl      ecx, 2                         
  0x0021A744  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021A74A  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021A750  c1e002                  shl      eax, 2                         
  0x0021A753  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x0021A759  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x0021A75F  03d7                    add      edx, edi                       
  0x0021A761  8b3d189f2900            mov      edi, dword ptr [0x299f18]      
  0x0021A767  0fb607                  movzx    eax, byte ptr [edi]            
  0x0021A76A  8b048570322900          mov      eax, dword ptr [eax*4 + 0x293270] 
  0x0021A771  03c8                    add      ecx, eax                       
  0x0021A773  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021A77B  03d0                    add      edx, eax                       
  0x0021A77D  660b0c9590462900        or       cx, word ptr [edx*4 + 0x294690] 
  0x0021A785  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A78B  03c6                    add      eax, esi                       
  0x0021A78D  660b0c85803a2900        or       cx, word ptr [eax*4 + 0x293a80] 
  0x0021A795  47                      inc      edi                            
  0x0021A796  893d189f2900            mov      dword ptr [0x299f18], edi      
  0x0021A79C  66890a                  mov      word ptr [edx], cx             
  0x0021A79F  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021A7A5  83c202                  add      edx, 2                         
  0x0021A7A8  43                      inc      ebx                            
  0x0021A7A9  f6c301                  test     bl, 1                          
  0x0021A7AC  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021A7B2  7518                    jne      0x21a7cc                       
  0x0021A7B4  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021A7BA  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021A7BF  41                      inc      ecx                            
  0x0021A7C0  40                      inc      eax                            
  0x0021A7C1  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021A7C7  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021A7B2 (cond_jump)
  0x0021A7CC  4d                      dec      ebp                            
  0x0021A7CD  0f855dffffff            jne      0x21a730                       
  0x0021A7D3  5f                      pop      edi                            
  0x0021A7D4  5e                      pop      esi                            
  0x0021A7D5  5d                      pop      ebp                            
                                        ; XREF: 0x0021A71B (cond_jump)
  0x0021A7D6  5b                      pop      ebx                            
  0x0021A7D7  c3                      ret                                     
; end of function
  0x0021A7D8  cc                      int3                                    
  0x0021A7D9  cc                      int3                                    
  0x0021A7DA  cc                      int3                                    
  0x0021A7DB  cc                      int3                                    
  0x0021A7DC  cc                      int3                                    
  0x0021A7DD  cc                      int3                                    
  0x0021A7DE  cc                      int3                                    
  0x0021A7DF  cc                      int3                                    

; ============================================================
; Function: sub_0021A7E0
; Start: 0x0021A7E0  End: 0x0021A8EF  Size: 271 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A7E0:
  0x0021A7E0  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021A7E4  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021A7E8  53                      push     ebx                            
  0x0021A7E9  55                      push     ebp                            
  0x0021A7EA  56                      push     esi                            
  0x0021A7EB  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021A7EF  57                      push     edi                            
                                        ; XREF: 0x0021A8E4 (cond_jump)
  0x0021A7F0  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A7F6  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021A7F9  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021A7FF  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021A802  c1e102                  shl      ecx, 2                         
  0x0021A805  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x0021A80B  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x0021A811  c1e202                  shl      edx, 2                         
  0x0021A814  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021A81A  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021A820  03f3                    add      esi, ebx                       
  0x0021A822  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x0021A828  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021A82B  8b0c8d70322900          mov      ecx, dword ptr [ecx*4 + 0x293270] 
  0x0021A832  43                      inc      ebx                            
  0x0021A833  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x0021A839  8d1c11                  lea      ebx, [ecx + edx]               
  0x0021A83C  668b1c9da0522900        mov      bx, word ptr [ebx*4 + 0x2952a0] 
  0x0021A844  8d2c31                  lea      ebp, [ecx + esi]               
  0x0021A847  660b1cad90462900        or       bx, word ptr [ebp*4 + 0x294690] 
  0x0021A84F  03cf                    add      ecx, edi                       
  0x0021A851  660b1c8d803a2900        or       bx, word ptr [ecx*4 + 0x293a80] 
  0x0021A859  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021A85F  668919                  mov      word ptr [ecx], bx             
  0x0021A862  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x0021A868  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021A86B  8b0c8d70322900          mov      ecx, dword ptr [ecx*4 + 0x293270] 
  0x0021A872  03d1                    add      edx, ecx                       
  0x0021A874  668b1495a0522900        mov      dx, word ptr [edx*4 + 0x2952a0] 
  0x0021A87C  03f1                    add      esi, ecx                       
  0x0021A87E  660b14b590462900        or       dx, word ptr [esi*4 + 0x294690] 
  0x0021A886  03cf                    add      ecx, edi                       
  0x0021A888  660b148d803a2900        or       dx, word ptr [ecx*4 + 0x293a80] 
  0x0021A890  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021A896  43                      inc      ebx                            
  0x0021A897  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x0021A89D  668911                  mov      word ptr [ecx], dx             
  0x0021A8A0  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A8A6  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021A8AC  b902000000              mov      ecx, 2                         
  0x0021A8B1  03f9                    add      edi, ecx                       
  0x0021A8B3  03f1                    add      esi, ecx                       
  0x0021A8B5  40                      inc      eax                            
  0x0021A8B6  a801                    test     al, 1                          
  0x0021A8B8  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021A8BE  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021A8C4  751a                    jne      0x21a8e0                       
  0x0021A8C6  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021A8CC  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021A8D2  42                      inc      edx                            
  0x0021A8D3  41                      inc      ecx                            
  0x0021A8D4  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021A8DA  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021A8C4 (cond_jump)
  0x0021A8E0  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021A8E4  0f8506ffffff            jne      0x21a7f0                       
  0x0021A8EA  5f                      pop      edi                            
  0x0021A8EB  5e                      pop      esi                            
  0x0021A8EC  5d                      pop      ebp                            
  0x0021A8ED  5b                      pop      ebx                            
  0x0021A8EE  c3                      ret                                     
; end of function
  0x0021A8EF  cc                      int3                                    

; ============================================================
; Function: sub_0021A8F0
; Start: 0x0021A8F0  End: 0x0021A940  Size: 80 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214310
; Called by: sub_0020C030
; ============================================================
sub_0021A8F0:
  0x0021A8F0  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021A8F4  8b4c2434                mov      ecx, dword ptr [esp + 0x34]    
  0x0021A8F8  8b54242c                mov      edx, dword ptr [esp + 0x2c]    
  0x0021A8FC  6820c12900              push     0x29c120                       
  0x0021A901  50                      push     eax                            
  0x0021A902  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021A906  51                      push     ecx                            
  0x0021A907  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021A90B  52                      push     edx                            
  0x0021A90C  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021A910  50                      push     eax                            
  0x0021A911  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021A915  51                      push     ecx                            
  0x0021A916  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021A91A  52                      push     edx                            
  0x0021A91B  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021A91F  50                      push     eax                            
  0x0021A920  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021A924  51                      push     ecx                            
  0x0021A925  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021A929  52                      push     edx                            
  0x0021A92A  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021A92E  50                      push     eax                            
  0x0021A92F  51                      push     ecx                            
  0x0021A930  52                      push     edx                            
  0x0021A931  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021A935  e8d699ffff              call     0x214310                       ; -> sub_00214310
  0x0021A93A  83c434                  add      esp, 0x34                      
  0x0021A93D  c23400                  ret      0x34                           
; end of function

; ============================================================
; Function: sub_0021A940
; Start: 0x0021A940  End: 0x0021A99B  Size: 91 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214790
; Called by: sub_0020C030
; ============================================================
sub_0021A940:
  0x0021A940  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021A944  8b4c243c                mov      ecx, dword ptr [esp + 0x3c]    
  0x0021A948  8b542434                mov      edx, dword ptr [esp + 0x34]    
  0x0021A94C  6820c12900              push     0x29c120                       
  0x0021A951  50                      push     eax                            
  0x0021A952  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021A956  51                      push     ecx                            
  0x0021A957  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021A95B  52                      push     edx                            
  0x0021A95C  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021A960  50                      push     eax                            
  0x0021A961  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021A965  51                      push     ecx                            
  0x0021A966  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021A96A  52                      push     edx                            
  0x0021A96B  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021A96F  50                      push     eax                            
  0x0021A970  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021A974  51                      push     ecx                            
  0x0021A975  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021A979  52                      push     edx                            
  0x0021A97A  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021A97E  50                      push     eax                            
  0x0021A97F  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021A983  51                      push     ecx                            
  0x0021A984  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021A988  52                      push     edx                            
  0x0021A989  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021A98D  50                      push     eax                            
  0x0021A98E  51                      push     ecx                            
  0x0021A98F  52                      push     edx                            
  0x0021A990  e8fb9dffff              call     0x214790                       ; -> sub_00214790
  0x0021A995  83c440                  add      esp, 0x40                      
  0x0021A998  c23c00                  ret      0x3c                           
; end of function
  0x0021A99B  cc                      int3                                    
  0x0021A99C  cc                      int3                                    
  0x0021A99D  cc                      int3                                    
  0x0021A99E  cc                      int3                                    
  0x0021A99F  cc                      int3                                    

; ============================================================
; Function: sub_0021A9A0
; Start: 0x0021A9A0  End: 0x0021ABE2  Size: 578 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021A9A0:
  0x0021A9A0  53                      push     ebx                            
  0x0021A9A1  55                      push     ebp                            
  0x0021A9A2  56                      push     esi                            
  0x0021A9A3  57                      push     edi                            
  0x0021A9A4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021A9AA  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021A9B0  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021A9B6  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021A9BC  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021A9C0  c1e003                  shl      eax, 3                         
  0x0021A9C3  03c7                    add      eax, edi                       
  0x0021A9C5  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021A9CA  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021A9D1  8da42400000000          lea      esp, [esp]                     
  0x0021A9D8  8da42400000000          lea      esp, [esp]                     
  0x0021A9DF  90                      nop                                     
                                        ; XREF: 0x0021AAB3 (cond_jump)
  0x0021A9E0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021A9E3  0fefc0                  pxor     mm0, mm0                       
  0x0021A9E6  33c0                    xor      eax, eax                       
  0x0021A9E8  83c204                  add      edx, 4                         
  0x0021A9EB  8a4500                  mov      al, byte ptr [ebp]             
  0x0021A9EE  0f60e0                  punpcklbw mm4, mm0                       
  0x0021A9F1  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021A9F9  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021AA01  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021AA04  83c502                  add      ebp, 2                         
  0x0021AA07  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021AA0E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021AA16  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021AA1E  8a03                    mov      al, byte ptr [ebx]             
  0x0021AA20  0f71f402                psllw    mm4, 2                         
  0x0021AA24  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021AA2B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021AA33  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021AA3B  0ffdd5                  paddw    mm2, mm5                       
  0x0021AA3E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021AA41  83c302                  add      ebx, 2                         
  0x0021AA44  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021AA4C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021AA54  0ffdf5                  paddw    mm6, mm5                       
  0x0021AA57  0f62d6                  punpckldq mm2, mm6                       
  0x0021AA5A  0ffdcc                  paddw    mm1, mm4                       
  0x0021AA5D  0ffdd4                  paddw    mm2, mm4                       
  0x0021AA60  0fedcf                  paddsw   mm1, mm7                       
  0x0021AA63  0ffddc                  paddw    mm3, mm4                       
  0x0021AA66  0fd9cf                  psubusw  mm1, mm7                       
  0x0021AA69  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021AA70  0fedd7                  paddsw   mm2, mm7                       
  0x0021AA73  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021AA7A  0fd9d7                  psubusw  mm2, mm7                       
  0x0021AA7D  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021AA84  0feddf                  paddsw   mm3, mm7                       
  0x0021AA87  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021AA8E  0fd9df                  psubusw  mm3, mm7                       
  0x0021AA91  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021AA98  0febca                  por      mm1, mm2                       
  0x0021AA9B  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021AAA2  0febcb                  por      mm1, mm3                       
  0x0021AAA5  83c708                  add      edi, 8                         
  0x0021AAA8  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021AAAD  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021AAB1  3bf8                    cmp      edi, eax                       
  0x0021AAB3  0f8227ffffff            jb       0x21a9e0                       
  0x0021AAB9  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021AABF  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021AAC5  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021AACB  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021AAD1  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021AAD7  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021AADB  c1e003                  shl      eax, 3                         
  0x0021AADE  03c7                    add      eax, edi                       
  0x0021AAE0  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021AAE5  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021AAEC  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x0021ABC3 (cond_jump)
  0x0021AAF0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021AAF3  0fefc0                  pxor     mm0, mm0                       
  0x0021AAF6  33c0                    xor      eax, eax                       
  0x0021AAF8  83c204                  add      edx, 4                         
  0x0021AAFB  8a4500                  mov      al, byte ptr [ebp]             
  0x0021AAFE  0f60e0                  punpcklbw mm4, mm0                       
  0x0021AB01  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021AB09  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021AB11  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021AB14  83c502                  add      ebp, 2                         
  0x0021AB17  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021AB1E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021AB26  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021AB2E  8a03                    mov      al, byte ptr [ebx]             
  0x0021AB30  0f71f402                psllw    mm4, 2                         
  0x0021AB34  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021AB3B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021AB43  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021AB4B  0ffdd5                  paddw    mm2, mm5                       
  0x0021AB4E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021AB51  83c302                  add      ebx, 2                         
  0x0021AB54  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021AB5C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021AB64  0ffdf5                  paddw    mm6, mm5                       
  0x0021AB67  0f62d6                  punpckldq mm2, mm6                       
  0x0021AB6A  0ffdcc                  paddw    mm1, mm4                       
  0x0021AB6D  0ffdd4                  paddw    mm2, mm4                       
  0x0021AB70  0fedcf                  paddsw   mm1, mm7                       
  0x0021AB73  0ffddc                  paddw    mm3, mm4                       
  0x0021AB76  0fd9cf                  psubusw  mm1, mm7                       
  0x0021AB79  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021AB80  0fedd7                  paddsw   mm2, mm7                       
  0x0021AB83  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021AB8A  0fd9d7                  psubusw  mm2, mm7                       
  0x0021AB8D  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021AB94  0feddf                  paddsw   mm3, mm7                       
  0x0021AB97  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021AB9E  0fd9df                  psubusw  mm3, mm7                       
  0x0021ABA1  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021ABA8  0febca                  por      mm1, mm2                       
  0x0021ABAB  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021ABB2  0febcb                  por      mm1, mm3                       
  0x0021ABB5  83c708                  add      edi, 8                         
  0x0021ABB8  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021ABBD  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021ABC1  3bf8                    cmp      edi, eax                       
  0x0021ABC3  0f8227ffffff            jb       0x21aaf0                       
  0x0021ABC9  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021ABCF  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021ABD5  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021ABDB  5f                      pop      edi                            
  0x0021ABDC  5e                      pop      esi                            
  0x0021ABDD  5d                      pop      ebp                            
  0x0021ABDE  5b                      pop      ebx                            
  0x0021ABDF  c20400                  ret      4                              
; end of function
  0x0021ABE2  8da42400000000          lea      esp, [esp]                     
  0x0021ABE9  8da42400000000          lea      esp, [esp]                     
  0x0021ABF0  53                      push     ebx                            
  0x0021ABF1  55                      push     ebp                            
  0x0021ABF2  56                      push     esi                            
  0x0021ABF3  57                      push     edi                            
  0x0021ABF4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021ABFA  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021AC00  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021AC06  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021AC0C  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021AC10  c1e003                  shl      eax, 3                         
  0x0021AC13  03c7                    add      eax, edi                       
  0x0021AC15  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021AC1A  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021AC21  8da42400000000          lea      esp, [esp]                     
  0x0021AC28  8da42400000000          lea      esp, [esp]                     
  0x0021AC2F  90                      nop                                     
                                        ; XREF: 0x0021AD4C (cond_jump)
  0x0021AC30  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021AC33  0fefc0                  pxor     mm0, mm0                       
  0x0021AC36  33c0                    xor      eax, eax                       
  0x0021AC38  83c204                  add      edx, 4                         
  0x0021AC3B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021AC3E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021AC41  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021AC49  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021AC51  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021AC54  83c502                  add      ebp, 2                         
  0x0021AC57  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021AC5E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021AC66  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021AC6E  8a03                    mov      al, byte ptr [ebx]             
  0x0021AC70  0f71f402                psllw    mm4, 2                         
  0x0021AC74  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021AC7B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021AC83  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021AC8B  0ffdd5                  paddw    mm2, mm5                       
  0x0021AC8E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021AC91  83c302                  add      ebx, 2                         
  0x0021AC94  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021AC9C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021ACA4  0ffdf5                  paddw    mm6, mm5                       
  0x0021ACA7  8a4500                  mov      al, byte ptr [ebp]             
  0x0021ACAA  0f62d6                  punpckldq mm2, mm6                       
  0x0021ACAD  0f73d110                psrlq    mm1, 0x10                      
  0x0021ACB1  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021ACB9  0f73d210                psrlq    mm2, 0x10                      
  0x0021ACBD  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021ACC5  0f73d310                psrlq    mm3, 0x10                      
  0x0021ACC9  8a03                    mov      al, byte ptr [ebx]             
  0x0021ACCB  0f73f630                psllq    mm6, 0x30                      
  0x0021ACCF  0febce                  por      mm1, mm6                       
  0x0021ACD2  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021ACDA  0ffdee                  paddw    mm5, mm6                       
  0x0021ACDD  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021ACE5  0f73f530                psllq    mm5, 0x30                      
  0x0021ACE9  0f73f630                psllq    mm6, 0x30                      
  0x0021ACED  0febd5                  por      mm2, mm5                       
  0x0021ACF0  0febde                  por      mm3, mm6                       
  0x0021ACF3  0ffdcc                  paddw    mm1, mm4                       
  0x0021ACF6  0ffdd4                  paddw    mm2, mm4                       
  0x0021ACF9  0fedcf                  paddsw   mm1, mm7                       
  0x0021ACFC  0ffddc                  paddw    mm3, mm4                       
  0x0021ACFF  0fd9cf                  psubusw  mm1, mm7                       
  0x0021AD02  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021AD09  0fedd7                  paddsw   mm2, mm7                       
  0x0021AD0C  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021AD13  0fd9d7                  psubusw  mm2, mm7                       
  0x0021AD16  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021AD1D  0feddf                  paddsw   mm3, mm7                       
  0x0021AD20  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021AD27  0fd9df                  psubusw  mm3, mm7                       
  0x0021AD2A  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021AD31  0febca                  por      mm1, mm2                       
  0x0021AD34  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021AD3B  0febcb                  por      mm1, mm3                       
  0x0021AD3E  83c708                  add      edi, 8                         
  0x0021AD41  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021AD46  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021AD4A  3bf8                    cmp      edi, eax                       
  0x0021AD4C  0f82defeffff            jb       0x21ac30                       
  0x0021AD52  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021AD58  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021AD5E  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021AD64  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021AD6A  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021AD70  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021AD74  c1e003                  shl      eax, 3                         
  0x0021AD77  03c7                    add      eax, edi                       
  0x0021AD79  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021AD7E  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021AD85  8da42400000000          lea      esp, [esp]                     
  0x0021AD8C  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x0021AEAC (cond_jump)
  0x0021AD90  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021AD93  0fefc0                  pxor     mm0, mm0                       
  0x0021AD96  33c0                    xor      eax, eax                       
  0x0021AD98  83c204                  add      edx, 4                         
  0x0021AD9B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021AD9E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021ADA1  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021ADA9  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021ADB1  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021ADB4  83c502                  add      ebp, 2                         
  0x0021ADB7  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021ADBE  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021ADC6  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021ADCE  8a03                    mov      al, byte ptr [ebx]             
  0x0021ADD0  0f71f402                psllw    mm4, 2                         
  0x0021ADD4  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021ADDB  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021ADE3  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021ADEB  0ffdd5                  paddw    mm2, mm5                       
  0x0021ADEE  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021ADF1  83c302                  add      ebx, 2                         
  0x0021ADF4  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021ADFC  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021AE04  0ffdf5                  paddw    mm6, mm5                       
  0x0021AE07  8a4500                  mov      al, byte ptr [ebp]             
  0x0021AE0A  0f62d6                  punpckldq mm2, mm6                       
  0x0021AE0D  0f73d110                psrlq    mm1, 0x10                      
  0x0021AE11  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021AE19  0f73d210                psrlq    mm2, 0x10                      
  0x0021AE1D  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021AE25  0f73d310                psrlq    mm3, 0x10                      
  0x0021AE29  8a03                    mov      al, byte ptr [ebx]             
  0x0021AE2B  0f73f630                psllq    mm6, 0x30                      
  0x0021AE2F  0febce                  por      mm1, mm6                       
  0x0021AE32  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021AE3A  0ffdee                  paddw    mm5, mm6                       
  0x0021AE3D  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021AE45  0f73f530                psllq    mm5, 0x30                      
  0x0021AE49  0f73f630                psllq    mm6, 0x30                      
  0x0021AE4D  0febd5                  por      mm2, mm5                       
  0x0021AE50  0febde                  por      mm3, mm6                       
  0x0021AE53  0ffdcc                  paddw    mm1, mm4                       
  0x0021AE56  0ffdd4                  paddw    mm2, mm4                       
  0x0021AE59  0fedcf                  paddsw   mm1, mm7                       
  0x0021AE5C  0ffddc                  paddw    mm3, mm4                       
  0x0021AE5F  0fd9cf                  psubusw  mm1, mm7                       
  0x0021AE62  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021AE69  0fedd7                  paddsw   mm2, mm7                       
  0x0021AE6C  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021AE73  0fd9d7                  psubusw  mm2, mm7                       
  0x0021AE76  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021AE7D  0feddf                  paddsw   mm3, mm7                       
  0x0021AE80  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021AE87  0fd9df                  psubusw  mm3, mm7                       
  0x0021AE8A  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021AE91  0febca                  por      mm1, mm2                       
  0x0021AE94  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021AE9B  0febcb                  por      mm1, mm3                       
  0x0021AE9E  83c708                  add      edi, 8                         
  0x0021AEA1  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021AEA6  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021AEAA  3bf8                    cmp      edi, eax                       
  0x0021AEAC  0f82defeffff            jb       0x21ad90                       
  0x0021AEB2  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021AEB8  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021AEBE  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021AEC4  5f                      pop      edi                            
  0x0021AEC5  5e                      pop      esi                            
  0x0021AEC6  5d                      pop      ebp                            
  0x0021AEC7  5b                      pop      ebx                            
  0x0021AEC8  c20400                  ret      4                              
