#ifndef __ZEROFUNCAO_H__
#define __ZEROFUNCAO_H__

#include <float.h>

typedef double real_t;

// Aproximação aceitável como valor zero
#define ZERO DBL_EPSILON

// Parâmetros para teste de convergência
#define MAXIT 600
#define EPS 1.0e-7
#define ULPS 3

typedef struct {
  real_t *p;
  int grau;
} Polinomio;

typedef enum {
  RELATIVO = 0,
  EPSILON,
  ULP,
} criterioParada;

typedef enum {
  CALCULO_RAPIDO = 0,
  CALCULO_LENTO,
} tipoCalculo;

typedef void (*calcFunc)(Polinomio, real_t, real_t*, real_t*);

// Métodos
// Retornam valor do erro quando método finalizou. Este valor depende de tipoErro
real_t newtonRaphson (Polinomio p, real_t x0, criterioParada cp, tipoCalculo tipo, int *it, real_t *raiz);
real_t bisseccao (Polinomio p, real_t a, real_t b, criterioParada cp, tipoCalculo tipo, int *it, real_t *raiz);

// Cálculo de Polinômios
void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx );
void calcPolinomio_lento(Polinomio p, real_t x, real_t *px, real_t *dpx );

// Lê um polinômio
void readPolynomial(Polinomio *pol);

#endif // __ZEROFUNCAO_H__

