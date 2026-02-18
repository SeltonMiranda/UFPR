/**************************************
 * Esse arquivo implementa a estrutura de dados Trie e suas operações.
 * Autores: Selton Miranda Rolim (GRR20235688) e Gabriel Carloto Nowak (GRR20235686).
***************************************/


#ifndef __TRIE__
#define __TRIE__

/* Intervalo de digitos -> (0...9) + # */
#define RANGE 11

/* Posição do hashtag no vetor */
#define HASHTAG_POS 10

/* Fim de uma palavra */
#define WORD_END '\0' 

typedef struct Nodo *ApNodo;
typedef struct Nodo {
    ApNodo prox[RANGE]; /* Vetor de ponteiros para nodos. */
    char *palavra; /* Ponteiro para uma palavra (pode conter uma string ou NULL). */
} Nodo;

typedef ApNodo Trie;

/**
 * Cria uma árvore Trie vazia.
 * @param raiz: Ponteiro para a raiz da árvore. 
 **/
void criaArv(Trie *raiz);

/**
 * Insere uma palavra na Trie. A palavra deve conter apenas letras.
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para a palavra a ser inserida na Trie. 
 * @return Trie: Raiz da nova arvore.
 **/
Trie insereArv(Trie *raiz, char *palavra);

/**
 * Destrói a Trie, liberando todos os seus nodos.
 * @param raiz: Ponteiro para a raiz da árvore.
 **/
void destroiArv(Trie raiz);

/**
 * Busca uma palavra na Trie. Assume que a palavra está no formato do teclado T9 .
 * @param raiz: Ponteiro para a raiz da árvore.
 * @param palavra: Ponteiro para uma string da palavra a ser buscada.
 * @return string: Retorna a palavra buscada
 **/
char *buscaPalavra(Trie *raiz, char *palavra);


#endif /* __TRIE__ */
