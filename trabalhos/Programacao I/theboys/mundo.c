
/* Personal includes */
#include "mundo.h"
#include "conjunto.h"
#include "fila.h"
#include "lef.h"
#include "missao.h"

/* System includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

static int random_between(int a, int b)
{
        return a + rand() % (b - a + 1); 
}

struct Mundo *inicializa_mundo()
{
        int i;
        struct Mundo *mundo;
        struct conjunto *c_habilidades;

        /* Facilita a criacao de subconjuntos de habilidades necessarias */
        c_habilidades = cria_cjt(NUM_HABILIDADES);
        if (!c_habilidades) 
                MEM_ALLOC_ERR("c_habilidades");
        
        for (i = 0; i < NUM_HABILIDADES; i++) 
                insere_cjt(c_habilidades, i);

        mundo = malloc(sizeof(struct Mundo));
        if (!mundo) {
                MEM_ALLOC_ERR("mundo");
        }

        mundo->tempo_inicial = 0;
        mundo->tempo_fim = T_FIM_DO_MUNDO;
        mundo->TamanhoMundo = TAMANHO_MUNDO;
        mundo->max_habilidades = NUM_HABILIDADES;
        mundo->max_herois = NUM_HEROIS;
        mundo->max_bases = NUM_BASES;
        mundo->max_missoes = NUM_MISSOES;
        mundo->herois = inicializa_herois(NUM_HEROIS, c_habilidades);
        mundo->bases = inicializa_bases(NUM_BASES, TAMANHO_MUNDO);
        mundo->missoes = inicializa_missoes(NUM_MISSOES, TAMANHO_MUNDO,
                                            c_habilidades);
        mundo->lista_eventos = cria_lef();
        if (!mundo->lista_eventos)
                MEM_ALLOC_ERR("mundo->lista_eventos");

        destroi_cjt(c_habilidades);
        return mundo;
}

struct Heroi *inicializa_herois(int n_herois, struct conjunto *c_habilidades)
{
        struct Heroi *herois;
        int i, max_hero_skill;

        herois = malloc(sizeof(struct Heroi) * n_herois);
        if (!herois) {
                MEM_ALLOC_ERR("herois"); 
        }

        for (i = 0; i < n_herois; i++) {
                herois[i].id = i;
                herois[i].exp = 0;
                herois[i].paciencia = random_between(0, 100);
                herois[i].vel = random_between(50, 5000);
                max_hero_skill = random_between(1, 3);
                herois[i].habilidades = cria_subcjt_cjt(c_habilidades,
                                                        max_hero_skill);
        }

        return herois;
}

struct Base *inicializa_bases(int n_bases, int tamanho_mundo)
{
        struct Base *bases;
        int i;

        bases = malloc(sizeof(struct Base) * n_bases);
        if (!bases) {
                MEM_ALLOC_ERR("bases");
        }
        
        for (i = 0; i < n_bases; i++) {
                bases[i].id = i;
                bases[i].pos_x = random_between(0, tamanho_mundo - 1);
                bases[i].pos_y = random_between(0, tamanho_mundo - 1);
                bases[i].max_herois = random_between(3, 10);
                bases[i].herois_presentes = cria_cjt(bases[i].max_herois);
                if (!bases[i].herois_presentes) {
                        MEM_ALLOC_ERR("bases[i].herois_presentes");
                }
                bases[i].fila_espera_herois = fila_cria();
                if (!bases[i].fila_espera_herois) {
                        MEM_ALLOC_ERR("bases[i].fila_espera_herois");
                }
        } 

        return bases;
}

struct Missao *inicializa_missoes(int n_missoes, int tamanho_mundo,
                                  struct conjunto *c_habilidades)
{
        struct Missao *missoes;
        int i, total_hab;

        missoes = malloc(sizeof(struct Missao) * n_missoes);
        if (!missoes)
                MEM_ALLOC_ERR("missoes");

        for (i = 0; i < n_missoes; i++) {
                missoes[i].id = i;
                missoes[i].cumprida = 0;
                missoes[i].tentativa = 1;
                missoes[i].pos_x = random_between(0, tamanho_mundo - 1);
                missoes[i].pos_y = random_between(0, tamanho_mundo - 1);
                total_hab = random_between(6, 10);
                missoes[i].hab_requeridas = cria_subcjt_cjt(c_habilidades,
                                                            total_hab);
        } 

        return missoes;
}

void init_eventos(struct Mundo *m)
{
        int i, tempo, base;
        for (i = 0; i < m->max_herois; i++) {
                base = random_between(0, m->max_bases - 1);
                tempo = random_between(0, 4320);
                insere_lef(m->lista_eventos, cria_evento(tempo, CHEGA,
                                m->herois[i].id, base)); 
        }        

        for (i = 0; i < m->max_missoes; i++) {
                tempo = random_between(0, m->tempo_fim);
                insere_lef(m->lista_eventos, cria_evento(tempo, MISSAO,
                                m->missoes[i].id, 0)); 
        }
        
        insere_lef(m->lista_eventos, cria_evento(m->tempo_fim, FIM, 0, 0)); 
}

void processa_evento_chega(int h, int b, struct Mundo *m)
{
        bool espera;
        m->herois[h].base = b; 

        if (cardinalidade_cjt(m->bases[b].herois_presentes) <
                m->bases[b].max_herois &&
                fila_vazia(m->bases[b].fila_espera_herois)) 
        {
                espera = true;
        } else {
                espera = m->herois[h].paciencia >
                        (10 * fila_tamanho(m->bases[b].fila_espera_herois));
        }

        if (espera) {
                struct evento_t *e = cria_evento(m->tempo_inicial, ESPERA, h, b);
                insere_lef(m->lista_eventos, e);
                printf("%6d: CHEGA HEROI %2d BASE %2d (%2d/%2d) ESPERA\n",
                       m->tempo_inicial, h, b,
                       fila_tamanho(m->bases[b].fila_espera_herois),
                       m->bases[b].max_herois);
        } else {
                struct evento_t *e = cria_evento(m->tempo_inicial, DESISTE, h, b);
                insere_lef(m->lista_eventos, e);
                printf("%6d: CHEGA HEROI %2d BASE %2d (%2d/%2d) DESISTE\n",
                       m->tempo_inicial, h, b,
                       fila_tamanho(m->bases[b].fila_espera_herois),
                       m->bases[b].max_herois);
        }
}

void processa_evento_espera(int h, int b, struct Mundo *m)
{
        printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
               m->tempo_inicial, h, b,
               fila_tamanho(m->bases[b].fila_espera_herois));

        struct evento_t *e;
        enqueue(m->bases[b].fila_espera_herois, h);
        e = cria_evento(m->tempo_inicial, AVISA, b, 0);
        insere_lef(m->lista_eventos, e);
}

void processa_evento_desiste(int h, int b, struct Mundo *m)
{
        struct evento_t *e;
        int nova_base;

        nova_base = random_between(0, NUM_BASES - 1);
        e = cria_evento(m->tempo_inicial, VIAJA, h, nova_base);
        insere_lef(m->lista_eventos, e);
        printf("%6d: DESISTE HEROI %2d BASE %d\n", m->tempo_inicial, h, b);
}
void processa_evento_avisa(int b, struct Mundo *m)
{
        int heroi;
        struct evento_t *e;

        printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ",
               m->tempo_inicial, b,
               cardinalidade_cjt(m->bases[b].herois_presentes),
               m->bases[b].max_herois);
        fila_imprime(m->bases[b].fila_espera_herois);
        printf("\n");

        while (cardinalidade_cjt(m->bases[b].herois_presentes) <
                m->bases[b].max_herois &&
                !fila_vazia(m->bases[b].fila_espera_herois))
        {
                dequeue(m->bases[b].fila_espera_herois, &heroi);
                insere_cjt(m->bases[b].herois_presentes, heroi);
                e = cria_evento(m->tempo_inicial, ENTRA, heroi, b);
                insere_lef(m->lista_eventos, e);

                printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
                       m->tempo_inicial, b, heroi);
        }
}

void processa_evento_entra(int h, int b, struct Mundo *m)
{
        int tempo_perm;
        struct evento_t *e;

        tempo_perm = 15 + m->herois[h].paciencia * random_between(1, 20);
        e = cria_evento(m->tempo_inicial + tempo_perm, SAI, h, b);
        insere_lef(m->lista_eventos, e);

        printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
               m->tempo_inicial, h, b,
               cardinalidade_cjt(m->bases[b].herois_presentes),
               m->bases[b].max_herois,
               m->tempo_inicial + tempo_perm);
}

void processa_evento_sai(int h, int b, struct Mundo *m)
{
        printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
               m->tempo_inicial, h, b,
               cardinalidade_cjt(m->bases[b].herois_presentes),
               m->bases[b].max_herois);

        int nova_base;
        struct evento_t *e1, *e2;

        retira_cjt(m->bases[b].herois_presentes, h);
        nova_base = random_between(0, NUM_BASES - 1);

        e1 = cria_evento(m->tempo_inicial, VIAJA, h, nova_base);
        e2 = cria_evento(m->tempo_inicial, AVISA, b, 0);
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

void processa_evento_viaja(int h, int d, struct Mundo *m)
{
        int dist, duracao, base_atual; 
        struct evento_t *e;

        base_atual = m->herois[h].base; 
        dist = dist_cartesiana(m->bases[base_atual].pos_x,
                               m->bases[base_atual].pos_y,
                               m->bases[d].pos_x,
                               m->bases[d].pos_y);
        duracao = dist / m->herois[h].vel;

        e = cria_evento(m->tempo_inicial + duracao, CHEGA, h, d);
        insere_lef(m->lista_eventos, e);

        printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
               m->tempo_inicial, h, base_atual, d, dist, m->herois[h].vel,
               m->tempo_inicial + duracao);
        
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
        for (i = 1; i < m->max_bases; i++) {
                dist = dist_cartesiana(Mpos_x, Mpos_y,
                                       m->bases[i].pos_x,
                                       m->bases[i].pos_y);
                if (dist < menor_dist) {
                        menor_dist = dist;
                        base = i;
                }
        }


        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS ", m->tempo_inicial,
                                                        id_m, base, dist);
 
        if (vazio_cjt(m->bases[base].herois_presentes))
                return -1;

        imprime_cjt(m->bases[base].herois_presentes);
        
        inicia_iterador_cjt(m->bases[base].herois_presentes);
        incrementa_iterador_cjt(m->bases[base].herois_presentes, &heroi);
        total_hab_anterior = NULL;
        total_hab_atual = copia_cjt(m->herois[heroi].habilidades);
        while (incrementa_iterador_cjt(m->bases[base].herois_presentes, &heroi)) {
                total_hab_anterior = total_hab_atual;
                printf("%6d: MISSAO %d HAB HEROI %2d: ", m->tempo_inicial, id_m,
                                                        heroi);
                imprime_cjt(m->herois[heroi].habilidades);
                total_hab_atual = uniao_cjt(total_hab_atual,
                                              m->herois[heroi].habilidades);
                total_hab_anterior = destroi_cjt(total_hab_anterior);
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: ", m->tempo_inicial, id_m, base);
        imprime_cjt(total_hab_atual);

        if (!contido_cjt(total_hab_atual, m->missoes[id_m].hab_requeridas)) {
                destroi_cjt(total_hab_atual);
                return -1;
        } else {
                destroi_cjt(total_hab_atual);
                return base;
        }
        
}

void processa_evento_missao(int mi, struct Mundo *m)
{
        printf("%6d: MISSAO %d TENT %d HAB REQ: ", m->tempo_inicial, mi,
                                                m->missoes[mi].tentativa);
        imprime_cjt(m->missoes[mi].hab_requeridas);

        struct evento_t *e;
        int bmp, heroi;
        bmp = calc_bmp(mi, m);
        if (bmp == -1) {
                e = cria_evento(m->tempo_inicial + 24 * 60, MISSAO, mi, 0);
                insere_lef(m->lista_eventos, e);
                m->missoes[mi].tentativa++;
                printf("%6d: MISSAO %d IMPOSSIVEL\n", m->tempo_inicial, mi);
        } else {
                inicia_iterador_cjt(m->bases[bmp].herois_presentes);
                while(incrementa_iterador_cjt(m->bases[bmp].herois_presentes, &heroi)) {
                        m->herois[heroi].exp++;
                }
                m->missoes[mi].cumprida = 1;
                printf("%6d: MISSAO %d CUMPRIDA BASE %d\n", m->tempo_inicial, mi, bmp);
        }
}

void processa_evento_fim(struct Mundo **m)
{
        printf("%6d: FIM\n", (*m)->tempo_inicial);
        int i, missoes_cumpridas, min_tent, max_tent, tentativas;

        for (i = 0; i < (*m)->max_herois; i++) {
                printf("HEROI %2d PAC %2d VEL %4d EXP %4d HABS ",
                       (*m)->herois[i].id, (*m)->herois[i].paciencia,
                       (*m)->herois[i].vel, (*m)->herois[i].exp);
                imprime_cjt((*m)->herois[i].habilidades);
                destroi_cjt((*m)->herois[i].habilidades);
        }
        free((*m)->herois);
        (*m)->herois = NULL;

        for (i = 0; i < (*m)->max_bases; i++) {
                destroi_cjt((*m)->bases[i].herois_presentes);
                fila_destroi(&(*m)->bases[i].fila_espera_herois);
        }
        free((*m)->bases);
        (*m)->bases = NULL;

        min_tent = (*m)->missoes[0].tentativa;
        max_tent = (*m)->missoes[0].tentativa;
        missoes_cumpridas = 0;
        tentativas = 0;
        for (i = 0; i < (*m)->max_missoes; i++) {
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
               (*m)->max_missoes, ((double)missoes_cumpridas / (*m)->max_missoes * 100));
        printf("TENTATIVA/MISSAO: MIN %d, MAX %d, MEDIA %.2f\n",
               min_tent, max_tent, (double)tentativas / (*m)->max_missoes);

        free((*m)->missoes);
        (*m)->missoes = NULL;
}

void termina_simulacao(struct Mundo **m)
{
        (*m)->lista_eventos = destroi_lef((*m)->lista_eventos);
        free(*m);
        *m = NULL;
}
