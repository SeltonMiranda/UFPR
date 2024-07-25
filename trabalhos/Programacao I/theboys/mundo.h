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

struct Mundo {
        int timer;
        int nHerois;
        int nBases;
        int nMissoes;
        int nHab;
        struct Base bases[N_BASES];
        struct Missao missoes[N_MISSOES];
        struct Heroi herois[N_HEROIS];
        struct lef_t *lista_eventos;
};

struct Mundo *initMundo();
void initHerois(struct Mundo *m);
void initBases(struct Mundo *m);
void initMissoes(struct Mundo *m);
void initEventos(struct Mundo *m);
void evento_chega(int h, int b, struct Mundo *m);
void evento_espera(int h, int b, struct Mundo *m);
void evento_avisa(int b, struct Mundo *m);
void evento_entra(int h, int b, struct Mundo *m);
void evento_sai(int h, int b, struct Mundo *m);
void evento_viaja(int h, int d, struct Mundo *m);
void evento_desiste(int h, int b, struct Mundo *m);
void evento_missao(int mi, struct Mundo *m);
void evento_fim(struct Mundo **m);
void termina_simulacao(struct Mundo **m);
void destroi_mundo(struct Mundo **m);
int getTimer(struct Mundo *m);
void setTimer(struct Mundo *m, int tempo);
struct lef_t *getListaDeEventos(struct Mundo *m);

#endif
