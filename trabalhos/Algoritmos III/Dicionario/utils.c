#include "utils.h"

#include <ctype.h>
#include <string.h>
#include <stdio.h>

int charToDigit(char c)
{
    switch (c) {
        case 'a':
        case 'b':
        case 'c':
            return 2;
        case 'd':
        case 'e':
        case 'f':
            return 3;
        case 'g':
        case 'h':
        case 'i':
            return 4;
        case 'j':
        case 'k':
        case 'l':
            return 5;
        case 'm':
        case 'n':
        case 'o':
            return 6;
        case 'p':
        case 'q':
        case 'r':
        case 's':
            return 7;
        case 't':
        case 'u':
        case 'v':
            return 8;
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return 9; 
        default:
             /* Isso eh inutil, uma vez que o caractere 
              * sempre estara no intervalo [a-z], mas
              * o compilador acusa erro se nao tiver.
              */
            return -1;
    }
}

int contains(char *digitos, char *fonte)
{
    for (size_t i = 0; i < strlen(digitos); i++) {
        if (strchr(fonte, digitos[i]))
            return 1;
    }
    return 0;
}

int palavraValida(char *p) {
    if (contains("?!,./:;@$&*%^()-_+=|[]{}\"\'\abcdefghijklmnopqrstuvwxyz01ABCDEFGHIJKLMNOPQRSTUVWXYZ ", p)) 
        return 0;
    if ( p[0] == HASHTAG && contains("23456789", p) )
        return 0;
    return 1;
}
