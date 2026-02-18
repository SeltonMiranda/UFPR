#include <stdio.h> 
  
int par(int n) 
{ 
    int r = n % 2; 
    if (r == 0)  
        return 1;
    return 0;
  
} 
  
int main()  { 
    int r, n = 10; 
    r = par(n);
    if(r)
        printf("par\n");
    else
        printf("impar\n");
  
    return 0; 
}

