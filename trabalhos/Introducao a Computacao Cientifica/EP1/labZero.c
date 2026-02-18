#include <stdio.h>
#include <math.h>
#include <float.h>

#include "utils.h"
#include "ZeroFuncao.h"
#include <fenv.h>

int main ()
{
  fesetround(FE_DOWNWARD);

  real_t lower, upper, raiz, erro;
  Polinomio pol;
  double tempo;
  int it;

  readPolynomial(&pol); 
  scanf("%lf %lf", &lower, &upper); // intervalo onde está uma das raizes.

  it = 0;
  printf("RAPIDO\n\n");
  for (int i = 0; i < 3; i++) {

    tempo = timestamp();
    erro  = bisseccao(pol, lower, upper, i, CALCULO_RAPIDO, &it, &raiz);
    tempo = timestamp() - tempo;

    printf("bissec  %+.15e %.15e %3d  %.8e\n", raiz, erro, it, tempo);
  }

  for (int i = 0; i < 3; i++) {

    tempo = timestamp();
    erro  = newtonRaphson(pol, (lower + upper) / 2, i, CALCULO_RAPIDO, &it, &raiz);
    tempo = timestamp() - tempo;

    printf("newton  %+.15e %.15e %3d  %.8e\n", raiz, erro, it, tempo);
  }
  printf("\n");

  printf("LENTO\n\n");
  for (int i = 0; i < 3; i++) {

    tempo = timestamp();
    erro  = bisseccao(pol, lower, upper, i, CALCULO_LENTO, &it, &raiz);
    tempo = timestamp() - tempo;

    printf("bissec  %+.15e %.15e %3d  %.8e\n", raiz, erro, it, tempo);
  }

  for (int i = 0; i < 3; i++) {

    tempo = timestamp();
    erro  = newtonRaphson(pol, (lower + upper) / 2, i, CALCULO_LENTO, &it, &raiz);
    tempo = timestamp() - tempo;

    printf("newton  %+.15e %.15e %3d  %.8e\n", raiz, erro, it, tempo);
  }
  return 0;
}

