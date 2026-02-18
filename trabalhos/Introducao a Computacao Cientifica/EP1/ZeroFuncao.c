#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"
#include "DoubleType.h"

// Retorna true (1) se o erro for menor que o critério selecionado
// caso contrário, retorna false (0)
static int shouldStop(real_t x_new, real_t x_old, real_t fx, real_t* error, int criterioParada) {

    switch (criterioParada) {
        case RELATIVO:
        {
            if (fabs(x_new) > DBL_EPSILON)
              *error = fabs((x_new - x_old) / x_new);
            else 
              *error = fabs(x_new - x_old);

            return (*error) <= EPS;
        }
        case EPSILON:
        {
            *error = fabs(fx);
            return (*error) <= DBL_EPSILON;
        } 
        case ULP:
        {
            Double_t f1, f2;
            f1.f = x_new;
            f2.f = x_old;

            uint64_t x1 = (uint64_t)f1.i;
            uint64_t x2 = (uint64_t)f2.i;
            

            *error = (real_t)(llabs(x1 - x2)) - 1;
            if ((*error) < DBL_EPSILON) (*error) = 0;

            return (*error) <= ULPS; 
        }

        default:
            PANIC("Critério de parada inexistente");
    }

}

// Função auxiliar que é utilizada no método Newton-Raphson
// retorna em *FX o valor do polinômio no ponto x
// retorna o próximo ponto x
static real_t f_phi(real_t x, tipoCalculo tipo, Polinomio p, real_t *FX) {
    calcFunc f_pol;
    real_t fx, dfx;

    if (tipo == CALCULO_LENTO) f_pol = calcPolinomio_lento;
    else                       f_pol = calcPolinomio_rapido;

    f_pol(p, x, &fx, &dfx);

    *FX = fx;
    if (fabs(dfx) < DBL_EPSILON) return x;
   
    return x - (fx / dfx);
}

// Lê um polinômio
void readPolynomial(Polinomio *pol) {
  scanf("%d", &pol->grau);

  pol->p = (real_t *)malloc(sizeof(real_t) * (pol->grau + 1));
  if (!pol->p)
    PANIC("Não foi possível alocar memória para o polinômio");

  for (int i = pol->grau; i >= 0; --i)
    scanf("%lf", &pol->p[i]);
}

// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
// Parâmetro tipoCalculo define o tipo de calculo do polinômio que deve ser utilizado
real_t newtonRaphson(Polinomio p, real_t x0, criterioParada cp, tipoCalculo tipo, int *it, real_t *raiz)
{
    real_t x_new, x_old, fx, error;
    x_new = x0;

    (*it) = 0;
    do {

        x_old = x_new;
        x_new = f_phi(x_old, tipo, p, &fx);
        (*it)++;

    } while (!shouldStop(x_new, x_old, fx, &error, cp) && (*it) <= MAXIT);

    *raiz = x_new;
    return error;
}


// Retorna valor do erro quando método finalizou. Este valor depende de tipoErro
// Parâmetro tipoCalculo define o tipo de calculo do polinômio que deve ser utilizado
real_t bisseccao(Polinomio p, real_t a, real_t b, criterioParada cp, tipoCalculo tipo, int *it, real_t *raiz)
{
    real_t xm_old, xm_new;
    real_t fx_1, dfx_1, fx_2, dfx_2;
    real_t error;
    calcFunc f_pol;

    if (tipo == CALCULO_LENTO) f_pol = calcPolinomio_lento;
    else                       f_pol = calcPolinomio_rapido;


    xm_new = (a + b) / 2;
    f_pol(p, a, &fx_1, &dfx_1);
    f_pol(p, xm_new, &fx_2, &dfx_2);

    if (fx_1 * fx_2 < 0)      b = xm_new;
    else if (fx_1 * fx_2 > 0) a = xm_new;
    else                      *raiz = xm_new;

    (*it) = 0;
    do {

        xm_old = xm_new;
        xm_new = (a + b) / 2;

        f_pol(p, a, &fx_1, &dfx_1);
        f_pol(p, xm_new, &fx_2, &dfx_2);

        if (fx_1 * fx_2 < 0)      b = xm_new;
        else if (fx_1 * fx_2 > 0) a = xm_new;
        else                      *raiz = xm_new;
            

        (*it)++;
    } while (!shouldStop(xm_new, xm_old, fx_2, &error, cp) && (*it) <= MAXIT);

    *raiz = xm_new;
    return error;
}


void calcPolinomio_rapido(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
    real_t fx  = p.p[p.grau];
    real_t dfx = fx;

    for (int i = p.grau - 1; i > 0; i--) {
        fx  = fx  * x + p.p[i];
        dfx = dfx * x + fx;
    }
    fx = (fx * x) + p.p[0];

    *px  = fx;
    *dpx = dfx;
}


void calcPolinomio_lento(Polinomio p, real_t x, real_t *px, real_t *dpx)
{
    real_t fx  = 0.0;
    real_t dfx = 0.0;

    for (int i = p.grau; i > 0; i--) {
        fx  += p.p[i] * pow(x, i);
        dfx += p.p[i] * pow(x, i - 1) * i; 
    }
    fx += p.p[0];

    *px  = fx;
    *dpx = dfx;
}
