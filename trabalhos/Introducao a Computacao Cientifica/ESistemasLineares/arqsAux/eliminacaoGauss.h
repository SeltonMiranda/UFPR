#ifndef __EliminacaoGauss__
#define __EliminacaoGauss__

#include "sislin.h"

void triangulariza( SistLinear_t *C );
void retrosubst( SistLinear_t *C, real_t *X );
void eliminacaoGauss(SistLinear_t *C, real_t *X);

#endif // __EliminacaoGauss__
