#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

struct fila *fila_cria()
{
        struct fila *f;
        f = malloc(sizeof(struct fila));
        if (!f) 
                return NULL;
        f->tamanho = 0;
        f->ini = NULL;
        f->fim = NULL;

        return f;
}

void fila_destroi(struct fila **fila)
{
        if (fila_vazia(*fila)) {
                free(*fila);
                return;
        }

        struct nodo *anterior, *temp;
        anterior = NULL;
        temp = (*fila)->ini;
        while (temp != NULL) {
                anterior = temp;
                temp = temp->prox;
                free(anterior);
        }

        free(*fila);
        *fila = NULL;
}

static struct nodo* cria_nodo(int dado)
{
        struct nodo *novo;
        novo = malloc(sizeof(struct nodo));
        if (!novo)
                return NULL;

        novo->chave = dado;
        novo->prox = NULL;
        return novo;
}

int enqueue(struct fila *fila, int dado)
{
        struct nodo *nodo;
        nodo = cria_nodo(dado); 
        if (!nodo)
                return 0;

        if (fila_vazia(fila)) {
                fila->ini = nodo;
                fila->fim = nodo;
                fila->tamanho++;
                return 1;
        }
        
        fila->fim->prox = nodo;
        fila->fim = nodo;
        fila->tamanho++;
        return 1;
}

int dequeue(struct fila *fila, int *dado)
{
        if(fila_vazia(fila))
                return 0;

        struct nodo* temp;
        *dado = fila->ini->chave;
        temp = fila->ini;
        fila->ini = fila->ini->prox;

        free(temp);
        fila->tamanho--;
        return 1;
}

int fila_tamanho(struct fila *fila)
{
        return fila->tamanho;
}

int fila_vazia(struct fila *fila)
{
        return fila->tamanho == 0;
}

void fila_imprime(struct fila *fila)
{
        if (fila_vazia(fila)) {
                printf("[ ]");
                return;
        }
        
        struct nodo *atual;
        atual = fila->ini;
        printf("[ ");
        while (atual != NULL) {
                printf("%d", atual->chave);
                printf(" ");
                atual = atual->prox;
        }
        printf("]");
}
