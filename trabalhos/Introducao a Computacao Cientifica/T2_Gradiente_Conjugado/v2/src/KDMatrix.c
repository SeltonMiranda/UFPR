/**
 * @author: Selton Miranda Rolim
 * GRR:    20235688
 */

#include "KDMatrix.h"

#include <stdio.h>
#include <string.h>

#define ALIGMENT 64
#define UNROLL_FACTOR 4

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** STATIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

static inline real_t generateRandomA(unsigned int i, unsigned int j, unsigned int k);

/**
 * Função que gera os coeficientes de um sistema linear k-diagonal
 * @param i,j coordenadas do elemento a ser calculado (0<=i,j<n)
 * @param k numero de diagonais da matriz A
 */
static inline real_t generateRandomA(unsigned int i, unsigned int j, unsigned int k)
{
  static real_t invRandMax = 1.0 / (real_t)RAND_MAX;
  return ((i == j) ? (real_t)(k << 1) : 1.0) * (real_t)random() * invRandMax;
}

/***************************************************************************************/
/****************************                  *****************************************/
/**************************** PUBLIC FUNCTIONS *****************************************/
/****************************                  *****************************************/
/***************************************************************************************/

real_t getValueAt(KDMatrix* matrix, int i, int j)
{
  int half = matrix->k / 2;
  int d = j - i;
  if ( d < -half || d > half)
  {
    return 0.0;
  }
  int row = d + half;
  int idx = row * matrix->n + i;
  return matrix->data[idx];
}

void setValueAt(KDMatrix* matrix, int i, int j, real_t value)
{
  int half = matrix->k / 2;
  int d = j - i;
  if (d < -half || d > half)
  {
    return;
  }
  int row = d + half;
  int idx = row * matrix->n + i;
  matrix->data[idx] = value;
}

ErrorType createKDiagonal(int n, int k, KDMatrix* matrix)
{
  if (n <= 0 || k <= 0 || k > n)
  {
    return ERROR_INVALID_MATRIX_SIZE;
  }

  ErrorType err = allocKDMatrix(matrix, n, k);
  if (err != OK)
  {
    return ERROR_MEMORY_ALLOCATION_FAILED;
  }

  int half = k / 2;
  for (int i = 0; i < n; i++)
  {
    for (int d = -half; d <= half; d++)
    {
      int j = i + d;
      if (j < 0 || j >= n)
      {
        continue;
      }
      setValueAt(matrix, i, j, generateRandomA(i, j, k));
    }
  }
  return OK;
}

ErrorType allocKDMatrix(KDMatrix* m, int n, int k)
{
  size_t bytes = (size_t)n * (size_t)k * sizeof(real_t);
  m->n = n;
  m->k = k;
  m->data = NULL;

  if (posix_memalign((void**)&m->data, ALIGMENT, bytes) != 0)
  {
    return ERROR_MEMORY_ALLOCATION_FAILED;
  }

  memset(m->data, 0, bytes);
  return OK;
}

inline void freeKDiagonal(KDMatrix* m)
{
  if (!m)
  {
    return;
  }

  if (m->data)
  {
    free(m->data);
  }
  m->data = NULL;
  m->n = m->k = 0;
}

void multMatrixVector(KDMatrix* m, real_t* x, real_t* res, int size)
{
  int    k    = m->k;
  int    half = k / 2;
  real_t sum;

  for (int i = 0; i < size; i++)
  { // linhas
    sum = 0.0;
    for (int j = i - half; j <= i + half; j++)
    { // colunas da banda
      if (j >= 0 && j < size)
        sum += getValueAt(m, i, j) * x[j];
    }

    res[i] = sum;
  }
}

void multMatrixVector_otimz(KDMatrix* m, real_t* restrict x, real_t* restrict res, int size)
{
    int n    = m->n;
    int k    = m->k;
    int half = k / 2;

    memset(res, 0, size * sizeof(real_t));
    for (int row = 0; row < k; row++)
    {
        real_t* band = m->data + (size_t)row * n;
        int d = row - half;
        int i_start;
        int i_end;

        if (d < 0) // Diagonais Inferiores
        {
            i_start = -d;
            i_end   = n; 
        }
        else // Diagonais Principal Superiores
        {
            i_start = 0;
            i_end   = n - d;
        }

        for (int i = i_start; i < i_end; i++)
        {
            res[i] += band[i] * x[i + d];
        }
    }
}
// {
//     int n    = m->n;
//     int k    = m->k;
//     int half = k / 2;
// 
//     // Diagonais superiores
//     for (int row = 0; row < half; row++)
//     {
//         real_t* band = m->data + (size_t)row * n;
//         int offset = row - half;          
//         for (int i = -(offset); i < n; i++)
//         {
//             res[i + offset] += band[i] * x[i];
//         }
//     }
// 
//     // Diagonais inferiores
//     for (int row = half; row < k; row++)
//     {
//         real_t* band = m->data + (size_t)row * n;
//         int offset = row - half;         
//         for (int i = 0; i < n - offset; i++)
//         {
//             res[i + offset] += band[i] * x[i];
//         }
//     }
// }

real_t dotProduct(real_t* x, real_t* y, int size)
{
  real_t res = 0.0;
  for (int i = 0; i < size; i++)
    res += x[i] * y[i];
  return res;
}

real_t dotProduct_otimz(real_t* restrict x, real_t* restrict y, int size)
{
  real_t sum0 = 0.0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
  int    i = 0;

  int unroll = size - (size % UNROLL_FACTOR);
  for (; i < unroll; i += UNROLL_FACTOR)
  {
    sum0 += x[i] * y[i];
    sum1 += x[i + 1] * y[i + 1];
    sum2 += x[i + 2] * y[i + 2];
    sum3 += x[i + 3] * y[i + 3];
  }

  real_t res = sum0 + sum1 + sum2 + sum3;
  for (; i < size; i++)
  {
    res += x[i] * y[i];
  }

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