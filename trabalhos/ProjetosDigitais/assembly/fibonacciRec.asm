; repeticao, funcoes com convencoes, uso de funçoes com pilha

; int fib(int n)
        addi a0, zero, 3

fib:
        addi t0, zero, 1
        beq, a0, zero, ret1
        beq, a0, t0, ret1
        jal zero, fora_if
ret1:
        addi v0, zero, 1 ; v[0] = 1
        jalr zero, ra, 0

fora_if:
        addi sp, sp, -12
        sw sp, ra, 0
        sw sp, a0, 4
        
        ;fib(n-1)
        addi a0, a0, -1
        jal ra, fib
        sw sp, v0, 8

        lw a0, sp, 4
        addi a0, a0, -2
        jal ra, fib

        lw t1, sp, 8 ; t1 -> valor de fib(n-1)
        add v0, v0, t1 ; v0 -> v0 (valor de fib(n-1))

        lw ra, sp, 0
        addi sp, sp, 12

        jalr zero, ra, 0
