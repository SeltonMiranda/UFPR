;int i, f, a1, a2, max = 50, fvet[50]
;
;a1 = a2 = 1
;fvet[0] = fvet[1] = 1
;for (i = 2, i < max, i++) {
;    f = a1 + a2
;    a2 = a1
;    a1 = f
;    fvet[i] = f
;}

main:
    addi t0, zero, 2; i = 2
    addi t1, zero, 50 ; max
    addi t2, zero, fvet ; t2 = &fvet
    addi a2, zero, 1 ; a2 = 1
    add  a1, zero, a2 ; a1 = a2

    sw t2, a1, 0 ; fvet[0] = 1
    sw t2, a1, 4 ; fvet[1] = 1

for:
    bge t0, t1, fora_for
    add t3, a1, a2 ; f = a1 + a2
    add a2, a1, zero  ; a2 = a1
    add a1, t3, zero ; a1 = f

    slli t4, t0, 2 ; i * 4
    add t5, t2, t4 ; &fvet + i * 4
    sw t5, t3, 0 ; fvet[i] = f
    addi t0, t0, 1
    jal zero, for
fora_for:
fvet:
