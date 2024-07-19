
// Personal Includes
#include "auxFunc.h"
#include "pilha.h"

// System Includes
#include <stdlib.h>
#include <stdio.h>

// ----------- Funcoes auxiliares ----------- 
static void trocar(int *a, int *b)
{
        int aux = *a;
        *a = *b;
        *b = aux;
}

static void copia(int vetor[], size_t inicio, size_t fim, int vetor2[])
{
        for (size_t i = inicio; i <= fim; i++)
                vetor[i] = vetor2[i - inicio];
}

static void merge(int vetor[], size_t inicio, size_t meio, 
                  size_t fim, uint64_t *numComp)
{
        if (inicio >= fim)
                return;

        size_t tamVetor= fim - inicio + 1;
        int *vetorAux = (int *)malloc(tamVetor * sizeof(int));
        if (!vetorAux) {
                fprintf(stderr, "ERROR: MEMORY ALLOCATION FAILED!");
                exit(EXIT_FAILURE);
        }

        size_t esq, dir, chave, k;
        esq = inicio;
        dir = meio + 1;
        k = 0;
        while (k <= fim - inicio) {
                (*numComp)++;
                if (dir > fim || (esq <= meio && vetor[esq] <= vetor[dir])) {
                        chave = esq;
                        esq++;
                } else {
                        chave = dir;
                        dir++;
                }
                vetorAux[k] = vetor[chave];
                k++;
        }
        copia(vetor, inicio, fim, vetorAux);
        free(vetorAux);
}

static ssize_t particionar(int vetor[], ssize_t inicio,
                           ssize_t fim, uint64_t *numComp)
{
        int pivo = vetor[fim];
        size_t retPos = inicio;

        for (ssize_t i = inicio; i < fim; i++) {
                (*numComp)++;
                if (vetor[i] <= pivo) {
                        trocar(&vetor[retPos], &vetor[i]);
                        retPos++;
                }
        }
        trocar(&vetor[retPos], &vetor[fim]);
        return retPos;
}

static void maxHeapify(int vetor[], size_t i, size_t tam, uint64_t *numComp)
{
        size_t esq, dir, maior;
        esq = (i << 1) + 1;
        dir = (i << 1) + 2;

        (*numComp)++;
        if (esq < tam && vetor[esq] > vetor[i]) 
                maior = esq;
        else
                maior = i;

        (*numComp)++;
        if (dir < tam && vetor[dir] > vetor[maior])
                maior = dir;

        if (maior != i) {
                trocar(&vetor[i], &vetor[maior]);
                maxHeapify(vetor, maior, tam, numComp);
        }
}

static void buildMaxHeap(int vetor[], size_t tam, uint64_t *numComp)
{
        for (size_t i = (tam / 2); i > 0; i--) 
                maxHeapify(vetor, i - 1, tam, numComp);
}

static void maxHeapifyIterative(int vetor[], size_t i, size_t tam, uint64_t *numComp)
{
        size_t esq, dir, maior;

        while (1) {
                esq = (i << 1) + 1;
                dir = (i << 1) + 2;


                (*numComp)++;
                if (esq < tam && vetor[esq] > vetor[i]) 
                        maior = esq;
                else
                        maior = i;

                (*numComp)++;
                if (dir < tam && vetor[dir] > vetor[maior])
                        maior = dir;

                if (i != maior) {
                        trocar(&vetor[i], &vetor[maior]);
                        i = maior;
                } else {
                        break;
                }
                 
        }
}

static void buildMaxHeapIterative(int vetor[], size_t tam, uint64_t *numComp)
{
        for (size_t i = (tam / 2); i > 0; i--) 
                maxHeapifyIterative(vetor, i - 1, tam, numComp);
}

// ----------- Merge Sort Recursivo ----------- 
void mergeSortAux(int vetor[], size_t inicio, size_t fim, uint64_t *numComp)
{
        if (inicio >= fim)
                return;
        uint64_t meio = inicio + (fim - inicio) / 2;
        mergeSortAux(vetor, inicio, meio, numComp);
        mergeSortAux(vetor, meio + 1, fim, numComp);
        merge(vetor, inicio, meio, fim, numComp);
}

// ----------- Merge Sort iterativo ----------- 
void mergeSortSR_aux(int vetor[], ssize_t inicio, ssize_t fim, uint64_t *numComp)
{
        Pilha *pilha = inicializaPilha(fim - inicio + 1);
        if (!pilha) {
                fprintf(stderr, "ERRO: Pilha nao inicializada\n");
                exit(EXIT_FAILURE);
        }

        Pilha *mergePilha = inicializaPilha(fim - inicio + 1);
        if (!mergePilha) {
                fprintf(stderr, "ERRO: Pilha nao inicializada\n");
                exit(EXIT_FAILURE);
        }

        push(pilha, inicio);
        push(pilha, fim);

        while (!pilhaVazia(pilha)) {
                ssize_t idx_esq, idx_dir;
                pop(pilha, &idx_dir);
                pop(pilha, &idx_esq);

                if (idx_esq < idx_dir) {
                        ssize_t idx_meio = idx_esq + (idx_dir - idx_esq) / 2;

                        push(pilha, idx_esq);
                        push(pilha, idx_meio);
                        push(pilha, idx_meio + 1);
                        push(pilha, idx_dir);

                        push(mergePilha, idx_esq);
                        push(mergePilha, idx_dir);
                }
        }

        while (!pilhaVazia(mergePilha)) {
                ssize_t idx_esq, idx_dir, idx_meio;

                pop(mergePilha, &idx_dir);
                pop(mergePilha, &idx_esq);
                idx_meio = idx_esq + (idx_dir - idx_esq) / 2;

                if (idx_esq < idx_dir) {
                        merge(vetor, idx_esq, idx_meio, idx_dir, numComp);
                }
        }

        destroiPilha(&pilha);
        destroiPilha(&mergePilha);
}

// ----------- Quick Sort Recursivo ----------- 
void quickSortAux(int vetor[], ssize_t inicio, ssize_t fim, uint64_t *numComp)
{
        if (inicio >= fim)
                return;
        ssize_t pos = particionar(vetor, inicio, fim, numComp);
        quickSortAux(vetor, inicio, pos - 1, numComp);
        quickSortAux(vetor, pos + 1, fim, numComp);
}

// ----------- Quick Sort iterativo ----------- 
void quickSortSR_aux(int vetor[], ssize_t a, ssize_t b, uint64_t *numComp)
{
        Pilha *pilha = inicializaPilha(b - a + 1);
        if (!pilha) {
                fprintf(stderr, "ERRO: Memoria nao alocada para pilha\n");
                exit(EXIT_FAILURE);
        }

        push(pilha, a);
        push(pilha, b);
        while ( !pilhaVazia(pilha) ) {
                ssize_t inicio, fim;
                pop(pilha, &fim);
                pop(pilha, &inicio);

                if (inicio < fim) {
                        ssize_t pos = particionar(vetor, inicio, fim, numComp);
                        push(pilha, inicio);
                        push(pilha, pos - 1);
                        push(pilha, pos + 1);
                        push(pilha, fim);
                }
        }
        destroiPilha(&pilha);
}

// ----------- Heap Sort Recursivo ----------- 
void heapSortAux(int vetor[], size_t tam, uint64_t *numComp)
{
        buildMaxHeap(vetor, tam, numComp);
        for (size_t i = tam - 1; i > 0; i--) {
                trocar(&vetor[0], &vetor[i]);
                maxHeapify(vetor, 0, i, numComp);
        }
}

// ----------- Heap Sort iterativo ----------- 
void heapSortSR_aux(int vetor[], size_t tam, uint64_t *numComp)
{
        buildMaxHeapIterative(vetor, tam, numComp);
        for (size_t i = tam - 1; i > 0; i--) {
                trocar(&vetor[0], &vetor[i]);
                maxHeapifyIterative(vetor, 0, i, numComp);
        }
}
