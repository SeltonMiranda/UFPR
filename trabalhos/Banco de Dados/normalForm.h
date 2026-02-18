#ifndef __NORMAL_FORM__
#define __NORMAL_FORM__

#include "FD.h"

/**
 * @brief Verifica se uma lista de dependencias funcionais
 * está violando a terceira forma normal ou BCNF.
 *
 * @param list Lista de dependencias funcionais.
 */
void normalform(FDList* list);

#endif // __NORMAL_FORM__