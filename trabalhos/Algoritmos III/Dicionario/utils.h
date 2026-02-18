/**************************************
 * Esse arquivo contém funções que ajudam na implementação da Trie e do projeto.
 * Autores: Selton Miranda Rolim (GRR20235688) e Gabriel Carloto Nowak (GRR20235686).
***************************************/


#ifndef __UTILS__
#define __UTILS__

#define HASHTAG '#'
#define ZERO '0'

/**
 * Converte um caractere para o respectivo número do teclado T9.
 * @param c: Caractere de uma palavra. 
 * @return : Número no teclado T9. 
 **/
int charToDigit(char c);

/**
 * Verifica se a palavra fonte contém algum caractere presente em digitos.
 * @param digitos: Ponteiro para uma sequencia de caracteres.
 * @param fonte: Ponteiro para uma palavra. 
 * @return bool: 1 se algum caractere está presente em fonte ou 0 caso contrário.
 **/
int contains(char *digitos, char *fonte);

/**
 * Verifica se uma palavra é valida (i.e, está no formato do teclato T9).
 * @param str: Ponteiro para uma palavra. 
 * @return bool: 1 se valida ou 0 caso contrário.
 **/
int palavraValida(char *p);

#endif /*  __UTILS__  */ 