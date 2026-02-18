main:
        addi s0, zero, 0x41
        addi s1, zero, 0x45

for:
        blt s1, s0, endProgram

        add a0, s0, zero
        jal ra, vogal

        add s2, a0, zero
        sub t0, s0, s2
        addi s0, s0, 1
        jal zero, for

endProgram:
        ebreak

vogal:
        addi t1, zero, 0x61
        beq a0, t1, ret_1

        addi t1, zero, 0x41
        beq a0, t1, ret_1

        addi t1, zero, 0x65
        beq a0, t1, ret_1

        addi t1, zero, 0x45
        beq a0, t1, ret_1

        addi t1, zero, 0x69
        beq a0, t1, ret_1

        addi t1, zero, 0x49
        beq a0, t1, ret_1

        addi t1, zero, 0x6f
        beq a0, t1, ret_1

        addi t1, zero, 0x4f
        beq a0, t1, ret_1

        addi t1, zero, 0x75
        beq a0, t1, ret_1

        addi t1, zero, 0x55
        bne a0, t1, ret_0

ret_1:
        addi a0, zero, 1
        jalr zero, ra, 0
        
ret_0:
        addi a0, zero, 0
        jalr zero, ra, 0
