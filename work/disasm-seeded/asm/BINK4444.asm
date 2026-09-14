; ============================================================
; Section: BINK4444
; VA: 0x0021AEE0 - 0x0021C3B0
; Size: 5328 bytes (5.2 KB)
; Functions: 17
; Instructions: 1430
; ============================================================

  0x0021AEE0  56                      push     esi                            
  0x0021AEE1  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0021AEE5  85f6                    test     esi, esi                       
  0x0021AEE7  7463                    je       0x21af4c                       
  0x0021AEE9  57                      push     edi                            
  0x0021AEEA  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021AF49 (cond_jump)
  0x0021AEF0  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021AEF6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021AEF9  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021AEFF  0fb63a                  movzx    edi, byte ptr [edx]            
  0x0021AF02  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021AF0A  660b04bd10932900        or       ax, word ptr [edi*4 + 0x299310] 
  0x0021AF12  41                      inc      ecx                            
  0x0021AF13  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021AF19  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021AF1F  42                      inc      edx                            
  0x0021AF20  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021AF26  668901                  mov      word ptr [ecx], ax             
  0x0021AF29  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021AF2F  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021AF35  66890411                mov      word ptr [ecx + edx], ax       
  0x0021AF39  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021AF3F  83c102                  add      ecx, 2                         
  0x0021AF42  4e                      dec      esi                            
  0x0021AF43  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021AF49  75a5                    jne      0x21aef0                       
  0x0021AF4B  5f                      pop      edi                            
                                        ; XREF: 0x0021AEE7 (cond_jump)
  0x0021AF4C  5e                      pop      esi                            
  0x0021AF4D  c3                      ret                                     
  0x0021AF4E  cc                      int3                                    
  0x0021AF4F  cc                      int3                                    

; ============================================================
; Function: sub_0021AF50
; Start: 0x0021AF50  End: 0x0021B021  Size: 209 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021AF50:
  0x0021AF50  53                      push     ebx                            
  0x0021AF51  55                      push     ebp                            
  0x0021AF52  56                      push     esi                            
  0x0021AF53  57                      push     edi                            
  0x0021AF54  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x0021AF58  8bf7                    mov      esi, edi                       
  0x0021AF5A  bb02000000              mov      ebx, 2                         
  0x0021AF5F  90                      nop                                     
                                        ; XREF: 0x0021B00F (cond_jump)
  0x0021AF60  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021AF66  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021AF69  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021AF6F  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021AF72  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021AF7A  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021AF82  41                      inc      ecx                            
  0x0021AF83  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021AF89  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021AF8F  42                      inc      edx                            
  0x0021AF90  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021AF96  668901                  mov      word ptr [ecx], ax             
  0x0021AF99  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021AF9F  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021AFA5  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021AFA9  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021AFAF  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021AFB2  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021AFB8  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021AFBB  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021AFC3  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021AFCB  41                      inc      ecx                            
  0x0021AFCC  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021AFD2  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021AFD8  42                      inc      edx                            
  0x0021AFD9  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021AFDF  668901                  mov      word ptr [ecx], ax             
  0x0021AFE2  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021AFE8  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021AFEE  6689040a                mov      word ptr [edx + ecx], ax       
  0x0021AFF2  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021AFF8  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021AFFE  03d3                    add      edx, ebx                       
  0x0021B000  03cb                    add      ecx, ebx                       
  0x0021B002  4e                      dec      esi                            
  0x0021B003  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021B009  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021B00F  0f854bffffff            jne      0x21af60                       
  0x0021B015  8b542418                mov      edx, dword ptr [esp + 0x18]    
  0x0021B019  8d0417                  lea      eax, [edi + edx]               
  0x0021B01C  5f                      pop      edi                            
  0x0021B01D  5e                      pop      esi                            
  0x0021B01E  5d                      pop      ebp                            
  0x0021B01F  5b                      pop      ebx                            
  0x0021B020  c3                      ret                                     
; end of function
  0x0021B021  cc                      int3                                    
  0x0021B022  cc                      int3                                    
  0x0021B023  cc                      int3                                    
  0x0021B024  cc                      int3                                    
  0x0021B025  cc                      int3                                    
  0x0021B026  cc                      int3                                    
  0x0021B027  cc                      int3                                    
  0x0021B028  cc                      int3                                    
  0x0021B029  cc                      int3                                    
  0x0021B02A  cc                      int3                                    
  0x0021B02B  cc                      int3                                    
  0x0021B02C  cc                      int3                                    
  0x0021B02D  cc                      int3                                    
  0x0021B02E  cc                      int3                                    
  0x0021B02F  cc                      int3                                    

; ============================================================
; Function: sub_0021B030
; Start: 0x0021B030  End: 0x0021B098  Size: 104 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B030:
  0x0021B030  56                      push     esi                            
  0x0021B031  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0021B035  85f6                    test     esi, esi                       
  0x0021B037  745d                    je       0x21b096                       
  0x0021B039  57                      push     edi                            
  0x0021B03A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021B093 (cond_jump)
  0x0021B040  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021B046  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021B049  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021B04F  0fb63a                  movzx    edi, byte ptr [edx]            
  0x0021B052  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021B05A  660b04bd10932900        or       ax, word ptr [edi*4 + 0x299310] 
  0x0021B062  41                      inc      ecx                            
  0x0021B063  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021B069  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B06F  42                      inc      edx                            
  0x0021B070  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021B076  668901                  mov      word ptr [ecx], ax             
  0x0021B079  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B07F  66894202                mov      word ptr [edx + 2], ax         
  0x0021B083  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B089  83c104                  add      ecx, 4                         
  0x0021B08C  4e                      dec      esi                            
  0x0021B08D  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021B093  75ab                    jne      0x21b040                       
  0x0021B095  5f                      pop      edi                            
                                        ; XREF: 0x0021B037 (cond_jump)
  0x0021B096  5e                      pop      esi                            
  0x0021B097  c3                      ret                                     
; end of function
  0x0021B098  cc                      int3                                    
  0x0021B099  cc                      int3                                    
  0x0021B09A  cc                      int3                                    
  0x0021B09B  cc                      int3                                    
  0x0021B09C  cc                      int3                                    
  0x0021B09D  cc                      int3                                    
  0x0021B09E  cc                      int3                                    
  0x0021B09F  cc                      int3                                    

; ============================================================
; Function: sub_0021B0A0
; Start: 0x0021B0A0  End: 0x0021B164  Size: 196 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B0A0:
  0x0021B0A0  53                      push     ebx                            
  0x0021B0A1  55                      push     ebp                            
  0x0021B0A2  56                      push     esi                            
  0x0021B0A3  57                      push     edi                            
  0x0021B0A4  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x0021B0A8  8bf7                    mov      esi, edi                       
  0x0021B0AA  bb04000000              mov      ebx, 4                         
  0x0021B0AF  90                      nop                                     
                                        ; XREF: 0x0021B153 (cond_jump)
  0x0021B0B0  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021B0B6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021B0B9  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021B0BF  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021B0C2  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021B0CA  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021B0D2  41                      inc      ecx                            
  0x0021B0D3  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021B0D9  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B0DF  42                      inc      edx                            
  0x0021B0E0  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021B0E6  668901                  mov      word ptr [ecx], ax             
  0x0021B0E9  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B0EF  66894202                mov      word ptr [edx + 2], ax         
  0x0021B0F3  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021B0F9  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021B0FC  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021B102  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021B105  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021B10D  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021B115  41                      inc      ecx                            
  0x0021B116  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021B11C  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021B122  42                      inc      edx                            
  0x0021B123  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021B129  668901                  mov      word ptr [ecx], ax             
  0x0021B12C  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B132  66894202                mov      word ptr [edx + 2], ax         
  0x0021B136  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B13C  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021B142  03d3                    add      edx, ebx                       
  0x0021B144  03cb                    add      ecx, ebx                       
  0x0021B146  4e                      dec      esi                            
  0x0021B147  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021B14D  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021B153  0f8557ffffff            jne      0x21b0b0                       
  0x0021B159  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021B15D  03c7                    add      eax, edi                       
  0x0021B15F  5f                      pop      edi                            
  0x0021B160  5e                      pop      esi                            
  0x0021B161  5d                      pop      ebp                            
  0x0021B162  5b                      pop      ebx                            
  0x0021B163  c3                      ret                                     
; end of function
  0x0021B164  cc                      int3                                    
  0x0021B165  cc                      int3                                    
  0x0021B166  cc                      int3                                    
  0x0021B167  cc                      int3                                    
  0x0021B168  cc                      int3                                    
  0x0021B169  cc                      int3                                    
  0x0021B16A  cc                      int3                                    
  0x0021B16B  cc                      int3                                    
  0x0021B16C  cc                      int3                                    
  0x0021B16D  cc                      int3                                    
  0x0021B16E  cc                      int3                                    
  0x0021B16F  cc                      int3                                    

; ============================================================
; Function: sub_0021B170
; Start: 0x0021B170  End: 0x0021B1F9  Size: 137 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B170:
  0x0021B170  56                      push     esi                            
  0x0021B171  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0021B175  85f6                    test     esi, esi                       
  0x0021B177  747e                    je       0x21b1f7                       
  0x0021B179  57                      push     edi                            
  0x0021B17A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021B1F4 (cond_jump)
  0x0021B180  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021B186  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021B189  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021B18F  0fb63a                  movzx    edi, byte ptr [edx]            
  0x0021B192  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021B19A  660b04bd10932900        or       ax, word ptr [edi*4 + 0x299310] 
  0x0021B1A2  41                      inc      ecx                            
  0x0021B1A3  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021B1A9  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B1AF  42                      inc      edx                            
  0x0021B1B0  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021B1B6  668901                  mov      word ptr [ecx], ax             
  0x0021B1B9  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B1BF  66894202                mov      word ptr [edx + 2], ax         
  0x0021B1C3  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B1C9  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021B1CF  66890411                mov      word ptr [ecx + edx], ax       
  0x0021B1D3  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B1D9  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021B1DF  6689440a02              mov      word ptr [edx + ecx + 2], ax   
  0x0021B1E4  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B1EA  83c104                  add      ecx, 4                         
  0x0021B1ED  4e                      dec      esi                            
  0x0021B1EE  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021B1F4  758a                    jne      0x21b180                       
  0x0021B1F6  5f                      pop      edi                            
                                        ; XREF: 0x0021B177 (cond_jump)
  0x0021B1F7  5e                      pop      esi                            
  0x0021B1F8  c3                      ret                                     
; end of function
  0x0021B1F9  cc                      int3                                    
  0x0021B1FA  cc                      int3                                    
  0x0021B1FB  cc                      int3                                    
  0x0021B1FC  cc                      int3                                    
  0x0021B1FD  cc                      int3                                    
  0x0021B1FE  cc                      int3                                    
  0x0021B1FF  cc                      int3                                    

; ============================================================
; Function: sub_0021B200
; Start: 0x0021B200  End: 0x0021B306  Size: 262 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B200:
  0x0021B200  53                      push     ebx                            
  0x0021B201  55                      push     ebp                            
  0x0021B202  56                      push     esi                            
  0x0021B203  57                      push     edi                            
  0x0021B204  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x0021B208  8bf7                    mov      esi, edi                       
  0x0021B20A  bb04000000              mov      ebx, 4                         
  0x0021B20F  90                      nop                                     
                                        ; XREF: 0x0021B2F5 (cond_jump)
  0x0021B210  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021B216  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021B219  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021B21F  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021B222  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021B22A  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021B232  41                      inc      ecx                            
  0x0021B233  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021B239  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B23F  42                      inc      edx                            
  0x0021B240  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021B246  668901                  mov      word ptr [ecx], ax             
  0x0021B249  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B24F  66894202                mov      word ptr [edx + 2], ax         
  0x0021B253  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B259  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021B25F  66890411                mov      word ptr [ecx + edx], ax       
  0x0021B263  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B269  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021B26F  6689441102              mov      word ptr [ecx + edx + 2], ax   
  0x0021B274  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021B27A  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021B27D  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021B283  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021B286  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021B28E  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021B296  41                      inc      ecx                            
  0x0021B297  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021B29D  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021B2A3  42                      inc      edx                            
  0x0021B2A4  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021B2AA  668901                  mov      word ptr [ecx], ax             
  0x0021B2AD  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B2B3  66894202                mov      word ptr [edx + 2], ax         
  0x0021B2B7  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021B2BD  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021B2C3  66890411                mov      word ptr [ecx + edx], ax       
  0x0021B2C7  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021B2CD  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021B2D3  6689441102              mov      word ptr [ecx + edx + 2], ax   
  0x0021B2D8  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B2DE  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021B2E4  03d3                    add      edx, ebx                       
  0x0021B2E6  03cb                    add      ecx, ebx                       
  0x0021B2E8  4e                      dec      esi                            
  0x0021B2E9  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021B2EF  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021B2F5  0f8515ffffff            jne      0x21b210                       
  0x0021B2FB  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021B2FF  03c7                    add      eax, edi                       
  0x0021B301  5f                      pop      edi                            
  0x0021B302  5e                      pop      esi                            
  0x0021B303  5d                      pop      ebp                            
  0x0021B304  5b                      pop      ebx                            
  0x0021B305  c3                      ret                                     
; end of function
  0x0021B306  cc                      int3                                    
  0x0021B307  cc                      int3                                    
  0x0021B308  cc                      int3                                    
  0x0021B309  cc                      int3                                    
  0x0021B30A  cc                      int3                                    
  0x0021B30B  cc                      int3                                    
  0x0021B30C  cc                      int3                                    
  0x0021B30D  cc                      int3                                    
  0x0021B30E  cc                      int3                                    
  0x0021B30F  cc                      int3                                    

; ============================================================
; Function: sub_0021B310
; Start: 0x0021B310  End: 0x0021B400  Size: 240 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B310:
  0x0021B310  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021B314  85c0                    test     eax, eax                       
  0x0021B316  53                      push     ebx                            
  0x0021B317  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021B31B  0f84dd000000            je       0x21b3fe                       
  0x0021B321  55                      push     ebp                            
  0x0021B322  56                      push     esi                            
  0x0021B323  57                      push     edi                            
  0x0021B324  8be8                    mov      ebp, eax                       
  0x0021B326  eb08                    jmp      0x21b330                       
  0x0021B328  8da42400000000          lea      esp, [esp]                     
  0x0021B32F  90                      nop                                     
                                        ; XREF: 0x0021B326 (jump), 0x0021B3F5 (cond_jump)
  0x0021B330  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021B335  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021B338  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021B33E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021B341  c1e002                  shl      eax, 2                         
  0x0021B344  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021B34A  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021B350  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021B355  c1e102                  shl      ecx, 2                         
  0x0021B358  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021B35E  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021B364  03d6                    add      edx, esi                       
  0x0021B366  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021B369  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021B370  40                      inc      eax                            
  0x0021B371  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021B376  8d040e                  lea      eax, [esi + ecx]               
  0x0021B379  668b0485a0522900        mov      ax, word ptr [eax*4 + 0x2952a0] 
  0x0021B381  8d0c16                  lea      ecx, [esi + edx]               
  0x0021B384  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021B38C  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021B392  0fb611                  movzx    edx, byte ptr [ecx]            
  0x0021B395  03f7                    add      esi, edi                       
  0x0021B397  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021B39F  660b0495b05a2900        or       ax, word ptr [edx*4 + 0x295ab0] 
  0x0021B3A7  41                      inc      ecx                            
  0x0021B3A8  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021B3AE  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B3B4  668901                  mov      word ptr [ecx], ax             
  0x0021B3B7  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B3BD  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021B3C3  66890411                mov      word ptr [ecx + edx], ax       
  0x0021B3C7  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B3CD  83c202                  add      edx, 2                         
  0x0021B3D0  43                      inc      ebx                            
  0x0021B3D1  f6c301                  test     bl, 1                          
  0x0021B3D4  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021B3DA  7518                    jne      0x21b3f4                       
  0x0021B3DC  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021B3E2  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021B3E7  41                      inc      ecx                            
  0x0021B3E8  40                      inc      eax                            
  0x0021B3E9  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021B3EF  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021B3DA (cond_jump)
  0x0021B3F4  4d                      dec      ebp                            
  0x0021B3F5  0f8535ffffff            jne      0x21b330                       
  0x0021B3FB  5f                      pop      edi                            
  0x0021B3FC  5e                      pop      esi                            
  0x0021B3FD  5d                      pop      ebp                            
                                        ; XREF: 0x0021B31B (cond_jump)
  0x0021B3FE  5b                      pop      ebx                            
  0x0021B3FF  c3                      ret                                     
; end of function
  0x0021B400  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021B404  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021B408  53                      push     ebx                            
  0x0021B409  55                      push     ebp                            
  0x0021B40A  56                      push     esi                            
  0x0021B40B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021B40F  57                      push     edi                            
                                        ; XREF: 0x0021B554 (cond_jump)
  0x0021B410  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021B416  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021B419  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021B41F  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021B422  c1e102                  shl      ecx, 2                         
  0x0021B425  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x0021B42B  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021B431  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021B437  c1e202                  shl      edx, 2                         
  0x0021B43A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021B440  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021B446  03f7                    add      esi, edi                       
  0x0021B448  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021B44B  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021B452  41                      inc      ecx                            
  0x0021B453  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021B459  8d0c17                  lea      ecx, [edi + edx]               
  0x0021B45C  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021B464  8d2c37                  lea      ebp, [edi + esi]               
  0x0021B467  660b0cad90462900        or       cx, word ptr [ebp*4 + 0x294690] 
  0x0021B46F  03fb                    add      edi, ebx                       
  0x0021B471  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021B479  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x0021B47F  0fb62f                  movzx    ebp, byte ptr [edi]            
  0x0021B482  660b0cadb05a2900        or       cx, word ptr [ebp*4 + 0x295ab0] 
  0x0021B48A  47                      inc      edi                            
  0x0021B48B  893d289f2900            mov      dword ptr [0x299f28], edi      
  0x0021B491  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021B497  66890f                  mov      word ptr [edi], cx             
  0x0021B49A  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x0021B4A0  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x0021B4A6  66890c2f                mov      word ptr [edi + ebp], cx       
  0x0021B4AA  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021B4B0  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021B4B3  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021B4BA  41                      inc      ecx                            
  0x0021B4BB  03d7                    add      edx, edi                       
  0x0021B4BD  03f7                    add      esi, edi                       
  0x0021B4BF  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021B4C5  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021B4CD  660b0cb590462900        or       cx, word ptr [esi*4 + 0x294690] 
  0x0021B4D5  8b152c9f2900            mov      edx, dword ptr [0x299f2c]      
  0x0021B4DB  0fb632                  movzx    esi, byte ptr [edx]            
  0x0021B4DE  03fb                    add      edi, ebx                       
  0x0021B4E0  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021B4E8  660b0cb5b05a2900        or       cx, word ptr [esi*4 + 0x295ab0] 
  0x0021B4F0  42                      inc      edx                            
  0x0021B4F1  89152c9f2900            mov      dword ptr [0x299f2c], edx      
  0x0021B4F7  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B4FD  66890a                  mov      word ptr [edx], cx             
  0x0021B500  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B506  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x0021B50C  66890c32                mov      word ptr [edx + esi], cx       
  0x0021B510  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021B516  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021B51C  b902000000              mov      ecx, 2                         
  0x0021B521  03f9                    add      edi, ecx                       
  0x0021B523  03f1                    add      esi, ecx                       
  0x0021B525  40                      inc      eax                            
  0x0021B526  a801                    test     al, 1                          
  0x0021B528  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021B52E  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021B534  751a                    jne      0x21b550                       
  0x0021B536  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021B53C  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021B542  42                      inc      edx                            
  0x0021B543  41                      inc      ecx                            
  0x0021B544  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021B54A  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021B534 (cond_jump)
  0x0021B550  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021B554  0f85b6feffff            jne      0x21b410                       
  0x0021B55A  5f                      pop      edi                            
  0x0021B55B  5e                      pop      esi                            
  0x0021B55C  5d                      pop      ebp                            
  0x0021B55D  5b                      pop      ebx                            
  0x0021B55E  c3                      ret                                     
  0x0021B55F  cc                      int3                                    

; ============================================================
; Function: sub_0021B560
; Start: 0x0021B560  End: 0x0021B64A  Size: 234 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B560:
  0x0021B560  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021B564  85c0                    test     eax, eax                       
  0x0021B566  53                      push     ebx                            
  0x0021B567  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021B56B  0f84d7000000            je       0x21b648                       
  0x0021B571  55                      push     ebp                            
  0x0021B572  56                      push     esi                            
  0x0021B573  57                      push     edi                            
  0x0021B574  8be8                    mov      ebp, eax                       
  0x0021B576  eb08                    jmp      0x21b580                       
  0x0021B578  8da42400000000          lea      esp, [esp]                     
  0x0021B57F  90                      nop                                     
                                        ; XREF: 0x0021B576 (jump), 0x0021B63F (cond_jump)
  0x0021B580  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021B585  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021B588  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021B58E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021B591  c1e002                  shl      eax, 2                         
  0x0021B594  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021B59A  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021B5A0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021B5A5  c1e102                  shl      ecx, 2                         
  0x0021B5A8  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021B5AE  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021B5B4  03d6                    add      edx, esi                       
  0x0021B5B6  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021B5B9  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021B5C0  40                      inc      eax                            
  0x0021B5C1  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021B5C6  8d040e                  lea      eax, [esi + ecx]               
  0x0021B5C9  668b0485a0522900        mov      ax, word ptr [eax*4 + 0x2952a0] 
  0x0021B5D1  8d0c16                  lea      ecx, [esi + edx]               
  0x0021B5D4  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021B5DC  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021B5E2  0fb611                  movzx    edx, byte ptr [ecx]            
  0x0021B5E5  03f7                    add      esi, edi                       
  0x0021B5E7  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021B5EF  660b0495b05a2900        or       ax, word ptr [edx*4 + 0x295ab0] 
  0x0021B5F7  41                      inc      ecx                            
  0x0021B5F8  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021B5FE  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B604  668901                  mov      word ptr [ecx], ax             
  0x0021B607  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B60D  66894202                mov      word ptr [edx + 2], ax         
  0x0021B611  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B617  83c204                  add      edx, 4                         
  0x0021B61A  43                      inc      ebx                            
  0x0021B61B  f6c301                  test     bl, 1                          
  0x0021B61E  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021B624  7518                    jne      0x21b63e                       
  0x0021B626  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021B62C  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021B631  41                      inc      ecx                            
  0x0021B632  40                      inc      eax                            
  0x0021B633  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021B639  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021B624 (cond_jump)
  0x0021B63E  4d                      dec      ebp                            
  0x0021B63F  0f853bffffff            jne      0x21b580                       
  0x0021B645  5f                      pop      edi                            
  0x0021B646  5e                      pop      esi                            
  0x0021B647  5d                      pop      ebp                            
                                        ; XREF: 0x0021B56B (cond_jump)
  0x0021B648  5b                      pop      ebx                            
  0x0021B649  c3                      ret                                     
; end of function
  0x0021B64A  cc                      int3                                    
  0x0021B64B  cc                      int3                                    
  0x0021B64C  cc                      int3                                    
  0x0021B64D  cc                      int3                                    
  0x0021B64E  cc                      int3                                    
  0x0021B64F  cc                      int3                                    

; ============================================================
; Function: sub_0021B650
; Start: 0x0021B650  End: 0x0021B7A3  Size: 339 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B650:
  0x0021B650  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021B654  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021B658  53                      push     ebx                            
  0x0021B659  55                      push     ebp                            
  0x0021B65A  56                      push     esi                            
  0x0021B65B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021B65F  57                      push     edi                            
                                        ; XREF: 0x0021B798 (cond_jump)
  0x0021B660  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021B666  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021B669  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021B66F  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021B672  c1e102                  shl      ecx, 2                         
  0x0021B675  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x0021B67B  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021B681  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021B687  c1e202                  shl      edx, 2                         
  0x0021B68A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021B690  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021B696  03f7                    add      esi, edi                       
  0x0021B698  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021B69B  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021B6A2  41                      inc      ecx                            
  0x0021B6A3  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021B6A9  8d0c17                  lea      ecx, [edi + edx]               
  0x0021B6AC  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021B6B4  8d2c37                  lea      ebp, [edi + esi]               
  0x0021B6B7  660b0cad90462900        or       cx, word ptr [ebp*4 + 0x294690] 
  0x0021B6BF  03fb                    add      edi, ebx                       
  0x0021B6C1  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021B6C9  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x0021B6CF  0fb62f                  movzx    ebp, byte ptr [edi]            
  0x0021B6D2  660b0cadb05a2900        or       cx, word ptr [ebp*4 + 0x295ab0] 
  0x0021B6DA  47                      inc      edi                            
  0x0021B6DB  893d289f2900            mov      dword ptr [0x299f28], edi      
  0x0021B6E1  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021B6E7  66890f                  mov      word ptr [edi], cx             
  0x0021B6EA  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021B6F0  66894f02                mov      word ptr [edi + 2], cx         
  0x0021B6F4  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021B6FA  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021B6FD  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021B704  41                      inc      ecx                            
  0x0021B705  03d7                    add      edx, edi                       
  0x0021B707  03f7                    add      esi, edi                       
  0x0021B709  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021B70F  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021B717  660b0cb590462900        or       cx, word ptr [esi*4 + 0x294690] 
  0x0021B71F  8b152c9f2900            mov      edx, dword ptr [0x299f2c]      
  0x0021B725  0fb632                  movzx    esi, byte ptr [edx]            
  0x0021B728  03fb                    add      edi, ebx                       
  0x0021B72A  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021B732  660b0cb5b05a2900        or       cx, word ptr [esi*4 + 0x295ab0] 
  0x0021B73A  42                      inc      edx                            
  0x0021B73B  89152c9f2900            mov      dword ptr [0x299f2c], edx      
  0x0021B741  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B747  66890a                  mov      word ptr [edx], cx             
  0x0021B74A  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B750  66894a02                mov      word ptr [edx + 2], cx         
  0x0021B754  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021B75A  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021B760  b904000000              mov      ecx, 4                         
  0x0021B765  03f9                    add      edi, ecx                       
  0x0021B767  03f1                    add      esi, ecx                       
  0x0021B769  40                      inc      eax                            
  0x0021B76A  a801                    test     al, 1                          
  0x0021B76C  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021B772  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021B778  751a                    jne      0x21b794                       
  0x0021B77A  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021B780  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021B786  42                      inc      edx                            
  0x0021B787  41                      inc      ecx                            
  0x0021B788  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021B78E  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021B778 (cond_jump)
  0x0021B794  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021B798  0f85c2feffff            jne      0x21b660                       
  0x0021B79E  5f                      pop      edi                            
  0x0021B79F  5e                      pop      esi                            
  0x0021B7A0  5d                      pop      ebp                            
  0x0021B7A1  5b                      pop      ebx                            
  0x0021B7A2  c3                      ret                                     
; end of function
  0x0021B7A3  cc                      int3                                    
  0x0021B7A4  cc                      int3                                    
  0x0021B7A5  cc                      int3                                    
  0x0021B7A6  cc                      int3                                    
  0x0021B7A7  cc                      int3                                    
  0x0021B7A8  cc                      int3                                    
  0x0021B7A9  cc                      int3                                    
  0x0021B7AA  cc                      int3                                    
  0x0021B7AB  cc                      int3                                    
  0x0021B7AC  cc                      int3                                    
  0x0021B7AD  cc                      int3                                    
  0x0021B7AE  cc                      int3                                    
  0x0021B7AF  cc                      int3                                    

; ============================================================
; Function: sub_0021B7B0
; Start: 0x0021B7B0  End: 0x0021B8BB  Size: 267 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B7B0:
  0x0021B7B0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021B7B4  85c0                    test     eax, eax                       
  0x0021B7B6  53                      push     ebx                            
  0x0021B7B7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021B7BB  0f84f8000000            je       0x21b8b9                       
  0x0021B7C1  55                      push     ebp                            
  0x0021B7C2  56                      push     esi                            
  0x0021B7C3  57                      push     edi                            
  0x0021B7C4  8be8                    mov      ebp, eax                       
  0x0021B7C6  eb08                    jmp      0x21b7d0                       
  0x0021B7C8  8da42400000000          lea      esp, [esp]                     
  0x0021B7CF  90                      nop                                     
                                        ; XREF: 0x0021B7C6 (jump), 0x0021B8B0 (cond_jump)
  0x0021B7D0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021B7D5  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021B7D8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021B7DE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021B7E1  c1e002                  shl      eax, 2                         
  0x0021B7E4  8bb038a72900            mov      esi, dword ptr [eax + 0x29a738] 
  0x0021B7EA  8bb8389f2900            mov      edi, dword ptr [eax + 0x299f38] 
  0x0021B7F0  a1189f2900              mov      eax, dword ptr [0x299f18]      
  0x0021B7F5  c1e102                  shl      ecx, 2                         
  0x0021B7F8  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021B7FE  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021B804  03d6                    add      edx, esi                       
  0x0021B806  0fb630                  movzx    esi, byte ptr [eax]            
  0x0021B809  8b34b570322900          mov      esi, dword ptr [esi*4 + 0x293270] 
  0x0021B810  40                      inc      eax                            
  0x0021B811  a3189f2900              mov      dword ptr [0x299f18], eax      
  0x0021B816  8d040e                  lea      eax, [esi + ecx]               
  0x0021B819  668b0485a0522900        mov      ax, word ptr [eax*4 + 0x2952a0] 
  0x0021B821  8d0c16                  lea      ecx, [esi + edx]               
  0x0021B824  660b048d90462900        or       ax, word ptr [ecx*4 + 0x294690] 
  0x0021B82C  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021B832  0fb611                  movzx    edx, byte ptr [ecx]            
  0x0021B835  03f7                    add      esi, edi                       
  0x0021B837  660b04b5803a2900        or       ax, word ptr [esi*4 + 0x293a80] 
  0x0021B83F  660b0495b05a2900        or       ax, word ptr [edx*4 + 0x295ab0] 
  0x0021B847  41                      inc      ecx                            
  0x0021B848  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021B84E  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B854  668901                  mov      word ptr [ecx], ax             
  0x0021B857  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B85D  66894202                mov      word ptr [edx + 2], ax         
  0x0021B861  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B867  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021B86D  66890411                mov      word ptr [ecx + edx], ax       
  0x0021B871  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021B877  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x0021B87D  6689440a02              mov      word ptr [edx + ecx + 2], ax   
  0x0021B882  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021B888  83c204                  add      edx, 4                         
  0x0021B88B  43                      inc      ebx                            
  0x0021B88C  f6c301                  test     bl, 1                          
  0x0021B88F  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021B895  7518                    jne      0x21b8af                       
  0x0021B897  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021B89D  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021B8A2  41                      inc      ecx                            
  0x0021B8A3  40                      inc      eax                            
  0x0021B8A4  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021B8AA  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021B895 (cond_jump)
  0x0021B8AF  4d                      dec      ebp                            
  0x0021B8B0  0f851affffff            jne      0x21b7d0                       
  0x0021B8B6  5f                      pop      edi                            
  0x0021B8B7  5e                      pop      esi                            
  0x0021B8B8  5d                      pop      ebp                            
                                        ; XREF: 0x0021B7BB (cond_jump)
  0x0021B8B9  5b                      pop      ebx                            
  0x0021B8BA  c3                      ret                                     
; end of function
  0x0021B8BB  cc                      int3                                    
  0x0021B8BC  cc                      int3                                    
  0x0021B8BD  cc                      int3                                    
  0x0021B8BE  cc                      int3                                    
  0x0021B8BF  cc                      int3                                    

; ============================================================
; Function: sub_0021B8C0
; Start: 0x0021B8C0  End: 0x0021BA55  Size: 405 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021B8C0:
  0x0021B8C0  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021B8C4  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021B8C8  53                      push     ebx                            
  0x0021B8C9  55                      push     ebp                            
  0x0021B8CA  56                      push     esi                            
  0x0021B8CB  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021B8CF  57                      push     edi                            
                                        ; XREF: 0x0021BA4A (cond_jump)
  0x0021B8D0  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021B8D6  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021B8D9  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021B8DF  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021B8E2  c1e102                  shl      ecx, 2                         
  0x0021B8E5  8b99389f2900            mov      ebx, dword ptr [ecx + 0x299f38] 
  0x0021B8EB  8bb938a72900            mov      edi, dword ptr [ecx + 0x29a738] 
  0x0021B8F1  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021B8F7  c1e202                  shl      edx, 2                         
  0x0021B8FA  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021B900  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021B906  03f7                    add      esi, edi                       
  0x0021B908  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021B90B  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021B912  41                      inc      ecx                            
  0x0021B913  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021B919  8d0c17                  lea      ecx, [edi + edx]               
  0x0021B91C  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021B924  8d2c37                  lea      ebp, [edi + esi]               
  0x0021B927  660b0cad90462900        or       cx, word ptr [ebp*4 + 0x294690] 
  0x0021B92F  03fb                    add      edi, ebx                       
  0x0021B931  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021B939  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x0021B93F  0fb62f                  movzx    ebp, byte ptr [edi]            
  0x0021B942  660b0cadb05a2900        or       cx, word ptr [ebp*4 + 0x295ab0] 
  0x0021B94A  47                      inc      edi                            
  0x0021B94B  893d289f2900            mov      dword ptr [0x299f28], edi      
  0x0021B951  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021B957  66890f                  mov      word ptr [edi], cx             
  0x0021B95A  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021B960  66894f02                mov      word ptr [edi + 2], cx         
  0x0021B964  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x0021B96A  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x0021B970  66890c2f                mov      word ptr [edi + ebp], cx       
  0x0021B974  8b3d309f2900            mov      edi, dword ptr [0x299f30]      
  0x0021B97A  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x0021B980  66894c2f02              mov      word ptr [edi + ebp + 2], cx   
  0x0021B985  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x0021B98B  0fb639                  movzx    edi, byte ptr [ecx]            
  0x0021B98E  8b3cbd70322900          mov      edi, dword ptr [edi*4 + 0x293270] 
  0x0021B995  03d7                    add      edx, edi                       
  0x0021B997  41                      inc      ecx                            
  0x0021B998  03f7                    add      esi, edi                       
  0x0021B99A  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x0021B9A0  668b0c95a0522900        mov      cx, word ptr [edx*4 + 0x2952a0] 
  0x0021B9A8  660b0cb590462900        or       cx, word ptr [esi*4 + 0x294690] 
  0x0021B9B0  8b152c9f2900            mov      edx, dword ptr [0x299f2c]      
  0x0021B9B6  0fb632                  movzx    esi, byte ptr [edx]            
  0x0021B9B9  03fb                    add      edi, ebx                       
  0x0021B9BB  660b0cbd803a2900        or       cx, word ptr [edi*4 + 0x293a80] 
  0x0021B9C3  660b0cb5b05a2900        or       cx, word ptr [esi*4 + 0x295ab0] 
  0x0021B9CB  42                      inc      edx                            
  0x0021B9CC  89152c9f2900            mov      dword ptr [0x299f2c], edx      
  0x0021B9D2  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B9D8  66890a                  mov      word ptr [edx], cx             
  0x0021B9DB  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B9E1  66894a02                mov      word ptr [edx + 2], cx         
  0x0021B9E5  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B9EB  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x0021B9F1  66890c32                mov      word ptr [edx + esi], cx       
  0x0021B9F5  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x0021B9FB  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x0021BA01  66894c3202              mov      word ptr [edx + esi + 2], cx   
  0x0021BA06  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021BA0C  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021BA12  b904000000              mov      ecx, 4                         
  0x0021BA17  03f9                    add      edi, ecx                       
  0x0021BA19  03f1                    add      esi, ecx                       
  0x0021BA1B  40                      inc      eax                            
  0x0021BA1C  a801                    test     al, 1                          
  0x0021BA1E  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021BA24  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021BA2A  751a                    jne      0x21ba46                       
  0x0021BA2C  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021BA32  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021BA38  42                      inc      edx                            
  0x0021BA39  41                      inc      ecx                            
  0x0021BA3A  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021BA40  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021BA2A (cond_jump)
  0x0021BA46  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021BA4A  0f8580feffff            jne      0x21b8d0                       
  0x0021BA50  5f                      pop      edi                            
  0x0021BA51  5e                      pop      esi                            
  0x0021BA52  5d                      pop      ebp                            
  0x0021BA53  5b                      pop      ebx                            
  0x0021BA54  c3                      ret                                     
; end of function
  0x0021BA55  cc                      int3                                    
  0x0021BA56  cc                      int3                                    
  0x0021BA57  cc                      int3                                    
  0x0021BA58  cc                      int3                                    
  0x0021BA59  cc                      int3                                    
  0x0021BA5A  cc                      int3                                    
  0x0021BA5B  cc                      int3                                    
  0x0021BA5C  cc                      int3                                    
  0x0021BA5D  cc                      int3                                    
  0x0021BA5E  cc                      int3                                    
  0x0021BA5F  cc                      int3                                    

; ============================================================
; Function: sub_0021BA60
; Start: 0x0021BA60  End: 0x0021BABE  Size: 94 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021BA60:
  0x0021BA60  56                      push     esi                            
  0x0021BA61  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x0021BA65  85f6                    test     esi, esi                       
  0x0021BA67  7453                    je       0x21babc                       
  0x0021BA69  57                      push     edi                            
  0x0021BA6A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021BAB9 (cond_jump)
  0x0021BA70  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021BA76  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021BA79  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021BA7F  0fb63a                  movzx    edi, byte ptr [edx]            
  0x0021BA82  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021BA8A  660b04bd10932900        or       ax, word ptr [edi*4 + 0x299310] 
  0x0021BA92  41                      inc      ecx                            
  0x0021BA93  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021BA99  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021BA9F  42                      inc      edx                            
  0x0021BAA0  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021BAA6  668901                  mov      word ptr [ecx], ax             
  0x0021BAA9  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021BAAF  83c102                  add      ecx, 2                         
  0x0021BAB2  4e                      dec      esi                            
  0x0021BAB3  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021BAB9  75b5                    jne      0x21ba70                       
  0x0021BABB  5f                      pop      edi                            
                                        ; XREF: 0x0021BA67 (cond_jump)
  0x0021BABC  5e                      pop      esi                            
  0x0021BABD  c3                      ret                                     
; end of function
  0x0021BABE  cc                      int3                                    
  0x0021BABF  cc                      int3                                    

; ============================================================
; Function: sub_0021BAC0
; Start: 0x0021BAC0  End: 0x0021BB71  Size: 177 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021BAC0:
  0x0021BAC0  53                      push     ebx                            
  0x0021BAC1  55                      push     ebp                            
  0x0021BAC2  56                      push     esi                            
  0x0021BAC3  57                      push     edi                            
  0x0021BAC4  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x0021BAC8  8bf7                    mov      esi, edi                       
  0x0021BACA  bb02000000              mov      ebx, 2                         
  0x0021BACF  90                      nop                                     
                                        ; XREF: 0x0021BB5F (cond_jump)
  0x0021BAD0  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021BAD6  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021BAD9  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021BADF  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021BAE2  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021BAEA  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021BAF2  41                      inc      ecx                            
  0x0021BAF3  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021BAF9  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021BAFF  42                      inc      edx                            
  0x0021BB00  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021BB06  668901                  mov      word ptr [ecx], ax             
  0x0021BB09  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021BB0F  0fb601                  movzx    eax, byte ptr [ecx]            
  0x0021BB12  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021BB18  0fb62a                  movzx    ebp, byte ptr [edx]            
  0x0021BB1B  668b0485b05a2900        mov      ax, word ptr [eax*4 + 0x295ab0] 
  0x0021BB23  660b04ad10932900        or       ax, word ptr [ebp*4 + 0x299310] 
  0x0021BB2B  41                      inc      ecx                            
  0x0021BB2C  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021BB32  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021BB38  42                      inc      edx                            
  0x0021BB39  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021BB3F  668901                  mov      word ptr [ecx], ax             
  0x0021BB42  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021BB48  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021BB4E  03d3                    add      edx, ebx                       
  0x0021BB50  03cb                    add      ecx, ebx                       
  0x0021BB52  4e                      dec      esi                            
  0x0021BB53  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021BB59  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x0021BB5F  0f856bffffff            jne      0x21bad0                       
  0x0021BB65  8b542418                mov      edx, dword ptr [esp + 0x18]    
  0x0021BB69  8d0417                  lea      eax, [edi + edx]               
  0x0021BB6C  5f                      pop      edi                            
  0x0021BB6D  5e                      pop      esi                            
  0x0021BB6E  5d                      pop      ebp                            
  0x0021BB6F  5b                      pop      ebx                            
  0x0021BB70  c3                      ret                                     
; end of function
  0x0021BB71  cc                      int3                                    
  0x0021BB72  cc                      int3                                    
  0x0021BB73  cc                      int3                                    
  0x0021BB74  cc                      int3                                    
  0x0021BB75  cc                      int3                                    
  0x0021BB76  cc                      int3                                    
  0x0021BB77  cc                      int3                                    
  0x0021BB78  cc                      int3                                    
  0x0021BB79  cc                      int3                                    
  0x0021BB7A  cc                      int3                                    
  0x0021BB7B  cc                      int3                                    
  0x0021BB7C  cc                      int3                                    
  0x0021BB7D  cc                      int3                                    
  0x0021BB7E  cc                      int3                                    
  0x0021BB7F  cc                      int3                                    

; ============================================================
; Function: sub_0021BB80
; Start: 0x0021BB80  End: 0x0021BC66  Size: 230 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021BB80:
  0x0021BB80  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021BB84  85c0                    test     eax, eax                       
  0x0021BB86  53                      push     ebx                            
  0x0021BB87  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021BB8B  0f84d3000000            je       0x21bc64                       
  0x0021BB91  55                      push     ebp                            
  0x0021BB92  56                      push     esi                            
  0x0021BB93  57                      push     edi                            
  0x0021BB94  8be8                    mov      ebp, eax                       
  0x0021BB96  eb08                    jmp      0x21bba0                       
  0x0021BB98  8da42400000000          lea      esp, [esp]                     
  0x0021BB9F  90                      nop                                     
                                        ; XREF: 0x0021BB96 (jump), 0x0021BC5B (cond_jump)
  0x0021BBA0  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x0021BBA5  0fb600                  movzx    eax, byte ptr [eax]            
  0x0021BBA8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021BBAE  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021BBB1  c1e102                  shl      ecx, 2                         
  0x0021BBB4  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x0021BBBA  8b8938ab2900            mov      ecx, dword ptr [ecx + 0x29ab38] 
  0x0021BBC0  c1e002                  shl      eax, 2                         
  0x0021BBC3  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x0021BBC9  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x0021BBCF  03d7                    add      edx, edi                       
  0x0021BBD1  8b3d189f2900            mov      edi, dword ptr [0x299f18]      
  0x0021BBD7  0fb607                  movzx    eax, byte ptr [edi]            
  0x0021BBDA  8b048570322900          mov      eax, dword ptr [eax*4 + 0x293270] 
  0x0021BBE1  03c8                    add      ecx, eax                       
  0x0021BBE3  668b0c8da0522900        mov      cx, word ptr [ecx*4 + 0x2952a0] 
  0x0021BBEB  03d0                    add      edx, eax                       
  0x0021BBED  660b0c9590462900        or       cx, word ptr [edx*4 + 0x294690] 
  0x0021BBF5  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x0021BBFB  03c6                    add      eax, esi                       
  0x0021BBFD  660b0c85803a2900        or       cx, word ptr [eax*4 + 0x293a80] 
  0x0021BC05  47                      inc      edi                            
  0x0021BC06  893d189f2900            mov      dword ptr [0x299f18], edi      
  0x0021BC0C  0fb602                  movzx    eax, byte ptr [edx]            
  0x0021BC0F  660b0c85b05a2900        or       cx, word ptr [eax*4 + 0x295ab0] 
  0x0021BC17  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021BC1D  66890a                  mov      word ptr [edx], cx             
  0x0021BC20  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x0021BC26  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021BC2C  46                      inc      esi                            
  0x0021BC2D  83c202                  add      edx, 2                         
  0x0021BC30  43                      inc      ebx                            
  0x0021BC31  f6c301                  test     bl, 1                          
  0x0021BC34  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021BC3A  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021BC40  7518                    jne      0x21bc5a                       
  0x0021BC42  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021BC48  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021BC4D  41                      inc      ecx                            
  0x0021BC4E  40                      inc      eax                            
  0x0021BC4F  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x0021BC55  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x0021BC40 (cond_jump)
  0x0021BC5A  4d                      dec      ebp                            
  0x0021BC5B  0f853fffffff            jne      0x21bba0                       
  0x0021BC61  5f                      pop      edi                            
  0x0021BC62  5e                      pop      esi                            
  0x0021BC63  5d                      pop      ebp                            
                                        ; XREF: 0x0021BB8B (cond_jump)
  0x0021BC64  5b                      pop      ebx                            
  0x0021BC65  c3                      ret                                     
; end of function
  0x0021BC66  cc                      int3                                    
  0x0021BC67  cc                      int3                                    
  0x0021BC68  cc                      int3                                    
  0x0021BC69  cc                      int3                                    
  0x0021BC6A  cc                      int3                                    
  0x0021BC6B  cc                      int3                                    
  0x0021BC6C  cc                      int3                                    
  0x0021BC6D  cc                      int3                                    
  0x0021BC6E  cc                      int3                                    
  0x0021BC6F  cc                      int3                                    

; ============================================================
; Function: sub_0021BC70
; Start: 0x0021BC70  End: 0x0021BDBB  Size: 331 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021BC70:
  0x0021BC70  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x0021BC74  8b442408                mov      eax, dword ptr [esp + 8]       
  0x0021BC78  53                      push     ebx                            
  0x0021BC79  55                      push     ebp                            
  0x0021BC7A  56                      push     esi                            
  0x0021BC7B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021BC7F  57                      push     edi                            
                                        ; XREF: 0x0021BDB0 (cond_jump)
  0x0021BC80  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021BC86  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x0021BC89  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021BC8F  0fb612                  movzx    edx, byte ptr [edx]            
  0x0021BC92  c1e102                  shl      ecx, 2                         
  0x0021BC95  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x0021BC9B  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x0021BCA1  c1e202                  shl      edx, 2                         
  0x0021BCA4  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x0021BCAA  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x0021BCB0  03f3                    add      esi, ebx                       
  0x0021BCB2  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x0021BCB8  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021BCBB  8b0c8d70322900          mov      ecx, dword ptr [ecx*4 + 0x293270] 
  0x0021BCC2  43                      inc      ebx                            
  0x0021BCC3  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x0021BCC9  8d1c11                  lea      ebx, [ecx + edx]               
  0x0021BCCC  668b1c9da0522900        mov      bx, word ptr [ebx*4 + 0x2952a0] 
  0x0021BCD4  8d2c31                  lea      ebp, [ecx + esi]               
  0x0021BCD7  660b1cad90462900        or       bx, word ptr [ebp*4 + 0x294690] 
  0x0021BCDF  03cf                    add      ecx, edi                       
  0x0021BCE1  660b1c8d803a2900        or       bx, word ptr [ecx*4 + 0x293a80] 
  0x0021BCE9  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021BCEF  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021BCF2  660b1c8db05a2900        or       bx, word ptr [ecx*4 + 0x295ab0] 
  0x0021BCFA  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021BD00  668919                  mov      word ptr [ecx], bx             
  0x0021BD03  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021BD09  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x0021BD0F  41                      inc      ecx                            
  0x0021BD10  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021BD16  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021BD19  8b0c8d70322900          mov      ecx, dword ptr [ecx*4 + 0x293270] 
  0x0021BD20  03d1                    add      edx, ecx                       
  0x0021BD22  668b1495a0522900        mov      dx, word ptr [edx*4 + 0x2952a0] 
  0x0021BD2A  03f1                    add      esi, ecx                       
  0x0021BD2C  660b14b590462900        or       dx, word ptr [esi*4 + 0x294690] 
  0x0021BD34  03cf                    add      ecx, edi                       
  0x0021BD36  660b148d803a2900        or       dx, word ptr [ecx*4 + 0x293a80] 
  0x0021BD3E  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021BD44  43                      inc      ebx                            
  0x0021BD45  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x0021BD4B  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x0021BD4E  660b148db05a2900        or       dx, word ptr [ecx*4 + 0x295ab0] 
  0x0021BD56  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x0021BD5C  668911                  mov      word ptr [ecx], dx             
  0x0021BD5F  8b1d2c9f2900            mov      ebx, dword ptr [0x299f2c]      
  0x0021BD65  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021BD6B  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021BD71  b902000000              mov      ecx, 2                         
  0x0021BD76  43                      inc      ebx                            
  0x0021BD77  03f9                    add      edi, ecx                       
  0x0021BD79  03f1                    add      esi, ecx                       
  0x0021BD7B  40                      inc      eax                            
  0x0021BD7C  a801                    test     al, 1                          
  0x0021BD7E  891d2c9f2900            mov      dword ptr [0x299f2c], ebx      
  0x0021BD84  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021BD8A  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021BD90  751a                    jne      0x21bdac                       
  0x0021BD92  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x0021BD98  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021BD9E  42                      inc      edx                            
  0x0021BD9F  41                      inc      ecx                            
  0x0021BDA0  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x0021BDA6  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021BD90 (cond_jump)
  0x0021BDAC  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021BDB0  0f85cafeffff            jne      0x21bc80                       
  0x0021BDB6  5f                      pop      edi                            
  0x0021BDB7  5e                      pop      esi                            
  0x0021BDB8  5d                      pop      ebp                            
  0x0021BDB9  5b                      pop      ebx                            
  0x0021BDBA  c3                      ret                                     
; end of function
  0x0021BDBB  cc                      int3                                    
  0x0021BDBC  cc                      int3                                    
  0x0021BDBD  cc                      int3                                    
  0x0021BDBE  cc                      int3                                    
  0x0021BDBF  cc                      int3                                    

; ============================================================
; Function: sub_0021BDC0
; Start: 0x0021BDC0  End: 0x0021BE10  Size: 80 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214310
; Called by: sub_0020C030
; ============================================================
sub_0021BDC0:
  0x0021BDC0  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021BDC4  8b4c2434                mov      ecx, dword ptr [esp + 0x34]    
  0x0021BDC8  8b54242c                mov      edx, dword ptr [esp + 0x2c]    
  0x0021BDCC  68e0c12900              push     0x29c1e0                       
  0x0021BDD1  50                      push     eax                            
  0x0021BDD2  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021BDD6  51                      push     ecx                            
  0x0021BDD7  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021BDDB  52                      push     edx                            
  0x0021BDDC  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021BDE0  50                      push     eax                            
  0x0021BDE1  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021BDE5  51                      push     ecx                            
  0x0021BDE6  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021BDEA  52                      push     edx                            
  0x0021BDEB  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021BDEF  50                      push     eax                            
  0x0021BDF0  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x0021BDF4  51                      push     ecx                            
  0x0021BDF5  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021BDF9  52                      push     edx                            
  0x0021BDFA  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021BDFE  50                      push     eax                            
  0x0021BDFF  51                      push     ecx                            
  0x0021BE00  52                      push     edx                            
  0x0021BE01  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021BE05  e80685ffff              call     0x214310                       ; -> sub_00214310
  0x0021BE0A  83c434                  add      esp, 0x34                      
  0x0021BE0D  c23400                  ret      0x34                           
; end of function

; ============================================================
; Function: sub_0021BE10
; Start: 0x0021BE10  End: 0x0021BE6B  Size: 91 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214790
; Called by: sub_0020C030
; ============================================================
sub_0021BE10:
  0x0021BE10  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021BE14  8b4c243c                mov      ecx, dword ptr [esp + 0x3c]    
  0x0021BE18  8b542434                mov      edx, dword ptr [esp + 0x34]    
  0x0021BE1C  68e0c12900              push     0x29c1e0                       
  0x0021BE21  50                      push     eax                            
  0x0021BE22  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021BE26  51                      push     ecx                            
  0x0021BE27  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021BE2B  52                      push     edx                            
  0x0021BE2C  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021BE30  50                      push     eax                            
  0x0021BE31  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021BE35  51                      push     ecx                            
  0x0021BE36  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021BE3A  52                      push     edx                            
  0x0021BE3B  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021BE3F  50                      push     eax                            
  0x0021BE40  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021BE44  51                      push     ecx                            
  0x0021BE45  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021BE49  52                      push     edx                            
  0x0021BE4A  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021BE4E  50                      push     eax                            
  0x0021BE4F  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x0021BE53  51                      push     ecx                            
  0x0021BE54  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021BE58  52                      push     edx                            
  0x0021BE59  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021BE5D  50                      push     eax                            
  0x0021BE5E  51                      push     ecx                            
  0x0021BE5F  52                      push     edx                            
  0x0021BE60  e82b89ffff              call     0x214790                       ; -> sub_00214790
  0x0021BE65  83c440                  add      esp, 0x40                      
  0x0021BE68  c23c00                  ret      0x3c                           
; end of function
  0x0021BE6B  cc                      int3                                    
  0x0021BE6C  cc                      int3                                    
  0x0021BE6D  cc                      int3                                    
  0x0021BE6E  cc                      int3                                    
  0x0021BE6F  cc                      int3                                    

; ============================================================
; Function: sub_0021BE70
; Start: 0x0021BE70  End: 0x0021C0C6  Size: 598 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_0021BE70:
  0x0021BE70  53                      push     ebx                            
  0x0021BE71  55                      push     ebp                            
  0x0021BE72  56                      push     esi                            
  0x0021BE73  57                      push     edi                            
  0x0021BE74  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021BE7A  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021BE80  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021BE86  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021BE8C  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021BE92  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021BE96  c1e003                  shl      eax, 3                         
  0x0021BE99  03c7                    add      eax, edi                       
  0x0021BE9B  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021BEA0  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021BEA7  8da42400000000          lea      esp, [esp]                     
  0x0021BEAE  8bff                    mov      edi, edi                       
                                        ; XREF: 0x0021BF81 (cond_jump)
  0x0021BEB0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021BEB3  0fefc0                  pxor     mm0, mm0                       
  0x0021BEB6  33c0                    xor      eax, eax                       
  0x0021BEB8  83c204                  add      edx, 4                         
  0x0021BEBB  8a4500                  mov      al, byte ptr [ebp]             
  0x0021BEBE  0f60e0                  punpcklbw mm4, mm0                       
  0x0021BEC1  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021BEC9  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021BED1  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021BED4  83c502                  add      ebp, 2                         
  0x0021BED7  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021BEDE  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021BEE6  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021BEEE  8a03                    mov      al, byte ptr [ebx]             
  0x0021BEF0  0f71f402                psllw    mm4, 2                         
  0x0021BEF4  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021BEFB  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021BF03  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021BF0B  0ffdd5                  paddw    mm2, mm5                       
  0x0021BF0E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021BF11  83c302                  add      ebx, 2                         
  0x0021BF14  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021BF1C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021BF24  0ffdf5                  paddw    mm6, mm5                       
  0x0021BF27  0f62d6                  punpckldq mm2, mm6                       
  0x0021BF2A  0ffdcc                  paddw    mm1, mm4                       
  0x0021BF2D  0ffdd4                  paddw    mm2, mm4                       
  0x0021BF30  0fedcf                  paddsw   mm1, mm7                       
  0x0021BF33  0ffddc                  paddw    mm3, mm4                       
  0x0021BF36  0fd9cf                  psubusw  mm1, mm7                       
  0x0021BF39  0f71d104                psrlw    mm1, 4                         
  0x0021BF3D  0fedd7                  paddsw   mm2, mm7                       
  0x0021BF40  0f6e31                  movd     mm6, dword ptr [ecx]           
  0x0021BF43  0fd9d7                  psubusw  mm2, mm7                       
  0x0021BF46  0f71d204                psrlw    mm2, 4                         
  0x0021BF4A  0feddf                  paddsw   mm3, mm7                       
  0x0021BF4D  0f71f204                psllw    mm2, 4                         
  0x0021BF51  0fd9df                  psubusw  mm3, mm7                       
  0x0021BF54  0f71d304                psrlw    mm3, 4                         
  0x0021BF58  0febca                  por      mm1, mm2                       
  0x0021BF5B  0f71f308                psllw    mm3, 8                         
  0x0021BF5F  0f60f0                  punpcklbw mm6, mm0                       
  0x0021BF62  0febcb                  por      mm1, mm3                       
  0x0021BF65  0f71d604                psrlw    mm6, 4                         
  0x0021BF69  0f71f60c                psllw    mm6, 0xc                       
  0x0021BF6D  83c708                  add      edi, 8                         
  0x0021BF70  0febce                  por      mm1, mm6                       
  0x0021BF73  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021BF78  83c104                  add      ecx, 4                         
  0x0021BF7B  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021BF7F  3bf8                    cmp      edi, eax                       
  0x0021BF81  0f8229ffffff            jb       0x21beb0                       
  0x0021BF87  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021BF8D  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021BF93  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021BF99  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021BF9F  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021BFA5  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021BFAB  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021BFB1  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021BFB5  c1e003                  shl      eax, 3                         
  0x0021BFB8  03c7                    add      eax, edi                       
  0x0021BFBA  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021BFBF  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021BFC6  8da42400000000          lea      esp, [esp]                     
  0x0021BFCD  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021C0A1 (cond_jump)
  0x0021BFD0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021BFD3  0fefc0                  pxor     mm0, mm0                       
  0x0021BFD6  33c0                    xor      eax, eax                       
  0x0021BFD8  83c204                  add      edx, 4                         
  0x0021BFDB  8a4500                  mov      al, byte ptr [ebp]             
  0x0021BFDE  0f60e0                  punpcklbw mm4, mm0                       
  0x0021BFE1  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021BFE9  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021BFF1  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021BFF4  83c502                  add      ebp, 2                         
  0x0021BFF7  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021BFFE  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021C006  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021C00E  8a03                    mov      al, byte ptr [ebx]             
  0x0021C010  0f71f402                psllw    mm4, 2                         
  0x0021C014  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021C01B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021C023  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021C02B  0ffdd5                  paddw    mm2, mm5                       
  0x0021C02E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021C031  83c302                  add      ebx, 2                         
  0x0021C034  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021C03C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021C044  0ffdf5                  paddw    mm6, mm5                       
  0x0021C047  0f62d6                  punpckldq mm2, mm6                       
  0x0021C04A  0ffdcc                  paddw    mm1, mm4                       
  0x0021C04D  0ffdd4                  paddw    mm2, mm4                       
  0x0021C050  0fedcf                  paddsw   mm1, mm7                       
  0x0021C053  0ffddc                  paddw    mm3, mm4                       
  0x0021C056  0fd9cf                  psubusw  mm1, mm7                       
  0x0021C059  0f71d104                psrlw    mm1, 4                         
  0x0021C05D  0fedd7                  paddsw   mm2, mm7                       
  0x0021C060  0f6e31                  movd     mm6, dword ptr [ecx]           
  0x0021C063  0fd9d7                  psubusw  mm2, mm7                       
  0x0021C066  0f71d204                psrlw    mm2, 4                         
  0x0021C06A  0feddf                  paddsw   mm3, mm7                       
  0x0021C06D  0f71f204                psllw    mm2, 4                         
  0x0021C071  0fd9df                  psubusw  mm3, mm7                       
  0x0021C074  0f71d304                psrlw    mm3, 4                         
  0x0021C078  0febca                  por      mm1, mm2                       
  0x0021C07B  0f71f308                psllw    mm3, 8                         
  0x0021C07F  0f60f0                  punpcklbw mm6, mm0                       
  0x0021C082  0febcb                  por      mm1, mm3                       
  0x0021C085  0f71d604                psrlw    mm6, 4                         
  0x0021C089  0f71f60c                psllw    mm6, 0xc                       
  0x0021C08D  83c708                  add      edi, 8                         
  0x0021C090  0febce                  por      mm1, mm6                       
  0x0021C093  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021C098  83c104                  add      ecx, 4                         
  0x0021C09B  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021C09F  3bf8                    cmp      edi, eax                       
  0x0021C0A1  0f8229ffffff            jb       0x21bfd0                       
  0x0021C0A7  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021C0AD  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021C0B3  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021C0B9  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021C0BF  5f                      pop      edi                            
  0x0021C0C0  5e                      pop      esi                            
  0x0021C0C1  5d                      pop      ebp                            
  0x0021C0C2  5b                      pop      ebx                            
  0x0021C0C3  c20400                  ret      4                              
; end of function
  0x0021C0C6  8da42400000000          lea      esp, [esp]                     
  0x0021C0CD  8d4900                  lea      ecx, [ecx]                     
  0x0021C0D0  53                      push     ebx                            
  0x0021C0D1  55                      push     ebp                            
  0x0021C0D2  56                      push     esi                            
  0x0021C0D3  57                      push     edi                            
  0x0021C0D4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021C0DA  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021C0E0  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021C0E6  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021C0EC  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x0021C0F2  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021C0F6  c1e003                  shl      eax, 3                         
  0x0021C0F9  03c7                    add      eax, edi                       
  0x0021C0FB  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021C100  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021C107  8da42400000000          lea      esp, [esp]                     
  0x0021C10E  8bff                    mov      edi, edi                       
                                        ; XREF: 0x0021C22A (cond_jump)
  0x0021C110  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021C113  0fefc0                  pxor     mm0, mm0                       
  0x0021C116  33c0                    xor      eax, eax                       
  0x0021C118  83c204                  add      edx, 4                         
  0x0021C11B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021C11E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021C121  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021C129  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021C131  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021C134  83c502                  add      ebp, 2                         
  0x0021C137  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021C13E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021C146  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021C14E  8a03                    mov      al, byte ptr [ebx]             
  0x0021C150  0f71f402                psllw    mm4, 2                         
  0x0021C154  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021C15B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021C163  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021C16B  0ffdd5                  paddw    mm2, mm5                       
  0x0021C16E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021C171  83c302                  add      ebx, 2                         
  0x0021C174  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021C17C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021C184  0ffdf5                  paddw    mm6, mm5                       
  0x0021C187  8a4500                  mov      al, byte ptr [ebp]             
  0x0021C18A  0f62d6                  punpckldq mm2, mm6                       
  0x0021C18D  0f73d110                psrlq    mm1, 0x10                      
  0x0021C191  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021C199  0f73d210                psrlq    mm2, 0x10                      
  0x0021C19D  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021C1A5  0f73d310                psrlq    mm3, 0x10                      
  0x0021C1A9  8a03                    mov      al, byte ptr [ebx]             
  0x0021C1AB  0f73f630                psllq    mm6, 0x30                      
  0x0021C1AF  0febce                  por      mm1, mm6                       
  0x0021C1B2  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021C1BA  0ffdee                  paddw    mm5, mm6                       
  0x0021C1BD  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021C1C5  0f73f530                psllq    mm5, 0x30                      
  0x0021C1C9  0f73f630                psllq    mm6, 0x30                      
  0x0021C1CD  0febd5                  por      mm2, mm5                       
  0x0021C1D0  0febde                  por      mm3, mm6                       
  0x0021C1D3  0ffdcc                  paddw    mm1, mm4                       
  0x0021C1D6  0ffdd4                  paddw    mm2, mm4                       
  0x0021C1D9  0fedcf                  paddsw   mm1, mm7                       
  0x0021C1DC  0ffddc                  paddw    mm3, mm4                       
  0x0021C1DF  0fd9cf                  psubusw  mm1, mm7                       
  0x0021C1E2  0f71d104                psrlw    mm1, 4                         
  0x0021C1E6  0fedd7                  paddsw   mm2, mm7                       
  0x0021C1E9  0f6e31                  movd     mm6, dword ptr [ecx]           
  0x0021C1EC  0fd9d7                  psubusw  mm2, mm7                       
  0x0021C1EF  0f71d204                psrlw    mm2, 4                         
  0x0021C1F3  0feddf                  paddsw   mm3, mm7                       
  0x0021C1F6  0f71f204                psllw    mm2, 4                         
  0x0021C1FA  0fd9df                  psubusw  mm3, mm7                       
  0x0021C1FD  0f71d304                psrlw    mm3, 4                         
  0x0021C201  0febca                  por      mm1, mm2                       
  0x0021C204  0f71f308                psllw    mm3, 8                         
  0x0021C208  0f60f0                  punpcklbw mm6, mm0                       
  0x0021C20B  0febcb                  por      mm1, mm3                       
  0x0021C20E  0f71d604                psrlw    mm6, 4                         
  0x0021C212  0f71f60c                psllw    mm6, 0xc                       
  0x0021C216  83c708                  add      edi, 8                         
  0x0021C219  0febce                  por      mm1, mm6                       
  0x0021C21C  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021C221  83c104                  add      ecx, 4                         
  0x0021C224  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021C228  3bf8                    cmp      edi, eax                       
  0x0021C22A  0f82e0feffff            jb       0x21c110                       
  0x0021C230  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021C236  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x0021C23C  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021C242  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021C248  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021C24E  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021C254  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x0021C25A  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021C25E  c1e003                  shl      eax, 3                         
  0x0021C261  03c7                    add      eax, edi                       
  0x0021C263  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021C268  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021C26F  90                      nop                                     
                                        ; XREF: 0x0021C38A (cond_jump)
  0x0021C270  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021C273  0fefc0                  pxor     mm0, mm0                       
  0x0021C276  33c0                    xor      eax, eax                       
  0x0021C278  83c204                  add      edx, 4                         
  0x0021C27B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021C27E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021C281  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021C289  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021C291  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021C294  83c502                  add      ebp, 2                         
  0x0021C297  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021C29E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021C2A6  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021C2AE  8a03                    mov      al, byte ptr [ebx]             
  0x0021C2B0  0f71f402                psllw    mm4, 2                         
  0x0021C2B4  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021C2BB  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021C2C3  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021C2CB  0ffdd5                  paddw    mm2, mm5                       
  0x0021C2CE  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021C2D1  83c302                  add      ebx, 2                         
  0x0021C2D4  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021C2DC  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021C2E4  0ffdf5                  paddw    mm6, mm5                       
  0x0021C2E7  8a4500                  mov      al, byte ptr [ebp]             
  0x0021C2EA  0f62d6                  punpckldq mm2, mm6                       
  0x0021C2ED  0f73d110                psrlq    mm1, 0x10                      
  0x0021C2F1  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021C2F9  0f73d210                psrlq    mm2, 0x10                      
  0x0021C2FD  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021C305  0f73d310                psrlq    mm3, 0x10                      
  0x0021C309  8a03                    mov      al, byte ptr [ebx]             
  0x0021C30B  0f73f630                psllq    mm6, 0x30                      
  0x0021C30F  0febce                  por      mm1, mm6                       
  0x0021C312  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021C31A  0ffdee                  paddw    mm5, mm6                       
  0x0021C31D  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021C325  0f73f530                psllq    mm5, 0x30                      
  0x0021C329  0f73f630                psllq    mm6, 0x30                      
  0x0021C32D  0febd5                  por      mm2, mm5                       
  0x0021C330  0febde                  por      mm3, mm6                       
  0x0021C333  0ffdcc                  paddw    mm1, mm4                       
  0x0021C336  0ffdd4                  paddw    mm2, mm4                       
  0x0021C339  0fedcf                  paddsw   mm1, mm7                       
  0x0021C33C  0ffddc                  paddw    mm3, mm4                       
  0x0021C33F  0fd9cf                  psubusw  mm1, mm7                       
  0x0021C342  0f71d104                psrlw    mm1, 4                         
  0x0021C346  0fedd7                  paddsw   mm2, mm7                       
  0x0021C349  0f6e31                  movd     mm6, dword ptr [ecx]           
  0x0021C34C  0fd9d7                  psubusw  mm2, mm7                       
  0x0021C34F  0f71d204                psrlw    mm2, 4                         
  0x0021C353  0feddf                  paddsw   mm3, mm7                       
  0x0021C356  0f71f204                psllw    mm2, 4                         
  0x0021C35A  0fd9df                  psubusw  mm3, mm7                       
  0x0021C35D  0f71d304                psrlw    mm3, 4                         
  0x0021C361  0febca                  por      mm1, mm2                       
  0x0021C364  0f71f308                psllw    mm3, 8                         
  0x0021C368  0f60f0                  punpcklbw mm6, mm0                       
  0x0021C36B  0febcb                  por      mm1, mm3                       
  0x0021C36E  0f71d604                psrlw    mm6, 4                         
  0x0021C372  0f71f60c                psllw    mm6, 0xc                       
  0x0021C376  83c708                  add      edi, 8                         
  0x0021C379  0febce                  por      mm1, mm6                       
  0x0021C37C  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021C381  83c104                  add      ecx, 4                         
  0x0021C384  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021C388  3bf8                    cmp      edi, eax                       
  0x0021C38A  0f82e0feffff            jb       0x21c270                       
  0x0021C390  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021C396  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021C39C  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021C3A2  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x0021C3A8  5f                      pop      edi                            
  0x0021C3A9  5e                      pop      esi                            
  0x0021C3AA  5d                      pop      ebp                            
  0x0021C3AB  5b                      pop      ebx                            
  0x0021C3AC  c20400                  ret      4                              
