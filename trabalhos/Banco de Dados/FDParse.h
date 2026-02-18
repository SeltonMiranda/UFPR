#ifndef __FD_PARSE__
#define __FD_PARSE__

#include "FD.h"

/**
 * @brief Esta função realiza o parsing de um arquivo '.fds'.
 *
 * @param path Caminho do arquivo.
 * @param list Ponteiro para uma lista de dependencias funcionais.
 */
void parse(char* path, FDList* list);

/**
 * @brief Esta função converte uma string de atributos para
 * uma estrutura de dados conjunto de atributos.
 *
 * @param str_attr Uma string de atributos.
 * @param set Conjunto de atributos.
 */
void strToAttr(char* str_attr, attributes set);

/**
 * @brief Esta função converte um Conjunto de atributos para uma string.
 *
 * @param set Conjunto de atributos.
 * @return A string do conjunto de atributos.
 */
char* attrToStr(attributes set);

/**
 * @brief Esta função imprime na linha de comando a lista dependencias funcionais.
 *
 * @param list A lista de dependencias funcionais.
 */
void print_fds(FDList* list);

// Funções para depuração
void print_debug(FDList* list);
void print_attr_debug(attributes attr);

#endif // __FD_PARSE__