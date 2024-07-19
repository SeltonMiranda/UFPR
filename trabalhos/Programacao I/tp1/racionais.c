#include <stdio.h>
#include <stdlib.h>

#include "racionais.h"

int aleat(int min, int max)
{
	return rand () % (max - min + 1) + min;
}

int mdc(int a, int b)
{
        if (b == 0)
                return a;
	return mdc(b, a % b);
}

int mmc(int a, int b)
{
        return (a*b) / mdc(a, b);
}

int valido_r(struct racional r)
{
	return r.valido; 
}

struct racional cria_r(int numerador, int denominador)
{
        struct racional r;

        r.num = numerador;
        r.den = denominador;
        r.valido = r.den == 0 ? 0 : 1;

        return simplifica_r(r);
}

struct racional sorteia_r(int n)
{
        int numerador, denominador;
        numerador = aleat(0, n);
        denominador = aleat(0, n);

        return cria_r(numerador, denominador);
}

struct racional simplifica_r(struct racional r)
{
	r.num /= mdc(abs(r.num), abs(r.den));
	r.den /= mdc(abs(r.num), abs(r.den));

        if (r.den < 0) {
                r.num *= -1;
                r.den *= -1;
        }

	return r; 
}

struct racional soma_r(struct racional r1, struct racional r2)
{
        int numerador, denominador;
        numerador = (r2.den*r1.num) + (r1.den*r2.num);
	denominador = r1.den*r2.den;

        return cria_r(numerador, denominador);
}

struct racional subtrai_r(struct racional r1, struct racional r2)
{
        int numerador, denominador;
        numerador = (r2.den*r1.num) - (r1.den*r2.num);
	denominador = r1.den*r2.den;

        return cria_r(numerador, denominador);
}

struct racional divide_r(struct racional r1, struct racional r2)
{
        return cria_r(r1.num*r2.den, r1.den*r2.num);
}

struct racional multiplica_r(struct racional r1, struct racional r2)
{
        return cria_r(r1.num*r2.num, r1.den*r2.den);
}

void imprime_r(struct racional r)
{
        if ( !valido_r(r) ) {
                printf("INVALIDO");
                return;
        } 
        
        r = simplifica_r(r);

        if (r.num == 0)
                printf("0");
        else if (r.num == r.den)
                printf("1");
        else if (r.den == 1)
                printf("%d", r.num);
        else
                printf("%d/%d", r.num, r.den);
}
