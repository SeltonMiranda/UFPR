#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "racionais.h"

int main()
{
        srand(0);
        struct racional r1, r2, soma, subt, mult, div;
        int n, max, i;

        scanf("%d %d", &n, &max);
        for (i = 1; i <= n; i++) {
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

                soma_r(r1, r2, &soma);
                subtrai_r(r1, r2, &subt);
                multiplica_r(r1, r2, &mult);
                
                if ( !divide_r(r1, r2, &div) ) {
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
                printf("\n");
        }
        return 0;
}
