; ============================================================
; Section: BINK16M
; VA: 0x0021EE40 - 0x0021F038
; Size: 504 bytes (0.5 KB)
; Functions: 0
; Instructions: 142
; ============================================================

  0x0021EE40  53                      push     ebx                            
  0x0021EE41  55                      push     ebp                            
  0x0021EE42  56                      push     esi                            
  0x0021EE43  57                      push     edi                            
  0x0021EE44  0f6f3d00a82500          movq     mm7, qword ptr [0x25a800]      
  0x0021EE4B  0f6f05d8a72500          movq     mm0, qword ptr [0x25a7d8]      
  0x0021EE52  0f6f15f0a72500          movq     mm2, qword ptr [0x25a7f0]      
  0x0021EE59  0f6f2df8a72500          movq     mm5, qword ptr [0x25a7f8]      
  0x0021EE60  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x0021EE66  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021EE6C  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021EE70  c1e003                  shl      eax, 3                         
  0x0021EE73  03c6                    add      eax, esi                       
  0x0021EE75  8da42400000000          lea      esp, [esp]                     
  0x0021EE7C  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x0021EEBF (cond_jump)
  0x0021EE80  0f6e19                  movd     mm3, dword ptr [ecx]           
  0x0021EE83  0fefe4                  pxor     mm4, mm4                       
  0x0021EE86  0f6e7104                movd     mm6, dword ptr [ecx + 4]       
  0x0021EE8A  0f60dc                  punpcklbw mm3, mm4                       
  0x0021EE8D  0fd9d8                  psubusw  mm3, mm0                       
  0x0021EE90  0f60f4                  punpcklbw mm6, mm4                       
  0x0021EE93  0fd9f0                  psubusw  mm6, mm0                       
  0x0021EE96  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021EE99  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021EE9C  90                      nop                                     
  0x0021EE9D  83c108                  add      ecx, 8                         
  0x0021EEA0  83c610                  add      esi, 0x10                      
  0x0021EEA3  0feddf                  paddsw   mm3, mm7                       
  0x0021EEA6  0fd9df                  psubusw  mm3, mm7                       
  0x0021EEA9  0fedf7                  paddsw   mm6, mm7                       
  0x0021EEAC  0fd5da                  pmullw   mm3, mm2                       
  0x0021EEAF  0fd9f7                  psubusw  mm6, mm7                       
  0x0021EEB2  0fd5f2                  pmullw   mm6, mm2                       
  0x0021EEB5  0f7f5ef0                movq     qword ptr [esi - 0x10], mm3    
  0x0021EEB9  0f7f76f8                movq     qword ptr [esi - 8], mm6       
  0x0021EEBD  3bf0                    cmp      esi, eax                       
  0x0021EEBF  72bf                    jb       0x21ee80                       
  0x0021EEC1  8935109f2900            mov      dword ptr [0x299f10], esi      
  0x0021EEC7  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021EECD  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021EED3  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021EED9  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021EEDD  c1e003                  shl      eax, 3                         
  0x0021EEE0  03c7                    add      eax, edi                       
  0x0021EEE2  8da42400000000          lea      esp, [esp]                     
  0x0021EEE9  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x0021EF2F (cond_jump)
  0x0021EEF0  0f6e1a                  movd     mm3, dword ptr [edx]           
  0x0021EEF3  0fefe4                  pxor     mm4, mm4                       
  0x0021EEF6  0f6e7204                movd     mm6, dword ptr [edx + 4]       
  0x0021EEFA  0f60dc                  punpcklbw mm3, mm4                       
  0x0021EEFD  0fd9d8                  psubusw  mm3, mm0                       
  0x0021EF00  0f60f4                  punpcklbw mm6, mm4                       
  0x0021EF03  0fd9f0                  psubusw  mm6, mm0                       
  0x0021EF06  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021EF09  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021EF0C  90                      nop                                     
  0x0021EF0D  83c208                  add      edx, 8                         
  0x0021EF10  83c710                  add      edi, 0x10                      
  0x0021EF13  0feddf                  paddsw   mm3, mm7                       
  0x0021EF16  0fd9df                  psubusw  mm3, mm7                       
  0x0021EF19  0fedf7                  paddsw   mm6, mm7                       
  0x0021EF1C  0fd5da                  pmullw   mm3, mm2                       
  0x0021EF1F  0fd9f7                  psubusw  mm6, mm7                       
  0x0021EF22  0fd5f2                  pmullw   mm6, mm2                       
  0x0021EF25  0f7f5ff0                movq     qword ptr [edi - 0x10], mm3    
  0x0021EF29  0f7f77f8                movq     qword ptr [edi - 8], mm6       
  0x0021EF2D  3bf8                    cmp      edi, eax                       
  0x0021EF2F  72bf                    jb       0x21eef0                       
  0x0021EF31  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x0021EF37  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021EF3D  5f                      pop      edi                            
  0x0021EF3E  5e                      pop      esi                            
  0x0021EF3F  5d                      pop      ebp                            
  0x0021EF40  5b                      pop      ebx                            
  0x0021EF41  c20400                  ret      4                              
  0x0021EF44  8da42400000000          lea      esp, [esp]                     
  0x0021EF4B  0500000000              add      eax, 0                         
  0x0021EF50  53                      push     ebx                            
  0x0021EF51  55                      push     ebp                            
  0x0021EF52  56                      push     esi                            
  0x0021EF53  57                      push     edi                            
  0x0021EF54  8b35189f2900            mov      esi, dword ptr [0x299f18]      
  0x0021EF5A  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021EF60  8b6c2414                mov      ebp, dword ptr [esp + 0x14]    
  0x0021EF64  33c0                    xor      eax, eax                       
  0x0021EF66  8da42400000000          lea      esp, [esp]                     
  0x0021EF6D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021EFB2 (cond_jump)
  0x0021EF70  8a06                    mov      al, byte ptr [esi]             
  0x0021EF72  33c9                    xor      ecx, ecx                       
  0x0021EF74  8a4e01                  mov      cl, byte ptr [esi + 1]         
  0x0021EF77  83c708                  add      edi, 8                         
  0x0021EF7A  8b148510932900          mov      edx, dword ptr [eax*4 + 0x299310] 
  0x0021EF81  8a4602                  mov      al, byte ptr [esi + 2]         
  0x0021EF84  8b1c8d10932900          mov      ebx, dword ptr [ecx*4 + 0x299310] 
  0x0021EF8B  8a4e03                  mov      cl, byte ptr [esi + 3]         
  0x0021EF8E  c1e310                  shl      ebx, 0x10                      
  0x0021EF91  8b048510932900          mov      eax, dword ptr [eax*4 + 0x299310] 
  0x0021EF98  8b0c8d10932900          mov      ecx, dword ptr [ecx*4 + 0x299310] 
  0x0021EF9F  0bda                    or       ebx, edx                       
  0x0021EFA1  c1e110                  shl      ecx, 0x10                      
  0x0021EFA4  895ff8                  mov      dword ptr [edi - 8], ebx       
  0x0021EFA7  0bc8                    or       ecx, eax                       
  0x0021EFA9  83c604                  add      esi, 4                         
  0x0021EFAC  894ffc                  mov      dword ptr [edi - 4], ecx       
  0x0021EFAF  33c0                    xor      eax, eax                       
  0x0021EFB1  4d                      dec      ebp                            
  0x0021EFB2  75bc                    jne      0x21ef70                       
  0x0021EFB4  8935189f2900            mov      dword ptr [0x299f18], esi      
  0x0021EFBA  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x0021EFC0  8b351c9f2900            mov      esi, dword ptr [0x299f1c]      
  0x0021EFC6  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021EFCC  8b6c2414                mov      ebp, dword ptr [esp + 0x14]    
  0x0021EFD0  33c0                    xor      eax, eax                       
  0x0021EFD2  8da42400000000          lea      esp, [esp]                     
  0x0021EFD9  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x0021F022 (cond_jump)
  0x0021EFE0  8a06                    mov      al, byte ptr [esi]             
  0x0021EFE2  33c9                    xor      ecx, ecx                       
  0x0021EFE4  8a4e01                  mov      cl, byte ptr [esi + 1]         
  0x0021EFE7  83c708                  add      edi, 8                         
  0x0021EFEA  8b148510932900          mov      edx, dword ptr [eax*4 + 0x299310] 
  0x0021EFF1  8a4602                  mov      al, byte ptr [esi + 2]         
  0x0021EFF4  8b1c8d10932900          mov      ebx, dword ptr [ecx*4 + 0x299310] 
  0x0021EFFB  8a4e03                  mov      cl, byte ptr [esi + 3]         
  0x0021EFFE  c1e310                  shl      ebx, 0x10                      
  0x0021F001  8b048510932900          mov      eax, dword ptr [eax*4 + 0x299310] 
  0x0021F008  8b0c8d10932900          mov      ecx, dword ptr [ecx*4 + 0x299310] 
  0x0021F00F  0bda                    or       ebx, edx                       
  0x0021F011  c1e110                  shl      ecx, 0x10                      
  0x0021F014  895ff8                  mov      dword ptr [edi - 8], ebx       
  0x0021F017  0bc8                    or       ecx, eax                       
  0x0021F019  83c604                  add      esi, 4                         
  0x0021F01C  894ffc                  mov      dword ptr [edi - 4], ecx       
  0x0021F01F  33c0                    xor      eax, eax                       
  0x0021F021  4d                      dec      ebp                            
  0x0021F022  75bc                    jne      0x21efe0                       
  0x0021F024  89351c9f2900            mov      dword ptr [0x299f1c], esi      
  0x0021F02A  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x0021F030  5f                      pop      edi                            
  0x0021F031  5e                      pop      esi                            
  0x0021F032  5d                      pop      ebp                            
  0x0021F033  5b                      pop      ebx                            
  0x0021F034  c20400                  ret      4                              
