        addi sp, sp, -1

; s0 == i
; s1 == num2
main:
        addi s0, zero, 2
        addi s1, zero, 12
        addi s3, zero, 1
        
for:
        bge s0, s1, end

        add a0, s0, zero
        jal ra, primo
        add s2, a0, zero

        addi s0, s0, 1
        bne s2, s3, for

        add s4, s4, s2
        jal zero, for
end:
        ebreak

primo:
        addi sp, sp, -20
        sw sp, ra, 16
        sw sp, s0, 12
        sw sp, s1, 8
        sw sp, s2, 4
        sw sp, s3, 0
        add t3, a0, zero

        addi t0, zero, 2
        srli t1, t3, 1

for_primo:
        blt t1, t0, ret_1
        
        rem t2, t3, t0
        beq t2, zero, ret_0

        addi t0, t0, 1
        jal zero, for_primo

ret_1:
        addi a0, zero, 1
        jalr zero, ra, 0

ret_0:
        addi a0, zero, 0
        jalr zero, ra, 0
