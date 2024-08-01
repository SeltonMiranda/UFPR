        addi sp, sp, -1
main:
        addi a0, zero, 2
        addi a1, zero, 3
        jal ra, power
        ebreak
power:
        addi t0, zero, 0
        beq t0, a1, ret_1
        
        addi sp, sp, -20
        sw sp, ra, 0
        sw sp, s0, 4
        sw sp, s1, 8
        sw sp, s2, 12

        add s0, a0, zero
        add s1, a1, zero

        addi t1, zero, 2
        rem t2, a1, t1
        beq a1, t0, ret_2
        
        srli a1, a1, 1
        add s2, a1, zero

        jal ra, power

        sw sp, a0, 16
        add a0, s0, zero
        add a1, s2, zero
        jal ra, power

        lw t3, sp, 16
        mul a0, a0, t3
        add t3, s0, zero
        mul a0, a0, t3

        lw ra, sp, 0
        lw s1, sp, 8
        lw s2, sp, 12
        addi sp, sp, 20

        jalr zero, ra, 0

ret_2:
        srli a1, a1, 1
        add s2, a1, zero
        jal ra, power

        sw sp, a0, 16
        add a0, s0, zero
        add a1, s2, zero
        jal ra, power

        lw t3, sp, 16
        mul a0, a0, t3
        lw ra, sp, 0
        lw s0, sp, 4
        lw s1, sp, 8
        lw s2, sp, 12
        addi sp, sp, 20

        jalr zero, ra, 0

ret_1:
        addi a0, zero, 1
        jalr zero, ra, 0
