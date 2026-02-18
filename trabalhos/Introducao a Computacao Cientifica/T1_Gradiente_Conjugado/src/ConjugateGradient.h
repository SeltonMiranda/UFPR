/**
 * Author: Selton Miranda Rolim
 * GRR:    20235688
 */

#ifndef __CONJUGATE_GRADIENT_METHOD__
#define __CONJUGATE_GRADIENT_METHOD__

#include "utils.h"
#include "ErrorType.h"

typedef struct LinearSystem_t LinearSystem;
typedef struct KDMatrix_t KDMatrix;

/**
 * @brief Ponteiro para uma função. Aplica o pré-condicionador definido por omêga.
 * 
 * @param A     Ponteiro para uma struct KDMatrix, para obter as matrizes D, L e U.
 * @param r     Ponteiro para o vetor de resíduo (entrada).
 * @param z     Ponteiro para o vetor de resíduo pré-condicionado (saída).
 * @param size  Dimensão do Sistema Linear.
 * @param _time Ponteiro para armazenar o tempo gasto na função.
 */
typedef void (*PreConditionerApplier)(KDMatrix* A, real_t *r, real_t* z, int size, real_t* _time);

typedef struct PreConditioner_t {
  /**
   * Valor que decidirá qual Pré-Condicionar será utilizado.
   */
  real_t omega;

  /**
   * Ponteiro para uma função que aplica o Pré-Condicionador de acordo com omega.
   */
  PreConditionerApplier PCApply;
} PreConditioner;

/**
 * @brief Inicializa o Pré-Condicionador de acordo com omega.
 * 
 * @param pc Ponteiro para uma struct PreConditioner.
 * @param omega Valor real que decidirá o Pré-Condicionador a ser utilizado.
 */
void initPreConditioner(PreConditioner* pc, real_t omega);

/**
 * @brief Função que utiliza o Método do Gradiente Conjugado Pré-Condicionado para resolver
 * um Sistema Linear Ax = b aproximado.
 * 
 * @param ls Ponteiro para uma struct LinearSystem.
 * @param pc Ponteiro para uma struct PreConditioner.
 * @param x  Ponteiro para um vetor solução (inicialmente deve estar zerado).
 * @param maxit Quantidade máxima de iterações realizadas pelo Método.
 * @param tol  Tolerância do erro da aproximação.
 * @param _timePC Ponteiro para armazenar o tempo de calculo do Pré-Condicionador.
 * @param _timeIter Ponteiro para armazenar o tempo médio de cada iteração.
 * @param it Ponteiro para armazenar a quantidade de iterações realizas pelo método.
 * @return OK em caso de sucesso ou erro, caso contrário.
 */
ErrorType pcg(
                LinearSystem* ls,
                PreConditioner* pc,
                real_t* x,
                int maxit,
                real_t tol,
                real_t* _timePC,
                real_t* _timeIter,
                int* it
              );

#endif // __CONJUGATE_GRADIENT_METHOD__