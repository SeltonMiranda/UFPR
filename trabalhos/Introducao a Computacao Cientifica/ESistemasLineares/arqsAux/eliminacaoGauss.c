/* Matriz  'normal' (vetor  de  ponteiros (linhas  matriz) para  vetores
   (colunas da matriz), estilo 'Mazieiro/Prog 2'
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "eliminacaoGauss.h"

/*
 * Encontra o valor máximo na linha e coluna K
 */
// n -> tamanho do SL
static int encontraMax(SistLinear_t *C, int k)
{
  int maior = ABS(C->A[k][k]);
  int linha = k;
  int linearSysSize = C->n;

  for (int i = 1; i < linearSysSize; i++) {
    if (ABS(C->A[i][k]) > maior) {
      maior = C->A[i][k];
      linha = i;
    }
  }

  return linha;
}

/*
 * Troca a linha k com a linha P
 */
// trocar linha k com linha p
static void trocaLinha (SistLinear_t *C, int k, int p)
{
  real_t temp;
  int linearSysSize = C->n;
  for (int i = 0; i < linearSysSize; i++) {
    temp = C->A[k][i];
    C->A[k][i] = C->A[p][i];
    C->A[p][i] = temp;
  }
  temp = C->b[k];
  C->b[k] = C->b[p];
  C->b[p] = temp;
}

/* Seja um S.L. de ordem 'n'
   C = A|B em Ax=B
 */
void triangulariza( SistLinear_t *C )
{
  int linearSysSize = C->n;
  real_t m;

  for (int i = 0; i < linearSysSize; i++) {
    int pivo = encontraMax(C, i);
    if (i != pivo)
      trocaLinha(C, i, pivo);

    for (int k = i + 1; k < linearSysSize; k++) {
      m = C->A[k][i] / C->A[i][i];
      C->A[k][i] = 0.0;

      for (int j = i + 1; j < linearSysSize; j++) {
        C->A[k][j] -= C->A[i][j] * m;
      }

      C->b[k] -= C->b[i] * m;
    }
  }
}

void retrosubst( SistLinear_t *C, real_t *X )
{
  int linearSysSize = C->n;
  for (int i = linearSysSize - 1; i >= 0; i--) {
    X[i] = C->b[i];

    for (int j = i + 1; j < linearSysSize; j++) {
      X[i] -= C->A[i][j] * X[j];
    }

    X[i] /= C->A[i][i];
  }
}

void eliminacaoGauss(SistLinear_t *C, real_t *X)
{
  triangulariza(C);
  retrosubst(C, X);
}
