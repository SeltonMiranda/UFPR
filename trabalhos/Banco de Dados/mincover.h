#ifndef __MINCOVER__
#define __MINCOVER__

#include "FD.h"

/**
 * @brief Calcula a cobertura miníma a partir da lista de dependencias funcionais.
 *
 * @param list Lista de dependencias funcionais.
 */
void mincover(FDList* list);

#endif // __MINCOVER__