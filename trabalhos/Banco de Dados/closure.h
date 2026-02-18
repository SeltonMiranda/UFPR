#ifndef __CLOSURE__
#define __CLOSURE__

#include "FD.h"

/**
 * @brief Esta função calcula o fecho de um conjunto (in-place)
 * usando a lista de dependencias funcionais.
 *
 * @param list Lista de dependencias funcionais.
 * @param set Conjunto.
 */
void closure(FDList* list, attributes set);

#endif // __CLOSURE__
