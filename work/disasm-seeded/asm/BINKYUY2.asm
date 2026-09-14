; ============================================================
; Section: BINKYUY2
; VA: 0x0021E700 - 0x0021E788
; Size: 136 bytes (0.1 KB)
; Functions: 18
; Instructions: 39
; ============================================================

  0x0021E700  53                      push     ebx                            
  0x0021E701  55                      push     ebp                            
  0x0021E702  56                      push     esi                            
  0x0021E703  57                      push     edi                            
  0x0021E704  0f6f1508a82500          movq     mm2, qword ptr [0x25a808]      
  0x0021E70B  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x0021E711  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021E717  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021E71B  8d04c6                  lea      eax, [esi + eax*8]             
  0x0021E71E  8bff                    mov      edi, edi                       
                                        ; XREF: 0x0021E732 (cond_jump)
  0x0021E720  0f6e09                  movd     mm1, dword ptr [ecx]           
  0x0021E723  0f60ca                  punpcklbw mm1, mm2                       
  0x0021E726  83c608                  add      esi, 8                         
  0x0021E729  83c104                  add      ecx, 4                         
  0x0021E72C  3bf0                    cmp      esi, eax                       
  0x0021E72E  0f7f4ef8                movq     qword ptr [esi - 8], mm1       
  0x0021E732  72ec                    jb       0x21e720                       
  0x0021E734  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x0021E739  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021E73F  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x0021E745  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x0021E74B  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x0021E74F  8d04c7                  lea      eax, [edi + eax*8]             
  0x0021E752  8da42400000000          lea      esp, [esp]                     
  0x0021E759  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x0021E772 (cond_jump)
  0x0021E760  0f6e0a                  movd     mm1, dword ptr [edx]           
  0x0021E763  0f60ca                  punpcklbw mm1, mm2                       
  0x0021E766  83c708                  add      edi, 8                         
  0x0021E769  83c204                  add      edx, 4                         
  0x0021E76C  3bf8                    cmp      edi, eax                       
  0x0021E76E  0f7f4ff8                movq     qword ptr [edi - 8], mm1       
  0x0021E772  72ec                    jb       0x21e760                       
  0x0021E774  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x0021E77A  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021E780  5f                      pop      edi                            
  0x0021E781  5e                      pop      esi                            
  0x0021E782  5d                      pop      ebp                            
  0x0021E783  5b                      pop      ebx                            
  0x0021E784  c20400                  ret      4                              
