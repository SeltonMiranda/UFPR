#include <stdlib.h>

#include "lef.h"
#include "mundo.h"


int main (){
        srand (0);
        struct Mundo *mundo;
        struct evento_t *atual;

        mundo = inicializa_mundo();
        init_eventos(mundo);
        
        while (mundo->tempo_inicial != mundo->tempo_fim)
        {
                atual = retira_lef(mundo->lista_eventos);
                mundo->tempo_inicial = atual->tempo;        

                switch (atual->tipo) {
                        case CHEGA:
                        processa_evento_chega(atual->dado1, atual->dado2, mundo);
                        break;

                        case ESPERA:
                        processa_evento_espera(atual->dado1, atual->dado2, mundo);
                        break;

                        case AVISA:
                        processa_evento_avisa(atual->dado1, mundo);
                        break;
                                
                        case ENTRA:
                        processa_evento_entra(atual->dado1, atual->dado2, mundo); 
                        break;

                        case SAI:
                        processa_evento_sai(atual->dado1, atual->dado2, mundo); 
                        break;

                        case VIAJA:
                        processa_evento_viaja(atual->dado1, atual->dado2, mundo);
                        break;

                        case DESISTE:
                        processa_evento_desiste(atual->dado1, atual->dado2, mundo);
                        break;

                        case MISSAO:
                        processa_evento_missao(atual->dado1, mundo);
                        break;

                        case FIM:
                        processa_evento_fim(&mundo);
                        break;

                }
                atual = destroi_evento(atual);

        }
        termina_simulacao(&mundo);
        return 0;
}
