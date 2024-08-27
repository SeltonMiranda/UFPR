#ifndef MUNDO_H
#define MUNDO_H

/* Personal includes */
#include "conjunto.h"
#include "missao.h"
#include "base.h"
#include "heroi.h"
#include "lef.h"

/* System includes */
#include <stdio.h>

/* Eventos */
#define CHEGA 0
#define ESPERA 1
#define DESISTE 2
#define AVISA 3
#define ENTRA 4
#define SAI 5
#define VIAJA 6
#define MISSAO 7
#define FIM 8

/* Constantes */
#define T_FIM_DO_MUNDO 525600
#define TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 6)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

#define MEM_ALLOC_ERR(s) do { \
        fprintf(stderr, "ERRO: Memoria nao alocada para %s\n", #s); \
        exit(1); \
} while (0);

typedef struct Mundo {
        int timer; /* Tempo atual da simulacao */
        int nHerois; /* Quantidade de herois */
        int nBases; /* Quantidade de bases */
        int nMissoes; /* Quantidade de missoes */
        int nHab; /* Quantidade de habilidades diferentes */
        struct Base bases[N_BASES]; /* Vetor de bases */
        struct Missao missoes[N_MISSOES]; /* Vetor de missoes */
        struct Heroi herois[N_HEROIS]; /* Vetor de herois */
        struct lef_t *lista_eventos; /* lista de eventos do mundo */
} Mundo;

/* Inicializa as estruturas do mundo */
Mundo *initMundo();

/* Inicializa os herois */
void initHerois(Mundo *m);

/* Inicializa as bases */
void initBases(Mundo *m);

/* Inicializa as missoes */
void initMissoes(Mundo *m);

/* Inicializa os evento */
void initEventos(Mundo *m);

/* Heroi chega na base */ 
void evento_chega(int h, int b, Mundo *m);

/* Heroi espera na fila */
void evento_espera(int h, int b, Mundo *m);

/* Avisa porteiro que o heroi entrou na fila */
void evento_avisa(int b, Mundo *m);

/* Heroi entra na base */
void evento_entra(int h, int b, Mundo *m);

/* Heroi sai da base */
void evento_sai(int h, int b, Mundo *m);

/* Heroi viaja para outra base */
void evento_viaja(int h, int d, Mundo *m);

/* Heroi desiste de entrar na fila */
void evento_desiste(int h, int b, Mundo *m);

/* Missao reune as habilidades dos herois na base */
void evento_missao(int mi, Mundo *m);

/* Ultimo evento, desaloca as estruturas do mundo */
void evento_fim(Mundo **m);

/* Destroi o mundo */
void termina_simulacao(Mundo **m);

/* Retorna o tempo atual do mundo */
int getTimer(Mundo *m);

/* Ajusta o tempo do mundo*/
void setTimer(Mundo *m, int tempo);

/* Retorna a lista de eventos do mundo*/
struct lef_t *getListaDeEventos(Mundo *m);
#endif /* MUNDO_H */
