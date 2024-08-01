#include <stdio.h>
 
int maior_array(int arr[], int n) {
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
 
int main() {
    int arr[] = { 10, 324, 45, 90, 9808 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maior: %d", maior_array(arr, n));
    return 0;
}

