#ifndef PILHA_H
#define PILHA_H

#include <sys/types.h>

typedef struct {
        ssize_t *vetor;
        ssize_t topo;
        size_t tam;
} Pilha;

// Inicializa uma pilha com tamanho tam
Pilha *inicializaPilha(size_t tam);

/*
 * Insere o valor no topo da pilha, retorna 1 em caso de sucesso
 * ou 0 em caso de falha
*/
int push(Pilha *pilha, ssize_t idx);

/*
 * Remove o elemento do topo da pilha, retornando-o no ponteiro,
 * retorna 1 em caso de sucesso ou 0 em caso de falha
*/
int pop(Pilha *pilha, ssize_t *idx);

// Retorna 1 se a pilha esta vazia ou 0 caso nao esteja
int pilhaVazia(Pilha *pilha);

// Desaloca a memoria para da pilha
void destroiPilha(Pilha **pilha);

#endif // PILHA_H
