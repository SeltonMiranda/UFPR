/**
 * Author: Selton Miranda Rolim
 * GRR:    20235688
 */

#include "LinearSystem.h"
#include "ConjugateGradient.h"

int main()
{
  srand(20252);
  LinearSystem ls;
  ErrorType err;
  int n, k, maxit, it;
  real_t omega, epsilon;
  rtime_t _timePC, _timeIter, _timeSP;
  PreConditioner pc;
  real_t* x;

  scanf("%d", &n);
  scanf("%d", &k);
  scanf("%lf", &omega);
  scanf("%d", &maxit);
  scanf("%lf", &epsilon);

  if (n <= 10) {
    HANDLE_ERROR(ERROR_INVALID_DIMENSION);
    return 1;
  }

  if (k <= 1 || k % 2 == 0) {
    HANDLE_ERROR(ERROR_INVALID_K);
    return 1;
  }

  err = createLinearSystem(n, k, &ls);
  if (err != OK) {
    HANDLE_ERROR(err);
    return 1;
  }

  printLinearSystem(&ls);
  printf("\n");

  err = genSymetricPositive(&ls, &_timeSP);
  if (err != OK) {
    HANDLE_ERROR(err);
    return 1;
  }
  
  initPreConditioner(&pc, omega);
  x = zeroes(ls.size);

  err = pcg(&ls, &pc, x, maxit, epsilon, &_timePC, &_timeIter, &it);
  if (err != OK) {
    HANDLE_ERROR(err);
    return 1;
  }

  printf("iteracoes: %d\n", it);
  printVector(x, ls.size);
  printf("\n");
  printf("tempo_pc: %.8f\n", _timePC);
  printf("tempo_iter: %.8f\n", _timeIter);

  free(x);
  freeLinearSystem(&ls);
  return 0;
}

