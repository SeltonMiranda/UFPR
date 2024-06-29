#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

int aleat (int min, int max)
{
        return rand() % (max - min + 1) + min;
}

int mdc (int a, int b)
{
        if (b == 0)
                return a;
        return mdc(b, a % b);
}

int mmc (int a, int b)
{
        return (a * b) / mdc(a, b);
}

void simplifica_r (struct racional *r)
{
        int maxDivisor = mdc(abs(r->num), abs(r->den));

        r->num /= maxDivisor;
        r->den /= maxDivisor;

        if (r->den < 0) {
                r->num *= -1;
                r->den *= -1;
        }
}

struct racional cria_r(int numerador, int denominador)
{
        struct racional r;
        r.num = numerador;
        r.den = numerador;
        r.valido = r.den != 0;
        simplifica_r(&r);

        return r;
}

struct racional sorteia_r(int n)
{
        struct racional r;
        r.num = aleat(-n, n);
        r.den = aleat(-n, n);
        r.valido = r.den != 0;
        simplifica_r(&r);

        return r;
}

int numerador_r(struct racional r)
{
        return r.num;
}

int denominador_r(struct racional r)
{
        return r.den;
}

int valido_r(struct racional r)
{
        return r.valido;
}

void soma_r(struct racional r1, struct racional r2, struct racional *r3)
{
        r3->num = r1.num * r2.den + r2.num * r1.den;
        r3->den = r1.den * r2.den;
        r3->valido = 1;
        simplifica_r(r3);
}


void subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{
        r3->num = r1.num * r2.den - r2.num * r1.den;
        r3->den = r1.den * r2.den;
        r3->valido = 1;
        simplifica_r(r3);
}


void multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{
        r3->num = r1.num * r2.num;
        r3->den = r1.den * r2.den;
        r3->valido = 1;
}

int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{
        r3->num = r1.num * r2.den;
        r3->den = r1.den * r2.num;
        r3->valido = r3->den != 0;
        return r3->valido;
}

int compara_r(struct racional r1, struct racional r2)
{
        if (r1.num * r2.den < r2.num * r1.den) 
                return -1;
        if (r1.num * r2.den > r2.num * r1.den) 
                return 1;
        return 0;
}

void imprime_r(struct racional r)
{
        if ( !valido_r(r) ) {
                printf("INVALIDO");
                return;
        }

        simplifica_r(&r);
        if (r.num == 0)
                printf("0");
        else if (r.num == r.den)
                printf("1");
        else if (r.den == 1)
                printf("%d", r.num);
        else
                printf("%d/%d", r.num, r.den);
}

