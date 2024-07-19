#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

void liberaVetor(struct racional **v, int n)
{
        int i;
        for (i = 0; i < n; i++)
                destroi_r(&v[i]);
}

struct racional *somaVetor(struct racional **v, int n)
{
        struct racional *soma, *resultado;
        int i;
        soma = cria_r(0, 1);
        for (i = 0; i < n; i++) {
                resultado = soma_r(soma, v[i]);
                if (!resultado) {
                        destroi_r(&soma);
                        return NULL;
                }
                destroi_r(&soma);
                soma = resultado;
        }
        return soma;
}

void troca(struct racional **v, int a, int b)
{
        struct racional *aux;
        aux = v[a];
        v[a] = v[b];
        v[b] = aux;
}

int achaMenor(struct racional **v, int i, int n)
{
        int j, menor;
        menor = i;
        for (j = i+1; j < n; j++)
                if (compara_r(v[j], v[menor]) == -1)
                        menor = j;
        return menor;
}

void ordenaVetor(struct racional **v, int n)
{
        int i, menor;
        for (i = 0; i < n-1; i++) {
                menor = achaMenor(v, i, n);
                troca(v, i, menor);
        }
}

void retiraInvalidos(struct racional **v, int *n)
{
        int i, tam;
        tam = *n;
        for (i = 0; i < tam; i++) {
                if (!valido_r(v[i])) {
                        destroi_r(&v[i]);
                        v[i] = v[tam - 1];
                        tam--;
                        i--;
                }
        }
        *n = tam;
}

void imprimeVetor(struct racional **v, int n)
{
        int i;
        for (i = 0; i < n; i++) {
                imprime_r(v[i]);
                printf(" ");
        }
}

int lerVetor(struct racional **v, int n)
{
        long int num, den;
        int i;
        for (i = 0; i < n; i++) {
                scanf("%ld %ld", &num, &den);
                v[i] = cria_r(num, den);
                if (!v[i]) {
                        liberaVetor(v, i-1);
                        return 0;
                }
        }
        return 1;
}

struct racional **alocaVetor(int n)
{
        struct racional **v;
        v = malloc(n*sizeof(struct racional *));
        if (!v)
                return NULL;
        return v;
}

int main ()
{
        struct racional **v; 
        struct racional *soma;
        int n;
        
        scanf("%d", &n);
        v = alocaVetor(n);
        if (v == NULL) {
                fprintf(stderr, "ERRO: Nao conseguiu alocar memoria\n");
                return 1;
        }

        if (!lerVetor(v, n)) {
                fprintf(stderr, "ERRO: Nao conseguiu alocar memoria\n");
                return 1;
        }
        imprimeVetor(v, n);
        printf("\n");

        retiraInvalidos(v, &n);
        imprimeVetor(v, n);
        printf("\n");

        retiraInvalidos(v, &n);
        ordenaVetor(v, n);
        imprimeVetor(v, n);
        printf("\n");

        soma = somaVetor(v, n);
        if (!soma) {
                fprintf(stderr, "MEMORIA NAO ALOCADA PARA SOMA");
                return 1;
        }
        printf("a soma de todos os elementos eh: ");
        imprime_r(soma);
        destroi_r(&soma);

        liberaVetor(v, n);
        free(v);
        v = NULL;
        printf("\n");
        return 0;
}
