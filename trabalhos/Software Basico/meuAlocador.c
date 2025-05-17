#include "meuAlocador.h"
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>


// ----------------- Estrutura Interna do Bloco ----------------- 
// bytes 0...7  -> Indica se o bloco está ocupado ou não
// bytes 8...15 -> Tamanho do bloco alocado
// bytes 16...n -> Regiao do bloco onde estarão os dados

void *topoInicialHeap;
void *topoAtual;

void iniciaAlocador() {
    topoInicialHeap = topoAtual= sbrk(0);
}

void finalizaAlocador() {
  brk(topoInicialHeap);
}

void* alocaMem(int num_bytes) {
  void *iterador;
  void *best_fit_bloco_livre = NULL;
  unsigned long menorTamanho;
  unsigned long ocupado;
  unsigned long tamanho_do_bloco;
  unsigned long tamanho_necessario = num_bytes + 16;

  iterador = topoInicialHeap;
  // Best fit
  while (iterador < topoAtual) {
    ocupado = *(unsigned long int*)((char*)iterador);
    tamanho_do_bloco = *(unsigned long int*)((char*)iterador + 8);

    // Se o bloco não estiver ocupado e tiver tamanho suficiente
    // verifica se é menor que o tamanho do bloco atual
    if (ocupado == 0 && tamanho_do_bloco >= tamanho_necessario ) {
      if (best_fit_bloco_livre == NULL || tamanho_do_bloco < menorTamanho) {
        best_fit_bloco_livre = iterador;
        menorTamanho = tamanho_do_bloco;
      }
    }

    iterador = (void*)((char*)iterador + tamanho_do_bloco);
  }

  if (best_fit_bloco_livre != NULL) {
    // Achou um bloco livre
    *(unsigned long *)((char*)best_fit_bloco_livre) = 1;
    return (void *)((char *)best_fit_bloco_livre + 16);
  }

  // Calcula o Tamanho total do bloco
  // unsigned long paginas = (tamanho_necessario + 4096 - 1) / 4096;
  // Tamnanho total = 4096 * numero de paginas
  // unsigned long tamanho_total = paginas * 4096;

  // ----------- Debugging -----------
  unsigned long tamanho_total = tamanho_necessario;
  // ----------- Debugging -----------

  // Aumentando a heap
  void* inicio_do_bloco = sbrk(tamanho_total);
  if (inicio_do_bloco == (void*)-1) {
    return NULL;
  }

  // Atualizando o topo da heap
  topoAtual = sbrk(0);

  // Configurando os metadados
  best_fit_bloco_livre = inicio_do_bloco;
  *(unsigned long *)((char*)best_fit_bloco_livre) = 1;
  *(unsigned long *)((char*)best_fit_bloco_livre + 8) = tamanho_total;

  return (void *)((char *)best_fit_bloco_livre + 16);
}

int liberaMem(void* bloco) {
  *(unsigned long *)((char*)bloco - 16) = 0;
}

void imprimeMapa() {
  void *iterador = topoInicialHeap;

  if (iterador == topoAtual) {
    return;
  }

  while (iterador < topoAtual) {
    unsigned long ocupado = *(unsigned long *)iterador;
    unsigned long tamanho = *(unsigned long *)(iterador + 8);

    for (int i = 0; i < 16; i++) {
      char c = '#';
      write(1, &c, 1);
    }

    char c = ocupado ? '+' : '-';
    for (unsigned long i = 16; i < tamanho; i++) {
      write(1, &c, 1);
    }

    iterador = (char *)iterador + tamanho;
  }

  char nova_linha = '\n';
  write(1, &nova_linha, 1);
}