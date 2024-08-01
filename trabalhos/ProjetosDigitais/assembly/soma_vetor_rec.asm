        addi sp, sp, -1
main:
        addi a0, zero, array 
        addi a1, zero, 0
        addi a2, zero, 4
        jal ra, soma_vetor_recursivo
        ebreak

soma_vetor_recursivo:
        bge a1, a2, ret

        sub t0, a2, a1
        srli t0, t0, 1
        add t0, t0, a1

        addi sp, sp, -24
        sw sp, ra, 0
        sw sp, s0, 4
        sw sp, s1, 8
        sw sp, s2, 12
        sw sp, s3, 16

        add s0, a0, zero
        add s1, a1, zero
        add s2, a2, zero
        add s3, t0, zero

        add a2, s3, zero
        jal ra, soma_vetor_recursivo
        sw sp, a0, 20 

        add a0, s0, zero
        addi a1, s3, 1
        add a2, s2, zero

        jal ra, soma_vetor_recursivo

        lw t1, sp, 20
        add a0, a0, t1

        lw ra, sp, 0
        lw s0, sp, 4
        lw s1, sp, 8
        lw s2, sp, 12
        lw s3, sp, 16
        addi sp, sp, 24

        jalr zero, ra, 0

ret:
        slli a1, a1, 2
        add a1, a1, a0
        lw a0, a1, 0
        jalr zero, ra, 0
array:
#%01%00%00%00
#%01%00%00%00
#%01%00%00%00
#%01%00%00%00
#%01%00%00%00
