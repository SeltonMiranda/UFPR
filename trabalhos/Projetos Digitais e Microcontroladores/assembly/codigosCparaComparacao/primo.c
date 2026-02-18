#include <stdio.h>

int primo(int x) 
{
        int i;
        for (i = 2; i < x / 2; i++) {
                if (x % i == 0)
                        return 0;
        }
        
        return 1;
}

int soma_primos(int a, int b)
{
        int s = 0;
        int i;
        i = a;
        while (i <= b) {
                s = s + primo(i);
                i++;
        }
        
        return s;
}

int main()
{
        int x = 2; int y = 1000;
        int s = soma_primos(x, y);
        return 0;
}
