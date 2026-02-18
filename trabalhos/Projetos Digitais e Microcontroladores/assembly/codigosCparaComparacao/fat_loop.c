#include <stdio.h>
 
int fat(int n) {
    int fat = 1, i;
 
    for (i = 2; i <= n; i++) {
        fat *= i;
    }
 
    return fat;
}
 
int main() {
    int n = 5;
    printf("Fatorial de %d eh %d\n", n, fat(n));
    return 0;
}
