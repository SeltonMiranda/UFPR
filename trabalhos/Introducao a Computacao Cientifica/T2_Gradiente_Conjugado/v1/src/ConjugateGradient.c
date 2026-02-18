/**
 * @author: Selton Miranda Rolim
 * GRR:    20235688
 */

#include "ConjugateGradient.h"
#include "LinearSystem.h"

#include <float.h>  // DBL_EPSILON
#include <string.h> // memcpy

#ifdef LIKWID_PERFMON
#include "likwid.h"
#endif

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** STATIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

static inline void noPreConditioner(KDMatrix* matrix, real_t* r, real_t* z, int size, real_t* _time, real_t omega);
static inline void jacobi(KDMatrix* matrix, real_t* r, real_t* z, int size, real_t* _time, real_t omega);
static inline void Gauss_Seidel(KDMatrix* matrix, real_t* r, real_t* z, int size, real_t* _time, real_t omega);
static inline void SSOR(KDMatrix* matrix, real_t* z, real_t* r, int size, real_t* _time, real_t omega);

static inline void noPreConditioner(KDMatrix* matrix, real_t* r, real_t* z, int size, real_t* _time, real_t omega)
{
  *_time = timestamp();
  memcpy(z, r, size * sizeof(real_t));
  *_time = timestamp() - *_time;
}

static inline void jacobi(KDMatrix* matrix, real_t* r, real_t* z, int size, real_t* _time, real_t omega)
{
  *_time = timestamp();
  real_t A_ii;
  for (int i = 0; i < size; i++)
  {
    A_ii = getValueAt(matrix, i, i);
    if (A_ii != 0.0)
      z[i] = r[i] / A_ii;
    else
      z[i] = r[i];
  }
  *_time = timestamp() - *_time;
}

static inline void Gauss_Seidel(KDMatrix* matrix, real_t* r, real_t* z, int size, real_t* _time, real_t omega)
{
  *_time    = timestamp();
  real_t* y = (real_t*)calloc(size, sizeof(real_t));
  real_t  sum, dii, aij;
  if (!y)
  {
    HANDLE_ERROR(ERROR_MEMORY_ALLOCATION_FAILED);
    exit(1);
  }

  // substituição direta (resolve (D + L) y = r)
  for (int i = 0; i < size; i++)
  {
    sum = 0.0;
    for (int j = 0; j < i; j++)
    {
      aij = getValueAt(matrix, i, j);
      sum += aij * y[j];
    }

    dii  = getValueAt(matrix, i, i);
    y[i] = (r[i] - sum) / dii;
  }

  // retrossubstituição (resolve (D + U) z = D * y)
  for (int i = size - 1; i >= 0; i--)
  {
    sum = 0.0;
    for (int j = i + 1; j < size; j++)
    {
      aij = getValueAt(matrix, i, j);
      sum += aij * z[j];
    }

    dii  = getValueAt(matrix, i, i);
    z[i] = (dii * y[i] - sum) / dii;
  }

  free(y);
  *_time = timestamp() - *_time;
}

static inline void SSOR(KDMatrix* matrix, real_t* r, real_t* z, int size, real_t* _time, real_t omega)
{
  *_time    = timestamp();
  real_t* y = (real_t*)calloc(size, sizeof(real_t));
  real_t  sum, dii, aij;
  if (!y)
  {
    HANDLE_ERROR(ERROR_MEMORY_ALLOCATION_FAILED);
    exit(1);
  }

  // substituição direta (resolve (D + ωL) y = r)
  for (int i = 0; i < size; i++)
  {
    sum = 0.0;
    for (int j = 0; j < i; j++)
    {
      aij = getValueAt(matrix, i, j);
      sum += aij * y[j];
    }

    dii  = getValueAt(matrix, i, i);
    y[i] = (r[i] - omega * sum) / dii;
  }

  // retrossubstituição (resolve (D + ωU) z = D * y)
  for (int i = size - 1; i >= 0; i--)
  {
    sum = 0.0;
    for (int j = i + 1; j < size; j++)
    {
      aij = getValueAt(matrix, i, j);
      sum += aij * z[j];
    }

    dii  = getValueAt(matrix, i, i);
    z[i] = (dii * y[i] - omega * sum) / dii;
  }

  free(y);
  *_time = timestamp() - *_time;
}

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** PUBLIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

void initPreConditioner(PreConditioner* pc, real_t omega)
{
  pc->omega = omega;
  if (omega == -1)
  {
    pc->PCApply = noPreConditioner;
  }
  else if (omega == 0.0)
  {
    pc->PCApply = jacobi;
  }
  else if (omega == 1.0)
  {
    pc->PCApply = Gauss_Seidel;
  }
  else
  {
    pc->PCApply = SSOR;
  }
}

ErrorType pcg(
    LinearSystem*   ls,
    PreConditioner* pc,
    real_t*         x,
    int             maxit,
    int*            it,
    real_t          tol,
    real_t*         maxNorm,
    real_t*         _timePC,
    real_t*         _timeIter)
{
  KDMatrix* A     = &ls->matrix;
  int       size  = ls->size;
  real_t*   b     = ls->b;
  real_t    alpha = 0.0, beta = 0.0;
  real_t    rtz, rtz_old, rnorm0;

  real_t* r  = (real_t*)calloc(size, sizeof(real_t));
  real_t* z  = (real_t*)calloc(size, sizeof(real_t));
  real_t* p  = (real_t*)calloc(size, sizeof(real_t));
  real_t* Ap = (real_t*)calloc(size, sizeof(real_t));

  if (!r || !z || !p || !Ap)
  {
    return ERROR_MEMORY_ALLOCATION_FAILED;
  }

  // r0 = b - A*x0
  multMatrixVector(A, x, r, size);
  for (int i = 0; i < size; i++)
  {
    r[i] = b[i] - r[i];
  }

  rnorm0 = sqrt(dotProduct(r, r, size));
  if (rnorm0 < DBL_EPSILON)
  {
    *it        = 0;
    *_timeIter = 0.0;
    *_timePC   = 0.0;
    *maxNorm   = 0.0;
    free(r);
    free(z);
    free(p);
    free(Ap);
    return OK;
  }

  // z0 = M^{-1} r0
  pc->PCApply(A, r, z, size, _timePC, pc->omega);
  rtz = dotProduct(r, z, size);

  // p0 = z0
  memcpy(p, z, size * sizeof(real_t));
  rtz_old = rtz;

  #ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("op1");
  #endif

  double tstart = timestamp();
  *it           = 0;
  for (int k = 0; k < maxit; k++)
  {
    multMatrixVector(A, p, Ap, size);
    real_t denom = dotProduct(p, Ap, size);
    if (ABS(denom) < DBL_EPSILON)
    {
      break;
    }

    alpha = rtz / denom;

    // x_k+1 = x_k + alpha * p
    for (int i = 0; i < size; i++)
    {
      x[i] += alpha * p[i];
    }

    // r_k+1 = r_k - alpha * A p
    for (int i = 0; i < size; i++)
    {
      r[i] -= alpha * Ap[i];
    }

    (*it) = k + 1;
    // teste de convergência: ||r|| < tol * ||r0||
    // rnorm = sqrt(dotProduct(r, r, size));
    // if (rnorm <= tol * rnorm0)
    // {
    //   break;
    // }

    // z_k+1 = M^(-1) r_k+1
    pc->PCApply(A, r, z, size, _timePC, pc->omega);

    rtz = dotProduct(r, z, size);
    if (rtz_old < DBL_EPSILON)
    {
      break;
    }
    beta = rtz / rtz_old;

    // p_k+1 = z_k+1 + beta * p_k
    for (int i = 0; i < size; i++)
    {
      p[i] = z[i] + beta * p[i];
    }

    rtz_old = rtz;
  }

  #ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("op1");
  #endif

  *_timeIter = timestamp() - tstart;

  if ((*it) > 0)
    (*_timeIter) /= (*it);

  // maxNorm: máximo incremento absoluto aplicado a x na última iteração
  *maxNorm = 0.0;
  for (int i = 0; i < size; i++)
  {
    real_t inc = ABS(alpha * p[i]); // alpha e p são os últimos usados
    if (inc > *maxNorm)
    {
      *maxNorm = inc;
    }
  }

  free(r);
  free(z);
  free(p);
  free(Ap);

  // if ((*it) == maxit)
  // {
  //   return ERROR_METHOD_NOT_CONVERGED;
  // }

  return OK;
}
