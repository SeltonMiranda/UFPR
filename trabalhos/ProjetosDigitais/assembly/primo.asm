        addi sp, zero, -1

main:
        addi a0, zero, 2 ; x = 2
        addi a1, zero, 7 ; y = 1000
        jal ra, soma_primos
        ebreak
        
; int soma_primos(int a, int b)
; s0 = i
; s1 = soma
; s2 = b
; a0 -> retorno
soma_primos:
        addi sp, sp, -16
        sw sp, s0, 0
        sw sp, s1, 4
        sw sp, s2, 8
        sw sp, ra, 12

        add s0, a0, zero ; i = a
        add s1, zero, zero ; soma = 0
        add s2, a1, zero ; b

while:
        blt s2, s0, ret
        add a0, s0, zero
        jal ra, primo
        add s1, s1, a0
        addi s0, s0, 1
        jal zero, while

ret:
        add a0, s1, zero ; return soma

        lw s0, sp, 0
        lw s1, sp, 4
        lw s2, sp, 8
        lw ra, sp, 12
        addi sp, sp, 16

        jalr zero, ra, 0


; a0 -> x
; t0 -> i
; t1 -> x / 2
primo:
        addi t0, zero, 2    
        srli t1, a0, 1 

for:
        bge t0, t1, ret_1 ; for (i = 2; i < x / 2; i++)
        rem t2, a0, t0
        beq t2, zero, ret_0 ; if (x % i == 0)
        addi t0, t0, 1
        jal zero, for

ret_1:
        addi a0, zero, 1
        jalr zero, ra, 0

ret_0:
        addi a0, zero, 0
        jalr zero, ra, 0
