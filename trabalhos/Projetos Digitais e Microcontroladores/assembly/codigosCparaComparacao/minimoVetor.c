#include <stdio.h>

int min(int a, int b) 
{
        if (a < b)
                return a;
        return b;
}


int minVet(int vet[], int n)
{
        if (n == 1) 
                return vet[0];
        return min(vet[n-1], minVet(vet, n - 1));
}

int main()
{
        int vet[5] = {2, 3, 4, 5, 6};
        int min = minVet(vet, 5);
        printf("minimo: %d\n", min);
        return 0;
}
