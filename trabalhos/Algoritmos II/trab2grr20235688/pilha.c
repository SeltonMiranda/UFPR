#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

Pilha *inicializaPilha(size_t tam)
{
        Pilha *p = (Pilha *)malloc(sizeof(Pilha));
        if (!p) {
                fprintf(stderr, "ERRO: Pilha nao foi alocada\n");
                return NULL;
        }

        p->vetor = (ssize_t *)malloc(tam * sizeof(ssize_t));
        if (!p->vetor) {
                fprintf(stderr, "ERRO: Vetor pilha nao foi alocado\n");
                free(p);
                return NULL;
        }

        p->tam = tam;
        p->topo = -1;

        return p;
}

int push(Pilha *pilha, ssize_t idx)
{
        if (!pilha)
                return 0;

        // Dessa maneira evita comparacoes entre tipos diferentes.
        if (pilha->topo >= 0 && (size_t)pilha->topo == pilha->tam - 1) {
                pilha->tam *= 2;
                pilha->vetor = (ssize_t *)realloc(pilha->vetor, pilha->tam * sizeof(ssize_t));
        }

        pilha->vetor[++pilha->topo] = idx;
        return 1; 
}

int pop(Pilha *pilha, ssize_t *idx)
{
        if (!pilha)
                return 0;

        if (pilhaVazia(pilha))
                return 0;

        *idx = pilha->vetor[pilha->topo--];
        return 1;
}

int pilhaVazia(Pilha *pilha)
{
        return pilha->topo == -1;
}

void destroiPilha(Pilha **pilha)
{
        free((*pilha)->vetor);
        free(*pilha);
        *pilha = NULL;
}
