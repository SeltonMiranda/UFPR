;;int fib(n) {
;;        if (n <= 1)
;;                return n
;;        return fib(n-1) + fib(n-2)
;;}
        addi sp, sp, -1
main:
        addi a0, zero, 10
        jal ra, fibonacci
        ebreak
fibonacci:
        addi t0, zero, 1
        bge t0, a0, ret

        addi sp, sp, -12 
        sw sp, ra, 0
        sw sp, a0, 4

        addi a0, a0, -1
        ;; fib (n - 1)
        jal ra, fibonacci
        sw sp, a0, 8 ;; armazena retorno de fib(n - 1)

        lw a0, sp, 4 ;; carrega em a0 n - 1 + 1
        addi a0, a0, -2 ;; n - 2
        ;; fib(n - 2)
        jal ra, fibonacci
        lw t1, sp, 8 ;; carrega retorno de fib(n - 1)
        add a0, a0, t1 ;; soma retorno de fib(n - 2) + t1
        lw ra, sp, 0
        addi sp, sp, 12

        jalr zero, ra, 0
ret:
        jalr zero, ra, 0
