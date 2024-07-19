#include <stdlib.h>
#include <string.h>

#include "ordenacao.h"
#include "auxFunctions.h"


void getNome(char nome[]) {
        // substitua por seu nome
        strncpy(nome, "Selton Miranda Rolim", MAX_CHAR_NOME);
        nome[MAX_CHAR_NOME - 1] =
                '\0';  // adicionada terminação manual para caso de overflow
}

// a função a seguir deve retornar o seu número de GRR
uint32_t getGRR() { return 20235688; }

ssize_t buscaSequencial(int vetor[], size_t tam, int valor,
                uint64_t* numComp) 
{
        for (size_t i = 0; i < tam ; i++) {
                (*numComp)++;
                if (valor == vetor[i])
                        return i;
        }
        return -1; 
}

ssize_t buscaSequencialRec(int vetor[], size_t tam, int valor,
                uint64_t* numComp)
{
        return buscaSequencialAux(vetor, 0, tam - 1,
                        valor, numComp);
}

ssize_t buscaBinaria(int vetor[], size_t tam, int valor,
                uint64_t* numComp) 
{
        ssize_t esq, dir;
        esq = 0;
        dir= tam - 1;
        while (esq <= dir) {
                ssize_t meio = (esq + dir) / 2;

                (*numComp)++;
                if (vetor[meio] < valor)
                        esq = meio + 1;
                else
                        dir = meio - 1;
        }

        (*numComp)++;
        if (vetor[dir + 1] == valor)
                return dir + 1;

        return -1;
}

ssize_t buscaBinariaRec(int vetor[], size_t tam, int valor,
                uint64_t* numComp) 
{
        ssize_t idx = bbAux(vetor, 0, tam - 1, valor, numComp); 
        (*numComp)++;
        if (idx == -1 || vetor[idx] != valor)
                return -1;
        return idx;
}

uint64_t insertionSort(int vetor[], size_t tam)
{
        uint64_t numComp = 0;
        int i, key, j;
        for (i = 1; i < tam; i++) {
                key = vetor[i];
                j = i - 1;
                numComp++;
                while (j >= 0 && vetor[j] > key) {
                        numComp++;
                        vetor[j + 1] = vetor[j];
                        j = j - 1;
                }
                vetor[j + 1] = key;
        }
        return numComp;
}

uint64_t insertionSortRec(int vetor[], size_t tam)
{
        uint64_t numComp = 0;
        insertionAux(vetor, 0, tam - 1, &numComp);
        return numComp; 
}

uint64_t selectionSort(int vetor[], size_t tam)
{
        uint64_t numComp = 0;
        for (size_t i = 0; i < tam - 1; i++) {
                size_t menor_idx = i;
                for (size_t j = i + 1; j < tam ; j++) {
                        if (vetor[j] < vetor[menor_idx])
                                menor_idx = j;
                        numComp++;
                }
                troca(vetor, i, menor_idx);
        }
        return numComp;
}

uint64_t selectionSortRec(int vetor[], size_t tam)
{
        uint64_t numComp = 0;
        selectionSortAux(vetor, 0, tam-1, &numComp);
        return numComp;
}

uint64_t mergeSortRec(int vetor[], size_t tam)
{
        uint64_t numComp = 0;
        mergeSortAux(vetor, 0, tam-1, &numComp);
        return numComp;
}
