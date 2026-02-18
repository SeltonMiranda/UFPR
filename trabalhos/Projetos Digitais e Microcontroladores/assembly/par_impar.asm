        addi sp, sp, -1
main:
        addi a0, zero, 11
        jal ra, par 
        addi t0, a0, 0

        bne t0, zero, ehpar
        addi t1, zero, 3
        ebreak
ehpar:
        addi t1, zero, 2
        ebreak
        
par:
        addi sp, sp, -8
        sw sp, ra, 4
        sw sp, s0, 0

        addi t5, zero, 2
        rem s0, a0, t5
        beq s0, zero, ret_1
        jal zero, ret_0

ret_1:
        addi a0, zero, 1
        addi sp, sp, 8
        jalr zero, ra, 0

ret_0:
        addi a0, zero, 0
        addi sp, sp, 8
        jalr zero, ra, 0
