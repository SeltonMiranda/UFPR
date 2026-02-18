#include <stdio.h>
 
int primo(int n) {
    int i;
   
    for (i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
 
    return 1;
}
 
int main() {
    int num1 = 2, num2 = 100, i, r;
 
    printf("Primos entre %d and %d: ", num1, num2);
    for (i = num1; i < num2; ++i) {
        r = primo(i);
        if (r == 1) {          
            printf("%d ", i);
        }
    }
 
    return 0;
}
