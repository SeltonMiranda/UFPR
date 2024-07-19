#include <stdio.h>
#include <stdlib.h>

#include "racionais.h"

int main()
{
        srand(10);
        struct racional r1, r2, soma, subt, mult, div;
        int n, max;

        scanf("%d %d", &n, &max);
        for (int i = 1; i <= n; i++) {
                r1 = sorteia_r(max);
                r2 = sorteia_r(max);

                printf("%d: ", i);
                imprime_r(r1);
		printf(" ");
                imprime_r(r2);
		printf(" ");

                if ( !valido_r(r1) || !valido_r(r2) ) {
                        printf("NUMERO INVALIDO\n");
                        return 1;
                }

                soma = soma_r(r1, r2);
                subt = subtrai_r(r1, r2);
                mult = multiplica_r(r1, r2);
                div = divide_r(r1, r2);
                
                if ( !valido_r(div) ) {
                         printf("DIVISAO INVALIDA\n");
                         return 1;
                 }

                imprime_r(soma);
		printf(" ");
                imprime_r(subt);
		printf(" ");
                imprime_r(mult);
		printf(" ");
                imprime_r(div);
		printf(" ");
                printf("\n");
        }
        return 0;
}
