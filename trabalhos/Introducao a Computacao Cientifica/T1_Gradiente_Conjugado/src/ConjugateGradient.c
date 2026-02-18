/**
 * Author: Selton Miranda Rolim
 * GRR:    20235688
 */

#include "ConjugateGradient.h"
#include "LinearSystem.h"

#include <string.h> // memcpy

/**
 * Devolve matriz M⁻¹
 *
 */
// static void geraPreCond(real_t *D, real_t *L, real_t *U, real_t w, int n, int k, real_t **M, real_t *tempo)
// {
//   if (w == -1) {
//     return;
//   }
// }

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** STATIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

static inline void noPreConditioner(KDMatrix* A, real_t* r, real_t* z, int size, real_t* _time);
static inline void applyJacobi(KDMatrix* A, real_t* r, real_t* z, int size, real_t* _time);

static inline void noPreConditioner(KDMatrix* A, real_t* r, real_t* z, int size, real_t* _time)
{
  *_time = timestamp();
  memcpy(z, r, size * sizeof(real_t));
  *_time = timestamp() - *_time;
  return;
}

static inline void applyJacobi(KDMatrix* A, real_t* r, real_t* z, int size, real_t* _time)
{
  *_time = timestamp();
  for (int i = 0; i < size; i++) {
    real_t A_ii = getValueAt(A, i, i);
    if (A_ii != 0.0) 
      z[i] = r[i] / A_ii;
    else
      z[i] = r[i];
  }
  *_time = timestamp() - *_time;
  return;
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
    pc->PCApply = noPreConditioner; 
  else if (omega == 0.0) {
    pc->PCApply = applyJacobi;
  }
}

ErrorType pcg(LinearSystem* ls, PreConditioner* pc, real_t* x, int maxit, real_t tol, real_t* _timePC, real_t* _timeIter, int* it)
{
  KDMatrix* A = &ls->matrix;
  int size = ls->size;
  real_t* b = ls->b;
  real_t alpha, beta, r_new, r_old, r0;

  real_t* r  = (real_t*)calloc(size, sizeof(real_t));
  real_t* z  = (real_t*)calloc(size, sizeof(real_t));
  real_t* p  = (real_t*)calloc(size, sizeof(real_t));
  real_t* Ap = (real_t*)calloc(size, sizeof(real_t));

  if (!r || !z || !p || !Ap) goto defer;

  // Calculando resídui r0 = b - Ax0
  multMatrixVector(A, x, r, size);
  for (int i = 0; i < size; i++)
    r[i] = b[i] - r[i];

  // Resolvendo Mz0 = r0 (pré-condicionador)
  pc->PCApply(A, r, z, size, _timePC);
  r_new = dotProduct(r, z, size);

  // Direção inicial p0 = z0
  memcpy(p, z, size * sizeof(real_t));
  r_old = r_new;
  r0    = r_new;

  *it = 0;
  for (int k = 0; k < maxit; k++) {
    *_timeIter = timestamp();

    // Calculando alpha_k = (r_k * z_k) / (p_k * A * p_k)
    multMatrixVector(A, p, Ap, size);
    alpha = r_new / dotProduct(p, Ap, size);
    r_old = r_new;

    // Calculando x_k+1 e r_k+1
    for (int i = 0; i < size; i++) {
      x[i] = x[i] + alpha * p[i];
      r[i] = r[i] - alpha * Ap[i];
    }

    
    // Resolvendo M * z_k+1 = r_k+1
    pc->PCApply(A, r, z, size, _timePC);
    r_new = dotProduct(r, z, size);

    if (sqrt(r_new) < tol * sqrt(r0)) break;

    // Calculando beta = (r_k+1 * z_k+1) / r_k * z_k
    beta = r_new / r_old;

    // Atualizando direção p_k+1 = z_k+1 + beta_k * p_k
    for (int i = 0; i < size; i++) {
      p[i] = z[i] + beta * p[i];
    }

    (*it)++;
  } 

  *_timeIter = timestamp() - *_timeIter;
  *_timeIter /= (*it);

  free(r);
  free(z);
  free(p);
  free(Ap);
  return OK;

defer:
  if (Ap) free(Ap);
  if (p)  free(p);
  if (z)  free(z);
  if (r)  free(r);
  return ERROR_MEMORY_ALLOCATION_FAILED;
}