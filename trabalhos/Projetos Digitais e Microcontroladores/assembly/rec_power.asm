        addi sp, sp, -1
main:
        addi a0, zero, 2
        addi a1, zero, 3
        jal ra, power
        ebreak
power:
        addi t0, zero, 0
        beq t0, a1, ret_0
        
        addi sp, sp, -12
        sw sp, ra, 0
        sw sp, a0, 4
        sw sp, a1, 8

        addi a1, a1, -1
        jal ra, power

        lw t1, sp, 4
        mul a0, a0, t1

        lw ra, sp, 0
        lw a1, sp, 8
        addi sp, sp, 12

        jalr zero, ra, 0

ret_0:
        addi a0, zero, 1
        jalr zero, ra, 0
