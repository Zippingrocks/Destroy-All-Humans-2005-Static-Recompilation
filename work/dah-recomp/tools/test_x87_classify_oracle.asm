; Native x87/8-bit oracle, only linked into the isolated regression harness.
; Test-only FNINIT intentionally starts with a clean hardware x87 stack.
.code
dah_test_fxam PROC
    fninit
    fld qword ptr [rcx]
    fxam
    fnstsw ax
    fstp st(0)
    movzx eax, ax
    ret
dah_test_fxam ENDP
dah_test_status_byte PROC
    mov al, cl
    shl al, 1
    sar al, 1
    rol al, 1
    movzx eax, al
    ret
dah_test_status_byte ENDP
; Windows x64: RCX=&x, RDX=&y, R8=&binary64 output, R9=&status.
dah_test_fprem PROC
    fninit
    fld qword ptr [rdx]
    fld qword ptr [rcx]
fprem_loop:
    fprem
    fnstsw ax
    test ah, 4
    jnz fprem_loop
    fnstsw word ptr [r9]
    fstp qword ptr [r8]
    fstp st(0)
    ret
dah_test_fprem ENDP
dah_test_faddp PROC
    fninit
    fld qword ptr [rdx]
    fld qword ptr [rcx]
    faddp st(1), st(0)
    fnstsw word ptr [r9]
    fstp qword ptr [r8]
    ret
dah_test_faddp ENDP
; Raw ten-byte extended operands: unlike FLD m64, this preserves signaling
; encodings until the arithmetic instruction classifies them.
dah_test_faddp80 PROC
    fninit
    fld tbyte ptr [rdx]
    fld tbyte ptr [rcx]
    faddp st(1), st(0)
    fnstsw word ptr [r9]
    fstp qword ptr [r8]
    ret
dah_test_faddp80 ENDP
END
