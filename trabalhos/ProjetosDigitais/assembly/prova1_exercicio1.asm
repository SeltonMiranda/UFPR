;int a = 1, b = 2, c = 3, max
;
;if (a >= b && a >= c) {
;    max = a
;} else if (b >= a && b >= c) {
;    max = b
;} else {
;    max = c
;}


main:
    addi t0, zero, 1 ; a = 1
    addi t1, zero, 2 ; b = 2
    addi t2, zero, 3 ; c = 3
    
    blt t0, t1, else_if ; a >= b
    blt t0, t2, else_if ; a >= c
    add t3, t0, zero ; max = a
    jal zero, fora_if
else_if:
    blt t1, t0, else ; b >= a
    blt t1, t2, else ; b >= c
    add t3, t1, zero
    jal zero, fora_if
else:
    add t3, t2, zero
fora_if:
    ebreak
