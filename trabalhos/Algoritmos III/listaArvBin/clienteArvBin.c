#include <stdio.h>
#include <stdlib.h>

typedef int ItemArv;
#include "arvBin.h"

int somaChave(ArvBin *arv)
{
    if (*arv == NULL) return 0;
    return (*arv)->item + somaChave(&(*arv)->esq) + somaChave(&(*arv)->dir);
}

int valorMinimo(ArvBin *arv)
{
    if (*arv == NULL) return 0;

    int min = (*arv)->item;
    int minEsq = valorMinimo(&(*arv)->esq);
    int minDir = valorMinimo(&(*arv)->dir);

    if (minEsq < min && minEsq != 0) min = minEsq;
    if (minDir < min && minDir != 0) min = minDir;

    return min;
}

void paiMaior(ArvBin *arv)
{
    if (*arv == NULL) return;

    paiMaior(&(*arv)->esq);
    paiMaior(&(*arv)->dir);

    if ((*arv)->esq != NULL && (*arv)->dir != NULL) {
        (*arv)->item = ((*arv)->esq->item > (*arv)->dir->item) ?
            (*arv)->esq->item : (*arv)->dir->item;
    } 
    else if ((*arv)->esq != NULL) {
        (*arv)->item = (*arv)->esq->item;
    } 
    else if ((*arv)->dir != NULL) {
        (*arv)->item = (*arv)->dir->item;
    }
}

void troca(ArvBin *a1, ArvBin *a2)
{
    int aux = (*a1)->item;
    (*a1)->item = (*a2)->item;
    (*a2)->item = aux;
}

void maiorNaRaiz(ArvBin *arv)
{
    if (*arv == NULL) return;
    
    maiorNaRaiz(&(*arv)->esq);
    maiorNaRaiz(&(*arv)->dir);

    ArvBin maior = *arv;
    
    if ((*arv)->esq != NULL && (*arv)->esq->item > maior->item)
        maior = (*arv)->esq;

    if ((*arv)->dir != NULL && (*arv)->dir->item > maior->item)
        maior = (*arv)->dir;

    if (maior != *arv) {
        troca(arv, &maior);
    }
}

void ordenaPeloMaior(ArvBin *arv)
{
    if (*arv == NULL) return;

    maiorNaRaiz(arv);
    if ((*arv)->esq != NULL && (*arv)->dir != NULL) {
        if ((*arv)->esq->item < (*arv)->dir->item)
            troca(&(*arv)->dir, &(*arv)->esq);
    }

    ordenaPeloMaior(&(*arv)->esq);
    ordenaPeloMaior(&(*arv)->dir);
}

ArvBin criaNodo(ItemArv item)
{
    ArvBin novo = (ApNodo)malloc(sizeof(Nodo));
    if (novo == NULL) return NULL;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->item = item;
    return novo;
}

ArvBin dobraArvore(ArvBin *arv)
{
    if (*arv == NULL) return *arv;

    ArvBin novo;
    if ((*arv)->item % 2 == 0) {
        novo = criaNodo((*arv)->item + 1);
        novo->esq = (*arv);
    } else if ((*arv)->item % 2 != 0) {
        novo = criaNodo((*arv)->item - 1);
        novo->dir = (*arv);
    }

    if ((*arv)->esq != NULL)
        (*arv)->esq = dobraArvore(&(*arv)->esq);

    if ((*arv)->dir != NULL)
        (*arv)->dir = dobraArvore(&(*arv)->dir);

    return novo;
}

int main(int argc, char *argv[])
{
    (void)argc;    
    (void)argv;
    ArvBin arv;
    ItemArv v;

    criaArv( &arv );
    printf("Insira uma sequencia de chaves. Finalize a sequencia com 0: \n");
    scanf( "%d", &v );
    while( v != 0 ){
        insereArvNivel( v, &arv );
        scanf( "%d", &v );
    }
    printf( "\nArvore\n" );
    escreveArv( arv );

      printf("%d\n", somaChave(&arv));

      printf("%d\n", valorMinimo(&arv) );

      paiMaior(&arv);
      escreveArv( arv );

      //maiorNaRaiz(&arv);
      //escreveArv( arv );

      //ordenaPeloMaior(&arv);
      //escreveArv( arv );

      //ArvBin raiz = dobraArvore(&arv);
      //escreveArv( raiz );
      
    free( arv );
    return 0;
}
