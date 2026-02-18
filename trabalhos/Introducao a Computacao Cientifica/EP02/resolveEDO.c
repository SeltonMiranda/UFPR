/**
 * Nome: Selton Miranda Rolim
 * GRR: 20235688
 */

#include <stdio.h>  // printf
#include <fenv.h>   // fesetround
#include <stdlib.h> // calloc, free
#include <likwid.h>

#include "edo.h"

int main(void)
{
  fesetround(FE_DOWNWARD);
  LIKWID_MARKER_INIT;

  EDo edo;
  Tridiag *sl;
  real_t *Y, normaL2;
  rtime_t tempo;
  int it, id;
  
  edo = lerEDO();
  Y = (real_t *)calloc(edo.n, sizeof(real_t));

  sl = genTridiag(&edo);
  id = 1;
  while (tentarLerCoeficientes(&edo)) {
    ajustarCoeficientes(&edo, sl);

    tempo = timestamp();

    LIKWID_MARKER_START(markerName("Gauss-Seidel_", id));
    // normaL2 = gaussSeidel_EDO(&edo, Y, &it);
    normaL2 = gaussSeidel_3Diag(sl, Y, &it);
    LIKWID_MARKER_STOP(markerName("Gauss-Seidel_", id));

    tempo = timestamp() - tempo;

    prnEDOsl(&edo); 
    printf("\n");
    prnVetor(Y, edo.n);
    printf("%d\n", it);
    printf("%.15e\n", normaL2);
    printf(FORMAT"\n", tempo);
    zeraVetor(Y, edo.n);
    id++;
  }

  liberaTridiag(&sl);
  liberaVetor(&Y);

  LIKWID_MARKER_CLOSE;
  return 0;
}
