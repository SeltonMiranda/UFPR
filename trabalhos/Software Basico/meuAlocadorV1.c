/*
 * Autor : Selton Miranda Rolim
 * Alocador de memória baseado no algoritmo de Jonathan Bartlett
 * No inicio de cada bloco alocado ha informacoes sobre estar ocupado e
 * o tamanho do bloco. Assim, Pode se percorrer a heap como uma lista ligada
 */


#include "meuAlocador.h"
#include <unistd.h> /* Para "write()" */
#include <string.h> /* Para "strlen()" */

/* 
 * ----------------- Estrutura Interna do Bloco ----------------- 
 * bytes 0...7  -> Indica se o bloco está ocupado ou não
 * bytes 8...15 -> Tamanho do bloco alocado
 * bytes 16...n -> Regiao do bloco onde estarão os dados
 */

#define TAM_BLOCO 32

void *topoInicialHeap;
void *topoAtual;

void iniciaAlocador() {
    topoInicialHeap = topoAtual= sbrk(0);
}

void finalizaAlocador() {
  brk(topoInicialHeap);
}

void* alocaMem(int num_bytes) {
  void *iterador = NULL;
  unsigned long ocupado;
  unsigned long tamanho_do_bloco;
  unsigned long tamanho_necessario = num_bytes + 16;

  iterador = topoInicialHeap;
  while (iterador < topoAtual) {
    ocupado = *(unsigned long *)((char *)iterador);
    tamanho_do_bloco = *(unsigned long *)((char *)iterador + 8);

    if (ocupado == 0 && tamanho_do_bloco >= tamanho_necessario ) {
      *(unsigned long *)((char *)iterador) = 1;   
      return (void *)((char *)iterador + 16);
    }

    iterador = (void *)((char *)iterador + tamanho_do_bloco);
  }
  
  // Calcula o Tamanho total do bloco
  unsigned long paginas = (tamanho_necessario + TAM_BLOCO - 1) / TAM_BLOCO;
  unsigned long tamanho_total = paginas * TAM_BLOCO;


  // Aumentando a heap
  void* inicio_do_bloco = sbrk(tamanho_total);
  if (inicio_do_bloco == (void *)-1) {
    return NULL;
  }

  // Atualizando o topo da heap
  topoAtual = sbrk(0);

  // Configurando os metadados
  *(unsigned long *)((char*)inicio_do_bloco) = 1;
  *(unsigned long *)((char*)inicio_do_bloco + 8) = tamanho_total;

  return (void *)((char *)inicio_do_bloco + 16);
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
