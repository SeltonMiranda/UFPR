; s0 = i
; s1 = s
; s2 = b


soma_primos:
        addi sp, sp, -16
        sw sp, s0, 0
        sw sp, s1, 4
        sw sp, s2, 8
        sw sp, ra, 12

        add s0, zero, a0
        add s1, zero, zero
        addi s2, zero, a1

wh:
        blt s2, s0, fora_w
        add a0, s0, zero
        jal ra, primo
        add s1, s1, v0
        addi s0, s0, 1
        jal zero, wh

fora_w:
        add v0, s1, zero
        lw s0, sp, 0
        lw s1, sp, 4
        lw s2, sp, 8
        lw ra, sp, 12
        jalr zero, ra, 0
