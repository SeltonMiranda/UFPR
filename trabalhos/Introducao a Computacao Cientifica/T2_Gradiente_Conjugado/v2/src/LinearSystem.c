/**
 * @author: Selton Miranda Rolim
 * GRR:    20235688
 */

#include "LinearSystem.h"

#ifdef LIKWID_PERFMON
#include <likwid.h>
#endif

#define UNROLL_FACTOR 4
#define ALIGNMENT 64

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** STATIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

static inline real_t    generateRandomB(unsigned int k);
static inline ErrorType allocArray(real_t** v, int n);
static inline void      deallocArray(real_t** v);

/**
 * @brief Função que gera os termos independentes de um sistema linear k-diagonal
 * @param k numero de diagonais da matriz A
 *
 * @return um valor aleatório.
 */
static inline real_t generateRandomB(unsigned int k)
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return (real_t)(k << 2) * (real_t)random() * invRandMax;
}

/**
 * @brief Aloca memória para um array.
 *
 * @param v Ponteiro para o endereço do array.
 * @param n Tamanho do array.
 *
 * @return Erro em caso de falha ou OK em caso de sucesso.
 */
static inline ErrorType allocArray(real_t** v, int n)
{
  if (posix_memalign((void**)v, ALIGNMENT, n * sizeof(real_t)) != 0)
  {
    return ERROR_MEMORY_ALLOCATION_FAILED;
  }
  memset(*v, 0, n * sizeof(real_t));
  return OK;
}

/**
 * @brief Desaloca memória para um array.
 *
 * @param v Ponteiro para o endereço do vetor.
 */
static inline void deallocArray(real_t** v)
{
  free(*v);
}

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** PUBLIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

ErrorType createLinearSystem(int size, int k, LinearSystem* ls)
{
  ErrorType err;
  err = createKDiagonal(size, k, &ls->matrix);
  if (err != OK)
    return err;

  err = allocArray(&ls->b, size);
  if (err != OK)
    return err;

  for (int i = 0; i < size; i++)
    ls->b[i] = generateRandomB(k);

  ls->size = size;
  return OK;
}

void freeLinearSystem(LinearSystem* ls)
{
  freeKDiagonal(&ls->matrix);
  deallocArray(&ls->b);
}

ErrorType genSymetricPositive(LinearSystem* ls, rtime_t* _time)
{
  KDMatrix* original = &ls->matrix;
  KDMatrix  new;
  real_t*   new_b;
  int       size = ls->size;
  int       k    = original->k;
  int       half = k / 2;

  new.k = k;
  if (allocKDMatrix(&new, size, k) != OK)
    return ERROR_MEMORY_ALLOCATION_FAILED;

  *_time = timestamp();

  for (int i = 0; i < size; i++)
  {
    for (int j = i - half; j <= i + half; j++)
    {
      if (j >= 0 && j < size)
      {
        real_t sum = 0.0;
        for (int l = 0; l < size; l++)
        {
          real_t A_li = getValueAt(original, l, i);
          real_t A_lj = getValueAt(original, l, j);
          sum += A_li * A_lj;
        }
        setValueAt(&new, i, j, sum);
      }
    }
  }

  if (allocArray(&new_b, size) != OK)
    return ERROR_MEMORY_ALLOCATION_FAILED;
  for (int i = 0; i < size; i++)
  {
    real_t sum = 0.0;
    for (int j = 0; j < size; j++)
    {
      real_t A_ji = getValueAt(original, j, i);
      sum += A_ji * ls->b[j];
    }
    new_b[i] = sum;
  }

  deallocArray(&ls->b);
  freeKDiagonal(original);

  ls->matrix = new;
  ls->b      = new_b;

  *_time = timestamp() - *_time;
  return OK;
}

void geraDLU(real_t* A, int n, int k, real_t** D, real_t** L, real_t** U, rtime_t* tempo)
{
  *tempo = timestamp();

  *tempo = timestamp() - *tempo;
}

ErrorType calcResiduoSL(LinearSystem* ls, real_t* x, real_t* normL2, rtime_t* _time)
{
  real_t *r, *temp;
  int     size  = ls->size;
  real_t  norma = 0.0;

  *_time = timestamp();

  if (allocArray(&r, size) != OK)
    return ERROR_MEMORY_ALLOCATION_FAILED;

  if (allocArray(&temp, size) != OK)
    return ERROR_MEMORY_ALLOCATION_FAILED;

  multMatrixVector(&ls->matrix, x, temp, size);
  for (int i = 0; i < size; i++)
    r[i] = ls->b[i] - temp[i];

  for (int i = 0; i < size; i++)
    norma += r[i] * r[i];
  deallocArray(&r);
  deallocArray(&temp);

  *_time    = timestamp() - *_time;
  (*normL2) = sqrt(norma);

  return OK;
}

ErrorType calcResiduoSL_otimz( LinearSystem* ls, real_t* x, real_t* normL2, rtime_t* _time)
{

    real_t* temp;
    int size = ls->size;
    if (allocArray(&temp, size) != OK)
    {
      return ERROR_MEMORY_ALLOCATION_FAILED;
    }
    *_time = timestamp();

#ifdef LIKWID_PERFMON
    LIKWID_MARKER_START("op2");
#endif

    real_t norma = 0.0;
    multMatrixVector_otimz(&ls->matrix, x, temp, size);

    real_t r0, r1, r2, r3;
    int i;
    for (i = 0; i < size - (size % UNROLL_FACTOR); i += UNROLL_FACTOR)
    {
      r0 = ls->b[i] - temp[i];
      r1 = ls->b[i+1] - temp[i+1];
      r2 = ls->b[i+2] - temp[i+2];
      r3 = ls->b[i+3] - temp[i+3];
      
      norma += r0 * r0;
      norma += r1 * r1;
      norma += r2 * r2;
      norma += r3 * r3;
    }
    real_t r;
    for (; i < size; i++)
    {
      r = ls->b[i] - temp[i];
      norma += r * r;
    }

#ifdef LIKWID_PERFMON
    LIKWID_MARKER_STOP("op2");
#endif

    deallocArray(&temp);

    *_time    = timestamp() - *_time;
    *normL2   = sqrt(norma);

    return OK;
}


static void printArray(real_t* array, int n)
{
  for (int i = 0; i < n; i++)
    printf(" %4.2f ", array[i]);
}

void printLinearSystem(LinearSystem* s)
{
  KDMatrix* m = &s->matrix;
  real_t*   b = s->b;
  int       n = s->size;
  printf("============ Matriz [%d]-Diagonal ==============\n", s->matrix.k);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf(" %5.2f", getValueAt(m, i, j));
    }
    printf(" | ");
    printf(" %5.2f", b[i]);
    printf("\n");
  }
  printf("================================================\n");

  printf("=========== Valores das diagonais ==============\n");
  int half = m->k / 2;
  for (int i = 0; i < m->k; i++)
  {
    printf("k = [%d] ", i);
    if (i < half)
      printf("subdiagonal\n");
    else if (i > half)
      printf("superdiagonal\n");
    else
      printf("diagonal principal\n");
    printArray(m->data, n);
    printf("\n\n");
  }
  printf("================================================\n");
  printf("Valores de b\n");
  for (int i = 0; i < s->size; i++)
  {
    printf(" %5.2f ", s->b[i]);
  }
  printf("\n================================================\n");
}