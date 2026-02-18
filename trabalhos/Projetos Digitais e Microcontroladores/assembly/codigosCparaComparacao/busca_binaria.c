#include <stdio.h>
 
int busca_binaria(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
 
        if (arr[mid] > x) {
            return busca_binaria(arr, l, mid - 1, x);
        }
 
        return busca_binaria(arr, mid + 1, r, x);
    }
    return -1;
}
 
int main(void) {
    int arr[] = { 2, 3, 5, 7, 9 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int x = 9;
    int index = busca_binaria(arr, 0, size - 1, x);
 
    if (index == -1) {
        printf("Nao encontrado");
    }
    else {
        printf("elemento esta no indice %d", index);
    }
 
    return 0;
}
