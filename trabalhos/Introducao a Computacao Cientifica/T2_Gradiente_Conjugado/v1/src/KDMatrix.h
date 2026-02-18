/**
 * @author: Selton Miranda Rolim
 * GRR:    20235688
 */

#ifndef __KDMATRIX__
#define __KDMATRIX__

#include "ErrorType.h"
#include "utils.h"

/**
 * Matriz k-Diagonal
 */
typedef struct KDMatrix_t
{
  /**
   * Quantidade de diagonais presentes na matriz.
   */
  int_t k;

  /**
   * Ponteiro de ponteiros para armazenar os valores das diagonais.
   */
  real_t** A;
} KDMatrix;

/**
 * @brief Aloca memória para uma struct KDMatrix.
 *
 * @param m Ponteiro para uma struct KDMatrix.
 * @param n Dimensão da matriz.
 */
ErrorType allocKDMatrix(KDMatrix* m, int n);

/**
 * @brief Cria uma Matriz K-Diagonal com valores aleatórios (aloca memória).
 *
 * @param n       Tamanho da matriz.
 * @param k       Quantidade de diagonais.
 * @param matrix  Ponteiro para uma estrutura KDMatrix.
 * @return OK em caso de successo ou erro, caso contrário.
 */
ErrorType createKDiagonal(int n, int k, KDMatrix* matrix);

/**
 * @brief Libera memória de uma Matriz K-Diagonal.
 *
 * @param m Ponteiro para uma struct KDMatrix.
 */
void freeKDiagonal(KDMatrix* m);

/**
 * @brief Retorna um elemento na matriz na posição (i,j). Se está dentro das bandas
 * retorna o valor, senão retorna zero.
 *
 * @param matrix Ponteiro para uma struct KDMatrix.
 * @param i      Linha da matriz.
 * @param j      Coluna da matriz.
 * @return O elemento na posição (i,j).
 */
real_t getValueAt(KDMatrix* matrix, int i, int j);

/**
 * @brief Seta um valor na matriz na posição (i,j).
 *
 * @param matrix Ponteiro para uma struct KDMatrix.
 * @param i      Linha da matriz.
 * @param j      Coluna da matriz.
 * @param value  O valor a ser setado.
 */
void setValueAt(KDMatrix* matrix, int i, int j, real_t value);

/**
 * @brief Calcula o produto A * x, onde A é uma matriz K-Diagonal e x um vetor.
 *
 * @param m    Ponteiro para uma struct KDMatrix.
 * @param v    Ponteiro para um vetor.
 * @param res  Ponteiro para o vetor de saída (Previamente alocado).
 * @param size Dimensão da matriz.
 */
void multMatrixVector(KDMatrix* m, real_t* v, real_t* res, int size);

/**
 * @brief Calcula o produto escalar <x,y> entre dois vetores.
 *
 * @param x     Ponteiro para um vetor.
 * @param y     Ponteiro para um vetor.
 * @param size  Dimensão do vetor.
 * @return      O valor do produto escalar <x,y>
 */
real_t dotProduct(real_t* x, real_t* y, int size);

/**
 * @brief Cria um vetor com zeros (aloca memória).
 *
 * @param size Dimensão do vetor.
 */
real_t* zeroes(int size);

/**
 * @brief Imprime um vetor na saída padrão.
 *
 * @param v    Ponteiro para um vetor.
 * @param size Dimensão do vetor.
 */
void printVector(real_t* v, int size);

#endif // __KDMATRIX__