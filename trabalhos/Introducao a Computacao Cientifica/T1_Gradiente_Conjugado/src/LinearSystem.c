/**
 * Author: Selton Miranda Rolim
 * GRR:    20235688
 */


#include "LinearSystem.h"

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** STATIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

static inline real_t generateRandomB( unsigned int k );
static inline ErrorType allocArray(real_t** v, int n);
static inline void deallocArray(real_t** v);

/**
 * Função que gera os termos independentes de um sistema linear k-diagonal
 * @param k numero de diagonais da matriz A
 */
static inline real_t generateRandomB( unsigned int k )
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return (real_t)(k<<2) * (real_t)random() * invRandMax;
}

static inline ErrorType allocArray(real_t** v, int n)
{
  *v = (real_t*)calloc(n, sizeof(real_t));
  if (!(*v)) return ERROR_MEMORY_ALLOCATION_FAILED;
  return OK;
}

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
  if (err != OK) return err;

  err = allocArray(&ls->b, size);
  if (err != OK) return err;

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
  KDMatrix new;
  real_t* new_b;
  int size = ls->size;
  int k = original->k;
  int half = k / 2;

  new.k = k;
  if (allocKDMatrix(&new, size) != OK)
    return ERROR_MEMORY_ALLOCATION_FAILED;

  *_time = timestamp();

  for (int i = 0; i < size; i++) {
    for (int j = i - half; j <= i + half; j++) {
      if (j >= 0 && j < size) {
        real_t sum = 0.0;
        for (int l = 0; l < size; l++) {
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
  for (int i = 0; i < size; i++) {
    real_t sum = 0.0;
    for (int j = 0; j < size; j++) {
      real_t A_ji = getValueAt(original, j , i);
      sum += A_ji * ls->b[j];
    }
    new_b[i] = sum;
  }

  deallocArray(&ls->b);
  freeKDiagonal(original);

  ls->matrix = new;
  ls->b = new_b;

  *_time = timestamp() - *_time;
  return OK;
}


void geraDLU (real_t *A, int n, int k, real_t **D, real_t **L, real_t **U, rtime_t *tempo)
{
  *tempo = timestamp();


  *tempo = timestamp() - *tempo;
}

ErrorType calcResiduoSL(LinearSystem* ls, real_t* x, real_t* norm, rtime_t *_time)
{
  real_t* r;
  int size = ls->size;
  real_t norma = 0.0;

  *_time = timestamp();

  if (allocArray(&r, size) != OK)
    return ERROR_MEMORY_ALLOCATION_FAILED;
  
  multMatrixVector(&ls->matrix, x, r, size);
  for (int i = 0; i < size; i++) 
    norma += r[i] * r[i];
  deallocArray(&r);

  *_time = timestamp() - *_time;

  return norma;
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
  int n = s->size;
  printf("============ Matriz [%ld]-Diagonal ==============\n", s->matrix.k);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf(" %5.2f", getValueAt(m, i, j));
    }
    printf(" | ");
    printf(" %5.2f", b[i]);
    printf("\n");
  }
  printf("================================================\n");

  printf("=========== Valores das diagonais ==============\n");
  int half = m->k / 2;
  for (int i = 0; i < m->k; i++) {
    printf("k = [%d] ", i);
    if (i < half)
      printf("subdiagonal\n");
    else if (i > half)
      printf("superdiagonal\n");
    else
      printf("diagonal principal\n");
    printArray(m->A[i], n);
    printf("\n\n");
  }
  printf("================================================\n");
}