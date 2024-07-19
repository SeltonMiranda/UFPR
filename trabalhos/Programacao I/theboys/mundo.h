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

/* Constantes Globais */
#define T_FIM_DO_MUNDO 525600
#define TAMANHO_MUNDO 20000
#define NUM_HABILIDADES 10
#define NUM_HEROIS (NUM_HABILIDADES * 5)
#define NUM_BASES (NUM_HEROIS / 6)
#define NUM_MISSOES (T_FIM_DO_MUNDO / 100)

#define MEM_ALLOC_ERR(s) do { \
        fprintf(stderr, "ERRO: Memoria para %s nao alocada\n", #s); \
        exit(1); \
} while (0);

struct Mundo {
        int tempo_inicial;
        int tempo_fim;

        int max_herois;
        struct Heroi *herois;

        int max_bases;
        struct Base *bases;

        int max_missoes;
        struct Missao *missoes;

        int max_habilidades;
        int TamanhoMundo;

        struct lef_t *lista_eventos;
};

struct Mundo *inicializa_mundo();
struct Heroi *inicializa_herois(int n_herois, struct conjunto *c_habilidades);
struct Base *inicializa_bases(int n_bases, int tamanho_mundo);
struct Missao *inicializa_missoes(int n_missoes, int tamanho_mundo,
                                  struct conjunto *c_habilidades);
void destroi_mundo(struct Mundo **m);
void init_eventos(struct Mundo *m);
void processa_evento_chega(int h, int b, struct Mundo *m);
void processa_evento_espera(int h, int b, struct Mundo *m);
void processa_evento_avisa(int b, struct Mundo *m);
void processa_evento_entra(int h, int b, struct Mundo *m);
void processa_evento_sai(int h, int b, struct Mundo *m);
void processa_evento_viaja(int h, int d, struct Mundo *m);
void processa_evento_desiste(int h, int b, struct Mundo *m);
void processa_evento_missao(int mi, struct Mundo *m);
void processa_evento_fim(struct Mundo **m);
void termina_simulacao(struct Mundo **m);

#endif
