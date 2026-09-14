; Function: sub_00217680
  0x00217680  8b542408                mov       edx, dword ptr [esp + 8]
  0x00217684  85d2                    test      edx, edx
  0x00217686  7442                    je        0x2176ca
  0x00217688  eb06                    jmp       0x217690
  0x0021768A  8d9b00000000            lea       ebx, [ebx]
  0x00217690  8b0d189f2900            mov       ecx, dword ptr [0x299f18]
  0x00217696  0fb601                  movzx     eax, byte ptr [ecx]
  0x00217699  8b0485109b2900          mov       eax, dword ptr [eax*4 + 0x299b10]
  0x002176A0  41                      inc       ecx
  0x002176A1  890d189f2900            mov       dword ptr [0x299f18], ecx
  0x002176A7  8b0d109f2900            mov       ecx, dword ptr [0x299f10]
  0x002176AD  8901                    mov       dword ptr [ecx], eax
  0x002176AF  8b0d109f2900            mov       ecx, dword ptr [0x299f10]
  0x002176B5  894104                  mov       dword ptr [ecx + 4], eax
  0x002176B8  8b0d109f2900            mov       ecx, dword ptr [0x299f10]
  0x002176BE  83c108                  add       ecx, 8
  0x002176C1  4a                      dec       edx
  0x002176C2  890d109f2900            mov       dword ptr [0x299f10], ecx
  0x002176C8  75c6                    jne       0x217690
  0x002176CA  c3                      ret       

; Function: sub_00217B70
  0x00217B70  8b442408                mov       eax, dword ptr [esp + 8]
  0x00217B74  85c0                    test      eax, eax
  0x00217B76  53                      push      ebx
  0x00217B77  8b5c2408                mov       ebx, dword ptr [esp + 8]
  0x00217B7B  0f84b6000000            je        0x217c37
  0x00217B81  55                      push      ebp
  0x00217B82  56                      push      esi
  0x00217B83  57                      push      edi
  0x00217B84  8be8                    mov       ebp, eax
  0x00217B86  eb08                    jmp       0x217b90
  0x00217B88  8da42400000000          lea       esp, [esp]
  0x00217B8F  90                      nop       
  0x00217B90  a1209f2900              mov       eax, dword ptr [0x299f20]
  0x00217B95  0fb600                  movzx     eax, byte ptr [eax]
  0x00217B98  8b0d249f2900            mov       ecx, dword ptr [0x299f24]
  0x00217B9E  0fb609                  movzx     ecx, byte ptr [ecx]
  0x00217BA1  c1e002                  shl       eax, 2
  0x00217BA4  8bb038a72900            mov       esi, dword ptr [eax + 0x29a738]
  0x00217BAA  8bb8389f2900            mov       edi, dword ptr [eax + 0x299f38]
  0x00217BB0  a1189f2900              mov       eax, dword ptr [0x299f18]
  0x00217BB5  c1e102                  shl       ecx, 2
  0x00217BB8  8b9138a32900            mov       edx, dword ptr [ecx + 0x29a338]
  0x00217BBE  8b8938ab2900            mov       ecx, dword ptr [ecx + 0x29ab38]
  0x00217BC4  03d6                    add       edx, esi
  0x00217BC6  0fb630                  movzx     esi, byte ptr [eax]
  0x00217BC9  8b34b5c05e2900          mov       esi, dword ptr [esi*4 + 0x295ec0]
  0x00217BD0  40                      inc       eax
  0x00217BD1  a3189f2900              mov       dword ptr [0x299f18], eax
  0x00217BD6  8b048e                  mov       eax, dword ptr [esi + ecx*4]
  0x00217BD9  8b0c96                  mov       ecx, dword ptr [esi + edx*4]
  0x00217BDC  8b15109f2900            mov       edx, dword ptr [0x299f10]
  0x00217BE2  c1e008                  shl       eax, 8
  0x00217BE5  0bc1                    or        eax, ecx
  0x00217BE7  8b0cbe                  mov       ecx, dword ptr [esi + edi*4]
  0x00217BEA  c1e008                  shl       eax, 8
  0x00217BED  0bc1                    or        eax, ecx
  0x00217BEF  8902                    mov       dword ptr [edx], eax
  0x00217BF1  8b0d109f2900            mov       ecx, dword ptr [0x299f10]
  0x00217BF7  8b15309f2900            mov       edx, dword ptr [0x299f30]
  0x00217BFD  89040a                  mov       dword ptr [edx + ecx], eax
  0x00217C00  8b15109f2900            mov       edx, dword ptr [0x299f10]
  0x00217C06  83c204                  add       edx, 4
  0x00217C09  43                      inc       ebx
  0x00217C0A  f6c301                  test      bl, 1
  0x00217C0D  8915109f2900            mov       dword ptr [0x299f10], edx
  0x00217C13  7518                    jne       0x217c2d
  0x00217C15  8b0d209f2900            mov       ecx, dword ptr [0x299f20]
  0x00217C1B  a1249f2900              mov       eax, dword ptr [0x299f24]
  0x00217C20  41                      inc       ecx
  0x00217C21  40                      inc       eax
  0x00217C22  890d209f2900            mov       dword ptr [0x299f20], ecx
  0x00217C28  a3249f2900              mov       dword ptr [0x299f24], eax
  0x00217C2D  4d                      dec       ebp
  0x00217C2E  0f855cffffff            jne       0x217b90
  0x00217C34  5f                      pop       edi
  0x00217C35  5e                      pop       esi
  0x00217C36  5d                      pop       ebp
  0x00217C37  5b                      pop       ebx
  0x00217C38  c3                      ret       

; Function: sub_00218530
  0x00218530  53                      push      ebx
  0x00218531  55                      push      ebp
  0x00218532  56                      push      esi
  0x00218533  57                      push      edi
  0x00218534  8b3d109f2900            mov       edi, dword ptr [0x299f10]
  0x0021853A  8b15189f2900            mov       edx, dword ptr [0x299f18]
  0x00218540  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x00218546  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x0021854C  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x00218550  c1e004                  shl       eax, 4
  0x00218553  03c7                    add       eax, edi
  0x00218555  a3109f2900              mov       dword ptr [0x299f10], eax
  0x0021855A  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x00218561  0f6e22                  movd      mm4, dword ptr [edx]
  0x00218564  0fefc0                  pxor      mm0, mm0
  0x00218567  33c0                    xor       eax, eax
  0x00218569  83c204                  add       edx, 4
  0x0021856C  8a4500                  mov       al, byte ptr [ebp]
  0x0021856F  0f60e0                  punpcklbw mm4, mm0
  0x00218572  0f6e148538b72900        movd      mm2, dword ptr [eax*4 + 0x29b738]
  0x0021857A  0f6e0c8538af2900        movd      mm1, dword ptr [eax*4 + 0x29af38]
  0x00218582  8a4501                  mov       al, byte ptr [ebp + 1]
  0x00218585  83c502                  add       ebp, 2
  0x00218588  0fd925d8a72500          psubusw   mm4, qword ptr [0x25a7d8]
  0x0021858F  0f6e348538b72900        movd      mm6, dword ptr [eax*4 + 0x29b738]
  0x00218597  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38]
  0x0021859F  8a03                    mov       al, byte ptr [ebx]
  0x002185A1  0f71f402                psllw     mm4, 2
  0x002185A5  0fe525e0a72500          pmulhw    mm4, qword ptr [0x25a7e0]
  0x002185AC  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x002185B4  0f6e1c8538bb2900        movd      mm3, dword ptr [eax*4 + 0x29bb38]
  0x002185BC  0ffdd5                  paddw     mm2, mm5
  0x002185BF  8a4301                  mov       al, byte ptr [ebx + 1]
  0x002185C2  83c302                  add       ebx, 2
  0x002185C5  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x002185CD  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38]
  0x002185D5  0ffdf5                  paddw     mm6, mm5
  0x002185D8  8a4500                  mov       al, byte ptr [ebp]
  0x002185DB  0f62d6                  punpckldq mm2, mm6
  0x002185DE  0f73d110                psrlq     mm1, 0x10
  0x002185E2  0f6e348538af2900        movd      mm6, dword ptr [eax*4 + 0x29af38]
  0x002185EA  0f73d210                psrlq     mm2, 0x10
  0x002185EE  0f6e2c8538b72900        movd      mm5, dword ptr [eax*4 + 0x29b738]
  0x002185F6  0f73d310                psrlq     mm3, 0x10
  0x002185FA  8a03                    mov       al, byte ptr [ebx]
  0x002185FC  0f73f630                psllq     mm6, 0x30
  0x00218600  0febce                  por       mm1, mm6
  0x00218603  0f6e348538b32900        movd      mm6, dword ptr [eax*4 + 0x29b338]
  0x0021860B  0ffdee                  paddw     mm5, mm6
  0x0021860E  0f6e348538bb2900        movd      mm6, dword ptr [eax*4 + 0x29bb38]
  0x00218616  0f73f530                psllq     mm5, 0x30
  0x0021861A  0f73f630                psllq     mm6, 0x30
  0x0021861E  0febd5                  por       mm2, mm5
  0x00218621  0febde                  por       mm3, mm6
  0x00218624  0ffdcc                  paddw     mm1, mm4
  0x00218627  0ffdd4                  paddw     mm2, mm4
  0x0021862A  0fedcf                  paddsw    mm1, mm7
  0x0021862D  0ffddc                  paddw     mm3, mm4
  0x00218630  0fd9cf                  psubusw   mm1, mm7
  0x00218633  0fedd7                  paddsw    mm2, mm7
  0x00218636  0f7fcc                  movq      mm4, mm1
  0x00218639  0fd9d7                  psubusw   mm2, mm7
  0x0021863C  0f61c8                  punpcklwd mm1, mm0
  0x0021863F  0f7fd5                  movq      mm5, mm2
  0x00218642  0f61d0                  punpcklwd mm2, mm0
  0x00218645  0feddf                  paddsw    mm3, mm7
  0x00218648  0f72f208                pslld     mm2, 8
  0x0021864C  0fd9df                  psubusw   mm3, mm7
  0x0021864F  0f69e0                  punpckhwd mm4, mm0
  0x00218652  0f7fde                  movq      mm6, mm3
  0x00218655  0f61d8                  punpcklwd mm3, mm0
  0x00218658  0f72f310                pslld     mm3, 0x10
  0x0021865C  0febca                  por       mm1, mm2
  0x0021865F  0febcb                  por       mm1, mm3
  0x00218662  0f69e8                  punpckhwd mm5, mm0
  0x00218665  0f69f0                  punpckhwd mm6, mm0
  0x00218668  0f72f508                pslld     mm5, 8
  0x0021866C  0f7f0f                  movq      qword ptr [edi], mm1
  0x0021866F  0f72f610                pslld     mm6, 0x10
  0x00218673  0febe5                  por       mm4, mm5
  0x00218676  83c710                  add       edi, 0x10
  0x00218679  0febe6                  por       mm4, mm6
  0x0021867C  a1109f2900              mov       eax, dword ptr [0x299f10]
  0x00218681  0f7f67f8                movq      qword ptr [edi - 8], mm4
  0x00218685  3bf8                    cmp       edi, eax
  0x00218687  0f82d4feffff            jb        0x218561
  0x0021868D  8915189f2900            mov       dword ptr [0x299f18], edx
  0x00218693  8b3d149f2900            mov       edi, dword ptr [0x299f14]
  0x00218699  8b151c9f2900            mov       edx, dword ptr [0x299f1c]
  0x0021869F  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x002186A5  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x002186AB  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x002186AF  c1e004                  shl       eax, 4
  0x002186B2  03c7                    add       eax, edi
  0x002186B4  a3149f2900              mov       dword ptr [0x299f14], eax
  0x002186B9  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x002186C0  0f6e22                  movd      mm4, dword ptr [edx]
  0x002186C3  0fefc0                  pxor      mm0, mm0
  0x002186C6  33c0                    xor       eax, eax
  0x002186C8  83c204                  add       edx, 4
  0x002186CB  8a4500                  mov       al, byte ptr [ebp]
  0x002186CE  0f60e0                  punpcklbw mm4, mm0
  0x002186D1  0f6e148538b72900        movd      mm2, dword ptr [eax*4 + 0x29b738]
  0x002186D9  0f6e0c8538af2900        movd      mm1, dword ptr [eax*4 + 0x29af38]
  0x002186E1  8a4501                  mov       al, byte ptr [ebp + 1]
  0x002186E4  83c502                  add       ebp, 2
  0x002186E7  0fd925d8a72500          psubusw   mm4, qword ptr [0x25a7d8]
  0x002186EE  0f6e348538b72900        movd      mm6, dword ptr [eax*4 + 0x29b738]
  0x002186F6  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38]
  0x002186FE  8a03                    mov       al, byte ptr [ebx]
  0x00218700  0f71f402                psllw     mm4, 2
  0x00218704  0fe525e0a72500          pmulhw    mm4, qword ptr [0x25a7e0]
  0x0021870B  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x00218713  0f6e1c8538bb2900        movd      mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021871B  0ffdd5                  paddw     mm2, mm5
  0x0021871E  8a4301                  mov       al, byte ptr [ebx + 1]
  0x00218721  83c302                  add       ebx, 2
  0x00218724  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021872C  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38]
  0x00218734  0ffdf5                  paddw     mm6, mm5
  0x00218737  8a4500                  mov       al, byte ptr [ebp]
  0x0021873A  0f62d6                  punpckldq mm2, mm6
  0x0021873D  0f73d110                psrlq     mm1, 0x10
  0x00218741  0f6e348538af2900        movd      mm6, dword ptr [eax*4 + 0x29af38]
  0x00218749  0f73d210                psrlq     mm2, 0x10
  0x0021874D  0f6e2c8538b72900        movd      mm5, dword ptr [eax*4 + 0x29b738]
  0x00218755  0f73d310                psrlq     mm3, 0x10
  0x00218759  8a03                    mov       al, byte ptr [ebx]
  0x0021875B  0f73f630                psllq     mm6, 0x30
  0x0021875F  0febce                  por       mm1, mm6
  0x00218762  0f6e348538b32900        movd      mm6, dword ptr [eax*4 + 0x29b338]
  0x0021876A  0ffdee                  paddw     mm5, mm6
  0x0021876D  0f6e348538bb2900        movd      mm6, dword ptr [eax*4 + 0x29bb38]
  0x00218775  0f73f530                psllq     mm5, 0x30
  0x00218779  0f73f630                psllq     mm6, 0x30
  0x0021877D  0febd5                  por       mm2, mm5
  0x00218780  0febde                  por       mm3, mm6
  0x00218783  0ffdcc                  paddw     mm1, mm4
  0x00218786  0ffdd4                  paddw     mm2, mm4
  0x00218789  0fedcf                  paddsw    mm1, mm7
  0x0021878C  0ffddc                  paddw     mm3, mm4
  0x0021878F  0fd9cf                  psubusw   mm1, mm7
  0x00218792  0fedd7                  paddsw    mm2, mm7
  0x00218795  0f7fcc                  movq      mm4, mm1
  0x00218798  0fd9d7                  psubusw   mm2, mm7
  0x0021879B  0f61c8                  punpcklwd mm1, mm0
  0x0021879E  0f7fd5                  movq      mm5, mm2
  0x002187A1  0f61d0                  punpcklwd mm2, mm0
  0x002187A4  0feddf                  paddsw    mm3, mm7
  0x002187A7  0f72f208                pslld     mm2, 8
  0x002187AB  0fd9df                  psubusw   mm3, mm7
  0x002187AE  0f69e0                  punpckhwd mm4, mm0
  0x002187B1  0f7fde                  movq      mm6, mm3
  0x002187B4  0f61d8                  punpcklwd mm3, mm0
  0x002187B7  0f72f310                pslld     mm3, 0x10
  0x002187BB  0febca                  por       mm1, mm2
  0x002187BE  0febcb                  por       mm1, mm3
  0x002187C1  0f69e8                  punpckhwd mm5, mm0
  0x002187C4  0f69f0                  punpckhwd mm6, mm0
  0x002187C7  0f72f508                pslld     mm5, 8
  0x002187CB  0f7f0f                  movq      qword ptr [edi], mm1
  0x002187CE  0f72f610                pslld     mm6, 0x10
  0x002187D2  0febe5                  por       mm4, mm5
  0x002187D5  83c710                  add       edi, 0x10
  0x002187D8  0febe6                  por       mm4, mm6
  0x002187DB  a1149f2900              mov       eax, dword ptr [0x299f14]
  0x002187E0  0f7f67f8                movq      qword ptr [edi - 8], mm4
  0x002187E4  3bf8                    cmp       edi, eax
  0x002187E6  0f82d4feffff            jb        0x2186c0
  0x002187EC  89151c9f2900            mov       dword ptr [0x299f1c], edx
  0x002187F2  892d209f2900            mov       dword ptr [0x299f20], ebp
  0x002187F8  891d249f2900            mov       dword ptr [0x299f24], ebx
  0x002187FE  5f                      pop       edi
  0x002187FF  5e                      pop       esi
  0x00218800  5d                      pop       ebp
  0x00218801  5b                      pop       ebx
  0x00218802  c20400                  ret       4

; Function: sub_0021F040
  0x0021F040  53                      push      ebx
  0x0021F041  55                      push      ebp
  0x0021F042  56                      push      esi
  0x0021F043  57                      push      edi
  0x0021F044  0f6f05d8a72500          movq      mm0, qword ptr [0x25a7d8]
  0x0021F04B  0f6f15b0a72500          movq      mm2, qword ptr [0x25a7b0]
  0x0021F052  0f6f2de0a72500          movq      mm5, qword ptr [0x25a7e0]
  0x0021F059  8b35109f2900            mov       esi, dword ptr [0x299f10]
  0x0021F05F  8b0d189f2900            mov       ecx, dword ptr [0x299f18]
  0x0021F065  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F069  c1e005                  shl       eax, 5
  0x0021F06C  03c6                    add       eax, esi
  0x0021F06E  8bff                    mov       edi, edi
  0x0021F070  0f6e19                  movd      mm3, dword ptr [ecx]
  0x0021F073  0fefe4                  pxor      mm4, mm4
  0x0021F076  0f6e7104                movd      mm6, dword ptr [ecx + 4]
  0x0021F07A  0f60dc                  punpcklbw mm3, mm4
  0x0021F07D  0fd9d8                  psubusw   mm3, mm0
  0x0021F080  0f60f4                  punpcklbw mm6, mm4
  0x0021F083  0fd9f0                  psubusw   mm6, mm0
  0x0021F086  0f71f302                psllw     mm3, 2
  0x0021F08A  0fe5dd                  pmulhw    mm3, mm5
  0x0021F08D  0f71f602                psllw     mm6, 2
  0x0021F091  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x0021F098  0fe5f5                  pmulhw    mm6, mm5
  0x0021F09B  83c108                  add       ecx, 8
  0x0021F09E  83c640                  add       esi, 0x40
  0x0021F0A1  0feddf                  paddsw    mm3, mm7
  0x0021F0A4  0fd9df                  psubusw   mm3, mm7
  0x0021F0A7  0fedf7                  paddsw    mm6, mm7
  0x0021F0AA  0f7fd9                  movq      mm1, mm3
  0x0021F0AD  0f61db                  punpcklwd mm3, mm3
  0x0021F0B0  0f69c9                  punpckhwd mm1, mm1
  0x0021F0B3  0fd5da                  pmullw    mm3, mm2
  0x0021F0B6  0fd5ca                  pmullw    mm1, mm2
  0x0021F0B9  0fd9f7                  psubusw   mm6, mm7
  0x0021F0BC  0f7ff4                  movq      mm4, mm6
  0x0021F0BF  0f61f6                  punpcklwd mm6, mm6
  0x0021F0C2  0f69e4                  punpckhwd mm4, mm4
  0x0021F0C5  0fd5f2                  pmullw    mm6, mm2
  0x0021F0C8  0f7fdf                  movq      mm7, mm3
  0x0021F0CB  0f62db                  punpckldq mm3, mm3
  0x0021F0CE  0f6aff                  punpckhdq mm7, mm7
  0x0021F0D1  0fd5e2                  pmullw    mm4, mm2
  0x0021F0D4  0f7f5ec0                movq      qword ptr [esi - 0x40], mm3
  0x0021F0D8  0f7fcb                  movq      mm3, mm1
  0x0021F0DB  0f7f7ec8                movq      qword ptr [esi - 0x38], mm7
  0x0021F0DF  0f62c9                  punpckldq mm1, mm1
  0x0021F0E2  0f6adb                  punpckhdq mm3, mm3
  0x0021F0E5  0f7ff7                  movq      mm7, mm6
  0x0021F0E8  0f7f4ed0                movq      qword ptr [esi - 0x30], mm1
  0x0021F0EC  0f62f6                  punpckldq mm6, mm6
  0x0021F0EF  0f7f5ed8                movq      qword ptr [esi - 0x28], mm3
  0x0021F0F3  0f6aff                  punpckhdq mm7, mm7
  0x0021F0F6  0f7f76e0                movq      qword ptr [esi - 0x20], mm6
  0x0021F0FA  0f7fe3                  movq      mm3, mm4
  0x0021F0FD  0f7f7ee8                movq      qword ptr [esi - 0x18], mm7
  0x0021F101  0f62e4                  punpckldq mm4, mm4
  0x0021F104  0f6adb                  punpckhdq mm3, mm3
  0x0021F107  3bf0                    cmp       esi, eax
  0x0021F109  0f7f66f0                movq      qword ptr [esi - 0x10], mm4
  0x0021F10D  0f7f5ef8                movq      qword ptr [esi - 8], mm3
  0x0021F111  0f8259ffffff            jb        0x21f070
  0x0021F117  8935109f2900            mov       dword ptr [0x299f10], esi
  0x0021F11D  890d189f2900            mov       dword ptr [0x299f18], ecx
  0x0021F123  8b3d149f2900            mov       edi, dword ptr [0x299f14]
  0x0021F129  8b151c9f2900            mov       edx, dword ptr [0x299f1c]
  0x0021F12F  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F133  c1e005                  shl       eax, 5
  0x0021F136  03c7                    add       eax, edi
  0x0021F138  8da42400000000          lea       esp, [esp]
  0x0021F13F  90                      nop       
  0x0021F140  0f6e1a                  movd      mm3, dword ptr [edx]
  0x0021F143  0fefe4                  pxor      mm4, mm4
  0x0021F146  0f6e7204                movd      mm6, dword ptr [edx + 4]
  0x0021F14A  0f60dc                  punpcklbw mm3, mm4
  0x0021F14D  0fd9d8                  psubusw   mm3, mm0
  0x0021F150  0f60f4                  punpcklbw mm6, mm4
  0x0021F153  0fd9f0                  psubusw   mm6, mm0
  0x0021F156  0f71f302                psllw     mm3, 2
  0x0021F15A  0fe5dd                  pmulhw    mm3, mm5
  0x0021F15D  0f71f602                psllw     mm6, 2
  0x0021F161  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x0021F168  0fe5f5                  pmulhw    mm6, mm5
  0x0021F16B  83c208                  add       edx, 8
  0x0021F16E  83c740                  add       edi, 0x40
  0x0021F171  0feddf                  paddsw    mm3, mm7
  0x0021F174  0fd9df                  psubusw   mm3, mm7
  0x0021F177  0fedf7                  paddsw    mm6, mm7
  0x0021F17A  0f7fd9                  movq      mm1, mm3
  0x0021F17D  0f61db                  punpcklwd mm3, mm3
  0x0021F180  0f69c9                  punpckhwd mm1, mm1
  0x0021F183  0fd5da                  pmullw    mm3, mm2
  0x0021F186  0fd5ca                  pmullw    mm1, mm2
  0x0021F189  0fd9f7                  psubusw   mm6, mm7
  0x0021F18C  0f7ff4                  movq      mm4, mm6
  0x0021F18F  0f61f6                  punpcklwd mm6, mm6
  0x0021F192  0f69e4                  punpckhwd mm4, mm4
  0x0021F195  0fd5f2                  pmullw    mm6, mm2
  0x0021F198  0f7fdf                  movq      mm7, mm3
  0x0021F19B  0f62db                  punpckldq mm3, mm3
  0x0021F19E  0f6aff                  punpckhdq mm7, mm7
  0x0021F1A1  0fd5e2                  pmullw    mm4, mm2
  0x0021F1A4  0f7f5fc0                movq      qword ptr [edi - 0x40], mm3
  0x0021F1A8  0f7fcb                  movq      mm3, mm1
  0x0021F1AB  0f7f7fc8                movq      qword ptr [edi - 0x38], mm7
  0x0021F1AF  0f62c9                  punpckldq mm1, mm1
  0x0021F1B2  0f6adb                  punpckhdq mm3, mm3
  0x0021F1B5  0f7ff7                  movq      mm7, mm6
  0x0021F1B8  0f7f4fd0                movq      qword ptr [edi - 0x30], mm1
  0x0021F1BC  0f62f6                  punpckldq mm6, mm6
  0x0021F1BF  0f7f5fd8                movq      qword ptr [edi - 0x28], mm3
  0x0021F1C3  0f6aff                  punpckhdq mm7, mm7
  0x0021F1C6  0f7f77e0                movq      qword ptr [edi - 0x20], mm6
  0x0021F1CA  0f7fe3                  movq      mm3, mm4
  0x0021F1CD  0f7f7fe8                movq      qword ptr [edi - 0x18], mm7
  0x0021F1D1  0f62e4                  punpckldq mm4, mm4
  0x0021F1D4  0f6adb                  punpckhdq mm3, mm3
  0x0021F1D7  3bf8                    cmp       edi, eax
  0x0021F1D9  0f7f67f0                movq      qword ptr [edi - 0x10], mm4
  0x0021F1DD  0f7f5ff8                movq      qword ptr [edi - 8], mm3
  0x0021F1E1  0f8259ffffff            jb        0x21f140
  0x0021F1E7  893d149f2900            mov       dword ptr [0x299f14], edi
  0x0021F1ED  89151c9f2900            mov       dword ptr [0x299f1c], edx
  0x0021F1F3  5f                      pop       edi
  0x0021F1F4  5e                      pop       esi
  0x0021F1F5  5d                      pop       ebp
  0x0021F1F6  5b                      pop       ebx
  0x0021F1F7  c20400                  ret       4

; Function: sub_0021F200
  0x0021F200  53                      push      ebx
  0x0021F201  55                      push      ebp
  0x0021F202  56                      push      esi
  0x0021F203  57                      push      edi
  0x0021F204  8b3d109f2900            mov       edi, dword ptr [0x299f10]
  0x0021F20A  8b15189f2900            mov       edx, dword ptr [0x299f18]
  0x0021F210  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x0021F216  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x0021F21C  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F220  c1e005                  shl       eax, 5
  0x0021F223  03c7                    add       eax, edi
  0x0021F225  a3109f2900              mov       dword ptr [0x299f10], eax
  0x0021F22A  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x0021F231  0f6e22                  movd      mm4, dword ptr [edx]
  0x0021F234  0fefc0                  pxor      mm0, mm0
  0x0021F237  33c0                    xor       eax, eax
  0x0021F239  83c204                  add       edx, 4
  0x0021F23C  8a4500                  mov       al, byte ptr [ebp]
  0x0021F23F  0f60e0                  punpcklbw mm4, mm0
  0x0021F242  0f6e148538b72900        movd      mm2, dword ptr [eax*4 + 0x29b738]
  0x0021F24A  0f6e0c8538af2900        movd      mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F252  8a4501                  mov       al, byte ptr [ebp + 1]
  0x0021F255  83c502                  add       ebp, 2
  0x0021F258  0fd925d8a72500          psubusw   mm4, qword ptr [0x25a7d8]
  0x0021F25F  0f6e348538b72900        movd      mm6, dword ptr [eax*4 + 0x29b738]
  0x0021F267  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F26F  8a03                    mov       al, byte ptr [ebx]
  0x0021F271  0f71f402                psllw     mm4, 2
  0x0021F275  0fe525e0a72500          pmulhw    mm4, qword ptr [0x25a7e0]
  0x0021F27C  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F284  0f6e1c8538bb2900        movd      mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F28C  0ffdd5                  paddw     mm2, mm5
  0x0021F28F  8a4301                  mov       al, byte ptr [ebx + 1]
  0x0021F292  83c302                  add       ebx, 2
  0x0021F295  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F29D  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F2A5  0ffdf5                  paddw     mm6, mm5
  0x0021F2A8  0f62d6                  punpckldq mm2, mm6
  0x0021F2AB  0ffdcc                  paddw     mm1, mm4
  0x0021F2AE  0ffdd4                  paddw     mm2, mm4
  0x0021F2B1  0fedcf                  paddsw    mm1, mm7
  0x0021F2B4  0ffddc                  paddw     mm3, mm4
  0x0021F2B7  0fd9cf                  psubusw   mm1, mm7
  0x0021F2BA  0fedd7                  paddsw    mm2, mm7
  0x0021F2BD  0f7fcc                  movq      mm4, mm1
  0x0021F2C0  0fd9d7                  psubusw   mm2, mm7
  0x0021F2C3  0f61c8                  punpcklwd mm1, mm0
  0x0021F2C6  0f7fd5                  movq      mm5, mm2
  0x0021F2C9  0f61d0                  punpcklwd mm2, mm0
  0x0021F2CC  0feddf                  paddsw    mm3, mm7
  0x0021F2CF  0f72f208                pslld     mm2, 8
  0x0021F2D3  0fd9df                  psubusw   mm3, mm7
  0x0021F2D6  0f69e0                  punpckhwd mm4, mm0
  0x0021F2D9  0f7fde                  movq      mm6, mm3
  0x0021F2DC  0f61d8                  punpcklwd mm3, mm0
  0x0021F2DF  0f72f310                pslld     mm3, 0x10
  0x0021F2E3  0febca                  por       mm1, mm2
  0x0021F2E6  0febcb                  por       mm1, mm3
  0x0021F2E9  0f69e8                  punpckhwd mm5, mm0
  0x0021F2EC  0f7fcb                  movq      mm3, mm1
  0x0021F2EF  0f69f0                  punpckhwd mm6, mm0
  0x0021F2F2  0f72f508                pslld     mm5, 8
  0x0021F2F6  83c720                  add       edi, 0x20
  0x0021F2F9  0f62c9                  punpckldq mm1, mm1
  0x0021F2FC  0febe5                  por       mm4, mm5
  0x0021F2FF  0f6adb                  punpckhdq mm3, mm3
  0x0021F302  0f7f4fe0                movq      qword ptr [edi - 0x20], mm1
  0x0021F306  0f72f610                pslld     mm6, 0x10
  0x0021F30A  0f7f5fe8                movq      qword ptr [edi - 0x18], mm3
  0x0021F30E  0febe6                  por       mm4, mm6
  0x0021F311  0f7fe6                  movq      mm6, mm4
  0x0021F314  0f62e4                  punpckldq mm4, mm4
  0x0021F317  0f6af6                  punpckhdq mm6, mm6
  0x0021F31A  a1109f2900              mov       eax, dword ptr [0x299f10]
  0x0021F31F  0f7f67f0                movq      qword ptr [edi - 0x10], mm4
  0x0021F323  0f7f77f8                movq      qword ptr [edi - 8], mm6
  0x0021F327  3bf8                    cmp       edi, eax
  0x0021F329  0f8202ffffff            jb        0x21f231
  0x0021F32F  8915189f2900            mov       dword ptr [0x299f18], edx
  0x0021F335  8b3d149f2900            mov       edi, dword ptr [0x299f14]
  0x0021F33B  8b151c9f2900            mov       edx, dword ptr [0x299f1c]
  0x0021F341  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x0021F347  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x0021F34D  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F351  c1e005                  shl       eax, 5
  0x0021F354  03c7                    add       eax, edi
  0x0021F356  a3149f2900              mov       dword ptr [0x299f14], eax
  0x0021F35B  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x0021F362  0f6e22                  movd      mm4, dword ptr [edx]
  0x0021F365  0fefc0                  pxor      mm0, mm0
  0x0021F368  33c0                    xor       eax, eax
  0x0021F36A  83c204                  add       edx, 4
  0x0021F36D  8a4500                  mov       al, byte ptr [ebp]
  0x0021F370  0f60e0                  punpcklbw mm4, mm0
  0x0021F373  0f6e148538b72900        movd      mm2, dword ptr [eax*4 + 0x29b738]
  0x0021F37B  0f6e0c8538af2900        movd      mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F383  8a4501                  mov       al, byte ptr [ebp + 1]
  0x0021F386  83c502                  add       ebp, 2
  0x0021F389  0fd925d8a72500          psubusw   mm4, qword ptr [0x25a7d8]
  0x0021F390  0f6e348538b72900        movd      mm6, dword ptr [eax*4 + 0x29b738]
  0x0021F398  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F3A0  8a03                    mov       al, byte ptr [ebx]
  0x0021F3A2  0f71f402                psllw     mm4, 2
  0x0021F3A6  0fe525e0a72500          pmulhw    mm4, qword ptr [0x25a7e0]
  0x0021F3AD  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F3B5  0f6e1c8538bb2900        movd      mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F3BD  0ffdd5                  paddw     mm2, mm5
  0x0021F3C0  8a4301                  mov       al, byte ptr [ebx + 1]
  0x0021F3C3  83c302                  add       ebx, 2
  0x0021F3C6  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F3CE  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F3D6  0ffdf5                  paddw     mm6, mm5
  0x0021F3D9  0f62d6                  punpckldq mm2, mm6
  0x0021F3DC  0ffdcc                  paddw     mm1, mm4
  0x0021F3DF  0ffdd4                  paddw     mm2, mm4
  0x0021F3E2  0fedcf                  paddsw    mm1, mm7
  0x0021F3E5  0ffddc                  paddw     mm3, mm4
  0x0021F3E8  0fd9cf                  psubusw   mm1, mm7
  0x0021F3EB  0fedd7                  paddsw    mm2, mm7
  0x0021F3EE  0f7fcc                  movq      mm4, mm1
  0x0021F3F1  0fd9d7                  psubusw   mm2, mm7
  0x0021F3F4  0f61c8                  punpcklwd mm1, mm0
  0x0021F3F7  0f7fd5                  movq      mm5, mm2
  0x0021F3FA  0f61d0                  punpcklwd mm2, mm0
  0x0021F3FD  0feddf                  paddsw    mm3, mm7
  0x0021F400  0f72f208                pslld     mm2, 8
  0x0021F404  0fd9df                  psubusw   mm3, mm7
  0x0021F407  0f69e0                  punpckhwd mm4, mm0
  0x0021F40A  0f7fde                  movq      mm6, mm3
  0x0021F40D  0f61d8                  punpcklwd mm3, mm0
  0x0021F410  0f72f310                pslld     mm3, 0x10
  0x0021F414  0febca                  por       mm1, mm2
  0x0021F417  0febcb                  por       mm1, mm3
  0x0021F41A  0f69e8                  punpckhwd mm5, mm0
  0x0021F41D  0f7fcb                  movq      mm3, mm1
  0x0021F420  0f69f0                  punpckhwd mm6, mm0
  0x0021F423  0f72f508                pslld     mm5, 8
  0x0021F427  83c720                  add       edi, 0x20
  0x0021F42A  0f62c9                  punpckldq mm1, mm1
  0x0021F42D  0febe5                  por       mm4, mm5
  0x0021F430  0f6adb                  punpckhdq mm3, mm3
  0x0021F433  0f7f4fe0                movq      qword ptr [edi - 0x20], mm1
  0x0021F437  0f72f610                pslld     mm6, 0x10
  0x0021F43B  0f7f5fe8                movq      qword ptr [edi - 0x18], mm3
  0x0021F43F  0febe6                  por       mm4, mm6
  0x0021F442  0f7fe6                  movq      mm6, mm4
  0x0021F445  0f62e4                  punpckldq mm4, mm4
  0x0021F448  0f6af6                  punpckhdq mm6, mm6
  0x0021F44B  a1149f2900              mov       eax, dword ptr [0x299f14]
  0x0021F450  0f7f67f0                movq      qword ptr [edi - 0x10], mm4
  0x0021F454  0f7f77f8                movq      qword ptr [edi - 8], mm6
  0x0021F458  3bf8                    cmp       edi, eax
  0x0021F45A  0f8202ffffff            jb        0x21f362
  0x0021F460  89151c9f2900            mov       dword ptr [0x299f1c], edx
  0x0021F466  892d209f2900            mov       dword ptr [0x299f20], ebp
  0x0021F46C  891d249f2900            mov       dword ptr [0x299f24], ebx
  0x0021F472  5f                      pop       edi
  0x0021F473  5e                      pop       esi
  0x0021F474  5d                      pop       ebp
  0x0021F475  5b                      pop       ebx
  0x0021F476  c20400                  ret       4

; Function: sub_0021F480
  0x0021F480  53                      push      ebx
  0x0021F481  55                      push      ebp
  0x0021F482  56                      push      esi
  0x0021F483  57                      push      edi
  0x0021F484  8b3d109f2900            mov       edi, dword ptr [0x299f10]
  0x0021F48A  8b15189f2900            mov       edx, dword ptr [0x299f18]
  0x0021F490  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x0021F496  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x0021F49C  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F4A0  c1e005                  shl       eax, 5
  0x0021F4A3  03c7                    add       eax, edi
  0x0021F4A5  a3109f2900              mov       dword ptr [0x299f10], eax
  0x0021F4AA  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x0021F4B1  0f6e22                  movd      mm4, dword ptr [edx]
  0x0021F4B4  0fefc0                  pxor      mm0, mm0
  0x0021F4B7  33c0                    xor       eax, eax
  0x0021F4B9  83c204                  add       edx, 4
  0x0021F4BC  8a4500                  mov       al, byte ptr [ebp]
  0x0021F4BF  0f60e0                  punpcklbw mm4, mm0
  0x0021F4C2  0f6e148538b72900        movd      mm2, dword ptr [eax*4 + 0x29b738]
  0x0021F4CA  0f6e0c8538af2900        movd      mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F4D2  8a4501                  mov       al, byte ptr [ebp + 1]
  0x0021F4D5  83c502                  add       ebp, 2
  0x0021F4D8  0fd925d8a72500          psubusw   mm4, qword ptr [0x25a7d8]
  0x0021F4DF  0f6e348538b72900        movd      mm6, dword ptr [eax*4 + 0x29b738]
  0x0021F4E7  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F4EF  8a03                    mov       al, byte ptr [ebx]
  0x0021F4F1  0f71f402                psllw     mm4, 2
  0x0021F4F5  0fe525e0a72500          pmulhw    mm4, qword ptr [0x25a7e0]
  0x0021F4FC  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F504  0f6e1c8538bb2900        movd      mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F50C  0ffdd5                  paddw     mm2, mm5
  0x0021F50F  8a4301                  mov       al, byte ptr [ebx + 1]
  0x0021F512  83c302                  add       ebx, 2
  0x0021F515  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F51D  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F525  0ffdf5                  paddw     mm6, mm5
  0x0021F528  8a4500                  mov       al, byte ptr [ebp]
  0x0021F52B  0f62d6                  punpckldq mm2, mm6
  0x0021F52E  0f73d110                psrlq     mm1, 0x10
  0x0021F532  0f6e348538af2900        movd      mm6, dword ptr [eax*4 + 0x29af38]
  0x0021F53A  0f73d210                psrlq     mm2, 0x10
  0x0021F53E  0f6e2c8538b72900        movd      mm5, dword ptr [eax*4 + 0x29b738]
  0x0021F546  0f73d310                psrlq     mm3, 0x10
  0x0021F54A  8a03                    mov       al, byte ptr [ebx]
  0x0021F54C  0f73f630                psllq     mm6, 0x30
  0x0021F550  0febce                  por       mm1, mm6
  0x0021F553  0f6e348538b32900        movd      mm6, dword ptr [eax*4 + 0x29b338]
  0x0021F55B  0ffdee                  paddw     mm5, mm6
  0x0021F55E  0f6e348538bb2900        movd      mm6, dword ptr [eax*4 + 0x29bb38]
  0x0021F566  0f73f530                psllq     mm5, 0x30
  0x0021F56A  0f73f630                psllq     mm6, 0x30
  0x0021F56E  0febd5                  por       mm2, mm5
  0x0021F571  0febde                  por       mm3, mm6
  0x0021F574  0ffdcc                  paddw     mm1, mm4
  0x0021F577  0ffdd4                  paddw     mm2, mm4
  0x0021F57A  0fedcf                  paddsw    mm1, mm7
  0x0021F57D  0ffddc                  paddw     mm3, mm4
  0x0021F580  0fd9cf                  psubusw   mm1, mm7
  0x0021F583  0fedd7                  paddsw    mm2, mm7
  0x0021F586  0f7fcc                  movq      mm4, mm1
  0x0021F589  0fd9d7                  psubusw   mm2, mm7
  0x0021F58C  0f61c8                  punpcklwd mm1, mm0
  0x0021F58F  0f7fd5                  movq      mm5, mm2
  0x0021F592  0f61d0                  punpcklwd mm2, mm0
  0x0021F595  0feddf                  paddsw    mm3, mm7
  0x0021F598  0f72f208                pslld     mm2, 8
  0x0021F59C  0fd9df                  psubusw   mm3, mm7
  0x0021F59F  0f69e0                  punpckhwd mm4, mm0
  0x0021F5A2  0f7fde                  movq      mm6, mm3
  0x0021F5A5  0f61d8                  punpcklwd mm3, mm0
  0x0021F5A8  0f72f310                pslld     mm3, 0x10
  0x0021F5AC  0febca                  por       mm1, mm2
  0x0021F5AF  0febcb                  por       mm1, mm3
  0x0021F5B2  0f69e8                  punpckhwd mm5, mm0
  0x0021F5B5  0f7fcb                  movq      mm3, mm1
  0x0021F5B8  0f69f0                  punpckhwd mm6, mm0
  0x0021F5BB  0f72f508                pslld     mm5, 8
  0x0021F5BF  83c720                  add       edi, 0x20
  0x0021F5C2  0f62c9                  punpckldq mm1, mm1
  0x0021F5C5  0febe5                  por       mm4, mm5
  0x0021F5C8  0f6adb                  punpckhdq mm3, mm3
  0x0021F5CB  0f7f4fe0                movq      qword ptr [edi - 0x20], mm1
  0x0021F5CF  0f72f610                pslld     mm6, 0x10
  0x0021F5D3  0f7f5fe8                movq      qword ptr [edi - 0x18], mm3
  0x0021F5D7  0febe6                  por       mm4, mm6
  0x0021F5DA  0f7fe6                  movq      mm6, mm4
  0x0021F5DD  0f62e4                  punpckldq mm4, mm4
  0x0021F5E0  0f6af6                  punpckhdq mm6, mm6
  0x0021F5E3  a1109f2900              mov       eax, dword ptr [0x299f10]
  0x0021F5E8  0f7f67f0                movq      qword ptr [edi - 0x10], mm4
  0x0021F5EC  0f7f77f8                movq      qword ptr [edi - 8], mm6
  0x0021F5F0  3bf8                    cmp       edi, eax
  0x0021F5F2  0f82b9feffff            jb        0x21f4b1
  0x0021F5F8  8915189f2900            mov       dword ptr [0x299f18], edx
  0x0021F5FE  8b3d149f2900            mov       edi, dword ptr [0x299f14]
  0x0021F604  8b151c9f2900            mov       edx, dword ptr [0x299f1c]
  0x0021F60A  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x0021F610  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x0021F616  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F61A  c1e005                  shl       eax, 5
  0x0021F61D  03c7                    add       eax, edi
  0x0021F61F  a3149f2900              mov       dword ptr [0x299f14], eax
  0x0021F624  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x0021F62B  0f6e22                  movd      mm4, dword ptr [edx]
  0x0021F62E  0fefc0                  pxor      mm0, mm0
  0x0021F631  33c0                    xor       eax, eax
  0x0021F633  83c204                  add       edx, 4
  0x0021F636  8a4500                  mov       al, byte ptr [ebp]
  0x0021F639  0f60e0                  punpcklbw mm4, mm0
  0x0021F63C  0f6e148538b72900        movd      mm2, dword ptr [eax*4 + 0x29b738]
  0x0021F644  0f6e0c8538af2900        movd      mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F64C  8a4501                  mov       al, byte ptr [ebp + 1]
  0x0021F64F  83c502                  add       ebp, 2
  0x0021F652  0fd925d8a72500          psubusw   mm4, qword ptr [0x25a7d8]
  0x0021F659  0f6e348538b72900        movd      mm6, dword ptr [eax*4 + 0x29b738]
  0x0021F661  0f620c8538af2900        punpckldq mm1, dword ptr [eax*4 + 0x29af38]
  0x0021F669  8a03                    mov       al, byte ptr [ebx]
  0x0021F66B  0f71f402                psllw     mm4, 2
  0x0021F66F  0fe525e0a72500          pmulhw    mm4, qword ptr [0x25a7e0]
  0x0021F676  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F67E  0f6e1c8538bb2900        movd      mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F686  0ffdd5                  paddw     mm2, mm5
  0x0021F689  8a4301                  mov       al, byte ptr [ebx + 1]
  0x0021F68C  83c302                  add       ebx, 2
  0x0021F68F  0f6e2c8538b32900        movd      mm5, dword ptr [eax*4 + 0x29b338]
  0x0021F697  0f621c8538bb2900        punpckldq mm3, dword ptr [eax*4 + 0x29bb38]
  0x0021F69F  0ffdf5                  paddw     mm6, mm5
  0x0021F6A2  8a4500                  mov       al, byte ptr [ebp]
  0x0021F6A5  0f62d6                  punpckldq mm2, mm6
  0x0021F6A8  0f73d110                psrlq     mm1, 0x10
  0x0021F6AC  0f6e348538af2900        movd      mm6, dword ptr [eax*4 + 0x29af38]
  0x0021F6B4  0f73d210                psrlq     mm2, 0x10
  0x0021F6B8  0f6e2c8538b72900        movd      mm5, dword ptr [eax*4 + 0x29b738]
  0x0021F6C0  0f73d310                psrlq     mm3, 0x10
  0x0021F6C4  8a03                    mov       al, byte ptr [ebx]
  0x0021F6C6  0f73f630                psllq     mm6, 0x30
  0x0021F6CA  0febce                  por       mm1, mm6
  0x0021F6CD  0f6e348538b32900        movd      mm6, dword ptr [eax*4 + 0x29b338]
  0x0021F6D5  0ffdee                  paddw     mm5, mm6
  0x0021F6D8  0f6e348538bb2900        movd      mm6, dword ptr [eax*4 + 0x29bb38]
  0x0021F6E0  0f73f530                psllq     mm5, 0x30
  0x0021F6E4  0f73f630                psllq     mm6, 0x30
  0x0021F6E8  0febd5                  por       mm2, mm5
  0x0021F6EB  0febde                  por       mm3, mm6
  0x0021F6EE  0ffdcc                  paddw     mm1, mm4
  0x0021F6F1  0ffdd4                  paddw     mm2, mm4
  0x0021F6F4  0fedcf                  paddsw    mm1, mm7
  0x0021F6F7  0ffddc                  paddw     mm3, mm4
  0x0021F6FA  0fd9cf                  psubusw   mm1, mm7
  0x0021F6FD  0fedd7                  paddsw    mm2, mm7
  0x0021F700  0f7fcc                  movq      mm4, mm1
  0x0021F703  0fd9d7                  psubusw   mm2, mm7
  0x0021F706  0f61c8                  punpcklwd mm1, mm0
  0x0021F709  0f7fd5                  movq      mm5, mm2
  0x0021F70C  0f61d0                  punpcklwd mm2, mm0
  0x0021F70F  0feddf                  paddsw    mm3, mm7
  0x0021F712  0f72f208                pslld     mm2, 8
  0x0021F716  0fd9df                  psubusw   mm3, mm7
  0x0021F719  0f69e0                  punpckhwd mm4, mm0
  0x0021F71C  0f7fde                  movq      mm6, mm3
  0x0021F71F  0f61d8                  punpcklwd mm3, mm0
  0x0021F722  0f72f310                pslld     mm3, 0x10
  0x0021F726  0febca                  por       mm1, mm2
  0x0021F729  0febcb                  por       mm1, mm3
  0x0021F72C  0f69e8                  punpckhwd mm5, mm0
  0x0021F72F  0f7fcb                  movq      mm3, mm1
  0x0021F732  0f69f0                  punpckhwd mm6, mm0
  0x0021F735  0f72f508                pslld     mm5, 8
  0x0021F739  83c720                  add       edi, 0x20
  0x0021F73C  0f62c9                  punpckldq mm1, mm1
  0x0021F73F  0febe5                  por       mm4, mm5
  0x0021F742  0f6adb                  punpckhdq mm3, mm3
  0x0021F745  0f7f4fe0                movq      qword ptr [edi - 0x20], mm1
  0x0021F749  0f72f610                pslld     mm6, 0x10
  0x0021F74D  0f7f5fe8                movq      qword ptr [edi - 0x18], mm3
  0x0021F751  0febe6                  por       mm4, mm6
  0x0021F754  0f7fe6                  movq      mm6, mm4
  0x0021F757  0f62e4                  punpckldq mm4, mm4
  0x0021F75A  0f6af6                  punpckhdq mm6, mm6
  0x0021F75D  a1149f2900              mov       eax, dword ptr [0x299f14]
  0x0021F762  0f7f67f0                movq      qword ptr [edi - 0x10], mm4
  0x0021F766  0f7f77f8                movq      qword ptr [edi - 8], mm6
  0x0021F76A  3bf8                    cmp       edi, eax
  0x0021F76C  0f82b9feffff            jb        0x21f62b
  0x0021F772  89151c9f2900            mov       dword ptr [0x299f1c], edx
  0x0021F778  892d209f2900            mov       dword ptr [0x299f20], ebp
  0x0021F77E  891d249f2900            mov       dword ptr [0x299f24], ebx
  0x0021F784  5f                      pop       edi
  0x0021F785  5e                      pop       esi
  0x0021F786  5d                      pop       ebp
  0x0021F787  5b                      pop       ebx
  0x0021F788  c20400                  ret       4

; Function: sub_0021F7A0
  0x0021F7A0  53                      push      ebx
  0x0021F7A1  55                      push      ebp
  0x0021F7A2  56                      push      esi
  0x0021F7A3  57                      push      edi
  0x0021F7A4  0f6f3de8a72500          movq      mm7, qword ptr [0x25a7e8]
  0x0021F7AB  0f6f05d8a72500          movq      mm0, qword ptr [0x25a7d8]
  0x0021F7B2  0f6f15c0a72500          movq      mm2, qword ptr [0x25a7c0]
  0x0021F7B9  0f6f2de0a72500          movq      mm5, qword ptr [0x25a7e0]
  0x0021F7C0  8b35109f2900            mov       esi, dword ptr [0x299f10]
  0x0021F7C6  8b0d189f2900            mov       ecx, dword ptr [0x299f18]
  0x0021F7CC  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F7D0  c1e004                  shl       eax, 4
  0x0021F7D3  03c6                    add       eax, esi
  0x0021F7D5  8da42400000000          lea       esp, [esp]
  0x0021F7DC  8d642400                lea       esp, [esp]
  0x0021F7E0  0f6e19                  movd      mm3, dword ptr [ecx]
  0x0021F7E3  0fefe4                  pxor      mm4, mm4
  0x0021F7E6  0f6e7104                movd      mm6, dword ptr [ecx + 4]
  0x0021F7EA  0f60dc                  punpcklbw mm3, mm4
  0x0021F7ED  0fd9d8                  psubusw   mm3, mm0
  0x0021F7F0  0f60f4                  punpcklbw mm6, mm4
  0x0021F7F3  0fd9f0                  psubusw   mm6, mm0
  0x0021F7F6  0f71f302                psllw     mm3, 2
  0x0021F7FA  0fe5dd                  pmulhw    mm3, mm5
  0x0021F7FD  0f71f602                psllw     mm6, 2
  0x0021F801  0fe5f5                  pmulhw    mm6, mm5
  0x0021F804  90                      nop       
  0x0021F805  83c108                  add       ecx, 8
  0x0021F808  83c620                  add       esi, 0x20
  0x0021F80B  0feddf                  paddsw    mm3, mm7
  0x0021F80E  0fd9df                  psubusw   mm3, mm7
  0x0021F811  0fedf7                  paddsw    mm6, mm7
  0x0021F814  0f7fd9                  movq      mm1, mm3
  0x0021F817  0f61db                  punpcklwd mm3, mm3
  0x0021F81A  0f69c9                  punpckhwd mm1, mm1
  0x0021F81D  0fd5da                  pmullw    mm3, mm2
  0x0021F820  0fd5ca                  pmullw    mm1, mm2
  0x0021F823  0fd9f7                  psubusw   mm6, mm7
  0x0021F826  0f7ff4                  movq      mm4, mm6
  0x0021F829  0f61f6                  punpcklwd mm6, mm6
  0x0021F82C  0f69e4                  punpckhwd mm4, mm4
  0x0021F82F  0fd5f2                  pmullw    mm6, mm2
  0x0021F832  0f7f5ee0                movq      qword ptr [esi - 0x20], mm3
  0x0021F836  0fd5e2                  pmullw    mm4, mm2
  0x0021F839  0f7f4ee8                movq      qword ptr [esi - 0x18], mm1
  0x0021F83D  0f7f76f0                movq      qword ptr [esi - 0x10], mm6
  0x0021F841  0f7f66f8                movq      qword ptr [esi - 8], mm4
  0x0021F845  3bf0                    cmp       esi, eax
  0x0021F847  7297                    jb        0x21f7e0
  0x0021F849  8935109f2900            mov       dword ptr [0x299f10], esi
  0x0021F84F  890d189f2900            mov       dword ptr [0x299f18], ecx
  0x0021F855  8b3d149f2900            mov       edi, dword ptr [0x299f14]
  0x0021F85B  8b151c9f2900            mov       edx, dword ptr [0x299f1c]
  0x0021F861  8b442414                mov       eax, dword ptr [esp + 0x14]
  0x0021F865  c1e004                  shl       eax, 4
  0x0021F868  03c7                    add       eax, edi
  0x0021F86A  8d9b00000000            lea       ebx, [ebx]
  0x0021F870  0f6e1a                  movd      mm3, dword ptr [edx]
  0x0021F873  0fefe4                  pxor      mm4, mm4
  0x0021F876  0f6e7204                movd      mm6, dword ptr [edx + 4]
  0x0021F87A  0f60dc                  punpcklbw mm3, mm4
  0x0021F87D  0fd9d8                  psubusw   mm3, mm0
  0x0021F880  0f60f4                  punpcklbw mm6, mm4
  0x0021F883  0fd9f0                  psubusw   mm6, mm0
  0x0021F886  0f71f302                psllw     mm3, 2
  0x0021F88A  0fe5dd                  pmulhw    mm3, mm5
  0x0021F88D  0f71f602                psllw     mm6, 2
  0x0021F891  0fe5f5                  pmulhw    mm6, mm5
  0x0021F894  90                      nop       
  0x0021F895  83c208                  add       edx, 8
  0x0021F898  83c720                  add       edi, 0x20
  0x0021F89B  0feddf                  paddsw    mm3, mm7
  0x0021F89E  0fd9df                  psubusw   mm3, mm7
  0x0021F8A1  0fedf7                  paddsw    mm6, mm7
  0x0021F8A4  0f7fd9                  movq      mm1, mm3
  0x0021F8A7  0f61db                  punpcklwd mm3, mm3
  0x0021F8AA  0f69c9                  punpckhwd mm1, mm1
  0x0021F8AD  0fd5da                  pmullw    mm3, mm2
  0x0021F8B0  0fd5ca                  pmullw    mm1, mm2
  0x0021F8B3  0fd9f7                  psubusw   mm6, mm7
  0x0021F8B6  0f7ff4                  movq      mm4, mm6
  0x0021F8B9  0f61f6                  punpcklwd mm6, mm6
  0x0021F8BC  0f69e4                  punpckhwd mm4, mm4
  0x0021F8BF  0fd5f2                  pmullw    mm6, mm2
  0x0021F8C2  0f7f5fe0                movq      qword ptr [edi - 0x20], mm3
  0x0021F8C6  0fd5e2                  pmullw    mm4, mm2
  0x0021F8C9  0f7f4fe8                movq      qword ptr [edi - 0x18], mm1
  0x0021F8CD  0f7f77f0                movq      qword ptr [edi - 0x10], mm6
  0x0021F8D1  0f7f67f8                movq      qword ptr [edi - 8], mm4
  0x0021F8D5  3bf8                    cmp       edi, eax
  0x0021F8D7  7297                    jb        0x21f870
  0x0021F8D9  893d149f2900            mov       dword ptr [0x299f14], edi
  0x0021F8DF  89151c9f2900            mov       dword ptr [0x299f1c], edx
  0x0021F8E5  5f                      pop       edi
  0x0021F8E6  5e                      pop       esi
  0x0021F8E7  5d                      pop       ebp
  0x0021F8E8  5b                      pop       ebx
  0x0021F8E9  c20400                  ret       4

; Function: sub_0021E4B0
  0x0021E4B0  53                      push      ebx
  0x0021E4B1  55                      push      ebp
  0x0021E4B2  56                      push      esi
  0x0021E4B3  57                      push      edi
  0x0021E4B4  8b3d109f2900            mov       edi, dword ptr [0x299f10]
  0x0021E4BA  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x0021E4C0  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x0021E4C6  8b15189f2900            mov       edx, dword ptr [0x299f18]
  0x0021E4CC  8b4c2414                mov       ecx, dword ptr [esp + 0x14]
  0x0021E4D0  8d4ccff0                lea       ecx, [edi + ecx*8 - 0x10]
  0x0021E4D4  8da42400000000          lea       esp, [esp]
  0x0021E4DB  0500000000              add       eax, 0
  0x0021E4E0  0f6e4d00                movd      mm1, dword ptr [ebp]
  0x0021E4E4  0f6e13                  movd      mm2, dword ptr [ebx]
  0x0021E4E7  0f6f32                  movq      mm6, qword ptr [edx]
  0x0021E4EA  0f60ca                  punpcklbw mm1, mm2
  0x0021E4ED  0f7ff7                  movq      mm7, mm6
  0x0021E4F0  0f60f1                  punpcklbw mm6, mm1
  0x0021E4F3  83c504                  add       ebp, 4
  0x0021E4F6  83c304                  add       ebx, 4
  0x0021E4F9  0f7f37                  movq      qword ptr [edi], mm6
  0x0021E4FC  0f68f9                  punpckhbw mm7, mm1
  0x0021E4FF  83c208                  add       edx, 8
  0x0021E502  3bf9                    cmp       edi, ecx
  0x0021E504  0f7f7f08                movq      qword ptr [edi + 8], mm7
  0x0021E508  8d7f10                  lea       edi, [edi + 0x10]
  0x0021E50B  72d3                    jb        0x21e4e0
  0x0021E50D  893d109f2900            mov       dword ptr [0x299f10], edi
  0x0021E513  8915189f2900            mov       dword ptr [0x299f18], edx
  0x0021E519  8b3d149f2900            mov       edi, dword ptr [0x299f14]
  0x0021E51F  8b2d209f2900            mov       ebp, dword ptr [0x299f20]
  0x0021E525  8b1d249f2900            mov       ebx, dword ptr [0x299f24]
  0x0021E52B  8b151c9f2900            mov       edx, dword ptr [0x299f1c]
  0x0021E531  8b4c2414                mov       ecx, dword ptr [esp + 0x14]
  0x0021E535  8d4ccff0                lea       ecx, [edi + ecx*8 - 0x10]
  0x0021E539  8da42400000000          lea       esp, [esp]
  0x0021E540  0f6e4d00                movd      mm1, dword ptr [ebp]
  0x0021E544  0f6e13                  movd      mm2, dword ptr [ebx]
  0x0021E547  0f6f32                  movq      mm6, qword ptr [edx]
  0x0021E54A  0f60ca                  punpcklbw mm1, mm2
  0x0021E54D  0f7ff7                  movq      mm7, mm6
  0x0021E550  0f60f1                  punpcklbw mm6, mm1
  0x0021E553  83c504                  add       ebp, 4
  0x0021E556  83c304                  add       ebx, 4
  0x0021E559  0f7f37                  movq      qword ptr [edi], mm6
  0x0021E55C  0f68f9                  punpckhbw mm7, mm1
  0x0021E55F  83c208                  add       edx, 8
  0x0021E562  3bf9                    cmp       edi, ecx
  0x0021E564  0f7f7f08                movq      qword ptr [edi + 8], mm7
  0x0021E568  8d7f10                  lea       edi, [edi + 0x10]
  0x0021E56B  72d3                    jb        0x21e540
  0x0021E56D  893d149f2900            mov       dword ptr [0x299f14], edi
  0x0021E573  892d209f2900            mov       dword ptr [0x299f20], ebp
  0x0021E579  891d249f2900            mov       dword ptr [0x299f24], ebx
  0x0021E57F  89151c9f2900            mov       dword ptr [0x299f1c], edx
  0x0021E585  5f                      pop       edi
  0x0021E586  5e                      pop       esi
  0x0021E587  5d                      pop       ebp
  0x0021E588  5b                      pop       ebx
  0x0021E589  c20400                  ret       4

