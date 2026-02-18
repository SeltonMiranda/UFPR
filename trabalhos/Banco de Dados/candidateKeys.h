#ifndef __CANDIDATE_KEYS__
#define __CANDIDATE_KEYS__

#include "FD.h"

/**
 * @brief Calcula as chaves candidatas de uma relação e a lista de dependencias funcionais.
 *
 * @param list Lista de dependencias funcionais.
 * @param keys_count A quantidade de chaves candidatas.
 * @return Array de chaves candidatas.
 */
attributes* candidateKeys(FDList* list, int* keys_count);

/**
 * @brief Imprime as chaves candidatas no terminal.
 *
 * @param ckeys Array de chaves candidatas.
 * @param keys_count Quantidade de chaves candidatas.
 */
void print_candidate_keys(attributes* cKeys, int keys_count);

#endif // __CANDIDATE_KEYS__