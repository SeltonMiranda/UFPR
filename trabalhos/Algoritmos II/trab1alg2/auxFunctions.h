#ifndef __AUXFUNC__
#define __AUXFUNC__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

void troca(int vetor[], size_t a, size_t b);

void copia(int vetor[], size_t inicio, size_t fim, int vetor2[]);

void insert(int vetor[], size_t inicio, size_t fim, uint64_t *numComp);

size_t Minimo(int vetor[], size_t inicio,
                size_t fim, uint64_t *numComp);

void merge(int vetor[], size_t inicio, size_t meio, 
                size_t fim, uint64_t *numComp);

ssize_t bbAux(int vetor[], ssize_t inicio,
                ssize_t fim, int value, uint64_t *numComp);

ssize_t buscaSequencialAux(int vetor[], size_t inicio, size_t fim,
                int value, uint64_t *numComp);

void insertionAux(int vetor[], size_t inicio,
                size_t fim, uint64_t *numComp);

void selectionSortAux(int vetor[], size_t inicio,
                size_t fim, uint64_t *numComp);

void mergeSortAux(int vetor[], size_t inicio,
                size_t fim, uint64_t *numComp);

#endif
