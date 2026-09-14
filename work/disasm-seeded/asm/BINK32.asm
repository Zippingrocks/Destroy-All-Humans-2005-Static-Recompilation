; ============================================================
; Section: BINK32
; VA: 0x00217680 - 0x00218805
; Size: 4485 bytes (4.4 KB)
; Functions: 17
; Instructions: 1311
; ============================================================

  0x00217680  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00217684  85d2                    test     edx, edx                       
  0x00217686  7442                    je       0x2176ca                       
  0x00217688  eb06                    jmp      0x217690                       
  0x0021768A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x00217688 (jump), 0x002176C8 (cond_jump)
  0x00217690  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217696  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00217699  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x002176A0  41                      inc      ecx                            
  0x002176A1  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x002176A7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002176AD  8901                    mov      dword ptr [ecx], eax           
  0x002176AF  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002176B5  894104                  mov      dword ptr [ecx + 4], eax       
  0x002176B8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002176BE  83c108                  add      ecx, 8                         
  0x002176C1  4a                      dec      edx                            
  0x002176C2  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x002176C8  75c6                    jne      0x217690                       
                                        ; XREF: 0x00217686 (cond_jump)
  0x002176CA  c3                      ret                                     
  0x002176CB  cc                      int3                                    
  0x002176CC  cc                      int3                                    
  0x002176CD  cc                      int3                                    
  0x002176CE  cc                      int3                                    
  0x002176CF  cc                      int3                                    

; ============================================================
; Function: sub_002176D0
; Start: 0x002176D0  End: 0x00217757  Size: 135 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002176D0:
  0x002176D0  56                      push     esi                            
  0x002176D1  8b742408                mov      esi, dword ptr [esp + 8]       
  0x002176D5  57                      push     edi                            
  0x002176D6  8bd6                    mov      edx, esi                       
  0x002176D8  bf08000000              mov      edi, 8                         
  0x002176DD  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021774B (cond_jump)
  0x002176E0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x002176E6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x002176E9  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x002176F0  41                      inc      ecx                            
  0x002176F1  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x002176F7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002176FD  8901                    mov      dword ptr [ecx], eax           
  0x002176FF  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217705  894104                  mov      dword ptr [ecx + 4], eax       
  0x00217708  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021770E  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00217711  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x00217718  41                      inc      ecx                            
  0x00217719  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021771F  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00217725  8901                    mov      dword ptr [ecx], eax           
  0x00217727  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021772D  894104                  mov      dword ptr [ecx + 4], eax       
  0x00217730  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x00217735  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021773B  03c7                    add      eax, edi                       
  0x0021773D  03cf                    add      ecx, edi                       
  0x0021773F  4a                      dec      edx                            
  0x00217740  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x00217745  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021774B  7593                    jne      0x2176e0                       
  0x0021774D  8b542410                mov      edx, dword ptr [esp + 0x10]    
  0x00217751  5f                      pop      edi                            
  0x00217752  8d0416                  lea      eax, [esi + edx]               
  0x00217755  5e                      pop      esi                            
  0x00217756  c3                      ret                                     
; end of function
  0x00217757  cc                      int3                                    
  0x00217758  cc                      int3                                    
  0x00217759  cc                      int3                                    
  0x0021775A  cc                      int3                                    
  0x0021775B  cc                      int3                                    
  0x0021775C  cc                      int3                                    
  0x0021775D  cc                      int3                                    
  0x0021775E  cc                      int3                                    
  0x0021775F  cc                      int3                                    

; ============================================================
; Function: sub_00217760
; Start: 0x00217760  End: 0x002177B2  Size: 82 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217760:
  0x00217760  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00217764  85d2                    test     edx, edx                       
  0x00217766  7449                    je       0x2177b1                       
  0x00217768  56                      push     esi                            
  0x00217769  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x002177AE (cond_jump)
  0x00217770  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217776  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00217779  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x00217780  41                      inc      ecx                            
  0x00217781  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00217787  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021778D  8901                    mov      dword ptr [ecx], eax           
  0x0021778F  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217795  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x0021779B  89040e                  mov      dword ptr [esi + ecx], eax     
  0x0021779E  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002177A4  83c104                  add      ecx, 4                         
  0x002177A7  4a                      dec      edx                            
  0x002177A8  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x002177AE  75c0                    jne      0x217770                       
  0x002177B0  5e                      pop      esi                            
                                        ; XREF: 0x00217766 (cond_jump)
  0x002177B1  c3                      ret                                     
; end of function
  0x002177B2  cc                      int3                                    
  0x002177B3  cc                      int3                                    
  0x002177B4  cc                      int3                                    
  0x002177B5  cc                      int3                                    
  0x002177B6  cc                      int3                                    
  0x002177B7  cc                      int3                                    
  0x002177B8  cc                      int3                                    
  0x002177B9  cc                      int3                                    
  0x002177BA  cc                      int3                                    
  0x002177BB  cc                      int3                                    
  0x002177BC  cc                      int3                                    
  0x002177BD  cc                      int3                                    
  0x002177BE  cc                      int3                                    
  0x002177BF  cc                      int3                                    

; ============================================================
; Function: sub_002177C0
; Start: 0x002177C0  End: 0x00217856  Size: 150 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002177C0:
  0x002177C0  53                      push     ebx                            
  0x002177C1  56                      push     esi                            
  0x002177C2  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x002177C6  57                      push     edi                            
  0x002177C7  8bd6                    mov      edx, esi                       
  0x002177C9  bf04000000              mov      edi, 4                         
  0x002177CE  8bff                    mov      edi, edi                       
                                        ; XREF: 0x00217849 (cond_jump)
  0x002177D0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x002177D6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x002177D9  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x002177E0  41                      inc      ecx                            
  0x002177E1  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x002177E7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002177ED  8901                    mov      dword ptr [ecx], eax           
  0x002177EF  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x002177F5  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x002177FB  890419                  mov      dword ptr [ecx + ebx], eax     
  0x002177FE  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00217804  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00217807  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x0021780E  41                      inc      ecx                            
  0x0021780F  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00217815  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021781B  8901                    mov      dword ptr [ecx], eax           
  0x0021781D  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00217823  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x00217829  890419                  mov      dword ptr [ecx + ebx], eax     
  0x0021782C  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00217832  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00217838  03df                    add      ebx, edi                       
  0x0021783A  03cf                    add      ecx, edi                       
  0x0021783C  4a                      dec      edx                            
  0x0021783D  891d109f2900            mov      dword ptr [0x299f10], ebx      
  0x00217843  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x00217849  7585                    jne      0x2177d0                       
  0x0021784B  8b542414                mov      edx, dword ptr [esp + 0x14]    
  0x0021784F  5f                      pop      edi                            
  0x00217850  8d0416                  lea      eax, [esi + edx]               
  0x00217853  5e                      pop      esi                            
  0x00217854  5b                      pop      ebx                            
  0x00217855  c3                      ret                                     
; end of function
  0x00217856  cc                      int3                                    
  0x00217857  cc                      int3                                    
  0x00217858  cc                      int3                                    
  0x00217859  cc                      int3                                    
  0x0021785A  cc                      int3                                    
  0x0021785B  cc                      int3                                    
  0x0021785C  cc                      int3                                    
  0x0021785D  cc                      int3                                    
  0x0021785E  cc                      int3                                    
  0x0021785F  cc                      int3                                    

; ============================================================
; Function: sub_00217860
; Start: 0x00217860  End: 0x002178CB  Size: 107 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217860:
  0x00217860  8b542408                mov      edx, dword ptr [esp + 8]       
  0x00217864  85d2                    test     edx, edx                       
  0x00217866  7462                    je       0x2178ca                       
  0x00217868  56                      push     esi                            
  0x00217869  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x002178C7 (cond_jump)
  0x00217870  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217876  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00217879  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x00217880  41                      inc      ecx                            
  0x00217881  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00217887  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021788D  8901                    mov      dword ptr [ecx], eax           
  0x0021788F  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217895  894104                  mov      dword ptr [ecx + 4], eax       
  0x00217898  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x0021789E  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x002178A4  890431                  mov      dword ptr [ecx + esi], eax     
  0x002178A7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002178AD  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x002178B3  89440e04                mov      dword ptr [esi + ecx + 4], eax 
  0x002178B7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002178BD  83c108                  add      ecx, 8                         
  0x002178C0  4a                      dec      edx                            
  0x002178C1  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x002178C7  75a7                    jne      0x217870                       
  0x002178C9  5e                      pop      esi                            
                                        ; XREF: 0x00217866 (cond_jump)
  0x002178CA  c3                      ret                                     
; end of function
  0x002178CB  cc                      int3                                    
  0x002178CC  cc                      int3                                    
  0x002178CD  cc                      int3                                    
  0x002178CE  cc                      int3                                    
  0x002178CF  cc                      int3                                    

; ============================================================
; Function: sub_002178D0
; Start: 0x002178D0  End: 0x0021799C  Size: 204 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002178D0:
  0x002178D0  53                      push     ebx                            
  0x002178D1  56                      push     esi                            
  0x002178D2  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x002178D6  57                      push     edi                            
  0x002178D7  8bd6                    mov      edx, esi                       
  0x002178D9  bf08000000              mov      edi, 8                         
  0x002178DE  8bff                    mov      edi, edi                       
                                        ; XREF: 0x0021798B (cond_jump)
  0x002178E0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x002178E6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x002178E9  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x002178F0  41                      inc      ecx                            
  0x002178F1  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x002178F7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002178FD  8901                    mov      dword ptr [ecx], eax           
  0x002178FF  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217905  894104                  mov      dword ptr [ecx + 4], eax       
  0x00217908  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x0021790E  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00217914  890419                  mov      dword ptr [ecx + ebx], eax     
  0x00217917  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x0021791D  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00217923  89441904                mov      dword ptr [ecx + ebx + 4], eax 
  0x00217927  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021792D  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00217930  8b0485109b2900          mov      eax, dword ptr [eax*4 + 0x299b10] 
  0x00217937  41                      inc      ecx                            
  0x00217938  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021793E  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00217944  8901                    mov      dword ptr [ecx], eax           
  0x00217946  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021794C  894104                  mov      dword ptr [ecx + 4], eax       
  0x0021794F  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00217955  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x0021795B  890419                  mov      dword ptr [ecx + ebx], eax     
  0x0021795E  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00217964  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x0021796A  89441904                mov      dword ptr [ecx + ebx + 4], eax 
  0x0021796E  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00217974  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021797A  03df                    add      ebx, edi                       
  0x0021797C  03cf                    add      ecx, edi                       
  0x0021797E  4a                      dec      edx                            
  0x0021797F  891d109f2900            mov      dword ptr [0x299f10], ebx      
  0x00217985  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021798B  0f854fffffff            jne      0x2178e0                       
  0x00217991  8b542414                mov      edx, dword ptr [esp + 0x14]    
  0x00217995  5f                      pop      edi                            
  0x00217996  8d0416                  lea      eax, [esi + edx]               
  0x00217999  5e                      pop      esi                            
  0x0021799A  5b                      pop      ebx                            
  0x0021799B  c3                      ret                                     
; end of function
  0x0021799C  cc                      int3                                    
  0x0021799D  cc                      int3                                    
  0x0021799E  cc                      int3                                    
  0x0021799F  cc                      int3                                    

; ============================================================
; Function: sub_002179A0
; Start: 0x002179A0  End: 0x00217A63  Size: 195 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002179A0:
  0x002179A0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x002179A4  85c0                    test     eax, eax                       
  0x002179A6  53                      push     ebx                            
  0x002179A7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x002179AB  0f84b0000000            je       0x217a61                       
  0x002179B1  55                      push     ebp                            
  0x002179B2  56                      push     esi                            
  0x002179B3  57                      push     edi                            
  0x002179B4  8be8                    mov      ebp, eax                       
  0x002179B6  eb08                    jmp      0x2179c0                       
  0x002179B8  8da42400000000          lea      esp, [esp]                     
  0x002179BF  90                      nop                                     
                                        ; XREF: 0x002179B6 (jump), 0x00217A58 (cond_jump)
  0x002179C0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x002179C5  0fb600                  movzx    eax, byte ptr [eax]            
  0x002179C8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x002179CE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x002179D1  c1e002                  shl      eax, 2                         
  0x002179D4  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x002179DA  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x002179E0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x002179E5  c1e102                  shl      ecx, 2                         
  0x002179E8  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x002179EE  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x002179F4  03d6                    add      edx, esi                       
  0x002179F6  0fb630                  movzx    esi, byte ptr [eax]            
  0x002179F9  8b34b5c05e2900          mov      esi, dword ptr [esi*4 + 0x295ec0] 
  0x00217A00  40                      inc      eax                            
  0x00217A01  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x00217A06  8b048e                  mov      eax, dword ptr [esi + ecx*4]   
  0x00217A09  8b0c96                  mov      ecx, dword ptr [esi + edx*4]   
  0x00217A0C  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217A12  c1e008                  shl      eax, 8                         
  0x00217A15  0bc1                    or       eax, ecx                       
  0x00217A17  8b0cbe                  mov      ecx, dword ptr [esi + edi*4]   
  0x00217A1A  c1e008                  shl      eax, 8                         
  0x00217A1D  0bc1                    or       eax, ecx                       
  0x00217A1F  8902                    mov      dword ptr [edx], eax           
  0x00217A21  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217A27  894104                  mov      dword ptr [ecx + 4], eax       
  0x00217A2A  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217A30  83c208                  add      edx, 8                         
  0x00217A33  43                      inc      ebx                            
  0x00217A34  f6c301                  test     bl, 1                          
  0x00217A37  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00217A3D  7518                    jne      0x217a57                       
  0x00217A3F  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x00217A45  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x00217A4A  41                      inc      ecx                            
  0x00217A4B  40                      inc      eax                            
  0x00217A4C  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x00217A52  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x00217A3D (cond_jump)
  0x00217A57  4d                      dec      ebp                            
  0x00217A58  0f8562ffffff            jne      0x2179c0                       
  0x00217A5E  5f                      pop      edi                            
  0x00217A5F  5e                      pop      esi                            
  0x00217A60  5d                      pop      ebp                            
                                        ; XREF: 0x002179AB (cond_jump)
  0x00217A61  5b                      pop      ebx                            
  0x00217A62  c3                      ret                                     
; end of function
  0x00217A63  cc                      int3                                    
  0x00217A64  cc                      int3                                    
  0x00217A65  cc                      int3                                    
  0x00217A66  cc                      int3                                    
  0x00217A67  cc                      int3                                    
  0x00217A68  cc                      int3                                    
  0x00217A69  cc                      int3                                    
  0x00217A6A  cc                      int3                                    
  0x00217A6B  cc                      int3                                    
  0x00217A6C  cc                      int3                                    
  0x00217A6D  cc                      int3                                    
  0x00217A6E  cc                      int3                                    
  0x00217A6F  cc                      int3                                    

; ============================================================
; Function: sub_00217A70
; Start: 0x00217A70  End: 0x00217B70  Size: 256 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217A70:
  0x00217A70  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00217A74  53                      push     ebx                            
  0x00217A75  55                      push     ebp                            
  0x00217A76  8b6c240c                mov      ebp, dword ptr [esp + 0xc]     
  0x00217A7A  56                      push     esi                            
  0x00217A7B  57                      push     edi                            
  0x00217A7C  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x00217B65 (cond_jump)
  0x00217A80  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x00217A86  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00217A89  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x00217A8F  0fb612                  movzx    edx, byte ptr [edx]            
  0x00217A92  c1e102                  shl      ecx, 2                         
  0x00217A95  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x00217A9B  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x00217AA1  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217AA7  c1e202                  shl      edx, 2                         
  0x00217AAA  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x00217AB0  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00217AB6  03f7                    add      esi, edi                       
  0x00217AB8  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00217ABB  8b3cbdc05e2900          mov      edi, dword ptr [edi*4 + 0x295ec0] 
  0x00217AC2  41                      inc      ecx                            
  0x00217AC3  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00217AC9  8b0c97                  mov      ecx, dword ptr [edi + edx*4]   
  0x00217ACC  c1e108                  shl      ecx, 8                         
  0x00217ACF  0b0cb7                  or       ecx, dword ptr [edi + esi*4]   
  0x00217AD2  c1e108                  shl      ecx, 8                         
  0x00217AD5  0b0c9f                  or       ecx, dword ptr [edi + ebx*4]   
  0x00217AD8  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217ADE  890f                    mov      dword ptr [edi], ecx           
  0x00217AE0  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217AE6  894f04                  mov      dword ptr [edi + 4], ecx       
  0x00217AE9  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00217AEF  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00217AF2  8b3cbdc05e2900          mov      edi, dword ptr [edi*4 + 0x295ec0] 
  0x00217AF9  41                      inc      ecx                            
  0x00217AFA  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00217B00  8b0c97                  mov      ecx, dword ptr [edi + edx*4]   
  0x00217B03  8b14b7                  mov      edx, dword ptr [edi + esi*4]   
  0x00217B06  c1e108                  shl      ecx, 8                         
  0x00217B09  0bca                    or       ecx, edx                       
  0x00217B0B  8b149f                  mov      edx, dword ptr [edi + ebx*4]   
  0x00217B0E  c1e108                  shl      ecx, 8                         
  0x00217B11  0bca                    or       ecx, edx                       
  0x00217B13  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217B19  890a                    mov      dword ptr [edx], ecx           
  0x00217B1B  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217B21  894a04                  mov      dword ptr [edx + 4], ecx       
  0x00217B24  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217B2A  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x00217B30  b908000000              mov      ecx, 8                         
  0x00217B35  03f9                    add      edi, ecx                       
  0x00217B37  03f1                    add      esi, ecx                       
  0x00217B39  40                      inc      eax                            
  0x00217B3A  a801                    test     al, 1                          
  0x00217B3C  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x00217B42  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x00217B48  751a                    jne      0x217b64                       
  0x00217B4A  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00217B50  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00217B56  42                      inc      edx                            
  0x00217B57  41                      inc      ecx                            
  0x00217B58  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x00217B5E  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x00217B48 (cond_jump)
  0x00217B64  4d                      dec      ebp                            
  0x00217B65  0f8515ffffff            jne      0x217a80                       
  0x00217B6B  5f                      pop      edi                            
  0x00217B6C  5e                      pop      esi                            
  0x00217B6D  5d                      pop      ebp                            
  0x00217B6E  5b                      pop      ebx                            
  0x00217B6F  c3                      ret                                     
; end of function
  0x00217B70  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00217B74  85c0                    test     eax, eax                       
  0x00217B76  53                      push     ebx                            
  0x00217B77  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x00217B7B  0f84b6000000            je       0x217c37                       
  0x00217B81  55                      push     ebp                            
  0x00217B82  56                      push     esi                            
  0x00217B83  57                      push     edi                            
  0x00217B84  8be8                    mov      ebp, eax                       
  0x00217B86  eb08                    jmp      0x217b90                       
  0x00217B88  8da42400000000          lea      esp, [esp]                     
  0x00217B8F  90                      nop                                     
                                        ; XREF: 0x00217B86 (jump), 0x00217C2E (cond_jump)
  0x00217B90  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x00217B95  0fb600                  movzx    eax, byte ptr [eax]            
  0x00217B98  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00217B9E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00217BA1  c1e002                  shl      eax, 2                         
  0x00217BA4  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x00217BAA  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x00217BB0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x00217BB5  c1e102                  shl      ecx, 2                         
  0x00217BB8  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x00217BBE  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x00217BC4  03d6                    add      edx, esi                       
  0x00217BC6  0fb630                  movzx    esi, byte ptr [eax]            
  0x00217BC9  8b34b5c05e2900          mov      esi, dword ptr [esi*4 + 0x295ec0] 
  0x00217BD0  40                      inc      eax                            
  0x00217BD1  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x00217BD6  8b048e                  mov      eax, dword ptr [esi + ecx*4]   
  0x00217BD9  8b0c96                  mov      ecx, dword ptr [esi + edx*4]   
  0x00217BDC  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217BE2  c1e008                  shl      eax, 8                         
  0x00217BE5  0bc1                    or       eax, ecx                       
  0x00217BE7  8b0cbe                  mov      ecx, dword ptr [esi + edi*4]   
  0x00217BEA  c1e008                  shl      eax, 8                         
  0x00217BED  0bc1                    or       eax, ecx                       
  0x00217BEF  8902                    mov      dword ptr [edx], eax           
  0x00217BF1  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217BF7  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00217BFD  89040a                  mov      dword ptr [edx + ecx], eax     
  0x00217C00  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217C06  83c204                  add      edx, 4                         
  0x00217C09  43                      inc      ebx                            
  0x00217C0A  f6c301                  test     bl, 1                          
  0x00217C0D  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00217C13  7518                    jne      0x217c2d                       
  0x00217C15  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x00217C1B  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x00217C20  41                      inc      ecx                            
  0x00217C21  40                      inc      eax                            
  0x00217C22  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x00217C28  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x00217C13 (cond_jump)
  0x00217C2D  4d                      dec      ebp                            
  0x00217C2E  0f855cffffff            jne      0x217b90                       
  0x00217C34  5f                      pop      edi                            
  0x00217C35  5e                      pop      esi                            
  0x00217C36  5d                      pop      ebp                            
                                        ; XREF: 0x00217B7B (cond_jump)
  0x00217C37  5b                      pop      ebx                            
  0x00217C38  c3                      ret                                     
  0x00217C39  cc                      int3                                    
  0x00217C3A  cc                      int3                                    
  0x00217C3B  cc                      int3                                    
  0x00217C3C  cc                      int3                                    
  0x00217C3D  cc                      int3                                    
  0x00217C3E  cc                      int3                                    
  0x00217C3F  cc                      int3                                    

; ============================================================
; Function: sub_00217C40
; Start: 0x00217C40  End: 0x00217D53  Size: 275 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217C40:
  0x00217C40  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00217C44  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00217C48  53                      push     ebx                            
  0x00217C49  55                      push     ebp                            
  0x00217C4A  56                      push     esi                            
  0x00217C4B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x00217C4F  57                      push     edi                            
                                        ; XREF: 0x00217D48 (cond_jump)
  0x00217C50  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00217C56  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x00217C59  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x00217C5F  0fb612                  movzx    edx, byte ptr [edx]            
  0x00217C62  c1e102                  shl      ecx, 2                         
  0x00217C65  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x00217C6B  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x00217C71  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217C77  c1e202                  shl      edx, 2                         
  0x00217C7A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x00217C80  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00217C86  03f7                    add      esi, edi                       
  0x00217C88  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00217C8B  8b3cbdc05e2900          mov      edi, dword ptr [edi*4 + 0x295ec0] 
  0x00217C92  41                      inc      ecx                            
  0x00217C93  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00217C99  8b0c97                  mov      ecx, dword ptr [edi + edx*4]   
  0x00217C9C  8b2cb7                  mov      ebp, dword ptr [edi + esi*4]   
  0x00217C9F  c1e108                  shl      ecx, 8                         
  0x00217CA2  0bcd                    or       ecx, ebp                       
  0x00217CA4  8b2c9f                  mov      ebp, dword ptr [edi + ebx*4]   
  0x00217CA7  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217CAD  c1e108                  shl      ecx, 8                         
  0x00217CB0  0bcd                    or       ecx, ebp                       
  0x00217CB2  890f                    mov      dword ptr [edi], ecx           
  0x00217CB4  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x00217CBA  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x00217CC0  890c2f                  mov      dword ptr [edi + ebp], ecx     
  0x00217CC3  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00217CC9  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00217CCC  8b3cbdc05e2900          mov      edi, dword ptr [edi*4 + 0x295ec0] 
  0x00217CD3  41                      inc      ecx                            
  0x00217CD4  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00217CDA  8b0c97                  mov      ecx, dword ptr [edi + edx*4]   
  0x00217CDD  8b2cb7                  mov      ebp, dword ptr [edi + esi*4]   
  0x00217CE0  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217CE6  c1e108                  shl      ecx, 8                         
  0x00217CE9  0bcd                    or       ecx, ebp                       
  0x00217CEB  8b2c9f                  mov      ebp, dword ptr [edi + ebx*4]   
  0x00217CEE  c1e108                  shl      ecx, 8                         
  0x00217CF1  0bcd                    or       ecx, ebp                       
  0x00217CF3  890a                    mov      dword ptr [edx], ecx           
  0x00217CF5  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217CFB  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00217D01  890c32                  mov      dword ptr [edx + esi], ecx     
  0x00217D04  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217D0A  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x00217D10  b904000000              mov      ecx, 4                         
  0x00217D15  03f9                    add      edi, ecx                       
  0x00217D17  03f1                    add      esi, ecx                       
  0x00217D19  40                      inc      eax                            
  0x00217D1A  a801                    test     al, 1                          
  0x00217D1C  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x00217D22  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x00217D28  751a                    jne      0x217d44                       
  0x00217D2A  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00217D30  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00217D36  42                      inc      edx                            
  0x00217D37  41                      inc      ecx                            
  0x00217D38  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x00217D3E  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x00217D28 (cond_jump)
  0x00217D44  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x00217D48  0f8502ffffff            jne      0x217c50                       
  0x00217D4E  5f                      pop      edi                            
  0x00217D4F  5e                      pop      esi                            
  0x00217D50  5d                      pop      ebp                            
  0x00217D51  5b                      pop      ebx                            
  0x00217D52  c3                      ret                                     
; end of function
  0x00217D53  cc                      int3                                    
  0x00217D54  cc                      int3                                    
  0x00217D55  cc                      int3                                    
  0x00217D56  cc                      int3                                    
  0x00217D57  cc                      int3                                    
  0x00217D58  cc                      int3                                    
  0x00217D59  cc                      int3                                    
  0x00217D5A  cc                      int3                                    
  0x00217D5B  cc                      int3                                    
  0x00217D5C  cc                      int3                                    
  0x00217D5D  cc                      int3                                    
  0x00217D5E  cc                      int3                                    
  0x00217D5F  cc                      int3                                    

; ============================================================
; Function: sub_00217D60
; Start: 0x00217D60  End: 0x00217E42  Size: 226 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217D60:
  0x00217D60  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00217D64  85c0                    test     eax, eax                       
  0x00217D66  53                      push     ebx                            
  0x00217D67  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x00217D6B  0f84cf000000            je       0x217e40                       
  0x00217D71  55                      push     ebp                            
  0x00217D72  56                      push     esi                            
  0x00217D73  57                      push     edi                            
  0x00217D74  8be8                    mov      ebp, eax                       
  0x00217D76  eb08                    jmp      0x217d80                       
  0x00217D78  8da42400000000          lea      esp, [esp]                     
  0x00217D7F  90                      nop                                     
                                        ; XREF: 0x00217D76 (jump), 0x00217E37 (cond_jump)
  0x00217D80  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x00217D85  0fb600                  movzx    eax, byte ptr [eax]            
  0x00217D88  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00217D8E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00217D91  c1e002                  shl      eax, 2                         
  0x00217D94  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x00217D9A  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x00217DA0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x00217DA5  c1e102                  shl      ecx, 2                         
  0x00217DA8  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x00217DAE  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x00217DB4  03d6                    add      edx, esi                       
  0x00217DB6  0fb630                  movzx    esi, byte ptr [eax]            
  0x00217DB9  8b34b5c05e2900          mov      esi, dword ptr [esi*4 + 0x295ec0] 
  0x00217DC0  40                      inc      eax                            
  0x00217DC1  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x00217DC6  8b048e                  mov      eax, dword ptr [esi + ecx*4]   
  0x00217DC9  8b0c96                  mov      ecx, dword ptr [esi + edx*4]   
  0x00217DCC  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217DD2  c1e008                  shl      eax, 8                         
  0x00217DD5  0bc1                    or       eax, ecx                       
  0x00217DD7  8b0cbe                  mov      ecx, dword ptr [esi + edi*4]   
  0x00217DDA  c1e008                  shl      eax, 8                         
  0x00217DDD  0bc1                    or       eax, ecx                       
  0x00217DDF  8902                    mov      dword ptr [edx], eax           
  0x00217DE1  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217DE7  894104                  mov      dword ptr [ecx + 4], eax       
  0x00217DEA  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00217DF0  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00217DF6  89040a                  mov      dword ptr [edx + ecx], eax     
  0x00217DF9  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217DFF  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00217E05  89441104                mov      dword ptr [ecx + edx + 4], eax 
  0x00217E09  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217E0F  83c208                  add      edx, 8                         
  0x00217E12  43                      inc      ebx                            
  0x00217E13  f6c301                  test     bl, 1                          
  0x00217E16  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00217E1C  7518                    jne      0x217e36                       
  0x00217E1E  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x00217E24  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x00217E29  41                      inc      ecx                            
  0x00217E2A  40                      inc      eax                            
  0x00217E2B  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x00217E31  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x00217E1C (cond_jump)
  0x00217E36  4d                      dec      ebp                            
  0x00217E37  0f8543ffffff            jne      0x217d80                       
  0x00217E3D  5f                      pop      edi                            
  0x00217E3E  5e                      pop      esi                            
  0x00217E3F  5d                      pop      ebp                            
                                        ; XREF: 0x00217D6B (cond_jump)
  0x00217E40  5b                      pop      ebx                            
  0x00217E41  c3                      ret                                     
; end of function
  0x00217E42  cc                      int3                                    
  0x00217E43  cc                      int3                                    
  0x00217E44  cc                      int3                                    
  0x00217E45  cc                      int3                                    
  0x00217E46  cc                      int3                                    
  0x00217E47  cc                      int3                                    
  0x00217E48  cc                      int3                                    
  0x00217E49  cc                      int3                                    
  0x00217E4A  cc                      int3                                    
  0x00217E4B  cc                      int3                                    
  0x00217E4C  cc                      int3                                    
  0x00217E4D  cc                      int3                                    
  0x00217E4E  cc                      int3                                    
  0x00217E4F  cc                      int3                                    

; ============================================================
; Function: sub_00217E50
; Start: 0x00217E50  End: 0x00217F95  Size: 325 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217E50:
  0x00217E50  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00217E54  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00217E58  53                      push     ebx                            
  0x00217E59  55                      push     ebp                            
  0x00217E5A  56                      push     esi                            
  0x00217E5B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x00217E5F  57                      push     edi                            
                                        ; XREF: 0x00217F8A (cond_jump)
  0x00217E60  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00217E66  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x00217E69  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x00217E6F  0fb612                  movzx    edx, byte ptr [edx]            
  0x00217E72  c1e102                  shl      ecx, 2                         
  0x00217E75  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x00217E7B  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x00217E81  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217E87  c1e202                  shl      edx, 2                         
  0x00217E8A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x00217E90  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00217E96  03f7                    add      esi, edi                       
  0x00217E98  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00217E9B  8b3cbdc05e2900          mov      edi, dword ptr [edi*4 + 0x295ec0] 
  0x00217EA2  41                      inc      ecx                            
  0x00217EA3  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00217EA9  8b0c97                  mov      ecx, dword ptr [edi + edx*4]   
  0x00217EAC  8b2cb7                  mov      ebp, dword ptr [edi + esi*4]   
  0x00217EAF  c1e108                  shl      ecx, 8                         
  0x00217EB2  0bcd                    or       ecx, ebp                       
  0x00217EB4  8b2c9f                  mov      ebp, dword ptr [edi + ebx*4]   
  0x00217EB7  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217EBD  c1e108                  shl      ecx, 8                         
  0x00217EC0  0bcd                    or       ecx, ebp                       
  0x00217EC2  890f                    mov      dword ptr [edi], ecx           
  0x00217EC4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217ECA  894f04                  mov      dword ptr [edi + 4], ecx       
  0x00217ECD  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x00217ED3  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x00217ED9  890c2f                  mov      dword ptr [edi + ebp], ecx     
  0x00217EDC  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x00217EE2  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x00217EE8  894c2f04                mov      dword ptr [edi + ebp + 4], ecx 
  0x00217EEC  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00217EF2  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00217EF5  8b3cbdc05e2900          mov      edi, dword ptr [edi*4 + 0x295ec0] 
  0x00217EFC  41                      inc      ecx                            
  0x00217EFD  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00217F03  8b0c97                  mov      ecx, dword ptr [edi + edx*4]   
  0x00217F06  8b2cb7                  mov      ebp, dword ptr [edi + esi*4]   
  0x00217F09  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217F0F  c1e108                  shl      ecx, 8                         
  0x00217F12  0bcd                    or       ecx, ebp                       
  0x00217F14  8b2c9f                  mov      ebp, dword ptr [edi + ebx*4]   
  0x00217F17  c1e108                  shl      ecx, 8                         
  0x00217F1A  0bcd                    or       ecx, ebp                       
  0x00217F1C  890a                    mov      dword ptr [edx], ecx           
  0x00217F1E  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217F24  894a04                  mov      dword ptr [edx + 4], ecx       
  0x00217F27  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217F2D  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00217F33  890c32                  mov      dword ptr [edx + esi], ecx     
  0x00217F36  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00217F3C  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00217F42  894c3204                mov      dword ptr [edx + esi + 4], ecx 
  0x00217F46  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00217F4C  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x00217F52  b908000000              mov      ecx, 8                         
  0x00217F57  03f9                    add      edi, ecx                       
  0x00217F59  03f1                    add      esi, ecx                       
  0x00217F5B  40                      inc      eax                            
  0x00217F5C  a801                    test     al, 1                          
  0x00217F5E  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x00217F64  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x00217F6A  751a                    jne      0x217f86                       
  0x00217F6C  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00217F72  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00217F78  42                      inc      edx                            
  0x00217F79  41                      inc      ecx                            
  0x00217F7A  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x00217F80  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x00217F6A (cond_jump)
  0x00217F86  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x00217F8A  0f85d0feffff            jne      0x217e60                       
  0x00217F90  5f                      pop      edi                            
  0x00217F91  5e                      pop      esi                            
  0x00217F92  5d                      pop      ebp                            
  0x00217F93  5b                      pop      ebx                            
  0x00217F94  c3                      ret                                     
; end of function
  0x00217F95  cc                      int3                                    
  0x00217F96  cc                      int3                                    
  0x00217F97  cc                      int3                                    
  0x00217F98  cc                      int3                                    
  0x00217F99  cc                      int3                                    
  0x00217F9A  cc                      int3                                    
  0x00217F9B  cc                      int3                                    
  0x00217F9C  cc                      int3                                    
  0x00217F9D  cc                      int3                                    
  0x00217F9E  cc                      int3                                    
  0x00217F9F  cc                      int3                                    

; ============================================================
; Function: sub_00217FA0
; Start: 0x00217FA0  End: 0x00217FE8  Size: 72 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217FA0:
  0x00217FA0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00217FA4  85c0                    test     eax, eax                       
  0x00217FA6  743f                    je       0x217fe7                       
  0x00217FA8  eb06                    jmp      0x217fb0                       
  0x00217FAA  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x00217FA8 (jump), 0x00217FE5 (cond_jump)
  0x00217FB0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217FB6  0fb611                  movzx    edx, byte ptr [ecx]            
  0x00217FB9  8b0c95109b2900          mov      ecx, dword ptr [edx*4 + 0x299b10] 
  0x00217FC0  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217FC6  890a                    mov      dword ptr [edx], ecx           
  0x00217FC8  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00217FCE  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00217FD4  41                      inc      ecx                            
  0x00217FD5  83c204                  add      edx, 4                         
  0x00217FD8  48                      dec      eax                            
  0x00217FD9  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00217FDF  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00217FE5  75c9                    jne      0x217fb0                       
                                        ; XREF: 0x00217FA6 (cond_jump)
  0x00217FE7  c3                      ret                                     
; end of function
  0x00217FE8  cc                      int3                                    
  0x00217FE9  cc                      int3                                    
  0x00217FEA  cc                      int3                                    
  0x00217FEB  cc                      int3                                    
  0x00217FEC  cc                      int3                                    
  0x00217FED  cc                      int3                                    
  0x00217FEE  cc                      int3                                    
  0x00217FEF  cc                      int3                                    

; ============================================================
; Function: sub_00217FF0
; Start: 0x00217FF0  End: 0x00218072  Size: 130 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00217FF0:
  0x00217FF0  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00217FF4  56                      push     esi                            
  0x00217FF5  8bc1                    mov      eax, ecx                       
  0x00217FF7  ba04000000              mov      edx, 4                         
  0x00217FFC  57                      push     edi                            
  0x00217FFD  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x00218067 (cond_jump)
  0x00218000  8b35189f2900            mov      esi, dword ptr [0x299f18]      
  0x00218006  0fb636                  movzx    esi, byte ptr [esi]            
  0x00218009  8b34b5109b2900          mov      esi, dword ptr [esi*4 + 0x299b10] 
  0x00218010  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00218016  8937                    mov      dword ptr [edi], esi           
  0x00218018  8b35189f2900            mov      esi, dword ptr [0x299f18]      
  0x0021801E  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x00218024  46                      inc      esi                            
  0x00218025  8935189f2900            mov      dword ptr [0x299f18], esi      
  0x0021802B  8b351c9f2900            mov      esi, dword ptr [0x299f1c]      
  0x00218031  0fb636                  movzx    esi, byte ptr [esi]            
  0x00218034  8b34b5109b2900          mov      esi, dword ptr [esi*4 + 0x299b10] 
  0x0021803B  8937                    mov      dword ptr [edi], esi           
  0x0021803D  8b3d1c9f2900            mov      edi, dword ptr [0x299f1c]      
  0x00218043  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x00218049  47                      inc      edi                            
  0x0021804A  893d1c9f2900            mov      dword ptr [0x299f1c], edi      
  0x00218050  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x00218056  03f2                    add      esi, edx                       
  0x00218058  03fa                    add      edi, edx                       
  0x0021805A  48                      dec      eax                            
  0x0021805B  8935109f2900            mov      dword ptr [0x299f10], esi      
  0x00218061  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x00218067  7597                    jne      0x218000                       
  0x00218069  8b442410                mov      eax, dword ptr [esp + 0x10]    
  0x0021806D  5f                      pop      edi                            
  0x0021806E  03c1                    add      eax, ecx                       
  0x00218070  5e                      pop      esi                            
  0x00218071  c3                      ret                                     
; end of function
  0x00218072  cc                      int3                                    
  0x00218073  cc                      int3                                    
  0x00218074  cc                      int3                                    
  0x00218075  cc                      int3                                    
  0x00218076  cc                      int3                                    
  0x00218077  cc                      int3                                    
  0x00218078  cc                      int3                                    
  0x00218079  cc                      int3                                    
  0x0021807A  cc                      int3                                    
  0x0021807B  cc                      int3                                    
  0x0021807C  cc                      int3                                    
  0x0021807D  cc                      int3                                    
  0x0021807E  cc                      int3                                    
  0x0021807F  cc                      int3                                    

; ============================================================
; Function: sub_00218080
; Start: 0x00218080  End: 0x0021813C  Size: 188 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218080:
  0x00218080  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00218084  85c0                    test     eax, eax                       
  0x00218086  53                      push     ebx                            
  0x00218087  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021808B  0f84a9000000            je       0x21813a                       
  0x00218091  55                      push     ebp                            
  0x00218092  56                      push     esi                            
  0x00218093  57                      push     edi                            
  0x00218094  8be8                    mov      ebp, eax                       
  0x00218096  eb08                    jmp      0x2180a0                       
  0x00218098  8da42400000000          lea      esp, [esp]                     
  0x0021809F  90                      nop                                     
                                        ; XREF: 0x00218096 (jump), 0x00218131 (cond_jump)
  0x002180A0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x002180A5  0fb600                  movzx    eax, byte ptr [eax]            
  0x002180A8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x002180AE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x002180B1  c1e102                  shl      ecx, 2                         
  0x002180B4  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x002180BA  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x002180C0  c1e002                  shl      eax, 2                         
  0x002180C3  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x002180C9  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x002180CF  03d7                    add      edx, edi                       
  0x002180D1  8b3d189f2900            mov      edi, dword ptr [0x299f18]      
  0x002180D7  0fb607                  movzx    eax, byte ptr [edi]            
  0x002180DA  8b0485c05e2900          mov      eax, dword ptr [eax*4 + 0x295ec0] 
  0x002180E1  47                      inc      edi                            
  0x002180E2  893d189f2900            mov      dword ptr [0x299f18], edi      
  0x002180E8  8b0c88                  mov      ecx, dword ptr [eax + ecx*4]   
  0x002180EB  8b3c90                  mov      edi, dword ptr [eax + edx*4]   
  0x002180EE  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x002180F4  c1e108                  shl      ecx, 8                         
  0x002180F7  0bcf                    or       ecx, edi                       
  0x002180F9  8b3cb0                  mov      edi, dword ptr [eax + esi*4]   
  0x002180FC  c1e108                  shl      ecx, 8                         
  0x002180FF  0bcf                    or       ecx, edi                       
  0x00218101  890a                    mov      dword ptr [edx], ecx           
  0x00218103  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218109  83c204                  add      edx, 4                         
  0x0021810C  43                      inc      ebx                            
  0x0021810D  f6c301                  test     bl, 1                          
  0x00218110  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00218116  7518                    jne      0x218130                       
  0x00218118  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021811E  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x00218123  41                      inc      ecx                            
  0x00218124  40                      inc      eax                            
  0x00218125  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021812B  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x00218116 (cond_jump)
  0x00218130  4d                      dec      ebp                            
  0x00218131  0f8569ffffff            jne      0x2180a0                       
  0x00218137  5f                      pop      edi                            
  0x00218138  5e                      pop      esi                            
  0x00218139  5d                      pop      ebp                            
                                        ; XREF: 0x0021808B (cond_jump)
  0x0021813A  5b                      pop      ebx                            
  0x0021813B  c3                      ret                                     
; end of function
  0x0021813C  cc                      int3                                    
  0x0021813D  cc                      int3                                    
  0x0021813E  cc                      int3                                    
  0x0021813F  cc                      int3                                    

; ============================================================
; Function: sub_00218140
; Start: 0x00218140  End: 0x0021822E  Size: 238 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218140:
  0x00218140  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00218144  53                      push     ebx                            
  0x00218145  55                      push     ebp                            
  0x00218146  8b6c240c                mov      ebp, dword ptr [esp + 0xc]     
  0x0021814A  56                      push     esi                            
  0x0021814B  57                      push     edi                            
  0x0021814C  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x00218223 (cond_jump)
  0x00218150  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x00218156  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00218159  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021815F  0fb612                  movzx    edx, byte ptr [edx]            
  0x00218162  c1e102                  shl      ecx, 2                         
  0x00218165  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x0021816B  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x00218171  c1e202                  shl      edx, 2                         
  0x00218174  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021817A  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00218180  03f3                    add      esi, ebx                       
  0x00218182  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x00218188  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021818B  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00218192  43                      inc      ebx                            
  0x00218193  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x00218199  8b1c91                  mov      ebx, dword ptr [ecx + edx*4]   
  0x0021819C  c1e308                  shl      ebx, 8                         
  0x0021819F  0b1cb1                  or       ebx, dword ptr [ecx + esi*4]   
  0x002181A2  c1e308                  shl      ebx, 8                         
  0x002181A5  0b1cb9                  or       ebx, dword ptr [ecx + edi*4]   
  0x002181A8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002181AE  8919                    mov      dword ptr [ecx], ebx           
  0x002181B0  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x002181B6  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x002181B9  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x002181C0  43                      inc      ebx                            
  0x002181C1  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x002181C7  8b1491                  mov      edx, dword ptr [ecx + edx*4]   
  0x002181CA  8b1cb1                  mov      ebx, dword ptr [ecx + esi*4]   
  0x002181CD  c1e208                  shl      edx, 8                         
  0x002181D0  0bd3                    or       edx, ebx                       
  0x002181D2  8b1cb9                  mov      ebx, dword ptr [ecx + edi*4]   
  0x002181D5  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x002181DB  c1e208                  shl      edx, 8                         
  0x002181DE  0bd3                    or       edx, ebx                       
  0x002181E0  8911                    mov      dword ptr [ecx], edx           
  0x002181E2  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x002181E8  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x002181EE  b904000000              mov      ecx, 4                         
  0x002181F3  03f9                    add      edi, ecx                       
  0x002181F5  03f1                    add      esi, ecx                       
  0x002181F7  40                      inc      eax                            
  0x002181F8  a801                    test     al, 1                          
  0x002181FA  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x00218200  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x00218206  751a                    jne      0x218222                       
  0x00218208  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021820E  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00218214  42                      inc      edx                            
  0x00218215  41                      inc      ecx                            
  0x00218216  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021821C  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x00218206 (cond_jump)
  0x00218222  4d                      dec      ebp                            
  0x00218223  0f8527ffffff            jne      0x218150                       
  0x00218229  5f                      pop      edi                            
  0x0021822A  5e                      pop      esi                            
  0x0021822B  5d                      pop      ebp                            
  0x0021822C  5b                      pop      ebx                            
  0x0021822D  c3                      ret                                     
; end of function
  0x0021822E  cc                      int3                                    
  0x0021822F  cc                      int3                                    

; ============================================================
; Function: sub_00218230
; Start: 0x00218230  End: 0x00218280  Size: 80 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214310
; Called by: sub_0020C030
; ============================================================
sub_00218230:
  0x00218230  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00218234  8b4c2434                mov      ecx, dword ptr [esp + 0x34]    
  0x00218238  8b54242c                mov      edx, dword ptr [esp + 0x2c]    
  0x0021823C  68a0bf2900              push     0x29bfa0                       
  0x00218241  50                      push     eax                            
  0x00218242  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00218246  51                      push     ecx                            
  0x00218247  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021824B  52                      push     edx                            
  0x0021824C  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x00218250  50                      push     eax                            
  0x00218251  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00218255  51                      push     ecx                            
  0x00218256  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021825A  52                      push     edx                            
  0x0021825B  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021825F  50                      push     eax                            
  0x00218260  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00218264  51                      push     ecx                            
  0x00218265  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x00218269  52                      push     edx                            
  0x0021826A  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021826E  50                      push     eax                            
  0x0021826F  51                      push     ecx                            
  0x00218270  52                      push     edx                            
  0x00218271  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x00218275  e896c0ffff              call     0x214310                       ; -> sub_00214310
  0x0021827A  83c434                  add      esp, 0x34                      
  0x0021827D  c23400                  ret      0x34                           
; end of function

; ============================================================
; Function: sub_00218280
; Start: 0x00218280  End: 0x002182DB  Size: 91 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214790
; Called by: sub_0020C030
; ============================================================
sub_00218280:
  0x00218280  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x00218284  8b4c243c                mov      ecx, dword ptr [esp + 0x3c]    
  0x00218288  8b542434                mov      edx, dword ptr [esp + 0x34]    
  0x0021828C  68a0bf2900              push     0x29bfa0                       
  0x00218291  50                      push     eax                            
  0x00218292  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x00218296  51                      push     ecx                            
  0x00218297  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021829B  52                      push     edx                            
  0x0021829C  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x002182A0  50                      push     eax                            
  0x002182A1  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x002182A5  51                      push     ecx                            
  0x002182A6  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x002182AA  52                      push     edx                            
  0x002182AB  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x002182AF  50                      push     eax                            
  0x002182B0  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x002182B4  51                      push     ecx                            
  0x002182B5  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x002182B9  52                      push     edx                            
  0x002182BA  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x002182BE  50                      push     eax                            
  0x002182BF  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x002182C3  51                      push     ecx                            
  0x002182C4  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x002182C8  52                      push     edx                            
  0x002182C9  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x002182CD  50                      push     eax                            
  0x002182CE  51                      push     ecx                            
  0x002182CF  52                      push     edx                            
  0x002182D0  e8bbc4ffff              call     0x214790                       ; -> sub_00214790
  0x002182D5  83c440                  add      esp, 0x40                      
  0x002182D8  c23c00                  ret      0x3c                           
; end of function
  0x002182DB  cc                      int3                                    
  0x002182DC  cc                      int3                                    
  0x002182DD  cc                      int3                                    
  0x002182DE  cc                      int3                                    
  0x002182DF  cc                      int3                                    

; ============================================================
; Function: sub_002182E0
; Start: 0x002182E0  End: 0x00218523  Size: 579 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002182E0:
  0x002182E0  53                      push     ebx                            
  0x002182E1  55                      push     ebp                            
  0x002182E2  56                      push     esi                            
  0x002182E3  57                      push     edi                            
  0x002182E4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x002182EA  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x002182F0  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x002182F6  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x002182FC  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x00218300  c1e004                  shl      eax, 4                         
  0x00218303  03c7                    add      eax, edi                       
  0x00218305  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021830A  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x002183EE (cond_jump)
  0x00218311  0f6e22                  movd     mm4, dword ptr [edx]           
  0x00218314  0fefc0                  pxor     mm0, mm0                       
  0x00218317  33c0                    xor      eax, eax                       
  0x00218319  83c204                  add      edx, 4                         
  0x0021831C  8a4500                  mov      al, byte ptr [ebp]             
  0x0021831F  0f60e0                  punpcklbw mm4, mm0                       
  0x00218322  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021832A  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x00218332  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x00218335  83c502                  add      ebp, 2                         
  0x00218338  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021833F  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x00218347  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021834F  8a03                    mov      al, byte ptr [ebx]             
  0x00218351  0f71f402                psllw    mm4, 2                         
  0x00218355  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021835C  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x00218364  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021836C  0ffdd5                  paddw    mm2, mm5                       
  0x0021836F  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x00218372  83c302                  add      ebx, 2                         
  0x00218375  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021837D  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x00218385  0ffdf5                  paddw    mm6, mm5                       
  0x00218388  0f62d6                  punpckldq mm2, mm6                       
  0x0021838B  0ffdcc                  paddw    mm1, mm4                       
  0x0021838E  0ffdd4                  paddw    mm2, mm4                       
  0x00218391  0fedcf                  paddsw   mm1, mm7                       
  0x00218394  0ffddc                  paddw    mm3, mm4                       
  0x00218397  0fd9cf                  psubusw  mm1, mm7                       
  0x0021839A  0fedd7                  paddsw   mm2, mm7                       
  0x0021839D  0f7fcc                  movq     mm4, mm1                       
  0x002183A0  0fd9d7                  psubusw  mm2, mm7                       
  0x002183A3  0f61c8                  punpcklwd mm1, mm0                       
  0x002183A6  0f7fd5                  movq     mm5, mm2                       
  0x002183A9  0f61d0                  punpcklwd mm2, mm0                       
  0x002183AC  0feddf                  paddsw   mm3, mm7                       
  0x002183AF  0f72f208                pslld    mm2, 8                         
  0x002183B3  0fd9df                  psubusw  mm3, mm7                       
  0x002183B6  0f69e0                  punpckhwd mm4, mm0                       
  0x002183B9  0f7fde                  movq     mm6, mm3                       
  0x002183BC  0f61d8                  punpcklwd mm3, mm0                       
  0x002183BF  0f72f310                pslld    mm3, 0x10                      
  0x002183C3  0febca                  por      mm1, mm2                       
  0x002183C6  0febcb                  por      mm1, mm3                       
  0x002183C9  0f69e8                  punpckhwd mm5, mm0                       
  0x002183CC  0f69f0                  punpckhwd mm6, mm0                       
  0x002183CF  0f72f508                pslld    mm5, 8                         
  0x002183D3  0f7f0f                  movq     qword ptr [edi], mm1           
  0x002183D6  0f72f610                pslld    mm6, 0x10                      
  0x002183DA  0febe5                  por      mm4, mm5                       
  0x002183DD  83c710                  add      edi, 0x10                      
  0x002183E0  0febe6                  por      mm4, mm6                       
  0x002183E3  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x002183E8  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x002183EC  3bf8                    cmp      edi, eax                       
  0x002183EE  0f821dffffff            jb       0x218311                       
  0x002183F4  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x002183FA  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x00218400  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x00218406  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021840C  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x00218412  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x00218416  c1e004                  shl      eax, 4                         
  0x00218419  03c7                    add      eax, edi                       
  0x0021841B  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x00218420  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x00218504 (cond_jump)
  0x00218427  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021842A  0fefc0                  pxor     mm0, mm0                       
  0x0021842D  33c0                    xor      eax, eax                       
  0x0021842F  83c204                  add      edx, 4                         
  0x00218432  8a4500                  mov      al, byte ptr [ebp]             
  0x00218435  0f60e0                  punpcklbw mm4, mm0                       
  0x00218438  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x00218440  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x00218448  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021844B  83c502                  add      ebp, 2                         
  0x0021844E  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x00218455  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021845D  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x00218465  8a03                    mov      al, byte ptr [ebx]             
  0x00218467  0f71f402                psllw    mm4, 2                         
  0x0021846B  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x00218472  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021847A  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x00218482  0ffdd5                  paddw    mm2, mm5                       
  0x00218485  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x00218488  83c302                  add      ebx, 2                         
  0x0021848B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x00218493  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021849B  0ffdf5                  paddw    mm6, mm5                       
  0x0021849E  0f62d6                  punpckldq mm2, mm6                       
  0x002184A1  0ffdcc                  paddw    mm1, mm4                       
  0x002184A4  0ffdd4                  paddw    mm2, mm4                       
  0x002184A7  0fedcf                  paddsw   mm1, mm7                       
  0x002184AA  0ffddc                  paddw    mm3, mm4                       
  0x002184AD  0fd9cf                  psubusw  mm1, mm7                       
  0x002184B0  0fedd7                  paddsw   mm2, mm7                       
  0x002184B3  0f7fcc                  movq     mm4, mm1                       
  0x002184B6  0fd9d7                  psubusw  mm2, mm7                       
  0x002184B9  0f61c8                  punpcklwd mm1, mm0                       
  0x002184BC  0f7fd5                  movq     mm5, mm2                       
  0x002184BF  0f61d0                  punpcklwd mm2, mm0                       
  0x002184C2  0feddf                  paddsw   mm3, mm7                       
  0x002184C5  0f72f208                pslld    mm2, 8                         
  0x002184C9  0fd9df                  psubusw  mm3, mm7                       
  0x002184CC  0f69e0                  punpckhwd mm4, mm0                       
  0x002184CF  0f7fde                  movq     mm6, mm3                       
  0x002184D2  0f61d8                  punpcklwd mm3, mm0                       
  0x002184D5  0f72f310                pslld    mm3, 0x10                      
  0x002184D9  0febca                  por      mm1, mm2                       
  0x002184DC  0febcb                  por      mm1, mm3                       
  0x002184DF  0f69e8                  punpckhwd mm5, mm0                       
  0x002184E2  0f69f0                  punpckhwd mm6, mm0                       
  0x002184E5  0f72f508                pslld    mm5, 8                         
  0x002184E9  0f7f0f                  movq     qword ptr [edi], mm1           
  0x002184EC  0f72f610                pslld    mm6, 0x10                      
  0x002184F0  0febe5                  por      mm4, mm5                       
  0x002184F3  83c710                  add      edi, 0x10                      
  0x002184F6  0febe6                  por      mm4, mm6                       
  0x002184F9  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x002184FE  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x00218502  3bf8                    cmp      edi, eax                       
  0x00218504  0f821dffffff            jb       0x218427                       
  0x0021850A  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x00218510  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x00218516  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021851C  5f                      pop      edi                            
  0x0021851D  5e                      pop      esi                            
  0x0021851E  5d                      pop      ebp                            
  0x0021851F  5b                      pop      ebx                            
  0x00218520  c20400                  ret      4                              
; end of function
  0x00218523  8da42400000000          lea      esp, [esp]                     
  0x0021852A  8d9b00000000            lea      ebx, [ebx]                     
  0x00218530  53                      push     ebx                            
  0x00218531  55                      push     ebp                            
  0x00218532  56                      push     esi                            
  0x00218533  57                      push     edi                            
  0x00218534  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021853A  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x00218540  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x00218546  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021854C  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x00218550  c1e004                  shl      eax, 4                         
  0x00218553  03c7                    add      eax, edi                       
  0x00218555  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021855A  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x00218687 (cond_jump)
  0x00218561  0f6e22                  movd     mm4, dword ptr [edx]           
  0x00218564  0fefc0                  pxor     mm0, mm0                       
  0x00218567  33c0                    xor      eax, eax                       
  0x00218569  83c204                  add      edx, 4                         
  0x0021856C  8a4500                  mov      al, byte ptr [ebp]             
  0x0021856F  0f60e0                  punpcklbw mm4, mm0                       
  0x00218572  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021857A  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x00218582  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x00218585  83c502                  add      ebp, 2                         
  0x00218588  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021858F  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x00218597  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021859F  8a03                    mov      al, byte ptr [ebx]             
  0x002185A1  0f71f402                psllw    mm4, 2                         
  0x002185A5  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x002185AC  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x002185B4  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x002185BC  0ffdd5                  paddw    mm2, mm5                       
  0x002185BF  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x002185C2  83c302                  add      ebx, 2                         
  0x002185C5  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x002185CD  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x002185D5  0ffdf5                  paddw    mm6, mm5                       
  0x002185D8  8a4500                  mov      al, byte ptr [ebp]             
  0x002185DB  0f62d6                  punpckldq mm2, mm6                       
  0x002185DE  0f73d110                psrlq    mm1, 0x10                      
  0x002185E2  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x002185EA  0f73d210                psrlq    mm2, 0x10                      
  0x002185EE  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x002185F6  0f73d310                psrlq    mm3, 0x10                      
  0x002185FA  8a03                    mov      al, byte ptr [ebx]             
  0x002185FC  0f73f630                psllq    mm6, 0x30                      
  0x00218600  0febce                  por      mm1, mm6                       
  0x00218603  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021860B  0ffdee                  paddw    mm5, mm6                       
  0x0021860E  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x00218616  0f73f530                psllq    mm5, 0x30                      
  0x0021861A  0f73f630                psllq    mm6, 0x30                      
  0x0021861E  0febd5                  por      mm2, mm5                       
  0x00218621  0febde                  por      mm3, mm6                       
  0x00218624  0ffdcc                  paddw    mm1, mm4                       
  0x00218627  0ffdd4                  paddw    mm2, mm4                       
  0x0021862A  0fedcf                  paddsw   mm1, mm7                       
  0x0021862D  0ffddc                  paddw    mm3, mm4                       
  0x00218630  0fd9cf                  psubusw  mm1, mm7                       
  0x00218633  0fedd7                  paddsw   mm2, mm7                       
  0x00218636  0f7fcc                  movq     mm4, mm1                       
  0x00218639  0fd9d7                  psubusw  mm2, mm7                       
  0x0021863C  0f61c8                  punpcklwd mm1, mm0                       
  0x0021863F  0f7fd5                  movq     mm5, mm2                       
  0x00218642  0f61d0                  punpcklwd mm2, mm0                       
  0x00218645  0feddf                  paddsw   mm3, mm7                       
  0x00218648  0f72f208                pslld    mm2, 8                         
  0x0021864C  0fd9df                  psubusw  mm3, mm7                       
  0x0021864F  0f69e0                  punpckhwd mm4, mm0                       
  0x00218652  0f7fde                  movq     mm6, mm3                       
  0x00218655  0f61d8                  punpcklwd mm3, mm0                       
  0x00218658  0f72f310                pslld    mm3, 0x10                      
  0x0021865C  0febca                  por      mm1, mm2                       
  0x0021865F  0febcb                  por      mm1, mm3                       
  0x00218662  0f69e8                  punpckhwd mm5, mm0                       
  0x00218665  0f69f0                  punpckhwd mm6, mm0                       
  0x00218668  0f72f508                pslld    mm5, 8                         
  0x0021866C  0f7f0f                  movq     qword ptr [edi], mm1           
  0x0021866F  0f72f610                pslld    mm6, 0x10                      
  0x00218673  0febe5                  por      mm4, mm5                       
  0x00218676  83c710                  add      edi, 0x10                      
  0x00218679  0febe6                  por      mm4, mm6                       
  0x0021867C  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x00218681  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x00218685  3bf8                    cmp      edi, eax                       
  0x00218687  0f82d4feffff            jb       0x218561                       
  0x0021868D  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x00218693  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x00218699  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021869F  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x002186A5  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x002186AB  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x002186AF  c1e004                  shl      eax, 4                         
  0x002186B2  03c7                    add      eax, edi                       
  0x002186B4  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x002186B9  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x002187E6 (cond_jump)
  0x002186C0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x002186C3  0fefc0                  pxor     mm0, mm0                       
  0x002186C6  33c0                    xor      eax, eax                       
  0x002186C8  83c204                  add      edx, 4                         
  0x002186CB  8a4500                  mov      al, byte ptr [ebp]             
  0x002186CE  0f60e0                  punpcklbw mm4, mm0                       
  0x002186D1  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x002186D9  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x002186E1  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x002186E4  83c502                  add      ebp, 2                         
  0x002186E7  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x002186EE  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x002186F6  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x002186FE  8a03                    mov      al, byte ptr [ebx]             
  0x00218700  0f71f402                psllw    mm4, 2                         
  0x00218704  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021870B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x00218713  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021871B  0ffdd5                  paddw    mm2, mm5                       
  0x0021871E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x00218721  83c302                  add      ebx, 2                         
  0x00218724  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021872C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x00218734  0ffdf5                  paddw    mm6, mm5                       
  0x00218737  8a4500                  mov      al, byte ptr [ebp]             
  0x0021873A  0f62d6                  punpckldq mm2, mm6                       
  0x0021873D  0f73d110                psrlq    mm1, 0x10                      
  0x00218741  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x00218749  0f73d210                psrlq    mm2, 0x10                      
  0x0021874D  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x00218755  0f73d310                psrlq    mm3, 0x10                      
  0x00218759  8a03                    mov      al, byte ptr [ebx]             
  0x0021875B  0f73f630                psllq    mm6, 0x30                      
  0x0021875F  0febce                  por      mm1, mm6                       
  0x00218762  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021876A  0ffdee                  paddw    mm5, mm6                       
  0x0021876D  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x00218775  0f73f530                psllq    mm5, 0x30                      
  0x00218779  0f73f630                psllq    mm6, 0x30                      
  0x0021877D  0febd5                  por      mm2, mm5                       
  0x00218780  0febde                  por      mm3, mm6                       
  0x00218783  0ffdcc                  paddw    mm1, mm4                       
  0x00218786  0ffdd4                  paddw    mm2, mm4                       
  0x00218789  0fedcf                  paddsw   mm1, mm7                       
  0x0021878C  0ffddc                  paddw    mm3, mm4                       
  0x0021878F  0fd9cf                  psubusw  mm1, mm7                       
  0x00218792  0fedd7                  paddsw   mm2, mm7                       
  0x00218795  0f7fcc                  movq     mm4, mm1                       
  0x00218798  0fd9d7                  psubusw  mm2, mm7                       
  0x0021879B  0f61c8                  punpcklwd mm1, mm0                       
  0x0021879E  0f7fd5                  movq     mm5, mm2                       
  0x002187A1  0f61d0                  punpcklwd mm2, mm0                       
  0x002187A4  0feddf                  paddsw   mm3, mm7                       
  0x002187A7  0f72f208                pslld    mm2, 8                         
  0x002187AB  0fd9df                  psubusw  mm3, mm7                       
  0x002187AE  0f69e0                  punpckhwd mm4, mm0                       
  0x002187B1  0f7fde                  movq     mm6, mm3                       
  0x002187B4  0f61d8                  punpcklwd mm3, mm0                       
  0x002187B7  0f72f310                pslld    mm3, 0x10                      
  0x002187BB  0febca                  por      mm1, mm2                       
  0x002187BE  0febcb                  por      mm1, mm3                       
  0x002187C1  0f69e8                  punpckhwd mm5, mm0                       
  0x002187C4  0f69f0                  punpckhwd mm6, mm0                       
  0x002187C7  0f72f508                pslld    mm5, 8                         
  0x002187CB  0f7f0f                  movq     qword ptr [edi], mm1           
  0x002187CE  0f72f610                pslld    mm6, 0x10                      
  0x002187D2  0febe5                  por      mm4, mm5                       
  0x002187D5  83c710                  add      edi, 0x10                      
  0x002187D8  0febe6                  por      mm4, mm6                       
  0x002187DB  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x002187E0  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x002187E4  3bf8                    cmp      edi, eax                       
  0x002187E6  0f82d4feffff            jb       0x2186c0                       
  0x002187EC  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x002187F2  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x002187F8  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x002187FE  5f                      pop      edi                            
  0x002187FF  5e                      pop      esi                            
  0x00218800  5d                      pop      ebp                            
  0x00218801  5b                      pop      ebx                            
