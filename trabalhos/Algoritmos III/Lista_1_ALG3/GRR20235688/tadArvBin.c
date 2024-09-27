/*---------------------------------------------------------
Implementação: TAD Árvore
-----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int ItemArv;
#include "itemInt.h"
#include "arvBin.h"

typedef ArvBin ItemFila;
#include "fila.h"

/* ----------------------------------------------------- */
/* Impressão da árvore */
void escreveArvR( ArvBin p ){
  if( p == NULL )
    printf("()");
  else{
    printf( "(" );
    write( p->item );
    escreveArvR( p->esq );
    escreveArvR( p->dir );
    printf(")");
  }
  return;
}

void escreveArv( ArvBin p ){
  escreveArvR( p );
  printf( "\n" );
}

/* ----------------------------------------------------- */
/* Função de inicialização de uma árvore vazia */
void criaArv(ArvBin *arv){
  *arv = NULL;
}

/* ----------------------------------------------------- */
/* Função que verifica se a árvore está vazia */
int arvVazia(ArvBin arv){
  return (arv == NULL);
}

/* ----------------------------------------------------- */
/* Retorna a quantidade de nodos internos na arvore      */
int contaNoArv( ArvBin p ){
    if( p == NULL )
        return 0;
    return 1 + contaNoArv( p-> esq ) + contaNoArv( p->dir );
}

/* ----------------------------------------------------- */
/* Retorna a altura da arvore com raiz em p */
int alturaArv( ArvBin p ){
    int he, hd;

    if( p == NULL )
        return 0;
    he= alturaArv( p-> esq );
    hd= alturaArv( p->dir );
    if( he > hd )
        return he+1;
    else
        return hd+1;
}


/* ----------------------------------------------------- */
/* Criação de um novo nodo com o valor do Item preenchido com v */
ArvBin criaNoArv( ItemArv v, ApNodo pai ){
  ArvBin p;

  p = (ArvBin)malloc( sizeof(Nodo) );
  cp(p->item, v);
  p->pai = pai;
  p->esq = NULL; p->dir = NULL;
  return p;
}

/* ----------------------------------------------------- 
   Insere um novo Item na árvore degenerada            
   Ou seja, a árvore fica na forma de uma lista ligada com
   apenas o filho esquerdo sendo um nodo interno. 
*/
ArvBin insereArvLista( ItemArv v, ArvBin arv ){
    if ( eq(arv, NULL) ) {
        return criaNoArv(v, NULL);
    }

    arv->esq = insereArvLista(v, arv->esq);
    arv->esq->pai = arv;

    return arv;
}


/* ----------------------------------------------------- 
   Insere um novo Item na árvore por nivel              
   Resulta em uma árvore quase-completa (balanceada)    
   Utilize o TAD Fila para a implementação desta função 
*/
ArvBin insereArvNivel( ItemArv v, ArvBin raiz ){
    if ( eq(raiz, NULL) ) {
        return criaNoArv(v, NULL);
    }

    Fila *f;
    criaFila(f);
    insereFila(raiz, f);
    while ( !filaVazia(*f) ) {
        ItemFila temp;
        removeFila(f, &temp);

        if ( !eq(temp->esq, NULL) ) {
            insereFila(temp->esq, f);
        } else {
            temp->esq = criaNoArv(v, temp);
            return raiz;
        }

        if (!eq(temp->dir, NULL)) {
            insereFila(temp->dir, f);
        } else {
            temp->dir = criaNoArv(v, temp);
            return raiz;
        }
    }

    return raiz;
}

/* ----------------------------------------------------- */
/* Libera espaço alocado para toda a árvore              */
void freeArv( ArvBin p ){
  if( p == NULL )
    return;
  freeArv( p->esq );
  freeArv( p->dir );
  free( p );
}
