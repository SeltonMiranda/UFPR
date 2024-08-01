#include <stdio.h>
 
int vogal(char c){
    if (c == 'a' || c == 'A' || c == 'e' || c == 'E'
        || c == 'i' || c == 'I' || c == 'o' || c == 'O'
        || c == 'u' || c == 'U') {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    char ch;
    for( ch = 'A'; ch <= 'Z'; ch++)
        printf("%c - %d\n", ch, vogal(ch));
 
    return 0;
}
