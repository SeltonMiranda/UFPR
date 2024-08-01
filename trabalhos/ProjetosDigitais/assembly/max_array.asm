        addi sp, sp, -1
main:
        addi a0, zero, vetor
        addi a1, zero, 5
        jal ra, maior_array
        ebreak


; s0 = &vetor
; s1 = n
; s2 = max
; s3 = i
maior_array:
        addi sp, sp, -20
        sw sp, s0, 16
        sw sp, s1, 12
        sw sp, s2, 8
        sw sp, s3, 4
        sw sp, ra, 0
        
        add s0, a0, zero ; s0 = &vetor
        add s1, a1, zero ; s1 = n
        lw s2, s0, 0 ; s2 = *(&vetor)
        addi s3, zero, 1

for:
        bge s3, s1, ret
        slli t0, s3, 2
        add t0, t0, s0
        lw t1, t0, 0

        bge s2, t1, skip
        addi s2, t1, 0
skip:
        addi s3, s3, 1
        jal zero, for
ret:
        addi a0, s2, 0
        lw s0, sp, 16
        lw s1, sp, 12
        lw s2, sp, 8
        lw s3, sp, 4
        lw ra, sp, 0
        addi sp, sp, 20

        jalr zero, ra, 0

vetor:
#%01%00%00%00
#%02%00%00%00
#%03%00%00%00
#%04%00%00%00
#%05%00%00%00

