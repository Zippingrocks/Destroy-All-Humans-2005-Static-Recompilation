; ============================================================
; Section: BINK32A
; VA: 0x00218820 - 0x00219C79
; Size: 5209 bytes (5.1 KB)
; Functions: 17
; Instructions: 1524
; ============================================================

  0x00218820  56                      push     esi                            
  0x00218821  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00218825  85f6                    test     esi, esi                       
  0x00218827  7458                    je       0x218881                       
  0x00218829  53                      push     ebx                            
  0x0021882A  57                      push     edi                            
  0x0021882B  eb03                    jmp      0x218830                       
  0x0021882D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021882B (jump), 0x0021887D (cond_jump)
  0x00218830  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00218836  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00218839  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x0021883F  0fb602                  movzx    eax, byte ptr [edx]            
  0x00218842  8b1cbd109b2900          mov      ebx, dword ptr [edi*4 + 0x299b10] 
  0x00218849  c1e018                  shl      eax, 0x18                      
  0x0021884C  0bc3                    or       eax, ebx                       
  0x0021884E  42                      inc      edx                            
  0x0021884F  41                      inc      ecx                            
  0x00218850  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00218856  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021885C  8915289f2900            mov      dword ptr [0x299f28], edx      
  0x00218862  8901                    mov      dword ptr [ecx], eax           
  0x00218864  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021886A  894204                  mov      dword ptr [edx + 4], eax       
  0x0021886D  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218873  83c108                  add      ecx, 8                         
  0x00218876  4e                      dec      esi                            
  0x00218877  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x0021887D  75b1                    jne      0x218830                       
  0x0021887F  5f                      pop      edi                            
  0x00218880  5b                      pop      ebx                            
                                        ; XREF: 0x00218827 (cond_jump)
  0x00218881  5e                      pop      esi                            
  0x00218882  c3                      ret                                     
  0x00218883  cc                      int3                                    
  0x00218884  cc                      int3                                    
  0x00218885  cc                      int3                                    
  0x00218886  cc                      int3                                    
  0x00218887  cc                      int3                                    
  0x00218888  cc                      int3                                    
  0x00218889  cc                      int3                                    
  0x0021888A  cc                      int3                                    
  0x0021888B  cc                      int3                                    
  0x0021888C  cc                      int3                                    
  0x0021888D  cc                      int3                                    
  0x0021888E  cc                      int3                                    
  0x0021888F  cc                      int3                                    

; ============================================================
; Function: sub_00218890
; Start: 0x00218890  End: 0x00218944  Size: 180 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218890:
  0x00218890  53                      push     ebx                            
  0x00218891  55                      push     ebp                            
  0x00218892  56                      push     esi                            
  0x00218893  57                      push     edi                            
  0x00218894  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x00218898  8bf7                    mov      esi, edi                       
  0x0021889A  bb08000000              mov      ebx, 8                         
  0x0021889F  90                      nop                                     
                                        ; XREF: 0x00218933 (cond_jump)
  0x002188A0  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x002188A6  0fb602                  movzx    eax, byte ptr [edx]            
  0x002188A9  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x002188AF  0fb629                  movzx    ebp, byte ptr [ecx]            
  0x002188B2  c1e018                  shl      eax, 0x18                      
  0x002188B5  0b04ad109b2900          or       eax, dword ptr [ebp*4 + 0x299b10] 
  0x002188BC  42                      inc      edx                            
  0x002188BD  41                      inc      ecx                            
  0x002188BE  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x002188C4  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002188CA  8915289f2900            mov      dword ptr [0x299f28], edx      
  0x002188D0  8901                    mov      dword ptr [ecx], eax           
  0x002188D2  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x002188D8  894204                  mov      dword ptr [edx + 4], eax       
  0x002188DB  8b152c9f2900            mov      edx, dword ptr [0x299f2c]      
  0x002188E1  0fb602                  movzx    eax, byte ptr [edx]            
  0x002188E4  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x002188EA  0fb629                  movzx    ebp, byte ptr [ecx]            
  0x002188ED  c1e018                  shl      eax, 0x18                      
  0x002188F0  0b04ad109b2900          or       eax, dword ptr [ebp*4 + 0x299b10] 
  0x002188F7  42                      inc      edx                            
  0x002188F8  41                      inc      ecx                            
  0x002188F9  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x002188FF  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218905  89152c9f2900            mov      dword ptr [0x299f2c], edx      
  0x0021890B  8901                    mov      dword ptr [ecx], eax           
  0x0021890D  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00218913  894204                  mov      dword ptr [edx + 4], eax       
  0x00218916  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021891C  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218922  03d3                    add      edx, ebx                       
  0x00218924  03cb                    add      ecx, ebx                       
  0x00218926  4e                      dec      esi                            
  0x00218927  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x0021892D  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x00218933  0f8567ffffff            jne      0x2188a0                       
  0x00218939  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x0021893D  03c7                    add      eax, edi                       
  0x0021893F  5f                      pop      edi                            
  0x00218940  5e                      pop      esi                            
  0x00218941  5d                      pop      ebp                            
  0x00218942  5b                      pop      ebx                            
  0x00218943  c3                      ret                                     
; end of function
  0x00218944  cc                      int3                                    
  0x00218945  cc                      int3                                    
  0x00218946  cc                      int3                                    
  0x00218947  cc                      int3                                    
  0x00218948  cc                      int3                                    
  0x00218949  cc                      int3                                    
  0x0021894A  cc                      int3                                    
  0x0021894B  cc                      int3                                    
  0x0021894C  cc                      int3                                    
  0x0021894D  cc                      int3                                    
  0x0021894E  cc                      int3                                    
  0x0021894F  cc                      int3                                    

; ============================================================
; Function: sub_00218950
; Start: 0x00218950  End: 0x002189B9  Size: 105 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218950:
  0x00218950  56                      push     esi                            
  0x00218951  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00218955  85f6                    test     esi, esi                       
  0x00218957  745e                    je       0x2189b7                       
  0x00218959  53                      push     ebx                            
  0x0021895A  57                      push     edi                            
  0x0021895B  eb03                    jmp      0x218960                       
  0x0021895D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x0021895B (jump), 0x002189B3 (cond_jump)
  0x00218960  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00218966  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00218969  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x0021896F  0fb602                  movzx    eax, byte ptr [edx]            
  0x00218972  8b1cbd109b2900          mov      ebx, dword ptr [edi*4 + 0x299b10] 
  0x00218979  c1e018                  shl      eax, 0x18                      
  0x0021897C  0bc3                    or       eax, ebx                       
  0x0021897E  42                      inc      edx                            
  0x0021897F  41                      inc      ecx                            
  0x00218980  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00218986  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x0021898C  8915289f2900            mov      dword ptr [0x299f28], edx      
  0x00218992  8901                    mov      dword ptr [ecx], eax           
  0x00218994  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021899A  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x002189A0  890411                  mov      dword ptr [ecx + edx], eax     
  0x002189A3  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002189A9  83c104                  add      ecx, 4                         
  0x002189AC  4e                      dec      esi                            
  0x002189AD  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x002189B3  75ab                    jne      0x218960                       
  0x002189B5  5f                      pop      edi                            
  0x002189B6  5b                      pop      ebx                            
                                        ; XREF: 0x00218957 (cond_jump)
  0x002189B7  5e                      pop      esi                            
  0x002189B8  c3                      ret                                     
; end of function
  0x002189B9  cc                      int3                                    
  0x002189BA  cc                      int3                                    
  0x002189BB  cc                      int3                                    
  0x002189BC  cc                      int3                                    
  0x002189BD  cc                      int3                                    
  0x002189BE  cc                      int3                                    
  0x002189BF  cc                      int3                                    

; ============================================================
; Function: sub_002189C0
; Start: 0x002189C0  End: 0x00218A80  Size: 192 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002189C0:
  0x002189C0  53                      push     ebx                            
  0x002189C1  55                      push     ebp                            
  0x002189C2  56                      push     esi                            
  0x002189C3  57                      push     edi                            
  0x002189C4  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x002189C8  8bf7                    mov      esi, edi                       
  0x002189CA  bb04000000              mov      ebx, 4                         
  0x002189CF  90                      nop                                     
                                        ; XREF: 0x00218A6F (cond_jump)
  0x002189D0  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x002189D6  0fb602                  movzx    eax, byte ptr [edx]            
  0x002189D9  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x002189DF  0fb629                  movzx    ebp, byte ptr [ecx]            
  0x002189E2  c1e018                  shl      eax, 0x18                      
  0x002189E5  0b04ad109b2900          or       eax, dword ptr [ebp*4 + 0x299b10] 
  0x002189EC  42                      inc      edx                            
  0x002189ED  41                      inc      ecx                            
  0x002189EE  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x002189F4  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002189FA  8915289f2900            mov      dword ptr [0x299f28], edx      
  0x00218A00  8901                    mov      dword ptr [ecx], eax           
  0x00218A02  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218A08  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00218A0E  89040a                  mov      dword ptr [edx + ecx], eax     
  0x00218A11  8b152c9f2900            mov      edx, dword ptr [0x299f2c]      
  0x00218A17  0fb602                  movzx    eax, byte ptr [edx]            
  0x00218A1A  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00218A20  0fb629                  movzx    ebp, byte ptr [ecx]            
  0x00218A23  c1e018                  shl      eax, 0x18                      
  0x00218A26  0b04ad109b2900          or       eax, dword ptr [ebp*4 + 0x299b10] 
  0x00218A2D  42                      inc      edx                            
  0x00218A2E  89152c9f2900            mov      dword ptr [0x299f2c], edx      
  0x00218A34  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00218A3A  41                      inc      ecx                            
  0x00218A3B  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00218A41  8902                    mov      dword ptr [edx], eax           
  0x00218A43  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218A49  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00218A4F  890411                  mov      dword ptr [ecx + edx], eax     
  0x00218A52  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218A58  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218A5E  03d3                    add      edx, ebx                       
  0x00218A60  03cb                    add      ecx, ebx                       
  0x00218A62  4e                      dec      esi                            
  0x00218A63  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00218A69  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x00218A6F  0f855bffffff            jne      0x2189d0                       
  0x00218A75  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x00218A79  03c7                    add      eax, edi                       
  0x00218A7B  5f                      pop      edi                            
  0x00218A7C  5e                      pop      esi                            
  0x00218A7D  5d                      pop      ebp                            
  0x00218A7E  5b                      pop      ebx                            
  0x00218A7F  c3                      ret                                     
; end of function
  0x00218A80  56                      push     esi                            
  0x00218A81  8b74240c                mov      esi, dword ptr [esp + 0xc]     
  0x00218A85  85f6                    test     esi, esi                       
  0x00218A87  7477                    je       0x218b00                       
  0x00218A89  53                      push     ebx                            
  0x00218A8A  57                      push     edi                            
  0x00218A8B  eb03                    jmp      0x218a90                       
  0x00218A8D  8d4900                  lea      ecx, [ecx]                     
                                        ; XREF: 0x00218A8B (jump), 0x00218AFC (cond_jump)
  0x00218A90  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00218A96  0fb639                  movzx    edi, byte ptr [ecx]            
  0x00218A99  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x00218A9F  0fb602                  movzx    eax, byte ptr [edx]            
  0x00218AA2  8b1cbd109b2900          mov      ebx, dword ptr [edi*4 + 0x299b10] 
  0x00218AA9  c1e018                  shl      eax, 0x18                      
  0x00218AAC  0bc3                    or       eax, ebx                       
  0x00218AAE  42                      inc      edx                            
  0x00218AAF  41                      inc      ecx                            
  0x00218AB0  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00218AB6  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218ABC  8915289f2900            mov      dword ptr [0x299f28], edx      
  0x00218AC2  8901                    mov      dword ptr [ecx], eax           
  0x00218AC4  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218ACA  894204                  mov      dword ptr [edx + 4], eax       
  0x00218ACD  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218AD3  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00218AD9  890411                  mov      dword ptr [ecx + edx], eax     
  0x00218ADC  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218AE2  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00218AE8  89440a04                mov      dword ptr [edx + ecx + 4], eax 
  0x00218AEC  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218AF2  83c108                  add      ecx, 8                         
  0x00218AF5  4e                      dec      esi                            
  0x00218AF6  890d109f2900            mov      dword ptr [0x299f10], ecx      
  0x00218AFC  7592                    jne      0x218a90                       
  0x00218AFE  5f                      pop      edi                            
  0x00218AFF  5b                      pop      ebx                            
                                        ; XREF: 0x00218A87 (cond_jump)
  0x00218B00  5e                      pop      esi                            
  0x00218B01  c3                      ret                                     
  0x00218B02  cc                      int3                                    
  0x00218B03  cc                      int3                                    
  0x00218B04  cc                      int3                                    
  0x00218B05  cc                      int3                                    
  0x00218B06  cc                      int3                                    
  0x00218B07  cc                      int3                                    
  0x00218B08  cc                      int3                                    
  0x00218B09  cc                      int3                                    
  0x00218B0A  cc                      int3                                    
  0x00218B0B  cc                      int3                                    
  0x00218B0C  cc                      int3                                    
  0x00218B0D  cc                      int3                                    
  0x00218B0E  cc                      int3                                    
  0x00218B0F  cc                      int3                                    

; ============================================================
; Function: sub_00218B10
; Start: 0x00218B10  End: 0x00218C02  Size: 242 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218B10:
  0x00218B10  53                      push     ebx                            
  0x00218B11  55                      push     ebp                            
  0x00218B12  56                      push     esi                            
  0x00218B13  57                      push     edi                            
  0x00218B14  8b7c2414                mov      edi, dword ptr [esp + 0x14]    
  0x00218B18  8bf7                    mov      esi, edi                       
  0x00218B1A  bb08000000              mov      ebx, 8                         
  0x00218B1F  90                      nop                                     
                                        ; XREF: 0x00218BF1 (cond_jump)
  0x00218B20  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x00218B26  0fb602                  movzx    eax, byte ptr [edx]            
  0x00218B29  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00218B2F  0fb629                  movzx    ebp, byte ptr [ecx]            
  0x00218B32  c1e018                  shl      eax, 0x18                      
  0x00218B35  0b04ad109b2900          or       eax, dword ptr [ebp*4 + 0x299b10] 
  0x00218B3C  42                      inc      edx                            
  0x00218B3D  8915289f2900            mov      dword ptr [0x299f28], edx      
  0x00218B43  41                      inc      ecx                            
  0x00218B44  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00218B4A  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218B50  8901                    mov      dword ptr [ecx], eax           
  0x00218B52  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218B58  894204                  mov      dword ptr [edx + 4], eax       
  0x00218B5B  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218B61  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00218B67  890411                  mov      dword ptr [ecx + edx], eax     
  0x00218B6A  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218B70  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x00218B76  89441104                mov      dword ptr [ecx + edx + 4], eax 
  0x00218B7A  8b152c9f2900            mov      edx, dword ptr [0x299f2c]      
  0x00218B80  0fb602                  movzx    eax, byte ptr [edx]            
  0x00218B83  8b0d1c9f2900            mov      ecx, dword ptr [0x299f1c]      
  0x00218B89  0fb629                  movzx    ebp, byte ptr [ecx]            
  0x00218B8C  c1e018                  shl      eax, 0x18                      
  0x00218B8F  0b04ad109b2900          or       eax, dword ptr [ebp*4 + 0x299b10] 
  0x00218B96  42                      inc      edx                            
  0x00218B97  41                      inc      ecx                            
  0x00218B98  890d1c9f2900            mov      dword ptr [0x299f1c], ecx      
  0x00218B9E  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218BA4  89152c9f2900            mov      dword ptr [0x299f2c], edx      
  0x00218BAA  8901                    mov      dword ptr [ecx], eax           
  0x00218BAC  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00218BB2  894204                  mov      dword ptr [edx + 4], eax       
  0x00218BB5  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218BBB  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00218BC1  890411                  mov      dword ptr [ecx + edx], eax     
  0x00218BC4  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218BCA  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00218BD0  89441104                mov      dword ptr [ecx + edx + 4], eax 
  0x00218BD4  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218BDA  8b0d149f2900            mov      ecx, dword ptr [0x299f14]      
  0x00218BE0  03d3                    add      edx, ebx                       
  0x00218BE2  03cb                    add      ecx, ebx                       
  0x00218BE4  4e                      dec      esi                            
  0x00218BE5  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00218BEB  890d149f2900            mov      dword ptr [0x299f14], ecx      
  0x00218BF1  0f8529ffffff            jne      0x218b20                       
  0x00218BF7  8b442418                mov      eax, dword ptr [esp + 0x18]    
  0x00218BFB  03c7                    add      eax, edi                       
  0x00218BFD  5f                      pop      edi                            
  0x00218BFE  5e                      pop      esi                            
  0x00218BFF  5d                      pop      ebp                            
  0x00218C00  5b                      pop      ebx                            
  0x00218C01  c3                      ret                                     
; end of function
  0x00218C02  cc                      int3                                    
  0x00218C03  cc                      int3                                    
  0x00218C04  cc                      int3                                    
  0x00218C05  cc                      int3                                    
  0x00218C06  cc                      int3                                    
  0x00218C07  cc                      int3                                    
  0x00218C08  cc                      int3                                    
  0x00218C09  cc                      int3                                    
  0x00218C0A  cc                      int3                                    
  0x00218C0B  cc                      int3                                    
  0x00218C0C  cc                      int3                                    
  0x00218C0D  cc                      int3                                    
  0x00218C0E  cc                      int3                                    
  0x00218C0F  cc                      int3                                    

; ============================================================
; Function: sub_00218C10
; Start: 0x00218C10  End: 0x00218CEC  Size: 220 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218C10:
  0x00218C10  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00218C14  85c0                    test     eax, eax                       
  0x00218C16  53                      push     ebx                            
  0x00218C17  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x00218C1B  0f84c9000000            je       0x218cea                       
  0x00218C21  55                      push     ebp                            
  0x00218C22  56                      push     esi                            
  0x00218C23  89442410                mov      dword ptr [esp + 0x10], eax    
  0x00218C27  57                      push     edi                            
  0x00218C28  eb06                    jmp      0x218c30                       
  0x00218C2A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x00218C28 (jump), 0x00218CE1 (cond_jump)
  0x00218C30  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x00218C35  0fb600                  movzx    eax, byte ptr [eax]            
  0x00218C38  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00218C3E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00218C41  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x00218C47  c1e102                  shl      ecx, 2                         
  0x00218C4A  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x00218C50  c1e002                  shl      eax, 2                         
  0x00218C53  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x00218C59  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x00218C5F  03d7                    add      edx, edi                       
  0x00218C61  8bb938ab2900            mov      edi, dword ptr [ecx + 0x29ab38] 
  0x00218C67  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00218C6D  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00218C70  8b0485c05e2900          mov      eax, dword ptr [eax*4 + 0x295ec0] 
  0x00218C77  41                      inc      ecx                            
  0x00218C78  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00218C7E  33c9                    xor      ecx, ecx                       
  0x00218C80  8a6d00                  mov      ch, byte ptr [ebp]             
  0x00218C83  0b0cb8                  or       ecx, dword ptr [eax + edi*4]   
  0x00218C86  8b3c90                  mov      edi, dword ptr [eax + edx*4]   
  0x00218C89  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218C8F  c1e108                  shl      ecx, 8                         
  0x00218C92  0bcf                    or       ecx, edi                       
  0x00218C94  8b3cb0                  mov      edi, dword ptr [eax + esi*4]   
  0x00218C97  c1e108                  shl      ecx, 8                         
  0x00218C9A  0bcf                    or       ecx, edi                       
  0x00218C9C  45                      inc      ebp                            
  0x00218C9D  8bc1                    mov      eax, ecx                       
  0x00218C9F  892d289f2900            mov      dword ptr [0x299f28], ebp      
  0x00218CA5  8902                    mov      dword ptr [edx], eax           
  0x00218CA7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218CAD  894104                  mov      dword ptr [ecx + 4], eax       
  0x00218CB0  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218CB6  83c208                  add      edx, 8                         
  0x00218CB9  43                      inc      ebx                            
  0x00218CBA  f6c301                  test     bl, 1                          
  0x00218CBD  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00218CC3  7518                    jne      0x218cdd                       
  0x00218CC5  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x00218CCB  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x00218CD0  41                      inc      ecx                            
  0x00218CD1  40                      inc      eax                            
  0x00218CD2  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x00218CD8  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x00218CC3 (cond_jump)
  0x00218CDD  ff4c2414                dec      dword ptr [esp + 0x14]         
  0x00218CE1  0f8549ffffff            jne      0x218c30                       
  0x00218CE7  5f                      pop      edi                            
  0x00218CE8  5e                      pop      esi                            
  0x00218CE9  5d                      pop      ebp                            
                                        ; XREF: 0x00218C1B (cond_jump)
  0x00218CEA  5b                      pop      ebx                            
  0x00218CEB  c3                      ret                                     
; end of function
  0x00218CEC  cc                      int3                                    
  0x00218CED  cc                      int3                                    
  0x00218CEE  cc                      int3                                    
  0x00218CEF  cc                      int3                                    

; ============================================================
; Function: sub_00218CF0
; Start: 0x00218CF0  End: 0x00218E1B  Size: 299 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218CF0:
  0x00218CF0  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00218CF4  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00218CF8  53                      push     ebx                            
  0x00218CF9  55                      push     ebp                            
  0x00218CFA  56                      push     esi                            
  0x00218CFB  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x00218CFF  57                      push     edi                            
                                        ; XREF: 0x00218E10 (cond_jump)
  0x00218D00  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00218D06  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x00218D09  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x00218D0F  0fb612                  movzx    edx, byte ptr [edx]            
  0x00218D12  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x00218D18  c1e102                  shl      ecx, 2                         
  0x00218D1B  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x00218D21  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x00218D27  c1e202                  shl      edx, 2                         
  0x00218D2A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x00218D30  03f3                    add      esi, ebx                       
  0x00218D32  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x00218D38  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x00218D3B  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00218D42  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00218D48  43                      inc      ebx                            
  0x00218D49  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x00218D4F  33db                    xor      ebx, ebx                       
  0x00218D51  8a7d00                  mov      bh, byte ptr [ebp]             
  0x00218D54  0b1c91                  or       ebx, dword ptr [ecx + edx*4]   
  0x00218D57  c1e308                  shl      ebx, 8                         
  0x00218D5A  0b1cb1                  or       ebx, dword ptr [ecx + esi*4]   
  0x00218D5D  c1e308                  shl      ebx, 8                         
  0x00218D60  0b1cb9                  or       ebx, dword ptr [ecx + edi*4]   
  0x00218D63  45                      inc      ebp                            
  0x00218D64  8bcb                    mov      ecx, ebx                       
  0x00218D66  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00218D6C  892d289f2900            mov      dword ptr [0x299f28], ebp      
  0x00218D72  890b                    mov      dword ptr [ebx], ecx           
  0x00218D74  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00218D7A  894b04                  mov      dword ptr [ebx + 4], ecx       
  0x00218D7D  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x00218D83  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x00218D86  8b2d2c9f2900            mov      ebp, dword ptr [0x299f2c]      
  0x00218D8C  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00218D93  43                      inc      ebx                            
  0x00218D94  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x00218D9A  33db                    xor      ebx, ebx                       
  0x00218D9C  8a7d00                  mov      bh, byte ptr [ebp]             
  0x00218D9F  0b1c91                  or       ebx, dword ptr [ecx + edx*4]   
  0x00218DA2  8b14b1                  mov      edx, dword ptr [ecx + esi*4]   
  0x00218DA5  c1e308                  shl      ebx, 8                         
  0x00218DA8  0bda                    or       ebx, edx                       
  0x00218DAA  8b14b9                  mov      edx, dword ptr [ecx + edi*4]   
  0x00218DAD  c1e308                  shl      ebx, 8                         
  0x00218DB0  0bda                    or       ebx, edx                       
  0x00218DB2  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00218DB8  45                      inc      ebp                            
  0x00218DB9  8bcb                    mov      ecx, ebx                       
  0x00218DBB  892d2c9f2900            mov      dword ptr [0x299f2c], ebp      
  0x00218DC1  890a                    mov      dword ptr [edx], ecx           
  0x00218DC3  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00218DC9  894a04                  mov      dword ptr [edx + 4], ecx       
  0x00218DCC  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00218DD2  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x00218DD8  b908000000              mov      ecx, 8                         
  0x00218DDD  03f9                    add      edi, ecx                       
  0x00218DDF  03f1                    add      esi, ecx                       
  0x00218DE1  40                      inc      eax                            
  0x00218DE2  a801                    test     al, 1                          
  0x00218DE4  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x00218DEA  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x00218DF0  751a                    jne      0x218e0c                       
  0x00218DF2  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00218DF8  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00218DFE  42                      inc      edx                            
  0x00218DFF  41                      inc      ecx                            
  0x00218E00  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x00218E06  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x00218DF0 (cond_jump)
  0x00218E0C  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x00218E10  0f85eafeffff            jne      0x218d00                       
  0x00218E16  5f                      pop      edi                            
  0x00218E17  5e                      pop      esi                            
  0x00218E18  5d                      pop      ebp                            
  0x00218E19  5b                      pop      ebx                            
  0x00218E1A  c3                      ret                                     
; end of function
  0x00218E1B  cc                      int3                                    
  0x00218E1C  cc                      int3                                    
  0x00218E1D  cc                      int3                                    
  0x00218E1E  cc                      int3                                    
  0x00218E1F  cc                      int3                                    

; ============================================================
; Function: sub_00218E20
; Start: 0x00218E20  End: 0x00218F02  Size: 226 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218E20:
  0x00218E20  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00218E24  85c0                    test     eax, eax                       
  0x00218E26  53                      push     ebx                            
  0x00218E27  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x00218E2B  0f84cf000000            je       0x218f00                       
  0x00218E31  55                      push     ebp                            
  0x00218E32  56                      push     esi                            
  0x00218E33  89442410                mov      dword ptr [esp + 0x10], eax    
  0x00218E37  57                      push     edi                            
  0x00218E38  eb06                    jmp      0x218e40                       
  0x00218E3A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x00218E38 (jump), 0x00218EF7 (cond_jump)
  0x00218E40  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x00218E45  0fb600                  movzx    eax, byte ptr [eax]            
  0x00218E48  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x00218E4E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00218E51  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x00218E57  c1e102                  shl      ecx, 2                         
  0x00218E5A  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x00218E60  c1e002                  shl      eax, 2                         
  0x00218E63  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x00218E69  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x00218E6F  03d7                    add      edx, edi                       
  0x00218E71  8bb938ab2900            mov      edi, dword ptr [ecx + 0x29ab38] 
  0x00218E77  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00218E7D  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00218E80  8b0485c05e2900          mov      eax, dword ptr [eax*4 + 0x295ec0] 
  0x00218E87  41                      inc      ecx                            
  0x00218E88  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x00218E8E  33c9                    xor      ecx, ecx                       
  0x00218E90  8a6d00                  mov      ch, byte ptr [ebp]             
  0x00218E93  0b0cb8                  or       ecx, dword ptr [eax + edi*4]   
  0x00218E96  8b3c90                  mov      edi, dword ptr [eax + edx*4]   
  0x00218E99  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218E9F  c1e108                  shl      ecx, 8                         
  0x00218EA2  0bcf                    or       ecx, edi                       
  0x00218EA4  8b3cb0                  mov      edi, dword ptr [eax + esi*4]   
  0x00218EA7  c1e108                  shl      ecx, 8                         
  0x00218EAA  0bcf                    or       ecx, edi                       
  0x00218EAC  45                      inc      ebp                            
  0x00218EAD  8bc1                    mov      eax, ecx                       
  0x00218EAF  892d289f2900            mov      dword ptr [0x299f28], ebp      
  0x00218EB5  8902                    mov      dword ptr [edx], eax           
  0x00218EB7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00218EBD  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x00218EC3  89040a                  mov      dword ptr [edx + ecx], eax     
  0x00218EC6  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00218ECC  83c204                  add      edx, 4                         
  0x00218ECF  43                      inc      ebx                            
  0x00218ED0  f6c301                  test     bl, 1                          
  0x00218ED3  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00218ED9  7518                    jne      0x218ef3                       
  0x00218EDB  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x00218EE1  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x00218EE6  41                      inc      ecx                            
  0x00218EE7  40                      inc      eax                            
  0x00218EE8  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x00218EEE  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x00218ED9 (cond_jump)
  0x00218EF3  ff4c2414                dec      dword ptr [esp + 0x14]         
  0x00218EF7  0f8543ffffff            jne      0x218e40                       
  0x00218EFD  5f                      pop      edi                            
  0x00218EFE  5e                      pop      esi                            
  0x00218EFF  5d                      pop      ebp                            
                                        ; XREF: 0x00218E2B (cond_jump)
  0x00218F00  5b                      pop      ebx                            
  0x00218F01  c3                      ret                                     
; end of function
  0x00218F02  cc                      int3                                    
  0x00218F03  cc                      int3                                    
  0x00218F04  cc                      int3                                    
  0x00218F05  cc                      int3                                    
  0x00218F06  cc                      int3                                    
  0x00218F07  cc                      int3                                    
  0x00218F08  cc                      int3                                    
  0x00218F09  cc                      int3                                    
  0x00218F0A  cc                      int3                                    
  0x00218F0B  cc                      int3                                    
  0x00218F0C  cc                      int3                                    
  0x00218F0D  cc                      int3                                    
  0x00218F0E  cc                      int3                                    
  0x00218F0F  cc                      int3                                    

; ============================================================
; Function: sub_00218F10
; Start: 0x00218F10  End: 0x00219047  Size: 311 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00218F10:
  0x00218F10  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00218F14  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00218F18  53                      push     ebx                            
  0x00218F19  55                      push     ebp                            
  0x00218F1A  56                      push     esi                            
  0x00218F1B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x00218F1F  57                      push     edi                            
                                        ; XREF: 0x0021903C (cond_jump)
  0x00218F20  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00218F26  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x00218F29  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x00218F2F  0fb612                  movzx    edx, byte ptr [edx]            
  0x00218F32  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x00218F38  c1e102                  shl      ecx, 2                         
  0x00218F3B  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x00218F41  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x00218F47  c1e202                  shl      edx, 2                         
  0x00218F4A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x00218F50  03f3                    add      esi, ebx                       
  0x00218F52  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x00218F58  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x00218F5B  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00218F62  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00218F68  43                      inc      ebx                            
  0x00218F69  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x00218F6F  33db                    xor      ebx, ebx                       
  0x00218F71  8a7d00                  mov      bh, byte ptr [ebp]             
  0x00218F74  0b1c91                  or       ebx, dword ptr [ecx + edx*4]   
  0x00218F77  c1e308                  shl      ebx, 8                         
  0x00218F7A  0b1cb1                  or       ebx, dword ptr [ecx + esi*4]   
  0x00218F7D  c1e308                  shl      ebx, 8                         
  0x00218F80  0b1cb9                  or       ebx, dword ptr [ecx + edi*4]   
  0x00218F83  45                      inc      ebp                            
  0x00218F84  8bcb                    mov      ecx, ebx                       
  0x00218F86  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x00218F8C  892d289f2900            mov      dword ptr [0x299f28], ebp      
  0x00218F92  890b                    mov      dword ptr [ebx], ecx           
  0x00218F94  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x00218F9A  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x00218FA0  890c2b                  mov      dword ptr [ebx + ebp], ecx     
  0x00218FA3  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x00218FA9  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x00218FAC  8b2d2c9f2900            mov      ebp, dword ptr [0x299f2c]      
  0x00218FB2  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00218FB9  43                      inc      ebx                            
  0x00218FBA  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x00218FC0  33db                    xor      ebx, ebx                       
  0x00218FC2  8a7d00                  mov      bh, byte ptr [ebp]             
  0x00218FC5  0b1c91                  or       ebx, dword ptr [ecx + edx*4]   
  0x00218FC8  8b14b1                  mov      edx, dword ptr [ecx + esi*4]   
  0x00218FCB  c1e308                  shl      ebx, 8                         
  0x00218FCE  0bda                    or       ebx, edx                       
  0x00218FD0  8b14b9                  mov      edx, dword ptr [ecx + edi*4]   
  0x00218FD3  c1e308                  shl      ebx, 8                         
  0x00218FD6  0bda                    or       ebx, edx                       
  0x00218FD8  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00218FDE  45                      inc      ebp                            
  0x00218FDF  8bcb                    mov      ecx, ebx                       
  0x00218FE1  892d2c9f2900            mov      dword ptr [0x299f2c], ebp      
  0x00218FE7  890a                    mov      dword ptr [edx], ecx           
  0x00218FE9  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00218FEF  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00218FF5  890c32                  mov      dword ptr [edx + esi], ecx     
  0x00218FF8  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00218FFE  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x00219004  b904000000              mov      ecx, 4                         
  0x00219009  03f9                    add      edi, ecx                       
  0x0021900B  03f1                    add      esi, ecx                       
  0x0021900D  40                      inc      eax                            
  0x0021900E  a801                    test     al, 1                          
  0x00219010  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x00219016  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021901C  751a                    jne      0x219038                       
  0x0021901E  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00219024  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021902A  42                      inc      edx                            
  0x0021902B  41                      inc      ecx                            
  0x0021902C  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x00219032  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021901C (cond_jump)
  0x00219038  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x0021903C  0f85defeffff            jne      0x218f20                       
  0x00219042  5f                      pop      edi                            
  0x00219043  5e                      pop      esi                            
  0x00219044  5d                      pop      ebp                            
  0x00219045  5b                      pop      ebx                            
  0x00219046  c3                      ret                                     
; end of function
  0x00219047  cc                      int3                                    
  0x00219048  cc                      int3                                    
  0x00219049  cc                      int3                                    
  0x0021904A  cc                      int3                                    
  0x0021904B  cc                      int3                                    
  0x0021904C  cc                      int3                                    
  0x0021904D  cc                      int3                                    
  0x0021904E  cc                      int3                                    
  0x0021904F  cc                      int3                                    

; ============================================================
; Function: sub_00219050
; Start: 0x00219050  End: 0x0021914B  Size: 251 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00219050:
  0x00219050  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00219054  85c0                    test     eax, eax                       
  0x00219056  53                      push     ebx                            
  0x00219057  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x0021905B  0f84e8000000            je       0x219149                       
  0x00219061  55                      push     ebp                            
  0x00219062  56                      push     esi                            
  0x00219063  89442410                mov      dword ptr [esp + 0x10], eax    
  0x00219067  57                      push     edi                            
  0x00219068  eb06                    jmp      0x219070                       
  0x0021906A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x00219068 (jump), 0x00219140 (cond_jump)
  0x00219070  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x00219075  0fb600                  movzx    eax, byte ptr [eax]            
  0x00219078  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021907E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00219081  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x00219087  c1e102                  shl      ecx, 2                         
  0x0021908A  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x00219090  c1e002                  shl      eax, 2                         
  0x00219093  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x00219099  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x0021909F  03d7                    add      edx, edi                       
  0x002190A1  8bb938ab2900            mov      edi, dword ptr [ecx + 0x29ab38] 
  0x002190A7  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x002190AD  0fb601                  movzx    eax, byte ptr [ecx]            
  0x002190B0  8b0485c05e2900          mov      eax, dword ptr [eax*4 + 0x295ec0] 
  0x002190B7  41                      inc      ecx                            
  0x002190B8  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x002190BE  33c9                    xor      ecx, ecx                       
  0x002190C0  8a6d00                  mov      ch, byte ptr [ebp]             
  0x002190C3  0b0cb8                  or       ecx, dword ptr [eax + edi*4]   
  0x002190C6  8b3c90                  mov      edi, dword ptr [eax + edx*4]   
  0x002190C9  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x002190CF  c1e108                  shl      ecx, 8                         
  0x002190D2  0bcf                    or       ecx, edi                       
  0x002190D4  8b3cb0                  mov      edi, dword ptr [eax + esi*4]   
  0x002190D7  c1e108                  shl      ecx, 8                         
  0x002190DA  0bcf                    or       ecx, edi                       
  0x002190DC  8bc1                    mov      eax, ecx                       
  0x002190DE  45                      inc      ebp                            
  0x002190DF  892d289f2900            mov      dword ptr [0x299f28], ebp      
  0x002190E5  8902                    mov      dword ptr [edx], eax           
  0x002190E7  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002190ED  894104                  mov      dword ptr [ecx + 4], eax       
  0x002190F0  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x002190F6  8b15309f2900            mov      edx, dword ptr [0x299f30]      
  0x002190FC  89040a                  mov      dword ptr [edx + ecx], eax     
  0x002190FF  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00219105  8b0d309f2900            mov      ecx, dword ptr [0x299f30]      
  0x0021910B  89441104                mov      dword ptr [ecx + edx + 4], eax 
  0x0021910F  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x00219115  83c208                  add      edx, 8                         
  0x00219118  43                      inc      ebx                            
  0x00219119  f6c301                  test     bl, 1                          
  0x0021911C  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00219122  7518                    jne      0x21913c                       
  0x00219124  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x0021912A  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x0021912F  41                      inc      ecx                            
  0x00219130  40                      inc      eax                            
  0x00219131  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x00219137  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x00219122 (cond_jump)
  0x0021913C  ff4c2414                dec      dword ptr [esp + 0x14]         
  0x00219140  0f852affffff            jne      0x219070                       
  0x00219146  5f                      pop      edi                            
  0x00219147  5e                      pop      esi                            
  0x00219148  5d                      pop      ebp                            
                                        ; XREF: 0x0021905B (cond_jump)
  0x00219149  5b                      pop      ebx                            
  0x0021914A  c3                      ret                                     
; end of function
  0x0021914B  cc                      int3                                    
  0x0021914C  cc                      int3                                    
  0x0021914D  cc                      int3                                    
  0x0021914E  cc                      int3                                    
  0x0021914F  cc                      int3                                    

; ============================================================
; Function: sub_00219150
; Start: 0x00219150  End: 0x002192B9  Size: 361 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00219150:
  0x00219150  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00219154  8b442408                mov      eax, dword ptr [esp + 8]       
  0x00219158  53                      push     ebx                            
  0x00219159  55                      push     ebp                            
  0x0021915A  56                      push     esi                            
  0x0021915B  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x0021915F  57                      push     edi                            
                                        ; XREF: 0x002192AE (cond_jump)
  0x00219160  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00219166  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x00219169  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x0021916F  0fb612                  movzx    edx, byte ptr [edx]            
  0x00219172  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x00219178  c1e102                  shl      ecx, 2                         
  0x0021917B  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x00219181  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x00219187  c1e202                  shl      edx, 2                         
  0x0021918A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x00219190  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00219196  03f3                    add      esi, ebx                       
  0x00219198  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x0021919E  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x002191A1  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x002191A8  43                      inc      ebx                            
  0x002191A9  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x002191AF  33db                    xor      ebx, ebx                       
  0x002191B1  8a7d00                  mov      bh, byte ptr [ebp]             
  0x002191B4  0b1c91                  or       ebx, dword ptr [ecx + edx*4]   
  0x002191B7  c1e308                  shl      ebx, 8                         
  0x002191BA  0b1cb1                  or       ebx, dword ptr [ecx + esi*4]   
  0x002191BD  c1e308                  shl      ebx, 8                         
                                        ; XREF: 0x000D83EF (data_imm)
  0x002191C0  0b1cb9                  or       ebx, dword ptr [ecx + edi*4]   
  0x002191C3  45                      inc      ebp                            
  0x002191C4  8bcb                    mov      ecx, ebx                       
  0x002191C6  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x002191CC  892d289f2900            mov      dword ptr [0x299f28], ebp      
  0x002191D2  890b                    mov      dword ptr [ebx], ecx           
  0x002191D4  8b1d109f2900            mov      ebx, dword ptr [0x299f10]      
  0x002191DA  894b04                  mov      dword ptr [ebx + 4], ecx       
  0x002191DD  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x002191E3  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x002191E9  890c2b                  mov      dword ptr [ebx + ebp], ecx     
  0x002191EC  8b2d109f2900            mov      ebp, dword ptr [0x299f10]      
  0x002191F2  8b1d309f2900            mov      ebx, dword ptr [0x299f30]      
  0x002191F8  894c2b04                mov      dword ptr [ebx + ebp + 4], ecx 
  0x002191FC  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x00219202  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x00219205  8b2d2c9f2900            mov      ebp, dword ptr [0x299f2c]      
  0x0021920B  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00219212  43                      inc      ebx                            
  0x00219213  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x00219219  33db                    xor      ebx, ebx                       
  0x0021921B  8a7d00                  mov      bh, byte ptr [ebp]             
  0x0021921E  0b1c91                  or       ebx, dword ptr [ecx + edx*4]   
  0x00219221  8b14b1                  mov      edx, dword ptr [ecx + esi*4]   
  0x00219224  c1e308                  shl      ebx, 8                         
  0x00219227  0bda                    or       ebx, edx                       
  0x00219229  8b14b9                  mov      edx, dword ptr [ecx + edi*4]   
  0x0021922C  c1e308                  shl      ebx, 8                         
  0x0021922F  0bda                    or       ebx, edx                       
  0x00219231  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00219237  8bcb                    mov      ecx, ebx                       
  0x00219239  45                      inc      ebp                            
  0x0021923A  892d2c9f2900            mov      dword ptr [0x299f2c], ebp      
  0x00219240  890a                    mov      dword ptr [edx], ecx           
  0x00219242  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00219248  894a04                  mov      dword ptr [edx + 4], ecx       
  0x0021924B  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00219251  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00219257  890c32                  mov      dword ptr [edx + esi], ecx     
  0x0021925A  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00219260  8b35309f2900            mov      esi, dword ptr [0x299f30]      
  0x00219266  894c3204                mov      dword ptr [edx + esi + 4], ecx 
  0x0021926A  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x00219270  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x00219276  b908000000              mov      ecx, 8                         
  0x0021927B  03f9                    add      edi, ecx                       
  0x0021927D  03f1                    add      esi, ecx                       
  0x0021927F  40                      inc      eax                            
  0x00219280  a801                    test     al, 1                          
  0x00219282  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x00219288  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x0021928E  751a                    jne      0x2192aa                       
  0x00219290  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x00219296  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021929C  42                      inc      edx                            
  0x0021929D  41                      inc      ecx                            
  0x0021929E  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x002192A4  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x0021928E (cond_jump)
  0x002192AA  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x002192AE  0f85acfeffff            jne      0x219160                       
  0x002192B4  5f                      pop      edi                            
  0x002192B5  5e                      pop      esi                            
  0x002192B6  5d                      pop      ebp                            
  0x002192B7  5b                      pop      ebx                            
  0x002192B8  c3                      ret                                     
; end of function
  0x002192B9  cc                      int3                                    
  0x002192BA  cc                      int3                                    
  0x002192BB  cc                      int3                                    
  0x002192BC  cc                      int3                                    
  0x002192BD  cc                      int3                                    
  0x002192BE  cc                      int3                                    
  0x002192BF  cc                      int3                                    

; ============================================================
; Function: sub_002192C0
; Start: 0x002192C0  End: 0x00219324  Size: 100 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002192C0:
  0x002192C0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x002192C4  85c0                    test     eax, eax                       
  0x002192C6  745b                    je       0x219323                       
  0x002192C8  56                      push     esi                            
  0x002192C9  8da42400000000          lea      esp, [esp]                     
                                        ; XREF: 0x00219320 (cond_jump)
  0x002192D0  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x002192D6  0fb611                  movzx    edx, byte ptr [ecx]            
  0x002192D9  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x002192DF  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x002192E2  8b3495109b2900          mov      esi, dword ptr [edx*4 + 0x299b10] 
  0x002192E9  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x002192EF  c1e118                  shl      ecx, 0x18                      
  0x002192F2  0bce                    or       ecx, esi                       
  0x002192F4  890a                    mov      dword ptr [edx], ecx           
  0x002192F6  8b15289f2900            mov      edx, dword ptr [0x299f28]      
  0x002192FC  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x00219302  42                      inc      edx                            
  0x00219303  8915289f2900            mov      dword ptr [0x299f28], edx      
  0x00219309  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021930F  41                      inc      ecx                            
  0x00219310  83c204                  add      edx, 4                         
  0x00219313  48                      dec      eax                            
  0x00219314  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021931A  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x00219320  75ae                    jne      0x2192d0                       
  0x00219322  5e                      pop      esi                            
                                        ; XREF: 0x002192C6 (cond_jump)
  0x00219323  c3                      ret                                     
; end of function
  0x00219324  cc                      int3                                    
  0x00219325  cc                      int3                                    
  0x00219326  cc                      int3                                    
  0x00219327  cc                      int3                                    
  0x00219328  cc                      int3                                    
  0x00219329  cc                      int3                                    
  0x0021932A  cc                      int3                                    
  0x0021932B  cc                      int3                                    
  0x0021932C  cc                      int3                                    
  0x0021932D  cc                      int3                                    
  0x0021932E  cc                      int3                                    
  0x0021932F  cc                      int3                                    

; ============================================================
; Function: sub_00219330
; Start: 0x00219330  End: 0x002193ED  Size: 189 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_00219330:
  0x00219330  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x00219334  53                      push     ebx                            
  0x00219335  56                      push     esi                            
  0x00219336  8bc1                    mov      eax, ecx                       
  0x00219338  ba04000000              mov      edx, 4                         
  0x0021933D  57                      push     edi                            
  0x0021933E  8bff                    mov      edi, edi                       
                                        ; XREF: 0x002193DD (cond_jump)
  0x00219340  8b35189f2900            mov      esi, dword ptr [0x299f18]      
  0x00219346  0fb636                  movzx    esi, byte ptr [esi]            
  0x00219349  8b1cb5109b2900          mov      ebx, dword ptr [esi*4 + 0x299b10] 
  0x00219350  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x00219356  0fb63f                  movzx    edi, byte ptr [edi]            
  0x00219359  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x0021935F  c1e718                  shl      edi, 0x18                      
  0x00219362  0bfb                    or       edi, ebx                       
  0x00219364  893e                    mov      dword ptr [esi], edi           
  0x00219366  8b3d289f2900            mov      edi, dword ptr [0x299f28]      
  0x0021936C  8b35189f2900            mov      esi, dword ptr [0x299f18]      
  0x00219372  47                      inc      edi                            
  0x00219373  46                      inc      esi                            
  0x00219374  893d289f2900            mov      dword ptr [0x299f28], edi      
  0x0021937A  8b3d2c9f2900            mov      edi, dword ptr [0x299f2c]      
  0x00219380  8935189f2900            mov      dword ptr [0x299f18], esi      
  0x00219386  0fb63f                  movzx    edi, byte ptr [edi]            
  0x00219389  8b351c9f2900            mov      esi, dword ptr [0x299f1c]      
  0x0021938F  0fb636                  movzx    esi, byte ptr [esi]            
  0x00219392  8b1cb5109b2900          mov      ebx, dword ptr [esi*4 + 0x299b10] 
  0x00219399  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x0021939F  c1e718                  shl      edi, 0x18                      
  0x002193A2  0bfb                    or       edi, ebx                       
  0x002193A4  893e                    mov      dword ptr [esi], edi           
  0x002193A6  8b352c9f2900            mov      esi, dword ptr [0x299f2c]      
  0x002193AC  8b3d1c9f2900            mov      edi, dword ptr [0x299f1c]      
  0x002193B2  46                      inc      esi                            
  0x002193B3  47                      inc      edi                            
  0x002193B4  89352c9f2900            mov      dword ptr [0x299f2c], esi      
  0x002193BA  8b35109f2900            mov      esi, dword ptr [0x299f10]      
  0x002193C0  893d1c9f2900            mov      dword ptr [0x299f1c], edi      
  0x002193C6  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x002193CC  03f2                    add      esi, edx                       
  0x002193CE  03fa                    add      edi, edx                       
  0x002193D0  48                      dec      eax                            
  0x002193D1  8935109f2900            mov      dword ptr [0x299f10], esi      
  0x002193D7  893d149f2900            mov      dword ptr [0x299f14], edi      
  0x002193DD  0f855dffffff            jne      0x219340                       
  0x002193E3  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x002193E7  5f                      pop      edi                            
  0x002193E8  5e                      pop      esi                            
  0x002193E9  03c1                    add      eax, ecx                       
  0x002193EB  5b                      pop      ebx                            
  0x002193EC  c3                      ret                                     
; end of function
  0x002193ED  cc                      int3                                    
  0x002193EE  cc                      int3                                    
  0x002193EF  cc                      int3                                    

; ============================================================
; Function: sub_002193F0
; Start: 0x002193F0  End: 0x002194C9  Size: 217 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002193F0:
  0x002193F0  8b442408                mov      eax, dword ptr [esp + 8]       
  0x002193F4  85c0                    test     eax, eax                       
  0x002193F6  53                      push     ebx                            
  0x002193F7  8b5c2408                mov      ebx, dword ptr [esp + 8]       
  0x002193FB  0f84c6000000            je       0x2194c7                       
  0x00219401  55                      push     ebp                            
  0x00219402  56                      push     esi                            
  0x00219403  89442410                mov      dword ptr [esp + 0x10], eax    
  0x00219407  57                      push     edi                            
  0x00219408  eb06                    jmp      0x219410                       
  0x0021940A  8d9b00000000            lea      ebx, [ebx]                     
                                        ; XREF: 0x00219408 (jump), 0x002194BE (cond_jump)
  0x00219410  a1209f2900              mov      eax, dword ptr [0x299f20]      
  0x00219415  0fb600                  movzx    eax, byte ptr [eax]            
  0x00219418  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x0021941E  0fb609                  movzx    ecx, byte ptr [ecx]            
  0x00219421  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x00219427  c1e102                  shl      ecx, 2                         
  0x0021942A  8b9138a32900            mov      edx, dword ptr [ecx + 0x29a338] 
  0x00219430  c1e002                  shl      eax, 2                         
  0x00219433  8bb838a72900            mov      edi, dword ptr [eax + 0x29a738] 
  0x00219439  8bb0389f2900            mov      esi, dword ptr [eax + 0x299f38] 
  0x0021943F  03d7                    add      edx, edi                       
  0x00219441  8bb938ab2900            mov      edi, dword ptr [ecx + 0x29ab38] 
  0x00219447  8b0d189f2900            mov      ecx, dword ptr [0x299f18]      
  0x0021944D  0fb601                  movzx    eax, byte ptr [ecx]            
  0x00219450  8b0485c05e2900          mov      eax, dword ptr [eax*4 + 0x295ec0] 
  0x00219457  41                      inc      ecx                            
  0x00219458  890d189f2900            mov      dword ptr [0x299f18], ecx      
  0x0021945E  33c9                    xor      ecx, ecx                       
  0x00219460  8a6d00                  mov      ch, byte ptr [ebp]             
  0x00219463  8b2cb8                  mov      ebp, dword ptr [eax + edi*4]   
  0x00219466  8b3c90                  mov      edi, dword ptr [eax + edx*4]   
  0x00219469  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021946F  0bcd                    or       ecx, ebp                       
  0x00219471  c1e108                  shl      ecx, 8                         
  0x00219474  0bcf                    or       ecx, edi                       
  0x00219476  8b3cb0                  mov      edi, dword ptr [eax + esi*4]   
  0x00219479  c1e108                  shl      ecx, 8                         
  0x0021947C  0bcf                    or       ecx, edi                       
  0x0021947E  890a                    mov      dword ptr [edx], ecx           
  0x00219480  8b35289f2900            mov      esi, dword ptr [0x299f28]      
  0x00219486  8b15109f2900            mov      edx, dword ptr [0x299f10]      
  0x0021948C  46                      inc      esi                            
  0x0021948D  83c204                  add      edx, 4                         
  0x00219490  43                      inc      ebx                            
  0x00219491  f6c301                  test     bl, 1                          
  0x00219494  8935289f2900            mov      dword ptr [0x299f28], esi      
  0x0021949A  8915109f2900            mov      dword ptr [0x299f10], edx      
  0x002194A0  7518                    jne      0x2194ba                       
  0x002194A2  8b0d209f2900            mov      ecx, dword ptr [0x299f20]      
  0x002194A8  a1249f2900              mov      eax, dword ptr [0x299f24]      
  0x002194AD  41                      inc      ecx                            
  0x002194AE  40                      inc      eax                            
  0x002194AF  890d209f2900            mov      dword ptr [0x299f20], ecx      
  0x002194B5  a3249f2900              mov      dword ptr [0x299f24], eax      
                                        ; XREF: 0x002194A0 (cond_jump)
  0x002194BA  ff4c2414                dec      dword ptr [esp + 0x14]         
  0x002194BE  0f854cffffff            jne      0x219410                       
  0x002194C4  5f                      pop      edi                            
  0x002194C5  5e                      pop      esi                            
  0x002194C6  5d                      pop      ebp                            
                                        ; XREF: 0x002193FB (cond_jump)
  0x002194C7  5b                      pop      ebx                            
  0x002194C8  c3                      ret                                     
; end of function
  0x002194C9  cc                      int3                                    
  0x002194CA  cc                      int3                                    
  0x002194CB  cc                      int3                                    
  0x002194CC  cc                      int3                                    
  0x002194CD  cc                      int3                                    
  0x002194CE  cc                      int3                                    
  0x002194CF  cc                      int3                                    

; ============================================================
; Function: sub_002194D0
; Start: 0x002194D0  End: 0x002195F8  Size: 296 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002194D0:
  0x002194D0  8b4c2404                mov      ecx, dword ptr [esp + 4]       
  0x002194D4  8b442408                mov      eax, dword ptr [esp + 8]       
  0x002194D8  53                      push     ebx                            
  0x002194D9  55                      push     ebp                            
  0x002194DA  56                      push     esi                            
  0x002194DB  894c2414                mov      dword ptr [esp + 0x14], ecx    
  0x002194DF  57                      push     edi                            
                                        ; XREF: 0x002195ED (cond_jump)
  0x002194E0  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x002194E6  0fb60a                  movzx    ecx, byte ptr [edx]            
  0x002194E9  8b15249f2900            mov      edx, dword ptr [0x299f24]      
  0x002194EF  0fb612                  movzx    edx, byte ptr [edx]            
  0x002194F2  8b2d289f2900            mov      ebp, dword ptr [0x299f28]      
  0x002194F8  c1e102                  shl      ecx, 2                         
  0x002194FB  8b9938a72900            mov      ebx, dword ptr [ecx + 0x29a738] 
  0x00219501  8bb9389f2900            mov      edi, dword ptr [ecx + 0x299f38] 
  0x00219507  c1e202                  shl      edx, 2                         
  0x0021950A  8bb238a32900            mov      esi, dword ptr [edx + 0x29a338] 
  0x00219510  03f3                    add      esi, ebx                       
  0x00219512  8b1d189f2900            mov      ebx, dword ptr [0x299f18]      
  0x00219518  0fb60b                  movzx    ecx, byte ptr [ebx]            
  0x0021951B  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00219522  8b9238ab2900            mov      edx, dword ptr [edx + 0x29ab38] 
  0x00219528  43                      inc      ebx                            
  0x00219529  891d189f2900            mov      dword ptr [0x299f18], ebx      
  0x0021952F  33db                    xor      ebx, ebx                       
  0x00219531  8a7d00                  mov      bh, byte ptr [ebp]             
  0x00219534  0b1c91                  or       ebx, dword ptr [ecx + edx*4]   
  0x00219537  8b2cb1                  mov      ebp, dword ptr [ecx + esi*4]   
  0x0021953A  c1e308                  shl      ebx, 8                         
  0x0021953D  0bdd                    or       ebx, ebp                       
  0x0021953F  8b2cb9                  mov      ebp, dword ptr [ecx + edi*4]   
  0x00219542  8b0d109f2900            mov      ecx, dword ptr [0x299f10]      
  0x00219548  c1e308                  shl      ebx, 8                         
  0x0021954B  0bdd                    or       ebx, ebp                       
  0x0021954D  8919                    mov      dword ptr [ecx], ebx           
  0x0021954F  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x00219555  8b1d1c9f2900            mov      ebx, dword ptr [0x299f1c]      
  0x0021955B  8b2d2c9f2900            mov      ebp, dword ptr [0x299f2c]      
  0x00219561  41                      inc      ecx                            
  0x00219562  43                      inc      ebx                            
  0x00219563  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x00219569  0fb64bff                movzx    ecx, byte ptr [ebx - 1]        
  0x0021956D  8b0c8dc05e2900          mov      ecx, dword ptr [ecx*4 + 0x295ec0] 
  0x00219574  891d1c9f2900            mov      dword ptr [0x299f1c], ebx      
  0x0021957A  33db                    xor      ebx, ebx                       
  0x0021957C  8a7d00                  mov      bh, byte ptr [ebp]             
  0x0021957F  8b2c91                  mov      ebp, dword ptr [ecx + edx*4]   
  0x00219582  8b15149f2900            mov      edx, dword ptr [0x299f14]      
  0x00219588  0bdd                    or       ebx, ebp                       
  0x0021958A  8b2cb1                  mov      ebp, dword ptr [ecx + esi*4]   
  0x0021958D  c1e308                  shl      ebx, 8                         
  0x00219590  0bdd                    or       ebx, ebp                       
  0x00219592  8b2cb9                  mov      ebp, dword ptr [ecx + edi*4]   
  0x00219595  c1e308                  shl      ebx, 8                         
  0x00219598  0bdd                    or       ebx, ebp                       
  0x0021959A  891a                    mov      dword ptr [edx], ebx           
  0x0021959C  8b1d2c9f2900            mov      ebx, dword ptr [0x299f2c]      
  0x002195A2  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x002195A8  8b35149f2900            mov      esi, dword ptr [0x299f14]      
  0x002195AE  b904000000              mov      ecx, 4                         
  0x002195B3  43                      inc      ebx                            
  0x002195B4  03f9                    add      edi, ecx                       
  0x002195B6  03f1                    add      esi, ecx                       
  0x002195B8  40                      inc      eax                            
  0x002195B9  a801                    test     al, 1                          
  0x002195BB  891d2c9f2900            mov      dword ptr [0x299f2c], ebx      
  0x002195C1  893d109f2900            mov      dword ptr [0x299f10], edi      
  0x002195C7  8935149f2900            mov      dword ptr [0x299f14], esi      
  0x002195CD  751a                    jne      0x2195e9                       
  0x002195CF  8b15209f2900            mov      edx, dword ptr [0x299f20]      
  0x002195D5  8b0d249f2900            mov      ecx, dword ptr [0x299f24]      
  0x002195DB  42                      inc      edx                            
  0x002195DC  41                      inc      ecx                            
  0x002195DD  8915209f2900            mov      dword ptr [0x299f20], edx      
  0x002195E3  890d249f2900            mov      dword ptr [0x299f24], ecx      
                                        ; XREF: 0x002195CD (cond_jump)
  0x002195E9  ff4c2418                dec      dword ptr [esp + 0x18]         
  0x002195ED  0f85edfeffff            jne      0x2194e0                       
  0x002195F3  5f                      pop      edi                            
  0x002195F4  5e                      pop      esi                            
  0x002195F5  5d                      pop      ebp                            
  0x002195F6  5b                      pop      ebx                            
  0x002195F7  c3                      ret                                     
; end of function
  0x002195F8  cc                      int3                                    
  0x002195F9  cc                      int3                                    
  0x002195FA  cc                      int3                                    
  0x002195FB  cc                      int3                                    
  0x002195FC  cc                      int3                                    
  0x002195FD  cc                      int3                                    
  0x002195FE  cc                      int3                                    
  0x002195FF  cc                      int3                                    

; ============================================================
; Function: sub_00219600
; Start: 0x00219600  End: 0x00219650  Size: 80 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214310
; Called by: sub_0020C030
; ============================================================
sub_00219600:
  0x00219600  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00219604  8b4c2434                mov      ecx, dword ptr [esp + 0x34]    
  0x00219608  8b54242c                mov      edx, dword ptr [esp + 0x2c]    
  0x0021960C  6860c02900              push     0x29c060                       
  0x00219611  50                      push     eax                            
  0x00219612  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00219616  51                      push     ecx                            
  0x00219617  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021961B  52                      push     edx                            
  0x0021961C  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x00219620  50                      push     eax                            
  0x00219621  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00219625  51                      push     ecx                            
  0x00219626  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x0021962A  52                      push     edx                            
  0x0021962B  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021962F  50                      push     eax                            
  0x00219630  8b442430                mov      eax, dword ptr [esp + 0x30]    
  0x00219634  51                      push     ecx                            
  0x00219635  8b4c2430                mov      ecx, dword ptr [esp + 0x30]    
  0x00219639  52                      push     edx                            
  0x0021963A  8b542430                mov      edx, dword ptr [esp + 0x30]    
  0x0021963E  50                      push     eax                            
  0x0021963F  51                      push     ecx                            
  0x00219640  52                      push     edx                            
  0x00219641  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x00219645  e8c6acffff              call     0x214310                       ; -> sub_00214310
  0x0021964A  83c434                  add      esp, 0x34                      
  0x0021964D  c23400                  ret      0x34                           
; end of function

; ============================================================
; Function: sub_00219650
; Start: 0x00219650  End: 0x002196AB  Size: 91 bytes
; Detection: call_target (confidence: 0.90)
; Calls: sub_00214790
; Called by: sub_0020C030
; ============================================================
sub_00219650:
  0x00219650  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x00219654  8b4c243c                mov      ecx, dword ptr [esp + 0x3c]    
  0x00219658  8b542434                mov      edx, dword ptr [esp + 0x34]    
  0x0021965C  6860c02900              push     0x29c060                       
  0x00219661  50                      push     eax                            
  0x00219662  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x00219666  51                      push     ecx                            
  0x00219667  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021966B  52                      push     edx                            
  0x0021966C  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x00219670  50                      push     eax                            
  0x00219671  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x00219675  51                      push     ecx                            
  0x00219676  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x0021967A  52                      push     edx                            
  0x0021967B  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021967F  50                      push     eax                            
  0x00219680  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x00219684  51                      push     ecx                            
  0x00219685  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x00219689  52                      push     edx                            
  0x0021968A  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021968E  50                      push     eax                            
  0x0021968F  8b442438                mov      eax, dword ptr [esp + 0x38]    
  0x00219693  51                      push     ecx                            
  0x00219694  8b4c2438                mov      ecx, dword ptr [esp + 0x38]    
  0x00219698  52                      push     edx                            
  0x00219699  8b542438                mov      edx, dword ptr [esp + 0x38]    
  0x0021969D  50                      push     eax                            
  0x0021969E  51                      push     ecx                            
  0x0021969F  52                      push     edx                            
  0x002196A0  e8ebb0ffff              call     0x214790                       ; -> sub_00214790
  0x002196A5  83c440                  add      esp, 0x40                      
  0x002196A8  c23c00                  ret      0x3c                           
; end of function
  0x002196AB  cc                      int3                                    
  0x002196AC  cc                      int3                                    
  0x002196AD  cc                      int3                                    
  0x002196AE  cc                      int3                                    
  0x002196AF  cc                      int3                                    

; ============================================================
; Function: sub_002196B0
; Start: 0x002196B0  End: 0x00219947  Size: 663 bytes
; Detection: cc_boundary (confidence: 0.85)
; ============================================================
sub_002196B0:
  0x002196B0  53                      push     ebx                            
  0x002196B1  55                      push     ebp                            
  0x002196B2  56                      push     esi                            
  0x002196B3  57                      push     edi                            
  0x002196B4  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x002196BA  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x002196C0  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x002196C6  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x002196CC  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x002196D2  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x002196D6  c1e004                  shl      eax, 4                         
  0x002196D9  03c7                    add      eax, edi                       
  0x002196DB  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x002196E0  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x002197E2 (cond_jump)
  0x002196E7  0f6e22                  movd     mm4, dword ptr [edx]           
  0x002196EA  0fefc0                  pxor     mm0, mm0                       
  0x002196ED  33c0                    xor      eax, eax                       
  0x002196EF  83c204                  add      edx, 4                         
  0x002196F2  8a4500                  mov      al, byte ptr [ebp]             
  0x002196F5  0f60e0                  punpcklbw mm4, mm0                       
  0x002196F8  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x00219700  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x00219708  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021970B  83c502                  add      ebp, 2                         
  0x0021970E  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x00219715  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021971D  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x00219725  8a03                    mov      al, byte ptr [ebx]             
  0x00219727  0f71f402                psllw    mm4, 2                         
  0x0021972B  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x00219732  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021973A  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x00219742  0ffdd5                  paddw    mm2, mm5                       
  0x00219745  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x00219748  83c302                  add      ebx, 2                         
  0x0021974B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x00219753  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021975B  0ffdf5                  paddw    mm6, mm5                       
  0x0021975E  0f62d6                  punpckldq mm2, mm6                       
  0x00219761  0ffdcc                  paddw    mm1, mm4                       
  0x00219764  0ffdd4                  paddw    mm2, mm4                       
  0x00219767  0fedcf                  paddsw   mm1, mm7                       
  0x0021976A  0ffddc                  paddw    mm3, mm4                       
  0x0021976D  0fd9cf                  psubusw  mm1, mm7                       
  0x00219770  0fedd7                  paddsw   mm2, mm7                       
  0x00219773  0f7fcc                  movq     mm4, mm1                       
  0x00219776  0fd9d7                  psubusw  mm2, mm7                       
  0x00219779  0f61c8                  punpcklwd mm1, mm0                       
  0x0021977C  0f7fd5                  movq     mm5, mm2                       
  0x0021977F  0f61d0                  punpcklwd mm2, mm0                       
  0x00219782  0feddf                  paddsw   mm3, mm7                       
  0x00219785  0f72f208                pslld    mm2, 8                         
  0x00219789  0fd9df                  psubusw  mm3, mm7                       
  0x0021978C  0f69e0                  punpckhwd mm4, mm0                       
  0x0021978F  0f7fde                  movq     mm6, mm3                       
  0x00219792  0f61d8                  punpcklwd mm3, mm0                       
  0x00219795  0f72f310                pslld    mm3, 0x10                      
  0x00219799  0febca                  por      mm1, mm2                       
  0x0021979C  0f6e11                  movd     mm2, dword ptr [ecx]           
  0x0021979F  0febcb                  por      mm1, mm3                       
  0x002197A2  0fefdb                  pxor     mm3, mm3                       
  0x002197A5  0f69e8                  punpckhwd mm5, mm0                       
  0x002197A8  0f60da                  punpcklbw mm3, mm2                       
  0x002197AB  0fefd2                  pxor     mm2, mm2                       
  0x002197AE  0f61d3                  punpcklwd mm2, mm3                       
  0x002197B1  0f69f0                  punpckhwd mm6, mm0                       
  0x002197B4  0febca                  por      mm1, mm2                       
  0x002197B7  0f72f508                pslld    mm5, 8                         
  0x002197BB  0fefd2                  pxor     mm2, mm2                       
  0x002197BE  0f7f0f                  movq     qword ptr [edi], mm1           
  0x002197C1  0f69d3                  punpckhwd mm2, mm3                       
  0x002197C4  0f72f610                pslld    mm6, 0x10                      
  0x002197C8  0febe2                  por      mm4, mm2                       
  0x002197CB  0febe5                  por      mm4, mm5                       
  0x002197CE  83c104                  add      ecx, 4                         
  0x002197D1  83c710                  add      edi, 0x10                      
  0x002197D4  0febe6                  por      mm4, mm6                       
  0x002197D7  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x002197DC  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x002197E0  3bf8                    cmp      edi, eax                       
  0x002197E2  0f82fffeffff            jb       0x2196e7                       
  0x002197E8  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x002197EE  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x002197F4  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x002197FA  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x00219800  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x00219806  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021980C  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x00219812  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x00219816  c1e004                  shl      eax, 4                         
  0x00219819  03c7                    add      eax, edi                       
  0x0021981B  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x00219820  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x00219922 (cond_jump)
  0x00219827  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021982A  0fefc0                  pxor     mm0, mm0                       
  0x0021982D  33c0                    xor      eax, eax                       
  0x0021982F  83c204                  add      edx, 4                         
  0x00219832  8a4500                  mov      al, byte ptr [ebp]             
  0x00219835  0f60e0                  punpcklbw mm4, mm0                       
  0x00219838  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x00219840  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x00219848  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x0021984B  83c502                  add      ebp, 2                         
  0x0021984E  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x00219855  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x0021985D  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x00219865  8a03                    mov      al, byte ptr [ebx]             
  0x00219867  0f71f402                psllw    mm4, 2                         
  0x0021986B  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x00219872  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x0021987A  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x00219882  0ffdd5                  paddw    mm2, mm5                       
  0x00219885  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x00219888  83c302                  add      ebx, 2                         
  0x0021988B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x00219893  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x0021989B  0ffdf5                  paddw    mm6, mm5                       
  0x0021989E  0f62d6                  punpckldq mm2, mm6                       
  0x002198A1  0ffdcc                  paddw    mm1, mm4                       
  0x002198A4  0ffdd4                  paddw    mm2, mm4                       
  0x002198A7  0fedcf                  paddsw   mm1, mm7                       
  0x002198AA  0ffddc                  paddw    mm3, mm4                       
  0x002198AD  0fd9cf                  psubusw  mm1, mm7                       
  0x002198B0  0fedd7                  paddsw   mm2, mm7                       
  0x002198B3  0f7fcc                  movq     mm4, mm1                       
  0x002198B6  0fd9d7                  psubusw  mm2, mm7                       
  0x002198B9  0f61c8                  punpcklwd mm1, mm0                       
  0x002198BC  0f7fd5                  movq     mm5, mm2                       
  0x002198BF  0f61d0                  punpcklwd mm2, mm0                       
  0x002198C2  0feddf                  paddsw   mm3, mm7                       
  0x002198C5  0f72f208                pslld    mm2, 8                         
  0x002198C9  0fd9df                  psubusw  mm3, mm7                       
  0x002198CC  0f69e0                  punpckhwd mm4, mm0                       
  0x002198CF  0f7fde                  movq     mm6, mm3                       
  0x002198D2  0f61d8                  punpcklwd mm3, mm0                       
  0x002198D5  0f72f310                pslld    mm3, 0x10                      
  0x002198D9  0febca                  por      mm1, mm2                       
  0x002198DC  0f6e11                  movd     mm2, dword ptr [ecx]           
  0x002198DF  0febcb                  por      mm1, mm3                       
  0x002198E2  0fefdb                  pxor     mm3, mm3                       
  0x002198E5  0f69e8                  punpckhwd mm5, mm0                       
  0x002198E8  0f60da                  punpcklbw mm3, mm2                       
  0x002198EB  0fefd2                  pxor     mm2, mm2                       
  0x002198EE  0f61d3                  punpcklwd mm2, mm3                       
  0x002198F1  0f69f0                  punpckhwd mm6, mm0                       
  0x002198F4  0febca                  por      mm1, mm2                       
  0x002198F7  0f72f508                pslld    mm5, 8                         
  0x002198FB  0fefd2                  pxor     mm2, mm2                       
  0x002198FE  0f7f0f                  movq     qword ptr [edi], mm1           
  0x00219901  0f69d3                  punpckhwd mm2, mm3                       
  0x00219904  0f72f610                pslld    mm6, 0x10                      
  0x00219908  0febe2                  por      mm4, mm2                       
  0x0021990B  0febe5                  por      mm4, mm5                       
  0x0021990E  83c104                  add      ecx, 4                         
  0x00219911  83c710                  add      edi, 0x10                      
  0x00219914  0febe6                  por      mm4, mm6                       
  0x00219917  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x0021991C  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x00219920  3bf8                    cmp      edi, eax                       
  0x00219922  0f82fffeffff            jb       0x219827                       
  0x00219928  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x0021992E  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x00219934  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x0021993A  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x00219940  5f                      pop      edi                            
  0x00219941  5e                      pop      esi                            
  0x00219942  5d                      pop      ebp                            
  0x00219943  5b                      pop      ebx                            
  0x00219944  c20400                  ret      4                              
; end of function
  0x00219947  8da42400000000          lea      esp, [esp]                     
  0x0021994E  8bff                    mov      edi, edi                       
  0x00219950  53                      push     ebx                            
  0x00219951  55                      push     ebp                            
  0x00219952  56                      push     esi                            
  0x00219953  57                      push     edi                            
  0x00219954  8b3d109f2900            mov      edi, dword ptr [0x299f10]      
  0x0021995A  8b15189f2900            mov      edx, dword ptr [0x299f18]      
  0x00219960  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x00219966  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x0021996C  8b0d289f2900            mov      ecx, dword ptr [0x299f28]      
  0x00219972  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x00219976  c1e004                  shl      eax, 4                         
  0x00219979  03c7                    add      eax, edi                       
  0x0021997B  a3109f2900              mov      dword ptr [0x299f10], eax      
  0x00219980  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x00219ACB (cond_jump)
  0x00219987  0f6e22                  movd     mm4, dword ptr [edx]           
  0x0021998A  0fefc0                  pxor     mm0, mm0                       
  0x0021998D  33c0                    xor      eax, eax                       
  0x0021998F  83c204                  add      edx, 4                         
  0x00219992  8a4500                  mov      al, byte ptr [ebp]             
  0x00219995  0f60e0                  punpcklbw mm4, mm0                       
  0x00219998  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x002199A0  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x002199A8  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x002199AB  83c502                  add      ebp, 2                         
  0x002199AE  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x002199B5  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x002199BD  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x002199C5  8a03                    mov      al, byte ptr [ebx]             
  0x002199C7  0f71f402                psllw    mm4, 2                         
  0x002199CB  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x002199D2  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x002199DA  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x002199E2  0ffdd5                  paddw    mm2, mm5                       
  0x002199E5  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x002199E8  83c302                  add      ebx, 2                         
  0x002199EB  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x002199F3  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x002199FB  0ffdf5                  paddw    mm6, mm5                       
  0x002199FE  8a4500                  mov      al, byte ptr [ebp]             
  0x00219A01  0f62d6                  punpckldq mm2, mm6                       
  0x00219A04  0f73d110                psrlq    mm1, 0x10                      
  0x00219A08  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x00219A10  0f73d210                psrlq    mm2, 0x10                      
  0x00219A14  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x00219A1C  0f73d310                psrlq    mm3, 0x10                      
  0x00219A20  8a03                    mov      al, byte ptr [ebx]             
  0x00219A22  0f73f630                psllq    mm6, 0x30                      
  0x00219A26  0febce                  por      mm1, mm6                       
  0x00219A29  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x00219A31  0ffdee                  paddw    mm5, mm6                       
  0x00219A34  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x00219A3C  0f73f530                psllq    mm5, 0x30                      
  0x00219A40  0f73f630                psllq    mm6, 0x30                      
  0x00219A44  0febd5                  por      mm2, mm5                       
  0x00219A47  0febde                  por      mm3, mm6                       
  0x00219A4A  0ffdcc                  paddw    mm1, mm4                       
  0x00219A4D  0ffdd4                  paddw    mm2, mm4                       
  0x00219A50  0fedcf                  paddsw   mm1, mm7                       
  0x00219A53  0ffddc                  paddw    mm3, mm4                       
  0x00219A56  0fd9cf                  psubusw  mm1, mm7                       
  0x00219A59  0fedd7                  paddsw   mm2, mm7                       
  0x00219A5C  0f7fcc                  movq     mm4, mm1                       
  0x00219A5F  0fd9d7                  psubusw  mm2, mm7                       
  0x00219A62  0f61c8                  punpcklwd mm1, mm0                       
  0x00219A65  0f7fd5                  movq     mm5, mm2                       
  0x00219A68  0f61d0                  punpcklwd mm2, mm0                       
  0x00219A6B  0feddf                  paddsw   mm3, mm7                       
  0x00219A6E  0f72f208                pslld    mm2, 8                         
  0x00219A72  0fd9df                  psubusw  mm3, mm7                       
  0x00219A75  0f69e0                  punpckhwd mm4, mm0                       
  0x00219A78  0f7fde                  movq     mm6, mm3                       
  0x00219A7B  0f61d8                  punpcklwd mm3, mm0                       
  0x00219A7E  0f72f310                pslld    mm3, 0x10                      
  0x00219A82  0febca                  por      mm1, mm2                       
  0x00219A85  0f6e11                  movd     mm2, dword ptr [ecx]           
  0x00219A88  0febcb                  por      mm1, mm3                       
  0x00219A8B  0fefdb                  pxor     mm3, mm3                       
  0x00219A8E  0f69e8                  punpckhwd mm5, mm0                       
  0x00219A91  0f60da                  punpcklbw mm3, mm2                       
  0x00219A94  0fefd2                  pxor     mm2, mm2                       
  0x00219A97  0f61d3                  punpcklwd mm2, mm3                       
  0x00219A9A  0f69f0                  punpckhwd mm6, mm0                       
  0x00219A9D  0febca                  por      mm1, mm2                       
  0x00219AA0  0f72f508                pslld    mm5, 8                         
  0x00219AA4  0fefd2                  pxor     mm2, mm2                       
  0x00219AA7  0f7f0f                  movq     qword ptr [edi], mm1           
  0x00219AAA  0f69d3                  punpckhwd mm2, mm3                       
  0x00219AAD  0f72f610                pslld    mm6, 0x10                      
  0x00219AB1  0febe2                  por      mm4, mm2                       
  0x00219AB4  0febe5                  por      mm4, mm5                       
  0x00219AB7  83c104                  add      ecx, 4                         
  0x00219ABA  83c710                  add      edi, 0x10                      
  0x00219ABD  0febe6                  por      mm4, mm6                       
  0x00219AC0  a1109f2900              mov      eax, dword ptr [0x299f10]      
  0x00219AC5  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x00219AC9  3bf8                    cmp      edi, eax                       
  0x00219ACB  0f82b6feffff            jb       0x219987                       
  0x00219AD1  8915189f2900            mov      dword ptr [0x299f18], edx      
  0x00219AD7  890d289f2900            mov      dword ptr [0x299f28], ecx      
  0x00219ADD  8b3d149f2900            mov      edi, dword ptr [0x299f14]      
  0x00219AE3  8b151c9f2900            mov      edx, dword ptr [0x299f1c]      
  0x00219AE9  8b2d209f2900            mov      ebp, dword ptr [0x299f20]      
  0x00219AEF  8b1d249f2900            mov      ebx, dword ptr [0x299f24]      
  0x00219AF5  8b0d2c9f2900            mov      ecx, dword ptr [0x299f2c]      
  0x00219AFB  8b442414                mov      eax, dword ptr [esp + 0x14]    
  0x00219AFF  c1e004                  shl      eax, 4                         
  0x00219B02  03c7                    add      eax, edi                       
  0x00219B04  a3149f2900              mov      dword ptr [0x299f14], eax      
  0x00219B09  0f6f3de8a72500          movq     mm7, qword ptr [0x25a7e8]      
                                        ; XREF: 0x00219C54 (cond_jump)
  0x00219B10  0f6e22                  movd     mm4, dword ptr [edx]           
  0x00219B13  0fefc0                  pxor     mm0, mm0                       
  0x00219B16  33c0                    xor      eax, eax                       
  0x00219B18  83c204                  add      edx, 4                         
  0x00219B1B  8a4500                  mov      al, byte ptr [ebp]             
  0x00219B1E  0f60e0                  punpcklbw mm4, mm0                       
  0x00219B21  0f6e148538b72900        movd     mm2, dword ptr [eax*4 + 0x29b738] 
  0x00219B29  0f6e0c8538af2900        movd     mm1, dword ptr [eax*4 + 0x29af38] 
  0x00219B31  8a4501                  mov      al, byte ptr [ebp + 1]         
  0x00219B34  83c502                  add      ebp, 2                         
  0x00219B37  0fd925d8a72500          psubusw  mm4, qword ptr [0x25a7d8]      
  0x00219B3E  0f6e348538b72900        movd     mm6, dword ptr [eax*4 + 0x29b738] 
  0x00219B46  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38] 
  0x00219B4E  8a03                    mov      al, byte ptr [ebx]             
  0x00219B50  0f71f402                psllw    mm4, 2                         
  0x00219B54  0fe525e0a72500          pmulhw   mm4, qword ptr [0x25a7e0]      
  0x00219B5B  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x00219B63  0f6e1c8538bb2900        movd     mm3, dword ptr [eax*4 + 0x29bb38] 
  0x00219B6B  0ffdd5                  paddw    mm2, mm5                       
  0x00219B6E  8a4301                  mov      al, byte ptr [ebx + 1]         
  0x00219B71  83c302                  add      ebx, 2                         
  0x00219B74  0f6e2c8538b32900        movd     mm5, dword ptr [eax*4 + 0x29b338] 
  0x00219B7C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38] 
  0x00219B84  0ffdf5                  paddw    mm6, mm5                       
  0x00219B87  8a4500                  mov      al, byte ptr [ebp]             
  0x00219B8A  0f62d6                  punpckldq mm2, mm6                       
  0x00219B8D  0f73d110                psrlq    mm1, 0x10                      
  0x00219B91  0f6e348538af2900        movd     mm6, dword ptr [eax*4 + 0x29af38] 
  0x00219B99  0f73d210                psrlq    mm2, 0x10                      
  0x00219B9D  0f6e2c8538b72900        movd     mm5, dword ptr [eax*4 + 0x29b738] 
  0x00219BA5  0f73d310                psrlq    mm3, 0x10                      
  0x00219BA9  8a03                    mov      al, byte ptr [ebx]             
  0x00219BAB  0f73f630                psllq    mm6, 0x30                      
  0x00219BAF  0febce                  por      mm1, mm6                       
  0x00219BB2  0f6e348538b32900        movd     mm6, dword ptr [eax*4 + 0x29b338] 
  0x00219BBA  0ffdee                  paddw    mm5, mm6                       
  0x00219BBD  0f6e348538bb2900        movd     mm6, dword ptr [eax*4 + 0x29bb38] 
  0x00219BC5  0f73f530                psllq    mm5, 0x30                      
  0x00219BC9  0f73f630                psllq    mm6, 0x30                      
  0x00219BCD  0febd5                  por      mm2, mm5                       
  0x00219BD0  0febde                  por      mm3, mm6                       
  0x00219BD3  0ffdcc                  paddw    mm1, mm4                       
  0x00219BD6  0ffdd4                  paddw    mm2, mm4                       
  0x00219BD9  0fedcf                  paddsw   mm1, mm7                       
  0x00219BDC  0ffddc                  paddw    mm3, mm4                       
  0x00219BDF  0fd9cf                  psubusw  mm1, mm7                       
  0x00219BE2  0fedd7                  paddsw   mm2, mm7                       
  0x00219BE5  0f7fcc                  movq     mm4, mm1                       
  0x00219BE8  0fd9d7                  psubusw  mm2, mm7                       
  0x00219BEB  0f61c8                  punpcklwd mm1, mm0                       
  0x00219BEE  0f7fd5                  movq     mm5, mm2                       
  0x00219BF1  0f61d0                  punpcklwd mm2, mm0                       
  0x00219BF4  0feddf                  paddsw   mm3, mm7                       
  0x00219BF7  0f72f208                pslld    mm2, 8                         
  0x00219BFB  0fd9df                  psubusw  mm3, mm7                       
  0x00219BFE  0f69e0                  punpckhwd mm4, mm0                       
  0x00219C01  0f7fde                  movq     mm6, mm3                       
  0x00219C04  0f61d8                  punpcklwd mm3, mm0                       
  0x00219C07  0f72f310                pslld    mm3, 0x10                      
  0x00219C0B  0febca                  por      mm1, mm2                       
  0x00219C0E  0f6e11                  movd     mm2, dword ptr [ecx]           
  0x00219C11  0febcb                  por      mm1, mm3                       
  0x00219C14  0fefdb                  pxor     mm3, mm3                       
  0x00219C17  0f69e8                  punpckhwd mm5, mm0                       
  0x00219C1A  0f60da                  punpcklbw mm3, mm2                       
  0x00219C1D  0fefd2                  pxor     mm2, mm2                       
  0x00219C20  0f61d3                  punpcklwd mm2, mm3                       
  0x00219C23  0f69f0                  punpckhwd mm6, mm0                       
  0x00219C26  0febca                  por      mm1, mm2                       
  0x00219C29  0f72f508                pslld    mm5, 8                         
  0x00219C2D  0fefd2                  pxor     mm2, mm2                       
  0x00219C30  0f7f0f                  movq     qword ptr [edi], mm1           
  0x00219C33  0f69d3                  punpckhwd mm2, mm3                       
  0x00219C36  0f72f610                pslld    mm6, 0x10                      
  0x00219C3A  0febe2                  por      mm4, mm2                       
  0x00219C3D  0febe5                  por      mm4, mm5                       
  0x00219C40  83c104                  add      ecx, 4                         
  0x00219C43  83c710                  add      edi, 0x10                      
  0x00219C46  0febe6                  por      mm4, mm6                       
  0x00219C49  a1149f2900              mov      eax, dword ptr [0x299f14]      
  0x00219C4E  0f7f67f8                movq     qword ptr [edi - 8], mm4       
  0x00219C52  3bf8                    cmp      edi, eax                       
  0x00219C54  0f82b6feffff            jb       0x219b10                       
  0x00219C5A  89151c9f2900            mov      dword ptr [0x299f1c], edx      
  0x00219C60  890d2c9f2900            mov      dword ptr [0x299f2c], ecx      
  0x00219C66  892d209f2900            mov      dword ptr [0x299f20], ebp      
  0x00219C6C  891d249f2900            mov      dword ptr [0x299f24], ebx      
  0x00219C72  5f                      pop      edi                            
  0x00219C73  5e                      pop      esi                            
  0x00219C74  5d                      pop      ebp                            
  0x00219C75  5b                      pop      ebx                            
