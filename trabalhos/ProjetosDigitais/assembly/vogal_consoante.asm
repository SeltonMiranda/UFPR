        addi sp, sp, -1
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
        addi sp, sp, -12 
        sw sp, ra, 8
        sw sp, s0, 4
        sw sp, s1, 0
        
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
        ;;lw ra, sp, 8
        ;;lw s0, sp, 4
        ;;lw s1, sp, 0
        ;;addi sp, sp, 12
        jalr zero, ra, 0
        
ret_0:
        addi a0, zero, 0
        ;;lw ra, sp, 8
        ;;lw s0, sp, 4
        ;;lw s1, sp, 0
        ;;addi sp, sp, 12
        jalr zero, ra, 0
