#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

/* coloque demais includes aqui */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (long int min, long int max)
{
        return rand() % (max - min + 1) - min;
}

/* Maximo Divisor Comum entre a e b.         */
/* Calcula o mdc pelo metodo de Euclides.    */
/* Dica: a versao recursiva eh bem elegante! */
long int mdc (long int a, long int b)
{
        if (b == 0)
                return a;
        return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long int mmc (long int a, long int b)
{
        return (a * b) / mdc (a, b);        
}

/* Recebe um numero racional e o retorna simplificado no parametro *r.
   Quem chama esta funcao deve garantir que *r seja valido e nao NULL. */
void simplifica_r (struct racional *r)
{
        long int maxDiv;
        maxDiv = mdc(r->num, r->den);
        r->num /= maxDiv;
        r->den /= maxDiv;

        if (r->den < 0) {
                r->num *= -1;
                r->den *= -1;
        }
}

int eh_igual(struct racional *r)
{
        return r->num == r->den ? 1 : 0;
}

struct racional *cria_r(long int numerador, long int denominador)
{
        struct racional *r;
        r = malloc(sizeof(struct racional));
        if (r == NULL)
                return NULL;
        r->num = numerador;
        r->den = denominador;
        simplifica_r(r);
        return r;
}

struct racional *sorteia_r(long int max) 
{
        struct racional *r;
        long int numerador, denominador;
        numerador = aleat(-max, max);
        denominador = aleat(-max, max);
        r = cria_r(numerador, denominador);
        return r;
}

void destroi_r(struct racional **r)
{
        free(*r);
        *r = NULL;
}

long int numerador_r(struct racional *r)
{
        return r->num;
}

long int denominador_r(struct racional *r)
{
        return r->den;
}

int valido_r(struct racional *r)
{
        return r->den == 0 ? 0 : 1;
}

struct racional *soma_r(struct racional *r1, struct racional *r2)
{
        struct racional *soma;
        soma = malloc(sizeof(struct racional));
        if (soma == NULL)
                return NULL;
        soma->num = r1->num * r2->den + r1->den * r2->num; 
        soma->den = r1->den * r2->den;
        simplifica_r(soma);
        return soma;
}

struct racional *subtrai_r(struct racional *r1, struct racional *r2)
{
        struct racional *sub;
        sub = malloc(sizeof(struct racional));
        if (sub == NULL)
                return NULL;
        sub->num = r1->num * r2->den - r1->den * r2->num; 
        sub->den = r1->den * r2->den;
        simplifica_r(sub);
        return sub;

}

struct racional *multiplica_r(struct racional *r1, struct racional *r2)
{
        struct racional *mult;
        mult = malloc(sizeof(struct racional));
        if (mult == NULL)
                return NULL;
        mult->num = r1->num * r2->num;
        mult->den = r1->den * r2->den;
        simplifica_r(mult);
        return mult;
}

struct racional *divide_r(struct racional *r1, struct racional *r2)
{
        struct racional *div;
        div = malloc(sizeof(struct racional));
        if (div == NULL)
                return NULL;

        div->num = r1->num * r2->den;
        div->den = r1->den * r2->num;
        if (!valido_r(div))
                return NULL;

        simplifica_r(div);
        return div;
}

int compara_r(struct racional *r1, struct racional *r2)
{
        if (r1->num * r2->den < r1->den * r2->num)
                return -1;
        if (r1->num * r2->den > r1->den * r2->num)
                return 1;
        return 0;
}

void imprime_r(struct racional *r)
{
        if (!valido_r(r)) {
                printf("INVALIDO");
                return;
        }

        simplifica_r(r);
        if (r->num == 0)
                printf("0");
        else if (r->den == 1)
                printf("%ld", r->num);
        else if (eh_igual(r))
                printf("1");
        else
                printf("%ld/%ld", r->num, r->den);
}
