// Personal include
#include "teste.h"
#include "ordenacao.h"

// System include
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

static void preenche_vetor_aleat(int vetor[], size_t tam)
{
        for (size_t i = 0; i < tam; i++) {
                vetor[i] = rand() % ULONG_MAX;
        }
}

static void preenche_vetor_inv_ord(int vetor[], size_t tam)
{
        for (size_t i = tam - 1; i > 0; i--)
                vetor[i] = i;
        vetor[0] = 0;

}

static void preenche_vetor_ord(int vetor[], size_t tam)
{
        for (size_t i = 0; i < tam; i++) 
                vetor[i] = i;
}

void testa_ambos_merge_sort(int vetor[], size_t tam)
{

        clock_t start, end;
        double total;
        uint64_t numComp = 0;

        preenche_vetor_ord(vetor, tam);
        start = clock();
        numComp = mergeSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Ordenado\n");
        printf("-------------------- Merge Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        numComp = 0;
        preenche_vetor_ord(vetor, tam);
        start = clock();
        numComp = mergeSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Merge Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        numComp = 0;
        preenche_vetor_inv_ord(vetor, tam);
        start = clock();
        numComp = mergeSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Inversamente Ordenado\n");
        printf("-------------------- Merge Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        numComp = 0;
        preenche_vetor_inv_ord(vetor, tam);
        start = clock();
        numComp = mergeSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Merge Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        numComp = 0;
        preenche_vetor_aleat(vetor, tam);
        start = clock();
        numComp = mergeSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Aleatoriamente Desordenado\n");
        printf("-------------------- Merge Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        numComp = 0;
        preenche_vetor_aleat(vetor, tam);
        start = clock();
        numComp = mergeSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Merge Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);
}

void testa_ambos_quick_sort(int vetor[], size_t tam)
{

        clock_t start, end;
        double total;
        uint64_t numComp = 0;

        preenche_vetor_ord(vetor, tam);
        start = clock();
        numComp = quickSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Ordenado\n");
        printf("-------------------- Quick Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_ord(vetor, tam);
        start = clock();
        numComp = quickSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Quick Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_inv_ord(vetor, tam);
        start = clock();
        numComp = quickSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Inversamente Ordenado\n");
        printf("-------------------- Quick Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_inv_ord(vetor, tam);
        start = clock();
        numComp = quickSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Quick Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_aleat(vetor, tam);
        start = clock();
        numComp = quickSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Aleatoriamente Desordenado\n");
        printf("-------------------- Quick Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_aleat(vetor, tam);
        start = clock();
        numComp = quickSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Quick Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);
}

void testa_ambos_heap_sort(int vetor[], size_t tam)
{

        clock_t start, end;
        double total;
        uint64_t numComp = 0;

        preenche_vetor_ord(vetor, tam);
        start = clock();
        numComp = heapSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Ordenado\n");
        printf("-------------------- Heap Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_ord(vetor, tam);
        start = clock();
        numComp = heapSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Heap Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_inv_ord(vetor, tam);
        start = clock();
        numComp = heapSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Inversamente Ordenado\n");
        printf("-------------------- Heap Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_inv_ord(vetor, tam);
        start = clock();
        numComp = heapSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Heap Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_aleat(vetor, tam);
        start = clock();
        numComp = heapSort(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("\tPara vetor Aleatoriamente Desordenado\n");
        printf("-------------------- Heap Sort Recursivo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);

        preenche_vetor_aleat(vetor, tam);
        start = clock();
        numComp = heapSortSR(vetor, tam);
        end = clock();
        total = ((double)end - start) / CLOCKS_PER_SEC;

        printf("-------------------- Heap Sort Iterativo --------------------\n");
        printf("\tQntde de Comparacoes: %lu", numComp);
        printf("\tTempo total: %f\n\n", total);
}
