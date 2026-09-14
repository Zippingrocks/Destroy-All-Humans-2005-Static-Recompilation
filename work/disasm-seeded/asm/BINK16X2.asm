; ============================================================
; Section: BINK16X2
; VA: 0x0021E8E0 - 0x0021EE38
; Size: 1368 bytes (1.3 KB)
; Functions: 0
; Instructions: 308
; ============================================================

  0x0021E8E0  53                      push     ebx                            
  0x0021E8E1  55                      push     ebp                            
  0x0021E8E2  56                      push     esi                            
  0x0021E8E3  57                      push     edi                            
  0x0021E8E4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021E8EA  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021E8F0  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021E8F6  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021E8FC  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021E900  c1e004                  shl      eax, 4                         
  0x0021E903  03c7                    add      eax, edi                       
  0x0021E905  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021E90A  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021E911  8da42400000000          lea      esp, [esp]                     
  0x0021E918  8da42400000000          lea      esp, [esp]                     
  0x0021E91F  90                      nop                                     
                                        ; XREF: 0x0021EA00 (cond_jump)
  0x0021E920  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021E923  0fefc0                  pxor     mm0, mm0                       
  0x0021E926  33c0                    xor      eax, eax                       
  0x0021E928  83c204                  add      edx, 4                         
  0x0021E92B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021E92E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021E931  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021E939  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021E941  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021E944  83c502                  add      ebp, 2                         
  0x0021E947  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021E94E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021E956  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021E95E  8a03                    mov      al, byte ptr [ebx]             
  0x0021E960  0f71f402                psllw    mm4, 2                         
  0x0021E964  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021E96B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021E973  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021E97B  0ffdd5                  paddw    mm2, mm5                       
  0x0021E97E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021E981  83c302                  add      ebx, 2                         
  0x0021E984  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021E98C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021E994  0ffdf5                  paddw    mm6, mm5                       
  0x0021E997  0f62d6                  punpckldq mm2, mm6                       
  0x0021E99A  0ffdcc                  paddw    mm1, mm4                       
  0x0021E99D  0ffdd4                  paddw    mm2, mm4                       
  0x0021E9A0  0fedcf                  paddsw   mm1, mm7                       
  0x0021E9A3  0ffddc                  paddw    mm3, mm4                       
  0x0021E9A6  0fd9cf                  psubusw  mm1, mm7                       
  0x0021E9A9  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021E9B0  0fedd7                  paddsw   mm2, mm7                       
  0x0021E9B3  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021E9BA  0fd9d7                  psubusw  mm2, mm7                       
  0x0021E9BD  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021E9C4  0feddf                  paddsw   mm3, mm7                       
  0x0021E9C7  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021E9CE  0fd9df                  psubusw  mm3, mm7                       
  0x0021E9D1  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021E9D8  0febca                  por      mm1, mm2                       
  0x0021E9DB  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021E9E2  0febcb                  por      mm1, mm3                       
  0x0021E9E5  83c710                  add      edi, 0x10                      
  0x0021E9E8  0f7fcb                  movq     mm3, mm1                       
  0x0021E9EB  0f61c9                  punpcklwd mm1, mm1                       
  0x0021E9EE  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021E9F3  0f69db                  punpckhwd mm3, mm3                       
  0x0021E9F6  0f7f4ff0                movq     qword ptr [edi - 0x10], mm1    
  0x0021E9FA  0f7f5ff8                movq     qword ptr [edi - 8], mm3       
  0x0021E9FE  3bf8                    cmp      edi, eax                       
  0x0021EA00  0f821affffff            jb       0x21e920                       
  0x0021EA06  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021EA0C  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021EA12  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021EA18  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021EA1E  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021EA24  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021EA28  c1e004                  shl      eax, 4                         
  0x0021EA2B  03c7                    add      eax, edi                       
  0x0021EA2D  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021EA32  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021EA39  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x0021EB20 (cond_jump)
  0x0021EA40  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021EA43  0fefc0                  pxor     mm0, mm0                       
  0x0021EA46  33c0                    xor      eax, eax                       
  0x0021EA48  83c204                  add      edx, 4                         
  0x0021EA4B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021EA4E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021EA51  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021EA59  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021EA61  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021EA64  83c502                  add      ebp, 2                         
  0x0021EA67  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021EA6E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021EA76  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021EA7E  8a03                    mov      al, byte ptr [ebx]             
  0x0021EA80  0f71f402                psllw    mm4, 2                         
  0x0021EA84  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021EA8B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021EA93  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021EA9B  0ffdd5                  paddw    mm2, mm5                       
  0x0021EA9E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021EAA1  83c302                  add      ebx, 2                         
  0x0021EAA4  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021EAAC  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021EAB4  0ffdf5                  paddw    mm6, mm5                       
  0x0021EAB7  0f62d6                  punpckldq mm2, mm6                       
  0x0021EABA  0ffdcc                  paddw    mm1, mm4                       
  0x0021EABD  0ffdd4                  paddw    mm2, mm4                       
  0x0021EAC0  0fedcf                  paddsw   mm1, mm7                       
  0x0021EAC3  0ffddc                  paddw    mm3, mm4                       
  0x0021EAC6  0fd9cf                  psubusw  mm1, mm7                       
  0x0021EAC9  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021EAD0  0fedd7                  paddsw   mm2, mm7                       
  0x0021EAD3  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021EADA  0fd9d7                  psubusw  mm2, mm7                       
  0x0021EADD  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021EAE4  0feddf                  paddsw   mm3, mm7                       
  0x0021EAE7  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021EAEE  0fd9df                  psubusw  mm3, mm7                       
  0x0021EAF1  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021EAF8  0febca                  por      mm1, mm2                       
  0x0021EAFB  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021EB02  0febcb                  por      mm1, mm3                       
  0x0021EB05  83c710                  add      edi, 0x10                      
  0x0021EB08  0f7fcb                  movq     mm3, mm1                       
  0x0021EB0B  0f61c9                  punpcklwd mm1, mm1                       
  0x0021EB0E  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021EB13  0f69db                  punpckhwd mm3, mm3                       
  0x0021EB16  0f7f4ff0                movq     qword ptr [edi - 0x10], mm1    
  0x0021EB1A  0f7f5ff8                movq     qword ptr [edi - 8], mm3       
  0x0021EB1E  3bf8                    cmp      edi, eax                       
  0x0021EB20  0f821affffff            jb       0x21ea40                       
  0x0021EB26  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021EB2C  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021EB32  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021EB38  5f                      pop      edi                            
  0x0021EB39  5e                      pop      esi                            
  0x0021EB3A  5d                      pop      ebp                            
  0x0021EB3B  5b                      pop      ebx                            
  0x0021EB3C  c20400                  ret      4                              
  0x0021EB3F  90                      nop                                     
  0x0021EB40  53                      push     ebx                            
  0x0021EB41  55                      push     ebp                            
  0x0021EB42  56                      push     esi                            
  0x0021EB43  57                      push     edi                            
  0x0021EB44  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021EB4A  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021EB50  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021EB56  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x0021EB5C  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021EB60  c1e004                  shl      eax, 4                         
  0x0021EB63  03c7                    add      eax, edi                       
  0x0021EB65  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021EB6A  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021EB71  8da42400000000          lea      esp, [esp]                     
  0x0021EB78  8da42400000000          lea      esp, [esp]                     
  0x0021EB7F  90                      nop                                     
                                        ; XREF: 0x0021ECA9 (cond_jump)
  0x0021EB80  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021EB83  0fefc0                  pxor     mm0, mm0                       
  0x0021EB86  33c0                    xor      eax, eax                       
  0x0021EB88  83c204                  add      edx, 4                         
  0x0021EB8B  8a4500                  mov      al, byte ptr [ebp]             
  0x0021EB8E  0f60e0                  punpcklbw mm4, mm0                       
  0x0021EB91  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021EB99  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021EBA1  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021EBA4  83c502                  add      ebp, 2                         
  0x0021EBA7  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021EBAE  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021EBB6  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021EBBE  8a03                    mov      al, byte ptr [ebx]             
  0x0021EBC0  0f71f402                psllw    mm4, 2                         
  0x0021EBC4  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021EBCB  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021EBD3  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021EBDB  0ffdd5                  paddw    mm2, mm5                       
  0x0021EBDE  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021EBE1  83c302                  add      ebx, 2                         
  0x0021EBE4  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021EBEC  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021EBF4  0ffdf5                  paddw    mm6, mm5                       
  0x0021EBF7  8a4500                  mov      al, byte ptr [ebp]             
  0x0021EBFA  0f62d6                  punpckldq mm2, mm6                       
  0x0021EBFD  0f73d110                psrlq    mm1, 0x10                      
  0x0021EC01  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021EC09  0f73d210                psrlq    mm2, 0x10                      
  0x0021EC0D  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021EC15  0f73d310                psrlq    mm3, 0x10                      
  0x0021EC19  8a03                    mov      al, byte ptr [ebx]             
  0x0021EC1B  0f73f630                psllq    mm6, 0x30                      
  0x0021EC1F  0febce                  por      mm1, mm6                       
  0x0021EC22  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021EC2A  0ffdee                  paddw    mm5, mm6                       
  0x0021EC2D  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021EC35  0f73f530                psllq    mm5, 0x30                      
  0x0021EC39  0f73f630                psllq    mm6, 0x30                      
  0x0021EC3D  0febd5                  por      mm2, mm5                       
  0x0021EC40  0febde                  por      mm3, mm6                       
  0x0021EC43  0ffdcc                  paddw    mm1, mm4                       
  0x0021EC46  0ffdd4                  paddw    mm2, mm4                       
  0x0021EC49  0fedcf                  paddsw   mm1, mm7                       
  0x0021EC4C  0ffddc                  paddw    mm3, mm4                       
  0x0021EC4F  0fd9cf                  psubusw  mm1, mm7                       
  0x0021EC52  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021EC59  0fedd7                  paddsw   mm2, mm7                       
  0x0021EC5C  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021EC63  0fd9d7                  psubusw  mm2, mm7                       
  0x0021EC66  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021EC6D  0feddf                  paddsw   mm3, mm7                       
  0x0021EC70  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021EC77  0fd9df                  psubusw  mm3, mm7                       
  0x0021EC7A  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021EC81  0febca                  por      mm1, mm2                       
  0x0021EC84  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021EC8B  0febcb                  por      mm1, mm3                       
  0x0021EC8E  83c710                  add      edi, 0x10                      
  0x0021EC91  0f7fcb                  movq     mm3, mm1                       
  0x0021EC94  0f61c9                  punpcklwd mm1, mm1                       
  0x0021EC97  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x0021EC9C  0f69db                  punpckhwd mm3, mm3                       
  0x0021EC9F  0f7f4ff0                movq     qword ptr [edi - 0x10], mm1    
  0x0021ECA3  0f7f5ff8                movq     qword ptr [edi - 8], mm3       
  0x0021ECA7  3bf8                    cmp      edi, eax                       
  0x0021ECA9  0f82d1feffff            jb       0x21eb80                       
  0x0021ECAF  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x0021ECB5  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021ECBB  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x0021ECC1  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021ECC7  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021ECCD  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021ECD1  c1e004                  shl      eax, 4                         
  0x0021ECD4  03c7                    add      eax, edi                       
  0x0021ECD6  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x0021ECDB  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
  0x0021ECE2  8da42400000000          lea      esp, [esp]                     
  0x0021ECE9  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x0021EE19 (cond_jump)
  0x0021ECF0  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021ECF3  0fefc0                  pxor     mm0, mm0                       
  0x0021ECF6  33c0                    xor      eax, eax                       
  0x0021ECF8  83c204                  add      edx, 4                         
  0x0021ECFB  8a4500                  mov      al, byte ptr [ebp]             
  0x0021ECFE  0f60e0                  punpcklbw mm4, mm0                       
  0x0021ED01  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x0021ED09  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021ED11  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021ED14  83c502                  add      ebp, 2                         
  0x0021ED17  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x0021ED1E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021ED26  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x0021ED2E  8a03                    mov      al, byte ptr [ebx]             
  0x0021ED30  0f71f402                psllw    mm4, 2                         
  0x0021ED34  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x0021ED3B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021ED43  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021ED4B  0ffdd5                  paddw    mm2, mm5                       
  0x0021ED4E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x0021ED51  83c302                  add      ebx, 2                         
  0x0021ED54  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021ED5C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021ED64  0ffdf5                  paddw    mm6, mm5                       
  0x0021ED67  8a4500                  mov      al, byte ptr [ebp]             
  0x0021ED6A  0f62d6                  punpckldq mm2, mm6                       
  0x0021ED6D  0f73d110                psrlq    mm1, 0x10                      
  0x0021ED71  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x0021ED79  0f73d210                psrlq    mm2, 0x10                      
  0x0021ED7D  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x0021ED85  0f73d310                psrlq    mm3, 0x10                      
  0x0021ED89  8a03                    mov      al, byte ptr [ebx]             
  0x0021ED8B  0f73f630                psllq    mm6, 0x30                      
  0x0021ED8F  0febce                  por      mm1, mm6                       
  0x0021ED92  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x0021ED9A  0ffdee                  paddw    mm5, mm6                       
  0x0021ED9D  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x0021EDA5  0f73f530                psllq    mm5, 0x30                      
  0x0021EDA9  0f73f630                psllq    mm6, 0x30                      
  0x0021EDAD  0febd5                  por      mm2, mm5                       
  0x0021EDB0  0febde                  por      mm3, mm6                       
  0x0021EDB3  0ffdcc                  paddw    mm1, mm4                       
  0x0021EDB6  0ffdd4                  paddw    mm2, mm4                       
  0x0021EDB9  0fedcf                  paddsw   mm1, mm7                       
  0x0021EDBC  0ffddc                  paddw    mm3, mm4                       
  0x0021EDBF  0fd9cf                  psubusw  mm1, mm7                       
  0x0021EDC2  0fd10d50bf2900          psrlw    mm1, qword ptr [0x29bf50]      
  0x0021EDC9  0fedd7                  paddsw   mm2, mm7                       
  0x0021EDCC  0ff10d38bf2900          psllw    mm1, qword ptr [0x29bf38]      
  0x0021EDD3  0fd9d7                  psubusw  mm2, mm7                       
  0x0021EDD6  0fd11558bf2900          psrlw    mm2, qword ptr [0x29bf58]      
  0x0021EDDD  0feddf                  paddsw   mm3, mm7                       
  0x0021EDE0  0ff11540bf2900          psllw    mm2, qword ptr [0x29bf40]      
  0x0021EDE7  0fd9df                  psubusw  mm3, mm7                       
  0x0021EDEA  0fd11d60bf2900          psrlw    mm3, qword ptr [0x29bf60]      
  0x0021EDF1  0febca                  por      mm1, mm2                       
  0x0021EDF4  0ff11d48bf2900          psllw    mm3, qword ptr [0x29bf48]      
  0x0021EDFB  0febcb                  por      mm1, mm3                       
  0x0021EDFE  83c710                  add      edi, 0x10                      
  0x0021EE01  0f7fcb                  movq     mm3, mm1                       
  0x0021EE04  0f61c9                  punpcklwd mm1, mm1                       
  0x0021EE07  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021EE0C  0f69db                  punpckhwd mm3, mm3                       
  0x0021EE0F  0f7f4ff0                movq     qword ptr [edi - 0x10], mm1    
  0x0021EE13  0f7f5ff8                movq     qword ptr [edi - 8], mm3       
  0x0021EE17  3bf8                    cmp      edi, eax                       
  0x0021EE19  0f82d1feffff            jb       0x21ecf0                       
  0x0021EE1F  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021EE25  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x0021EE2B  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021EE31  5f                      pop      edi                            
  0x0021EE32  5e                      pop      esi                            
  0x0021EE33  5d                      pop      ebp                            
  0x0021EE34  5b                      pop      ebx                            
  0x0021EE35  c20400                  ret      4                              
