#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#include "ordenacao.h"

void imprimeVetor(int v[], ssize_t tam)
{
        for (size_t i = 0; i < tam; i++) {
                printf("%d ", v[i]);
        }
        printf("\n");
}

void preencheVetor2(int v[], int tam)
{
        for (size_t i = 0; i < tam; i++) {
                v[i] = i;
        }
}

void preencheVetor(int v[], int tam)
{
        for (size_t i = 0; i < tam; i++) {
                v[i] = rand() % tam + 1;
        }
}

int main() {

        srand(time(NULL));
        char nome[MAX_CHAR_NOME];
        size_t idxBusca;
        uint64_t numComp_idx;
        uint64_t numComp;

        ssize_t tamVetor = 100000;
        int* vetor = malloc(tamVetor * sizeof(int));
        if (vetor == NULL) {
                printf("Falha fatal. Impossível alocar memoria.");
                return EXIT_FAILURE;
        }

        getNome(nome);
        printf("Trabalho de %s\n", nome);
        printf("GRR %u\n", getGRR());
        printf("\n");

        preencheVetor(vetor, tamVetor);
        clock_t start, end;  
        double total;

        printf("Vetor Desordenado\n");
        start = clock();  
        numComp = mergeSortRec(vetor, tamVetor);
        end = clock();  
        total = ((double)end - start) / CLOCKS_PER_SEC;
        printf("Numero de comparacoes do MergeSort: %lu\n", numComp);
        printf("Tempo total: %f\n", total);
        printf("\n");

        preencheVetor(vetor, tamVetor);
        printf("Vetor Desordenado\n");
        start = clock();  
        numComp = insertionSort(vetor, tamVetor);
        end = clock();  
        total = ((double)end - start) / CLOCKS_PER_SEC;
        printf("Numero de comparacoes do InsertionSort: %lu\n", numComp);
        printf("Tempo total: %f\n", total);
        printf("\n");

        tamVetor = 1000000;
        vetor = realloc(vetor, sizeof(int)*tamVetor);
        if (vetor == NULL) {
                fprintf(stderr, "MEMORY ALLOCATION FAILED!");
                return EXIT_FAILURE;
        }

        preencheVetor2(vetor, tamVetor);
        printf("Vetor Ordenado\n");
        start = clock();  
        numComp = mergeSortRec(vetor, tamVetor);
        end = clock();  
        total = ((double)end - start) / CLOCKS_PER_SEC;
        printf("Numero de comparacoes do MergeSort: %lu\n", numComp);
        printf("Tempo total: %f\n", total);
        printf("\n");


        preencheVetor2(vetor, tamVetor);
        printf("Vetor Ordenado\n");
        start = clock();  
        numComp = insertionSort(vetor, tamVetor);
        end = clock();  
        total = ((double)end - start) / CLOCKS_PER_SEC;
        printf("Numero de comparacoes do InsertionSort: %lu\n", numComp);
        printf("Tempo total: %f\n", total);
        printf("\n");

        preencheVetor(vetor, tamVetor);
        int number = rand() % tamVetor + 1;
        numComp_idx = 0;
        start = clock();
        idxBusca = buscaSequencial(vetor, tamVetor, number, &numComp_idx);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("Tempo total buscaSequencial: %f\n", total);
        printf("Numero de comparacoes: %lu, indice de %d: %zd\n",
                        numComp_idx, number, idxBusca);
        printf("\n");
        
        number = rand() % tamVetor + 1;
        numComp_idx = 0;
        start = clock();
        idxBusca = buscaBinaria(vetor, tamVetor, number, &numComp_idx);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("Tempo total buscaBinaria: %f\n", total);
        printf("Numero de comparacoes: %lu, indice de %d: %zd\n",
                        numComp_idx, number, idxBusca);

        free(vetor);
        return EXIT_SUCCESS;
}
