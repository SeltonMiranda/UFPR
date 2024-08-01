        addi sp, sp, -1

main:
        addi a7, zero, 3
        addi a0, zero, string
        addi a1, zero, 40
        ecall

        addi a1, zero, 0x6F
        addi a2, zero, 0x30
        jal ra, search_replace

        addi a7, zero, 3
        addi a0, zero, string
        addi a1, zero, 40
        ecall
        ebreak

search_replace:
        lb t0, a0, 0
        beq t0, 0x00, ret

        beq t0, a1, found

        addi sp, sp, -8
        sw sp, ra, 4
        sb sp, a0, 0

        addi a0, a0, 1
        jal ra, search_replace

        lw ra, sp, 4
        lb a0, sp, 0
        addi sp, sp, 8

        jalr zero, ra, 0

found:
        sb a0, a2, 0
        jal zero, search_replace

ret:
        jalr zero, ra, 0
string:
#Projetos Digitais e Microprocessadores%0a%00
