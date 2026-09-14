; ============================================================
; Section: BINK32MX
; VA: 0x0021F040 - 0x0021F1FC
; Size: 444 bytes (0.4 KB)
; Functions: 0
; Instructions: 130
; ============================================================

  0x0021F040  53                      push     ebx                            
  0x0021F041  55                      push     ebp                            
  0x0021F042  56                      push     esi                            
  0x0021F043  57                      push     edi                            
  0x0021F044  0f6f05d8a72500          movq     mm0, qword ptr [0x25a7d8]      
  0x0021F04B  0f6f15b0a72500          movq     mm2, qword ptr [0x25a7b0]      
  0x0021F052  0f6f2de0a72500          movq     mm5, qword ptr [0x25a7e0]      
  0x0021F059  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x0021F05F  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021F065  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F069  c1e005                  shl      eax, 5                         
  0x0021F06C  03c6                    add      eax, esi                       
  0x0021F06E  8bff                    mov      edi, edi                       
                                        ; XREF: 0x0021F111 (cond_jump)
  0x0021F070  0f6e19                  movd     mm3, dword ptr [ecx]           
  0x0021F073  0fefe4                  pxor     mm4, mm4                       
  0x0021F076  0f6e7104                movd     mm6, dword ptr [ecx + 4]       
  0x0021F07A  0f60dc                  punpcklbw mm3, mm4                       
  0x0021F07D  0fd9d8                  psubusw  mm3, mm0                       
  0x0021F080  0f60f4                  punpcklbw mm6, mm4                       
  0x0021F083  0fd9f0                  psubusw  mm6, mm0                       
  0x0021F086  0f71f302                psllw    mm3, 2                         
  0x0021F08A  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021F08D  0f71f602                psllw    mm6, 2                         
  0x0021F091  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021F098  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021F09B  83c108                  add      ecx, 8                         
  0x0021F09E  83c640                  add      esi, 0x40                      
  0x0021F0A1  0feddf                  paddsw   mm3, mm7                       
  0x0021F0A4  0fd9df                  psubusw  mm3, mm7                       
  0x0021F0A7  0fedf7                  paddsw   mm6, mm7                       
  0x0021F0AA  0f7fd9                  movq     mm1, mm3                       
  0x0021F0AD  0f61db                  punpcklwd mm3, mm3                       
  0x0021F0B0  0f69c9                  punpckhwd mm1, mm1                       
  0x0021F0B3  0fd5da                  pmullw   mm3, mm2                       
  0x0021F0B6  0fd5ca                  pmullw   mm1, mm2                       
  0x0021F0B9  0fd9f7                  psubusw  mm6, mm7                       
  0x0021F0BC  0f7ff4                  movq     mm4, mm6                       
  0x0021F0BF  0f61f6                  punpcklwd mm6, mm6                       
  0x0021F0C2  0f69e4                  punpckhwd mm4, mm4                       
  0x0021F0C5  0fd5f2                  pmullw   mm6, mm2                       
  0x0021F0C8  0f7fdf                  movq     mm7, mm3                       
  0x0021F0CB  0f62db                  punpckldq mm3, mm3                       
  0x0021F0CE  0f6aff                  punpckhdq mm7, mm7                       
  0x0021F0D1  0fd5e2                  pmullw   mm4, mm2                       
  0x0021F0D4  0f7f5ec0                movq     qword ptr [esi - 0x40], mm3    
  0x0021F0D8  0f7fcb                  movq     mm3, mm1                       
  0x0021F0DB  0f7f7ec8                movq     qword ptr [esi - 0x38], mm7    
  0x0021F0DF  0f62c9                  punpckldq mm1, mm1                       
  0x0021F0E2  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F0E5  0f7ff7                  movq     mm7, mm6                       
  0x0021F0E8  0f7f4ed0                movq     qword ptr [esi - 0x30], mm1    
  0x0021F0EC  0f62f6                  punpckldq mm6, mm6                       
  0x0021F0EF  0f7f5ed8                movq     qword ptr [esi - 0x28], mm3    
  0x0021F0F3  0f6aff                  punpckhdq mm7, mm7                       
  0x0021F0F6  0f7f76e0                movq     qword ptr [esi - 0x20], mm6    
  0x0021F0FA  0f7fe3                  movq     mm3, mm4                       
  0x0021F0FD  0f7f7ee8                movq     qword ptr [esi - 0x18], mm7    
  0x0021F101  0f62e4                  punpckldq mm4, mm4                       
  0x0021F104  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F107  3bf0                    cmp      esi, eax                       
  0x0021F109  0f7f66f0                movq     qword ptr [esi - 0x10], mm4    
  0x0021F10D  0f7f5ef8                movq     qword ptr [esi - 8], mm3       
  0x0021F111  0f8259ffffff            jb       0x21f070                       
  0x0021F117  8935109f2900            mov      dword ptr [0x299f10], esi      
  0x0021F11D  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021F123  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021F129  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021F12F  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F133  c1e005                  shl      eax, 5                         
  0x0021F136  03c7                    add      eax, edi                       
  0x0021F138  8da42400000000          lea      esp, [esp]                     
  0x0021F13F  90                      nop                                     
                                        ; XREF: 0x0021F1E1 (cond_jump)
  0x0021F140  0f6e1a                  movd     mm3, dword ptr [edx]           
  0x0021F143  0fefe4                  pxor     mm4, mm4                       
  0x0021F146  0f6e7204                movd     mm6, dword ptr [edx + 4]       
  0x0021F14A  0f60dc                  punpcklbw mm3, mm4                       
  0x0021F14D  0fd9d8                  psubusw  mm3, mm0                       
  0x0021F150  0f60f4                  punpcklbw mm6, mm4                       
  0x0021F153  0fd9f0                  psubusw  mm6, mm0                       
  0x0021F156  0f71f302                psllw    mm3, 2                         
  0x0021F15A  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021F15D  0f71f602                psllw    mm6, 2                         
  0x0021F161  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021F168  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021F16B  83c208                  add      edx, 8                         
  0x0021F16E  83c740                  add      edi, 0x40                      
  0x0021F171  0feddf                  paddsw   mm3, mm7                       
  0x0021F174  0fd9df                  psubusw  mm3, mm7                       
  0x0021F177  0fedf7                  paddsw   mm6, mm7                       
  0x0021F17A  0f7fd9                  movq     mm1, mm3                       
  0x0021F17D  0f61db                  punpcklwd mm3, mm3                       
  0x0021F180  0f69c9                  punpckhwd mm1, mm1                       
  0x0021F183  0fd5da                  pmullw   mm3, mm2                       
  0x0021F186  0fd5ca                  pmullw   mm1, mm2                       
  0x0021F189  0fd9f7                  psubusw  mm6, mm7                       
  0x0021F18C  0f7ff4                  movq     mm4, mm6                       
  0x0021F18F  0f61f6                  punpcklwd mm6, mm6                       
  0x0021F192  0f69e4                  punpckhwd mm4, mm4                       
  0x0021F195  0fd5f2                  pmullw   mm6, mm2                       
  0x0021F198  0f7fdf                  movq     mm7, mm3                       
  0x0021F19B  0f62db                  punpckldq mm3, mm3                       
  0x0021F19E  0f6aff                  punpckhdq mm7, mm7                       
  0x0021F1A1  0fd5e2                  pmullw   mm4, mm2                       
  0x0021F1A4  0f7f5fc0                movq     qword ptr [edi - 0x40], mm3    
  0x0021F1A8  0f7fcb                  movq     mm3, mm1                       
  0x0021F1AB  0f7f7fc8                movq     qword ptr [edi - 0x38], mm7    
  0x0021F1AF  0f62c9                  punpckldq mm1, mm1                       
  0x0021F1B2  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F1B5  0f7ff7                  movq     mm7, mm6                       
  0x0021F1B8  0f7f4fd0                movq     qword ptr [edi - 0x30], mm1    
  0x0021F1BC  0f62f6                  punpckldq mm6, mm6                       
  0x0021F1BF  0f7f5fd8                movq     qword ptr [edi - 0x28], mm3    
  0x0021F1C3  0f6aff                  punpckhdq mm7, mm7                       
  0x0021F1C6  0f7f77e0                movq     qword ptr [edi - 0x20], mm6    
  0x0021F1CA  0f7fe3                  movq     mm3, mm4                       
  0x0021F1CD  0f7f7fe8                movq     qword ptr [edi - 0x18], mm7    
  0x0021F1D1  0f62e4                  punpckldq mm4, mm4                       
  0x0021F1D4  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F1D7  3bf8                    cmp      edi, eax                       
  0x0021F1D9  0f7f67f0                movq     qword ptr [edi - 0x10], mm4    
  0x0021F1DD  0f7f5ff8                movq     qword ptr [edi - 8], mm3       
  0x0021F1E1  0f8259ffffff            jb       0x21f140                       
  0x0021F1E7  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x0021F1ED  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021F1F3  5f                      pop      edi                            
  0x0021F1F4  5e                      pop      esi                            
  0x0021F1F5  5d                      pop      ebp                            
  0x0021F1F6  5b                      pop      ebx                            
  0x0021F1F7  c20400                  ret      4                              
  0x0021F1FA  0000                    add      byte ptr [eax], al             
