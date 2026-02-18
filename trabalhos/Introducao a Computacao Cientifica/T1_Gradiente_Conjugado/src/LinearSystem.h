/**
 * Author: Selton Miranda Rolim
 * GRR:    20235688
 */

#ifndef __SISLIN_H__
#define __SISLIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KDMatrix.h"

typedef struct LinearSystem_t {
  /**
   * A Matriz k-Diagonal do Sistema Linear.
   */
  KDMatrix matrix;

  /**
   * Vetor de Termos independentes.
   */
  real_t *b;

  /**
   * Dimensão do sistema linear.
   */
  int_t size;
} LinearSystem;

/**
 * @brief Cria um sistema linear Ax = b, onde A é uma matriz k-diagonal (aloca memória).
 * 
 * @param n   Tamanho do sistema linear.
 * @param k   Quantidade de diagonais.
 * @param ls  Ponteiro para uma struct LinearSystem.
 * @return OK em caso de sucesso ou erro, caso contrário.
 */
ErrorType createLinearSystem(int size, int k, LinearSystem* ls);

/**
 * @brief Libera memória de um sistema linear.
 * 
 * @param ls Ponteiro para uma struct LinearSystem.
 */
void freeLinearSystem(LinearSystem* ls);

/**
 * @brief Gera uma matriz k-diagonal Simétrica Positiva Definida (in-place)
 * 
 * @param ls    Ponteiro para uma struct LinearSystem.
 * @param _time Ponteiro para armazenar o tempo do calculo da norma.
 * @return Ok em caso de sucesso ou erro, caso contrário.
 */
ErrorType genSymetricPositive(LinearSystem* ls, rtime_t* _time);

/**
 * TODO!
 * Ideias
 * 1. Gerar D, L e U e guardar na struct PreConditioner.
 * 2. Utilizar essa função somente quando terminar de implementar pré-condicionadores de
 * Gauss-Seidel e SSOR.
 */
void geraDLU (real_t *A, int n, int k, real_t **D, real_t **L, real_t **U, real_t *tempo);

/**
 * @brief Calcula o resíduo do Sistema Linear Ax = b ou seja r = b - Ax, onde 
 * x é o vetor solução.
 * 
 * @param ls    Ponteiro para uma struct LinearSystem (entrada).
 * @param x     Ponteiro para um vetor solução (entrada).
 * @param norm  Ponteiro para armazenar a norma (saída).
 * @param _time Ponteiro para armazenar o tempo do calculo da norma.
 * @return OK em caso de sucesso ou erro, caso contrário.
 */
ErrorType calcResiduoSL(LinearSystem* ls, real_t* x, real_t* norm, real_t *_time);

/**
 * @brief Imprime o Sistema linear Ax = b no formato A | b na saída padrão.
 * Usado para depuração.
 * 
 * @param s Ponteiro para uma struct LinearSystem.
 */
void printLinearSystem(LinearSystem* s);

#endif // __SISLIN_H__