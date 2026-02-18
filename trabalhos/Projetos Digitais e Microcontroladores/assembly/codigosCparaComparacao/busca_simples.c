#include <stdio.h>

int buscaSimplesRec(int vetor[], int a, int b, int x)
{
        if (a > b)
                return 0;
        
        if (vetor[b] == x)
                return 1;

        return buscaSimplesRec(vetor, a, b - 1, x);
}


int main()
{
        int vetor[5] = {1, 2, 3, 4, 5};
        int achou = buscaSimplesRec(vetor, 0, 4, 3);
        return 0;
}
