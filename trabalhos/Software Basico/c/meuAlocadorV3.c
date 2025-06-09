#include <stdio.h>

void *listaLivre = NULL;
void *listaOcupado = NULL;
void *topoInicialHeap;
void *topoAtual;

void iniciaAlocador() {
  printf("Inicializando alocador de memoria proprio\n");
  topoInicialHeap = topoAtual = sbrk(0);
}

void finalizaAlocador() {
  brk(topoInicialHeap);
  listaLivre = NULL;
  listaOcupado = NULL;
}

void *alocaMem(int num_bytes) {
  void *bloco_atual = NULL;
  void *bloco_anterior = NULL;
  unsigned long tamanho_necessario = num_bytes + 16;

  bloco_atual = listaLivre;
  while (bloco_atual != NULL) {
    void *proximo = *(void **)bloco_atual;
    unsigned long tamanho_do_bloco_atual = *(unsigned long *)((char *)bloco_atual + 8);

    if (tamanho_do_bloco_atual >= tamanho_necessario) {
      if (bloco_anterior != NULL) {
        listaLivre = proximo;
      } else {
        *(void **)bloco_anterior = proximo;
      }
      *(void **)bloco_atual = listaOcupado;
      listaOcupado = bloco_atual;
      return (void *)((char *)bloco_atual + 16);
    }

    bloco_anterior = bloco_atual;
    bloco_atual = proximo;
  }

  void *inicio_do_bloco = sbrk(tamanho_necessario);
  if (inicio_do_bloco == (void *)-1) {
    return NULL;
  }
  topoAtual = sbrk(0);

  *(void **)inicio_do_bloco = listaOcupado;
  *(unsigned long *)((char *)inicio_do_bloco + 8) = tamanho_necessario;
  listaOcupado = inicio_do_bloco;

  return (void *)((char*)inicio_do_bloco + 16);
}

int liberaMem(void *bloco) {
  if (bloco == NULL) {
    return 0;
  }

  void *ptr = (char *)ptr - 16;
  void *bloco_atual = listaOcupado;
  void *bloco_anterior = NULL;

  while (bloco_atual != NULL) {
    if (bloco_atual == ptr) {
      // Remove da lista de ocupados
      void *proximo = *(void **)bloco_atual;
      if (bloco_anterior  == NULL) {
        listaOcupado = proximo;
      } else {
        *(void **)bloco_anterior = proximo;
      }

      *(void **)ptr = listaLivre;
      listaLivre = ptr;
      return 1;
    }

    bloco_anterior = bloco_atual;
    bloco_atual = *(void **)bloco_atual;
  }

  return 0;
}