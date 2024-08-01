        addi sp, sp, -1
main:
        addi a0, zero, array ;; &array
        addi a1, zero, 5 ;; n
        jal ra, minimoVetor
        ebreak

minimoVetor:
        addi t0, zero, 1
        beq a1, t0, ret

        addi sp, sp, -12
        sw sp, ra, 8
        sw sp, a0, 4
        sw sp, a1, 0

        addi a1, a1, -1 ;; a1 = n - 1
        jal ra, minimoVetor

        add a1, a0, zero
        lw t0, sp, 4 ;; t0 recebe &array
        lw t1, sp, 0 ;; t1 recebe n que estava na pilha

        ;; buscando o valor no endereco do vetor
        addi t1, t1, -1 ;; n = n - 1
        slli t1, t1, 2
        add t0, t0, t1
        lw t2, t0, 0

        add a1, a0, zero
        add a0, t2, zero
        jal ra, min
        
        lw ra, sp, 8
        addi sp, sp, 12
        jalr zero, ra, 0

ret:
        lw a0, a0, 0 ;; a0 recebe array[0]
        jalr zero, ra, 0

min:
        bge a0, a1, ret_min
        jalr zero, ra, 0
ret_min:
        add a0, a1, zero
        jalr zero, ra, 0

array:
#%09%00%00%00
#%03%00%00%00
#%04%00%00%00
#%05%00%00%00
#%06%00%00%00
