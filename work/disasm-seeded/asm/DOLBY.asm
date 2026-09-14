; ============================================================
; Section: DOLBY
; VA: 0x00287D40 - 0x0028EEC0
; Size: 29056 bytes (28.4 KB)
; Functions: 0
; Instructions: 12339
; ============================================================

                                        ; XREF: 0x001F765D (data_imm)
  0x00287D40  080c0500000000          or       byte ptr [eax], cl             
  0x00287D47  0001                    add      byte ptr [ecx], al             
  0x00287D49  0000                    add      byte ptr [eax], al             
  0x00287D4B  0001                    add      byte ptr [ecx], al             
  0x00287D4D  0000                    add      byte ptr [eax], al             
  0x00287D4F  0000                    add      byte ptr [eax], al             
  0x00287D51  0000                    add      byte ptr [eax], al             
  0x00287D53  0000                    add      byte ptr [eax], al             
  0x00287D55  0000                    add      byte ptr [eax], al             
  0x00287D57  00cc                    add      ah, cl                         
  0x00287D59  cc                      int3                                    
  0x00287D5A  cc                      int3                                    
  0x00287D5B  0000                    add      byte ptr [eax], al             
  0x00287D5D  0000                    add      byte ptr [eax], al             
  0x00287D5F  0000                    add      byte ptr [eax], al             
  0x00287D61  002400                  add      byte ptr [eax + eax], ah       
  0x00287D64  847007                  test     byte ptr [eax + 7], dh         
  0x00287D67  000400                  add      byte ptr [eax + eax], al       
  0x00287D6A  0000                    add      byte ptr [eax], al             
  0x00287D6C  847007                  test     byte ptr [eax + 7], dh         
  0x00287D6F  000500000032            add      byte ptr [0x32000000], al      
  0x00287D75  f4                      hlt                                     
  0x00287D76  07                      pop      es                             
  0x00287D77  00ff                    add      bh, bh                         
  0x00287D7A  ff00                    inc      dword ptr [eax]                
  0x00287D7C  30f4                    xor      ah, dh                         
  0x00287D7E  07                      pop      es                             
  0x00287D7F  0001                    add      byte ptr [ecx], al             
  0x00287D81  0000                    add      byte ptr [eax], al             
  0x00287D83  0031                    add      byte ptr [ecx], dh             
  0x00287D85  f4                      hlt                                     
  0x00287D86  07                      pop      es                             
  0x00287D87  0001                    add      byte ptr [ecx], al             
  0x00287D89  0000                    add      byte ptr [eax], al             
  0x00287D8B  00bb0005002a            add      byte ptr [ebx + 0x2a000500], bh 
  0x00287D91  f4                      hlt                                     
  0x00287D92  0500e00b00              add      eax, 0xbe000                   
  0x00287D97  00b820050074            add      byte ptr [eax + 0x74000520], bh 
  0x00287D9D  fa                      cli                                     
  0x00287D9E  0a00                    or       al, byte ptr [eax]             
  0x00287DA0  1300                    adc      eax, dword ptr [eax]           
  0x00287DA2  2000                    and      byte ptr [eax], al             
  0x00287DA4  887007                  mov      byte ptr [eax + 7], dh         
  0x00287DA7  0001                    add      byte ptr [ecx], al             
  0x00287DA9  0000                    add      byte ptr [eax], al             
  0x00287DAB  0008                    add      byte ptr [eax], cl             
  0x00287DAD  0000                    add      byte ptr [eax], al             
  0x00287DAF  008870070002            add      byte ptr [eax + 0x2000770], cl 
  0x00287DB5  0000                    add      byte ptr [eax], al             
  0x00287DB7  008870070003            add      byte ptr [eax + 0x3000770], cl 
  0x00287DBD  0000                    add      byte ptr [eax], al             
  0x00287DBF  0000                    add      byte ptr [eax], al             
  0x00287DC1  f4                      hlt                                     
  0x00287DC2  56                      push     esi                            
  0x00287DC3  0000                    add      byte ptr [eax], al             
  0x00287DC5  0000                    add      byte ptr [eax], al             
  0x00287DC7  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x00287DCD  0100                    add      dword ptr [eax], eax           
  0x00287DCF  0003                    add      byte ptr [ebx], al             
  0x00287DD1  0020                    add      byte ptr [eax], ah             
  0x00287DD3  004210                  add      byte ptr [edx + 0x10], al      
  0x00287DD6  0d00a20000              or       eax, 0xa200                    
  0x00287DDB  0085f4080002            add      byte ptr [ebp + 0x20008f4], al 
  0x00287DE1  0000                    add      byte ptr [eax], al             
  0x00287DE3  008ef0070007            add      byte ptr [esi + 0x70007f0], cl 
  0x00287DE9  0000                    add      byte ptr [eax], al             
  0x00287DEB  00804101008e            add      byte ptr [eax - 0x71fffebf], al 
  0x00287DF1  7007                    jo       0x287dfa                       
  0x00287DF3  0007                    add      byte ptr [edi], al             
  0x00287DF5  0000                    add      byte ptr [eax], al             
  0x00287DF7  0084f408000100          add      byte ptr [esp + esi*8 + 0x10008], al 
  0x00287DFE  0000                    add      byte ptr [eax], al             
  0x00287E00  1300                    adc      eax, dword ptr [eax]           
  0x00287E02  2000                    and      byte ptr [eax], al             
  0x00287E04  80410100                add      byte ptr [ecx + 1], 0          
  0x00287E08  81850a003100000000f0    add      dword ptr [ebp + 0x31000a], 0xf0000000 
  0x00287E12  44                      inc      esp                            
  0x00287E13  00b3ffff0084            add      byte ptr [ebx - 0x7bff0001], dh 
  0x00287E19  7007                    jo       0x287e22                       
  0x00287E1B  000500000085            add      byte ptr [0x85000000], al      
  0x00287E21  f4                      hlt                                     
                                        ; XREF: 0x00287E19 (cond_jump)
  0x00287E22  0800                    or       byte ptr [eax], al             
  0x00287E24  0200                    add      al, byte ptr [eax]             
  0x00287E26  0000                    add      byte ptr [eax], al             
  0x00287E2A  07                      pop      es                             
  0x00287E2B  0001                    add      byte ptr [ecx], al             
  0x00287E2D  0000                    add      byte ptr [eax], al             
  0x00287E2F  0003                    add      byte ptr [ebx], al             
  0x00287E31  f4                      hlt                                     
  0x00287E32  60                      pushal                                  
  0x00287E33  00c0                    add      al, al                         
  0x00287E35  0b00                    or       eax, dword ptr [eax]           
  0x00287E37  0009                    add      byte ptr [ecx], cl             
  0x00287E39  2405                    and      al, 5                          
  0x00287E3B  0000                    add      byte ptr [eax], al             
  0x00287E3D  f4                      hlt                                     
  0x00287E3E  56                      push     esi                            
  0x00287E3F  000a                    add      byte ptr [edx], cl             
  0x00287E41  0000                    add      byte ptr [eax], al             
  0x00287E43  0000                    add      byte ptr [eax], al             
  0x00287E45  2038                    and      byte ptr [eax], bh             
  0x00287E47  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x00287E4D  0100                    add      dword ptr [eax], eax           
  0x00287E4F  0003                    add      byte ptr [ebx], al             
  0x00287E51  0020                    add      byte ptr [eax], ah             
  0x00287E53  004210                  add      byte ptr [edx + 0x10], al      
  0x00287E56  0d00820000              or       eax, 0x8200                    
  0x00287E5B  0000                    add      byte ptr [eax], al             
  0x00287E5E  56                      push     esi                            
  0x00287E5F  00c1                    add      cl, al                         
  0x00287E61  0b00                    or       eax, dword ptr [eax]           
  0x00287E63  0003                    add      byte ptr [ebx], al             
  0x00287E65  f4                      hlt                                     
  0x00287E66  60                      pushal                                  
  0x00287E67  0000                    add      byte ptr [eax], al             
  0x00287E69  0300                    add      eax, dword ptr [eax]           
  0x00287E6B  0012                    add      byte ptr [edx], dl             
  0x00287E6D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00287E6E  050000f456              add      eax, 0x56f40000                
  0x00287E73  0001                    add      byte ptr [ecx], al             
  0x00287E75  0000                    add      byte ptr [eax], al             
  0x00287E77  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x00287E7D  0100                    add      dword ptr [eax], eax           
  0x00287E7F  0003                    add      byte ptr [ebx], al             
  0x00287E81  0020                    add      byte ptr [eax], ah             
  0x00287E83  004210                  add      byte ptr [edx + 0x10], al      
  0x00287E86  0d00760000              or       eax, 0x7600                    
  0x00287E8B  008ff0070002            add      byte ptr [edi + 0x20007f0], cl 
  0x00287E91  0000                    add      byte ptr [eax], al             
  0x00287E93  0000                    add      byte ptr [eax], al             
  0x00287E95  f4                      hlt                                     
  0x00287E96  60                      pushal                                  
  0x00287E97  00c0                    add      al, al                         
  0x00287E99  0b00                    or       eax, dword ptr [eax]           
  0x00287E9B  0080f00b0004            add      byte ptr [eax + 0x4000bf0], al 
  0x00287EA1  0300                    add      eax, dword ptr [eax]           
  0x00287EA3  0000                    add      byte ptr [eax], al             
  0x00287EA5  002400                  add      byte ptr [eax + eax], ah       
  0x00287EA8  847007                  test     byte ptr [eax + 7], dh         
  0x00287EAB  0002                    add      byte ptr [edx], al             
  0x00287EAD  0000                    add      byte ptr [eax], al             
  0x00287EAF  001c0c                  add      byte ptr [esp + ecx], bl       
  0x00287EB2  050000f057              add      eax, 0x57f00000                
  0x00287EB7  00c3                    add      bl, al                         
  0x00287EB9  0b00                    or       eax, dword ptr [eax]           
  0x00287EBB  000b                    add      byte ptr [ebx], cl             
  0x00287EBD  f4                      hlt                                     
  0x00287EBE  60                      pushal                                  
  0x00287EBF  0000                    add      byte ptr [eax], al             
  0x00287EC1  0300                    add      eax, dword ptr [eax]           
  0x00287EC3  0017                    add      byte ptr [edi], dl             
  0x00287EC5  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00287EC6  050013f444              add      eax, 0x44f41300                
  0x00287ECB  0005000000cd            add      byte ptr [0xcd000000], al      
  0x00287ED1  40                      inc      eax                            
  0x00287ED2  0100                    add      dword ptr [eax], eax           
  0x00287ED4  0100                    add      dword ptr [eax], eax           
  0x00287ED6  0000                    add      byte ptr [eax], al             
  0x00287ED8  41                      inc      ecx                            
  0x00287ED9  2a20                    sub      ah, byte ptr [eax]             
  0x00287EDB  0000                    add      byte ptr [eax], al             
  0x00287EDD  f4                      hlt                                     
  0x00287EDE  44                      inc      esp                            
  0x00287EDF  0006                    add      byte ptr [esi], al             
  0x00287EE1  0000                    add      byte ptr [eax], al             
  0x00287EE3  00cd                    add      ch, cl                         
  0x00287EE5  40                      inc      eax                            
  0x00287EE6  0100                    add      dword ptr [eax], eax           
  0x00287EE8  0200                    add      al, byte ptr [eax]             
  0x00287EEA  0000                    add      byte ptr [eax], al             
  0x00287EEC  41                      inc      ecx                            
  0x00287EED  2a20                    sub      ah, byte ptr [eax]             
  0x00287EEF  0003                    add      byte ptr [ebx], al             
  0x00287EF1  0020                    add      byte ptr [eax], ah             
  0x00287EF3  000b                    add      byte ptr [ebx], cl             
  0x00287EF5  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00287EF6  050080f00b              add      eax, 0xbf08000                 
  0x00287EFB  008001000003            add      byte ptr [eax + 0x3000001], al 
  0x00287F01  0020                    add      byte ptr [eax], ah             
  0x00287F03  004210                  add      byte ptr [edx + 0x10], al      
  0x00287F06  0d00560000              or       eax, 0x5600                    
  0x00287F0B  0000                    add      byte ptr [eax], al             
  0x00287F0D  f4                      hlt                                     
  0x00287F0E  60                      pushal                                  
  0x00287F0F  00c0                    add      al, al                         
  0x00287F11  0b00                    or       eax, dword ptr [eax]           
  0x00287F13  0080f00b0004            add      byte ptr [eax + 0x4000bf0], al 
  0x00287F19  0300                    add      eax, dword ptr [eax]           
  0x00287F1B  0001                    add      byte ptr [ecx], al             
  0x00287F1D  0c05                    or       al, 5                          
  0x00287F1F  0000                    add      byte ptr [eax], al             
  0x00287F22  56                      push     esi                            
  0x00287F23  00c2                    add      dl, al                         
  0x00287F25  0b00                    or       eax, dword ptr [eax]           
  0x00287F27  0003                    add      byte ptr [ebx], al             
  0x00287F29  f4                      hlt                                     
  0x00287F2A  60                      pushal                                  
  0x00287F2B  0000                    add      byte ptr [eax], al             
  0x00287F2D  0300                    add      eax, dword ptr [eax]           
  0x00287F2F  004fa4                  add      byte ptr [edi - 0x5c], cl      
  0x00287F32  050000f456              add      eax, 0x56f40000                
  0x00287F37  0002                    add      byte ptr [edx], al             
  0x00287F39  0000                    add      byte ptr [eax], al             
  0x00287F3B  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x00287F41  0100                    add      dword ptr [eax], eax           
  0x00287F43  0003                    add      byte ptr [ebx], al             
  0x00287F45  0020                    add      byte ptr [eax], ah             
  0x00287F47  004210                  add      byte ptr [edx + 0x10], al      
  0x00287F4A  0d00450000              or       eax, 0x4500                    
  0x00287F4F  0000                    add      byte ptr [eax], al             
  0x00287F51  f4                      hlt                                     
  0x00287F52  60                      pushal                                  
  0x00287F53  00c0                    add      al, al                         
  0x00287F55  0b00                    or       eax, dword ptr [eax]           
  0x00287F57  008ff0070003            add      byte ptr [edi + 0x30007f0], cl 
  0x00287F5D  0000                    add      byte ptr [eax], al             
  0x00287F5F  0084f007000100          add      byte ptr [eax + esi*8 + 0x10007], al 
  0x00287F66  0000                    add      byte ptr [eax], al             
  0x00287F68  80f00b                  xor      al, 0xb                        
  0x00287F6B  000403                  add      byte ptr [ebx + eax], al       
  0x00287F6E  0000                    add      byte ptr [eax], al             
  0x00287F70  00f4                    add      ah, dh                         
  0x00287F72  60                      pushal                                  
  0x00287F73  0000                    add      byte ptr [eax], al             
  0x00287F75  0300                    add      eax, dword ptr [eax]           
  0x00287F77  0000                    add      byte ptr [eax], al             
  0x00287F79  f4                      hlt                                     
  0x00287F7A  56                      push     esi                            
  0x00287F7B  0003                    add      byte ptr [ebx], al             
  0x00287F7D  0000                    add      byte ptr [eax], al             
  0x00287F7F  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x00287F85  0100                    add      dword ptr [eax], eax           
  0x00287F87  0003                    add      byte ptr [ebx], al             
  0x00287F89  0020                    add      byte ptr [eax], ah             
  0x00287F8B  004210                  add      byte ptr [edx + 0x10], al      
  0x00287F8E  0d00340000              or       eax, 0x3400                    
  0x00287F93  008ff0070003            add      byte ptr [edi + 0x30007f0], cl 
  0x00287F99  0000                    add      byte ptr [eax], al             
  0x00287F9B  0080f00b0004            add      byte ptr [eax + 0x4000bf0], al 
  0x00287FA1  0300                    add      eax, dword ptr [eax]           
  0x00287FA3  0000                    add      byte ptr [eax], al             
  0x00287FA5  f4                      hlt                                     
  0x00287FA6  60                      pushal                                  
  0x00287FA7  0000                    add      byte ptr [eax], al             
  0x00287FA9  0300                    add      eax, dword ptr [eax]           
  0x00287FAB  0000                    add      byte ptr [eax], al             
  0x00287FAD  f4                      hlt                                     
  0x00287FAE  56                      push     esi                            
  0x00287FAF  000400                  add      byte ptr [eax + eax], al       
  0x00287FB2  0000                    add      byte ptr [eax], al             
  0x00287FB4  80f00b                  xor      al, 0xb                        
  0x00287FB7  008001000003            add      byte ptr [eax + 0x3000001], al 
  0x00287FBD  0020                    add      byte ptr [eax], ah             
  0x00287FBF  004210                  add      byte ptr [edx + 0x10], al      
  0x00287FC2  0d00270000              or       eax, 0x2700                    
  0x00287FC7  008ff0070003            add      byte ptr [edi + 0x30007f0], cl 
  0x00287FCD  0000                    add      byte ptr [eax], al             
  0x00287FCF  0084f007000100          add      byte ptr [eax + esi*8 + 0x10007], al 
  0x00287FD6  0000                    add      byte ptr [eax], al             
  0x00287FD8  80f00b                  xor      al, 0xb                        
  0x00287FDB  000403                  add      byte ptr [ebx + eax], al       
  0x00287FDE  0000                    add      byte ptr [eax], al             
  0x00287FE0  0000                    add      byte ptr [eax], al             
  0x00287FE2  2400                    and      al, 0                          
  0x00287FE4  847007                  test     byte ptr [eax + 7], dh         
  0x00287FE7  0003                    add      byte ptr [ebx], al             
  0x00287FE9  0000                    add      byte ptr [eax], al             
  0x00287FEB  008ef0070001            add      byte ptr [esi + 0x10007f0], cl 
  0x00287FF1  0000                    add      byte ptr [eax], al             
  0x00287FF3  008041010085            add      byte ptr [eax - 0x7afffebf], al 
  0x00287FF9  46                      inc      esi                            
  0x00287FFA  0100                    add      dword ptr [eax], eax           
  0x00287FFC  1321                    adc      esp, dword ptr [ecx]           
  0x00287FFE  2000                    and      byte ptr [eax], al             
  0x00288001  7007                    jo       0x28800a                       
  0x00288003  0001                    add      byte ptr [ecx], al             
  0x00288005  0000                    add      byte ptr [eax], al             
  0x00288007  0000                    add      byte ptr [eax], al             
  0x00288009  f4                      hlt                                     
                                        ; XREF: 0x00288001 (cond_jump)
  0x0028800A  56                      push     esi                            
  0x0028800B  000b                    add      byte ptr [ebx], cl             
  0x0028800D  0000                    add      byte ptr [eax], al             
  0x0028800F  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x00288015  0100                    add      dword ptr [eax], eax           
  0x00288017  0000                    add      byte ptr [eax], al             
  0x0028801A  56                      push     esi                            
  0x0028801B  00b3ffff0084            add      byte ptr [ebx - 0x7bff0001], dh 
  0x00288022  07                      pop      es                             
  0x00288023  000500000044            add      byte ptr [0x44000000], al      
  0x00288029  0020                    add      byte ptr [eax], ah             
  0x0028802B  008c7007000400          add      byte ptr [eax + esi*2 + 0x40007], cl 
  0x00288032  0000                    add      byte ptr [eax], al             
  0x00288034  00f4                    add      ah, dh                         
  0x00288036  44                      inc      esp                            
  0x00288037  00a0cd0a00f8            add      byte ptr [eax - 0x7fff533], ah 
  0x0028803D  1f                      pop      ds                             
  0x0028803E  0c00                    or       al, 0                          
  0x00288040  c9                      leave                                   
  0x00288041  96                      xchg     esi, eax                       
  0x00288042  050000f444              add      eax, 0x44f40000                
  0x00288047  00bbbbbb0084            add      byte ptr [ebx - 0x7bff4445], bh 
  0x0028804D  7007                    jo       0x288056                       
  0x0028804F  0006                    add      byte ptr [esi], al             
  0x00288051  0000                    add      byte ptr [eax], al             
  0x00288053  0000                    add      byte ptr [eax], al             
  0x00288055  0c05                    or       al, 5                          
  0x00288057  00c3                    add      bl, al                         
  0x00288059  0e                      push     cs                             
  0x0028805A  0500c20e05              add      eax, 0x50ec200                 
  0x0028805F  0000                    add      byte ptr [eax], al             
  0x00288061  f4                      hlt                                     
  0x00288062  6200                    bound    eax, qword ptr [eax]           
  0x00288064  0001                    add      byte ptr [ecx], al             
  0x00288066  0000                    add      byte ptr [eax], al             
  0x00288068  009a21000001            add      byte ptr [edx + 0x1000021], bl 
  0x0028806E  3d00854001              cmp      eax, 0x1408500                 
  0x00288073  000f                    add      byte ptr [edi], cl             
  0x00288075  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x00288076  0500004a20              add      eax, 0x204a0000                
  0x0028807B  0000                    add      byte ptr [eax], al             
  0x0028807D  4a                      dec      edx                            
  0x0028807E  2000                    and      byte ptr [eax], al             
  0x00288080  91                      xchg     ecx, eax                       
  0x00288081  da07                    fiadd    dword ptr [edi]                
  0x00288083  0085510100ce            add      byte ptr [ebp - 0x31fffeaf], al 
  0x00288089  1405                    adc      al, 5                          
  0x0028808B  008546010054            add      byte ptr [ebp + 0x54000146], al 
  0x00288091  f4                      hlt                                     
  0x00288092  0500854901              add      eax, 0x1498500                 
  0x00288097  008ca40500854a          add      byte ptr [esp + 0x4a850005], cl 
  0x0028809E  0100                    add      dword ptr [eax], eax           
  0x002880A0  4b                      dec      ebx                            
  0x002880A1  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x002880A2  0500854b01              add      eax, 0x14b8500                 
  0x002880A7  0051a4                  add      byte ptr [ecx - 0x5c], dl      
  0x002880AA  0500854c01              add      eax, 0x14c8500                 
  0x002880AF  0095a4050085            add      byte ptr [ebp - 0x7afffa5c], dl 
  0x002880B5  4d                      dec      ebp                            
  0x002880B6  0100                    add      dword ptr [eax], eax           
  0x002880B8  98                      cwde                                    
  0x002880B9  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x002880BA  0500854801              add      eax, 0x1488500                 
  0x002880BF  005ba4                  add      byte ptr [ebx - 0x5c], bl      
  0x002880C2  0500854e01              add      eax, 0x14e8500                 
  0x002880C7  0087a4050085            add      byte ptr [edi - 0x7afffa5c], al 
  0x002880CD  4f                      dec      edi                            
  0x002880CE  0100                    add      dword ptr [eax], eax           
  0x002880D0  82a405004c0c0500        and      byte ptr [ebp + eax + 0x50c4c00], 0 
  0x002880D8  0000                    add      byte ptr [eax], al             
  0x002880DA  0000                    add      byte ptr [eax], al             
  0x002880DC  0000                    add      byte ptr [eax], al             
  0x002880DE  0000                    add      byte ptr [eax], al             
  0x002880E0  0000                    add      byte ptr [eax], al             
  0x002880E2  0000                    add      byte ptr [eax], al             
  0x002880E4  0100                    add      dword ptr [eax], eax           
  0x002880E6  0000                    add      byte ptr [eax], al             
  0x002880E8  0000                    add      byte ptr [eax], al             
  0x002880EA  0000                    add      byte ptr [eax], al             
  0x002880EC  0000                    add      byte ptr [eax], al             
  0x002880EE  0000                    add      byte ptr [eax], al             
  0x002880F0  0000                    add      byte ptr [eax], al             
  0x002880F2  0000                    add      byte ptr [eax], al             
  0x002880F4  0000                    add      byte ptr [eax], al             
  0x002880F6  0000                    add      byte ptr [eax], al             
  0x002880F8  0000                    add      byte ptr [eax], al             
  0x002880FA  0000                    add      byte ptr [eax], al             
  0x002880FC  0000                    add      byte ptr [eax], al             
  0x002880FE  0000                    add      byte ptr [eax], al             
  0x00288100  0000                    add      byte ptr [eax], al             
  0x00288102  0000                    add      byte ptr [eax], al             
  0x00288104  0000                    add      byte ptr [eax], al             
  0x00288106  0000                    add      byte ptr [eax], al             
  0x00288108  0000                    add      byte ptr [eax], al             
  0x0028810A  0000                    add      byte ptr [eax], al             
  0x0028810C  0000                    add      byte ptr [eax], al             
  0x0028810E  0000                    add      byte ptr [eax], al             
  0x00288110  0000                    add      byte ptr [eax], al             
  0x00288112  0000                    add      byte ptr [eax], al             
  0x00288114  0000                    add      byte ptr [eax], al             
  0x00288116  0000                    add      byte ptr [eax], al             
  0x00288118  0000                    add      byte ptr [eax], al             
  0x0028811A  0000                    add      byte ptr [eax], al             
  0x0028811C  0000                    add      byte ptr [eax], al             
  0x0028811E  0000                    add      byte ptr [eax], al             
  0x00288120  0000                    add      byte ptr [eax], al             
  0x00288122  0000                    add      byte ptr [eax], al             
  0x00288124  0000                    add      byte ptr [eax], al             
  0x00288126  0000                    add      byte ptr [eax], al             
  0x00288128  0000                    add      byte ptr [eax], al             
  0x0028812A  0000                    add      byte ptr [eax], al             
  0x0028812C  0000                    add      byte ptr [eax], al             
  0x0028812E  0000                    add      byte ptr [eax], al             
  0x00288130  0000                    add      byte ptr [eax], al             
  0x00288132  0000                    add      byte ptr [eax], al             
  0x00288134  0000                    add      byte ptr [eax], al             
  0x00288136  0000                    add      byte ptr [eax], al             
  0x00288138  0000                    add      byte ptr [eax], al             
  0x0028813A  0000                    add      byte ptr [eax], al             
  0x0028813C  0000                    add      byte ptr [eax], al             
  0x0028813E  0000                    add      byte ptr [eax], al             
  0x00288140  0000                    add      byte ptr [eax], al             
  0x00288142  0000                    add      byte ptr [eax], al             
  0x00288144  0000                    add      byte ptr [eax], al             
  0x00288146  0000                    add      byte ptr [eax], al             
  0x00288148  0000                    add      byte ptr [eax], al             
  0x0028814A  0000                    add      byte ptr [eax], al             
  0x0028814C  8eda                    mov      ds, edx                        
  0x0028814E  07                      pop      es                             
  0x0028814F  0000                    add      byte ptr [eax], al             
  0x00288151  0423                    add      al, 0x23                       
  0x00288153  004598                  add      byte ptr [ebp - 0x68], al      
  0x00288156  2100                    and      dword ptr [eax], eax           
  0x00288159  080500900c05            or       byte ptr [0x50c9000], al       
  0x0028815F  0098da07001f            add      byte ptr [eax + 0x1f0007da], bl 
  0x00288165  0905008d0c05            or       dword ptr [0x50c8d00], eax     
  0x0028816B  0084f007001601          add      byte ptr [eax + esi*8 + 0x1160007], al 
  0x00288172  0000                    add      byte ptr [eax], al             
  0x00288174  48                      dec      eax                            
  0x00288175  c40b                    les      ecx, ptr [ebx]                 
  0x00288177  00847007001601          add      byte ptr [eax + esi*2 + 0x1160007], al 
  0x0028817E  0000                    add      byte ptr [eax], al             
  0x00288180  870c0500002f23          xchg     dword ptr [eax + 0x232f0000], ecx 
  0x00288187  00931d0c0000            add      byte ptr [ebx + 0xc1d], dl     
  0x0028818D  2422                    and      al, 0x22                       
  0x0028818F  004800                  add      byte ptr [eax], cl             
  0x00288192  2000                    and      byte ptr [eax], al             
  0x00288196  07                      pop      es                             
  0x00288197  0016                    add      byte ptr [esi], dl             
  0x00288199  0100                    add      dword ptr [eax], eax           
  0x0028819B  0010                    add      byte ptr [eax], dl             
  0x0028819D  0020                    add      byte ptr [eax], ah             
  0x0028819F  0000                    add      byte ptr [eax], al             
  0x002881A1  91                      xchg     ecx, eax                       
  0x002881A2  2100                    and      dword ptr [eax], eax           
  0x002881A4  93                      xchg     ebx, eax                       
  0x002881A5  0805005d0c05            or       byte ptr [0x50c5d00], al       
  0x002881AB  0000                    add      byte ptr [eax], al             
  0x002881AD  2e2300                  and      eax, dword ptr cs:[eax]        
  0x002881B0  854001                  test     dword ptr [eax + 1], eax       
  0x002881B3  005a24                  add      byte ptr [edx + 0x24], bl      
  0x002881B6  050000013a              add      eax, 0x3a010000                
  0x002881BB  0000                    add      byte ptr [eax], al             
  0x002881BD  003c00                  add      byte ptr [eax + eax], bh       
  0x002881C0  c00805                  ror      byte ptr [eax], 5              
  0x002881C3  00560c                  add      byte ptr [esi + 0xc], dl       
  0x002881C6  050000003a              add      eax, 0x3a000000                
  0x002881CB  0000                    add      byte ptr [eax], al             
  0x002881CD  003c00                  add      byte ptr [eax + eax], bh       
  0x002881D0  9c                      pushfd                                  
  0x002881D1  080500520c05            or       byte ptr [0x50c5200], al       
  0x002881D7  0000                    add      byte ptr [eax], al             
  0x002881D9  f4                      hlt                                     
  0x002881DA  61                      popal                                   
  0x002881DB  00ab01000003            add      byte ptr [ebx + 0x3000001], ch 
  0x002881E1  0c05                    or       al, 5                          
  0x002881E3  0000                    add      byte ptr [eax], al             
  0x002881E5  f4                      hlt                                     
  0x002881E6  61                      popal                                   
  0x002881E7  00af01000010            add      byte ptr [edi + 0x10000001], ch 
  0x002881ED  d806                    fadd     dword ptr [esi]                
  0x002881EF  000400                  add      byte ptr [eax + eax], al       
  0x002881F2  0000                    add      byte ptr [eax], al             
  0x002881F4  00d8                    add      al, bl                         
  0x002881F6  44                      inc      esp                            
  0x002881F7  00845907000000          add      byte ptr [ecx + ebx*2 + 7], al 
  0x002881FE  0000                    add      byte ptr [eax], al             
  0x00288200  47                      inc      edi                            
  0x00288201  0c05                    or       al, 5                          
  0x00288203  0000                    add      byte ptr [eax], al             
  0x00288205  003a                    add      byte ptr [edx], bh             
  0x00288207  0000                    add      byte ptr [eax], al             
  0x00288209  013c00                  add      dword ptr [eax + eax], edi     
  0x0028820C  0000                    add      byte ptr [eax], al             
  0x0028820E  3d008c0805              cmp      eax, 0x5088c00                 
  0x00288213  00420c                  add      byte ptr [edx + 0xc], al       
  0x00288216  050000003a              add      eax, 0x3a000000                
  0x0028821B  0000                    add      byte ptr [eax], al             
  0x0028821D  003c00                  add      byte ptr [eax + eax], bh       
  0x00288220  8808                    mov      byte ptr [eax], cl             
  0x00288222  05001e0c05              add      eax, 0x50c1e00                 
  0x00288227  002402                  add      byte ptr [edx + eax], ah       
  0x0028822A  0000                    add      byte ptr [eax], al             
  0x0028822C  2e0200                  add      al, byte ptr cs:[eax]          
  0x0028822F  004a02                  add      byte ptr [edx + 2], cl         
  0x00288232  0000                    add      byte ptr [eax], al             
  0x00288234  55                      push     ebp                            
  0x00288235  0200                    add      al, byte ptr [eax]             
  0x00288237  006002                  add      byte ptr [eax + 2], ah         
  0x0028823A  0000                    add      byte ptr [eax], al             
  0x0028823C  6b0200                  imul     eax, dword ptr [edx], 0        
  0x0028823F  008d40010008            add      byte ptr [ebp + 0x8000140], cl 
  0x00288245  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00288246  050000bc21              add      eax, 0x21bc0000                
  0x0028824B  0000                    add      byte ptr [eax], al             
  0x0028824D  f4                      hlt                                     
  0x0028824E  6400f1                  add      cl, dh                         
  0x00288251  0100                    add      dword ptr [eax], eax           
  0x00288253  0000                    add      byte ptr [eax], al             
  0x00288255  49                      dec      ecx                            
  0x00288256  2000                    and      byte ptr [eax], al             
  0x00288258  96                      xchg     esi, eax                       
  0x00288259  ec                      in       al, dx                         
  0x0028825A  07                      pop      es                             
  0x0028825B  0080e60b000f            add      byte ptr [eax + 0xf000be6], al 
  0x00288261  0c05                    or       al, 5                          
  0x00288263  0000                    add      byte ptr [eax], al             
  0x00288265  0f2300                  mov      dr0, eax                       
  0x0028826A  07                      pop      es                             
  0x0028826B  009f01000084            add      byte ptr [edi - 0x7bffffff], bl 
  0x00288272  07                      pop      es                             
  0x00288273  009e01000014            add      byte ptr [esi + 0x14000001], bl 
  0x00288279  0020                    add      byte ptr [eax], ah             
  0x0028827B  000a                    add      byte ptr [edx], cl             
  0x0028827D  94                      xchg     esp, eax                       
  0x0028827E  0500485220              add      eax, 0x20524800                
  0x00288283  00845a0700985a          add      byte ptr [edx + ebx*2 + 0x5a980007], al 
  0x0028828A  07                      pop      es                             
  0x0028828B  008c7007009f01          add      byte ptr [eax + esi*2 + 0x19f0007], cl 
  0x00288292  0000                    add      byte ptr [eax], al             
  0x00288294  8d7007                  lea      esi, [eax + 7]                 
  0x00288297  009e01000013            add      byte ptr [esi + 0x13000001], bl 
  0x0028829D  0020                    add      byte ptr [eax], ah             
  0x0028829F  000c00                  add      byte ptr [eax + eax], cl       
  0x002882A2  0000                    add      byte ptr [eax], al             
  0x002882A4  00f4                    add      ah, dh                         
  0x002882A6  56                      push     esi                            
  0x002882A7  000400                  add      byte ptr [eax + eax], al       
  0x002882AA  0000                    add      byte ptr [eax], al             
  0x002882AC  0c00                    or       al, 0                          
  0x002882AE  0000                    add      byte ptr [eax], al             
  0x002882B0  84f0                    test     al, dh                         
  0x002882B2  07                      pop      es                             
  0x002882B3  0022                    add      byte ptr [edx], ah             
  0x002882B5  0100                    add      dword ptr [eax], eax           
  0x002882B7  00847007009e01          add      byte ptr [eax + esi*2 + 0x19e0007], al 
  0x002882BE  0000                    add      byte ptr [eax], al             
  0x002882C0  84f0                    test     al, dh                         
  0x002882C2  07                      pop      es                             
  0x002882C3  0023                    add      byte ptr [ebx], ah             
  0x002882C5  0100                    add      dword ptr [eax], eax           
  0x002882C7  00847007009f01          add      byte ptr [eax + esi*2 + 0x19f0007], al 
  0x002882CE  0000                    add      byte ptr [eax], al             
  0x002882D0  13f4                    adc      esi, esp                       
  0x002882D2  60                      pushal                                  
  0x002882D3  0022                    add      byte ptr [edx], ah             
  0x002882D5  0100                    add      dword ptr [eax], eax           
  0x002882D7  00901e060002            add      byte ptr [eax + 0x200061e], dl 
  0x002882DD  0000                    add      byte ptr [eax], al             
  0x002882DF  008e58070080            add      byte ptr [esi - 0x7ffff8a8], cl 
  0x002882E5  100d00ce0000            adc      byte ptr [0xce00], cl          
  0x002882EB  00cc                    add      ah, cl                         
  0x002882ED  0f05                    syscall                                 
  0x002882EF  0000                    add      byte ptr [eax], al             
  0x002882F1  f4                      hlt                                     
  0x002882F2  6400a201000000          add      byte ptr fs:[edx + 1], ah      
  0x002882F9  0c22                    or       al, 0x22                       
  0x002882FB  008040010000            add      byte ptr [eax + 0x140], al     
  0x00288301  90                      nop                                     
  0x00288302  2100                    and      dword ptr [eax], eax           
  0x00288304  80f00b                  xor      al, 0xb                        
  0x00288307  007602                  add      byte ptr [esi + 2], dh         
  0x0028830A  0000                    add      byte ptr [eax], al             
  0x0028830C  80f00b                  xor      al, 0xb                        
  0x0028830F  00e1                    add      cl, ah                         
  0x00288311  0200                    add      al, byte ptr [eax]             
  0x00288313  000c00                  add      byte ptr [eax + eax], cl       
  0x00288316  0000                    add      byte ptr [eax], al             
  0x00288318  00f4                    add      ah, dh                         
  0x0028831A  6400a201000000          add      byte ptr fs:[edx + 1], ah      
  0x00288321  0c22                    or       al, 0x22                       
  0x00288323  008040010000            add      byte ptr [eax + 0x140], al     
  0x00288329  90                      nop                                     
  0x0028832A  2100                    and      dword ptr [eax], eax           
  0x0028832C  80f00b                  xor      al, 0xb                        
  0x0028832F  008802000080            add      byte ptr [eax - 0x7ffffffe], cl 
  0x00288335  f00b00                  lock or  eax, dword ptr [eax]           
  0x00288338  e102                    loope    0x28833c                       
  0x0028833A  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x00288338 (cond_jump)
  0x0028833C  0c00                    or       al, 0                          
  0x0028833E  0000                    add      byte ptr [eax], al             
  0x00288340  00f4                    add      ah, dh                         
  0x00288342  6400a201000000          add      byte ptr fs:[edx + 1], ah      
  0x00288349  0c22                    or       al, 0x22                       
  0x0028834B  008040010000            add      byte ptr [eax + 0x140], al     
  0x00288351  90                      nop                                     
  0x00288352  2100                    and      dword ptr [eax], eax           
  0x00288354  004e23                  add      byte ptr [esi + 0x23], cl      
  0x00288357  008540010042            add      byte ptr [ebp + 0x42000140], al 
  0x0028835D  100d00060000            adc      byte ptr [0x600], cl           
  0x00288363  0080f00b009a            add      byte ptr [eax - 0x65fff410], al 
  0x00288369  0200                    add      al, byte ptr [eax]             
  0x0028836B  00c0                    add      al, al                         
  0x0028836D  100d00040000            adc      byte ptr [0x400], cl           
  0x00288373  0080f00b00b1            add      byte ptr [eax - 0x4efff410], al 
  0x00288379  0200                    add      al, byte ptr [eax]             
  0x0028837B  0080f00b00e1            add      byte ptr [eax - 0x1efff410], al 
  0x00288381  0200                    add      al, byte ptr [eax]             
  0x00288383  000c00                  add      byte ptr [eax + eax], cl       
  0x00288386  0000                    add      byte ptr [eax], al             
  0x00288388  00f4                    add      ah, dh                         
  0x0028838A  6400a201000000          add      byte ptr fs:[edx + 1], ah      
  0x00288391  0c22                    or       al, 0x22                       
  0x00288393  00c0                    add      al, al                         
  0x00288395  40                      inc      eax                            
  0x00288396  0100                    add      dword ptr [eax], eax           
  0x00288398  0018                    add      byte ptr [eax], bl             
  0x0028839A  0000                    add      byte ptr [eax], al             
  0x0028839C  0090210080f0            add      byte ptr [eax - 0xf7fffdf], dl 
  0x002883A2  0b00                    or       eax, dword ptr [eax]           
  0x002883A4  7602                    jbe      0x2883a8                       
  0x002883A6  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x002883A4 (cond_jump)
  0x002883A8  80f00b                  xor      al, 0xb                        
  0x002883AB  00e1                    add      cl, ah                         
  0x002883AD  0200                    add      al, byte ptr [eax]             
  0x002883AF  000c00                  add      byte ptr [eax + eax], cl       
  0x002883B2  0000                    add      byte ptr [eax], al             
  0x002883B4  00f4                    add      ah, dh                         
  0x002883B6  6400a201000000          add      byte ptr fs:[edx + 1], ah      
  0x002883BD  0c22                    or       al, 0x22                       
  0x002883BF  00c0                    add      al, al                         
  0x002883C1  40                      inc      eax                            
  0x002883C2  0100                    add      dword ptr [eax], eax           
  0x002883C4  0018                    add      byte ptr [eax], bl             
  0x002883C6  0000                    add      byte ptr [eax], al             
  0x002883C8  0090210080f0            add      byte ptr [eax - 0xf7fffdf], dl 
  0x002883CE  0b00                    or       eax, dword ptr [eax]           
  0x002883D0  8802                    mov      byte ptr [edx], al             
  0x002883D2  0000                    add      byte ptr [eax], al             
  0x002883D4  80f00b                  xor      al, 0xb                        
  0x002883D7  00e1                    add      cl, ah                         
  0x002883D9  0200                    add      al, byte ptr [eax]             
  0x002883DB  000c00                  add      byte ptr [eax + eax], cl       
  0x002883DE  0000                    add      byte ptr [eax], al             
  0x002883E0  00f4                    add      ah, dh                         
  0x002883E2  6400a201000000          add      byte ptr fs:[edx + 1], ah      
  0x002883E9  0c22                    or       al, 0x22                       
  0x002883EB  00c0                    add      al, al                         
  0x002883ED  40                      inc      eax                            
  0x002883EE  0100                    add      dword ptr [eax], eax           
  0x002883F0  0028                    add      byte ptr [eax], ch             
  0x002883F2  0000                    add      byte ptr [eax], al             
  0x002883F4  0090210080f0            add      byte ptr [eax - 0xf7fffdf], dl 
  0x002883FA  0b00                    or       eax, dword ptr [eax]           
  0x002883FC  7602                    jbe      0x288400                       
  0x002883FE  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x002883FC (cond_jump)
  0x00288400  80f00b                  xor      al, 0xb                        
  0x00288403  00e1                    add      cl, ah                         
  0x00288405  0200                    add      al, byte ptr [eax]             
  0x00288407  000c00                  add      byte ptr [eax + eax], cl       
  0x0028840A  0000                    add      byte ptr [eax], al             
  0x0028840C  00f4                    add      ah, dh                         
  0x0028840E  6400a201000000          add      byte ptr fs:[edx + 1], ah      
  0x00288415  0c22                    or       al, 0x22                       
  0x00288417  00c0                    add      al, al                         
  0x00288419  40                      inc      eax                            
  0x0028841A  0100                    add      dword ptr [eax], eax           
  0x0028841C  0028                    add      byte ptr [eax], ch             
  0x0028841E  0000                    add      byte ptr [eax], al             
  0x00288420  0090210080f0            add      byte ptr [eax - 0xf7fffdf], dl 
  0x00288426  0b00                    or       eax, dword ptr [eax]           
  0x00288428  8802                    mov      byte ptr [edx], al             
  0x0028842A  0000                    add      byte ptr [eax], al             
  0x0028842C  80f00b                  xor      al, 0xb                        
  0x0028842F  00e1                    add      cl, ah                         
  0x00288431  0200                    add      al, byte ptr [eax]             
  0x00288433  000c00                  add      byte ptr [eax + eax], cl       
  0x00288436  0000                    add      byte ptr [eax], al             
  0x00288438  80f00b                  xor      al, 0xb                        
  0x0028843B  00d0                    add      al, dl                         
  0x0028843D  0200                    add      al, byte ptr [eax]             
  0x0028843F  0000                    add      byte ptr [eax], al             
  0x00288441  95                      xchg     ebp, eax                       
  0x00288442  2200                    and      al, byte ptr [eax]             
  0x00288444  008c2200c64001          add      byte ptr [edx + 0x140c600], cl 
  0x0028844B  00ff                    add      bh, bh                         
  0x0028844D  3f                      aas                                     
  0x0028844E  0000                    add      byte ptr [eax], al             
  0x00288450  c24001                  ret      0x140                          
  0x00288453  0000                    add      byte ptr [eax], al             
  0x00288455  40                      inc      eax                            
  0x00288456  0000                    add      byte ptr [eax], al             
  0x00288458  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x0028845B  0000                    add      byte ptr [eax], al             
  0x0028845D  f4                      hlt                                     
  0x0028845E  54                      push     esp                            
  0x0028845F  00e0                    add      al, ah                         
  0x00288461  5b                      pop      ebx                            
  0x00288462  0000                    add      byte ptr [eax], al             
  0x00288464  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x00288467  00985d070090            add      byte ptr [eax - 0x6ffff8a3], bl 
  0x0028846D  5d                      pop      ebp                            
  0x0028846E  07                      pop      es                             
  0x0028846F  0000                    add      byte ptr [eax], al             
  0x00288471  2e2200                  and      al, byte ptr cs:[eax]          
  0x00288474  841e                    test     byte ptr [esi], bl             
  0x00288476  0c00                    or       al, 0                          
  0x00288478  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x0028847B  000c00                  add      byte ptr [eax + eax], cl       
  0x0028847E  0000                    add      byte ptr [eax], al             
  0x00288480  80f00b                  xor      al, 0xb                        
  0x00288483  00d0                    add      al, dl                         
  0x00288485  0200                    add      al, byte ptr [eax]             
  0x00288487  0000                    add      byte ptr [eax], al             
  0x00288489  95                      xchg     ebp, eax                       
  0x0028848A  2200                    and      al, byte ptr [eax]             
  0x0028848C  008c2200c64001          add      byte ptr [edx + 0x140c600], cl 
  0x00288493  00ff                    add      bh, bh                         
  0x00288495  3f                      aas                                     
  0x00288496  0000                    add      byte ptr [eax], al             
  0x00288498  c24001                  ret      0x140                          
  0x0028849B  0000                    add      byte ptr [eax], al             
  0x0028849D  40                      inc      eax                            
  0x0028849E  0000                    add      byte ptr [eax], al             
  0x002884A0  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x002884A3  0000                    add      byte ptr [eax], al             
  0x002884A5  f4                      hlt                                     
  0x002884A6  54                      push     esp                            
  0x002884A7  00e2                    add      dl, ah                         
  0x002884A9  5b                      pop      ebx                            
  0x002884AA  0000                    add      byte ptr [eax], al             
  0x002884AC  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x002884AF  00985d070090            add      byte ptr [eax - 0x6ffff8a3], bl 
  0x002884B5  5d                      pop      ebp                            
  0x002884B6  07                      pop      es                             
  0x002884B7  0000                    add      byte ptr [eax], al             
  0x002884B9  2e2200                  and      al, byte ptr cs:[eax]          
  0x002884BC  841e                    test     byte ptr [esi], bl             
  0x002884BE  0c00                    or       al, 0                          
  0x002884C0  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x002884C3  000c00                  add      byte ptr [eax + eax], cl       
  0x002884C6  0000                    add      byte ptr [eax], al             
  0x002884C8  80f00b                  xor      al, 0xb                        
  0x002884CB  00d0                    add      al, dl                         
  0x002884CD  0200                    add      al, byte ptr [eax]             
  0x002884CF  0000                    add      byte ptr [eax], al             
  0x002884D1  95                      xchg     ebp, eax                       
  0x002884D2  2200                    and      al, byte ptr [eax]             
  0x002884D4  008c2200c64001          add      byte ptr [edx + 0x140c600], cl 
  0x002884DB  00ff                    add      bh, bh                         
  0x002884DD  3f                      aas                                     
  0x002884DE  0000                    add      byte ptr [eax], al             
  0x002884E0  c24001                  ret      0x140                          
  0x002884E3  0000                    add      byte ptr [eax], al             
  0x002884E5  40                      inc      eax                            
  0x002884E6  0000                    add      byte ptr [eax], al             
  0x002884E8  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x002884EB  0000                    add      byte ptr [eax], al             
  0x002884ED  f4                      hlt                                     
  0x002884EE  54                      push     esp                            
  0x002884EF  0002                    add      byte ptr [edx], al             
  0x002884F1  46                      inc      esi                            
  0x002884F2  0000                    add      byte ptr [eax], al             
  0x002884F4  002f                    add      byte ptr [edi], ch             
  0x002884F6  2200                    and      al, byte ptr [eax]             
  0x002884F8  8b1e                    mov      ebx, dword ptr [esi]           
  0x002884FA  0c00                    or       al, 0                          
  0x002884FC  00e5                    add      ch, ah                         
  0x002884FE  2100                    and      dword ptr [eax], eax           
  0x00288500  6200                    bound    eax, qword ptr [eax]           
  0x00288502  2000                    and      byte ptr [eax], al             
  0x00288504  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x00288507  00985d070000            add      byte ptr [eax + 0x75d], bl     
  0x0028850D  8e23                    mov      fs, word ptr [ebx]             
  0x0028850F  009c1e0c000004          add      byte ptr [esi + ebx + 0x400000c], bl 
  0x00288516  2200                    and      al, byte ptr [eax]             
  0x00288518  40                      inc      eax                            
  0x00288519  0020                    add      byte ptr [eax], ah             
  0x0028851B  008c5d07000c00          add      byte ptr [ebp + ebx*2 + 0xc0007], cl 
  0x00288522  0000                    add      byte ptr [eax], al             
  0x00288524  80f00b                  xor      al, 0xb                        
  0x00288527  00d0                    add      al, dl                         
  0x00288529  0200                    add      al, byte ptr [eax]             
  0x0028852B  0000                    add      byte ptr [eax], al             
  0x0028852D  95                      xchg     ebp, eax                       
  0x0028852E  2200                    and      al, byte ptr [eax]             
  0x00288530  008c2200c64001          add      byte ptr [edx + 0x140c600], cl 
  0x00288537  00ff                    add      bh, bh                         
  0x00288539  3f                      aas                                     
  0x0028853A  0000                    add      byte ptr [eax], al             
  0x0028853C  c24001                  ret      0x140                          
  0x0028853F  0000                    add      byte ptr [eax], al             
  0x00288541  40                      inc      eax                            
  0x00288542  0000                    add      byte ptr [eax], al             
  0x00288544  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x00288547  0000                    add      byte ptr [eax], al             
  0x00288549  f4                      hlt                                     
  0x0028854A  54                      push     esp                            
  0x0028854B  0003                    add      byte ptr [ebx], al             
  0x0028854D  06                      push     es                             
  0x0028854E  0000                    add      byte ptr [eax], al             
  0x00288550  002f                    add      byte ptr [edi], ch             
  0x00288552  2200                    and      al, byte ptr [eax]             
  0x00288554  8b1e                    mov      ebx, dword ptr [esi]           
  0x00288556  0c00                    or       al, 0                          
  0x00288558  00e5                    add      ch, ah                         
  0x0028855A  2100                    and      dword ptr [eax], eax           
  0x0028855C  6200                    bound    eax, qword ptr [eax]           
  0x0028855E  2000                    and      byte ptr [eax], al             
  0x00288560  000f                    add      byte ptr [edi], cl             
  0x00288562  2300                    and      eax, dword ptr [eax]           
  0x00288564  9d                      popfd                                   
  0x00288565  1e                      push     ds                             
  0x00288566  0c00                    or       al, 0                          
  0x00288568  00e5                    add      ch, ah                         
  0x0028856A  2100                    and      dword ptr [eax], eax           
  0x0028856C  6200                    bound    eax, qword ptr [eax]           
  0x0028856E  2000                    and      byte ptr [eax], al             
  0x00288570  8c5d07                  mov      word ptr [ebp + 7], ds         
  0x00288573  0000                    add      byte ptr [eax], al             
  0x00288575  0f2300                  mov      dr0, eax                       
  0x00288578  891e                    mov      dword ptr [esi], ebx           
  0x0028857A  0c00                    or       al, 0                          
  0x0028857C  004523                  add      byte ptr [ebp + 0x23], al      
  0x0028857F  006800                  add      byte ptr [eax], ch             
  0x00288582  2000                    and      byte ptr [eax], al             
  0x00288584  8d5d07                  lea      ebx, [ebp + 7]                 
  0x00288587  0000                    add      byte ptr [eax], al             
  0x00288589  8e23                    mov      fs, word ptr [ebx]             
  0x0028858B  009c1e0c000004          add      byte ptr [esi + ebx + 0x400000c], bl 
  0x00288592  2200                    and      al, byte ptr [eax]             
  0x00288594  40                      inc      eax                            
  0x00288595  0020                    add      byte ptr [eax], ah             
  0x00288597  008c5d07000c00          add      byte ptr [ebp + ebx*2 + 0xc0007], cl 
  0x0028859E  0000                    add      byte ptr [eax], al             
  0x002885A0  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x002885A1  96                      xchg     esi, eax                       
  0x002885A2  0a00                    or       al, byte ptr [eax]             
  0x002885A4  d002                    rol      byte ptr [edx], 1              
  0x002885A6  0000                    add      byte ptr [eax], al             
  0x002885A8  85f4                    test     esp, esi                       
  0x002885AA  0800                    or       byte ptr [eax], al             
  0x002885AC  800000                  add      byte ptr [eax], 0              
  0x002885AF  000c00                  add      byte ptr [eax + eax], cl       
  0x002885B2  0000                    add      byte ptr [eax], al             
  0x002885B4  96                      xchg     esi, eax                       
  0x002885B5  f4                      hlt                                     
  0x002885B6  0800                    or       byte ptr [eax], al             
  0x002885B8  0100                    add      dword ptr [eax], eax           
  0x002885BA  0000                    add      byte ptr [eax], al             
  0x002885BC  84960a00d702            test     byte ptr [esi + 0x2d7000a], dl 
  0x002885C2  0000                    add      byte ptr [eax], al             
  0x002885C4  0c00                    or       al, 0                          
  0x002885C6  0000                    add      byte ptr [eax], al             
  0x002885C8  aa                      stosb    byte ptr es:[edi], al          
  0x002885C9  850a                    test     dword ptr [edx], ecx           
  0x002885CB  00fe                    add      dh, bh                         
  0x002885CD  0200                    add      al, byte ptr [eax]             
  0x002885CF  0087850a00da            add      byte ptr [edi - 0x25fff57b], al 
  0x002885D5  0200                    add      al, byte ptr [eax]             
  0x002885D7  0085f4080080            add      byte ptr [ebp - 0x7ffff70c], al 
  0x002885DD  0000                    add      byte ptr [eax], al             
  0x002885DF  000c00                  add      byte ptr [eax + eax], cl       
  0x002885E2  0000                    add      byte ptr [eax], al             
  0x002885E4  008e2200c040            add      byte ptr [esi + 0x40c00022], cl 
  0x002885EA  0100                    add      dword ptr [eax], eax           
  0x002885EC  0028                    add      byte ptr [eax], ch             
  0x002885EE  0000                    add      byte ptr [eax], al             
  0x002885F0  14ce                    adc      al, 0xce                       
  0x002885F2  0800                    or       byte ptr [eax], al             
  0x002885F4  80f00b                  xor      al, 0xb                        
  0x002885F7  00d5                    add      ch, dl                         
  0x002885F9  0200                    add      al, byte ptr [eax]             
  0x002885FB  001b                    add      byte ptr [ebx], bl             
  0x002885FD  0020                    add      byte ptr [eax], ah             
  0x002885FF  0000                    add      byte ptr [eax], al             
  0x00288601  af                      scasd    eax, dword ptr es:[edi]        
  0x00288602  2300                    and      eax, dword ptr [eax]           
  0x00288604  8d4001                  lea      eax, [eax + 1]                 
  0x00288607  004a10                  add      byte ptr [edx + 0x10], cl      
  0x0028860A  0d00040000              or       eax, 0x400                     
  0x0028860F  0080f00b00da            add      byte ptr [eax - 0x25fff410], al 
  0x00288615  0200                    add      al, byte ptr [eax]             
  0x00288617  000c00                  add      byte ptr [eax + eax], cl       
  0x0028861A  0000                    add      byte ptr [eax], al             
  0x0028861C  85f4                    test     esp, esi                       
  0x0028861E  0800                    or       byte ptr [eax], al             
  0x00288620  ff0f                    dec      dword ptr [edi]                
  0x00288622  0000                    add      byte ptr [eax], al             
  0x00288624  84f4                    test     ah, dh                         
  0x00288626  0800                    or       byte ptr [eax], al             
  0x00288628  0100                    add      dword ptr [eax], eax           
  0x0028862A  0000                    add      byte ptr [eax], al             
  0x0028862C  8af4                    mov      dh, ah                         
  0x0028862E  0800                    or       byte ptr [eax], al             
  0x00288630  0000                    add      byte ptr [eax], al             
  0x00288632  0000                    add      byte ptr [eax], al             
  0x00288634  00f4                    add      ah, dh                         
  0x00288636  44                      inc      esp                            
  0x00288637  0000                    add      byte ptr [eax], al             
  0x00288639  40                      inc      eax                            
  0x0028863A  0000                    add      byte ptr [eax], al             
  0x0028863C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028863F  00d5                    add      ch, dl                         
  0x00288642  ff00                    inc      dword ptr [eax]                
  0x00288644  007044                  add      byte ptr [eax + 0x44], dh      
  0x00288647  00d4                    add      ah, dl                         
  0x0028864A  ff00                    inc      dword ptr [eax]                
  0x0028864C  97                      xchg     edi, eax                       
  0x0028864D  f4                      hlt                                     
  0x0028864E  0800                    or       byte ptr [eax], al             
  0x00288650  0000                    add      byte ptr [eax], al             
  0x00288652  0000                    add      byte ptr [eax], al             
  0x00288654  0c00                    or       al, 0                          
  0x00288656  0000                    add      byte ptr [eax], al             
  0x00288658  000c0500000000          add      byte ptr [eax], cl             
  0x0028865F  00401b                  add      byte ptr [eax + 0x1b], al      
  0x00288662  d000                    rol      byte ptr [eax], 1              
  0x00288664  f20200                  add      al, byte ptr [eax]             
  0x00288667  007201                  add      byte ptr [edx + 1], dh         
  0x0028866A  0100                    add      dword ptr [eax], eax           
  0x0028866C  11f5                    adc      ebp, esi                       
  0x0028866E  f700400c0500            test     dword ptr [eax], 0x50c40       
  0x00288674  37                      aaa                                     
  0x00288675  0c04                    or       al, 4                          
  0x00288677  00a78a040084            add      byte ptr [edi - 0x7bfffb76], ah 
  0x0028867D  180500b1b705            sbb      byte ptr [0x5b7b100], al       
  0x00288683  004a6a                  add      byte ptr [edx + 0x6a], cl      
  0x00288686  06                      push     es                             
  0x00288687  00ae32070085            add      byte ptr [esi - 0x7afff8ce], ch 
  0x0028868D  1308                    adc      ecx, dword ptr [eax]           
  0x0028868F  00cc                    add      ah, cl                         
  0x00288691  0f09                    wbinvd                                  
  0x00288693  00db                    add      bl, bl                         
  0x00288695  2a0a                    sub      cl, byte ptr [edx]             
  0x00288697  007368                  add      byte ptr [ebx + 0x68], dh      
  0x0028869A  0b00                    or       eax, dword ptr [eax]           
  0x0028869C  cdcc                    int      0xcc                           
  0x0028869E  0c00                    or       al, 0                          
  0x002886A0  a15c0e003f              mov      eax, dword ptr [0x3f000e5c]    
  0x002886A5  1d10009a14              sbb      eax, 0x149a0010                
  0x002886AA  1200                    adc      al, byte ptr [eax]             
  0x002886AC  61                      popal                                   
  0x002886AD  49                      dec      ecx                            
  0x002886AE  1400                    adc      al, 0                          
  0x002886B0  11c3                    adc      ebx, eax                       
  0x002886B2  16                      push     ss                             
  0x002886B3  0013                    add      byte ptr [ebx], dl             
  0x002886B5  8a19                    mov      bl, byte ptr [ecx]             
  0x002886B7  00d7                    add      bh, dl                         
  0x002886B9  a7                      cmpsd    dword ptr [esi], dword ptr es:[edi] 
  0x002886BA  1c00                    sbb      al, 0                          
  0x002886BC  f3262000                and      byte ptr es:[eax], al          
  0x002886C0  47                      inc      edi                            
  0x002886C1  132400                  adc      esp, dword ptr [eax + eax]     
  0x002886C4  27                      daa                                     
  0x002886C5  7a28                    jp       0x2886ef                       
  0x002886C7  00866a2d002d            add      byte ptr [esi + 0x2d002d6a], al 
  0x002886CD  f5                      cmc                                     
  0x002886CE  3200                    xor      al, byte ptr [eax]             
  0x002886D0  ee                      out      dx, al                         
  0x002886D1  2c39                    sub      al, 0x39                       
  0x002886D3  00e7                    add      bh, ah                         
  0x002886D5  2640                    inc      eax                            
  0x002886D7  00cd                    add      ch, cl                         
  0x002886D9  fa                      cli                                     
  0x002886DA  47                      inc      edi                            
  0x002886DB  0036                    add      byte ptr [esi], dh             
  0x002886DD  c3                      ret                                     
  0x002886DE  50                      push     eax                            
  0x002886DF  00f8                    add      al, bh                         
  0x002886E1  9d                      popfd                                   
  0x002886E2  5a                      pop      edx                            
  0x002886E3  008cac65008314          add      byte ptr [esp + ebp*4 + 0x14830065], cl 
  0x002886EA  7200                    jb       0x2886ec                       
  0x002886EE  7f00                    jg       0x2886f0                       
                                        ; XREF: 0x002886EE (cond_jump)
  0x002886F0  007060                  add      byte ptr [eax + 0x60], dh      
  0x002886F3  002e                    add      byte ptr [esi], ch             
  0x002886F5  06                      push     es                             
  0x002886F6  0000                    add      byte ptr [eax], al             
  0x002886F8  0b00                    or       eax, dword ptr [eax]           
  0x002886FA  2000                    and      byte ptr [eax], al             
  0x002886FC  06                      push     es                             
  0x002886FD  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x002886FE  050000f444              add      eax, 0x44f40000                
  0x00288703  0002                    add      byte ptr [edx], al             
  0x00288705  800000                  add      byte ptr [eax], 0              
  0x00288708  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028870B  000406                  add      byte ptr [esi + eax], al       
  0x0028870E  0000                    add      byte ptr [eax], al             
  0x00288710  050c050000              add      eax, 0x50c                     
  0x00288715  f4                      hlt                                     
  0x00288716  44                      inc      esp                            
  0x00288717  0002                    add      byte ptr [edx], al             
  0x00288719  0000                    add      byte ptr [eax], al             
  0x0028871B  0000                    add      byte ptr [eax], al             
  0x0028871D  7044                    jo       0x288763                       
  0x0028871F  000406                  add      byte ptr [esi + eax], al       
  0x00288722  0000                    add      byte ptr [eax], al             
  0x00288724  00f4                    add      ah, dh                         
  0x00288726  44                      inc      esp                            
  0x00288727  000a                    add      byte ptr [edx], cl             
  0x00288729  0000                    add      byte ptr [eax], al             
  0x0028872B  0000                    add      byte ptr [eax], al             
  0x0028872D  7044                    jo       0x288773                       
  0x0028872F  0000                    add      byte ptr [eax], al             
  0x00288731  06                      push     es                             
  0x00288732  0000                    add      byte ptr [eax], al             
  0x00288734  00f4                    add      ah, dh                         
  0x00288736  44                      inc      esp                            
  0x00288737  000a                    add      byte ptr [edx], cl             
  0x00288739  06                      push     es                             
  0x0028873A  0000                    add      byte ptr [eax], al             
  0x0028873C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028873F  0001                    add      byte ptr [ecx], al             
  0x00288741  06                      push     es                             
  0x00288742  0000                    add      byte ptr [eax], al             
  0x00288744  00f4                    add      ah, dh                         
  0x00288746  44                      inc      esp                            
  0x00288747  0010                    add      byte ptr [eax], dl             
  0x00288749  06                      push     es                             
  0x0028874A  0000                    add      byte ptr [eax], al             
  0x0028874C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028874F  0002                    add      byte ptr [edx], al             
  0x00288751  06                      push     es                             
  0x00288752  0000                    add      byte ptr [eax], al             
  0x00288754  00f4                    add      ah, dh                         
  0x00288756  44                      inc      esp                            
  0x00288757  0016                    add      byte ptr [esi], dl             
  0x00288759  06                      push     es                             
  0x0028875A  0000                    add      byte ptr [eax], al             
  0x0028875C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028875F  0003                    add      byte ptr [ebx], al             
  0x00288761  06                      push     es                             
  0x00288762  0000                    add      byte ptr [eax], al             
  0x00288764  00f4                    add      ah, dh                         
  0x00288766  44                      inc      esp                            
  0x00288767  001c06                  add      byte ptr [esi + eax], bl       
  0x0028876A  0000                    add      byte ptr [eax], al             
  0x0028876C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028876F  000506000000            add      byte ptr [6], al               
  0x00288775  f4                      hlt                                     
  0x00288776  44                      inc      esp                            
  0x00288777  0022                    add      byte ptr [edx], ah             
  0x00288779  06                      push     es                             
  0x0028877A  0000                    add      byte ptr [eax], al             
  0x0028877C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028877F  0006                    add      byte ptr [esi], al             
  0x00288781  06                      push     es                             
  0x00288782  0000                    add      byte ptr [eax], al             
  0x00288784  00f4                    add      ah, dh                         
  0x00288786  44                      inc      esp                            
  0x00288787  0028                    add      byte ptr [eax], ch             
  0x00288789  06                      push     es                             
  0x0028878A  0000                    add      byte ptr [eax], al             
  0x0028878C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028878F  0007                    add      byte ptr [edi], al             
  0x00288791  06                      push     es                             
  0x00288792  0000                    add      byte ptr [eax], al             
  0x00288794  00f4                    add      ah, dh                         
  0x00288796  44                      inc      esp                            
  0x00288797  0000                    add      byte ptr [eax], al             
  0x00288799  0000                    add      byte ptr [eax], al             
  0x0028879B  0000                    add      byte ptr [eax], al             
  0x0028879D  7044                    jo       0x2887e3                       
  0x0028879F  0008                    add      byte ptr [eax], cl             
  0x002887A1  06                      push     es                             
  0x002887A2  0000                    add      byte ptr [eax], al             
  0x002887A4  00f4                    add      ah, dh                         
  0x002887A6  44                      inc      esp                            
  0x002887A7  0000                    add      byte ptr [eax], al             
  0x002887A9  0100                    add      dword ptr [eax], eax           
  0x002887AB  0000                    add      byte ptr [eax], al             
  0x002887AD  7044                    jo       0x2887f3                       
  0x002887AF  0009                    add      byte ptr [ecx], cl             
  0x002887B1  06                      push     es                             
  0x002887B2  0000                    add      byte ptr [eax], al             
  0x002887B4  00f4                    add      ah, dh                         
  0x002887B6  60                      pushal                                  
  0x002887B7  000a                    add      byte ptr [edx], cl             
  0x002887B9  06                      push     es                             
  0x002887BA  0000                    add      byte ptr [eax], al             
  0x002887BC  00f4                    add      ah, dh                         
  0x002887BE  44                      inc      esp                            
  0x002887BF  0000                    add      byte ptr [eax], al             
  0x002887C1  0000                    add      byte ptr [eax], al             
  0x002887C3  0000                    add      byte ptr [eax], al             
  0x002887C5  58                      pop      eax                            
  0x002887C6  44                      inc      esp                            
  0x002887C7  0000                    add      byte ptr [eax], al             
  0x002887C9  f4                      hlt                                     
  0x002887CA  44                      inc      esp                            
  0x002887CB  0000                    add      byte ptr [eax], al             
  0x002887CD  0100                    add      dword ptr [eax], eax           
  0x002887CF  0000                    add      byte ptr [eax], al             
  0x002887D1  58                      pop      eax                            
  0x002887D2  44                      inc      esp                            
  0x002887D3  0000                    add      byte ptr [eax], al             
  0x002887D5  f4                      hlt                                     
  0x002887D6  44                      inc      esp                            
  0x002887D7  0000                    add      byte ptr [eax], al             
  0x002887D9  0200                    add      al, byte ptr [eax]             
  0x002887DB  0000                    add      byte ptr [eax], al             
  0x002887DD  58                      pop      eax                            
  0x002887DE  44                      inc      esp                            
  0x002887DF  0000                    add      byte ptr [eax], al             
  0x002887E1  f4                      hlt                                     
  0x002887E2  44                      inc      esp                            
                                        ; XREF: 0x0028879D (cond_jump)
  0x002887E3  0000                    add      byte ptr [eax], al             
  0x002887E5  0300                    add      eax, dword ptr [eax]           
  0x002887E7  0000                    add      byte ptr [eax], al             
  0x002887E9  58                      pop      eax                            
  0x002887EA  44                      inc      esp                            
  0x002887EB  0000                    add      byte ptr [eax], al             
  0x002887ED  f4                      hlt                                     
  0x002887EE  44                      inc      esp                            
  0x002887EF  0000                    add      byte ptr [eax], al             
  0x002887F1  0400                    add      al, 0                          
                                        ; XREF: 0x002887AD (cond_jump)
  0x002887F3  0000                    add      byte ptr [eax], al             
  0x002887F5  58                      pop      eax                            
  0x002887F6  44                      inc      esp                            
  0x002887F7  0000                    add      byte ptr [eax], al             
  0x002887F9  f4                      hlt                                     
  0x002887FA  44                      inc      esp                            
  0x002887FB  00ff                    add      bh, bh                         
  0x002887FE  ff00                    inc      dword ptr [eax]                
  0x00288800  006044                  add      byte ptr [eax + 0x44], ah      
  0x00288803  0000                    add      byte ptr [eax], al             
  0x00288805  f4                      hlt                                     
  0x00288806  60                      pushal                                  
  0x00288807  0010                    add      byte ptr [eax], dl             
  0x00288809  06                      push     es                             
  0x0028880A  0000                    add      byte ptr [eax], al             
  0x0028880C  00f4                    add      ah, dh                         
  0x0028880E  44                      inc      esp                            
  0x0028880F  0001                    add      byte ptr [ecx], al             
  0x00288811  0000                    add      byte ptr [eax], al             
  0x00288813  0000                    add      byte ptr [eax], al             
  0x00288815  58                      pop      eax                            
  0x00288816  44                      inc      esp                            
  0x00288817  0000                    add      byte ptr [eax], al             
  0x00288819  58                      pop      eax                            
  0x0028881A  44                      inc      esp                            
  0x0028881B  0000                    add      byte ptr [eax], al             
  0x0028881D  58                      pop      eax                            
  0x0028881E  44                      inc      esp                            
  0x0028881F  0000                    add      byte ptr [eax], al             
  0x00288821  58                      pop      eax                            
  0x00288822  44                      inc      esp                            
  0x00288823  0000                    add      byte ptr [eax], al             
  0x00288825  58                      pop      eax                            
  0x00288826  44                      inc      esp                            
  0x00288827  0000                    add      byte ptr [eax], al             
  0x00288829  002400                  add      byte ptr [eax + eax], ah       
  0x0028882C  006044                  add      byte ptr [eax + 0x44], ah      
  0x0028882F  0000                    add      byte ptr [eax], al             
  0x00288831  f4                      hlt                                     
  0x00288832  60                      pushal                                  
  0x00288833  0016                    add      byte ptr [esi], dl             
  0x00288835  06                      push     es                             
  0x00288836  0000                    add      byte ptr [eax], al             
  0x00288838  00f4                    add      ah, dh                         
  0x0028883A  44                      inc      esp                            
  0x0028883B  00ff                    add      bh, bh                         
  0x0028883E  ff00                    inc      dword ptr [eax]                
  0x00288840  005844                  add      byte ptr [eax + 0x44], bl      
  0x00288843  0000                    add      byte ptr [eax], al             
  0x00288845  58                      pop      eax                            
  0x00288846  44                      inc      esp                            
  0x00288847  0000                    add      byte ptr [eax], al             
  0x00288849  58                      pop      eax                            
  0x0028884A  44                      inc      esp                            
  0x0028884B  0000                    add      byte ptr [eax], al             
  0x0028884D  58                      pop      eax                            
  0x0028884E  44                      inc      esp                            
  0x0028884F  0000                    add      byte ptr [eax], al             
  0x00288851  58                      pop      eax                            
  0x00288852  44                      inc      esp                            
  0x00288853  0000                    add      byte ptr [eax], al             
  0x00288855  60                      pushal                                  
  0x00288856  44                      inc      esp                            
  0x00288857  0000                    add      byte ptr [eax], al             
  0x00288859  f4                      hlt                                     
  0x0028885A  60                      pushal                                  
  0x0028885B  001c06                  add      byte ptr [esi + eax], bl       
  0x0028885E  0000                    add      byte ptr [eax], al             
  0x00288860  00f4                    add      ah, dh                         
  0x00288862  44                      inc      esp                            
  0x00288863  0000                    add      byte ptr [eax], al             
  0x00288865  0400                    add      al, 0                          
  0x00288867  0000                    add      byte ptr [eax], al             
  0x00288869  58                      pop      eax                            
  0x0028886A  44                      inc      esp                            
  0x0028886B  0000                    add      byte ptr [eax], al             
  0x0028886D  f4                      hlt                                     
  0x0028886E  44                      inc      esp                            
  0x0028886F  00ff                    add      bh, bh                         
  0x00288872  ff00                    inc      dword ptr [eax]                
  0x00288874  005844                  add      byte ptr [eax + 0x44], bl      
  0x00288877  0000                    add      byte ptr [eax], al             
  0x00288879  f4                      hlt                                     
  0x0028887A  44                      inc      esp                            
  0x0028887B  0000                    add      byte ptr [eax], al             
  0x0028887D  0500000058              add      eax, 0x58000000                
  0x00288882  44                      inc      esp                            
  0x00288883  0000                    add      byte ptr [eax], al             
  0x00288885  f4                      hlt                                     
  0x00288886  44                      inc      esp                            
  0x00288887  00ff                    add      bh, bh                         
  0x0028888A  ff00                    inc      dword ptr [eax]                
  0x0028888C  005844                  add      byte ptr [eax + 0x44], bl      
  0x0028888F  0000                    add      byte ptr [eax], al             
  0x00288891  f4                      hlt                                     
  0x00288892  44                      inc      esp                            
  0x00288893  00ff                    add      bh, bh                         
  0x00288896  ff00                    inc      dword ptr [eax]                
  0x00288898  005844                  add      byte ptr [eax + 0x44], bl      
  0x0028889B  0000                    add      byte ptr [eax], al             
  0x0028889D  f4                      hlt                                     
  0x0028889E  44                      inc      esp                            
  0x0028889F  00ff                    add      bh, bh                         
  0x002888A2  ff00                    inc      dword ptr [eax]                
  0x002888A4  005844                  add      byte ptr [eax + 0x44], bl      
  0x002888A7  0000                    add      byte ptr [eax], al             
  0x002888A9  f4                      hlt                                     
  0x002888AA  60                      pushal                                  
  0x002888AB  0022                    add      byte ptr [edx], ah             
  0x002888AD  06                      push     es                             
  0x002888AE  0000                    add      byte ptr [eax], al             
  0x002888B0  00f4                    add      ah, dh                         
  0x002888B2  44                      inc      esp                            
  0x002888B3  0001                    add      byte ptr [ecx], al             
  0x002888B5  0000                    add      byte ptr [eax], al             
  0x002888B7  0000                    add      byte ptr [eax], al             
  0x002888B9  58                      pop      eax                            
  0x002888BA  44                      inc      esp                            
  0x002888BB  0000                    add      byte ptr [eax], al             
  0x002888BD  002400                  add      byte ptr [eax + eax], ah       
  0x002888C0  005844                  add      byte ptr [eax + 0x44], bl      
  0x002888C3  0000                    add      byte ptr [eax], al             
  0x002888C5  f4                      hlt                                     
  0x002888C6  44                      inc      esp                            
  0x002888C7  0001                    add      byte ptr [ecx], al             
  0x002888C9  0000                    add      byte ptr [eax], al             
  0x002888CB  0000                    add      byte ptr [eax], al             
  0x002888CD  58                      pop      eax                            
  0x002888CE  44                      inc      esp                            
  0x002888CF  0000                    add      byte ptr [eax], al             
  0x002888D1  002400                  add      byte ptr [eax + eax], ah       
  0x002888D4  005844                  add      byte ptr [eax + 0x44], bl      
  0x002888D7  0000                    add      byte ptr [eax], al             
  0x002888D9  002400                  add      byte ptr [eax + eax], ah       
  0x002888DC  005844                  add      byte ptr [eax + 0x44], bl      
  0x002888DF  0000                    add      byte ptr [eax], al             
  0x002888E1  002400                  add      byte ptr [eax + eax], ah       
  0x002888E4  005844                  add      byte ptr [eax + 0x44], bl      
  0x002888E7  0000                    add      byte ptr [eax], al             
  0x002888E9  f4                      hlt                                     
  0x002888EA  60                      pushal                                  
  0x002888EB  0028                    add      byte ptr [eax], ch             
  0x002888ED  06                      push     es                             
  0x002888EE  0000                    add      byte ptr [eax], al             
  0x002888F0  00f4                    add      ah, dh                         
  0x002888F2  44                      inc      esp                            
  0x002888F3  00ff                    add      bh, bh                         
  0x002888F6  ff00                    inc      dword ptr [eax]                
  0x002888F8  005844                  add      byte ptr [eax + 0x44], bl      
  0x002888FB  0000                    add      byte ptr [eax], al             
  0x002888FD  58                      pop      eax                            
  0x002888FE  44                      inc      esp                            
  0x002888FF  0000                    add      byte ptr [eax], al             
  0x00288901  58                      pop      eax                            
  0x00288902  44                      inc      esp                            
  0x00288903  0000                    add      byte ptr [eax], al             
  0x00288905  58                      pop      eax                            
  0x00288906  44                      inc      esp                            
  0x00288907  0000                    add      byte ptr [eax], al             
  0x00288909  58                      pop      eax                            
  0x0028890A  44                      inc      esp                            
  0x0028890B  0000                    add      byte ptr [eax], al             
  0x0028890D  58                      pop      eax                            
  0x0028890E  44                      inc      esp                            
  0x0028890F  0000                    add      byte ptr [eax], al             
  0x00288911  f4                      hlt                                     
  0x00288912  56                      push     esi                            
  0x00288913  0007                    add      byte ptr [edi], al             
  0x00288915  0000                    add      byte ptr [eax], al             
  0x00288917  0000                    add      byte ptr [eax], al             
  0x00288919  f4                      hlt                                     
  0x0028891A  60                      pushal                                  
  0x0028891B  0000                    add      byte ptr [eax], al             
  0x0028891D  0000                    add      byte ptr [eax], al             
  0x0028891F  0000                    add      byte ptr [eax], al             
  0x00288921  f4                      hlt                                     
  0x00288922  7000                    jo       0x288924                       
                                        ; XREF: 0x00288922 (cond_jump)
  0x00288924  0001                    add      byte ptr [ecx], al             
  0x00288926  0000                    add      byte ptr [eax], al             
  0x00288928  0000                    add      byte ptr [eax], al             
  0x0028892A  3900                    cmp      dword ptr [eax], eax           
  0x0028892C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028892F  0000                    add      byte ptr [eax], al             
  0x00288931  f4                      hlt                                     
  0x00288932  56                      push     esi                            
  0x00288933  0007                    add      byte ptr [edi], al             
  0x00288935  0000                    add      byte ptr [eax], al             
  0x00288937  0000                    add      byte ptr [eax], al             
  0x00288939  f4                      hlt                                     
  0x0028893A  60                      pushal                                  
  0x0028893B  0000                    add      byte ptr [eax], al             
  0x0028893D  0100                    add      dword ptr [eax], eax           
  0x0028893F  0000                    add      byte ptr [eax], al             
  0x00288941  f4                      hlt                                     
  0x00288942  7000                    jo       0x288944                       
                                        ; XREF: 0x00288942 (cond_jump)
  0x00288944  0001                    add      byte ptr [ecx], al             
  0x00288946  0000                    add      byte ptr [eax], al             
  0x00288948  0001                    add      byte ptr [ecx], al             
  0x0028894A  3900                    cmp      dword ptr [eax], eax           
  0x0028894C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028894F  0000                    add      byte ptr [eax], al             
  0x00288951  f4                      hlt                                     
  0x00288952  56                      push     esi                            
  0x00288953  0007                    add      byte ptr [edi], al             
  0x00288955  0000                    add      byte ptr [eax], al             
  0x00288957  0000                    add      byte ptr [eax], al             
  0x00288959  f4                      hlt                                     
  0x0028895A  60                      pushal                                  
  0x0028895B  0000                    add      byte ptr [eax], al             
  0x0028895D  0200                    add      al, byte ptr [eax]             
  0x0028895F  0000                    add      byte ptr [eax], al             
  0x00288961  f4                      hlt                                     
  0x00288962  7000                    jo       0x288964                       
                                        ; XREF: 0x00288962 (cond_jump)
  0x00288964  0001                    add      byte ptr [ecx], al             
  0x00288966  0000                    add      byte ptr [eax], al             
  0x00288968  0002                    add      byte ptr [edx], al             
  0x0028896A  3900                    cmp      dword ptr [eax], eax           
  0x0028896C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028896F  0000                    add      byte ptr [eax], al             
  0x00288971  f4                      hlt                                     
  0x00288972  56                      push     esi                            
  0x00288973  0007                    add      byte ptr [edi], al             
  0x00288975  0000                    add      byte ptr [eax], al             
  0x00288977  0000                    add      byte ptr [eax], al             
  0x00288979  f4                      hlt                                     
  0x0028897A  60                      pushal                                  
  0x0028897B  0000                    add      byte ptr [eax], al             
  0x0028897D  0300                    add      eax, dword ptr [eax]           
  0x0028897F  0000                    add      byte ptr [eax], al             
  0x00288981  f4                      hlt                                     
  0x00288982  7000                    jo       0x288984                       
                                        ; XREF: 0x00288982 (cond_jump)
  0x00288984  0001                    add      byte ptr [ecx], al             
  0x00288986  0000                    add      byte ptr [eax], al             
  0x00288988  0003                    add      byte ptr [ebx], al             
  0x0028898A  3900                    cmp      dword ptr [eax], eax           
  0x0028898C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028898F  0000                    add      byte ptr [eax], al             
  0x00288991  f4                      hlt                                     
  0x00288992  56                      push     esi                            
  0x00288993  0007                    add      byte ptr [edi], al             
  0x00288995  0000                    add      byte ptr [eax], al             
  0x00288997  0000                    add      byte ptr [eax], al             
  0x00288999  f4                      hlt                                     
  0x0028899A  60                      pushal                                  
  0x0028899B  0000                    add      byte ptr [eax], al             
  0x0028899D  0400                    add      al, 0                          
  0x0028899F  0000                    add      byte ptr [eax], al             
  0x002889A1  f4                      hlt                                     
  0x002889A2  7000                    jo       0x2889a4                       
                                        ; XREF: 0x002889A2 (cond_jump)
  0x002889A4  0001                    add      byte ptr [ecx], al             
  0x002889A6  0000                    add      byte ptr [eax], al             
  0x002889A8  000439                  add      byte ptr [ecx + edi], al       
  0x002889AB  0080010d0013            add      byte ptr [eax + 0x13000d01], al 
  0x002889B2  6200                    bound    eax, qword ptr [eax]           
  0x002889B4  2e06                    push     es                             
  0x002889B6  0000                    add      byte ptr [eax], al             
  0x002889B8  dc1a                    fcomp    qword ptr [edx]                
  0x002889BA  0200                    add      al, byte ptr [eax]             
  0x002889BC  00f4                    add      ah, dh                         
  0x002889BE  44                      inc      esp                            
  0x002889BF  0001                    add      byte ptr [ecx], al             
  0x002889C1  0000                    add      byte ptr [eax], al             
  0x002889C3  004500                  add      byte ptr [ebp], al             
  0x002889C6  2000                    and      byte ptr [eax], al             
  0x002889C8  41                      inc      ecx                            
  0x002889C9  2920                    sub      dword ptr [eax], esp           
  0x002889CB  0000                    add      byte ptr [eax], al             
  0x002889CD  f4                      hlt                                     
  0x002889CE  44                      inc      esp                            
  0x002889CF  001f                    add      byte ptr [edi], bl             
  0x002889D1  0000                    add      byte ptr [eax], al             
  0x002889D3  004500                  add      byte ptr [ebp], al             
  0x002889D6  2000                    and      byte ptr [eax], al             
  0x002889D8  41                      inc      ecx                            
  0x002889D9  27                      daa                                     
  0x002889DA  2000                    and      byte ptr [eax], al             
  0x002889DC  0098210000f4            add      byte ptr [eax - 0xbffffdf], bl 
  0x002889E2  60                      pushal                                  
  0x002889E3  000503000085            add      byte ptr [0x85000003], al      
  0x002889E9  e807009708              call     0x8bf89f5                      
  0x002889EE  050013f460              add      eax, 0x60f41300                
  0x002889F3  0000                    add      byte ptr [eax], al             
  0x002889F5  06                      push     es                             
  0x002889F6  0000                    add      byte ptr [eax], al             
  0x002889F8  00f4                    add      ah, dh                         
  0x002889FA  57                      push     edi                            
  0x002889FB  0016                    add      byte ptr [esi], dl             
  0x002889FD  0000                    add      byte ptr [eax], al             
  0x002889FF  0080100d005b            add      byte ptr [eax + 0x5b000d10], al 
  0x00288A05  0000                    add      byte ptr [eax], al             
  0x00288A07  0013                    add      byte ptr [ebx], dl             
  0x00288A09  f4                      hlt                                     
  0x00288A0A  6200                    bound    eax, qword ptr [eax]           
  0x00288A0C  000400                  add      byte ptr [eax + eax], al       
  0x00288A0F  001b                    add      byte ptr [ebx], bl             
  0x00288A11  0020                    add      byte ptr [eax], ah             
  0x00288A13  009100060005            add      byte ptr [ecx + 0x5000600], dl 
  0x00288A19  0000                    add      byte ptr [eax], al             
  0x00288A1B  0000                    add      byte ptr [eax], al             
  0x00288A1D  da44008a                fiadd    dword ptr [eax + eax - 0x76]   
  0x00288A21  0020                    add      byte ptr [eax], ah             
  0x00288A23  004700                  add      byte ptr [edi], al             
  0x00288A26  2000                    and      byte ptr [eax], al             
  0x00288A28  40                      inc      eax                            
  0x00288A29  90                      nop                                     
  0x00288A2A  0200                    add      al, byte ptr [eax]             
  0x00288A2C  260020                  add      byte ptr es:[eax], ah          
  0x00288A2F  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x00288A35  7056                    jo       0x288a8d                       
  0x00288A37  002f                    add      byte ptr [edi], ch             
  0x00288A39  06                      push     es                             
  0x00288A3A  0000                    add      byte ptr [eax], al             
  0x00288A3C  00a721000026            add      byte ptr [edi + 0x26000021], ah 
  0x00288A42  2100                    and      dword ptr [eax], eax           
  0x00288A44  13402f                  adc      eax, dword ptr [eax + 0x2f]    
  0x00288A47  009017060009            add      byte ptr [eax + 0x9000617], dl 
  0x00288A4D  0000                    add      byte ptr [eax], al             
  0x00288A4F  0010                    add      byte ptr [eax], dl             
  0x00288A51  c521                    lds      esp, ptr [ecx]                 
  0x00288A53  0000                    add      byte ptr [eax], al             
  0x00288A55  0000                    add      byte ptr [eax], al             
  0x00288A57  0000                    add      byte ptr [eax], al             
  0x00288A59  c421                    les      esp, ptr [ecx]                 
  0x00288A5B  00840020003000          add      byte ptr [eax + eax + 0x300020], al 
  0x00288A62  2000                    and      byte ptr [eax], al             
  0x00288A64  00ae20001021            add      byte ptr [esi + 0x21100020], ch 
  0x00288A6A  2000                    and      byte ptr [eax], al             
  0x00288A6C  2a00                    sub      al, byte ptr [eax]             
  0x00288A6E  2000                    and      byte ptr [eax], al             
  0x00288A70  007056                  add      byte ptr [eax + 0x56], dh      
  0x00288A73  0031                    add      byte ptr [ecx], dh             
  0x00288A75  06                      push     es                             
  0x00288A76  0000                    add      byte ptr [eax], al             
  0x00288A78  13f4                    adc      esi, esp                       
  0x00288A7A  6200                    bound    eax, qword ptr [eax]           
  0x00288A7C  000500001b00            add      byte ptr [0x1b0000], al        
  0x00288A82  2000                    and      byte ptr [eax], al             
  0x00288A84  91                      xchg     ecx, eax                       
  0x00288A85  0006                    add      byte ptr [esi], al             
  0x00288A87  000500000000            add      byte ptr [0], al               
                                        ; XREF: 0x00288A35 (cond_jump)
  0x00288A8D  da44008a                fiadd    dword ptr [eax + eax - 0x76]   
  0x00288A91  0020                    add      byte ptr [eax], ah             
  0x00288A93  004700                  add      byte ptr [edi], al             
  0x00288A96  2000                    and      byte ptr [eax], al             
  0x00288A98  40                      inc      eax                            
  0x00288A99  90                      nop                                     
  0x00288A9A  0200                    add      al, byte ptr [eax]             
  0x00288A9C  260020                  add      byte ptr es:[eax], ah          
  0x00288A9F  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x00288AA5  7056                    jo       0x288afd                       
  0x00288AA7  0030                    add      byte ptr [eax], dh             
  0x00288AA9  06                      push     es                             
  0x00288AAA  0000                    add      byte ptr [eax], al             
  0x00288AAC  00a721000026            add      byte ptr [edi + 0x26000021], ah 
  0x00288AB2  2100                    and      dword ptr [eax], eax           
  0x00288AB4  13402f                  adc      eax, dword ptr [eax + 0x2f]    
  0x00288AB7  009017060009            add      byte ptr [eax + 0x9000617], dl 
  0x00288ABD  0000                    add      byte ptr [eax], al             
  0x00288ABF  0010                    add      byte ptr [eax], dl             
  0x00288AC1  c521                    lds      esp, ptr [ecx]                 
  0x00288AC3  0000                    add      byte ptr [eax], al             
  0x00288AC5  0000                    add      byte ptr [eax], al             
  0x00288AC7  0000                    add      byte ptr [eax], al             
  0x00288AC9  c421                    les      esp, ptr [ecx]                 
  0x00288ACB  00840020003000          add      byte ptr [eax + eax + 0x300020], al 
  0x00288AD2  2000                    and      byte ptr [eax], al             
  0x00288AD4  00ae20001021            add      byte ptr [esi + 0x21100020], ch 
  0x00288ADA  2000                    and      byte ptr [eax], al             
  0x00288ADC  2a00                    sub      al, byte ptr [eax]             
  0x00288ADE  2000                    and      byte ptr [eax], al             
  0x00288AE0  007056                  add      byte ptr [eax + 0x56], dh      
  0x00288AE3  0032                    add      byte ptr [edx], dh             
  0x00288AE5  06                      push     es                             
  0x00288AE6  0000                    add      byte ptr [eax], al             
  0x00288AE8  00f4                    add      ah, dh                         
  0x00288AEA  56                      push     esi                            
  0x00288AEB  0008                    add      byte ptr [eax], cl             
  0x00288AED  0000                    add      byte ptr [eax], al             
  0x00288AEF  0000                    add      byte ptr [eax], al             
  0x00288AF1  f4                      hlt                                     
  0x00288AF2  60                      pushal                                  
  0x00288AF3  0000                    add      byte ptr [eax], al             
  0x00288AF5  0400                    add      al, 0                          
  0x00288AF7  0000                    add      byte ptr [eax], al             
  0x00288AF9  f4                      hlt                                     
  0x00288AFA  7000                    jo       0x288afc                       
                                        ; XREF: 0x00288AFA (cond_jump)
  0x00288AFC  0001                    add      byte ptr [ecx], al             
  0x00288AFE  0000                    add      byte ptr [eax], al             
  0x00288B00  0000                    add      byte ptr [eax], al             
  0x00288B02  3900                    cmp      dword ptr [eax], eax           
  0x00288B04  80010d                  add      byte ptr [ecx], 0xd            
  0x00288B07  0000                    add      byte ptr [eax], al             
  0x00288B09  f4                      hlt                                     
  0x00288B0A  56                      push     esi                            
  0x00288B0B  0008                    add      byte ptr [eax], cl             
  0x00288B0D  0000                    add      byte ptr [eax], al             
  0x00288B0F  0000                    add      byte ptr [eax], al             
  0x00288B11  f4                      hlt                                     
  0x00288B12  60                      pushal                                  
  0x00288B13  0000                    add      byte ptr [eax], al             
  0x00288B15  05000000f4              add      eax, 0xf4000000                
  0x00288B1A  7000                    jo       0x288b1c                       
                                        ; XREF: 0x00288B1A (cond_jump)
  0x00288B1C  0001                    add      byte ptr [ecx], al             
  0x00288B1E  0000                    add      byte ptr [eax], al             
  0x00288B20  0001                    add      byte ptr [ecx], al             
  0x00288B22  3900                    cmp      dword ptr [eax], eax           
  0x00288B24  80010d                  add      byte ptr [ecx], 0xd            
  0x00288B27  0000                    add      byte ptr [eax], al             
  0x00288B29  f4                      hlt                                     
  0x00288B2A  56                      push     esi                            
  0x00288B2B  000f                    add      byte ptr [edi], cl             
  0x00288B2D  0000                    add      byte ptr [eax], al             
  0x00288B2F  0000                    add      byte ptr [eax], al             
  0x00288B31  f4                      hlt                                     
  0x00288B32  60                      pushal                                  
  0x00288B33  002f                    add      byte ptr [edi], ch             
  0x00288B35  06                      push     es                             
  0x00288B36  0000                    add      byte ptr [eax], al             
  0x00288B38  000438                  add      byte ptr [eax + edi], al       
  0x00288B3B  0000                    add      byte ptr [eax], al             
  0x00288B3D  0039                    add      byte ptr [ecx], bh             
  0x00288B3F  0080010d000c            add      byte ptr [eax + 0xc000d01], al 
  0x00288B45  0000                    add      byte ptr [eax], al             
  0x00288B47  0000                    add      byte ptr [eax], al             
  0x00288B49  f4                      hlt                                     
  0x00288B4A  60                      pushal                                  
  0x00288B4B  0000                    add      byte ptr [eax], al             
  0x00288B4D  0000                    add      byte ptr [eax], al             
  0x00288B4F  009280060005            add      byte ptr [edx + 0x5000680], dl 
  0x00288B55  0000                    add      byte ptr [eax], al             
  0x00288B57  0000                    add      byte ptr [eax], al             
  0x00288B59  d84400a1                fadd     dword ptr [eax + eax - 0x5f]   
  0x00288B5D  d04600                  rol      byte ptr [esi], 1              
  0x00288B60  e958560000              jmp      0x28e1bd                       
  0x00288B65  58                      pop      eax                            
  0x00288B66  57                      push     edi                            
  0x00288B67  000c00                  add      byte ptr [eax + eax], cl       
  0x00288B6A  0000                    add      byte ptr [eax], al             
  0x00288B6C  20f4                    and      ah, dh                         
  0x00288B6E  0500ffffff              add      eax, 0xffffff00                
  0x00288B73  00a0610400a0            add      byte ptr [eax - 0x5ffffb9f], ah 
  0x00288B79  620400                  bound    eax, qword ptr [eax + eax]     
  0x00288B7C  a0640400a0              mov      al, byte ptr [0xa0000464]      
  0x00288B81  650400                  add      al, 0                          
  0x00288B84  a0660400b8              mov      al, byte ptr [0xb8000466]      
  0x00288B89  f30000                  add      byte ptr [eax], al             
  0x00288B8C  00f4                    add      ah, dh                         
  0x00288B8E  44                      inc      esp                            
  0x00288B8F  0016                    add      byte ptr [esi], dl             
  0x00288B91  0000                    add      byte ptr [eax], al             
  0x00288B93  004d00                  add      byte ptr [ebp], cl             
  0x00288B96  2000                    and      byte ptr [eax], al             
  0x00288B98  4a                      dec      edx                            
  0x00288B99  100d00080000            adc      byte ptr [0x800], cl           
  0x00288B9F  0000                    add      byte ptr [eax], al             
  0x00288BA1  0030                    add      byte ptr [eax], dh             
  0x00288BA3  0000                    add      byte ptr [eax], al             
  0x00288BA5  f4                      hlt                                     
  0x00288BA6  56                      push     esi                            
  0x00288BA7  0000                    add      byte ptr [eax], al             
  0x00288BA9  0000                    add      byte ptr [eax], al             
  0x00288BAB  0000                    add      byte ptr [eax], al             
  0x00288BAD  f4                      hlt                                     
  0x00288BAE  57                      push     edi                            
  0x00288BAF  00ff                    add      bh, bh                         
  0x00288BB2  ff00                    inc      dword ptr [eax]                
  0x00288BB4  0c00                    or       al, 0                          
  0x00288BB6  0000                    add      byte ptr [eax], al             
  0x00288BB8  80100d                  adc      byte ptr [eax], 0xd            
  0x00288BBB  00b800000000            add      byte ptr [eax], bh             
  0x00288BC2  56                      push     esi                            
  0x00288BC3  0036                    add      byte ptr [esi], dh             
  0x00288BC5  06                      push     es                             
  0x00288BC6  0000                    add      byte ptr [eax], al             
  0x00288BC8  0300                    add      eax, dword ptr [eax]           
  0x00288BCA  2000                    and      byte ptr [eax], al             
  0x00288BCC  06                      push     es                             
  0x00288BCD  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00288BCE  050080100d              add      eax, 0xd108000                 
  0x00288BD3  005001                  add      byte ptr [eax + 1], dl         
  0x00288BD6  0000                    add      byte ptr [eax], al             
  0x00288BD8  80100d                  adc      byte ptr [eax], 0xd            
  0x00288BDB  002f                    add      byte ptr [edi], ch             
  0x00288BDD  0100                    add      dword ptr [eax], eax           
  0x00288BDF  0003                    add      byte ptr [ebx], al             
  0x00288BE1  0c05                    or       al, 5                          
  0x00288BE3  0080100d0053            add      byte ptr [eax + 0x53000d10], al 
  0x00288BE9  0100                    add      dword ptr [eax], eax           
  0x00288BEB  0080100d0030            add      byte ptr [eax + 0x30000d10], al 
  0x00288BF1  0100                    add      dword ptr [eax], eax           
  0x00288BF3  0000                    add      byte ptr [eax], al             
  0x00288BF6  56                      push     esi                            
  0x00288BF7  0037                    add      byte ptr [edi], dh             
  0x00288BF9  06                      push     es                             
  0x00288BFA  0000                    add      byte ptr [eax], al             
  0x00288BFC  854001                  test     dword ptr [eax + 1], eax       
  0x00288BFF  0017                    add      byte ptr [edi], dl             
  0x00288C01  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00288C02  050000f066              add      eax, 0x66f00000                
  0x00288C07  0033                    add      byte ptr [ebx], dh             
  0x00288C09  06                      push     es                             
  0x00288C0A  0000                    add      byte ptr [eax], al             
  0x00288C0C  0003                    add      byte ptr [ebx], al             
  0x00288C0E  3e0000                  add      byte ptr ds:[eax], al          
  0x00288C11  ee                      out      dx, al                         
  0x00288C12  60                      pushal                                  
  0x00288C13  0000                    add      byte ptr [eax], al             
  0x00288C15  043e                    add      al, 0x3e                       
  0x00288C17  0000                    add      byte ptr [eax], al             
  0x00288C19  ee                      out      dx, al                         
  0x00288C1A  61                      popal                                   
  0x00288C1B  0000                    add      byte ptr [eax], al             
  0x00288C1D  f066003406              lock add byte ptr [esi + eax], dh       
  0x00288C22  0000                    add      byte ptr [eax], al             
  0x00288C24  0003                    add      byte ptr [ebx], al             
  0x00288C26  3e0000                  add      byte ptr ds:[eax], al          
  0x00288C29  ee                      out      dx, al                         
  0x00288C2A  7000                    jo       0x288c2c                       
                                        ; XREF: 0x00288C2A (cond_jump)
  0x00288C2C  00043e                  add      byte ptr [esi + edi], al       
  0x00288C2F  0000                    add      byte ptr [eax], al             
  0x00288C31  ee                      out      dx, al                         
  0x00288C32  7100                    jno      0x288c34                       
                                        ; XREF: 0x00288C32 (cond_jump)
  0x00288C34  00f4                    add      ah, dh                         
  0x00288C36  46                      inc      esi                            
  0x00288C37  007a82                  add      byte ptr [edx - 0x7e], bh      
  0x00288C3A  5a                      pop      edx                            
  0x00288C3B  0000                    add      byte ptr [eax], al             
  0x00288C3E  6200                    bound    eax, qword ptr [eax]           
  0x00288C40  3c06                    cmp      al, 6                          
  0x00288C42  0000                    add      byte ptr [eax], al             
  0x00288C44  10d2                    adc      dl, dl                         
  0x00288C46  06                      push     es                             
  0x00288C47  000500000000            add      byte ptr [0], al               
  0x00288C4D  e044                    loopne   0x288c93                       
  0x00288C4F  00d0                    add      al, dl                         
  0x00288C51  c9                      leave                                   
  0x00288C52  44                      inc      esp                            
  0x00288C53  00d3                    add      bl, dl                         
  0x00288C55  0020                    add      byte ptr [eax], ah             
  0x00288C57  0000                    add      byte ptr [eax], al             
  0x00288C59  48                      dec      eax                            
  0x00288C5A  56                      push     esi                            
  0x00288C5B  0000                    add      byte ptr [eax], al             
  0x00288C5D  f0660033                lock add byte ptr [ebx], dh             
  0x00288C61  06                      push     es                             
  0x00288C62  0000                    add      byte ptr [eax], al             
  0x00288C64  0000                    add      byte ptr [eax], al             
  0x00288C66  3e0000                  add      byte ptr ds:[eax], al          
  0x00288C69  ee                      out      dx, al                         
  0x00288C6A  60                      pushal                                  
  0x00288C6B  0000                    add      byte ptr [eax], al             
  0x00288C6D  023e                    add      bh, byte ptr [esi]             
  0x00288C6F  0000                    add      byte ptr [eax], al             
  0x00288C71  ee                      out      dx, al                         
  0x00288C72  61                      popal                                   
  0x00288C73  0000                    add      byte ptr [eax], al             
  0x00288C75  013e                    add      dword ptr [esi], edi           
  0x00288C77  0000                    add      byte ptr [eax], al             
  0x00288C79  ee                      out      dx, al                         
  0x00288C7A  6200                    bound    eax, qword ptr [eax]           
  0x00288C7C  00f0                    add      al, dh                         
  0x00288C7E  660038                  add      byte ptr [eax], bh             
  0x00288C81  06                      push     es                             
  0x00288C82  0000                    add      byte ptr [eax], al             
  0x00288C84  0000                    add      byte ptr [eax], al             
  0x00288C86  3e0000                  add      byte ptr ds:[eax], al          
  0x00288C89  ee                      out      dx, al                         
  0x00288C8A  640000                  add      byte ptr fs:[eax], al          
  0x00288C8D  023e                    add      bh, byte ptr [esi]             
  0x00288C8F  0000                    add      byte ptr [eax], al             
  0x00288C91  ee                      out      dx, al                         
  0x00288C92  650000                  add      byte ptr gs:[eax], al          
  0x00288C95  f066003406              lock add byte ptr [esi + eax], dh       
  0x00288C9A  0000                    add      byte ptr [eax], al             
  0x00288C9C  0000                    add      byte ptr [eax], al             
  0x00288C9E  3e0000                  add      byte ptr ds:[eax], al          
  0x00288CA1  ee                      out      dx, al                         
  0x00288CA2  7000                    jo       0x288ca4                       
                                        ; XREF: 0x00288CA2 (cond_jump)
  0x00288CA4  0002                    add      byte ptr [edx], al             
  0x00288CA6  3e0000                  add      byte ptr ds:[eax], al          
  0x00288CA9  ee                      out      dx, al                         
  0x00288CAA  7100                    jno      0x288cac                       
                                        ; XREF: 0x00288CAA (cond_jump)
  0x00288CAC  0001                    add      byte ptr [ecx], al             
  0x00288CAE  3e0000                  add      byte ptr ds:[eax], al          
  0x00288CB1  ee                      out      dx, al                         
  0x00288CB2  7200                    jb       0x288cb4                       
                                        ; XREF: 0x00288CB2 (cond_jump)
  0x00288CB4  00f0                    add      al, dh                         
  0x00288CB6  660039                  add      byte ptr [ecx], bh             
  0x00288CB9  06                      push     es                             
  0x00288CBA  0000                    add      byte ptr [eax], al             
  0x00288CBC  0000                    add      byte ptr [eax], al             
  0x00288CBE  3e0000                  add      byte ptr ds:[eax], al          
  0x00288CC1  ee                      out      dx, al                         
  0x00288CC2  7400                    je       0x288cc4                       
                                        ; XREF: 0x00288CC2 (cond_jump)
  0x00288CC4  00f4                    add      ah, dh                         
  0x00288CC6  7600                    jbe      0x288cc8                       
                                        ; XREF: 0x00288CC6 (cond_jump)
  0x00288CC8  0200                    add      al, byte ptr [eax]             
  0x00288CCA  0000                    add      byte ptr [eax], al             
  0x00288CCC  00ee                    add      dh, ch                         
  0x00288CCE  7500                    jne      0x288cd0                       
                                        ; XREF: 0x00288CCE (cond_jump)
  0x00288CD0  00f4                    add      ah, dh                         
  0x00288CD2  45                      inc      ebp                            
  0x00288CD3  007a82                  add      byte ptr [edx - 0x7e], bh      
  0x00288CD6  5a                      pop      edx                            
  0x00288CD7  0000                    add      byte ptr [eax], al             
  0x00288CD9  f066003c06              lock add byte ptr [esi + eax], bh       
  0x00288CDE  0000                    add      byte ptr [eax], al             
  0x00288CE0  00d6                    add      dh, dl                         
  0x00288CE2  06                      push     es                             
  0x00288CE3  00a604000000            add      byte ptr [esi + 4], ah         
  0x00288CE9  ca4400                  retf     0x44                           
  0x00288CEC  00c8                    add      al, cl                         
  0x00288CEE  56                      push     esi                            
  0x00288CEF  00a3c95700ab            add      byte ptr [ebx - 0x54ffa837], ah 
  0x00288CF5  4c                      dec      esp                            
  0x00288CF6  56                      push     esi                            
  0x00288CF7  0000                    add      byte ptr [eax], al             
  0x00288CF9  4d                      dec      ebp                            
  0x00288CFA  57                      push     edi                            
  0x00288CFB  0000                    add      byte ptr [eax], al             
  0x00288CFD  f4                      hlt                                     
  0x00288CFE  61                      popal                                   
  0x00288CFF  003d06000000            add      byte ptr [6], bh               
  0x00288D05  f065008b06000000        lock add byte ptr gs:[ebx + 6], cl      
  0x00288D0D  f4                      hlt                                     
  0x00288D0E  6200                    bound    eax, qword ptr [eax]           
  0x00288D10  7106                    jno      0x288d18                       
  0x00288D12  0000                    add      byte ptr [eax], al             
  0x00288D14  00f0                    add      al, dh                         
  0x00288D16  660038                  add      byte ptr [eax], bh             
  0x00288D19  06                      push     es                             
  0x00288D1A  0000                    add      byte ptr [eax], al             
  0x00288D1C  0000                    add      byte ptr [eax], al             
  0x00288D1E  3e0000                  add      byte ptr ds:[eax], al          
  0x00288D21  ee                      out      dx, al                         
  0x00288D22  60                      pushal                                  
  0x00288D23  0000                    add      byte ptr [eax], al             
  0x00288D25  1422                    adc      al, 0x22                       
  0x00288D27  0000                    add      byte ptr [eax], al             
  0x00288D29  f0660039                lock add byte ptr [ecx], bh             
  0x00288D2D  06                      push     es                             
  0x00288D2E  0000                    add      byte ptr [eax], al             
  0x00288D30  00ee                    add      dh, ch                         
  0x00288D32  7000                    jo       0x288d34                       
                                        ; XREF: 0x00288D32 (cond_jump)
  0x00288D34  001c23                  add      byte ptr [ebx], bl             
  0x00288D37  0000                    add      byte ptr [eax], al             
  0x00288D3A  50                      push     eax                            
  0x00288D3B  003c06                  add      byte ptr [esi + eax], bh       
  0x00288D3E  0000                    add      byte ptr [eax], al             
  0x00288D40  0a00                    or       al, byte ptr [eax]             
  0x00288D42  0000                    add      byte ptr [eax], al             
  0x00288D44  001e                    add      byte ptr [esi], bl             
  0x00288D46  2100                    and      dword ptr [eax], eax           
  0x00288D48  00f4                    add      ah, dh                         
  0x00288D4A  7200                    jb       0x288d4c                       
                                        ; XREF: 0x00288D4A (cond_jump)
  0x00288D4C  0400                    add      al, 0                          
  0x00288D4E  0000                    add      byte ptr [eax], al             
  0x00288D50  80f00b                  xor      al, 0xb                        
  0x00288D53  00ca                    add      dl, cl                         
  0x00288D55  05000000f4              add      eax, 0xf4000000                
  0x00288D5A  61                      popal                                   
  0x00288D5B  004d06                  add      byte ptr [ebp + 6], cl         
  0x00288D5E  0000                    add      byte ptr [eax], al             
  0x00288D60  00f0                    add      al, dh                         
  0x00288D62  65008b06000000          add      byte ptr gs:[ebx + 6], cl      
  0x00288D69  f4                      hlt                                     
  0x00288D6A  6200                    bound    eax, qword ptr [eax]           
  0x00288D6C  7906                    jns      0x288d74                       
  0x00288D6E  0000                    add      byte ptr [eax], al             
  0x00288D70  00f0                    add      al, dh                         
  0x00288D72  660038                  add      byte ptr [eax], bh             
  0x00288D75  06                      push     es                             
  0x00288D76  0000                    add      byte ptr [eax], al             
  0x00288D78  0002                    add      byte ptr [edx], al             
  0x00288D7A  3e0000                  add      byte ptr ds:[eax], al          
  0x00288D7D  ee                      out      dx, al                         
  0x00288D7E  60                      pushal                                  
  0x00288D7F  0000                    add      byte ptr [eax], al             
  0x00288D81  1422                    adc      al, 0x22                       
  0x00288D83  0000                    add      byte ptr [eax], al             
  0x00288D85  f0660039                lock add byte ptr [ecx], bh             
  0x00288D89  06                      push     es                             
  0x00288D8A  0000                    add      byte ptr [eax], al             
  0x00288D8C  00ee                    add      dh, ch                         
  0x00288D8E  7000                    jo       0x288d90                       
                                        ; XREF: 0x00288D8E (cond_jump)
  0x00288D90  001c23                  add      byte ptr [ebx], bl             
  0x00288D93  0000                    add      byte ptr [eax], al             
  0x00288D96  50                      push     eax                            
  0x00288D97  003c06                  add      byte ptr [esi + eax], bh       
  0x00288D9A  0000                    add      byte ptr [eax], al             
  0x00288D9C  0a00                    or       al, byte ptr [eax]             
  0x00288D9E  0000                    add      byte ptr [eax], al             
  0x00288DA0  001e                    add      byte ptr [esi], bl             
  0x00288DA2  2100                    and      dword ptr [eax], eax           
  0x00288DA4  00f4                    add      ah, dh                         
  0x00288DA6  7200                    jb       0x288da8                       
                                        ; XREF: 0x00288DA6 (cond_jump)
  0x00288DA8  0400                    add      al, 0                          
  0x00288DAA  0000                    add      byte ptr [eax], al             
  0x00288DAC  80f00b                  xor      al, 0xb                        
  0x00288DAF  00ca                    add      dl, cl                         
  0x00288DB1  05000000f4              add      eax, 0xf4000000                
  0x00288DB6  61                      popal                                   
  0x00288DB7  005d06                  add      byte ptr [ebp + 6], bl         
  0x00288DBA  0000                    add      byte ptr [eax], al             
  0x00288DBC  00f0                    add      al, dh                         
  0x00288DBE  65008c06000000f4        add      byte ptr gs:[esi + eax - 0xc000000], cl 
  0x00288DC6  6200                    bound    eax, qword ptr [eax]           
  0x00288DC8  8106000000f0            add      dword ptr [esi], 0xf0000000    
  0x00288DCE  660033                  add      byte ptr [ebx], dh             
  0x00288DD1  06                      push     es                             
  0x00288DD2  0000                    add      byte ptr [eax], al             
  0x00288DD4  0003                    add      byte ptr [ebx], al             
  0x00288DD6  3e0000                  add      byte ptr ds:[eax], al          
  0x00288DD9  ee                      out      dx, al                         
  0x00288DDA  60                      pushal                                  
  0x00288DDB  0000                    add      byte ptr [eax], al             
  0x00288DDD  1422                    adc      al, 0x22                       
  0x00288DDF  0000                    add      byte ptr [eax], al             
  0x00288DE1  f066003406              lock add byte ptr [esi + eax], dh       
  0x00288DE6  0000                    add      byte ptr [eax], al             
  0x00288DE8  00ee                    add      dh, ch                         
  0x00288DEA  7000                    jo       0x288dec                       
                                        ; XREF: 0x00288DEA (cond_jump)
  0x00288DEC  001c23                  add      byte ptr [ebx], bl             
  0x00288DEF  0000                    add      byte ptr [eax], al             
  0x00288DF2  50                      push     eax                            
  0x00288DF3  003c06                  add      byte ptr [esi + eax], bh       
  0x00288DF6  0000                    add      byte ptr [eax], al             
  0x00288DF8  0a00                    or       al, byte ptr [eax]             
  0x00288DFA  0000                    add      byte ptr [eax], al             
  0x00288DFC  001e                    add      byte ptr [esi], bl             
  0x00288DFE  2100                    and      dword ptr [eax], eax           
  0x00288E00  00f4                    add      ah, dh                         
  0x00288E02  7200                    jb       0x288e04                       
                                        ; XREF: 0x00288E02 (cond_jump)
  0x00288E04  0500000080              add      eax, 0x80000000                
  0x00288E09  f00b00                  lock or  eax, dword ptr [eax]           
  0x00288E0C  ca0500                  retf     5                              
  0x00288E0F  0000                    add      byte ptr [eax], al             
  0x00288E11  f0660038                lock add byte ptr [eax], bh             
  0x00288E15  06                      push     es                             
  0x00288E16  0000                    add      byte ptr [eax], al             
  0x00288E18  0000                    add      byte ptr [eax], al             
  0x00288E1A  3e0000                  add      byte ptr ds:[eax], al          
  0x00288E1D  ee                      out      dx, al                         
  0x00288E1E  60                      pushal                                  
  0x00288E1F  0000                    add      byte ptr [eax], al             
  0x00288E21  023e                    add      bh, byte ptr [esi]             
  0x00288E23  0000                    add      byte ptr [eax], al             
  0x00288E25  ee                      out      dx, al                         
  0x00288E26  61                      popal                                   
  0x00288E27  0000                    add      byte ptr [eax], al             
  0x00288E29  f0660033                lock add byte ptr [ebx], dh             
  0x00288E2D  06                      push     es                             
  0x00288E2E  0000                    add      byte ptr [eax], al             
  0x00288E30  0003                    add      byte ptr [ebx], al             
  0x00288E32  3e0000                  add      byte ptr ds:[eax], al          
  0x00288E35  ee                      out      dx, al                         
  0x00288E36  6200                    bound    eax, qword ptr [eax]           
  0x00288E38  00f0                    add      al, dh                         
  0x00288E3A  660039                  add      byte ptr [ecx], bh             
  0x00288E3D  06                      push     es                             
  0x00288E3E  0000                    add      byte ptr [eax], al             
  0x00288E40  0000                    add      byte ptr [eax], al             
  0x00288E42  3e0000                  add      byte ptr ds:[eax], al          
  0x00288E45  ee                      out      dx, al                         
  0x00288E46  7000                    jo       0x288e48                       
                                        ; XREF: 0x00288E46 (cond_jump)
  0x00288E48  0002                    add      byte ptr [edx], al             
  0x00288E4A  3e0000                  add      byte ptr ds:[eax], al          
  0x00288E4D  ee                      out      dx, al                         
  0x00288E4E  7100                    jno      0x288e50                       
                                        ; XREF: 0x00288E4E (cond_jump)
  0x00288E50  00f0                    add      al, dh                         
  0x00288E52  66003406                add      byte ptr [esi + eax], dh       
  0x00288E56  0000                    add      byte ptr [eax], al             
  0x00288E58  0003                    add      byte ptr [ebx], al             
  0x00288E5A  3e0000                  add      byte ptr ds:[eax], al          
  0x00288E5D  ee                      out      dx, al                         
  0x00288E5E  7200                    jb       0x288e60                       
                                        ; XREF: 0x00288E5E (cond_jump)
  0x00288E60  00f4                    add      ah, dh                         
  0x00288E62  45                      inc      ebp                            
  0x00288E63  007a82                  add      byte ptr [edx - 0x7e], bh      
  0x00288E66  5a                      pop      edx                            
  0x00288E67  0000                    add      byte ptr [eax], al             
  0x00288E69  f064003c06              lock add byte ptr fs:[esi + eax], bh    
  0x00288E6E  0000                    add      byte ptr [eax], al             
  0x00288E70  00d4                    add      ah, dl                         
  0x00288E72  06                      push     es                             
  0x00288E73  000a                    add      byte ptr [edx], cl             
  0x00288E75  05000000ca              add      eax, 0xca000000                
  0x00288E7A  44                      inc      esp                            
  0x00288E7B  0000                    add      byte ptr [eax], al             
  0x00288E7D  e056                    loopne   0x288ed5                       
  0x00288E7F  00a3e15700af            add      byte ptr [ebx - 0x50ffa81f], ah 
  0x00288E85  48                      dec      eax                            
  0x00288E86  56                      push     esi                            
  0x00288E87  0000                    add      byte ptr [eax], al             
  0x00288E89  49                      dec      ecx                            
  0x00288E8A  57                      push     edi                            
  0x00288E8B  0080100d00b4            add      byte ptr [eax - 0x4bfff2f0], al 
  0x00288E91  0000                    add      byte ptr [eax], al             
  0x00288E93  000c00                  add      byte ptr [eax + eax], cl       
  0x00288E96  0000                    add      byte ptr [eax], al             
  0x00288E98  005820                  add      byte ptr [eax + 0x20], bl      
  0x00288E9B  0000                    add      byte ptr [eax], al             
  0x00288E9D  d8440000                fadd     dword ptr [eax + eax]          
  0x00288EA1  7044                    jo       0x288ee7                       
  0x00288EA3  0033                    add      byte ptr [ebx], dh             
  0x00288EA5  06                      push     es                             
  0x00288EA6  0000                    add      byte ptr [eax], al             
  0x00288EA8  00d8                    add      al, bl                         
  0x00288EAA  44                      inc      esp                            
  0x00288EAB  0000                    add      byte ptr [eax], al             
  0x00288EAD  7044                    jo       0x288ef3                       
  0x00288EAF  003406                  add      byte ptr [esi + eax], dh       
  0x00288EB2  0000                    add      byte ptr [eax], al             
  0x00288EB4  00d8                    add      al, bl                         
  0x00288EB6  44                      inc      esp                            
  0x00288EB7  0000                    add      byte ptr [eax], al             
  0x00288EB9  7044                    jo       0x288eff                       
  0x00288EBB  003506000000            add      byte ptr [6], dh               
  0x00288EC1  d85700                  fcom     dword ptr [edi]                
  0x00288EC4  90                      nop                                     
  0x00288EC5  180c00                  sbb      byte ptr [eax + eax], cl       
  0x00288EC8  27                      daa                                     
  0x00288EC9  1000                    adc      byte ptr [eax], al             
  0x00288ECB  0000                    add      byte ptr [eax], al             
  0x00288ECD  7050                    jo       0x288f1f                       
  0x00288ECF  0036                    add      byte ptr [esi], dh             
  0x00288ED1  06                      push     es                             
  0x00288ED2  0000                    add      byte ptr [eax], al             
  0x00288ED4  90                      nop                                     
                                        ; XREF: 0x00288E7D (cond_jump)
  0x00288ED5  180c00                  sbb      byte ptr [eax + eax], cl       
  0x00288ED8  1910                    sbb      dword ptr [eax], edx           
  0x00288EDA  0000                    add      byte ptr [eax], al             
  0x00288EDC  007050                  add      byte ptr [eax + 0x50], dh      
  0x00288EDF  0037                    add      byte ptr [edi], dh             
  0x00288EE1  06                      push     es                             
  0x00288EE2  0000                    add      byte ptr [eax], al             
  0x00288EE4  00d8                    add      al, bl                         
  0x00288EE6  44                      inc      esp                            
                                        ; XREF: 0x00288EA1 (cond_jump)
  0x00288EE7  0000                    add      byte ptr [eax], al             
  0x00288EE9  7044                    jo       0x288f2f                       
  0x00288EEB  0038                    add      byte ptr [eax], bh             
  0x00288EED  06                      push     es                             
  0x00288EEE  0000                    add      byte ptr [eax], al             
  0x00288EF0  00d8                    add      al, bl                         
  0x00288EF2  44                      inc      esp                            
                                        ; XREF: 0x00288EAD (cond_jump)
  0x00288EF3  0000                    add      byte ptr [eax], al             
  0x00288EF5  7044                    jo       0x288f3b                       
  0x00288EF7  0039                    add      byte ptr [ecx], bh             
  0x00288EF9  06                      push     es                             
  0x00288EFA  0000                    add      byte ptr [eax], al             
  0x00288EFC  00d8                    add      al, bl                         
  0x00288EFE  44                      inc      esp                            
                                        ; XREF: 0x00288EB9 (cond_jump)
  0x00288EFF  0000                    add      byte ptr [eax], al             
  0x00288F01  7044                    jo       0x288f47                       
  0x00288F03  003a                    add      byte ptr [edx], bh             
  0x00288F05  06                      push     es                             
  0x00288F06  0000                    add      byte ptr [eax], al             
  0x00288F08  00d8                    add      al, bl                         
  0x00288F0A  57                      push     edi                            
  0x00288F0B  0090180c0024            add      byte ptr [eax + 0x24000c18], dl 
  0x00288F11  2000                    and      byte ptr [eax], al             
  0x00288F13  0000                    add      byte ptr [eax], al             
  0x00288F15  7050                    jo       0x288f67                       
  0x00288F17  003b                    add      byte ptr [ebx], bh             
  0x00288F19  06                      push     es                             
  0x00288F1A  0000                    add      byte ptr [eax], al             
  0x00288F1C  00d8                    add      al, bl                         
  0x00288F1E  44                      inc      esp                            
                                        ; XREF: 0x00288ECD (cond_jump)
  0x00288F1F  0000                    add      byte ptr [eax], al             
  0x00288F21  7044                    jo       0x288f67                       
  0x00288F23  003c06                  add      byte ptr [esi + eax], bh       
  0x00288F26  0000                    add      byte ptr [eax], al             
  0x00288F28  0c00                    or       al, 0                          
  0x00288F2A  0000                    add      byte ptr [eax], al             
  0x00288F2C  8d95c0000000            lea      edx, [ebp + 0xc0]              
  0x00288F32  0000                    add      byte ptr [eax], al             
  0x00288F34  e5d4                    in       eax, 0xd4                      
  0x00288F36  7e00                    jle      0x288f38                       
                                        ; XREF: 0x00288F36 (cond_jump)
  0x00288F38  0000                    add      byte ptr [eax], al             
  0x00288F3A  c00000                  rol      byte ptr [eax], 0              
  0x00288F3D  0000                    add      byte ptr [eax], al             
  0x00288F3F  004ae2                  add      byte ptr [edx - 0x1e], cl      
  0x00288F42  4f                      dec      edi                            
  0x00288F43  00cc                    add      ah, cl                         
  0x00288F45  673f                    aas                                     
                                        ; XREF: 0x00288F01 (cond_jump)
  0x00288F47  00cc                    add      ah, cl                         
  0x00288F49  673f                    aas                                     
  0x00288F4B  004ae2                  add      byte ptr [edx - 0x1e], cl      
  0x00288F4E  4f                      dec      edi                            
  0x00288F4F  00ff                    add      bh, bh                         
  0x00288F52  7f00                    jg       0x288f54                       
                                        ; XREF: 0x00288F52 (cond_jump)
  0x00288F54  e85b850038              call     0x382914b4                     
  0x00288F59  667500                  jne      0x288f5c                       
                                        ; XREF: 0x00288F59 (cond_jump)
  0x00288F5C  386675                  cmp      byte ptr [esi + 0x75], ah      
  0x00288F5F  00e8                    add      al, ch                         
  0x00288F61  5b                      pop      ebx                            
  0x00288F62  8500                    test     dword ptr [eax], eax           
  0x00288F66  7f00                    jg       0x288f68                       
                                        ; XREF: 0x00288F66 (cond_jump)
  0x00288F68  92                      xchg     edx, eax                       
  0x00288F69  1f                      pop      ds                             
  0x00288F6A  ea004b40e2004b          ljmp     0x4b00:0xe2404b00              
  0x00288F71  40                      inc      eax                            
  0x00288F72  e200                    loop     0x288f74                       
                                        ; XREF: 0x00288F72 (cond_jump)
  0x00288F74  92                      xchg     edx, eax                       
  0x00288F75  1f                      pop      ds                             
  0x00288F76  ea00ffff7f001b          ljmp     0x1b00:0x7fffff00              
  0x00288F7D  2b810085ac7d            sub      eax, dword ptr [ecx + 0x7dac8500] 
  0x00288F83  0094d57e006c2a          add      byte ptr [ebp + edx*8 + 0x2a6c007e], dl 
  0x00288F8A  810094d57e00            add      dword ptr [eax], 0x7ed594      
  0x00288F90  4a                      dec      edx                            
  0x00288F91  e24f                    loop     0x288fe2                       
  0x00288F93  00cc                    add      ah, cl                         
  0x00288F95  673f                    aas                                     
  0x00288F97  0026                    add      byte ptr [esi], ah             
  0x00288F99  94                      xchg     esp, eax                       
  0x00288F9A  57                      push     edi                            
  0x00288F9B  007fff                  add      byte ptr [edi - 1], bh         
  0x00288F9E  55                      push     ebp                            
  0x00288F9F  0026                    add      byte ptr [esi], ah             
  0x00288FA1  94                      xchg     esp, eax                       
  0x00288FA2  57                      push     edi                            
  0x00288FA3  004ae2                  add      byte ptr [edx - 0x1e], cl      
  0x00288FA6  4f                      dec      edi                            
  0x00288FA7  00cc                    add      ah, cl                         
  0x00288FA9  673f                    aas                                     
  0x00288FAB  0026                    add      byte ptr [esi], ah             
  0x00288FAD  94                      xchg     esp, eax                       
  0x00288FAE  57                      push     edi                            
  0x00288FAF  007fff                  add      byte ptr [edi - 1], bh         
  0x00288FB2  55                      push     ebp                            
  0x00288FB3  0026                    add      byte ptr [esi], ah             
  0x00288FB5  94                      xchg     esp, eax                       
  0x00288FB6  57                      push     edi                            
  0x00288FB7  0022                    add      byte ptr [edx], ah             
  0x00288FB9  3e82006d                add      byte ptr ds:[eax], 0x6d        
  0x00288FBD  877b00                  xchg     dword ptr [ebx], edi           
  0x00288FC0  6d                      insd     dword ptr es:[edi], dx         
  0x00288FC1  877b00                  xchg     dword ptr [ebx], edi           
  0x00288FC4  223e                    and      bh, byte ptr [esi]             
  0x00288FC6  8200ff                  add      byte ptr [eax], 0xff           
  0x00288FCA  7f00                    jg       0x288fcc                       
                                        ; XREF: 0x00288FCA (cond_jump)
  0x00288FCC  5e                      pop      esi                            
  0x00288FCD  3bb2004ff727            cmp      esi, dword ptr [edx + 0x27f74f00] 
  0x00288FD3  004ff7                  add      byte ptr [edi - 9], cl         
  0x00288FD6  27                      daa                                     
  0x00288FD7  005e3b                  add      byte ptr [esi + 0x3b], bl      
  0x00288FDA  b200                    mov      dl, 0                          
  0x00288FDE  7f00                    jg       0x288fe0                       
                                        ; XREF: 0x00288FDE (cond_jump)
  0x00288FE0  7489                    je       0x288f6b                       
                                        ; XREF: 0x00288F91 (cond_jump)
  0x00288FE2  c00000                  rol      byte ptr [eax], 0              
  0x00288FE5  0000                    add      byte ptr [eax], al             
  0x00288FE7  0019                    add      byte ptr [ecx], bl             
  0x00288FE9  ed                      in       eax, dx                        
  0x00288FEA  7e00                    jle      0x288fec                       
                                        ; XREF: 0x00288FEA (cond_jump)
  0x00288FEC  0000                    add      byte ptr [eax], al             
  0x00288FEE  c00000                  rol      byte ptr [eax], 0              
  0x00288FF1  0000                    add      byte ptr [eax], al             
  0x00288FF3  00f8                    add      al, bh                         
  0x00288FF5  2a4600                  sub      al, byte ptr [esi]             
  0x00288FF8  208637002086            and      byte ptr [esi - 0x79dfffc9], al 
  0x00288FFE  37                      aaa                                     
  0x00288FFF  00f8                    add      al, bh                         
  0x00289001  2a4600                  sub      al, byte ptr [esi]             
  0x00289006  7f00                    jg       0x289008                       
                                        ; XREF: 0x00289006 (cond_jump)
  0x00289008  9e                      sahf                                    
  0x00289009  ef                      out      dx, eax                        
  0x0028900A  8400                    test     byte ptr [eax], al             
  0x0028900C  353a760035              xor      eax, 0x3500763a                
  0x00289011  3a7600                  cmp      dh, byte ptr [esi]             
  0x00289014  9e                      sahf                                    
  0x00289015  ef                      out      dx, eax                        
  0x00289016  8400                    test     byte ptr [eax], al             
  0x0028901A  7f00                    jg       0x28901c                       
                                        ; XREF: 0x0028901A (cond_jump)
  0x0028901C  fe48e6                  dec      byte ptr [eax - 0x1a]          
  0x0028901F  008ab7e4008a            add      byte ptr [edx - 0x75ff1b49], cl 
  0x00289025  b7e4                    mov      bh, 0xe4                       
  0x00289027  00fe                    add      dh, bh                         
  0x00289029  48                      dec      eax                            
  0x0028902A  e600                    out      0, al                          
  0x0028902E  7f00                    jg       0x289030                       
                                        ; XREF: 0x0028902E (cond_jump)
  0x00289030  e712                    out      0x12, eax                      
  0x00289032  81007fdc7d00            add      dword ptr [eax], 0x7ddc7f      
  0x00289038  ac                      lodsb    al, byte ptr [esi]             
  0x00289039  ed                      in       eax, dx                        
  0x0028903A  7e00                    jle      0x28903c                       
                                        ; XREF: 0x0028903A (cond_jump)
  0x0028903C  54                      push     esp                            
  0x0028903D  128100aced7e            adc      al, byte ptr [ecx + 0x7eedac00] 
  0x00289043  00f8                    add      al, bh                         
  0x00289045  2a4600                  sub      al, byte ptr [esi]             
  0x00289048  20863700f31d            and      byte ptr [esi + 0x1df30037], al 
  0x0028904E  51                      push     ecx                            
  0x0028904F  0090f54e00f3            add      byte ptr [eax - 0xcffb10b], dl 
  0x00289055  1d5100f82a              sbb      eax, 0x2af80051                
  0x0028905A  46                      inc      esi                            
  0x0028905B  0020                    add      byte ptr [eax], ah             
  0x0028905D  8637                    xchg     byte ptr [edi], dh             
  0x0028905F  00f3                    add      bl, dh                         
  0x00289061  1d510090f5              sbb      eax, 0xf5900051                
  0x00289066  4e                      dec      esi                            
  0x00289067  00f3                    add      bl, dh                         
  0x00289069  1d51001a10              sbb      eax, 0x101a0051                
  0x0028906E  8200ed                  add      byte ptr [eax], 0xed           
  0x00289071  e27b                    loop     0x2890ee                       
  0x00289073  00ed                    add      ch, ch                         
  0x00289075  e27b                    loop     0x2890f2                       
  0x00289077  001a                    add      byte ptr [edx], bl             
  0x00289079  108200ffff7f            adc      byte ptr [edx + 0x7fffff00], al 
  0x0028907F  00fc                    add      ah, bh                         
  0x00289081  2eaf                    scasd    eax, dword ptr es:[edi]        
  0x00289083  0000                    add      byte ptr [eax], al             
  0x00289085  782c                    js       0x2890b3                       
  0x00289087  0000                    add      byte ptr [eax], al             
  0x00289089  782c                    js       0x2890b7                       
  0x0028908B  00fc                    add      ah, bh                         
  0x0028908D  2eaf                    scasd    eax, dword ptr es:[edi]        
  0x0028908F  00ff                    add      bh, bh                         
  0x00289092  7f00                    jg       0x289094                       
                                        ; XREF: 0x00289092 (cond_jump)
  0x00289094  13f4                    adc      esi, esp                       
  0x00289096  61                      popal                                   
  0x00289097  003d06000090            add      byte ptr [0x90000006], bh      
  0x0028909D  4e                      dec      esi                            
  0x0028909E  06                      push     es                             
  0x0028909F  0002                    add      byte ptr [edx], al             
  0x002890A1  0000                    add      byte ptr [eax], al             
  0x002890A3  0000                    add      byte ptr [eax], al             
  0x002890A5  59                      pop      ecx                            
  0x002890A6  56                      push     esi                            
  0x002890A7  000c00                  add      byte ptr [eax + eax], cl       
  0x002890AA  0000                    add      byte ptr [eax], al             
  0x002890AC  00f4                    add      ah, dh                         
  0x002890AE  60                      pushal                                  
  0x002890AF  0033                    add      byte ptr [ebx], dh             
  0x002890B1  05000000f4              add      eax, 0xf4000000                
  0x002890B6  61                      popal                                   
                                        ; XREF: 0x00289089 (cond_jump)
  0x002890B7  0000                    add      byte ptr [eax], al             
  0x002890B9  0000                    add      byte ptr [eax], al             
  0x002890BB  00905a060003            add      byte ptr [eax + 0x300065a], dl 
  0x002890C1  0000                    add      byte ptr [eax], al             
  0x002890C3  0084d807000059          add      byte ptr [eax + ebx*8 + 0x59000007], al 
  0x002890CA  4c                      dec      esp                            
  0x002890CB  0000                    add      byte ptr [eax], al             
  0x002890CE  56                      push     esi                            
  0x002890CF  003b                    add      byte ptr [ebx], bh             
  0x002890D1  06                      push     es                             
  0x002890D2  0000                    add      byte ptr [eax], al             
  0x002890D4  0000                    add      byte ptr [eax], al             
  0x002890D6  2400                    and      al, 0                          
  0x002890D8  00f4                    add      ah, dh                         
  0x002890DA  60                      pushal                                  
  0x002890DB  002d00000045            add      byte ptr [0x45000000], ch      
  0x002890E1  f4                      hlt                                     
  0x002890E2  61                      popal                                   
  0x002890E3  004100                  add      byte ptr [ecx], al             
  0x002890E6  0000                    add      byte ptr [eax], al             
  0x002890E8  05a4050000              add      eax, 0x5a4                     
  0x002890ED  f4                      hlt                                     
                                        ; XREF: 0x00289071 (cond_jump)
  0x002890EE  60                      pushal                                  
  0x002890EF  0000                    add      byte ptr [eax], al             
  0x002890F1  0000                    add      byte ptr [eax], al             
  0x002890F3  0000                    add      byte ptr [eax], al             
  0x002890F5  f4                      hlt                                     
  0x002890F6  61                      popal                                   
  0x002890F7  001400                  add      byte ptr [eax + eax], dl       
  0x002890FA  0000                    add      byte ptr [eax], al             
  0x002890FC  007060                  add      byte ptr [eax + 0x60], dh      
  0x002890FF  008b06000000            add      byte ptr [ebx + 6], cl         
  0x00289105  7061                    jo       0x289168                       
  0x00289107  008c0600000c00          add      byte ptr [esi + eax + 0xc0000], cl 
  0x0028910E  0000                    add      byte ptr [eax], al             
  0x00289110  00f4                    add      ah, dh                         
  0x00289112  56                      push     esi                            
  0x00289113  0011                    add      byte ptr [ecx], dl             
  0x00289115  0000                    add      byte ptr [eax], al             
  0x00289117  0000                    add      byte ptr [eax], al             
  0x00289119  f4                      hlt                                     
  0x0028911A  57                      push     edi                            
  0x0028911B  0000                    add      byte ptr [eax], al             
  0x0028911D  0000                    add      byte ptr [eax], al             
  0x0028911F  0000                    add      byte ptr [eax], al             
  0x00289121  4e                      dec      esi                            
  0x00289122  3800                    cmp      byte ptr [eax], al             
  0x00289124  80f00b                  xor      al, 0xb                        
  0x00289127  00800100000c            add      byte ptr [eax + 0xc000001], al 
  0x0028912D  0000                    add      byte ptr [eax], al             
  0x0028912F  0000                    add      byte ptr [eax], al             
  0x00289131  f4                      hlt                                     
  0x00289132  56                      push     esi                            
  0x00289133  0011                    add      byte ptr [ecx], dl             
  0x00289135  0000                    add      byte ptr [eax], al             
  0x00289137  0000                    add      byte ptr [eax], al             
  0x00289139  f4                      hlt                                     
  0x0028913A  57                      push     edi                            
  0x0028913B  0001                    add      byte ptr [ecx], al             
  0x0028913D  0000                    add      byte ptr [eax], al             
  0x0028913F  0000                    add      byte ptr [eax], al             
  0x00289141  f4                      hlt                                     
  0x00289142  60                      pushal                                  
  0x00289143  003d06000000            add      byte ptr [6], bh               
  0x00289149  4e                      dec      esi                            
  0x0028914A  3800                    cmp      byte ptr [eax], al             
  0x0028914C  0000                    add      byte ptr [eax], al             
  0x0028914E  3900                    cmp      dword ptr [eax], eax           
  0x00289150  80f00b                  xor      al, 0xb                        
  0x00289153  00800100000c            add      byte ptr [eax + 0xc000001], al 
  0x00289159  0000                    add      byte ptr [eax], al             
  0x0028915B  0000                    add      byte ptr [eax], al             
  0x0028915D  f4                      hlt                                     
  0x0028915E  56                      push     esi                            
  0x0028915F  0011                    add      byte ptr [ecx], dl             
  0x00289161  0000                    add      byte ptr [eax], al             
  0x00289163  0000                    add      byte ptr [eax], al             
  0x00289165  f4                      hlt                                     
  0x00289166  57                      push     edi                            
  0x00289167  0002                    add      byte ptr [edx], al             
  0x00289169  0000                    add      byte ptr [eax], al             
  0x0028916B  0000                    add      byte ptr [eax], al             
  0x0028916D  f4                      hlt                                     
  0x0028916E  60                      pushal                                  
  0x0028916F  003d06000000            add      byte ptr [6], bh               
  0x00289175  4e                      dec      esi                            
  0x00289176  3800                    cmp      byte ptr [eax], al             
  0x00289178  0000                    add      byte ptr [eax], al             
  0x0028917A  3900                    cmp      dword ptr [eax], eax           
  0x0028917C  80f00b                  xor      al, 0xb                        
  0x0028917F  00800100000c            add      byte ptr [eax + 0xc000001], al 
  0x00289185  0000                    add      byte ptr [eax], al             
  0x00289187  0000                    add      byte ptr [eax], al             
  0x00289189  f4                      hlt                                     
  0x0028918A  7100                    jno      0x28918c                       
  0x0028918E  ff00                    inc      dword ptr [eax]                
  0x00289190  00f4                    add      ah, dh                         
  0x00289192  7500                    jne      0x289194                       
                                        ; XREF: 0x00289192 (cond_jump)
  0x00289194  fc                      cld                                     
  0x00289196  ff00                    inc      dword ptr [eax]                
  0x00289198  0096220010da            add      byte ptr [esi - 0x25efffde], dl 
  0x0028919E  06                      push     es                             
  0x0028919F  0021                    add      byte ptr [ecx], ah             
  0x002891A1  0000                    add      byte ptr [eax], al             
  0x002891A3  0000                    add      byte ptr [eax], al             
  0x002891A5  da5700                  ficom    dword ptr [edi]                
  0x002891A8  00d2                    add      dl, dl                         
  0x002891AA  51                      push     ecx                            
  0x002891AB  0000                    add      byte ptr [eax], al             
  0x002891AD  b9f00010de              mov      ecx, 0xde1000f0                
  0x002891B2  06                      push     es                             
  0x002891B3  000b                    add      byte ptr [ebx], cl             
  0x002891B5  0000                    add      byte ptr [eax], al             
  0x002891B7  00d4                    add      ah, dl                         
  0x002891B9  e145                    loope    0x289200                       
  0x002891BB  00d6                    add      dh, dl                         
  0x002891BD  39f0                    cmp      eax, esi                       
  0x002891BF  00e6                    add      dh, ah                         
  0x002891C1  a8f0                    test     al, 0xf0                       
  0x002891C3  00d2                    add      dl, dl                         
  0x002891C5  a1f400e259              mov      eax, dword ptr [0x59e200f4]    
  0x002891CA  44                      inc      esp                            
  0x002891CB  00e2                    add      dl, ah                         
  0x002891CD  a1d000d249              mov      eax, dword ptr [0x49d200d0]    
  0x002891D2  45                      inc      ebp                            
  0x002891D3  0010                    add      byte ptr [eax], dl             
  0x002891D5  0020                    add      byte ptr [eax], ah             
  0x002891D7  0009                    add      byte ptr [ecx], cl             
  0x002891D9  dd10                    fst      qword ptr [eax]                
  0x002891DB  004c4c44                add      byte ptr [esp + ecx*2 + 0x44], cl 
  0x002891DF  00d4                    add      ah, dl                         
  0x002891E1  e145                    loope    0x289228                       
  0x002891E3  00d6                    add      dh, dl                         
  0x002891E5  39f0                    cmp      eax, esi                       
  0x002891E7  00e6                    add      dh, ah                         
  0x002891E9  a8f0                    test     al, 0xf0                       
  0x002891EB  00d2                    add      dl, dl                         
  0x002891ED  a1f400e259              mov      eax, dword ptr [0x59e200f4]    
  0x002891F2  44                      inc      esp                            
  0x002891F3  00e2                    add      dl, ah                         
  0x002891F5  a1f000d259              mov      eax, dword ptr [0x59d200f0]    
  0x002891FA  45                      inc      ebp                            
  0x002891FB  0010                    add      byte ptr [eax], dl             
  0x002891FD  0020                    add      byte ptr [eax], ah             
  0x002891FF  0009                    add      byte ptr [ecx], cl             
  0x00289201  c421                    les      esp, ptr [ecx]                 
  0x00289203  004c4c44                add      byte ptr [esp + ecx*2 + 0x44], cl 
  0x00289207  0084f10300005a          add      byte ptr [ecx + esi*8 + 0x5a000003], al 
  0x0028920E  55                      push     ebp                            
  0x0028920F  0000                    add      byte ptr [eax], al             
  0x00289211  5a                      pop      edx                            
  0x00289212  51                      push     ecx                            
  0x00289213  0000                    add      byte ptr [eax], al             
  0x00289215  d422                    aam      0x22                           
  0x00289217  0000                    add      byte ptr [eax], al             
  0x00289219  90                      nop                                     
  0x0028921A  2200                    and      al, byte ptr [eax]             
  0x0028921C  00982300a460            add      byte ptr [eax + 0x60a40023], bl 
  0x00289222  0400                    add      al, 0                          
  0x00289224  0c00                    or       al, 0                          
  0x00289226  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x001F74DD (data_imm), 0x002891E1 (cond_jump)
  0x00289228  40                      inc      eax                            
  0x00289229  1bd0                    sbb      edx, eax                       
  0x0028922B  006208                  add      byte ptr [edx + 8], ah         
  0x0028922E  0000                    add      byte ptr [eax], al             
  0x00289230  7201                    jb       0x289233                       
  0x00289232  0200                    add      al, byte ptr [eax]             
  0x00289234  56                      push     esi                            
  0x00289235  6b680000                imul     ebp, dword ptr [eax], 0        
  0x00289239  7044                    jo       0x28927f                       
  0x0028923B  006509                  add      byte ptr [ebp + 9], ah         
  0x0028923E  0000                    add      byte ptr [eax], al             
  0x00289240  007060                  add      byte ptr [eax + 0x60], dh      
  0x00289243  006809                  add      byte ptr [eax + 9], ch         
  0x00289246  0000                    add      byte ptr [eax], al             
  0x00289248  0b00                    or       eax, dword ptr [eax]           
  0x0028924A  2000                    and      byte ptr [eax], al             
  0x0028924C  07                      pop      es                             
  0x0028924D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028924E  0500df0805              add      eax, 0x508df00                 
  0x00289253  0080100d00ce            add      byte ptr [eax - 0x31fff2f0], al 
  0x00289259  07                      pop      es                             
  0x0028925A  0000                    add      byte ptr [eax], al             
  0x0028925C  80100d                  adc      byte ptr [eax], 0xd            
  0x0028925F  000b                    add      byte ptr [ebx], cl             
  0x00289261  0800                    or       byte ptr [eax], al             
  0x00289263  00050c050080            add      byte ptr [0x8000050c], al      
  0x00289269  100d00d40700            adc      byte ptr [0x7d400], cl         
  0x0028926F  0080100d00f8            add      byte ptr [eax - 0x7fff2f0], al 
  0x00289275  07                      pop      es                             
  0x00289276  0000                    add      byte ptr [eax], al             
  0x00289279  08050000f062            or       byte ptr [0x62f00000], al      
                                        ; XREF: 0x00289239 (cond_jump)
  0x0028927F  006809                  add      byte ptr [eax + 9], ch         
  0x00289282  0000                    add      byte ptr [eax], al             
  0x00289284  00f4                    add      ah, dh                         
  0x00289286  60                      pushal                                  
  0x00289287  00c2                    add      dl, al                         
  0x00289289  0f0000                  sldt     word ptr [eax]                 
  0x0028928C  d8720a                  fdiv     dword ptr [edx + 0xa]          
  0x0028928F  000500000000            add      byte ptr [0], al               
  0x00289295  002400                  add      byte ptr [eax + eax], ah       
  0x00289298  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028929B  006609                  add      byte ptr [esi + 9], ah         
  0x0028929E  0000                    add      byte ptr [eax], al             
  0x002892A0  00e8                    add      al, ch                         
  0x002892A2  5e                      pop      esi                            
  0x002892A3  009f1a02000b            add      byte ptr [edi + 0xb00021a], bl 
  0x002892A9  0020                    add      byte ptr [eax], ah             
  0x002892AB  0002                    add      byte ptr [edx], al             
  0x002892AD  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x002892AE  0500804101              add      eax, 0x1418000                 
  0x002892B3  0000                    add      byte ptr [eax], al             
  0x002892B5  7054                    jo       0x28930b                       
  0x002892B7  006709                  add      byte ptr [edi + 9], ah         
  0x002892BA  0000                    add      byte ptr [eax], al             
  0x002892BC  00f0                    add      al, dh                         
  0x002892BE  44                      inc      esp                            
  0x002892BF  006609                  add      byte ptr [esi + 9], ah         
  0x002892C2  0000                    add      byte ptr [eax], al             
  0x002892C4  52                      push     edx                            
  0x002892C5  090500110805            or       dword ptr [0x5081100], eax     
  0x002892CB  0000                    add      byte ptr [eax], al             
  0x002892CE  44                      inc      esp                            
  0x002892CF  006609                  add      byte ptr [esi + 9], ah         
  0x002892D2  0000                    add      byte ptr [eax], al             
  0x002892D4  80100d                  adc      byte ptr [eax], 0xd            
  0x002892D7  0002                    add      byte ptr [edx], al             
  0x002892D9  0800                    or       byte ptr [eax], al             
  0x002892DB  0000                    add      byte ptr [eax], al             
  0x002892DE  56                      push     esi                            
  0x002892DF  006609                  add      byte ptr [esi + 9], ah         
  0x002892E2  0000                    add      byte ptr [eax], al             
  0x002892E4  80410100                add      byte ptr [ecx + 1], 0          
  0x002892E8  00f0                    add      al, dh                         
  0x002892EA  44                      inc      esp                            
  0x002892EB  006709                  add      byte ptr [edi + 9], ah         
  0x002892EE  0000                    add      byte ptr [eax], al             
  0x002892F0  007054                  add      byte ptr [eax + 0x54], dh      
  0x002892F3  006609                  add      byte ptr [esi + 9], ah         
  0x002892F6  0000                    add      byte ptr [eax], al             
  0x002892F8  45                      inc      ebp                            
  0x002892F9  0020                    add      byte ptr [eax], ah             
  0x002892FB  00d0                    add      al, dl                         
  0x002892FD  97                      xchg     edi, eax                       
  0x002892FE  050080100d              add      eax, 0xd108000                 
  0x00289303  00bc0700000c00          add      byte ptr [edi + eax + 0xc0000], bh 
  0x0028930A  0000                    add      byte ptr [eax], al             
  0x0028930C  00f0                    add      al, dh                         
  0x0028930E  56                      push     esi                            
  0x0028930F  006609                  add      byte ptr [esi + 9], ah         
  0x00289312  0000                    add      byte ptr [eax], al             
  0x00289314  00f0                    add      al, dh                         
  0x00289316  44                      inc      esp                            
  0x00289317  006509                  add      byte ptr [ebp + 9], ah         
  0x0028931A  0000                    add      byte ptr [eax], al             
  0x0028931C  40                      inc      eax                            
  0x0028931D  190c00                  sbb      dword ptr [eax + eax], ecx     
  0x00289320  208000000070            and      byte ptr [eax + 0x70000000], al 
  0x00289326  54                      push     esp                            
  0x00289327  004309                  add      byte ptr [ebx + 9], al         
  0x0028932A  0000                    add      byte ptr [eax], al             
  0x0028932C  00f0                    add      al, dh                         
  0x0028932E  56                      push     esi                            
  0x0028932F  006609                  add      byte ptr [esi + 9], ah         
  0x00289332  0000                    add      byte ptr [eax], al             
  0x00289334  0300                    add      eax, dword ptr [eax]           
  0x00289336  2000                    and      byte ptr [eax], al             
  0x00289338  5a                      pop      edx                            
  0x00289339  2405                    and      al, 5                          
  0x0028933B  0000                    add      byte ptr [eax], al             
  0x0028933E  6200                    bound    eax, qword ptr [eax]           
  0x00289340  6809000000              push     9                              
  0x00289345  f4                      hlt                                     
  0x00289346  60                      pushal                                  
  0x00289347  005309                  add      byte ptr [ebx + 9], dl         
  0x0028934A  0000                    add      byte ptr [eax], al             
  0x0028934C  00f4                    add      ah, dh                         
  0x0028934E  44                      inc      esp                            
  0x0028934F  008000000090            add      byte ptr [eax - 0x70000000], al 
  0x00289355  06                      push     es                             
  0x00289356  06                      push     es                             
  0x00289357  0002                    add      byte ptr [edx], al             
  0x00289359  0000                    add      byte ptr [eax], al             
  0x0028935B  0000                    add      byte ptr [eax], al             
  0x0028935D  58                      pop      eax                            
  0x0028935E  44                      inc      esp                            
  0x0028935F  00de                    add      dh, bl                         
  0x00289361  1202                    adc      al, byte ptr [edx]             
  0x00289363  00941a02004019          add      byte ptr [edx + ebx + 0x19400002], dl 
  0x0028936A  0c00                    or       al, 0                          
  0x0028936C  1b10                    sbb      edx, dword ptr [eax]           
  0x0028936E  0000                    add      byte ptr [eax], al             
  0x00289370  007054                  add      byte ptr [eax + 0x54], dh      
  0x00289373  0036                    add      byte ptr [esi], dh             
  0x00289375  0900                    or       dword ptr [eax], eax           
  0x00289377  0013                    add      byte ptr [ebx], dl             
  0x00289379  f4                      hlt                                     
  0x0028937A  44                      inc      esp                            
  0x0028937B  0012                    add      byte ptr [edx], dl             
  0x0028937D  0000                    add      byte ptr [eax], al             
  0x0028937F  004019                  add      byte ptr [eax + 0x19], al      
  0x00289382  0c00                    or       al, 0                          
  0x00289384  215000                  and      dword ptr [eax], edx           
  0x00289387  0000                    add      byte ptr [eax], al             
  0x00289389  7054                    jo       0x2893df                       
  0x0028938B  003a                    add      byte ptr [edx], bh             
  0x0028938D  0900                    or       dword ptr [eax], eax           
  0x0028938F  009e220200d4            add      byte ptr [esi - 0x2bfffdde], bl 
  0x00289395  2a02                    sub      al, byte ptr [edx]             
  0x00289397  004019                  add      byte ptr [eax + 0x19], al      
  0x0028939A  0c00                    or       al, 0                          
  0x0028939C  2110                    and      dword ptr [eax], edx           
  0x0028939E  0000                    add      byte ptr [eax], al             
  0x002893A0  94                      xchg     esp, eax                       
  0x002893A1  2a02                    sub      al, byte ptr [edx]             
  0x002893A3  004019                  add      byte ptr [eax + 0x19], al      
  0x002893A6  0c00                    or       al, 0                          
  0x002893A8  2210                    and      dl, byte ptr [eax]             
  0x002893AA  0000                    add      byte ptr [eax], al             
  0x002893AC  d422                    aam      0x22                           
  0x002893AE  0200                    add      al, byte ptr [eax]             
  0x002893B0  40                      inc      eax                            
  0x002893B1  190c00                  sbb      dword ptr [eax + eax], ecx     
  0x002893B4  2310                    and      edx, dword ptr [eax]           
  0x002893B6  0000                    add      byte ptr [eax], al             
  0x002893B8  007054                  add      byte ptr [eax + 0x54], dh      
  0x002893BB  003b                    add      byte ptr [ebx], bh             
  0x002893BD  0900                    or       dword ptr [eax], eax           
  0x002893BF  0013                    add      byte ptr [ebx], dl             
  0x002893C1  0020                    add      byte ptr [eax], ah             
  0x002893C3  00944a02004019          add      byte ptr [edx + ecx*2 + 0x19400002], dl 
  0x002893CA  0c00                    or       al, 0                          
  0x002893CC  1a20                    sbb      ah, byte ptr [eax]             
  0x002893CE  0000                    add      byte ptr [eax], al             
  0x002893D0  007054                  add      byte ptr [eax + 0x54], dh      
  0x002893D3  004709                  add      byte ptr [edi + 9], al         
  0x002893D6  0000                    add      byte ptr [eax], al             
  0x002893D8  d41a                    aam      0x1a                           
  0x002893DA  0200                    add      al, byte ptr [eax]             
  0x002893DC  007044                  add      byte ptr [eax + 0x44], dh      
                                        ; XREF: 0x00289389 (cond_jump)
  0x002893DF  004809                  add      byte ptr [eax + 9], cl         
  0x002893E2  0000                    add      byte ptr [eax], al             
  0x002893E4  1300                    adc      eax, dword ptr [eax]           
  0x002893E6  2000                    and      byte ptr [eax], al             
  0x002893E8  94                      xchg     esp, eax                       
  0x002893E9  3a02                    cmp      al, byte ptr [edx]             
  0x002893EB  004019                  add      byte ptr [eax + 0x19], al      
  0x002893EE  0c00                    or       al, 0                          
  0x002893F0  1810                    sbb      byte ptr [eax], dl             
  0x002893F2  0000                    add      byte ptr [eax], al             
  0x002893F4  94                      xchg     esp, eax                       
  0x002893F5  3202                    xor      al, byte ptr [edx]             
  0x002893F7  004019                  add      byte ptr [eax + 0x19], al      
  0x002893FA  0c00                    or       al, 0                          
  0x002893FC  1910                    sbb      dword ptr [eax], edx           
  0x002893FE  0000                    add      byte ptr [eax], al             
  0x00289400  007054                  add      byte ptr [eax + 0x54], dh      
  0x00289403  00440900                add      byte ptr [ecx + ecx], al       
  0x00289407  00d4                    add      ah, dl                         
  0x00289409  3a02                    cmp      al, byte ptr [edx]             
  0x0028940B  0000                    add      byte ptr [eax], al             
  0x0028940D  7044                    jo       0x289453                       
  0x0028940F  004609                  add      byte ptr [esi + 9], al         
  0x00289412  0000                    add      byte ptr [eax], al             
  0x00289414  d432                    aam      0x32                           
  0x00289416  0200                    add      al, byte ptr [eax]             
  0x00289418  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028941B  004509                  add      byte ptr [ebp + 9], al         
  0x0028941E  0000                    add      byte ptr [eax], al             
  0x00289420  13f4                    adc      esi, esp                       
  0x00289422  60                      pushal                                  
  0x00289423  0032                    add      byte ptr [edx], dh             
  0x00289425  0900                    or       dword ptr [eax], eax           
  0x00289427  0000                    add      byte ptr [eax], al             
  0x00289429  f4                      hlt                                     
  0x0028942A  57                      push     edi                            
  0x0028942B  0010                    add      byte ptr [eax], dl             
  0x0028942D  0000                    add      byte ptr [eax], al             
  0x0028942F  0080100d00a9            add      byte ptr [eax - 0x56fff2f0], al 
  0x00289435  0200                    add      al, byte ptr [eax]             
  0x00289437  0000                    add      byte ptr [eax], al             
  0x00289439  f4                      hlt                                     
  0x0028943A  44                      inc      esp                            
  0x0028943B  0000                    add      byte ptr [eax], al             
  0x0028943D  0000                    add      byte ptr [eax], al             
  0x0028943F  004500                  add      byte ptr [ebp], al             
  0x00289442  2000                    and      byte ptr [eax], al             
  0x00289444  00740500                add      byte ptr [ebp + eax], dh       
  0x00289448  0c00                    or       al, 0                          
  0x0028944A  0000                    add      byte ptr [eax], al             
  0x0028944C  1b00                    sbb      eax, dword ptr [eax]           
  0x0028944E  3000                    xor      byte ptr [eax], al             
  0x00289450  80100d                  adc      byte ptr [eax], 0xd            
                                        ; XREF: 0x0028940D (cond_jump)
  0x00289453  00a10200000c            add      byte ptr [ecx + 0xc000002], ah 
  0x00289459  0000                    add      byte ptr [eax], al             
  0x0028945B  0000                    add      byte ptr [eax], al             
  0x0028945D  f4                      hlt                                     
  0x0028945E  44                      inc      esp                            
  0x0028945F  001500000000            add      byte ptr [0], dl               
  0x00289465  7044                    jo       0x2894ab                       
  0x00289467  0032                    add      byte ptr [edx], dh             
  0x00289469  0900                    or       dword ptr [eax], eax           
  0x0028946B  0000                    add      byte ptr [eax], al             
  0x0028946D  f4                      hlt                                     
  0x0028946E  44                      inc      esp                            
  0x0028946F  005309                  add      byte ptr [ebx + 9], dl         
  0x00289472  0000                    add      byte ptr [eax], al             
  0x00289474  007044                  add      byte ptr [eax + 0x44], dh      
  0x00289477  0033                    add      byte ptr [ebx], dh             
  0x00289479  0900                    or       dword ptr [eax], eax           
  0x0028947B  0000                    add      byte ptr [eax], al             
  0x0028947D  f4                      hlt                                     
  0x0028947E  44                      inc      esp                            
  0x0028947F  005f09                  add      byte ptr [edi + 9], bl         
  0x00289482  0000                    add      byte ptr [eax], al             
  0x00289484  007044                  add      byte ptr [eax + 0x44], dh      
  0x00289487  003409                  add      byte ptr [ecx + ecx], dh       
  0x0028948A  0000                    add      byte ptr [eax], al             
  0x0028948C  00f4                    add      ah, dh                         
  0x0028948E  44                      inc      esp                            
  0x0028948F  005909                  add      byte ptr [ecx + 9], bl         
  0x00289492  0000                    add      byte ptr [eax], al             
  0x00289494  007044                  add      byte ptr [eax + 0x44], dh      
  0x00289497  003509000000            add      byte ptr [9], dh               
  0x0028949D  f4                      hlt                                     
  0x0028949E  44                      inc      esp                            
  0x0028949F  00ff                    add      bh, bh                         
  0x002894A1  ff00                    inc      dword ptr [eax]                
  0x002894A3  0000                    add      byte ptr [eax], al             
  0x002894A5  7044                    jo       0x2894eb                       
  0x002894A7  0039                    add      byte ptr [ecx], bh             
  0x002894A9  0900                    or       dword ptr [eax], eax           
                                        ; XREF: 0x00289465 (cond_jump)
  0x002894AB  0000                    add      byte ptr [eax], al             
  0x002894AD  f4                      hlt                                     
  0x002894AE  44                      inc      esp                            
  0x002894AF  004709                  add      byte ptr [edi + 9], al         
  0x002894B2  0000                    add      byte ptr [eax], al             
  0x002894B4  007044                  add      byte ptr [eax + 0x44], dh      
  0x002894B7  003c09                  add      byte ptr [ecx + ecx], bh       
  0x002894BA  0000                    add      byte ptr [eax], al             
  0x002894BC  0000                    add      byte ptr [eax], al             
  0x002894BE  2400                    and      al, 0                          
  0x002894C0  007044                  add      byte ptr [eax + 0x44], dh      
  0x002894C3  0037                    add      byte ptr [edi], dh             
  0x002894C5  0900                    or       dword ptr [eax], eax           
  0x002894C7  0000                    add      byte ptr [eax], al             
  0x002894C9  7044                    jo       0x28950f                       
  0x002894CB  0038                    add      byte ptr [eax], bh             
  0x002894CD  0900                    or       dword ptr [eax], eax           
  0x002894CF  0000                    add      byte ptr [eax], al             
  0x002894D1  7044                    jo       0x289517                       
  0x002894D3  003d09000000            add      byte ptr [9], bh               
  0x002894D9  7044                    jo       0x28951f                       
  0x002894DB  003e                    add      byte ptr [esi], bh             
  0x002894DD  0900                    or       dword ptr [eax], eax           
  0x002894DF  0000                    add      byte ptr [eax], al             
  0x002894E1  7044                    jo       0x289527                       
  0x002894E3  003f                    add      byte ptr [edi], bh             
  0x002894E5  0900                    or       dword ptr [eax], eax           
  0x002894E7  0000                    add      byte ptr [eax], al             
  0x002894E9  7044                    jo       0x28952f                       
                                        ; XREF: 0x002894A5 (cond_jump)
  0x002894EB  004009                  add      byte ptr [eax + 9], al         
  0x002894EE  0000                    add      byte ptr [eax], al             
  0x002894F0  007044                  add      byte ptr [eax + 0x44], dh      
  0x002894F3  004109                  add      byte ptr [ecx + 9], al         
  0x002894F6  0000                    add      byte ptr [eax], al             
  0x002894F8  007044                  add      byte ptr [eax + 0x44], dh      
  0x002894FB  004209                  add      byte ptr [edx + 9], al         
  0x002894FE  0000                    add      byte ptr [eax], al             
  0x00289500  00f4                    add      ah, dh                         
  0x00289502  60                      pushal                                  
  0x00289503  004d09                  add      byte ptr [ebp + 9], cl         
  0x00289506  0000                    add      byte ptr [eax], al             
  0x00289508  00f4                    add      ah, dh                         
  0x0028950A  44                      inc      esp                            
  0x0028950B  0000                    add      byte ptr [eax], al             
  0x0028950D  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x002894C9 (cond_jump)
  0x0028950F  0000                    add      byte ptr [eax], al             
  0x00289511  58                      pop      eax                            
  0x00289512  44                      inc      esp                            
  0x00289513  0000                    add      byte ptr [eax], al             
  0x00289515  f4                      hlt                                     
  0x00289516  44                      inc      esp                            
                                        ; XREF: 0x002894D1 (cond_jump)
  0x00289517  0002                    add      byte ptr [edx], al             
  0x00289519  0000                    add      byte ptr [eax], al             
  0x0028951B  0000                    add      byte ptr [eax], al             
  0x0028951D  58                      pop      eax                            
  0x0028951E  44                      inc      esp                            
                                        ; XREF: 0x002894D9 (cond_jump)
  0x0028951F  0000                    add      byte ptr [eax], al             
  0x00289521  f4                      hlt                                     
  0x00289522  44                      inc      esp                            
  0x00289523  0003                    add      byte ptr [ebx], al             
  0x00289525  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x002894E1 (cond_jump)
  0x00289527  0000                    add      byte ptr [eax], al             
  0x00289529  58                      pop      eax                            
  0x0028952A  44                      inc      esp                            
  0x0028952B  0000                    add      byte ptr [eax], al             
  0x0028952D  f4                      hlt                                     
  0x0028952E  44                      inc      esp                            
                                        ; XREF: 0x002894E9 (cond_jump)
  0x0028952F  000400                  add      byte ptr [eax + eax], al       
  0x00289532  0000                    add      byte ptr [eax], al             
  0x00289534  005844                  add      byte ptr [eax + 0x44], bl      
  0x00289537  0000                    add      byte ptr [eax], al             
  0x00289539  f4                      hlt                                     
  0x0028953A  44                      inc      esp                            
  0x0028953B  0001                    add      byte ptr [ecx], al             
  0x0028953D  0000                    add      byte ptr [eax], al             
  0x0028953F  0000                    add      byte ptr [eax], al             
  0x00289541  58                      pop      eax                            
  0x00289542  44                      inc      esp                            
  0x00289543  0000                    add      byte ptr [eax], al             
  0x00289545  f4                      hlt                                     
  0x00289546  44                      inc      esp                            
  0x00289547  000500000000            add      byte ptr [0], al               
  0x0028954D  58                      pop      eax                            
  0x0028954E  44                      inc      esp                            
  0x0028954F  0000                    add      byte ptr [eax], al             
  0x00289551  f4                      hlt                                     
  0x00289552  60                      pushal                                  
  0x00289553  005f09                  add      byte ptr [edi + 9], bl         
  0x00289556  0000                    add      byte ptr [eax], al             
  0x00289558  00f4                    add      ah, dh                         
  0x0028955A  44                      inc      esp                            
  0x0028955B  0001                    add      byte ptr [ecx], al             
  0x0028955D  0000                    add      byte ptr [eax], al             
  0x0028955F  009006060002            add      byte ptr [eax + 0x2000606], dl 
  0x00289565  0000                    add      byte ptr [eax], al             
  0x00289567  0000                    add      byte ptr [eax], al             
  0x00289569  58                      pop      eax                            
  0x0028956A  44                      inc      esp                            
  0x0028956B  0000                    add      byte ptr [eax], al             
  0x0028956D  f4                      hlt                                     
  0x0028956E  60                      pushal                                  
  0x0028956F  005909                  add      byte ptr [ecx + 9], bl         
  0x00289572  0000                    add      byte ptr [eax], al             
  0x00289574  00f4                    add      ah, dh                         
  0x00289576  44                      inc      esp                            
  0x00289577  00ff                    add      bh, bh                         
  0x00289579  ff00                    inc      dword ptr [eax]                
  0x0028957B  009006060002            add      byte ptr [eax + 0x2000606], dl 
  0x00289581  0000                    add      byte ptr [eax], al             
  0x00289583  0000                    add      byte ptr [eax], al             
  0x00289585  58                      pop      eax                            
  0x00289586  44                      inc      esp                            
  0x00289587  000c00                  add      byte ptr [eax + eax], cl       
  0x0028958A  0000                    add      byte ptr [eax], al             
  0x0028958C  00f0                    add      al, dh                         
  0x0028958E  6200                    bound    eax, qword ptr [eax]           
  0x00289590  6809000000              push     9                              
  0x00289595  f4                      hlt                                     
  0x00289596  45                      inc      ebp                            
  0x00289597  0003                    add      byte ptr [ebx], al             
  0x00289599  0000                    add      byte ptr [eax], al             
  0x0028959B  00d6                    add      dh, dl                         
  0x0028959D  1202                    adc      al, byte ptr [edx]             
  0x0028959F  00e0                    add      al, ah                         
  0x002895A1  0020                    add      byte ptr [eax], ah             
  0x002895A3  0000                    add      byte ptr [eax], al             
  0x002895A5  f4                      hlt                                     
  0x002895A6  6200                    bound    eax, qword ptr [eax]           
  0x002895A8  92                      xchg     edx, eax                       
  0x002895A9  0f0000                  sldt     word ptr [eax]                 
  0x002895AC  000e                    add      byte ptr [esi], cl             
  0x002895AE  2100                    and      dword ptr [eax], eax           
  0x002895B0  40                      inc      eax                            
  0x002895B1  0020                    add      byte ptr [eax], ah             
  0x002895B3  0000                    add      byte ptr [eax], al             
  0x002895B5  f4                      hlt                                     
  0x002895B6  60                      pushal                                  
  0x002895B7  008000000000            add      byte ptr [eax], al             
  0x002895BD  9a210000f47000          lcall    0x70, 0xf4000021               
  0x002895C4  0001                    add      byte ptr [ecx], al             
  0x002895C6  0000                    add      byte ptr [eax], al             
  0x002895C8  00f4                    add      ah, dh                         
  0x002895CA  56                      push     esi                            
  0x002895CB  0007                    add      byte ptr [edi], al             
  0x002895CD  0000                    add      byte ptr [eax], al             
  0x002895CF  0000                    add      byte ptr [eax], al             
  0x002895D1  ea790080010d00          ljmp     0xd:0x1800079                  
  0x002895D8  0300                    add      eax, dword ptr [eax]           
  0x002895DA  2000                    and      byte ptr [eax], al             
  0x002895DC  002405000c0000          add      byte ptr [eax + 0xc00], ah     
  0x002895E3  0000                    add      byte ptr [eax], al             
  0x002895E5  0823                    or       byte ptr [ebx], ah             
  0x002895E7  000a                    add      byte ptr [edx], cl             
  0x002895E9  0000                    add      byte ptr [eax], al             
  0x002895EB  00a0c80400a0            add      byte ptr [eax - 0x5ffffb38], ah 
  0x002895F1  61                      popal                                   
  0x002895F2  0400                    add      al, 0                          
  0x002895F4  a0640400a0              mov      al, byte ptr [0xa0000464]      
  0x002895F9  650400                  add      al, 0                          
  0x002895FC  f8                      clc                                     
  0x002895FD  0400                    add      al, 0                          
  0x002895FF  0000                    add      byte ptr [eax], al             
  0x00289601  0e                      push     cs                             
  0x00289602  2300                    and      eax, dword ptr [eax]           
  0x00289604  2200                    and      al, byte ptr [eax]             
  0x00289606  2000                    and      byte ptr [eax], al             
  0x00289608  009821000014            add      byte ptr [eax + 0x14000021], bl 
  0x0028960E  2200                    and      al, byte ptr [eax]             
  0x00289610  114804                  adc      dword ptr [eax + 4], ecx       
  0x00289613  0000                    add      byte ptr [eax], al             
  0x00289615  35220000e0              xor      eax, 0xe0000022                
  0x0028961A  5f                      pop      edi                            
  0x0028961B  0000                    add      byte ptr [eax], al             
  0x0028961D  e14f                    loope    0x28966e                       
  0x0028961F  0078e0                  add      byte ptr [eax - 0x20], bh      
  0x00289622  5e                      pop      esi                            
  0x00289623  0010                    add      byte ptr [eax], dl             
  0x00289625  d806                    fadd     dword ptr [esi]                
  0x00289627  0009                    add      byte ptr [ecx], cl             
  0x00289629  0000                    add      byte ptr [eax], al             
  0x0028962B  0019                    add      byte ptr [ecx], bl             
  0x0028962D  d94500                  fld      dword ptr [ebp]                
  0x00289630  16                      push     ss                             
  0x00289631  0020                    add      byte ptr [eax], ah             
  0x00289633  0000                    add      byte ptr [eax], al             
  0x00289635  808f0068b88a00          or       byte ptr [edi - 0x75479800], 0 
  0x0028963C  19e1                    sbb      ecx, esp                       
  0x0028963E  4f                      dec      edi                            
  0x0028963F  0016                    add      byte ptr [esi], dl             
  0x00289641  0020                    add      byte ptr [eax], ah             
  0x00289643  0000                    add      byte ptr [eax], al             
  0x00289645  1ccf                    sbb      al, 0xcf                       
  0x00289647  00781d                  add      byte ptr [eax + 0x1d], bh      
  0x0028964A  ca0000                  retf     0                              
  0x0028964D  0e                      push     cs                             
  0x0028964E  2300                    and      eax, dword ptr [eax]           
  0x00289650  2230                    and      dh, byte ptr [eax]             
  0x00289652  2200                    and      al, byte ptr [eax]             
  0x00289654  009821000014            add      byte ptr [eax + 0x14000021], bl 
  0x0028965A  2200                    and      al, byte ptr [eax]             
  0x0028965C  114804                  adc      dword ptr [eax + 4], ecx       
  0x0028965F  0000                    add      byte ptr [eax], al             
  0x00289661  35220000e0              xor      eax, 0xe0000022                
  0x00289666  5f                      pop      edi                            
  0x00289667  0000                    add      byte ptr [eax], al             
  0x00289669  e14f                    loope    0x2896ba                       
  0x0028966B  0078e0                  add      byte ptr [eax - 0x20], bh      
                                        ; XREF: 0x0028961D (cond_jump)
  0x0028966E  5e                      pop      esi                            
  0x0028966F  0010                    add      byte ptr [eax], dl             
  0x00289671  d806                    fadd     dword ptr [esi]                
  0x00289673  0009                    add      byte ptr [ecx], cl             
  0x00289675  0000                    add      byte ptr [eax], al             
  0x00289677  0019                    add      byte ptr [ecx], bl             
  0x00289679  d94500                  fld      dword ptr [ebp]                
  0x0028967C  16                      push     ss                             
  0x0028967D  0020                    add      byte ptr [eax], ah             
  0x0028967F  0000                    add      byte ptr [eax], al             
  0x00289681  808f0068b88a00          or       byte ptr [edi - 0x75479800], 0 
  0x00289688  19e1                    sbb      ecx, esp                       
  0x0028968A  4f                      dec      edi                            
  0x0028968B  0016                    add      byte ptr [esi], dl             
  0x0028968D  0020                    add      byte ptr [eax], ah             
  0x0028968F  0000                    add      byte ptr [eax], al             
  0x00289691  1ccf                    sbb      al, 0xcf                       
  0x00289693  00781d                  add      byte ptr [eax + 0x1d], bh      
  0x00289696  ca0000                  retf     0                              
  0x00289699  3022                    xor      byte ptr [edx], ah             
  0x0028969B  0000                    add      byte ptr [eax], al             
  0x0028969D  1422                    adc      al, 0x22                       
  0x0028969F  0011                    add      byte ptr [ecx], dl             
  0x002896A1  48                      dec      eax                            
  0x002896A2  0400                    add      al, 0                          
  0x002896A4  0035220000e0            add      byte ptr [0xe0000022], dh      
  0x002896AA  5f                      pop      edi                            
  0x002896AB  0000                    add      byte ptr [eax], al             
  0x002896AD  e145                    loope    0x2896f4                       
  0x002896AF  006ce05e                add      byte ptr [eax + 0x5e], ch      
  0x002896B3  0010                    add      byte ptr [eax], dl             
  0x002896B5  d806                    fadd     dword ptr [esi]                
  0x002896B7  0009                    add      byte ptr [ecx], cl             
  0x002896B9  0000                    add      byte ptr [eax], al             
  0x002896BB  0019                    add      byte ptr [ecx], bl             
  0x002896BE  4f                      dec      edi                            
  0x002896BF  0016                    add      byte ptr [esi], dl             
  0x002896C1  0020                    add      byte ptr [eax], ah             
  0x002896C3  0000                    add      byte ptr [eax], al             
  0x002896C5  808f0078b88a00          or       byte ptr [edi - 0x75478800], 0 
  0x002896CC  19e1                    sbb      ecx, esp                       
  0x002896CE  45                      inc      ebp                            
  0x002896CF  0016                    add      byte ptr [esi], dl             
  0x002896D1  0020                    add      byte ptr [eax], ah             
  0x002896D3  0000                    add      byte ptr [eax], al             
  0x002896D5  1ccf                    sbb      al, 0xcf                       
  0x002896D7  006c1dca                add      byte ptr [ebp + ebx - 0x36], ch 
  0x002896DB  0000                    add      byte ptr [eax], al             
  0x002896DD  0e                      push     cs                             
  0x002896DE  2300                    and      eax, dword ptr [eax]           
  0x002896E0  2202                    and      al, byte ptr [edx]             
  0x002896E2  3a00                    cmp      al, byte ptr [eax]             
  0x002896E4  0030                    add      byte ptr [eax], dh             
  0x002896E6  2200                    and      al, byte ptr [eax]             
  0x002896E8  009921000011            add      byte ptr [ecx + 0x11000021], bl 
  0x002896EE  2200                    and      al, byte ptr [eax]             
  0x002896F0  0032                    add      byte ptr [edx], dh             
  0x002896F2  2300                    and      eax, dword ptr [eax]           
                                        ; XREF: 0x002896AD (cond_jump)
  0x002896F4  001422                  add      byte ptr [edx], dl             
  0x002896F7  0000                    add      byte ptr [eax], al             
  0x002896F9  f4                      hlt                                     
  0x002896FA  6600520f                add      byte ptr [edx + 0xf], dl       
  0x002896FE  0000                    add      byte ptr [eax], al             
  0x00289700  004920                  add      byte ptr [ecx + 0x20], cl      
  0x00289703  0000                    add      byte ptr [eax], al             
  0x00289705  352200185a              xor      eax, 0x5a180022                
  0x0028970A  0400                    add      al, 0                          
  0x0028970C  001c23                  add      byte ptr [ebx], bl             
  0x0028970F  0000                    add      byte ptr [eax], al             
  0x00289711  1d23000052              sbb      eax, 0x52000023                
  0x00289716  2000                    and      byte ptr [eax], al             
  0x00289718  00e0                    add      al, ah                         
  0x0028971A  5f                      pop      edi                            
  0x0028971B  0000                    add      byte ptr [eax], al             
  0x0028971D  c1f400                  sal      esp, 0                         
  0x00289720  00de                    add      dh, bl                         
  0x00289722  4c                      dec      esp                            
  0x00289723  00aed94f00bf            add      byte ptr [esi - 0x40ffb027], ch 
  0x00289729  e05e                    loopne   0x289789                       
  0x0028972B  0010                    add      byte ptr [eax], dl             
  0x0028972D  da06                    fiadd    dword ptr [esi]                
  0x0028972F  0020                    add      byte ptr [eax], ah             
  0x00289731  0000                    add      byte ptr [eax], al             
  0x00289733  0010                    add      byte ptr [eax], dl             
  0x00289735  d206                    rol      byte ptr [esi], cl             
  0x00289737  0007                    add      byte ptr [edi], al             
  0x00289739  0000                    add      byte ptr [eax], al             
  0x0028973B  0016                    add      byte ptr [esi], dl             
  0x0028973D  808f00eee14500          or       byte ptr [edi + 0x45e1ee00], 0 
  0x00289744  cb                      retf                                    
  0x00289745  b88a00161c              mov      eax, 0x1c16008a                
  0x0028974A  cf                      iretd                                   
  0x0028974B  00aed94f00bf            add      byte ptr [esi - 0x40ffb027], ch 
  0x00289751  1dca000049              sbb      eax, 0x490000ca                
  0x00289756  2000                    and      byte ptr [eax], al             
  0x00289758  16                      push     ss                             
  0x00289759  808f00eea88a00          or       byte ptr [edi - 0x75571200], 0 
  0x00289760  cb                      retf                                    
  0x00289761  e145                    loope    0x2897a8                       
  0x00289763  0016                    add      byte ptr [esi], dl             
  0x00289765  0ccf                    or       al, 0xcf                       
  0x00289767  00ea                    add      dl, ch                         
  0x0028976A  4f                      dec      edi                            
  0x0028976B  00cf                    add      bh, cl                         
  0x0028976D  0dca0010d2              or       eax, 0xd21000ca                
  0x00289772  06                      push     es                             
  0x00289773  0007                    add      byte ptr [edi], al             
  0x00289775  0000                    add      byte ptr [eax], al             
  0x00289777  0016                    add      byte ptr [esi], dl             
  0x00289779  808f00aee14500          or       byte ptr [edi + 0x45e1ae00], 0 
  0x00289780  bfb88a0016              mov      edi, 0x16008ab8                
  0x00289785  1ccf                    sbb      al, 0xcf                       
  0x00289787  00ea                    add      dl, ch                         
  0x0028978A  4f                      dec      edi                            
  0x0028978B  00cf                    add      bh, cl                         
  0x0028978D  1dca000049              sbb      eax, 0x490000ca                
  0x00289792  2000                    and      byte ptr [eax], al             
  0x00289794  16                      push     ss                             
  0x00289795  808f00aea88a00          or       byte ptr [edi - 0x75575200], 0 
  0x0028979C  bfc1f40000              mov      edi, 0xf4c1                    
  0x002897A1  de4c0016                fimul    word ptr [eax + eax + 0x16]    
  0x002897A5  0ccf                    or       al, 0xcf                       
  0x002897A7  00aed94f00bf            add      byte ptr [esi - 0x40ffb027], ch 
  0x002897AD  0dca00002f              or       eax, 0x2f0000ca                
  0x002897B2  2300                    and      eax, dword ptr [eax]           
  0x002897B4  2a4e23                  sub      cl, byte ptr [esi + 0x23]      
  0x002897B7  0032                    add      byte ptr [edx], dh             
  0x002897B9  0020                    add      byte ptr [eax], ah             
  0x002897BB  0000                    add      byte ptr [eax], al             
  0x002897BD  b92100009a              mov      ecx, 0x9a000021                
  0x002897C2  2100                    and      dword ptr [eax], eax           
  0x002897C4  80cd0c                  or       ch, 0xc                        
  0x002897C7  00ca                    add      dl, cl                         
  0x002897CA  ff00                    inc      dword ptr [eax]                
  0x002897CC  0002                    add      byte ptr [edx], al             
  0x002897CE  3800                    cmp      byte ptr [eax], al             
  0x002897D0  001422                  add      byte ptr [edx], dl             
  0x002897D3  0000                    add      byte ptr [eax], al             
  0x002897D5  1c23                    sbb      al, 0x23                       
  0x002897D7  0000                    add      byte ptr [eax], al             
  0x002897D9  52                      push     edx                            
  0x002897DA  2300                    and      eax, dword ptr [eax]           
  0x002897DC  00f4                    add      ah, dh                         
  0x002897DE  6600520f                add      byte ptr [edx + 0xf], dl       
  0x002897E2  0000                    add      byte ptr [eax], al             
  0x002897E4  115804                  adc      dword ptr [eax + 4], ebx       
  0x002897E7  0000                    add      byte ptr [eax], al             
  0x002897E9  1923                    sbb      dword ptr [ebx], esp           
  0x002897EB  0000                    add      byte ptr [eax], al             
  0x002897ED  352200001d              xor      eax, 0x1d000022                
  0x002897F2  2300                    and      eax, dword ptr [eax]           
  0x002897F4  005220                  add      byte ptr [edx + 0x20], dl      
  0x002897F7  0000                    add      byte ptr [eax], al             
  0x002897F9  e05f                    loopne   0x28985a                       
  0x002897FB  0000                    add      byte ptr [eax], al             
  0x002897FD  c1f400                  sal      esp, 0                         
  0x00289800  00de                    add      dh, bl                         
  0x00289802  4c                      dec      esp                            
  0x00289803  00aec94f00bf            add      byte ptr [esi - 0x40ffb037], ch 
  0x00289809  e05e                    loopne   0x289869                       
  0x0028980B  0016                    add      byte ptr [esi], dl             
  0x0028980D  0020                    add      byte ptr [eax], ah             
  0x0028980F  0000                    add      byte ptr [eax], al             
  0x00289811  808f00eea88a00          or       byte ptr [edi - 0x75571200], 0 
  0x00289818  cb                      retf                                    
  0x00289819  e145                    loope    0x289860                       
  0x0028981B  0016                    add      byte ptr [esi], dl             
  0x0028981D  0ccf                    or       al, 0xcf                       
  0x0028981F  0010                    add      byte ptr [eax], dl             
  0x00289821  d206                    rol      byte ptr [esi], cl             
  0x00289823  0010                    add      byte ptr [eax], dl             
  0x00289825  0000                    add      byte ptr [eax], al             
  0x00289827  00ea                    add      dl, ch                         
  0x00289829  c9                      leave                                   
  0x0028982A  4f                      dec      edi                            
  0x0028982B  00cf                    add      bh, cl                         
  0x0028982D  0dca001600              or       eax, 0x1600ca                  
  0x00289832  2000                    and      byte ptr [eax], al             
  0x00289834  00808f00aea8            add      byte ptr [eax - 0x5751ff71], al 
  0x0028983A  8a00                    mov      al, byte ptr [eax]             
  0x0028983C  bfc1f40000              mov      edi, 0xf4c1                    
  0x00289841  de4c0016                fimul    word ptr [eax + eax + 0x16]    
  0x00289845  0ccf                    or       al, 0xcf                       
  0x00289847  00aec94f00bf            add      byte ptr [esi - 0x40ffb037], ch 
  0x0028984D  0dca001600              or       eax, 0x1600ca                  
  0x00289852  2000                    and      byte ptr [eax], al             
  0x00289854  00808f00eea8            add      byte ptr [eax - 0x5711ff71], al 
                                        ; XREF: 0x002897F9 (cond_jump)
  0x0028985A  8a00                    mov      al, byte ptr [eax]             
  0x0028985C  cb                      retf                                    
  0x0028985D  e145                    loope    0x2898a4                       
  0x0028985F  0016                    add      byte ptr [esi], dl             
  0x00289861  0ccf                    or       al, 0xcf                       
  0x00289863  00ea                    add      dl, ch                         
  0x00289865  c9                      leave                                   
  0x00289866  4f                      dec      edi                            
  0x00289867  00cf                    add      bh, cl                         
                                        ; XREF: 0x00289809 (cond_jump)
  0x00289869  0dca001600              or       eax, 0x1600ca                  
  0x0028986E  2000                    and      byte ptr [eax], al             
  0x00289870  00808f00aea8            add      byte ptr [eax - 0x5751ff71], al 
  0x00289876  8a00                    mov      al, byte ptr [eax]             
  0x00289878  bf00200020              mov      edi, 0x20002000                
  0x0028987D  f4                      hlt                                     
  0x0028987E  0500ffff00              add      eax, 0xffff00                  
  0x00289883  0016                    add      byte ptr [esi], dl             
  0x00289885  4c                      dec      esp                            
  0x00289886  57                      push     edi                            
  0x00289887  00a061040000            add      byte ptr [eax + 0x461], ah     
  0x0028988D  4d                      dec      ebp                            
  0x0028988E  56                      push     esi                            
  0x0028988F  00a0640400a0            add      byte ptr [eax - 0x5ffffb9c], ah 
  0x00289895  650400                  add      al, 0                          
  0x00289898  b8f300000c              mov      eax, 0xc0000f3                 
  0x0028989D  0000                    add      byte ptr [eax], al             
  0x0028989F  0000                    add      byte ptr [eax], al             
  0x002898A1  f4                      hlt                                     
  0x002898A2  7100                    jno      0x2898a4                       
  0x002898A6  ff00                    inc      dword ptr [eax]                
  0x002898A8  00f4                    add      ah, dh                         
  0x002898AA  7500                    jne      0x2898ac                       
                                        ; XREF: 0x002898AA (cond_jump)
  0x002898AC  fc                      cld                                     
  0x002898AE  ff00                    inc      dword ptr [eax]                
  0x002898B0  0096220010da            add      byte ptr [esi - 0x25efffde], dl 
  0x002898B6  06                      push     es                             
  0x002898B7  001a                    add      byte ptr [edx], bl             
  0x002898B9  0000                    add      byte ptr [eax], al             
  0x002898BB  0000                    add      byte ptr [eax], al             
  0x002898BD  b9f00010de              mov      ecx, 0xde1000f0                
  0x002898C2  06                      push     es                             
  0x002898C3  000a                    add      byte ptr [edx], cl             
  0x002898C5  0000                    add      byte ptr [eax], al             
  0x002898C7  00d4                    add      ah, dl                         
  0x002898C9  e145                    loope    0x289910                       
  0x002898CB  00d6                    add      dh, dl                         
  0x002898CD  39f0                    cmp      eax, esi                       
  0x002898CF  00e6                    add      dh, ah                         
  0x002898D1  a8f0                    test     al, 0xf0                       
  0x002898D3  00d2                    add      dl, dl                         
  0x002898D5  a1f400e259              mov      eax, dword ptr [0x59e200f4]    
  0x002898DA  44                      inc      esp                            
  0x002898DB  00e2                    add      dl, ah                         
  0x002898DD  a1d000d349              mov      eax, dword ptr [0x49d300d0]    
  0x002898E2  45                      inc      ebp                            
  0x002898E3  0000                    add      byte ptr [eax], al             
  0x002898E5  dd10                    fst      qword ptr [eax]                
  0x002898E7  0000                    add      byte ptr [eax], al             
  0x002898E9  4c                      dec      esp                            
  0x002898EA  44                      inc      esp                            
  0x002898EB  00d4                    add      ah, dl                         
  0x002898ED  e145                    loope    0x289934                       
  0x002898EF  00d6                    add      dh, dl                         
  0x002898F1  39f0                    cmp      eax, esi                       
  0x002898F3  00e6                    add      dh, ah                         
  0x002898F5  a8f0                    test     al, 0xf0                       
  0x002898F7  00d2                    add      dl, dl                         
  0x002898F9  a1f400e259              mov      eax, dword ptr [0x59e200f4]    
  0x002898FE  44                      inc      esp                            
  0x002898FF  00e2                    add      dl, ah                         
  0x00289901  a1f000d359              mov      eax, dword ptr [0x59d300f0]    
  0x00289906  45                      inc      ebp                            
  0x00289907  0000                    add      byte ptr [eax], al             
  0x00289909  4c                      dec      esp                            
  0x0028990A  56                      push     esi                            
  0x0028990B  008ef1030000            add      byte ptr [esi + 0x3f1], cl     
  0x00289911  d422                    aam      0x22                           
  0x00289913  0000                    add      byte ptr [eax], al             
  0x00289915  90                      nop                                     
  0x00289916  2200                    and      al, byte ptr [eax]             
  0x00289918  00982300a460            add      byte ptr [eax + 0x60a40023], bl 
  0x0028991E  0400                    add      al, 0                          
  0x00289920  0c00                    or       al, 0                          
  0x00289922  0000                    add      byte ptr [eax], al             
  0x00289924  00f4                    add      ah, dh                         
  0x00289926  7100                    jno      0x289928                       
  0x0028992A  ff00                    inc      dword ptr [eax]                
  0x0028992C  00f4                    add      ah, dh                         
  0x0028992E  7500                    jne      0x289930                       
                                        ; XREF: 0x0028992E (cond_jump)
  0x00289930  fc                      cld                                     
  0x00289932  ff00                    inc      dword ptr [eax]                
                                        ; XREF: 0x002898ED (cond_jump)
  0x00289934  0096220010da            add      byte ptr [esi - 0x25efffde], dl 
  0x0028993A  06                      push     es                             
  0x0028993B  0021                    add      byte ptr [ecx], ah             
  0x0028993D  0000                    add      byte ptr [eax], al             
  0x0028993F  0000                    add      byte ptr [eax], al             
  0x00289941  da5700                  ficom    dword ptr [edi]                
  0x00289944  00d2                    add      dl, dl                         
  0x00289946  51                      push     ecx                            
  0x00289947  0000                    add      byte ptr [eax], al             
  0x00289949  b9f00010de              mov      ecx, 0xde1000f0                
  0x0028994E  06                      push     es                             
  0x0028994F  000b                    add      byte ptr [ebx], cl             
  0x00289951  0000                    add      byte ptr [eax], al             
  0x00289953  00d4                    add      ah, dl                         
  0x00289955  e145                    loope    0x28999c                       
  0x00289957  00d6                    add      dh, dl                         
  0x00289959  39f0                    cmp      eax, esi                       
  0x0028995B  00e6                    add      dh, ah                         
  0x0028995D  a8f0                    test     al, 0xf0                       
  0x0028995F  00d2                    add      dl, dl                         
  0x00289961  a1f400e259              mov      eax, dword ptr [0x59e200f4]    
  0x00289966  44                      inc      esp                            
  0x00289967  00e2                    add      dl, ah                         
  0x00289969  a1d000d249              mov      eax, dword ptr [0x49d200d0]    
  0x0028996E  45                      inc      ebp                            
  0x0028996F  0010                    add      byte ptr [eax], dl             
  0x00289971  0020                    add      byte ptr [eax], ah             
  0x00289973  0009                    add      byte ptr [ecx], cl             
  0x00289975  dd10                    fst      qword ptr [eax]                
  0x00289977  004c4c44                add      byte ptr [esp + ecx*2 + 0x44], cl 
  0x0028997B  00d4                    add      ah, dl                         
  0x0028997D  e145                    loope    0x2899c4                       
  0x0028997F  00d6                    add      dh, dl                         
  0x00289981  39f0                    cmp      eax, esi                       
  0x00289983  00e6                    add      dh, ah                         
  0x00289985  a8f0                    test     al, 0xf0                       
  0x00289987  00d2                    add      dl, dl                         
  0x00289989  a1f400e259              mov      eax, dword ptr [0x59e200f4]    
  0x0028998E  44                      inc      esp                            
  0x0028998F  00e2                    add      dl, ah                         
  0x00289991  a1f000d259              mov      eax, dword ptr [0x59d200f0]    
  0x00289996  45                      inc      ebp                            
  0x00289997  0010                    add      byte ptr [eax], dl             
  0x00289999  0020                    add      byte ptr [eax], ah             
  0x0028999B  0009                    add      byte ptr [ecx], cl             
  0x0028999D  c421                    les      esp, ptr [ecx]                 
  0x0028999F  004c4c44                add      byte ptr [esp + ecx*2 + 0x44], cl 
  0x002899A3  0084f10300005a          add      byte ptr [ecx + esi*8 + 0x5a000003], al 
  0x002899AA  55                      push     ebp                            
  0x002899AB  0000                    add      byte ptr [eax], al             
  0x002899AD  5a                      pop      edx                            
  0x002899AE  51                      push     ecx                            
  0x002899AF  0000                    add      byte ptr [eax], al             
  0x002899B1  d422                    aam      0x22                           
  0x002899B3  0000                    add      byte ptr [eax], al             
  0x002899B5  90                      nop                                     
  0x002899B6  2200                    and      al, byte ptr [eax]             
  0x002899B8  00982300a460            add      byte ptr [eax + 0x60a40023], bl 
  0x002899BE  0400                    add      al, 0                          
  0x002899C0  0c00                    or       al, 0                          
  0x002899C2  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028997D (cond_jump)
  0x002899C4  00c8                    add      al, cl                         
  0x002899C6  44                      inc      esp                            
  0x002899C7  00a000200014            add      byte ptr [eax + 0x14002000], ah 
  0x002899CD  c8440011                enter    0x44, 0x11                     
  0x002899D1  0020                    add      byte ptr [eax], ah             
  0x002899D3  0010                    add      byte ptr [eax], dl             
  0x002899D5  de06                    fiadd    word ptr [esi]                 
  0x002899D7  0005000000a0            add      byte ptr [0xa0000000], al      
  0x002899DD  0c18                    or       al, 0x18                       
  0x002899DF  00bac8440014            add      byte ptr [edx + 0x140044c8], bh 
  0x002899E5  0020                    add      byte ptr [eax], ah             
  0x002899E7  0011                    add      byte ptr [ecx], dl             
  0x002899E9  0020                    add      byte ptr [eax], ah             
  0x002899EB  0000                    add      byte ptr [eax], al             
  0x002899ED  2418                    and      al, 0x18                       
  0x002899EF  00ba0020000c            add      byte ptr [edx + 0xc002000], bh 
  0x002899F5  0000                    add      byte ptr [eax], al             
  0x002899F7  0013                    add      byte ptr [ebx], dl             
  0x002899F9  c84600e1                enter    0x46, -0x1f                    
  0x002899FD  0020                    add      byte ptr [eax], ah             
  0x002899FF  0010                    add      byte ptr [eax], dl             
  0x00289A01  de06                    fiadd    word ptr [esi]                 
  0x00289A03  0003                    add      byte ptr [ebx], al             
  0x00289A05  0000                    add      byte ptr [eax], al             
  0x00289A07  0000                    add      byte ptr [eax], al             
  0x00289A09  c84600e1                enter    0x46, -0x1f                    
  0x00289A0D  4c                      dec      esp                            
  0x00289A0E  56                      push     esi                            
  0x00289A0F  0000                    add      byte ptr [eax], al             
  0x00289A11  6456                    push     esi                            
  0x00289A13  000c00                  add      byte ptr [eax + eax], cl       
  0x00289A16  0000                    add      byte ptr [eax], al             
  0x00289A18  004039                  add      byte ptr [eax + 0x39], al      
  0x00289A1B  0000                    add      byte ptr [eax], al             
  0x00289A1D  3d23000049              cmp      eax, 0x49000023                
  0x00289A22  2000                    and      byte ptr [eax], al             
  0x00289A24  004d20                  add      byte ptr [ebp + 0x20], cl      
  0x00289A27  0012                    add      byte ptr [edx], dl             
  0x00289A29  51                      push     ecx                            
  0x00289A2A  0400                    add      al, 0                          
  0x00289A2C  16                      push     ss                             
  0x00289A2D  55                      push     ebp                            
  0x00289A2E  0400                    add      al, 0                          
  0x00289A30  10d9                    adc      cl, bl                         
  0x00289A32  06                      push     es                             
  0x00289A33  000400                  add      byte ptr [eax + eax], al       
  0x00289A36  0000                    add      byte ptr [eax], al             
  0x00289A38  00d9                    add      cl, bl                         
  0x00289A3A  46                      inc      esi                            
  0x00289A3B  0000                    add      byte ptr [eax], al             
  0x00289A3D  b2b0                    mov      dl, 0xb0                       
  0x00289A3F  0000                    add      byte ptr [eax], al             
  0x00289A41  56                      push     esi                            
  0x00289A42  44                      inc      esp                            
  0x00289A43  0000                    add      byte ptr [eax], al             
  0x00289A46  3800                    cmp      byte ptr [eax], al             
  0x00289A48  001c23                  add      byte ptr [ebx], bl             
  0x00289A4B  0000                    add      byte ptr [eax], al             
  0x00289A4D  41                      inc      ecx                            
  0x00289A4E  2000                    and      byte ptr [eax], al             
  0x00289A50  004520                  add      byte ptr [ebp + 0x20], al      
  0x00289A53  0012                    add      byte ptr [edx], dl             
  0x00289A55  48                      dec      eax                            
  0x00289A56  0400                    add      al, 0                          
  0x00289A58  16                      push     ss                             
  0x00289A59  4c                      dec      esp                            
  0x00289A5A  0400                    add      al, 0                          
  0x00289A5C  0002                    add      byte ptr [edx], al             
  0x00289A5E  3800                    cmp      byte ptr [eax], al             
  0x00289A60  00f4                    add      ah, dh                         
  0x00289A62  7200                    jb       0x289a64                       
  0x00289A66  ff00                    inc      dword ptr [eax]                
  0x00289A68  0002                    add      byte ptr [edx], al             
  0x00289A6A  3c00                    cmp      al, 0                          
  0x00289A6C  00f4                    add      ah, dh                         
  0x00289A6E  7600                    jbe      0x289a70                       
  0x00289A72  ff00                    inc      dword ptr [eax]                
  0x00289A74  0088d000d4ca            add      byte ptr [eax - 0x352bff30], cl 
  0x00289A7A  d500                    aad      0                              
  0x00289A7C  f30020                  add      byte ptr [eax], ah             
  0x00289A7F  00c8                    add      al, cl                         
  0x00289A81  59                      pop      ecx                            
  0x00289A82  56                      push     esi                            
  0x00289A83  00eb                    add      bl, ch                         
  0x00289A85  88d0                    mov      al, dl                         
  0x00289A87  00903f060005            add      byte ptr [eax + 0x500063f], dl 
  0x00289A8D  0000                    add      byte ptr [eax], al             
  0x00289A8F  00d4                    add      ah, dl                         
  0x00289A91  cad500                  retf     0xd5                           
  0x00289A94  f35d                    pop      ebp                            
  0x00289A96  57                      push     edi                            
  0x00289A97  00c8                    add      al, cl                         
  0x00289A99  59                      pop      ecx                            
  0x00289A9A  56                      push     esi                            
  0x00289A9B  00eb                    add      bl, ch                         
  0x00289A9D  88d0                    mov      al, dl                         
  0x00289A9F  0000                    add      byte ptr [eax], al             
  0x00289AA1  5d                      pop      ebp                            
  0x00289AA2  57                      push     edi                            
  0x00289AA3  0000                    add      byte ptr [eax], al             
  0x00289AA5  40                      inc      eax                            
  0x00289AA6  2000                    and      byte ptr [eax], al             
  0x00289AA8  00442000                add      byte ptr [eax], al             
  0x00289AAC  007f38                  add      byte ptr [edi + 0x38], bh      
  0x00289AAF  0000                    add      byte ptr [eax], al             
  0x00289AB1  1a23                    sbb      ah, byte ptr [ebx]             
  0x00289AB3  0000                    add      byte ptr [eax], al             
  0x00289AB5  1c23                    sbb      al, 0x23                       
  0x00289AB7  0000                    add      byte ptr [eax], al             
  0x00289AB9  1e                      push     ds                             
  0x00289ABA  2300                    and      eax, dword ptr [eax]           
  0x00289ABC  004120                  add      byte ptr [ecx + 0x20], al      
  0x00289ABF  0000                    add      byte ptr [eax], al             
  0x00289AC1  45                      inc      ebp                            
  0x00289AC2  2000                    and      byte ptr [eax], al             
  0x00289AC4  004020                  add      byte ptr [eax + 0x20], al      
  0x00289AC7  0000                    add      byte ptr [eax], al             
  0x00289AC9  4a                      dec      edx                            
  0x00289ACA  2000                    and      byte ptr [eax], al             
  0x00289ACC  00442000                add      byte ptr [eax], al             
  0x00289AD0  004e20                  add      byte ptr [esi + 0x20], cl      
  0x00289AD3  0000                    add      byte ptr [eax], al             
  0x00289AD5  0238                    add      bh, byte ptr [eax]             
  0x00289AD7  0000                    add      byte ptr [eax], al             
  0x00289AD9  f4                      hlt                                     
  0x00289ADA  7200                    jb       0x289adc                       
  0x00289ADE  ff00                    inc      dword ptr [eax]                
  0x00289AE0  0002                    add      byte ptr [edx], al             
  0x00289AE2  3c00                    cmp      al, 0                          
  0x00289AE4  00f4                    add      ah, dh                         
  0x00289AE6  7600                    jbe      0x289ae8                       
  0x00289AEA  ff00                    inc      dword ptr [eax]                
  0x00289AEC  0088d000d4ca            add      byte ptr [eax - 0x352bff30], cl 
  0x00289AF2  d500                    aad      0                              
  0x00289AF4  f30020                  add      byte ptr [eax], ah             
  0x00289AF7  00c8                    add      al, cl                         
  0x00289AF9  7956                    jns      0x289b51                       
  0x00289AFB  00eb                    add      bl, ch                         
  0x00289AFD  88d0                    mov      al, dl                         
  0x00289AFF  00903f060005            add      byte ptr [eax + 0x500063f], dl 
  0x00289B05  0000                    add      byte ptr [eax], al             
  0x00289B07  00d4                    add      ah, dl                         
  0x00289B09  cad500                  retf     0xd5                           
  0x00289B0C  f37d5f                  jge      0x289b6e                       
  0x00289B0F  00c8                    add      al, cl                         
  0x00289B11  7956                    jns      0x289b69                       
  0x00289B13  00eb                    add      bl, ch                         
  0x00289B15  88d0                    mov      al, dl                         
  0x00289B17  0000                    add      byte ptr [eax], al             
  0x00289B19  7d5f                    jge      0x289b7a                       
  0x00289B1B  000c00                  add      byte ptr [eax + eax], cl       
  0x00289B1E  0000                    add      byte ptr [eax], al             
  0x00289B20  00c0                    add      al, al                         
  0x00289B22  f1                      int1                                    
  0x00289B23  0000                    add      byte ptr [eax], al             
  0x00289B25  da4d00                  fimul    dword ptr [ebp]                
  0x00289B28  c8d84e00                enter    0x4ed8, 0                      
  0x00289B2C  eb00                    jmp      0x289b2e                       
                                        ; XREF: 0x00289B2C (jump)
  0x00289B2E  2000                    and      byte ptr [eax], al             
  0x00289B30  b064                    mov      al, 0x64                       
  0x00289B32  5f                      pop      edi                            
  0x00289B33  0010                    add      byte ptr [eax], dl             
  0x00289B35  da06                    fiadd    dword ptr [esi]                
  0x00289B37  0006                    add      byte ptr [esi], al             
  0x00289B39  0000                    add      byte ptr [eax], al             
  0x00289B3B  00a7c0f10000            add      byte ptr [edi + 0xf1c0], ah    
  0x00289B41  da4d00                  fimul    dword ptr [ebp]                
  0x00289B44  c8d84e00                enter    0x4ed8, 0                      
  0x00289B48  eb5c                    jmp      0x289ba6                       
  0x00289B4A  56                      push     esi                            
  0x00289B4B  00b0645f00a7            add      byte ptr [eax - 0x58ffa09c], dh 
                                        ; XREF: 0x00289AF9 (cond_jump)
  0x00289B51  0020                    add      byte ptr [eax], ah             
  0x00289B53  0000                    add      byte ptr [eax], al             
  0x00289B55  5c                      pop      esp                            
  0x00289B56  56                      push     esi                            
  0x00289B57  000c00                  add      byte ptr [eax + eax], cl       
  0x00289B5A  0000                    add      byte ptr [eax], al             
  0x00289B5C  00c0                    add      al, al                         
  0x00289B5E  f1                      int1                                    
  0x00289B5F  0000                    add      byte ptr [eax], al             
  0x00289B61  da4d00                  fimul    dword ptr [ebp]                
  0x00289B64  c8e14e00                enter    0x4ee1, 0                      
  0x00289B68  eb00                    jmp      0x289b6a                       
                                        ; XREF: 0x00289B68 (jump)
  0x00289B6A  2000                    and      byte ptr [eax], al             
  0x00289B6C  b0d8                    mov      al, 0xd8                       
                                        ; XREF: 0x00289B0C (cond_jump)
  0x00289B6E  4e                      dec      esi                            
  0x00289B6F  00a7d94400c8            add      byte ptr [edi - 0x37ffbb27], ah 
  0x00289B75  645f                    pop      edi                            
  0x00289B77  00eb                    add      bl, ch                         
  0x00289B79  5c                      pop      esp                            
                                        ; XREF: 0x00289B19 (cond_jump)
  0x00289B7A  56                      push     esi                            
  0x00289B7B  00b0655f0010            add      byte ptr [eax + 0x10005f65], dh 
  0x00289B81  da06                    fiadd    dword ptr [esi]                
  0x00289B83  000a                    add      byte ptr [edx], cl             
  0x00289B85  0000                    add      byte ptr [eax], al             
  0x00289B87  00a7c0f10000            add      byte ptr [edi + 0xf1c0], ah    
  0x00289B8D  da4d00                  fimul    dword ptr [ebp]                
  0x00289B90  c8e14e00                enter    0x4ee1, 0                      
  0x00289B94  eb5d                    jmp      0x289bf3                       
  0x00289B96  56                      push     esi                            
  0x00289B97  00b0d84e00a7            add      byte ptr [eax - 0x58ffb128], dh 
  0x00289B9D  d94400c8                fld      dword ptr [eax + eax - 0x38]   
  0x00289BA1  645f                    pop      edi                            
  0x00289BA3  00eb                    add      bl, ch                         
  0x00289BA5  5c                      pop      esp                            
                                        ; XREF: 0x00289B48 (jump)
  0x00289BA6  56                      push     esi                            
  0x00289BA7  00b0655f00a7            add      byte ptr [eax - 0x58ffa09b], dh 
  0x00289BAD  0020                    add      byte ptr [eax], ah             
  0x00289BAF  0000                    add      byte ptr [eax], al             
  0x00289BB1  5d                      pop      ebp                            
  0x00289BB2  56                      push     esi                            
  0x00289BB3  000c00                  add      byte ptr [eax + eax], cl       
  0x00289BB6  0000                    add      byte ptr [eax], al             
  0x00289BB8  00c0                    add      al, al                         
  0x00289BBA  f1                      int1                                    
  0x00289BBB  0000                    add      byte ptr [eax], al             
  0x00289BBD  da4d00                  fimul    dword ptr [ebp]                
  0x00289BC0  a8c8                    test     al, 0xc8                       
  0x00289BC2  4e                      dec      esi                            
  0x00289BC3  00bb002000e0            add      byte ptr [ebx - 0x1fffe000], bh 
  0x00289BC9  4d                      dec      ebp                            
  0x00289BCA  57                      push     edi                            
  0x00289BCB  0010                    add      byte ptr [eax], dl             
  0x00289BCD  da06                    fiadd    dword ptr [esi]                
  0x00289BCF  0006                    add      byte ptr [esi], al             
  0x00289BD1  0000                    add      byte ptr [eax], al             
  0x00289BD3  00c7                    add      bh, al                         
  0x00289BD5  c0f100                  sal      cl, 0                          
  0x00289BD8  00da                    add      dl, bl                         
  0x00289BDA  4d                      dec      ebp                            
  0x00289BDB  00a8c84e00bb            add      byte ptr [eax - 0x44ffb138], ch 
  0x00289BE1  4c                      dec      esp                            
  0x00289BE2  56                      push     esi                            
  0x00289BE3  00e0                    add      al, ah                         
  0x00289BE5  4d                      dec      ebp                            
  0x00289BE6  57                      push     edi                            
  0x00289BE7  00c7                    add      bh, al                         
  0x00289BE9  0020                    add      byte ptr [eax], ah             
  0x00289BEB  0000                    add      byte ptr [eax], al             
  0x00289BED  4c                      dec      esp                            
  0x00289BEE  56                      push     esi                            
  0x00289BEF  000c00                  add      byte ptr [eax + eax], cl       
  0x00289BF2  0000                    add      byte ptr [eax], al             
  0x00289BF4  00c1                    add      cl, al                         
  0x00289BF6  f1                      int1                                    
  0x00289BF7  0000                    add      byte ptr [eax], al             
  0x00289BF9  da4d00                  fimul    dword ptr [ebp]                
  0x00289BFC  a8e1                    test     al, 0xe1                       
  0x00289BFE  4e                      dec      esi                            
  0x00289BFF  00bbe04e00e0            add      byte ptr [ebx - 0x1fffb120], bh 
  0x00289C05  c84400c7                enter    0x44, -0x39                    
  0x00289C09  55                      push     ebp                            
  0x00289C0A  57                      push     edi                            
  0x00289C0B  00b8e14e00ab            add      byte ptr [eax - 0x54ffb11f], bh 
  0x00289C11  5c                      pop      esp                            
  0x00289C12  56                      push     esi                            
  0x00289C13  00e0                    add      al, ah                         
  0x00289C15  c9                      leave                                   
  0x00289C16  44                      inc      esp                            
  0x00289C17  00c7                    add      bh, al                         
  0x00289C19  4d                      dec      ebp                            
  0x00289C1A  57                      push     edi                            
  0x00289C1B  0010                    add      byte ptr [eax], dl             
  0x00289C1D  da06                    fiadd    dword ptr [esi]                
  0x00289C1F  000b                    add      byte ptr [ebx], cl             
  0x00289C21  0000                    add      byte ptr [eax], al             
  0x00289C23  0000                    add      byte ptr [eax], al             
  0x00289C25  c1f100                  sal      ecx, 0                         
  0x00289C28  00da                    add      dl, bl                         
  0x00289C2A  4d                      dec      ebp                            
  0x00289C2B  00a8e14e00bb            add      byte ptr [eax - 0x44ffb11f], ch 
  0x00289C31  0cc8                    or       al, 0xc8                       
  0x00289C33  00e0                    add      al, ah                         
  0x00289C35  c84400c7                enter    0x44, -0x39                    
  0x00289C39  55                      push     ebp                            
  0x00289C3A  57                      push     edi                            
  0x00289C3B  00b8e14e00ab            add      byte ptr [eax - 0x54ffb11f], bh 
  0x00289C41  5c                      pop      esp                            
  0x00289C42  56                      push     esi                            
  0x00289C43  00e0                    add      al, ah                         
  0x00289C45  c9                      leave                                   
  0x00289C46  44                      inc      esp                            
  0x00289C47  00c7                    add      bh, al                         
  0x00289C49  4d                      dec      ebp                            
  0x00289C4A  57                      push     edi                            
  0x00289C4B  0000                    add      byte ptr [eax], al             
  0x00289C4D  4c                      dec      esp                            
  0x00289C4E  56                      push     esi                            
  0x00289C4F  000c00                  add      byte ptr [eax + eax], cl       
  0x00289C52  0000                    add      byte ptr [eax], al             
  0x00289C54  00d8                    add      al, bl                         
  0x00289C56  56                      push     esi                            
  0x00289C57  0010                    add      byte ptr [eax], dl             
  0x00289C59  d906                    fld      dword ptr [esi]                
  0x00289C5B  0007                    add      byte ptr [edi], al             
  0x00289C5D  0000                    add      byte ptr [eax], al             
  0x00289C5F  0001                    add      byte ptr [ecx], al             
  0x00289C61  1e                      push     ds                             
  0x00289C62  0c00                    or       al, 0                          
  0x00289C64  3e0020                  add      byte ptr ds:[eax], ah          
  0x00289C67  0003                    add      byte ptr [ebx], al             
  0x00289C69  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00289C6A  2300                    and      eax, dword ptr [eax]           
  0x00289C6C  48                      dec      eax                            
  0x00289C6D  a0020000d8              mov      al, byte ptr [0xd8000002]      
  0x00289C72  56                      push     esi                            
  0x00289C73  0000                    add      byte ptr [eax], al             
  0x00289C75  59                      pop      ecx                            
  0x00289C76  57                      push     edi                            
  0x00289C77  0000                    add      byte ptr [eax], al             
  0x00289C79  50                      push     eax                            
  0x00289C7A  2000                    and      byte ptr [eax], al             
  0x00289C7C  0c00                    or       al, 0                          
  0x00289C7E  0000                    add      byte ptr [eax], al             
  0x00289C80  00f4                    add      ah, dh                         
  0x00289C82  46                      inc      esi                            
  0x00289C83  0001                    add      byte ptr [ecx], al             
  0x00289C85  0000                    add      byte ptr [eax], al             
  0x00289C87  0000                    add      byte ptr [eax], al             
  0x00289C89  ae                      scasb    al, byte ptr es:[edi]          
  0x00289C8A  2300                    and      eax, dword ptr [eax]           
  0x00289C8C  55                      push     ebp                            
  0x00289C8D  3522000da4              xor      eax, 0xa40d0022                
  0x00289C92  050000b422              add      eax, 0x22b40000                
  0x00289C97  0010                    add      byte ptr [eax], dl             
  0x00289C99  dc06                    fadd     qword ptr [esi]                
  0x00289C9B  0009                    add      byte ptr [ecx], cl             
  0x00289C9D  0000                    add      byte ptr [eax], al             
  0x00289C9F  0000                    add      byte ptr [eax], al             
  0x00289CA1  f4                      hlt                                     
  0x00289CA2  56                      push     esi                            
  0x00289CA3  00ff                    add      bh, bh                         
  0x00289CA6  7f00                    jg       0x289ca8                       
                                        ; XREF: 0x00289CA6 (cond_jump)
  0x00289CA8  10dd                    adc      ch, bl                         
  0x00289CAA  06                      push     es                             
  0x00289CAB  000400                  add      byte ptr [eax + eax], al       
  0x00289CAE  0000                    add      byte ptr [eax], al             
  0x00289CB0  00dc                    add      ah, bl                         
  0x00289CB2  44                      inc      esp                            
  0x00289CB3  004500                  add      byte ptr [ebp], al             
  0x00289CB6  2000                    and      byte ptr [eax], al             
  0x00289CB8  40                      inc      eax                            
  0x00289CB9  7002                    jo       0x289cbd                       
  0x00289CBB  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x00289CB9 (cond_jump)
  0x00289CBD  4d                      dec      ebp                            
  0x00289CBE  54                      push     esp                            
  0x00289CBF  0000                    add      byte ptr [eax], al             
  0x00289CC1  352200004f              xor      eax, 0x4f000022                
  0x00289CC6  2300                    and      eax, dword ptr [eax]           
  0x00289CC8  0be2                    or       esp, edx                       
  0x00289CCA  56                      push     esi                            
  0x00289CCB  0006                    add      byte ptr [esi], al             
  0x00289CCD  2405                    and      al, 5                          
  0x00289CCF  0000                    add      byte ptr [eax], al             
  0x00289CD1  f4                      hlt                                     
  0x00289CD2  44                      inc      esp                            
  0x00289CD3  000f                    add      byte ptr [edi], cl             
  0x00289CD5  0000                    add      byte ptr [eax], al             
  0x00289CD7  004500                  add      byte ptr [ebp], al             
  0x00289CDA  2000                    and      byte ptr [eax], al             
  0x00289CDC  40                      inc      eax                            
  0x00289CDD  7002                    jo       0x289ce1                       
  0x00289CDF  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x00289CDD (cond_jump)
  0x00289CE1  62540000                bound    edx, qword ptr [eax + eax]     
  0x00289CE5  8521                    test     dword ptr [ecx], esp           
  0x00289CE7  0010                    add      byte ptr [eax], dl             
  0x00289CE9  dc06                    fadd     qword ptr [esi]                
  0x00289CEB  000400                  add      byte ptr [eax + eax], al       
  0x00289CEE  0000                    add      byte ptr [eax], al             
  0x00289CF0  00e5                    add      ch, ah                         
  0x00289CF2  56                      push     esi                            
  0x00289CF3  00648521                add      byte ptr [ebp + eax*4 + 0x21], ah 
  0x00289CF7  0000                    add      byte ptr [eax], al             
  0x00289CF9  4d                      dec      ebp                            
  0x00289CFA  54                      push     esp                            
  0x00289CFB  0000                    add      byte ptr [eax], al             
  0x00289CFD  3522005987              xor      eax, 0x87590022                
  0x00289D02  2300                    and      eax, dword ptr [eax]           
  0x00289D04  00f4                    add      ah, dh                         
  0x00289D06  45                      inc      ebp                            
  0x00289D07  0002                    add      byte ptr [edx], al             
  0x00289D09  0000                    add      byte ptr [eax], al             
  0x00289D0B  0000                    add      byte ptr [eax], al             
  0x00289D0D  e556                    in       eax, 0x56                      
  0x00289D0F  0065f4                  add      byte ptr [ebp - 0xc], ah       
  0x00289D12  45                      inc      ebp                            
  0x00289D13  00fe                    add      dh, bh                         
  0x00289D16  ff00                    inc      dword ptr [eax]                
  0x00289D18  17                      pop      ss                             
  0x00289D19  7405                    je       0x289d20                       
  0x00289D1B  0065f4                  add      byte ptr [ebp - 0xc], ah       
  0x00289D1E  45                      inc      ebp                            
  0x00289D1F  0002                    add      byte ptr [edx], al             
  0x00289D21  0000                    add      byte ptr [eax], al             
  0x00289D23  0011                    add      byte ptr [ecx], dl             
  0x00289D25  94                      xchg     esp, eax                       
  0x00289D26  0500584d20              add      eax, 0x204d5800                
  0x00289D2B  007d00                  add      byte ptr [ebp], bh             
  0x00289D2E  2000                    and      byte ptr [eax], al             
  0x00289D30  4d                      dec      ebp                            
  0x00289D31  7405                    je       0x289d38                       
  0x00289D33  00d6                    add      dh, dl                         
  0x00289D35  97                      xchg     edi, eax                       
  0x00289D36  050000e556              add      eax, 0x56e50000                
  0x00289D3B  0065f4                  add      byte ptr [ebp - 0xc], ah       
  0x00289D3E  45                      inc      ebp                            
  0x00289D3F  00fe                    add      dh, bh                         
  0x00289D42  ff00                    inc      dword ptr [eax]                
  0x00289D44  13740500                adc      esi, dword ptr [ebp + eax]     
  0x00289D48  65f4                    hlt                                     
  0x00289D4A  45                      inc      ebp                            
  0x00289D4B  0002                    add      byte ptr [edx], al             
  0x00289D4D  0000                    add      byte ptr [eax], al             
  0x00289D4F  0006                    add      byte ptr [esi], al             
  0x00289D51  94                      xchg     esp, eax                       
  0x00289D52  0500584d20              add      eax, 0x204d5800                
  0x00289D57  007d00                  add      byte ptr [ebp], bh             
  0x00289D5A  2000                    and      byte ptr [eax], al             
  0x00289D5C  42                      inc      edx                            
  0x00289D5D  7405                    je       0x289d64                       
  0x00289D5F  00cb                    add      bl, cl                         
  0x00289D61  97                      xchg     edi, eax                       
  0x00289D62  0500d5a705              add      eax, 0x5a7d500                 
  0x00289D67  005c4520                add      byte ptr [ebp + eax*2 + 0x20], bl 
  0x00289D6B  000da4050000            add      byte ptr [0x5a4], cl           
  0x00289D71  e556                    in       eax, 0x56                      
  0x00289D73  00540020                add      byte ptr [eax + eax + 0x20], dl 
  0x00289D77  0000                    add      byte ptr [eax], al             
  0x00289D79  4d                      dec      ebp                            
  0x00289D7A  54                      push     esp                            
  0x00289D7B  0000                    add      byte ptr [eax], al             
  0x00289D7D  e556                    in       eax, 0x56                      
  0x00289D7F  0050f4                  add      byte ptr [eax - 0xc], dl       
  0x00289D82  45                      inc      ebp                            
  0x00289D83  0002                    add      byte ptr [edx], al             
  0x00289D85  0000                    add      byte ptr [eax], al             
  0x00289D87  0000                    add      byte ptr [eax], al             
  0x00289D89  45                      inc      ebp                            
  0x00289D8A  54                      push     esp                            
  0x00289D8B  00c0                    add      al, al                         
  0x00289D8D  0f05                    syscall                                 
  0x00289D8F  0054f445                add      byte ptr [esp + esi*8 + 0x45], dl 
  0x00289D93  0002                    add      byte ptr [edx], al             
  0x00289D95  0000                    add      byte ptr [eax], al             
  0x00289D97  0000                    add      byte ptr [eax], al             
  0x00289D99  6554                    push     esp                            
  0x00289D9B  00c7                    add      bh, al                         
  0x00289D9D  0f05                    syscall                                 
  0x00289D9F  0000                    add      byte ptr [eax], al             
  0x00289DA1  4e                      dec      esi                            
  0x00289DA2  2300                    and      eax, dword ptr [eax]           
  0x00289DA4  034d20                  add      ecx, dword ptr [ebp + 0x20]    
  0x00289DA7  0007                    add      byte ptr [edi], al             
  0x00289DA9  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00289DAA  050000e256              add      eax, 0x56e20000                
  0x00289DAF  00540020                add      byte ptr [eax + eax + 0x20], dl 
  0x00289DB3  0000                    add      byte ptr [eax], al             
  0x00289DB5  62540000                bound    edx, qword ptr [eax + eax]     
  0x00289DB9  e556                    in       eax, 0x56                      
  0x00289DBB  005000                  add      byte ptr [eax], dl             
  0x00289DBE  2000                    and      byte ptr [eax], al             
  0x00289DC0  006554                  add      byte ptr [ebp + 0x54], ah      
  0x00289DC3  0000                    add      byte ptr [eax], al             
  0x00289DC5  e256                    loop     0x289e1d                       
  0x00289DC7  00540020                add      byte ptr [eax + eax + 0x20], dl 
  0x00289DCB  0000                    add      byte ptr [eax], al             
  0x00289DCD  62540000                bound    edx, qword ptr [eax + eax]     
  0x00289DD1  e556                    in       eax, 0x56                      
  0x00289DD3  0050f4                  add      byte ptr [eax - 0xc], dl       
  0x00289DD6  45                      inc      ebp                            
  0x00289DD7  0002                    add      byte ptr [edx], al             
  0x00289DD9  0000                    add      byte ptr [eax], al             
  0x00289DDB  005865                  add      byte ptr [eax + 0x65], bl      
  0x00289DDE  54                      push     esp                            
  0x00289DDF  008b0f050000            add      byte ptr [ebx + 0x50f], cl     
  0x00289DE5  35220000e2              xor      eax, 0xe2000022                
  0x00289DEA  45                      inc      ebp                            
  0x00289DEB  0010                    add      byte ptr [eax], dl             
  0x00289DED  dc06                    fadd     qword ptr [esi]                
  0x00289DEF  000500000000            add      byte ptr [0], al               
  0x00289DF5  e556                    in       eax, 0x56                      
  0x00289DF7  006000                  add      byte ptr [eax], ah             
  0x00289DFA  2000                    and      byte ptr [eax], al             
  0x00289DFC  00852100004d            add      byte ptr [ebp + 0x4d000021], al 
  0x00289E02  54                      push     esp                            
  0x00289E03  0000                    add      byte ptr [eax], al             
  0x00289E05  ae                      scasb    al, byte ptr es:[edi]          
  0x00289E06  2300                    and      eax, dword ptr [eax]           
  0x00289E08  55                      push     ebp                            
  0x00289E09  35220009a4              xor      eax, 0xa4090022                
  0x00289E0E  050000b422              add      eax, 0x22b40000                
  0x00289E13  0010                    add      byte ptr [eax], dl             
  0x00289E15  dc06                    fadd     qword ptr [esi]                
  0x00289E17  0006                    add      byte ptr [esi], al             
  0x00289E19  0000                    add      byte ptr [eax], al             
  0x00289E1B  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x00289DC5 (cond_jump)
  0x00289E1D  cd44                    int      0x44                           
  0x00289E1F  0010                    add      byte ptr [eax], dl             
  0x00289E21  dd06                    fld      qword ptr [esi]                
  0x00289E23  0002                    add      byte ptr [edx], al             
  0x00289E25  0000                    add      byte ptr [eax], al             
  0x00289E27  0000                    add      byte ptr [eax], al             
  0x00289E29  5c                      pop      esp                            
  0x00289E2A  44                      inc      esp                            
  0x00289E2B  0000                    add      byte ptr [eax], al             
  0x00289E2D  0000                    add      byte ptr [eax], al             
  0x00289E2F  000c00                  add      byte ptr [eax + eax], cl       
  0x00289E32  0000                    add      byte ptr [eax], al             
  0x00289E34  00f0                    add      al, dh                         
  0x00289E36  44                      inc      esp                            
  0x00289E37  00410b                  add      byte ptr [ecx + 0xb], al       
  0x00289E3A  0000                    add      byte ptr [eax], al             
  0x00289E3C  00f0                    add      al, dh                         
  0x00289E3E  56                      push     esi                            
  0x00289E3F  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x00289E45  0020                    add      byte ptr [eax], ah             
  0x00289E47  0013                    add      byte ptr [ebx], dl             
  0x00289E49  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00289E4A  0500009620              add      eax, 0x20960000                
  0x00289E4F  0000                    add      byte ptr [eax], al             
  0x00289E51  f4                      hlt                                     
  0x00289E52  60                      pushal                                  
  0x00289E53  008001000000            add      byte ptr [eax + 1], al         
  0x00289E59  f4                      hlt                                     
  0x00289E5A  61                      popal                                   
  0x00289E5B  004102                  add      byte ptr [ecx + 2], al         
  0x00289E5E  0000                    add      byte ptr [eax], al             
  0x00289E60  00f4                    add      ah, dh                         
  0x00289E62  56                      push     esi                            
  0x00289E63  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x00289E69  c422                    les      esp, ptr [edx]                 
  0x00289E6B  004000                  add      byte ptr [eax], al             
  0x00289E6E  2000                    and      byte ptr [eax], al             
  0x00289E70  0092210000e2            add      byte ptr [edx - 0x1dffffdf], dl 
  0x00289E76  7100                    jno      0x289e78                       
                                        ; XREF: 0x00289E76 (cond_jump)
  0x00289E78  10d9                    adc      cl, bl                         
  0x00289E7A  06                      push     es                             
  0x00289E7B  000500000000            add      byte ptr [0], al               
  0x00289E81  d9440000                fld      dword ptr [eax + eax]          
  0x00289E85  e056                    loopne   0x289edd                       
  0x00289E87  00481e                  add      byte ptr [eax + 0x1e], cl      
  0x00289E8A  0c00                    or       al, 0                          
  0x00289E8C  005854                  add      byte ptr [eax + 0x54], bl      
  0x00289E8F  0010                    add      byte ptr [eax], dl             
  0x00289E91  0c05                    or       al, 5                          
  0x00289E93  0000                    add      byte ptr [eax], al             
  0x00289E96  56                      push     esi                            
  0x00289E97  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x00289E9A  0000                    add      byte ptr [eax], al             
  0x00289E9C  0300                    add      eax, dword ptr [eax]           
  0x00289E9E  2000                    and      byte ptr [eax], al             
  0x00289EA0  0ca4                    or       al, 0xa4                       
  0x00289EA2  050000f460              add      eax, 0x60f40000                
  0x00289EA7  003502000000            add      byte ptr [2], dh               
  0x00289EAD  f4                      hlt                                     
  0x00289EAE  61                      popal                                   
  0x00289EAF  00f6                    add      dh, dh                         
  0x00289EB1  0200                    add      al, byte ptr [eax]             
  0x00289EB3  0000                    add      byte ptr [eax], al             
  0x00289EB5  07                      pop      es                             
  0x00289EB6  3900                    cmp      dword ptr [eax], eax           
  0x00289EB8  10d9                    adc      cl, bl                         
  0x00289EBA  06                      push     es                             
  0x00289EBB  000500000000            add      byte ptr [0], al               
  0x00289EC1  d9440000                fld      dword ptr [eax + eax]          
  0x00289EC5  e056                    loopne   0x289f1d                       
  0x00289EC7  00481e                  add      byte ptr [eax + 0x1e], cl      
  0x00289ECA  0c00                    or       al, 0                          
  0x00289ECC  005854                  add      byte ptr [eax + 0x54], bl      
  0x00289ECF  000c00                  add      byte ptr [eax + eax], cl       
  0x00289ED2  0000                    add      byte ptr [eax], al             
  0x00289ED4  20f4                    and      ah, dh                         
  0x00289ED6  0500ffffff              add      eax, 0xffffff00                
  0x00289EDB  00a0610400a0            add      byte ptr [eax - 0x5ffffb9f], ah 
  0x00289EE1  620400                  bound    eax, qword ptr [eax + eax]     
  0x00289EE4  a0640400a0              mov      al, byte ptr [0xa0000464]      
  0x00289EE9  650400                  add      al, 0                          
  0x00289EEC  a0660400b8              mov      al, byte ptr [0xb8000466]      
  0x00289EF1  f30000                  add      byte ptr [eax], al             
  0x00289EF4  00f4                    add      ah, dh                         
  0x00289EF6  44                      inc      esp                            
  0x00289EF7  0000                    add      byte ptr [eax], al             
  0x00289EF9  0000                    add      byte ptr [eax], al             
  0x00289EFB  004d00                  add      byte ptr [ebp], cl             
  0x00289EFE  2000                    and      byte ptr [eax], al             
  0x00289F00  0ca4                    or       al, 0xa4                       
  0x00289F02  050000f444              add      eax, 0x44f40000                
  0x00289F07  0010                    add      byte ptr [eax], dl             
  0x00289F09  0000                    add      byte ptr [eax], al             
  0x00289F0B  004d00                  add      byte ptr [ebp], cl             
  0x00289F0E  2000                    and      byte ptr [eax], al             
  0x00289F10  4a                      dec      edx                            
  0x00289F11  100d00110000            adc      byte ptr [0x1100], cl          
  0x00289F17  0000                    add      byte ptr [eax], al             
  0x00289F19  0030                    add      byte ptr [eax], dh             
  0x00289F1B  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x00289EC5 (cond_jump)
  0x00289F1D  f4                      hlt                                     
  0x00289F1E  56                      push     esi                            
  0x00289F1F  0000                    add      byte ptr [eax], al             
  0x00289F21  0000                    add      byte ptr [eax], al             
  0x00289F23  0000                    add      byte ptr [eax], al             
  0x00289F25  f4                      hlt                                     
  0x00289F26  57                      push     edi                            
  0x00289F27  00ff                    add      bh, bh                         
  0x00289F2A  ff00                    inc      dword ptr [eax]                
  0x00289F2C  0c00                    or       al, 0                          
  0x00289F2E  0000                    add      byte ptr [eax], al             
  0x00289F30  1300                    adc      eax, dword ptr [eax]           
  0x00289F32  2000                    and      byte ptr [eax], al             
  0x00289F34  007056                  add      byte ptr [eax + 0x56], dh      
  0x00289F37  0012                    add      byte ptr [edx], dl             
  0x00289F39  0900                    or       dword ptr [eax], eax           
  0x00289F3B  0000                    add      byte ptr [eax], al             
  0x00289F3D  0030                    add      byte ptr [eax], dh             
  0x00289F3F  0000                    add      byte ptr [eax], al             
  0x00289F41  f4                      hlt                                     
  0x00289F42  56                      push     esi                            
  0x00289F43  0000                    add      byte ptr [eax], al             
  0x00289F45  0000                    add      byte ptr [eax], al             
  0x00289F47  0000                    add      byte ptr [eax], al             
  0x00289F49  f4                      hlt                                     
  0x00289F4A  57                      push     edi                            
  0x00289F4B  0008                    add      byte ptr [eax], cl             
  0x00289F4D  06                      push     es                             
  0x00289F4E  0000                    add      byte ptr [eax], al             
  0x00289F50  0c00                    or       al, 0                          
  0x00289F52  0000                    add      byte ptr [eax], al             
  0x00289F54  5c                      pop      esp                            
  0x00289F55  08050080100d            or       byte ptr [0xd108000], al       
  0x00289F5B  009600000000            add      byte ptr [esi], dl             
  0x00289F62  56                      push     esi                            
  0x00289F63  00960b000003            add      byte ptr [esi + 0x300000b], dl 
  0x00289F69  0020                    add      byte ptr [eax], ah             
  0x00289F6B  005374                  add      byte ptr [ebx + 0x74], dl      
  0x00289F6E  050080100d              add      eax, 0xd108000                 
  0x00289F73  00c4                    add      ah, al                         
  0x00289F75  0000                    add      byte ptr [eax], al             
  0x00289F77  0000                    add      byte ptr [eax], al             
  0x00289F7A  56                      push     esi                            
  0x00289F7B  00960b000003            add      byte ptr [esi + 0x300000b], dl 
  0x00289F81  0020                    add      byte ptr [eax], ah             
  0x00289F83  004d74                  add      byte ptr [ebp + 0x74], cl      
  0x00289F86  050080100d              add      eax, 0xd108000                 
  0x00289F8B  006e01                  add      byte ptr [esi + 1], ch         
  0x00289F8E  0000                    add      byte ptr [eax], al             
  0x00289F90  80100d                  adc      byte ptr [eax], 0xd            
  0x00289F93  00b101000080            add      byte ptr [ecx - 0x7fffffff], dh 
  0x00289F99  100d00f40100            adc      byte ptr [0x1f400], cl         
  0x00289F9F  0000                    add      byte ptr [eax], al             
  0x00289FA1  002400                  add      byte ptr [eax + eax], ah       
  0x00289FA4  007044                  add      byte ptr [eax + 0x44], dh      
  0x00289FA7  0031                    add      byte ptr [ecx], dh             
  0x00289FA9  0900                    or       dword ptr [eax], eax           
  0x00289FAB  0000                    add      byte ptr [eax], al             
  0x00289FAE  56                      push     esi                            
  0x00289FAF  00410b                  add      byte ptr [ecx + 0xb], al       
  0x00289FB2  0000                    add      byte ptr [eax], al             
  0x00289FB4  00f0                    add      al, dh                         
  0x00289FB6  44                      inc      esp                            
  0x00289FB7  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x00289FBD  0020                    add      byte ptr [eax], ah             
  0x00289FBF  0009                    add      byte ptr [ecx], cl             
  0x00289FC1  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x00289FC2  050080100d              add      eax, 0xd108000                 
  0x00289FC7  004601                  add      byte ptr [esi + 1], al         
  0x00289FCA  0000                    add      byte ptr [eax], al             
  0x00289FCC  80100d                  adc      byte ptr [eax], 0xd            
  0x00289FCF  002f                    add      byte ptr [edi], ch             
  0x00289FD1  0200                    add      al, byte ptr [eax]             
  0x00289FD3  0000                    add      byte ptr [eax], al             
  0x00289FD5  7055                    jo       0x28a02c                       
  0x00289FD7  0031                    add      byte ptr [ecx], dh             
  0x00289FD9  0900                    or       dword ptr [eax], eax           
  0x00289FDB  0080100d0017            add      byte ptr [eax + 0x17000d10], al 
  0x00289FE1  0300                    add      eax, dword ptr [eax]           
  0x00289FE3  0080100d002f            add      byte ptr [eax + 0x2f000d10], al 
  0x00289FE9  0300                    add      eax, dword ptr [eax]           
  0x00289FEB  0080100d003e            add      byte ptr [eax + 0x3e000d10], al 
  0x00289FF1  0300                    add      eax, dword ptr [eax]           
  0x00289FF3  0080100d0099            add      byte ptr [eax - 0x66fff2f0], al 
  0x00289FF9  0300                    add      eax, dword ptr [eax]           
  0x00289FFB  0080100d0055            add      byte ptr [eax + 0x55000d10], al 
  0x0028A001  0300                    add      eax, dword ptr [eax]           
  0x0028A003  0000                    add      byte ptr [eax], al             
  0x0028A006  56                      push     esi                            
  0x0028A007  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A00A  0000                    add      byte ptr [eax], al             
  0x0028A00C  0300                    add      eax, dword ptr [eax]           
  0x0028A00E  2000                    and      byte ptr [eax], al             
  0x0028A010  0a10                    or       dl, byte ptr [eax]             
  0x0028A012  0d00400400              or       eax, 0x44000                   
  0x0028A017  0080100d00a2            add      byte ptr [eax - 0x5dfff2f0], al 
  0x0028A01D  0300                    add      eax, dword ptr [eax]           
  0x0028A01F  0080100d00cf            add      byte ptr [eax - 0x30fff2f0], al 
  0x0028A025  0300                    add      eax, dword ptr [eax]           
  0x0028A027  0080100d00ea            add      byte ptr [eax - 0x15fff2f0], al 
  0x0028A02D  0300                    add      eax, dword ptr [eax]           
  0x0028A02F  0080100d0081            add      byte ptr [eax - 0x7efff2f0], al 
  0x0028A036  ff00                    inc      dword ptr [eax]                
  0x0028A038  1300                    adc      eax, dword ptr [eax]           
  0x0028A03A  2000                    and      byte ptr [eax], al             
  0x0028A03C  1b10                    sbb      edx, dword ptr [eax]           
  0x0028A03E  2100                    and      dword ptr [eax], eax           
  0x0028A040  0c00                    or       al, 0                          
  0x0028A042  0000                    add      byte ptr [eax], al             
  0x0028A044  005820                  add      byte ptr [eax + 0x20], bl      
  0x0028A047  0000                    add      byte ptr [eax], al             
  0x0028A049  d8440000                fadd     dword ptr [eax + eax]          
  0x0028A04D  7044                    jo       0x28a093                       
  0x0028A04F  00420b                  add      byte ptr [edx + 0xb], al       
  0x0028A052  0000                    add      byte ptr [eax], al             
  0x0028A054  00d8                    add      al, bl                         
  0x0028A056  44                      inc      esp                            
  0x0028A057  0000                    add      byte ptr [eax], al             
  0x0028A059  7044                    jo       0x28a09f                       
  0x0028A05B  00430b                  add      byte ptr [ebx + 0xb], al       
  0x0028A05E  0000                    add      byte ptr [eax], al             
  0x0028A060  00d8                    add      al, bl                         
  0x0028A062  44                      inc      esp                            
  0x0028A063  0000                    add      byte ptr [eax], al             
  0x0028A065  7044                    jo       0x28a0ab                       
  0x0028A067  00440b00                add      byte ptr [ebx + ecx], al       
  0x0028A06B  0000                    add      byte ptr [eax], al             
  0x0028A06D  d85700                  fcom     dword ptr [edi]                
  0x0028A070  90                      nop                                     
  0x0028A071  180c00                  sbb      byte ptr [eax + eax], cl       
  0x0028A074  2420                    and      al, 0x20                       
  0x0028A076  0000                    add      byte ptr [eax], al             
  0x0028A078  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A07B  007b0b                  add      byte ptr [ebx + 0xb], bh       
  0x0028A07E  0000                    add      byte ptr [eax], al             
  0x0028A080  90                      nop                                     
  0x0028A081  180c00                  sbb      byte ptr [eax + eax], cl       
  0x0028A084  1b10                    sbb      edx, dword ptr [eax]           
  0x0028A086  0000                    add      byte ptr [eax], al             
  0x0028A088  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A08B  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028A08E  0000                    add      byte ptr [eax], al             
  0x0028A090  90                      nop                                     
  0x0028A091  180c00                  sbb      byte ptr [eax + eax], cl       
  0x0028A094  1830                    sbb      byte ptr [eax], dh             
  0x0028A096  0000                    add      byte ptr [eax], al             
  0x0028A098  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A09B  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028A09E  0000                    add      byte ptr [eax], al             
  0x0028A0A0  00d8                    add      al, bl                         
  0x0028A0A2  44                      inc      esp                            
  0x0028A0A3  0000                    add      byte ptr [eax], al             
  0x0028A0A5  7044                    jo       0x28a0eb                       
  0x0028A0A7  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028A0AA  0000                    add      byte ptr [eax], al             
  0x0028A0AC  00d8                    add      al, bl                         
  0x0028A0AE  44                      inc      esp                            
  0x0028A0AF  0000                    add      byte ptr [eax], al             
  0x0028A0B1  7044                    jo       0x28a0f7                       
  0x0028A0B3  00460b                  add      byte ptr [esi + 0xb], al       
  0x0028A0B6  0000                    add      byte ptr [eax], al             
  0x0028A0B8  00d8                    add      al, bl                         
  0x0028A0BA  44                      inc      esp                            
  0x0028A0BB  0000                    add      byte ptr [eax], al             
  0x0028A0BD  7044                    jo       0x28a103                       
  0x0028A0BF  00470b                  add      byte ptr [edi + 0xb], al       
  0x0028A0C2  0000                    add      byte ptr [eax], al             
  0x0028A0C4  00d8                    add      al, bl                         
  0x0028A0C6  57                      push     edi                            
  0x0028A0C7  0090180c0020            add      byte ptr [eax + 0x20000c18], dl 
  0x0028A0CD  60                      pushal                                  
  0x0028A0CE  0000                    add      byte ptr [eax], al             
  0x0028A0D0  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A0D3  007c0b00                add      byte ptr [ebx + ecx], bh       
  0x0028A0D7  0000                    add      byte ptr [eax], al             
  0x0028A0D9  d85700                  fcom     dword ptr [edi]                
  0x0028A0DC  90                      nop                                     
  0x0028A0DD  180c00                  sbb      byte ptr [eax + eax], cl       
  0x0028A0E0  2310                    and      edx, dword ptr [eax]           
  0x0028A0E2  0000                    add      byte ptr [eax], al             
  0x0028A0E4  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A0E7  003d02000090            add      byte ptr [0x90000002], bh      
  0x0028A0ED  180c00                  sbb      byte ptr [eax + eax], cl       
  0x0028A0F0  2210                    and      dl, byte ptr [eax]             
  0x0028A0F2  0000                    add      byte ptr [eax], al             
  0x0028A0F4  007050                  add      byte ptr [eax + 0x50], dh      
                                        ; XREF: 0x0028A0B1 (cond_jump)
  0x0028A0F7  003e                    add      byte ptr [esi], bh             
  0x0028A0F9  0200                    add      al, byte ptr [eax]             
  0x0028A0FB  0090180c0021            add      byte ptr [eax + 0x21000c18], dl 
  0x0028A101  1000                    adc      byte ptr [eax], al             
                                        ; XREF: 0x0028A0BD (cond_jump)
  0x0028A103  0000                    add      byte ptr [eax], al             
  0x0028A105  7050                    jo       0x28a157                       
  0x0028A107  003f                    add      byte ptr [edi], bh             
  0x0028A109  0200                    add      al, byte ptr [eax]             
  0x0028A10B  0090180c0018            add      byte ptr [eax + 0x18000c18], dl 
  0x0028A111  40                      inc      eax                            
  0x0028A112  0000                    add      byte ptr [eax], al             
  0x0028A114  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A117  004002                  add      byte ptr [eax + 2], al         
  0x0028A11A  0000                    add      byte ptr [eax], al             
  0x0028A11C  00d8                    add      al, bl                         
  0x0028A11E  61                      popal                                   
  0x0028A11F  0000                    add      byte ptr [eax], al             
  0x0028A121  06                      push     es                             
  0x0028A122  3800                    cmp      byte ptr [eax], al             
  0x0028A124  004820                  add      byte ptr [eax + 0x20], cl      
  0x0028A127  0000                    add      byte ptr [eax], al             
  0x0028A129  d95700                  fst      dword ptr [edi]                
  0x0028A12C  90                      nop                                     
  0x0028A12D  180c00                  sbb      byte ptr [eax + eax], cl       
  0x0028A130  1a20                    sbb      ah, byte ptr [eax]             
  0x0028A132  0000                    add      byte ptr [eax], al             
  0x0028A134  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A137  004e0b                  add      byte ptr [esi + 0xb], cl       
  0x0028A13A  0000                    add      byte ptr [eax], al             
  0x0028A13C  00d9                    add      cl, bl                         
  0x0028A13E  57                      push     edi                            
  0x0028A13F  008e5f010000            add      byte ptr [esi + 0x15f], cl     
  0x0028A145  7057                    jo       0x28a19e                       
  0x0028A147  00490b                  add      byte ptr [ecx + 0xb], cl       
  0x0028A14A  0000                    add      byte ptr [eax], al             
  0x0028A14C  00d8                    add      al, bl                         
  0x0028A14E  57                      push     edi                            
  0x0028A14F  0090180c0018            add      byte ptr [eax + 0x18000c18], dl 
  0x0028A155  800000                  add      byte ptr [eax], 0              
  0x0028A158  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028A15B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A15E  0000                    add      byte ptr [eax], al             
  0x0028A160  90                      nop                                     
  0x0028A161  180c00                  sbb      byte ptr [eax + eax], cl       
  0x0028A164  208000000070            and      byte ptr [eax + 0x70000000], al 
  0x0028A16A  50                      push     eax                            
  0x0028A16B  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028A16E  0000                    add      byte ptr [eax], al             
  0x0028A170  00d8                    add      al, bl                         
  0x0028A172  57                      push     edi                            
  0x0028A173  0090180c0018            add      byte ptr [eax + 0x18000c18], dl 
  0x0028A179  1000                    adc      byte ptr [eax], al             
  0x0028A17B  0000                    add      byte ptr [eax], al             
  0x0028A17D  7050                    jo       0x28a1cf                       
  0x0028A17F  004c0b00                add      byte ptr [ebx + ecx], cl       
  0x0028A183  0090180c0019            add      byte ptr [eax + 0x19000c18], dl 
  0x0028A189  1000                    adc      byte ptr [eax], al             
  0x0028A18B  0000                    add      byte ptr [eax], al             
  0x0028A18D  7050                    jo       0x28a1df                       
  0x0028A18F  004a0b                  add      byte ptr [edx + 0xb], cl       
  0x0028A192  0000                    add      byte ptr [eax], al             
  0x0028A194  00d8                    add      al, bl                         
  0x0028A196  57                      push     edi                            
  0x0028A197  0000                    add      byte ptr [eax], al             
  0x0028A199  7057                    jo       0x28a1f2                       
  0x0028A19B  004b0b                  add      byte ptr [ebx + 0xb], cl       
                                        ; XREF: 0x0028A145 (cond_jump)
  0x0028A19E  0000                    add      byte ptr [eax], al             
  0x0028A1A0  00e0                    add      al, ah                         
  0x0028A1A2  57                      push     edi                            
  0x0028A1A3  0000                    add      byte ptr [eax], al             
  0x0028A1A5  7057                    jo       0x28a1fe                       
  0x0028A1A7  004d0b                  add      byte ptr [ebp + 0xb], cl       
  0x0028A1AA  0000                    add      byte ptr [eax], al             
  0x0028A1AC  0c00                    or       al, 0                          
  0x0028A1AE  0000                    add      byte ptr [eax], al             
  0x0028A1B0  00f4                    add      ah, dh                         
  0x0028A1B2  44                      inc      esp                            
  0x0028A1B3  0000                    add      byte ptr [eax], al             
  0x0028A1B5  0000                    add      byte ptr [eax], al             
  0x0028A1B7  0000                    add      byte ptr [eax], al             
  0x0028A1B9  7044                    jo       0x28a1ff                       
  0x0028A1BB  00960b000000            add      byte ptr [esi + 0xb], dl       
  0x0028A1C2  56                      push     esi                            
  0x0028A1C3  004002                  add      byte ptr [eax + 2], al         
  0x0028A1C6  0000                    add      byte ptr [eax], al             
  0x0028A1C8  00f4                    add      ah, dh                         
  0x0028A1CA  44                      inc      esp                            
  0x0028A1CB  0009                    add      byte ptr [ecx], cl             
  0x0028A1CD  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028A17D (cond_jump)
  0x0028A1CF  004500                  add      byte ptr [ebp], al             
  0x0028A1D2  2000                    and      byte ptr [eax], al             
  0x0028A1D4  41                      inc      ecx                            
  0x0028A1D5  27                      daa                                     
  0x0028A1D6  2000                    and      byte ptr [eax], al             
  0x0028A1D8  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028A1DB  004002                  add      byte ptr [eax + 2], al         
  0x0028A1DE  0000                    add      byte ptr [eax], al             
  0x0028A1E0  00f0                    add      al, dh                         
  0x0028A1E2  56                      push     esi                            
  0x0028A1E3  00490b                  add      byte ptr [ecx + 0xb], cl       
  0x0028A1E6  0000                    add      byte ptr [eax], al             
  0x0028A1E8  00f4                    add      ah, dh                         
  0x0028A1EA  44                      inc      esp                            
  0x0028A1EB  001f                    add      byte ptr [edi], bl             
  0x0028A1ED  0000                    add      byte ptr [eax], al             
  0x0028A1EF  0045f4                  add      byte ptr [ebp - 0xc], al       
                                        ; XREF: 0x0028A199 (cond_jump)
  0x0028A1F2  45                      inc      ebp                            
  0x0028A1F3  0000                    add      byte ptr [eax], al             
  0x0028A1F5  0000                    add      byte ptr [eax], al             
  0x0028A1F7  004127                  add      byte ptr [ecx + 0x27], al      
  0x0028A1FA  2000                    and      byte ptr [eax], al             
  0x0028A1FC  650020                  add      byte ptr gs:[eax], ah          
                                        ; XREF: 0x0028A1B9 (cond_jump)
  0x0028A1FF  006129                  add      byte ptr [ecx + 0x29], ah      
  0x0028A202  2000                    and      byte ptr [eax], al             
  0x0028A204  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028A207  00490b                  add      byte ptr [ecx + 0xb], cl       
  0x0028A20A  0000                    add      byte ptr [eax], al             
  0x0028A20C  00f0                    add      al, dh                         
  0x0028A20E  56                      push     esi                            
  0x0028A20F  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028A212  0000                    add      byte ptr [eax], al             
  0x0028A214  00f4                    add      ah, dh                         
  0x0028A216  44                      inc      esp                            
  0x0028A217  0007                    add      byte ptr [edi], al             
  0x0028A219  0000                    add      byte ptr [eax], al             
  0x0028A21B  0045f4                  add      byte ptr [ebp - 0xc], al       
  0x0028A21E  45                      inc      ebp                            
  0x0028A21F  0006                    add      byte ptr [esi], al             
  0x0028A221  0000                    add      byte ptr [eax], al             
  0x0028A223  0014a4                  add      byte ptr [esp], dl             
  0x0028A226  050065f444              add      eax, 0x44f46500                
  0x0028A22B  0003                    add      byte ptr [ebx], al             
  0x0028A22D  0000                    add      byte ptr [eax], al             
  0x0028A22F  0011                    add      byte ptr [ecx], dl             
  0x0028A231  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028A232  050045f445              add      eax, 0x45f44500                
  0x0028A237  0002                    add      byte ptr [edx], al             
  0x0028A239  0000                    add      byte ptr [eax], al             
  0x0028A23B  000e                    add      byte ptr [esi], cl             
  0x0028A23D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028A23E  050065f444              add      eax, 0x44f46500                
  0x0028A243  000400                  add      byte ptr [eax + eax], al       
  0x0028A246  0000                    add      byte ptr [eax], al             
  0x0028A248  0ba4050045f445          or       esp, dword ptr [ebp + eax + 0x45f44500] 
  0x0028A24F  000500000008            add      byte ptr [0x8000000], al       
  0x0028A255  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028A256  050065f444              add      eax, 0x44f46500                
  0x0028A25B  0001                    add      byte ptr [ecx], al             
  0x0028A25D  0000                    add      byte ptr [eax], al             
  0x0028A25F  0005a4050000            add      byte ptr [0x5a4], al           
  0x0028A265  f4                      hlt                                     
  0x0028A266  44                      inc      esp                            
  0x0028A267  0002                    add      byte ptr [edx], al             
  0x0028A269  0000                    add      byte ptr [eax], al             
  0x0028A26B  0000                    add      byte ptr [eax], al             
  0x0028A26D  7044                    jo       0x28a2b3                       
  0x0028A26F  00960b000000            add      byte ptr [esi + 0xb], dl       
  0x0028A275  7054                    jo       0x28a2cb                       
  0x0028A277  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028A27A  0000                    add      byte ptr [eax], al             
  0x0028A27C  0c00                    or       al, 0                          
  0x0028A27E  0000                    add      byte ptr [eax], al             
  0x0028A280  00f0                    add      al, dh                         
  0x0028A282  56                      push     esi                            
  0x0028A283  0012                    add      byte ptr [edx], dl             
  0x0028A285  0900                    or       dword ptr [eax], eax           
  0x0028A287  0000                    add      byte ptr [eax], al             
  0x0028A289  f4                      hlt                                     
  0x0028A28A  44                      inc      esp                            
  0x0028A28B  006507                  add      byte ptr [ebp + 7], ah         
  0x0028A28E  0200                    add      al, byte ptr [eax]             
  0x0028A290  45                      inc      ebp                            
  0x0028A291  0020                    add      byte ptr [eax], ah             
  0x0028A293  0006                    add      byte ptr [esi], al             
  0x0028A295  2405                    and      al, 5                          
  0x0028A297  0000                    add      byte ptr [eax], al             
  0x0028A29A  56                      push     esi                            
  0x0028A29B  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028A29E  0000                    add      byte ptr [eax], al             
  0x0028A2A0  0300                    add      eax, dword ptr [eax]           
  0x0028A2A2  2000                    and      byte ptr [eax], al             
  0x0028A2A4  5e                      pop      esi                            
  0x0028A2A5  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028A2A6  05000c0000              add      eax, 0xc00                     
  0x0028A2AB  0013                    add      byte ptr [ebx], dl             
  0x0028A2AD  f4                      hlt                                     
  0x0028A2AE  60                      pushal                                  
  0x0028A2AF  00fd                    add      ch, bh                         
  0x0028A2B1  0400                    add      al, 0                          
                                        ; XREF: 0x0028A26D (cond_jump)
  0x0028A2B3  009006060003            add      byte ptr [eax + 0x3000606], dl 
  0x0028A2B9  0000                    add      byte ptr [eax], al             
  0x0028A2BB  0000                    add      byte ptr [eax], al             
  0x0028A2BD  58                      pop      eax                            
  0x0028A2BE  54                      push     esp                            
  0x0028A2BF  0000                    add      byte ptr [eax], al             
  0x0028A2C1  58                      pop      eax                            
  0x0028A2C2  54                      push     esp                            
  0x0028A2C3  0013                    add      byte ptr [ebx], dl             
  0x0028A2C5  f4                      hlt                                     
  0x0028A2C6  60                      pushal                                  
  0x0028A2C7  00a805000090            add      byte ptr [eax - 0x6ffffffb], ch 
  0x0028A2CD  0506000200              add      eax, 0x20006                   
  0x0028A2D2  0000                    add      byte ptr [eax], al             
  0x0028A2D4  005854                  add      byte ptr [eax + 0x54], bl      
  0x0028A2D7  0013                    add      byte ptr [ebx], dl             
  0x0028A2D9  f4                      hlt                                     
  0x0028A2DA  60                      pushal                                  
  0x0028A2DB  007b05                  add      byte ptr [ebx + 5], bh         
  0x0028A2DE  0000                    add      byte ptr [eax], al             
  0x0028A2E0  90                      nop                                     
  0x0028A2E1  2806                    sub      byte ptr [esi], al             
  0x0028A2E3  0002                    add      byte ptr [edx], al             
  0x0028A2E5  0000                    add      byte ptr [eax], al             
  0x0028A2E7  0000                    add      byte ptr [eax], al             
  0x0028A2E9  58                      pop      eax                            
  0x0028A2EA  54                      push     esp                            
  0x0028A2EB  0013                    add      byte ptr [ebx], dl             
  0x0028A2ED  f4                      hlt                                     
  0x0028A2EE  60                      pushal                                  
  0x0028A2EF  00ae05000090            add      byte ptr [esi - 0x6ffffffb], ch 
  0x0028A2F5  5a                      pop      edx                            
  0x0028A2F6  06                      push     es                             
  0x0028A2F7  0002                    add      byte ptr [edx], al             
  0x0028A2F9  0000                    add      byte ptr [eax], al             
  0x0028A2FB  0000                    add      byte ptr [eax], al             
  0x0028A2FD  58                      pop      eax                            
  0x0028A2FE  54                      push     esp                            
  0x0028A2FF  0013                    add      byte ptr [ebx], dl             
  0x0028A301  f4                      hlt                                     
  0x0028A302  60                      pushal                                  
  0x0028A303  0008                    add      byte ptr [eax], cl             
  0x0028A305  06                      push     es                             
  0x0028A306  0000                    add      byte ptr [eax], al             
  0x0028A308  90                      nop                                     
  0x0028A309  0506000200              add      eax, 0x20006                   
  0x0028A30E  0000                    add      byte ptr [eax], al             
  0x0028A310  005854                  add      byte ptr [eax + 0x54], bl      
  0x0028A313  0013                    add      byte ptr [ebx], dl             
  0x0028A315  f4                      hlt                                     
  0x0028A316  60                      pushal                                  
  0x0028A317  000d06000090            add      byte ptr [0x90000006], cl      
  0x0028A31D  0506000200              add      eax, 0x20006                   
  0x0028A322  0000                    add      byte ptr [eax], al             
  0x0028A324  005854                  add      byte ptr [eax + 0x54], bl      
  0x0028A327  0013                    add      byte ptr [ebx], dl             
  0x0028A329  f4                      hlt                                     
  0x0028A32A  60                      pushal                                  
  0x0028A32B  0009                    add      byte ptr [ecx], cl             
  0x0028A32D  0500009010              add      eax, 0x10900000                
  0x0028A332  06                      push     es                             
  0x0028A333  0002                    add      byte ptr [edx], al             
  0x0028A335  0000                    add      byte ptr [eax], al             
  0x0028A337  0000                    add      byte ptr [eax], al             
  0x0028A339  58                      pop      eax                            
  0x0028A33A  54                      push     esp                            
  0x0028A33B  0013                    add      byte ptr [ebx], dl             
  0x0028A33D  f4                      hlt                                     
  0x0028A33E  60                      pushal                                  
  0x0028A33F  0019                    add      byte ptr [ecx], bl             
  0x0028A341  0500009008              add      eax, 0x8900000                 
  0x0028A346  06                      push     es                             
  0x0028A347  0002                    add      byte ptr [edx], al             
  0x0028A349  0000                    add      byte ptr [eax], al             
  0x0028A34B  0000                    add      byte ptr [eax], al             
  0x0028A34D  58                      pop      eax                            
  0x0028A34E  54                      push     esp                            
  0x0028A34F  0013                    add      byte ptr [ebx], dl             
  0x0028A351  f4                      hlt                                     
  0x0028A352  60                      pushal                                  
  0x0028A353  0021                    add      byte ptr [ecx], ah             
  0x0028A355  050000903c              add      eax, 0x3c900000                
  0x0028A35A  06                      push     es                             
  0x0028A35B  0002                    add      byte ptr [edx], al             
  0x0028A35D  0000                    add      byte ptr [eax], al             
  0x0028A35F  0000                    add      byte ptr [eax], al             
  0x0028A361  58                      pop      eax                            
  0x0028A362  54                      push     esp                            
  0x0028A363  0013                    add      byte ptr [ebx], dl             
  0x0028A365  f4                      hlt                                     
  0x0028A366  60                      pushal                                  
  0x0028A367  005d05                  add      byte ptr [ebp + 5], bl         
  0x0028A36A  0000                    add      byte ptr [eax], al             
  0x0028A36C  90                      nop                                     
  0x0028A36D  1e                      push     ds                             
  0x0028A36E  06                      push     es                             
  0x0028A36F  0002                    add      byte ptr [edx], al             
  0x0028A371  0000                    add      byte ptr [eax], al             
  0x0028A373  0000                    add      byte ptr [eax], al             
  0x0028A375  58                      pop      eax                            
  0x0028A376  54                      push     esp                            
  0x0028A377  0013                    add      byte ptr [ebx], dl             
  0x0028A379  f4                      hlt                                     
  0x0028A37A  60                      pushal                                  
  0x0028A37B  0012                    add      byte ptr [edx], dl             
  0x0028A37D  06                      push     es                             
  0x0028A37E  0000                    add      byte ptr [eax], al             
  0x0028A380  93                      xchg     ebx, eax                       
  0x0028A381  0006                    add      byte ptr [esi], al             
  0x0028A383  0002                    add      byte ptr [edx], al             
  0x0028A385  0000                    add      byte ptr [eax], al             
  0x0028A387  0000                    add      byte ptr [eax], al             
  0x0028A389  58                      pop      eax                            
  0x0028A38A  54                      push     esp                            
  0x0028A38B  0000                    add      byte ptr [eax], al             
  0x0028A38D  f4                      hlt                                     
  0x0028A38E  44                      inc      esp                            
  0x0028A38F  006507                  add      byte ptr [ebp + 7], ah         
  0x0028A392  0200                    add      al, byte ptr [eax]             
  0x0028A394  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028A397  0012                    add      byte ptr [edx], dl             
  0x0028A399  0900                    or       dword ptr [eax], eax           
  0x0028A39B  0000                    add      byte ptr [eax], al             
  0x0028A39D  f4                      hlt                                     
  0x0028A39E  44                      inc      esp                            
  0x0028A39F  0000                    add      byte ptr [eax], al             
  0x0028A3A1  0000                    add      byte ptr [eax], al             
  0x0028A3A3  0000                    add      byte ptr [eax], al             
  0x0028A3A5  7044                    jo       0x28a3eb                       
  0x0028A3A7  00960b000000            add      byte ptr [esi + 0xb], dl       
  0x0028A3AD  f4                      hlt                                     
  0x0028A3AE  61                      popal                                   
  0x0028A3AF  00c2                    add      dl, al                         
  0x0028A3B1  0f0000                  sldt     word ptr [eax]                 
  0x0028A3B4  00f0                    add      al, dh                         
  0x0028A3B6  7100                    jno      0x28a3b8                       
                                        ; XREF: 0x0028A3B6 (cond_jump)
  0x0028A3B8  7d0b                    jge      0x28a3c5                       
  0x0028A3BA  0000                    add      byte ptr [eax], al             
  0x0028A3BC  00f0                    add      al, dh                         
  0x0028A3BE  44                      inc      esp                            
  0x0028A3BF  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028A3C2  0000                    add      byte ptr [eax], al             
  0x0028A3C4  00e9                    add      cl, ch                         
  0x0028A3C6  5e                      pop      esi                            
  0x0028A3C7  004070                  add      byte ptr [eax + 0x70], al      
  0x0028A3CA  54                      push     esp                            
  0x0028A3CB  00970b000000            add      byte ptr [edi + 0xb], dl       
  0x0028A3D1  7054                    jo       0x28a427                       
  0x0028A3D3  00980b00001b            add      byte ptr [eax + 0x1b00000b], bl 
  0x0028A3DA  44                      inc      esp                            
  0x0028A3DB  00970b000013            add      byte ptr [edi + 0x1300000b], dl 
  0x0028A3E1  052d004d02              add      eax, 0x24d002d                 
  0x0028A3E6  2c00                    sub      al, 0                          
  0x0028A3E8  5a                      pop      edx                            
  0x0028A3E9  94                      xchg     esp, eax                       
  0x0028A3EA  05001bf044              add      eax, 0x44f01b00                
  0x0028A3EF  00980b000013            add      byte ptr [eax + 0x1300000b], bl 
  0x0028A3F5  06                      push     es                             
  0x0028A3F6  2d004d022c              sub      eax, 0x2c024d00                
  0x0028A3FB  005594                  add      byte ptr [ebp - 0x6c], dl      
  0x0028A3FE  050000f056              add      eax, 0x56f00000                
  0x0028A403  007c0b00                add      byte ptr [ebx + ecx], bh       
  0x0028A407  0023                    add      byte ptr [ebx], ah             
  0x0028A409  0020                    add      byte ptr [eax], ah             
  0x0028A40B  0000                    add      byte ptr [eax], al             
  0x0028A40D  7054                    jo       0x28a463                       
  0x0028A40F  00990b00001b            add      byte ptr [ecx + 0x1b00000b], bl 
  0x0028A416  44                      inc      esp                            
  0x0028A417  007b0b                  add      byte ptr [ebx + 0xb], bh       
  0x0028A41A  0000                    add      byte ptr [eax], al             
  0x0028A41C  1303                    adc      eax, dword ptr [ebx]           
  0x0028A41E  2d004d042c              sub      eax, 0x2c044d00                
  0x0028A423  004b94                  add      byte ptr [ebx - 0x6c], cl      
  0x0028A426  05001bf044              add      eax, 0x44f01b00                
  0x0028A42B  00990b000013            add      byte ptr [ecx + 0x1300000b], bl 
  0x0028A431  132d004d032c            adc      ebp, dword ptr [0x2c034d00]    
  0x0028A437  004694                  add      byte ptr [esi - 0x6c], al      
  0x0028A43A  050000f056              add      eax, 0x56f00000                
  0x0028A43F  007c0b00                add      byte ptr [ebx + ecx], bh       
  0x0028A443  00c4                    add      ah, al                         
  0x0028A445  40                      inc      eax                            
  0x0028A446  0100                    add      dword ptr [eax], eax           
  0x0028A448  2400                    and      al, 0                          
  0x0028A44A  0000                    add      byte ptr [eax], al             
  0x0028A44C  00da                    add      dl, bl                         
  0x0028A44E  2100                    and      dword ptr [eax], eax           
  0x0028A450  00f0                    add      al, dh                         
  0x0028A452  44                      inc      esp                            
  0x0028A453  007b0b                  add      byte ptr [ebx + 0xb], bh       
  0x0028A456  0000                    add      byte ptr [eax], al             
  0x0028A458  00f4                    add      ah, dh                         
  0x0028A45A  46                      inc      esi                            
  0x0028A45B  0006                    add      byte ptr [esi], al             
  0x0028A45D  0000                    add      byte ptr [eax], al             
  0x0028A45F  00d0                    add      al, dl                         
  0x0028A461  44                      inc      esp                            
  0x0028A462  2300                    and      eax, dword ptr [eax]           
  0x0028A464  2e1d0c0040f4            sbb      eax, 0xf440000c                
  0x0028A46A  44                      inc      esp                            
  0x0028A46B  004c0f00                add      byte ptr [edi + ecx], cl       
  0x0028A46F  004000                  add      byte ptr [eax], al             
  0x0028A472  2000                    and      byte ptr [eax], al             
  0x0028A474  0091210000e1            add      byte ptr [ecx - 0x1effffdf], dl 
  0x0028A47A  5e                      pop      esi                            
  0x0028A47B  0022                    add      byte ptr [edx], ah             
  0x0028A47D  cf                      iretd                                   
  0x0028A47E  2100                    and      dword ptr [eax], eax           
  0x0028A480  22842100220020          and      al, byte ptr [ecx + 0x20002200] 
  0x0028A487  004070                  add      byte ptr [eax + 0x70], al      
  0x0028A48A  57                      push     edi                            
  0x0028A48B  009a0b000000            add      byte ptr [edx + 0xb], bl       
  0x0028A491  8521                    test     dword ptr [ecx], esp           
  0x0028A493  006ce421                add      byte ptr [esp + 0x21], ch      
  0x0028A497  0000                    add      byte ptr [eax], al             
  0x0028A499  f4                      hlt                                     
  0x0028A49A  46                      inc      esi                            
  0x0028A49B  0008                    add      byte ptr [eax], cl             
  0x0028A49D  0000                    add      byte ptr [eax], al             
  0x0028A49F  00d0                    add      al, dl                         
  0x0028A4A1  a7                      cmpsd    dword ptr [esi], dword ptr es:[edi] 
  0x0028A4A2  2100                    and      dword ptr [eax], eax           
  0x0028A4A4  e87050009d              call     0x9d28f519                     
  0x0028A4A9  0b00                    or       eax, dword ptr [eax]           
  0x0028A4AB  0000                    add      byte ptr [eax], al             
  0x0028A4AD  7045                    jo       0x28a4f4                       
  0x0028A4AF  009b0b0000b0            add      byte ptr [ebx - 0x4ffffff5], bl 
  0x0028A4B5  7051                    jo       0x28a508                       
  0x0028A4B7  009e0b000000            add      byte ptr [esi + 0xb], bl       
  0x0028A4BD  7047                    jo       0x28a506                       
  0x0028A4BF  009c0b00000070          add      byte ptr [ebx + ecx + 0x70000000], bl 
  0x0028A4C6  50                      push     eax                            
  0x0028A4C7  009f0b000003            add      byte ptr [edi + 0x300000b], bl 
  0x0028A4CD  0c05                    or       al, 5                          
  0x0028A4CF  0000                    add      byte ptr [eax], al             
  0x0028A4D1  7054                    jo       0x28a527                       
  0x0028A4D3  00960b00000c            add      byte ptr [esi + 0xc00000b], dl 
  0x0028A4D9  0000                    add      byte ptr [eax], al             
  0x0028A4DB  0000                    add      byte ptr [eax], al             
  0x0028A4DD  f4                      hlt                                     
  0x0028A4DE  56                      push     esi                            
  0x0028A4DF  001409                  add      byte ptr [ecx + ecx], dl       
  0x0028A4E2  0000                    add      byte ptr [eax], al             
  0x0028A4E4  00f0                    add      al, dh                         
  0x0028A4E6  44                      inc      esp                            
  0x0028A4E7  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A4EA  0000                    add      byte ptr [eax], al             
  0x0028A4EC  40                      inc      eax                            
  0x0028A4ED  0020                    add      byte ptr [eax], ah             
  0x0028A4EF  0000                    add      byte ptr [eax], al             
  0x0028A4F1  91                      xchg     ecx, eax                       
  0x0028A4F2  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028A4AD (cond_jump)
  0x0028A4F4  00e1                    add      cl, ah                         
  0x0028A4F6  56                      push     esi                            
  0x0028A4F7  0001                    add      byte ptr [ecx], al             
  0x0028A4F9  1e                      push     ds                             
  0x0028A4FA  0c00                    or       al, 0                          
  0x0028A4FC  3ef4                    hlt                                     
  0x0028A4FE  44                      inc      esp                            
  0x0028A4FF  0001                    add      byte ptr [ecx], al             
  0x0028A501  0000                    add      byte ptr [eax], al             
  0x0028A503  004c0020                add      byte ptr [eax + eax + 0x20], cl 
  0x0028A507  001b                    add      byte ptr [ebx], bl             
  0x0028A509  2920                    sub      dword ptr [eax], esp           
  0x0028A50B  0003                    add      byte ptr [ebx], al             
  0x0028A50D  f4                      hlt                                     
  0x0028A50E  45                      inc      ebp                            
  0x0028A50F  0003                    add      byte ptr [ebx], al             
  0x0028A511  0000                    add      byte ptr [eax], al             
  0x0028A513  0068a0                  add      byte ptr [eax - 0x60], ch      
  0x0028A516  0200                    add      al, byte ptr [eax]             
  0x0028A518  6d                      insd     dword ptr es:[edi], dx         
  0x0028A519  0020                    add      byte ptr [eax], ah             
  0x0028A51B  006870                  add      byte ptr [eax + 0x70], ch      
  0x0028A51E  0200                    add      al, byte ptr [eax]             
  0x0028A520  00f4                    add      ah, dh                         
  0x0028A522  56                      push     esi                            
  0x0028A523  00610b                  add      byte ptr [ecx + 0xb], ah       
  0x0028A526  0000                    add      byte ptr [eax], al             
  0x0028A528  00f0                    add      al, dh                         
  0x0028A52A  44                      inc      esp                            
  0x0028A52B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A52E  0000                    add      byte ptr [eax], al             
  0x0028A530  40                      inc      eax                            
  0x0028A531  0020                    add      byte ptr [eax], ah             
  0x0028A533  0000                    add      byte ptr [eax], al             
  0x0028A535  90                      nop                                     
  0x0028A536  2100                    and      dword ptr [eax], eax           
  0x0028A538  006055                  add      byte ptr [eax + 0x55], ah      
  0x0028A53B  000c00                  add      byte ptr [eax + eax], cl       
  0x0028A53E  0000                    add      byte ptr [eax], al             
  0x0028A540  00f0                    add      al, dh                         
  0x0028A542  44                      inc      esp                            
  0x0028A543  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028A546  0000                    add      byte ptr [eax], al             
  0x0028A548  00f4                    add      ah, dh                         
  0x0028A54A  46                      inc      esi                            
  0x0028A54B  0006                    add      byte ptr [esi], al             
  0x0028A54D  0000                    add      byte ptr [eax], al             
  0x0028A54F  00d0                    add      al, dl                         
  0x0028A552  44                      inc      esp                            
  0x0028A553  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A556  0000                    add      byte ptr [eax], al             
  0x0028A558  2e1d0c0040f4            sbb      eax, 0xf440000c                
  0x0028A55E  44                      inc      esp                            
  0x0028A55F  00920f000040            add      byte ptr [edx + 0x4000000f], dl 
  0x0028A565  0020                    add      byte ptr [eax], ah             
  0x0028A567  0000                    add      byte ptr [eax], al             
  0x0028A569  94                      xchg     esp, eax                       
  0x0028A56A  2100                    and      dword ptr [eax], eax           
  0x0028A56C  00f0                    add      al, dh                         
  0x0028A56E  56                      push     esi                            
  0x0028A56F  00440b00                add      byte ptr [ebx + ecx], al       
  0x0028A573  0000                    add      byte ptr [eax], al             
  0x0028A575  e44c                    in       al, 0x4c                       
  0x0028A577  004000                  add      byte ptr [eax], al             
  0x0028A57A  2000                    and      byte ptr [eax], al             
  0x0028A57C  0091210020e1            add      byte ptr [ecx - 0x1edfffdf], dl 
  0x0028A582  050000f056              add      eax, 0x56f00000                
  0x0028A587  00420b                  add      byte ptr [edx + 0xb], al       
  0x0028A58A  0000                    add      byte ptr [eax], al             
  0x0028A58C  00e4                    add      ah, ah                         
  0x0028A58E  4c                      dec      esp                            
  0x0028A58F  004000                  add      byte ptr [eax], al             
  0x0028A592  2000                    and      byte ptr [eax], al             
  0x0028A594  0091210000f0            add      byte ptr [ecx - 0xfffffdf], dl 
  0x0028A59A  56                      push     esi                            
  0x0028A59B  00430b                  add      byte ptr [ebx + 0xb], al       
  0x0028A59E  0000                    add      byte ptr [eax], al             
  0x0028A5A0  00e4                    add      ah, ah                         
  0x0028A5A2  4c                      dec      esp                            
  0x0028A5A3  004000                  add      byte ptr [eax], al             
  0x0028A5A6  2000                    and      byte ptr [eax], al             
  0x0028A5A8  0092210000f4            add      byte ptr [edx - 0xbffffdf], dl 
  0x0028A5AE  44                      inc      esp                            
  0x0028A5AF  0000                    add      byte ptr [eax], al             
  0x0028A5B1  0100                    add      dword ptr [eax], eax           
  0x0028A5B3  0000                    add      byte ptr [eax], al             
  0x0028A5B5  e246                    loop     0x28a5fd                       
  0x0028A5B7  00d0                    add      al, dl                         
  0x0028A5B9  0020                    add      byte ptr [eax], ah             
  0x0028A5BB  0022                    add      byte ptr [edx], ah             
  0x0028A5BD  002400                  add      byte ptr [eax + eax], ah       
  0x0028A5C0  0006                    add      byte ptr [esi], al             
  0x0028A5C2  2100                    and      dword ptr [eax], eax           
  0x0028A5C4  d000                    rol      byte ptr [eax], 1              
  0x0028A5C6  2400                    and      al, 0                          
  0x0028A5C8  00e2                    add      dl, ah                         
  0x0028A5CA  46                      inc      esi                            
  0x0028A5CB  00d2                    add      dl, dl                         
  0x0028A5CD  002400                  add      byte ptr [eax + eax], ah       
  0x0028A5D0  2e1d0c0040e1            sbb      eax, 0xe140000c                
  0x0028A5D6  44                      inc      esp                            
  0x0028A5D7  004000                  add      byte ptr [eax], al             
  0x0028A5DA  2000                    and      byte ptr [eax], al             
  0x0028A5DC  0090210000e2            add      byte ptr [eax - 0x1dffffdf], dl 
  0x0028A5E2  7000                    jo       0x28a5e4                       
                                        ; XREF: 0x0028A5E2 (cond_jump)
  0x0028A5E4  00f4                    add      ah, dh                         
  0x0028A5E6  6400fd                  add      ch, bh                         
  0x0028A5E9  0200                    add      al, byte ptr [eax]             
  0x0028A5EB  0000                    add      byte ptr [eax], al             
  0x0028A5ED  013c00                  add      dword ptr [eax + eax], edi     
  0x0028A5F0  00ff                    add      bh, bh                         
  0x0028A5F2  3e0000                  add      byte ptr ds:[eax], al          
  0x0028A5F5  f4                      hlt                                     
  0x0028A5F6  45                      inc      ebp                            
  0x0028A5F7  00cf                    add      bh, cl                         
  0x0028A5F9  f73f                    idiv     dword ptr [edi]                
  0x0028A5FB  0000                    add      byte ptr [eax], al             
  0x0028A5FE  56                      push     esi                            
  0x0028A5FF  003f                    add      byte ptr [edi], bh             
  0x0028A601  0200                    add      al, byte ptr [eax]             
  0x0028A603  0003                    add      byte ptr [ebx], al             
  0x0028A605  0020                    add      byte ptr [eax], ah             
  0x0028A607  000f                    add      byte ptr [edi], cl             
  0x0028A609  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028A60A  050000f056              add      eax, 0x56f00000                
  0x0028A60F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A612  0000                    add      byte ptr [eax], al             
  0x0028A614  32f4                    xor      dh, ah                         
  0x0028A616  44                      inc      esp                            
  0x0028A617  00fd                    add      ch, bh                         
  0x0028A619  0400                    add      al, 0                          
  0x0028A61B  004000                  add      byte ptr [eax], al             
  0x0028A61E  2000                    and      byte ptr [eax], al             
  0x0028A620  0091210000f4            add      byte ptr [ecx - 0xbffffdf], dl 
  0x0028A626  47                      inc      edi                            
  0x0028A627  004703                  add      byte ptr [edi + 3], al         
  0x0028A62A  0000                    add      byte ptr [eax], al             
  0x0028A62C  00d9                    add      cl, bl                         
  0x0028A62E  57                      push     edi                            
  0x0028A62F  0000                    add      byte ptr [eax], al             
  0x0028A631  d15100                  rcl      dword ptr [ecx]                
  0x0028A634  e704                    out      4, eax                         
  0x0028A636  0d00005955              or       eax, 0x55590000                
  0x0028A63B  0000                    add      byte ptr [eax], al             
  0x0028A63D  61                      popal                                   
  0x0028A63E  51                      push     ecx                            
  0x0028A63F  0002                    add      byte ptr [edx], al             
  0x0028A641  0c05                    or       al, 5                          
  0x0028A643  00f4                    add      ah, dh                         
  0x0028A645  040d                    add      al, 0xd                        
  0x0028A647  0020                    add      byte ptr [eax], ah             
  0x0028A649  f4                      hlt                                     
  0x0028A64A  0500ffff00              add      eax, 0xffff00                  
  0x0028A64F  000c00                  add      byte ptr [eax + eax], cl       
  0x0028A652  0000                    add      byte ptr [eax], al             
  0x0028A654  00f0                    add      al, dh                         
  0x0028A656  56                      push     esi                            
  0x0028A657  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A65A  0000                    add      byte ptr [eax], al             
  0x0028A65C  00f0                    add      al, dh                         
  0x0028A65E  44                      inc      esp                            
  0x0028A65F  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x0028A665  0020                    add      byte ptr [eax], ah             
  0x0028A667  004da4                  add      byte ptr [ebp - 0x5c], cl      
  0x0028A66A  050000f056              add      eax, 0x56f00000                
  0x0028A66F  003d02000003            add      byte ptr [0x3000002], bh       
  0x0028A675  0020                    add      byte ptr [eax], ah             
  0x0028A677  005ba4                  add      byte ptr [ebx - 0x5c], bl      
  0x0028A67A  050000f460              add      eax, 0x60f40000                
  0x0028A67F  00fd                    add      ch, bh                         
  0x0028A681  0200                    add      al, byte ptr [eax]             
  0x0028A683  0000                    add      byte ptr [eax], al             
  0x0028A685  1422                    adc      al, 0x22                       
  0x0028A687  0000                    add      byte ptr [eax], al             
  0x0028A689  0138                    add      dword ptr [eax], edi           
  0x0028A68B  0000                    add      byte ptr [eax], al             
  0x0028A68D  1c23                    sbb      al, 0x23                       
  0x0028A68F  0000                    add      byte ptr [eax], al             
  0x0028A692  44                      inc      esp                            
  0x0028A693  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A696  0000                    add      byte ptr [eax], al             
  0x0028A698  00f4                    add      ah, dh                         
  0x0028A69A  46                      inc      esi                            
  0x0028A69B  000c00                  add      byte ptr [eax + eax], cl       
  0x0028A69E  0000                    add      byte ptr [eax], al             
  0x0028A6A0  d0f4                    sal      ah, 1                          
  0x0028A6A2  44                      inc      esp                            
  0x0028A6A3  0021                    add      byte ptr [ecx], ah             
  0x0028A6A5  0500002e1d              add      eax, 0x1d2e0000                
  0x0028A6AA  0c00                    or       al, 0                          
  0x0028A6AC  40                      inc      eax                            
  0x0028A6AD  0020                    add      byte ptr [eax], ah             
  0x0028A6AF  0000                    add      byte ptr [eax], al             
  0x0028A6B1  91                      xchg     ecx, eax                       
  0x0028A6B2  2100                    and      dword ptr [eax], eax           
  0x0028A6B4  00f0                    add      al, dh                         
  0x0028A6B6  44                      inc      esp                            
  0x0028A6B7  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A6BA  0000                    add      byte ptr [eax], al             
  0x0028A6BC  00f4                    add      ah, dh                         
  0x0028A6BE  46                      inc      esi                            
  0x0028A6BF  0006                    add      byte ptr [esi], al             
  0x0028A6C1  0000                    add      byte ptr [eax], al             
  0x0028A6C3  00d0                    add      al, dl                         
  0x0028A6C5  f4                      hlt                                     
  0x0028A6C6  44                      inc      esp                            
  0x0028A6C7  005d05                  add      byte ptr [ebp + 5], bl         
  0x0028A6CA  0000                    add      byte ptr [eax], al             
  0x0028A6CC  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028A6D2  2000                    and      byte ptr [eax], al             
  0x0028A6D4  0092210000f0            add      byte ptr [edx - 0xfffffdf], dl 
  0x0028A6DA  56                      push     esi                            
  0x0028A6DB  004002                  add      byte ptr [eax + 2], al         
  0x0028A6DE  0000                    add      byte ptr [eax], al             
  0x0028A6E0  c44001                  les      eax, ptr [eax + 1]             
  0x0028A6E3  0007                    add      byte ptr [edi], al             
  0x0028A6E5  0000                    add      byte ptr [eax], al             
  0x0028A6E7  0000                    add      byte ptr [eax], al             
  0x0028A6E9  da21                    fisub    dword ptr [ecx]                
  0x0028A6EB  0000                    add      byte ptr [eax], al             
  0x0028A6ED  44                      inc      esp                            
  0x0028A6EE  2300                    and      eax, dword ptr [eax]           
  0x0028A6F0  00f4                    add      ah, dh                         
  0x0028A6F2  46                      inc      esi                            
  0x0028A6F3  000f                    add      byte ptr [edi], cl             
  0x0028A6F5  0000                    add      byte ptr [eax], al             
  0x0028A6F7  00d0                    add      al, dl                         
  0x0028A6F9  f4                      hlt                                     
  0x0028A6FA  44                      inc      esp                            
  0x0028A6FB  001408                  add      byte ptr [eax + ecx], dl       
  0x0028A6FE  0000                    add      byte ptr [eax], al             
  0x0028A700  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028A706  2000                    and      byte ptr [eax], al             
  0x0028A708  009521000003            add      byte ptr [ebp + 0x3000021], dl 
  0x0028A70E  3a00                    cmp      al, byte ptr [eax]             
  0x0028A710  00ff                    add      bh, bh                         
  0x0028A712  3e009e040d0013          add      byte ptr ds:[esi + 0x13000d04], bl 
  0x0028A719  0c05                    or       al, 5                          
  0x0028A71B  0000                    add      byte ptr [eax], al             
  0x0028A71E  56                      push     esi                            
  0x0028A71F  003e                    add      byte ptr [esi], bh             
  0x0028A721  0200                    add      al, byte ptr [eax]             
  0x0028A723  0003                    add      byte ptr [ebx], al             
  0x0028A725  0020                    add      byte ptr [eax], ah             
  0x0028A727  000f                    add      byte ptr [edi], cl             
  0x0028A729  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028A72A  050000f460              add      eax, 0x60f40000                
  0x0028A72F  00fd                    add      ch, bh                         
  0x0028A731  0200                    add      al, byte ptr [eax]             
  0x0028A733  0000                    add      byte ptr [eax], al             
  0x0028A735  1422                    adc      al, 0x22                       
  0x0028A737  0000                    add      byte ptr [eax], al             
  0x0028A739  0138                    add      dword ptr [eax], edi           
  0x0028A73B  0000                    add      byte ptr [eax], al             
  0x0028A73D  1c23                    sbb      al, 0x23                       
  0x0028A73F  0000                    add      byte ptr [eax], al             
  0x0028A741  f4                      hlt                                     
  0x0028A742  61                      popal                                   
  0x0028A743  0009                    add      byte ptr [ecx], cl             
  0x0028A745  05000000f4              add      eax, 0xf4000000                
  0x0028A74A  6200                    bound    eax, qword ptr [eax]           
  0x0028A74C  1905000000f4            sbb      dword ptr [0xf4000000], eax    
  0x0028A752  650000                  add      byte ptr gs:[eax], al          
  0x0028A755  0800                    or       byte ptr [eax], al             
  0x0028A757  0000                    add      byte ptr [eax], al             
  0x0028A759  043a                    add      al, 0x3a                       
  0x0028A75B  0000                    add      byte ptr [eax], al             
  0x0028A75E  3e00bf040d000c          add      byte ptr ds:[edi + 0xc000d04], bh 
  0x0028A765  0000                    add      byte ptr [eax], al             
  0x0028A767  0000                    add      byte ptr [eax], al             
  0x0028A76A  44                      inc      esp                            
  0x0028A76B  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028A76E  0000                    add      byte ptr [eax], al             
  0x0028A770  00f4                    add      ah, dh                         
  0x0028A772  46                      inc      esi                            
  0x0028A773  0006                    add      byte ptr [esi], al             
  0x0028A775  0000                    add      byte ptr [eax], al             
  0x0028A777  00d0                    add      al, dl                         
  0x0028A77A  44                      inc      esp                            
  0x0028A77B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A77E  0000                    add      byte ptr [eax], al             
  0x0028A780  2e1d0c0040f4            sbb      eax, 0xf440000c                
  0x0028A786  44                      inc      esp                            
  0x0028A787  00920f000040            add      byte ptr [edx + 0x4000000f], dl 
  0x0028A78D  0020                    add      byte ptr [eax], ah             
  0x0028A78F  0000                    add      byte ptr [eax], al             
  0x0028A791  91                      xchg     ecx, eax                       
  0x0028A792  2100                    and      dword ptr [eax], eax           
  0x0028A794  00e1                    add      cl, ah                         
  0x0028A796  4c                      dec      esp                            
  0x0028A797  0000                    add      byte ptr [eax], al             
  0x0028A799  7044                    jo       0x28a7df                       
  0x0028A79B  0013                    add      byte ptr [ebx], dl             
  0x0028A79D  0900                    or       dword ptr [eax], eax           
  0x0028A79F  0000                    add      byte ptr [eax], al             
  0x0028A7A1  f4                      hlt                                     
  0x0028A7A2  61                      popal                                   
  0x0028A7A3  00fd                    add      ch, bh                         
  0x0028A7A5  0200                    add      al, byte ptr [eax]             
  0x0028A7A7  0013                    add      byte ptr [ebx], dl             
  0x0028A7A9  0020                    add      byte ptr [eax], ah             
  0x0028A7AB  001b                    add      byte ptr [ebx], bl             
  0x0028A7AD  d9440091                fld      dword ptr [eax + eax - 0x6f]   
  0x0028A7B1  0006                    add      byte ptr [esi], al             
  0x0028A7B3  000400                  add      byte ptr [eax + eax], al       
  0x0028A7B6  0000                    add      byte ptr [eax], al             
  0x0028A7B8  47                      inc      edi                            
  0x0028A7B9  0020                    add      byte ptr [eax], ah             
  0x0028A7BB  004090                  add      byte ptr [eax - 0x70], al      
  0x0028A7BE  0200                    add      al, byte ptr [eax]             
  0x0028A7C0  8ad9                    mov      bl, cl                         
  0x0028A7C2  44                      inc      esp                            
  0x0028A7C3  0000                    add      byte ptr [eax], al             
  0x0028A7C5  f4                      hlt                                     
  0x0028A7C6  60                      pushal                                  
  0x0028A7C7  00a805000000            add      byte ptr [eax + 5], ch         
  0x0028A7CE  7000                    jo       0x28a7d0                       
                                        ; XREF: 0x0028A7CE (cond_jump)
  0x0028A7D0  41                      inc      ecx                            
  0x0028A7D1  0b00                    or       eax, dword ptr [eax]           
  0x0028A7D3  0032                    add      byte ptr [edx], dh             
  0x0028A7D5  0020                    add      byte ptr [eax], ah             
  0x0028A7D7  0026                    add      byte ptr [esi], ah             
  0x0028A7D9  e844004768              call     0x686fa822                     
  0x0028A7DE  56                      push     esi                            
                                        ; XREF: 0x0028A799 (cond_jump)
  0x0028A7DF  004090                  add      byte ptr [eax - 0x70], al      
  0x0028A7E2  0200                    add      al, byte ptr [eax]             
  0x0028A7E4  00c7                    add      bh, al                         
  0x0028A7E6  2100                    and      dword ptr [eax], eax           
  0x0028A7E8  00f4                    add      ah, dh                         
  0x0028A7EA  56                      push     esi                            
  0x0028A7EB  001409                  add      byte ptr [ecx + ecx], dl       
  0x0028A7EE  0000                    add      byte ptr [eax], al             
  0x0028A7F0  00f0                    add      al, dh                         
  0x0028A7F2  44                      inc      esp                            
  0x0028A7F3  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A7F6  0000                    add      byte ptr [eax], al             
  0x0028A7F8  40                      inc      eax                            
  0x0028A7F9  0020                    add      byte ptr [eax], ah             
  0x0028A7FB  0000                    add      byte ptr [eax], al             
  0x0028A7FD  90                      nop                                     
  0x0028A7FE  2100                    and      dword ptr [eax], eax           
  0x0028A800  006047                  add      byte ptr [eax + 0x47], ah      
  0x0028A803  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x0028A80A  44                      inc      esp                            
  0x0028A80B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A80E  0000                    add      byte ptr [eax], al             
  0x0028A810  00f4                    add      ah, dh                         
  0x0028A812  46                      inc      esi                            
  0x0028A813  0002                    add      byte ptr [edx], al             
  0x0028A815  0000                    add      byte ptr [eax], al             
  0x0028A817  00d0                    add      al, dl                         
  0x0028A819  f4                      hlt                                     
  0x0028A81A  44                      inc      esp                            
  0x0028A81B  0020                    add      byte ptr [eax], ah             
  0x0028A81D  0900                    or       dword ptr [eax], eax           
  0x0028A81F  002e                    add      byte ptr [esi], ch             
  0x0028A821  1d0c004000              sbb      eax, 0x40000c                  
  0x0028A826  2000                    and      byte ptr [eax], al             
  0x0028A828  009021000058            add      byte ptr [eax + 0x58000021], dl 
  0x0028A82E  55                      push     ebp                            
  0x0028A82F  0000                    add      byte ptr [eax], al             
  0x0028A831  60                      pushal                                  
  0x0028A832  51                      push     ecx                            
  0x0028A833  0000                    add      byte ptr [eax], al             
  0x0028A835  f4                      hlt                                     
  0x0028A836  56                      push     esi                            
  0x0028A837  001a                    add      byte ptr [edx], bl             
  0x0028A839  0900                    or       dword ptr [eax], eax           
  0x0028A83B  0000                    add      byte ptr [eax], al             
  0x0028A83E  44                      inc      esp                            
  0x0028A83F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A842  0000                    add      byte ptr [eax], al             
  0x0028A844  40                      inc      eax                            
  0x0028A845  0020                    add      byte ptr [eax], ah             
  0x0028A847  0000                    add      byte ptr [eax], al             
  0x0028A849  90                      nop                                     
  0x0028A84A  2100                    and      dword ptr [eax], eax           
  0x0028A84C  00a721000026            add      byte ptr [edi + 0x26000021], ah 
  0x0028A852  2100                    and      dword ptr [eax], eax           
  0x0028A854  13402f                  adc      eax, dword ptr [eax + 0x2f]    
  0x0028A857  009017060008            add      byte ptr [eax + 0x8000617], dl 
  0x0028A85D  0000                    add      byte ptr [eax], al             
  0x0028A85F  0010                    add      byte ptr [eax], dl             
  0x0028A861  c521                    lds      esp, ptr [ecx]                 
  0x0028A863  0000                    add      byte ptr [eax], al             
  0x0028A865  c421                    les      esp, ptr [ecx]                 
  0x0028A867  00840020003000          add      byte ptr [eax + eax + 0x300020], al 
  0x0028A86E  2000                    and      byte ptr [eax], al             
  0x0028A870  00ae20001021            add      byte ptr [esi + 0x21100020], ch 
  0x0028A876  2000                    and      byte ptr [eax], al             
  0x0028A878  2a00                    sub      al, byte ptr [eax]             
  0x0028A87A  2000                    and      byte ptr [eax], al             
  0x0028A87C  3200                    xor      al, byte ptr [eax]             
  0x0028A87E  2000                    and      byte ptr [eax], al             
  0x0028A880  006056                  add      byte ptr [eax + 0x56], ah      
  0x0028A883  000c00                  add      byte ptr [eax + eax], cl       
  0x0028A886  0000                    add      byte ptr [eax], al             
  0x0028A888  00f4                    add      ah, dh                         
  0x0028A88A  60                      pushal                                  
  0x0028A88B  00fd                    add      ch, bh                         
  0x0028A88D  0200                    add      al, byte ptr [eax]             
  0x0028A88F  0000                    add      byte ptr [eax], al             
  0x0028A891  f4                      hlt                                     
  0x0028A892  6400fd                  add      ch, bh                         
  0x0028A895  0300                    add      eax, dword ptr [eax]           
  0x0028A897  0000                    add      byte ptr [eax], al             
  0x0028A899  0138                    add      dword ptr [eax], edi           
  0x0028A89B  0000                    add      byte ptr [eax], al             
  0x0028A89D  1c23                    sbb      al, 0x23                       
  0x0028A89F  0000                    add      byte ptr [eax], al             
  0x0028A8A2  44                      inc      esp                            
  0x0028A8A3  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A8A6  0000                    add      byte ptr [eax], al             
  0x0028A8A8  00f4                    add      ah, dh                         
  0x0028A8AA  46                      inc      esi                            
  0x0028A8AB  0008                    add      byte ptr [eax], cl             
  0x0028A8AD  0000                    add      byte ptr [eax], al             
  0x0028A8AF  00d0                    add      al, dl                         
  0x0028A8B1  f4                      hlt                                     
  0x0028A8B2  44                      inc      esp                            
  0x0028A8B3  007b05                  add      byte ptr [ebx + 5], bh         
  0x0028A8B6  0000                    add      byte ptr [eax], al             
  0x0028A8B8  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028A8BE  2000                    and      byte ptr [eax], al             
  0x0028A8C0  0091210000f4            add      byte ptr [ecx - 0xbffffdf], dl 
  0x0028A8C6  6500a208000000          add      byte ptr gs:[edx + 8], ah      
  0x0028A8CD  023a                    add      bh, byte ptr [edx]             
  0x0028A8CF  0000                    add      byte ptr [eax], al             
  0x0028A8D2  3e009e040d0000          add      byte ptr ds:[esi + 0xd04], bl  
  0x0028A8DA  44                      inc      esp                            
  0x0028A8DB  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A8DE  0000                    add      byte ptr [eax], al             
  0x0028A8E0  00f4                    add      ah, dh                         
  0x0028A8E2  46                      inc      esi                            
  0x0028A8E3  0012                    add      byte ptr [edx], dl             
  0x0028A8E5  0000                    add      byte ptr [eax], al             
  0x0028A8E7  00d0                    add      al, dl                         
  0x0028A8E9  f4                      hlt                                     
  0x0028A8EA  44                      inc      esp                            
  0x0028A8EB  00ae0500002e            add      byte ptr [esi + 0x2e000005], ch 
  0x0028A8F1  1d0c004000              sbb      eax, 0x40000c                  
  0x0028A8F6  2000                    and      byte ptr [eax], al             
  0x0028A8F8  00902100000e            add      byte ptr [eax + 0xe000021], dl 
  0x0028A8FE  3800                    cmp      byte ptr [eax], al             
  0x0028A900  00f4                    add      ah, dh                         
  0x0028A902  61                      popal                                   
  0x0028A903  00fd                    add      ch, bh                         
  0x0028A905  0300                    add      eax, dword ptr [eax]           
  0x0028A907  0000                    add      byte ptr [eax], al             
  0x0028A909  48                      dec      eax                            
  0x0028A90A  2000                    and      byte ptr [eax], al             
  0x0028A90C  90                      nop                                     
  0x0028A90D  0406                    add      al, 6                          
  0x0028A90F  0009                    add      byte ptr [ecx], cl             
  0x0028A911  0000                    add      byte ptr [eax], al             
  0x0028A913  0013                    add      byte ptr [ebx], dl             
  0x0028A915  0020                    add      byte ptr [eax], ah             
  0x0028A917  009040060004            add      byte ptr [eax + 0x4000640], dl 
  0x0028A91D  0000                    add      byte ptr [eax], al             
  0x0028A91F  0000                    add      byte ptr [eax], al             
  0x0028A921  d9440047                fld      dword ptr [eax + eax + 0x47]   
  0x0028A925  0020                    add      byte ptr [eax], ah             
  0x0028A927  004090                  add      byte ptr [eax - 0x70], al      
  0x0028A92A  0200                    add      al, byte ptr [eax]             
  0x0028A92C  260020                  add      byte ptr es:[eax], ah          
  0x0028A92F  0000                    add      byte ptr [eax], al             
  0x0028A931  58                      pop      eax                            
  0x0028A932  56                      push     esi                            
  0x0028A933  0000                    add      byte ptr [eax], al             
  0x0028A936  44                      inc      esp                            
  0x0028A937  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A93A  0000                    add      byte ptr [eax], al             
  0x0028A93C  00f4                    add      ah, dh                         
  0x0028A93E  46                      inc      esi                            
  0x0028A93F  0012                    add      byte ptr [edx], dl             
  0x0028A941  0000                    add      byte ptr [eax], al             
  0x0028A943  00d0                    add      al, dl                         
  0x0028A945  f4                      hlt                                     
  0x0028A946  44                      inc      esp                            
  0x0028A947  00ae0500002e            add      byte ptr [esi + 0x2e000005], ch 
  0x0028A94D  1d0c004000              sbb      eax, 0x40000c                  
  0x0028A952  2000                    and      byte ptr [eax], al             
  0x0028A954  009021000008            add      byte ptr [eax + 0x8000021], dl 
  0x0028A95A  3800                    cmp      byte ptr [eax], al             
  0x0028A95C  00f4                    add      ah, dh                         
  0x0028A95E  57                      push     edi                            
  0x0028A95F  0002                    add      byte ptr [edx], al             
  0x0028A961  0000                    add      byte ptr [eax], al             
  0x0028A963  0000                    add      byte ptr [eax], al             
  0x0028A965  48                      dec      eax                            
  0x0028A966  2000                    and      byte ptr [eax], al             
  0x0028A968  0006                    add      byte ptr [esi], al             
  0x0028A96A  3800                    cmp      byte ptr [eax], al             
  0x0028A96C  90                      nop                                     
  0x0028A96D  0206                    add      al, byte ptr [esi]             
  0x0028A96F  000b                    add      byte ptr [ebx], cl             
  0x0028A971  0000                    add      byte ptr [eax], al             
  0x0028A973  0000                    add      byte ptr [eax], al             
  0x0028A975  1122                    adc      dword ptr [edx], esp           
  0x0028A977  0012                    add      byte ptr [edx], dl             
  0x0028A979  48                      dec      eax                            
  0x0028A97A  0400                    add      al, 0                          
  0x0028A97C  10cd                    adc      ch, cl                         
  0x0028A97E  06                      push     es                             
  0x0028A97F  0006                    add      byte ptr [esi], al             
  0x0028A981  0000                    add      byte ptr [eax], al             
  0x0028A983  0000                    add      byte ptr [eax], al             
  0x0028A985  da440000                fiadd    dword ptr [eax + eax]          
  0x0028A989  da5600                  ficom    dword ptr [esi]                
  0x0028A98C  45                      inc      ebp                            
  0x0028A98D  0020                    add      byte ptr [eax], ah             
  0x0028A98F  004090                  add      byte ptr [eax - 0x70], al      
  0x0028A992  0200                    add      al, byte ptr [eax]             
  0x0028A994  005956                  add      byte ptr [ecx + 0x56], bl      
  0x0028A997  002a                    add      byte ptr [edx], ch             
  0x0028A999  40                      inc      eax                            
  0x0028A99A  2000                    and      byte ptr [eax], al             
  0x0028A99C  00f0                    add      al, dh                         
  0x0028A99E  44                      inc      esp                            
  0x0028A99F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028A9A2  0000                    add      byte ptr [eax], al             
  0x0028A9A4  00f4                    add      ah, dh                         
  0x0028A9A6  46                      inc      esi                            
  0x0028A9A7  0012                    add      byte ptr [edx], dl             
  0x0028A9A9  0000                    add      byte ptr [eax], al             
  0x0028A9AB  00d0                    add      al, dl                         
  0x0028A9AD  f4                      hlt                                     
  0x0028A9AE  44                      inc      esp                            
  0x0028A9AF  00ae0500002e            add      byte ptr [esi + 0x2e000005], ch 
  0x0028A9B5  1d0c004000              sbb      eax, 0x40000c                  
  0x0028A9BA  2000                    and      byte ptr [eax], al             
  0x0028A9BC  009021000006            add      byte ptr [eax + 0x6000021], dl 
  0x0028A9C2  3800                    cmp      byte ptr [eax], al             
  0x0028A9C4  00f4                    add      ah, dh                         
  0x0028A9C6  6200                    bound    eax, qword ptr [eax]           
  0x0028A9C8  af                      scasd    eax, dword ptr es:[edi]        
  0x0028A9C9  0800                    or       byte ptr [eax], al             
  0x0028A9CB  0000                    add      byte ptr [eax], al             
  0x0028A9CD  0239                    add      bh, byte ptr [ecx]             
  0x0028A9CF  001b                    add      byte ptr [ebx], bl             
  0x0028A9D1  f4                      hlt                                     
  0x0028A9D2  45                      inc      ebp                            
  0x0028A9D3  0001                    add      byte ptr [ecx], al             
  0x0028A9D5  0000                    add      byte ptr [eax], al             
  0x0028A9D7  0000                    add      byte ptr [eax], al             
  0x0028A9D9  a6                      cmpsb    byte ptr [esi], byte ptr es:[edi] 
  0x0028A9DA  2000                    and      byte ptr [eax], al             
  0x0028A9DC  90                      nop                                     
  0x0028A9DD  0306                    add      eax, dword ptr [esi]           
  0x0028A9DF  000d00000000            add      byte ptr [0], cl               
  0x0028A9E5  1122                    adc      dword ptr [edx], esp           
  0x0028A9E7  0000                    add      byte ptr [eax], al             
  0x0028A9E9  da4f00                  fimul    dword ptr [edi]                
  0x0028A9EC  004920                  add      byte ptr [ecx + 0x20], cl      
  0x0028A9EF  0000                    add      byte ptr [eax], al             
  0x0028A9F1  d1440010                rol      dword ptr [eax + eax + 0x10], 1 
  0x0028A9F5  c60600                  mov      byte ptr [esi], 0              
  0x0028A9F8  0400                    add      al, 0                          
  0x0028A9FA  0000                    add      byte ptr [eax], al             
  0x0028A9FC  c0c944                  ror      cl, 0x44                       
  0x0028A9FF  0045d1                  add      byte ptr [ebp - 0x2f], al      
  0x0028AA02  44                      inc      esp                            
  0x0028AA03  006870                  add      byte ptr [eax + 0x70], ch      
  0x0028AA06  0200                    add      al, byte ptr [eax]             
  0x0028AA08  00ce                    add      dh, cl                         
  0x0028AA0A  2000                    and      byte ptr [eax], al             
  0x0028AA0C  324820                  xor      cl, byte ptr [eax + 0x20]      
  0x0028AA0F  0000                    add      byte ptr [eax], al             
  0x0028AA11  8621                    xchg     byte ptr [ecx], ah             
  0x0028AA13  0000                    add      byte ptr [eax], al             
  0x0028AA16  44                      inc      esp                            
  0x0028AA17  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AA1A  0000                    add      byte ptr [eax], al             
  0x0028AA1C  00f4                    add      ah, dh                         
  0x0028AA1E  46                      inc      esi                            
  0x0028AA1F  0012                    add      byte ptr [edx], dl             
  0x0028AA21  0000                    add      byte ptr [eax], al             
  0x0028AA23  00d0                    add      al, dl                         
  0x0028AA25  f4                      hlt                                     
  0x0028AA26  44                      inc      esp                            
  0x0028AA27  00ae0500002e            add      byte ptr [esi + 0x2e000005], ch 
  0x0028AA2D  1d0c004000              sbb      eax, 0x40000c                  
  0x0028AA32  2000                    and      byte ptr [eax], al             
  0x0028AA34  009021000002            add      byte ptr [eax + 0x2000021], dl 
  0x0028AA3A  3800                    cmp      byte ptr [eax], al             
  0x0028AA3C  00f4                    add      ah, dh                         
  0x0028AA3E  44                      inc      esp                            
  0x0028AA3F  0000                    add      byte ptr [eax], al             
  0x0028AA41  3200                    xor      al, byte ptr [eax]             
  0x0028AA43  0000                    add      byte ptr [eax], al             
  0x0028AA45  e856004500              call     0x6daaa0                       
  0x0028AA4A  2000                    and      byte ptr [eax], al             
  0x0028AA4C  1b29                    sbb      ebp, dword ptr [ecx]           
  0x0028AA4E  2000                    and      byte ptr [eax], al             
  0x0028AA50  00f0                    add      al, dh                         
  0x0028AA52  44                      inc      esp                            
  0x0028AA53  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AA56  0000                    add      byte ptr [eax], al             
  0x0028AA58  00f4                    add      ah, dh                         
  0x0028AA5A  46                      inc      esi                            
  0x0028AA5B  0002                    add      byte ptr [edx], al             
  0x0028AA5D  0000                    add      byte ptr [eax], al             
  0x0028AA5F  00d0                    add      al, dl                         
  0x0028AA61  f4                      hlt                                     
  0x0028AA62  44                      inc      esp                            
  0x0028AA63  0020                    add      byte ptr [eax], ah             
  0x0028AA65  0900                    or       dword ptr [eax], eax           
  0x0028AA67  002e                    add      byte ptr [esi], ch             
  0x0028AA69  1d0c004000              sbb      eax, 0x40000c                  
  0x0028AA6E  2000                    and      byte ptr [eax], al             
  0x0028AA70  0091210000f4            add      byte ptr [ecx - 0xbffffdf], dl 
  0x0028AA76  56                      push     esi                            
  0x0028AA77  0008                    add      byte ptr [eax], cl             
  0x0028AA79  06                      push     es                             
  0x0028AA7A  0000                    add      byte ptr [eax], al             
  0x0028AA7C  00f0                    add      al, dh                         
  0x0028AA7E  44                      inc      esp                            
  0x0028AA7F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AA82  0000                    add      byte ptr [eax], al             
  0x0028AA84  40                      inc      eax                            
  0x0028AA85  0020                    add      byte ptr [eax], ah             
  0x0028AA87  0000                    add      byte ptr [eax], al             
  0x0028AA89  90                      nop                                     
  0x0028AA8A  2100                    and      dword ptr [eax], eax           
  0x0028AA8C  00e1                    add      cl, ah                         
  0x0028AA8E  44                      inc      esp                            
  0x0028AA8F  0000                    add      byte ptr [eax], al             
  0x0028AA91  f4                      hlt                                     
  0x0028AA92  46                      inc      esi                            
  0x0028AA93  00ff                    add      bh, bh                         
  0x0028AA96  7f00                    jg       0x28aa98                       
                                        ; XREF: 0x0028AA96 (cond_jump)
  0x0028AA98  d0e0                    shl      al, 1                          
  0x0028AA9A  44                      inc      esp                            
  0x0028AA9B  004500                  add      byte ptr [ebp], al             
  0x0028AA9E  2000                    and      byte ptr [eax], al             
  0x0028AAA0  1b29                    sbb      ebp, dword ptr [ecx]           
  0x0028AAA2  2000                    and      byte ptr [eax], al             
  0x0028AAA4  00f4                    add      ah, dh                         
  0x0028AAA6  56                      push     esi                            
  0x0028AAA7  002c09                  add      byte ptr [ecx + ecx], ch       
  0x0028AAAA  0000                    add      byte ptr [eax], al             
  0x0028AAAC  00f0                    add      al, dh                         
  0x0028AAAE  44                      inc      esp                            
  0x0028AAAF  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AAB2  0000                    add      byte ptr [eax], al             
  0x0028AAB4  40                      inc      eax                            
  0x0028AAB5  0020                    add      byte ptr [eax], ah             
  0x0028AAB7  0000                    add      byte ptr [eax], al             
  0x0028AAB9  90                      nop                                     
  0x0028AABA  2100                    and      dword ptr [eax], eax           
  0x0028AABC  006055                  add      byte ptr [eax + 0x55], ah      
  0x0028AABF  0000                    add      byte ptr [eax], al             
  0x0028AAC2  44                      inc      esp                            
  0x0028AAC3  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AAC6  0000                    add      byte ptr [eax], al             
  0x0028AAC8  00f4                    add      ah, dh                         
  0x0028AACA  46                      inc      esi                            
  0x0028AACB  0012                    add      byte ptr [edx], dl             
  0x0028AACD  0000                    add      byte ptr [eax], al             
  0x0028AACF  00d0                    add      al, dl                         
  0x0028AAD1  f4                      hlt                                     
  0x0028AAD2  44                      inc      esp                            
  0x0028AAD3  00ae0500002e            add      byte ptr [esi + 0x2e000005], ch 
  0x0028AAD9  1d0c004000              sbb      eax, 0x40000c                  
  0x0028AADE  2000                    and      byte ptr [eax], al             
  0x0028AAE0  009021000006            add      byte ptr [eax + 0x6000021], dl 
  0x0028AAE6  3800                    cmp      byte ptr [eax], al             
  0x0028AAE8  00f4                    add      ah, dh                         
  0x0028AAEA  6200                    bound    eax, qword ptr [eax]           
  0x0028AAEC  ac                      lodsb    al, byte ptr [esi]             
  0x0028AAED  0800                    or       byte ptr [eax], al             
  0x0028AAEF  0000                    add      byte ptr [eax], al             
  0x0028AAF1  0239                    add      bh, byte ptr [ecx]             
  0x0028AAF3  001b                    add      byte ptr [ebx], bl             
  0x0028AAF5  a6                      cmpsb    byte ptr [esi], byte ptr es:[edi] 
  0x0028AAF6  2000                    and      byte ptr [eax], al             
  0x0028AAF8  90                      nop                                     
  0x0028AAF9  0306                    add      eax, dword ptr [esi]           
  0x0028AAFB  000d00000000            add      byte ptr [0], cl               
  0x0028AB01  1122                    adc      dword ptr [edx], esp           
  0x0028AB03  0000                    add      byte ptr [eax], al             
  0x0028AB05  da4f00                  fimul    dword ptr [edi]                
  0x0028AB08  004920                  add      byte ptr [ecx + 0x20], cl      
  0x0028AB0B  0000                    add      byte ptr [eax], al             
  0x0028AB0D  d1440010                rol      dword ptr [eax + eax + 0x10], 1 
  0x0028AB11  c60600                  mov      byte ptr [esi], 0              
  0x0028AB14  0400                    add      al, 0                          
  0x0028AB16  0000                    add      byte ptr [eax], al             
  0x0028AB18  c0c944                  ror      cl, 0x44                       
  0x0028AB1B  0045d1                  add      byte ptr [ebp - 0x2f], al      
  0x0028AB1E  44                      inc      esp                            
  0x0028AB1F  006870                  add      byte ptr [eax + 0x70], ch      
  0x0028AB22  0200                    add      al, byte ptr [eax]             
  0x0028AB24  00ce                    add      dh, cl                         
  0x0028AB26  2000                    and      byte ptr [eax], al             
  0x0028AB28  324820                  xor      cl, byte ptr [eax + 0x20]      
  0x0028AB2B  0000                    add      byte ptr [eax], al             
  0x0028AB2D  8621                    xchg     byte ptr [ecx], ah             
  0x0028AB2F  0000                    add      byte ptr [eax], al             
  0x0028AB32  44                      inc      esp                            
  0x0028AB33  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AB36  0000                    add      byte ptr [eax], al             
  0x0028AB38  00f4                    add      ah, dh                         
  0x0028AB3A  46                      inc      esi                            
  0x0028AB3B  0012                    add      byte ptr [edx], dl             
  0x0028AB3D  0000                    add      byte ptr [eax], al             
  0x0028AB3F  00d0                    add      al, dl                         
  0x0028AB41  f4                      hlt                                     
  0x0028AB42  44                      inc      esp                            
  0x0028AB43  00ae0500002e            add      byte ptr [esi + 0x2e000005], ch 
  0x0028AB49  1d0c004000              sbb      eax, 0x40000c                  
  0x0028AB4E  2000                    and      byte ptr [eax], al             
  0x0028AB50  009021000002            add      byte ptr [eax + 0x2000021], dl 
  0x0028AB56  3800                    cmp      byte ptr [eax], al             
  0x0028AB58  00f4                    add      ah, dh                         
  0x0028AB5A  44                      inc      esp                            
  0x0028AB5B  0000                    add      byte ptr [eax], al             
  0x0028AB5D  3200                    xor      al, byte ptr [eax]             
  0x0028AB5F  0000                    add      byte ptr [eax], al             
  0x0028AB61  e856004500              call     0x6dabbc                       
  0x0028AB66  2000                    and      byte ptr [eax], al             
  0x0028AB68  1b29                    sbb      ebp, dword ptr [ecx]           
  0x0028AB6A  2000                    and      byte ptr [eax], al             
  0x0028AB6C  00f0                    add      al, dh                         
  0x0028AB6E  44                      inc      esp                            
  0x0028AB6F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AB72  0000                    add      byte ptr [eax], al             
  0x0028AB74  00f4                    add      ah, dh                         
  0x0028AB76  46                      inc      esi                            
  0x0028AB77  0002                    add      byte ptr [edx], al             
  0x0028AB79  0000                    add      byte ptr [eax], al             
  0x0028AB7B  00d0                    add      al, dl                         
  0x0028AB7D  f4                      hlt                                     
  0x0028AB7E  44                      inc      esp                            
  0x0028AB7F  0020                    add      byte ptr [eax], ah             
  0x0028AB81  0900                    or       dword ptr [eax], eax           
  0x0028AB83  002e                    add      byte ptr [esi], ch             
  0x0028AB85  1d0c004000              sbb      eax, 0x40000c                  
  0x0028AB8A  2000                    and      byte ptr [eax], al             
  0x0028AB8C  0091210000f4            add      byte ptr [ecx - 0xbffffdf], dl 
  0x0028AB92  56                      push     esi                            
  0x0028AB93  0008                    add      byte ptr [eax], cl             
  0x0028AB95  06                      push     es                             
  0x0028AB96  0000                    add      byte ptr [eax], al             
  0x0028AB98  00f0                    add      al, dh                         
  0x0028AB9A  44                      inc      esp                            
  0x0028AB9B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AB9E  0000                    add      byte ptr [eax], al             
  0x0028ABA0  40                      inc      eax                            
  0x0028ABA1  0020                    add      byte ptr [eax], ah             
  0x0028ABA3  0000                    add      byte ptr [eax], al             
  0x0028ABA5  90                      nop                                     
  0x0028ABA6  2100                    and      dword ptr [eax], eax           
  0x0028ABA8  00e1                    add      cl, ah                         
  0x0028ABAA  44                      inc      esp                            
  0x0028ABAB  0000                    add      byte ptr [eax], al             
  0x0028ABAD  f4                      hlt                                     
  0x0028ABAE  46                      inc      esi                            
  0x0028ABAF  0000                    add      byte ptr [eax], al             
  0x0028ABB1  004000                  add      byte ptr [eax], al             
  0x0028ABB4  d0e0                    shl      al, 1                          
  0x0028ABB6  46                      inc      esi                            
  0x0028ABB7  005560                  add      byte ptr [ebp + 0x60], dl      
  0x0028ABBA  44                      inc      esp                            
  0x0028ABBB  001b                    add      byte ptr [ebx], bl             
  0x0028ABBD  2920                    sub      dword ptr [eax], esp           
  0x0028ABBF  0000                    add      byte ptr [eax], al             
  0x0028ABC1  f4                      hlt                                     
  0x0028ABC2  56                      push     esi                            
  0x0028ABC3  007f0b                  add      byte ptr [edi + 0xb], bh       
  0x0028ABC6  0000                    add      byte ptr [eax], al             
  0x0028ABC8  00f0                    add      al, dh                         
  0x0028ABCA  44                      inc      esp                            
  0x0028ABCB  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028ABCE  0000                    add      byte ptr [eax], al             
  0x0028ABD0  40                      inc      eax                            
  0x0028ABD1  0020                    add      byte ptr [eax], ah             
  0x0028ABD3  0000                    add      byte ptr [eax], al             
  0x0028ABD5  90                      nop                                     
  0x0028ABD6  2100                    and      dword ptr [eax], eax           
  0x0028ABD8  006055                  add      byte ptr [eax + 0x55], ah      
  0x0028ABDB  0000                    add      byte ptr [eax], al             
  0x0028ABDE  44                      inc      esp                            
  0x0028ABDF  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028ABE2  0000                    add      byte ptr [eax], al             
  0x0028ABE4  00f4                    add      ah, dh                         
  0x0028ABE6  46                      inc      esi                            
  0x0028ABE7  0012                    add      byte ptr [edx], dl             
  0x0028ABE9  0000                    add      byte ptr [eax], al             
  0x0028ABEB  00d0                    add      al, dl                         
  0x0028ABED  f4                      hlt                                     
  0x0028ABEE  44                      inc      esp                            
  0x0028ABEF  00ae0500002e            add      byte ptr [esi + 0x2e000005], ch 
  0x0028ABF5  1d0c004000              sbb      eax, 0x40000c                  
  0x0028ABFA  2000                    and      byte ptr [eax], al             
  0x0028ABFC  009021000006            add      byte ptr [eax + 0x6000021], dl 
  0x0028AC02  3800                    cmp      byte ptr [eax], al             
  0x0028AC04  00ae20009003            add      byte ptr [esi + 0x3900020], ch 
  0x0028AC0A  06                      push     es                             
  0x0028AC0B  000a                    add      byte ptr [edx], cl             
  0x0028AC0D  0000                    add      byte ptr [eax], al             
  0x0028AC0F  0000                    add      byte ptr [eax], al             
  0x0028AC11  1122                    adc      dword ptr [edx], esp           
  0x0028AC13  0000                    add      byte ptr [eax], al             
  0x0028AC15  99                      cdq                                     
  0x0028AC16  2100                    and      dword ptr [eax], eax           
  0x0028AC18  0012                    add      byte ptr [edx], dl             
  0x0028AC1A  2200                    and      al, byte ptr [eax]             
  0x0028AC1C  004920                  add      byte ptr [ecx + 0x20], cl      
  0x0028AC1F  0000                    add      byte ptr [eax], al             
  0x0028AC21  d9440000                fld      dword ptr [eax + eax]          
  0x0028AC25  5a                      pop      edx                            
  0x0028AC26  44                      inc      esp                            
  0x0028AC27  0000                    add      byte ptr [eax], al             
  0x0028AC29  d9440000                fld      dword ptr [eax + eax]          
  0x0028AC2D  5a                      pop      edx                            
  0x0028AC2E  44                      inc      esp                            
  0x0028AC2F  0032                    add      byte ptr [edx], dh             
  0x0028AC31  48                      dec      eax                            
  0x0028AC32  2000                    and      byte ptr [eax], al             
  0x0028AC34  0c00                    or       al, 0                          
  0x0028AC36  0000                    add      byte ptr [eax], al             
  0x0028AC38  00f4                    add      ah, dh                         
  0x0028AC3A  56                      push     esi                            
  0x0028AC3B  007f0b                  add      byte ptr [edi + 0xb], bh       
  0x0028AC3E  0000                    add      byte ptr [eax], al             
  0x0028AC40  00f0                    add      al, dh                         
  0x0028AC42  44                      inc      esp                            
  0x0028AC43  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AC46  0000                    add      byte ptr [eax], al             
  0x0028AC48  40                      inc      eax                            
  0x0028AC49  0020                    add      byte ptr [eax], ah             
  0x0028AC4B  0000                    add      byte ptr [eax], al             
  0x0028AC4D  90                      nop                                     
  0x0028AC4E  2100                    and      dword ptr [eax], eax           
  0x0028AC50  00f4                    add      ah, dh                         
  0x0028AC52  56                      push     esi                            
  0x0028AC53  000d06000000            add      byte ptr [6], cl               
  0x0028AC5A  44                      inc      esp                            
  0x0028AC5B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AC5E  0000                    add      byte ptr [eax], al             
  0x0028AC60  40                      inc      eax                            
  0x0028AC61  0020                    add      byte ptr [eax], ah             
  0x0028AC63  0000                    add      byte ptr [eax], al             
  0x0028AC65  91                      xchg     ecx, eax                       
  0x0028AC66  2100                    and      dword ptr [eax], eax           
  0x0028AC68  00f4                    add      ah, dh                         
  0x0028AC6A  56                      push     esi                            
  0x0028AC6B  00840b000000f0          add      byte ptr [ebx + ecx - 0x10000000], al 
  0x0028AC72  44                      inc      esp                            
  0x0028AC73  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AC76  0000                    add      byte ptr [eax], al             
  0x0028AC78  40                      inc      eax                            
  0x0028AC79  0020                    add      byte ptr [eax], ah             
  0x0028AC7B  0000                    add      byte ptr [eax], al             
  0x0028AC7D  92                      xchg     edx, eax                       
  0x0028AC7E  2100                    and      dword ptr [eax], eax           
  0x0028AC80  1be0                    sbb      esp, eax                       
  0x0028AC82  44                      inc      esp                            
  0x0028AC83  0000                    add      byte ptr [eax], al             
  0x0028AC85  e156                    loope    0x28acdd                       
  0x0028AC87  0042f4                  add      byte ptr [edx - 0xc], al       
  0x0028AC8A  45                      inc      ebp                            
  0x0028AC8B  0001                    add      byte ptr [ecx], al             
  0x0028AC8D  0000                    add      byte ptr [eax], al             
  0x0028AC8F  0068a0                  add      byte ptr [eax - 0x60], ch      
  0x0028AC92  0200                    add      al, byte ptr [eax]             
  0x0028AC94  006257                  add      byte ptr [edx + 0x57], ah      
  0x0028AC97  0000                    add      byte ptr [eax], al             
  0x0028AC99  61                      popal                                   
  0x0028AC9A  44                      inc      esp                            
  0x0028AC9B  000c00                  add      byte ptr [eax + eax], cl       
  0x0028AC9E  0000                    add      byte ptr [eax], al             
  0x0028ACA0  00f4                    add      ah, dh                         
  0x0028ACA2  60                      pushal                                  
  0x0028ACA3  00fd                    add      ch, bh                         
  0x0028ACA5  0200                    add      al, byte ptr [eax]             
  0x0028ACA7  0000                    add      byte ptr [eax], al             
  0x0028ACAA  44                      inc      esp                            
  0x0028ACAB  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028ACAE  0000                    add      byte ptr [eax], al             
  0x0028ACB0  00f4                    add      ah, dh                         
  0x0028ACB2  46                      inc      esi                            
  0x0028ACB3  0080000000d0            add      byte ptr [eax - 0x30000000], al 
  0x0028ACB9  f4                      hlt                                     
  0x0028ACBA  44                      inc      esp                            
  0x0028ACBB  0012                    add      byte ptr [edx], dl             
  0x0028ACBD  06                      push     es                             
  0x0028ACBE  0000                    add      byte ptr [eax], al             
  0x0028ACC0  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028ACC6  2000                    and      byte ptr [eax], al             
  0x0028ACC8  0091210000f4            add      byte ptr [ecx - 0xbffffdf], dl 
  0x0028ACCE  6400b208000000          add      byte ptr fs:[edx + 8], dh      
  0x0028ACD5  f4                      hlt                                     
  0x0028ACD6  650000                  add      byte ptr gs:[eax], al          
  0x0028ACD9  0000                    add      byte ptr [eax], al             
  0x0028ACDB  00fc                    add      ah, bh                         
                                        ; XREF: 0x0028AC85 (cond_jump)
  0x0028ACDD  040d                    add      al, 0xd                        
  0x0028ACDF  000c00                  add      byte ptr [eax + eax], cl       
  0x0028ACE2  0000                    add      byte ptr [eax], al             
  0x0028ACE4  00f0                    add      al, dh                         
  0x0028ACE6  56                      push     esi                            
  0x0028ACE7  0031                    add      byte ptr [ecx], dh             
  0x0028ACE9  0900                    or       dword ptr [eax], eax           
  0x0028ACEB  0003                    add      byte ptr [ebx], al             
  0x0028ACED  0020                    add      byte ptr [eax], ah             
  0x0028ACEF  000e                    add      byte ptr [esi], cl             
  0x0028ACF1  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028ACF2  050000f460              add      eax, 0x60f40000                
  0x0028ACF7  0000                    add      byte ptr [eax], al             
  0x0028ACF9  0000                    add      byte ptr [eax], al             
  0x0028ACFB  0000                    add      byte ptr [eax], al             
  0x0028ACFD  f4                      hlt                                     
  0x0028ACFE  61                      popal                                   
  0x0028ACFF  004000                  add      byte ptr [eax], al             
  0x0028AD02  0000                    add      byte ptr [eax], al             
  0x0028AD04  001422                  add      byte ptr [edx], dl             
  0x0028AD07  0000                    add      byte ptr [eax], al             
  0x0028AD09  35220000f4              xor      eax, 0xf4000022                
  0x0028AD0E  6200                    bound    eax, qword ptr [eax]           
  0x0028AD10  b20a                    mov      dl, 0xa                        
  0x0028AD12  0000                    add      byte ptr [eax], al             
  0x0028AD14  00f4                    add      ah, dh                         
  0x0028AD16  6600f2                  add      dl, dh                         
  0x0028AD19  0a00                    or       al, byte ptr [eax]             
  0x0028AD1B  0000                    add      byte ptr [eax], al             
  0x0028AD1D  3f                      aas                                     
  0x0028AD1E  3a00                    cmp      al, byte ptr [eax]             
  0x0028AD20  4d                      dec      ebp                            
  0x0028AD21  050d000a0c              add      eax, 0xc0a000d                 
  0x0028AD26  050000f460              add      eax, 0x60f40000                
  0x0028AD2B  0000                    add      byte ptr [eax], al             
  0x0028AD2D  0000                    add      byte ptr [eax], al             
  0x0028AD2F  0000                    add      byte ptr [eax], al             
  0x0028AD31  1422                    adc      al, 0x22                       
  0x0028AD33  0000                    add      byte ptr [eax], al             
  0x0028AD35  f4                      hlt                                     
  0x0028AD36  6200                    bound    eax, qword ptr [eax]           
  0x0028AD38  b209                    mov      dl, 9                          
  0x0028AD3A  0000                    add      byte ptr [eax], al             
  0x0028AD3C  00f4                    add      ah, dh                         
  0x0028AD3E  660032                  add      byte ptr [edx], dh             
  0x0028AD41  0a00                    or       al, byte ptr [eax]             
  0x0028AD43  0000                    add      byte ptr [eax], al             
  0x0028AD45  7f3a                    jg       0x28ad81                       
  0x0028AD47  003e                    add      byte ptr [esi], bh             
  0x0028AD49  050d000c00              add      eax, 0xc000d                   
  0x0028AD4E  0000                    add      byte ptr [eax], al             
  0x0028AD50  a0000500a0              mov      al, byte ptr [0xa0000500]      
  0x0028AD55  61                      popal                                   
  0x0028AD56  0400                    add      al, 0                          
  0x0028AD58  00f0                    add      al, dh                         
  0x0028AD5A  56                      push     esi                            
  0x0028AD5B  0031                    add      byte ptr [ecx], dh             
  0x0028AD5D  0900                    or       dword ptr [eax], eax           
  0x0028AD5F  0003                    add      byte ptr [ebx], al             
  0x0028AD61  0020                    add      byte ptr [eax], ah             
  0x0028AD63  0015a4050000            add      byte ptr [0x5a4], dl           
  0x0028AD69  f4                      hlt                                     
  0x0028AD6A  60                      pushal                                  
  0x0028AD6B  0000                    add      byte ptr [eax], al             
  0x0028AD6D  0000                    add      byte ptr [eax], al             
  0x0028AD6F  0000                    add      byte ptr [eax], al             
  0x0028AD71  f4                      hlt                                     
  0x0028AD72  61                      popal                                   
  0x0028AD73  004000                  add      byte ptr [eax], al             
  0x0028AD76  0000                    add      byte ptr [eax], al             
  0x0028AD78  00f4                    add      ah, dh                         
  0x0028AD7A  6400fd                  add      ch, bh                         
  0x0028AD7D  0300                    add      eax, dword ptr [eax]           
  0x0028AD7F  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028AD45 (cond_jump)
  0x0028AD81  f4                      hlt                                     
  0x0028AD82  6500fc                  add      ah, bh                         
  0x0028AD85  0400                    add      al, 0                          
  0x0028AD87  0000                    add      byte ptr [eax], al             
  0x0028AD89  f4                      hlt                                     
  0x0028AD8A  6200                    bound    eax, qword ptr [eax]           
  0x0028AD8C  b20a                    mov      dl, 0xa                        
  0x0028AD8E  0000                    add      byte ptr [eax], al             
  0x0028AD90  00f4                    add      ah, dh                         
  0x0028AD92  6600f2                  add      dl, dh                         
  0x0028AD95  0a00                    or       al, byte ptr [eax]             
  0x0028AD97  0000                    add      byte ptr [eax], al             
  0x0028AD99  2038                    and      byte ptr [eax], bh             
  0x0028AD9B  0000                    add      byte ptr [eax], al             
  0x0028AD9D  1923                    sbb      dword ptr [ebx], esp           
  0x0028AD9F  0000                    add      byte ptr [eax], al             
  0x0028ADA1  3f                      aas                                     
  0x0028ADA2  3a00                    cmp      al, byte ptr [eax]             
  0x0028ADA4  0003                    add      byte ptr [ebx], al             
  0x0028ADA6  3c00                    cmp      al, 0                          
  0x0028ADA8  00f4                    add      ah, dh                         
  0x0028ADAA  7500                    jne      0x28adac                       
                                        ; XREF: 0x0028ADAA (cond_jump)
  0x0028ADAC  fd                      std                                     
  0x0028ADAE  ff00                    inc      dword ptr [eax]                
  0x0028ADB0  7305                    jae      0x28adb7                       
  0x0028ADB2  0d00110c05              or       eax, 0x50c1100                 
                                        ; XREF: 0x0028ADB0 (cond_jump)
  0x0028ADB7  0000                    add      byte ptr [eax], al             
  0x0028ADB9  f4                      hlt                                     
  0x0028ADBA  60                      pushal                                  
  0x0028ADBB  0000                    add      byte ptr [eax], al             
  0x0028ADBD  0000                    add      byte ptr [eax], al             
  0x0028ADBF  0000                    add      byte ptr [eax], al             
  0x0028ADC1  f4                      hlt                                     
  0x0028ADC2  6400fd                  add      ch, bh                         
  0x0028ADC5  0300                    add      eax, dword ptr [eax]           
  0x0028ADC7  0000                    add      byte ptr [eax], al             
  0x0028ADC9  f4                      hlt                                     
  0x0028ADCA  6500fc                  add      ah, bh                         
  0x0028ADCD  0400                    add      al, 0                          
  0x0028ADCF  0000                    add      byte ptr [eax], al             
  0x0028ADD1  f4                      hlt                                     
  0x0028ADD2  6200                    bound    eax, qword ptr [eax]           
  0x0028ADD4  b209                    mov      dl, 9                          
  0x0028ADD6  0000                    add      byte ptr [eax], al             
  0x0028ADD8  00f4                    add      ah, dh                         
  0x0028ADDA  660032                  add      byte ptr [edx], dh             
  0x0028ADDD  0a00                    or       al, byte ptr [eax]             
  0x0028ADDF  0000                    add      byte ptr [eax], al             
  0x0028ADE1  40                      inc      eax                            
  0x0028ADE2  3800                    cmp      byte ptr [eax], al             
  0x0028ADE4  007f3a                  add      byte ptr [edi + 0x3a], bh      
  0x0028ADE7  0000                    add      byte ptr [eax], al             
  0x0028ADE9  023c00                  add      bh, byte ptr [eax + eax]       
  0x0028ADEC  00f4                    add      ah, dh                         
  0x0028ADEE  7500                    jne      0x28adf0                       
  0x0028ADF2  ff00                    inc      dword ptr [eax]                
  0x0028ADF4  64050d0020f4            add      eax, 0xf420000d                
  0x0028ADFA  0500ffff00              add      eax, 0xffff00                  
  0x0028ADFF  00a061040000            add      byte ptr [eax + 0x461], ah     
  0x0028AE06  56                      push     esi                            
  0x0028AE07  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AE0A  0000                    add      byte ptr [eax], al             
  0x0028AE0C  00f0                    add      al, dh                         
  0x0028AE0E  44                      inc      esp                            
  0x0028AE0F  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x0028AE15  f4                      hlt                                     
  0x0028AE16  60                      pushal                                  
  0x0028AE17  00fd                    add      ch, bh                         
  0x0028AE19  0300                    add      eax, dword ptr [eax]           
  0x0028AE1B  0008                    add      byte ptr [eax], cl             
  0x0028AE1D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AE1E  050000f461              add      eax, 0x61f40000                
  0x0028AE23  008001000090            add      byte ptr [eax - 0x6fffffff], al 
  0x0028AE29  b506                    mov      ch, 6                          
  0x0028AE2B  0003                    add      byte ptr [ebx], al             
  0x0028AE2D  0000                    add      byte ptr [eax], al             
  0x0028AE2F  0000                    add      byte ptr [eax], al             
  0x0028AE31  d8440000                fadd     dword ptr [eax + eax]          
  0x0028AE35  59                      pop      ecx                            
  0x0028AE36  44                      inc      esp                            
  0x0028AE37  0007                    add      byte ptr [edi], al             
  0x0028AE39  0c05                    or       al, 5                          
  0x0028AE3B  0000                    add      byte ptr [eax], al             
  0x0028AE3D  f4                      hlt                                     
  0x0028AE3E  61                      popal                                   
  0x0028AE3F  003502000090            add      byte ptr [0x90000002], dh      
  0x0028AE45  07                      pop      es                             
  0x0028AE46  06                      push     es                             
  0x0028AE47  0003                    add      byte ptr [ebx], al             
  0x0028AE49  0000                    add      byte ptr [eax], al             
  0x0028AE4B  0000                    add      byte ptr [eax], al             
  0x0028AE4D  d8440000                fadd     dword ptr [eax + eax]          
  0x0028AE51  59                      pop      ecx                            
  0x0028AE52  44                      inc      esp                            
  0x0028AE53  000c00                  add      byte ptr [eax + eax], cl       
  0x0028AE56  0000                    add      byte ptr [eax], al             
  0x0028AE58  00f0                    add      al, dh                         
  0x0028AE5A  56                      push     esi                            
  0x0028AE5B  0031                    add      byte ptr [ecx], dh             
  0x0028AE5D  0900                    or       dword ptr [eax], eax           
  0x0028AE5F  0003                    add      byte ptr [ebx], al             
  0x0028AE61  0020                    add      byte ptr [eax], ah             
  0x0028AE63  000a                    add      byte ptr [edx], cl             
  0x0028AE65  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AE66  050000f460              add      eax, 0x60f40000                
  0x0028AE6B  0000                    add      byte ptr [eax], al             
  0x0028AE6D  0000                    add      byte ptr [eax], al             
  0x0028AE6F  0000                    add      byte ptr [eax], al             
  0x0028AE71  40                      inc      eax                            
  0x0028AE72  3800                    cmp      byte ptr [eax], al             
  0x0028AE74  ef                      out      dx, eax                        
  0x0028AE75  030d0000f460            add      ecx, dword ptr [0x60f40000]    
  0x0028AE7B  004000                  add      byte ptr [eax], al             
  0x0028AE7E  0000                    add      byte ptr [eax], al             
  0x0028AE80  004038                  add      byte ptr [eax + 0x38], al      
  0x0028AE83  00ef                    add      bh, ch                         
  0x0028AE85  030d00050c05            add      ecx, dword ptr [0x50c0500]     
  0x0028AE8B  0000                    add      byte ptr [eax], al             
  0x0028AE8D  f4                      hlt                                     
  0x0028AE8E  60                      pushal                                  
  0x0028AE8F  0000                    add      byte ptr [eax], al             
  0x0028AE91  0000                    add      byte ptr [eax], al             
  0x0028AE93  0000                    add      byte ptr [eax], al             
  0x0028AE95  803800                  cmp      byte ptr [eax], 0              
  0x0028AE98  ef                      out      dx, eax                        
  0x0028AE99  030d000c0000            add      ecx, dword ptr [0xc00]         
  0x0028AE9F  0000                    add      byte ptr [eax], al             
  0x0028AEA2  56                      push     esi                            
  0x0028AEA3  00970b000000            add      byte ptr [edi + 0xb], dl       
  0x0028AEAA  44                      inc      esp                            
  0x0028AEAB  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AEAE  0000                    add      byte ptr [eax], al             
  0x0028AEB0  45                      inc      ebp                            
  0x0028AEB1  f4                      hlt                                     
  0x0028AEB2  45                      inc      ebp                            
  0x0028AEB3  0001                    add      byte ptr [ecx], al             
  0x0028AEB5  0000                    add      byte ptr [eax], al             
  0x0028AEB7  0003                    add      byte ptr [ebx], al             
  0x0028AEB9  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AEBA  05000d0805              add      eax, 0x5080d00                 
  0x0028AEBF  0003                    add      byte ptr [ebx], al             
  0x0028AEC1  0c05                    or       al, 5                          
  0x0028AEC3  0000                    add      byte ptr [eax], al             
  0x0028AEC5  7045                    jo       0x28af0c                       
  0x0028AEC7  008f0b000000            add      byte ptr [edi + 0xb], cl       
  0x0028AECD  f4                      hlt                                     
  0x0028AECE  60                      pushal                                  
  0x0028AECF  007f0b                  add      byte ptr [edi + 0xb], bh       
  0x0028AED2  0000                    add      byte ptr [eax], al             
  0x0028AED4  00f4                    add      ah, dh                         
  0x0028AED6  61                      popal                                   
  0x0028AED7  00a305000090            add      byte ptr [ebx - 0x6ffffffb], ah 
  0x0028AEDD  0506000300              add      eax, 0x30006                   
  0x0028AEE2  0000                    add      byte ptr [eax], al             
  0x0028AEE4  00d8                    add      al, bl                         
  0x0028AEE6  44                      inc      esp                            
  0x0028AEE7  0000                    add      byte ptr [eax], al             
  0x0028AEE9  59                      pop      ecx                            
  0x0028AEEA  44                      inc      esp                            
  0x0028AEEB  000c00                  add      byte ptr [eax + eax], cl       
  0x0028AEEE  0000                    add      byte ptr [eax], al             
  0x0028AEF0  0003                    add      byte ptr [ebx], al             
  0x0028AEF2  2900                    sub      dword ptr [eax], eax           
  0x0028AEF4  00f0                    add      al, dh                         
  0x0028AEF6  7000                    jo       0x28aef8                       
                                        ; XREF: 0x0028AEF6 (cond_jump)
  0x0028AEF8  41                      inc      ecx                            
  0x0028AEF9  0b00                    or       eax, dword ptr [eax]           
  0x0028AEFB  0000                    add      byte ptr [eax], al             
  0x0028AEFD  f4                      hlt                                     
  0x0028AEFE  60                      pushal                                  
  0x0028AEFF  007f0b                  add      byte ptr [edi + 0xb], bh       
  0x0028AF02  0000                    add      byte ptr [eax], al             
  0x0028AF04  00e8                    add      al, ch                         
  0x0028AF06  56                      push     esi                            
  0x0028AF07  008541010010            add      byte ptr [ebp + 0x10000141], al 
  0x0028AF0D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AF0E  050000f460              add      eax, 0x60f40000                
  0x0028AF13  002c09                  add      byte ptr [ecx + ecx], ch       
  0x0028AF16  0000                    add      byte ptr [eax], al             
  0x0028AF18  00e8                    add      al, ch                         
  0x0028AF1A  56                      push     esi                            
  0x0028AF1B  00854101000b            add      byte ptr [ebp + 0xb000141], al 
  0x0028AF21  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AF22  050000f056              add      eax, 0x56f00000                
  0x0028AF27  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028AF2A  0000                    add      byte ptr [eax], al             
  0x0028AF2C  854001                  test     dword ptr [eax + 1], eax       
  0x0028AF2F  0006                    add      byte ptr [esi], al             
  0x0028AF31  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AF32  050000f460              add      eax, 0x60f40000                
  0x0028AF37  00a305000000            add      byte ptr [ebx + 5], ah         
  0x0028AF3D  e856008541              call     0x41adaf98                     
  0x0028AF42  0100                    add      dword ptr [eax], eax           
  0x0028AF44  02a40500000229          add      ah, byte ptr [ebp + eax + 0x29020000] 
  0x0028AF4B  0000                    add      byte ptr [eax], al             
  0x0028AF4D  f4                      hlt                                     
  0x0028AF4E  60                      pushal                                  
  0x0028AF4F  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028AF55  6851000c00              push     0xc0051                        
  0x0028AF5A  0000                    add      byte ptr [eax], al             
  0x0028AF5C  0018                    add      byte ptr [eax], bl             
  0x0028AF5E  3d0000f044              cmp      eax, 0x44f00000                
  0x0028AF63  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AF66  0000                    add      byte ptr [eax], al             
  0x0028AF68  00f0                    add      al, dh                         
  0x0028AF6A  56                      push     esi                            
  0x0028AF6B  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x0028AF71  f4                      hlt                                     
  0x0028AF72  60                      pushal                                  
  0x0028AF73  00800100000c            add      byte ptr [eax + 0xc000001], al 
  0x0028AF79  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AF7A  0500009620              add      eax, 0x20960000                
  0x0028AF7F  0000                    add      byte ptr [eax], al             
  0x0028AF81  f4                      hlt                                     
  0x0028AF82  61                      popal                                   
  0x0028AF83  004102                  add      byte ptr [ecx + 2], al         
  0x0028AF86  0000                    add      byte ptr [eax], al             
  0x0028AF88  00f4                    add      ah, dh                         
  0x0028AF8A  56                      push     esi                            
  0x0028AF8B  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x0028AF91  c422                    les      esp, ptr [edx]                 
  0x0028AF93  004000                  add      byte ptr [eax], al             
  0x0028AF96  2000                    and      byte ptr [eax], al             
  0x0028AF98  0092210000e2            add      byte ptr [edx - 0x1dffffdf], dl 
  0x0028AF9E  7100                    jno      0x28afa0                       
                                        ; XREF: 0x0028AF9E (cond_jump)
  0x0028AFA0  8b050d000a0c            mov      eax, dword ptr [0xc0a000d]     
  0x0028AFA6  050000f056              add      eax, 0x56f00000                
  0x0028AFAB  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028AFAE  0000                    add      byte ptr [eax], al             
  0x0028AFB0  03f4                    add      esi, esp                       
  0x0028AFB2  60                      pushal                                  
  0x0028AFB3  003502000005            add      byte ptr [0x5000002], dh       
  0x0028AFB9  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AFBA  050000f461              add      eax, 0x61f40000                
  0x0028AFBF  00f6                    add      dh, dh                         
  0x0028AFC1  0200                    add      al, byte ptr [eax]             
  0x0028AFC3  0000                    add      byte ptr [eax], al             
  0x0028AFC5  07                      pop      es                             
  0x0028AFC6  3900                    cmp      dword ptr [eax], eax           
  0x0028AFC8  8b050d000c00            mov      eax, dword ptr [0xc000d]       
  0x0028AFCE  0000                    add      byte ptr [eax], al             
  0x0028AFD0  00f0                    add      al, dh                         
  0x0028AFD2  44                      inc      esp                            
  0x0028AFD3  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AFD6  0000                    add      byte ptr [eax], al             
  0x0028AFD8  00f0                    add      al, dh                         
  0x0028AFDA  56                      push     esi                            
  0x0028AFDB  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x0028AFE1  f4                      hlt                                     
  0x0028AFE2  61                      popal                                   
  0x0028AFE3  004102                  add      byte ptr [ecx + 2], al         
  0x0028AFE6  0000                    add      byte ptr [eax], al             
  0x0028AFE8  59                      pop      ecx                            
  0x0028AFE9  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028AFEA  050000f456              add      eax, 0x56f40000                
  0x0028AFEF  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028AFF6  44                      inc      esp                            
  0x0028AFF7  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028AFFA  0000                    add      byte ptr [eax], al             
  0x0028AFFC  40                      inc      eax                            
  0x0028AFFD  0020                    add      byte ptr [eax], ah             
  0x0028AFFF  0000                    add      byte ptr [eax], al             
  0x0028B001  90                      nop                                     
  0x0028B002  2100                    and      dword ptr [eax], eax           
  0x0028B004  00f4                    add      ah, dh                         
  0x0028B006  56                      push     esi                            
  0x0028B007  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x0028B00E  44                      inc      esp                            
  0x0028B00F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028B012  0000                    add      byte ptr [eax], al             
  0x0028B014  40                      inc      eax                            
  0x0028B015  0020                    add      byte ptr [eax], ah             
  0x0028B017  0000                    add      byte ptr [eax], al             
  0x0028B019  92                      xchg     edx, eax                       
  0x0028B01A  2100                    and      dword ptr [eax], eax           
  0x0028B01C  00e0                    add      al, ah                         
  0x0028B01E  56                      push     esi                            
  0x0028B01F  0000                    add      byte ptr [eax], al             
  0x0028B021  e271                    loop     0x28b094                       
  0x0028B023  0000                    add      byte ptr [eax], al             
  0x0028B025  94                      xchg     esp, eax                       
  0x0028B026  2100                    and      dword ptr [eax], eax           
  0x0028B028  0036                    add      byte ptr [esi], dh             
  0x0028B02A  2200                    and      al, byte ptr [eax]             
  0x0028B02C  00f4                    add      ah, dh                         
  0x0028B02E  56                      push     esi                            
  0x0028B02F  005c0b00                add      byte ptr [ebx + ecx], bl       
  0x0028B033  0000                    add      byte ptr [eax], al             
  0x0028B036  44                      inc      esp                            
  0x0028B037  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028B03A  0000                    add      byte ptr [eax], al             
  0x0028B03C  40                      inc      eax                            
  0x0028B03D  0020                    add      byte ptr [eax], ah             
  0x0028B03F  0000                    add      byte ptr [eax], al             
  0x0028B041  90                      nop                                     
  0x0028B042  2100                    and      dword ptr [eax], eax           
  0x0028B044  00f4                    add      ah, dh                         
  0x0028B046  56                      push     esi                            
  0x0028B047  00910b000000            add      byte ptr [ecx + 0xb], dl       
  0x0028B04E  44                      inc      esp                            
  0x0028B04F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028B052  0000                    add      byte ptr [eax], al             
  0x0028B054  40                      inc      eax                            
  0x0028B055  0020                    add      byte ptr [eax], ah             
  0x0028B057  0000                    add      byte ptr [eax], al             
  0x0028B059  92                      xchg     edx, eax                       
  0x0028B05A  2100                    and      dword ptr [eax], eax           
  0x0028B05C  002e                    add      byte ptr [esi], ch             
  0x0028B05E  2300                    and      eax, dword ptr [eax]           
  0x0028B060  844101                  test     byte ptr [ecx + 1], al         
  0x0028B063  00c4                    add      ah, al                         
  0x0028B065  740b                    je       0x28b072                       
  0x0028B067  0016                    add      byte ptr [esi], dl             
  0x0028B069  0f0000                  sldt     word ptr [eax]                 
  0x0028B06C  00852100adf4            add      byte ptr [ebp - 0xb52ffdf], al 
                                        ; XREF: 0x0028B065 (cond_jump)
  0x0028B072  47                      inc      edi                            
  0x0028B073  0001                    add      byte ptr [ecx], al             
  0x0028B075  0000                    add      byte ptr [eax], al             
  0x0028B077  00c4                    add      ah, al                         
  0x0028B079  740b                    je       0x28b086                       
  0x0028B07B  0012                    add      byte ptr [edx], dl             
  0x0028B07D  0f0000                  sldt     word ptr [eax]                 
  0x0028B080  00e6                    add      dh, ah                         
  0x0028B082  2100                    and      dword ptr [eax], eax           
  0x0028B084  d09d20002e1d            rcr      byte ptr [ebp + 0x1d2e0020], 1 
  0x0028B08A  0c00                    or       al, 0                          
  0x0028B08C  65f4                    hlt                                     
  0x0028B08E  46                      inc      esi                            
  0x0028B08F  00abaa2a0078            add      byte ptr [ebx + 0x78002aaa], ch 
  0x0028B095  2920                    sub      dword ptr [eax], esp           
  0x0028B097  0000                    add      byte ptr [eax], al             
  0x0028B099  60                      pushal                                  
  0x0028B09A  55                      push     ebp                            
  0x0028B09B  0000                    add      byte ptr [eax], al             
  0x0028B09D  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x0028B09E  2100                    and      dword ptr [eax], eax           
  0x0028B0A0  e9bc210082              jmp      0x8228d261                     
  0x0028B0A5  1d0c001000              sbb      eax, 0x10000c                  
  0x0028B0AA  2000                    and      byte ptr [eax], al             
  0x0028B0AC  650020                  add      byte ptr gs:[eax], ah          
  0x0028B0AF  007829                  add      byte ptr [eax + 0x29], bh      
  0x0028B0B2  2000                    and      byte ptr [eax], al             
  0x0028B0B4  006255                  add      byte ptr [edx + 0x55], ah      
  0x0028B0B7  0000                    add      byte ptr [eax], al             
  0x0028B0B9  3222                    xor      ah, byte ptr [edx]             
  0x0028B0BB  0000                    add      byte ptr [eax], al             
  0x0028B0BD  59                      pop      ecx                            
  0x0028B0BE  2000                    and      byte ptr [eax], al             
  0x0028B0C0  0000                    add      byte ptr [eax], al             
  0x0028B0C2  3a00                    cmp      al, byte ptr [eax]             
  0x0028B0C4  96                      xchg     esi, eax                       
  0x0028B0C5  050d00110c              add      eax, 0xc11000d                 
  0x0028B0CA  050000f056              add      eax, 0x56f00000                
  0x0028B0CF  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028B0D2  0000                    add      byte ptr [eax], al             
  0x0028B0D4  03f4                    add      esi, esp                       
  0x0028B0D6  60                      pushal                                  
  0x0028B0D7  008f0b00000c            add      byte ptr [edi + 0xc00000b], cl 
  0x0028B0DD  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028B0DE  050000f461              add      eax, 0x61f40000                
  0x0028B0E3  00f6                    add      dh, dh                         
  0x0028B0E5  0200                    add      al, byte ptr [eax]             
  0x0028B0E7  0000                    add      byte ptr [eax], al             
  0x0028B0E9  07                      pop      es                             
  0x0028B0EA  3900                    cmp      dword ptr [eax], eax           
  0x0028B0EC  0036                    add      byte ptr [esi], dh             
  0x0028B0EE  2200                    and      al, byte ptr [eax]             
  0x0028B0F0  0032                    add      byte ptr [edx], dh             
  0x0028B0F2  2200                    and      al, byte ptr [eax]             
  0x0028B0F4  005920                  add      byte ptr [ecx + 0x20], bl      
  0x0028B0F7  0000                    add      byte ptr [eax], al             
  0x0028B0F9  003a                    add      byte ptr [edx], bh             
  0x0028B0FB  0000                    add      byte ptr [eax], al             
  0x0028B0FD  06                      push     es                             
  0x0028B0FE  3c00                    cmp      al, 0                          
  0x0028B100  00f0                    add      al, dh                         
  0x0028B102  7d00                    jge      0x28b104                       
                                        ; XREF: 0x0028B102 (cond_jump)
  0x0028B104  130f                    adc      ecx, dword ptr [edi]           
  0x0028B106  0000                    add      byte ptr [eax], al             
  0x0028B108  96                      xchg     esi, eax                       
  0x0028B109  050d000c00              add      eax, 0xc000d                   
  0x0028B10E  0000                    add      byte ptr [eax], al             
  0x0028B110  00f0                    add      al, dh                         
  0x0028B112  56                      push     esi                            
  0x0028B113  004002                  add      byte ptr [eax + 2], al         
  0x0028B116  0000                    add      byte ptr [eax], al             
  0x0028B118  041d                    add      al, 0x1d                       
  0x0028B11A  0c00                    or       al, 0                          
  0x0028B11C  00c7                    add      bh, al                         
  0x0028B11E  2100                    and      dword ptr [eax], eax           
  0x0028B120  00f4                    add      ah, dh                         
  0x0028B122  46                      inc      esi                            
  0x0028B123  0003                    add      byte ptr [ebx], al             
  0x0028B125  0000                    add      byte ptr [eax], al             
  0x0028B127  00b00020002e            add      byte ptr [eax + 0x2e002000], dh 
  0x0028B12D  1d0c00c040              sbb      eax, 0x40c0000c                
  0x0028B132  0100                    add      dword ptr [eax], eax           
  0x0028B134  49                      dec      ecx                            
  0x0028B135  0000                    add      byte ptr [eax], al             
  0x0028B137  0000                    add      byte ptr [eax], al             
  0x0028B13A  2100                    and      dword ptr [eax], eax           
  0x0028B13C  00f4                    add      ah, dh                         
  0x0028B13E  61                      popal                                   
  0x0028B13F  00a00b000000            add      byte ptr [eax + 0xb], ah       
  0x0028B145  f4                      hlt                                     
  0x0028B146  6200                    bound    eax, qword ptr [eax]           
  0x0028B148  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x0028B149  0b00                    or       eax, dword ptr [eax]           
  0x0028B14B  0000                    add      byte ptr [eax], al             
  0x0028B14E  45                      inc      ebp                            
  0x0028B14F  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028B155  c506                    lds      eax, ptr [esi]                 
  0x0028B157  0003                    add      byte ptr [ebx], al             
  0x0028B159  0000                    add      byte ptr [eax], al             
  0x0028B15B  0000                    add      byte ptr [eax], al             
  0x0028B15D  59                      pop      ecx                            
  0x0028B15E  47                      inc      edi                            
  0x0028B15F  0000                    add      byte ptr [eax], al             
  0x0028B161  5a                      pop      edx                            
  0x0028B162  46                      inc      esi                            
  0x0028B163  0000                    add      byte ptr [eax], al             
  0x0028B165  f4                      hlt                                     
  0x0028B166  57                      push     edi                            
  0x0028B167  0001                    add      byte ptr [ecx], al             
  0x0028B169  0000                    add      byte ptr [eax], al             
  0x0028B16B  0000                    add      byte ptr [eax], al             
  0x0028B16E  56                      push     esi                            
  0x0028B16F  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028B172  0000                    add      byte ptr [eax], al             
  0x0028B174  0300                    add      eax, dword ptr [eax]           
  0x0028B176  2000                    and      byte ptr [eax], al             
  0x0028B178  02a405001b0020          add      ah, byte ptr [ebp + eax + 0x20001b00] 
  0x0028B17F  0000                    add      byte ptr [eax], al             
  0x0028B181  7057                    jo       0x28b1da                       
  0x0028B183  00900b00000c            add      byte ptr [eax + 0xc00000b], dl 
  0x0028B189  0000                    add      byte ptr [eax], al             
  0x0028B18B  0000                    add      byte ptr [eax], al             
  0x0028B18D  f4                      hlt                                     
  0x0028B18E  56                      push     esi                            
  0x0028B18F  0012                    add      byte ptr [edx], dl             
  0x0028B191  0000                    add      byte ptr [eax], al             
  0x0028B193  0000                    add      byte ptr [eax], al             
  0x0028B195  f4                      hlt                                     
  0x0028B196  57                      push     edi                            
  0x0028B197  0000                    add      byte ptr [eax], al             
  0x0028B199  0000                    add      byte ptr [eax], al             
  0x0028B19B  0000                    add      byte ptr [eax], al             
  0x0028B19D  f4                      hlt                                     
  0x0028B19E  7000                    jo       0x28b1a0                       
                                        ; XREF: 0x0028B19E (cond_jump)
  0x0028B1A0  16                      push     ss                             
  0x0028B1A1  0400                    add      al, 0                          
  0x0028B1A3  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B1A9  0100                    add      dword ptr [eax], eax           
  0x0028B1AB  0003                    add      byte ptr [ebx], al             
  0x0028B1AD  0020                    add      byte ptr [eax], ah             
  0x0028B1AF  0000                    add      byte ptr [eax], al             
  0x0028B1B1  2405                    and      al, 5                          
  0x0028B1B3  000c00                  add      byte ptr [eax + eax], cl       
  0x0028B1B6  0000                    add      byte ptr [eax], al             
  0x0028B1B8  00f4                    add      ah, dh                         
  0x0028B1BA  56                      push     esi                            
  0x0028B1BB  0012                    add      byte ptr [edx], dl             
  0x0028B1BD  0000                    add      byte ptr [eax], al             
  0x0028B1BF  0000                    add      byte ptr [eax], al             
  0x0028B1C1  f4                      hlt                                     
  0x0028B1C2  57                      push     edi                            
  0x0028B1C3  0001                    add      byte ptr [ecx], al             
  0x0028B1C5  0000                    add      byte ptr [eax], al             
  0x0028B1C7  0000                    add      byte ptr [eax], al             
  0x0028B1C9  f4                      hlt                                     
  0x0028B1CA  60                      pushal                                  
  0x0028B1CB  00fd                    add      ch, bh                         
  0x0028B1CD  0400                    add      al, 0                          
  0x0028B1CF  0000                    add      byte ptr [eax], al             
  0x0028B1D1  f4                      hlt                                     
  0x0028B1D2  7000                    jo       0x28b1d4                       
                                        ; XREF: 0x0028B1D2 (cond_jump)
  0x0028B1D4  16                      push     ss                             
  0x0028B1D5  0400                    add      al, 0                          
  0x0028B1D7  0000                    add      byte ptr [eax], al             
  0x0028B1D9  0039                    add      byte ptr [ecx], bh             
  0x0028B1DB  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B1E1  0100                    add      dword ptr [eax], eax           
  0x0028B1E3  0003                    add      byte ptr [ebx], al             
  0x0028B1E5  0020                    add      byte ptr [eax], ah             
  0x0028B1E7  0000                    add      byte ptr [eax], al             
  0x0028B1E9  2405                    and      al, 5                          
  0x0028B1EB  000c00                  add      byte ptr [eax + eax], cl       
  0x0028B1EE  0000                    add      byte ptr [eax], al             
  0x0028B1F0  00f4                    add      ah, dh                         
  0x0028B1F2  56                      push     esi                            
  0x0028B1F3  0012                    add      byte ptr [edx], dl             
  0x0028B1F5  0000                    add      byte ptr [eax], al             
  0x0028B1F7  0000                    add      byte ptr [eax], al             
  0x0028B1F9  f4                      hlt                                     
  0x0028B1FA  57                      push     edi                            
  0x0028B1FB  0002                    add      byte ptr [edx], al             
  0x0028B1FD  0000                    add      byte ptr [eax], al             
  0x0028B1FF  0000                    add      byte ptr [eax], al             
  0x0028B201  f4                      hlt                                     
  0x0028B202  60                      pushal                                  
  0x0028B203  00fd                    add      ch, bh                         
  0x0028B205  0400                    add      al, 0                          
  0x0028B207  0000                    add      byte ptr [eax], al             
  0x0028B209  f4                      hlt                                     
  0x0028B20A  7000                    jo       0x28b20c                       
                                        ; XREF: 0x0028B20A (cond_jump)
  0x0028B20C  16                      push     ss                             
  0x0028B20D  0400                    add      al, 0                          
  0x0028B20F  0000                    add      byte ptr [eax], al             
  0x0028B211  0039                    add      byte ptr [ecx], bh             
  0x0028B213  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B219  0100                    add      dword ptr [eax], eax           
  0x0028B21B  0003                    add      byte ptr [ebx], al             
  0x0028B21D  0020                    add      byte ptr [eax], ah             
  0x0028B21F  0000                    add      byte ptr [eax], al             
  0x0028B221  2405                    and      al, 5                          
  0x0028B223  0000                    add      byte ptr [eax], al             
  0x0028B225  f4                      hlt                                     
  0x0028B226  56                      push     esi                            
  0x0028B227  000e                    add      byte ptr [esi], cl             
  0x0028B229  0000                    add      byte ptr [eax], al             
  0x0028B22B  0000                    add      byte ptr [eax], al             
  0x0028B22D  f4                      hlt                                     
  0x0028B22E  60                      pushal                                  
  0x0028B22F  001409                  add      byte ptr [ecx + ecx], dl       
  0x0028B232  0000                    add      byte ptr [eax], al             
  0x0028B234  000c38                  add      byte ptr [eax + edi], cl       
  0x0028B237  0000                    add      byte ptr [eax], al             
  0x0028B239  0039                    add      byte ptr [ecx], bh             
  0x0028B23B  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B241  0100                    add      dword ptr [eax], eax           
  0x0028B243  0003                    add      byte ptr [ebx], al             
  0x0028B245  0020                    add      byte ptr [eax], ah             
  0x0028B247  0000                    add      byte ptr [eax], al             
  0x0028B249  2405                    and      al, 5                          
  0x0028B24B  000c00                  add      byte ptr [eax + eax], cl       
  0x0028B24E  0000                    add      byte ptr [eax], al             
  0x0028B250  00f4                    add      ah, dh                         
  0x0028B252  56                      push     esi                            
  0x0028B253  0019                    add      byte ptr [ecx], bl             
  0x0028B255  0000                    add      byte ptr [eax], al             
  0x0028B257  0000                    add      byte ptr [eax], al             
  0x0028B259  f4                      hlt                                     
  0x0028B25A  57                      push     edi                            
  0x0028B25B  0001                    add      byte ptr [ecx], al             
  0x0028B25D  0000                    add      byte ptr [eax], al             
  0x0028B25F  0000                    add      byte ptr [eax], al             
  0x0028B261  0039                    add      byte ptr [ecx], bh             
  0x0028B263  0000                    add      byte ptr [eax], al             
  0x0028B265  f4                      hlt                                     
  0x0028B266  7000                    jo       0x28b268                       
                                        ; XREF: 0x0028B266 (cond_jump)
  0x0028B268  800000                  add      byte ptr [eax], 0              
  0x0028B26B  0000                    add      byte ptr [eax], al             
  0x0028B26D  f4                      hlt                                     
  0x0028B26E  60                      pushal                                  
  0x0028B26F  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028B272  0000                    add      byte ptr [eax], al             
  0x0028B274  80f00b                  xor      al, 0xb                        
  0x0028B277  008001000003            add      byte ptr [eax + 0x3000001], al 
  0x0028B27D  0020                    add      byte ptr [eax], ah             
  0x0028B27F  0000                    add      byte ptr [eax], al             
  0x0028B281  2405                    and      al, 5                          
  0x0028B283  000c00                  add      byte ptr [eax + eax], cl       
  0x0028B286  0000                    add      byte ptr [eax], al             
  0x0028B288  00f4                    add      ah, dh                         
  0x0028B28A  56                      push     esi                            
  0x0028B28B  001500000000            add      byte ptr [0], dl               
  0x0028B291  f4                      hlt                                     
  0x0028B292  57                      push     edi                            
  0x0028B293  0000                    add      byte ptr [eax], al             
  0x0028B295  0000                    add      byte ptr [eax], al             
  0x0028B297  0000                    add      byte ptr [eax], al             
  0x0028B299  f4                      hlt                                     
  0x0028B29A  7000                    jo       0x28b29c                       
                                        ; XREF: 0x0028B29A (cond_jump)
  0x0028B29C  90                      nop                                     
  0x0028B29D  0300                    add      eax, dword ptr [eax]           
  0x0028B29F  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B2A5  0100                    add      dword ptr [eax], eax           
  0x0028B2A7  0003                    add      byte ptr [ebx], al             
  0x0028B2A9  0020                    add      byte ptr [eax], ah             
  0x0028B2AB  0000                    add      byte ptr [eax], al             
  0x0028B2AD  2405                    and      al, 5                          
  0x0028B2AF  0000                    add      byte ptr [eax], al             
  0x0028B2B1  f4                      hlt                                     
  0x0028B2B2  56                      push     esi                            
  0x0028B2B3  0016                    add      byte ptr [esi], dl             
  0x0028B2B5  0000                    add      byte ptr [eax], al             
  0x0028B2B7  0000                    add      byte ptr [eax], al             
  0x0028B2B9  f4                      hlt                                     
  0x0028B2BA  57                      push     edi                            
  0x0028B2BB  0000                    add      byte ptr [eax], al             
  0x0028B2BD  0000                    add      byte ptr [eax], al             
  0x0028B2BF  0000                    add      byte ptr [eax], al             
  0x0028B2C1  f4                      hlt                                     
  0x0028B2C2  7000                    jo       0x28b2c4                       
                                        ; XREF: 0x0028B2C2 (cond_jump)
  0x0028B2C4  90                      nop                                     
  0x0028B2C5  0300                    add      eax, dword ptr [eax]           
  0x0028B2C7  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B2CD  0100                    add      dword ptr [eax], eax           
  0x0028B2CF  0003                    add      byte ptr [ebx], al             
  0x0028B2D1  0020                    add      byte ptr [eax], ah             
  0x0028B2D3  0000                    add      byte ptr [eax], al             
  0x0028B2D5  2405                    and      al, 5                          
  0x0028B2D7  000c00                  add      byte ptr [eax + eax], cl       
  0x0028B2DA  0000                    add      byte ptr [eax], al             
  0x0028B2DC  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028B2DF  006909                  add      byte ptr [ecx + 9], ch         
  0x0028B2E2  0000                    add      byte ptr [eax], al             
  0x0028B2E4  00f0                    add      al, dh                         
  0x0028B2E6  56                      push     esi                            
  0x0028B2E7  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x0028B2ED  0020                    add      byte ptr [eax], ah             
  0x0028B2EF  0007                    add      byte ptr [edi], al             
  0x0028B2F1  2405                    and      al, 5                          
  0x0028B2F3  0000                    add      byte ptr [eax], al             
  0x0028B2F5  f4                      hlt                                     
  0x0028B2F6  7100                    jno      0x28b2f8                       
                                        ; XREF: 0x0028B2F6 (cond_jump)
  0x0028B2F8  8903                    mov      dword ptr [ebx], eax           
  0x0028B2FA  0000                    add      byte ptr [eax], al             
  0x0028B2FC  0007                    add      byte ptr [edi], al             
  0x0028B2FE  3800                    cmp      byte ptr [eax], al             
  0x0028B300  00f4                    add      ah, dh                         
  0x0028B302  60                      pushal                                  
  0x0028B303  003502000007            add      byte ptr [0x7000002], dh       
  0x0028B309  0c05                    or       al, 5                          
  0x0028B30B  0000                    add      byte ptr [eax], al             
  0x0028B30D  f4                      hlt                                     
  0x0028B30E  46                      inc      esi                            
  0x0028B30F  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028B315  d820                    fsub     dword ptr [eax]                
  0x0028B317  0022                    add      byte ptr [edx], ah             
  0x0028B319  f4                      hlt                                     
  0x0028B31A  60                      pushal                                  
  0x0028B31B  008001000000            add      byte ptr [eax + 1], al         
  0x0028B321  1921                    sbb      dword ptr [ecx], esp           
  0x0028B323  0000                    add      byte ptr [eax], al             
  0x0028B325  f4                      hlt                                     
  0x0028B326  56                      push     esi                            
  0x0028B327  001500000000            add      byte ptr [0], dl               
  0x0028B32D  f4                      hlt                                     
  0x0028B32E  57                      push     edi                            
  0x0028B32F  0002                    add      byte ptr [edx], al             
  0x0028B331  0000                    add      byte ptr [eax], al             
  0x0028B333  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B339  0100                    add      dword ptr [eax], eax           
  0x0028B33B  0003                    add      byte ptr [ebx], al             
  0x0028B33D  0020                    add      byte ptr [eax], ah             
  0x0028B33F  0000                    add      byte ptr [eax], al             
  0x0028B341  2405                    and      al, 5                          
  0x0028B343  0000                    add      byte ptr [eax], al             
  0x0028B346  44                      inc      esp                            
  0x0028B347  006909                  add      byte ptr [ecx + 9], ch         
  0x0028B34A  0000                    add      byte ptr [eax], al             
  0x0028B34C  00f0                    add      al, dh                         
  0x0028B34E  56                      push     esi                            
  0x0028B34F  00970b000045            add      byte ptr [edi + 0x4500000b], dl 
  0x0028B355  0020                    add      byte ptr [eax], ah             
  0x0028B357  0007                    add      byte ptr [edi], al             
  0x0028B359  2405                    and      al, 5                          
  0x0028B35B  0000                    add      byte ptr [eax], al             
  0x0028B35D  f4                      hlt                                     
  0x0028B35E  7100                    jno      0x28b360                       
                                        ; XREF: 0x0028B35E (cond_jump)
  0x0028B360  8903                    mov      dword ptr [ebx], eax           
  0x0028B362  0000                    add      byte ptr [eax], al             
  0x0028B364  0007                    add      byte ptr [edi], al             
  0x0028B366  3800                    cmp      byte ptr [eax], al             
  0x0028B368  00f4                    add      ah, dh                         
  0x0028B36A  60                      pushal                                  
  0x0028B36B  00f6                    add      dh, dh                         
  0x0028B36D  0200                    add      al, byte ptr [eax]             
  0x0028B36F  0007                    add      byte ptr [edi], al             
  0x0028B371  0c05                    or       al, 5                          
  0x0028B373  0000                    add      byte ptr [eax], al             
  0x0028B375  f4                      hlt                                     
  0x0028B376  46                      inc      esi                            
  0x0028B377  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028B37D  d820                    fsub     dword ptr [eax]                
  0x0028B37F  0022                    add      byte ptr [edx], ah             
  0x0028B381  f4                      hlt                                     
  0x0028B382  60                      pushal                                  
  0x0028B383  004102                  add      byte ptr [ecx + 2], al         
  0x0028B386  0000                    add      byte ptr [eax], al             
  0x0028B388  0019                    add      byte ptr [ecx], bl             
  0x0028B38A  2100                    and      dword ptr [eax], eax           
  0x0028B38C  00f4                    add      ah, dh                         
  0x0028B38E  56                      push     esi                            
  0x0028B38F  0016                    add      byte ptr [esi], dl             
  0x0028B391  0000                    add      byte ptr [eax], al             
  0x0028B393  0000                    add      byte ptr [eax], al             
  0x0028B395  f4                      hlt                                     
  0x0028B396  57                      push     edi                            
  0x0028B397  0002                    add      byte ptr [edx], al             
  0x0028B399  0000                    add      byte ptr [eax], al             
  0x0028B39B  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028B3A1  0100                    add      dword ptr [eax], eax           
  0x0028B3A3  0003                    add      byte ptr [ebx], al             
  0x0028B3A5  0020                    add      byte ptr [eax], ah             
  0x0028B3A7  0000                    add      byte ptr [eax], al             
  0x0028B3A9  2405                    and      al, 5                          
  0x0028B3AB  000c00                  add      byte ptr [eax + eax], cl       
  0x0028B3AE  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x001F74C9 (data_imm)
  0x0028B3B0  40                      inc      eax                            
  0x0028B3B1  1bd0                    sbb      edx, eax                       
  0x0028B3B3  005206                  add      byte ptr [edx + 6], dl         
  0x0028B3B6  0000                    add      byte ptr [eax], al             
  0x0028B3B8  7201                    jb       0x28b3bb                       
  0x0028B3BA  0300                    add      eax, dword ptr [eax]           
  0x0028B3BC  50                      push     eax                            
  0x0028B3BD  0b8c000b002000          or       ecx, dword ptr [eax + eax + 0x20000b] 
  0x0028B3C4  0210                    add      dl, byte ptr [eax]             
  0x0028B3C6  0d004b0600              or       eax, 0x64b00                   
  0x0028B3CB  0080100d003b            add      byte ptr [eax + 0x3b000d10], al 
  0x0028B3D1  06                      push     es                             
  0x0028B3D2  0000                    add      byte ptr [eax], al             
  0x0028B3D4  00f4                    add      ah, dh                         
  0x0028B3D6  57                      push     edi                            
  0x0028B3D7  0010                    add      byte ptr [eax], dl             
  0x0028B3D9  0000                    add      byte ptr [eax], al             
  0x0028B3DB  0000                    add      byte ptr [eax], al             
  0x0028B3DD  0030                    add      byte ptr [eax], dh             
  0x0028B3DF  0080100d0033            add      byte ptr [eax + 0x33000d10], al 
  0x0028B3E5  0200                    add      al, byte ptr [eax]             
  0x0028B3E7  0000                    add      byte ptr [eax], al             
  0x0028B3E9  f4                      hlt                                     
  0x0028B3EA  44                      inc      esp                            
  0x0028B3EB  0000                    add      byte ptr [eax], al             
  0x0028B3ED  0000                    add      byte ptr [eax], al             
  0x0028B3EF  004500                  add      byte ptr [ebp], al             
  0x0028B3F2  2000                    and      byte ptr [eax], al             
  0x0028B3F4  00740500                add      byte ptr [ebp + eax], dh       
  0x0028B3F8  80100d                  adc      byte ptr [eax], 0xd            
  0x0028B3FB  003f                    add      byte ptr [edi], bh             
  0x0028B3FD  06                      push     es                             
  0x0028B3FE  0000                    add      byte ptr [eax], al             
  0x0028B400  0c00                    or       al, 0                          
  0x0028B402  0000                    add      byte ptr [eax], al             
  0x0028B404  61                      popal                                   
  0x0028B405  f4                      hlt                                     
  0x0028B406  46                      inc      esi                            
  0x0028B407  0010                    add      byte ptr [eax], dl             
  0x0028B409  0000                    add      byte ptr [eax], al             
  0x0028B40B  0000                    add      byte ptr [eax], al             
  0x0028B40D  07                      pop      es                             
  0x0028B40E  2300                    and      eax, dword ptr [eax]           
  0x0028B410  10d9                    adc      cl, bl                         
  0x0028B412  06                      push     es                             
  0x0028B413  000a                    add      byte ptr [edx], cl             
  0x0028B415  0000                    add      byte ptr [eax], al             
  0x0028B417  007cd950                add      byte ptr [ecx + ebx*8 + 0x50], bh 
  0x0028B41B  0007                    add      byte ptr [edi], al             
  0x0028B41D  7405                    je       0x28b424                       
  0x0028B41F  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028B422  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028B41D (cond_jump)
  0x0028B424  46                      inc      esi                            
  0x0028B425  1e                      push     ds                             
  0x0028B426  0c00                    or       al, 0                          
  0x0028B428  90                      nop                                     
  0x0028B429  1e                      push     ds                             
  0x0028B42A  0c00                    or       al, 0                          
  0x0028B42C  49                      dec      ecx                            
  0x0028B42D  e421                    in       al, 0x21                       
  0x0028B42F  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028B432  54                      push     esp                            
  0x0028B433  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028B436  0c00                    or       al, 0                          
  0x0028B438  4e                      dec      esi                            
  0x0028B439  1e                      push     ds                             
  0x0028B43A  0c00                    or       al, 0                          
  0x0028B43C  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028B442  0000                    add      byte ptr [eax], al             
  0x0028B444  61                      popal                                   
  0x0028B445  f4                      hlt                                     
                                        ; XREF: 0x0028B498 (cond_jump)
  0x0028B446  46                      inc      esi                            
  0x0028B447  0010                    add      byte ptr [eax], dl             
  0x0028B449  0000                    add      byte ptr [eax], al             
  0x0028B44B  0000                    add      byte ptr [eax], al             
  0x0028B44D  07                      pop      es                             
  0x0028B44E  2300                    and      eax, dword ptr [eax]           
  0x0028B450  7cd9                    jl       0x28b42b                       
  0x0028B452  50                      push     eax                            
  0x0028B453  0007                    add      byte ptr [edi], al             
  0x0028B455  7405                    je       0x28b45c                       
  0x0028B457  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028B45A  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028B455 (cond_jump)
  0x0028B45C  46                      inc      esi                            
  0x0028B45D  1e                      push     ds                             
  0x0028B45E  0c00                    or       al, 0                          
  0x0028B460  90                      nop                                     
  0x0028B461  1e                      push     ds                             
  0x0028B462  0c00                    or       al, 0                          
  0x0028B464  49                      dec      ecx                            
  0x0028B465  e421                    in       al, 0x21                       
  0x0028B467  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028B46A  54                      push     esp                            
  0x0028B46B  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028B46E  0c00                    or       al, 0                          
  0x0028B470  4e                      dec      esi                            
  0x0028B471  1e                      push     ds                             
  0x0028B472  0c00                    or       al, 0                          
  0x0028B474  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028B47A  0000                    add      byte ptr [eax], al             
  0x0028B47C  00f4                    add      ah, dh                         
  0x0028B47E  46                      inc      esi                            
  0x0028B47F  0010                    add      byte ptr [eax], dl             
  0x0028B481  0000                    add      byte ptr [eax], al             
  0x0028B483  0000                    add      byte ptr [eax], al             
  0x0028B485  07                      pop      es                             
  0x0028B486  2300                    and      eax, dword ptr [eax]           
  0x0028B488  10d9                    adc      cl, bl                         
  0x0028B48A  06                      push     es                             
  0x0028B48B  000d00000000            add      byte ptr [0], cl               
  0x0028B491  d95600                  fst      dword ptr [esi]                
  0x0028B494  6e                      outsb    dx, byte ptr [esi]             
  0x0028B495  1e                      push     ds                             
  0x0028B496  0c00                    or       al, 0                          
  0x0028B498  7cac                    jl       0x28b446                       
  0x0028B49A  2000                    and      byte ptr [eax], al             
  0x0028B49C  07                      pop      es                             
  0x0028B49D  7405                    je       0x28b4a4                       
  0x0028B49F  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028B4A2  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028B49D (cond_jump)
  0x0028B4A4  46                      inc      esi                            
  0x0028B4A5  1e                      push     ds                             
  0x0028B4A6  0c00                    or       al, 0                          
  0x0028B4A8  90                      nop                                     
  0x0028B4A9  1e                      push     ds                             
  0x0028B4AA  0c00                    or       al, 0                          
  0x0028B4AC  49                      dec      ecx                            
  0x0028B4AD  e421                    in       al, 0x21                       
  0x0028B4AF  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028B4B2  54                      push     esp                            
  0x0028B4B3  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028B4B6  0c00                    or       al, 0                          
  0x0028B4B8  4e                      dec      esi                            
  0x0028B4B9  1e                      push     ds                             
  0x0028B4BA  0c00                    or       al, 0                          
  0x0028B4BC  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028B4C2  0000                    add      byte ptr [eax], al             
  0x0028B4C4  00f4                    add      ah, dh                         
  0x0028B4C6  46                      inc      esi                            
  0x0028B4C7  0010                    add      byte ptr [eax], dl             
  0x0028B4C9  0000                    add      byte ptr [eax], al             
  0x0028B4CB  0000                    add      byte ptr [eax], al             
  0x0028B4CD  07                      pop      es                             
                                        ; XREF: 0x0028B520 (cond_jump)
  0x0028B4CE  2300                    and      eax, dword ptr [eax]           
  0x0028B4D0  10d9                    adc      cl, bl                         
  0x0028B4D2  06                      push     es                             
  0x0028B4D3  000d00000000            add      byte ptr [0], cl               
  0x0028B4D9  d95e00                  fstp     dword ptr [esi]                
  0x0028B4DC  6e                      outsb    dx, byte ptr [esi]             
  0x0028B4DD  1e                      push     ds                             
  0x0028B4DE  0c00                    or       al, 0                          
  0x0028B4E0  7cac                    jl       0x28b48e                       
  0x0028B4E2  2000                    and      byte ptr [eax], al             
  0x0028B4E4  07                      pop      es                             
  0x0028B4E5  7405                    je       0x28b4ec                       
  0x0028B4E7  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028B4EA  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028B4E5 (cond_jump)
  0x0028B4EC  46                      inc      esi                            
  0x0028B4ED  1e                      push     ds                             
  0x0028B4EE  0c00                    or       al, 0                          
  0x0028B4F0  90                      nop                                     
  0x0028B4F1  1e                      push     ds                             
  0x0028B4F2  0c00                    or       al, 0                          
  0x0028B4F4  49                      dec      ecx                            
  0x0028B4F5  e421                    in       al, 0x21                       
  0x0028B4F7  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028B4FA  54                      push     esp                            
  0x0028B4FB  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028B4FE  0c00                    or       al, 0                          
  0x0028B500  4e                      dec      esi                            
  0x0028B501  1e                      push     ds                             
  0x0028B502  0c00                    or       al, 0                          
  0x0028B504  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028B50A  0000                    add      byte ptr [eax], al             
  0x0028B50C  00f4                    add      ah, dh                         
                                        ; XREF: 0x0028B560 (cond_jump)
  0x0028B50E  46                      inc      esi                            
  0x0028B50F  0010                    add      byte ptr [eax], dl             
  0x0028B511  0000                    add      byte ptr [eax], al             
  0x0028B513  0000                    add      byte ptr [eax], al             
  0x0028B515  07                      pop      es                             
  0x0028B516  2300                    and      eax, dword ptr [eax]           
  0x0028B518  00d9                    add      cl, bl                         
  0x0028B51A  56                      push     esi                            
  0x0028B51B  006e1e                  add      byte ptr [esi + 0x1e], ch      
  0x0028B51E  0c00                    or       al, 0                          
  0x0028B520  7cac                    jl       0x28b4ce                       
  0x0028B522  2000                    and      byte ptr [eax], al             
  0x0028B524  07                      pop      es                             
  0x0028B525  7405                    je       0x28b52c                       
  0x0028B527  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028B52A  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028B525 (cond_jump)
  0x0028B52C  46                      inc      esi                            
  0x0028B52D  1e                      push     ds                             
  0x0028B52E  0c00                    or       al, 0                          
  0x0028B530  90                      nop                                     
  0x0028B531  1e                      push     ds                             
  0x0028B532  0c00                    or       al, 0                          
  0x0028B534  49                      dec      ecx                            
  0x0028B535  e421                    in       al, 0x21                       
  0x0028B537  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028B53A  54                      push     esp                            
  0x0028B53B  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028B53E  0c00                    or       al, 0                          
  0x0028B540  4e                      dec      esi                            
  0x0028B541  1e                      push     ds                             
  0x0028B542  0c00                    or       al, 0                          
  0x0028B544  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028B54A  0000                    add      byte ptr [eax], al             
  0x0028B54C  00f4                    add      ah, dh                         
  0x0028B54E  46                      inc      esi                            
  0x0028B54F  0010                    add      byte ptr [eax], dl             
  0x0028B551  0000                    add      byte ptr [eax], al             
  0x0028B553  0000                    add      byte ptr [eax], al             
  0x0028B555  07                      pop      es                             
  0x0028B556  2300                    and      eax, dword ptr [eax]           
  0x0028B558  00d9                    add      cl, bl                         
  0x0028B55A  5e                      pop      esi                            
  0x0028B55B  006e1e                  add      byte ptr [esi + 0x1e], ch      
  0x0028B55E  0c00                    or       al, 0                          
  0x0028B560  7cac                    jl       0x28b50e                       
  0x0028B562  2000                    and      byte ptr [eax], al             
  0x0028B564  07                      pop      es                             
  0x0028B565  7405                    je       0x28b56c                       
  0x0028B567  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028B56A  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028B565 (cond_jump)
  0x0028B56C  46                      inc      esi                            
  0x0028B56D  1e                      push     ds                             
  0x0028B56E  0c00                    or       al, 0                          
  0x0028B570  90                      nop                                     
  0x0028B571  1e                      push     ds                             
  0x0028B572  0c00                    or       al, 0                          
  0x0028B574  49                      dec      ecx                            
  0x0028B575  e421                    in       al, 0x21                       
  0x0028B577  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028B57A  54                      push     esp                            
  0x0028B57B  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028B57E  0c00                    or       al, 0                          
  0x0028B580  4e                      dec      esi                            
  0x0028B581  1e                      push     ds                             
  0x0028B582  0c00                    or       al, 0                          
  0x0028B584  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028B58A  0000                    add      byte ptr [eax], al             
  0x0028B58C  00f4                    add      ah, dh                         
  0x0028B58E  61                      popal                                   
  0x0028B58F  0012                    add      byte ptr [edx], dl             
  0x0028B591  0d000000f4              or       eax, 0xf4000000                
  0x0028B596  46                      inc      esi                            
  0x0028B597  00ff                    add      bh, bh                         
  0x0028B599  0000                    add      byte ptr [eax], al             
  0x0028B59B  0010                    add      byte ptr [eax], dl             
  0x0028B59D  d806                    fadd     dword ptr [esi]                
  0x0028B59F  000e                    add      byte ptr [esi], cl             
  0x0028B5A1  0000                    add      byte ptr [eax], al             
  0x0028B5A3  00901c0c0056            add      byte ptr [eax + 0x56000c1c], dl 
  0x0028B5A9  0020                    add      byte ptr [eax], ah             
  0x0028B5AB  0000                    add      byte ptr [eax], al             
  0x0028B5AD  d85100                  fcom     dword ptr [ecx]                
  0x0028B5B0  00992100911d            add      byte ptr [ecx + 0x1d910021], bl 
  0x0028B5B6  0c00                    or       al, 0                          
  0x0028B5B8  00e9                    add      cl, ch                         
  0x0028B5BA  4c                      dec      esp                            
  0x0028B5BB  004b00                  add      byte ptr [ebx], cl             
  0x0028B5BE  2000                    and      byte ptr [eax], al             
  0x0028B5C0  90                      nop                                     
  0x0028B5C1  1c0c                    sbb      al, 0xc                        
  0x0028B5C3  005600                  add      byte ptr [esi], dl             
  0x0028B5C6  2000                    and      byte ptr [eax], al             
  0x0028B5C8  00992100911d            add      byte ptr [ecx + 0x1d910021], bl 
  0x0028B5CE  0c00                    or       al, 0                          
  0x0028B5D0  00e9                    add      cl, ch                         
  0x0028B5D2  4c                      dec      esp                            
  0x0028B5D3  004b00                  add      byte ptr [ebx], cl             
  0x0028B5D6  2000                    and      byte ptr [eax], al             
  0x0028B5D8  91                      xchg     ecx, eax                       
  0x0028B5D9  1e                      push     ds                             
  0x0028B5DA  0c00                    or       al, 0                          
  0x0028B5DC  00ae2100111c            add      byte ptr [esi + 0x1c110021], ch 
  0x0028B5E2  0c00                    or       al, 0                          
  0x0028B5E4  0c00                    or       al, 0                          
  0x0028B5E6  0000                    add      byte ptr [eax], al             
  0x0028B5E8  1bf4                    sbb      esi, esp                       
  0x0028B5EA  61                      popal                                   
  0x0028B5EB  0012                    add      byte ptr [edx], dl             
  0x0028B5ED  0e                      push     cs                             
  0x0028B5EE  0000                    add      byte ptr [eax], al             
  0x0028B5F0  00f4                    add      ah, dh                         
  0x0028B5F2  46                      inc      esi                            
  0x0028B5F3  00ff                    add      bh, bh                         
  0x0028B5F5  0000                    add      byte ptr [eax], al             
  0x0028B5F7  0000                    add      byte ptr [eax], al             
  0x0028B5F9  48                      dec      eax                            
  0x0028B5FA  2000                    and      byte ptr [eax], al             
  0x0028B5FC  10d8                    adc      al, bl                         
  0x0028B5FE  06                      push     es                             
  0x0028B5FF  000d0000005e            add      byte ptr [0x5e000000], cl      
  0x0028B605  ae                      scasb    al, byte ptr es:[edi]          
  0x0028B606  2100                    and      dword ptr [eax], eax           
  0x0028B608  00f8                    add      al, bh                         
  0x0028B60A  44                      inc      esp                            
  0x0028B60B  0000                    add      byte ptr [eax], al             
  0x0028B60D  b92100d01e              mov      ecx, 0x1ed00021                
  0x0028B612  0c00                    or       al, 0                          
  0x0028B614  42                      inc      edx                            
  0x0028B615  0020                    add      byte ptr [eax], ah             
  0x0028B617  0000                    add      byte ptr [eax], al             
  0x0028B619  e94c004300              jmp      0x6bb66a                       
  0x0028B61E  2000                    and      byte ptr [eax], al             
  0x0028B620  56                      push     esi                            
  0x0028B622  2100                    and      dword ptr [eax], eax           
  0x0028B624  00992100d11e            add      byte ptr [ecx + 0x1ed10021], bl 
  0x0028B62A  0c00                    or       al, 0                          
  0x0028B62C  00e9                    add      cl, ch                         
  0x0028B62E  4c                      dec      esp                            
  0x0028B62F  004b00                  add      byte ptr [ebx], cl             
  0x0028B632  2000                    and      byte ptr [eax], al             
  0x0028B634  91                      xchg     ecx, eax                       
  0x0028B635  1e                      push     ds                             
  0x0028B636  0c00                    or       al, 0                          
  0x0028B638  00ae2100111c            add      byte ptr [esi + 0x1c110021], ch 
  0x0028B63E  0c00                    or       al, 0                          
  0x0028B640  0c00                    or       al, 0                          
  0x0028B642  0000                    add      byte ptr [eax], al             
  0x0028B644  180400                  sbb      byte ptr [eax + eax], al       
  0x0028B647  0018                    add      byte ptr [eax], bl             
  0x0028B649  0400                    add      al, 0                          
  0x0028B64B  0018                    add      byte ptr [eax], bl             
  0x0028B64D  0400                    add      al, 0                          
  0x0028B64F  002a                    add      byte ptr [edx], ch             
  0x0028B651  0400                    add      al, 0                          
  0x0028B653  002a                    add      byte ptr [edx], ch             
  0x0028B655  0400                    add      al, 0                          
  0x0028B657  002a                    add      byte ptr [edx], ch             
  0x0028B659  0400                    add      al, 0                          
  0x0028B65B  002504000042            add      byte ptr [0x42000004], ah      
  0x0028B661  0400                    add      al, 0                          
  0x0028B663  004204                  add      byte ptr [edx + 4], al         
  0x0028B666  0000                    add      byte ptr [eax], al             
  0x0028B668  42                      inc      edx                            
  0x0028B669  0400                    add      al, 0                          
  0x0028B66B  004204                  add      byte ptr [edx + 4], al         
  0x0028B66E  0000                    add      byte ptr [eax], al             
  0x0028B670  42                      inc      edx                            
  0x0028B671  0400                    add      al, 0                          
  0x0028B673  004204                  add      byte ptr [edx + 4], al         
  0x0028B676  0000                    add      byte ptr [eax], al             
  0x0028B678  42                      inc      edx                            
  0x0028B679  0400                    add      al, 0                          
  0x0028B67B  004204                  add      byte ptr [edx + 4], al         
  0x0028B67E  0000                    add      byte ptr [eax], al             
  0x0028B680  42                      inc      edx                            
  0x0028B681  0400                    add      al, 0                          
  0x0028B683  004204                  add      byte ptr [edx + 4], al         
  0x0028B686  0000                    add      byte ptr [eax], al             
  0x0028B688  42                      inc      edx                            
  0x0028B689  0400                    add      al, 0                          
  0x0028B68B  004204                  add      byte ptr [edx + 4], al         
  0x0028B68E  0000                    add      byte ptr [eax], al             
  0x0028B690  42                      inc      edx                            
  0x0028B691  0400                    add      al, 0                          
  0x0028B693  004e04                  add      byte ptr [esi + 4], cl         
  0x0028B696  0000                    add      byte ptr [eax], al             
  0x0028B698  4e                      dec      esi                            
  0x0028B699  0400                    add      al, 0                          
  0x0028B69B  004e04                  add      byte ptr [esi + 4], cl         
  0x0028B69E  0000                    add      byte ptr [eax], al             
  0x0028B6A0  5f                      pop      edi                            
  0x0028B6A1  0400                    add      al, 0                          
  0x0028B6A3  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6A6  0000                    add      byte ptr [eax], al             
  0x0028B6A8  5f                      pop      edi                            
  0x0028B6A9  0400                    add      al, 0                          
  0x0028B6AB  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6AE  0000                    add      byte ptr [eax], al             
  0x0028B6B0  5f                      pop      edi                            
  0x0028B6B1  0400                    add      al, 0                          
  0x0028B6B3  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6B6  0000                    add      byte ptr [eax], al             
  0x0028B6B8  5f                      pop      edi                            
  0x0028B6B9  0400                    add      al, 0                          
  0x0028B6BB  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6BE  0000                    add      byte ptr [eax], al             
  0x0028B6C0  5f                      pop      edi                            
  0x0028B6C1  0400                    add      al, 0                          
  0x0028B6C3  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6C6  0000                    add      byte ptr [eax], al             
  0x0028B6C8  5f                      pop      edi                            
  0x0028B6C9  0400                    add      al, 0                          
  0x0028B6CB  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6CE  0000                    add      byte ptr [eax], al             
  0x0028B6D0  5f                      pop      edi                            
  0x0028B6D1  0400                    add      al, 0                          
  0x0028B6D3  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6D6  0000                    add      byte ptr [eax], al             
  0x0028B6D8  5f                      pop      edi                            
  0x0028B6D9  0400                    add      al, 0                          
  0x0028B6DB  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6DE  0000                    add      byte ptr [eax], al             
  0x0028B6E0  5f                      pop      edi                            
  0x0028B6E1  0400                    add      al, 0                          
  0x0028B6E3  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6E6  0000                    add      byte ptr [eax], al             
  0x0028B6E8  5f                      pop      edi                            
  0x0028B6E9  0400                    add      al, 0                          
  0x0028B6EB  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6EE  0000                    add      byte ptr [eax], al             
  0x0028B6F0  5f                      pop      edi                            
  0x0028B6F1  0400                    add      al, 0                          
  0x0028B6F3  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6F6  0000                    add      byte ptr [eax], al             
  0x0028B6F8  5f                      pop      edi                            
  0x0028B6F9  0400                    add      al, 0                          
  0x0028B6FB  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B6FE  0000                    add      byte ptr [eax], al             
  0x0028B700  5f                      pop      edi                            
  0x0028B701  0400                    add      al, 0                          
  0x0028B703  005f04                  add      byte ptr [edi + 4], bl         
  0x0028B706  0000                    add      byte ptr [eax], al             
  0x0028B708  5f                      pop      edi                            
  0x0028B709  0400                    add      al, 0                          
  0x0028B70B  0000                    add      byte ptr [eax], al             
  0x0028B70D  b122                    mov      cl, 0x22                       
  0x0028B70F  0000                    add      byte ptr [eax], al             
  0x0028B711  1923                    sbb      dword ptr [ebx], esp           
  0x0028B713  0000                    add      byte ptr [eax], al             
  0x0028B715  48                      dec      eax                            
  0x0028B716  2000                    and      byte ptr [eax], al             
  0x0028B718  004920                  add      byte ptr [ecx + 0x20], cl      
  0x0028B71B  001b                    add      byte ptr [ebx], bl             
  0x0028B71D  f4                      hlt                                     
  0x0028B71E  45                      inc      ebp                            
  0x0028B71F  004000                  add      byte ptr [eax], al             
  0x0028B722  0000                    add      byte ptr [eax], al             
  0x0028B724  00f4                    add      ah, dh                         
  0x0028B726  51                      push     ecx                            
  0x0028B727  0000                    add      byte ptr [eax], al             
  0x0028B729  0c00                    or       al, 0                          
  0x0028B72B  0001                    add      byte ptr [ecx], al             
  0x0028B72D  d8440010                fadd     dword ptr [eax + eax + 0x10]   
  0x0028B731  dc06                    fadd     qword ptr [esi]                
  0x0028B733  0003                    add      byte ptr [ebx], al             
  0x0028B735  0000                    add      byte ptr [eax], al             
  0x0028B737  00a6d8440001            add      byte ptr [esi + 0x10044d8], ah 
  0x0028B73D  59                      pop      ecx                            
  0x0028B73E  50                      push     eax                            
  0x0028B73F  0000                    add      byte ptr [eax], al             
  0x0028B741  002400                  add      byte ptr [eax + eax], ah       
  0x0028B744  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028B747  009204000000            add      byte ptr [edx + 4], dl         
  0x0028B74D  002400                  add      byte ptr [eax + eax], ah       
  0x0028B750  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028B753  009104000000            add      byte ptr [ecx + 4], dl         
  0x0028B759  1023                    adc      byte ptr [ebx], ah             
  0x0028B75B  0000                    add      byte ptr [eax], al             
  0x0028B75D  b8220000f4              mov      eax, 0xf4000022                
  0x0028B762  7400                    je       0x28b764                       
                                        ; XREF: 0x0028B762 (cond_jump)
  0x0028B764  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x0028B765  0300                    add      eax, dword ptr [eax]           
  0x0028B767  0000                    add      byte ptr [eax], al             
  0x0028B769  f4                      hlt                                     
  0x0028B76A  650032                  add      byte ptr gs:[edx], dh          
  0x0028B76D  0b00                    or       eax, dword ptr [eax]           
  0x0028B76F  0000                    add      byte ptr [eax], al             
  0x0028B772  44                      inc      esp                            
  0x0028B773  007b0b                  add      byte ptr [ebx + 0xb], bh       
  0x0028B776  0000                    add      byte ptr [eax], al             
  0x0028B778  00f4                    add      ah, dh                         
  0x0028B77A  46                      inc      esi                            
  0x0028B77B  0032                    add      byte ptr [edx], dh             
  0x0028B77D  0000                    add      byte ptr [eax], al             
  0x0028B77F  00d0                    add      al, dl                         
  0x0028B781  44                      inc      esp                            
  0x0028B782  2200                    and      al, byte ptr [eax]             
  0x0028B784  2e1d0c0040f4            sbb      eax, 0xf440000c                
  0x0028B78A  44                      inc      esp                            
  0x0028B78B  001c0c                  add      byte ptr [esp + ecx], bl       
  0x0028B78E  0000                    add      byte ptr [eax], al             
  0x0028B790  40                      inc      eax                            
  0x0028B791  0020                    add      byte ptr [eax], ah             
  0x0028B793  0000                    add      byte ptr [eax], al             
  0x0028B795  96                      xchg     esi, eax                       
  0x0028B796  2100                    and      dword ptr [eax], eax           
  0x0028B798  0001                    add      byte ptr [ecx], al             
  0x0028B79A  3900                    cmp      dword ptr [eax], eax           
  0x0028B79C  ce                      into                                    
  0x0028B79D  720b                    jb       0x28b7aa                       
  0x0028B79F  001a                    add      byte ptr [edx], bl             
  0x0028B7A1  0f0000                  sldt     word ptr [eax]                 
  0x0028B7A4  00c4                    add      ah, al                         
  0x0028B7A6  2300                    and      eax, dword ptr [eax]           
  0x0028B7A8  45                      inc      ebp                            
  0x0028B7A9  07                      pop      es                             
                                        ; XREF: 0x0028B79D (cond_jump)
  0x0028B7AA  2200                    and      al, byte ptr [eax]             
  0x0028B7AC  40                      inc      eax                            
  0x0028B7AD  7002                    jo       0x28b7b1                       
  0x0028B7AF  00742423                add      byte ptr [esp + 0x23], dh      
  0x0028B7B3  0044e857                add      byte ptr [eax + ebp*8 + 0x57], al 
  0x0028B7B7  0000                    add      byte ptr [eax], al             
  0x0028B7B9  58                      pop      eax                            
  0x0028B7BA  2000                    and      byte ptr [eax], al             
  0x0028B7BC  00e8                    add      al, ch                         
  0x0028B7BE  45                      inc      ebp                            
  0x0028B7BF  000da4050000            add      byte ptr [0x5a4], cl           
  0x0028B7C5  f4                      hlt                                     
  0x0028B7C6  47                      inc      edi                            
  0x0028B7C7  00d1                    add      cl, dl                         
  0x0028B7C9  0000                    add      byte ptr [eax], al             
  0x0028B7CB  0010                    add      byte ptr [eax], dl             
  0x0028B7CD  cc                      int3                                    
  0x0028B7CE  06                      push     es                             
  0x0028B7CF  0009                    add      byte ptr [ecx], cl             
  0x0028B7D1  0000                    add      byte ptr [eax], al             
  0x0028B7D3  006cee21                add      byte ptr [esi + ebp*8 + 0x21], ch 
  0x0028B7D7  006090                  add      byte ptr [eax - 0x70], ah      
  0x0028B7DA  0200                    add      al, byte ptr [eax]             
  0x0028B7DC  2e58                    pop      eax                            
  0x0028B7DE  2000                    and      byte ptr [eax], al             
  0x0028B7E0  2be8                    sub      ebp, eax                       
  0x0028B7E2  45                      inc      ebp                            
  0x0028B7E3  007dbd                  add      byte ptr [ebp - 0x43], bh      
  0x0028B7E6  2100                    and      dword ptr [eax], eax           
  0x0028B7E8  00ed                    add      ch, ch                         
  0x0028B7EA  4c                      dec      esp                            
  0x0028B7EB  00402f                  add      byte ptr [eax + 0x2f], al      
  0x0028B7EE  2000                    and      byte ptr [eax], al             
  0x0028B7F0  00cf                    add      bh, cl                         
  0x0028B7F2  2100                    and      dword ptr [eax], eax           
  0x0028B7F4  00542200                add      byte ptr [edx], dl             
  0x0028B7F8  61                      popal                                   
  0x0028B7F9  f4                      hlt                                     
  0x0028B7FA  44                      inc      esp                            
  0x0028B7FB  0000                    add      byte ptr [eax], al             
  0x0028B7FD  0100                    add      dword ptr [eax], eax           
  0x0028B7FF  0094ec070044f0          add      byte ptr [esp + ebp*8 - 0xfbbfff9], dl 
  0x0028B806  47                      inc      edi                            
  0x0028B807  009104000080            add      byte ptr [ecx - 0x7ffffffc], dl 
  0x0028B80D  e40a                    in       al, 0xa                        
  0x0028B80F  000d70570093            add      byte ptr [0x93005770], cl      
  0x0028B815  0400                    add      al, 0                          
  0x0028B817  0008                    add      byte ptr [eax], cl             
  0x0028B819  f4                      hlt                                     
  0x0028B81A  05006dee20              add      eax, 0x20ee6d00                
  0x0028B81F  0058f4                  add      byte ptr [eax - 0xc], bl       
  0x0028B822  0500c44001              add      eax, 0x140c400                 
  0x0028B827  004000                  add      byte ptr [eax], al             
  0x0028B82A  0000                    add      byte ptr [eax], al             
  0x0028B82C  1329                    adc      ebp, dword ptr [ecx]           
  0x0028B82E  2000                    and      byte ptr [eax], al             
  0x0028B830  00872100530c            add      byte ptr [edi + 0xc530021], al 
  0x0028B836  050000f447              add      eax, 0x47f40000                
  0x0028B83B  008001000050            add      byte ptr [eax + 0x50000001], al 
  0x0028B841  0c05                    or       al, 5                          
  0x0028B843  0000                    add      byte ptr [eax], al             
  0x0028B845  8621                    xchg     byte ptr [ecx], ah             
  0x0028B847  0000                    add      byte ptr [eax], al             
  0x0028B849  ce                      into                                    
  0x0028B84A  2300                    and      eax, dword ptr [eax]           
  0x0028B84C  854701                  test     dword ptr [edi + 1], eax       
  0x0028B84F  000da4050000            add      byte ptr [0x5a4], cl           
  0x0028B855  ce                      into                                    
  0x0028B856  2000                    and      byte ptr [eax], al             
  0x0028B858  0d00200008              or       eax, 0x8002000                 
  0x0028B85D  f4                      hlt                                     
  0x0028B85E  05006dee20              add      eax, 0x20ee6d00                
  0x0028B863  0008                    add      byte ptr [eax], cl             
  0x0028B865  f4                      hlt                                     
  0x0028B866  0500c44001              add      eax, 0x140c400                 
  0x0028B86B  004000                  add      byte ptr [eax], al             
  0x0028B86E  0000                    add      byte ptr [eax], al             
  0x0028B870  1329                    adc      ebp, dword ptr [ecx]           
  0x0028B872  2000                    and      byte ptr [eax], al             
  0x0028B874  00872100030c            add      byte ptr [edi + 0xc030021], al 
  0x0028B87A  050000f447              add      eax, 0x47f40000                
  0x0028B87F  008001000000            add      byte ptr [eax + 1], al         
  0x0028B886  44                      inc      esp                            
  0x0028B887  00930400004d            add      byte ptr [ebx + 0x4d000004], dl 
  0x0028B88E  56                      push     esi                            
  0x0028B88F  009204000000            add      byte ptr [edx + 4], dl         
  0x0028B895  7055                    jo       0x28b8ec                       
  0x0028B897  009304000004            add      byte ptr [ebx + 0x4000004], dl 
  0x0028B89D  94                      xchg     esp, eax                       
  0x0028B89E  0500002e23              add      eax, 0x232e0000                
  0x0028B8A3  0000                    add      byte ptr [eax], al             
  0x0028B8A5  7071                    jo       0x28b918                       
  0x0028B8A7  009204000003            add      byte ptr [edx + 0x3000004], dl 
  0x0028B8AD  0020                    add      byte ptr [eax], ah             
  0x0028B8AF  0014a4                  add      byte ptr [esp], dl             
  0x0028B8B2  05001e0c05              add      eax, 0x50c1e00                 
  0x0028B8B7  000d00200008            add      byte ptr [0x8002000], cl       
  0x0028B8BD  f4                      hlt                                     
  0x0028B8BE  05006dee20              add      eax, 0x20ee6d00                
  0x0028B8C3  001a                    add      byte ptr [edx], bl             
  0x0028B8C5  f4                      hlt                                     
  0x0028B8C6  0500c44001              add      eax, 0x140c400                 
  0x0028B8CB  004000                  add      byte ptr [eax], al             
  0x0028B8CE  0000                    add      byte ptr [eax], al             
  0x0028B8D0  1329                    adc      ebp, dword ptr [ecx]           
  0x0028B8D2  2000                    and      byte ptr [eax], al             
  0x0028B8D4  00872100150c            add      byte ptr [edi + 0xc150021], al 
  0x0028B8DA  050000f447              add      eax, 0x47f40000                
  0x0028B8DF  004001                  add      byte ptr [eax + 1], al         
  0x0028B8E2  0000                    add      byte ptr [eax], al             
  0x0028B8E4  120c0500710020          adc      cl, byte ptr [eax + 0x20007100] 
  0x0028B8EB  00c4                    add      ah, al                         
  0x0028B8ED  40                      inc      eax                            
  0x0028B8EE  0100                    add      dword ptr [eax], eax           
  0x0028B8F0  800000                  add      byte ptr [eax], 0              
  0x0028B8F3  0013                    add      byte ptr [ebx], dl             
  0x0028B8F5  2920                    sub      dword ptr [eax], esp           
  0x0028B8F7  0000                    add      byte ptr [eax], al             
  0x0028B8F9  8721                    xchg     dword ptr [ecx], esp           
  0x0028B8FB  000c0c                  add      byte ptr [esp + ecx], cl       
  0x0028B8FE  050001f044              add      eax, 0x44f00100                
  0x0028B903  008f04000044            add      byte ptr [edi + 0x44000004], cl 
  0x0028B90A  44                      inc      esp                            
  0x0028B90B  008e04000001            add      byte ptr [esi + 0x1000004], cl 
  0x0028B911  7054                    jo       0x28b967                       
  0x0028B913  008b04000044            add      byte ptr [ebx + 0x44000004], cl 
  0x0028B919  7047                    jo       0x28b962                       
  0x0028B91B  009104000074            add      byte ptr [ecx + 0x74000004], dl 
  0x0028B921  7054                    jo       0x28b977                       
  0x0028B923  008a0400001b            add      byte ptr [edx + 0x1b000004], cl 
  0x0028B929  0c05                    or       al, 5                          
  0x0028B92B  0000                    add      byte ptr [eax], al             
  0x0028B92E  56                      push     esi                            
  0x0028B92F  008b04000000            add      byte ptr [ebx + 4], cl         
  0x0028B936  44                      inc      esp                            
  0x0028B937  008d04000044            add      byte ptr [ebp + 0x44000004], cl 
  0x0028B93E  44                      inc      esp                            
  0x0028B93F  008f04000001            add      byte ptr [edi + 0x1000004], cl 
  0x0028B945  8621                    xchg     byte ptr [ecx], ah             
  0x0028B947  0044f045                add      byte ptr [eax + esi*8 + 0x45], al 
  0x0028B94B  008a04000055            add      byte ptr [edx + 0x55000004], cl 
  0x0028B952  44                      inc      esp                            
  0x0028B953  008c0400005090          add      byte ptr [esp + eax - 0x6fb00000], cl 
  0x0028B95A  0200                    add      al, byte ptr [eax]             
  0x0028B95C  61                      popal                                   
  0x0028B95D  7054                    jo       0x28b9b3                       
  0x0028B95F  008b04000044            add      byte ptr [ebx + 0x44000004], cl 
  0x0028B966  44                      inc      esp                            
                                        ; XREF: 0x0028B911 (cond_jump)
  0x0028B967  008e04000001            add      byte ptr [esi + 0x1000004], cl 
  0x0028B96D  8621                    xchg     byte ptr [ecx], ah             
  0x0028B96F  00447047                add      byte ptr [eax + esi*2 + 0x47], al 
  0x0028B973  009104000055            add      byte ptr [ecx + 0x55000004], dl 
  0x0028B97A  44                      inc      esp                            
  0x0028B97B  008b04000050            add      byte ptr [ebx + 0x50000004], cl 
  0x0028B981  90                      nop                                     
  0x0028B982  0200                    add      al, byte ptr [eax]             
  0x0028B984  7470                    je       0x28b9f6                       
  0x0028B986  54                      push     esp                            
  0x0028B987  008a04000045            add      byte ptr [edx + 0x45000004], cl 
  0x0028B98D  0020                    add      byte ptr [eax], ah             
  0x0028B98F  004090                  add      byte ptr [eax - 0x70], al      
  0x0028B992  0200                    add      al, byte ptr [eax]             
  0x0028B994  00f0                    add      al, dh                         
  0x0028B996  44                      inc      esp                            
  0x0028B997  00900400004c            add      byte ptr [eax + 0x4c000004], dl 
  0x0028B99D  de4e00                  fimul    word ptr [esi]                 
  0x0028B9A0  851c0c                  test     dword ptr [esp + ecx], ebx     
  0x0028B9A3  001429                  add      byte ptr [ecx + ebp], dl       
  0x0028B9A6  2000                    and      byte ptr [eax], al             
  0x0028B9A8  55                      push     ebp                            
  0x0028B9A9  0020                    add      byte ptr [eax], ah             
  0x0028B9AB  005090                  add      byte ptr [eax - 0x70], dl      
  0x0028B9AE  0200                    add      al, byte ptr [eax]             
  0x0028B9B0  006a54                  add      byte ptr [edx + 0x54], ch      
                                        ; XREF: 0x0028B95D (cond_jump)
  0x0028B9B3  0000                    add      byte ptr [eax], al             
  0x0028B9B5  0e                      push     cs                             
  0x0028B9B6  2200                    and      al, byte ptr [eax]             
  0x0028B9B8  00c4                    add      ah, al                         
  0x0028B9BA  2300                    and      eax, dword ptr [eax]           
  0x0028B9BC  45                      inc      ebp                            
  0x0028B9BD  5a                      pop      edx                            
  0x0028B9BE  2000                    and      byte ptr [eax], al             
  0x0028B9C0  d7                      xlatb                                   
  0x0028B9C1  96                      xchg     esi, eax                       
  0x0028B9C2  05000c0000              add      eax, 0xc00                     
  0x0028B9C7  0000                    add      byte ptr [eax], al             
  0x0028B9CA  56                      push     esi                            
  0x0028B9CB  00b704000003            add      byte ptr [edi + 0x3000004], dh 
  0x0028B9D2  44                      inc      esp                            
  0x0028B9D3  00a204000007            add      byte ptr [edx + 0x7000004], ah 
  0x0028B9D9  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028B9DA  050000ee20              add      eax, 0x20ee0000                
  0x0028B9DF  00640024                add      byte ptr [eax + eax + 0x24], ah 
  0x0028B9E3  0010                    add      byte ptr [eax], dl             
  0x0028B9E5  cc                      int3                                    
  0x0028B9E6  06                      push     es                             
  0x0028B9E7  0002                    add      byte ptr [edx], al             
  0x0028B9E9  0000                    add      byte ptr [eax], al             
  0x0028B9EB  0000                    add      byte ptr [eax], al             
  0x0028B9ED  59                      pop      ecx                            
  0x0028B9EE  44                      inc      esp                            
  0x0028B9EF  004d0c                  add      byte ptr [ebp + 0xc], cl       
  0x0028B9F2  050000f464              add      eax, 0x64f40000                
  0x0028B9F7  00ba0c000000            add      byte ptr [edx + 0xc], bh       
  0x0028B9FD  f4                      hlt                                     
  0x0028B9FE  6600a504000000          add      byte ptr [ebp + 4], ah         
  0x0028BA05  da5700                  ficom    dword ptr [edi]                
  0x0028BA08  4c                      dec      esp                            
  0x0028BA0A  46                      inc      esi                            
  0x0028BA0B  00bf0400005c            add      byte ptr [edi + 0x5c000004], bh 
  0x0028BA11  0020                    add      byte ptr [eax], ah             
  0x0028BA13  001b                    add      byte ptr [ebx], bl             
  0x0028BA15  2920                    sub      dword ptr [eax], esp           
  0x0028BA17  00ce                    add      dh, cl                         
  0x0028BA19  40                      inc      eax                            
  0x0028BA1A  0100                    add      dword ptr [eax], eax           
  0x0028BA1C  e01f                    loopne   0x28ba3d                       
  0x0028BA1E  0000                    add      byte ptr [eax], al             
  0x0028BA20  58                      pop      eax                            
  0x0028BA21  dd5e00                  fstp     qword ptr [esi]                
  0x0028BA24  7500                    jne      0x28ba26                       
                                        ; XREF: 0x0028BA24 (cond_jump)
  0x0028BA26  2000                    and      byte ptr [eax], al             
  0x0028BA28  7070                    jo       0x28ba9a                       
  0x0028BA2A  0200                    add      al, byte ptr [eax]             
  0x0028BA2C  64c521                  lds      esp, ptr fs:[ecx]              
  0x0028BA2F  0084410100009e          add      byte ptr [ecx + eax*2 - 0x61ffffff], al 
  0x0028BA36  2100                    and      dword ptr [eax], eax           
  0x0028BA38  00d8                    add      al, bl                         
  0x0028BA3A  56                      push     esi                            
  0x0028BA3B  0014f4                  add      byte ptr [esp + esi*8], dl     
  0x0028BA3E  46                      inc      esi                            
  0x0028BA3F  003f                    add      byte ptr [edi], bh             
  0x0028BA41  0000                    add      byte ptr [eax], al             
  0x0028BA43  0013                    add      byte ptr [ebx], dl             
  0x0028BA45  2920                    sub      dword ptr [eax], esp           
  0x0028BA47  00ca                    add      dl, cl                         
  0x0028BA49  1e                      push     ds                             
  0x0028BA4A  0c00                    or       al, 0                          
  0x0028BA4C  55                      push     ebp                            
  0x0028BA4D  0020                    add      byte ptr [eax], ah             
  0x0028BA4F  005070                  add      byte ptr [eax + 0x70], dl      
  0x0028BA52  0200                    add      al, byte ptr [eax]             
  0x0028BA54  009c210010de06          add      byte ptr [ecx + 0x6de1000], bl 
  0x0028BA5B  000b                    add      byte ptr [ebx], cl             
  0x0028BA5D  0000                    add      byte ptr [eax], al             
  0x0028BA5F  0000                    add      byte ptr [eax], al             
  0x0028BA61  d85600                  fcom     dword ptr [esi]                
  0x0028BA64  14ec                    adc      al, 0xec                       
  0x0028BA66  7e00                    jle      0x28ba68                       
                                        ; XREF: 0x0028BA66 (cond_jump)
  0x0028BA68  1329                    adc      ebp, dword ptr [ecx]           
  0x0028BA6A  2000                    and      byte ptr [eax], al             
  0x0028BA6C  ca1e0c                  retf     0xc1e                          
  0x0028BA6F  005559                  add      byte ptr [ebp + 0x59], dl      
  0x0028BA72  7600                    jbe      0x28ba74                       
                                        ; XREF: 0x0028BA72 (cond_jump)
  0x0028BA74  50                      push     eax                            
  0x0028BA75  7002                    jo       0x28ba79                       
  0x0028BA77  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028BA75 (cond_jump)
  0x0028BA79  9c                      pushfd                                  
  0x0028BA7A  2100                    and      dword ptr [eax], eax           
  0x0028BA7C  00ee                    add      dh, ch                         
  0x0028BA7E  56                      push     esi                            
  0x0028BA7F  008041010000            add      byte ptr [eax + 0x141], al     
  0x0028BA85  6e                      outsb    dx, byte ptr [esi]             
  0x0028BA86  54                      push     esp                            
  0x0028BA87  0000                    add      byte ptr [eax], al             
  0x0028BA89  ec                      in       al, dx                         
  0x0028BA8A  7e00                    jle      0x28ba8c                       
                                        ; XREF: 0x0028BA8A (cond_jump)
  0x0028BA8C  005976                  add      byte ptr [ecx + 0x76], bl      
  0x0028BA8F  0000                    add      byte ptr [eax], al             
  0x0028BA91  ee                      out      dx, al                         
  0x0028BA92  56                      push     esi                            
  0x0028BA93  008041010071            add      byte ptr [eax + 0x71000141], al 
  0x0028BA99  6e                      outsb    dx, byte ptr [esi]             
                                        ; XREF: 0x0028BA28 (cond_jump)
  0x0028BA9A  54                      push     esp                            
  0x0028BA9B  006500                  add      byte ptr [ebp], ah             
  0x0028BA9E  2000                    and      byte ptr [eax], al             
  0x0028BAA0  99                      cdq                                     
  0x0028BAA1  7705                    ja       0x28baa8                       
  0x0028BAA3  000c00                  add      byte ptr [eax + eax], cl       
  0x0028BAA6  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028BAA1 (cond_jump)
  0x0028BAA8  00f4                    add      ah, dh                         
  0x0028BAAA  60                      pushal                                  
  0x0028BAAB  00680b                  add      byte ptr [eax + 0xb], ch       
  0x0028BAAE  0000                    add      byte ptr [eax], al             
  0x0028BAB0  00f0                    add      al, dh                         
  0x0028BAB2  7000                    jo       0x28bab4                       
                                        ; XREF: 0x0028BAB2 (cond_jump)
  0x0028BAB4  40                      inc      eax                            
  0x0028BAB5  0b00                    or       eax, dword ptr [eax]           
  0x0028BAB7  0000                    add      byte ptr [eax], al             
  0x0028BAB9  e8570000f0              call     0xf028bb15                     
  0x0028BABE  44                      inc      esp                            
  0x0028BABF  007a0b                  add      byte ptr [edx + 0xb], bh       
  0x0028BAC2  0000                    add      byte ptr [eax], al             
  0x0028BAC4  4c                      dec      esp                            
  0x0028BAC5  0020                    add      byte ptr [eax], ah             
  0x0028BAC7  000b                    add      byte ptr [ebx], cl             
  0x0028BAC9  0020                    add      byte ptr [eax], ah             
  0x0028BACB  000c14                  add      byte ptr [esp + edx], cl       
  0x0028BACE  0500130020              add      eax, 0x20001300                
  0x0028BAD3  0000                    add      byte ptr [eax], al             
  0x0028BAD5  7056                    jo       0x28bb2d                       
  0x0028BAD7  00660b                  add      byte ptr [esi + 0xb], ah       
  0x0028BADA  0000                    add      byte ptr [eax], al             
  0x0028BADC  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028BADF  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028BAE2  0000                    add      byte ptr [eax], al             
  0x0028BAE4  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028BAE7  00a40400000070          add      byte ptr [esp + eax + 0x70000000], ah 
  0x0028BAEE  56                      push     esi                            
  0x0028BAEF  006e0b                  add      byte ptr [esi + 0xb], ch       
  0x0028BAF2  0000                    add      byte ptr [eax], al             
  0x0028BAF4  c0100d                  rcl      byte ptr [eax], 0xd            
  0x0028BAF7  0027                    add      byte ptr [edi], ah             
  0x0028BAF9  0000                    add      byte ptr [eax], al             
  0x0028BAFB  0013                    add      byte ptr [ebx], dl             
  0x0028BAFD  0020                    add      byte ptr [eax], ah             
  0x0028BAFF  0000                    add      byte ptr [eax], al             
  0x0028BB01  d821                    fsub     dword ptr [ecx]                
  0x0028BB03  0000                    add      byte ptr [eax], al             
  0x0028BB06  44                      inc      esp                            
  0x0028BB07  00700b                  add      byte ptr [eax + 0xb], dh       
  0x0028BB0A  0000                    add      byte ptr [eax], al             
  0x0028BB0C  45                      inc      ebp                            
  0x0028BB0D  0020                    add      byte ptr [eax], ah             
  0x0028BB0F  000494                  add      byte ptr [esp + edx*4], al     
  0x0028BB12  050000f456              add      eax, 0x56f40000                
  0x0028BB17  0009                    add      byte ptr [ecx], cl             
  0x0028BB19  0000                    add      byte ptr [eax], al             
  0x0028BB1B  0000                    add      byte ptr [eax], al             
  0x0028BB1D  d821                    fsub     dword ptr [ecx]                
  0x0028BB1F  000500200009            add      byte ptr [0x9002000], al       
  0x0028BB25  f4                      hlt                                     
  0x0028BB26  0500130020              add      eax, 0x20001300                
  0x0028BB2B  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028BAD5 (cond_jump)
  0x0028BB2D  7056                    jo       0x28bb85                       
  0x0028BB2F  00660b                  add      byte ptr [esi + 0xb], ah       
  0x0028BB32  0000                    add      byte ptr [eax], al             
  0x0028BB34  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028BB37  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028BB3A  0000                    add      byte ptr [eax], al             
  0x0028BB3C  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028BB3F  00a4040000130c          add      byte ptr [esp + eax + 0xc130000], ah 
  0x0028BB46  050000f456              add      eax, 0x56f40000                
  0x0028BB4B  0001                    add      byte ptr [ecx], al             
  0x0028BB4D  0000                    add      byte ptr [eax], al             
  0x0028BB4F  0000                    add      byte ptr [eax], al             
  0x0028BB51  7056                    jo       0x28bba9                       
  0x0028BB53  00660b                  add      byte ptr [esi + 0xb], ah       
  0x0028BB56  0000                    add      byte ptr [eax], al             
  0x0028BB58  00ee                    add      dh, ch                         
  0x0028BB5A  2100                    and      dword ptr [eax], eax           
  0x0028BB5C  000423                  add      byte ptr [ebx], al             
  0x0028BB5F  00440020                add      byte ptr [eax + eax + 0x20], al 
  0x0028BB63  0006                    add      byte ptr [esi], al             
  0x0028BB65  1c0c                    sbb      al, 0xc                        
  0x0028BB67  0000                    add      byte ptr [eax], al             
  0x0028BB69  0028                    add      byte ptr [eax], ch             
  0x0028BB6B  0000                    add      byte ptr [eax], al             
  0x0028BB6D  7056                    jo       0x28bbc5                       
  0x0028BB6F  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028BB72  0000                    add      byte ptr [eax], al             
  0x0028BB74  06                      push     es                             
  0x0028BB75  1d0c000004              sbb      eax, 0x400000c                 
  0x0028BB7A  2300                    and      eax, dword ptr [eax]           
  0x0028BB7C  40                      inc      eax                            
  0x0028BB7D  0020                    add      byte ptr [eax], ah             
  0x0028BB7F  0000                    add      byte ptr [eax], al             
  0x0028BB81  7056                    jo       0x28bbd9                       
  0x0028BB83  00a404000000c4          add      byte ptr [esp + eax - 0x3c000000], ah 
  0x0028BB8A  2100                    and      dword ptr [eax], eax           
  0x0028BB8C  4c                      dec      esp                            
  0x0028BB8D  0020                    add      byte ptr [eax], ah             
  0x0028BB8F  0000                    add      byte ptr [eax], al             
  0x0028BB92  56                      push     esi                            
  0x0028BB93  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028BB96  0000                    add      byte ptr [eax], al             
  0x0028BB98  00f4                    add      ah, dh                         
  0x0028BB9A  44                      inc      esp                            
  0x0028BB9B  000500000045            add      byte ptr [0x45000000], al      
  0x0028BBA1  0020                    add      byte ptr [eax], ah             
  0x0028BBA3  0013                    add      byte ptr [ebx], dl             
  0x0028BBA5  2405                    and      al, 5                          
  0x0028BBA7  0000                    add      byte ptr [eax], al             
  0x0028BBAA  56                      push     esi                            
  0x0028BBAB  009f0b000000            add      byte ptr [edi + 0xb], bl       
  0x0028BBB2  44                      inc      esp                            
  0x0028BBB3  007a0b                  add      byte ptr [edx + 0xb], bh       
  0x0028BBB6  0000                    add      byte ptr [eax], al             
  0x0028BBB8  44                      inc      esp                            
  0x0028BBB9  0020                    add      byte ptr [eax], ah             
  0x0028BBBB  0000                    add      byte ptr [eax], al             
  0x0028BBBE  44                      inc      esp                            
  0x0028BBBF  00530b                  add      byte ptr [ebx + 0xb], dl       
  0x0028BBC2  0000                    add      byte ptr [eax], al             
  0x0028BBC4  44                      inc      esp                            
                                        ; XREF: 0x0028BB6D (cond_jump)
  0x0028BBC5  0020                    add      byte ptr [eax], ah             
  0x0028BBC7  0000                    add      byte ptr [eax], al             
  0x0028BBC9  d921                    fldenv   [ecx]                          
  0x0028BBCB  0000                    add      byte ptr [eax], al             
  0x0028BBCD  7057                    jo       0x28bc26                       
  0x0028BBCF  006e0b                  add      byte ptr [esi + 0xb], ch       
  0x0028BBD2  0000                    add      byte ptr [eax], al             
  0x0028BBD4  0300                    add      eax, dword ptr [eax]           
  0x0028BBD6  2000                    and      byte ptr [eax], al             
  0x0028BBD8  0494                    add      al, 0x94                       
  0x0028BBDA  0500050020              add      eax, 0x20000500                
  0x0028BBDF  0002                    add      byte ptr [edx], al             
  0x0028BBE1  f4                      hlt                                     
  0x0028BBE2  0500030c05              add      eax, 0x50c0300                 
  0x0028BBE7  0000                    add      byte ptr [eax], al             
  0x0028BBE9  2423                    and      al, 0x23                       
  0x0028BBEB  0000                    add      byte ptr [eax], al             
  0x0028BBEE  2000                    and      byte ptr [eax], al             
  0x0028BBF0  00f0                    add      al, dh                         
  0x0028BBF2  56                      push     esi                            
  0x0028BBF3  00700b                  add      byte ptr [eax + 0xb], dh       
  0x0028BBF6  0000                    add      byte ptr [eax], al             
  0x0028BBF8  0300                    add      eax, dword ptr [eax]           
  0x0028BBFA  2000                    and      byte ptr [eax], al             
  0x0028BBFC  0af4                    or       dh, ah                         
  0x0028BBFE  050000f444              add      eax, 0x44f40000                
  0x0028BC03  0001                    add      byte ptr [ecx], al             
  0x0028BC05  0000                    add      byte ptr [eax], al             
  0x0028BC07  0000                    add      byte ptr [eax], al             
  0x0028BC09  7044                    jo       0x28bc4f                       
  0x0028BC0B  00660b                  add      byte ptr [esi + 0xb], ah       
  0x0028BC0E  0000                    add      byte ptr [eax], al             
  0x0028BC10  00f0                    add      al, dh                         
  0x0028BC12  44                      inc      esp                            
  0x0028BC13  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028BC16  0000                    add      byte ptr [eax], al             
  0x0028BC18  40                      inc      eax                            
  0x0028BC19  0020                    add      byte ptr [eax], ah             
  0x0028BC1B  0000                    add      byte ptr [eax], al             
  0x0028BC1D  7056                    jo       0x28bc75                       
  0x0028BC1F  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028BC22  0000                    add      byte ptr [eax], al             
  0x0028BC24  0c00                    or       al, 0                          
                                        ; XREF: 0x0028BBCD (cond_jump)
  0x0028BC26  0000                    add      byte ptr [eax], al             
  0x0028BC28  0011                    add      byte ptr [ecx], dl             
  0x0028BC2A  2200                    and      al, byte ptr [eax]             
  0x0028BC2C  00b2220069f4            add      byte ptr [edx - 0xb96ffde], dh 
  0x0028BC32  46                      inc      esi                            
  0x0028BC33  0002                    add      byte ptr [edx], al             
  0x0028BC35  0000                    add      byte ptr [eax], al             
  0x0028BC37  0010                    add      byte ptr [eax], dl             
  0x0028BC39  d806                    fadd     dword ptr [esi]                
  0x0028BC3B  000500000000            add      byte ptr [0], al               
  0x0028BC41  c9                      leave                                   
  0x0028BC42  56                      push     esi                            
  0x0028BC43  00148f                  add      byte ptr [edi + ecx*4], dl     
  0x0028BC46  2100                    and      dword ptr [eax], eax           
  0x0028BC48  50                      push     eax                            
  0x0028BC49  0020                    add      byte ptr [eax], ah             
  0x0028BC4B  0000                    add      byte ptr [eax], al             
  0x0028BC4D  5a                      pop      edx                            
  0x0028BC4E  54                      push     esp                            
                                        ; XREF: 0x0028BC09 (cond_jump)
  0x0028BC4F  0000                    add      byte ptr [eax], al             
  0x0028BC51  4e                      dec      esi                            
  0x0028BC52  2300                    and      eax, dword ptr [eax]           
  0x0028BC54  32442300                xor      al, byte ptr [ebx]             
  0x0028BC58  40                      inc      eax                            
  0x0028BC59  0423                    add      al, 0x23                       
  0x0028BC5B  00440024                add      byte ptr [eax + eax + 0x24], al 
  0x0028BC5F  0004a4                  add      byte ptr [esp], al             
  0x0028BC62  050010cc06              add      eax, 0x6cc1000                 
  0x0028BC67  0002                    add      byte ptr [edx], al             
  0x0028BC69  0000                    add      byte ptr [eax], al             
  0x0028BC6B  0000                    add      byte ptr [eax], al             
  0x0028BC6D  5a                      pop      edx                            
  0x0028BC6E  44                      inc      esp                            
  0x0028BC6F  0000                    add      byte ptr [eax], al             
  0x0028BC71  b022                    mov      al, 0x22                       
  0x0028BC73  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028BC1D (cond_jump)
  0x0028BC75  91                      xchg     ecx, eax                       
  0x0028BC76  2200                    and      al, byte ptr [eax]             
  0x0028BC78  00f4                    add      ah, dh                         
  0x0028BC7A  65000d0d000000          add      byte ptr gs:[0xd], cl          
  0x0028BC81  f4                      hlt                                     
  0x0028BC82  7500                    jne      0x28bc84                       
  0x0028BC86  ff00                    inc      dword ptr [eax]                
  0x0028BC88  10da                    adc      dl, bl                         
  0x0028BC8A  06                      push     es                             
  0x0028BC8B  0007                    add      byte ptr [edi], al             
  0x0028BC8D  0000                    add      byte ptr [eax], al             
  0x0028BC8F  0000                    add      byte ptr [eax], al             
  0x0028BC91  b8f000d0b8              mov      eax, 0xb8d000f0                
  0x0028BC97  00d2                    add      dl, dl                         
  0x0028BC99  b8d000d200              mov      eax, 0xd200d0                  
  0x0028BC9E  2000                    and      byte ptr [eax], al             
  0x0028BCA0  2200                    and      al, byte ptr [eax]             
  0x0028BCA2  2000                    and      byte ptr [eax], al             
  0x0028BCA4  005958                  add      byte ptr [ecx + 0x58], bl      
  0x0028BCA7  000c00                  add      byte ptr [eax + eax], cl       
  0x0028BCAA  0000                    add      byte ptr [eax], al             
  0x0028BCAC  20f4                    and      ah, dh                         
  0x0028BCAE  0500ffffff              add      eax, 0xffffff00                
  0x0028BCB3  00a0610400a0            add      byte ptr [eax - 0x5ffffb9f], ah 
  0x0028BCB9  620400                  bound    eax, qword ptr [eax + eax]     
  0x0028BCBC  a0640400a0              mov      al, byte ptr [0xa0000464]      
  0x0028BCC1  650400                  add      al, 0                          
  0x0028BCC4  a0660400b8              mov      al, byte ptr [0xb8000466]      
  0x0028BCC9  f30000                  add      byte ptr [eax], al             
  0x0028BCCC  00f4                    add      ah, dh                         
  0x0028BCCE  44                      inc      esp                            
  0x0028BCCF  0000                    add      byte ptr [eax], al             
  0x0028BCD1  0000                    add      byte ptr [eax], al             
  0x0028BCD3  004d00                  add      byte ptr [ebp], cl             
  0x0028BCD6  2000                    and      byte ptr [eax], al             
  0x0028BCD8  0ca4                    or       al, 0xa4                       
  0x0028BCDA  050000f444              add      eax, 0x44f40000                
  0x0028BCDF  0010                    add      byte ptr [eax], dl             
  0x0028BCE1  0000                    add      byte ptr [eax], al             
  0x0028BCE3  004d00                  add      byte ptr [ebp], cl             
  0x0028BCE6  2000                    and      byte ptr [eax], al             
  0x0028BCE8  4a                      dec      edx                            
  0x0028BCE9  100d000f0000            adc      byte ptr [0xf00], cl           
  0x0028BCEF  0000                    add      byte ptr [eax], al             
  0x0028BCF1  0030                    add      byte ptr [eax], dh             
  0x0028BCF3  0000                    add      byte ptr [eax], al             
  0x0028BCF5  f4                      hlt                                     
  0x0028BCF6  56                      push     esi                            
  0x0028BCF7  0000                    add      byte ptr [eax], al             
  0x0028BCF9  0000                    add      byte ptr [eax], al             
  0x0028BCFB  0000                    add      byte ptr [eax], al             
  0x0028BCFD  f4                      hlt                                     
  0x0028BCFE  57                      push     edi                            
  0x0028BCFF  00ff                    add      bh, bh                         
  0x0028BD02  ff00                    inc      dword ptr [eax]                
  0x0028BD04  0c00                    or       al, 0                          
  0x0028BD06  0000                    add      byte ptr [eax], al             
  0x0028BD08  1300                    adc      eax, dword ptr [eax]           
  0x0028BD0A  2000                    and      byte ptr [eax], al             
  0x0028BD0C  0000                    add      byte ptr [eax], al             
  0x0028BD0E  3000                    xor      byte ptr [eax], al             
  0x0028BD10  00f4                    add      ah, dh                         
  0x0028BD12  56                      push     esi                            
  0x0028BD13  0000                    add      byte ptr [eax], al             
  0x0028BD15  0000                    add      byte ptr [eax], al             
  0x0028BD17  0000                    add      byte ptr [eax], al             
  0x0028BD19  f4                      hlt                                     
  0x0028BD1A  57                      push     edi                            
  0x0028BD1B  0008                    add      byte ptr [eax], cl             
  0x0028BD1D  06                      push     es                             
  0x0028BD1E  0000                    add      byte ptr [eax], al             
  0x0028BD20  0c00                    or       al, 0                          
  0x0028BD22  0000                    add      byte ptr [eax], al             
  0x0028BD24  00f0                    add      al, dh                         
  0x0028BD26  56                      push     esi                            
  0x0028BD27  00960b000003            add      byte ptr [esi + 0x300000b], dl 
  0x0028BD2D  0020                    add      byte ptr [eax], ah             
  0x0028BD2F  001e                    add      byte ptr [esi], bl             
  0x0028BD31  7405                    je       0x28bd38                       
  0x0028BD33  0000                    add      byte ptr [eax], al             
  0x0028BD36  56                      push     esi                            
  0x0028BD37  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028BD3A  0000                    add      byte ptr [eax], al             
  0x0028BD3C  0300                    add      eax, dword ptr [eax]           
  0x0028BD3E  2e0002                  add      byte ptr cs:[edx], al          
  0x0028BD41  2405                    and      al, 5                          
  0x0028BD43  008041010000            add      byte ptr [eax + 0x141], al     
  0x0028BD49  7056                    jo       0x28bda1                       
  0x0028BD4B  00890b000080            add      byte ptr [ecx - 0x7ffffff5], cl 
  0x0028BD51  100d008b0300            adc      byte ptr [0x38b00], cl         
  0x0028BD57  0000                    add      byte ptr [eax], al             
  0x0028BD59  f4                      hlt                                     
  0x0028BD5A  44                      inc      esp                            
  0x0028BD5B  00b007000000            add      byte ptr [eax + 7], dh         
  0x0028BD61  7044                    jo       0x28bda7                       
  0x0028BD63  00720b                  add      byte ptr [edx + 0xb], dh       
  0x0028BD66  0000                    add      byte ptr [eax], al             
  0x0028BD68  80100d                  adc      byte ptr [eax], 0xd            
  0x0028BD6B  001400                  add      byte ptr [eax + eax], dl       
  0x0028BD6E  0000                    add      byte ptr [eax], al             
  0x0028BD70  00f0                    add      al, dh                         
  0x0028BD72  56                      push     esi                            
  0x0028BD73  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028BD76  0000                    add      byte ptr [eax], al             
  0x0028BD78  0300                    add      eax, dword ptr [eax]           
  0x0028BD7A  2e0003                  add      byte ptr cs:[ebx], al          
  0x0028BD7D  2405                    and      al, 5                          
  0x0028BD7F  0080100d0053            add      byte ptr [eax + 0x53000d10], al 
  0x0028BD85  0300                    add      eax, dword ptr [eax]           
  0x0028BD87  0080100d009d            add      byte ptr [eax - 0x62fff2f0], al 
  0x0028BD8D  0000                    add      byte ptr [eax], al             
  0x0028BD8F  0000                    add      byte ptr [eax], al             
  0x0028BD92  56                      push     esi                            
  0x0028BD93  00960b000003            add      byte ptr [esi + 0x300000b], dl 
  0x0028BD99  0020                    add      byte ptr [eax], ah             
  0x0028BD9B  0003                    add      byte ptr [ebx], al             
  0x0028BD9D  2405                    and      al, 5                          
  0x0028BD9F  0080100d009c            add      byte ptr [eax - 0x63fff2f0], al 
  0x0028BDA5  0100                    add      dword ptr [eax], eax           
                                        ; XREF: 0x0028BD61 (cond_jump)
  0x0028BDA7  0013                    add      byte ptr [ebx], dl             
  0x0028BDA9  0020                    add      byte ptr [eax], ah             
  0x0028BDAB  001b                    add      byte ptr [ebx], bl             
  0x0028BDAD  1021                    adc      byte ptr [ecx], ah             
  0x0028BDAF  000c00                  add      byte ptr [eax + eax], cl       
  0x0028BDB2  0000                    add      byte ptr [eax], al             
  0x0028BDB4  0c00                    or       al, 0                          
  0x0028BDB6  0000                    add      byte ptr [eax], al             
  0x0028BDB8  00f4                    add      ah, dh                         
  0x0028BDBA  44                      inc      esp                            
  0x0028BDBB  0001                    add      byte ptr [ecx], al             
  0x0028BDBD  0000                    add      byte ptr [eax], al             
  0x0028BDBF  0000                    add      byte ptr [eax], al             
  0x0028BDC1  7044                    jo       0x28be07                       
  0x0028BDC3  006f0b                  add      byte ptr [edi + 0xb], ch       
  0x0028BDC6  0000                    add      byte ptr [eax], al             
  0x0028BDC8  1bf0                    sbb      esi, eax                       
  0x0028BDCA  56                      push     esi                            
  0x0028BDCB  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028BDCE  0000                    add      byte ptr [eax], al             
  0x0028BDD0  0300                    add      eax, dword ptr [eax]           
  0x0028BDD2  2000                    and      byte ptr [eax], al             
  0x0028BDD4  02240500090000          add      ah, byte ptr [eax + 0x900]     
  0x0028BDDB  0000                    add      byte ptr [eax], al             
  0x0028BDDD  7051                    jo       0x28be30                       
  0x0028BDDF  00c0                    add      al, al                         
  0x0028BDE1  0400                    add      al, 0                          
  0x0028BDE3  0000                    add      byte ptr [eax], al             
  0x0028BDE5  0230                    add      dh, byte ptr [eax]             
  0x0028BDE7  0000                    add      byte ptr [eax], al             
  0x0028BDE9  0131                    add      dword ptr [ecx], esi           
  0x0028BDEB  0000                    add      byte ptr [eax], al             
  0x0028BDED  0132                    add      dword ptr [edx], esi           
  0x0028BDEF  0000                    add      byte ptr [eax], al             
  0x0028BDF1  023500c4700b            add      dh, byte ptr [0xb70c400]       
  0x0028BDF7  0008                    add      byte ptr [eax], cl             
  0x0028BDF9  0c00                    or       al, 0                          
  0x0028BDFB  0000                    add      byte ptr [eax], al             
  0x0028BDFD  7044                    jo       0x28be43                       
  0x0028BDFF  008d040000c4            add      byte ptr [ebp - 0x3bfffffc], cl 
  0x0028BE05  710b                    jno      0x28be12                       
                                        ; XREF: 0x0028BDC1 (cond_jump)
  0x0028BE07  00040c                  add      byte ptr [esp + ecx], al       
  0x0028BE0A  0000                    add      byte ptr [eax], al             
  0x0028BE0C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028BE0F  008c040000c472          add      byte ptr [esp + eax + 0x72c40000], cl 
  0x0028BE16  0b00                    or       eax, dword ptr [eax]           
  0x0028BE18  140c                    adc      al, 0xc                        
  0x0028BE1A  0000                    add      byte ptr [eax], al             
  0x0028BE1C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028BE1F  008f040000c4            add      byte ptr [edi - 0x3bfffffc], cl 
  0x0028BE25  750b                    jne      0x28be32                       
  0x0028BE27  0018                    add      byte ptr [eax], bl             
  0x0028BE29  0c00                    or       al, 0                          
  0x0028BE2B  0000                    add      byte ptr [eax], al             
  0x0028BE2D  7044                    jo       0x28be73                       
  0x0028BE2F  009004000000            add      byte ptr [eax + 4], dl         
  0x0028BE35  0036                    add      byte ptr [esi], dh             
  0x0028BE37  0000                    add      byte ptr [eax], al             
  0x0028BE3A  44                      inc      esp                            
  0x0028BE3B  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028BE41  c406                    les      eax, ptr [esi]                 
                                        ; XREF: 0x0028BDFD (cond_jump)
  0x0028BE43  004e00                  add      byte ptr [esi], cl             
  0x0028BE46  0000                    add      byte ptr [eax], al             
  0x0028BE48  0001                    add      byte ptr [ecx], al             
  0x0028BE4A  2800                    sub      byte ptr [eax], al             
  0x0028BE4C  007050                  add      byte ptr [eax + 0x50], dh      
  0x0028BE4F  00c0                    add      al, al                         
  0x0028BE51  0400                    add      al, 0                          
  0x0028BE53  0000                    add      byte ptr [eax], al             
  0x0028BE55  0430                    add      al, 0x30                       
  0x0028BE57  00c4                    add      ah, al                         
  0x0028BE59  700b                    jo       0x28be66                       
  0x0028BE5B  000c0c                  add      byte ptr [esp + ecx], cl       
  0x0028BE5E  0000                    add      byte ptr [eax], al             
  0x0028BE60  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028BE63  008e04000000            add      byte ptr [esi + 4], cl         
  0x0028BE69  f4                      hlt                                     
  0x0028BE6A  44                      inc      esp                            
  0x0028BE6B  0000                    add      byte ptr [eax], al             
  0x0028BE6D  80ff00                  cmp      bh, 0                          
  0x0028BE70  007044                  add      byte ptr [eax + 0x44], dh      
                                        ; XREF: 0x0028BE2D (cond_jump)
  0x0028BE73  008a04000000            add      byte ptr [edx + 4], cl         
  0x0028BE79  f4                      hlt                                     
  0x0028BE7A  44                      inc      esp                            
  0x0028BE7B  0000                    add      byte ptr [eax], al             
  0x0028BE7D  80ff00                  cmp      bh, 0                          
  0x0028BE80  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028BE83  008b04000000            add      byte ptr [ebx + 4], cl         
  0x0028BE89  c422                    les      esp, ptr [edx]                 
  0x0028BE8B  0000                    add      byte ptr [eax], al             
  0x0028BE8D  f4                      hlt                                     
  0x0028BE8E  46                      inc      esi                            
  0x0028BE8F  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028BE95  f4                      hlt                                     
  0x0028BE96  44                      inc      esp                            
  0x0028BE97  00fa                    add      dl, bh                         
  0x0028BE99  0000                    add      byte ptr [eax], al             
  0x0028BE9B  002e                    add      byte ptr [esi], ch             
  0x0028BE9D  1d0c004000              sbb      eax, 0x40000c                  
  0x0028BEA2  2000                    and      byte ptr [eax], al             
  0x0028BEA4  0090210000c4            add      byte ptr [eax - 0x3bffffdf], dl 
  0x0028BEAA  2200                    and      al, byte ptr [eax]             
  0x0028BEAC  00f4                    add      ah, dh                         
  0x0028BEAE  46                      inc      esi                            
  0x0028BEAF  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028BEB5  f4                      hlt                                     
  0x0028BEB6  44                      inc      esp                            
  0x0028BEB7  00fa                    add      dl, bh                         
  0x0028BEB9  0000                    add      byte ptr [eax], al             
  0x0028BEBB  002e                    add      byte ptr [esi], ch             
  0x0028BEBD  1d0c004000              sbb      eax, 0x40000c                  
  0x0028BEC2  2000                    and      byte ptr [eax], al             
  0x0028BEC4  0095210000c4            add      byte ptr [ebp - 0x3bffffdf], dl 
  0x0028BECA  2200                    and      al, byte ptr [eax]             
  0x0028BECC  00f4                    add      ah, dh                         
  0x0028BECE  46                      inc      esi                            
  0x0028BECF  0032                    add      byte ptr [edx], dh             
  0x0028BED1  0000                    add      byte ptr [eax], al             
  0x0028BED3  00d0                    add      al, dl                         
  0x0028BED5  f4                      hlt                                     
  0x0028BED6  44                      inc      esp                            
  0x0028BED7  0000                    add      byte ptr [eax], al             
  0x0028BED9  0000                    add      byte ptr [eax], al             
  0x0028BEDB  002e                    add      byte ptr [esi], ch             
  0x0028BEDD  1d0c004000              sbb      eax, 0x40000c                  
  0x0028BEE2  2000                    and      byte ptr [eax], al             
  0x0028BEE4  009a21000000            add      byte ptr [edx + 0x21], bl      
  0x0028BEEA  3800                    cmp      byte ptr [eax], al             
  0x0028BEEC  00f4                    add      ah, dh                         
  0x0028BEEE  56                      push     esi                            
  0x0028BEEF  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x0028BEF5  c422                    les      esp, ptr [edx]                 
  0x0028BEF7  004000                  add      byte ptr [eax], al             
  0x0028BEFA  2000                    and      byte ptr [eax], al             
  0x0028BEFC  0091210000e1            add      byte ptr [ecx - 0x1effffdf], dl 
  0x0028BF02  7400                    je       0x28bf04                       
                                        ; XREF: 0x0028BF02 (cond_jump)
  0x0028BF04  00e1                    add      cl, ah                         
  0x0028BF06  7600                    jbe      0x28bf08                       
                                        ; XREF: 0x0028BF06 (cond_jump)
  0x0028BF08  0000                    add      byte ptr [eax], al             
  0x0028BF0A  3200                    xor      al, byte ptr [eax]             
  0x0028BF0C  007066                  add      byte ptr [eax + 0x66], dh      
  0x0028BF0F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028BF12  0000                    add      byte ptr [eax], al             
  0x0028BF14  d7                      xlatb                                   
  0x0028BF15  030d0000f066            add      ecx, dword ptr [0x66f00000]    
  0x0028BF1B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028BF1E  0000                    add      byte ptr [eax], al             
  0x0028BF20  00f4                    add      ah, dh                         
  0x0028BF22  56                      push     esi                            
  0x0028BF23  00c1                    add      cl, al                         
  0x0028BF25  0400                    add      al, 0                          
  0x0028BF27  0000                    add      byte ptr [eax], al             
  0x0028BF29  c422                    les      esp, ptr [edx]                 
  0x0028BF2B  004000                  add      byte ptr [eax], al             
  0x0028BF2E  2000                    and      byte ptr [eax], al             
  0x0028BF30  009021000060            add      byte ptr [eax + 0x60000021], dl 
  0x0028BF36  6200                    bound    eax, qword ptr [eax]           
  0x0028BF38  00f4                    add      ah, dh                         
  0x0028BF3A  56                      push     esi                            
  0x0028BF3B  009404000000c4          add      byte ptr [esp + eax - 0x3c000000], dl 
  0x0028BF42  2200                    and      al, byte ptr [eax]             
  0x0028BF44  40                      inc      eax                            
  0x0028BF45  0020                    add      byte ptr [eax], ah             
  0x0028BF47  0000                    add      byte ptr [eax], al             
  0x0028BF49  90                      nop                                     
  0x0028BF4A  2100                    and      dword ptr [eax], eax           
  0x0028BF4C  00f0                    add      al, dh                         
  0x0028BF4E  44                      inc      esp                            
  0x0028BF4F  008a04000000            add      byte ptr [edx + 4], cl         
  0x0028BF55  60                      pushal                                  
  0x0028BF56  44                      inc      esp                            
  0x0028BF57  0000                    add      byte ptr [eax], al             
  0x0028BF59  f4                      hlt                                     
  0x0028BF5A  56                      push     esi                            
  0x0028BF5B  009904000000            add      byte ptr [ecx + 4], bl         
  0x0028BF61  c422                    les      esp, ptr [edx]                 
  0x0028BF63  004000                  add      byte ptr [eax], al             
  0x0028BF66  2000                    and      byte ptr [eax], al             
  0x0028BF68  0090210000f0            add      byte ptr [eax - 0xfffffdf], dl 
  0x0028BF6E  44                      inc      esp                            
  0x0028BF6F  008b04000000            add      byte ptr [ebx + 4], cl         
  0x0028BF75  60                      pushal                                  
  0x0028BF76  44                      inc      esp                            
  0x0028BF77  0000                    add      byte ptr [eax], al             
  0x0028BF79  5e                      pop      esi                            
  0x0028BF7A  2000                    and      byte ptr [eax], al             
  0x0028BF7C  00f0                    add      al, dh                         
  0x0028BF7E  56                      push     esi                            
  0x0028BF7F  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028BF82  0000                    add      byte ptr [eax], al             
  0x0028BF84  0300                    add      eax, dword ptr [eax]           
  0x0028BF86  2000                    and      byte ptr [eax], al             
  0x0028BF88  1ca4                    sbb      al, 0xa4                       
  0x0028BF8A  0500000128              add      eax, 0x28010000                
  0x0028BF8F  0000                    add      byte ptr [eax], al             
  0x0028BF91  7050                    jo       0x28bfe3                       
  0x0028BF93  00c0                    add      al, al                         
  0x0028BF95  0400                    add      al, 0                          
  0x0028BF97  0000                    add      byte ptr [eax], al             
  0x0028BF99  0430                    add      al, 0x30                       
  0x0028BF9B  00c4                    add      ah, al                         
  0x0028BF9D  700b                    jo       0x28bfaa                       
  0x0028BF9F  000c0c                  add      byte ptr [esp + ecx], cl       
  0x0028BFA2  0000                    add      byte ptr [eax], al             
  0x0028BFA4  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028BFA7  008e04000000            add      byte ptr [esi + 4], cl         
  0x0028BFAD  f4                      hlt                                     
  0x0028BFAE  44                      inc      esp                            
  0x0028BFAF  0000                    add      byte ptr [eax], al             
  0x0028BFB1  80ff00                  cmp      bh, 0                          
  0x0028BFB4  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028BFB7  008a04000000            add      byte ptr [edx + 4], cl         
  0x0028BFBD  f4                      hlt                                     
  0x0028BFBE  44                      inc      esp                            
  0x0028BFBF  0000                    add      byte ptr [eax], al             
  0x0028BFC1  80ff00                  cmp      bh, 0                          
  0x0028BFC4  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028BFC7  008b04000000            add      byte ptr [ebx + 4], cl         
  0x0028BFCD  f4                      hlt                                     
  0x0028BFCE  60                      pushal                                  
  0x0028BFCF  008304000000            add      byte ptr [ebx + 4], al         
  0x0028BFD5  f4                      hlt                                     
  0x0028BFD6  65008304000000          add      byte ptr gs:[ebx + 4], al      
  0x0028BFDD  f4                      hlt                                     
  0x0028BFDE  7200                    jb       0x28bfe0                       
                                        ; XREF: 0x0028BFDE (cond_jump)
  0x0028BFE0  b804000000              mov      eax, 4                         
  0x0028BFE5  0038                    add      byte ptr [eax], bh             
  0x0028BFE7  0000                    add      byte ptr [eax], al             
  0x0028BFE9  07                      pop      es                             
  0x0028BFEA  3c00                    cmp      al, 0                          
  0x0028BFEC  0007                    add      byte ptr [edi], al             
  0x0028BFEE  3e0000                  add      byte ptr ds:[eax], al          
  0x0028BFF1  0032                    add      byte ptr [edx], dh             
  0x0028BFF3  00d7                    add      bh, dl                         
  0x0028BFF5  030d000c0000            add      ecx, dword ptr [0xc00]         
  0x0028BFFB  0000                    add      byte ptr [eax], al             
  0x0028BFFE  56                      push     esi                            
  0x0028BFFF  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C002  0000                    add      byte ptr [eax], al             
  0x0028C004  0300                    add      eax, dword ptr [eax]           
  0x0028C006  2000                    and      byte ptr [eax], al             
  0x0028C008  0424                    add      al, 0x24                       
  0x0028C00A  0500000024              add      eax, 0x24000000                
  0x0028C00F  0000                    add      byte ptr [eax], al             
  0x0028C011  7044                    jo       0x28c057                       
  0x0028C013  006e0b                  add      byte ptr [esi + 0xb], ch       
  0x0028C016  0000                    add      byte ptr [eax], al             
  0x0028C018  0000                    add      byte ptr [eax], al             
  0x0028C01A  3400                    xor      al, 0                          
  0x0028C01C  1b00                    sbb      eax, dword ptr [eax]           
  0x0028C01E  2000                    and      byte ptr [eax], al             
  0x0028C020  00f0                    add      al, dh                         
  0x0028C022  44                      inc      esp                            
  0x0028C023  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028C029  c406                    les      eax, ptr [esi]                 
  0x0028C02B  0003                    add      byte ptr [ebx], al             
  0x0028C02D  0000                    add      byte ptr [eax], al             
  0x0028C02F  008841010088            add      byte ptr [eax - 0x77fffebf], cl 
  0x0028C035  41                      inc      ecx                            
  0x0028C036  0100                    add      dword ptr [eax], eax           
  0x0028C038  884101                  mov      byte ptr [ecx + 1], al         
  0x0028C03B  0000                    add      byte ptr [eax], al             
  0x0028C03E  56                      push     esi                            
  0x0028C03F  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028C042  0000                    add      byte ptr [eax], al             
  0x0028C044  0300                    add      eax, dword ptr [eax]           
  0x0028C046  2000                    and      byte ptr [eax], al             
  0x0028C048  02240500884101          add      ah, byte ptr [eax + 0x1418800] 
  0x0028C04F  0000                    add      byte ptr [eax], al             
  0x0028C052  56                      push     esi                            
  0x0028C053  004a0b                  add      byte ptr [edx + 0xb], cl       
  0x0028C056  0000                    add      byte ptr [eax], al             
  0x0028C058  03f4                    add      esi, esp                       
  0x0028C05A  44                      inc      esp                            
  0x0028C05B  0008                    add      byte ptr [eax], cl             
  0x0028C05D  0000                    add      byte ptr [eax], al             
  0x0028C05F  0002                    add      byte ptr [edx], al             
  0x0028C061  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C062  0500480020              add      eax, 0x20004800                
  0x0028C067  008841010000            add      byte ptr [eax + 0x141], cl     
  0x0028C06E  56                      push     esi                            
  0x0028C06F  00890b000003            add      byte ptr [ecx + 0x300000b], cl 
  0x0028C075  0020                    add      byte ptr [eax], ah             
  0x0028C077  0002                    add      byte ptr [edx], al             
  0x0028C079  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C07A  0500884101              add      eax, 0x1418800                 
  0x0028C07F  0000                    add      byte ptr [eax], al             
  0x0028C082  56                      push     esi                            
  0x0028C083  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028C086  0000                    add      byte ptr [eax], al             
  0x0028C088  854201                  test     dword ptr [edx + 1], eax       
  0x0028C08B  0007                    add      byte ptr [edi], al             
  0x0028C08D  2405                    and      al, 5                          
  0x0028C08F  008841010000            add      byte ptr [eax + 0x141], cl     
  0x0028C096  56                      push     esi                            
  0x0028C097  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C09A  0000                    add      byte ptr [eax], al             
  0x0028C09C  03f4                    add      esi, esp                       
  0x0028C09E  44                      inc      esp                            
  0x0028C09F  000400                  add      byte ptr [eax + eax], al       
  0x0028C0A2  0000                    add      byte ptr [eax], al             
  0x0028C0A4  48                      dec      eax                            
  0x0028C0A5  2a20                    sub      ah, byte ptr [eax]             
  0x0028C0A7  0000                    add      byte ptr [eax], al             
  0x0028C0AA  44                      inc      esp                            
  0x0028C0AB  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028C0B1  c406                    les      eax, ptr [esi]                 
  0x0028C0B3  0002                    add      byte ptr [edx], al             
  0x0028C0B5  0000                    add      byte ptr [eax], al             
  0x0028C0B7  008842010000            add      byte ptr [eax + 0x142], cl     
  0x0028C0BE  56                      push     esi                            
  0x0028C0BF  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028C0C2  0000                    add      byte ptr [eax], al             
  0x0028C0C4  0300                    add      eax, dword ptr [eax]           
  0x0028C0C6  2000                    and      byte ptr [eax], al             
  0x0028C0C8  02a40500884101          add      ah, byte ptr [ebp + eax + 0x1418800] 
  0x0028C0CF  0000                    add      byte ptr [eax], al             
  0x0028C0D1  f4                      hlt                                     
  0x0028C0D2  56                      push     esi                            
  0x0028C0D3  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028C0D9  002400                  add      byte ptr [eax + eax], ah       
  0x0028C0DC  40                      inc      eax                            
  0x0028C0DD  0020                    add      byte ptr [eax], ah             
  0x0028C0DF  0000                    add      byte ptr [eax], al             
  0x0028C0E1  90                      nop                                     
  0x0028C0E2  2100                    and      dword ptr [eax], eax           
  0x0028C0E4  00f0                    add      al, dh                         
  0x0028C0E6  44                      inc      esp                            
  0x0028C0E7  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028C0ED  c406                    les      eax, ptr [esi]                 
  0x0028C0EF  0006                    add      byte ptr [esi], al             
  0x0028C0F1  0000                    add      byte ptr [eax], al             
  0x0028C0F3  0000                    add      byte ptr [eax], al             
  0x0028C0F5  d85600                  fcom     dword ptr [esi]                
  0x0028C0F8  0300                    add      eax, dword ptr [eax]           
  0x0028C0FA  2000                    and      byte ptr [eax], al             
  0x0028C0FC  02a40500884601          add      ah, byte ptr [ebp + eax + 0x1468800] 
  0x0028C103  0000                    add      byte ptr [eax], al             
  0x0028C105  0000                    add      byte ptr [eax], al             
  0x0028C107  0000                    add      byte ptr [eax], al             
  0x0028C109  f4                      hlt                                     
  0x0028C10A  60                      pushal                                  
  0x0028C10B  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028C111  f4                      hlt                                     
  0x0028C112  61                      popal                                   
  0x0028C113  00910b000000            add      byte ptr [ecx + 0xb], dl       
  0x0028C119  f4                      hlt                                     
  0x0028C11A  46                      inc      esi                            
  0x0028C11B  0007                    add      byte ptr [edi], al             
  0x0028C11D  0000                    add      byte ptr [eax], al             
  0x0028C11F  0000                    add      byte ptr [eax], al             
  0x0028C122  44                      inc      esp                            
  0x0028C123  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028C129  c406                    les      eax, ptr [esi]                 
  0x0028C12B  000a                    add      byte ptr [edx], cl             
  0x0028C12D  0000                    add      byte ptr [eax], al             
  0x0028C12F  0000                    add      byte ptr [eax], al             
  0x0028C131  d85600                  fcom     dword ptr [esi]                
  0x0028C134  03d9                    add      ebx, ecx                       
  0x0028C136  44                      inc      esp                            
  0x0028C137  0006                    add      byte ptr [esi], al             
  0x0028C139  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C13A  0500884401              add      eax, 0x1448800                 
  0x0028C13F  00d0                    add      al, dl                         
  0x0028C141  0020                    add      byte ptr [eax], ah             
  0x0028C143  002e                    add      byte ptr [esi], ch             
  0x0028C145  1d0c001800              sbb      eax, 0x18000c                  
  0x0028C14A  2000                    and      byte ptr [eax], al             
  0x0028C14C  884201                  mov      byte ptr [edx + 1], al         
  0x0028C14F  0000                    add      byte ptr [eax], al             
  0x0028C151  0000                    add      byte ptr [eax], al             
  0x0028C153  0000                    add      byte ptr [eax], al             
  0x0028C156  56                      push     esi                            
  0x0028C157  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028C15A  0000                    add      byte ptr [eax], al             
  0x0028C15C  0300                    add      eax, dword ptr [eax]           
  0x0028C15E  2000                    and      byte ptr [eax], al             
  0x0028C160  08a4050000f056          or       byte ptr [ebp + eax + 0x56f00000], ah 
  0x0028C167  008f0b000003            add      byte ptr [edi + 0x300000b], cl 
  0x0028C16D  f4                      hlt                                     
  0x0028C16E  44                      inc      esp                            
  0x0028C16F  000e                    add      byte ptr [esi], cl             
  0x0028C171  0000                    add      byte ptr [eax], al             
  0x0028C173  0003                    add      byte ptr [ebx], al             
  0x0028C175  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C176  0500884401              add      eax, 0x1448800                 
  0x0028C17B  004800                  add      byte ptr [eax], cl             
  0x0028C17E  2000                    and      byte ptr [eax], al             
  0x0028C180  884101                  mov      byte ptr [ecx + 1], al         
  0x0028C183  0000                    add      byte ptr [eax], al             
  0x0028C186  56                      push     esi                            
  0x0028C187  00900b000003            add      byte ptr [eax + 0x300000b], dl 
  0x0028C18D  0020                    add      byte ptr [eax], ah             
  0x0028C18F  0006                    add      byte ptr [esi], al             
  0x0028C191  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C192  0500884201              add      eax, 0x1428800                 
  0x0028C197  008842010088            add      byte ptr [eax - 0x77fffebe], cl 
  0x0028C19D  42                      inc      edx                            
  0x0028C19E  0100                    add      dword ptr [eax], eax           
  0x0028C1A0  884201                  mov      byte ptr [edx + 1], al         
  0x0028C1A3  008843010088            add      byte ptr [eax - 0x77fffebd], cl 
  0x0028C1A9  41                      inc      ecx                            
  0x0028C1AA  0100                    add      dword ptr [eax], eax           
  0x0028C1AC  00f0                    add      al, dh                         
  0x0028C1AE  56                      push     esi                            
  0x0028C1AF  006f0b                  add      byte ptr [edi + 0xb], ch       
  0x0028C1B2  0000                    add      byte ptr [eax], al             
  0x0028C1B4  0300                    add      eax, dword ptr [eax]           
  0x0028C1B6  2000                    and      byte ptr [eax], al             
  0x0028C1B8  0e                      push     cs                             
  0x0028C1B9  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C1BA  0500884601              add      eax, 0x1468800                 
  0x0028C1BF  0000                    add      byte ptr [eax], al             
  0x0028C1C2  44                      inc      esp                            
  0x0028C1C3  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028C1C9  c406                    les      eax, ptr [esi]                 
  0x0028C1CB  0003                    add      byte ptr [ebx], al             
  0x0028C1CD  0000                    add      byte ptr [eax], al             
  0x0028C1CF  008844010088            add      byte ptr [eax - 0x77fffebc], cl 
  0x0028C1D5  43                      inc      ebx                            
  0x0028C1D6  0100                    add      dword ptr [eax], eax           
  0x0028C1D8  00f0                    add      al, dh                         
  0x0028C1DA  56                      push     esi                            
  0x0028C1DB  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028C1DE  0000                    add      byte ptr [eax], al             
  0x0028C1E0  0300                    add      eax, dword ptr [eax]           
  0x0028C1E2  2000                    and      byte ptr [eax], al             
  0x0028C1E4  03a40500884401          add      esp, dword ptr [ebp + eax + 0x1448800] 
  0x0028C1EB  008843010088            add      byte ptr [eax - 0x77fffebd], cl 
  0x0028C1F1  41                      inc      ecx                            
  0x0028C1F2  0100                    add      dword ptr [eax], eax           
  0x0028C1F4  884101                  mov      byte ptr [ecx + 1], al         
  0x0028C1F7  001b                    add      byte ptr [ebx], bl             
  0x0028C1F9  e721                    out      0x21, eax                      
  0x0028C1FB  0000                    add      byte ptr [eax], al             
  0x0028C1FE  56                      push     esi                            
  0x0028C1FF  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C202  0000                    add      byte ptr [eax], al             
  0x0028C204  c54001                  lds      eax, ptr [eax + 1]             
  0x0028C207  0003                    add      byte ptr [ebx], al             
  0x0028C209  0000                    add      byte ptr [eax], al             
  0x0028C20B  004210                  add      byte ptr [edx + 0x10], al      
  0x0028C20E  0d000d0000              or       eax, 0xd00                     
  0x0028C213  0079e7                  add      byte ptr [ecx - 0x19], bh      
  0x0028C216  2100                    and      dword ptr [eax], eax           
  0x0028C218  884901                  mov      byte ptr [ecx + 1], cl         
  0x0028C21B  0079e7                  add      byte ptr [ecx - 0x19], bh      
  0x0028C21E  2100                    and      dword ptr [eax], eax           
  0x0028C220  884101                  mov      byte ptr [ecx + 1], al         
  0x0028C223  008841010000            add      byte ptr [eax + 0x141], cl     
  0x0028C22A  56                      push     esi                            
  0x0028C22B  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C22E  0000                    add      byte ptr [eax], al             
  0x0028C230  c54001                  lds      eax, ptr [eax + 1]             
  0x0028C233  0003                    add      byte ptr [ebx], al             
  0x0028C235  0000                    add      byte ptr [eax], al             
  0x0028C237  0002                    add      byte ptr [edx], al             
  0x0028C239  2405                    and      al, 5                          
  0x0028C23B  00886f010088            add      byte ptr [eax - 0x77fffe91], cl 
  0x0028C241  47                      inc      edi                            
  0x0028C242  0100                    add      dword ptr [eax], eax           
  0x0028C245  1e                      push     ds                             
  0x0028C246  0c00                    or       al, 0                          
  0x0028C248  007055                  add      byte ptr [eax + 0x55], dh      
  0x0028C24B  00700b                  add      byte ptr [eax + 0xb], dh       
  0x0028C24E  0000                    add      byte ptr [eax], al             
  0x0028C250  871e                    xchg     dword ptr [esi], ebx           
  0x0028C252  0c00                    or       al, 0                          
  0x0028C254  79e4                    jns      0x28c23a                       
  0x0028C256  2100                    and      dword ptr [eax], eax           
  0x0028C258  48                      dec      eax                            
  0x0028C259  0020                    add      byte ptr [eax], ah             
  0x0028C25B  0000                    add      byte ptr [eax], al             
  0x0028C25D  7055                    jo       0x28c2b4                       
  0x0028C25F  00710b                  add      byte ptr [ecx + 0xb], dh       
  0x0028C262  0000                    add      byte ptr [eax], al             
  0x0028C264  00f0                    add      al, dh                         
  0x0028C266  56                      push     esi                            
  0x0028C267  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C26A  0000                    add      byte ptr [eax], al             
  0x0028C26C  0300                    add      eax, dword ptr [eax]           
  0x0028C26E  2000                    and      byte ptr [eax], al             
  0x0028C270  07                      pop      es                             
  0x0028C271  2405                    and      al, 5                          
  0x0028C273  001b                    add      byte ptr [ebx], bl             
  0x0028C275  0020                    add      byte ptr [eax], ah             
  0x0028C277  008841010088            add      byte ptr [eax - 0x77fffebf], cl 
  0x0028C27D  41                      inc      ecx                            
  0x0028C27E  0100                    add      dword ptr [eax], eax           
  0x0028C280  885001                  mov      byte ptr [eax + 1], dl         
  0x0028C283  0000                    add      byte ptr [eax], al             
  0x0028C285  7055                    jo       0x28c2dc                       
  0x0028C287  00530b                  add      byte ptr [ebx + 0xb], dl       
  0x0028C28A  0000                    add      byte ptr [eax], al             
  0x0028C28C  00f0                    add      al, dh                         
  0x0028C28E  56                      push     esi                            
  0x0028C28F  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C292  0000                    add      byte ptr [eax], al             
  0x0028C294  0300                    add      eax, dword ptr [eax]           
  0x0028C296  2000                    and      byte ptr [eax], al             
  0x0028C298  8c24050000f057          mov      word ptr [eax + 0x57f00000], fs 
  0x0028C29F  00510b                  add      byte ptr [ecx + 0xb], dl       
  0x0028C2A2  0000                    add      byte ptr [eax], al             
  0x0028C2A4  00f0                    add      al, dh                         
  0x0028C2A6  44                      inc      esp                            
  0x0028C2A7  00530b                  add      byte ptr [ebx + 0xb], dl       
  0x0028C2AA  0000                    add      byte ptr [eax], al             
  0x0028C2AC  48                      dec      eax                            
  0x0028C2AD  0020                    add      byte ptr [eax], ah             
  0x0028C2AF  0000                    add      byte ptr [eax], al             
  0x0028C2B2  44                      inc      esp                            
  0x0028C2B3  009a0b000000            add      byte ptr [edx + 0xb], bl       
  0x0028C2B9  f4                      hlt                                     
  0x0028C2BA  46                      inc      esi                            
  0x0028C2BB  0008                    add      byte ptr [eax], cl             
  0x0028C2BD  0000                    add      byte ptr [eax], al             
  0x0028C2BF  00d0                    add      al, dl                         
  0x0028C2C1  0020                    add      byte ptr [eax], ah             
  0x0028C2C3  0000                    add      byte ptr [eax], al             
  0x0028C2C5  0e                      push     cs                             
  0x0028C2C6  2100                    and      dword ptr [eax], eax           
  0x0028C2C8  1400                    adc      al, 0                          
  0x0028C2CA  2000                    and      byte ptr [eax], al             
  0x0028C2CC  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028C2CF  00520b                  add      byte ptr [edx + 0xb], dl       
  0x0028C2D2  0000                    add      byte ptr [eax], al             
  0x0028C2D4  00f0                    add      al, dh                         
  0x0028C2D6  56                      push     esi                            
  0x0028C2D7  00530b                  add      byte ptr [ebx + 0xb], dl       
  0x0028C2DA  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028C285 (cond_jump)
  0x0028C2DC  00f0                    add      al, dh                         
  0x0028C2DE  44                      inc      esp                            
  0x0028C2DF  009f0b000045            add      byte ptr [edi + 0x4500000b], bl 
  0x0028C2E5  0020                    add      byte ptr [eax], ah             
  0x0028C2E7  00857405001b            add      byte ptr [ebp + 0x1b000574], al 
  0x0028C2ED  f4                      hlt                                     
  0x0028C2EE  44                      inc      esp                            
  0x0028C2EF  005555                  add      byte ptr [ebp + 0x55], dl      
  0x0028C2F2  150000f056              adc      eax, 0x56f00000                
  0x0028C2F7  00520b                  add      byte ptr [edx + 0xb], dl       
  0x0028C2FA  0000                    add      byte ptr [eax], al             
  0x0028C2FC  c44001                  les      eax, ptr [eax + 1]             
  0x0028C2FF  002f                    add      byte ptr [edi], ch             
  0x0028C301  0000                    add      byte ptr [eax], al             
  0x0028C303  0000                    add      byte ptr [eax], al             
  0x0028C305  8521                    test     dword ptr [ecx], esp           
  0x0028C307  00a800200000            add      byte ptr [eax + 0x2000], ch    
  0x0028C30D  af                      scasd    eax, dword ptr es:[edi]        
  0x0028C30E  2100                    and      dword ptr [eax], eax           
  0x0028C310  00f0                    add      al, dh                         
  0x0028C312  44                      inc      esp                            
  0x0028C313  00710b                  add      byte ptr [ecx + 0xb], dh       
  0x0028C316  0000                    add      byte ptr [eax], al             
  0x0028C318  4d                      dec      ebp                            
  0x0028C319  0020                    add      byte ptr [eax], ah             
  0x0028C31B  0058f4                  add      byte ptr [eax - 0xc], bl       
  0x0028C31E  050000a521              add      eax, 0x21a50000                
  0x0028C323  0000                    add      byte ptr [eax], al             
  0x0028C325  f4                      hlt                                     
  0x0028C326  44                      inc      esp                            
  0x0028C327  0006                    add      byte ptr [esi], al             
  0x0028C329  0000                    add      byte ptr [eax], al             
  0x0028C32B  00a00020002e            add      byte ptr [eax + 0x2e002000], ah 
  0x0028C331  1d0c0036f0              sbb      eax, 0xf036000c                
  0x0028C336  44                      inc      esp                            
  0x0028C337  00520b                  add      byte ptr [edx + 0xb], dl       
  0x0028C33A  0000                    add      byte ptr [eax], al             
  0x0028C33C  40                      inc      eax                            
  0x0028C33D  0020                    add      byte ptr [eax], ah             
  0x0028C33F  00c4                    add      ah, al                         
  0x0028C341  40                      inc      eax                            
  0x0028C342  0100                    add      dword ptr [eax], eax           
  0x0028C344  2f                      das                                     
  0x0028C345  0000                    add      byte ptr [eax], al             
  0x0028C347  0000                    add      byte ptr [eax], al             
  0x0028C34A  2100                    and      dword ptr [eax], eax           
  0x0028C34C  c8400100                enter    0x140, 0                       
  0x0028C350  0100                    add      dword ptr [eax], eax           
  0x0028C352  0000                    add      byte ptr [eax], al             
  0x0028C354  00f4                    add      ah, dh                         
  0x0028C356  56                      push     esi                            
  0x0028C357  00680b                  add      byte ptr [eax + 0xb], ch       
  0x0028C35A  0000                    add      byte ptr [eax], al             
  0x0028C35C  0000                    add      byte ptr [eax], al             
  0x0028C35E  2400                    and      al, 0                          
  0x0028C360  40                      inc      eax                            
  0x0028C361  0020                    add      byte ptr [eax], ah             
  0x0028C363  0000                    add      byte ptr [eax], al             
  0x0028C365  90                      nop                                     
  0x0028C366  2100                    and      dword ptr [eax], eax           
  0x0028C368  00f8                    add      al, bh                         
  0x0028C36A  2000                    and      byte ptr [eax], al             
  0x0028C36C  10d8                    adc      al, bl                         
  0x0028C36E  06                      push     es                             
  0x0028C36F  0002                    add      byte ptr [edx], al             
  0x0028C371  0000                    add      byte ptr [eax], al             
  0x0028C373  0000                    add      byte ptr [eax], al             
  0x0028C375  58                      pop      eax                            
  0x0028C376  57                      push     edi                            
  0x0028C377  00cc                    add      ah, cl                         
  0x0028C379  40                      inc      eax                            
  0x0028C37A  0100                    add      dword ptr [eax], eax           
  0x0028C37C  0100                    add      dword ptr [eax], eax           
  0x0028C37E  0000                    add      byte ptr [eax], al             
  0x0028C380  00f4                    add      ah, dh                         
  0x0028C382  56                      push     esi                            
  0x0028C383  0006                    add      byte ptr [esi], al             
  0x0028C385  0000                    add      byte ptr [eax], al             
  0x0028C387  00740020                add      byte ptr [eax + eax + 0x20], dh 
  0x0028C38B  0003                    add      byte ptr [ebx], al             
  0x0028C38D  0020                    add      byte ptr [eax], ah             
  0x0028C38F  0005f4050000            add      byte ptr [0x5f4], al           
  0x0028C395  d821                    fsub     dword ptr [ecx]                
  0x0028C397  0010                    add      byte ptr [eax], dl             
  0x0028C399  d806                    fadd     dword ptr [esi]                
  0x0028C39B  0002                    add      byte ptr [edx], al             
  0x0028C39D  0000                    add      byte ptr [eax], al             
  0x0028C39F  0000                    add      byte ptr [eax], al             
  0x0028C3A1  58                      pop      eax                            
  0x0028C3A2  57                      push     edi                            
  0x0028C3A3  0000                    add      byte ptr [eax], al             
  0x0028C3A5  f4                      hlt                                     
  0x0028C3A6  56                      push     esi                            
  0x0028C3A7  00680b                  add      byte ptr [eax + 0xb], ch       
  0x0028C3AA  0000                    add      byte ptr [eax], al             
  0x0028C3AC  00f4                    add      ah, dh                         
  0x0028C3AE  44                      inc      esp                            
  0x0028C3AF  0003                    add      byte ptr [ebx], al             
  0x0028C3B1  0000                    add      byte ptr [eax], al             
  0x0028C3B3  004000                  add      byte ptr [eax], al             
  0x0028C3B6  2000                    and      byte ptr [eax], al             
  0x0028C3B8  0090210000e0            add      byte ptr [eax - 0x1fffffdf], dl 
  0x0028C3BE  56                      push     esi                            
  0x0028C3BF  00806f010000            add      byte ptr [eax + 0x16f], al     
  0x0028C3C5  60                      pushal                                  
  0x0028C3C6  56                      push     esi                            
  0x0028C3C7  0000                    add      byte ptr [eax], al             
  0x0028C3C9  f4                      hlt                                     
  0x0028C3CA  56                      push     esi                            
  0x0028C3CB  00680b                  add      byte ptr [eax + 0xb], ch       
  0x0028C3CE  0000                    add      byte ptr [eax], al             
  0x0028C3D0  0000                    add      byte ptr [eax], al             
  0x0028C3D2  2400                    and      al, 0                          
  0x0028C3D4  40                      inc      eax                            
  0x0028C3D5  0020                    add      byte ptr [eax], ah             
  0x0028C3D7  0000                    add      byte ptr [eax], al             
  0x0028C3D9  90                      nop                                     
  0x0028C3DA  2100                    and      dword ptr [eax], eax           
  0x0028C3DC  00f0                    add      al, dh                         
  0x0028C3DE  7000                    jo       0x28c3e0                       
                                        ; XREF: 0x0028C3DE (cond_jump)
  0x0028C3E0  40                      inc      eax                            
  0x0028C3E1  0b00                    or       eax, dword ptr [eax]           
  0x0028C3E3  0000                    add      byte ptr [eax], al             
  0x0028C3E5  e8560000f0              call     0xf028c440                     
  0x0028C3EA  44                      inc      esp                            
  0x0028C3EB  00710b                  add      byte ptr [ecx + 0xb], dh       
  0x0028C3EE  0000                    add      byte ptr [eax], al             
  0x0028C3F0  44                      inc      esp                            
  0x0028C3F1  0020                    add      byte ptr [eax], ah             
  0x0028C3F3  0000                    add      byte ptr [eax], al             
  0x0028C3F5  6856000c00              push     0xc0056                        
  0x0028C3FA  0000                    add      byte ptr [eax], al             
  0x0028C3FC  00f4                    add      ah, dh                         
  0x0028C3FE  44                      inc      esp                            
                                        ; XREF: 0x001E5C19 (data_imm)
  0x0028C3FF  0001                    add      byte ptr [ecx], al             
  0x0028C401  0000                    add      byte ptr [eax], al             
  0x0028C403  0000                    add      byte ptr [eax], al             
  0x0028C405  7044                    jo       0x28c44b                       
  0x0028C407  00960b00000c            add      byte ptr [esi + 0xc00000b], dl 
  0x0028C40D  0000                    add      byte ptr [eax], al             
  0x0028C40F  0080100d0023            add      byte ptr [eax + 0x23000d10], al 
  0x0028C415  0000                    add      byte ptr [eax], al             
  0x0028C417  0003                    add      byte ptr [ebx], al             
  0x0028C419  0020                    add      byte ptr [eax], ah             
  0x0028C41B  001b                    add      byte ptr [ebx], bl             
  0x0028C41D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C41E  050080100d              add      eax, 0xd108000                 
  0x0028C423  00a2fdff0000            add      byte ptr [edx + 0xfffd], ah    
  0x0028C429  f4                      hlt                                     
  0x0028C42A  56                      push     esi                            
  0x0028C42B  000500000000            add      byte ptr [0], al               
  0x0028C432  44                      inc      esp                            
  0x0028C433  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C436  0000                    add      byte ptr [eax], al             
  0x0028C438  45                      inc      ebp                            
  0x0028C439  0020                    add      byte ptr [eax], ah             
  0x0028C43B  0017                    add      byte ptr [edi], dl             
  0x0028C43D  f4                      hlt                                     
  0x0028C43E  050000f456              add      eax, 0x56f40000                
  0x0028C443  00680b                  add      byte ptr [eax + 0xb], ch       
  0x0028C446  0000                    add      byte ptr [eax], al             
  0x0028C448  00f0                    add      al, dh                         
  0x0028C44A  44                      inc      esp                            
                                        ; XREF: 0x0028C405 (cond_jump)
  0x0028C44B  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028C44E  0000                    add      byte ptr [eax], al             
  0x0028C450  40                      inc      eax                            
  0x0028C451  0020                    add      byte ptr [eax], ah             
  0x0028C453  00c0                    add      al, al                         
  0x0028C455  40                      inc      eax                            
  0x0028C456  0100                    add      dword ptr [eax], eax           
  0x0028C458  0100                    add      dword ptr [eax], eax           
  0x0028C45A  0000                    add      byte ptr [eax], al             
  0x0028C45C  00d0                    add      al, dl                         
  0x0028C45E  2100                    and      dword ptr [eax], eax           
  0x0028C460  00d0                    add      al, dl                         
  0x0028C462  56                      push     esi                            
  0x0028C463  0000                    add      byte ptr [eax], al             
  0x0028C465  d8440040                fadd     dword ptr [eax + eax + 0x40]   
  0x0028C469  0020                    add      byte ptr [eax], ah             
  0x0028C46B  0000                    add      byte ptr [eax], al             
  0x0028C46E  44                      inc      esp                            
  0x0028C46F  007a0b                  add      byte ptr [edx + 0xb], bh       
  0x0028C472  0000                    add      byte ptr [eax], al             
  0x0028C474  44                      inc      esp                            
  0x0028C476  45                      inc      ebp                            
  0x0028C477  00a40400006400          add      byte ptr [esp + eax + 0x640000], ah 
  0x0028C47E  2000                    and      byte ptr [eax], al             
  0x0028C480  006056                  add      byte ptr [eax + 0x56], ah      
  0x0028C483  00050c050080            add      byte ptr [0x8000050c], al      
  0x0028C489  100d00580100            adc      byte ptr [0x15800], cl         
  0x0028C48F  0080100d0086            add      byte ptr [eax - 0x79fff2f0], al 
  0x0028C495  fd                      std                                     
  0x0028C496  ff00                    inc      dword ptr [eax]                
  0x0028C498  0c00                    or       al, 0                          
  0x0028C49A  0000                    add      byte ptr [eax], al             
  0x0028C49C  00f4                    add      ah, dh                         
  0x0028C49E  45                      inc      ebp                            
  0x0028C49F  0090ffff0000            add      byte ptr [eax + 0xffff], dl    
  0x0028C4A5  7045                    jo       0x28c4ec                       
  0x0028C4A7  009f04000080            add      byte ptr [edi - 0x7ffffffc], bl 
  0x0028C4AD  100d007c0000            adc      byte ptr [0x7c00], cl          
  0x0028C4B3  0000                    add      byte ptr [eax], al             
  0x0028C4B5  f4                      hlt                                     
  0x0028C4B6  44                      inc      esp                            
  0x0028C4B7  0008                    add      byte ptr [eax], cl             
  0x0028C4B9  0000                    add      byte ptr [eax], al             
  0x0028C4BB  0000                    add      byte ptr [eax], al             
  0x0028C4BD  7044                    jo       0x28c503                       
  0x0028C4BF  009e04000000            add      byte ptr [esi + 4], bl         
  0x0028C4C5  002400                  add      byte ptr [eax + eax], ah       
  0x0028C4C8  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028C4CB  00b504000000            add      byte ptr [ebp + 4], dh         
  0x0028C4D2  50                      push     eax                            
  0x0028C4D3  009e0400000a            add      byte ptr [esi + 0xa000004], bl 
  0x0028C4D9  0000                    add      byte ptr [eax], al             
  0x0028C4DB  0000                    add      byte ptr [eax], al             
  0x0028C4DD  7050                    jo       0x28c52f                       
  0x0028C4DF  009e04000080            add      byte ptr [esi - 0x7ffffffc], bl 
  0x0028C4E5  100d00870000            adc      byte ptr [0x8700], cl          
  0x0028C4EB  000b                    add      byte ptr [ebx], cl             
  0x0028C4ED  0020                    add      byte ptr [eax], ah             
  0x0028C4EF  0009                    add      byte ptr [ecx], cl             
  0x0028C4F1  94                      xchg     esp, eax                       
  0x0028C4F2  050000f444              add      eax, 0x44f40000                
  0x0028C4F7  0001                    add      byte ptr [ecx], al             
  0x0028C4F9  0000                    add      byte ptr [eax], al             
  0x0028C4FB  0000                    add      byte ptr [eax], al             
  0x0028C4FD  7044                    jo       0x28c543                       
  0x0028C4FF  00b504000000            add      byte ptr [ebp + 4], dh         
  0x0028C506  44                      inc      esp                            
  0x0028C507  009f04000000            add      byte ptr [edi + 4], bl         
  0x0028C50D  7044                    jo       0x28c553                       
  0x0028C50F  00b604000000            add      byte ptr [esi + 4], dh         
  0x0028C516  56                      push     esi                            
  0x0028C517  00b504000003            add      byte ptr [ebp + 0x3000004], dh 
  0x0028C51D  0020                    add      byte ptr [eax], ah             
  0x0028C51F  000f                    add      byte ptr [edi], cl             
  0x0028C521  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C522  050000f456              add      eax, 0x56f40000                
  0x0028C527  0010                    add      byte ptr [eax], dl             
  0x0028C529  0000                    add      byte ptr [eax], al             
  0x0028C52B  0000                    add      byte ptr [eax], al             
  0x0028C52D  c421                    les      esp, ptr [ecx]                 
                                        ; XREF: 0x0028C4DD (cond_jump)
  0x0028C52F  0000                    add      byte ptr [eax], al             
  0x0028C531  7056                    jo       0x28c589                       
  0x0028C533  00a004000000            add      byte ptr [eax + 4], ah         
  0x0028C53A  56                      push     esi                            
  0x0028C53B  009f04000000            add      byte ptr [edi + 4], bl         
  0x0028C541  7056                    jo       0x28c599                       
                                        ; XREF: 0x0028C4FD (cond_jump)
  0x0028C543  00a104000040            add      byte ptr [ecx + 0x40000004], ah 
  0x0028C549  0020                    add      byte ptr [eax], ah             
  0x0028C54B  0022                    add      byte ptr [edx], ah             
  0x0028C54D  0020                    add      byte ptr [eax], ah             
  0x0028C54F  0000                    add      byte ptr [eax], al             
  0x0028C551  7056                    jo       0x28c5a9                       
                                        ; XREF: 0x0028C50D (cond_jump)
  0x0028C553  009f0400000e            add      byte ptr [edi + 0xe000004], bl 
  0x0028C559  0c05                    or       al, 5                          
  0x0028C55B  0000                    add      byte ptr [eax], al             
  0x0028C55D  f4                      hlt                                     
  0x0028C55E  56                      push     esi                            
  0x0028C55F  0010                    add      byte ptr [eax], dl             
  0x0028C562  ff00                    inc      dword ptr [eax]                
  0x0028C564  00c4                    add      ah, al                         
  0x0028C566  2100                    and      dword ptr [eax], eax           
  0x0028C568  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028C56B  00a104000000            add      byte ptr [ecx + 4], ah         
  0x0028C572  56                      push     esi                            
  0x0028C573  009f04000000            add      byte ptr [edi + 4], bl         
  0x0028C579  7056                    jo       0x28c5d1                       
  0x0028C57B  00a004000040            add      byte ptr [eax + 0x40000004], ah 
  0x0028C581  0020                    add      byte ptr [eax], ah             
  0x0028C583  0022                    add      byte ptr [edx], ah             
  0x0028C585  0020                    add      byte ptr [eax], ah             
  0x0028C587  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028C531 (cond_jump)
  0x0028C589  7056                    jo       0x28c5e1                       
  0x0028C58B  009f04000080            add      byte ptr [edi - 0x7ffffffc], bl 
  0x0028C591  100d00430000            adc      byte ptr [0x4300], cl          
  0x0028C597  0080100d005a            add      byte ptr [eax + 0x5a000d10], al 
  0x0028C59D  0000                    add      byte ptr [eax], al             
  0x0028C59F  000b                    add      byte ptr [ebx], cl             
  0x0028C5A1  0020                    add      byte ptr [eax], ah             
  0x0028C5A3  000e                    add      byte ptr [esi], cl             
  0x0028C5A5  94                      xchg     esp, eax                       
  0x0028C5A6  050000f044              add      eax, 0x44f00000                
  0x0028C5AB  009f04000000            add      byte ptr [edi + 4], bl         
  0x0028C5B1  7044                    jo       0x28c5f7                       
  0x0028C5B3  00a104000000            add      byte ptr [ecx + 4], ah         
  0x0028C5B9  f4                      hlt                                     
  0x0028C5BA  44                      inc      esp                            
  0x0028C5BB  0001                    add      byte ptr [ecx], al             
  0x0028C5BD  0000                    add      byte ptr [eax], al             
  0x0028C5BF  0000                    add      byte ptr [eax], al             
  0x0028C5C1  7044                    jo       0x28c607                       
  0x0028C5C3  00b504000000            add      byte ptr [ebp + 4], dh         
  0x0028C5CA  44                      inc      esp                            
  0x0028C5CB  009f04000000            add      byte ptr [edi + 4], bl         
                                        ; XREF: 0x0028C579 (cond_jump)
  0x0028C5D1  7044                    jo       0x28c617                       
  0x0028C5D3  00b604000005            add      byte ptr [esi + 0x5000004], dh 
  0x0028C5D9  0c05                    or       al, 5                          
  0x0028C5DB  0000                    add      byte ptr [eax], al             
  0x0028C5DE  44                      inc      esp                            
  0x0028C5DF  009f04000000            add      byte ptr [edi + 4], bl         
  0x0028C5E5  7044                    jo       0x28c62b                       
  0x0028C5E7  00a004000000            add      byte ptr [eax + 4], ah         
  0x0028C5EE  56                      push     esi                            
  0x0028C5EF  00a004000000            add      byte ptr [eax + 4], ah         
  0x0028C5F6  44                      inc      esp                            
                                        ; XREF: 0x0028C5B1 (cond_jump)
  0x0028C5F7  00a104000044            add      byte ptr [ecx + 0x44000004], ah 
  0x0028C5FE  2100                    and      dword ptr [eax], eax           
  0x0028C600  c54001                  lds      eax, ptr [eax + 1]             
  0x0028C603  0001                    add      byte ptr [ecx], al             
  0x0028C605  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028C5C1 (cond_jump)
  0x0028C607  0008                    add      byte ptr [eax], cl             
  0x0028C609  2405                    and      al, 5                          
  0x0028C60B  0080100d0028            add      byte ptr [eax + 0x28000d10], al 
  0x0028C611  0100                    add      dword ptr [eax], eax           
  0x0028C613  0000                    add      byte ptr [eax], al             
  0x0028C615  f4                      hlt                                     
  0x0028C616  44                      inc      esp                            
                                        ; XREF: 0x0028C5D1 (cond_jump)
  0x0028C617  0001                    add      byte ptr [ecx], al             
  0x0028C619  0000                    add      byte ptr [eax], al             
  0x0028C61B  0000                    add      byte ptr [eax], al             
  0x0028C61D  7044                    jo       0x28c663                       
  0x0028C61F  00b50400001b            add      byte ptr [ebp + 0x1b000004], dh 
  0x0028C625  0c05                    or       al, 5                          
  0x0028C627  005100                  add      byte ptr [ecx], dl             
  0x0028C62A  2000                    and      byte ptr [eax], al             
  0x0028C62C  40                      inc      eax                            
  0x0028C62D  0020                    add      byte ptr [eax], ah             
  0x0028C62F  0022                    add      byte ptr [edx], ah             
  0x0028C631  0020                    add      byte ptr [eax], ah             
  0x0028C633  004500                  add      byte ptr [ebp], al             
  0x0028C636  2000                    and      byte ptr [eax], al             
  0x0028C638  0474                    add      al, 0x74                       
  0x0028C63A  0500008e20              add      eax, 0x208e0000                
  0x0028C63F  008041010005            add      byte ptr [eax + 0x5000141], al 
  0x0028C645  0c05                    or       al, 5                          
  0x0028C647  005500                  add      byte ptr [ebp], dl             
  0x0028C64A  2000                    and      byte ptr [eax], al             
  0x0028C64C  0394050000ce20          add      edx, dword ptr [ebp + eax + 0x20ce0000] 
  0x0028C653  00844101000070          add      byte ptr [ecx + eax*2 + 0x70000001], al 
  0x0028C65A  54                      push     esp                            
  0x0028C65B  009f04000000            add      byte ptr [edi + 4], bl         
  0x0028C662  56                      push     esi                            
                                        ; XREF: 0x0028C61D (cond_jump)
  0x0028C663  009e04000084            add      byte ptr [esi - 0x7bfffffc], bl 
  0x0028C669  41                      inc      ecx                            
  0x0028C66A  0100                    add      dword ptr [eax], eax           
  0x0028C66C  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028C66F  009e04000087            add      byte ptr [esi - 0x78fffffc], bl 
  0x0028C675  7705                    ja       0x28c67c                       
  0x0028C677  0000                    add      byte ptr [eax], al             
  0x0028C67A  56                      push     esi                            
  0x0028C67B  00b504000085            add      byte ptr [ebp - 0x7afffffc], dh 
  0x0028C681  41                      inc      ecx                            
  0x0028C682  0100                    add      dword ptr [eax], eax           
  0x0028C684  0324050080100d          add      esp, dword ptr [eax + 0xd108000] 
  0x0028C68B  0009                    add      byte ptr [ecx], cl             
  0x0028C68D  0100                    add      dword ptr [eax], eax           
  0x0028C68F  0000                    add      byte ptr [eax], al             
  0x0028C692  56                      push     esi                            
  0x0028C693  00b50400000c            add      byte ptr [ebp + 0xc000004], dh 
  0x0028C699  0000                    add      byte ptr [eax], al             
  0x0028C69B  0000                    add      byte ptr [eax], al             
  0x0028C69E  56                      push     esi                            
  0x0028C69F  009f040000c0            add      byte ptr [edi - 0x3ffffffc], bl 
  0x0028C6A5  40                      inc      eax                            
  0x0028C6A6  0100                    add      dword ptr [eax], eax           
  0x0028C6A8  f00000                  lock add byte ptr [eax], al             
  0x0028C6AB  0008                    add      byte ptr [eax], cl             
  0x0028C6AD  1c0c                    sbb      al, 0xc                        
  0x0028C6AF  0000                    add      byte ptr [eax], al             
  0x0028C6B1  8421                    test     byte ptr [ecx], ah             
  0x0028C6B3  0000                    add      byte ptr [eax], al             
  0x0028C6B5  002c00                  add      byte ptr [eax + eax], ch       
  0x0028C6B8  081d0c000086            or       byte ptr [0x8600000c], bl      
  0x0028C6BE  2100                    and      dword ptr [eax], eax           
  0x0028C6C0  00f4                    add      ah, dh                         
  0x0028C6C2  60                      pushal                                  
  0x0028C6C3  00730b                  add      byte ptr [ebx + 0xb], dh       
  0x0028C6C6  0000                    add      byte ptr [eax], al             
  0x0028C6C8  00f4                    add      ah, dh                         
  0x0028C6CA  6200                    bound    eax, qword ptr [eax]           
  0x0028C6CC  790b                    jns      0x28c6d9                       
  0x0028C6CE  0000                    add      byte ptr [eax], al             
  0x0028C6D0  00f4                    add      ah, dh                         
  0x0028C6D2  6400740b00              add      byte ptr fs:[ebx + ecx], dh    
  0x0028C6D7  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028C6CC (cond_jump)
  0x0028C6D9  053c0000f0              add      eax, 0xf000003c                
  0x0028C6DE  7000                    jo       0x28c6e0                       
                                        ; XREF: 0x0028C6DE (cond_jump)
  0x0028C6E0  97                      xchg     edi, eax                       
  0x0028C6E1  0b00                    or       eax, dword ptr [eax]           
  0x0028C6E3  0000                    add      byte ptr [eax], al             
  0x0028C6E5  95                      xchg     ebp, eax                       
  0x0028C6E6  2200                    and      al, byte ptr [eax]             
  0x0028C6E8  005844                  add      byte ptr [eax + 0x44], bl      
  0x0028C6EB  0000                    add      byte ptr [eax], al             
  0x0028C6ED  5a                      pop      edx                            
  0x0028C6EE  46                      inc      esi                            
  0x0028C6EF  0010                    add      byte ptr [eax], dl             
  0x0028C6F1  d806                    fadd     dword ptr [esi]                
  0x0028C6F3  0002                    add      byte ptr [edx], al             
  0x0028C6F5  0000                    add      byte ptr [eax], al             
  0x0028C6F7  0000                    add      byte ptr [eax], al             
  0x0028C6F9  5d                      pop      ebp                            
  0x0028C6FA  46                      inc      esi                            
  0x0028C6FB  000c00                  add      byte ptr [eax + eax], cl       
  0x0028C6FE  0000                    add      byte ptr [eax], al             
  0x0028C700  00f0                    add      al, dh                         
  0x0028C702  7000                    jo       0x28c704                       
                                        ; XREF: 0x0028C702 (cond_jump)
  0x0028C704  40                      inc      eax                            
  0x0028C705  0b00                    or       eax, dword ptr [eax]           
  0x0028C707  0000                    add      byte ptr [eax], al             
  0x0028C709  f4                      hlt                                     
  0x0028C70A  60                      pushal                                  
  0x0028C70B  00680b                  add      byte ptr [eax + 0xb], ch       
  0x0028C70E  0000                    add      byte ptr [eax], al             
  0x0028C710  00e8                    add      al, ch                         
  0x0028C712  57                      push     edi                            
  0x0028C713  0000                    add      byte ptr [eax], al             
  0x0028C715  fa                      cli                                     
  0x0028C716  2100                    and      dword ptr [eax], eax           
  0x0028C718  00f0                    add      al, dh                         
  0x0028C71A  56                      push     esi                            
  0x0028C71B  00c0                    add      al, al                         
  0x0028C71D  0400                    add      al, 0                          
  0x0028C71F  0003                    add      byte ptr [ebx], al             
  0x0028C721  0020                    add      byte ptr [eax], ah             
  0x0028C723  0045a5                  add      byte ptr [ebp - 0x5b], al      
  0x0028C726  050000f456              add      eax, 0x56f40000                
  0x0028C72B  0001                    add      byte ptr [ecx], al             
  0x0028C72D  0000                    add      byte ptr [eax], al             
  0x0028C72F  0000                    add      byte ptr [eax], al             
  0x0028C731  7056                    jo       0x28c789                       
  0x0028C733  00b704000000            add      byte ptr [edi + 4], dh         
  0x0028C739  f4                      hlt                                     
  0x0028C73A  56                      push     esi                            
  0x0028C73B  0000                    add      byte ptr [eax], al             
  0x0028C73D  0000                    add      byte ptr [eax], al             
  0x0028C73F  0000                    add      byte ptr [eax], al             
  0x0028C742  44                      inc      esp                            
  0x0028C743  00730b                  add      byte ptr [ebx + 0xb], dh       
  0x0028C746  0000                    add      byte ptr [eax], al             
  0x0028C748  45                      inc      ebp                            
  0x0028C749  0020                    add      byte ptr [eax], ah             
  0x0028C74B  0004a4                  add      byte ptr [esp], al             
  0x0028C74E  0500000024              add      eax, 0x24000000                
  0x0028C753  0000                    add      byte ptr [eax], al             
  0x0028C755  7044                    jo       0x28c79b                       
  0x0028C757  00b704000000            add      byte ptr [edi + 4], dh         
  0x0028C75D  f4                      hlt                                     
  0x0028C75E  46                      inc      esi                            
  0x0028C75F  0000                    add      byte ptr [eax], al             
  0x0028C761  0000                    add      byte ptr [eax], al             
  0x0028C763  0000                    add      byte ptr [eax], al             
  0x0028C765  f4                      hlt                                     
  0x0028C766  60                      pushal                                  
  0x0028C767  00740b00                add      byte ptr [ebx + ecx], dh       
  0x0028C76B  0000                    add      byte ptr [eax], al             
  0x0028C76E  44                      inc      esp                            
  0x0028C76F  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028C775  c406                    les      eax, ptr [esi]                 
  0x0028C777  0008                    add      byte ptr [eax], cl             
  0x0028C779  0000                    add      byte ptr [eax], al             
  0x0028C77B  0000                    add      byte ptr [eax], al             
  0x0028C77D  d85600                  fcom     dword ptr [esi]                
  0x0028C780  55                      push     ebp                            
  0x0028C781  0020                    add      byte ptr [eax], ah             
  0x0028C783  0004a4                  add      byte ptr [esp], al             
  0x0028C786  0500130020              add      eax, 0x20001300                
  0x0028C78B  0000                    add      byte ptr [eax], al             
  0x0028C78D  7056                    jo       0x28c7e5                       
  0x0028C78F  00b704000000            add      byte ptr [edi + 4], dh         
  0x0028C795  0000                    add      byte ptr [eax], al             
  0x0028C797  0000                    add      byte ptr [eax], al             
  0x0028C79A  56                      push     esi                            
                                        ; XREF: 0x0028C755 (cond_jump)
  0x0028C79B  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028C79E  0000                    add      byte ptr [eax], al             
  0x0028C7A0  0300                    add      eax, dword ptr [eax]           
  0x0028C7A2  2000                    and      byte ptr [eax], al             
  0x0028C7A4  08a4050000f056          or       byte ptr [ebp + eax + 0x56f00000], ah 
  0x0028C7AB  00790b                  add      byte ptr [ecx + 0xb], bh       
  0x0028C7AE  0000                    add      byte ptr [eax], al             
  0x0028C7B0  55                      push     ebp                            
  0x0028C7B1  0020                    add      byte ptr [eax], ah             
  0x0028C7B3  0004a4                  add      byte ptr [esp], al             
  0x0028C7B6  0500130020              add      eax, 0x20001300                
  0x0028C7BB  0000                    add      byte ptr [eax], al             
  0x0028C7BD  7056                    jo       0x28c815                       
  0x0028C7BF  00b704000000            add      byte ptr [edi + 4], dh         
  0x0028C7C5  07                      pop      es                             
  0x0028C7C6  3000                    xor      byte ptr [eax], al             
  0x0028C7C8  c4700b                  les      esi, ptr [eax + 0xb]           
  0x0028C7CB  00b20c000000            add      byte ptr [edx + 0xc], dh       
  0x0028C7D1  7044                    jo       0x28c817                       
  0x0028C7D3  00bf04000013            add      byte ptr [edi + 0x13000004], bh 
  0x0028C7D9  f4                      hlt                                     
  0x0028C7DA  60                      pushal                                  
  0x0028C7DB  00a504000090            add      byte ptr [ebp - 0x6ffffffc], ah 
  0x0028C7E1  1006                    adc      byte ptr [esi], al             
  0x0028C7E3  0002                    add      byte ptr [edx], al             
                                        ; XREF: 0x0028C78D (cond_jump)
  0x0028C7E5  0000                    add      byte ptr [eax], al             
  0x0028C7E7  0000                    add      byte ptr [eax], al             
  0x0028C7E9  58                      pop      eax                            
  0x0028C7EA  56                      push     esi                            
  0x0028C7EB  0000                    add      byte ptr [eax], al             
  0x0028C7ED  0036                    add      byte ptr [esi], dh             
  0x0028C7EF  0000                    add      byte ptr [eax], al             
  0x0028C7F2  44                      inc      esp                            
  0x0028C7F3  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028C7F9  c406                    les      eax, ptr [esi]                 
  0x0028C7FB  0036                    add      byte ptr [esi], dh             
  0x0028C7FD  0000                    add      byte ptr [eax], al             
  0x0028C7FF  0000                    add      byte ptr [eax], al             
  0x0028C801  f4                      hlt                                     
  0x0028C802  56                      push     esi                            
  0x0028C803  00740b00                add      byte ptr [ebx + ecx], dh       
  0x0028C807  0000                    add      byte ptr [eax], al             
  0x0028C809  c422                    les      esp, ptr [edx]                 
  0x0028C80B  004000                  add      byte ptr [eax], al             
  0x0028C80E  2000                    and      byte ptr [eax], al             
  0x0028C810  0090210000f0            add      byte ptr [eax - 0xfffffdf], dl 
  0x0028C816  56                      push     esi                            
                                        ; XREF: 0x0028C7D1 (cond_jump)
  0x0028C817  00730b                  add      byte ptr [ebx + 0xb], dh       
  0x0028C81A  0000                    add      byte ptr [eax], al             
  0x0028C81C  00e0                    add      al, ah                         
  0x0028C81E  44                      inc      esp                            
  0x0028C81F  00844f0100081d          add      byte ptr [edi + ecx*2 + 0x1d080001], al 
  0x0028C826  0c00                    or       al, 0                          
  0x0028C828  40                      inc      eax                            
  0x0028C829  0020                    add      byte ptr [eax], ah             
  0x0028C82B  00041d0c000070          add      byte ptr [ebx + 0x7000000c], al 
  0x0028C832  54                      push     esp                            
  0x0028C833  00a204000000            add      byte ptr [edx + 4], ah         
  0x0028C839  f4                      hlt                                     
  0x0028C83A  56                      push     esi                            
  0x0028C83B  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x0028C841  c422                    les      esp, ptr [edx]                 
  0x0028C843  004000                  add      byte ptr [eax], al             
  0x0028C846  2000                    and      byte ptr [eax], al             
  0x0028C848  009021000000            add      byte ptr [eax + 0x21], dl      
  0x0028C84E  250000e047              and      eax, 0x47e00000                
  0x0028C853  0000                    add      byte ptr [eax], al             
  0x0028C855  c422                    les      esp, ptr [edx]                 
  0x0028C857  0000                    add      byte ptr [eax], al             
  0x0028C859  f4                      hlt                                     
  0x0028C85A  46                      inc      esi                            
  0x0028C85B  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028C861  f4                      hlt                                     
  0x0028C862  44                      inc      esp                            
  0x0028C863  00fa                    add      dl, bh                         
  0x0028C865  0000                    add      byte ptr [eax], al             
  0x0028C867  002e                    add      byte ptr [esi], ch             
  0x0028C869  1d0c004000              sbb      eax, 0x40000c                  
  0x0028C86E  2000                    and      byte ptr [eax], al             
  0x0028C870  0090210000c4            add      byte ptr [eax - 0x3bffffdf], dl 
  0x0028C876  2200                    and      al, byte ptr [eax]             
  0x0028C878  00f4                    add      ah, dh                         
  0x0028C87A  46                      inc      esi                            
  0x0028C87B  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028C882  44                      inc      esp                            
  0x0028C883  00720b                  add      byte ptr [edx + 0xb], dh       
  0x0028C886  0000                    add      byte ptr [eax], al             
  0x0028C888  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028C88E  2000                    and      byte ptr [eax], al             
  0x0028C890  0091210000c4            add      byte ptr [ecx - 0x3bffffdf], dl 
  0x0028C896  2200                    and      al, byte ptr [eax]             
  0x0028C898  00f4                    add      ah, dh                         
  0x0028C89A  46                      inc      esi                            
  0x0028C89B  0032                    add      byte ptr [edx], dh             
  0x0028C89D  0000                    add      byte ptr [eax], al             
  0x0028C89F  00d0                    add      al, dl                         
  0x0028C8A1  f4                      hlt                                     
  0x0028C8A2  44                      inc      esp                            
  0x0028C8A3  0000                    add      byte ptr [eax], al             
  0x0028C8A5  0000                    add      byte ptr [eax], al             
  0x0028C8A7  002e                    add      byte ptr [esi], ch             
  0x0028C8A9  1d0c004000              sbb      eax, 0x40000c                  
  0x0028C8AE  2000                    and      byte ptr [eax], al             
  0x0028C8B0  0092210000f4            add      byte ptr [edx - 0xbffffdf], dl 
  0x0028C8B6  65001a                  add      byte ptr gs:[edx], bl          
  0x0028C8B9  0f0000                  sldt     word ptr [eax]                 
  0x0028C8BC  007066                  add      byte ptr [eax + 0x66], dh      
  0x0028C8BF  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028C8C2  0000                    add      byte ptr [eax], al             
  0x0028C8C4  86040d0000f066          xchg     byte ptr [ecx + 0x66f00000], al 
  0x0028C8CB  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028C8CE  0000                    add      byte ptr [eax], al             
  0x0028C8D0  005e20                  add      byte ptr [esi + 0x20], bl      
  0x0028C8D3  0000                    add      byte ptr [eax], al             
  0x0028C8D6  56                      push     esi                            
  0x0028C8D7  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028C8DA  0000                    add      byte ptr [eax], al             
  0x0028C8DC  0300                    add      eax, dword ptr [eax]           
  0x0028C8DE  2000                    and      byte ptr [eax], al             
  0x0028C8E0  17                      pop      ss                             
  0x0028C8E1  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028C8E2  050000f056              add      eax, 0x56f00000                
  0x0028C8E7  00730b                  add      byte ptr [ebx + 0xb], dh       
  0x0028C8EA  0000                    add      byte ptr [eax], al             
  0x0028C8EC  00f0                    add      al, dh                         
  0x0028C8EE  44                      inc      esp                            
  0x0028C8EF  00790b                  add      byte ptr [ecx + 0xb], bh       
  0x0028C8F2  0000                    add      byte ptr [eax], al             
  0x0028C8F4  844f01                  test     byte ptr [edi + 1], cl         
  0x0028C8F7  0008                    add      byte ptr [eax], cl             
  0x0028C8F9  1d0c004000              sbb      eax, 0x40000c                  
  0x0028C8FE  2000                    and      byte ptr [eax], al             
  0x0028C900  041d                    add      al, 0x1d                       
  0x0028C902  0c00                    or       al, 0                          
  0x0028C904  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028C907  00a204000000            add      byte ptr [edx + 4], ah         
  0x0028C90D  00250000f447            add      byte ptr [0x47f40000], ah      
  0x0028C913  0007                    add      byte ptr [edi], al             
  0x0028C915  0000                    add      byte ptr [eax], al             
  0x0028C917  0000                    add      byte ptr [eax], al             
  0x0028C919  f4                      hlt                                     
  0x0028C91A  60                      pushal                                  
  0x0028C91B  008304000000            add      byte ptr [ebx + 4], al         
  0x0028C921  f4                      hlt                                     
  0x0028C922  61                      popal                                   
  0x0028C923  0039                    add      byte ptr [ecx], bh             
  0x0028C925  0b00                    or       eax, dword ptr [eax]           
  0x0028C927  0000                    add      byte ptr [eax], al             
  0x0028C929  f4                      hlt                                     
  0x0028C92A  6200                    bound    eax, qword ptr [eax]           
  0x0028C92C  b804000000              mov      eax, 4                         
  0x0028C931  f4                      hlt                                     
  0x0028C932  65001a                  add      byte ptr gs:[edx], bl          
  0x0028C935  0f0000                  sldt     word ptr [eax]                 
  0x0028C938  86040d0000f460          xchg     byte ptr [ecx + 0x60f40000], al 
  0x0028C93F  00a60400001b            add      byte ptr [esi + 0x1b000004], ah 
  0x0028C945  f4                      hlt                                     
  0x0028C946  6600fb                  add      bl, bh                         
  0x0028C949  0c00                    or       al, 0                          
  0x0028C94B  0000                    add      byte ptr [eax], al             
  0x0028C94D  d8440013                fadd     dword ptr [eax + eax + 0x13]   
  0x0028C951  f4                      hlt                                     
  0x0028C952  47                      inc      edi                            
  0x0028C953  005555                  add      byte ptr [ebp + 0x55], dl      
  0x0028C956  d500                    aad      0                              
  0x0028C958  00e8                    add      al, ch                         
  0x0028C95A  2000                    and      byte ptr [eax], al             
  0x0028C95D  de4e00                  fimul    word ptr [esi]                 
  0x0028C960  13842100dad844          adc      eax, dword ptr [ecx + 0x44d8da00] 
  0x0028C967  0000                    add      byte ptr [eax], al             
  0x0028C969  e82000c6de              call     0xdeeec98e                     
  0x0028C96E  4e                      dec      esi                            
  0x0028C96F  0000                    add      byte ptr [eax], al             
  0x0028C971  8421                    test     byte ptr [ecx], ah             
  0x0028C973  00da                    add      dl, bl                         
  0x0028C975  d8f0                    fdiv     st(0)                          
  0x0028C977  00da                    add      dl, bl                         
  0x0028C979  d8440013                fadd     dword ptr [eax + eax + 0x13]   
  0x0028C97D  f4                      hlt                                     
  0x0028C97E  47                      inc      edi                            
  0x0028C97F  0000                    add      byte ptr [eax], al             
  0x0028C981  00c0                    add      al, al                         
  0x0028C983  0000                    add      byte ptr [eax], al             
  0x0028C985  e82000c6de              call     0xdeeec9aa                     
  0x0028C98A  4e                      dec      esi                            
  0x0028C98B  0000                    add      byte ptr [eax], al             
  0x0028C98D  8421                    test     byte ptr [ecx], ah             
  0x0028C98F  00da                    add      dl, bl                         
  0x0028C991  0020                    add      byte ptr [eax], ah             
  0x0028C993  0000                    add      byte ptr [eax], al             
  0x0028C995  d8f0                    fdiv     st(0)                          
  0x0028C997  00900a060002            add      byte ptr [eax + 0x200060a], dl 
  0x0028C99D  0000                    add      byte ptr [eax], al             
  0x0028C99F  00da                    add      dl, bl                         
  0x0028C9A1  d8f0                    fdiv     st(0)                          
  0x0028C9A3  00da                    add      dl, bl                         
  0x0028C9A5  0020                    add      byte ptr [eax], ah             
  0x0028C9A7  00ae1d0c0000            add      byte ptr [esi + 0xc1d], ch     
  0x0028C9AD  7056                    jo       0x28ca05                       
  0x0028C9AF  007a0b                  add      byte ptr [edx + 0xb], bh       
  0x0028C9B2  0000                    add      byte ptr [eax], al             
  0x0028C9B4  020c0500000c05          add      cl, byte ptr [eax + 0x50c0000] 
  0x0028C9BB  001b                    add      byte ptr [ebx], bl             
  0x0028C9BE  44                      inc      esp                            
  0x0028C9BF  007a0b                  add      byte ptr [edx + 0xb], bh       
  0x0028C9C2  0000                    add      byte ptr [eax], al             
  0x0028C9C4  004f23                  add      byte ptr [edi + 0x23], cl      
  0x0028C9C7  004c0020                add      byte ptr [eax + eax + 0x20], cl 
  0x0028C9CB  0000                    add      byte ptr [eax], al             
  0x0028C9CD  fa                      cli                                     
  0x0028C9CE  2100                    and      dword ptr [eax], eax           
  0x0028C9D0  0b00                    or       eax, dword ptr [eax]           
  0x0028C9D2  2000                    and      byte ptr [eax], al             
  0x0028C9D4  02140500030c05          add      dl, byte ptr [eax + 0x50c0300] 
  0x0028C9DB  0080100d0033            add      byte ptr [eax + 0x33000d10], al 
  0x0028C9E1  fc                      cld                                     
  0x0028C9E2  ff00                    inc      dword ptr [eax]                
  0x0028C9E4  0c00                    or       al, 0                          
  0x0028C9E6  0000                    add      byte ptr [eax], al             
  0x0028C9E8  1bf4                    sbb      esi, esp                       
  0x0028C9EA  60                      pushal                                  
  0x0028C9EB  007a0b                  add      byte ptr [edx + 0xb], bh       
  0x0028C9EE  0000                    add      byte ptr [eax], al             
  0x0028C9F0  006057                  add      byte ptr [eax + 0x57], ah      
  0x0028C9F3  0000                    add      byte ptr [eax], al             
  0x0028C9F5  f4                      hlt                                     
  0x0028C9F6  60                      pushal                                  
  0x0028C9F7  00730b                  add      byte ptr [ebx + 0xb], dh       
  0x0028C9FA  0000                    add      byte ptr [eax], al             
  0x0028C9FC  00f4                    add      ah, dh                         
  0x0028C9FE  6200                    bound    eax, qword ptr [eax]           
  0x0028CA00  790b                    jns      0x28ca0d                       
  0x0028CA02  0000                    add      byte ptr [eax], al             
  0x0028CA04  00f4                    add      ah, dh                         
  0x0028CA06  6400740b00              add      byte ptr fs:[ebx + ecx], dh    
  0x0028CA0B  0000                    add      byte ptr [eax], al             
  0x0028CA0E  7000                    jo       0x28ca10                       
                                        ; XREF: 0x0028CA0E (cond_jump)
  0x0028CA10  97                      xchg     edi, eax                       
  0x0028CA11  0b00                    or       eax, dword ptr [eax]           
  0x0028CA13  0000                    add      byte ptr [eax], al             
  0x0028CA15  95                      xchg     ebp, eax                       
  0x0028CA16  2200                    and      al, byte ptr [eax]             
  0x0028CA18  006057                  add      byte ptr [eax + 0x57], ah      
  0x0028CA1B  0000                    add      byte ptr [eax], al             
  0x0028CA1D  625700                  bound    edx, qword ptr [edi]           
  0x0028CA20  10d8                    adc      al, bl                         
  0x0028CA22  06                      push     es                             
  0x0028CA23  0002                    add      byte ptr [edx], al             
  0x0028CA25  0000                    add      byte ptr [eax], al             
  0x0028CA27  0000                    add      byte ptr [eax], al             
  0x0028CA29  5d                      pop      ebp                            
  0x0028CA2A  57                      push     edi                            
  0x0028CA2B  0000                    add      byte ptr [eax], al             
  0x0028CA2D  0036                    add      byte ptr [esi], dh             
  0x0028CA2F  0000                    add      byte ptr [eax], al             
  0x0028CA32  44                      inc      esp                            
  0x0028CA33  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028CA39  c406                    les      eax, ptr [esi]                 
  0x0028CA3B  0012                    add      byte ptr [edx], dl             
  0x0028CA3D  0000                    add      byte ptr [eax], al             
  0x0028CA3F  0000                    add      byte ptr [eax], al             
  0x0028CA41  c422                    les      esp, ptr [edx]                 
  0x0028CA43  0000                    add      byte ptr [eax], al             
  0x0028CA45  f4                      hlt                                     
  0x0028CA46  46                      inc      esi                            
  0x0028CA47  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028CA4E  44                      inc      esp                            
  0x0028CA4F  00720b                  add      byte ptr [edx + 0xb], dh       
  0x0028CA52  0000                    add      byte ptr [eax], al             
  0x0028CA54  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028CA5A  2000                    and      byte ptr [eax], al             
  0x0028CA5C  0090210000f4            add      byte ptr [eax - 0xbffffdf], dl 
  0x0028CA62  56                      push     esi                            
  0x0028CA63  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x0028CA69  c422                    les      esp, ptr [edx]                 
  0x0028CA6B  004000                  add      byte ptr [eax], al             
  0x0028CA6E  2000                    and      byte ptr [eax], al             
  0x0028CA70  009221001062            add      byte ptr [edx + 0x62100021], dl 
  0x0028CA76  06                      push     es                             
  0x0028CA77  0002                    add      byte ptr [edx], al             
  0x0028CA79  0000                    add      byte ptr [eax], al             
  0x0028CA7B  0000                    add      byte ptr [eax], al             
  0x0028CA7D  58                      pop      eax                            
  0x0028CA7E  57                      push     edi                            
  0x0028CA7F  0000                    add      byte ptr [eax], al             
  0x0028CA81  5e                      pop      esi                            
  0x0028CA82  2000                    and      byte ptr [eax], al             
  0x0028CA84  00f0                    add      al, dh                         
  0x0028CA86  56                      push     esi                            
  0x0028CA87  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028CA8A  0000                    add      byte ptr [eax], al             
  0x0028CA8C  0300                    add      eax, dword ptr [eax]           
  0x0028CA8E  2000                    and      byte ptr [eax], al             
  0x0028CA90  06                      push     es                             
  0x0028CA91  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028CA92  050000f460              add      eax, 0x60f40000                
  0x0028CA97  0039                    add      byte ptr [ecx], bh             
  0x0028CA99  0b00                    or       eax, dword ptr [eax]           
  0x0028CA9B  009007060002            add      byte ptr [eax + 0x2000607], dl 
  0x0028CAA1  0000                    add      byte ptr [eax], al             
  0x0028CAA3  0000                    add      byte ptr [eax], al             
  0x0028CAA5  58                      pop      eax                            
  0x0028CAA6  57                      push     edi                            
  0x0028CAA7  000c00                  add      byte ptr [eax + eax], cl       
  0x0028CAAA  0000                    add      byte ptr [eax], al             
  0x0028CAAC  00f0                    add      al, dh                         
  0x0028CAAE  44                      inc      esp                            
  0x0028CAAF  00b604000000            add      byte ptr [esi + 4], dh         
  0x0028CAB5  7044                    jo       0x28cafb                       
  0x0028CAB7  009f04000080            add      byte ptr [edi - 0x7ffffffc], bl 
  0x0028CABD  100d00f8feff            adc      byte ptr [0xfffef800], cl      
  0x0028CAC3  000f                    add      byte ptr [edi], cl             
  0x0028CAC5  0a05000c0000            or       al, byte ptr [0xc00]           
  0x0028CACB  001b                    add      byte ptr [ebx], bl             
  0x0028CACD  0020                    add      byte ptr [eax], ah             
  0x0028CACF  008850010088            add      byte ptr [eax - 0x77fffeb0], cl 
  0x0028CAD5  50                      push     eax                            
  0x0028CAD6  0100                    add      dword ptr [eax], eax           
  0x0028CAD8  884201                  mov      byte ptr [edx + 1], al         
  0x0028CADB  008846010088            add      byte ptr [eax - 0x77fffeba], cl 
  0x0028CAE1  45                      inc      ebp                            
  0x0028CAE2  0100                    add      dword ptr [eax], eax           
  0x0028CAE4  884301                  mov      byte ptr [ebx + 1], al         
  0x0028CAE7  008843010000            add      byte ptr [eax + 0x143], cl     
  0x0028CAEE  56                      push     esi                            
  0x0028CAEF  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028CAF2  0000                    add      byte ptr [eax], al             
  0x0028CAF4  854101                  test     dword ptr [ecx + 1], eax       
  0x0028CAF7  0004a4                  add      byte ptr [esp], al             
  0x0028CAFA  0500864101              add      eax, 0x1418600                 
  0x0028CAFF  0002                    add      byte ptr [edx], al             
  0x0028CB01  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028CB02  0500884201              add      eax, 0x1428800                 
  0x0028CB07  0000                    add      byte ptr [eax], al             
  0x0028CB0A  56                      push     esi                            
  0x0028CB0B  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028CB0E  0000                    add      byte ptr [eax], al             
  0x0028CB10  86440100                xchg     byte ptr [ecx + eax], al       
  0x0028CB14  02a40500884201          add      ah, byte ptr [ebp + eax + 0x1428800] 
  0x0028CB1B  0000                    add      byte ptr [eax], al             
  0x0028CB1E  56                      push     esi                            
  0x0028CB1F  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028CB22  0000                    add      byte ptr [eax], al             
  0x0028CB24  854201                  test     dword ptr [edx + 1], eax       
  0x0028CB27  0002                    add      byte ptr [edx], al             
  0x0028CB29  2405                    and      al, 5                          
  0x0028CB2B  008842010088            add      byte ptr [eax - 0x77fffebe], cl 
  0x0028CB31  41                      inc      ecx                            
  0x0028CB32  0100                    add      dword ptr [eax], eax           
  0x0028CB34  884501                  mov      byte ptr [ebp + 1], al         
  0x0028CB37  008841010000            add      byte ptr [eax + 0x141], cl     
  0x0028CB3E  56                      push     esi                            
  0x0028CB3F  004c0b00                add      byte ptr [ebx + ecx], cl       
  0x0028CB43  0003                    add      byte ptr [ebx], al             
  0x0028CB45  f4                      hlt                                     
  0x0028CB46  44                      inc      esp                            
  0x0028CB47  0008                    add      byte ptr [eax], cl             
  0x0028CB49  0000                    add      byte ptr [eax], al             
  0x0028CB4B  0002                    add      byte ptr [edx], al             
  0x0028CB4D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028CB4E  0500480020              add      eax, 0x20004800                
  0x0028CB53  008841010088            add      byte ptr [eax - 0x77fffebf], cl 
  0x0028CB59  41                      inc      ecx                            
  0x0028CB5A  0100                    add      dword ptr [eax], eax           
  0x0028CB5C  884101                  mov      byte ptr [ecx + 1], al         
  0x0028CB5F  008841010088            add      byte ptr [eax - 0x77fffebf], cl 
  0x0028CB65  41                      inc      ecx                            
  0x0028CB66  0100                    add      dword ptr [eax], eax           
  0x0028CB68  884101                  mov      byte ptr [ecx + 1], al         
  0x0028CB6B  008841010000            add      byte ptr [eax + 0x141], cl     
  0x0028CB71  7057                    jo       0x28cbca                       
  0x0028CB73  00510b                  add      byte ptr [ecx + 0xb], dl       
  0x0028CB76  0000                    add      byte ptr [eax], al             
  0x0028CB78  0c00                    or       al, 0                          
  0x0028CB7A  0000                    add      byte ptr [eax], al             
  0x0028CB7C  0000                    add      byte ptr [eax], al             
  0x0028CB7E  360000                  add      byte ptr ss:[eax], al          
  0x0028CB82  44                      inc      esp                            
  0x0028CB83  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028CB89  c406                    les      eax, ptr [esi]                 
  0x0028CB8B  003400                  add      byte ptr [eax + eax], dh       
  0x0028CB8E  0000                    add      byte ptr [eax], al             
  0x0028CB90  00f4                    add      ah, dh                         
  0x0028CB92  56                      push     esi                            
  0x0028CB93  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028CB99  c422                    les      esp, ptr [edx]                 
  0x0028CB9B  004000                  add      byte ptr [eax], al             
  0x0028CB9E  2000                    and      byte ptr [eax], al             
  0x0028CBA0  0090210000e0            add      byte ptr [eax - 0x1fffffdf], dl 
  0x0028CBA6  56                      push     esi                            
  0x0028CBA7  0003                    add      byte ptr [ebx], al             
  0x0028CBA9  92                      xchg     edx, eax                       
  0x0028CBAA  2100                    and      dword ptr [eax], eax           
  0x0028CBAC  4b                      dec      ebx                            
  0x0028CBAD  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028CBAE  050000c422              add      eax, 0x22c40000                
  0x0028CBB3  0000                    add      byte ptr [eax], al             
  0x0028CBB5  f4                      hlt                                     
  0x0028CBB6  46                      inc      esi                            
  0x0028CBB7  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028CBBD  f4                      hlt                                     
  0x0028CBBE  44                      inc      esp                            
  0x0028CBBF  00fa                    add      dl, bh                         
  0x0028CBC1  0000                    add      byte ptr [eax], al             
  0x0028CBC3  002e                    add      byte ptr [esi], ch             
  0x0028CBC5  1d0c004000              sbb      eax, 0x40000c                  
                                        ; XREF: 0x0028CB71 (cond_jump)
  0x0028CBCA  2000                    and      byte ptr [eax], al             
  0x0028CBCC  0090210000f4            add      byte ptr [eax - 0xbffffdf], dl 
  0x0028CBD2  56                      push     esi                            
  0x0028CBD3  005c0b00                add      byte ptr [ebx + ecx], bl       
  0x0028CBD7  0000                    add      byte ptr [eax], al             
  0x0028CBD9  c422                    les      esp, ptr [edx]                 
  0x0028CBDB  004000                  add      byte ptr [eax], al             
  0x0028CBDE  2000                    and      byte ptr [eax], al             
  0x0028CBE0  0091210000e1            add      byte ptr [ecx - 0x1effffdf], dl 
  0x0028CBE6  7000                    jo       0x28cbe8                       
                                        ; XREF: 0x0028CBE6 (cond_jump)
  0x0028CBE8  d9720b                  fnstenv  [edx + 0xb]                    
  0x0028CBEB  0012                    add      byte ptr [edx], dl             
  0x0028CBED  0f0000                  sldt     word ptr [eax]                 
  0x0028CBF0  00f4                    add      ah, dh                         
  0x0028CBF2  56                      push     esi                            
  0x0028CBF3  00910b000000            add      byte ptr [ecx + 0xb], dl       
  0x0028CBF9  c422                    les      esp, ptr [edx]                 
  0x0028CBFB  004000                  add      byte ptr [eax], al             
  0x0028CBFE  2000                    and      byte ptr [eax], al             
  0x0028CC00  0091210000e1            add      byte ptr [ecx - 0x1effffdf], dl 
  0x0028CC06  7200                    jb       0x28cc08                       
                                        ; XREF: 0x0028CC06 (cond_jump)
  0x0028CC08  00d8                    add      al, bl                         
  0x0028CC0A  45                      inc      ebp                            
  0x0028CC0B  0000                    add      byte ptr [eax], al             
  0x0028CC0D  c422                    les      esp, ptr [edx]                 
  0x0028CC0F  0000                    add      byte ptr [eax], al             
  0x0028CC11  f4                      hlt                                     
  0x0028CC12  46                      inc      esi                            
  0x0028CC13  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028CC19  f4                      hlt                                     
  0x0028CC1A  44                      inc      esp                            
  0x0028CC1B  00b00700002e            add      byte ptr [eax + 0x2e000007], dh 
  0x0028CC21  1d0c004000              sbb      eax, 0x40000c                  
  0x0028CC26  2000                    and      byte ptr [eax], al             
  0x0028CC28  00952100005d            add      byte ptr [ebp + 0x5d000021], dl 
  0x0028CC2E  45                      inc      ebp                            
  0x0028CC2F  0000                    add      byte ptr [eax], al             
  0x0028CC31  c422                    les      esp, ptr [edx]                 
  0x0028CC33  0000                    add      byte ptr [eax], al             
  0x0028CC35  f4                      hlt                                     
  0x0028CC36  46                      inc      esi                            
  0x0028CC37  001f                    add      byte ptr [edi], bl             
  0x0028CC39  0000                    add      byte ptr [eax], al             
  0x0028CC3B  00d0                    add      al, dl                         
  0x0028CC3D  f4                      hlt                                     
  0x0028CC3E  44                      inc      esp                            
  0x0028CC3F  0000                    add      byte ptr [eax], al             
  0x0028CC41  0000                    add      byte ptr [eax], al             
  0x0028CC43  002e                    add      byte ptr [esi], ch             
  0x0028CC45  1d0c004000              sbb      eax, 0x40000c                  
  0x0028CC4A  2000                    and      byte ptr [eax], al             
  0x0028CC4C  00942100005c4d          add      byte ptr [ecx + 0x4d5c0000], dl 
  0x0028CC53  001e                    add      byte ptr [esi], bl             
  0x0028CC55  050d00005e              add      eax, 0x5e00000d                
  0x0028CC5A  2000                    and      byte ptr [eax], al             
  0x0028CC5C  00f0                    add      al, dh                         
  0x0028CC5E  56                      push     esi                            
  0x0028CC5F  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028CC62  0000                    add      byte ptr [eax], al             
  0x0028CC64  0300                    add      eax, dword ptr [eax]           
  0x0028CC66  2000                    and      byte ptr [eax], al             
  0x0028CC68  13a4050000f056          adc      esp, dword ptr [ebp + eax + 0x56f00000] 
  0x0028CC6F  008f0b000003            add      byte ptr [edi + 0x300000b], cl 
  0x0028CC75  0020                    add      byte ptr [eax], ah             
  0x0028CC77  000f                    add      byte ptr [edi], cl             
  0x0028CC79  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028CC7A  050000f460              add      eax, 0x60f40000                
  0x0028CC7F  008304000000            add      byte ptr [ebx + 4], al         
  0x0028CC85  06                      push     es                             
  0x0028CC86  3800                    cmp      byte ptr [eax], al             
  0x0028CC88  00f0                    add      al, dh                         
  0x0028CC8A  7900                    jns      0x28cc8c                       
                                        ; XREF: 0x0028CC8A (cond_jump)
  0x0028CC8C  130f                    adc      ecx, dword ptr [edi]           
  0x0028CC8E  0000                    add      byte ptr [eax], al             
  0x0028CC90  0002                    add      byte ptr [edx], al             
  0x0028CC92  3a00                    cmp      al, byte ptr [eax]             
  0x0028CC94  00d8                    add      al, bl                         
  0x0028CC96  45                      inc      ebp                            
  0x0028CC97  0000                    add      byte ptr [eax], al             
  0x0028CC99  f4                      hlt                                     
  0x0028CC9A  650039                  add      byte ptr gs:[ecx], bh          
  0x0028CC9D  0b00                    or       eax, dword ptr [eax]           
  0x0028CC9F  0000                    add      byte ptr [eax], al             
  0x0028CCA1  5d                      pop      ebp                            
  0x0028CCA2  45                      inc      ebp                            
  0x0028CCA3  0000                    add      byte ptr [eax], al             
  0x0028CCA5  f4                      hlt                                     
  0x0028CCA6  64009b00000000          add      byte ptr fs:[ebx], bl          
  0x0028CCAD  5c                      pop      esp                            
  0x0028CCAE  4d                      dec      ebp                            
  0x0028CCAF  001e                    add      byte ptr [esi], bl             
  0x0028CCB1  050d000c00              add      eax, 0xc000d                   
  0x0028CCB6  0000                    add      byte ptr [eax], al             
  0x0028CCB8  00f4                    add      ah, dh                         
  0x0028CCBA  56                      push     esi                            
  0x0028CCBB  0016                    add      byte ptr [esi], dl             
  0x0028CCBD  0000                    add      byte ptr [eax], al             
  0x0028CCBF  0000                    add      byte ptr [eax], al             
  0x0028CCC1  f4                      hlt                                     
  0x0028CCC2  57                      push     edi                            
  0x0028CCC3  0001                    add      byte ptr [ecx], al             
  0x0028CCC5  0000                    add      byte ptr [eax], al             
  0x0028CCC7  0000                    add      byte ptr [eax], al             
  0x0028CCC9  f4                      hlt                                     
  0x0028CCCA  7000                    jo       0x28cccc                       
                                        ; XREF: 0x0028CCCA (cond_jump)
  0x0028CCCC  90                      nop                                     
  0x0028CCCD  0300                    add      eax, dword ptr [eax]           
  0x0028CCCF  0000                    add      byte ptr [eax], al             
  0x0028CCD1  0039                    add      byte ptr [ecx], bh             
  0x0028CCD3  0000                    add      byte ptr [eax], al             
  0x0028CCD5  f4                      hlt                                     
  0x0028CCD6  60                      pushal                                  
  0x0028CCD7  00fa                    add      dl, bh                         
  0x0028CCD9  0000                    add      byte ptr [eax], al             
  0x0028CCDB  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028CCE1  0100                    add      dword ptr [eax], eax           
  0x0028CCE3  0003                    add      byte ptr [ebx], al             
  0x0028CCE5  0020                    add      byte ptr [eax], ah             
  0x0028CCE7  0000                    add      byte ptr [eax], al             
  0x0028CCE9  2405                    and      al, 5                          
  0x0028CCEB  000c00                  add      byte ptr [eax + eax], cl       
  0x0028CCEE  0000                    add      byte ptr [eax], al             
  0x0028CCF0  0c00                    or       al, 0                          
  0x0028CCF2  0000                    add      byte ptr [eax], al             
  0x0028CCF4  0c00                    or       al, 0                          
  0x0028CCF6  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x001F74B5 (data_imm)
  0x0028CCF8  40                      inc      eax                            
  0x0028CCF9  1bd0                    sbb      edx, eax                       
  0x0028CCFB  00d3                    add      bl, dl                         
  0x0028CCFD  06                      push     es                             
  0x0028CCFE  0000                    add      byte ptr [eax], al             
  0x0028CD00  7201                    jb       0x28cd03                       
  0x0028CD02  0400                    add      al, 0                          
  0x0028CD04  c2c60f                  ret      0xfc6                          
  0x0028CD07  0000                    add      byte ptr [eax], al             
  0x0028CD09  7044                    jo       0x28cd4f                       
  0x0028CD0B  00fb                    add      bl, bh                         
  0x0028CD0D  0000                    add      byte ptr [eax], al             
  0x0028CD0F  000b                    add      byte ptr [ebx], cl             
  0x0028CD11  0020                    add      byte ptr [eax], ah             
  0x0028CD13  0003                    add      byte ptr [ebx], al             
  0x0028CD15  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028CD16  050080100d              add      eax, 0xd108000                 
  0x0028CD1B  00c0                    add      al, al                         
  0x0028CD1D  06                      push     es                             
  0x0028CD1E  0000                    add      byte ptr [eax], al             
  0x0028CD20  80100d                  adc      byte ptr [eax], 0xd            
  0x0028CD23  006c0600                add      byte ptr [esi + eax], ch       
  0x0028CD27  0000                    add      byte ptr [eax], al             
  0x0028CD2A  57                      push     edi                            
  0x0028CD2B  00fb                    add      bl, bh                         
  0x0028CD2D  0000                    add      byte ptr [eax], al             
  0x0028CD2F  000b                    add      byte ptr [ebx], cl             
  0x0028CD31  f4                      hlt                                     
  0x0028CD32  60                      pushal                                  
  0x0028CD33  001f                    add      byte ptr [edi], bl             
  0x0028CD35  0000                    add      byte ptr [eax], al             
  0x0028CD37  0012                    add      byte ptr [edx], dl             
  0x0028CD39  2405                    and      al, 5                          
  0x0028CD3B  0000                    add      byte ptr [eax], al             
  0x0028CD3D  002400                  add      byte ptr [eax + eax], ah       
  0x0028CD40  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028CD43  004f0b                  add      byte ptr [edi + 0xb], cl       
  0x0028CD46  0000                    add      byte ptr [eax], al             
  0x0028CD48  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028CD4B  00500b                  add      byte ptr [eax + 0xb], dl       
  0x0028CD4E  0000                    add      byte ptr [eax], al             
  0x0028CD50  00f4                    add      ah, dh                         
  0x0028CD52  44                      inc      esp                            
  0x0028CD53  0000                    add      byte ptr [eax], al             
  0x0028CD55  72f8                    jb       0x28cd4f                       
  0x0028CD57  0000                    add      byte ptr [eax], al             
  0x0028CD59  58                      pop      eax                            
  0x0028CD5A  44                      inc      esp                            
  0x0028CD5B  0000                    add      byte ptr [eax], al             
  0x0028CD5D  f4                      hlt                                     
  0x0028CD5E  44                      inc      esp                            
  0x0028CD5F  0000                    add      byte ptr [eax], al             
  0x0028CD61  1f                      pop      ds                             
  0x0028CD62  4e                      dec      esi                            
  0x0028CD63  0000                    add      byte ptr [eax], al             
  0x0028CD65  58                      pop      eax                            
  0x0028CD66  44                      inc      esp                            
  0x0028CD67  0000                    add      byte ptr [eax], al             
  0x0028CD69  f4                      hlt                                     
  0x0028CD6A  44                      inc      esp                            
  0x0028CD6B  0000                    add      byte ptr [eax], al             
  0x0028CD6D  0100                    add      dword ptr [eax], eax           
  0x0028CD6F  0000                    add      byte ptr [eax], al             
  0x0028CD71  58                      pop      eax                            
  0x0028CD72  44                      inc      esp                            
  0x0028CD73  0000                    add      byte ptr [eax], al             
  0x0028CD75  f4                      hlt                                     
  0x0028CD76  44                      inc      esp                            
  0x0028CD77  0000                    add      byte ptr [eax], al             
  0x0028CD79  005000                  add      byte ptr [eax], dl             
  0x0028CD7C  005844                  add      byte ptr [eax + 0x44], bl      
  0x0028CD7F  0000                    add      byte ptr [eax], al             
  0x0028CD82  56                      push     esi                            
  0x0028CD83  004f0b                  add      byte ptr [edi + 0xb], cl       
  0x0028CD86  0000                    add      byte ptr [eax], al             
  0x0028CD88  03f0                    add      esi, eax                       
  0x0028CD8A  44                      inc      esp                            
  0x0028CD8B  00500b                  add      byte ptr [eax + 0xb], dl       
  0x0028CD8E  0000                    add      byte ptr [eax], al             
  0x0028CD90  02a40500005844          add      ah, byte ptr [ebp + eax + 0x44580000] 
  0x0028CD97  0000                    add      byte ptr [eax], al             
  0x0028CD99  f4                      hlt                                     
  0x0028CD9A  57                      push     edi                            
  0x0028CD9B  0010                    add      byte ptr [eax], dl             
  0x0028CD9D  0000                    add      byte ptr [eax], al             
  0x0028CD9F  0080100d00a6            add      byte ptr [eax - 0x59fff2f0], al 
  0x0028CDA5  0100                    add      dword ptr [eax], eax           
  0x0028CDA7  0000                    add      byte ptr [eax], al             
  0x0028CDA9  f4                      hlt                                     
  0x0028CDAA  44                      inc      esp                            
  0x0028CDAB  0000                    add      byte ptr [eax], al             
  0x0028CDAD  0000                    add      byte ptr [eax], al             
  0x0028CDAF  004500                  add      byte ptr [ebp], al             
  0x0028CDB2  2000                    and      byte ptr [eax], al             
  0x0028CDB4  00740500                add      byte ptr [ebp + eax], dh       
  0x0028CDB8  005820                  add      byte ptr [eax + 0x20], bl      
  0x0028CDBB  0000                    add      byte ptr [eax], al             
  0x0028CDBD  d85600                  fcom     dword ptr [esi]                
  0x0028CDC0  00f0                    add      al, dh                         
  0x0028CDC2  57                      push     edi                            
  0x0028CDC3  00fb                    add      bl, bh                         
  0x0028CDC5  0000                    add      byte ptr [eax], al             
  0x0028CDC7  000b                    add      byte ptr [ebx], cl             
  0x0028CDC9  f4                      hlt                                     
  0x0028CDCA  44                      inc      esp                            
  0x0028CDCB  000400                  add      byte ptr [eax + eax], al       
  0x0028CDCE  0000                    add      byte ptr [eax], al             
  0x0028CDD0  40                      inc      eax                            
  0x0028CDD1  2a20                    sub      ah, byte ptr [eax]             
  0x0028CDD3  0000                    add      byte ptr [eax], al             
  0x0028CDD6  57                      push     edi                            
  0x0028CDD7  004f0b                  add      byte ptr [edi + 0xb], cl       
  0x0028CDDA  0000                    add      byte ptr [eax], al             
  0x0028CDDC  0bf4                    or       esi, esp                       
  0x0028CDDE  44                      inc      esp                            
  0x0028CDDF  0001                    add      byte ptr [ecx], al             
  0x0028CDE1  0000                    add      byte ptr [eax], al             
  0x0028CDE3  004022                  add      byte ptr [eax + 0x22], al      
  0x0028CDE6  2000                    and      byte ptr [eax], al             
  0x0028CDE8  0000                    add      byte ptr [eax], al             
  0x0028CDEA  2400                    and      al, 0                          
  0x0028CDEC  0000                    add      byte ptr [eax], al             
  0x0028CDEE  250000f460              and      eax, 0x60f40000                
  0x0028CDF3  001f                    add      byte ptr [edi], bl             
  0x0028CDF5  0000                    add      byte ptr [eax], al             
  0x0028CDF7  0080cc0c0007            add      byte ptr [eax + 0x7000ccc], al 
  0x0028CDFD  0000                    add      byte ptr [eax], al             
  0x0028CDFF  0040cc                  add      byte ptr [eax - 0x34], al      
  0x0028CE02  0a00                    or       al, byte ptr [eax]             
  0x0028CE04  0098210000f4            add      byte ptr [eax - 0xbffffdf], bl 
  0x0028CE0A  44                      inc      esp                            
  0x0028CE0B  0001                    add      byte ptr [ecx], al             
  0x0028CE0D  0000                    add      byte ptr [eax], al             
  0x0028CE0F  0000                    add      byte ptr [eax], al             
  0x0028CE11  e845000070              call     0x7028ce5b                     
  0x0028CE16  44                      inc      esp                            
  0x0028CE17  004f0b                  add      byte ptr [edi + 0xb], cl       
  0x0028CE1A  0000                    add      byte ptr [eax], al             
  0x0028CE1C  007045                  add      byte ptr [eax + 0x45], dh      
  0x0028CE1F  00500b                  add      byte ptr [eax + 0xb], dl       
  0x0028CE22  0000                    add      byte ptr [eax], al             
  0x0028CE24  0084210000f056          add      byte ptr [ecx + 0x56f00000], al 
  0x0028CE2B  00fb                    add      bl, bh                         
  0x0028CE2D  0000                    add      byte ptr [eax], al             
  0x0028CE2F  0080100d0036            add      byte ptr [eax + 0x36000d10], al 
  0x0028CE35  06                      push     es                             
  0x0028CE36  0000                    add      byte ptr [eax], al             
  0x0028CE38  0c00                    or       al, 0                          
  0x0028CE3A  0000                    add      byte ptr [eax], al             
  0x0028CE3C  61                      popal                                   
  0x0028CE3D  f4                      hlt                                     
  0x0028CE3E  46                      inc      esi                            
  0x0028CE3F  0010                    add      byte ptr [eax], dl             
  0x0028CE41  0000                    add      byte ptr [eax], al             
  0x0028CE43  0000                    add      byte ptr [eax], al             
  0x0028CE45  07                      pop      es                             
  0x0028CE46  2300                    and      eax, dword ptr [eax]           
  0x0028CE48  10d9                    adc      cl, bl                         
  0x0028CE4A  06                      push     es                             
  0x0028CE4B  000a                    add      byte ptr [edx], cl             
  0x0028CE4D  0000                    add      byte ptr [eax], al             
  0x0028CE4F  007cd950                add      byte ptr [ecx + ebx*8 + 0x50], bh 
  0x0028CE53  0007                    add      byte ptr [edi], al             
  0x0028CE55  7405                    je       0x28ce5c                       
  0x0028CE57  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028CE5A  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028CE55 (cond_jump)
  0x0028CE5C  46                      inc      esi                            
  0x0028CE5D  1e                      push     ds                             
  0x0028CE5E  0c00                    or       al, 0                          
  0x0028CE60  90                      nop                                     
  0x0028CE61  1e                      push     ds                             
  0x0028CE62  0c00                    or       al, 0                          
  0x0028CE64  49                      dec      ecx                            
  0x0028CE65  e421                    in       al, 0x21                       
  0x0028CE67  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028CE6A  54                      push     esp                            
  0x0028CE6B  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028CE6E  0c00                    or       al, 0                          
  0x0028CE70  4e                      dec      esi                            
  0x0028CE71  1e                      push     ds                             
  0x0028CE72  0c00                    or       al, 0                          
  0x0028CE74  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028CE7A  0000                    add      byte ptr [eax], al             
  0x0028CE7C  61                      popal                                   
  0x0028CE7D  f4                      hlt                                     
                                        ; XREF: 0x0028CED0 (cond_jump)
  0x0028CE7E  46                      inc      esi                            
  0x0028CE7F  0010                    add      byte ptr [eax], dl             
  0x0028CE81  0000                    add      byte ptr [eax], al             
  0x0028CE83  0000                    add      byte ptr [eax], al             
  0x0028CE85  07                      pop      es                             
  0x0028CE86  2300                    and      eax, dword ptr [eax]           
  0x0028CE88  7cd9                    jl       0x28ce63                       
  0x0028CE8A  50                      push     eax                            
  0x0028CE8B  0007                    add      byte ptr [edi], al             
  0x0028CE8D  7405                    je       0x28ce94                       
  0x0028CE8F  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028CE92  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028CE8D (cond_jump)
  0x0028CE94  46                      inc      esi                            
  0x0028CE95  1e                      push     ds                             
  0x0028CE96  0c00                    or       al, 0                          
  0x0028CE98  90                      nop                                     
  0x0028CE99  1e                      push     ds                             
  0x0028CE9A  0c00                    or       al, 0                          
  0x0028CE9C  49                      dec      ecx                            
  0x0028CE9D  e421                    in       al, 0x21                       
  0x0028CE9F  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028CEA2  54                      push     esp                            
  0x0028CEA3  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028CEA6  0c00                    or       al, 0                          
  0x0028CEA8  4e                      dec      esi                            
  0x0028CEA9  1e                      push     ds                             
  0x0028CEAA  0c00                    or       al, 0                          
  0x0028CEAC  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028CEB2  0000                    add      byte ptr [eax], al             
  0x0028CEB4  00f4                    add      ah, dh                         
  0x0028CEB6  46                      inc      esi                            
  0x0028CEB7  0010                    add      byte ptr [eax], dl             
  0x0028CEB9  0000                    add      byte ptr [eax], al             
  0x0028CEBB  0000                    add      byte ptr [eax], al             
  0x0028CEBD  07                      pop      es                             
  0x0028CEBE  2300                    and      eax, dword ptr [eax]           
  0x0028CEC0  10d9                    adc      cl, bl                         
  0x0028CEC2  06                      push     es                             
  0x0028CEC3  000d00000000            add      byte ptr [0], cl               
  0x0028CEC9  d95600                  fst      dword ptr [esi]                
  0x0028CECC  6e                      outsb    dx, byte ptr [esi]             
  0x0028CECD  1e                      push     ds                             
  0x0028CECE  0c00                    or       al, 0                          
  0x0028CED0  7cac                    jl       0x28ce7e                       
  0x0028CED2  2000                    and      byte ptr [eax], al             
  0x0028CED4  07                      pop      es                             
  0x0028CED5  7405                    je       0x28cedc                       
  0x0028CED7  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028CEDA  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028CED5 (cond_jump)
  0x0028CEDC  46                      inc      esi                            
  0x0028CEDD  1e                      push     ds                             
  0x0028CEDE  0c00                    or       al, 0                          
  0x0028CEE0  90                      nop                                     
  0x0028CEE1  1e                      push     ds                             
  0x0028CEE2  0c00                    or       al, 0                          
  0x0028CEE4  49                      dec      ecx                            
  0x0028CEE5  e421                    in       al, 0x21                       
  0x0028CEE7  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028CEEA  54                      push     esp                            
  0x0028CEEB  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028CEEE  0c00                    or       al, 0                          
  0x0028CEF0  4e                      dec      esi                            
  0x0028CEF1  1e                      push     ds                             
  0x0028CEF2  0c00                    or       al, 0                          
  0x0028CEF4  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028CEFA  0000                    add      byte ptr [eax], al             
  0x0028CEFC  00f4                    add      ah, dh                         
  0x0028CEFE  46                      inc      esi                            
  0x0028CEFF  0010                    add      byte ptr [eax], dl             
  0x0028CF01  0000                    add      byte ptr [eax], al             
  0x0028CF03  0000                    add      byte ptr [eax], al             
  0x0028CF05  07                      pop      es                             
                                        ; XREF: 0x0028CF58 (cond_jump)
  0x0028CF06  2300                    and      eax, dword ptr [eax]           
  0x0028CF08  10d9                    adc      cl, bl                         
  0x0028CF0A  06                      push     es                             
  0x0028CF0B  000d00000000            add      byte ptr [0], cl               
  0x0028CF11  d95e00                  fstp     dword ptr [esi]                
  0x0028CF14  6e                      outsb    dx, byte ptr [esi]             
  0x0028CF15  1e                      push     ds                             
  0x0028CF16  0c00                    or       al, 0                          
  0x0028CF18  7cac                    jl       0x28cec6                       
  0x0028CF1A  2000                    and      byte ptr [eax], al             
  0x0028CF1C  07                      pop      es                             
  0x0028CF1D  7405                    je       0x28cf24                       
  0x0028CF1F  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028CF22  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028CF1D (cond_jump)
  0x0028CF24  46                      inc      esi                            
  0x0028CF25  1e                      push     ds                             
  0x0028CF26  0c00                    or       al, 0                          
  0x0028CF28  90                      nop                                     
  0x0028CF29  1e                      push     ds                             
  0x0028CF2A  0c00                    or       al, 0                          
  0x0028CF2C  49                      dec      ecx                            
  0x0028CF2D  e421                    in       al, 0x21                       
  0x0028CF2F  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028CF32  54                      push     esp                            
  0x0028CF33  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028CF36  0c00                    or       al, 0                          
  0x0028CF38  4e                      dec      esi                            
  0x0028CF39  1e                      push     ds                             
  0x0028CF3A  0c00                    or       al, 0                          
  0x0028CF3C  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028CF42  0000                    add      byte ptr [eax], al             
  0x0028CF44  00f4                    add      ah, dh                         
                                        ; XREF: 0x0028CF98 (cond_jump)
  0x0028CF46  46                      inc      esi                            
  0x0028CF47  0010                    add      byte ptr [eax], dl             
  0x0028CF49  0000                    add      byte ptr [eax], al             
  0x0028CF4B  0000                    add      byte ptr [eax], al             
  0x0028CF4D  07                      pop      es                             
  0x0028CF4E  2300                    and      eax, dword ptr [eax]           
  0x0028CF50  00d9                    add      cl, bl                         
  0x0028CF52  56                      push     esi                            
  0x0028CF53  006e1e                  add      byte ptr [esi + 0x1e], ch      
  0x0028CF56  0c00                    or       al, 0                          
  0x0028CF58  7cac                    jl       0x28cf06                       
  0x0028CF5A  2000                    and      byte ptr [eax], al             
  0x0028CF5C  07                      pop      es                             
  0x0028CF5D  7405                    je       0x28cf64                       
  0x0028CF5F  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028CF62  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028CF5D (cond_jump)
  0x0028CF64  46                      inc      esi                            
  0x0028CF65  1e                      push     ds                             
  0x0028CF66  0c00                    or       al, 0                          
  0x0028CF68  90                      nop                                     
  0x0028CF69  1e                      push     ds                             
  0x0028CF6A  0c00                    or       al, 0                          
  0x0028CF6C  49                      dec      ecx                            
  0x0028CF6D  e421                    in       al, 0x21                       
  0x0028CF6F  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028CF72  54                      push     esp                            
  0x0028CF73  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028CF76  0c00                    or       al, 0                          
  0x0028CF78  4e                      dec      esi                            
  0x0028CF79  1e                      push     ds                             
  0x0028CF7A  0c00                    or       al, 0                          
  0x0028CF7C  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028CF82  0000                    add      byte ptr [eax], al             
  0x0028CF84  00f4                    add      ah, dh                         
  0x0028CF86  46                      inc      esi                            
  0x0028CF87  0010                    add      byte ptr [eax], dl             
  0x0028CF89  0000                    add      byte ptr [eax], al             
  0x0028CF8B  0000                    add      byte ptr [eax], al             
  0x0028CF8D  07                      pop      es                             
  0x0028CF8E  2300                    and      eax, dword ptr [eax]           
  0x0028CF90  00d9                    add      cl, bl                         
  0x0028CF92  5e                      pop      esi                            
  0x0028CF93  006e1e                  add      byte ptr [esi + 0x1e], ch      
  0x0028CF96  0c00                    or       al, 0                          
  0x0028CF98  7cac                    jl       0x28cf46                       
  0x0028CF9A  2000                    and      byte ptr [eax], al             
  0x0028CF9C  07                      pop      es                             
  0x0028CF9D  7405                    je       0x28cfa4                       
  0x0028CF9F  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028CFA2  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028CF9D (cond_jump)
  0x0028CFA4  46                      inc      esi                            
  0x0028CFA5  1e                      push     ds                             
  0x0028CFA6  0c00                    or       al, 0                          
  0x0028CFA8  90                      nop                                     
  0x0028CFA9  1e                      push     ds                             
  0x0028CFAA  0c00                    or       al, 0                          
  0x0028CFAC  49                      dec      ecx                            
  0x0028CFAD  e421                    in       al, 0x21                       
  0x0028CFAF  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028CFB2  54                      push     esp                            
  0x0028CFB3  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028CFB6  0c00                    or       al, 0                          
  0x0028CFB8  4e                      dec      esi                            
  0x0028CFB9  1e                      push     ds                             
  0x0028CFBA  0c00                    or       al, 0                          
  0x0028CFBC  008521000c00            add      byte ptr [ebp + 0xc0021], al   
  0x0028CFC2  0000                    add      byte ptr [eax], al             
  0x0028CFC4  00f4                    add      ah, dh                         
  0x0028CFC6  61                      popal                                   
  0x0028CFC7  0012                    add      byte ptr [edx], dl             
  0x0028CFC9  0d000000f4              or       eax, 0xf4000000                
  0x0028CFCE  46                      inc      esi                            
  0x0028CFCF  00ff                    add      bh, bh                         
  0x0028CFD1  0000                    add      byte ptr [eax], al             
  0x0028CFD3  0010                    add      byte ptr [eax], dl             
  0x0028CFD5  d806                    fadd     dword ptr [esi]                
  0x0028CFD7  000e                    add      byte ptr [esi], cl             
  0x0028CFD9  0000                    add      byte ptr [eax], al             
  0x0028CFDB  00901c0c0056            add      byte ptr [eax + 0x56000c1c], dl 
  0x0028CFE1  0020                    add      byte ptr [eax], ah             
  0x0028CFE3  0000                    add      byte ptr [eax], al             
  0x0028CFE5  d85100                  fcom     dword ptr [ecx]                
  0x0028CFE8  00992100911d            add      byte ptr [ecx + 0x1d910021], bl 
  0x0028CFEE  0c00                    or       al, 0                          
  0x0028CFF0  00e9                    add      cl, ch                         
  0x0028CFF2  4c                      dec      esp                            
  0x0028CFF3  004b00                  add      byte ptr [ebx], cl             
  0x0028CFF6  2000                    and      byte ptr [eax], al             
  0x0028CFF8  90                      nop                                     
  0x0028CFF9  1c0c                    sbb      al, 0xc                        
  0x0028CFFB  005600                  add      byte ptr [esi], dl             
  0x0028CFFE  2000                    and      byte ptr [eax], al             
  0x0028D000  00992100911d            add      byte ptr [ecx + 0x1d910021], bl 
  0x0028D006  0c00                    or       al, 0                          
  0x0028D008  00e9                    add      cl, ch                         
  0x0028D00A  4c                      dec      esp                            
  0x0028D00B  004b00                  add      byte ptr [ebx], cl             
  0x0028D00E  2000                    and      byte ptr [eax], al             
  0x0028D010  91                      xchg     ecx, eax                       
  0x0028D011  1e                      push     ds                             
  0x0028D012  0c00                    or       al, 0                          
  0x0028D014  00ae2100111c            add      byte ptr [esi + 0x1c110021], ch 
  0x0028D01A  0c00                    or       al, 0                          
  0x0028D01C  0c00                    or       al, 0                          
  0x0028D01E  0000                    add      byte ptr [eax], al             
  0x0028D020  1bf4                    sbb      esi, esp                       
  0x0028D022  61                      popal                                   
  0x0028D023  0012                    add      byte ptr [edx], dl             
  0x0028D025  0e                      push     cs                             
  0x0028D026  0000                    add      byte ptr [eax], al             
  0x0028D028  00f4                    add      ah, dh                         
  0x0028D02A  46                      inc      esi                            
  0x0028D02B  00ff                    add      bh, bh                         
  0x0028D02D  0000                    add      byte ptr [eax], al             
  0x0028D02F  0000                    add      byte ptr [eax], al             
  0x0028D031  48                      dec      eax                            
  0x0028D032  2000                    and      byte ptr [eax], al             
  0x0028D034  10d8                    adc      al, bl                         
  0x0028D036  06                      push     es                             
  0x0028D037  000d0000005e            add      byte ptr [0x5e000000], cl      
  0x0028D03D  ae                      scasb    al, byte ptr es:[edi]          
  0x0028D03E  2100                    and      dword ptr [eax], eax           
  0x0028D040  00f8                    add      al, bh                         
  0x0028D042  44                      inc      esp                            
  0x0028D043  0000                    add      byte ptr [eax], al             
  0x0028D045  b92100d01e              mov      ecx, 0x1ed00021                
  0x0028D04A  0c00                    or       al, 0                          
  0x0028D04C  42                      inc      edx                            
  0x0028D04D  0020                    add      byte ptr [eax], ah             
  0x0028D04F  0000                    add      byte ptr [eax], al             
  0x0028D051  e94c004300              jmp      0x6bd0a2                       
  0x0028D056  2000                    and      byte ptr [eax], al             
  0x0028D058  56                      push     esi                            
  0x0028D05A  2100                    and      dword ptr [eax], eax           
  0x0028D05C  00992100d11e            add      byte ptr [ecx + 0x1ed10021], bl 
  0x0028D062  0c00                    or       al, 0                          
  0x0028D064  00e9                    add      cl, ch                         
  0x0028D066  4c                      dec      esp                            
  0x0028D067  004b00                  add      byte ptr [ebx], cl             
  0x0028D06A  2000                    and      byte ptr [eax], al             
  0x0028D06C  91                      xchg     ecx, eax                       
  0x0028D06D  1e                      push     ds                             
  0x0028D06E  0c00                    or       al, 0                          
  0x0028D070  00ae2100111c            add      byte ptr [esi + 0x1c110021], ch 
  0x0028D076  0c00                    or       al, 0                          
  0x0028D078  0c00                    or       al, 0                          
  0x0028D07A  0000                    add      byte ptr [eax], al             
  0x0028D07C  7904                    jns      0x28d082                       
  0x0028D07E  0000                    add      byte ptr [eax], al             
  0x0028D080  fa                      cli                                     
  0x0028D081  0300                    add      eax, dword ptr [eax]           
  0x0028D083  0017                    add      byte ptr [edi], dl             
  0x0028D085  0400                    add      al, 0                          
  0x0028D087  003404                  add      byte ptr [esp + eax], dh       
  0x0028D08A  0000                    add      byte ptr [eax], al             
  0x0028D08C  3b0400                  cmp      eax, dword ptr [eax + eax]     
  0x0028D08F  00540400                add      byte ptr [esp + eax], dl       
  0x0028D093  005b04                  add      byte ptr [ebx + 4], bl         
  0x0028D096  0000                    add      byte ptr [eax], al             
  0x0028D098  5e                      pop      esi                            
  0x0028D099  0400                    add      al, 0                          
  0x0028D09B  006104                  add      byte ptr [ecx + 4], ah         
  0x0028D09E  0000                    add      byte ptr [eax], al             
  0x0028D0A0  640400                  add      al, 0                          
  0x0028D0A3  006704                  add      byte ptr [edi + 4], ah         
  0x0028D0A6  0000                    add      byte ptr [eax], al             
  0x0028D0A8  6a04                    push     4                              
  0x0028D0AA  0000                    add      byte ptr [eax], al             
  0x0028D0AC  6d                      insd     dword ptr es:[edi], dx         
  0x0028D0AD  0400                    add      al, 0                          
  0x0028D0AF  007004                  add      byte ptr [eax + 4], dh         
  0x0028D0B2  0000                    add      byte ptr [eax], al             
  0x0028D0B4  7304                    jae      0x28d0ba                       
  0x0028D0B6  0000                    add      byte ptr [eax], al             
  0x0028D0B8  7604                    jbe      0x28d0be                       
                                        ; XREF: 0x0028D0B4 (cond_jump)
  0x0028D0BA  0000                    add      byte ptr [eax], al             
  0x0028D0BC  00f4                    add      ah, dh                         
                                        ; XREF: 0x0028D0B8 (cond_jump)
  0x0028D0BE  7400                    je       0x28d0c0                       
                                        ; XREF: 0x0028D0BE (cond_jump)
  0x0028D0C0  e103                    loope    0x28d0c5                       
  0x0028D0C2  0000                    add      byte ptr [eax], al             
  0x0028D0C4  10d8                    adc      al, bl                         
  0x0028D0C6  06                      push     es                             
  0x0028D0C7  008600000000            add      byte ptr [esi], al             
  0x0028D0CD  dd640000                frstor   dword ptr [eax + eax]          
  0x0028D0D1  e056                    loopne   0x28d129                       
  0x0028D0D3  0096ec070000            add      byte ptr [esi + 0x7ec], dl     
  0x0028D0D9  8521                    test     dword ptr [ecx], esp           
  0x0028D0DB  0080e60a0000            add      byte ptr [eax + 0xae6], al     
  0x0028D0E1  f4                      hlt                                     
  0x0028D0E2  44                      inc      esp                            
  0x0028D0E3  0003                    add      byte ptr [ebx], al             
  0x0028D0E5  0000                    add      byte ptr [eax], al             
  0x0028D0E7  00a0f4620005            add      byte ptr [eax + 0x50062f4], ah 
  0x0028D0ED  0000                    add      byte ptr [eax], al             
  0x0028D0EF  0040f0                  add      byte ptr [eax - 0x10], al      
  0x0028D0F2  7200                    jb       0x28d0f4                       
                                        ; XREF: 0x0028D0F2 (cond_jump)
  0x0028D0F4  0200                    add      al, byte ptr [eax]             
  0x0028D0F6  0000                    add      byte ptr [eax], al             
  0x0028D0F8  224f23                  and      cl, byte ptr [edi + 0x23]      
  0x0028D0FB  000b                    add      byte ptr [ebx], cl             
  0x0028D0FD  0139                    add      dword ptr [ecx], edi           
  0x0028D0FF  0000                    add      byte ptr [eax], al             
  0x0028D101  6a54                    push     0x54                           
  0x0028D103  000424                  add      byte ptr [esp], al             
  0x0028D106  0500007060              add      eax, 0x60700000                
  0x0028D10B  000d0000000e            add      byte ptr [0xe000000], cl       
  0x0028D111  0c05                    or       al, 5                          
  0x0028D113  0000                    add      byte ptr [eax], al             
  0x0028D115  f4                      hlt                                     
  0x0028D116  66000a                  add      byte ptr [edx], cl             
  0x0028D119  0d00000024              or       eax, 0x24000000                
  0x0028D11E  2300                    and      eax, dword ptr [eax]           
  0x0028D120  4d                      dec      ebp                            
  0x0028D121  0239                    add      bh, byte ptr [ecx]             
  0x0028D123  0009                    add      byte ptr [ecx], cl             
  0x0028D125  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D126  050000daf0              add      eax, 0xf0da0000                
  0x0028D12B  00d0                    add      al, dl                         
  0x0028D12F  00d2                    add      dl, dl                         
  0x0028D133  00d2                    add      dl, dl                         
  0x0028D135  f066000d00000024        lock add byte ptr [0x24000000], cl      
  0x0028D13D  1d0c000000              sbb      eax, 0xc                       
  0x0028D142  3900                    cmp      dword ptr [eax], eax           
  0x0028D144  006650                  add      byte ptr [esi + 0x50], ah      
  0x0028D147  0013                    add      byte ptr [ebx], dl             
  0x0028D149  7071                    jo       0x28d1bc                       
  0x0028D14B  0002                    add      byte ptr [edx], al             
  0x0028D14D  0000                    add      byte ptr [eax], al             
  0x0028D14F  00c3                    add      bl, al                         
  0x0028D151  0c05                    or       al, 5                          
  0x0028D153  0000                    add      byte ptr [eax], al             
  0x0028D155  f4                      hlt                                     
  0x0028D156  44                      inc      esp                            
  0x0028D157  0005000000a0            add      byte ptr [0xa0000000], al      
  0x0028D15D  f4                      hlt                                     
  0x0028D15E  6200                    bound    eax, qword ptr [eax]           
  0x0028D160  0800                    or       byte ptr [eax], al             
  0x0028D162  0000                    add      byte ptr [eax], al             
  0x0028D164  40                      inc      eax                            
  0x0028D166  7200                    jb       0x28d168                       
                                        ; XREF: 0x0028D166 (cond_jump)
  0x0028D168  0300                    add      eax, dword ptr [eax]           
  0x0028D16A  0000                    add      byte ptr [eax], al             
  0x0028D16C  224f23                  and      cl, byte ptr [edi + 0x23]      
  0x0028D16F  000b                    add      byte ptr [ebx], cl             
  0x0028D171  0139                    add      dword ptr [ecx], edi           
  0x0028D173  0000                    add      byte ptr [eax], al             
  0x0028D175  6a54                    push     0x54                           
  0x0028D177  000424                  add      byte ptr [esp], al             
  0x0028D17A  0500007060              add      eax, 0x60700000                
  0x0028D17F  000e                    add      byte ptr [esi], cl             
  0x0028D181  0000                    add      byte ptr [eax], al             
  0x0028D183  000e                    add      byte ptr [esi], cl             
  0x0028D185  0c05                    or       al, 5                          
  0x0028D187  0000                    add      byte ptr [eax], al             
  0x0028D189  f4                      hlt                                     
  0x0028D18A  66000d0d000000          add      byte ptr [0xd], cl             
  0x0028D191  2423                    and      al, 0x23                       
  0x0028D193  004d02                  add      byte ptr [ebp + 2], cl         
  0x0028D196  3900                    cmp      dword ptr [eax], eax           
  0x0028D198  09a4050000daf0          or       dword ptr [ebp + eax - 0xf260000], esp 
  0x0028D19F  00d0                    add      al, dl                         
  0x0028D1A3  00d2                    add      dl, dl                         
  0x0028D1A7  00d2                    add      dl, dl                         
  0x0028D1A9  f066000e                lock add byte ptr [esi], cl             
  0x0028D1AD  0000                    add      byte ptr [eax], al             
  0x0028D1AF  0020                    add      byte ptr [eax], ah             
  0x0028D1B1  1d0c000000              sbb      eax, 0xc                       
  0x0028D1B6  3900                    cmp      dword ptr [eax], eax           
  0x0028D1B8  006650                  add      byte ptr [esi + 0x50], ah      
  0x0028D1BB  0013                    add      byte ptr [ebx], dl             
  0x0028D1BD  7071                    jo       0x28d230                       
  0x0028D1BF  0003                    add      byte ptr [ebx], al             
  0x0028D1C1  0000                    add      byte ptr [eax], al             
  0x0028D1C3  00860c050000            add      byte ptr [esi + 0x50c], al     
  0x0028D1C9  f4                      hlt                                     
  0x0028D1CA  44                      inc      esp                            
  0x0028D1CB  0007                    add      byte ptr [edi], al             
  0x0028D1CD  0000                    add      byte ptr [eax], al             
  0x0028D1CF  00a000200040            add      byte ptr [eax + 0x40002000], ah 
  0x0028D1D5  0020                    add      byte ptr [eax], ah             
  0x0028D1D7  0038                    add      byte ptr [eax], bh             
  0x0028D1D9  1d0c00101c              sbb      eax, 0x1c10000c                
  0x0028D1DE  0c00                    or       al, 0                          
  0x0028D1E0  5f                      pop      edi                            
  0x0028D1E1  0c05                    or       al, 5                          
  0x0028D1E3  0000                    add      byte ptr [eax], al             
  0x0028D1E5  f4                      hlt                                     
  0x0028D1E6  44                      inc      esp                            
  0x0028D1E7  000b                    add      byte ptr [ebx], cl             
  0x0028D1E9  0000                    add      byte ptr [eax], al             
  0x0028D1EB  00a0f462000b            add      byte ptr [eax + 0xb0062f4], ah 
  0x0028D1F1  0000                    add      byte ptr [eax], al             
  0x0028D1F3  0040f0                  add      byte ptr [eax - 0x10], al      
  0x0028D1F6  7200                    jb       0x28d1f8                       
                                        ; XREF: 0x0028D1F6 (cond_jump)
  0x0028D1F8  0400                    add      al, 0                          
  0x0028D1FA  0000                    add      byte ptr [eax], al             
  0x0028D1FC  224f23                  and      cl, byte ptr [edi + 0x23]      
  0x0028D1FF  000b                    add      byte ptr [ebx], cl             
  0x0028D201  0139                    add      dword ptr [ecx], edi           
  0x0028D203  0000                    add      byte ptr [eax], al             
  0x0028D205  f4                      hlt                                     
  0x0028D206  660010                  add      byte ptr [eax], dl             
  0x0028D209  0d0000006a              or       eax, 0x6a000000                
  0x0028D20E  54                      push     esp                            
  0x0028D20F  000424                  add      byte ptr [esp], al             
  0x0028D212  0500007060              add      eax, 0x60700000                
  0x0028D217  000f                    add      byte ptr [edi], cl             
  0x0028D219  0000                    add      byte ptr [eax], al             
  0x0028D21B  0008                    add      byte ptr [eax], cl             
  0x0028D21D  0c05                    or       al, 5                          
  0x0028D21F  0000                    add      byte ptr [eax], al             
  0x0028D223  00d0                    add      al, dl                         
  0x0028D227  00d2                    add      dl, dl                         
  0x0028D229  f066000f                lock add byte ptr [edi], cl             
  0x0028D22D  0000                    add      byte ptr [eax], al             
  0x0028D22F  0020                    add      byte ptr [eax], ah             
  0x0028D231  1d0c000000              sbb      eax, 0xc                       
  0x0028D236  3900                    cmp      dword ptr [eax], eax           
  0x0028D238  006650                  add      byte ptr [esi + 0x50], ah      
  0x0028D23B  0013                    add      byte ptr [ebx], dl             
  0x0028D23D  7071                    jo       0x28d2b0                       
  0x0028D23F  000400                  add      byte ptr [eax + eax], al       
  0x0028D242  0000                    add      byte ptr [eax], al             
  0x0028D244  46                      inc      esi                            
  0x0028D245  0c05                    or       al, 5                          
  0x0028D247  0000                    add      byte ptr [eax], al             
  0x0028D249  f4                      hlt                                     
  0x0028D24A  44                      inc      esp                            
  0x0028D24B  000f                    add      byte ptr [edi], cl             
  0x0028D24D  0000                    add      byte ptr [eax], al             
  0x0028D24F  00a000200040            add      byte ptr [eax + 0x40002000], ah 
  0x0028D255  0020                    add      byte ptr [eax], ah             
  0x0028D257  0036                    add      byte ptr [esi], dh             
  0x0028D259  1d0c00101c              sbb      eax, 0x1c10000c                
  0x0028D25E  0c00                    or       al, 0                          
  0x0028D260  1f                      pop      ds                             
  0x0028D261  0c05                    or       al, 5                          
  0x0028D263  0000                    add      byte ptr [eax], al             
  0x0028D265  f4                      hlt                                     
  0x0028D266  56                      push     esi                            
  0x0028D267  0000                    add      byte ptr [eax], al             
  0x0028D269  000400                  add      byte ptr [eax + eax], al       
  0x0028D26C  1b0c050000f456          sbb      ecx, dword ptr [eax + 0x56f40000] 
  0x0028D273  0000                    add      byte ptr [eax], al             
  0x0028D275  0002                    add      byte ptr [edx], al             
  0x0028D277  0018                    add      byte ptr [eax], bl             
  0x0028D279  0c05                    or       al, 5                          
  0x0028D27B  0000                    add      byte ptr [eax], al             
  0x0028D27D  f4                      hlt                                     
  0x0028D27E  56                      push     esi                            
  0x0028D27F  0000                    add      byte ptr [eax], al             
  0x0028D281  0001                    add      byte ptr [ecx], al             
  0x0028D283  00150c050000            add      byte ptr [0x50c], dl           
  0x0028D289  f4                      hlt                                     
  0x0028D28A  56                      push     esi                            
  0x0028D28B  0000                    add      byte ptr [eax], al             
  0x0028D28D  800000                  add      byte ptr [eax], 0              
  0x0028D290  120c050000f456          adc      cl, byte ptr [eax + 0x56f40000] 
  0x0028D297  0000                    add      byte ptr [eax], al             
  0x0028D299  40                      inc      eax                            
  0x0028D29A  0000                    add      byte ptr [eax], al             
  0x0028D29D  0c05                    or       al, 5                          
  0x0028D29F  0000                    add      byte ptr [eax], al             
  0x0028D2A1  f4                      hlt                                     
  0x0028D2A2  56                      push     esi                            
  0x0028D2A3  0000                    add      byte ptr [eax], al             
  0x0028D2A5  2000                    and      byte ptr [eax], al             
  0x0028D2A7  000c0c                  add      byte ptr [esp + ecx], cl       
  0x0028D2AA  050000f456              add      eax, 0x56f40000                
  0x0028D2AF  0000                    add      byte ptr [eax], al             
  0x0028D2B1  1000                    adc      byte ptr [eax], al             
  0x0028D2B3  0009                    add      byte ptr [ecx], cl             
  0x0028D2B5  0c05                    or       al, 5                          
  0x0028D2B7  0000                    add      byte ptr [eax], al             
  0x0028D2B9  f4                      hlt                                     
  0x0028D2BA  56                      push     esi                            
  0x0028D2BB  0000                    add      byte ptr [eax], al             
  0x0028D2BD  0800                    or       byte ptr [eax], al             
  0x0028D2BF  0006                    add      byte ptr [esi], al             
  0x0028D2C1  0c05                    or       al, 5                          
  0x0028D2C3  0000                    add      byte ptr [eax], al             
  0x0028D2C5  f4                      hlt                                     
  0x0028D2C6  56                      push     esi                            
  0x0028D2C7  0000                    add      byte ptr [eax], al             
  0x0028D2C9  0400                    add      al, 0                          
  0x0028D2CB  0003                    add      byte ptr [ebx], al             
  0x0028D2CD  0c05                    or       al, 5                          
  0x0028D2CF  0000                    add      byte ptr [eax], al             
  0x0028D2D1  f4                      hlt                                     
  0x0028D2D2  56                      push     esi                            
  0x0028D2D3  0000                    add      byte ptr [eax], al             
  0x0028D2D5  0100                    add      dword ptr [eax], eax           
  0x0028D2D7  006000                  add      byte ptr [eax], ah             
  0x0028D2DA  2000                    and      byte ptr [eax], al             
  0x0028D2DC  005856                  add      byte ptr [eax + 0x56], bl      
  0x0028D2DF  000c00                  add      byte ptr [eax + eax], cl       
  0x0028D2E2  0000                    add      byte ptr [eax], al             
  0x0028D2E4  c6040000                mov      byte ptr [eax + eax], 0        
  0x0028D2E8  b204                    mov      dl, 4                          
  0x0028D2EA  0000                    add      byte ptr [eax], al             
  0x0028D2EC  a804                    test     al, 4                          
  0x0028D2EE  0000                    add      byte ptr [eax], al             
  0x0028D2F0  bb0400009e              mov      ebx, 0x9e000004                
  0x0028D2F5  0400                    add      al, 0                          
  0x0028D2F7  00bb040000bb            add      byte ptr [ebx - 0x44fffffc], bh 
  0x0028D2FD  0400                    add      al, 0                          
  0x0028D2FF  00bb040000bb            add      byte ptr [ebx - 0x44fffffc], bh 
  0x0028D305  0400                    add      al, 0                          
  0x0028D307  00bb040000bb            add      byte ptr [ebx - 0x44fffffc], bh 
  0x0028D30D  0400                    add      al, 0                          
  0x0028D30F  00bb040000bb            add      byte ptr [ebx - 0x44fffffc], bh 
  0x0028D315  0400                    add      al, 0                          
  0x0028D317  00bb040000bb            add      byte ptr [ebx - 0x44fffffc], bh 
  0x0028D31D  0400                    add      al, 0                          
  0x0028D31F  00bb04000000            add      byte ptr [ebx + 4], bh         
  0x0028D326  6200                    bound    eax, qword ptr [eax]           
  0x0028D328  55                      push     ebp                            
  0x0028D329  0b00                    or       eax, dword ptr [eax]           
  0x0028D32B  0022                    add      byte ptr [edx], ah             
  0x0028D32E  0500470b00              add      eax, 0xb4700                   
  0x0028D333  0000                    add      byte ptr [eax], al             
  0x0028D336  56                      push     esi                            
  0x0028D337  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028D33A  0000                    add      byte ptr [eax], al             
  0x0028D33C  00f0                    add      al, dh                         
  0x0028D33E  45                      inc      ebp                            
  0x0028D33F  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028D342  0000                    add      byte ptr [eax], al             
  0x0028D344  00f4                    add      ah, dh                         
  0x0028D346  46                      inc      esi                            
  0x0028D347  0010                    add      byte ptr [eax], dl             
  0x0028D349  0000                    add      byte ptr [eax], al             
  0x0028D34B  0000                    add      byte ptr [eax], al             
  0x0028D34D  f4                      hlt                                     
  0x0028D34E  7400                    je       0x28d350                       
                                        ; XREF: 0x0028D34E (cond_jump)
  0x0028D350  7b04                    jnp      0x28d356                       
  0x0028D352  0000                    add      byte ptr [eax], al             
  0x0028D354  10d8                    adc      al, bl                         
                                        ; XREF: 0x0028D350 (cond_jump)
  0x0028D356  06                      push     es                             
  0x0028D357  002f                    add      byte ptr [edi], ch             
  0x0028D359  0000                    add      byte ptr [eax], al             
  0x0028D35B  0000                    add      byte ptr [eax], al             
  0x0028D35D  dd640096                frstor   dword ptr [eax + eax - 0x6a]   
  0x0028D361  ec                      in       al, dx                         
  0x0028D362  07                      pop      es                             
  0x0028D363  00c7                    add      bh, al                         
  0x0028D365  740b                    je       0x28d372                       
  0x0028D367  00fa                    add      dl, bh                         
  0x0028D369  0c00                    or       al, 0                          
  0x0028D36B  0080e60a0000            add      byte ptr [eax + 0xae6], al     
                                        ; XREF: 0x0028D365 (cond_jump)
  0x0028D372  57                      push     edi                            
  0x0028D373  000400                  add      byte ptr [eax + eax], al       
  0x0028D376  0000                    add      byte ptr [eax], al             
  0x0028D378  8c4101                  mov      word ptr [ecx + 1], es         
  0x0028D37B  0000                    add      byte ptr [eax], al             
  0x0028D37D  7055                    jo       0x28d3d4                       
  0x0028D37F  000400                  add      byte ptr [eax + eax], al       
  0x0028D382  0000                    add      byte ptr [eax], al             
  0x0028D384  43                      inc      ebx                            
  0x0028D385  2405                    and      al, 5                          
  0x0028D387  0000                    add      byte ptr [eax], al             
  0x0028D389  0239                    add      bh, byte ptr [ecx]             
  0x0028D38B  0000                    add      byte ptr [eax], al             
  0x0028D38D  7071                    jo       0x28d400                       
  0x0028D38F  000400                  add      byte ptr [eax + eax], al       
  0x0028D392  0000                    add      byte ptr [eax], al             
  0x0028D394  140c                    adc      al, 0xc                        
  0x0028D396  050000f057              add      eax, 0x57f00000                
  0x0028D39B  0003                    add      byte ptr [ebx], al             
  0x0028D39D  0000                    add      byte ptr [eax], al             
  0x0028D39F  008c4101000070          add      byte ptr [ecx + eax*2 + 0x70000001], cl 
  0x0028D3A6  55                      push     ebp                            
  0x0028D3A7  0003                    add      byte ptr [ebx], al             
  0x0028D3A9  0000                    add      byte ptr [eax], al             
  0x0028D3AB  0019                    add      byte ptr [ecx], bl             
  0x0028D3AD  2405                    and      al, 5                          
  0x0028D3AF  0000                    add      byte ptr [eax], al             
  0x0028D3B1  0339                    add      edi, dword ptr [ecx]           
  0x0028D3B3  0000                    add      byte ptr [eax], al             
  0x0028D3B5  7071                    jo       0x28d428                       
  0x0028D3B7  0003                    add      byte ptr [ebx], al             
  0x0028D3B9  0000                    add      byte ptr [eax], al             
  0x0028D3BB  000a                    add      byte ptr [edx], cl             
  0x0028D3BD  0c05                    or       al, 5                          
  0x0028D3BF  0000                    add      byte ptr [eax], al             
  0x0028D3C2  57                      push     edi                            
  0x0028D3C3  0002                    add      byte ptr [edx], al             
  0x0028D3C5  0000                    add      byte ptr [eax], al             
  0x0028D3C7  008c4101000070          add      byte ptr [ecx + eax*2 + 0x70000001], cl 
  0x0028D3CE  55                      push     ebp                            
  0x0028D3CF  0002                    add      byte ptr [edx], al             
  0x0028D3D1  0000                    add      byte ptr [eax], al             
  0x0028D3D3  000f                    add      byte ptr [edi], cl             
  0x0028D3D5  2405                    and      al, 5                          
  0x0028D3D7  0000                    add      byte ptr [eax], al             
  0x0028D3D9  0339                    add      edi, dword ptr [ecx]           
  0x0028D3DB  0000                    add      byte ptr [eax], al             
  0x0028D3DD  7071                    jo       0x28d450                       
  0x0028D3DF  0002                    add      byte ptr [edx], al             
  0x0028D3E1  0000                    add      byte ptr [eax], al             
  0x0028D3E3  006900                  add      byte ptr [ecx], ch             
  0x0028D3E6  2000                    and      byte ptr [eax], al             
  0x0028D3E8  7ce0                    jl       0x28d3ca                       
  0x0028D3EA  50                      push     eax                            
  0x0028D3EB  0007                    add      byte ptr [edi], al             
  0x0028D3ED  7405                    je       0x28d3f4                       
  0x0028D3EF  0078e4                  add      byte ptr [eax - 0x1c], bh      
  0x0028D3F2  2100                    and      dword ptr [eax], eax           
                                        ; XREF: 0x0028D3ED (cond_jump)
  0x0028D3F4  46                      inc      esi                            
  0x0028D3F5  1e                      push     ds                             
  0x0028D3F6  0c00                    or       al, 0                          
  0x0028D3F8  90                      nop                                     
  0x0028D3F9  1e                      push     ds                             
  0x0028D3FA  0c00                    or       al, 0                          
  0x0028D3FC  49                      dec      ecx                            
  0x0028D3FD  e421                    in       al, 0x21                       
  0x0028D3FF  00585a                  add      byte ptr [eax + 0x5a], bl      
  0x0028D402  54                      push     esp                            
  0x0028D403  00681e                  add      byte ptr [eax + 0x1e], ch      
  0x0028D406  0c00                    or       al, 0                          
  0x0028D408  4e                      dec      esi                            
  0x0028D409  1e                      push     ds                             
  0x0028D40A  0c00                    or       al, 0                          
  0x0028D40C  00a521000058            add      byte ptr [ebp + 0x58000021], ah 
  0x0028D412  2000                    and      byte ptr [eax], al             
  0x0028D414  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028D417  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028D41A  0000                    add      byte ptr [eax], al             
  0x0028D41C  007045                  add      byte ptr [eax + 0x45], dh      
  0x0028D41F  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028D422  0000                    add      byte ptr [eax], al             
  0x0028D424  007062                  add      byte ptr [eax + 0x62], dh      
  0x0028D427  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028D42A  0000                    add      byte ptr [eax], al             
  0x0028D42C  22f4                    and      dh, ah                         
  0x0028D42E  0500ffff00              add      eax, 0xffff00                  
  0x0028D433  000c00                  add      byte ptr [eax + eax], cl       
  0x0028D436  0000                    add      byte ptr [eax], al             
  0x0028D438  20f4                    and      ah, dh                         
  0x0028D43A  0500ffffff              add      eax, 0xffffff00                
  0x0028D43F  00a0610400a0            add      byte ptr [eax - 0x5ffffb9f], ah 
  0x0028D445  620400                  bound    eax, qword ptr [eax + eax]     
  0x0028D448  a0640400a0              mov      al, byte ptr [0xa0000464]      
  0x0028D44D  650400                  add      al, 0                          
                                        ; XREF: 0x0028D3DD (cond_jump)
  0x0028D450  a0660400b8              mov      al, byte ptr [0xb8000466]      
  0x0028D455  f30000                  add      byte ptr [eax], al             
  0x0028D458  00f4                    add      ah, dh                         
  0x0028D45A  44                      inc      esp                            
  0x0028D45B  0000                    add      byte ptr [eax], al             
  0x0028D45D  0000                    add      byte ptr [eax], al             
  0x0028D45F  004d00                  add      byte ptr [ebp], cl             
  0x0028D462  2000                    and      byte ptr [eax], al             
  0x0028D464  0ca4                    or       al, 0xa4                       
  0x0028D466  050000f444              add      eax, 0x44f40000                
  0x0028D46B  0010                    add      byte ptr [eax], dl             
  0x0028D46D  0000                    add      byte ptr [eax], al             
  0x0028D46F  004d00                  add      byte ptr [ebp], cl             
  0x0028D472  2000                    and      byte ptr [eax], al             
  0x0028D474  4a                      dec      edx                            
  0x0028D475  100d000f0000            adc      byte ptr [0xf00], cl           
  0x0028D47B  0000                    add      byte ptr [eax], al             
  0x0028D47D  0030                    add      byte ptr [eax], dh             
  0x0028D47F  0000                    add      byte ptr [eax], al             
  0x0028D481  f4                      hlt                                     
  0x0028D482  56                      push     esi                            
  0x0028D483  0000                    add      byte ptr [eax], al             
  0x0028D485  0000                    add      byte ptr [eax], al             
  0x0028D487  0000                    add      byte ptr [eax], al             
  0x0028D489  f4                      hlt                                     
  0x0028D48A  57                      push     edi                            
  0x0028D48B  00ff                    add      bh, bh                         
  0x0028D48E  ff00                    inc      dword ptr [eax]                
  0x0028D490  0c00                    or       al, 0                          
  0x0028D492  0000                    add      byte ptr [eax], al             
  0x0028D494  1300                    adc      eax, dword ptr [eax]           
  0x0028D496  2000                    and      byte ptr [eax], al             
  0x0028D498  0000                    add      byte ptr [eax], al             
  0x0028D49A  3000                    xor      byte ptr [eax], al             
  0x0028D49C  00f4                    add      ah, dh                         
  0x0028D49E  56                      push     esi                            
  0x0028D49F  0000                    add      byte ptr [eax], al             
  0x0028D4A1  0000                    add      byte ptr [eax], al             
  0x0028D4A3  0000                    add      byte ptr [eax], al             
  0x0028D4A5  f4                      hlt                                     
  0x0028D4A6  57                      push     edi                            
  0x0028D4A7  0008                    add      byte ptr [eax], cl             
  0x0028D4A9  06                      push     es                             
  0x0028D4AA  0000                    add      byte ptr [eax], al             
  0x0028D4AC  0c00                    or       al, 0                          
  0x0028D4AE  0000                    add      byte ptr [eax], al             
  0x0028D4B0  00f0                    add      al, dh                         
  0x0028D4B2  56                      push     esi                            
  0x0028D4B3  00960b000003            add      byte ptr [esi + 0x300000b], dl 
  0x0028D4B9  0020                    add      byte ptr [eax], ah             
  0x0028D4BB  005874                  add      byte ptr [eax + 0x74], bl      
  0x0028D4BE  0500007060              add      eax, 0x60700000                
  0x0028D4C3  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028D4C6  0000                    add      byte ptr [eax], al             
  0x0028D4C8  007060                  add      byte ptr [eax + 0x60], dh      
  0x0028D4CB  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028D4CE  0000                    add      byte ptr [eax], al             
  0x0028D4D0  00f4                    add      ah, dh                         
  0x0028D4D2  45                      inc      ebp                            
  0x0028D4D3  00b007000000            add      byte ptr [eax + 7], dh         
  0x0028D4D9  7045                    jo       0x28d520                       
  0x0028D4DB  00720b                  add      byte ptr [edx + 0xb], dh       
  0x0028D4DE  0000                    add      byte ptr [eax], al             
  0x0028D4E0  00f0                    add      al, dh                         
  0x0028D4E2  56                      push     esi                            
  0x0028D4E3  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028D4E6  0000                    add      byte ptr [eax], al             
  0x0028D4E8  0300                    add      eax, dword ptr [eax]           
  0x0028D4EA  2400                    and      al, 0                          
  0x0028D4EC  09240500007044          or       dword ptr [eax + 0x44700000], esp 
  0x0028D4F3  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028D4F6  0000                    add      byte ptr [eax], al             
  0x0028D4F8  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028D4FB  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028D4FE  0000                    add      byte ptr [eax], al             
  0x0028D500  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028D503  009d0b000080            add      byte ptr [ebp - 0x7ffffff5], bl 
  0x0028D509  100d008c0000            adc      byte ptr [0x8c00], cl          
  0x0028D50F  0080100d0029            add      byte ptr [eax + 0x29000d10], al 
  0x0028D515  0100                    add      dword ptr [eax], eax           
  0x0028D517  0080100d009e            add      byte ptr [eax - 0x61fff2f0], al 
  0x0028D51D  0100                    add      dword ptr [eax], eax           
  0x0028D51F  0080100d0066            add      byte ptr [eax + 0x66000d10], al 
  0x0028D525  0300                    add      eax, dword ptr [eax]           
  0x0028D527  0000                    add      byte ptr [eax], al             
  0x0028D52A  56                      push     esi                            
  0x0028D52B  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028D52E  0000                    add      byte ptr [eax], al             
  0x0028D530  854501                  test     dword ptr [ebp + 1], eax       
  0x0028D533  0003                    add      byte ptr [ebx], al             
  0x0028D535  2405                    and      al, 5                          
  0x0028D537  0080100d0093            add      byte ptr [eax - 0x6cfff2f0], al 
  0x0028D53D  0300                    add      eax, dword ptr [eax]           
  0x0028D53F  0000                    add      byte ptr [eax], al             
  0x0028D542  56                      push     esi                            
  0x0028D543  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028D546  0000                    add      byte ptr [eax], al             
  0x0028D548  00f0                    add      al, dh                         
  0x0028D54A  44                      inc      esp                            
  0x0028D54B  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028D54E  0000                    add      byte ptr [eax], al             
  0x0028D550  44                      inc      esp                            
  0x0028D551  0020                    add      byte ptr [eax], ah             
  0x0028D553  0000                    add      byte ptr [eax], al             
  0x0028D555  7054                    jo       0x28d5ab                       
  0x0028D557  00580b                  add      byte ptr [eax + 0xb], bl       
  0x0028D55A  0000                    add      byte ptr [eax], al             
  0x0028D55C  80100d                  adc      byte ptr [eax], 0xd            
  0x0028D55F  00d0                    add      al, dl                         
  0x0028D561  0300                    add      eax, dword ptr [eax]           
  0x0028D563  0000                    add      byte ptr [eax], al             
  0x0028D566  56                      push     esi                            
  0x0028D567  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028D56A  0000                    add      byte ptr [eax], al             
  0x0028D56C  854501                  test     dword ptr [ebp + 1], eax       
  0x0028D56F  000b                    add      byte ptr [ebx], cl             
  0x0028D571  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D572  050000f044              add      eax, 0x44f00000                
  0x0028D577  00580b                  add      byte ptr [eax + 0xb], bl       
  0x0028D57A  0000                    add      byte ptr [eax], al             
  0x0028D57C  00f4                    add      ah, dh                         
  0x0028D57E  45                      inc      ebp                            
  0x0028D57F  0010                    add      byte ptr [eax], dl             
  0x0028D581  0000                    add      byte ptr [eax], al             
  0x0028D583  00a0f044009d            add      byte ptr [eax - 0x62ffbb10], ah 
  0x0028D589  0b00                    or       eax, dword ptr [eax]           
  0x0028D58B  002e                    add      byte ptr [esi], ch             
  0x0028D58D  1d0c004000              sbb      eax, 0x40000c                  
  0x0028D592  2000                    and      byte ptr [eax], al             
  0x0028D594  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028D597  009d0b000080            add      byte ptr [ebp - 0x7ffffff5], bl 
  0x0028D59D  100d00080000            adc      byte ptr [0x800], cl           
  0x0028D5A3  000c00                  add      byte ptr [eax + eax], cl       
  0x0028D5A6  0000                    add      byte ptr [eax], al             
  0x0028D5A8  00f4                    add      ah, dh                         
  0x0028D5AA  44                      inc      esp                            
                                        ; XREF: 0x0028D555 (cond_jump)
  0x0028D5AB  0000                    add      byte ptr [eax], al             
  0x0028D5AD  0100                    add      dword ptr [eax], eax           
  0x0028D5AF  0000                    add      byte ptr [eax], al             
  0x0028D5B1  7044                    jo       0x28d5f7                       
  0x0028D5B3  0010                    add      byte ptr [eax], dl             
  0x0028D5B5  0000                    add      byte ptr [eax], al             
  0x0028D5B7  000c00                  add      byte ptr [eax + eax], cl       
  0x0028D5BA  0000                    add      byte ptr [eax], al             
  0x0028D5BC  00f0                    add      al, dh                         
  0x0028D5BE  56                      push     esi                            
  0x0028D5BF  00960b000003            add      byte ptr [esi + 0x300000b], dl 
  0x0028D5C5  0020                    add      byte ptr [eax], ah             
  0x0028D5C7  0007                    add      byte ptr [edi], al             
  0x0028D5C9  f4                      hlt                                     
  0x0028D5CA  050013f044              add      eax, 0x44f01300                
  0x0028D5CF  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028D5D2  0000                    add      byte ptr [eax], al             
  0x0028D5D4  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028D5D7  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028D5DA  0000                    add      byte ptr [eax], al             
  0x0028D5DC  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028D5DF  009a0b000000            add      byte ptr [edx + 0xb], bl       
  0x0028D5E5  f4                      hlt                                     
  0x0028D5E6  60                      pushal                                  
  0x0028D5E7  0011                    add      byte ptr [ecx], dl             
  0x0028D5E9  0000                    add      byte ptr [eax], al             
  0x0028D5EB  0000                    add      byte ptr [eax], al             
  0x0028D5ED  f4                      hlt                                     
  0x0028D5EE  44                      inc      esp                            
  0x0028D5EF  000d00000000            add      byte ptr [0], cl               
  0x0028D5F5  58                      pop      eax                            
  0x0028D5F6  44                      inc      esp                            
                                        ; XREF: 0x0028D5B1 (cond_jump)
  0x0028D5F7  0000                    add      byte ptr [eax], al             
  0x0028D5FA  56                      push     esi                            
  0x0028D5FB  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028D5FE  0000                    add      byte ptr [eax], al             
  0x0028D600  00f0                    add      al, dh                         
  0x0028D602  44                      inc      esp                            
  0x0028D603  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028D606  0000                    add      byte ptr [eax], al             
  0x0028D608  44                      inc      esp                            
  0x0028D609  0020                    add      byte ptr [eax], ah             
  0x0028D60B  0000                    add      byte ptr [eax], al             
  0x0028D60D  58                      pop      eax                            
  0x0028D60E  54                      push     esp                            
  0x0028D60F  0000                    add      byte ptr [eax], al             
  0x0028D612  44                      inc      esp                            
  0x0028D613  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028D616  0000                    add      byte ptr [eax], al             
  0x0028D618  005844                  add      byte ptr [eax + 0x44], bl      
  0x0028D61B  0000                    add      byte ptr [eax], al             
  0x0028D61D  002400                  add      byte ptr [eax + eax], ah       
  0x0028D620  005844                  add      byte ptr [eax + 0x44], bl      
  0x0028D623  0000                    add      byte ptr [eax], al             
  0x0028D625  58                      pop      eax                            
  0x0028D626  44                      inc      esp                            
  0x0028D627  0000                    add      byte ptr [eax], al             
  0x0028D629  58                      pop      eax                            
  0x0028D62A  44                      inc      esp                            
  0x0028D62B  0000                    add      byte ptr [eax], al             
  0x0028D62D  58                      pop      eax                            
  0x0028D62E  44                      inc      esp                            
  0x0028D62F  0013                    add      byte ptr [ebx], dl             
  0x0028D631  f4                      hlt                                     
  0x0028D632  44                      inc      esp                            
  0x0028D633  0009                    add      byte ptr [ecx], cl             
  0x0028D635  0000                    add      byte ptr [eax], al             
  0x0028D637  0000                    add      byte ptr [eax], al             
  0x0028D639  7044                    jo       0x28d67f                       
  0x0028D63B  001e                    add      byte ptr [esi], bl             
  0x0028D63D  0000                    add      byte ptr [eax], al             
  0x0028D63F  0000                    add      byte ptr [eax], al             
  0x0028D642  44                      inc      esp                            
  0x0028D643  001e                    add      byte ptr [esi], bl             
  0x0028D645  0000                    add      byte ptr [eax], al             
  0x0028D647  004019                  add      byte ptr [eax + 0x19], al      
  0x0028D64A  0c00                    or       al, 0                          
  0x0028D64C  184000                  sbb      byte ptr [eax], al             
  0x0028D64F  0000                    add      byte ptr [eax], al             
  0x0028D651  58                      pop      eax                            
  0x0028D652  54                      push     esp                            
  0x0028D653  0000                    add      byte ptr [eax], al             
  0x0028D655  002400                  add      byte ptr [eax + eax], ah       
  0x0028D658  005844                  add      byte ptr [eax + 0x44], bl      
  0x0028D65B  001b                    add      byte ptr [ebx], bl             
  0x0028D65D  0020                    add      byte ptr [eax], ah             
  0x0028D65F  0013                    add      byte ptr [ebx], dl             
  0x0028D661  0020                    add      byte ptr [eax], ah             
  0x0028D663  00df                    add      bh, bl                         
  0x0028D665  1e                      push     ds                             
  0x0028D666  0c00                    or       al, 0                          
  0x0028D668  00a4210040190c          add      byte ptr [ecx + 0xc194000], ah 
  0x0028D66F  0020                    add      byte ptr [eax], ah             
  0x0028D671  800000                  add      byte ptr [eax], 0              
  0x0028D674  1b00                    sbb      eax, dword ptr [eax]           
  0x0028D676  2000                    and      byte ptr [eax], al             
  0x0028D678  df1e                    fistp    word ptr [esi]                 
  0x0028D67A  0c00                    or       al, 0                          
  0x0028D67C  00a4210040190c          add      byte ptr [ecx + 0xc194000], ah 
  0x0028D683  0018                    add      byte ptr [eax], bl             
  0x0028D685  800000                  add      byte ptr [eax], 0              
  0x0028D688  005854                  add      byte ptr [eax + 0x54], bl      
  0x0028D68B  0013                    add      byte ptr [ebx], dl             
  0x0028D68E  57                      push     edi                            
  0x0028D68F  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028D692  0000                    add      byte ptr [eax], al             
  0x0028D694  0bf4                    or       esi, esp                       
  0x0028D696  45                      inc      ebp                            
  0x0028D697  008000000007            add      byte ptr [eax + 0x7000000], al 
  0x0028D69D  2405                    and      al, 5                          
  0x0028D69F  001b                    add      byte ptr [ebx], bl             
  0x0028D6A1  0020                    add      byte ptr [eax], ah             
  0x0028D6A3  00a11c0c0068            add      byte ptr [ecx + 0x68000c1c], ah 
  0x0028D6A9  0020                    add      byte ptr [eax], ah             
  0x0028D6AB  0000                    add      byte ptr [eax], al             
  0x0028D6AD  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D6AE  2100                    and      dword ptr [eax], eax           
  0x0028D6B0  40                      inc      eax                            
  0x0028D6B1  190c00                  sbb      dword ptr [eax + eax], ecx     
  0x0028D6B4  208000001b00            and      byte ptr [eax + 0x1b0000], al  
  0x0028D6BA  2000                    and      byte ptr [eax], al             
  0x0028D6BC  a11c0c0068              mov      eax, dword ptr [0x68000c1c]    
  0x0028D6C1  0020                    add      byte ptr [eax], ah             
  0x0028D6C3  0000                    add      byte ptr [eax], al             
  0x0028D6C5  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D6C6  2100                    and      dword ptr [eax], eax           
  0x0028D6C8  40                      inc      eax                            
  0x0028D6C9  190c00                  sbb      dword ptr [eax + eax], ecx     
  0x0028D6CC  188000000058            sbb      byte ptr [eax + 0x58000000], al 
  0x0028D6D2  54                      push     esp                            
  0x0028D6D3  0013                    add      byte ptr [ebx], dl             
  0x0028D6D6  57                      push     edi                            
  0x0028D6D7  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028D6DA  0000                    add      byte ptr [eax], al             
  0x0028D6DC  0b00                    or       eax, dword ptr [eax]           
  0x0028D6DE  2000                    and      byte ptr [eax], al             
  0x0028D6E0  07                      pop      es                             
  0x0028D6E1  2405                    and      al, 5                          
  0x0028D6E3  001b                    add      byte ptr [ebx], bl             
  0x0028D6E5  0020                    add      byte ptr [eax], ah             
  0x0028D6E7  00a11c0c0068            add      byte ptr [ecx + 0x68000c1c], ah 
  0x0028D6ED  0020                    add      byte ptr [eax], ah             
  0x0028D6EF  0000                    add      byte ptr [eax], al             
  0x0028D6F1  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D6F2  2100                    and      dword ptr [eax], eax           
  0x0028D6F4  40                      inc      eax                            
  0x0028D6F5  190c00                  sbb      dword ptr [eax + eax], ecx     
  0x0028D6F8  20800000a11c            and      byte ptr [eax + 0x1ca10000], al 
  0x0028D6FE  0c00                    or       al, 0                          
  0x0028D700  6800200000              push     0x2000                         
  0x0028D705  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D706  2100                    and      dword ptr [eax], eax           
  0x0028D708  40                      inc      eax                            
  0x0028D709  190c00                  sbb      dword ptr [eax + eax], ecx     
  0x0028D70C  188000000058            sbb      byte ptr [eax + 0x58000000], al 
  0x0028D712  54                      push     esp                            
  0x0028D713  0013                    add      byte ptr [ebx], dl             
  0x0028D715  0020                    add      byte ptr [eax], ah             
  0x0028D717  0000                    add      byte ptr [eax], al             
  0x0028D719  58                      pop      eax                            
  0x0028D71A  54                      push     esp                            
  0x0028D71B  0000                    add      byte ptr [eax], al             
  0x0028D71D  f4                      hlt                                     
  0x0028D71E  60                      pushal                                  
  0x0028D71F  0011                    add      byte ptr [ecx], dl             
  0x0028D721  0000                    add      byte ptr [eax], al             
  0x0028D723  0000                    add      byte ptr [eax], al             
  0x0028D726  56                      push     esi                            
  0x0028D727  00960b000000            add      byte ptr [esi + 0xb], dl       
  0x0028D72D  f4                      hlt                                     
  0x0028D72E  57                      push     edi                            
  0x0028D72F  0008                    add      byte ptr [eax], cl             
  0x0028D731  06                      push     es                             
  0x0028D732  0000                    add      byte ptr [eax], al             
  0x0028D734  0c00                    or       al, 0                          
  0x0028D736  0000                    add      byte ptr [eax], al             
  0x0028D738  00f0                    add      al, dh                         
  0x0028D73A  6200                    bound    eax, qword ptr [eax]           
  0x0028D73C  45                      inc      ebp                            
  0x0028D73D  0b00                    or       eax, dword ptr [eax]           
  0x0028D73F  0022                    add      byte ptr [edx], ah             
  0x0028D742  0500470b00              add      eax, 0xb4700                   
  0x0028D747  0000                    add      byte ptr [eax], al             
  0x0028D749  f4                      hlt                                     
  0x0028D74A  57                      push     edi                            
  0x0028D74B  0010                    add      byte ptr [eax], dl             
  0x0028D74D  0000                    add      byte ptr [eax], al             
  0x0028D74F  0000                    add      byte ptr [eax], al             
  0x0028D751  00250000f444            add      byte ptr [0x44f40000], ah      
  0x0028D757  00770b                  add      byte ptr [edi + 0xb], dh       
  0x0028D75A  0000                    add      byte ptr [eax], al             
  0x0028D75C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028D75F  0000                    add      byte ptr [eax], al             
  0x0028D761  0000                    add      byte ptr [eax], al             
  0x0028D763  0000                    add      byte ptr [eax], al             
  0x0028D765  f4                      hlt                                     
  0x0028D766  44                      inc      esp                            
  0x0028D767  0000                    add      byte ptr [eax], al             
  0x0028D769  0000                    add      byte ptr [eax], al             
  0x0028D76B  0000                    add      byte ptr [eax], al             
  0x0028D76D  7044                    jo       0x28d7b3                       
  0x0028D76F  00540b00                add      byte ptr [ebx + ecx], dl       
  0x0028D773  0000                    add      byte ptr [eax], al             
  0x0028D775  f4                      hlt                                     
  0x0028D776  61                      popal                                   
  0x0028D777  0000                    add      byte ptr [eax], al             
  0x0028D779  0000                    add      byte ptr [eax], al             
  0x0028D77B  0000                    add      byte ptr [eax], al             
  0x0028D77D  1038                    adc      byte ptr [eax], bh             
  0x0028D77F  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D785  f4                      hlt                                     
  0x0028D786  61                      popal                                   
  0x0028D787  00540b00                add      byte ptr [ebx + ecx], dl       
  0x0028D78B  0000                    add      byte ptr [eax], al             
  0x0028D78D  1038                    adc      byte ptr [eax], bh             
  0x0028D78F  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D795  f4                      hlt                                     
  0x0028D796  61                      popal                                   
  0x0028D797  007b0b                  add      byte ptr [ebx + 0xb], bh       
  0x0028D79A  0000                    add      byte ptr [eax], al             
  0x0028D79C  0002                    add      byte ptr [edx], al             
  0x0028D79E  3800                    cmp      byte ptr [eax], al             
  0x0028D7A0  93                      xchg     ebx, eax                       
  0x0028D7A1  030d0000f461            add      ecx, dword ptr [0x61f40000]    
  0x0028D7A7  007c0b00                add      byte ptr [ebx + ecx], bh       
  0x0028D7AB  0000                    add      byte ptr [eax], al             
  0x0028D7AD  06                      push     es                             
  0x0028D7AE  3800                    cmp      byte ptr [eax], al             
  0x0028D7B0  93                      xchg     ebx, eax                       
  0x0028D7B1  030d00000428            add      ecx, dword ptr [0x28040000]    
  0x0028D7B7  0000                    add      byte ptr [eax], al             
  0x0028D7B9  7050                    jo       0x28d80b                       
  0x0028D7BB  001e                    add      byte ptr [esi], bl             
  0x0028D7BD  0000                    add      byte ptr [eax], al             
  0x0028D7BF  0000                    add      byte ptr [eax], al             
  0x0028D7C1  f4                      hlt                                     
  0x0028D7C2  61                      popal                                   
  0x0028D7C3  001e                    add      byte ptr [esi], bl             
  0x0028D7C5  0000                    add      byte ptr [eax], al             
  0x0028D7C7  0000                    add      byte ptr [eax], al             
  0x0028D7C9  0538009303              add      eax, 0x3930038                 
  0x0028D7CE  0d00000028              or       eax, 0x28000000                
  0x0028D7D3  0000                    add      byte ptr [eax], al             
  0x0028D7D5  7050                    jo       0x28d827                       
  0x0028D7D7  001e                    add      byte ptr [esi], bl             
  0x0028D7D9  0000                    add      byte ptr [eax], al             
  0x0028D7DB  0000                    add      byte ptr [eax], al             
  0x0028D7DD  f4                      hlt                                     
  0x0028D7DE  61                      popal                                   
  0x0028D7DF  001e                    add      byte ptr [esi], bl             
  0x0028D7E1  0000                    add      byte ptr [eax], al             
  0x0028D7E3  0000                    add      byte ptr [eax], al             
  0x0028D7E5  0338                    add      edi, dword ptr [eax]           
  0x0028D7E7  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D7ED  f4                      hlt                                     
  0x0028D7EE  61                      popal                                   
  0x0028D7EF  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028D7F2  0000                    add      byte ptr [eax], al             
  0x0028D7F4  0003                    add      byte ptr [ebx], al             
  0x0028D7F6  3800                    cmp      byte ptr [eax], al             
  0x0028D7F8  93                      xchg     ebx, eax                       
  0x0028D7F9  030d0000f056            add      ecx, dword ptr [0x56f00000]    
  0x0028D7FF  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028D802  0000                    add      byte ptr [eax], al             
  0x0028D804  854101                  test     dword ptr [ecx + 1], eax       
  0x0028D807  000a                    add      byte ptr [edx], cl             
  0x0028D809  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D80A  0500864101              add      eax, 0x1418600                 
  0x0028D80F  0008                    add      byte ptr [eax], cl             
  0x0028D811  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028D812  0500000028              add      eax, 0x28000000                
  0x0028D817  0000                    add      byte ptr [eax], al             
  0x0028D819  7050                    jo       0x28d86b                       
  0x0028D81B  001e                    add      byte ptr [esi], bl             
  0x0028D81D  0000                    add      byte ptr [eax], al             
  0x0028D81F  0000                    add      byte ptr [eax], al             
  0x0028D821  f4                      hlt                                     
  0x0028D822  61                      popal                                   
  0x0028D823  001e                    add      byte ptr [esi], bl             
  0x0028D825  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028D7D5 (cond_jump)
  0x0028D827  0000                    add      byte ptr [eax], al             
  0x0028D829  0238                    add      bh, byte ptr [eax]             
  0x0028D82B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D832  56                      push     esi                            
  0x0028D833  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028D836  0000                    add      byte ptr [eax], al             
  0x0028D838  86440100                xchg     byte ptr [ecx + eax], al       
  0x0028D83C  08a40500000028          or       byte ptr [ebp + eax + 0x28000000], ah 
  0x0028D843  0000                    add      byte ptr [eax], al             
  0x0028D845  7050                    jo       0x28d897                       
  0x0028D847  001e                    add      byte ptr [esi], bl             
  0x0028D849  0000                    add      byte ptr [eax], al             
  0x0028D84B  0000                    add      byte ptr [eax], al             
  0x0028D84D  f4                      hlt                                     
  0x0028D84E  61                      popal                                   
  0x0028D84F  001e                    add      byte ptr [esi], bl             
  0x0028D851  0000                    add      byte ptr [eax], al             
  0x0028D853  0000                    add      byte ptr [eax], al             
  0x0028D855  0238                    add      bh, byte ptr [eax]             
  0x0028D857  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D85E  56                      push     esi                            
  0x0028D85F  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028D862  0000                    add      byte ptr [eax], al             
  0x0028D864  854201                  test     dword ptr [edx + 1], eax       
  0x0028D867  000524050000            add      byte ptr [0x524], al           
  0x0028D86D  f4                      hlt                                     
  0x0028D86E  61                      popal                                   
  0x0028D86F  004e0b                  add      byte ptr [esi + 0xb], cl       
  0x0028D872  0000                    add      byte ptr [eax], al             
  0x0028D874  0002                    add      byte ptr [edx], al             
  0x0028D876  3800                    cmp      byte ptr [eax], al             
  0x0028D878  93                      xchg     ebx, eax                       
  0x0028D879  030d0000f461            add      ecx, dword ptr [0x61f40000]    
  0x0028D87F  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028D882  0000                    add      byte ptr [eax], al             
  0x0028D884  0001                    add      byte ptr [ecx], al             
  0x0028D886  3800                    cmp      byte ptr [eax], al             
  0x0028D888  93                      xchg     ebx, eax                       
  0x0028D889  030d0000f461            add      ecx, dword ptr [0x61f40000]    
  0x0028D88F  00490b                  add      byte ptr [ecx + 0xb], cl       
  0x0028D892  0000                    add      byte ptr [eax], al             
  0x0028D894  000538009303            add      byte ptr [0x3930038], al       
  0x0028D89A  0d0000f461              or       eax, 0x61f40000                
  0x0028D89F  004c0b00                add      byte ptr [ebx + ecx], cl       
  0x0028D8A3  0000                    add      byte ptr [eax], al             
  0x0028D8A5  0138                    add      dword ptr [eax], edi           
  0x0028D8A7  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D8AE  56                      push     esi                            
  0x0028D8AF  004c0b00                add      byte ptr [ebx + ecx], cl       
  0x0028D8B3  0003                    add      byte ptr [ebx], al             
  0x0028D8B5  0020                    add      byte ptr [eax], ah             
  0x0028D8B7  0005a4050000            add      byte ptr [0x5a4], al           
  0x0028D8BD  f4                      hlt                                     
  0x0028D8BE  61                      popal                                   
  0x0028D8BF  004d0b                  add      byte ptr [ebp + 0xb], cl       
  0x0028D8C2  0000                    add      byte ptr [eax], al             
  0x0028D8C4  0008                    add      byte ptr [eax], cl             
  0x0028D8C6  3800                    cmp      byte ptr [eax], al             
  0x0028D8C8  93                      xchg     ebx, eax                       
  0x0028D8C9  030d00000028            add      ecx, dword ptr [0x28000000]    
  0x0028D8CF  0000                    add      byte ptr [eax], al             
  0x0028D8D1  7050                    jo       0x28d923                       
  0x0028D8D3  001e                    add      byte ptr [esi], bl             
  0x0028D8D5  0000                    add      byte ptr [eax], al             
  0x0028D8D7  0000                    add      byte ptr [eax], al             
  0x0028D8D9  f4                      hlt                                     
  0x0028D8DA  61                      popal                                   
  0x0028D8DB  001e                    add      byte ptr [esi], bl             
  0x0028D8DD  0000                    add      byte ptr [eax], al             
  0x0028D8DF  0000                    add      byte ptr [eax], al             
  0x0028D8E1  0138                    add      dword ptr [eax], edi           
  0x0028D8E3  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D8E9  0028                    add      byte ptr [eax], ch             
  0x0028D8EB  0000                    add      byte ptr [eax], al             
  0x0028D8ED  7050                    jo       0x28d93f                       
  0x0028D8EF  001e                    add      byte ptr [esi], bl             
  0x0028D8F1  0000                    add      byte ptr [eax], al             
  0x0028D8F3  0000                    add      byte ptr [eax], al             
  0x0028D8F5  f4                      hlt                                     
  0x0028D8F6  61                      popal                                   
  0x0028D8F7  001e                    add      byte ptr [esi], bl             
  0x0028D8F9  0000                    add      byte ptr [eax], al             
  0x0028D8FB  0000                    add      byte ptr [eax], al             
  0x0028D8FD  0138                    add      dword ptr [eax], edi           
  0x0028D8FF  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D905  0028                    add      byte ptr [eax], ch             
  0x0028D907  0000                    add      byte ptr [eax], al             
  0x0028D909  7050                    jo       0x28d95b                       
  0x0028D90B  001e                    add      byte ptr [esi], bl             
  0x0028D90D  0000                    add      byte ptr [eax], al             
  0x0028D90F  0000                    add      byte ptr [eax], al             
  0x0028D911  f4                      hlt                                     
  0x0028D912  61                      popal                                   
  0x0028D913  001e                    add      byte ptr [esi], bl             
  0x0028D915  0000                    add      byte ptr [eax], al             
  0x0028D917  0000                    add      byte ptr [eax], al             
  0x0028D919  0138                    add      dword ptr [eax], edi           
  0x0028D91B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D921  0128                    add      dword ptr [eax], ebp           
                                        ; XREF: 0x0028D8D1 (cond_jump)
  0x0028D923  0000                    add      byte ptr [eax], al             
  0x0028D925  7050                    jo       0x28d977                       
  0x0028D927  001e                    add      byte ptr [esi], bl             
  0x0028D929  0000                    add      byte ptr [eax], al             
  0x0028D92B  0000                    add      byte ptr [eax], al             
  0x0028D92D  f4                      hlt                                     
  0x0028D92E  61                      popal                                   
  0x0028D92F  001e                    add      byte ptr [esi], bl             
  0x0028D931  0000                    add      byte ptr [eax], al             
  0x0028D933  0000                    add      byte ptr [eax], al             
  0x0028D935  0138                    add      dword ptr [eax], edi           
  0x0028D937  0093030d0013            add      byte ptr [ebx + 0x13000d03], dl 
  0x0028D93D  0020                    add      byte ptr [eax], ah             
                                        ; XREF: 0x0028D8ED (cond_jump)
  0x0028D93F  0000                    add      byte ptr [eax], al             
  0x0028D941  7056                    jo       0x28d999                       
  0x0028D943  001e                    add      byte ptr [esi], bl             
  0x0028D945  0000                    add      byte ptr [eax], al             
  0x0028D947  0000                    add      byte ptr [eax], al             
  0x0028D949  f4                      hlt                                     
  0x0028D94A  61                      popal                                   
  0x0028D94B  001e                    add      byte ptr [esi], bl             
  0x0028D94D  0000                    add      byte ptr [eax], al             
  0x0028D94F  0000                    add      byte ptr [eax], al             
  0x0028D951  0138                    add      dword ptr [eax], edi           
  0x0028D953  0093030d0013            add      byte ptr [ebx + 0x13000d03], dl 
  0x0028D959  0020                    add      byte ptr [eax], ah             
                                        ; XREF: 0x0028D909 (cond_jump)
  0x0028D95B  0000                    add      byte ptr [eax], al             
  0x0028D95D  7056                    jo       0x28d9b5                       
  0x0028D95F  001e                    add      byte ptr [esi], bl             
  0x0028D961  0000                    add      byte ptr [eax], al             
  0x0028D963  0000                    add      byte ptr [eax], al             
  0x0028D965  f4                      hlt                                     
  0x0028D966  61                      popal                                   
  0x0028D967  001e                    add      byte ptr [esi], bl             
  0x0028D969  0000                    add      byte ptr [eax], al             
  0x0028D96B  0000                    add      byte ptr [eax], al             
  0x0028D96D  0138                    add      dword ptr [eax], edi           
  0x0028D96F  0093030d0013            add      byte ptr [ebx + 0x13000d03], dl 
  0x0028D975  0020                    add      byte ptr [eax], ah             
                                        ; XREF: 0x0028D925 (cond_jump)
  0x0028D977  0000                    add      byte ptr [eax], al             
  0x0028D979  7050                    jo       0x28d9cb                       
  0x0028D97B  001e                    add      byte ptr [esi], bl             
  0x0028D97D  0000                    add      byte ptr [eax], al             
  0x0028D97F  0000                    add      byte ptr [eax], al             
  0x0028D981  f4                      hlt                                     
  0x0028D982  61                      popal                                   
  0x0028D983  001e                    add      byte ptr [esi], bl             
  0x0028D985  0000                    add      byte ptr [eax], al             
  0x0028D987  0000                    add      byte ptr [eax], al             
  0x0028D989  0138                    add      dword ptr [eax], edi           
  0x0028D98B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028D991  7045                    jo       0x28d9d8                       
  0x0028D993  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028D996  0000                    add      byte ptr [eax], al             
  0x0028D998  007057                  add      byte ptr [eax + 0x57], dh      
  0x0028D99B  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028D99E  0000                    add      byte ptr [eax], al             
  0x0028D9A0  007062                  add      byte ptr [eax + 0x62], dh      
  0x0028D9A3  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028D9A6  0000                    add      byte ptr [eax], al             
  0x0028D9A8  22f4                    and      dh, ah                         
  0x0028D9AA  0500ffff00              add      eax, 0xffff00                  
  0x0028D9AF  000c00                  add      byte ptr [eax + eax], cl       
  0x0028D9B2  0000                    add      byte ptr [eax], al             
  0x0028D9B4  1300                    adc      eax, dword ptr [eax]           
  0x0028D9B6  2000                    and      byte ptr [eax], al             
  0x0028D9B8  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028D9BB  0002                    add      byte ptr [edx], al             
  0x0028D9BD  0000                    add      byte ptr [eax], al             
  0x0028D9BF  0000                    add      byte ptr [eax], al             
  0x0028D9C1  7056                    jo       0x28da19                       
  0x0028D9C3  0003                    add      byte ptr [ebx], al             
  0x0028D9C5  0000                    add      byte ptr [eax], al             
  0x0028D9C7  0000                    add      byte ptr [eax], al             
  0x0028D9C9  7056                    jo       0x28da21                       
                                        ; XREF: 0x0028D979 (cond_jump)
  0x0028D9CB  000400                  add      byte ptr [eax + eax], al       
  0x0028D9CE  0000                    add      byte ptr [eax], al             
  0x0028D9D0  0000                    add      byte ptr [eax], al             
  0x0028D9D2  360000                  add      byte ptr ss:[eax], al          
  0x0028D9D6  44                      inc      esp                            
  0x0028D9D7  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028D9DD  c406                    les      eax, ptr [esi]                 
  0x0028D9DF  001d00000000            add      byte ptr [0], bl               
  0x0028D9E5  f4                      hlt                                     
  0x0028D9E6  56                      push     esi                            
  0x0028D9E7  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x0028D9ED  c422                    les      esp, ptr [edx]                 
  0x0028D9EF  004000                  add      byte ptr [eax], al             
  0x0028D9F2  2000                    and      byte ptr [eax], al             
  0x0028D9F4  0090210000e0            add      byte ptr [eax - 0x1fffffdf], dl 
  0x0028D9FA  7000                    jo       0x28d9fc                       
                                        ; XREF: 0x0028D9FA (cond_jump)
  0x0028D9FC  00c4                    add      ah, al                         
  0x0028D9FE  2200                    and      al, byte ptr [eax]             
  0x0028DA00  00f4                    add      ah, dh                         
  0x0028DA02  46                      inc      esi                            
  0x0028DA03  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028DA09  f4                      hlt                                     
  0x0028DA0A  44                      inc      esp                            
  0x0028DA0B  0000                    add      byte ptr [eax], al             
  0x0028DA0D  0100                    add      dword ptr [eax], eax           
  0x0028DA0F  002e                    add      byte ptr [esi], ch             
  0x0028DA11  1d0c004000              sbb      eax, 0x40000c                  
  0x0028DA16  2000                    and      byte ptr [eax], al             
  0x0028DA18  0090210000c4            add      byte ptr [eax - 0x3bffffdf], dl 
  0x0028DA1E  2200                    and      al, byte ptr [eax]             
  0x0028DA20  00f4                    add      ah, dh                         
  0x0028DA22  46                      inc      esi                            
  0x0028DA23  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028DA2A  44                      inc      esp                            
  0x0028DA2B  00720b                  add      byte ptr [edx + 0xb], dh       
  0x0028DA2E  0000                    add      byte ptr [eax], al             
  0x0028DA30  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028DA36  2000                    and      byte ptr [eax], al             
  0x0028DA38  009521000070            add      byte ptr [ebp + 0x70000021], dl 
  0x0028DA3E  6600410b                add      byte ptr [ecx + 0xb], al       
  0x0028DA42  0000                    add      byte ptr [eax], al             
  0x0028DA44  f1                      int1                                    
  0x0028DA45  030d0000f066            add      ecx, dword ptr [0x66f00000]    
  0x0028DA4B  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028DA4E  0000                    add      byte ptr [eax], al             
  0x0028DA50  005e20                  add      byte ptr [esi + 0x20], bl      
  0x0028DA53  0000                    add      byte ptr [eax], al             
  0x0028DA56  56                      push     esi                            
  0x0028DA57  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028DA5A  0000                    add      byte ptr [eax], al             
  0x0028DA5C  0300                    add      eax, dword ptr [eax]           
  0x0028DA5E  2000                    and      byte ptr [eax], al             
  0x0028DA60  07                      pop      es                             
  0x0028DA61  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028DA62  0500000738              add      eax, 0x38070000                
  0x0028DA67  0000                    add      byte ptr [eax], al             
  0x0028DA69  f4                      hlt                                     
  0x0028DA6A  60                      pushal                                  
  0x0028DA6B  008904000000            add      byte ptr [ecx + 4], cl         
  0x0028DA71  f4                      hlt                                     
  0x0028DA72  650039                  add      byte ptr gs:[ecx], bh          
  0x0028DA75  0b00                    or       eax, dword ptr [eax]           
  0x0028DA77  00f1                    add      cl, dh                         
  0x0028DA79  030d0000f057            add      ecx, dword ptr [0x57f00000]    
  0x0028DA7F  0002                    add      byte ptr [edx], al             
  0x0028DA81  0000                    add      byte ptr [eax], al             
  0x0028DA83  000b                    add      byte ptr [ebx], cl             
  0x0028DA85  0020                    add      byte ptr [eax], ah             
  0x0028DA87  0014a4                  add      byte ptr [esp], dl             
  0x0028DA8A  050000f462              add      eax, 0x62f40000                
  0x0028DA8F  000500000000            add      byte ptr [0], al               
  0x0028DA95  f4                      hlt                                     
  0x0028DA96  66000a                  add      byte ptr [edx], cl             
  0x0028DA99  0d0000004e              or       eax, 0x4e000000                
  0x0028DA9E  2200                    and      al, byte ptr [eax]             
  0x0028DAA0  10f4                    adc      ah, dh                         
  0x0028DAA2  44                      inc      esp                            
  0x0028DAA3  0001                    add      byte ptr [ecx], al             
  0x0028DAA5  0000                    add      byte ptr [eax], al             
  0x0028DAA7  008c4301003ed0          add      byte ptr [ebx + eax*2 - 0x2fc1ffff], cl 
  0x0028DAAE  2100                    and      dword ptr [eax], eax           
  0x0028DAB0  10cd                    adc      ch, cl                         
  0x0028DAB2  06                      push     es                             
  0x0028DAB3  0002                    add      byte ptr [edx], al             
  0x0028DAB5  0000                    add      byte ptr [eax], al             
  0x0028DAB7  0000                    add      byte ptr [eax], al             
  0x0028DAB9  58                      pop      eax                            
  0x0028DABA  44                      inc      esp                            
  0x0028DABB  0000                    add      byte ptr [eax], al             
  0x0028DABF  00d0                    add      al, dl                         
  0x0028DAC3  00d2                    add      dl, dl                         
  0x0028DAC7  00d2                    add      dl, dl                         
  0x0028DAC9  f066000d00000024        lock add byte ptr [0x24000000], cl      
  0x0028DAD1  1d0c000066              sbb      eax, 0x6600000c                
  0x0028DAD6  50                      push     eax                            
  0x0028DAD7  0000                    add      byte ptr [eax], al             
  0x0028DADA  57                      push     edi                            
  0x0028DADB  0003                    add      byte ptr [ebx], al             
  0x0028DADD  0000                    add      byte ptr [eax], al             
  0x0028DADF  000b                    add      byte ptr [ebx], cl             
  0x0028DAE1  0020                    add      byte ptr [eax], ah             
  0x0028DAE3  0014a4                  add      byte ptr [esp], dl             
  0x0028DAE6  050000f462              add      eax, 0x62f40000                
  0x0028DAEB  0008                    add      byte ptr [eax], cl             
  0x0028DAED  0000                    add      byte ptr [eax], al             
  0x0028DAEF  0000                    add      byte ptr [eax], al             
  0x0028DAF1  f4                      hlt                                     
  0x0028DAF2  66000d0d000000          add      byte ptr [0xd], cl             
  0x0028DAF9  4e                      dec      esi                            
  0x0028DAFA  2200                    and      al, byte ptr [eax]             
  0x0028DAFC  10f4                    adc      ah, dh                         
  0x0028DAFE  44                      inc      esp                            
  0x0028DAFF  0002                    add      byte ptr [edx], al             
  0x0028DB01  0000                    add      byte ptr [eax], al             
  0x0028DB03  008c4301003ed0          add      byte ptr [ebx + eax*2 - 0x2fc1ffff], cl 
  0x0028DB0A  2100                    and      dword ptr [eax], eax           
  0x0028DB0C  10cd                    adc      ch, cl                         
  0x0028DB0E  06                      push     es                             
  0x0028DB0F  0002                    add      byte ptr [edx], al             
  0x0028DB11  0000                    add      byte ptr [eax], al             
  0x0028DB13  0000                    add      byte ptr [eax], al             
  0x0028DB15  58                      pop      eax                            
  0x0028DB16  44                      inc      esp                            
  0x0028DB17  0000                    add      byte ptr [eax], al             
  0x0028DB1B  00d0                    add      al, dl                         
  0x0028DB1F  00d2                    add      dl, dl                         
  0x0028DB23  00d2                    add      dl, dl                         
  0x0028DB25  f066000e                lock add byte ptr [esi], cl             
  0x0028DB29  0000                    add      byte ptr [eax], al             
  0x0028DB2B  0020                    add      byte ptr [eax], ah             
  0x0028DB2D  1d0c000066              sbb      eax, 0x6600000c                
  0x0028DB32  50                      push     eax                            
  0x0028DB33  0000                    add      byte ptr [eax], al             
  0x0028DB36  57                      push     edi                            
  0x0028DB37  000400                  add      byte ptr [eax + eax], al       
  0x0028DB3A  0000                    add      byte ptr [eax], al             
  0x0028DB3C  0b00                    or       eax, dword ptr [eax]           
  0x0028DB3E  2000                    and      byte ptr [eax], al             
  0x0028DB40  13a4050000f462          adc      esp, dword ptr [ebp + eax + 0x62f40000] 
  0x0028DB47  000b                    add      byte ptr [ebx], cl             
  0x0028DB49  0000                    add      byte ptr [eax], al             
  0x0028DB4B  0000                    add      byte ptr [eax], al             
  0x0028DB4D  f4                      hlt                                     
  0x0028DB4E  660010                  add      byte ptr [eax], dl             
  0x0028DB51  0d0000004e              or       eax, 0x4e000000                
  0x0028DB56  2200                    and      al, byte ptr [eax]             
  0x0028DB58  10f4                    adc      ah, dh                         
  0x0028DB5A  44                      inc      esp                            
  0x0028DB5B  00050000008c            add      byte ptr [0x8c000000], al      
  0x0028DB61  42                      inc      edx                            
  0x0028DB62  0100                    add      dword ptr [eax], eax           
  0x0028DB64  3ed021                  shl      byte ptr ds:[ecx], 1           
  0x0028DB67  0010                    add      byte ptr [eax], dl             
  0x0028DB69  cd06                    int      6                              
  0x0028DB6B  0002                    add      byte ptr [edx], al             
  0x0028DB6D  0000                    add      byte ptr [eax], al             
  0x0028DB6F  0000                    add      byte ptr [eax], al             
  0x0028DB71  58                      pop      eax                            
  0x0028DB72  44                      inc      esp                            
  0x0028DB73  0000                    add      byte ptr [eax], al             
  0x0028DB77  00d0                    add      al, dl                         
  0x0028DB7B  00d2                    add      dl, dl                         
  0x0028DB7D  f066000f                lock add byte ptr [edi], cl             
  0x0028DB81  0000                    add      byte ptr [eax], al             
  0x0028DB83  0020                    add      byte ptr [eax], ah             
  0x0028DB85  1d0c000066              sbb      eax, 0x6600000c                
  0x0028DB8A  50                      push     eax                            
  0x0028DB8B  000c00                  add      byte ptr [eax + eax], cl       
  0x0028DB8E  0000                    add      byte ptr [eax], al             
  0x0028DB90  00f0                    add      al, dh                         
  0x0028DB92  6200                    bound    eax, qword ptr [eax]           
  0x0028DB94  55                      push     ebp                            
  0x0028DB95  0b00                    or       eax, dword ptr [eax]           
  0x0028DB97  0022                    add      byte ptr [edx], ah             
  0x0028DB9A  0500470b00              add      eax, 0xb4700                   
  0x0028DB9F  0000                    add      byte ptr [eax], al             
  0x0028DBA2  57                      push     edi                            
  0x0028DBA3  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028DBA6  0000                    add      byte ptr [eax], al             
  0x0028DBA8  00f0                    add      al, dh                         
  0x0028DBAA  45                      inc      ebp                            
  0x0028DBAB  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028DBAE  0000                    add      byte ptr [eax], al             
  0x0028DBB0  00f4                    add      ah, dh                         
  0x0028DBB2  61                      popal                                   
  0x0028DBB3  007f0b                  add      byte ptr [edi + 0xb], bh       
  0x0028DBB6  0000                    add      byte ptr [eax], al             
  0x0028DBB8  00f0                    add      al, dh                         
  0x0028DBBA  7100                    jno      0x28dbbc                       
                                        ; XREF: 0x0028DBBA (cond_jump)
  0x0028DBBC  97                      xchg     edi, eax                       
  0x0028DBBD  0b00                    or       eax, dword ptr [eax]           
  0x0028DBBF  0000                    add      byte ptr [eax], al             
  0x0028DBC1  0138                    add      dword ptr [eax], edi           
  0x0028DBC3  006f03                  add      byte ptr [edi + 3], ch         
  0x0028DBC6  0d0000f461              or       eax, 0x61f40000                
  0x0028DBCB  00840b000000f0          add      byte ptr [ebx + ecx - 0x10000000], al 
  0x0028DBD2  7100                    jno      0x28dbd4                       
                                        ; XREF: 0x0028DBD2 (cond_jump)
  0x0028DBD4  97                      xchg     edi, eax                       
  0x0028DBD5  0b00                    or       eax, dword ptr [eax]           
  0x0028DBD7  0000                    add      byte ptr [eax], al             
  0x0028DBD9  0138                    add      dword ptr [eax], edi           
  0x0028DBDB  006f03                  add      byte ptr [edi + 3], ch         
  0x0028DBDE  0d0000f461              or       eax, 0x61f40000                
  0x0028DBE3  004a0b                  add      byte ptr [edx + 0xb], cl       
  0x0028DBE6  0000                    add      byte ptr [eax], al             
  0x0028DBE8  0001                    add      byte ptr [ecx], al             
  0x0028DBEA  3800                    cmp      byte ptr [eax], al             
  0x0028DBEC  93                      xchg     ebx, eax                       
  0x0028DBED  030d0000f056            add      ecx, dword ptr [0x56f00000]    
  0x0028DBF3  004a0b                  add      byte ptr [edx + 0xb], cl       
  0x0028DBF6  0000                    add      byte ptr [eax], al             
  0x0028DBF8  0300                    add      eax, dword ptr [eax]           
  0x0028DBFA  2000                    and      byte ptr [eax], al             
  0x0028DBFC  05a4050000              add      eax, 0x5a4                     
  0x0028DC01  f4                      hlt                                     
  0x0028DC02  61                      popal                                   
  0x0028DC03  004b0b                  add      byte ptr [ebx + 0xb], cl       
  0x0028DC06  0000                    add      byte ptr [eax], al             
  0x0028DC08  0008                    add      byte ptr [eax], cl             
  0x0028DC0A  3800                    cmp      byte ptr [eax], al             
  0x0028DC0C  93                      xchg     ebx, eax                       
  0x0028DC0D  030d00130020            add      ecx, dword ptr [0x20001300]    
  0x0028DC13  0000                    add      byte ptr [eax], al             
  0x0028DC15  7056                    jo       0x28dc6d                       
  0x0028DC17  001e                    add      byte ptr [esi], bl             
  0x0028DC19  0000                    add      byte ptr [eax], al             
  0x0028DC1B  0000                    add      byte ptr [eax], al             
  0x0028DC1D  f4                      hlt                                     
  0x0028DC1E  61                      popal                                   
  0x0028DC1F  00890b000000            add      byte ptr [ecx + 0xb], cl       
  0x0028DC25  0138                    add      dword ptr [eax], edi           
  0x0028DC27  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DC2D  f9                      stc                                     
  0x0028DC2E  56                      push     esi                            
  0x0028DC2F  0003                    add      byte ptr [ebx], al             
  0x0028DC31  0020                    add      byte ptr [eax], ah             
  0x0028DC33  0005a4050000            add      byte ptr [0x5a4], al           
  0x0028DC39  f4                      hlt                                     
  0x0028DC3A  61                      popal                                   
  0x0028DC3B  001e                    add      byte ptr [esi], bl             
  0x0028DC3D  0000                    add      byte ptr [eax], al             
  0x0028DC3F  0000                    add      byte ptr [eax], al             
  0x0028DC41  0138                    add      dword ptr [eax], edi           
  0x0028DC43  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DC4A  56                      push     esi                            
  0x0028DC4B  007d0b                  add      byte ptr [ebp + 0xb], bh       
  0x0028DC4E  0000                    add      byte ptr [eax], al             
  0x0028DC50  c54001                  lds      eax, ptr [eax + 1]             
  0x0028DC53  0002                    add      byte ptr [edx], al             
  0x0028DC55  0000                    add      byte ptr [eax], al             
  0x0028DC57  0012                    add      byte ptr [edx], dl             
  0x0028DC59  2405                    and      al, 5                          
  0x0028DC5B  0000                    add      byte ptr [eax], al             
  0x0028DC5D  f4                      hlt                                     
  0x0028DC5E  44                      inc      esp                            
  0x0028DC5F  0010                    add      byte ptr [eax], dl             
  0x0028DC61  0000                    add      byte ptr [eax], al             
  0x0028DC63  0000                    add      byte ptr [eax], al             
  0x0028DC65  7044                    jo       0x28dcab                       
  0x0028DC67  001e                    add      byte ptr [esi], bl             
  0x0028DC69  0000                    add      byte ptr [eax], al             
  0x0028DC6B  0000                    add      byte ptr [eax], al             
  0x0028DC6E  56                      push     esi                            
  0x0028DC6F  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028DC72  0000                    add      byte ptr [eax], al             
  0x0028DC74  0300                    add      eax, dword ptr [eax]           
  0x0028DC76  2000                    and      byte ptr [eax], al             
  0x0028DC78  06                      push     es                             
  0x0028DC79  2405                    and      al, 5                          
  0x0028DC7B  0000                    add      byte ptr [eax], al             
  0x0028DC7D  f4                      hlt                                     
  0x0028DC7E  61                      popal                                   
  0x0028DC7F  001e                    add      byte ptr [esi], bl             
  0x0028DC81  0000                    add      byte ptr [eax], al             
  0x0028DC83  0000                    add      byte ptr [eax], al             
  0x0028DC85  0538009303              add      eax, 0x3930038                 
  0x0028DC8A  0d00050c05              or       eax, 0x50c0500                 
  0x0028DC8F  0000                    add      byte ptr [eax], al             
  0x0028DC91  f4                      hlt                                     
  0x0028DC92  61                      popal                                   
  0x0028DC93  001e                    add      byte ptr [esi], bl             
  0x0028DC95  0000                    add      byte ptr [eax], al             
  0x0028DC97  0000                    add      byte ptr [eax], al             
  0x0028DC99  0138                    add      dword ptr [eax], edi           
  0x0028DC9B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DCA1  f4                      hlt                                     
  0x0028DCA2  61                      popal                                   
  0x0028DCA3  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028DCAA  7100                    jno      0x28dcac                       
                                        ; XREF: 0x0028DCAA (cond_jump)
  0x0028DCAC  97                      xchg     edi, eax                       
  0x0028DCAD  0b00                    or       eax, dword ptr [eax]           
  0x0028DCAF  0000                    add      byte ptr [eax], al             
  0x0028DCB1  0238                    add      bh, byte ptr [eax]             
  0x0028DCB3  006f03                  add      byte ptr [edi + 3], ch         
  0x0028DCB6  0d0000f056              or       eax, 0x56f00000                
  0x0028DCBB  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028DCBE  0000                    add      byte ptr [eax], al             
  0x0028DCC0  0300                    add      eax, dword ptr [eax]           
  0x0028DCC2  2000                    and      byte ptr [eax], al             
  0x0028DCC4  05a4050000              add      eax, 0x5a4                     
  0x0028DCC9  f4                      hlt                                     
  0x0028DCCA  61                      popal                                   
  0x0028DCCB  008f0b000000            add      byte ptr [edi + 0xb], cl       
  0x0028DCD1  0138                    add      dword ptr [eax], edi           
  0x0028DCD3  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DCD9  0036                    add      byte ptr [esi], dh             
  0x0028DCDB  0000                    add      byte ptr [eax], al             
  0x0028DCDE  44                      inc      esp                            
  0x0028DCDF  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028DCE5  c406                    les      eax, ptr [esi]                 
  0x0028DCE7  0011                    add      byte ptr [ecx], dl             
  0x0028DCE9  0000                    add      byte ptr [eax], al             
  0x0028DCEB  0000                    add      byte ptr [eax], al             
  0x0028DCED  f4                      hlt                                     
  0x0028DCEE  56                      push     esi                            
  0x0028DCEF  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028DCF5  c422                    les      esp, ptr [edx]                 
  0x0028DCF7  004000                  add      byte ptr [eax], al             
  0x0028DCFA  2000                    and      byte ptr [eax], al             
  0x0028DCFC  0091210000e1            add      byte ptr [ecx - 0x1effffdf], dl 
  0x0028DD02  56                      push     esi                            
  0x0028DD03  0003                    add      byte ptr [ebx], al             
  0x0028DD05  0020                    add      byte ptr [eax], ah             
  0x0028DD07  0008                    add      byte ptr [eax], cl             
  0x0028DD09  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028DD0A  050000f456              add      eax, 0x56f40000                
  0x0028DD0F  00a00b000000            add      byte ptr [eax + 0xb], ah       
  0x0028DD15  c422                    les      esp, ptr [edx]                 
  0x0028DD17  004000                  add      byte ptr [eax], al             
  0x0028DD1A  2000                    and      byte ptr [eax], al             
  0x0028DD1C  009121000006            add      byte ptr [ecx + 0x6000021], dl 
  0x0028DD22  3800                    cmp      byte ptr [eax], al             
  0x0028DD24  93                      xchg     ebx, eax                       
  0x0028DD25  030d00005e20            add      ecx, dword ptr [0x205e0000]    
  0x0028DD2B  0000                    add      byte ptr [eax], al             
  0x0028DD2D  0036                    add      byte ptr [esi], dh             
  0x0028DD2F  0000                    add      byte ptr [eax], al             
  0x0028DD32  44                      inc      esp                            
  0x0028DD33  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028DD39  c406                    les      eax, ptr [esi]                 
  0x0028DD3B  0023                    add      byte ptr [ebx], ah             
  0x0028DD3D  0000                    add      byte ptr [eax], al             
  0x0028DD3F  0000                    add      byte ptr [eax], al             
  0x0028DD41  f4                      hlt                                     
  0x0028DD42  56                      push     esi                            
  0x0028DD43  008a0b000000            add      byte ptr [edx + 0xb], cl       
  0x0028DD49  c422                    les      esp, ptr [edx]                 
  0x0028DD4B  004000                  add      byte ptr [eax], al             
  0x0028DD4E  2000                    and      byte ptr [eax], al             
  0x0028DD50  0091210000e1            add      byte ptr [ecx - 0x1effffdf], dl 
  0x0028DD56  56                      push     esi                            
  0x0028DD57  0003                    add      byte ptr [ebx], al             
  0x0028DD59  0020                    add      byte ptr [eax], ah             
  0x0028DD5B  001a                    add      byte ptr [edx], bl             
  0x0028DD5D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028DD5E  050000c422              add      eax, 0x22c40000                
  0x0028DD63  0000                    add      byte ptr [eax], al             
  0x0028DD65  f4                      hlt                                     
  0x0028DD66  46                      inc      esi                            
  0x0028DD67  001f                    add      byte ptr [edi], bl             
  0x0028DD69  0000                    add      byte ptr [eax], al             
  0x0028DD6B  00d0                    add      al, dl                         
  0x0028DD6D  f4                      hlt                                     
  0x0028DD6E  44                      inc      esp                            
  0x0028DD6F  0000                    add      byte ptr [eax], al             
  0x0028DD71  0000                    add      byte ptr [eax], al             
  0x0028DD73  002e                    add      byte ptr [esi], ch             
  0x0028DD75  1d0c004000              sbb      eax, 0x40000c                  
  0x0028DD7A  2000                    and      byte ptr [eax], al             
  0x0028DD7C  009121000004            add      byte ptr [ecx + 0x4000021], dl 
  0x0028DD82  3800                    cmp      byte ptr [eax], al             
  0x0028DD84  a3030d0000              mov      dword ptr [0xd03], eax         
  0x0028DD89  f4                      hlt                                     
  0x0028DD8A  56                      push     esi                            
  0x0028DD8B  00910b000000            add      byte ptr [ecx + 0xb], dl       
  0x0028DD91  c422                    les      esp, ptr [edx]                 
  0x0028DD93  004000                  add      byte ptr [eax], al             
  0x0028DD96  2000                    and      byte ptr [eax], al             
  0x0028DD98  0090210000e0            add      byte ptr [eax - 0x1fffffdf], dl 
  0x0028DD9E  7100                    jno      0x28dda0                       
                                        ; XREF: 0x0028DD9E (cond_jump)
  0x0028DDA0  0007                    add      byte ptr [edi], al             
  0x0028DDA2  3800                    cmp      byte ptr [eax], al             
  0x0028DDA4  81030d0000f4            add      dword ptr [ebx], 0xf400000d    
  0x0028DDAA  56                      push     esi                            
  0x0028DDAB  00610b                  add      byte ptr [ecx + 0xb], ah       
  0x0028DDAE  0000                    add      byte ptr [eax], al             
  0x0028DDB0  00c4                    add      ah, al                         
  0x0028DDB2  2200                    and      al, byte ptr [eax]             
  0x0028DDB4  40                      inc      eax                            
  0x0028DDB5  0020                    add      byte ptr [eax], ah             
  0x0028DDB7  0000                    add      byte ptr [eax], al             
  0x0028DDB9  91                      xchg     ecx, eax                       
  0x0028DDBA  2100                    and      dword ptr [eax], eax           
  0x0028DDBC  0002                    add      byte ptr [edx], al             
  0x0028DDBE  3800                    cmp      byte ptr [eax], al             
  0x0028DDC0  93                      xchg     ebx, eax                       
  0x0028DDC1  030d00005e20            add      ecx, dword ptr [0x205e0000]    
  0x0028DDC7  0000                    add      byte ptr [eax], al             
  0x0028DDCA  56                      push     esi                            
  0x0028DDCB  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028DDCE  0000                    add      byte ptr [eax], al             
  0x0028DDD0  0300                    add      eax, dword ptr [eax]           
  0x0028DDD2  2000                    and      byte ptr [eax], al             
  0x0028DDD4  0ca4                    or       al, 0xa4                       
  0x0028DDD6  050000f056              add      eax, 0x56f00000                
  0x0028DDDB  008f0b000003            add      byte ptr [edi + 0x300000b], cl 
  0x0028DDE1  0020                    add      byte ptr [eax], ah             
  0x0028DDE3  0008                    add      byte ptr [eax], cl             
  0x0028DDE5  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028DDE6  050000f461              add      eax, 0x61f40000                
  0x0028DDEB  009b00000000            add      byte ptr [ebx], bl             
  0x0028DDF1  0438                    add      al, 0x38                       
  0x0028DDF3  00a3030d0000            add      byte ptr [ebx + 0xd03], ah     
  0x0028DDF9  0239                    add      bh, byte ptr [ecx]             
  0x0028DDFB  0000                    add      byte ptr [eax], al             
  0x0028DDFD  07                      pop      es                             
  0x0028DDFE  3800                    cmp      byte ptr [eax], al             
  0x0028DE00  81030d0000f4            add      dword ptr [ebx], 0xf400000d    
  0x0028DE06  61                      popal                                   
  0x0028DE07  00900b000000            add      byte ptr [eax + 0xb], dl       
  0x0028DE0D  0138                    add      dword ptr [eax], edi           
  0x0028DE0F  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DE15  f9                      stc                                     
  0x0028DE16  56                      push     esi                            
  0x0028DE17  0003                    add      byte ptr [ebx], al             
  0x0028DE19  0020                    add      byte ptr [eax], ah             
  0x0028DE1B  0049a4                  add      byte ptr [ecx - 0x5c], cl      
  0x0028DE1E  050000f456              add      eax, 0x56f40000                
  0x0028DE23  0002                    add      byte ptr [edx], al             
  0x0028DE25  0000                    add      byte ptr [eax], al             
  0x0028DE27  0000                    add      byte ptr [eax], al             
  0x0028DE29  7056                    jo       0x28de81                       
  0x0028DE2B  001e                    add      byte ptr [esi], bl             
  0x0028DE2D  0000                    add      byte ptr [eax], al             
  0x0028DE2F  0000                    add      byte ptr [eax], al             
  0x0028DE31  f4                      hlt                                     
  0x0028DE32  61                      popal                                   
  0x0028DE33  001e                    add      byte ptr [esi], bl             
  0x0028DE35  0000                    add      byte ptr [eax], al             
  0x0028DE37  0000                    add      byte ptr [eax], al             
  0x0028DE39  0238                    add      bh, byte ptr [eax]             
  0x0028DE3B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DE41  f4                      hlt                                     
  0x0028DE42  56                      push     esi                            
  0x0028DE43  0001                    add      byte ptr [ecx], al             
  0x0028DE45  0000                    add      byte ptr [eax], al             
  0x0028DE47  0000                    add      byte ptr [eax], al             
  0x0028DE49  7056                    jo       0x28dea1                       
  0x0028DE4B  001e                    add      byte ptr [esi], bl             
  0x0028DE4D  0000                    add      byte ptr [eax], al             
  0x0028DE4F  0000                    add      byte ptr [eax], al             
  0x0028DE51  f4                      hlt                                     
  0x0028DE52  61                      popal                                   
  0x0028DE53  001e                    add      byte ptr [esi], bl             
  0x0028DE55  0000                    add      byte ptr [eax], al             
  0x0028DE57  0000                    add      byte ptr [eax], al             
  0x0028DE59  0238                    add      bh, byte ptr [eax]             
  0x0028DE5B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DE61  f4                      hlt                                     
  0x0028DE62  56                      push     esi                            
  0x0028DE63  0001                    add      byte ptr [ecx], al             
  0x0028DE65  0000                    add      byte ptr [eax], al             
  0x0028DE67  0000                    add      byte ptr [eax], al             
  0x0028DE69  7056                    jo       0x28dec1                       
  0x0028DE6B  001e                    add      byte ptr [esi], bl             
  0x0028DE6D  0000                    add      byte ptr [eax], al             
  0x0028DE6F  0000                    add      byte ptr [eax], al             
  0x0028DE71  f4                      hlt                                     
  0x0028DE72  61                      popal                                   
  0x0028DE73  001e                    add      byte ptr [esi], bl             
  0x0028DE75  0000                    add      byte ptr [eax], al             
  0x0028DE77  0000                    add      byte ptr [eax], al             
  0x0028DE79  0238                    add      bh, byte ptr [eax]             
  0x0028DE7B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
                                        ; XREF: 0x0028DE29 (cond_jump)
  0x0028DE81  f4                      hlt                                     
  0x0028DE82  56                      push     esi                            
  0x0028DE83  0002                    add      byte ptr [edx], al             
  0x0028DE85  0000                    add      byte ptr [eax], al             
  0x0028DE87  0000                    add      byte ptr [eax], al             
  0x0028DE89  7056                    jo       0x28dee1                       
  0x0028DE8B  001e                    add      byte ptr [esi], bl             
  0x0028DE8D  0000                    add      byte ptr [eax], al             
  0x0028DE8F  0000                    add      byte ptr [eax], al             
  0x0028DE91  f4                      hlt                                     
  0x0028DE92  61                      popal                                   
  0x0028DE93  001e                    add      byte ptr [esi], bl             
  0x0028DE95  0000                    add      byte ptr [eax], al             
  0x0028DE97  0000                    add      byte ptr [eax], al             
  0x0028DE99  0238                    add      bh, byte ptr [eax]             
  0x0028DE9B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
                                        ; XREF: 0x0028DE49 (cond_jump)
  0x0028DEA1  f4                      hlt                                     
  0x0028DEA2  56                      push     esi                            
  0x0028DEA3  0007                    add      byte ptr [edi], al             
  0x0028DEA5  0000                    add      byte ptr [eax], al             
  0x0028DEA7  0000                    add      byte ptr [eax], al             
  0x0028DEA9  7056                    jo       0x28df01                       
  0x0028DEAB  001e                    add      byte ptr [esi], bl             
  0x0028DEAD  0000                    add      byte ptr [eax], al             
  0x0028DEAF  0000                    add      byte ptr [eax], al             
  0x0028DEB1  f4                      hlt                                     
  0x0028DEB2  61                      popal                                   
  0x0028DEB3  001e                    add      byte ptr [esi], bl             
  0x0028DEB5  0000                    add      byte ptr [eax], al             
  0x0028DEB7  0000                    add      byte ptr [eax], al             
  0x0028DEB9  0338                    add      edi, dword ptr [eax]           
  0x0028DEBB  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
                                        ; XREF: 0x0028DE69 (cond_jump)
  0x0028DEC1  f4                      hlt                                     
  0x0028DEC2  61                      popal                                   
  0x0028DEC3  006f0b                  add      byte ptr [edi + 0xb], ch       
  0x0028DEC6  0000                    add      byte ptr [eax], al             
  0x0028DEC8  0001                    add      byte ptr [ecx], al             
  0x0028DECA  3800                    cmp      byte ptr [eax], al             
  0x0028DECC  93                      xchg     ebx, eax                       
  0x0028DECD  030d0000f956            add      ecx, dword ptr [0x56f90000]    
  0x0028DED3  0003                    add      byte ptr [ebx], al             
  0x0028DED5  0020                    add      byte ptr [eax], ah             
  0x0028DED7  004aa4                  add      byte ptr [edx - 0x5c], cl      
  0x0028DEDA  050000f461              add      eax, 0x61f40000                
  0x0028DEDF  00730b                  add      byte ptr [ebx + 0xb], dh       
  0x0028DEE2  0000                    add      byte ptr [eax], al             
  0x0028DEE4  0006                    add      byte ptr [esi], al             
  0x0028DEE6  3800                    cmp      byte ptr [eax], al             
  0x0028DEE8  93                      xchg     ebx, eax                       
  0x0028DEE9  030d00000036            add      ecx, dword ptr [0x36000000]    
  0x0028DEEF  0000                    add      byte ptr [eax], al             
  0x0028DEF2  44                      inc      esp                            
  0x0028DEF3  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028DEF9  c406                    les      eax, ptr [esi]                 
  0x0028DEFB  0011                    add      byte ptr [ecx], dl             
  0x0028DEFD  0000                    add      byte ptr [eax], al             
  0x0028DEFF  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028DEA9 (cond_jump)
  0x0028DF01  f4                      hlt                                     
  0x0028DF02  56                      push     esi                            
  0x0028DF03  00740b00                add      byte ptr [ebx + ecx], dh       
  0x0028DF07  0000                    add      byte ptr [eax], al             
  0x0028DF09  c422                    les      esp, ptr [edx]                 
  0x0028DF0B  004000                  add      byte ptr [eax], al             
  0x0028DF0E  2000                    and      byte ptr [eax], al             
  0x0028DF10  009121000004            add      byte ptr [ecx + 0x4000021], dl 
  0x0028DF16  3800                    cmp      byte ptr [eax], al             
  0x0028DF18  93                      xchg     ebx, eax                       
  0x0028DF19  030d0000f456            add      ecx, dword ptr [0x56f40000]    
  0x0028DF1F  000400                  add      byte ptr [eax + eax], al       
  0x0028DF22  0000                    add      byte ptr [eax], al             
  0x0028DF24  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028DF27  001e                    add      byte ptr [esi], bl             
  0x0028DF29  0000                    add      byte ptr [eax], al             
  0x0028DF2B  0000                    add      byte ptr [eax], al             
  0x0028DF2D  f4                      hlt                                     
  0x0028DF2E  61                      popal                                   
  0x0028DF2F  001e                    add      byte ptr [esi], bl             
  0x0028DF31  0000                    add      byte ptr [eax], al             
  0x0028DF33  0000                    add      byte ptr [eax], al             
  0x0028DF35  0338                    add      edi, dword ptr [eax]           
  0x0028DF37  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DF3D  5e                      pop      esi                            
  0x0028DF3E  2000                    and      byte ptr [eax], al             
  0x0028DF40  00f0                    add      al, dh                         
  0x0028DF42  56                      push     esi                            
  0x0028DF43  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028DF46  0000                    add      byte ptr [eax], al             
  0x0028DF48  0300                    add      eax, dword ptr [eax]           
  0x0028DF4A  2000                    and      byte ptr [eax], al             
  0x0028DF4C  0da4050000              or       eax, 0x5a4                     
  0x0028DF51  f4                      hlt                                     
  0x0028DF52  61                      popal                                   
  0x0028DF53  00790b                  add      byte ptr [ecx + 0xb], bh       
  0x0028DF56  0000                    add      byte ptr [eax], al             
  0x0028DF58  000438                  add      byte ptr [eax + edi], al       
  0x0028DF5B  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028DF61  f4                      hlt                                     
  0x0028DF62  56                      push     esi                            
  0x0028DF63  000400                  add      byte ptr [eax + eax], al       
  0x0028DF66  0000                    add      byte ptr [eax], al             
  0x0028DF68  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028DF6B  001e                    add      byte ptr [esi], bl             
  0x0028DF6D  0000                    add      byte ptr [eax], al             
  0x0028DF6F  0000                    add      byte ptr [eax], al             
  0x0028DF71  f4                      hlt                                     
  0x0028DF72  61                      popal                                   
  0x0028DF73  001e                    add      byte ptr [esi], bl             
  0x0028DF75  0000                    add      byte ptr [eax], al             
  0x0028DF77  0000                    add      byte ptr [eax], al             
  0x0028DF79  0338                    add      edi, dword ptr [eax]           
  0x0028DF7B  0093030d0013            add      byte ptr [ebx + 0x13000d03], dl 
  0x0028DF81  f4                      hlt                                     
  0x0028DF82  61                      popal                                   
  0x0028DF83  001e                    add      byte ptr [esi], bl             
  0x0028DF85  0000                    add      byte ptr [eax], al             
  0x0028DF87  0000                    add      byte ptr [eax], al             
  0x0028DF89  61                      popal                                   
  0x0028DF8A  56                      push     esi                            
  0x0028DF8B  0000                    add      byte ptr [eax], al             
  0x0028DF8D  0138                    add      dword ptr [eax], edi           
  0x0028DF8F  0093030d0001            add      byte ptr [ebx + 0x1000d03], dl 
  0x0028DF95  0c05                    or       al, 5                          
  0x0028DF97  0000                    add      byte ptr [eax], al             
  0x0028DF9A  56                      push     esi                            
  0x0028DF9B  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028DF9E  0000                    add      byte ptr [eax], al             
  0x0028DFA0  854301                  test     dword ptr [ebx + 1], eax       
  0x0028DFA3  005524                  add      byte ptr [ebp + 0x24], dl      
  0x0028DFA6  0500004e22              add      eax, 0x224e0000                
  0x0028DFAB  0000                    add      byte ptr [eax], al             
  0x0028DFAE  44                      inc      esp                            
  0x0028DFAF  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028DFB2  0000                    add      byte ptr [eax], al             
  0x0028DFB4  44                      inc      esp                            
  0x0028DFB5  f4                      hlt                                     
  0x0028DFB6  46                      inc      esi                            
  0x0028DFB7  0010                    add      byte ptr [eax], dl             
  0x0028DFB9  0000                    add      byte ptr [eax], al             
  0x0028DFBB  0000                    add      byte ptr [eax], al             
  0x0028DFBE  2100                    and      dword ptr [eax], eax           
  0x0028DFC0  00ee                    add      dh, ch                         
  0x0028DFC2  2100                    and      dword ptr [eax], eax           
  0x0028DFC4  36f4                    hlt                                     
  0x0028DFC6  44                      inc      esp                            
  0x0028DFC7  0010                    add      byte ptr [eax], dl             
  0x0028DFC9  0000                    add      byte ptr [eax], al             
  0x0028DFCB  004000                  add      byte ptr [eax], al             
  0x0028DFCE  2000                    and      byte ptr [eax], al             
  0x0028DFD0  00c4                    add      ah, al                         
  0x0028DFD2  2100                    and      dword ptr [eax], eax           
  0x0028DFD4  b0f0                    mov      al, 0xf0                       
                                        ; XREF: 0x0028DFE4 (cond_jump)
  0x0028DFD6  47                      inc      edi                            
  0x0028DFD7  009d0b00002e            add      byte ptr [ebp + 0x2e00000b], bl 
  0x0028DFDD  1d0c004000              sbb      eax, 0x40000c                  
  0x0028DFE2  2000                    and      byte ptr [eax], al             
  0x0028DFE4  70f0                    jo       0x28dfd6                       
  0x0028DFE6  44                      inc      esp                            
  0x0028DFE7  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028DFEA  0000                    add      byte ptr [eax], al             
  0x0028DFEC  41                      inc      ecx                            
  0x0028DFEE  2100                    and      dword ptr [eax], eax           
  0x0028DFF0  06                      push     es                             
  0x0028DFF1  1d0c0000b0              sbb      eax, 0xb000000c                
  0x0028DFF6  1800                    sbb      byte ptr [eax], al             
  0x0028DFF8  9e                      sahf                                    
  0x0028DFF9  0b00                    or       eax, dword ptr [eax]           
  0x0028DFFB  0054f044                add      byte ptr [eax + esi*8 + 0x44], dl 
  0x0028DFFF  007a0b                  add      byte ptr [edx + 0xb], bh       
  0x0028E002  0000                    add      byte ptr [eax], al             
  0x0028E004  44                      inc      esp                            
  0x0028E005  0020                    add      byte ptr [eax], ah             
  0x0028E007  00740020                add      byte ptr [eax + eax + 0x20], dh 
  0x0028E00B  0003                    add      byte ptr [ebx], al             
  0x0028E00D  0020                    add      byte ptr [eax], ah             
  0x0028E00F  001a                    add      byte ptr [edx], bl             
  0x0028E011  f4                      hlt                                     
  0x0028E012  0500804701              add      eax, 0x1478000                 
  0x0028E017  0000                    add      byte ptr [eax], al             
  0x0028E01A  44                      inc      esp                            
  0x0028E01B  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028E01E  0000                    add      byte ptr [eax], al             
  0x0028E020  06                      push     es                             
  0x0028E021  1c0c                    sbb      al, 0xc                        
  0x0028E023  0041c4                  add      byte ptr [ecx - 0x3c], al      
  0x0028E026  2100                    and      dword ptr [eax], eax           
  0x0028E028  40                      inc      eax                            
  0x0028E029  0020                    add      byte ptr [eax], ah             
  0x0028E02B  0000                    add      byte ptr [eax], al             
  0x0028E02D  7056                    jo       0x28e085                       
  0x0028E02F  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028E032  0000                    add      byte ptr [eax], al             
  0x0028E034  c54001                  lds      eax, ptr [eax + 1]             
  0x0028E037  00ff                    add      bh, bh                         
  0x0028E039  0100                    add      dword ptr [eax], eax           
  0x0028E03B  0002                    add      byte ptr [edx], al             
  0x0028E03D  f4                      hlt                                     
  0x0028E03E  05000c0000              add      eax, 0xc00                     
  0x0028E043  0000                    add      byte ptr [eax], al             
  0x0028E046  56                      push     esi                            
  0x0028E047  00710b                  add      byte ptr [ecx + 0xb], dh       
  0x0028E04A  0000                    add      byte ptr [eax], al             
  0x0028E04C  41                      inc      ecx                            
  0x0028E04D  c421                    les      esp, ptr [ecx]                 
  0x0028E04F  0006                    add      byte ptr [esi], al             
  0x0028E051  1d0c0041c4              sbb      eax, 0xc441000c                
  0x0028E056  2100                    and      dword ptr [eax], eax           
  0x0028E058  40                      inc      eax                            
  0x0028E059  0020                    add      byte ptr [eax], ah             
  0x0028E05B  0000                    add      byte ptr [eax], al             
  0x0028E05D  7056                    jo       0x28e0b5                       
  0x0028E05F  00710b                  add      byte ptr [ecx + 0xb], dh       
  0x0028E062  0000                    add      byte ptr [eax], al             
  0x0028E064  00f4                    add      ah, dh                         
  0x0028E066  60                      pushal                                  
  0x0028E067  006c0b00                add      byte ptr [ebx + ecx], ch       
  0x0028E06B  0000                    add      byte ptr [eax], al             
  0x0028E06D  e056                    loopne   0x28e0c5                       
  0x0028E06F  00440020                add      byte ptr [eax + eax + 0x20], al 
  0x0028E073  0000                    add      byte ptr [eax], al             
  0x0028E075  60                      pushal                                  
  0x0028E076  56                      push     esi                            
  0x0028E077  0000                    add      byte ptr [eax], al             
  0x0028E079  f4                      hlt                                     
  0x0028E07A  61                      popal                                   
  0x0028E07B  00660b                  add      byte ptr [esi + 0xb], ah       
  0x0028E07E  0000                    add      byte ptr [eax], al             
  0x0028E080  0001                    add      byte ptr [ecx], al             
  0x0028E082  3800                    cmp      byte ptr [eax], al             
  0x0028E084  93                      xchg     ebx, eax                       
                                        ; XREF: 0x0028E02D (cond_jump)
  0x0028E085  030d0000f956            add      ecx, dword ptr [0x56f90000]    
  0x0028E08B  0003                    add      byte ptr [ebx], al             
  0x0028E08D  0020                    add      byte ptr [eax], ah             
  0x0028E08F  0001                    add      byte ptr [ecx], al             
  0x0028E091  a5                      movsd    dword ptr es:[edi], dword ptr [esi] 
  0x0028E092  050000f461              add      eax, 0x61f40000                
  0x0028E097  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028E09A  0000                    add      byte ptr [eax], al             
  0x0028E09C  0009                    add      byte ptr [ecx], cl             
  0x0028E09E  3800                    cmp      byte ptr [eax], al             
  0x0028E0A0  93                      xchg     ebx, eax                       
  0x0028E0A1  030d0000f056            add      ecx, dword ptr [0x56f00000]    
  0x0028E0A7  00700b                  add      byte ptr [eax + 0xb], dh       
  0x0028E0AA  0000                    add      byte ptr [eax], al             
  0x0028E0AC  0300                    add      eax, dword ptr [eax]           
  0x0028E0AE  2000                    and      byte ptr [eax], al             
  0x0028E0B0  9f                      lahf                                    
  0x0028E0B1  f4                      hlt                                     
  0x0028E0B2  050000f444              add      eax, 0x44f40000                
  0x0028E0B7  0001                    add      byte ptr [ecx], al             
  0x0028E0B9  0000                    add      byte ptr [eax], al             
  0x0028E0BB  0000                    add      byte ptr [eax], al             
  0x0028E0BD  7044                    jo       0x28e103                       
  0x0028E0BF  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E0C2  0000                    add      byte ptr [eax], al             
  0x0028E0C4  13f4                    adc      esi, esp                       
  0x0028E0C6  61                      popal                                   
  0x0028E0C7  001e                    add      byte ptr [esi], bl             
  0x0028E0C9  0000                    add      byte ptr [eax], al             
  0x0028E0CB  0000                    add      byte ptr [eax], al             
  0x0028E0CD  61                      popal                                   
  0x0028E0CE  56                      push     esi                            
  0x0028E0CF  0000                    add      byte ptr [eax], al             
  0x0028E0D1  0138                    add      dword ptr [eax], edi           
  0x0028E0D3  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E0D9  002400                  add      byte ptr [eax + eax], ah       
  0x0028E0DC  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028E0DF  001e                    add      byte ptr [esi], bl             
  0x0028E0E1  0000                    add      byte ptr [eax], al             
  0x0028E0E3  0000                    add      byte ptr [eax], al             
  0x0028E0E5  f4                      hlt                                     
  0x0028E0E6  61                      popal                                   
  0x0028E0E7  001e                    add      byte ptr [esi], bl             
  0x0028E0E9  0000                    add      byte ptr [eax], al             
  0x0028E0EB  0000                    add      byte ptr [eax], al             
  0x0028E0ED  0138                    add      dword ptr [eax], edi           
  0x0028E0EF  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E0F6  56                      push     esi                            
  0x0028E0F7  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E0FA  0000                    add      byte ptr [eax], al             
  0x0028E0FC  80410100                add      byte ptr [ecx + 1], 0          
  0x0028E100  007056                  add      byte ptr [eax + 0x56], dh      
                                        ; XREF: 0x0028E0BD (cond_jump)
  0x0028E103  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E106  0000                    add      byte ptr [eax], al             
  0x0028E108  00f0                    add      al, dh                         
  0x0028E10A  56                      push     esi                            
  0x0028E10B  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028E10E  0000                    add      byte ptr [eax], al             
  0x0028E110  854301                  test     dword ptr [ebx + 1], eax       
  0x0028E113  004124                  add      byte ptr [ecx + 0x24], al      
  0x0028E116  0500000024              add      eax, 0x24000000                
  0x0028E11B  0000                    add      byte ptr [eax], al             
  0x0028E11D  7044                    jo       0x28e163                       
  0x0028E11F  001e                    add      byte ptr [esi], bl             
  0x0028E121  0000                    add      byte ptr [eax], al             
  0x0028E123  0000                    add      byte ptr [eax], al             
  0x0028E125  ee                      out      dx, al                         
  0x0028E126  2100                    and      dword ptr [eax], eax           
  0x0028E128  855001                  test     dword ptr [eax + 1], edx       
  0x0028E12B  000b                    add      byte ptr [ebx], cl             
  0x0028E12D  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028E12E  050000f044              add      eax, 0x44f00000                
  0x0028E133  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E136  0000                    add      byte ptr [eax], al             
  0x0028E138  40                      inc      eax                            
  0x0028E139  0020                    add      byte ptr [eax], ah             
  0x0028E13B  0000                    add      byte ptr [eax], al             
  0x0028E13D  e421                    in       al, 0x21                       
  0x0028E13F  0000                    add      byte ptr [eax], al             
  0x0028E141  7056                    jo       0x28e199                       
  0x0028E143  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E146  0000                    add      byte ptr [eax], al             
  0x0028E148  00f4                    add      ah, dh                         
  0x0028E14A  61                      popal                                   
  0x0028E14B  001e                    add      byte ptr [esi], bl             
  0x0028E14D  0000                    add      byte ptr [eax], al             
  0x0028E14F  0000                    add      byte ptr [eax], al             
  0x0028E151  98                      cwde                                    
  0x0028E152  2000                    and      byte ptr [eax], al             
  0x0028E154  93                      xchg     ebx, eax                       
  0x0028E155  030d00004e22            add      ecx, dword ptr [0x224e0000]    
  0x0028E15B  0000                    add      byte ptr [eax], al             
  0x0028E15D  7056                    jo       0x28e1b5                       
  0x0028E15F  00590b                  add      byte ptr [ecx + 0xb], bl       
  0x0028E162  0000                    add      byte ptr [eax], al             
  0x0028E164  00f4                    add      ah, dh                         
  0x0028E166  61                      popal                                   
  0x0028E167  001e                    add      byte ptr [esi], bl             
  0x0028E169  0000                    add      byte ptr [eax], al             
  0x0028E16B  0000                    add      byte ptr [eax], al             
  0x0028E16D  1038                    adc      byte ptr [eax], bh             
  0x0028E16F  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E175  f4                      hlt                                     
  0x0028E176  61                      popal                                   
  0x0028E177  001e                    add      byte ptr [esi], bl             
  0x0028E179  0000                    add      byte ptr [eax], al             
  0x0028E17B  0000                    add      byte ptr [eax], al             
  0x0028E17D  1038                    adc      byte ptr [eax], bh             
  0x0028E17F  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E186  56                      push     esi                            
  0x0028E187  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E18A  0000                    add      byte ptr [eax], al             
  0x0028E18C  80600100                and      byte ptr [eax + 1], 0          
  0x0028E190  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028E193  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E196  0000                    add      byte ptr [eax], al             
  0x0028E198  0000                    add      byte ptr [eax], al             
  0x0028E19A  2400                    and      al, 0                          
  0x0028E19C  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028E19F  001e                    add      byte ptr [esi], bl             
  0x0028E1A1  0000                    add      byte ptr [eax], al             
  0x0028E1A3  0000                    add      byte ptr [eax], al             
  0x0028E1A6  56                      push     esi                            
  0x0028E1A7  00700b                  add      byte ptr [eax + 0xb], dh       
  0x0028E1AA  0000                    add      byte ptr [eax], al             
  0x0028E1AC  06                      push     es                             
  0x0028E1AD  1d0c0000f0              sbb      eax, 0xf000000c                
  0x0028E1B2  44                      inc      esp                            
  0x0028E1B3  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E1B6  0000                    add      byte ptr [eax], al             
  0x0028E1B8  44                      inc      esp                            
  0x0028E1B9  0020                    add      byte ptr [eax], ah             
  0x0028E1BB  0006                    add      byte ptr [esi], al             
                                        ; XREF: 0x00288B60 (jump)
  0x0028E1BD  1c0c                    sbb      al, 0xc                        
  0x0028E1BF  0010                    add      byte ptr [eax], dl             
  0x0028E1C1  cc                      int3                                    
  0x0028E1C2  06                      push     es                             
  0x0028E1C3  000a                    add      byte ptr [edx], cl             
  0x0028E1C5  0000                    add      byte ptr [eax], al             
  0x0028E1C7  0000                    add      byte ptr [eax], al             
  0x0028E1C9  f4                      hlt                                     
  0x0028E1CA  61                      popal                                   
  0x0028E1CB  001e                    add      byte ptr [esi], bl             
  0x0028E1CD  0000                    add      byte ptr [eax], al             
  0x0028E1CF  0000                    add      byte ptr [eax], al             
  0x0028E1D1  0838                    or       byte ptr [eax], bh             
  0x0028E1D3  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E1DA  56                      push     esi                            
  0x0028E1DB  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E1DE  0000                    add      byte ptr [eax], al             
  0x0028E1E0  80480100                or       byte ptr [eax + 1], 0          
  0x0028E1E4  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028E1E7  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E1EA  0000                    add      byte ptr [eax], al             
  0x0028E1EC  00f0                    add      al, dh                         
  0x0028E1EE  56                      push     esi                            
  0x0028E1EF  00700b                  add      byte ptr [eax + 0xb], dh       
  0x0028E1F2  0000                    add      byte ptr [eax], al             
  0x0028E1F4  06                      push     es                             
  0x0028E1F5  1d0c0000f0              sbb      eax, 0xf000000c                
  0x0028E1FA  44                      inc      esp                            
  0x0028E1FB  005b0b                  add      byte ptr [ebx + 0xb], bl       
  0x0028E1FE  0000                    add      byte ptr [eax], al             
  0x0028E200  44                      inc      esp                            
  0x0028E201  0020                    add      byte ptr [eax], ah             
  0x0028E203  0000                    add      byte ptr [eax], al             
  0x0028E205  f4                      hlt                                     
  0x0028E206  61                      popal                                   
  0x0028E207  001e                    add      byte ptr [esi], bl             
  0x0028E209  0000                    add      byte ptr [eax], al             
  0x0028E20B  0000                    add      byte ptr [eax], al             
  0x0028E20D  98                      cwde                                    
  0x0028E20E  2100                    and      dword ptr [eax], eax           
  0x0028E210  93                      xchg     ebx, eax                       
  0x0028E211  030d0000f056            add      ecx, dword ptr [0x56f00000]    
  0x0028E217  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028E21A  0000                    add      byte ptr [eax], al             
  0x0028E21C  00f0                    add      al, dh                         
  0x0028E21E  44                      inc      esp                            
  0x0028E21F  00700b                  add      byte ptr [eax + 0xb], dh       
  0x0028E222  0000                    add      byte ptr [eax], al             
  0x0028E224  44                      inc      esp                            
  0x0028E225  0020                    add      byte ptr [eax], ah             
  0x0028E227  000f                    add      byte ptr [edi], cl             
  0x0028E229  0c05                    or       al, 5                          
  0x0028E22B  0000                    add      byte ptr [eax], al             
  0x0028E22E  56                      push     esi                            
  0x0028E22F  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028E232  0000                    add      byte ptr [eax], al             
  0x0028E234  0300                    add      eax, dword ptr [eax]           
  0x0028E236  2e000b                  add      byte ptr cs:[ebx], cl          
  0x0028E239  f4                      hlt                                     
  0x0028E23A  0500000024              add      eax, 0x24000000                
  0x0028E23F  0000                    add      byte ptr [eax], al             
  0x0028E241  7044                    jo       0x28e287                       
  0x0028E243  001e                    add      byte ptr [esi], bl             
  0x0028E245  0000                    add      byte ptr [eax], al             
  0x0028E247  0000                    add      byte ptr [eax], al             
  0x0028E249  f4                      hlt                                     
  0x0028E24A  61                      popal                                   
  0x0028E24B  001e                    add      byte ptr [esi], bl             
  0x0028E24D  0000                    add      byte ptr [eax], al             
  0x0028E24F  0000                    add      byte ptr [eax], al             
  0x0028E251  0838                    or       byte ptr [eax], bh             
  0x0028E253  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E25A  56                      push     esi                            
  0x0028E25B  00670b                  add      byte ptr [edi + 0xb], ah       
  0x0028E25E  0000                    add      byte ptr [eax], al             
  0x0028E260  844101                  test     byte ptr [ecx + 1], al         
  0x0028E263  0003                    add      byte ptr [ebx], al             
  0x0028E265  0020                    add      byte ptr [eax], ah             
  0x0028E267  000b                    add      byte ptr [ebx], cl             
  0x0028E269  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028E26A  050010cc06              add      eax, 0x6cc1000                 
  0x0028E26F  0009                    add      byte ptr [ecx], cl             
  0x0028E271  0000                    add      byte ptr [eax], al             
  0x0028E273  0013                    add      byte ptr [ebx], dl             
  0x0028E275  0020                    add      byte ptr [eax], ah             
  0x0028E277  0000                    add      byte ptr [eax], al             
  0x0028E279  7056                    jo       0x28e2d1                       
  0x0028E27B  0010                    add      byte ptr [eax], dl             
  0x0028E27D  0000                    add      byte ptr [eax], al             
  0x0028E27F  0000                    add      byte ptr [eax], al             
  0x0028E281  f4                      hlt                                     
  0x0028E282  61                      popal                                   
  0x0028E283  0010                    add      byte ptr [eax], dl             
  0x0028E285  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028E241 (cond_jump)
  0x0028E287  0000                    add      byte ptr [eax], al             
  0x0028E289  0838                    or       byte ptr [eax], bh             
  0x0028E28B  006103                  add      byte ptr [ecx + 3], ah         
  0x0028E28E  0d00000000              or       eax, 0                         
  0x0028E293  0000                    add      byte ptr [eax], al             
  0x0028E295  7045                    jo       0x28e2dc                       
  0x0028E297  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028E29A  0000                    add      byte ptr [eax], al             
  0x0028E29C  007057                  add      byte ptr [eax + 0x57], dh      
  0x0028E29F  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028E2A2  0000                    add      byte ptr [eax], al             
  0x0028E2A4  007062                  add      byte ptr [eax + 0x62], dh      
  0x0028E2A7  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028E2AA  0000                    add      byte ptr [eax], al             
  0x0028E2AC  22f4                    and      dh, ah                         
  0x0028E2AE  0500ffff00              add      eax, 0xffff00                  
  0x0028E2B3  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E2B6  0000                    add      byte ptr [eax], al             
  0x0028E2B8  0001                    add      byte ptr [ecx], al             
  0x0028E2BA  3900                    cmp      dword ptr [eax], eax           
  0x0028E2BC  007071                  add      byte ptr [eax + 0x71], dh      
  0x0028E2BF  0002                    add      byte ptr [edx], al             
  0x0028E2C1  0000                    add      byte ptr [eax], al             
  0x0028E2C3  0000                    add      byte ptr [eax], al             
  0x0028E2C5  7071                    jo       0x28e338                       
  0x0028E2C7  0003                    add      byte ptr [ebx], al             
  0x0028E2C9  0000                    add      byte ptr [eax], al             
  0x0028E2CB  0000                    add      byte ptr [eax], al             
  0x0028E2CD  7071                    jo       0x28e340                       
  0x0028E2CF  000400                  add      byte ptr [eax + eax], al       
  0x0028E2D2  0000                    add      byte ptr [eax], al             
  0x0028E2D4  0000                    add      byte ptr [eax], al             
  0x0028E2D6  360000                  add      byte ptr ss:[eax], al          
  0x0028E2DA  44                      inc      esp                            
  0x0028E2DB  00970b000010            add      byte ptr [edi + 0x1000000b], dl 
  0x0028E2E1  c406                    les      eax, ptr [esi]                 
  0x0028E2E3  001d00000000            add      byte ptr [0], bl               
  0x0028E2E9  f4                      hlt                                     
  0x0028E2EA  56                      push     esi                            
  0x0028E2EB  00a50b000000            add      byte ptr [ebp + 0xb], ah       
  0x0028E2F1  c422                    les      esp, ptr [edx]                 
  0x0028E2F3  004000                  add      byte ptr [eax], al             
  0x0028E2F6  2000                    and      byte ptr [eax], al             
  0x0028E2F8  0090210000e0            add      byte ptr [eax - 0x1fffffdf], dl 
  0x0028E2FE  7000                    jo       0x28e300                       
                                        ; XREF: 0x0028E2FE (cond_jump)
  0x0028E300  00c4                    add      ah, al                         
  0x0028E302  2200                    and      al, byte ptr [eax]             
  0x0028E304  00f4                    add      ah, dh                         
  0x0028E306  46                      inc      esi                            
  0x0028E307  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028E30D  f4                      hlt                                     
  0x0028E30E  44                      inc      esp                            
  0x0028E30F  0000                    add      byte ptr [eax], al             
  0x0028E311  0100                    add      dword ptr [eax], eax           
  0x0028E313  002e                    add      byte ptr [esi], ch             
  0x0028E315  1d0c004000              sbb      eax, 0x40000c                  
  0x0028E31A  2000                    and      byte ptr [eax], al             
  0x0028E31C  0090210000c4            add      byte ptr [eax - 0x3bffffdf], dl 
  0x0028E322  2200                    and      al, byte ptr [eax]             
  0x0028E324  00f4                    add      ah, dh                         
  0x0028E326  46                      inc      esi                            
  0x0028E327  00b5000000d0            add      byte ptr [ebp - 0x30000000], dh 
  0x0028E32E  44                      inc      esp                            
  0x0028E32F  00720b                  add      byte ptr [edx + 0xb], dh       
  0x0028E332  0000                    add      byte ptr [eax], al             
  0x0028E334  2e1d0c004000            sbb      eax, 0x40000c                  
  0x0028E33A  2000                    and      byte ptr [eax], al             
  0x0028E33C  009521000070            add      byte ptr [ebp + 0x70000021], dl 
  0x0028E342  6600410b                add      byte ptr [ecx + 0xb], al       
  0x0028E346  0000                    add      byte ptr [eax], al             
  0x0028E348  8b040d0000f066          mov      eax, dword ptr [ecx + 0x66f00000] 
  0x0028E34F  00410b                  add      byte ptr [ecx + 0xb], al       
  0x0028E352  0000                    add      byte ptr [eax], al             
  0x0028E354  005e20                  add      byte ptr [esi + 0x20], bl      
  0x0028E357  0000                    add      byte ptr [eax], al             
  0x0028E35A  56                      push     esi                            
  0x0028E35B  007e0b                  add      byte ptr [esi + 0xb], bh       
  0x0028E35E  0000                    add      byte ptr [eax], al             
  0x0028E360  0300                    add      eax, dword ptr [eax]           
  0x0028E362  2000                    and      byte ptr [eax], al             
  0x0028E364  07                      pop      es                             
  0x0028E365  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028E366  0500000738              add      eax, 0x38070000                
  0x0028E36B  0000                    add      byte ptr [eax], al             
  0x0028E36D  f4                      hlt                                     
  0x0028E36E  60                      pushal                                  
  0x0028E36F  008904000000            add      byte ptr [ecx + 4], cl         
  0x0028E375  f4                      hlt                                     
  0x0028E376  650039                  add      byte ptr gs:[ecx], bh          
  0x0028E379  0b00                    or       eax, dword ptr [eax]           
  0x0028E37B  008b040d000c            add      byte ptr [ebx + 0xc000d04], cl 
  0x0028E381  0000                    add      byte ptr [eax], al             
  0x0028E383  0000                    add      byte ptr [eax], al             
  0x0028E386  6200                    bound    eax, qword ptr [eax]           
  0x0028E388  55                      push     ebp                            
  0x0028E389  0b00                    or       eax, dword ptr [eax]           
  0x0028E38B  0022                    add      byte ptr [edx], ah             
  0x0028E38E  0500470b00              add      eax, 0xb4700                   
  0x0028E393  0000                    add      byte ptr [eax], al             
  0x0028E396  57                      push     edi                            
  0x0028E397  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028E39A  0000                    add      byte ptr [eax], al             
  0x0028E39C  00f0                    add      al, dh                         
  0x0028E39E  45                      inc      ebp                            
  0x0028E39F  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028E3A2  0000                    add      byte ptr [eax], al             
  0x0028E3A4  0000                    add      byte ptr [eax], al             
  0x0028E3A6  2400                    and      al, 0                          
  0x0028E3A8  007044                  add      byte ptr [eax + 0x44], dh      
  0x0028E3AB  001e                    add      byte ptr [esi], bl             
  0x0028E3AD  0000                    add      byte ptr [eax], al             
  0x0028E3AF  0000                    add      byte ptr [eax], al             
  0x0028E3B2  56                      push     esi                            
  0x0028E3B3  006e0b                  add      byte ptr [esi + 0xb], ch       
  0x0028E3B6  0000                    add      byte ptr [eax], al             
  0x0028E3B8  855001                  test     dword ptr [eax + 1], edx       
  0x0028E3BB  0009                    add      byte ptr [ecx], cl             
  0x0028E3BD  94                      xchg     esp, eax                       
  0x0028E3BE  0500845001              add      eax, 0x1508400                 
  0x0028E3C3  0000                    add      byte ptr [eax], al             
  0x0028E3C5  7054                    jo       0x28e41b                       
  0x0028E3C7  006e0b                  add      byte ptr [esi + 0xb], ch       
  0x0028E3CA  0000                    add      byte ptr [eax], al             
  0x0028E3CC  00f4                    add      ah, dh                         
  0x0028E3CE  61                      popal                                   
  0x0028E3CF  001e                    add      byte ptr [esi], bl             
  0x0028E3D1  0000                    add      byte ptr [eax], al             
  0x0028E3D3  0000                    add      byte ptr [eax], al             
  0x0028E3D5  1038                    adc      byte ptr [eax], bh             
  0x0028E3D7  0093030d00d5            add      byte ptr [ebx - 0x2afff2fd], dl 
  0x0028E3DD  0f05                    syscall                                 
  0x0028E3DF  0003                    add      byte ptr [ebx], al             
  0x0028E3E1  0020                    add      byte ptr [eax], ah             
  0x0028E3E3  0005a4050000            add      byte ptr [0x5a4], al           
  0x0028E3E9  f4                      hlt                                     
  0x0028E3EA  61                      popal                                   
  0x0028E3EB  001e                    add      byte ptr [esi], bl             
  0x0028E3ED  0000                    add      byte ptr [eax], al             
  0x0028E3EF  0000                    add      byte ptr [eax], al             
  0x0028E3F1  98                      cwde                                    
  0x0028E3F2  2100                    and      dword ptr [eax], eax           
  0x0028E3F4  93                      xchg     ebx, eax                       
  0x0028E3F5  030d00130020            add      ecx, dword ptr [0x20001300]    
  0x0028E3FB  0000                    add      byte ptr [eax], al             
  0x0028E3FD  7056                    jo       0x28e455                       
  0x0028E3FF  0001                    add      byte ptr [ecx], al             
  0x0028E401  0000                    add      byte ptr [eax], al             
  0x0028E403  0000                    add      byte ptr [eax], al             
  0x0028E405  7056                    jo       0x28e45d                       
  0x0028E407  001e                    add      byte ptr [esi], bl             
  0x0028E409  0000                    add      byte ptr [eax], al             
  0x0028E40B  0000                    add      byte ptr [eax], al             
  0x0028E40D  f4                      hlt                                     
  0x0028E40E  61                      popal                                   
  0x0028E40F  001e                    add      byte ptr [esi], bl             
  0x0028E411  0000                    add      byte ptr [eax], al             
  0x0028E413  0000                    add      byte ptr [eax], al             
  0x0028E415  0138                    add      dword ptr [eax], edi           
  0x0028E417  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E41D  f4                      hlt                                     
  0x0028E41E  61                      popal                                   
  0x0028E41F  0001                    add      byte ptr [ecx], al             
  0x0028E421  0000                    add      byte ptr [eax], al             
  0x0028E423  0000                    add      byte ptr [eax], al             
  0x0028E425  0138                    add      dword ptr [eax], edi           
  0x0028E427  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E42D  f4                      hlt                                     
  0x0028E42E  61                      popal                                   
  0x0028E42F  001e                    add      byte ptr [esi], bl             
  0x0028E431  0000                    add      byte ptr [eax], al             
  0x0028E433  0000                    add      byte ptr [eax], al             
  0x0028E435  1038                    adc      byte ptr [eax], bh             
  0x0028E437  0093030d0000            add      byte ptr [ebx + 0xd03], dl     
  0x0028E43D  7045                    jo       0x28e484                       
  0x0028E43F  00560b                  add      byte ptr [esi + 0xb], dl       
  0x0028E442  0000                    add      byte ptr [eax], al             
  0x0028E444  007057                  add      byte ptr [eax + 0x57], dh      
  0x0028E447  00570b                  add      byte ptr [edi + 0xb], dl       
  0x0028E44A  0000                    add      byte ptr [eax], al             
  0x0028E44C  007062                  add      byte ptr [eax + 0x62], dh      
  0x0028E44F  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028E452  0000                    add      byte ptr [eax], al             
  0x0028E454  22f4                    and      dh, ah                         
  0x0028E456  0500ffff00              add      eax, 0xffff00                  
  0x0028E45B  0000                    add      byte ptr [eax], al             
  0x0028E45E  56                      push     esi                            
  0x0028E45F  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028E462  0000                    add      byte ptr [eax], al             
  0x0028E464  00f0                    add      al, dh                         
  0x0028E466  44                      inc      esp                            
  0x0028E467  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E46A  0000                    add      byte ptr [eax], al             
  0x0028E46C  44                      inc      esp                            
  0x0028E46D  0020                    add      byte ptr [eax], ah             
  0x0028E46F  0000                    add      byte ptr [eax], al             
  0x0028E471  c421                    les      esp, ptr [ecx]                 
  0x0028E473  0000                    add      byte ptr [eax], al             
  0x0028E475  f4                      hlt                                     
  0x0028E476  45                      inc      ebp                            
  0x0028E477  0010                    add      byte ptr [eax], dl             
  0x0028E479  0000                    add      byte ptr [eax], al             
  0x0028E47B  00a00020002e            add      byte ptr [eax + 0x2e002000], ah 
  0x0028E481  1d0c0000f0              sbb      eax, 0xf000000c                
  0x0028E486  44                      inc      esp                            
  0x0028E487  009d0b000040            add      byte ptr [ebp + 0x4000000b], bl 
  0x0028E48D  0020                    add      byte ptr [eax], ah             
  0x0028E48F  0000                    add      byte ptr [eax], al             
  0x0028E491  7056                    jo       0x28e4e9                       
  0x0028E493  009d0b00000c            add      byte ptr [ebp + 0xc00000b], bl 
  0x0028E499  0000                    add      byte ptr [eax], al             
  0x0028E49B  0000                    add      byte ptr [eax], al             
  0x0028E49E  56                      push     esi                            
  0x0028E49F  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028E4A2  0000                    add      byte ptr [eax], al             
  0x0028E4A4  854001                  test     dword ptr [eax + 1], eax       
  0x0028E4A7  0010                    add      byte ptr [eax], dl             
  0x0028E4A9  2405                    and      al, 5                          
  0x0028E4AB  0000                    add      byte ptr [eax], al             
  0x0028E4AE  60                      pushal                                  
  0x0028E4AF  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E4B2  0000                    add      byte ptr [eax], al             
  0x0028E4B4  005820                  add      byte ptr [eax + 0x20], bl      
  0x0028E4B7  0020                    add      byte ptr [eax], ah             
  0x0028E4BA  0500470b00              add      eax, 0xb4700                   
  0x0028E4BF  0000                    add      byte ptr [eax], al             
  0x0028E4C2  56                      push     esi                            
  0x0028E4C3  00580b                  add      byte ptr [eax + 0xb], bl       
  0x0028E4C6  0000                    add      byte ptr [eax], al             
  0x0028E4C8  844101                  test     byte ptr [ecx + 1], al         
  0x0028E4CB  001b                    add      byte ptr [ebx], bl             
  0x0028E4CD  d821                    fsub     dword ptr [ecx]                
  0x0028E4CF  00b3030d0000            add      byte ptr [ebx + 0xd03], dh     
  0x0028E4D5  7055                    jo       0x28e52c                       
  0x0028E4D7  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E4DA  0000                    add      byte ptr [eax], al             
  0x0028E4DC  20f4                    and      ah, dh                         
  0x0028E4DE  0500ffff00              add      eax, 0xffff00                  
  0x0028E4E3  00da                    add      dl, bl                         
  0x0028E4E5  0c05                    or       al, 5                          
  0x0028E4E7  008541010003            add      byte ptr [ebp + 0x3000141], al 
  0x0028E4ED  a4                      movsb    byte ptr es:[edi], byte ptr [esi] 
  0x0028E4EE  0500854201              add      eax, 0x1428500                 
  0x0028E4F3  000f                    add      byte ptr [edi], cl             
  0x0028E4F5  2405                    and      al, 5                          
  0x0028E4F7  0000                    add      byte ptr [eax], al             
  0x0028E4FA  60                      pushal                                  
  0x0028E4FB  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E4FE  0000                    add      byte ptr [eax], al             
  0x0028E500  20f0                    and      al, dh                         
  0x0028E502  0500470b00              add      eax, 0xb4700                   
  0x0028E507  001b                    add      byte ptr [ebx], bl             
  0x0028E50A  7000                    jo       0x28e50c                       
                                        ; XREF: 0x0028E50A (cond_jump)
  0x0028E50C  58                      pop      eax                            
  0x0028E50D  0b00                    or       eax, dword ptr [eax]           
  0x0028E50F  0000                    add      byte ptr [eax], al             
  0x0028E512  55                      push     ebp                            
  0x0028E513  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E516  0000                    add      byte ptr [eax], al             
  0x0028E518  b303                    mov      bl, 3                          
  0x0028E51A  0d00007055              or       eax, 0x55700000                
  0x0028E51F  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E522  0000                    add      byte ptr [eax], al             
  0x0028E524  20f4                    and      ah, dh                         
  0x0028E526  0500ffff00              add      eax, 0xffff00                  
  0x0028E52B  00c8                    add      al, cl                         
  0x0028E52D  0c05                    or       al, 5                          
  0x0028E52F  008543010082            add      byte ptr [ebp - 0x7dfffebd], al 
  0x0028E535  2405                    and      al, 5                          
  0x0028E537  0000                    add      byte ptr [eax], al             
  0x0028E53A  56                      push     esi                            
  0x0028E53B  00590b                  add      byte ptr [ecx + 0xb], bl       
  0x0028E53E  0000                    add      byte ptr [eax], al             
  0x0028E540  00f0                    add      al, dh                         
  0x0028E542  44                      inc      esp                            
  0x0028E543  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E546  0000                    add      byte ptr [eax], al             
  0x0028E548  44                      inc      esp                            
  0x0028E549  0020                    add      byte ptr [eax], ah             
  0x0028E54B  008041010000            add      byte ptr [eax + 0x141], al     
  0x0028E551  d821                    fsub     dword ptr [ecx]                
  0x0028E553  0000                    add      byte ptr [eax], al             
  0x0028E555  90                      nop                                     
  0x0028E556  2000                    and      byte ptr [eax], al             
  0x0028E558  20f0                    and      al, dh                         
  0x0028E55A  0500470b00              add      eax, 0xb4700                   
  0x0028E55F  0000                    add      byte ptr [eax], al             
  0x0028E562  55                      push     ebp                            
  0x0028E563  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E566  0000                    add      byte ptr [eax], al             
  0x0028E568  b303                    mov      bl, 3                          
  0x0028E56A  0d00911e0c              or       eax, 0xc1e9100                 
  0x0028E56F  0000                    add      byte ptr [eax], al             
  0x0028E572  61                      popal                                   
  0x0028E573  00590b                  add      byte ptr [ecx + 0xb], bl       
  0x0028E576  0000                    add      byte ptr [eax], al             
  0x0028E578  006155                  add      byte ptr [ecx + 0x55], ah      
  0x0028E57B  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x0028E582  44                      inc      esp                            
  0x0028E583  009d0b000000            add      byte ptr [ebp + 0xb], bl       
  0x0028E589  082500a00020            or       byte ptr [0x2000a000], ah      
  0x0028E58F  0000                    add      byte ptr [eax], al             
  0x0028E592  44                      inc      esp                            
  0x0028E593  009b0b000041            add      byte ptr [ebx + 0x4100000b], bl 
  0x0028E599  c421                    les      esp, ptr [ecx]                 
  0x0028E59B  00440020                add      byte ptr [eax + eax + 0x20], al 
  0x0028E59F  0000                    add      byte ptr [eax], al             
  0x0028E5A1  0423                    add      al, 0x23                       
  0x0028E5A3  00440020                add      byte ptr [eax + eax + 0x20], al 
  0x0028E5A7  0000                    add      byte ptr [eax], al             
  0x0028E5A9  9a200000d82100          lcall    0x21, 0xd8000020               
  0x0028E5B0  00f0                    add      al, dh                         
  0x0028E5B2  56                      push     esi                            
  0x0028E5B3  00590b                  add      byte ptr [ecx + 0xb], bl       
  0x0028E5B6  0000                    add      byte ptr [eax], al             
  0x0028E5B8  80410100                add      byte ptr [ecx + 1], 0          
  0x0028E5BC  00d0                    add      al, dl                         
  0x0028E5BE  2100                    and      dword ptr [eax], eax           
  0x0028E5C0  ca030d                  retf     0xd03                          
  0x0028E5C3  0000                    add      byte ptr [eax], al             
  0x0028E5C6  56                      push     esi                            
  0x0028E5C7  00590b                  add      byte ptr [ecx + 0xb], bl       
  0x0028E5CA  0000                    add      byte ptr [eax], al             
  0x0028E5CC  80410100                add      byte ptr [ecx + 1], 0          
  0x0028E5D0  00d0                    add      al, dl                         
  0x0028E5D2  2100                    and      dword ptr [eax], eax           
  0x0028E5D4  91                      xchg     ecx, eax                       
  0x0028E5D5  1e                      push     ds                             
  0x0028E5D6  0c00                    or       al, 0                          
  0x0028E5D8  006055                  add      byte ptr [eax + 0x55], ah      
  0x0028E5DB  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x0028E5E2  56                      push     esi                            
  0x0028E5E3  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028E5E6  0000                    add      byte ptr [eax], al             
  0x0028E5E8  00f0                    add      al, dh                         
  0x0028E5EA  44                      inc      esp                            
  0x0028E5EB  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E5EE  0000                    add      byte ptr [eax], al             
  0x0028E5F0  44                      inc      esp                            
  0x0028E5F1  0020                    add      byte ptr [eax], ah             
  0x0028E5F3  0000                    add      byte ptr [eax], al             
  0x0028E5F5  44                      inc      esp                            
  0x0028E5F6  2300                    and      eax, dword ptr [eax]           
  0x0028E5F8  44                      inc      esp                            
  0x0028E5F9  0020                    add      byte ptr [eax], ah             
  0x0028E5FB  0000                    add      byte ptr [eax], al             
  0x0028E5FD  0423                    add      al, 0x23                       
  0x0028E5FF  00440020                add      byte ptr [eax + eax + 0x20], al 
  0x0028E603  0000                    add      byte ptr [eax], al             
  0x0028E605  d821                    fsub     dword ptr [ecx]                
  0x0028E607  0000                    add      byte ptr [eax], al             
  0x0028E60A  56                      push     esi                            
  0x0028E60B  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E60E  0000                    add      byte ptr [eax], al             
  0x0028E610  40                      inc      eax                            
  0x0028E611  0020                    add      byte ptr [eax], ah             
  0x0028E613  0000                    add      byte ptr [eax], al             
  0x0028E615  44                      inc      esp                            
  0x0028E616  2300                    and      eax, dword ptr [eax]           
  0x0028E618  40                      inc      eax                            
  0x0028E619  0020                    add      byte ptr [eax], ah             
  0x0028E61B  0000                    add      byte ptr [eax], al             
  0x0028E61D  d021                    shl      byte ptr [ecx], 1              
  0x0028E61F  001b                    add      byte ptr [ebx], bl             
  0x0028E621  0020                    add      byte ptr [eax], ah             
  0x0028E623  00b3030d0000            add      byte ptr [ebx + 0xd03], dh     
  0x0028E629  7055                    jo       0x28e680                       
  0x0028E62B  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E62E  0000                    add      byte ptr [eax], al             
  0x0028E630  20f4                    and      ah, dh                         
  0x0028E632  0500ffff00              add      eax, 0xffff00                  
  0x0028E637  00450c                  add      byte ptr [ebp + 0xc], al       
  0x0028E63A  0500854401              add      eax, 0x1448500                 
  0x0028E63F  000f                    add      byte ptr [edi], cl             
  0x0028E641  2405                    and      al, 5                          
  0x0028E643  0020                    add      byte ptr [eax], ah             
  0x0028E646  0500470b00              add      eax, 0xb4700                   
  0x0028E64B  0000                    add      byte ptr [eax], al             
  0x0028E64E  60                      pushal                                  
  0x0028E64F  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E652  0000                    add      byte ptr [eax], al             
  0x0028E654  00f0                    add      al, dh                         
  0x0028E656  7000                    jo       0x28e658                       
                                        ; XREF: 0x0028E656 (cond_jump)
  0x0028E658  58                      pop      eax                            
  0x0028E659  0b00                    or       eax, dword ptr [eax]           
  0x0028E65B  0000                    add      byte ptr [eax], al             
  0x0028E65E  57                      push     edi                            
  0x0028E65F  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E662  0000                    add      byte ptr [eax], al             
  0x0028E664  b303                    mov      bl, 3                          
  0x0028E666  0d00007055              or       eax, 0x55700000                
  0x0028E66B  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E66E  0000                    add      byte ptr [eax], al             
  0x0028E670  20f4                    and      ah, dh                         
  0x0028E672  0500ffff00              add      eax, 0xffff00                  
  0x0028E677  00150c050085            add      byte ptr [0x8500050c], dl      
  0x0028E67D  45                      inc      ebp                            
  0x0028E67E  0100                    add      dword ptr [eax], eax           
                                        ; XREF: 0x0028E629 (cond_jump)
  0x0028E680  1324050020f005          adc      esp, dword ptr [eax + 0x5f02000] 
  0x0028E687  00470b                  add      byte ptr [edi + 0xb], al       
  0x0028E68A  0000                    add      byte ptr [eax], al             
  0x0028E68C  00f0                    add      al, dh                         
  0x0028E68E  60                      pushal                                  
  0x0028E68F  00450b                  add      byte ptr [ebp + 0xb], al       
  0x0028E692  0000                    add      byte ptr [eax], al             
  0x0028E694  00f0                    add      al, dh                         
  0x0028E696  7000                    jo       0x28e698                       
                                        ; XREF: 0x0028E696 (cond_jump)
  0x0028E698  58                      pop      eax                            
  0x0028E699  0b00                    or       eax, dword ptr [eax]           
  0x0028E69B  0000                    add      byte ptr [eax], al             
  0x0028E69E  57                      push     edi                            
  0x0028E69F  005a0b                  add      byte ptr [edx + 0xb], bl       
  0x0028E6A2  0000                    add      byte ptr [eax], al             
  0x0028E6A4  b303                    mov      bl, 3                          
  0x0028E6A6  0d0000f056              or       eax, 0x56f00000                
  0x0028E6AB  00550b                  add      byte ptr [ebp + 0xb], dl       
  0x0028E6AE  0000                    add      byte ptr [eax], al             
  0x0028E6B0  844101                  test     byte ptr [ecx + 1], al         
  0x0028E6B3  0000                    add      byte ptr [eax], al             
  0x0028E6B5  d021                    shl      byte ptr [ecx], 1              
  0x0028E6B7  00911e0c0000            add      byte ptr [ecx + 0xc1e], dl     
  0x0028E6BD  60                      pushal                                  
  0x0028E6BE  55                      push     ebp                            
  0x0028E6BF  00911c0c0020            add      byte ptr [ecx + 0x20000c1c], dl 
  0x0028E6C5  f4                      hlt                                     
  0x0028E6C6  0500ffff00              add      eax, 0xffff00                  
  0x0028E6CB  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E6CE  0000                    add      byte ptr [eax], al             
  0x0028E6D0  00f4                    add      ah, dh                         
  0x0028E6D2  56                      push     esi                            
  0x0028E6D3  001500000000            add      byte ptr [0], dl               
  0x0028E6D9  f4                      hlt                                     
  0x0028E6DA  57                      push     edi                            
  0x0028E6DB  0001                    add      byte ptr [ecx], al             
  0x0028E6DD  0000                    add      byte ptr [eax], al             
  0x0028E6DF  0000                    add      byte ptr [eax], al             
  0x0028E6E1  f4                      hlt                                     
  0x0028E6E2  7000                    jo       0x28e6e4                       
                                        ; XREF: 0x0028E6E2 (cond_jump)
  0x0028E6E4  90                      nop                                     
  0x0028E6E5  0300                    add      eax, dword ptr [eax]           
  0x0028E6E7  0000                    add      byte ptr [eax], al             
  0x0028E6E9  0039                    add      byte ptr [ecx], bh             
  0x0028E6EB  0000                    add      byte ptr [eax], al             
  0x0028E6ED  f4                      hlt                                     
  0x0028E6EE  60                      pushal                                  
  0x0028E6EF  0000                    add      byte ptr [eax], al             
  0x0028E6F1  0100                    add      dword ptr [eax], eax           
  0x0028E6F3  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028E6F9  0100                    add      dword ptr [eax], eax           
  0x0028E6FB  0003                    add      byte ptr [ebx], al             
  0x0028E6FD  0020                    add      byte ptr [eax], ah             
  0x0028E6FF  0000                    add      byte ptr [eax], al             
  0x0028E701  2405                    and      al, 5                          
  0x0028E703  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E706  0000                    add      byte ptr [eax], al             
  0x0028E708  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028E70B  00fd                    add      ch, bh                         
  0x0028E70D  0000                    add      byte ptr [eax], al             
  0x0028E70F  0000                    add      byte ptr [eax], al             
  0x0028E711  7044                    jo       0x28e757                       
  0x0028E713  00fe                    add      dh, bh                         
  0x0028E715  0000                    add      byte ptr [eax], al             
  0x0028E717  0000                    add      byte ptr [eax], al             
  0x0028E719  7060                    jo       0x28e77b                       
  0x0028E71B  00ff                    add      bh, bh                         
  0x0028E71D  0000                    add      byte ptr [eax], al             
  0x0028E71F  0003                    add      byte ptr [ebx], al             
  0x0028E721  0020                    add      byte ptr [eax], ah             
  0x0028E723  0010                    add      byte ptr [eax], dl             
  0x0028E725  2405                    and      al, 5                          
  0x0028E727  0000                    add      byte ptr [eax], al             
  0x0028E729  f4                      hlt                                     
  0x0028E72A  56                      push     esi                            
  0x0028E72B  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E72E  0000                    add      byte ptr [eax], al             
  0x0028E730  00f4                    add      ah, dh                         
  0x0028E732  7000                    jo       0x28e734                       
                                        ; XREF: 0x0028E732 (cond_jump)
  0x0028E734  da0500000000            fiadd    dword ptr [0]                  
  0x0028E73A  3900                    cmp      dword ptr [eax], eax           
  0x0028E73C  80f00b                  xor      al, 0xb                        
  0x0028E73F  008001000003            add      byte ptr [eax + 0x3000001], al 
  0x0028E745  0020                    add      byte ptr [eax], ah             
  0x0028E747  0000                    add      byte ptr [eax], al             
  0x0028E749  2405                    and      al, 5                          
  0x0028E74B  0000                    add      byte ptr [eax], al             
  0x0028E74E  56                      push     esi                            
  0x0028E74F  00fd                    add      ch, bh                         
  0x0028E751  0000                    add      byte ptr [eax], al             
  0x0028E753  0000                    add      byte ptr [eax], al             
  0x0028E756  60                      pushal                                  
                                        ; XREF: 0x0028E711 (cond_jump)
  0x0028E757  00ff                    add      bh, bh                         
  0x0028E759  0000                    add      byte ptr [eax], al             
  0x0028E75B  0000                    add      byte ptr [eax], al             
  0x0028E75E  44                      inc      esp                            
  0x0028E75F  00fe                    add      dh, bh                         
  0x0028E761  0000                    add      byte ptr [eax], al             
  0x0028E763  0003                    add      byte ptr [ebx], al             
  0x0028E765  f4                      hlt                                     
  0x0028E766  45                      inc      ebp                            
  0x0028E767  00da                    add      dl, bl                         
  0x0028E769  0500000324              add      eax, 0x24030000                
  0x0028E76E  0500007045              add      eax, 0x45700000                
  0x0028E773  00480b                  add      byte ptr [eax + 0xb], cl       
  0x0028E776  0000                    add      byte ptr [eax], al             
  0x0028E778  0098200000f0            add      byte ptr [eax - 0xfffffe0], bl 
  0x0028E77E  56                      push     esi                            
  0x0028E77F  00480b                  add      byte ptr [eax + 0xb], cl       
  0x0028E782  0000                    add      byte ptr [eax], al             
  0x0028E784  40                      inc      eax                            
  0x0028E785  99                      cdq                                     
  0x0028E786  2100                    and      dword ptr [eax], eax           
  0x0028E788  007054                  add      byte ptr [eax + 0x54], dh      
  0x0028E78B  00480b                  add      byte ptr [eax + 0xb], cl       
  0x0028E78E  0000                    add      byte ptr [eax], al             
  0x0028E790  00f4                    add      ah, dh                         
  0x0028E792  56                      push     esi                            
  0x0028E793  0009                    add      byte ptr [ecx], cl             
  0x0028E795  0000                    add      byte ptr [eax], al             
  0x0028E797  0000                    add      byte ptr [eax], al             
  0x0028E799  f4                      hlt                                     
  0x0028E79A  57                      push     edi                            
  0x0028E79B  0002                    add      byte ptr [edx], al             
  0x0028E79D  0000                    add      byte ptr [eax], al             
  0x0028E79F  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028E7A5  0100                    add      dword ptr [eax], eax           
  0x0028E7A7  0003                    add      byte ptr [ebx], al             
  0x0028E7A9  0020                    add      byte ptr [eax], ah             
  0x0028E7AB  0000                    add      byte ptr [eax], al             
  0x0028E7AD  2405                    and      al, 5                          
  0x0028E7AF  0000                    add      byte ptr [eax], al             
  0x0028E7B2  56                      push     esi                            
  0x0028E7B3  00fd                    add      ch, bh                         
  0x0028E7B5  0000                    add      byte ptr [eax], al             
  0x0028E7B7  008545010009            add      byte ptr [ebp + 0x9000145], al 
  0x0028E7BD  2405                    and      al, 5                          
  0x0028E7BF  0000                    add      byte ptr [eax], al             
  0x0028E7C1  f4                      hlt                                     
  0x0028E7C2  56                      push     esi                            
  0x0028E7C3  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E7C6  0000                    add      byte ptr [eax], al             
  0x0028E7C8  00f4                    add      ah, dh                         
  0x0028E7CA  7000                    jo       0x28e7cc                       
                                        ; XREF: 0x0028E7CA (cond_jump)
  0x0028E7CC  2201                    and      al, byte ptr [ecx]             
  0x0028E7CE  0000                    add      byte ptr [eax], al             
  0x0028E7D0  00f4                    add      ah, dh                         
  0x0028E7D2  7100                    jno      0x28e7d4                       
                                        ; XREF: 0x0028E7D2 (cond_jump)
  0x0028E7D4  de0a                    fimul    word ptr [edx]                 
  0x0028E7D6  0000                    add      byte ptr [eax], al             
  0x0028E7D8  80f00b                  xor      al, 0xb                        
  0x0028E7DB  008001000000            add      byte ptr [eax + 1], al         
  0x0028E7E1  f4                      hlt                                     
  0x0028E7E2  56                      push     esi                            
  0x0028E7E3  0019                    add      byte ptr [ecx], bl             
  0x0028E7E5  0000                    add      byte ptr [eax], al             
  0x0028E7E7  0000                    add      byte ptr [eax], al             
  0x0028E7E9  f4                      hlt                                     
  0x0028E7EA  57                      push     edi                            
  0x0028E7EB  0002                    add      byte ptr [edx], al             
  0x0028E7ED  0000                    add      byte ptr [eax], al             
  0x0028E7EF  0000                    add      byte ptr [eax], al             
  0x0028E7F1  0039                    add      byte ptr [ecx], bh             
  0x0028E7F3  0000                    add      byte ptr [eax], al             
  0x0028E7F5  f4                      hlt                                     
  0x0028E7F6  7000                    jo       0x28e7f8                       
                                        ; XREF: 0x0028E7F6 (cond_jump)
  0x0028E7F8  800000                  add      byte ptr [eax], 0              
  0x0028E7FB  0000                    add      byte ptr [eax], al             
  0x0028E7FD  f4                      hlt                                     
  0x0028E7FE  60                      pushal                                  
  0x0028E7FF  00400b                  add      byte ptr [eax + 0xb], al       
  0x0028E802  0000                    add      byte ptr [eax], al             
  0x0028E804  80f00b                  xor      al, 0xb                        
  0x0028E807  008001000003            add      byte ptr [eax + 0x3000001], al 
  0x0028E80D  0020                    add      byte ptr [eax], ah             
  0x0028E80F  0000                    add      byte ptr [eax], al             
  0x0028E811  2405                    and      al, 5                          
  0x0028E813  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E816  0000                    add      byte ptr [eax], al             
  0x0028E818  00f4                    add      ah, dh                         
  0x0028E81A  56                      push     esi                            
  0x0028E81B  0019                    add      byte ptr [ecx], bl             
  0x0028E81D  0000                    add      byte ptr [eax], al             
  0x0028E81F  0000                    add      byte ptr [eax], al             
  0x0028E821  f4                      hlt                                     
  0x0028E822  57                      push     edi                            
  0x0028E823  0000                    add      byte ptr [eax], al             
  0x0028E825  0000                    add      byte ptr [eax], al             
  0x0028E827  0000                    add      byte ptr [eax], al             
  0x0028E829  f4                      hlt                                     
  0x0028E82A  7000                    jo       0x28e82c                       
                                        ; XREF: 0x0028E82A (cond_jump)
  0x0028E82C  800000                  add      byte ptr [eax], 0              
  0x0028E82F  0080f00b0080            add      byte ptr [eax - 0x7ffff410], al 
  0x0028E835  0100                    add      dword ptr [eax], eax           
  0x0028E837  0003                    add      byte ptr [ebx], al             
  0x0028E839  0020                    add      byte ptr [eax], ah             
  0x0028E83B  0000                    add      byte ptr [eax], al             
  0x0028E83D  2405                    and      al, 5                          
  0x0028E83F  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E842  0000                    add      byte ptr [eax], al             
  0x0028E844  0000                    add      byte ptr [eax], al             
  0x0028E846  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x001F74A1 (data_imm)
  0x0028E848  40                      inc      eax                            
  0x0028E849  1bd0                    sbb      edx, eax                       
  0x0028E84B  00bc0000007201          add      byte ptr [eax + eax + 0x1720000], bh 
  0x0028E852  0500265e7d              add      eax, 0x7d5e2600                
  0x0028E857  0000                    add      byte ptr [eax], al             
  0x0028E859  7060                    jo       0x28e8bb                       
  0x0028E85B  0000                    add      byte ptr [eax], al             
  0x0028E85D  07                      pop      es                             
  0x0028E85E  0000                    add      byte ptr [eax], al             
  0x0028E860  00f4                    add      ah, dh                         
  0x0028E862  56                      push     esi                            
  0x0028E863  0007                    add      byte ptr [edi], al             
  0x0028E865  0000                    add      byte ptr [eax], al             
  0x0028E867  0000                    add      byte ptr [eax], al             
  0x0028E869  f4                      hlt                                     
  0x0028E86A  60                      pushal                                  
  0x0028E86B  0000                    add      byte ptr [eax], al             
  0x0028E86D  0000                    add      byte ptr [eax], al             
  0x0028E86F  0000                    add      byte ptr [eax], al             
  0x0028E871  f4                      hlt                                     
  0x0028E872  7000                    jo       0x28e874                       
                                        ; XREF: 0x0028E872 (cond_jump)
  0x0028E874  0001                    add      byte ptr [ecx], al             
  0x0028E876  0000                    add      byte ptr [eax], al             
  0x0028E878  0000                    add      byte ptr [eax], al             
  0x0028E87A  3900                    cmp      dword ptr [eax], eax           
  0x0028E87C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028E87F  0000                    add      byte ptr [eax], al             
  0x0028E881  f4                      hlt                                     
  0x0028E882  56                      push     esi                            
  0x0028E883  0007                    add      byte ptr [edi], al             
  0x0028E885  0000                    add      byte ptr [eax], al             
  0x0028E887  0000                    add      byte ptr [eax], al             
  0x0028E889  f4                      hlt                                     
  0x0028E88A  60                      pushal                                  
  0x0028E88B  0000                    add      byte ptr [eax], al             
  0x0028E88D  0100                    add      dword ptr [eax], eax           
  0x0028E88F  0000                    add      byte ptr [eax], al             
  0x0028E891  f4                      hlt                                     
  0x0028E892  7000                    jo       0x28e894                       
                                        ; XREF: 0x0028E892 (cond_jump)
  0x0028E894  0001                    add      byte ptr [ecx], al             
  0x0028E896  0000                    add      byte ptr [eax], al             
  0x0028E898  0001                    add      byte ptr [ecx], al             
  0x0028E89A  3900                    cmp      dword ptr [eax], eax           
  0x0028E89C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028E89F  0000                    add      byte ptr [eax], al             
  0x0028E8A1  f4                      hlt                                     
  0x0028E8A2  56                      push     esi                            
  0x0028E8A3  0007                    add      byte ptr [edi], al             
  0x0028E8A5  0000                    add      byte ptr [eax], al             
  0x0028E8A7  0000                    add      byte ptr [eax], al             
  0x0028E8A9  f4                      hlt                                     
  0x0028E8AA  60                      pushal                                  
  0x0028E8AB  0000                    add      byte ptr [eax], al             
  0x0028E8AD  0200                    add      al, byte ptr [eax]             
  0x0028E8AF  0000                    add      byte ptr [eax], al             
  0x0028E8B1  f4                      hlt                                     
  0x0028E8B2  7000                    jo       0x28e8b4                       
                                        ; XREF: 0x0028E8B2 (cond_jump)
  0x0028E8B4  0001                    add      byte ptr [ecx], al             
  0x0028E8B6  0000                    add      byte ptr [eax], al             
  0x0028E8B8  0002                    add      byte ptr [edx], al             
  0x0028E8BA  3900                    cmp      dword ptr [eax], eax           
  0x0028E8BC  80010d                  add      byte ptr [ecx], 0xd            
  0x0028E8BF  0000                    add      byte ptr [eax], al             
  0x0028E8C1  f4                      hlt                                     
  0x0028E8C2  56                      push     esi                            
  0x0028E8C3  0007                    add      byte ptr [edi], al             
  0x0028E8C5  0000                    add      byte ptr [eax], al             
  0x0028E8C7  0000                    add      byte ptr [eax], al             
  0x0028E8C9  f4                      hlt                                     
  0x0028E8CA  60                      pushal                                  
  0x0028E8CB  0000                    add      byte ptr [eax], al             
  0x0028E8CD  0300                    add      eax, dword ptr [eax]           
  0x0028E8CF  0000                    add      byte ptr [eax], al             
  0x0028E8D1  f4                      hlt                                     
  0x0028E8D2  7000                    jo       0x28e8d4                       
                                        ; XREF: 0x0028E8D2 (cond_jump)
  0x0028E8D4  0001                    add      byte ptr [ecx], al             
  0x0028E8D6  0000                    add      byte ptr [eax], al             
  0x0028E8D8  0003                    add      byte ptr [ebx], al             
  0x0028E8DA  3900                    cmp      dword ptr [eax], eax           
  0x0028E8DC  80010d                  add      byte ptr [ecx], 0xd            
  0x0028E8DF  0000                    add      byte ptr [eax], al             
  0x0028E8E1  f4                      hlt                                     
  0x0028E8E2  56                      push     esi                            
  0x0028E8E3  0007                    add      byte ptr [edi], al             
  0x0028E8E5  0000                    add      byte ptr [eax], al             
  0x0028E8E7  0000                    add      byte ptr [eax], al             
  0x0028E8E9  f4                      hlt                                     
  0x0028E8EA  60                      pushal                                  
  0x0028E8EB  0000                    add      byte ptr [eax], al             
  0x0028E8ED  0400                    add      al, 0                          
  0x0028E8EF  0000                    add      byte ptr [eax], al             
  0x0028E8F1  f4                      hlt                                     
  0x0028E8F2  7000                    jo       0x28e8f4                       
                                        ; XREF: 0x0028E8F2 (cond_jump)
  0x0028E8F4  0001                    add      byte ptr [ecx], al             
  0x0028E8F6  0000                    add      byte ptr [eax], al             
  0x0028E8F8  000439                  add      byte ptr [ecx + edi], al       
  0x0028E8FB  0080010d0000            add      byte ptr [eax + 0xd01], al     
  0x0028E901  f4                      hlt                                     
  0x0028E902  44                      inc      esp                            
  0x0028E903  0000                    add      byte ptr [eax], al             
  0x0028E905  004000                  add      byte ptr [eax], al             
  0x0028E908  00704c                  add      byte ptr [eax + 0x4c], dh      
  0x0028E90B  0000                    add      byte ptr [eax], al             
  0x0028E90D  0000                    add      byte ptr [eax], al             
  0x0028E90F  0000                    add      byte ptr [eax], al             
  0x0028E911  f4                      hlt                                     
  0x0028E912  44                      inc      esp                            
  0x0028E913  007982                  add      byte ptr [ecx - 0x7e], bh      
  0x0028E916  5a                      pop      edx                            
  0x0028E917  0000                    add      byte ptr [eax], al             
  0x0028E919  704c                    jo       0x28e967                       
  0x0028E91B  0001                    add      byte ptr [ecx], al             
  0x0028E91D  0000                    add      byte ptr [eax], al             
  0x0028E91F  0000                    add      byte ptr [eax], al             
  0x0028E921  f4                      hlt                                     
  0x0028E922  44                      inc      esp                            
  0x0028E923  0000                    add      byte ptr [eax], al             
  0x0028E925  004000                  add      byte ptr [eax], al             
  0x0028E928  00704c                  add      byte ptr [eax + 0x4c], dh      
  0x0028E92B  0002                    add      byte ptr [edx], al             
  0x0028E92D  0000                    add      byte ptr [eax], al             
  0x0028E92F  0000                    add      byte ptr [eax], al             
  0x0028E931  f4                      hlt                                     
  0x0028E932  44                      inc      esp                            
  0x0028E933  003c41                  add      byte ptr [ecx + eax*2], bh     
  0x0028E936  2d0000704c              sub      eax, 0x4c700000                
  0x0028E93B  0003                    add      byte ptr [ebx], al             
  0x0028E93D  0000                    add      byte ptr [eax], al             
  0x0028E93F  0000                    add      byte ptr [eax], al             
  0x0028E941  f4                      hlt                                     
  0x0028E942  44                      inc      esp                            
  0x0028E943  003c41                  add      byte ptr [ecx + eax*2], bh     
  0x0028E946  2d0000704c              sub      eax, 0x4c700000                
  0x0028E94B  000400                  add      byte ptr [eax + eax], al       
  0x0028E94E  0000                    add      byte ptr [eax], al             
  0x0028E950  00f0                    add      al, dh                         
  0x0028E952  6200                    bound    eax, qword ptr [eax]           
  0x0028E954  0007                    add      byte ptr [edi], al             
  0x0028E956  0000                    add      byte ptr [eax], al             
  0x0028E958  0000                    add      byte ptr [eax], al             
  0x0028E95A  0000                    add      byte ptr [eax], al             
  0x0028E95C  0000                    add      byte ptr [eax], al             
  0x0028E95E  0000                    add      byte ptr [eax], al             
  0x0028E960  d542                    aad      0x42                           
  0x0028E962  0200                    add      al, byte ptr [eax]             
  0x0028E964  9e                      sahf                                    
  0x0028E965  42                      inc      edx                            
  0x0028E966  0200                    add      al, byte ptr [eax]             
  0x0028E968  0300                    add      eax, dword ptr [eax]           
  0x0028E96A  2000                    and      byte ptr [eax], al             
  0x0028E96C  0ba4050000f460          or       esp, dword ptr [ebp + eax + 0x60f40000] 
  0x0028E973  0000                    add      byte ptr [eax], al             
  0x0028E975  0000                    add      byte ptr [eax], al             
  0x0028E977  0000                    add      byte ptr [eax], al             
  0x0028E979  0138                    add      dword ptr [eax], edi           
  0x0028E97B  0000                    add      byte ptr [eax], al             
  0x0028E97E  4e                      dec      esi                            
  0x0028E97F  0000                    add      byte ptr [eax], al             
  0x0028E981  0000                    add      byte ptr [eax], al             
  0x0028E983  009005060004            add      byte ptr [eax + 0x4000605], dl 
  0x0028E989  0000                    add      byte ptr [eax], al             
  0x0028E98B  00e1                    add      cl, ah                         
  0x0028E98D  0020                    add      byte ptr [eax], ah             
  0x0028E98F  0000                    add      byte ptr [eax], al             
  0x0028E991  e84e000058              call     0x5828e9e4                     
  0x0028E996  5e                      pop      esi                            
  0x0028E997  0000                    add      byte ptr [eax], al             
  0x0028E999  f4                      hlt                                     
  0x0028E99A  6200                    bound    eax, qword ptr [eax]           
  0x0028E99C  0005000000f4            add      byte ptr [0xf4000000], al      
  0x0028E9A2  660000                  add      byte ptr [eax], al             
  0x0028E9A5  06                      push     es                             
  0x0028E9A6  0000                    add      byte ptr [eax], al             
  0x0028E9A8  00f4                    add      ah, dh                         
  0x0028E9AA  7000                    jo       0x28e9ac                       
                                        ; XREF: 0x0028E9AA (cond_jump)
  0x0028E9AC  0001                    add      byte ptr [ecx], al             
  0x0028E9AE  0000                    add      byte ptr [eax], al             
  0x0028E9B0  00f4                    add      ah, dh                         
  0x0028E9B2  60                      pushal                                  
  0x0028E9B3  0000                    add      byte ptr [eax], al             
  0x0028E9B5  0000                    add      byte ptr [eax], al             
  0x0028E9B7  0000                    add      byte ptr [eax], al             
  0x0028E9B9  f4                      hlt                                     
  0x0028E9BA  640000                  add      byte ptr fs:[eax], al          
  0x0028E9BD  0000                    add      byte ptr [eax], al             
  0x0028E9BF  0000                    add      byte ptr [eax], al             
  0x0028E9C1  1522009100              adc      eax, 0x910022                  
  0x0028E9C6  06                      push     es                             
  0x0028E9C7  000c00                  add      byte ptr [eax + eax], cl       
  0x0028E9CA  0000                    add      byte ptr [eax], al             
  0x0028E9CC  0088f000d088            add      byte ptr [eax - 0x772fff10], cl 
  0x0028E9D3  00d2                    add      dl, dl                         
  0x0028E9D5  88f0                    mov      al, dh                         
  0x0028E9D7  00d2                    add      dl, dl                         
  0x0028E9D9  88f0                    mov      al, dh                         
  0x0028E9DB  00d2                    add      dl, dl                         
  0x0028E9DD  80c000                  add      al, 0                          
  0x0028E9E0  d3dd                    rcr      ebp, cl                        
  0x0028E9E2  4e                      dec      esi                            
  0x0028E9E3  0000                    add      byte ptr [eax], al             
  0x0028E9E5  b022                    mov      al, 0x22                       
  0x0028E9E7  0000                    add      byte ptr [eax], al             
  0x0028E9E9  f4                      hlt                                     
  0x0028E9EA  640000                  add      byte ptr fs:[eax], al          
  0x0028E9ED  0000                    add      byte ptr [eax], al             
  0x0028E9EF  0000                    add      byte ptr [eax], al             
  0x0028E9F1  5a                      pop      edx                            
  0x0028E9F2  56                      push     esi                            
  0x0028E9F3  0000                    add      byte ptr [eax], al             
  0x0028E9F5  5e                      pop      esi                            
  0x0028E9F6  56                      push     esi                            
  0x0028E9F7  0013                    add      byte ptr [ebx], dl             
  0x0028E9F9  f4                      hlt                                     
  0x0028E9FA  6200                    bound    eax, qword ptr [eax]           
  0x0028E9FC  000500001b00            add      byte ptr [0x1b0000], al        
  0x0028EA02  2000                    and      byte ptr [eax], al             
  0x0028EA04  91                      xchg     ecx, eax                       
  0x0028EA05  0006                    add      byte ptr [esi], al             
  0x0028EA07  000500000000            add      byte ptr [0], al               
  0x0028EA0D  da44008a                fiadd    dword ptr [eax + eax - 0x76]   
  0x0028EA11  0020                    add      byte ptr [eax], ah             
  0x0028EA13  004700                  add      byte ptr [edi], al             
  0x0028EA16  2000                    and      byte ptr [eax], al             
  0x0028EA18  40                      inc      eax                            
  0x0028EA19  90                      nop                                     
  0x0028EA1A  0200                    add      al, byte ptr [eax]             
  0x0028EA1C  260020                  add      byte ptr es:[eax], ah          
  0x0028EA1F  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x0028EA25  7056                    jo       0x28ea7d                       
  0x0028EA27  0001                    add      byte ptr [ecx], al             
  0x0028EA29  07                      pop      es                             
  0x0028EA2A  0000                    add      byte ptr [eax], al             
  0x0028EA2C  00a721000026            add      byte ptr [edi + 0x26000021], ah 
  0x0028EA32  2100                    and      dword ptr [eax], eax           
  0x0028EA34  13402f                  adc      eax, dword ptr [eax + 0x2f]    
  0x0028EA37  009017060009            add      byte ptr [eax + 0x9000617], dl 
  0x0028EA3D  0000                    add      byte ptr [eax], al             
  0x0028EA3F  0010                    add      byte ptr [eax], dl             
  0x0028EA41  c521                    lds      esp, ptr [ecx]                 
  0x0028EA43  0000                    add      byte ptr [eax], al             
  0x0028EA45  0000                    add      byte ptr [eax], al             
  0x0028EA47  0000                    add      byte ptr [eax], al             
  0x0028EA49  c421                    les      esp, ptr [ecx]                 
  0x0028EA4B  00840020003000          add      byte ptr [eax + eax + 0x300020], al 
  0x0028EA52  2000                    and      byte ptr [eax], al             
  0x0028EA54  00ae20001021            add      byte ptr [esi + 0x21100020], ch 
  0x0028EA5A  2000                    and      byte ptr [eax], al             
  0x0028EA5C  2a00                    sub      al, byte ptr [eax]             
  0x0028EA5E  2000                    and      byte ptr [eax], al             
  0x0028EA60  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028EA63  0003                    add      byte ptr [ebx], al             
  0x0028EA65  07                      pop      es                             
  0x0028EA66  0000                    add      byte ptr [eax], al             
  0x0028EA68  13f4                    adc      esi, esp                       
  0x0028EA6A  6200                    bound    eax, qword ptr [eax]           
  0x0028EA6C  0006                    add      byte ptr [esi], al             
  0x0028EA6E  0000                    add      byte ptr [eax], al             
  0x0028EA70  1b00                    sbb      eax, dword ptr [eax]           
  0x0028EA72  2000                    and      byte ptr [eax], al             
  0x0028EA74  91                      xchg     ecx, eax                       
  0x0028EA75  0006                    add      byte ptr [esi], al             
  0x0028EA77  000500000000            add      byte ptr [0], al               
                                        ; XREF: 0x0028EA25 (cond_jump)
  0x0028EA7D  da44008a                fiadd    dword ptr [eax + eax - 0x76]   
  0x0028EA81  0020                    add      byte ptr [eax], ah             
  0x0028EA83  004700                  add      byte ptr [edi], al             
  0x0028EA86  2000                    and      byte ptr [eax], al             
  0x0028EA88  40                      inc      eax                            
  0x0028EA89  90                      nop                                     
  0x0028EA8A  0200                    add      al, byte ptr [eax]             
  0x0028EA8C  260020                  add      byte ptr es:[eax], ah          
  0x0028EA8F  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x0028EA95  7056                    jo       0x28eaed                       
  0x0028EA97  0002                    add      byte ptr [edx], al             
  0x0028EA99  07                      pop      es                             
  0x0028EA9A  0000                    add      byte ptr [eax], al             
  0x0028EA9C  00a721000026            add      byte ptr [edi + 0x26000021], ah 
  0x0028EAA2  2100                    and      dword ptr [eax], eax           
  0x0028EAA4  13402f                  adc      eax, dword ptr [eax + 0x2f]    
  0x0028EAA7  009017060009            add      byte ptr [eax + 0x9000617], dl 
  0x0028EAAD  0000                    add      byte ptr [eax], al             
  0x0028EAAF  0010                    add      byte ptr [eax], dl             
  0x0028EAB1  c521                    lds      esp, ptr [ecx]                 
  0x0028EAB3  0000                    add      byte ptr [eax], al             
  0x0028EAB5  0000                    add      byte ptr [eax], al             
  0x0028EAB7  0000                    add      byte ptr [eax], al             
  0x0028EAB9  c421                    les      esp, ptr [ecx]                 
  0x0028EABB  00840020003000          add      byte ptr [eax + eax + 0x300020], al 
  0x0028EAC2  2000                    and      byte ptr [eax], al             
  0x0028EAC4  00ae20001021            add      byte ptr [esi + 0x21100020], ch 
  0x0028EACA  2000                    and      byte ptr [eax], al             
  0x0028EACC  2a00                    sub      al, byte ptr [eax]             
  0x0028EACE  2000                    and      byte ptr [eax], al             
  0x0028EAD0  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028EAD3  000407                  add      byte ptr [edi + eax], al       
  0x0028EAD6  0000                    add      byte ptr [eax], al             
  0x0028EAD8  00f4                    add      ah, dh                         
  0x0028EADA  56                      push     esi                            
  0x0028EADB  0008                    add      byte ptr [eax], cl             
  0x0028EADD  0000                    add      byte ptr [eax], al             
  0x0028EADF  0000                    add      byte ptr [eax], al             
  0x0028EAE1  f4                      hlt                                     
  0x0028EAE2  60                      pushal                                  
  0x0028EAE3  0000                    add      byte ptr [eax], al             
  0x0028EAE5  05000000f4              add      eax, 0xf4000000                
  0x0028EAEA  7000                    jo       0x28eaec                       
                                        ; XREF: 0x0028EAEA (cond_jump)
  0x0028EAEC  0001                    add      byte ptr [ecx], al             
  0x0028EAEE  0000                    add      byte ptr [eax], al             
  0x0028EAF0  0000                    add      byte ptr [eax], al             
  0x0028EAF2  3900                    cmp      dword ptr [eax], eax           
  0x0028EAF4  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EAF7  0000                    add      byte ptr [eax], al             
  0x0028EAF9  f4                      hlt                                     
  0x0028EAFA  56                      push     esi                            
  0x0028EAFB  0008                    add      byte ptr [eax], cl             
  0x0028EAFD  0000                    add      byte ptr [eax], al             
  0x0028EAFF  0000                    add      byte ptr [eax], al             
  0x0028EB01  f4                      hlt                                     
  0x0028EB02  60                      pushal                                  
  0x0028EB03  0000                    add      byte ptr [eax], al             
  0x0028EB05  06                      push     es                             
  0x0028EB06  0000                    add      byte ptr [eax], al             
  0x0028EB08  00f4                    add      ah, dh                         
  0x0028EB0A  7000                    jo       0x28eb0c                       
                                        ; XREF: 0x0028EB0A (cond_jump)
  0x0028EB0C  0001                    add      byte ptr [ecx], al             
  0x0028EB0E  0000                    add      byte ptr [eax], al             
  0x0028EB10  0001                    add      byte ptr [ecx], al             
  0x0028EB12  3900                    cmp      dword ptr [eax], eax           
  0x0028EB14  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EB17  0000                    add      byte ptr [eax], al             
  0x0028EB19  f4                      hlt                                     
  0x0028EB1A  56                      push     esi                            
  0x0028EB1B  000f                    add      byte ptr [edi], cl             
  0x0028EB1D  0000                    add      byte ptr [eax], al             
  0x0028EB1F  0000                    add      byte ptr [eax], al             
  0x0028EB21  f4                      hlt                                     
  0x0028EB22  60                      pushal                                  
  0x0028EB23  0001                    add      byte ptr [ecx], al             
  0x0028EB25  07                      pop      es                             
  0x0028EB26  0000                    add      byte ptr [eax], al             
  0x0028EB28  000438                  add      byte ptr [eax + edi], al       
  0x0028EB2B  0000                    add      byte ptr [eax], al             
  0x0028EB2D  0039                    add      byte ptr [ecx], bh             
  0x0028EB2F  0080010d000c            add      byte ptr [eax + 0xc000d01], al 
  0x0028EB35  0000                    add      byte ptr [eax], al             
  0x0028EB37  00401b                  add      byte ptr [eax + 0x1b], al      
  0x0028EB3A  d000                    rol      byte ptr [eax], 1              
  0x0028EB3C  c9                      leave                                   
  0x0028EB3D  0000                    add      byte ptr [eax], al             
  0x0028EB3F  007201                  add      byte ptr [edx + 1], dh         
  0x0028EB42  06                      push     es                             
  0x0028EB43  00b0c4870000            add      byte ptr [eax + 0x87c4], dh    
  0x0028EB49  7060                    jo       0x28ebab                       
  0x0028EB4B  0000                    add      byte ptr [eax], al             
  0x0028EB4D  07                      pop      es                             
  0x0028EB4E  0000                    add      byte ptr [eax], al             
  0x0028EB50  00f4                    add      ah, dh                         
  0x0028EB52  56                      push     esi                            
  0x0028EB53  0007                    add      byte ptr [edi], al             
  0x0028EB55  0000                    add      byte ptr [eax], al             
  0x0028EB57  0000                    add      byte ptr [eax], al             
  0x0028EB59  f4                      hlt                                     
  0x0028EB5A  60                      pushal                                  
  0x0028EB5B  0000                    add      byte ptr [eax], al             
  0x0028EB5D  0000                    add      byte ptr [eax], al             
  0x0028EB5F  0000                    add      byte ptr [eax], al             
  0x0028EB61  f4                      hlt                                     
  0x0028EB62  7000                    jo       0x28eb64                       
                                        ; XREF: 0x0028EB62 (cond_jump)
  0x0028EB64  0001                    add      byte ptr [ecx], al             
  0x0028EB66  0000                    add      byte ptr [eax], al             
  0x0028EB68  0000                    add      byte ptr [eax], al             
  0x0028EB6A  3900                    cmp      dword ptr [eax], eax           
  0x0028EB6C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EB6F  0000                    add      byte ptr [eax], al             
  0x0028EB71  f4                      hlt                                     
  0x0028EB72  56                      push     esi                            
  0x0028EB73  0007                    add      byte ptr [edi], al             
  0x0028EB75  0000                    add      byte ptr [eax], al             
  0x0028EB77  0000                    add      byte ptr [eax], al             
  0x0028EB79  f4                      hlt                                     
  0x0028EB7A  60                      pushal                                  
  0x0028EB7B  0000                    add      byte ptr [eax], al             
  0x0028EB7D  0100                    add      dword ptr [eax], eax           
  0x0028EB7F  0000                    add      byte ptr [eax], al             
  0x0028EB81  f4                      hlt                                     
  0x0028EB82  7000                    jo       0x28eb84                       
                                        ; XREF: 0x0028EB82 (cond_jump)
  0x0028EB84  0001                    add      byte ptr [ecx], al             
  0x0028EB86  0000                    add      byte ptr [eax], al             
  0x0028EB88  0001                    add      byte ptr [ecx], al             
  0x0028EB8A  3900                    cmp      dword ptr [eax], eax           
  0x0028EB8C  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EB8F  0000                    add      byte ptr [eax], al             
  0x0028EB91  f4                      hlt                                     
  0x0028EB92  56                      push     esi                            
  0x0028EB93  0007                    add      byte ptr [edi], al             
  0x0028EB95  0000                    add      byte ptr [eax], al             
  0x0028EB97  0000                    add      byte ptr [eax], al             
  0x0028EB99  f4                      hlt                                     
  0x0028EB9A  60                      pushal                                  
  0x0028EB9B  0000                    add      byte ptr [eax], al             
  0x0028EB9D  0200                    add      al, byte ptr [eax]             
  0x0028EB9F  0000                    add      byte ptr [eax], al             
  0x0028EBA1  f4                      hlt                                     
  0x0028EBA2  7000                    jo       0x28eba4                       
                                        ; XREF: 0x0028EBA2 (cond_jump)
  0x0028EBA4  0001                    add      byte ptr [ecx], al             
  0x0028EBA6  0000                    add      byte ptr [eax], al             
  0x0028EBA8  0002                    add      byte ptr [edx], al             
  0x0028EBAA  3900                    cmp      dword ptr [eax], eax           
  0x0028EBAC  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EBAF  0000                    add      byte ptr [eax], al             
  0x0028EBB1  f4                      hlt                                     
  0x0028EBB2  56                      push     esi                            
  0x0028EBB3  0007                    add      byte ptr [edi], al             
  0x0028EBB5  0000                    add      byte ptr [eax], al             
  0x0028EBB7  0000                    add      byte ptr [eax], al             
  0x0028EBB9  f4                      hlt                                     
  0x0028EBBA  60                      pushal                                  
  0x0028EBBB  0000                    add      byte ptr [eax], al             
  0x0028EBBD  0300                    add      eax, dword ptr [eax]           
  0x0028EBBF  0000                    add      byte ptr [eax], al             
  0x0028EBC1  f4                      hlt                                     
  0x0028EBC2  7000                    jo       0x28ebc4                       
                                        ; XREF: 0x0028EBC2 (cond_jump)
  0x0028EBC4  0001                    add      byte ptr [ecx], al             
  0x0028EBC6  0000                    add      byte ptr [eax], al             
  0x0028EBC8  0003                    add      byte ptr [ebx], al             
  0x0028EBCA  3900                    cmp      dword ptr [eax], eax           
  0x0028EBCC  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EBCF  0000                    add      byte ptr [eax], al             
  0x0028EBD1  f4                      hlt                                     
  0x0028EBD2  56                      push     esi                            
  0x0028EBD3  0007                    add      byte ptr [edi], al             
  0x0028EBD5  0000                    add      byte ptr [eax], al             
  0x0028EBD7  0000                    add      byte ptr [eax], al             
  0x0028EBD9  f4                      hlt                                     
  0x0028EBDA  60                      pushal                                  
  0x0028EBDB  0000                    add      byte ptr [eax], al             
  0x0028EBDD  0400                    add      al, 0                          
  0x0028EBDF  0000                    add      byte ptr [eax], al             
  0x0028EBE1  f4                      hlt                                     
  0x0028EBE2  7000                    jo       0x28ebe4                       
                                        ; XREF: 0x0028EBE2 (cond_jump)
  0x0028EBE4  0001                    add      byte ptr [ecx], al             
  0x0028EBE6  0000                    add      byte ptr [eax], al             
  0x0028EBE8  000439                  add      byte ptr [ecx + edi], al       
  0x0028EBEB  0080010d0000            add      byte ptr [eax + 0xd01], al     
  0x0028EBF1  f4                      hlt                                     
  0x0028EBF2  44                      inc      esp                            
  0x0028EBF3  00ff                    add      bh, bh                         
  0x0028EBF6  7f00                    jg       0x28ebf8                       
                                        ; XREF: 0x0028EBF6 (cond_jump)
  0x0028EBF8  00704c                  add      byte ptr [eax + 0x4c], dh      
  0x0028EBFB  0000                    add      byte ptr [eax], al             
  0x0028EBFD  0000                    add      byte ptr [eax], al             
  0x0028EBFF  0000                    add      byte ptr [eax], al             
  0x0028EC01  704c                    jo       0x28ec4f                       
  0x0028EC03  000500000000            add      byte ptr [0], al               
  0x0028EC09  f4                      hlt                                     
  0x0028EC0A  44                      inc      esp                            
  0x0028EC0B  007982                  add      byte ptr [ecx - 0x7e], bh      
  0x0028EC0E  5a                      pop      edx                            
  0x0028EC0F  0000                    add      byte ptr [eax], al             
  0x0028EC11  704c                    jo       0x28ec5f                       
  0x0028EC13  0002                    add      byte ptr [edx], al             
  0x0028EC15  0000                    add      byte ptr [eax], al             
  0x0028EC17  0000                    add      byte ptr [eax], al             
  0x0028EC19  704c                    jo       0x28ec67                       
  0x0028EC1B  0003                    add      byte ptr [ebx], al             
  0x0028EC1D  0000                    add      byte ptr [eax], al             
  0x0028EC1F  0000                    add      byte ptr [eax], al             
  0x0028EC21  f4                      hlt                                     
  0x0028EC22  44                      inc      esp                            
  0x0028EC23  007982                  add      byte ptr [ecx - 0x7e], bh      
  0x0028EC26  5a                      pop      edx                            
  0x0028EC27  0000                    add      byte ptr [eax], al             
  0x0028EC29  704c                    jo       0x28ec77                       
  0x0028EC2B  0006                    add      byte ptr [esi], al             
  0x0028EC2D  0000                    add      byte ptr [eax], al             
  0x0028EC2F  0000                    add      byte ptr [eax], al             
  0x0028EC31  704c                    jo       0x28ec7f                       
  0x0028EC33  0009                    add      byte ptr [ecx], cl             
  0x0028EC35  0000                    add      byte ptr [eax], al             
  0x0028EC37  0000                    add      byte ptr [eax], al             
  0x0028EC39  f4                      hlt                                     
  0x0028EC3A  44                      inc      esp                            
  0x0028EC3B  0000                    add      byte ptr [eax], al             
  0x0028EC3D  0000                    add      byte ptr [eax], al             
  0x0028EC3F  0000                    add      byte ptr [eax], al             
  0x0028EC41  704c                    jo       0x28ec8f                       
  0x0028EC43  000400                  add      byte ptr [eax + eax], al       
  0x0028EC46  0000                    add      byte ptr [eax], al             
  0x0028EC48  00704c                  add      byte ptr [eax + 0x4c], dh      
  0x0028EC4B  0008                    add      byte ptr [eax], cl             
  0x0028EC4D  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028EC01 (cond_jump)
  0x0028EC4F  0000                    add      byte ptr [eax], al             
  0x0028EC51  704c                    jo       0x28ec9f                       
  0x0028EC53  0001                    add      byte ptr [ecx], al             
  0x0028EC55  0000                    add      byte ptr [eax], al             
  0x0028EC57  0000                    add      byte ptr [eax], al             
  0x0028EC59  704c                    jo       0x28eca7                       
  0x0028EC5B  0007                    add      byte ptr [edi], al             
  0x0028EC5D  0000                    add      byte ptr [eax], al             
                                        ; XREF: 0x0028EC11 (cond_jump)
  0x0028EC5F  0000                    add      byte ptr [eax], al             
  0x0028EC62  6200                    bound    eax, qword ptr [eax]           
  0x0028EC64  0007                    add      byte ptr [edi], al             
  0x0028EC66  0000                    add      byte ptr [eax], al             
  0x0028EC68  0000                    add      byte ptr [eax], al             
  0x0028EC6A  0000                    add      byte ptr [eax], al             
  0x0028EC6C  0000                    add      byte ptr [eax], al             
  0x0028EC6E  0000                    add      byte ptr [eax], al             
  0x0028EC70  d542                    aad      0x42                           
  0x0028EC72  0200                    add      al, byte ptr [eax]             
  0x0028EC74  9e                      sahf                                    
  0x0028EC75  42                      inc      edx                            
  0x0028EC76  0200                    add      al, byte ptr [eax]             
  0x0028EC78  0300                    add      eax, dword ptr [eax]           
  0x0028EC7A  2000                    and      byte ptr [eax], al             
  0x0028EC7C  0ba4050000f460          or       esp, dword ptr [ebp + eax + 0x60f40000] 
  0x0028EC83  0000                    add      byte ptr [eax], al             
  0x0028EC85  0000                    add      byte ptr [eax], al             
  0x0028EC87  0000                    add      byte ptr [eax], al             
  0x0028EC89  0138                    add      dword ptr [eax], edi           
  0x0028EC8B  0000                    add      byte ptr [eax], al             
  0x0028EC8E  4e                      dec      esi                            
                                        ; XREF: 0x0028EC41 (cond_jump)
  0x0028EC8F  0000                    add      byte ptr [eax], al             
  0x0028EC91  0000                    add      byte ptr [eax], al             
  0x0028EC93  00900a060004            add      byte ptr [eax + 0x400060a], dl 
  0x0028EC99  0000                    add      byte ptr [eax], al             
  0x0028EC9B  00e1                    add      cl, ah                         
  0x0028EC9D  0020                    add      byte ptr [eax], ah             
                                        ; XREF: 0x0028EC51 (cond_jump)
  0x0028EC9F  0000                    add      byte ptr [eax], al             
  0x0028ECA1  e84e000058              call     0x5828ecf4                     
  0x0028ECA6  5e                      pop      esi                            
                                        ; XREF: 0x0028EC59 (cond_jump)
  0x0028ECA7  0000                    add      byte ptr [eax], al             
  0x0028ECA9  f4                      hlt                                     
  0x0028ECAA  6200                    bound    eax, qword ptr [eax]           
  0x0028ECAC  0005000000f4            add      byte ptr [0xf4000000], al      
  0x0028ECB2  660000                  add      byte ptr [eax], al             
  0x0028ECB5  06                      push     es                             
  0x0028ECB6  0000                    add      byte ptr [eax], al             
  0x0028ECB8  00f4                    add      ah, dh                         
  0x0028ECBA  7000                    jo       0x28ecbc                       
                                        ; XREF: 0x0028ECBA (cond_jump)
  0x0028ECBC  0001                    add      byte ptr [ecx], al             
  0x0028ECBE  0000                    add      byte ptr [eax], al             
  0x0028ECC0  00f4                    add      ah, dh                         
  0x0028ECC2  60                      pushal                                  
  0x0028ECC3  0000                    add      byte ptr [eax], al             
  0x0028ECC5  0000                    add      byte ptr [eax], al             
  0x0028ECC7  0000                    add      byte ptr [eax], al             
  0x0028ECC9  f4                      hlt                                     
  0x0028ECCA  640000                  add      byte ptr fs:[eax], al          
  0x0028ECCD  0000                    add      byte ptr [eax], al             
  0x0028ECCF  0000                    add      byte ptr [eax], al             
  0x0028ECD1  1522009100              adc      eax, 0x910022                  
  0x0028ECD6  06                      push     es                             
  0x0028ECD7  0011                    add      byte ptr [ecx], dl             
  0x0028ECD9  0000                    add      byte ptr [eax], al             
  0x0028ECDB  0000                    add      byte ptr [eax], al             
  0x0028ECDD  88f0                    mov      al, dh                         
  0x0028ECDF  00d0                    add      al, dl                         
  0x0028ECE1  dc4e00                  fmul     qword ptr [esi]                
  0x0028ECE4  d888f000d2dc            fmul     dword ptr [eax - 0x232dff10]   
  0x0028ECEA  4e                      dec      esi                            
  0x0028ECEB  00da                    add      dl, bl                         
  0x0028ECED  88f0                    mov      al, dh                         
  0x0028ECEF  00d2                    add      dl, dl                         
  0x0028ECF1  dc4e00                  fmul     qword ptr [esi]                
  0x0028ECF4  da88f000d2dc            fimul    dword ptr [eax - 0x232dff10]   
  0x0028ECFA  4e                      dec      esi                            
  0x0028ECFB  00da                    add      dl, bl                         
  0x0028ECFD  88f0                    mov      al, dh                         
  0x0028ECFF  00d3                    add      bl, dl                         
  0x0028ED01  dc4e00                  fmul     qword ptr [esi]                
  0x0028ED04  dbdd                    fcmovnu  st(0), st(5)                   
  0x0028ED06  4e                      dec      esi                            
  0x0028ED07  0000                    add      byte ptr [eax], al             
  0x0028ED09  b022                    mov      al, 0x22                       
  0x0028ED0B  0000                    add      byte ptr [eax], al             
  0x0028ED0D  f4                      hlt                                     
  0x0028ED0E  640000                  add      byte ptr fs:[eax], al          
  0x0028ED11  0000                    add      byte ptr [eax], al             
  0x0028ED13  0000                    add      byte ptr [eax], al             
  0x0028ED15  5a                      pop      edx                            
  0x0028ED16  56                      push     esi                            
  0x0028ED17  0000                    add      byte ptr [eax], al             
  0x0028ED19  5e                      pop      esi                            
  0x0028ED1A  57                      push     edi                            
  0x0028ED1B  0013                    add      byte ptr [ebx], dl             
  0x0028ED1D  f4                      hlt                                     
  0x0028ED1E  6200                    bound    eax, qword ptr [eax]           
  0x0028ED20  000500001b00            add      byte ptr [0x1b0000], al        
  0x0028ED26  2000                    and      byte ptr [eax], al             
  0x0028ED28  91                      xchg     ecx, eax                       
  0x0028ED29  0006                    add      byte ptr [esi], al             
  0x0028ED2B  000500000000            add      byte ptr [0], al               
  0x0028ED31  da44008a                fiadd    dword ptr [eax + eax - 0x76]   
  0x0028ED35  0020                    add      byte ptr [eax], ah             
  0x0028ED37  004700                  add      byte ptr [edi], al             
  0x0028ED3A  2000                    and      byte ptr [eax], al             
  0x0028ED3C  40                      inc      eax                            
  0x0028ED3D  90                      nop                                     
  0x0028ED3E  0200                    add      al, byte ptr [eax]             
  0x0028ED40  260020                  add      byte ptr es:[eax], ah          
  0x0028ED43  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x0028ED49  7056                    jo       0x28eda1                       
  0x0028ED4B  0001                    add      byte ptr [ecx], al             
  0x0028ED4D  07                      pop      es                             
  0x0028ED4E  0000                    add      byte ptr [eax], al             
  0x0028ED50  00a721000026            add      byte ptr [edi + 0x26000021], ah 
  0x0028ED56  2100                    and      dword ptr [eax], eax           
  0x0028ED58  13402f                  adc      eax, dword ptr [eax + 0x2f]    
  0x0028ED5B  009017060009            add      byte ptr [eax + 0x9000617], dl 
  0x0028ED61  0000                    add      byte ptr [eax], al             
  0x0028ED63  0010                    add      byte ptr [eax], dl             
  0x0028ED65  c521                    lds      esp, ptr [ecx]                 
  0x0028ED67  0000                    add      byte ptr [eax], al             
  0x0028ED69  0000                    add      byte ptr [eax], al             
  0x0028ED6B  0000                    add      byte ptr [eax], al             
  0x0028ED6D  c421                    les      esp, ptr [ecx]                 
  0x0028ED6F  00840020003000          add      byte ptr [eax + eax + 0x300020], al 
  0x0028ED76  2000                    and      byte ptr [eax], al             
  0x0028ED78  00ae20001021            add      byte ptr [esi + 0x21100020], ch 
  0x0028ED7E  2000                    and      byte ptr [eax], al             
  0x0028ED80  2a00                    sub      al, byte ptr [eax]             
  0x0028ED82  2000                    and      byte ptr [eax], al             
  0x0028ED84  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028ED87  0003                    add      byte ptr [ebx], al             
  0x0028ED89  07                      pop      es                             
  0x0028ED8A  0000                    add      byte ptr [eax], al             
  0x0028ED8C  13f4                    adc      esi, esp                       
  0x0028ED8E  6200                    bound    eax, qword ptr [eax]           
  0x0028ED90  0006                    add      byte ptr [esi], al             
  0x0028ED92  0000                    add      byte ptr [eax], al             
  0x0028ED94  1b00                    sbb      eax, dword ptr [eax]           
  0x0028ED96  2000                    and      byte ptr [eax], al             
  0x0028ED98  91                      xchg     ecx, eax                       
  0x0028ED99  0006                    add      byte ptr [esi], al             
  0x0028ED9B  000500000000            add      byte ptr [0], al               
                                        ; XREF: 0x0028ED49 (cond_jump)
  0x0028EDA1  da44008a                fiadd    dword ptr [eax + eax - 0x76]   
  0x0028EDA5  0020                    add      byte ptr [eax], ah             
  0x0028EDA7  004700                  add      byte ptr [edi], al             
  0x0028EDAA  2000                    and      byte ptr [eax], al             
  0x0028EDAC  40                      inc      eax                            
  0x0028EDAD  90                      nop                                     
  0x0028EDAE  0200                    add      al, byte ptr [eax]             
  0x0028EDB0  260020                  add      byte ptr es:[eax], ah          
  0x0028EDB3  00911c0c0000            add      byte ptr [ecx + 0xc1c], dl     
  0x0028EDB9  7056                    jo       0x28ee11                       
  0x0028EDBB  0002                    add      byte ptr [edx], al             
  0x0028EDBD  07                      pop      es                             
  0x0028EDBE  0000                    add      byte ptr [eax], al             
  0x0028EDC0  00a721000026            add      byte ptr [edi + 0x26000021], ah 
  0x0028EDC6  2100                    and      dword ptr [eax], eax           
  0x0028EDC8  13402f                  adc      eax, dword ptr [eax + 0x2f]    
  0x0028EDCB  009017060009            add      byte ptr [eax + 0x9000617], dl 
  0x0028EDD1  0000                    add      byte ptr [eax], al             
  0x0028EDD3  0010                    add      byte ptr [eax], dl             
  0x0028EDD5  c521                    lds      esp, ptr [ecx]                 
  0x0028EDD7  0000                    add      byte ptr [eax], al             
  0x0028EDD9  0000                    add      byte ptr [eax], al             
  0x0028EDDB  0000                    add      byte ptr [eax], al             
  0x0028EDDD  c421                    les      esp, ptr [ecx]                 
  0x0028EDDF  00840020003000          add      byte ptr [eax + eax + 0x300020], al 
  0x0028EDE6  2000                    and      byte ptr [eax], al             
  0x0028EDE8  00ae20001021            add      byte ptr [esi + 0x21100020], ch 
  0x0028EDEE  2000                    and      byte ptr [eax], al             
  0x0028EDF0  2a00                    sub      al, byte ptr [eax]             
  0x0028EDF2  2000                    and      byte ptr [eax], al             
  0x0028EDF4  007056                  add      byte ptr [eax + 0x56], dh      
  0x0028EDF7  000407                  add      byte ptr [edi + eax], al       
  0x0028EDFA  0000                    add      byte ptr [eax], al             
  0x0028EDFC  00f4                    add      ah, dh                         
  0x0028EDFE  56                      push     esi                            
  0x0028EDFF  0008                    add      byte ptr [eax], cl             
  0x0028EE01  0000                    add      byte ptr [eax], al             
  0x0028EE03  0000                    add      byte ptr [eax], al             
  0x0028EE05  f4                      hlt                                     
  0x0028EE06  60                      pushal                                  
  0x0028EE07  0000                    add      byte ptr [eax], al             
  0x0028EE09  05000000f4              add      eax, 0xf4000000                
  0x0028EE0E  7000                    jo       0x28ee10                       
                                        ; XREF: 0x0028EE0E (cond_jump)
  0x0028EE10  0001                    add      byte ptr [ecx], al             
  0x0028EE12  0000                    add      byte ptr [eax], al             
  0x0028EE14  0000                    add      byte ptr [eax], al             
  0x0028EE16  3900                    cmp      dword ptr [eax], eax           
  0x0028EE18  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EE1B  0000                    add      byte ptr [eax], al             
  0x0028EE1D  f4                      hlt                                     
  0x0028EE1E  56                      push     esi                            
  0x0028EE1F  0008                    add      byte ptr [eax], cl             
  0x0028EE21  0000                    add      byte ptr [eax], al             
  0x0028EE23  0000                    add      byte ptr [eax], al             
  0x0028EE25  f4                      hlt                                     
  0x0028EE26  60                      pushal                                  
  0x0028EE27  0000                    add      byte ptr [eax], al             
  0x0028EE29  06                      push     es                             
  0x0028EE2A  0000                    add      byte ptr [eax], al             
  0x0028EE2C  00f4                    add      ah, dh                         
  0x0028EE2E  7000                    jo       0x28ee30                       
                                        ; XREF: 0x0028EE2E (cond_jump)
  0x0028EE30  0001                    add      byte ptr [ecx], al             
  0x0028EE32  0000                    add      byte ptr [eax], al             
  0x0028EE34  0001                    add      byte ptr [ecx], al             
  0x0028EE36  3900                    cmp      dword ptr [eax], eax           
  0x0028EE38  80010d                  add      byte ptr [ecx], 0xd            
  0x0028EE3B  0000                    add      byte ptr [eax], al             
  0x0028EE3D  f4                      hlt                                     
  0x0028EE3E  56                      push     esi                            
  0x0028EE3F  000f                    add      byte ptr [edi], cl             
  0x0028EE41  0000                    add      byte ptr [eax], al             
  0x0028EE43  0000                    add      byte ptr [eax], al             
  0x0028EE45  f4                      hlt                                     
  0x0028EE46  60                      pushal                                  
  0x0028EE47  0001                    add      byte ptr [ecx], al             
  0x0028EE49  07                      pop      es                             
  0x0028EE4A  0000                    add      byte ptr [eax], al             
  0x0028EE4C  000438                  add      byte ptr [eax + edi], al       
  0x0028EE4F  0000                    add      byte ptr [eax], al             
  0x0028EE51  0039                    add      byte ptr [ecx], bh             
  0x0028EE53  0080010d000c            add      byte ptr [eax + 0xc000d01], al 
  0x0028EE59  0000                    add      byte ptr [eax], al             
  0x0028EE5B  0000                    add      byte ptr [eax], al             
  0x0028EE5D  0000                    add      byte ptr [eax], al             
  0x0028EE5F  0018                    add      byte ptr [eax], bl             
  0x0028EE61  0000                    add      byte ptr [eax], al             
  0x0028EE63  0001                    add      byte ptr [ecx], al             
  0x0028EE65  0000                    add      byte ptr [eax], al             
  0x0028EE67  0001                    add      byte ptr [ecx], al             
  0x0028EE69  0000                    add      byte ptr [eax], al             
  0x0028EE6B  0000                    add      byte ptr [eax], al             
  0x0028EE6D  0000                    add      byte ptr [eax], al             
  0x0028EE6F  0000                    add      byte ptr [eax], al             
  0x0028EE71  0000                    add      byte ptr [eax], al             
  0x0028EE73  0007                    add      byte ptr [edi], al             
  0x0028EE75  0000                    add      byte ptr [eax], al             
  0x0028EE77  0001                    add      byte ptr [ecx], al             
  0x0028EE79  0000                    add      byte ptr [eax], al             
  0x0028EE7B  001f                    add      byte ptr [edi], bl             
  0x0028EE7D  0000                    add      byte ptr [eax], al             
  0x0028EE7F  0009                    add      byte ptr [ecx], cl             
  0x0028EE81  0000                    add      byte ptr [eax], al             
  0x0028EE83  0000                    add      byte ptr [eax], al             
  0x0028EE85  0000                    add      byte ptr [eax], al             
  0x0028EE87  0001                    add      byte ptr [ecx], al             
  0x0028EE89  0000                    add      byte ptr [eax], al             
  0x0028EE8B  0001                    add      byte ptr [ecx], al             
  0x0028EE8D  0000                    add      byte ptr [eax], al             
  0x0028EE8F  0000                    add      byte ptr [eax], al             
  0x0028EE91  0000                    add      byte ptr [eax], al             
  0x0028EE93  0000                    add      byte ptr [eax], al             
  0x0028EE95  0000                    add      byte ptr [eax], al             
  0x0028EE97  0001                    add      byte ptr [ecx], al             
  0x0028EE99  0000                    add      byte ptr [eax], al             
  0x0028EE9B  00ef                    add      bh, ch                         
  0x0028EE9D  0000                    add      byte ptr [eax], al             
  0x0028EE9F  0000                    add      byte ptr [eax], al             
  0x0028EEA1  0000                    add      byte ptr [eax], al             
  0x0028EEA3  008cac65000200          add      byte ptr [esp + ebp*4 + 0x20065], cl 
  0x0028EEAA  0000                    add      byte ptr [eax], al             
