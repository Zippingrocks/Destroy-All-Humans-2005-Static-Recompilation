; Win64 float arguments arrive in XMM0 and XMM1. Return AH plus the actual
; parity result from the retail TEST AH,44h in bit 8. No game or GUI involved.
.code
hardware_ucomiss_lahf PROC
    ucomiss xmm0, xmm1
    lahf
    test ah, 44h
    setp dl
    movzx eax, ah
    movzx edx, dl
    shl edx, 8
    or eax, edx
    ret
hardware_ucomiss_lahf ENDP

hardware_comiss_lahf PROC
    comiss xmm0, xmm1
    lahf
    test ah, 44h
    setp dl
    movzx eax, ah
    movzx edx, dl
    shl edx, 8
    or eax, edx
    ret
hardware_comiss_lahf ENDP
END
