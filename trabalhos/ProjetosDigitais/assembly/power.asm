main:
        addi a0, zero, 2
        addi a1, zero, 3
        jal ra, power_of_n
        ebreak

power_of_n:
        addi t0, zero, 0
        addi t1, zero, 1
for:
        bge t0, a1, return

        mul t1, t1, a0
        addi t0, t0, 1
        jal zero, for
return:
        add a0, zero, t1
        jalr zero, ra, 0

