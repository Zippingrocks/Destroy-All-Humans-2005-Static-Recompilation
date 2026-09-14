; ============================================================
; Section: BINK32X2
; VA: 0x0021F200 - 0x0021F78C
; Size: 1420 bytes (1.4 KB)
; Functions: 0
; Instructions: 355
; ============================================================

  0x0021F200  53                      push     ebx                            
  0x0021F201  55                      push     ebp                            
  0x0021F202  56                      push     esi                            
  0x0021F203  57                      push     edi                            
  0x0021F204  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021F20A  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021F210  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021F216  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021F21C  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F220  c1e005                  shl      eax, 5                         
  0x0021F223  03c7                    add      eax, edi                       
  0x0021F225  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021F22A  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x0021F329 (cond_jump)
  0x0021F231  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021F234  0fefc0                  pxor     mm0, mm0                       
  0x0021F237  33c0                    xor      eax, eax                       
  0x0021F239  83c204                  add      edx, 4                         
  0x0021F23C  8a4500                  mov      al, byte ptr [ebp]             
  0x0021F23F  0f60e0                  punpcklbw mm4, mm0                       
  0x0021F242  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021F24A  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F252  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021F255  83c502                  add      ebp, 2                         
  0x0021F258  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021F25F  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021F267  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F26F  8a03                    mov      al, byte ptr [ebx]             
  0x0021F271  0f71f402                psllw    mm4, 2                         
  0x0021F275  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021F27C  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F284  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F28C  0ffdd5                  paddw    mm2, mm5                       
  0x0021F28F  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021F292  83c302                  add      ebx, 2                         
  0x0021F295  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F29D  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F2A5  0ffdf5                  paddw    mm6, mm5                       
  0x0021F2A8  0f62d6                  punpckldq mm2, mm6                       
  0x0021F2AB  0ffdcc                  paddw    mm1, mm4                       
  0x0021F2AE  0ffdd4                  paddw    mm2, mm4                       
  0x0021F2B1  0fedcf                  paddsw   mm1, mm7                       
  0x0021F2B4  0ffddc                  paddw    mm3, mm4                       
  0x0021F2B7  0fd9cf                  psubusw  mm1, mm7                       
  0x0021F2BA  0fedd7                  paddsw   mm2, mm7                       
  0x0021F2BD  0f7fcc                  movq     mm4, mm1                       
  0x0021F2C0  0fd9d7                  psubusw  mm2, mm7                       
  0x0021F2C3  0f61c8                  punpcklwd mm1, mm0                       
  0x0021F2C6  0f7fd5                  movq     mm5, mm2                       
  0x0021F2C9  0f61d0                  punpcklwd mm2, mm0                       
  0x0021F2CC  0feddf                  paddsw   mm3, mm7                       
  0x0021F2CF  0f72f208                pslld    mm2, 8                         
  0x0021F2D3  0fd9df                  psubusw  mm3, mm7                       
  0x0021F2D6  0f69e0                  punpckhwd mm4, mm0                       
  0x0021F2D9  0f7fde                  movq     mm6, mm3                       
  0x0021F2DC  0f61d8                  punpcklwd mm3, mm0                       
  0x0021F2DF  0f72f310                pslld    mm3, 0x10                      
  0x0021F2E3  0febca                  por      mm1, mm2                       
  0x0021F2E6  0febcb                  por      mm1, mm3                       
  0x0021F2E9  0f69e8                  punpckhwd mm5, mm0                       
  0x0021F2EC  0f7fcb                  movq     mm3, mm1                       
  0x0021F2EF  0f69f0                  punpckhwd mm6, mm0                       
  0x0021F2F2  0f72f508                pslld    mm5, 8                         
  0x0021F2F6  83c720                  add      edi, 0x20                      
  0x0021F2F9  0f62c9                  punpckldq mm1, mm1                       
  0x0021F2FC  0febe5                  por      mm4, mm5                       
  0x0021F2FF  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F302  0f7f4fe0                movq     qword ptr [edi - 0x20], mm1    
  0x0021F306  0f72f610                pslld    mm6, 0x10                      
  0x0021F30A  0f7f5fe8                movq     qword ptr [edi - 0x18], mm3    
  0x0021F30E  0febe6                  por      mm4, mm6                       
  0x0021F311  0f7fe6                  movq     mm6, mm4                       
  0x0021F314  0f62e4                  punpckldq mm4, mm4                       
  0x0021F317  0f6af6                  punpckhdq mm6, mm6                       
  0x0021F31A  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021F31F  0f7f67f0                movq     qword ptr [edi - 0x10], mm4    
  0x0021F323  0f7f77f8                movq     qword ptr [edi - 8], mm6       
  0x0021F327  3bf8                    cmp      edi, eax                       
  0x0021F329  0f8202ffffff            jb       0x21f231                       
  0x0021F32F  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021F335  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021F33B  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021F341  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021F347  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021F34D  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F351  c1e005                  shl      eax, 5                         
  0x0021F354  03c7                    add      eax, edi                       
  0x0021F356  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021F35B  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x0021F45A (cond_jump)
  0x0021F362  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021F365  0fefc0                  pxor     mm0, mm0                       
  0x0021F368  33c0                    xor      eax, eax                       
  0x0021F36A  83c204                  add      edx, 4                         
  0x0021F36D  8a4500                  mov      al, byte ptr [ebp]             
  0x0021F370  0f60e0                  punpcklbw mm4, mm0                       
  0x0021F373  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021F37B  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F383  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021F386  83c502                  add      ebp, 2                         
  0x0021F389  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021F390  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021F398  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F3A0  8a03                    mov      al, byte ptr [ebx]             
  0x0021F3A2  0f71f402                psllw    mm4, 2                         
  0x0021F3A6  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021F3AD  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F3B5  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F3BD  0ffdd5                  paddw    mm2, mm5                       
  0x0021F3C0  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021F3C3  83c302                  add      ebx, 2                         
  0x0021F3C6  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F3CE  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F3D6  0ffdf5                  paddw    mm6, mm5                       
  0x0021F3D9  0f62d6                  punpckldq mm2, mm6                       
  0x0021F3DC  0ffdcc                  paddw    mm1, mm4                       
  0x0021F3DF  0ffdd4                  paddw    mm2, mm4                       
  0x0021F3E2  0fedcf                  paddsw   mm1, mm7                       
  0x0021F3E5  0ffddc                  paddw    mm3, mm4                       
  0x0021F3E8  0fd9cf                  psubusw  mm1, mm7                       
  0x0021F3EB  0fedd7                  paddsw   mm2, mm7                       
  0x0021F3EE  0f7fcc                  movq     mm4, mm1                       
  0x0021F3F1  0fd9d7                  psubusw  mm2, mm7                       
  0x0021F3F4  0f61c8                  punpcklwd mm1, mm0                       
  0x0021F3F7  0f7fd5                  movq     mm5, mm2                       
  0x0021F3FA  0f61d0                  punpcklwd mm2, mm0                       
  0x0021F3FD  0feddf                  paddsw   mm3, mm7                       
  0x0021F400  0f72f208                pslld    mm2, 8                         
  0x0021F404  0fd9df                  psubusw  mm3, mm7                       
  0x0021F407  0f69e0                  punpckhwd mm4, mm0                       
  0x0021F40A  0f7fde                  movq     mm6, mm3                       
  0x0021F40D  0f61d8                  punpcklwd mm3, mm0                       
  0x0021F410  0f72f310                pslld    mm3, 0x10                      
  0x0021F414  0febca                  por      mm1, mm2                       
  0x0021F417  0febcb                  por      mm1, mm3                       
  0x0021F41A  0f69e8                  punpckhwd mm5, mm0                       
  0x0021F41D  0f7fcb                  movq     mm3, mm1                       
  0x0021F420  0f69f0                  punpckhwd mm6, mm0                       
  0x0021F423  0f72f508                pslld    mm5, 8                         
  0x0021F427  83c720                  add      edi, 0x20                      
  0x0021F42A  0f62c9                  punpckldq mm1, mm1                       
  0x0021F42D  0febe5                  por      mm4, mm5                       
  0x0021F430  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F433  0f7f4fe0                movq     qword ptr [edi - 0x20], mm1    
  0x0021F437  0f72f610                pslld    mm6, 0x10                      
  0x0021F43B  0f7f5fe8                movq     qword ptr [edi - 0x18], mm3    
  0x0021F43F  0febe6                  por      mm4, mm6                       
  0x0021F442  0f7fe6                  movq     mm6, mm4                       
  0x0021F445  0f62e4                  punpckldq mm4, mm4                       
  0x0021F448  0f6af6                  punpckhdq mm6, mm6                       
  0x0021F44B  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021F450  0f7f67f0                movq     qword ptr [edi - 0x10], mm4    
  0x0021F454  0f7f77f8                movq     qword ptr [edi - 8], mm6       
  0x0021F458  3bf8                    cmp      edi, eax                       
  0x0021F45A  0f8202ffffff            jb       0x21f362                       
  0x0021F460  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021F466  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021F46C  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021F472  5f                      pop      edi                            
  0x0021F473  5e                      pop      esi                            
  0x0021F474  5d                      pop      ebp                            
  0x0021F475  5b                      pop      ebx                            
  0x0021F476  c20400                  ret      4                              
  0x0021F479  8da42400000000          lea      esp, [esp]                     
  0x0021F480  53                      push     ebx                            
  0x0021F481  55                      push     ebp                            
  0x0021F482  56                      push     esi                            
  0x0021F483  57                      push     edi                            
  0x0021F484  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021F48A  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021F490  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021F496  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021F49C  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F4A0  c1e005                  shl      eax, 5                         
  0x0021F4A3  03c7                    add      eax, edi                       
  0x0021F4A5  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021F4AA  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x0021F5F2 (cond_jump)
  0x0021F4B1  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021F4B4  0fefc0                  pxor     mm0, mm0                       
  0x0021F4B7  33c0                    xor      eax, eax                       
  0x0021F4B9  83c204                  add      edx, 4                         
  0x0021F4BC  8a4500                  mov      al, byte ptr [ebp]             
  0x0021F4BF  0f60e0                  punpcklbw mm4, mm0                       
  0x0021F4C2  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021F4CA  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F4D2  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021F4D5  83c502                  add      ebp, 2                         
  0x0021F4D8  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021F4DF  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021F4E7  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F4EF  8a03                    mov      al, byte ptr [ebx]             
  0x0021F4F1  0f71f402                psllw    mm4, 2                         
  0x0021F4F5  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021F4FC  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F504  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F50C  0ffdd5                  paddw    mm2, mm5                       
  0x0021F50F  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021F512  83c302                  add      ebx, 2                         
  0x0021F515  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F51D  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F525  0ffdf5                  paddw    mm6, mm5                       
  0x0021F528  8a4500                  mov      al, byte ptr [ebp]             
  0x0021F52B  0f62d6                  punpckldq mm2, mm6                       
  0x0021F52E  0f73d110                psrlq    mm1, 0x10                      
  0x0021F532  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021F53A  0f73d210                psrlq    mm2, 0x10                      
  0x0021F53E  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021F546  0f73d310                psrlq    mm3, 0x10                      
  0x0021F54A  8a03                    mov      al, byte ptr [ebx]             
  0x0021F54C  0f73f630                psllq    mm6, 0x30                      
  0x0021F550  0febce                  por      mm1, mm6                       
  0x0021F553  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021F55B  0ffdee                  paddw    mm5, mm6                       
  0x0021F55E  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021F566  0f73f530                psllq    mm5, 0x30                      
  0x0021F56A  0f73f630                psllq    mm6, 0x30                      
  0x0021F56E  0febd5                  por      mm2, mm5                       
  0x0021F571  0febde                  por      mm3, mm6                       
  0x0021F574  0ffdcc                  paddw    mm1, mm4                       
  0x0021F577  0ffdd4                  paddw    mm2, mm4                       
  0x0021F57A  0fedcf                  paddsw   mm1, mm7                       
  0x0021F57D  0ffddc                  paddw    mm3, mm4                       
  0x0021F580  0fd9cf                  psubusw  mm1, mm7                       
  0x0021F583  0fedd7                  paddsw   mm2, mm7                       
  0x0021F586  0f7fcc                  movq     mm4, mm1                       
  0x0021F589  0fd9d7                  psubusw  mm2, mm7                       
  0x0021F58C  0f61c8                  punpcklwd mm1, mm0                       
  0x0021F58F  0f7fd5                  movq     mm5, mm2                       
  0x0021F592  0f61d0                  punpcklwd mm2, mm0                       
  0x0021F595  0feddf                  paddsw   mm3, mm7                       
  0x0021F598  0f72f208                pslld    mm2, 8                         
  0x0021F59C  0fd9df                  psubusw  mm3, mm7                       
  0x0021F59F  0f69e0                  punpckhwd mm4, mm0                       
  0x0021F5A2  0f7fde                  movq     mm6, mm3                       
  0x0021F5A5  0f61d8                  punpcklwd mm3, mm0                       
  0x0021F5A8  0f72f310                pslld    mm3, 0x10                      
  0x0021F5AC  0febca                  por      mm1, mm2                       
  0x0021F5AF  0febcb                  por      mm1, mm3                       
  0x0021F5B2  0f69e8                  punpckhwd mm5, mm0                       
  0x0021F5B5  0f7fcb                  movq     mm3, mm1                       
  0x0021F5B8  0f69f0                  punpckhwd mm6, mm0                       
  0x0021F5BB  0f72f508                pslld    mm5, 8                         
  0x0021F5BF  83c720                  add      edi, 0x20                      
  0x0021F5C2  0f62c9                  punpckldq mm1, mm1                       
  0x0021F5C5  0febe5                  por      mm4, mm5                       
  0x0021F5C8  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F5CB  0f7f4fe0                movq     qword ptr [edi - 0x20], mm1    
  0x0021F5CF  0f72f610                pslld    mm6, 0x10                      
  0x0021F5D3  0f7f5fe8                movq     qword ptr [edi - 0x18], mm3    
  0x0021F5D7  0febe6                  por      mm4, mm6                       
  0x0021F5DA  0f7fe6                  movq     mm6, mm4                       
  0x0021F5DD  0f62e4                  punpckldq mm4, mm4                       
  0x0021F5E0  0f6af6                  punpckhdq mm6, mm6                       
  0x0021F5E3  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021F5E8  0f7f67f0                movq     qword ptr [edi - 0x10], mm4    
  0x0021F5EC  0f7f77f8                movq     qword ptr [edi - 8], mm6       
  0x0021F5F0  3bf8                    cmp      edi, eax                       
  0x0021F5F2  0f82b9feffff            jb       0x21f4b1                       
  0x0021F5F8  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021F5FE  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021F604  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021F60A  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021F610  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021F616  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021F61A  c1e005                  shl      eax, 5                         
  0x0021F61D  03c7                    add      eax, edi                       
  0x0021F61F  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021F624  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x0021F76C (cond_jump)
  0x0021F62B  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021F62E  0fefc0                  pxor     mm0, mm0                       
  0x0021F631  33c0                    xor      eax, eax                       
  0x0021F633  83c204                  add      edx, 4                         
  0x0021F636  8a4500                  mov      al, byte ptr [ebp]             
  0x0021F639  0f60e0                  punpcklbw mm4, mm0                       
  0x0021F63C  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021F644  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F64C  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021F64F  83c502                  add      ebp, 2                         
  0x0021F652  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021F659  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021F661  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021F669  8a03                    mov      al, byte ptr [ebx]             
  0x0021F66B  0f71f402                psllw    mm4, 2                         
  0x0021F66F  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021F676  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F67E  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F686  0ffdd5                  paddw    mm2, mm5                       
  0x0021F689  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021F68C  83c302                  add      ebx, 2                         
  0x0021F68F  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021F697  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021F69F  0ffdf5                  paddw    mm6, mm5                       
  0x0021F6A2  8a4500                  mov      al, byte ptr [ebp]             
  0x0021F6A5  0f62d6                  punpckldq mm2, mm6                       
  0x0021F6A8  0f73d110                psrlq    mm1, 0x10                      
  0x0021F6AC  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021F6B4  0f73d210                psrlq    mm2, 0x10                      
  0x0021F6B8  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021F6C0  0f73d310                psrlq    mm3, 0x10                      
  0x0021F6C4  8a03                    mov      al, byte ptr [ebx]             
  0x0021F6C6  0f73f630                psllq    mm6, 0x30                      
  0x0021F6CA  0febce                  por      mm1, mm6                       
  0x0021F6CD  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021F6D5  0ffdee                  paddw    mm5, mm6                       
  0x0021F6D8  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021F6E0  0f73f530                psllq    mm5, 0x30                      
  0x0021F6E4  0f73f630                psllq    mm6, 0x30                      
  0x0021F6E8  0febd5                  por      mm2, mm5                       
  0x0021F6EB  0febde                  por      mm3, mm6                       
  0x0021F6EE  0ffdcc                  paddw    mm1, mm4                       
  0x0021F6F1  0ffdd4                  paddw    mm2, mm4                       
  0x0021F6F4  0fedcf                  paddsw   mm1, mm7                       
  0x0021F6F7  0ffddc                  paddw    mm3, mm4                       
  0x0021F6FA  0fd9cf                  psubusw  mm1, mm7                       
  0x0021F6FD  0fedd7                  paddsw   mm2, mm7                       
  0x0021F700  0f7fcc                  movq     mm4, mm1                       
  0x0021F703  0fd9d7                  psubusw  mm2, mm7                       
  0x0021F706  0f61c8                  punpcklwd mm1, mm0                       
  0x0021F709  0f7fd5                  movq     mm5, mm2                       
  0x0021F70C  0f61d0                  punpcklwd mm2, mm0                       
  0x0021F70F  0feddf                  paddsw   mm3, mm7                       
  0x0021F712  0f72f208                pslld    mm2, 8                         
  0x0021F716  0fd9df                  psubusw  mm3, mm7                       
  0x0021F719  0f69e0                  punpckhwd mm4, mm0                       
  0x0021F71C  0f7fde                  movq     mm6, mm3                       
  0x0021F71F  0f61d8                  punpcklwd mm3, mm0                       
  0x0021F722  0f72f310                pslld    mm3, 0x10                      
  0x0021F726  0febca                  por      mm1, mm2                       
  0x0021F729  0febcb                  por      mm1, mm3                       
  0x0021F72C  0f69e8                  punpckhwd mm5, mm0                       
  0x0021F72F  0f7fcb                  movq     mm3, mm1                       
  0x0021F732  0f69f0                  punpckhwd mm6, mm0                       
  0x0021F735  0f72f508                pslld    mm5, 8                         
  0x0021F739  83c720                  add      edi, 0x20                      
  0x0021F73C  0f62c9                  punpckldq mm1, mm1                       
  0x0021F73F  0febe5                  por      mm4, mm5                       
  0x0021F742  0f6adb                  punpckhdq mm3, mm3                       
  0x0021F745  0f7f4fe0                movq     qword ptr [edi - 0x20], mm1    
  0x0021F749  0f72f610                pslld    mm6, 0x10                      
  0x0021F74D  0f7f5fe8                movq     qword ptr [edi - 0x18], mm3    
  0x0021F751  0febe6                  por      mm4, mm6                       
  0x0021F754  0f7fe6                  movq     mm6, mm4                       
  0x0021F757  0f62e4                  punpckldq mm4, mm4                       
  0x0021F75A  0f6af6                  punpckhdq mm6, mm6                       
  0x0021F75D  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021F762  0f7f67f0                movq     qword ptr [edi - 0x10], mm4    
  0x0021F766  0f7f77f8                movq     qword ptr [edi - 8], mm6       
  0x0021F76A  3bf8                    cmp      edi, eax                       
  0x0021F76C  0f82b9feffff            jb       0x21f62b                       
  0x0021F772  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021F778  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021F77E  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021F784  5f                      pop      edi                            
  0x0021F785  5e                      pop      esi                            
  0x0021F786  5d                      pop      ebp                            
  0x0021F787  5b                      pop      ebx                            
  0x0021F788  c20400                  ret      4                              
