#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct lista *lista_cria ()
{
        struct lista *lst;
        lst = malloc(sizeof(struct lista));
        if (lst == NULL) 
                return NULL;

        lst->ini = NULL;
        lst->ptr = NULL;
        lst->tamanho = 0;

        return lst;
}

void lista_destroi (struct lista **lista)
{
        struct nodo *atual;
        struct nodo *anterior;
        atual = (*lista)->ini;
        while (atual != NULL) {
                anterior = atual;
                atual = atual->prox;
                free(anterior);
        }

        free(*lista);
        *lista = NULL;
        return;
}


static struct nodo *nodo_cria(int chave)
{
        struct nodo *nodo;
        nodo = (struct nodo*)malloc(sizeof(struct nodo));
        if (nodo == NULL)
                return NULL;

        nodo->chave = chave;
        nodo->prox = NULL;

        return nodo;
}

int lista_insere_inicio (struct lista *lista, int chave)
{
        struct nodo* nodo;
        nodo = nodo_cria(chave);
        if (nodo == NULL) 
                return 0;

        if (lista->ini == NULL) {
                lista->ini = nodo;
                lista->tamanho++;
                return 1;
        }

        struct nodo *temp;
        temp = lista->ini;
        lista->ini = nodo;
        lista->ini->prox = temp;
        lista->tamanho++;

        return 1;
}

int lista_insere_fim (struct lista *lista, int chave)
{
        struct nodo *nodo;
        nodo = nodo_cria(chave);
        if (nodo == NULL)
                return 0;

        if (lista->ini == NULL) {
                lista->ini = nodo;
                lista->tamanho++;
                return 1;
        }

        struct nodo *atual;
        atual = lista->ini;
        while (atual->prox != NULL)
                atual = atual->prox;

        atual->prox = nodo;
        lista->tamanho++;
        return 1;

}

int lista_insere_ordenado (struct lista *lista, int chave)
{
        struct nodo *nodo;
        nodo = nodo_cria(chave);
        if (nodo == NULL)
                return 0;

        if (lista_vazia(lista) || lista->ini->chave > chave) {
                nodo->prox = lista->ini;
                lista->ini = nodo;
        } else {
                struct nodo *atual = lista->ini;
                while (atual->prox != NULL && atual->prox->chave < chave) {
                        atual = atual->prox;
                }
                nodo->prox = atual->prox;
                atual->prox = nodo;
        }

        lista->tamanho++;
        return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave)
{
        if (lista_vazia(lista))
                return 0;

        struct nodo *temp;
        temp = lista->ini;
        lista->ini = lista->ini->prox;
        *chave = temp->chave;
        free(temp);
        lista->tamanho--;

        return 1;
}

int lista_remove_fim (struct lista *lista, int *chave)
{
        if (lista_vazia(lista))
                return 0;

        if (lista->tamanho == 1) {
                free(lista->ini);
                lista->ini = NULL;
                lista->tamanho--;
                return 1;
        }

        struct nodo *anterior;
        struct nodo *atual;
        atual = lista->ini;
        anterior = NULL;
        while (atual->prox != NULL) {
                anterior = atual;
                atual = atual->prox;
        }

        *chave = atual->chave;
        free(atual);
        anterior->prox = NULL;
        lista->tamanho--;

        return 1;
}
int lista_remove_ordenado (struct lista *lista, int chave)
{
        if (lista_vazia(lista))
                return 0;
        
        struct nodo *anterior;
        struct nodo *atual;

        anterior = NULL;
        atual = lista->ini;
        while (atual != NULL && atual->chave != chave) {
                anterior = atual;
                atual = atual->prox;
        }

        /* Caso em que a chave a ser removida eh o primeiro nodo */
        if (anterior == NULL) {
                lista->ini = atual->prox;
        } else {
                anterior->prox = atual->prox;
        }

        free(atual);
        lista->tamanho--;
        return 1;

} 

int lista_vazia (struct lista *lista)
{
        return lista->tamanho == 0;
}

int lista_tamanho (struct lista *lista)
{
        return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave)
{
        struct nodo *temp;
        temp = lista->ini;

        while (temp != NULL) {
                if (temp->chave == chave)
                        return 1;
                temp = temp->prox;
        }

        return 0;
}

void lista_inicia_iterador (struct lista *lista){
        lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave)
{
        *chave = lista->ptr->chave;
        if (lista->ptr->prox != NULL) {
                lista->ptr = lista->ptr->prox;
                return 1;
        }
        return 0;
}
