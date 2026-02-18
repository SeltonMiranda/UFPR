/**
 * @author: Selton Miranda Rolim
 * GRR:    20235688
 */

#include "ConjugateGradient.h"
#include "LinearSystem.h"

#ifdef LIKWID_PERFMON
#include <likwid.h>
#endif

int main()
{
  srand(20252);
  LinearSystem   ls;
  ErrorType      err;
  int            n, k, maxit, it;
  real_t         omega, epsilon, maxNorm, normL2;
  rtime_t        _timePC, _timeIter, _timeSP, _timeR;
  PreConditioner pc;
  real_t*        x;

  scanf("%d", &n);
  scanf("%d", &k);
  scanf("%lf", &omega);
  scanf("%d", &maxit);
  scanf("%lf", &epsilon);

  if (n <= 10)
  {
    HANDLE_ERROR(ERROR_INVALID_DIMENSION);
    return EXIT_FAILURE;
  }

  if (k <= 1 || k % 2 == 0)
  {
    HANDLE_ERROR(ERROR_INVALID_K);
    return EXIT_FAILURE;
  }

  if (!(omega == -1.0 || omega == 0.0 || (omega >= 1.0 && omega < 2.0)))
  {
    HANDLE_ERROR(ERROR_INVALID_OMEGA);
    return EXIT_FAILURE;
  }

  err = createLinearSystem(n, k, &ls);
  if (err != OK)
  {
    HANDLE_ERROR(err);
    return EXIT_FAILURE;
  }

  err = genSymetricPositive(&ls, &_timeSP);
  if (err != OK)
  {
    HANDLE_ERROR(err);
    return EXIT_FAILURE;
  }

#ifdef __DEBUG__
  printLinearSystem(&ls);
  printf("\n");
  return 0;
#endif

  initPreConditioner(&pc, omega);
  x = zeroes(ls.size);

#ifdef LIKWID_PERFMON
  LIKWID_MARKER_INIT;
#endif

  err = pcg(&ls, &pc, x, maxit, &it, epsilon, &maxNorm, &_timePC, &_timeIter);
  if (err != OK)
  {
    HANDLE_ERROR(err);
    return EXIT_FAILURE;
  }

#ifdef LIKWID_PERFMON
  LIKWID_MARKER_CLOSE;
#endif

#ifdef LIKWID_PERFMON
  LIKWID_MARKER_INIT;
#endif

  err = calcResiduoSL(&ls, x, &normL2, &_timeR);
  if (err != OK)
  {
    HANDLE_ERROR(err);
    return EXIT_FAILURE;
  }

  printf("%ld\n", ls.size);
  printVector(x, ls.size);
  printf("\n");
  printf("%.16f\n", maxNorm);
  printf("%.16f\n", normL2);
  printf("%.8f\n", _timePC);
  printf("%.8f\n", _timeIter);
  printf("%.8f\n", _timeR);
  
  // printf("%.8f\n", _timeIter);
  // printf("%.8f\n", _timeR);
  // printVector(x, ls.size);

#ifdef __DEBUG__
  printf("tamanho: %ld\n", ls.size);
  printf("iteracoes: %d\n", it);
  printf("\n");
  printf("norma: %.16f\n", maxNorm);
  printf("residuo: %.16f\n", normL2);
  printf("tempo_pc: %.8f\n", _timePC);
  printf("tempo_iter: %.8f\n", _timeIter);
  printf("tempo_residuo: %.8f\n", _timeR);
#endif

#ifdef LIKWID_PERFMON
  LIKWID_MARKER_CLOSE;
#endif

  free(x);
  freeLinearSystem(&ls);
  return EXIT_SUCCESS;
}
