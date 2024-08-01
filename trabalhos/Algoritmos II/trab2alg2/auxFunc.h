#ifndef AUXFUNC_H
#define AUXFUNC_H

#include <sys/types.h>
#include <stdint.h>

void mergeSortAux(int vetor[], size_t inicio, size_t fim, uint64_t *numComp);
void quickSortAux(int vetor[], ssize_t inicio, ssize_t fim, uint64_t *numComp);
void heapSortAux(int vetor[], size_t tam, uint64_t *numComp);
void quickSortSR_aux(int vetor[], ssize_t a, ssize_t b, uint64_t *numComp);
void mergeSortSR_aux(int vetor[], ssize_t inicio, ssize_t fim, uint64_t *numComp);
void heapSortSR_aux(int vetor[], size_t tam, uint64_t *numComp);

#endif // AUXFUNC_H
