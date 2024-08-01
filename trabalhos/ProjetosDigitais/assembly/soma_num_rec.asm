        addi sp, sp, -1
main:
        addi a0, zero, 4
        jal ra, soma_rec
        ebreak
soma_rec:
        addi t0, zero, 1
        bge t0, a0, ret_n
        
        addi sp, sp, -8
        sw sp, ra, 4
        sw sp, a0, 0

        addi a0, a0, -1
        jal ra, soma_rec

        lw ra, sp, 4
        lw t1, sp, 0 ; t1 = a0 anterior
        addi sp, sp, 8

        add a0, a0, t1 ; soma = a0 + a0 - 1
        jalr zero, ra, 0

ret_n:
        jalr zero, ra, 0

