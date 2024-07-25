/* Personal Includes */
#include "lef.h"
#include "mundo.h"

/* System Includes */
#include <stdlib.h>

int main()
{
        srand (0);
        struct Mundo *mundo;
        struct evento_t *ev;

        mundo = initMundo();
        initEventos(mundo);
        while (getTimer(mundo) != T_FIM_DO_MUNDO) {
                ev = retira_lef(getListaDeEventos(mundo));
                setTimer(mundo, ev->tempo);
                switch (ev->tipo) {
                        case CHEGA:
                        evento_chega(ev->dado1, ev->dado2, mundo);
                        break;

                        case ESPERA:
                        evento_espera(ev->dado1, ev->dado2, mundo);
                        break;

                        case AVISA:
                        evento_avisa(ev->dado1, mundo);
                        break;
                                
                        case ENTRA:
                        evento_entra(ev->dado1, ev->dado2, mundo); 
                        break;

                        case SAI:
                        evento_sai(ev->dado1, ev->dado2, mundo); 
                        break;

                        case VIAJA:
                        evento_viaja(ev->dado1, ev->dado2, mundo);
                        break;

                        case DESISTE:
                        evento_desiste(ev->dado1, ev->dado2, mundo);
                        break;

                        case MISSAO:
                        evento_missao(ev->dado1, mundo);
                        break;

                        case FIM:
                        evento_fim(&mundo);
                        break;
                }
                ev = destroi_evento(ev);
        }
        termina_simulacao(&mundo);
        return 0;
}
