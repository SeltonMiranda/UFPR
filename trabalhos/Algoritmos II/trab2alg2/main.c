// System include
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Personal include
#include "ordenacao.h"
#include "teste.h"

int main() {
        srand(time(NULL));
        char nome[MAX_CHAR];

        size_t tamVetor = 5000;
        int* vetor = (int*)malloc(tamVetor * sizeof(int));
        if (vetor == NULL) {
                printf("Falha fatal. Impossível alocar memoria.");
                return 1;
        }
        
        getNome(nome);
        printf("Trabalho de %s\n", nome);
        printf("GRR %u\n", getGRR());

        testa_ambos_quick_sort(vetor, tamVetor);
        printf("\n\n");
        testa_ambos_merge_sort(vetor, tamVetor);
        printf("\n\n");
        testa_ambos_heap_sort(vetor, tamVetor);

        free(vetor);
        return 0;
}
