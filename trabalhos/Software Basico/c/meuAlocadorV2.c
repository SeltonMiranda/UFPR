/*
 * Autor : Selton Miranda Rolim
 * Alocador V1 mas agora com fusao dos blocos livres
 */

#include "../meuAlocador.h"
#include <unistd.h> /* Para "write()" */
#include <string.h> /* Para "strlen()" */

#define METADATA_SIZE 16

void *topoInicialHeap;
void *topoAtual;

void iniciaAlocador() {
    topoInicialHeap = topoAtual= sbrk(0);
}

void finalizaAlocador() {
  brk(topoInicialHeap);
}

int liberaMem(void* bloco) {
  *(unsigned long *)((char*)bloco - METADATA_SIZE) = 0;
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

    for (int i = 0; i < METADATA_SIZE; i++) {
      char c = '#';
      write(1, &c, 1);
    }

    char c = ocupado ? '+' : '-';
    for (unsigned long i = 0; i < tamanho; i++) {
      write(1, &c, 1);
    }

    iterador = (void *)((char *)iterador + tamanho + METADATA_SIZE);
  }

  char nova_linha = '\n';
  write(1, &nova_linha, 1);
}

void* alocaMem(int num_bytes) {
  unsigned long ocupado;
  unsigned long tamanho_do_bloco;

  void *iterador = NULL;  
  iterador = topoInicialHeap;
  while (iterador < topoAtual) {
    ocupado = *(unsigned long int*)((char*)iterador);
    tamanho_do_bloco = *(unsigned long int*)((char*)iterador + 8);
    
    // Se o bloco atual ja possui tamanho suficiente retorna-o
    if (ocupado == 0 && tamanho_do_bloco >= num_bytes) {
      *(unsigned long *)((char *)iterador) = 1;
      return (void *)(unsigned long *)((char *)iterador + METADATA_SIZE);
    }

    // Se o bloco atual nao possui o tamanho suficiente verifica se é possível fundir
    if (ocupado == 0) {
      unsigned long tamanho_total_fusao = tamanho_do_bloco; 
      void *proximo_bloco = (void*)((char *)iterador + METADATA_SIZE + tamanho_do_bloco);

      while (proximo_bloco < topoAtual && tamanho_total_fusao < num_bytes) {
        unsigned long prox_ocupado = *(unsigned long *)((char*)proximo_bloco);
        unsigned long prox_tamanho = *(unsigned long *)((char *)proximo_bloco + 8);

        if (prox_ocupado != 0) {
          break;
        }

        tamanho_total_fusao += METADATA_SIZE + prox_tamanho;
        proximo_bloco = (void *)((char *)proximo_bloco + METADATA_SIZE + prox_tamanho);
      }

      // Se o tamanho dos blocos fundidos for maior que o necessario retorna o endereço desse bloco
      if (tamanho_total_fusao >= num_bytes) {
        *(unsigned long *)((char *)iterador) = 1;
        *(unsigned long *)((char *)iterador + 8) = tamanho_total_fusao;
        return (void *)(unsigned long *)((char *)iterador + METADATA_SIZE);
      }
    }

    iterador = (void *)((char*)iterador + METADATA_SIZE + tamanho_do_bloco);
  }
  
  // Aumentando a heap
  void* inicio_do_bloco = sbrk(num_bytes + METADATA_SIZE);
  if (inicio_do_bloco == (void*)-1) {
    return NULL;
  }

  // Atualizando o topo da heap
  topoAtual = sbrk(0);

  // Configurando os metadados
  *(unsigned long *)((char*)inicio_do_bloco) = 1;
  *(unsigned long *)((char*)inicio_do_bloco + 8) = num_bytes;

  return (void *)((char *)inicio_do_bloco + METADATA_SIZE);
}