#include "ordenacao.h"
#include <string.h>

// Personal includes
#include "auxFunc.h"


void getNome(char nome[]) {
    strncpy(nome, "Selton Miranda Rolim", MAX_CHAR);
    nome[MAX_CHAR - 1] = '\0';
}

uint32_t getGRR() { return 20235688; }

uint64_t mergeSort(int vetor[], size_t tam) {
        uint64_t numComp = 0;
        mergeSortAux(vetor, 0, tam - 1, &numComp);
        return numComp;
}

uint64_t quickSort(int vetor[], size_t tam) {
        uint64_t numComp = 0;
        quickSortAux(vetor, 0, tam - 1, &numComp);
        return numComp;
}

uint64_t heapSort(int vetor[], size_t tam) {
        uint64_t numComp = 0;
        heapSortAux(vetor, tam, &numComp);
        return numComp;
}

uint64_t mergeSortSR(int vetor[], size_t tam) {
        uint64_t numComp = 0;
        mergeSortSR_aux(vetor, 0, tam - 1, &numComp);
        return numComp;
}

uint64_t quickSortSR(int vetor[], size_t tam) {
        uint64_t numComp = 0; 
        quickSortSR_aux(vetor, 0, tam - 1, &numComp);
        return numComp;
}

uint64_t heapSortSR(int vetor[], size_t tam) {
        uint64_t numComp = 0;
        heapSortSR_aux(vetor, tam, &numComp);
        return numComp;
}
