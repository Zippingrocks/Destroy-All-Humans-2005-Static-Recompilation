; ============================================================
; Section: BINK16MX
; VA: 0x0021E7A0 - 0x0021E8D0
; Size: 304 bytes (0.3 KB)
; Functions: 0
; Instructions: 91
; ============================================================

  0x0021E7A0  53                      push     ebx                            
  0x0021E7A1  55                      push     ebp                            
  0x0021E7A2  56                      push     esi                            
  0x0021E7A3  57                      push     edi                            
  0x0021E7A4  0f6f3d00a82500          movq     mm7, qword ptr [0x25a800]      
  0x0021E7AB  0f6f05d8a72500          movq     mm0, qword ptr [0x25a7d8]      
  0x0021E7B2  0f6f15f0a72500          movq     mm2, qword ptr [0x25a7f0]      
  0x0021E7B9  0f6f2df8a72500          movq     mm5, qword ptr [0x25a7f8]      
  0x0021E7C0  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x0021E7C6  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021E7CC  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021E7D0  c1e004                  shl      eax, 4                         
  0x0021E7D3  03c6                    add      eax, esi                       
  0x0021E7D5  8da42400000000          lea      esp, [esp]                     
  0x0021E7DC  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x0021E839 (cond_jump)
  0x0021E7E0  0f6e19                  movd     mm3, dword ptr [ecx]           
  0x0021E7E3  0fefe4                  pxor     mm4, mm4                       
  0x0021E7E6  0f6e7104                movd     mm6, dword ptr [ecx + 4]       
  0x0021E7EA  0f60dc                  punpcklbw mm3, mm4                       
  0x0021E7ED  0fd9d8                  psubusw  mm3, mm0                       
  0x0021E7F0  0f60f4                  punpcklbw mm6, mm4                       
  0x0021E7F3  0fd9f0                  psubusw  mm6, mm0                       
  0x0021E7F6  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021E7F9  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021E7FC  90                      nop                                     
  0x0021E7FD  83c108                  add      ecx, 8                         
  0x0021E800  83c620                  add      esi, 0x20                      
  0x0021E803  0feddf                  paddsw   mm3, mm7                       
  0x0021E806  0fd9df                  psubusw  mm3, mm7                       
  0x0021E809  0fedf7                  paddsw   mm6, mm7                       
  0x0021E80C  0fd5da                  pmullw   mm3, mm2                       
  0x0021E80F  0fd9f7                  psubusw  mm6, mm7                       
  0x0021E812  0fd5f2                  pmullw   mm6, mm2                       
  0x0021E815  0f7fd9                  movq     mm1, mm3                       
  0x0021E818  0f61db                  punpcklwd mm3, mm3                       
  0x0021E81B  0f69c9                  punpckhwd mm1, mm1                       
  0x0021E81E  0f7ff4                  movq     mm4, mm6                       
  0x0021E821  0f7f5ee0                movq     qword ptr [esi - 0x20], mm3    
  0x0021E825  0f61f6                  punpcklwd mm6, mm6                       
  0x0021E828  0f7f4ee8                movq     qword ptr [esi - 0x18], mm1    
  0x0021E82C  0f69e4                  punpckhwd mm4, mm4                       
  0x0021E82F  0f7f76f0                movq     qword ptr [esi - 0x10], mm6    
  0x0021E833  0f7f66f8                movq     qword ptr [esi - 8], mm4       
  0x0021E837  3bf0                    cmp      esi, eax                       
  0x0021E839  72a5                    jb       0x21e7e0                       
  0x0021E83B  8935109f2900            mov      dword ptr [0x299f10], esi      
  0x0021E841  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021E847  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021E84D  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021E853  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021E857  c1e004                  shl      eax, 4                         
  0x0021E85A  03c7                    add      eax, edi                       
  0x0021E85C  8d642400                lea      esp, [esp]                     
                                        ; XREF: 0x0021E8B9 (cond_jump)
  0x0021E860  0f6e1a                  movd     mm3, dword ptr [edx]           
  0x0021E863  0fefe4                  pxor     mm4, mm4                       
  0x0021E866  0f6e7204                movd     mm6, dword ptr [edx + 4]       
  0x0021E86A  0f60dc                  punpcklbw mm3, mm4                       
  0x0021E86D  0fd9d8                  psubusw  mm3, mm0                       
  0x0021E870  0f60f4                  punpcklbw mm6, mm4                       
  0x0021E873  0fd9f0                  psubusw  mm6, mm0                       
  0x0021E876  0fe5dd                  pmulhw   mm3, mm5                       
  0x0021E879  0fe5f5                  pmulhw   mm6, mm5                       
  0x0021E87C  90                      nop                                     
  0x0021E87D  83c208                  add      edx, 8                         
  0x0021E880  83c720                  add      edi, 0x20                      
  0x0021E883  0feddf                  paddsw   mm3, mm7                       
  0x0021E886  0fd9df                  psubusw  mm3, mm7                       
  0x0021E889  0fedf7                  paddsw   mm6, mm7                       
  0x0021E88C  0fd5da                  pmullw   mm3, mm2                       
  0x0021E88F  0fd9f7                  psubusw  mm6, mm7                       
  0x0021E892  0fd5f2                  pmullw   mm6, mm2                       
  0x0021E895  0f7fd9                  movq     mm1, mm3                       
  0x0021E898  0f61db                  punpcklwd mm3, mm3                       
  0x0021E89B  0f69c9                  punpckhwd mm1, mm1                       
  0x0021E89E  0f7ff4                  movq     mm4, mm6                       
  0x0021E8A1  0f7f5fe0                movq     qword ptr [edi - 0x20], mm3    
  0x0021E8A5  0f61f6                  punpcklwd mm6, mm6                       
  0x0021E8A8  0f7f4fe8                movq     qword ptr [edi - 0x18], mm1    
  0x0021E8AC  0f69e4                  punpckhwd mm4, mm4                       
  0x0021E8AF  0f7f77f0                movq     qword ptr [edi - 0x10], mm6    
  0x0021E8B3  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x0021E8B7  3bf8                    cmp      edi, eax                       
  0x0021E8B9  72a5                    jb       0x21e860                       
  0x0021E8BB  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x0021E8C1  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021E8C7  5f                      pop      edi                            
  0x0021E8C8  5e                      pop      esi                            
  0x0021E8C9  5d                      pop      ebp                            
  0x0021E8CA  5b                      pop      ebx                            
  0x0021E8CB  c20400                  ret      4                              
  0x0021E8CE  0000                    add      byte ptr [eax], al             
