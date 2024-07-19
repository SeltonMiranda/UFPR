#include "lef.h"
#include <stdlib.h>
#include <stdio.h>

struct evento_t *cria_evento(int tempo, int tipo, int dado1, int dado2)
{
        struct evento_t *e;
        e = (struct evento_t*)malloc(sizeof(struct evento_t));
        if (e == NULL)
                return NULL;
        e->tempo = tempo;
        e->tipo = tipo;
        e->dado1 = dado1;
        e->dado2 = dado2;

        return e;
}

struct evento_t *destroi_evento(struct evento_t *e)
{
        free(e);
        e = NULL;
        return NULL;
}

static struct nodo_lef_t *cria_nodo(struct evento_t *e)
{
        struct nodo_lef_t *nodo;
        nodo = malloc(sizeof(struct nodo_lef_t));
        if (nodo == NULL)
                return NULL;

        nodo->evento = e;
        nodo->prox = NULL;
        return nodo;
}

int insere_lef(struct lef_t *l, struct evento_t *e)
{
        struct nodo_lef_t *nodo;
        nodo = cria_nodo(e);
        if (nodo == NULL)
                return 0;

        /* Caso em que a lista esta vazia */
        if (l->primeiro == NULL) {
                l->primeiro = nodo;   
                return 1;
        } 

        struct nodo_lef_t *atual;
        struct nodo_lef_t *anterior;

        atual = l->primeiro;
        anterior = NULL;

        while (atual && atual->evento->tempo <= e->tempo) {
                anterior = atual;
                atual = atual->prox;
        }

        /* Caso em que a insercao acontece no primeiro nodo */
        if (anterior == NULL) {
                nodo->prox = l->primeiro;
                l->primeiro = nodo;
                return 1;
        }

        nodo->prox = anterior->prox;
        anterior->prox = nodo;
        return 1;
}

struct evento_t *retira_lef(struct lef_t *l)
{
        if (vazia_lef(l))
                return NULL;

        struct nodo_lef_t *removido;
        struct evento_t *evento;

        removido = l->primeiro;
        evento = removido->evento;
        l->primeiro = l->primeiro->prox;
        free(removido);

        return evento;
}

struct lef_t *cria_lef()
{
        struct lef_t *lef = malloc(sizeof(struct lef_t));
        if (!lef)
                return NULL;

        lef->primeiro = NULL;
        return lef;
}

struct lef_t *destroi_lef(struct lef_t *l)
{
        struct nodo_lef_t *atual, *anterior;
        anterior = NULL;
        atual = l->primeiro;
        while (atual != NULL) {
                anterior = atual;
                atual = atual->prox;
                free(anterior->evento);
                free(anterior);
        }

        free(l);
        l = NULL;
        return NULL;
}

int vazia_lef(struct lef_t *l)
{
        return l->primeiro == NULL;
}

void imprime_lef(struct lef_t *l)
{
        struct nodo_lef_t *atual;
        atual = l->primeiro;
        int total;

        total = 0;
        printf("LEF:\n");
        while (atual != NULL) {
                struct evento_t *e;
                e = atual->evento;
                printf("  tempo %d tipo %d d1 %d d2 %d\n", e->tempo, e->tipo, e->dado1, e->dado2);
                total++;
                atual = atual->prox;
        }

        printf("  Total %d eventos\n", total);
}
