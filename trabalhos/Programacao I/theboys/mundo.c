/* Personal includes */
#include "mundo.h"
#include "conjunto.h"
#include "fila.h"
#include "lef.h"

/* System includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

struct Mundo *initMundo()
{
        int i;
        struct Mundo *mundo;
        struct conjunto *c_habilidades;

        /* Facilita a criacao de subconjuntos de habilidades necessarias */
        c_habilidades = cria_cjt(N_HABILIDADES);
        if (!c_habilidades) 
                MEM_ALLOC_ERR("c_habilidades");
        
        for (i = 0; i < N_HABILIDADES; i++) 
                insere_cjt(c_habilidades, i);

        mundo = malloc(sizeof(struct Mundo));
        if (!mundo) {
                MEM_ALLOC_ERR("mundo");
        }

        mundo->timer = 0;
        mundo->nHab = N_HABILIDADES;
        mundo->nHerois = N_HEROIS;
        mundo->nBases = N_BASES;
        mundo->nMissoes = N_MISSOES;
        mundo->herois = initHerois(c_habilidades);
        mundo->bases = initBases();
        mundo->missoes = initMissoes(c_habilidades);
        mundo->lista_eventos = cria_lef();
        if (!mundo->lista_eventos)
                MEM_ALLOC_ERR("mundo->lista_eventos");

        destroi_cjt(c_habilidades);
        return mundo;
}

static int rBetween(int a, int b)
{
        return a + rand() % (b - a + 1); 
}

int getTimer(struct Mundo *m)
{
        return m->timer;
}

void setTimer(struct Mundo *m, int tempo)
{
        m->timer = tempo;
}

struct lef_t *getListaDeEventos(struct Mundo *m)
{
        return m->lista_eventos;
}

struct Heroi *initHerois(struct conjunto *c_habilidades)
{
        struct Heroi *herois;
        int i;

        herois = malloc(sizeof(struct Heroi) * N_HEROIS);
        if (!herois)
                MEM_ALLOC_ERR("initHerois"); 

        for (i = 0; i < N_HEROIS; i++) {
                herois[i].id = i;
                herois[i].exp = 0;
                herois[i].paciencia = rBetween(0, 100);
                herois[i].vel = rBetween(50, 5000);
                herois[i].hab = cria_subcjt_cjt(c_habilidades, rBetween(1, 3));
        }

        return herois;
}

struct Base *initBases()
{
        struct Base *bases;
        int i;

        bases = malloc(sizeof(struct Base) * N_BASES);
        if (!bases)
                MEM_ALLOC_ERR("initBases");
        
        for (i = 0; i < N_BASES; i++) {
                bases[i].id = i;
                bases[i].pos_x = rBetween(0, TAMANHO_MUNDO - 1);
                bases[i].pos_y = rBetween(0, TAMANHO_MUNDO - 1);
                bases[i].nHerois = rBetween(3, 10);
                bases[i].hPresentes = cria_cjt(bases[i].nHerois);
                if (!bases[i].hPresentes) {
                        MEM_ALLOC_ERR("bases[i].hPresentes");
                }
                bases[i].fHerois = fila_cria();
                if (!bases[i].fHerois) {
                        MEM_ALLOC_ERR("bases[i].fHerois");
                }
        } 

        return bases;
}

struct Missao *initMissoes(struct conjunto *c_habilidades)
{
        struct Missao *missoes;
        int i, total_hab;

        missoes = malloc(sizeof(struct Missao) * N_MISSOES);
        if (!missoes)
                MEM_ALLOC_ERR("missoes");

        for (i = 0; i < N_MISSOES; i++) {
                missoes[i].id = i;
                missoes[i].cumprida = 0;
                missoes[i].tentativa = 1;
                missoes[i].pos_x = rBetween(0, TAMANHO_MUNDO - 1);
                missoes[i].pos_y = rBetween(0, TAMANHO_MUNDO - 1);
                total_hab = rBetween(6, 10);
                missoes[i].hab_requeridas = cria_subcjt_cjt(c_habilidades,
                                                            total_hab);
        } 

        return missoes;
}

void initEventos(struct Mundo *m)
{
        int i, tempo, base;
        for (i = 0; i < m->nHerois; i++) {
                base = rBetween(0, m->nBases - 1);
                tempo = rBetween(0, 4320);
                insere_lef(m->lista_eventos, cria_evento(tempo, CHEGA,
                                m->herois[i].id, base)); 
        }        

        for (i = 0; i < m->nMissoes; i++) {
                tempo = rBetween(0, T_FIM_DO_MUNDO);
                insere_lef(m->lista_eventos, cria_evento(tempo, MISSAO,
                                m->missoes[i].id, 0)); 
        }
        
        insere_lef(m->lista_eventos, cria_evento(T_FIM_DO_MUNDO, FIM, 0, 0)); 
}

void evento_chega(int h, int b, struct Mundo *m)
{
        bool espera;
        m->herois[h].base = b; 

        if (cardinalidade_cjt(m->bases[b].hPresentes) <
                m->bases[b].nHerois &&
                fila_vazia(m->bases[b].fHerois)) 
        {
                espera = true;
        } else {
                espera = m->herois[h].paciencia >
                        (10 * fila_tamanho(m->bases[b].fHerois));
        }

        if (espera) {
                struct evento_t *e = cria_evento(m->timer, ESPERA, h, b);
                insere_lef(m->lista_eventos, e);
                printf("%6d: CHEGA HEROI %2d BASE %2d (%2d/%2d) ESPERA\n",
                       m->timer, h, b,
                       cardinalidade_cjt(m->bases[b].hPresentes),
                       m->bases[b].nHerois);
        } else {
                struct evento_t *e = cria_evento(m->timer, DESISTE, h, b);
                insere_lef(m->lista_eventos, e);
                printf("%6d: CHEGA HEROI %2d BASE %2d (%2d/%2d) DESISTE\n",
                       m->timer, h, b,
                       cardinalidade_cjt(m->bases[b].hPresentes),
                       m->bases[b].nHerois);
        }
}

void evento_espera(int h, int b, struct Mundo *m)
{
        printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
               m->timer, h, b,
               fila_tamanho(m->bases[b].fHerois));

        struct evento_t *e;
        enqueue(m->bases[b].fHerois, h);
        e = cria_evento(m->timer, AVISA, b, 0);
        insere_lef(m->lista_eventos, e);
}

void evento_desiste(int h, int b, struct Mundo *m)
{
        struct evento_t *e;
        int nova_base;

        nova_base = rBetween(0, N_BASES - 1);
        e = cria_evento(m->timer, VIAJA, h, nova_base);
        insere_lef(m->lista_eventos, e);
        printf("%6d: DESISTE HEROI %2d BASE %d\n", m->timer, h, b);
}
void evento_avisa(int b, struct Mundo *m)
{
        int heroi;
        struct evento_t *e;

        printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ",
               m->timer, b,
               cardinalidade_cjt(m->bases[b].hPresentes),
               m->bases[b].nHerois);
        fila_imprime(m->bases[b].fHerois);
        printf("\n");

        while (cardinalidade_cjt(m->bases[b].hPresentes) < m->bases[b].nHerois &&
                !fila_vazia(m->bases[b].fHerois))
        {
                dequeue(m->bases[b].fHerois, &heroi);
                insere_cjt(m->bases[b].hPresentes, heroi);
                e = cria_evento(m->timer, ENTRA, heroi, b);
                insere_lef(m->lista_eventos, e);

                printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
                       m->timer, b, heroi);
        }
}

void evento_entra(int h, int b, struct Mundo *m)
{
        int tempo_perm;
        struct evento_t *e;

        tempo_perm = 15 + m->herois[h].paciencia * rBetween(1, 20);
        e = cria_evento(m->timer + tempo_perm, SAI, h, b);
        insere_lef(m->lista_eventos, e);

        printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
               m->timer, h, b,
               cardinalidade_cjt(m->bases[b].hPresentes),
               m->bases[b].nHerois,
               m->timer + tempo_perm);
}

void evento_sai(int h, int b, struct Mundo *m)
{
        printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
               m->timer, h, b,
               cardinalidade_cjt(m->bases[b].hPresentes),
               m->bases[b].nHerois);

        int nova_base;
        struct evento_t *e1, *e2;

        retira_cjt(m->bases[b].hPresentes, h);
        nova_base = rBetween(0, N_BASES - 1);

        e1 = cria_evento(m->timer, VIAJA, h, nova_base);
        e2 = cria_evento(m->timer, AVISA, b, 0);
        insere_lef(m->lista_eventos, e1);
        insere_lef(m->lista_eventos, e2);
}

static int dist_cartesiana(int x1, int y1, int x2, int y2)
{
        int deltax, deltay;
        deltax = x1 - x2;
        deltay = y1 - y2;

        return sqrt(deltax * deltax + deltay * deltay);
}

void evento_viaja(int h, int d, struct Mundo *m)
{
        int dist, duracao, base_atual; 
        struct evento_t *e;

        base_atual = m->herois[h].base; 
        dist = dist_cartesiana(m->bases[base_atual].pos_x,
                               m->bases[base_atual].pos_y,
                               m->bases[d].pos_x,
                               m->bases[d].pos_y);
        duracao = dist / m->herois[h].vel;

        e = cria_evento(m->timer + duracao, CHEGA, h, d);
        insere_lef(m->lista_eventos, e);

        printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
               m->timer, h, base_atual, d, dist, m->herois[h].vel,
               m->timer + duracao);
        
}

int calc_bmp(int id_m, struct Mundo *m)
{
        struct conjunto *total_hab_atual, *total_hab_anterior;
        int i, dist, Mpos_x, Mpos_y, menor_dist, base, heroi;
        Mpos_x = m->missoes[id_m].pos_x;
        Mpos_y = m->missoes[id_m].pos_y;

        dist = dist_cartesiana(Mpos_x, Mpos_y,
                                m->bases[0].pos_x,
                                m->bases[0].pos_y);
        menor_dist = dist;
        base = 0;
        for (i = 1; i < m->nBases; i++) {
                dist = dist_cartesiana(Mpos_x, Mpos_y,
                                       m->bases[i].pos_x,
                                       m->bases[i].pos_y);
                if (dist < menor_dist) {
                        menor_dist = dist;
                        base = i;
                }
        }


        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS ", m->timer,
                                                        id_m, base, dist);
 
        if (vazio_cjt(m->bases[base].hPresentes))
                return -1;

        imprime_cjt(m->bases[base].hPresentes);
        
        inicia_iterador_cjt(m->bases[base].hPresentes);
        incrementa_iterador_cjt(m->bases[base].hPresentes, &heroi);
        total_hab_anterior = NULL;
        total_hab_atual = copia_cjt(m->herois[heroi].hab);
        while (incrementa_iterador_cjt(m->bases[base].hPresentes, &heroi)) {
                total_hab_anterior = total_hab_atual;
                printf("%6d: MISSAO %d HAB HEROI %2d: ", m->timer, id_m,
                                                        heroi);
                imprime_cjt(m->herois[heroi].hab);
                total_hab_atual = uniao_cjt(total_hab_atual,
                                              m->herois[heroi].hab);
                total_hab_anterior = destroi_cjt(total_hab_anterior);
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: ", m->timer, id_m, base);
        imprime_cjt(total_hab_atual);

        if (!contido_cjt(total_hab_atual, m->missoes[id_m].hab_requeridas)) {
                destroi_cjt(total_hab_atual);
                return -1;
        } else {
                destroi_cjt(total_hab_atual);
                return base;
        }
        
}

void evento_missao(int mi, struct Mundo *m)
{
        printf("%6d: MISSAO %d TENT %d HAB REQ: ", m->timer, mi,
                                                m->missoes[mi].tentativa);
        imprime_cjt(m->missoes[mi].hab_requeridas);

        struct evento_t *e;
        int bmp, heroi;
        bmp = calc_bmp(mi, m);
        if (bmp == -1) {
                e = cria_evento(m->timer + 24 * 60, MISSAO, mi, 0);
                insere_lef(m->lista_eventos, e);
                m->missoes[mi].tentativa++;
                printf("%6d: MISSAO %d IMPOSSIVEL\n", m->timer, mi);
        } else {
                inicia_iterador_cjt(m->bases[bmp].hPresentes);
                while(incrementa_iterador_cjt(m->bases[bmp].hPresentes, &heroi)) {
                        m->herois[heroi].exp++;
                }
                m->missoes[mi].cumprida = 1;
                printf("%6d: MISSAO %d CUMPRIDA BASE %d\n", m->timer, mi, bmp);
        }
}

void evento_fim(struct Mundo **m)
{
        printf("%6d: FIM\n", (*m)->timer);
        int i, missoes_cumpridas, min_tent, max_tent, tentativas;

        for (i = 0; i < (*m)->nHerois; i++) {
                printf("HEROI %2d PAC %2d VEL %4d EXP %4d HABS ",
                       (*m)->herois[i].id, (*m)->herois[i].paciencia,
                       (*m)->herois[i].vel, (*m)->herois[i].exp);
                imprime_cjt((*m)->herois[i].hab);
                destroi_cjt((*m)->herois[i].hab);
        }
        free((*m)->herois);
        (*m)->herois = NULL;

        for (i = 0; i < (*m)->nBases; i++) {
                destroi_cjt((*m)->bases[i].hPresentes);
                fila_destroi(&(*m)->bases[i].fHerois);
        }
        free((*m)->bases);
        (*m)->bases = NULL;

        min_tent = (*m)->missoes[0].tentativa;
        max_tent = (*m)->missoes[0].tentativa;
        missoes_cumpridas = 0;
        tentativas = 0;
        for (i = 0; i < (*m)->nMissoes; i++) {
                if ((*m)->missoes[i].cumprida)
                        missoes_cumpridas++;
                
                if ((*m)->missoes[i].tentativa < min_tent)
                        min_tent = (*m)->missoes[i].tentativa;
                
                if ((*m)->missoes[i].tentativa > max_tent)
                        max_tent = (*m)->missoes[i].tentativa;

                tentativas += (*m)->missoes[i].tentativa;
                destroi_cjt((*m)->missoes[i].hab_requeridas);
        }
        printf("MISSOES CUMPRIDAS: %d/%d (%.2f%%)\n", missoes_cumpridas,
               (*m)->nMissoes, ((double)missoes_cumpridas / (*m)->nMissoes * 100));
        printf("TENTATIVA/MISSAO: MIN %d, MAX %d, MEDIA %.2f\n",
               min_tent, max_tent, (double)tentativas / (*m)->nMissoes);

        free((*m)->missoes);
        (*m)->missoes = NULL;
}

void termina_simulacao(struct Mundo **m)
{
        (*m)->lista_eventos = destroi_lef((*m)->lista_eventos);
        free(*m);
        *m = NULL;
}
