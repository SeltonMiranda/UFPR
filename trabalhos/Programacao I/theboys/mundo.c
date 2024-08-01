/* Personal includes */
#include "mundo.h"
#include "conjunto.h"
#include "fila.h"
#include "lef.h"

/* System includes */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

struct Mundo *initMundo()
{
        struct Mundo *mundo;
        mundo = malloc(sizeof(struct Mundo));
        if (!mundo) {
                MEM_ALLOC_ERR("mundo");
        }

        mundo->timer = 0;
        mundo->nHab = N_HABILIDADES;
        mundo->nHerois = N_HEROIS;
        mundo->nBases = N_BASES;
        mundo->nMissoes = N_MISSOES;
        mundo->lista_eventos = cria_lef();
        if (!mundo->lista_eventos)
                MEM_ALLOC_ERR("mundo->lista_eventos");

        initBases(mundo);
        initMissoes(mundo); initHerois(mundo);
        return mundo;
}

static int rBetween(int a, int b)
{
        return rand() % (b - a + 1) + a; 
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

void initHerois(struct Mundo *m)
{
        int i, qnt;
        struct conjunto *hHab;
        for (i = 0; i < N_HEROIS; i++) {
                m->herois[i].id = i;
                m->herois[i].exp = 0;
                m->herois[i].paciencia = rBetween(0, 100);
                m->herois[i].vel = rBetween(50, 5000);
                m->herois[i].hab = cria_cjt(N_HABILIDADES);
                qnt = rBetween(1, 3);
                hHab = m->herois[i].hab;

                while (cardinalidade_cjt(hHab) < qnt)
                        insere_cjt(hHab, rBetween(0, N_HABILIDADES - 1));
        }
}

void initBases(struct Mundo *m)
{
        int i;
        for (i = 0; i < N_BASES; i++) {
                m->bases[i].id = i;
                m->bases[i].pos_x = rBetween(0, TAMANHO_MUNDO - 1);
                m->bases[i].pos_y = rBetween(0, TAMANHO_MUNDO - 1);
                m->bases[i].nHerois = rBetween(3, 10);
                m->bases[i].hPresentes = cria_cjt(m->bases[i].nHerois);
                if (!m->bases[i].hPresentes) {
                        MEM_ALLOC_ERR("m->bases[i].hPresentes");
                }
                m->bases[i].fHerois = fila_cria();
                if (!m->bases[i].fHerois)
                        MEM_ALLOC_ERR("m->bases[i].fHerois");
        } 
}

void initMissoes(struct Mundo *m)
{
        int i, qnt;
        struct conjunto *mHab;
        for (i = 0; i < N_MISSOES; i++) {
                m->missoes[i].id = i;
                m->missoes[i].cumprida = 0;
                m->missoes[i].tentativa = 1;
                m->missoes[i].pos_x = rBetween(0, TAMANHO_MUNDO - 1);
                m->missoes[i].pos_y = rBetween(0, TAMANHO_MUNDO - 1);
                m->missoes[i].hab_requeridas = cria_cjt(N_HABILIDADES); 
                if (!m->missoes[i].hab_requeridas)
                        MEM_ALLOC_ERR("m->missoes[i].hab_requeridas");
                qnt = rBetween(6, 10);
                mHab = m->missoes[i].hab_requeridas;

                while (cardinalidade_cjt(mHab) < qnt)
                        insere_cjt(mHab, rBetween(0, N_HABILIDADES - 1));
        } 

}

void initEventos(struct Mundo *m)
{
        int i, tempo, base;
        struct evento_t *e;
        for (i = 0; i < m->nHerois; i++) {
                base = rBetween(0, m->nBases - 1);
                tempo = rBetween(0, 4320);
                e = cria_evento(tempo, CHEGA, i, base);
                if (e == NULL)
                        MEM_ALLOC_ERR("evento heroi nao criado\n");
                insere_lef(m->lista_eventos, e); 
        }        

        for (i = 0; i < m->nMissoes; i++) {
                tempo = rBetween(0, T_FIM_DO_MUNDO);
                e = cria_evento(tempo, MISSAO, i, 0);
                if (e == NULL)
                        MEM_ALLOC_ERR("evento missao nao alocado\n");
                insere_lef(m->lista_eventos, e); 
        }

        e = cria_evento(T_FIM_DO_MUNDO, FIM, 0, 0);
        if (e == NULL)
                MEM_ALLOC_ERR("evento fim nao alocado\n");
        insere_lef(m->lista_eventos, e); 
}

void evento_chega(int h, int b, struct Mundo *m)
{
        m->herois[h].base = b; 

        int espera;
        int maxHeroisBase, qntdHeroisBase, pacHeroi; 
        struct fila *heroisFila;
        struct evento_t *e;

        pacHeroi = m->herois[h].paciencia;
        qntdHeroisBase = cardinalidade_cjt(m->bases[b].hPresentes);
        maxHeroisBase = m->bases[b].nHerois;
        heroisFila = m->bases[b].fHerois;

        if (qntdHeroisBase < maxHeroisBase && fila_vazia(heroisFila)) {
                espera = 1;
        } else {
                espera = pacHeroi > (10 * fila_tamanho(heroisFila));
        }

        if (espera) {
                e = cria_evento(m->timer, ESPERA, h, b);
                if (e == NULL)
                        MEM_ALLOC_ERR("ERRO: evento ESPERA nao alocado\n");

                insere_lef(m->lista_eventos, e);
                printf("%6d: CHEGA HEROI %2d BASE %2d (%2d/%2d) ESPERA\n",
                       m->timer, h, b, qntdHeroisBase, maxHeroisBase);
        } else {
                e = cria_evento(m->timer, DESISTE, h, b);
                if (e == NULL)
                        MEM_ALLOC_ERR("ERRO: evento DESISTE nao alocado\n");

                insere_lef(m->lista_eventos, e);
                printf("%6d: CHEGA HEROI %2d BASE %2d (%2d/%2d) DESISTE\n",
                       m->timer, h, b, qntdHeroisBase, maxHeroisBase);
        }
}

void evento_espera(int h, int b, struct Mundo *m)
{
        int tamFila;
        struct evento_t *e;

        tamFila = fila_tamanho(m->bases[b].fHerois);
        printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
               m->timer, h, b, tamFila);

        enqueue(m->bases[b].fHerois, h);
        e = cria_evento(m->timer, AVISA, b, 0);
        if (e == NULL)
                MEM_ALLOC_ERR("erro ao criar evento espera\n");
        insere_lef(m->lista_eventos, e);
}

void evento_desiste(int h, int b, struct Mundo *m)
{
        struct evento_t *e;
        int nova_base;

        nova_base = rBetween(0, N_BASES - 1);
        e = cria_evento(m->timer, VIAJA, h, nova_base);
        if (e == NULL)
                MEM_ALLOC_ERR("erro ao criar evento VIAJA\n");
        insere_lef(m->lista_eventos, e);
        printf("%6d: DESISTE HEROI %2d BASE %d\n", m->timer, h, b);
}
void evento_avisa(int b, struct Mundo *m)
{
        int heroi, qntHeroisBase, maxHerois, filaHeroisVazia;
        struct evento_t *e;

        filaHeroisVazia = fila_vazia(m->bases[b].fHerois);
        qntHeroisBase = cardinalidade_cjt(m->bases[b].hPresentes);
        maxHerois = m->bases[b].nHerois; 

        printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ",
               m->timer, b, qntHeroisBase, maxHerois);
        fila_imprime(m->bases[b].fHerois);
        printf("\n");

        while (qntHeroisBase < maxHerois && !filaHeroisVazia)
        {
                dequeue(m->bases[b].fHerois, &heroi);
                insere_cjt(m->bases[b].hPresentes, heroi);
        
                e = cria_evento(m->timer, ENTRA, heroi, b);
                if (e == NULL)
                        MEM_ALLOC_ERR("erro ao criar evento ENTRA\n");

                insere_lef(m->lista_eventos, e);
                printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n",
                       m->timer, b, heroi);

                filaHeroisVazia = fila_vazia(m->bases[b].fHerois);
                qntHeroisBase = cardinalidade_cjt(m->bases[b].hPresentes);
        }
}

void evento_entra(int h, int b, struct Mundo *m)
{
        int tempo_perm, qntHeroisBase, maxHerois, tmpTot;
        struct evento_t *e;

        qntHeroisBase = cardinalidade_cjt(m->bases[b].hPresentes);
        maxHerois = m->bases[b].nHerois;
        tempo_perm = 15 + m->herois[h].paciencia * rBetween(1, 20);
        tmpTot = m->timer + tempo_perm;

        e = cria_evento(m->timer + tempo_perm, SAI, h, b);
        if (e == NULL)
                MEM_ALLOC_ERR("erro ao alocar evento SAI\n");

        insere_lef(m->lista_eventos, e);
        printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
               m->timer, h, b, qntHeroisBase, maxHerois, tmpTot);
}

void evento_sai(int h, int b, struct Mundo *m)
{
        int qntHeroisBase, maxHerois, nova_base;
        struct evento_t *e;

        qntHeroisBase = cardinalidade_cjt(m->bases[b].hPresentes);
        maxHerois = m->bases[b].nHerois;
        printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
               m->timer, h, b, qntHeroisBase, maxHerois);

        retira_cjt(m->bases[b].hPresentes, h);
        nova_base = rBetween(0, N_BASES - 1);

        e = cria_evento(m->timer, VIAJA, h, nova_base);
        insere_lef(m->lista_eventos, e);

        e = cria_evento(m->timer, AVISA, b, 0);
        insere_lef(m->lista_eventos, e);
}

static int distCartesiana(int x1, int y1, int x2, int y2)
{
        int deltax, deltay;
        deltax = x1 - x2;
        deltay = y1 - y2;
        return (int)sqrt(deltax * deltax + deltay * deltay);
}

void evento_viaja(int h, int d, struct Mundo *m)
{
        int dist, duracao, baseAtual, atualx, atualy, destx, desty; 
        int velHeroi, tmpChegada;
        struct evento_t *e;

        baseAtual = m->herois[h].base; 
        atualx = m->bases[baseAtual].pos_x;
        atualy = m->bases[baseAtual].pos_y;
        destx = m->bases[d].pos_x;
        desty = m->bases[d].pos_y;
        velHeroi = m->herois[h].vel;

        dist = distCartesiana(atualx, atualy, destx, desty);
        duracao = dist / velHeroi;

        e = cria_evento(m->timer + duracao, CHEGA, h, d);
        insere_lef(m->lista_eventos, e);

        tmpChegada = m->timer + duracao;
        printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
               m->timer, h, baseAtual, d, dist, velHeroi, tmpChegada);
}

static struct conjunto *uniaoHabilidades(struct Mundo *m, int idBase)
{
        struct conjunto *uniao, *uniao_anterior, *heroisBase;
        int heroi;

        heroisBase = m->bases[idBase].hPresentes;

        inicia_iterador_cjt(heroisBase);
        incrementa_iterador_cjt(heroisBase, &heroi);

        uniao_anterior = NULL;
        uniao = copia_cjt(m->herois[heroi].hab);
        while (incrementa_iterador_cjt(heroisBase, &heroi)) {
                uniao_anterior = uniao;
                uniao = uniao_cjt(uniao, m->herois[heroi].hab);
                uniao_anterior = destroi_cjt(uniao_anterior);
        }
        return uniao;
}

static int calc_bmp(int id_m, struct Mundo *m)
{
        int dist[N_BASES];
        struct conjunto *uniao, *mHab;
        int i, j, Mposx, Mposy, Bposx, Bposy;
        int minDist, minIndex;

        mHab = m->missoes[id_m].hab_requeridas;
        Mposx = m->missoes[id_m].pos_x;
        Mposy = m->missoes[id_m].pos_y;

        /* Calcula a distancia de cada base para a missao */
        for (i = 0; i < N_BASES; i++) {
                Bposx = m->bases[i].pos_x;
                Bposy = m->bases[i].pos_y;
                dist[i] = distCartesiana(Mposx, Mposy, Bposx, Bposy);
        }

        j = 0;
        while (j < N_BASES) {
                minDist = INT_MAX;
                minIndex = -1;
                /* Encontra a base mais proxima */
                for (i = 0; i < N_BASES; i++) {
                        if (dist[i] >= 0 && dist[i] < minDist) {
                                minDist = dist[i];
                                minIndex = i;
                        }
                }

                if (vazio_cjt(m->bases[minIndex].hPresentes)) {
                        dist[minIndex] = -1;
                } else {
                        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS ",
                                        m->timer, id_m, minIndex, minDist);
                        imprime_cjt(m->bases[minIndex].hPresentes);

                        uniao = uniaoHabilidades(m, minIndex);
                        printf("%6d: MISSAO %d HAB BASE %d: ", m->timer,
                                        id_m, minIndex);
                        imprime_cjt(uniao);

                        if (contido_cjt(mHab, uniao)) {
                                uniao = destroi_cjt(uniao);
                                return minIndex;
                        }
                        uniao = destroi_cjt(uniao);
                        
                        /* Caso a uniao das habilidades dos herois nao seja
                        *  suficiente, nao precisamos mais procurar pela 
                        *  base
                        */
                        dist[minIndex] = -1;
                }
                j++;
        }
        /* retorna -1 se nenhuma base atende os requisitos da missao */
        return -1;
}

void evento_missao(int mi, struct Mundo *m)
{
        struct evento_t *e;
        struct conjunto *heroisBase;
        int bmp, heroi;

        printf("%6d: MISSAO %d HAB REQ: ", m->timer, mi);
        imprime_cjt(m->missoes[mi].hab_requeridas);

        bmp = calc_bmp(mi, m);
        if (bmp == -1) {
                e = cria_evento(m->timer + 24 * 60, MISSAO, mi, 0);
                if (e == NULL)
                        MEM_ALLOC_ERR("ERRO: evento MISSAO nao alocado\n");
                insere_lef(m->lista_eventos, e);

                m->missoes[mi].tentativa++;
                printf("%6d: MISSAO %d IMPOSSIVEL\n", m->timer, mi);
        } else {
                heroisBase = m->bases[bmp].hPresentes;

                inicia_iterador_cjt(heroisBase);
                while(incrementa_iterador_cjt(heroisBase, &heroi))
                        m->herois[heroi].exp++;

                m->missoes[mi].cumprida = 1;
                printf("%6d: MISSAO %d CUMPRIDA BASE %d\n",
                                m->timer, mi, bmp);
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

        for (i = 0; i < (*m)->nBases; i++) {
                destroi_cjt((*m)->bases[i].hPresentes);
                fila_destroi(&(*m)->bases[i].fHerois);
        }

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
               (*m)->nMissoes,
               ((double)missoes_cumpridas / (*m)->nMissoes * 100));

        printf("TENTATIVA/MISSAO: MIN %d, MAX %d, MEDIA %.2f\n",
               min_tent, max_tent, (double)tentativas / (*m)->nMissoes);
}

void termina_simulacao(struct Mundo **m)
{
        (*m)->lista_eventos = destroi_lef((*m)->lista_eventos);
        free(*m);
        *m = NULL;
}
