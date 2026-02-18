;int x, y, mdc
;x = 10
;y = 25
;mdc = gcd(x,y)
;x = x/mdc
;y = y/mdc

;int gcd(int a, int b) {
;    if (a == 0)
;        return b
;    if (b == 0)
;        return a
;    if (a == b)
;        return a
;    if (a > b)
;        return gcd(a - b, b)
;    return (a, b - a)
;}

    addi sp, sp, -1 ; EGG não inicializa o ponteiro da stack automaticamente
main:
    addi t0, zero, 10 ; x = 10
    addi t1, zero, 25 ; y = 25

    ; Registradores a0...7 são usados para parâmetros de funções
    add a0, t0, zero
    add a1, t1, zero
    jal ra, gcd
    ; O retorno da função é sempre em a0 ou a1, nesse caso a0
    div t0, t0, a0 ; x = x/mdc
    div t1, t1, a0 ; y = y/mdc
    ebreak
gcd:
    ; ------> Convenção <--------
    ; Como vou usar registradores salvos s0...s11, preciso salvar
    ; os valores deles na stack primeiramente, além do endereço de retorno.
    ; Lembre-se de alocar espaço na stack
    addi sp, sp, -12
    sw sp, ra, 0
    sw sp, s0, 4
    sw sp, s1, 8

    ; Atribuindo os valores dos parâmetros para os registradores "s0" e "s1"
    addi s0, a0, 0
    addi s1, a1, 0

    beq s0, zero, ret_b ; a = 0
    beq s1, zero, ret_a ; b = 0
    beq s0, s1, ret_a ; a = b
    blt s1, s0, left ; b < a

    ; a < b
    sub a1, a1, a0 ; b = b - a
    jal ra, gcd ; gcd(a, b - a)

    lw ra, sp, 0
    lw s0, sp, 4
    lw s1, sp, 8
    addi sp, sp, 12
    jalr zero, ra, 0

left:
    sub a0, a0, a1 ; a = a - b
    jal ra, gcd ; gcd(a - b, b)

    ; ------> Convenção <--------
    ; Carregando os valores salvos na stack para os registradores "s0" e "s1"
    lw ra, sp, 0
    lw s0, sp, 4
    lw s1, sp, 8
    ; Lembre-se de desalocar o espaço da stack
    addi sp, sp, 12
    jalr zero, ra, 0 ; Retorna para o endereço contido no registrador "ra"

ret_b:
    addi a0, a1, 0 ; Retorno da função sempre em a0 ou a1
    jalr zero, ra, 0

; Como a0 é o primeiro parâmetro da função, não há necessidade de movê-lo
; simplesmente retorne
ret_a:
    jalr zero, ra, 0

    
