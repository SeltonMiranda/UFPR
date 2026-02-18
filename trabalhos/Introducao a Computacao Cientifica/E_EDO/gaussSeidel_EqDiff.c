#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "edo.h"
#include "gaussSeidel_EqDiff.h"

// Gera diagonais e termos independentes a partir da definição do EDO
Tridiag *genTridiag (EDo *edo)
{
  Tridiag *sl;
  real_t x;
  int n = edo->n;
  
  sl = (Tridiag *) malloc (sizeof(Tridiag));
  sl->n = edo->n;

  sl->D = (real_t *) calloc(n, sizeof(real_t));
  sl->Di = (real_t *) calloc(n, sizeof(real_t));
  sl->Ds = (real_t *) calloc(n, sizeof(real_t));
  sl->B = (real_t *) calloc(n, sizeof(real_t));

  real_t h = (edo->b - edo->a)/(n+1);

  for (int i=0; i < n; ++i) {
    x = edo->a + (i+1)*h;
    sl->B[i] = h*h * edo->r(x);
    sl->Di[i] = 1 - h * edo->p(x)/2.0;
    sl->D[i] = -2 + h*h * edo->q(x);
    sl->Ds[i] = 1 + h * edo->p(x)/2.0;
  }

  sl->B[0] -= edo->ya * (1 - h*edo->p(edo->a+h)/2.0);
  sl->B[n-1] -= edo->yb * (1 + h*edo->p(edo->b-h)/2.0);
  
  return sl;
}


rtime_t gaussSeidel_3Diag(Tridiag *sl, real_t *Y, unsigned int maxiter)
{
  int n = sl->n; 
  int it = 0;
  real_t *b, *a, *c, *d;
  a = sl->Di; 
  b = sl->B;
  c = sl->Ds;
  d = sl->D;

  // algoritmo  Gauss-Seidel   com  vetores   das  diagonais   e  termos
  // independentes do SL
  rtime_t tTotal = timestamp();
  while (it < maxiter) {
    Y[0] = (b[0] - c[0] * Y[1]) / d[0];

    for (int i = 1; i < n - 1; i++) {
      Y[i] = (b[i] - a[i-1] * Y[i-1] - c[i] * Y[i+1]) / d[i];
    }

    Y[n-1] = (b[n-1] - a[n-2] * Y[n-2]) / d[n-1];
    it++;
  }

  return timestamp() - tTotal;
}

// Normal2 para tridiagonal, sem precisar alocar um vetor r
//if i == 0
//res = sl->b[i] - sl[ds] * y[i+1]
//else if i == n -1
//res = sl->b[] - sl->d[] * y[i-1]
//else
//res = sl->b[] - sl->d[] * y[i-1] - sl->ds[i] * y[i+1];

real_t normaL2_3Diag (Tridiag *sl, real_t *Y)
{
  int n = sl->n;
  real_t normaL2;
  real_t *r;

  normaL2 = 0.0;
  r = calloc(n, sizeof(real_t));
  if (r == NULL) {
    printf("Erro! Não foi possível alocar memória para o resíduo\n");
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    // Começa com b
    r[i] = sl->B[i];

    // Termo da diagonal principal
    r[i] -= sl->D[i] * Y[i];

    // Termo da diagonal inferior
    if (i > 0) {
      r[i] -= sl->Di[i - 1] * Y[i - 1];
    }

    // Termo da diagonal superior
    if (i < n - 1) {
      r[i] -= sl->Ds[i] * Y[i + 1];
    }
  }

  for (int i = 0; i < n; i++) {
    normaL2 += r[i] * r[i];
  }

  free(r);
  return sqrt(normaL2);
}


rtime_t gaussSeidel_EDO (EDo *edoeq, real_t *Y, unsigned int maxiter)
{
  int n = edoeq->n;
  // real_t xi, bi, d, di, ds;
  real_t h;

  rtime_t tTotal = timestamp();

  
  h = (edoeq->b - edoeq->a) / (n+1);

  // for (int k=0; k < maxiter; ++k) {

  //   // algoritmo Gauss-Seidel usando parâmetros EDO, sem usar vetores para
  //   // diagonais e termos independentes do SL
  //   for (int i = 0; i < n; i++) {
  //     xi = edoeq->a + (i + 1) * h; 
  //     bi = h * h + edoeq->r(xi);
  //     di = 1 - h * edoeq->p(xi) / 2.0;
  //     d  = - 2 + h * h * edoeq->q(xi);
  //     ds = 1 + h * edoeq->p(xi) / 2.0;

  //     if (i == 0) {
  //       bi -= ds * Y[i + 1] + edoeq->ya * (1 - h * edoeq->p(edoeq->a + h) / 2.0);
  //     } else if (i == n - 1) {
  //       bi -= di * Y[i - 1] + edoeq->yb * (1 + h * edoeq->p(edoeq->b - h) / 2.0);
  //     } else {
  //       bi -= ds * Y[i + 1] + di * Y[i-1];
  //     }

  //     Y[i] = bi / d;
  //   }
  // }

  for (unsigned int k = 0; k < maxiter; k++) {
    for (int i = 0; i < n; i++) {
      real_t x = edoeq->a + (i+1)*h;

      // coeficientes
      real_t p_esq = edoeq->p(x - h/2.0);
      real_t p_dir = edoeq->p(x + h/2.0);

      real_t a = -p_esq / (h*h);
      real_t c = -p_dir / (h*h);
      real_t d = (p_esq + p_dir) / (h*h) + edoeq->q(x);
      real_t b = edoeq->r(x);

      // correção pelos contornos
      if (i == 0) {
          b -= a * edoeq->ya;
      } else {
          b -= a * Y[i-1];
      }

      if (i == n-1) {
          b -= c * edoeq->yb;
      } else {
          b -= c * Y[i+1];
      }

      // atualização Gauss-Seidel
      Y[i] = b / d;
    }
  }

  return timestamp() - tTotal;
}

real_t normaL2_EDO (EDo *edoeq, real_t *Y)
{
  int n = edoeq->n;
  real_t normaL2, h;

  normaL2 = 0.0;
  h = (edoeq->b-edoeq->a)/(n+1);

  for (int i = 0; i < n; i++) {
    real_t x = edoeq->a + (i+1)*h;

    // coeficientes
    real_t p_esq = edoeq->p(x - h/2.0);
    real_t p_dir = edoeq->p(x + h/2.0);

    real_t a = -p_esq / (h*h);
    real_t c = -p_dir / (h*h);
    real_t d = (p_esq + p_dir) / (h*h) + edoeq->q(x);

    // lado direito
    real_t b = edoeq->r(x);

    // resíduo r_i = b - (a*y_{i-1} + d*y_i + c*y_{i+1})
    real_t res = b - d * Y[i];
    if (i > 0)
        res -= a * Y[i-1];
    else
        res -= a * edoeq->ya;   // condição de contorno em a

    if (i < n-1)
        res -= c * Y[i+1];
    else
        res -= c * edoeq->yb;   // condição de contorno em b

    normaL2 += res*res;
  }

  return sqrt(normaL2);
}

// Exibe um vetor na saída padrão
void prnVetor (real_t *v, unsigned int n)
{
  int i;

  //  printf ("\n");
  printf ("   ");
  for(i=0; i < n; ++i)
      printf ("%20.12e", v[i]);
  printf ("\n");

}

void prnTriDiagonal(Tridiag *sl)
{
    prnVetor(sl->Di,sl->n);
    prnVetor(sl->D,sl->n);
    prnVetor(sl->Ds,sl->n);
    prnVetor(sl->B,sl->n);
}


// Exibe SL na saída padrão
void prnEDOsl (EDo *edoeq, int diagOnly)
{
  int n = edoeq->n, i, j;
  real_t x, b, d, di, ds;
  real_t h = (edoeq->b - edoeq->a)/(n+1);

  printf ("\tn = %d, \t H = %.8g\nSL:\n", n, h);
  if (diagOnly) {
    prnTriDiagonal(genTridiag(edoeq));
  }
  else {
    for (i=0; i < n; ++i) {
      x = edoeq->a + (i+1)*h;
      b = h*h * edoeq->r(x);      
      di = 1 - h * edoeq->p(x)/2.0;
      d = -2 + h*h * edoeq->q(x);
      ds = 1 + h * edoeq->p(x)/2.0;
      
      for (j=0; j < n; ++j) {
	if (i == j)
	  printf ("%20.12e",d);
	else if (j == i-1 && i)
	  printf ("%20.12e",di);
	else if (j == i+1 && i != n-1)
	  printf ("%20.12e",ds);
	else
	  printf("%20.12e", 0.0);
      }
      
      if (i == 0)
	      b -= edoeq->ya * (1 - h*edoeq->p(edoeq->a+h)/2.0);
      else if (i == n-1)
	      b -= edoeq->yb * (1 + h*edoeq->p(edoeq->b-h)/2.0);
      printf (" | %20.12e\n", b);
    }
  }
}


