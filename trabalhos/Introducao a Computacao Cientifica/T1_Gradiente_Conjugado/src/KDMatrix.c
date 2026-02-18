/**
 * Author: Selton Miranda Rolim
 * GRR:    20235688
 */

#include "KDMatrix.h"

#include <stdio.h>

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** STATIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

static inline real_t generateRandomA( unsigned int i, unsigned int j, unsigned int k );
static ErrorType allocKD(KDMatrix* matrix, int n);
static inline void deallocKDMatrix(KDMatrix* matrix);

/**
 * Função que gera os coeficientes de um sistema linear k-diagonal
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
 * @param k numero de diagonais da matriz A
 */
static inline real_t generateRandomA( unsigned int i, unsigned int j, unsigned int k )
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return ( (i==j) ? (real_t)(k<<1) : 1.0 )  * (real_t)random() * invRandMax;
}

/**
 * @brief Aloca memória para uma matriz k-diagonal.
 * 
 * @param matrix Ponteiro para uma matriz k-diagonal.
 * @return OK em caso de sucesso ou erro, caso contrário.
 */
static ErrorType allocKD(KDMatrix* matrix, int n)
{
  int k = matrix->k;
  matrix->A = (real_t**)calloc(k, sizeof(real_t*)); // Aloca k diagonais
  if (!matrix->A)
    return ERROR_MEMORY_ALLOCATION_FAILED;

  for (int i = 0; i < k; i++) {
    matrix->A[i] = (real_t*)calloc(n, sizeof(real_t)); // Aloca n elementos para cada diagonal
    if (!matrix->A[i])
      return ERROR_MEMORY_ALLOCATION_FAILED;
  }

  return OK;
}

static inline void deallocKDMatrix(KDMatrix* matrix)
{
  int k = matrix->k;
  for (int i = 0; i < k; i++)
    free(matrix->A[i]);
  free(matrix->A);
}

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** PUBLIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

real_t getValueAt(KDMatrix* matrix, int i, int j)
{
  int diff = j - i;
  int half = matrix->k / 2;

  // Fora das diagonais (Para depuração)
  if (diff < -half || diff > half)
    return 0.0;

  int diag = diff + half; 
  return matrix->A[diag][j];
}

void setValueAt(KDMatrix* matrix, int i, int j, real_t value)
{
  int diff = j - i;
  int half = matrix->k / 2;
  
  if (diff < -half || diff > half)
    return;

  int diag = diff + half;
  matrix->A[diag][j] = value;
}

/* Cria matriz 'A' k-diagonal */
ErrorType createKDiagonal(int n, int k, KDMatrix* matrix)
{
  if (n <= 0 || k <= 0 || k > n)
    return ERROR_INVALID_MATRIX_SIZE;

  matrix->k = k;
  if (allocKD(matrix, n) != OK)
    return ERROR_MEMORY_ALLOCATION_FAILED;
  
  int half = k / 2;
  for (int d = 0; d < k; d++) { // diagonal
    for (int j = 0; j < n; j++) { // coluna
      int i = j + (d - half); // linha 
      if (i >= 0 && i < n)
        setValueAt(matrix, i, j, generateRandomA(i, j, k));
    }
  }

  return OK;
}

ErrorType allocKDMatrix(KDMatrix* m, int n)
{
  return allocKD(m, n);
}

inline void freeKDiagonal(KDMatrix* m)
{
  deallocKDMatrix(m);
}

void multMatrixVector(KDMatrix* m, real_t *x, real_t* res, int size)
{
  // assert(m);
  // assert(x);
  // assert(res);

  int k = m->k;
  int half = k / 2;
  real_t sum;

  for (int i = 0; i < size; i++) { // linhas
    sum = 0.0;
    for (int j = i - half; j <= i + half; j++) { // colunas da banda
      if (j >= 0 && j < size)
        sum += getValueAt(m, i, j) * x[j];
    }

    res[i] = sum;
  }
}

inline real_t dotProduct(real_t* x, real_t* y, int size)
{
  real_t res = 0.0;
  for (int i = 0; i < size; i++)
    res += x[i] * y[i];
  return res;
}

inline real_t* zeroes(int size)
{
  return (real_t*)calloc(size, sizeof(real_t));
}

inline void printVector(real_t* v, int size)
{
  for (int i = 0; i < size; i++)
    printf(" %.16f ", v[i]);
}