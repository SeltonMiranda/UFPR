#include "auxFunctions.h"
#include "ordenacao.h"

void troca(int vetor[], size_t a, size_t b)
{
        int aux = vetor[a];
        vetor[a] = vetor[b];
        vetor[b] = aux; 
}

size_t minimo(int vetor[], size_t inicio,
                size_t fim, uint64_t *numComp)
{
        size_t min = inicio;
        for (size_t i = inicio + 1; i <= fim; i++) {
                if (vetor[i] < vetor[min]) {
                        min = i;
                }
                (*numComp)++; 
        }
        return min;
}

void copia(int vetor[], size_t inicio, size_t fim, int vetor2[])
{
        for (size_t i = inicio; i <= fim; i++)
                vetor[i] = vetor2[i - inicio];
}

void merge(int vetor[], size_t inicio, size_t meio, 
                size_t fim, uint64_t *numComp)
{
        if (inicio >= fim)
                return;
        size_t tamVetor= fim - inicio + 1;
        int *vetorAux = malloc(tamVetor * sizeof(int));
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

ssize_t bbAux(int vetor[], ssize_t inicio,
                ssize_t fim, int valor, uint64_t *numComp)
{
        if (inicio > fim)
                return inicio - 1;
        ssize_t meio = (inicio + fim)/ 2;
        (*numComp)++;
        if (valor < vetor[meio])
                return bbAux(vetor, inicio, meio - 1, valor, numComp);
        return bbAux(vetor, meio + 1, fim, valor, numComp);
}

ssize_t buscaSequencialAux(int vetor[], size_t inicio, size_t fim,
                int valor, uint64_t *numComp)
{
        if (inicio > fim)
                return -1;
        (*numComp)++;
        if (valor == vetor[inicio])
                return inicio;
        return buscaSequencialAux(vetor, inicio + 1, fim, valor, numComp);
}

static ssize_t buscaInsertion(int vetor[], size_t inicio,
                size_t fim, int valor,
                uint64_t *numComp)
{
        for (size_t i = fim; i >= inicio; i--) {
                (*numComp)++;
                if (valor >= vetor[i])
                        return i;
        }
        return -1;
}

void insere(int vetor[], size_t inicio, size_t fim, uint64_t *numComp)
{
        ssize_t i, idx;
        idx = buscaInsertion(vetor, inicio, fim - 1, vetor[fim], numComp);
        i = fim;
        while (i > idx + 1) {
                troca(vetor, i, i-1);
                i--;
        }
}

void insertionAux(int vetor[], size_t inicio,
                size_t fim, uint64_t *numComp)
{
        if (inicio >= fim)
                return;
        insertionAux(vetor, inicio, fim - 1, numComp);
        insere(vetor, inicio, fim, numComp);
}

void selectionSortAux(int vetor[], size_t inicio,
                size_t fim, uint64_t *numComp)
{
        if (inicio >= fim) 
                return;
        troca(vetor, inicio, minimo(vetor, inicio, fim, numComp));
        return selectionSortAux(vetor, inicio + 1, fim, numComp);
}



void mergeSortAux(int vetor[], size_t inicio, size_t fim, uint64_t *numComp)
{
        if (inicio >= fim)
                return;
        uint64_t meio = (inicio + fim) / 2;
        mergeSortAux(vetor, inicio, meio, numComp);
        mergeSortAux(vetor, meio + 1, fim, numComp);
        merge(vetor, inicio, meio, fim, numComp);
}
