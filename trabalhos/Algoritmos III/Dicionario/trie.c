#include "trie.h"

#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Função que cria um novo nodo na Trie. Pode conter
 * uma palavra ou não.
 *
 * @param palavra: Ponteiro para palavra a ser inserida ou NULL. 
 * @return ApNodo: Novo nodo. 
 **/
static ApNodo criaNodo(const char *palavra) {
    ApNodo novo = (ApNodo)malloc(sizeof(Nodo));
    if (novo == NULL)
        return NULL;

    if (palavra == NULL) novo->palavra = NULL;
    else novo->palavra = strdup(palavra);

    for (int i = 0; i < RANGE; i++)
        novo->prox[i] = NULL;
    
    return novo;
}

/**
 * Função auxiliar que trata as colisoes de palavras na Trie,
 * insere uma palavra como uma lista ligada.
 * 
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para palavra a ser inserida.  
 **/
static Trie insereLista(Trie *raiz, char *palavra) {
    if (*raiz == NULL) {
        return criaNodo(palavra);
    }

    ApNodo atual = *raiz;
    ApNodo anterior = NULL;
    while (atual != NULL) {
        anterior = atual;
        atual = atual->prox[HASHTAG_POS];
    }
        
    atual = criaNodo(palavra);
    if (atual == NULL) {
        fprintf(stderr, "ERRO: Nao foi possivel alocar memoria para o nodo %s\n", palavra);
        return NULL;
    }

    if (anterior != NULL)
        anterior->prox[HASHTAG_POS] = atual;
    return *raiz; 
}

/**
 * Função recursiva auxiliar que insere uma palavra na Trie,
 * retorna a nova raíz da subárvore.
 * 
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para palavra a ser inserida.
 * @param c: Ponteiro para o primeiro caractere da palavra.
 * @return Trie: Raíz da nova subárvore.  
 **/
static Trie insereR(Trie *raiz, char *palavra, char *c) {
    if (*raiz == NULL) {
        *raiz = criaNodo(NULL);
        if (*raiz == NULL) {
                fprintf(stderr, "ERRO: Nao foi possivel alocar memoria para o nodo\n");
                return NULL;
        }
    }

    if (*c == WORD_END) { 
        if ((*raiz)->palavra != NULL) { /* Verifica se já existe uma palavra no nodo atual. */
            *raiz = insereLista(raiz, palavra); 
            if (*raiz == NULL)
                return NULL;
        } else {
            (*raiz)->palavra = strdup(palavra);
        }
        return *raiz;
    }
   
    int index = charToDigit(*c);
    (*raiz)->prox[index] = insereR(&((*raiz)->prox[index]), palavra, ++c);
    return *raiz;
}

Trie insereArv(Trie *raiz, char *palavra) {
    char *c = palavra; /* Ponteiro para o primeiro caractere da palavra */
    return insereR(raiz, palavra, c);
}

/**
 * Função auxiliar recursiva que busca uma palavra na Trie.
 * 
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para palavra a ser inserida.  
 **/
static char *buscaR(Trie *raiz, char *c) {   
    if (*raiz == NULL)
	    return NULL;

    if (*c == WORD_END)
        return (*raiz)->palavra;

    if (*c == HASHTAG)
        return buscaR(&(*raiz)->prox[HASHTAG_POS], ++c);

    int index = *c - ZERO;  
    return buscaR(&(*raiz)->prox[index], ++c);
}

char *buscaPalavra(Trie *raiz, char *palavra) {
    if (*raiz == NULL) 
        return NULL;

    return buscaR(raiz, palavra);
}

void criaArv(Trie *raiz) {
    *raiz = NULL;
}

void destroiArv(Trie raiz) {
    if (raiz == NULL) return;

    for (int i = 0; i < RANGE; i++) {
        destroiArv(raiz->prox[i]);    
    }

    if (raiz->palavra) 
        free(raiz->palavra);
    free(raiz);
}
