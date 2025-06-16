#include <stdio.h>
#include "../meuAlocador.h"
#include <unistd.h> /* Para "write()" */
#include <string.h> /* Para "strlen()" */


/* 
 * ----------------- Estrutura Interna do Bloco ----------------- 
 * bytes 0...7    -> Indica se o bloco está ocupado ou não
 * bytes 8...15   -> Tamanho do bloco alocado
 * bytes 16...23  -> ponteiro para lista de ocupados ou livres
 * bytes 24...n   -> Regiao do bloco onde estarão os dados
 */

void *listaLivre = NULL;
void *listaOcupado = NULL;
void *topoInicialHeap;
void *topoAtual;

void iniciaAlocador() {
  topoInicialHeap = topoAtual = sbrk(0);
}

void finalizaAlocador() {
  brk(topoInicialHeap);
  listaLivre = NULL;
  listaOcupado = NULL;
}

void *alocaMem(int num_bytes) {
  void *bloco_atual = listaLivre;
  void *bloco_anterior = NULL;

  while (bloco_atual != NULL) {
    unsigned long tamanho_do_bloco_atual = *(unsigned long *)((char *)bloco_atual + 8);
    void *proximo = *(void **)((char*)bloco_atual + 16);

    if (tamanho_do_bloco_atual >= num_bytes) {
      // Remover da lista de livres
      if (bloco_anterior == NULL) {
        listaLivre = proximo;
      } else {
        *(void **)((char *)bloco_anterior + 16) = proximo;
      }

      // Marcar como ocupado
      *(unsigned long *)(bloco_atual) = 1;

      // Adicionar na lista de ocupados
      *(void **)((char *)bloco_atual + 16) = listaOcupado;
      listaOcupado = bloco_atual;

      return (void *)((char *)bloco_atual + 24);
    }

    bloco_anterior = bloco_atual;
    bloco_atual = proximo;
  }

  // Nenhum bloco livre serve, alocar novo com sbrk
  void *inicio_do_bloco = sbrk(num_bytes + 24);
  if (inicio_do_bloco == (void *)-1) {
    return NULL;
  }
  topoAtual = sbrk(0);

  *(unsigned long *)(inicio_do_bloco) = 1;                        // ocupado
  *(unsigned long *)((char *)inicio_do_bloco + 8) = num_bytes;   // tamanho (somente a área útil)
  *(void **)((char *)inicio_do_bloco + 16) = listaOcupado;       // encadeamento
  listaOcupado = inicio_do_bloco;

  return (void *)((char *)inicio_do_bloco + 24);
}

int liberaMem(void *bloco) {
  if (bloco == NULL) {
    return 0;
  }

  void *ptr = (char *)bloco - 24;
  void *bloco_atual = listaOcupado;
  void *bloco_anterior = NULL;

  while (bloco_atual != NULL) {
    void *proximo = *(void **)((char*)bloco_atual + 16);
    if (bloco_atual == ptr) {
      // Remove da lista de ocupados
      if (bloco_anterior  == NULL) {
        listaOcupado = proximo;
      } else {
        *(void **)((char*)bloco_anterior + 16) = proximo;
      }

      *(unsigned long *)((char *)ptr) = 0;
      *(void **)((char*)ptr + 16) = listaLivre;
      listaLivre = ptr;
      return 1;
    }

    bloco_anterior = bloco_atual;
    // bloco_atual = *(void **)((char *)bloco_atual + 16);
    bloco_atual = proximo;
  }

  return 0;
}

// void imprimeMapa() {
//   char *ptr = (char *)topoInicialHeap;
// 
//   if (ptr == topoAtual) {
//     printf("<vazio\n");
//     return;
//   }
// 
//   while (ptr < (char *)topoAtual) {
//     unsigned long ocupado = *(unsigned long *)ptr;
//     unsigned long tamanho = *(unsigned long *)(ptr + 8); // tamanho total do bloco 
// 
//     // Imprime os 24 bytes gerenciais
//     for (int i = 0; i < 24; i++) {
//       printf("#");
//     }
// 
//     // Imprime os bytes de dados
//     int dados = tamanho;
//     char simbolo = (ocupado == 0) ? '-' : '+';
//     for (int i = 0; i < dados; i++) {
//       printf("%c", simbolo);
//     }
// 
//     ptr = (void*)((char*)ptr + tamanho + 24);
//   }
// 
//   printf("\n");
// }


void imprimeMapa() {
  char *ptr = (char *)topoInicialHeap;

  if (ptr == topoAtual) {
    write(1, "<vazio\n", 7);
    return;
  }

  while (ptr < (char *)topoAtual) {
    unsigned long ocupado = *(unsigned long *)ptr;
    unsigned long tamanho = *(unsigned long *)(ptr + 8); // tamanho total do bloco

    // Imprime os 24 bytes gerenciais como '#'
    for (int i = 0; i < 24; i++) {
      write(1, "#", 1);
    }

    // Imprime os dados como '-' (livre) ou '+' (ocupado)
    char simbolo = (ocupado == 0) ? '-' : '+';
    for (int i = 0; i < tamanho; i++) {
      write(1, &simbolo, 1);
    }

    ptr = (void *)((char *)ptr + tamanho + 24);
  }

  write(1, "\n", 1);
}
