/**
 * Nome: Selton Miranda Rolim
 * GRR: 20235688
 */

#include <stdio.h>  // printf
#include <math.h>   // exp
#include <stdlib.h> // calloc, free
#include <string.h> // memset

#include "utils.h"
#include "edo.h"

Tridiag *genTridiag (EDo *edo)
{
  Tridiag *sl;
  real_t x, rx;
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
    rx = edo->r1*x + edo->r2*x*x + edo->r3*cos(x) + edo->r4*exp(x);
    
    // sl->B[i] = h*h * rx;
    sl->Di[i] = 1 - h * edo->p/2.0;
    sl->D[i] = -2 + h*h * edo->q;
    sl->Ds[i] = 1 + h * edo->p/2.0;
  }

  // sl->B[0] -= edo->ya * (1 - h*edo->p/2.0);
  // sl->B[n-1] -= edo->yb * (1 + h*edo->p/2.0);
  
  return sl;
}


// Exibe SL na saída padrão
void prnEDOsl (EDo *edoeq)
{
  int n = edoeq->n, i, j;
  real_t x, b, d, di, ds,rx;
  real_t h = (edoeq->b - edoeq->a)/(n+1);

  printf ("%d\n", n);

  for (i=0; i < n; ++i) {
    x = edoeq->a + (i+1)*h;
    rx = edoeq->r1*x + edoeq->r2*x*x + edoeq->r3*cos(x) + edoeq->r4*exp(x);
    
    b = h*h * rx; 
    di = 1 - h * edoeq->p/2.0;
    d = -2 + h*h * edoeq->q;
    ds = 1 + h * edoeq->p/2.0;
      
    for (j=0; j < n; ++j) {
      if (i == j)
	printf (FORMAT,d);
      else if (j == i-1 && i)
	printf (FORMAT,di);
      else if (j == i+1 && i != n-1)
	printf (FORMAT,ds);
      else
	printf(FORMAT, 0.0);
    }
      
    if (i == 0)
      b -= edoeq->ya * (1 - h*edoeq->p/2.0);
    else if (i == n-1)
      b -= edoeq->yb * (1 + h*edoeq->p/2.0);

    printf (FORMAT, b);
      
    printf ("\n");
  }
}

EDo lerEDO(void)
{
  EDo edo;
  scanf("%d", &edo.n);
  scanf("%lf %lf", &edo.a, &edo.b);
  scanf("%lf %lf", &edo.ya, &edo.yb);
  scanf("%lf %lf", &edo.p, &edo.q);
  return edo;
}

bool tentarLerCoeficientes(EDo *edo) 
{
  int coeficientesLidos = scanf("%lf %lf %lf %lf", &edo->r1, &edo->r2, &edo->r3, &edo->r4);
  if (coeficientesLidos != 4) 
    return false;
  return true;
}

void ajustarCoeficientes(EDo *edo, Tridiag *sl)
{
  int n;
  real_t x, rx, b, h;

  n = edo->n;
  h = (edo->b - edo->a) / (n + 1);
  for (int i = 0; i < n; ++i) 
  {
    x  = edo->a + (i + 1) * h;
    rx = edo->r1 * x + edo->r2 * x * x + edo->r3 * cos(x) + edo->r4 * exp(x);
    
    sl->B[i] = h * h * rx;
  }

  sl->B[0] -= edo->ya * (1 - h*edo->p/2.0);
  sl->B[n-1] -= edo->yb * (1 + h*edo->p/2.0);
}



void zeraVetor(real_t *v, int n)
{
  memset(v, 0, sizeof(v));
}

void prnVetor (real_t *v, unsigned int n)
{
  int i;

  //  printf ("\n");
  printf ("  ");
  for(i=0; i < n; ++i)
      printf (FORMAT, v[i]);
  printf ("\n");

}

void liberaTridiag(Tridiag **sl)
{
  free((*sl)->B);
  free((*sl)->D);
  free((*sl)->Di);
  free((*sl)->Ds);
  free((*sl));
}

void liberaVetor(real_t **v)
{
  free((*v));
}

real_t normaL2_EDO (EDo *edo, real_t *Y)
{
  int n = edo->n;
  real_t normaL2, res, x, rx, d, ds, di, b;
  real_t h = (edo->b - edo->a) / (n + 1.0);

  normaL2 = 0.0;
  d  = -2  + h*h*edo->q;
  di = 1 - 0.5*h*edo->p;
  ds = 1 + 0.5*h*edo->p;

  // Calcula o resíduo da primeira linha
  {
    x  = edo->a + h;
    rx = edo->r1 * x + edo->r2 * x * x + edo->r3 * cos(x) + edo->r4 * exp(x);
    b = h * h * rx - di * edo->ya; 

    res = b - (d * Y[0] + ds * Y[1]);
    normaL2 += res * res;
  }

  for (int i = 1; i < n - 1; i++) 
  {
    x  = edo->a + (i + 1) * h;
    rx = edo->r1 * x + edo->r2 * x * x + edo->r3 * cos(x) + edo->r4 * exp(x);
    b =  h * h * rx; 

    res = b - (di * Y[i - 1] + d * Y[i] + ds * Y[i + 1]);
    normaL2 += res * res;
  }

  // Calcula o resíduo da última linha
  {
    x  = edo->a + (n * h);
    rx = edo->r1 * x + edo->r2 * x * x + edo->r3 * cos(x) + edo->r4 * exp(x);
    b =  h * h * rx - ds * edo->yb; 

    res = b - (d * Y[n-1] + di * Y[n-2]);
    normaL2 += res * res;
  }

  return sqrt(normaL2);
}

real_t normaL2_3Diag(Tridiag *sl, real_t *Y)
{
  int n = sl->n;
  real_t normaL2 = 0.0;
  real_t res;

  /* resíduo da primeira linha */
  res = sl->B[0] - (sl->D[0] * Y[0] + sl->Ds[0] * Y[1]);
  normaL2 += res * res;

  for (int i = 1; i < n - 1; i++)
  {
    res = sl->B[i] - ((sl->Di[i-1] * Y[i-1]) + (sl->D[i] * Y[i]) + (sl->Ds[i] * Y[i+1]));
    normaL2 += res * res;
  }

  /* resíduo da última linha */
  res = sl->B[n-1] - (sl->Di[n-2] * Y[n-2] + sl->D[n-1] * Y[n-1]);
  normaL2 += res * res;

  return sqrt(normaL2);
}


real_t gaussSeidel_3Diag(Tridiag *sl, real_t *Y, int *it)
{
  int n;
  real_t normaL2;

  *it = 0;
  n = sl->n;
  normaL2 = 0.0;
  do {
    Y[0] = (sl->B[0] - sl->Ds[0] * Y[1]) / sl->D[0];

    for (int i = 1; i < n - 1; i++)
    {
      Y[i] = (sl->B[i] - sl->Di[i - 1] * Y[i - 1] - sl->Ds[i] * Y[i + 1]) / sl->D[i];
    }

    Y[n - 1] = (sl->B[n - 1] - sl->Di[n - 2] * Y[n - 2] ) / sl->D[n - 1];

    normaL2 = normaL2_3Diag(sl, Y);
    (*it)++;
  } while (normaL2 > NORMA_MAX && *it < MAXIT);

  return normaL2;
}

real_t gaussSeidel_EDO(EDo *edo, real_t *Y, int *it)
{
  int n;
  real_t h, x, rx, b, d, di, ds;
  real_t normaL2;

  n = edo->n;
  h = (edo->b - edo->a) / (n + 1);
  normaL2 = 0.0;
  *it = 0;

  d  = -2 + h*h*edo->q;
  di = 1 - 0.5*h*edo->p;
  ds = 1 + 0.5*h*edo->p;

  do {
    x = edo->a + h;
    rx = edo->r1 * x + edo->r2 * x * x + edo->r3 * cos(x) + edo->r4 * exp(x);
    b = h * h * rx - di * edo->ya - ds * Y[1]; 
    Y[0] = b / d;

    for (int i = 1; i < n - 1; i++)
    {
      x = edo->a + (i + 1) * h;
      rx = edo->r1 * x + edo->r2 * x * x + edo->r3 * cos(x) + edo->r4 * exp(x);
      b = h * h * rx - di * Y[i-1] - ds * Y[i+1]; 
      Y[i] = b / d;
    }

    x = edo->a + n * h;
    rx = edo->r1 * x + edo->r2 * x * x + edo->r3 * cos(x) + edo->r4 * exp(x);
    b = h * h * rx - ds * edo->yb - di * Y[n-2]; 
    Y[n - 1] = b / d;

    normaL2 = normaL2_EDO(edo, Y);
    (*it)++;
  } while (normaL2 > NORMA_MAX && *it < MAXIT);

  return normaL2;
}
