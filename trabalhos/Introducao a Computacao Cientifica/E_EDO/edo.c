#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "edo.h"
#include "gaussSeidel_EqDiff.h"

#define MAXIT 50
#define len(array) (sizeof(array)/sizeof(array[0]))

real_t pp (real_t x);
real_t qq (real_t x);
real_t rr (real_t x);

int main ()
{
  int malha[] = {5, 10, 100, 1000};

  for (int i = 0; i < len(malha); i++ ) {
    int pontos = malha[i];
    EDo edo = {pontos, 0, 1, -1, 0, pp, qq, rr}; // definição da EDO do exercício
    Tridiag *sist;
    real_t *Y; // Resultado da EDO.
    rtime_t tempo;
    real_t normaL2;

    Y = (real_t *)calloc(edo.n, sizeof(real_t));
    if (Y == NULL) {
      printf("Erro! Não foi possível alocar memória para o vetor solução\n");
      exit(1);
    }
    printf("\n \t Pontos na malhamalha [ %d ] \n", pontos);

    printf("\n\n ==========  Tridiagonal  ==========\n\n");
    sist = genTridiag(&edo);
    tempo = gaussSeidel_3Diag(sist, Y, MAXIT);
    normaL2 = normaL2_3Diag(sist, Y);
    // prnTriDiagonal(sist);
    printf("\n");
    prnVetor(Y, sist->n);
	  printf("NORMA_L2: %20.12e\n", normaL2);
	  printf("TEMPO: %20.12e\n", tempo);

    printf("\n\n ==========  EDO  ==========\n\n");

    for (int i = 0; i < edo.n; i++) {
      Y[i] = 0;
    }

    tempo = gaussSeidel_EDO(&edo, Y, MAXIT);
    normaL2 = normaL2_EDO(&edo, Y);
    // prnEDOsl(&edo, 0);
    printf("\n");
    prnVetor(Y, sist->n);
	  printf("NORMA_L2: %20.12e\n", normaL2);
	  printf("TEMPO: %20.12e\n", tempo);
    printf("\n");

    free(sist->B);
    free(sist->D);
    free(sist->Ds);
    free(sist->Di);
    free(sist);
    free(Y);
  }
  return 0;
}

real_t pp (real_t x)
{
  return x+1;
}

real_t qq (real_t x)
{
  return -2*x;
}

real_t rr (real_t x)
{
  // Escolher apenas um dos retornos abaixo. Qual o melhor?
  return (1-x*x)*exp(-x);
  // return (1+x)*(1-x)*exp(-x);
}


