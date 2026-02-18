#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "gaussSeidel.h"

// Método de Gauss-Seidel clássico
int gaussSeidel (SistLinear_t *C, real_t *X, real_t erro, int maxit, real_t *norma)
{
    int it, linearSysSize;
    real_t *x_ant, x_new, sum;


    linearSysSize = C->n;
    x_ant = (real_t *)calloc(linearSysSize, sizeof(real_t));
    if (!x_ant) {
        fprintf(stderr, "ERRO! Não foi possível alocar memória linha: %d arquivo: %s\n", __LINE__, __FILE__);
        exit(1);
    }

    it = 0;
    do {

        for (int i = 0; i < linearSysSize; i++) {
            sum = 0;
            for (int j = 0; j < i; j++) {
                sum += C->A[i][j] * X[j];
            }

            for (int j = i + 1; j < linearSysSize; j++) {
                sum += C->A[i][j] * x_ant[j];
            }

            x_new  = (C->b[i] - sum) / C->A[i][i];

            x_ant[i] = X[i];
            X[i] = x_new;
        }

        it++;
        *norma = normaMax(X, x_ant, linearSysSize);
    } while (*norma > erro && it < maxit);

    free(x_ant);
    return it;
}


