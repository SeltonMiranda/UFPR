;;  int fibonacci(int n) {
;;      if (n == 1 || n == 0)
;;          return n;
;;      return fibonacci(n - 1) + fibonacci(n - 2);
;;  }

;; Pela conveção, toda função, ao ser chamada, tem como parâmetros a0, a1, ...
;; além disso, o valor de retorno da função deverá estar em a0

    addi sp, sp, -1 ;; É um detalhe do EGG
main:
    addi a0, zero, 5
    jal ra, fibonacci
    ebreak

fibonacci:
    addi t0, zero, 1
    beq t0, a0, ret_n ; n == 1
    beq zero, a0, ret_n ; n == 0

    ; Aloca espaço na stack
    ; Guarda o endereço de retorno e o parâmetro da função
    addi sp, sp, -12
    sw sp, ra, 0
    sw sp, a0, 4

    addi a0, a0, -1 ; n = n - 1
    jal ra, fibonacci ; Chama fibonacci( n - 1 )

    ; Guarda o valor de retorno de fibonacci( n - 1 )
    sw sp, a0, 8 

    ; Precisamos do valor de "n (a0)" guardado na stack
    lw a0, sp, 4
    
    add a0, a0, -2 ; n = n - 2
    jal ra, fibonacci ; Chama fibonacci( n - 2 )
    
    ; Recupera-se o valor de retorno de fibonacci( n - 1 )
    lw t1, sp, 8
    
    ; Soma o valor da stack com o valor de retorno de fibonacci( n - 2 )
    add a0, a0, t1

    ; Recupera-se o endereço de retorno
    lw ra, sp, 0
    ; Desaloca o espaço na stack
    addi sp, sp, 12
    jalr zero, ra, 0

; Caso base --> n == 1 || n == 0
ret_n:
    jalr zero, ra, 0
