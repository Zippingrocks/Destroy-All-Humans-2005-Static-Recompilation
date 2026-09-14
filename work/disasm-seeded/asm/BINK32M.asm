; ============================================================
; Section: BINK32M
; VA: 0x0021F7A0 - 0x0021F8EC
; Size: 332 bytes (0.3 KB)
; Functions: 0
; Instructions: 98
; ============================================================

  0x0021F7A0  53                      push     ebx                            
  0x0021F7A1  55                      push     ebp                            
  0x0021F7A2  56                      push     esi                            
  0x0021F7A3  57                      push     edi                            
  0x0021F7A4  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021F7AB  0f6f05d8a72500          movq     mm0, qword ptr [0x25a7d8]      
  0x0021F7B2  0f6f15c0a72500          movq     mm2, qword ptr [0x25a7c0]      
  0x0021F7B9  0f6f2de0a72500          movq     mm5, qword ptr [0x25a7e0]      
  0x0021F7C0  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x0021F7C6  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021F7CC  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F7D0  c1e004                  shl      eax, 4                         
  0x0021F7D3  03c6                    add      eax, esi                       
  0x0021F7D5  8da42400000000          lea      esp, [esp]                     
  0x0021F7DC  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x0021F847 (cond_jump)
  0x0021F7E0  0f6e19                  movd     mm3, dword ptr [ecx]           
  0x0021F7E3  0fefe4                  pxor     mm4, mm4                       
  0x0021F7E6  0f6e7104                movd     mm6, dword ptr [ecx + 4]       
  0x0021F7EA  0f60dc                  punpcklbw mm3, mm4                       
  0x0021F7ED  0fd9d8                  psubusw  mm3, mm0                       
  0x0021F7F0  0f60f4                  punpcklbw mm6, mm4                       
  0x0021F7F3  0fd9f0                  psubusw  mm6, mm0                       
  0x0021F7F6  0f71f302                psllw    mm3, 2                         
  0x0021F7FA  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021F7FD  0f71f602                psllw    mm6, 2                         
  0x0021F801  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021F804  90                      nop                                     
  0x0021F805  83c108                  add      ecx, 8                         
  0x0021F808  83c620                  add      esi, 0x20                      
  0x0021F80B  0feddf                  paddsw   mm3, mm7                       
  0x0021F80E  0fd9df                  psubusw  mm3, mm7                       
  0x0021F811  0fedf7                  paddsw   mm6, mm7                       
  0x0021F814  0f7fd9                  movq     mm1, mm3                       
  0x0021F817  0f61db                  punpcklwd mm3, mm3                       
  0x0021F81A  0f69c9                  punpckhwd mm1, mm1                       
  0x0021F81D  0fd5da                  pmullw   mm3, mm2                       
  0x0021F820  0fd5ca                  pmullw   mm1, mm2                       
  0x0021F823  0fd9f7                  psubusw  mm6, mm7                       
  0x0021F826  0f7ff4                  movq     mm4, mm6                       
  0x0021F829  0f61f6                  punpcklwd mm6, mm6                       
  0x0021F82C  0f69e4                  punpckhwd mm4, mm4                       
  0x0021F82F  0fd5f2                  pmullw   mm6, mm2                       
  0x0021F832  0f7f5ee0                movq     qword ptr [esi - 0x20], mm3    
  0x0021F836  0fd5e2                  pmullw   mm4, mm2                       
  0x0021F839  0f7f4ee8                movq     qword ptr [esi - 0x18], mm1    
  0x0021F83D  0f7f76f0                movq     qword ptr [esi - 0x10], mm6    
  0x0021F841  0f7f66f8                movq     qword ptr [esi - 8], mm4       
  0x0021F845  3bf0                    cmp      esi, eax                       
  0x0021F847  7297                    jb       0x21f7e0                       
  0x0021F849  8935109f2900            mov      dword ptr [0x299f10], esi      
  0x0021F84F  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021F855  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021F85B  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021F861  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F865  c1e004                  shl      eax, 4                         
  0x0021F868  03c7                    add      eax, edi                       
  0x0021F86A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x0021F8D7 (cond_jump)
  0x0021F870  0f6e1a                  movd     mm3, dword ptr [edx]           
  0x0021F873  0fefe4                  pxor     mm4, mm4                       
  0x0021F876  0f6e7204                movd     mm6, dword ptr [edx + 4]       
  0x0021F87A  0f60dc                  punpcklbw mm3, mm4                       
  0x0021F87D  0fd9d8                  psubusw  mm3, mm0                       
  0x0021F880  0f60f4                  punpcklbw mm6, mm4                       
  0x0021F883  0fd9f0                  psubusw  mm6, mm0                       
  0x0021F886  0f71f302                psllw    mm3, 2                         
  0x0021F88A  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021F88D  0f71f602                psllw    mm6, 2                         
  0x0021F891  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021F894  90                      nop                                     
  0x0021F895  83c208                  add      edx, 8                         
  0x0021F898  83c720                  add      edi, 0x20                      
  0x0021F89B  0feddf                  paddsw   mm3, mm7                       
  0x0021F89E  0fd9df                  psubusw  mm3, mm7                       
  0x0021F8A1  0fedf7                  paddsw   mm6, mm7                       
  0x0021F8A4  0f7fd9                  movq     mm1, mm3                       
  0x0021F8A7  0f61db                  punpcklwd mm3, mm3                       
  0x0021F8AA  0f69c9                  punpckhwd mm1, mm1                       
  0x0021F8AD  0fd5da                  pmullw   mm3, mm2                       
  0x0021F8B0  0fd5ca                  pmullw   mm1, mm2                       
  0x0021F8B3  0fd9f7                  psubusw  mm6, mm7                       
  0x0021F8B6  0f7ff4                  movq     mm4, mm6                       
  0x0021F8B9  0f61f6                  punpcklwd mm6, mm6                       
  0x0021F8BC  0f69e4                  punpckhwd mm4, mm4                       
  0x0021F8BF  0fd5f2                  pmullw   mm6, mm2                       
  0x0021F8C2  0f7f5fe0                movq     qword ptr [edi - 0x20], mm3    
  0x0021F8C6  0fd5e2                  pmullw   mm4, mm2                       
  0x0021F8C9  0f7f4fe8                movq     qword ptr [edi - 0x18], mm1    
  0x0021F8CD  0f7f77f0                movq     qword ptr [edi - 0x10], mm6    
  0x0021F8D1  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x0021F8D5  3bf8                    cmp      edi, eax                       
  0x0021F8D7  7297                    jb       0x21f870                       
  0x0021F8D9  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x0021F8DF  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021F8E5  5f                      pop      edi                            
  0x0021F8E6  5e                      pop      esi                            
  0x0021F8E7  5d                      pop      ebp                            
  0x0021F8E8  5b                      pop      ebx                            
  0x0021F8E9  c20400                  ret      4                              
