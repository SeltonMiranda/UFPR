        addi sp, zero, -1

        addi a0, zero, vetor ; &vetor
        addi a1, zero, 0 ; a = 0
        addi a2, zero, 4 ; b = 4
        addi a3, zero, 3 ; x = 3
        jal ra, busca
        ebreak

busca:
        blt a2, a1, ret0

        add t0, a2, zero ; t0 = b
        slli t0, t0, 2 ; t0 = b * 4
        add t1, a0, t0; t1 = &vetor + b * 4
        lw t2, t1, 0 ; t2 = *(&vetor + b * 4)
        beq t2, a3, ret1

        addi sp, sp, -8
        sw sp, ra, 4
        sw sp, a2, 0

        addi a2, a2, -1 ; b = b - 1
        jal ra, busca
        
        lw a2, sp, 0
        lw ra, sp, 4
        addi sp, sp, 8

        jalr zero, ra, 0

ret0:
        addi a4, zero, 0
        jalr zero, ra, 0

ret1:
        add a4, zero, a2
        jalr zero, ra, 0

vetor:
#%01%00%00%00
#%02%00%00%00
#%03%00%00%00
#%04%00%00%00
#%05%00%00%00
