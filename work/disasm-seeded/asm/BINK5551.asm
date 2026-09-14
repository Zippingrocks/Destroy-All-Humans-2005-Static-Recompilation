; ============================================================
; Section: BINK5551
; VA: 0x0021C3C0 - 0x0021D8D4
; Size: 5396 bytes (5.3 KB)
; Functions: 16
; Instructions: 1531
; ============================================================

  0x0021C3C0  57                      push     edi                            
  0x0021C3C1  8b7c240c                mov      edi, dword ptr [esp + 0xc]     
  0x0021C3C5  85ff                    test     edi, edi                       
  0x0021C3C7  7464                    je       0x21c42d                       
  0x0021C3C9  53                      push     ebx                            
  0x0021C3CA  56                      push     esi                            
  0x0021C3CB  eb03                    jmp      0x21c3d0                       
  0x0021C3CD  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021C3CB (jump), 0x0021C429 (cond_jump)
  0x0021C3D0  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021C3D6  8a16                    mov      dl, byte ptr [esi]             
  0x0021C3D8  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021C3DE  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C3E1  33db                    xor      ebx, ebx                       
  0x0021C3E3  80e280                  and      dl, 0x80                       
  0x0021C3E6  8afa                    mov      bh, dl                         
  0x0021C3E8  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C3F0  46                      inc      esi                            
  0x0021C3F1  41                      inc      ecx                            
  0x0021C3F2  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021C3F8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C3FE  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021C404  8bc3                    mov      eax, ebx                       
  0x0021C406  668901                  mov      word ptr [ecx], ax             
  0x0021C409  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C40F  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021C415  66890411                mov      word ptr [ecx + edx], ax       
  0x0021C419  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C41F  83c102                  add      ecx, 2                         
  0x0021C422  4f                      dec      edi                            
  0x0021C423  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021C429  75a5                    jne      0x21c3d0                       
  0x0021C42B  5e                      pop      esi                            
  0x0021C42C  5b                      pop      ebx                            
                                        ; XREF: 0x0021C3C7 (cond_jump)
  0x0021C42D  5f                      pop      edi                            
  0x0021C42E  c3                      ret                                     
  0x0021C42F  cc                      int3                                    

; ============================================================
; Function: sub_0021C430
; Start: 0x0021C430  End: 0x0021C505  Size: 213 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021C430:
  0x0021C430  53                      push     ebx                            
  0x0021C431  55                      push     ebp                            
  0x0021C432  8b6c240c                mov      ebp, dword ptr [esp + 0xc]     
  0x0021C436  56                      push     esi                            
  0x0021C437  57                      push     edi                            
  0x0021C438  8bfd                    mov      edi, ebp                       
  0x0021C43A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021C4F3 (cond_jump)
  0x0021C440  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021C446  8a16                    mov      dl, byte ptr [esi]             
  0x0021C448  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021C44E  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C451  80e280                  and      dl, 0x80                       
  0x0021C454  33db                    xor      ebx, ebx                       
  0x0021C456  8afa                    mov      bh, dl                         
  0x0021C458  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C460  46                      inc      esi                            
  0x0021C461  41                      inc      ecx                            
  0x0021C462  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021C468  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C46E  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021C474  8bc3                    mov      eax, ebx                       
  0x0021C476  668901                  mov      word ptr [ecx], ax             
  0x0021C479  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C47F  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021C485  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021C489  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x0021C48F  8a06                    mov      al, byte ptr [esi]             
  0x0021C491  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021C497  0fb611                  movzx    edx, byte ptr [ecx]            
  0x0021C49A  2480                    and      al, 0x80                       
  0x0021C49C  33db                    xor      ebx, ebx                       
  0x0021C49E  8af8                    mov      bh, al                         
  0x0021C4A0  660b1c9510932900        or       bx, word ptr [edx*4 + 0x299310] 
  0x0021C4A8  46                      inc      esi                            
  0x0021C4A9  41                      inc      ecx                            
  0x0021C4AA  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021C4B0  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C4B6  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x0021C4BC  8bc3                    mov      eax, ebx                       
  0x0021C4BE  668901                  mov      word ptr [ecx], ax             
  0x0021C4C1  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021C4C7  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021C4CD  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021C4D1  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C4D7  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C4DD  b802000000              mov      eax, 2                         
  0x0021C4E2  03d0                    add      edx, eax                       
  0x0021C4E4  03c8                    add      ecx, eax                       
  0x0021C4E6  4f                      dec      edi                            
  0x0021C4E7  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021C4ED  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021C4F3  0f8547ffffff            jne      0x21c440                       
  0x0021C4F9  8b542418                mov      edx, dword ptr [esp + 0x18]    
  0x0021C4FD  5f                      pop      edi                            
  0x0021C4FE  5e                      pop      esi                            
  0x0021C4FF  8d042a                  lea      eax, [edx + ebp]               
  0x0021C502  5d                      pop      ebp                            
  0x0021C503  5b                      pop      ebx                            
  0x0021C504  c3                      ret                                     
; end of function
  0x0021C505  cc                      int3                                    
  0x0021C506  cc                      int3                                    
  0x0021C507  cc                      int3                                    
  0x0021C508  cc                      int3                                    
  0x0021C509  cc                      int3                                    
  0x0021C50A  cc                      int3                                    
  0x0021C50B  cc                      int3                                    
  0x0021C50C  cc                      int3                                    
  0x0021C50D  cc                      int3                                    
  0x0021C50E  cc                      int3                                    
  0x0021C50F  cc                      int3                                    

; ============================================================
; Function: sub_0021C510
; Start: 0x0021C510  End: 0x0021C579  Size: 105 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021C510:
  0x0021C510  57                      push     edi                            
  0x0021C511  8b7c240c                mov      edi, dword ptr [esp + 0xc]     
  0x0021C515  85ff                    test     edi, edi                       
  0x0021C517  745e                    je       0x21c577                       
  0x0021C519  53                      push     ebx                            
  0x0021C51A  56                      push     esi                            
  0x0021C51B  eb03                    jmp      0x21c520                       
  0x0021C51D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021C51B (jump), 0x0021C573 (cond_jump)
  0x0021C520  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021C526  8a16                    mov      dl, byte ptr [esi]             
  0x0021C528  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021C52E  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C531  33db                    xor      ebx, ebx                       
  0x0021C533  80e280                  and      dl, 0x80                       
  0x0021C536  8afa                    mov      bh, dl                         
  0x0021C538  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C540  46                      inc      esi                            
  0x0021C541  41                      inc      ecx                            
  0x0021C542  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021C548  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C54E  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021C554  8bc3                    mov      eax, ebx                       
  0x0021C556  668901                  mov      word ptr [ecx], ax             
  0x0021C559  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C55F  66894202                mov      word ptr [edx + 2], ax         
  0x0021C563  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C569  83c104                  add      ecx, 4                         
  0x0021C56C  4f                      dec      edi                            
  0x0021C56D  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021C573  75ab                    jne      0x21c520                       
  0x0021C575  5e                      pop      esi                            
  0x0021C576  5b                      pop      ebx                            
                                        ; XREF: 0x0021C517 (cond_jump)
  0x0021C577  5f                      pop      edi                            
  0x0021C578  c3                      ret                                     
; end of function
  0x0021C579  cc                      int3                                    
  0x0021C57A  cc                      int3                                    
  0x0021C57B  cc                      int3                                    
  0x0021C57C  cc                      int3                                    
  0x0021C57D  cc                      int3                                    
  0x0021C57E  cc                      int3                                    
  0x0021C57F  cc                      int3                                    

; ============================================================
; Function: sub_0021C580
; Start: 0x0021C580  End: 0x0021C649  Size: 201 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021C580:
  0x0021C580  53                      push     ebx                            
  0x0021C581  55                      push     ebp                            
  0x0021C582  8b6c240c                mov      ebp, dword ptr [esp + 0xc]     
  0x0021C586  56                      push     esi                            
  0x0021C587  57                      push     edi                            
  0x0021C588  8bfd                    mov      edi, ebp                       
  0x0021C58A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021C638 (cond_jump)
  0x0021C590  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021C596  8a16                    mov      dl, byte ptr [esi]             
  0x0021C598  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021C59E  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C5A1  80e280                  and      dl, 0x80                       
  0x0021C5A4  33db                    xor      ebx, ebx                       
  0x0021C5A6  8afa                    mov      bh, dl                         
  0x0021C5A8  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C5B0  46                      inc      esi                            
  0x0021C5B1  41                      inc      ecx                            
  0x0021C5B2  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021C5B8  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C5BE  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021C5C4  8bc3                    mov      eax, ebx                       
  0x0021C5C6  668901                  mov      word ptr [ecx], ax             
  0x0021C5C9  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C5CF  66894202                mov      word ptr [edx + 2], ax         
  0x0021C5D3  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x0021C5D9  8a16                    mov      dl, byte ptr [esi]             
  0x0021C5DB  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021C5E1  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C5E4  80e280                  and      dl, 0x80                       
  0x0021C5E7  33db                    xor      ebx, ebx                       
  0x0021C5E9  8afa                    mov      bh, dl                         
  0x0021C5EB  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C5F3  46                      inc      esi                            
  0x0021C5F4  41                      inc      ecx                            
  0x0021C5F5  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021C5FB  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C601  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x0021C607  8bc3                    mov      eax, ebx                       
  0x0021C609  668901                  mov      word ptr [ecx], ax             
  0x0021C60C  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021C612  66894202                mov      word ptr [edx + 2], ax         
  0x0021C616  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C61C  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C622  b804000000              mov      eax, 4                         
  0x0021C627  03d0                    add      edx, eax                       
  0x0021C629  03c8                    add      ecx, eax                       
  0x0021C62B  4f                      dec      edi                            
  0x0021C62C  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021C632  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021C638  0f8552ffffff            jne      0x21c590                       
  0x0021C63E  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021C642  5f                      pop      edi                            
  0x0021C643  5e                      pop      esi                            
  0x0021C644  03c5                    add      eax, ebp                       
  0x0021C646  5d                      pop      ebp                            
  0x0021C647  5b                      pop      ebx                            
  0x0021C648  c3                      ret                                     
; end of function
  0x0021C649  cc                      int3                                    
  0x0021C64A  cc                      int3                                    
  0x0021C64B  cc                      int3                                    
  0x0021C64C  cc                      int3                                    
  0x0021C64D  cc                      int3                                    
  0x0021C64E  cc                      int3                                    
  0x0021C64F  cc                      int3                                    

; ============================================================
; Function: sub_0021C650
; Start: 0x0021C650  End: 0x0021C6DA  Size: 138 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021C650:
  0x0021C650  57                      push     edi                            
  0x0021C651  8b7c240c                mov      edi, dword ptr [esp + 0xc]     
  0x0021C655  85ff                    test     edi, edi                       
  0x0021C657  747f                    je       0x21c6d8                       
  0x0021C659  53                      push     ebx                            
  0x0021C65A  56                      push     esi                            
  0x0021C65B  eb03                    jmp      0x21c660                       
  0x0021C65D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021C65B (jump), 0x0021C6D4 (cond_jump)
  0x0021C660  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021C666  8a16                    mov      dl, byte ptr [esi]             
  0x0021C668  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021C66E  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C671  80e280                  and      dl, 0x80                       
  0x0021C674  33db                    xor      ebx, ebx                       
  0x0021C676  8afa                    mov      bh, dl                         
  0x0021C678  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C680  46                      inc      esi                            
  0x0021C681  41                      inc      ecx                            
  0x0021C682  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021C688  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C68E  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021C694  8bc3                    mov      eax, ebx                       
  0x0021C696  668901                  mov      word ptr [ecx], ax             
  0x0021C699  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C69F  66894202                mov      word ptr [edx + 2], ax         
  0x0021C6A3  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C6A9  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021C6AF  66890411                mov      word ptr [ecx + edx], ax       
  0x0021C6B3  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C6B9  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021C6BF  6689440a02              mov      word ptr [edx + ecx + 2], ax   
  0x0021C6C4  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C6CA  83c104                  add      ecx, 4                         
  0x0021C6CD  4f                      dec      edi                            
  0x0021C6CE  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021C6D4  758a                    jne      0x21c660                       
  0x0021C6D6  5e                      pop      esi                            
  0x0021C6D7  5b                      pop      ebx                            
                                        ; XREF: 0x0021C657 (cond_jump)
  0x0021C6D8  5f                      pop      edi                            
  0x0021C6D9  c3                      ret                                     
; end of function
  0x0021C6DA  cc                      int3                                    
  0x0021C6DB  cc                      int3                                    
  0x0021C6DC  cc                      int3                                    
  0x0021C6DD  cc                      int3                                    
  0x0021C6DE  cc                      int3                                    
  0x0021C6DF  cc                      int3                                    

; ============================================================
; Function: sub_0021C6E0
; Start: 0x0021C6E0  End: 0x0021C7EB  Size: 267 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021C6E0:
  0x0021C6E0  53                      push     ebx                            
  0x0021C6E1  55                      push     ebp                            
  0x0021C6E2  8b6c240c                mov      ebp, dword ptr [esp + 0xc]     
  0x0021C6E6  56                      push     esi                            
  0x0021C6E7  57                      push     edi                            
  0x0021C6E8  8bfd                    mov      edi, ebp                       
  0x0021C6EA  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021C7DA (cond_jump)
  0x0021C6F0  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021C6F6  8a16                    mov      dl, byte ptr [esi]             
  0x0021C6F8  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021C6FE  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C701  80e280                  and      dl, 0x80                       
  0x0021C704  33db                    xor      ebx, ebx                       
  0x0021C706  8afa                    mov      bh, dl                         
  0x0021C708  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C710  46                      inc      esi                            
  0x0021C711  41                      inc      ecx                            
  0x0021C712  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021C718  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C71E  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021C724  8bc3                    mov      eax, ebx                       
  0x0021C726  668901                  mov      word ptr [ecx], ax             
  0x0021C729  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C72F  66894202                mov      word ptr [edx + 2], ax         
  0x0021C733  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C739  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021C73F  66890411                mov      word ptr [ecx + edx], ax       
  0x0021C743  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C749  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021C74F  6689441102              mov      word ptr [ecx + edx + 2], ax   
  0x0021C754  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x0021C75A  8a16                    mov      dl, byte ptr [esi]             
  0x0021C75C  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021C762  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021C765  80e280                  and      dl, 0x80                       
  0x0021C768  33db                    xor      ebx, ebx                       
  0x0021C76A  8afa                    mov      bh, dl                         
  0x0021C76C  660b1c8510932900        or       bx, word ptr [eax*4 + 0x299310] 
  0x0021C774  46                      inc      esi                            
  0x0021C775  41                      inc      ecx                            
  0x0021C776  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021C77C  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C782  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x0021C788  8bc3                    mov      eax, ebx                       
  0x0021C78A  668901                  mov      word ptr [ecx], ax             
  0x0021C78D  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021C793  66894202                mov      word ptr [edx + 2], ax         
  0x0021C797  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C79D  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021C7A3  66890411                mov      word ptr [ecx + edx], ax       
  0x0021C7A7  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C7AD  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021C7B3  6689441102              mov      word ptr [ecx + edx + 2], ax   
  0x0021C7B8  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C7BE  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021C7C4  b804000000              mov      eax, 4                         
  0x0021C7C9  03d0                    add      edx, eax                       
  0x0021C7CB  03c8                    add      ecx, eax                       
  0x0021C7CD  4f                      dec      edi                            
  0x0021C7CE  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021C7D4  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021C7DA  0f8510ffffff            jne      0x21c6f0                       
  0x0021C7E0  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021C7E4  5f                      pop      edi                            
  0x0021C7E5  5e                      pop      esi                            
  0x0021C7E6  03c5                    add      eax, ebp                       
  0x0021C7E8  5d                      pop      ebp                            
  0x0021C7E9  5b                      pop      ebx                            
  0x0021C7EA  c3                      ret                                     
; end of function
  0x0021C7EB  cc                      int3                                    
  0x0021C7EC  cc                      int3                                    
  0x0021C7ED  cc                      int3                                    
  0x0021C7EE  cc                      int3                                    
  0x0021C7EF  cc                      int3                                    

; ============================================================
; Function: sub_0021C7F0
; Start: 0x0021C7F0  End: 0x0021C8E0  Size: 240 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021C7F0:
  0x0021C7F0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021C7F4  85c0                    test     eax, eax                       
  0x0021C7F6  53                      push     ebx                            
  0x0021C7F7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021C7FB  0f84dd000000            je       0x21c8de                       
  0x0021C801  55                      push     ebp                            
  0x0021C802  56                      push     esi                            
  0x0021C803  57                      push     edi                            
  0x0021C804  8be8                    mov      ebp, eax                       
  0x0021C806  eb08                    jmp      0x21c810                       
  0x0021C808  8da42400000000          lea      esp, [esp]                     
  0x0021C80F  90                      nop                                     
                                        ; XREF: 0x0021C806 (jump), 0x0021C8D5 (cond_jump)
  0x0021C810  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021C815  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021C818  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021C81E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021C821  c1e002                  shl      eax, 2                         
  0x0021C824  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021C82A  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021C830  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021C835  c1e102                  shl      ecx, 2                         
  0x0021C838  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021C83E  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021C844  03d6                    add      edx, esi                       
  0x0021C846  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021C849  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021C850  40                      inc      eax                            
  0x0021C851  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021C856  8d040e                  lea      eax, [esi + ecx]               
  0x0021C859  0fb70485a0522900        movzx    eax, word ptr [eax*4 + 0x2952a0] 
  0x0021C861  8d0c16                  lea      ecx, [esi + edx]               
  0x0021C864  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021C86C  03f7                    add      esi, edi                       
  0x0021C86E  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021C876  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021C87C  8a16                    mov      dl, byte ptr [esi]             
  0x0021C87E  80e280                  and      dl, 0x80                       
  0x0021C881  33c9                    xor      ecx, ecx                       
  0x0021C883  8aea                    mov      ch, dl                         
  0x0021C885  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C88B  0bc1                    or       eax, ecx                       
  0x0021C88D  46                      inc      esi                            
  0x0021C88E  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021C894  668902                  mov      word ptr [edx], ax             
  0x0021C897  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021C89D  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021C8A3  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021C8A7  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021C8AD  83c202                  add      edx, 2                         
  0x0021C8B0  43                      inc      ebx                            
  0x0021C8B1  f6c301                  test     bl, 1                          
  0x0021C8B4  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021C8BA  7518                    jne      0x21c8d4                       
  0x0021C8BC  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021C8C2  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021C8C7  41                      inc      ecx                            
  0x0021C8C8  40                      inc      eax                            
  0x0021C8C9  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021C8CF  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021C8BA (cond_jump)
  0x0021C8D4  4d                      dec      ebp                            
  0x0021C8D5  0f8535ffffff            jne      0x21c810                       
  0x0021C8DB  5f                      pop      edi                            
  0x0021C8DC  5e                      pop      esi                            
  0x0021C8DD  5d                      pop      ebp                            
                                        ; XREF: 0x0021C7FB (cond_jump)
  0x0021C8DE  5b                      pop      ebx                            
  0x0021C8DF  c3                      ret                                     
; end of function
  0x0021C8E0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021C8E4  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021C8E8  53                      push     ebx                            
  0x0021C8E9  55                      push     ebp                            
  0x0021C8EA  56                      push     esi                            
  0x0021C8EB  89442414                mov      dword ptr [esp + 0x14], eax    
  0x0021C8EF  894c2410                mov      dword ptr [esp + 0x10], ecx    
  0x0021C8F3  57                      push     edi                            
  0x0021C8F4  eb0a                    jmp      0x21c900                       
  0x0021C8F6  8da42400000000          lea      esp, [esp]                     
  0x0021C8FD  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021C8F4 (jump), 0x0021CA48 (cond_jump)
  0x0021C900  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021C906  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021C909  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021C90E  0fb610                  movzx    edx, byte ptr [eax]            
  0x0021C911  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021C916  c1e102                  shl      ecx, 2                         
  0x0021C919  8ba9389f2900            mov      ebp, dword ptr [ecx + 0x299f38] 
  0x0021C91F  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021C925  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021C928  c1e202                  shl      edx, 2                         
  0x0021C92B  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021C931  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021C937  03f7                    add      esi, edi                       
  0x0021C939  8b3c8d70322900          mov      edi, dword ptr [ecx*4 + 0x293270] 
  0x0021C940  40                      inc      eax                            
  0x0021C941  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021C946  8d0417                  lea      eax, [edi + edx]               
  0x0021C949  33c9                    xor      ecx, ecx                       
  0x0021C94B  668b0c85a0522900        mov      cx, word ptr [eax*4 + 0x2952a0] 
  0x0021C953  8d1c37                  lea      ebx, [edi + esi]               
  0x0021C956  660b0c9d90462900        or       cx, word ptr [ebx*4 + 0x294690] 
  0x0021C95E  03fd                    add      edi, ebp                       
  0x0021C960  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021C968  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x0021C96E  8a07                    mov      al, byte ptr [edi]             
  0x0021C970  2480                    and      al, 0x80                       
  0x0021C972  33db                    xor      ebx, ebx                       
  0x0021C974  8af8                    mov      bh, al                         
  0x0021C976  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021C97B  0bcb                    or       ecx, ebx                       
  0x0021C97D  47                      inc      edi                            
  0x0021C97E  893d289f2900            mov      dword ptr [0x299f28], edi      
  0x0021C984  668908                  mov      word ptr [eax], cx             
  0x0021C987  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021C98D  a1309f2900              mov      eax, dword ptr [0x299f30]      
  0x0021C992  66890c38                mov      word ptr [eax + edi], cx       
  0x0021C996  a11c9f2900              mov      eax, dword ptr [0x299f1c]      
  0x0021C99B  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021C99E  8b3c8d70322900          mov      edi, dword ptr [ecx*4 + 0x293270] 
  0x0021C9A5  40                      inc      eax                            
  0x0021C9A6  03d7                    add      edx, edi                       
  0x0021C9A8  a31c9f2900              mov      dword ptr [0x299f1c], eax      
  0x0021C9AD  8d0437                  lea      eax, [edi + esi]               
  0x0021C9B0  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x0021C9B6  33c9                    xor      ecx, ecx                       
  0x0021C9B8  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021C9C0  660b0c8590462900        or       cx, word ptr [eax*4 + 0x294690] 
  0x0021C9C8  8a16                    mov      dl, byte ptr [esi]             
  0x0021C9CA  33c0                    xor      eax, eax                       
  0x0021C9CC  03fd                    add      edi, ebp                       
  0x0021C9CE  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021C9D6  80e280                  and      dl, 0x80                       
  0x0021C9D9  8ae2                    mov      ah, dl                         
  0x0021C9DB  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021C9E1  0bc8                    or       ecx, eax                       
  0x0021C9E3  46                      inc      esi                            
  0x0021C9E4  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x0021C9EA  66890a                  mov      word ptr [edx], cx             
  0x0021C9ED  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021C9F2  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021C9F8  66890c10                mov      word ptr [eax + edx], cx       
  0x0021C9FC  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021CA02  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021CA08  b802000000              mov      eax, 2                         
  0x0021CA0D  03f8                    add      edi, eax                       
  0x0021CA0F  03f0                    add      esi, eax                       
  0x0021CA11  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021CA15  40                      inc      eax                            
  0x0021CA16  a801                    test     al, 1                          
  0x0021CA18  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021CA1E  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021CA24  89442418                mov      dword ptr [esp + 0x18], eax    
  0x0021CA28  751a                    jne      0x21ca44                       
  0x0021CA2A  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021CA30  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021CA36  42                      inc      edx                            
  0x0021CA37  41                      inc      ecx                            
  0x0021CA38  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021CA3E  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021CA28 (cond_jump)
  0x0021CA44  ff4c2414                dec      dword ptr [esp + 0x14]         
  0x0021CA48  0f85b2feffff            jne      0x21c900                       
  0x0021CA4E  5f                      pop      edi                            
  0x0021CA4F  5e                      pop      esi                            
  0x0021CA50  5d                      pop      ebp                            
  0x0021CA51  5b                      pop      ebx                            
  0x0021CA52  c3                      ret                                     
  0x0021CA53  cc                      int3                                    
  0x0021CA54  cc                      int3                                    
  0x0021CA55  cc                      int3                                    
  0x0021CA56  cc                      int3                                    
  0x0021CA57  cc                      int3                                    
  0x0021CA58  cc                      int3                                    
  0x0021CA59  cc                      int3                                    
  0x0021CA5A  cc                      int3                                    
  0x0021CA5B  cc                      int3                                    
  0x0021CA5C  cc                      int3                                    
  0x0021CA5D  cc                      int3                                    
  0x0021CA5E  cc                      int3                                    
  0x0021CA5F  cc                      int3                                    

; ============================================================
; Function: sub_0021CA60
; Start: 0x0021CA60  End: 0x0021CB4A  Size: 234 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021CA60:
  0x0021CA60  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021CA64  85c0                    test     eax, eax                       
  0x0021CA66  53                      push     ebx                            
  0x0021CA67  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021CA6B  0f84d7000000            je       0x21cb48                       
  0x0021CA71  55                      push     ebp                            
  0x0021CA72  56                      push     esi                            
  0x0021CA73  57                      push     edi                            
  0x0021CA74  8be8                    mov      ebp, eax                       
  0x0021CA76  eb08                    jmp      0x21ca80                       
  0x0021CA78  8da42400000000          lea      esp, [esp]                     
  0x0021CA7F  90                      nop                                     
                                        ; XREF: 0x0021CA76 (jump), 0x0021CB3F (cond_jump)
  0x0021CA80  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021CA85  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021CA88  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021CA8E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021CA91  c1e002                  shl      eax, 2                         
  0x0021CA94  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021CA9A  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021CAA0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021CAA5  c1e102                  shl      ecx, 2                         
  0x0021CAA8  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021CAAE  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021CAB4  03d6                    add      edx, esi                       
  0x0021CAB6  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021CAB9  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021CAC0  40                      inc      eax                            
  0x0021CAC1  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021CAC6  8d040e                  lea      eax, [esi + ecx]               
  0x0021CAC9  0fb70485a0522900        movzx    eax, word ptr [eax*4 + 0x2952a0] 
  0x0021CAD1  8d0c16                  lea      ecx, [esi + edx]               
  0x0021CAD4  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021CADC  03f7                    add      esi, edi                       
  0x0021CADE  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021CAE6  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021CAEC  8a16                    mov      dl, byte ptr [esi]             
  0x0021CAEE  80e280                  and      dl, 0x80                       
  0x0021CAF1  33c9                    xor      ecx, ecx                       
  0x0021CAF3  8aea                    mov      ch, dl                         
  0x0021CAF5  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021CAFB  0bc1                    or       eax, ecx                       
  0x0021CAFD  46                      inc      esi                            
  0x0021CAFE  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021CB04  668902                  mov      word ptr [edx], ax             
  0x0021CB07  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021CB0D  66894102                mov      word ptr [ecx + 2], ax         
  0x0021CB11  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021CB17  83c204                  add      edx, 4                         
  0x0021CB1A  43                      inc      ebx                            
  0x0021CB1B  f6c301                  test     bl, 1                          
  0x0021CB1E  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021CB24  7518                    jne      0x21cb3e                       
  0x0021CB26  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021CB2C  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021CB31  41                      inc      ecx                            
  0x0021CB32  40                      inc      eax                            
  0x0021CB33  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021CB39  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021CB24 (cond_jump)
  0x0021CB3E  4d                      dec      ebp                            
  0x0021CB3F  0f853bffffff            jne      0x21ca80                       
  0x0021CB45  5f                      pop      edi                            
  0x0021CB46  5e                      pop      esi                            
  0x0021CB47  5d                      pop      ebp                            
                                        ; XREF: 0x0021CA6B (cond_jump)
  0x0021CB48  5b                      pop      ebx                            
  0x0021CB49  c3                      ret                                     
; end of function
  0x0021CB4A  cc                      int3                                    
  0x0021CB4B  cc                      int3                                    
  0x0021CB4C  cc                      int3                                    
  0x0021CB4D  cc                      int3                                    
  0x0021CB4E  cc                      int3                                    
  0x0021CB4F  cc                      int3                                    

; ============================================================
; Function: sub_0021CB50
; Start: 0x0021CB50  End: 0x0021CCB7  Size: 359 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021CB50:
  0x0021CB50  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021CB54  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021CB58  53                      push     ebx                            
  0x0021CB59  55                      push     ebp                            
  0x0021CB5A  56                      push     esi                            
  0x0021CB5B  89442414                mov      dword ptr [esp + 0x14], eax    
  0x0021CB5F  894c2410                mov      dword ptr [esp + 0x10], ecx    
  0x0021CB63  57                      push     edi                            
  0x0021CB64  eb0a                    jmp      0x21cb70                       
  0x0021CB66  8da42400000000          lea      esp, [esp]                     
  0x0021CB6D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021CB64 (jump), 0x0021CCAC (cond_jump)
  0x0021CB70  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021CB76  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021CB79  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021CB7E  0fb610                  movzx    edx, byte ptr [eax]            
  0x0021CB81  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021CB86  c1e102                  shl      ecx, 2                         
  0x0021CB89  8ba9389f2900            mov      ebp, dword ptr [ecx + 0x299f38] 
  0x0021CB8F  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021CB95  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021CB98  c1e202                  shl      edx, 2                         
  0x0021CB9B  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021CBA1  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021CBA7  03f7                    add      esi, edi                       
  0x0021CBA9  8b3c8d70322900          mov      edi, dword ptr [ecx*4 + 0x293270] 
  0x0021CBB0  40                      inc      eax                            
  0x0021CBB1  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021CBB6  8d0417                  lea      eax, [edi + edx]               
  0x0021CBB9  33c9                    xor      ecx, ecx                       
  0x0021CBBB  668b0c85a0522900        mov      cx, word ptr [eax*4 + 0x2952a0] 
  0x0021CBC3  8d1c37                  lea      ebx, [edi + esi]               
  0x0021CBC6  660b0c9d90462900        or       cx, word ptr [ebx*4 + 0x294690] 
  0x0021CBCE  03fd                    add      edi, ebp                       
  0x0021CBD0  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021CBD8  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x0021CBDE  8a07                    mov      al, byte ptr [edi]             
  0x0021CBE0  2480                    and      al, 0x80                       
  0x0021CBE2  33db                    xor      ebx, ebx                       
  0x0021CBE4  8af8                    mov      bh, al                         
  0x0021CBE6  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021CBEB  0bcb                    or       ecx, ebx                       
  0x0021CBED  47                      inc      edi                            
  0x0021CBEE  893d289f2900            mov      dword ptr [0x299f28], edi      
  0x0021CBF4  668908                  mov      word ptr [eax], cx             
  0x0021CBF7  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021CBFC  66894802                mov      word ptr [eax + 2], cx         
  0x0021CC00  a11c9f2900              mov      eax, dword ptr [0x299f1c]      
  0x0021CC05  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021CC08  8b3c8d70322900          mov      edi, dword ptr [ecx*4 + 0x293270] 
  0x0021CC0F  40                      inc      eax                            
  0x0021CC10  a31c9f2900              mov      dword ptr [0x299f1c], eax      
  0x0021CC15  03d7                    add      edx, edi                       
  0x0021CC17  8d0437                  lea      eax, [edi + esi]               
  0x0021CC1A  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x0021CC20  33c9                    xor      ecx, ecx                       
  0x0021CC22  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021CC2A  660b0c8590462900        or       cx, word ptr [eax*4 + 0x294690] 
  0x0021CC32  8a16                    mov      dl, byte ptr [esi]             
  0x0021CC34  33c0                    xor      eax, eax                       
  0x0021CC36  03fd                    add      edi, ebp                       
  0x0021CC38  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021CC40  80e280                  and      dl, 0x80                       
  0x0021CC43  8ae2                    mov      ah, dl                         
  0x0021CC45  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021CC4B  0bc8                    or       ecx, eax                       
  0x0021CC4D  46                      inc      esi                            
  0x0021CC4E  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x0021CC54  66890a                  mov      word ptr [edx], cx             
  0x0021CC57  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021CC5C  66894802                mov      word ptr [eax + 2], cx         
  0x0021CC60  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021CC66  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021CC6C  b804000000              mov      eax, 4                         
  0x0021CC71  03f8                    add      edi, eax                       
  0x0021CC73  03f0                    add      esi, eax                       
  0x0021CC75  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021CC79  40                      inc      eax                            
  0x0021CC7A  a801                    test     al, 1                          
  0x0021CC7C  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021CC82  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021CC88  89442418                mov      dword ptr [esp + 0x18], eax    
  0x0021CC8C  751a                    jne      0x21cca8                       
  0x0021CC8E  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021CC94  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021CC9A  42                      inc      edx                            
  0x0021CC9B  41                      inc      ecx                            
  0x0021CC9C  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021CCA2  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021CC8C (cond_jump)
  0x0021CCA8  ff4c2414                dec      dword ptr [esp + 0x14]         
  0x0021CCAC  0f85befeffff            jne      0x21cb70                       
  0x0021CCB2  5f                      pop      edi                            
  0x0021CCB3  5e                      pop      esi                            
  0x0021CCB4  5d                      pop      ebp                            
  0x0021CCB5  5b                      pop      ebx                            
  0x0021CCB6  c3                      ret                                     
; end of function
  0x0021CCB7  cc                      int3                                    
  0x0021CCB8  cc                      int3                                    
  0x0021CCB9  cc                      int3                                    
  0x0021CCBA  cc                      int3                                    
  0x0021CCBB  cc                      int3                                    
  0x0021CCBC  cc                      int3                                    
  0x0021CCBD  cc                      int3                                    
  0x0021CCBE  cc                      int3                                    
  0x0021CCBF  cc                      int3                                    

; ============================================================
; Function: sub_0021CCC0
; Start: 0x0021CCC0  End: 0x0021CDCB  Size: 267 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021CCC0:
  0x0021CCC0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021CCC4  85c0                    test     eax, eax                       
  0x0021CCC6  53                      push     ebx                            
  0x0021CCC7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021CCCB  0f84f8000000            je       0x21cdc9                       
  0x0021CCD1  55                      push     ebp                            
  0x0021CCD2  56                      push     esi                            
  0x0021CCD3  57                      push     edi                            
  0x0021CCD4  8be8                    mov      ebp, eax                       
  0x0021CCD6  eb08                    jmp      0x21cce0                       
  0x0021CCD8  8da42400000000          lea      esp, [esp]                     
  0x0021CCDF  90                      nop                                     
                                        ; XREF: 0x0021CCD6 (jump), 0x0021CDC0 (cond_jump)
  0x0021CCE0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021CCE5  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021CCE8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021CCEE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021CCF1  c1e002                  shl      eax, 2                         
  0x0021CCF4  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021CCFA  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021CD00  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021CD05  c1e102                  shl      ecx, 2                         
  0x0021CD08  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021CD0E  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021CD14  03d6                    add      edx, esi                       
  0x0021CD16  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021CD19  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021CD20  40                      inc      eax                            
  0x0021CD21  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021CD26  8d040e                  lea      eax, [esi + ecx]               
  0x0021CD29  0fb70485a0522900        movzx    eax, word ptr [eax*4 + 0x2952a0] 
  0x0021CD31  8d0c16                  lea      ecx, [esi + edx]               
  0x0021CD34  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021CD3C  03f7                    add      esi, edi                       
  0x0021CD3E  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021CD46  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021CD4C  8a16                    mov      dl, byte ptr [esi]             
  0x0021CD4E  80e280                  and      dl, 0x80                       
  0x0021CD51  33c9                    xor      ecx, ecx                       
  0x0021CD53  8aea                    mov      ch, dl                         
  0x0021CD55  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021CD5B  0bc1                    or       eax, ecx                       
  0x0021CD5D  46                      inc      esi                            
  0x0021CD5E  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021CD64  668902                  mov      word ptr [edx], ax             
  0x0021CD67  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021CD6D  66894102                mov      word ptr [ecx + 2], ax         
  0x0021CD71  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021CD77  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021CD7D  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021CD81  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021CD87  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021CD8D  6689441102              mov      word ptr [ecx + edx + 2], ax   
  0x0021CD92  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021CD98  83c204                  add      edx, 4                         
  0x0021CD9B  43                      inc      ebx                            
  0x0021CD9C  f6c301                  test     bl, 1                          
  0x0021CD9F  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021CDA5  7518                    jne      0x21cdbf                       
  0x0021CDA7  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021CDAD  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021CDB2  41                      inc      ecx                            
  0x0021CDB3  40                      inc      eax                            
  0x0021CDB4  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021CDBA  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021CDA5 (cond_jump)
  0x0021CDBF  4d                      dec      ebp                            
  0x0021CDC0  0f851affffff            jne      0x21cce0                       
  0x0021CDC6  5f                      pop      edi                            
  0x0021CDC7  5e                      pop      esi                            
  0x0021CDC8  5d                      pop      ebp                            
                                        ; XREF: 0x0021CCCB (cond_jump)
  0x0021CDC9  5b                      pop      ebx                            
  0x0021CDCA  c3                      ret                                     
; end of function
  0x0021CDCB  cc                      int3                                    
  0x0021CDCC  cc                      int3                                    
  0x0021CDCD  cc                      int3                                    
  0x0021CDCE  cc                      int3                                    
  0x0021CDCF  cc                      int3                                    

; ============================================================
; Function: sub_0021CDD0
; Start: 0x0021CDD0  End: 0x0021CF75  Size: 421 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021CDD0:
  0x0021CDD0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021CDD4  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021CDD8  53                      push     ebx                            
  0x0021CDD9  55                      push     ebp                            
  0x0021CDDA  56                      push     esi                            
  0x0021CDDB  89442414                mov      dword ptr [esp + 0x14], eax    
  0x0021CDDF  894c2410                mov      dword ptr [esp + 0x10], ecx    
  0x0021CDE3  57                      push     edi                            
  0x0021CDE4  eb0a                    jmp      0x21cdf0                       
  0x0021CDE6  8da42400000000          lea      esp, [esp]                     
  0x0021CDED  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021CDE4 (jump), 0x0021CF6A (cond_jump)
  0x0021CDF0  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021CDF6  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021CDF9  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021CDFE  0fb610                  movzx    edx, byte ptr [eax]            
  0x0021CE01  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021CE06  c1e102                  shl      ecx, 2                         
  0x0021CE09  8ba9389f2900            mov      ebp, dword ptr [ecx + 0x299f38] 
  0x0021CE0F  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021CE15  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021CE18  c1e202                  shl      edx, 2                         
  0x0021CE1B  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021CE21  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021CE27  03f7                    add      esi, edi                       
  0x0021CE29  8b3c8d70322900          mov      edi, dword ptr [ecx*4 + 0x293270] 
  0x0021CE30  40                      inc      eax                            
  0x0021CE31  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021CE36  8d0417                  lea      eax, [edi + edx]               
  0x0021CE39  8d1c37                  lea      ebx, [edi + esi]               
  0x0021CE3C  33c9                    xor      ecx, ecx                       
  0x0021CE3E  668b0c85a0522900        mov      cx, word ptr [eax*4 + 0x2952a0] 
  0x0021CE46  660b0c9d90462900        or       cx, word ptr [ebx*4 + 0x294690] 
  0x0021CE4E  03fd                    add      edi, ebp                       
  0x0021CE50  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021CE58  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x0021CE5E  8a07                    mov      al, byte ptr [edi]             
  0x0021CE60  2480                    and      al, 0x80                       
  0x0021CE62  33db                    xor      ebx, ebx                       
  0x0021CE64  8af8                    mov      bh, al                         
  0x0021CE66  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021CE6B  0bcb                    or       ecx, ebx                       
  0x0021CE6D  47                      inc      edi                            
  0x0021CE6E  893d289f2900            mov      dword ptr [0x299f28], edi      
  0x0021CE74  668908                  mov      word ptr [eax], cx             
  0x0021CE77  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021CE7C  66894802                mov      word ptr [eax + 2], cx         
  0x0021CE80  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021CE86  a1309f2900              mov      eax, dword ptr [0x299f30]      
  0x0021CE8B  66890c38                mov      word ptr [eax + edi], cx       
  0x0021CE8F  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021CE95  a1309f2900              mov      eax, dword ptr [0x299f30]      
  0x0021CE9A  66894c3802              mov      word ptr [eax + edi + 2], cx   
  0x0021CE9F  a11c9f2900              mov      eax, dword ptr [0x299f1c]      
  0x0021CEA4  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021CEA7  8b3c8d70322900          mov      edi, dword ptr [ecx*4 + 0x293270] 
  0x0021CEAE  40                      inc      eax                            
  0x0021CEAF  a31c9f2900              mov      dword ptr [0x299f1c], eax      
  0x0021CEB4  03d7                    add      edx, edi                       
  0x0021CEB6  8d0437                  lea      eax, [edi + esi]               
  0x0021CEB9  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x0021CEBF  33c9                    xor      ecx, ecx                       
  0x0021CEC1  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021CEC9  660b0c8590462900        or       cx, word ptr [eax*4 + 0x294690] 
  0x0021CED1  8a16                    mov      dl, byte ptr [esi]             
  0x0021CED3  33c0                    xor      eax, eax                       
  0x0021CED5  03fd                    add      edi, ebp                       
  0x0021CED7  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021CEDF  80e280                  and      dl, 0x80                       
  0x0021CEE2  8ae2                    mov      ah, dl                         
  0x0021CEE4  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021CEEA  0bc8                    or       ecx, eax                       
  0x0021CEEC  46                      inc      esi                            
  0x0021CEED  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x0021CEF3  66890a                  mov      word ptr [edx], cx             
  0x0021CEF6  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021CEFB  66894802                mov      word ptr [eax + 2], cx         
  0x0021CEFF  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021CF05  a1309f2900              mov      eax, dword ptr [0x299f30]      
  0x0021CF0A  66890c02                mov      word ptr [edx + eax], cx       
  0x0021CF0E  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021CF14  a1309f2900              mov      eax, dword ptr [0x299f30]      
  0x0021CF19  66894c0202              mov      word ptr [edx + eax + 2], cx   
  0x0021CF1E  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021CF24  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021CF2A  b804000000              mov      eax, 4                         
  0x0021CF2F  03f8                    add      edi, eax                       
  0x0021CF31  03f0                    add      esi, eax                       
  0x0021CF33  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021CF37  40                      inc      eax                            
  0x0021CF38  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021CF3E  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021CF44  89442418                mov      dword ptr [esp + 0x18], eax    
  0x0021CF48  a801                    test     al, 1                          
  0x0021CF4A  751a                    jne      0x21cf66                       
  0x0021CF4C  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021CF52  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021CF58  42                      inc      edx                            
  0x0021CF59  41                      inc      ecx                            
  0x0021CF5A  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021CF60  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021CF4A (cond_jump)
  0x0021CF66  ff4c2414                dec      dword ptr [esp + 0x14]         
  0x0021CF6A  0f8580feffff            jne      0x21cdf0                       
  0x0021CF70  5f                      pop      edi                            
  0x0021CF71  5e                      pop      esi                            
  0x0021CF72  5d                      pop      ebp                            
  0x0021CF73  5b                      pop      ebx                            
  0x0021CF74  c3                      ret                                     
; end of function
  0x0021CF75  cc                      int3                                    
  0x0021CF76  cc                      int3                                    
  0x0021CF77  cc                      int3                                    
  0x0021CF78  cc                      int3                                    
  0x0021CF79  cc                      int3                                    
  0x0021CF7A  cc                      int3                                    
  0x0021CF7B  cc                      int3                                    
  0x0021CF7C  cc                      int3                                    
  0x0021CF7D  cc                      int3                                    
  0x0021CF7E  cc                      int3                                    
  0x0021CF7F  cc                      int3                                    

; ============================================================
; Function: sub_0021CF80
; Start: 0x0021CF80  End: 0x0021CFDC  Size: 92 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021CF80:
  0x0021CF80  57                      push     edi                            
  0x0021CF81  8b7c240c                mov      edi, dword ptr [esp + 0xc]     
  0x0021CF85  85ff                    test     edi, edi                       
  0x0021CF87  7451                    je       0x21cfda                       
  0x0021CF89  53                      push     ebx                            
  0x0021CF8A  56                      push     esi                            
  0x0021CF8B  eb03                    jmp      0x21cf90                       
  0x0021CF8D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021CF8B (jump), 0x0021CFD6 (cond_jump)
  0x0021CF90  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021CF96  8a16                    mov      dl, byte ptr [esi]             
  0x0021CF98  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021CF9D  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021CFA0  33db                    xor      ebx, ebx                       
  0x0021CFA2  80e280                  and      dl, 0x80                       
  0x0021CFA5  8afa                    mov      bh, dl                         
  0x0021CFA7  660b1c8d10932900        or       bx, word ptr [ecx*4 + 0x299310] 
  0x0021CFAF  46                      inc      esi                            
  0x0021CFB0  40                      inc      eax                            
  0x0021CFB1  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021CFB6  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021CFBB  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021CFC1  8bcb                    mov      ecx, ebx                       
  0x0021CFC3  668908                  mov      word ptr [eax], cx             
  0x0021CFC6  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021CFCC  83c102                  add      ecx, 2                         
  0x0021CFCF  4f                      dec      edi                            
  0x0021CFD0  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021CFD6  75b8                    jne      0x21cf90                       
  0x0021CFD8  5e                      pop      esi                            
  0x0021CFD9  5b                      pop      ebx                            
                                        ; XREF: 0x0021CF87 (cond_jump)
  0x0021CFDA  5f                      pop      edi                            
  0x0021CFDB  c3                      ret                                     
; end of function
  0x0021CFDC  cc                      int3                                    
  0x0021CFDD  cc                      int3                                    
  0x0021CFDE  cc                      int3                                    
  0x0021CFDF  cc                      int3                                    

; ============================================================
; Function: sub_0021CFE0
; Start: 0x0021CFE0  End: 0x0021D090  Size: 176 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021CFE0:
  0x0021CFE0  53                      push     ebx                            
  0x0021CFE1  55                      push     ebp                            
  0x0021CFE2  8b6c240c                mov      ebp, dword ptr [esp + 0xc]     
  0x0021CFE6  56                      push     esi                            
  0x0021CFE7  57                      push     edi                            
  0x0021CFE8  8bfd                    mov      edi, ebp                       
  0x0021CFEA  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021D07E (cond_jump)
  0x0021CFF0  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021CFF6  8a16                    mov      dl, byte ptr [esi]             
  0x0021CFF8  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021CFFD  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021D000  33db                    xor      ebx, ebx                       
  0x0021D002  80e280                  and      dl, 0x80                       
  0x0021D005  8afa                    mov      bh, dl                         
  0x0021D007  660b1c8d10932900        or       bx, word ptr [ecx*4 + 0x299310] 
  0x0021D00F  46                      inc      esi                            
  0x0021D010  40                      inc      eax                            
  0x0021D011  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021D016  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021D01B  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021D021  8bcb                    mov      ecx, ebx                       
  0x0021D023  668908                  mov      word ptr [eax], cx             
  0x0021D026  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x0021D02C  8a16                    mov      dl, byte ptr [esi]             
  0x0021D02E  a11c9f2900              mov      eax, dword ptr [0x299f1c]      
  0x0021D033  0fb608                  movzx    ecx, byte ptr [eax]            
  0x0021D036  80e280                  and      dl, 0x80                       
  0x0021D039  33db                    xor      ebx, ebx                       
  0x0021D03B  8afa                    mov      bh, dl                         
  0x0021D03D  660b1c8d10932900        or       bx, word ptr [ecx*4 + 0x299310] 
  0x0021D045  46                      inc      esi                            
  0x0021D046  40                      inc      eax                            
  0x0021D047  a31c9f2900              mov      dword ptr [0x299f1c], eax      
  0x0021D04C  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021D051  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x0021D057  8bcb                    mov      ecx, ebx                       
  0x0021D059  668908                  mov      word ptr [eax], cx             
  0x0021D05C  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021D062  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021D068  b802000000              mov      eax, 2                         
  0x0021D06D  03d0                    add      edx, eax                       
  0x0021D06F  03c8                    add      ecx, eax                       
  0x0021D071  4f                      dec      edi                            
  0x0021D072  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021D078  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021D07E  0f856cffffff            jne      0x21cff0                       
  0x0021D084  8b4c2418                mov      ecx, dword ptr [esp + 0x18]    
  0x0021D088  5f                      pop      edi                            
  0x0021D089  5e                      pop      esi                            
  0x0021D08A  8d0429                  lea      eax, [ecx + ebp]               
  0x0021D08D  5d                      pop      ebp                            
  0x0021D08E  5b                      pop      ebx                            
  0x0021D08F  c3                      ret                                     
; end of function
  0x0021D090  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021D094  85c0                    test     eax, eax                       
  0x0021D096  53                      push     ebx                            
  0x0021D097  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021D09B  0f84d1000000            je       0x21d172                       
  0x0021D0A1  55                      push     ebp                            
  0x0021D0A2  56                      push     esi                            
  0x0021D0A3  57                      push     edi                            
  0x0021D0A4  8be8                    mov      ebp, eax                       
  0x0021D0A6  eb08                    jmp      0x21d0b0                       
  0x0021D0A8  8da42400000000          lea      esp, [esp]                     
  0x0021D0AF  90                      nop                                     
                                        ; XREF: 0x0021D0A6 (jump), 0x0021D169 (cond_jump)
  0x0021D0B0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021D0B5  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021D0B8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021D0BE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021D0C1  c1e002                  shl      eax, 2                         
  0x0021D0C4  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x0021D0CA  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x0021D0D0  c1e102                  shl      ecx, 2                         
  0x0021D0D3  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021D0D9  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021D0DF  03d7                    add      edx, edi                       
  0x0021D0E1  8b3d189f2900            mov      edi, dword ptr [0x299f18]      
  0x0021D0E7  0fb607                  movzx    eax, byte ptr [edi]            
  0x0021D0EA  8b048570322900          mov      eax, dword ptr [eax*4 + 0x293270] 
  0x0021D0F1  03c8                    add      ecx, eax                       
  0x0021D0F3  0fb70c8da0522900        movzx    ecx, word ptr [ecx*4 + 0x2952a0] 
  0x0021D0FB  03d0                    add      edx, eax                       
  0x0021D0FD  660b0c9590462900        or       cx, word ptr [edx*4 + 0x294690] 
  0x0021D105  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x0021D10B  03c6                    add      eax, esi                       
  0x0021D10D  660b0c85803a2900        or       cx, word ptr [eax*4 + 0x293a80] 
  0x0021D115  47                      inc      edi                            
  0x0021D116  893d189f2900            mov      dword ptr [0x299f18], edi      
  0x0021D11C  8a02                    mov      al, byte ptr [edx]             
  0x0021D11E  33d2                    xor      edx, edx                       
  0x0021D120  2480                    and      al, 0x80                       
  0x0021D122  8af0                    mov      dh, al                         
  0x0021D124  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021D129  0bca                    or       ecx, edx                       
  0x0021D12B  668908                  mov      word ptr [eax], cx             
  0x0021D12E  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021D134  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021D13A  46                      inc      esi                            
  0x0021D13B  83c202                  add      edx, 2                         
  0x0021D13E  43                      inc      ebx                            
  0x0021D13F  f6c301                  test     bl, 1                          
  0x0021D142  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021D148  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021D14E  7518                    jne      0x21d168                       
  0x0021D150  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021D156  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021D15B  41                      inc      ecx                            
  0x0021D15C  40                      inc      eax                            
  0x0021D15D  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021D163  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021D14E (cond_jump)
  0x0021D168  4d                      dec      ebp                            
  0x0021D169  0f8541ffffff            jne      0x21d0b0                       
  0x0021D16F  5f                      pop      edi                            
  0x0021D170  5e                      pop      esi                            
  0x0021D171  5d                      pop      ebp                            
                                        ; XREF: 0x0021D09B (cond_jump)
  0x0021D172  5b                      pop      ebx                            
  0x0021D173  c3                      ret                                     
  0x0021D174  cc                      int3                                    
  0x0021D175  cc                      int3                                    
  0x0021D176  cc                      int3                                    
  0x0021D177  cc                      int3                                    
  0x0021D178  cc                      int3                                    
  0x0021D179  cc                      int3                                    
  0x0021D17A  cc                      int3                                    
  0x0021D17B  cc                      int3                                    
  0x0021D17C  cc                      int3                                    
  0x0021D17D  cc                      int3                                    
  0x0021D17E  cc                      int3                                    
  0x0021D17F  cc                      int3                                    

; ============================================================
; Function: sub_0021D180
; Start: 0x0021D180  End: 0x0021D2D1  Size: 337 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021D180:
  0x0021D180  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021D184  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021D188  53                      push     ebx                            
  0x0021D189  55                      push     ebp                            
  0x0021D18A  56                      push     esi                            
  0x0021D18B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021D18F  57                      push     edi                            
                                        ; XREF: 0x0021D2C6 (cond_jump)
  0x0021D190  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021D196  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021D199  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021D19F  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021D1A2  c1e102                  shl      ecx, 2                         
  0x0021D1A5  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x0021D1AB  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x0021D1B1  c1e202                  shl      edx, 2                         
  0x0021D1B4  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021D1BA  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021D1C0  03f3                    add      esi, ebx                       
  0x0021D1C2  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x0021D1C8  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021D1CB  8b0c8d70322900          mov      ecx, dword ptr [ecx*4 + 0x293270] 
  0x0021D1D2  43                      inc      ebx                            
  0x0021D1D3  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x0021D1D9  8d1c11                  lea      ebx, [ecx + edx]               
  0x0021D1DC  0fb71c9da0522900        movzx    ebx, word ptr [ebx*4 + 0x2952a0] 
  0x0021D1E4  8d2c31                  lea      ebp, [ecx + esi]               
  0x0021D1E7  660b1cad90462900        or       bx, word ptr [ebp*4 + 0x294690] 
  0x0021D1EF  03cf                    add      ecx, edi                       
  0x0021D1F1  660b1c8d803a2900        or       bx, word ptr [ecx*4 + 0x293a80] 
  0x0021D1F9  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021D1FF  8a09                    mov      cl, byte ptr [ecx]             
  0x0021D201  80e180                  and      cl, 0x80                       
  0x0021D204  89442414                mov      dword ptr [esp + 0x14], eax    
  0x0021D208  33c0                    xor      eax, eax                       
  0x0021D20A  8ae1                    mov      ah, cl                         
  0x0021D20C  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021D212  0bd8                    or       ebx, eax                       
  0x0021D214  668919                  mov      word ptr [ecx], bx             
  0x0021D217  a1289f2900              mov      eax, dword ptr [0x299f28]      
  0x0021D21C  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x0021D222  40                      inc      eax                            
  0x0021D223  a3289f2900              mov      dword ptr [0x299f28], eax      
  0x0021D228  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021D22B  8b0c8d70322900          mov      ecx, dword ptr [ecx*4 + 0x293270] 
  0x0021D232  03d1                    add      edx, ecx                       
  0x0021D234  0fb71495a0522900        movzx    edx, word ptr [edx*4 + 0x2952a0] 
  0x0021D23C  03f1                    add      esi, ecx                       
  0x0021D23E  660b14b590462900        or       dx, word ptr [esi*4 + 0x294690] 
  0x0021D246  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021D24A  03cf                    add      ecx, edi                       
  0x0021D24C  660b148d803a2900        or       dx, word ptr [ecx*4 + 0x293a80] 
  0x0021D254  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021D25A  43                      inc      ebx                            
  0x0021D25B  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x0021D261  8a09                    mov      cl, byte ptr [ecx]             
  0x0021D263  80e180                  and      cl, 0x80                       
  0x0021D266  33db                    xor      ebx, ebx                       
  0x0021D268  8af9                    mov      bh, cl                         
  0x0021D26A  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021D270  0bd3                    or       edx, ebx                       
  0x0021D272  668911                  mov      word ptr [ecx], dx             
  0x0021D275  8b1d2c9f2900            mov      ebx, dword ptr [0x299f2c]      
  0x0021D27B  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021D281  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021D287  b902000000              mov      ecx, 2                         
  0x0021D28C  43                      inc      ebx                            
  0x0021D28D  03f9                    add      edi, ecx                       
  0x0021D28F  03f1                    add      esi, ecx                       
  0x0021D291  40                      inc      eax                            
  0x0021D292  a801                    test     al, 1                          
  0x0021D294  891d2c9f2900            mov      dword ptr [0x299f2c], ebx      
  0x0021D29A  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021D2A0  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021D2A6  751a                    jne      0x21d2c2                       
  0x0021D2A8  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021D2AE  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021D2B4  42                      inc      edx                            
  0x0021D2B5  41                      inc      ecx                            
  0x0021D2B6  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021D2BC  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021D2A6 (cond_jump)
  0x0021D2C2  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021D2C6  0f85c4feffff            jne      0x21d190                       
  0x0021D2CC  5f                      pop      edi                            
  0x0021D2CD  5e                      pop      esi                            
  0x0021D2CE  5d                      pop      ebp                            
  0x0021D2CF  5b                      pop      ebx                            
  0x0021D2D0  c3                      ret                                     
; end of function
  0x0021D2D1  cc                      int3                                    
  0x0021D2D2  cc                      int3                                    
  0x0021D2D3  cc                      int3                                    
  0x0021D2D4  cc                      int3                                    
  0x0021D2D5  cc                      int3                                    
  0x0021D2D6  cc                      int3                                    
  0x0021D2D7  cc                      int3                                    
  0x0021D2D8  cc                      int3                                    
  0x0021D2D9  cc                      int3                                    
  0x0021D2DA  cc                      int3                                    
  0x0021D2DB  cc                      int3                                    
  0x0021D2DC  cc                      int3                                    
  0x0021D2DD  cc                      int3                                    
  0x0021D2DE  cc                      int3                                    
  0x0021D2DF  cc                      int3                                    

; ============================================================
; Function: sub_0021D2E0
; Start: 0x0021D2E0  End: 0x0021D330  Size: 80 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214310
; Called by: sub_0020C030
; ============================================================
sub_0021D2E0:
  0x0021D2E0  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021D2E4  8b4c2434                mov      ecx, dword ptr [esp + 0x34]    
  0x0021D2E8  8b54242c                mov      edx, dword ptr [esp + 0x2c]    
  0x0021D2EC  68a0c22900              push     0x29c2a0                       
  0x0021D2F1  50                      push     eax                            
  0x0021D2F2  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021D2F6  51                      push     ecx                            
  0x0021D2F7  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021D2FB  52                      push     edx                            
  0x0021D2FC  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021D300  50                      push     eax                            
  0x0021D301  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021D305  51                      push     ecx                            
  0x0021D306  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021D30A  52                      push     edx                            
  0x0021D30B  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021D30F  50                      push     eax                            
  0x0021D310  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021D314  51                      push     ecx                            
  0x0021D315  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021D319  52                      push     edx                            
  0x0021D31A  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021D31E  50                      push     eax                            
  0x0021D31F  51                      push     ecx                            
  0x0021D320  52                      push     edx                            
  0x0021D321  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021D325  e8e66fffff              call     0x214310                       ; -> sub_00214310
  0x0021D32A  83c434                  add      esp, 0x34                      
  0x0021D32D  c23400                  ret      0x34                           
; end of function

; ============================================================
; Function: sub_0021D330
; Start: 0x0021D330  End: 0x0021D38B  Size: 91 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214790
; Called by: sub_0020C030
; ============================================================
sub_0021D330:
  0x0021D330  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021D334  8b4c243c                mov      ecx, dword ptr [esp + 0x3c]    
  0x0021D338  8b542434                mov      edx, dword ptr [esp + 0x34]    
  0x0021D33C  68a0c22900              push     0x29c2a0                       
  0x0021D341  50                      push     eax                            
  0x0021D342  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021D346  51                      push     ecx                            
  0x0021D347  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021D34B  52                      push     edx                            
  0x0021D34C  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021D350  50                      push     eax                            
  0x0021D351  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021D355  51                      push     ecx                            
  0x0021D356  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021D35A  52                      push     edx                            
  0x0021D35B  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021D35F  50                      push     eax                            
  0x0021D360  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021D364  51                      push     ecx                            
  0x0021D365  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021D369  52                      push     edx                            
  0x0021D36A  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021D36E  50                      push     eax                            
  0x0021D36F  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021D373  51                      push     ecx                            
  0x0021D374  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021D378  52                      push     edx                            
  0x0021D379  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021D37D  50                      push     eax                            
  0x0021D37E  51                      push     ecx                            
  0x0021D37F  52                      push     edx                            
  0x0021D380  e80b74ffff              call     0x214790                       ; -> sub_00214790
  0x0021D385  83c440                  add      esp, 0x40                      
  0x0021D388  c23c00                  ret      0x3c                           
; end of function
  0x0021D38B  cc                      int3                                    
  0x0021D38C  cc                      int3                                    
  0x0021D38D  cc                      int3                                    
  0x0021D38E  cc                      int3                                    
  0x0021D38F  cc                      int3                                    

; ============================================================
; Function: sub_0021D390
; Start: 0x0021D390  End: 0x0021D5E5  Size: 597 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021D390:
  0x0021D390  53                      push     ebx                            
  0x0021D391  55                      push     ebp                            
  0x0021D392  56                      push     esi                            
  0x0021D393  57                      push     edi                            
  0x0021D394  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021D39A  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021D3A0  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021D3A6  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021D3AC  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021D3B2  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021D3B6  c1e003                  shl      eax, 3                         
  0x0021D3B9  03c7                    add      eax, edi                       
  0x0021D3BB  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021D3C0  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021D3C7  8da42400000000          lea      esp, [esp]                     
  0x0021D3CE  8bff                    mov      edi, edi                       
                                        ; XREF: 0x0021D4A0 (cond_jump)
  0x0021D3D0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021D3D3  0fefc0                  pxor     mm0, mm0                       
  0x0021D3D6  33c0                    xor      eax, eax                       
  0x0021D3D8  83c204                  add      edx, 4                         
  0x0021D3DB  8a4500                  mov      al, byte ptr [ebp]             
  0x0021D3DE  0f60e0                  punpcklbw mm4, mm0                       
  0x0021D3E1  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021D3E9  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D3F1  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021D3F4  83c502                  add      ebp, 2                         
  0x0021D3F7  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021D3FE  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021D406  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D40E  8a03                    mov      al, byte ptr [ebx]             
  0x0021D410  0f71f402                psllw    mm4, 2                         
  0x0021D414  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021D41B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D423  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D42B  0ffdd5                  paddw    mm2, mm5                       
  0x0021D42E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021D431  83c302                  add      ebx, 2                         
  0x0021D434  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D43C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D444  0ffdf5                  paddw    mm6, mm5                       
  0x0021D447  0f62d6                  punpckldq mm2, mm6                       
  0x0021D44A  0ffdcc                  paddw    mm1, mm4                       
  0x0021D44D  8b01                    mov      eax, dword ptr [ecx]           
  0x0021D44F  0ffdd4                  paddw    mm2, mm4                       
  0x0021D452  2580808080              and      eax, 0x80808080                
  0x0021D457  0fedcf                  paddsw   mm1, mm7                       
  0x0021D45A  0f6ef0                  movd     mm6, eax                       
  0x0021D45D  0ffddc                  paddw    mm3, mm4                       
  0x0021D460  0f60c6                  punpcklbw mm0, mm6                       
  0x0021D463  0fd9cf                  psubusw  mm1, mm7                       
  0x0021D466  0f71d103                psrlw    mm1, 3                         
  0x0021D46A  0fedd7                  paddsw   mm2, mm7                       
  0x0021D46D  0fd9d7                  psubusw  mm2, mm7                       
  0x0021D470  0f71d203                psrlw    mm2, 3                         
  0x0021D474  0feddf                  paddsw   mm3, mm7                       
  0x0021D477  0f71f205                psllw    mm2, 5                         
  0x0021D47B  0fd9df                  psubusw  mm3, mm7                       
  0x0021D47E  0f71d303                psrlw    mm3, 3                         
  0x0021D482  0febca                  por      mm1, mm2                       
  0x0021D485  0f71f30a                psllw    mm3, 0xa                       
  0x0021D489  0febc8                  por      mm1, mm0                       
  0x0021D48C  0febcb                  por      mm1, mm3                       
  0x0021D48F  83c708                  add      edi, 8                         
  0x0021D492  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021D497  83c104                  add      ecx, 4                         
  0x0021D49A  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021D49E  3bf8                    cmp      edi, eax                       
  0x0021D4A0  0f822affffff            jb       0x21d3d0                       
  0x0021D4A6  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021D4AC  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021D4B2  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021D4B8  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021D4BE  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021D4C4  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021D4CA  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021D4D0  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021D4D4  c1e003                  shl      eax, 3                         
  0x0021D4D7  03c7                    add      eax, edi                       
  0x0021D4D9  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021D4DE  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021D4E5  8da42400000000          lea      esp, [esp]                     
  0x0021D4EC  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x0021D5C0 (cond_jump)
  0x0021D4F0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021D4F3  0fefc0                  pxor     mm0, mm0                       
  0x0021D4F6  33c0                    xor      eax, eax                       
  0x0021D4F8  83c204                  add      edx, 4                         
  0x0021D4FB  8a4500                  mov      al, byte ptr [ebp]             
  0x0021D4FE  0f60e0                  punpcklbw mm4, mm0                       
  0x0021D501  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021D509  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D511  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021D514  83c502                  add      ebp, 2                         
  0x0021D517  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021D51E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021D526  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D52E  8a03                    mov      al, byte ptr [ebx]             
  0x0021D530  0f71f402                psllw    mm4, 2                         
  0x0021D534  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021D53B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D543  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D54B  0ffdd5                  paddw    mm2, mm5                       
  0x0021D54E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021D551  83c302                  add      ebx, 2                         
  0x0021D554  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D55C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D564  0ffdf5                  paddw    mm6, mm5                       
  0x0021D567  0f62d6                  punpckldq mm2, mm6                       
  0x0021D56A  0ffdcc                  paddw    mm1, mm4                       
  0x0021D56D  8b01                    mov      eax, dword ptr [ecx]           
  0x0021D56F  0ffdd4                  paddw    mm2, mm4                       
  0x0021D572  2580808080              and      eax, 0x80808080                
  0x0021D577  0fedcf                  paddsw   mm1, mm7                       
  0x0021D57A  0f6ef0                  movd     mm6, eax                       
  0x0021D57D  0ffddc                  paddw    mm3, mm4                       
  0x0021D580  0f60c6                  punpcklbw mm0, mm6                       
  0x0021D583  0fd9cf                  psubusw  mm1, mm7                       
  0x0021D586  0f71d103                psrlw    mm1, 3                         
  0x0021D58A  0fedd7                  paddsw   mm2, mm7                       
  0x0021D58D  0fd9d7                  psubusw  mm2, mm7                       
  0x0021D590  0f71d203                psrlw    mm2, 3                         
  0x0021D594  0feddf                  paddsw   mm3, mm7                       
  0x0021D597  0f71f205                psllw    mm2, 5                         
  0x0021D59B  0fd9df                  psubusw  mm3, mm7                       
  0x0021D59E  0f71d303                psrlw    mm3, 3                         
  0x0021D5A2  0febca                  por      mm1, mm2                       
  0x0021D5A5  0f71f30a                psllw    mm3, 0xa                       
  0x0021D5A9  0febc8                  por      mm1, mm0                       
  0x0021D5AC  0febcb                  por      mm1, mm3                       
  0x0021D5AF  83c708                  add      edi, 8                         
  0x0021D5B2  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021D5B7  83c104                  add      ecx, 4                         
  0x0021D5BA  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021D5BE  3bf8                    cmp      edi, eax                       
  0x0021D5C0  0f822affffff            jb       0x21d4f0                       
  0x0021D5C6  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021D5CC  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021D5D2  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021D5D8  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021D5DE  5f                      pop      edi                            
  0x0021D5DF  5e                      pop      esi                            
  0x0021D5E0  5d                      pop      ebp                            
  0x0021D5E1  5b                      pop      ebx                            
  0x0021D5E2  c20400                  ret      4                              
; end of function
  0x0021D5E5  8da42400000000          lea      esp, [esp]                     
  0x0021D5EC  8d642400                lea      esp, [esp]                     
  0x0021D5F0  53                      push     ebx                            
  0x0021D5F1  55                      push     ebp                            
  0x0021D5F2  56                      push     esi                            
  0x0021D5F3  57                      push     edi                            
  0x0021D5F4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021D5FA  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021D600  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021D606  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021D60C  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021D612  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021D616  c1e003                  shl      eax, 3                         
  0x0021D619  03c7                    add      eax, edi                       
  0x0021D61B  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021D620  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021D627  8da42400000000          lea      esp, [esp]                     
  0x0021D62E  8bff                    mov      edi, edi                       
                                        ; XREF: 0x0021D749 (cond_jump)
  0x0021D630  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021D633  0fefc0                  pxor     mm0, mm0                       
  0x0021D636  33c0                    xor      eax, eax                       
  0x0021D638  83c204                  add      edx, 4                         
  0x0021D63B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021D63E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021D641  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021D649  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D651  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021D654  83c502                  add      ebp, 2                         
  0x0021D657  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021D65E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021D666  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D66E  8a03                    mov      al, byte ptr [ebx]             
  0x0021D670  0f71f402                psllw    mm4, 2                         
  0x0021D674  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021D67B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D683  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D68B  0ffdd5                  paddw    mm2, mm5                       
  0x0021D68E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021D691  83c302                  add      ebx, 2                         
  0x0021D694  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D69C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D6A4  0ffdf5                  paddw    mm6, mm5                       
  0x0021D6A7  8a4500                  mov      al, byte ptr [ebp]             
  0x0021D6AA  0f62d6                  punpckldq mm2, mm6                       
  0x0021D6AD  0f73d110                psrlq    mm1, 0x10                      
  0x0021D6B1  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021D6B9  0f73d210                psrlq    mm2, 0x10                      
  0x0021D6BD  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021D6C5  0f73d310                psrlq    mm3, 0x10                      
  0x0021D6C9  8a03                    mov      al, byte ptr [ebx]             
  0x0021D6CB  0f73f630                psllq    mm6, 0x30                      
  0x0021D6CF  0febce                  por      mm1, mm6                       
  0x0021D6D2  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021D6DA  0ffdee                  paddw    mm5, mm6                       
  0x0021D6DD  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021D6E5  0f73f530                psllq    mm5, 0x30                      
  0x0021D6E9  0f73f630                psllq    mm6, 0x30                      
  0x0021D6ED  0febd5                  por      mm2, mm5                       
  0x0021D6F0  0febde                  por      mm3, mm6                       
  0x0021D6F3  0ffdcc                  paddw    mm1, mm4                       
  0x0021D6F6  8b01                    mov      eax, dword ptr [ecx]           
  0x0021D6F8  0ffdd4                  paddw    mm2, mm4                       
  0x0021D6FB  2580808080              and      eax, 0x80808080                
  0x0021D700  0fedcf                  paddsw   mm1, mm7                       
  0x0021D703  0f6ef0                  movd     mm6, eax                       
  0x0021D706  0ffddc                  paddw    mm3, mm4                       
  0x0021D709  0f60c6                  punpcklbw mm0, mm6                       
  0x0021D70C  0fd9cf                  psubusw  mm1, mm7                       
  0x0021D70F  0f71d103                psrlw    mm1, 3                         
  0x0021D713  0fedd7                  paddsw   mm2, mm7                       
  0x0021D716  0fd9d7                  psubusw  mm2, mm7                       
  0x0021D719  0f71d203                psrlw    mm2, 3                         
  0x0021D71D  0feddf                  paddsw   mm3, mm7                       
  0x0021D720  0f71f205                psllw    mm2, 5                         
  0x0021D724  0fd9df                  psubusw  mm3, mm7                       
  0x0021D727  0f71d303                psrlw    mm3, 3                         
  0x0021D72B  0febca                  por      mm1, mm2                       
  0x0021D72E  0f71f30a                psllw    mm3, 0xa                       
  0x0021D732  0febc8                  por      mm1, mm0                       
  0x0021D735  0febcb                  por      mm1, mm3                       
  0x0021D738  83c708                  add      edi, 8                         
  0x0021D73B  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021D740  83c104                  add      ecx, 4                         
  0x0021D743  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021D747  3bf8                    cmp      edi, eax                       
  0x0021D749  0f82e1feffff            jb       0x21d630                       
  0x0021D74F  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021D755  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021D75B  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021D761  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021D767  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021D76D  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021D771  c1e003                  shl      eax, 3                         
  0x0021D774  03c7                    add      eax, edi                       
  0x0021D776  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021D77B  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021D782  8da42400000000          lea      esp, [esp]                     
  0x0021D789  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x0021D8AD (cond_jump)
  0x0021D790  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021D793  0fefc0                  pxor     mm0, mm0                       
  0x0021D796  33c0                    xor      eax, eax                       
  0x0021D798  83c204                  add      edx, 4                         
  0x0021D79B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021D79E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021D7A1  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021D7A9  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D7B1  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021D7B4  83c502                  add      ebp, 2                         
  0x0021D7B7  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021D7BE  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021D7C6  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021D7CE  8a03                    mov      al, byte ptr [ebx]             
  0x0021D7D0  0f71f402                psllw    mm4, 2                         
  0x0021D7D4  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021D7DB  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D7E3  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D7EB  0ffdd5                  paddw    mm2, mm5                       
  0x0021D7EE  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021D7F1  83c302                  add      ebx, 2                         
  0x0021D7F4  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021D7FC  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021D804  0ffdf5                  paddw    mm6, mm5                       
  0x0021D807  8a4500                  mov      al, byte ptr [ebp]             
  0x0021D80A  0f62d6                  punpckldq mm2, mm6                       
  0x0021D80D  0f73d110                psrlq    mm1, 0x10                      
  0x0021D811  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021D819  0f73d210                psrlq    mm2, 0x10                      
  0x0021D81D  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021D825  0f73d310                psrlq    mm3, 0x10                      
  0x0021D829  8a03                    mov      al, byte ptr [ebx]             
  0x0021D82B  0f73f630                psllq    mm6, 0x30                      
  0x0021D82F  0febce                  por      mm1, mm6                       
  0x0021D832  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021D83A  0ffdee                  paddw    mm5, mm6                       
  0x0021D83D  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021D845  0f73f530                psllq    mm5, 0x30                      
  0x0021D849  0f73f630                psllq    mm6, 0x30                      
  0x0021D84D  0febd5                  por      mm2, mm5                       
  0x0021D850  0febde                  por      mm3, mm6                       
  0x0021D853  0ffdcc                  paddw    mm1, mm4                       
  0x0021D856  8b01                    mov      eax, dword ptr [ecx]           
  0x0021D858  0ffdd4                  paddw    mm2, mm4                       
  0x0021D85B  2580808080              and      eax, 0x80808080                
  0x0021D860  0fedcf                  paddsw   mm1, mm7                       
  0x0021D863  0f6ef0                  movd     mm6, eax                       
  0x0021D866  0ffddc                  paddw    mm3, mm4                       
  0x0021D869  0f60c6                  punpcklbw mm0, mm6                       
  0x0021D86C  0fd9cf                  psubusw  mm1, mm7                       
  0x0021D86F  0f71d103                psrlw    mm1, 3                         
  0x0021D873  0fedd7                  paddsw   mm2, mm7                       
  0x0021D876  0f71f100                psllw    mm1, 0                         
  0x0021D87A  0fd9d7                  psubusw  mm2, mm7                       
  0x0021D87D  0f71d203                psrlw    mm2, 3                         
  0x0021D881  0feddf                  paddsw   mm3, mm7                       
  0x0021D884  0f71f205                psllw    mm2, 5                         
  0x0021D888  0fd9df                  psubusw  mm3, mm7                       
  0x0021D88B  0f71d303                psrlw    mm3, 3                         
  0x0021D88F  0febca                  por      mm1, mm2                       
  0x0021D892  0f71f30a                psllw    mm3, 0xa                       
  0x0021D896  0febc8                  por      mm1, mm0                       
  0x0021D899  0febcb                  por      mm1, mm3                       
  0x0021D89C  83c708                  add      edi, 8                         
  0x0021D89F  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021D8A4  83c104                  add      ecx, 4                         
  0x0021D8A7  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021D8AB  3bf8                    cmp      edi, eax                       
  0x0021D8AD  0f82ddfeffff            jb       0x21d790                       
  0x0021D8B3  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021D8B9  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021D8BF  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021D8C5  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021D8CB  5f                      pop      edi                            
  0x0021D8CC  5e                      pop      esi                            
  0x0021D8CD  5d                      pop      ebp                            
  0x0021D8CE  5b                      pop      ebx                            
  0x0021D8CF  c20400                  ret      4                              
  0x0021D8D2  0000                    add      byte ptr [eax], al             
