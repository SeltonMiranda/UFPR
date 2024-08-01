#include <stdio.h>
 
int soma_rec(int n) {
    if (n <= 1)
        return n;
   
    return n + soma_rec(n - 1);
}
 
int main() {
    int n = 100;
    printf("Soma de 1 ate %d = %d ", n, soma_rec(n));
    return 0;
}
