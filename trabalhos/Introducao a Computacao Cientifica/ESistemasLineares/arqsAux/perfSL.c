#include <stdio.h>
#include <likwid.h>
#include <fenv.h>

#include "utils.h"
#include "sislin.h"
#include "eliminacaoGauss.h"
#include "gaussSeidel.h"


void run_eliminacaoGauss(SistLinear_t *s) {
    real_t *X;
    real_t *r;

    r = (real_t *)calloc(s->n, sizeof(real_t));
    X = (real_t *)calloc(s->n, sizeof(real_t));

    rtime_t _time = timestamp(); 
    eliminacaoGauss(s, X);
    _time = timestamp() - _time;
    residuo(s, X, r, s->n); 

    printf("EG:\n");
    printf("%.12e ms\n", _time);
    prnVetor(X, s->n);
    prnVetor(r, s->n);

    free(X);
    free(r);
}

void run_gaussSeidel(SistLinear_t *s) {
    real_t *X, *r;
    real_t norma;
    int it;

    r = (real_t *)calloc(s->n, sizeof(real_t));
    X = (real_t *)calloc(s->n, sizeof(real_t));

    rtime_t _time = timestamp(); 
    it = gaussSeidel(s, X, TOL, MAXIT, &norma);
    _time = timestamp() - _time;
    residuo(s, X, r, s->n); 

    printf("GS [%d iteracoes]:\n", it);
    printf("%.12e ms\n", _time);
    prnVetor(X, s->n);
    prnVetor(r, s->n);

    free(X);
    free(r);
    return;
}

int main(void) {
    fesetround(FE_DOWNWARD);
    SistLinear_t *s1, *s2;

    s1 = lerSisLin();
    s2 = dupSisLin(s1);
    run_eliminacaoGauss(s1);
    printf("\n");
    run_gaussSeidel(s2);
    liberaSisLin(s1);
    liberaSisLin(s2);

    return 0;
}
