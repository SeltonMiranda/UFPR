.section .data
  topoInicialHeap:  .quad 0
  topoAtual:        .quad 0

  info:             .byte '#'
  ocupado:          .byte '+'
  livre:            .byte '-'
  nova_linha:       .byte '\n'

  string:           .string "<vazio>\n"
  .equ METADATA_SIZE, 16

.section .text

.globl iniciaAlocador
.globl finalizaAlocador
.globl liberaMem
.globl alocaMem
.globl imprimeMapa

iniciaAlocador:
  pushq %rbp
  movq  %rsp, %rbp

  movq  $12, %rax  # rax := 12 -- syscall brk
  movq  $0,  %rdi  # rdi := 0  -- argumento
  syscall

  movq  %rax, topoInicialHeap  # Atualiza topo inicial da heap
  movq  %rax, topoAtual        # Atualiza topo atual da heap

  popq  %rbp
  ret

finalizaAlocador:
  pushq %rbp
  movq  %rsp, %rbp

  movq  $12, %rax             # rax := 12 -- syscall brk
  movq  topoInicialHeap, %rdi # rdi := topoInicialHeap
  syscall

  popq  %rbp
  ret

# rdi := num_bytes
# %r12 := iterador
# %r13 := ocupado
# %r14 := tamanho_do_bloco
# %r15 := tamanho_total_fusao
alocaMem:

  pushq %rbp
  movq %rsp, %rbp

  pushq %rbx
  pushq %r12
  pushq %r13
  pushq %r14
  pushq %r15

  movq topoInicialHeap, %r12 # iterador := topoInicialHeap

procurar_bloco:

  cmpq topoAtual, %r12 # if (iterador >= topoAtual)
  jge alocar_bloco

  movq (%r12), %r13 # %r13 := *(iterador) (ocupado/livre)
  movq 8(%r12), %r14 # %r14 := *(iterador + 8) (tamanho_do_bloco)

  cmpq $0, %r13 # if (ocupado != 0)
  jne tentar_fundir_bloco

  cmpq %rdi, %r14 # if (tamanho_do_bloco < num_bytes)
  jl tentar_fundir_bloco

  movq $1, (%r12) # *(iterador) := 1
  movq %r12, %rax # %rax := iterador
  addq $METADATA_SIZE, %rax # %rax += 16

  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx

  popq %rbp
  ret

tentar_fundir_bloco:

  cmpq $0, %r13 # if (ocupado != 0)
  jne ir_proximo_bloco

  movq %r14, %r15 # tamanho_total_fusao (%r15) := tamanho_do_bloco (%r14)

  movq %r12, %rbx # proximo_bloco (%rbx):= iterador (%r12)
  addq %r14, %rbx # proximo_bloco += tamanho_do_bloco
  addq $METADATA_SIZE, %rbx # proximo_bloco += 16

calcular_tamanho_fusao:

  cmpq topoAtual, %rbx # if (proximo_bloco >= topoAtual)
  jge fundir_bloco 

  cmpq %rdi, %r15 # if (tamanho_total_fusao >= num_bytes)
  jge fundir_bloco

  movq (%rbx), %rax # prox_ocupado (%rax) := *(proximo_bloco) (%rbx)  
  movq 8(%rbx), %rcx # prox_tamanho (%rcx) := *(proximo_bloco + 8) (%rbx + 8)

  cmpq $0, %rax # if (prox_ocupado != 0)
  jne fundir_bloco

  addq %rcx, %r15 # tamanho_total_fusao (%r15) += prox_tamanho (%rcx)
  addq $METADATA_SIZE, %r15 # tamanho_total_fusao += 16

  addq %rcx, %rbx # proximo_bloco (%rbx) += prox_tamanho (%rcx)
  addq $METADATA_SIZE, %rbx # proximo_bloco (%rbx) += 16
  jmp calcular_tamanho_fusao

fundir_bloco:

  cmpq %rdi, %r15 # if (tamanho_total_fusao < num_bytes)
  jl ir_proximo_bloco

  movq $1, (%r12) # *(iterador) := 1
  movq %r15, 8(%r12) # *(iterador + 8) := tamanho_total_fusao

  movq %r12, %rax # %rax := iterador
  addq $METADATA_SIZE, %rax # %rax += 16

  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx

  popq %rbp
  ret

ir_proximo_bloco:

  addq %r14, %r12 # iterador += tamanho_do_bloco
  addq $METADATA_SIZE, %r12 # iterador += 16
  jmp procurar_bloco

alocar_bloco:

  movq %rdi, %r9  # %r9 := num_bytes
  movq topoAtual, %r10 # %r10 := topoAtual

  movq topoAtual, %r11 # %r11 := topoAtual
  addq %rdi, %r11 # %r11 += num_bytes
  addq $METADATA_SIZE, %r11 # %r11 += 16

  movq $12, %rax # %rax := 12 (sycall brk)
  movq %r11, %rdi # novo endereço do topo
  syscall

  movq %rax, topoAtual # Atualiza topo da heap

  # Preenche metadados
  movq $1, (%r10) # *(inicio_do_bloco) := 1 
  movq %r9, 8(%r10) # *(inicio_do_bloco + 8) := num_bytes

  movq %r10, %rax # %rax := inicio_do_bloco
  addq $METADATA_SIZE, %rax # %rax += 16

  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx

  movq %rbp, %rsp
  popq %rbp
  ret

# rdi := void *bloco
liberaMem:
  pushq %rbp 
  movq %rsp, %rbp

  cmpq $0, %rdi # if (bloco == NULL)
  je erro

  subq $16, %rdi # &bloco - 16
  movq $0, (%rdi) # *(&bloco) = 0 (livre)

  movq $0, %rax
  popq %rbp
  ret

erro:
  movq $0, %rax
  popq %rbp
  ret

# rbx := iterador
# r8  := i
# r12 := ocupado
# r13 := tamanho
# r14 := string
imprimeMapa:
  pushq %rbp
  movq %rsp, %rbp
 
  pushq %rbx
  pushq %r12
  pushq %r13
  pushq %r14
  pushq %r15
 
  movq topoInicialHeap, %rbx # iterador := topoInicialHeap
  cmpq topoAtual, %rbx # if (iterador == topoAtual)
  je vazio
 
percorrer_blocos:
  cmpq topoAtual, %rbx # if (iterador >= topoAtual)
  jge fim_heap
 
  movq (%rbx), %r12 # ocupado := *(iterador) 
  movq 8(%rbx), %r13 # tamanho := *(iterador + 8)
 
  movq $0, %r8 # i := 0
for_imprime_info:
  cmpq $16, %r8 # if (i >= 16)
  jge fora_for_imprime_info
 
  movq $1, %rax # rax := 1 (syscall write)
  movq $1, %rdi # rdi := 1 (stdout)
  leaq info, %rsi # endereço do caractere
  movq $1, %rdx # tamanho
  syscall
 
  addq $1, %r8 # i += 1
  jmp for_imprime_info
 
fora_for_imprime_info:
 
  cmpq $1, %r12 # if (ocupado == 1)
  je imprimir_ocupado
 
  movq $0, %r8 # i = 16
for_imprime_livre:
  cmpq %r13, %r8
  jge imprimir_proximo_bloco
 
  movq $1, %rax
  movq $1, %rdi
  leaq livre, %rsi
  movq $1, %rdx
  syscall
 
  addq $1, %r8 # i += 1
  jmp for_imprime_livre
 
imprimir_ocupado:
  movq $0, %r8 # i = 16
 
for_imprime_ocupado:
  cmpq %r13, %r8
  jge imprimir_proximo_bloco
 
  movq $1, %rax
  movq $1, %rdi
  leaq ocupado, %rsi
  movq $1, %rdx
  syscall
 
  addq $1, %r8 # i += 1
  jmp for_imprime_ocupado
 
imprimir_proximo_bloco:
  addq %r13, %rbx
  addq $16, %rbx
  jmp percorrer_blocos
 
fim_heap:
 
  movq $1, %rax
  movq $1, %rdi
  leaq nova_linha, %rsi
  movq $1, %rdx
  syscall
 
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
 
  movq %rbp, %rsp
  popq %rbp
  ret
 
vazio:
  movq $1, %rax
  movq $1, %rdi
  leaq string, %rsi
  movq $8, %rdx
  syscall
 
  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx
 
  movq %rbp, %rsp
  popq %rbp
  ret

