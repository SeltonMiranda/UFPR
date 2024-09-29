/*---------------------------------------------------------
PROGRAMA: cliente TAD ArvBin -----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 1000

typedef int ItemArv;
#include "arvBin.h"

/* ----------------------------------------------------- 
  Função: obtem o maior valor par e o maior valor ímpar 
  armazenado na árvore
  Entrada: raiz da árvore
  Saída: maiorPar - maior valor par armazenado na árvore;
                    se não existir nenhum par, retorna com valor zero
         maiorImpar - maior valor ímpar armazenado na árvore
                    se não existir nenhum impar, retorna com valor zero
*/
void maiorParMaiorImpar( ArvBin p, ItemArv *maiorPar, ItemArv *maiorImpar ){
    if ( p == NULL) 
        return;

    maiorParMaiorImpar(p->esq, maiorPar, maiorImpar);
    maiorParMaiorImpar(p->dir, maiorPar, maiorImpar);

    if (p->item % 2 == 0) {
        if (p->item > *maiorPar) *maiorPar = p->item;
    } else if (p->item % 2 == 1) {
        if (p->item > *maiorImpar) *maiorImpar = p->item;
    }

    return;
}

/* ----------------------------------------------------- */
/* Encontra o valor máximo de uma subarvore              */
int max( ArvBin p ) {
    if ( p == NULL ) return 0;// De acordo com a lista o intervalo de valores é [1,999]
    int maxEsq = max(p->esq);
    int maxDir = max(p->dir);

    if (p->item > maxEsq && p->item > maxDir) return p->item;
    else if (maxEsq > maxDir) return maxEsq;
    else return maxDir;
}

/* ----------------------------------------------------- */
/* Encontra o valor mínimo de uma subarvore              */
int min( ArvBin p ) {
    if ( p == NULL ) return 1000;// De acordo com a lista o intervalo de valores é [1,999]
    int minEsq = min(p->esq);
    int minDir = min(p->dir);

    if (p->item < minEsq && p->item < minDir) return p->item;
    else if (minEsq < minDir) return minEsq;
    else return minDir;
}

/* ----------------------------------------------------- 
  Função: verifica se a árvore binária é uma árvore binária de busca
  Entrada: raiz de árvore
  Saida: 1 se a árvore é de busca
         0 se a árvore não é de busca
*/
int ehDeBusca( ArvBin raiz ){
    if ( raiz == NULL ) return 1;

    if ( raiz->esq != NULL ) {
        if ( max(raiz->esq) >= raiz->item ) return 0;
    } 

    if ( raiz->dir != NULL ) {
        if ( min(raiz->dir) <= raiz->item) return 0;
    }

    return ehDeBusca(raiz->esq) && ehDeBusca(raiz->dir);
}


/* ----------------------------------------------------- 
  Função: espelha a árvore
  Entrada: raiz de uma subárvore
  Saída: raiz com os filhos esquerdo e direito trocados
*/
ArvBin espelha( ArvBin p ){
    if (p == NULL) 
        return p;

    p->esq = espelha(p->esq);
    p->dir = espelha(p->dir);

    ArvBin aux;
    aux = p->esq;
    p->esq = p->dir;
    p->dir = aux;
    
    return p;
}

/* ----------------------------------------------------- 
  Função: troca o conteúdo dos nodos de forma que cada nodo 
          contenha o menor valor dentre os valores do nodo 
          corrente e seus filhos
  Entrada: raiz da árvore
  Saida: árvore com os valores armazenados nos nodos trocados
*/
void paiMenor( ArvBin p ){
    if ( p == NULL ) return;

    paiMenor(p->esq);
    paiMenor(p->dir);
    if ( p->esq != NULL) {
        if (p->item > p->esq->item) {
            ItemArv aux;
            aux = p->item;
            p->item = p->esq->item;
            p->esq->item = aux;
        }
    } 

    if ( p->dir != NULL ) {
        if (p->item > p->dir->item) {
            ItemArv aux;
            aux = p->item;
            p->item = p->dir->item;
            p->dir->item = aux;
        }
    }
    return;
}


/* ----------------------------------------------------- 
   Funcao: Cada nodo passa a ter um novo nodo pai     
Se o nodo contiver um valor par, ele será o filho esquerdo do seu novo pai, contendo o dobro do seu valor; se o nodo contiver um valor impar, ele será o filho direito do seu novo pai, contendo o dobro do seu valor mais 1
   Entrada: raiz de um subárvore
   Saída: nova raiz da subárvore com o dobro de nodos 
*/
ArvBin novoPai( ArvBin p ){
    if ( p == NULL ) return p;

    p->esq = novoPai(p->esq);
    p->dir = novoPai(p->dir);

    if ( p->item % 2 == 0 ) {
        ArvBin novo = criaNoArv(p->item * 2, p->pai);
        novo->esq = p;
        p->pai = novo;
        return novo;
    } else if ( p->item % 2 == 1 ) {
        ArvBin novo = criaNoArv(p->item * 2 + 1, p->pai);
        novo->dir = p;
        p->pai = novo;
        return novo;
    }

}

int main(int argc, char *argv[]){
  ArvBin arv;
  ItemArv v, maiorPar, maiorImpar;

  criaArv( &arv );
  printf("Insira uma sequencia de chaves. Finalize a sequencia com 0: \n");
  scanf( "%d", &v );
  while( v != 0 ){
    arv= insereArvLista( v, arv );
    scanf( "%d", &v );
  }
  printf( "Arvore Degenerada\n" );
  escreveArv( arv );
  printf( "Altura = %d\n", alturaArv( arv ));

  if( ehDeBusca( arv ))
    printf("Eh uma arvore de busca\n");
  else
    printf("Nao eh uma arvore de busca\n");
  freeArv( arv );

  criaArv( &arv );
  printf("Insira uma sequencia de chaves. Finalize a sequencia com 0: \n");
  scanf( "%d", &v );
  while( v != 0 ){
    arv= insereArvNivel( v, arv );
    scanf( "%d", &v );
  }
  printf( "Arvore Balanceada\n" );
  escreveArv( arv );
  printf( "Altura = %d\n", alturaArv( arv ));

  if( ehDeBusca( arv ))
    printf("Eh uma arvore de busca\n");
  else
    printf("Nao eh uma arvore de busca\n");

  maiorPar= 0;
  maiorImpar= 0;
  maiorParMaiorImpar( arv, &maiorPar, &maiorImpar );
  if( maiorPar == 0 )
    printf("Nao encontrou valor par\n");
  else
    printf( "Maior par = %d\n", maiorPar );
  if( maiorImpar == 0 )
    printf("Nao encontrou valor impar\n");
  else
    printf( "Maior impar = %d\n", maiorImpar );

  arv= espelha( arv );
  printf("Arvore espelhada\n");
  escreveArv( arv );

  paiMenor( arv );
  printf("Arvore com pai menor\n");
  escreveArv( arv );

  arv= novoPai( arv );
  printf("Arvore dobrada\n");
  escreveArv( arv );

  freeArv( arv );
  return 0;
}
