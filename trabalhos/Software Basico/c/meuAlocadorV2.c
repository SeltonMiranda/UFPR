/*
 * Autor : Selton Miranda Rolim
 * Alocador V1 mas agora com fusao dos blocos livres
 */

#include "meuAlocador.h"
#include <unistd.h> /* Para "write()" */
#include <string.h> /* Para "strlen()" */

#define TAM_BLOCO 1

void *topoInicialHeap;
void *topoAtual;

void iniciaAlocador() {
    topoInicialHeap = topoAtual= sbrk(0);
}

void finalizaAlocador() {
  brk(topoInicialHeap);
}

int liberaMem(void* bloco) {
  *(unsigned long *)((char*)bloco - 16) = 0;
  return 1;
}

void imprimeMapa() {
  void *iterador = topoInicialHeap;

  if (iterador == topoAtual) {
    char *string = "<vazio>\n";
    write(1, string, strlen(string));
    return;
  }

  while (iterador < topoAtual) {
    unsigned long ocupado = *(unsigned long *)iterador;
    unsigned long tamanho = *(unsigned long *)((char *)iterador + 8);

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

void* alocaMem(int num_bytes) {
  unsigned long ocupado;
  unsigned long tamanho_do_bloco;
  unsigned long tamanho_necessario = num_bytes + 16;

  void *iterador = NULL;  
  iterador = topoInicialHeap;
  while (iterador < topoAtual) {
    ocupado = *(unsigned long int*)((char*)iterador);
    tamanho_do_bloco = *(unsigned long int*)((char*)iterador + 8);
    
    // Se o bloco atual ja possui tamanho suficiente retorna-o
    if (ocupado == 0 && tamanho_do_bloco >= tamanho_necessario) {
      *(unsigned long *)((char *)iterador) = 1;
      return (void *)(unsigned long *)((char *)iterador + 16);
    }

    // Se o bloco atual nao possui o tamanho suficiente verifica se é possível fundir
    if (ocupado == 0 && tamanho_do_bloco < tamanho_necessario) {
      void *proximo_bloco = (void*)((char *)iterador + tamanho_do_bloco);

      while (proximo_bloco < topoAtual) {
        unsigned long prox_ocupado = *(unsigned long *)((char*)proximo_bloco);
        unsigned long prox_tamanho = *(unsigned long *)((char *)proximo_bloco + 8);

        if (prox_ocupado != 0) {
          break;
        }

        // Funde o bloco
        tamanho_do_bloco += prox_tamanho;
        *(unsigned long *)((char *)iterador + 8) = tamanho_do_bloco;
        
        proximo_bloco = (void *)((char *)proximo_bloco + prox_tamanho);
      }

      // Se o tamanho dos blocos fundidos for maior que o necessario retorna o endereço desse bloco
      if (tamanho_do_bloco >= tamanho_necessario) {
        *(unsigned long *)((char *)iterador) = 1;
        return (void *)(unsigned long *)((char *)iterador + 16);
      }
    }

    iterador = (void *)((char*)iterador + tamanho_do_bloco);
  }
  
  // Calcula o Tamanho total do bloco
  unsigned long paginas = (tamanho_necessario + TAM_BLOCO - 1) / TAM_BLOCO;
  unsigned long tamanho_total = paginas * TAM_BLOCO;


  // Aumentando a heap
  void* inicio_do_bloco = sbrk(tamanho_total);
  if (inicio_do_bloco == (void*)-1) {
    return NULL;
  }

  // Atualizando o topo da heap
  topoAtual = sbrk(0);

  // Configurando os metadados
  *(unsigned long *)((char*)inicio_do_bloco) = 1;
  *(unsigned long *)((char*)inicio_do_bloco + 8) = tamanho_total;

  return (void *)((char *)inicio_do_bloco + 16);
}