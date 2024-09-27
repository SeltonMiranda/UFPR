/*---------------------------------------------------------
Interface: TAD Arvore
-----------------------------------------------------------*/
typedef struct Nodo *ApNodo;
typedef struct Nodo {
  ItemArv item;
  ApNodo pai, esq, dir;
} Nodo;

typedef ApNodo ArvBin;

void criaArv( ArvBin* );
ArvBin criaNoArv( ItemArv v, ApNodo pai );
int arvVazia( ArvBin );
ArvBin insereArvLista( ItemArv, ArvBin );  /* insercao arv. degenerada */
ArvBin insereArvNivel( ItemArv, ArvBin );  /* insercao por nivel */
void escreveArv( ArvBin );
int alturaArv( ArvBin );
int contaNoArv( ArvBin );
void freeArv( ArvBin );
