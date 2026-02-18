        addi sp, sp, -1
main:
        addi a0, zero, array
        addi a1, zero, 5
        jal ra, minVet
        ebreak
minVet:
        addi t0, zero, 1
        beq a1, t0, return

        addi sp, sp, -12
        sw sp, ra, 0
        sw sp, s0, 4
        sw sp, s1, 8

        add s0, a0, zero
        add s1, a1, zero

        addi a1, a1, -1
        jal ra, minVet

        add a1, s1, zero
        addi a1, a1, -1
        add a1, a1, s0
        lw a1, a1, 0
        jal ra, min

        lw ra, sp, 0
        lw s0, sp, 4
        lw s1, sp, 8
        addi sp, sp, 12
        jalr zero, ra, 0

min:
        blt a0, a1, ret_a0
        addi a0, a1, 0
        jalr zero, ra, 0
ret_a0:
        jalr zero, ra, 0
return:
        lw a0, a0, 0
        jalr zero, ra, 0

array:
#%09%00%00%00
#%03%00%00%00
#%04%00%00%00
#%05%00%00%00
#%06%00%00%00
