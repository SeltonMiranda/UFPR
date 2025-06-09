.section .data
  topoInicialHeap:  .quad 0
  topoAtual:        .quad 0

  info:             .byte '#'
  ocupado:          .byte '+'
  livre:            .byte '-'
  nova_linha:       .byte '\n'

  string:           .string "<vazio>\n"

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

# %rdi      -> num_bytes
# -8(%rbp)  -> iterador
# -16(%rbp) -> tamanho_necessario
alocaMem:
  pushq %rbp
  movq  %rsp, %rbp

  pushq %rbx
  pushq %r12
  pushq %r13
  pushq %r14
  pushq %r15
  
  subq  $16,  %rsp # Aloca 16 bytes para variaveis locais

  movq  topoInicialHeap, %r10 # r10 := topoInicialHeap
  movq  %r10, -8(%rbp) # iterador := topoInicialHeap
  movq  %rdi, -16(%rbp) # tamanho_necessario := num_bytes
  addq  $16,  -16(%rbp) # tamanho_necessario += 16

  movq -8(%rbp), %rbx # rbx := iterador

procurar_bloco:
  cmpq topoAtual, %rbx # if (iterador >= topoAtual)
  jge alocar_novo_bloco

  movq (%rbx), %r12   # r12 := ocupado
  movq 8(%rbx), %r13  # r13 := tamanho_do_bloco

  cmpq $0, %r12 # if (ocupado != 0)
  jne proximo_bloco

  cmpq %rdi, %r13 # if (tamanho_do_bloco < num_bytes)
  jl  proximo_bloco

  movq $1, (%rbx) # marca como ocupado
  movq 16(%rbx), %rax # rax := iterador + 16

  popq %r15
  popq %r14
  popq %r13
  popq %r12
  popq %rbx

  movq %rbp, %rsp
  popq %rbp
  ret

proximo_bloco:
  movq  $16,  %r14  # r14 := 16
  addq  %r13, %r14  # r14 += tamanho_do_bloco
  addq  %r14, %rbx  # iterador += tamanho_do_bloco + 16 
  jmp procurar_bloco

alocar_novo_bloco:
  movq topoAtual, %r14 # r14 := topoAtual

  movq topoAtual, %r15 # r15 := topoAtual
  addq %rdi, %r15 # r15 += num_bytes
  addq $16, %r15 # r15 += 16

  movq $12, %rax # rax := 12 (syscall brk)
  movq %r15, %rdi # novo endereço do topo
  syscall

  movq %r15, topoAtual # Atualiza topo da heap

  movq -16(%rbp), %rdi # rdi = tamanho_necessario
  subq $16, %rdi # rdi -= 16

  # Preenche metadados
  movq $1, (%r14) # inicio_do_bloco := 1 (ocupado)
  movq %rdi, 8(%r14) # (inicio_do_bloco + 8) := num_bytes

  addq $16, %r14
  movq %r14, %rax # rax := (inicio_do_bloco + 16)

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
