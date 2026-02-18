/**
 * Nome: Selton Miranda Rolim
 * GRR: 20235688
 */

#ifndef __EQDIFF_H__
#define __EQDIFF_H__

#include <stdbool.h>

#include "utils.h"

#define FORMAT "%23.15e"
#define MAXIT  100
#define NORMA_MAX 1e-5

/**
 * @struct Tridiag
 * @brief Representa uma matriz tridiagonal.
 * 
 * Essa struct armazena as diagonais principal, superior e inferior de uma matriz
 * tridiagonal.
 */
typedef struct {
  /**
   * @var D, Di, Ds, B
   * @brief Ponteiros para vetores.
   */
  real_t *D, *Di, *Ds, *B;

  /**
   * @var n
   * @brief Tamanho da matriz tridiagonal.
   */
  int n;
} Tridiag;


/**
 * @struct EDo
 * @brief Representa uma Equação Diferencial Ordinária.
 * 
 * Esta struct armazena as informações de uma EDO do tipo y'' + py' + qy = r(x),
 * onde p e q são coeficientes reais e r(x) = r1*x + r2*x*x + r3*cos(x) + r4*e^x.
 * 
 */
typedef struct {
  /**
   * @var n
   * @brief Número de pontos internos na malha.
   */
  int n;

  /**
   * @var a, b
   * @brief Intervalo a qual será aplicada a EDO.
   */
  real_t a, b;

  /**
   * @var ya, yb
   * @brief Condições de contorno.
   */
  real_t ya, yb;

  /**
   * @var p, q, r1, r2, r3, r4
   * @brief Coeficientes EDO genérica de 2° ordem e grau 1.
   */
  real_t p, q, r1, r2, r3, r4;
} EDo;


/**
 * @brief Gera uma matriz tridiagonal.
 * 
 * Esta função cria uma matriz tridiagonal a partir de uma EDO.
 *  
 * 
 * @param edoeq Ponteiro para uma struct EDo.
 * @return Ponteiro para uma struct Tridiag.
 * @note Esta função aloca memória para um struct Tridiag.
 */
Tridiag *genTridiag (EDo *edoeq);

/**
 * @brief Imprime a matriz tridiagonal de uma EDO.
 * 
 * Auto-explicativo.
 * 
 * @param edoeq Ponteiro para uma struct EDo.
 */
void prnEDOsl (EDo *edoeq);

/**
 * @brief Lê uma EDO.
 * 
 * Esta função lê os termos de uma equação diferencial ordinária de uma entrada.
 * 
 * @return Uma struct EDo.
 */
EDo lerEDO(void);

/**
 * @brief lê os coeficientes de uma função r(x).
 * 
 * Tenta ler os coefiecentes da função r(x) da EDO.
 * 
 * @param  edo Ponteiro para EDO.
 * @return True se leu exatamente 4 coeficientes, False caso contrário.
 */
bool tentarLerCoeficientes(EDo *edo);

/**
 * @brief Ajusta o vetor de coeficientes.
 * 
 * Ajusta o vetor de coeficientes da matriz tridiagonal.
 * 
 * @param edo Ponteiro para EDO.
 * @param sl  Ponteiro para a matriz tridiagonal.
 */
void ajustarCoeficientes(EDo *edo, Tridiag *sl);

/**
 * @brief Decompõe uma matriz tridiagonal pelo método LU.
 * 
 * Esta função decompõe uma matriz tridiagonal em duas matrizes, UPPER e LOWER.
 * A modificação é feita in-place, ou seja, a matriz tridiagonal é modificada.
 * 
 * @param sl Ponteiro para matriz tridiagonal.
 */
void fatoracaoLU(Tridiag *sl);

/**
 * @brief Calcula AX = b.
 * 
 * Esta função calcula AX = b, sendo que A = LU, retornando o resultado em X.
 * @param sl Ponteiro para a matriz tridiagonal.
 * @param X  Ponteiro para o vetor de incógnitas.
 */
void calcula(Tridiag *sl, real_t *X);

/**
 * @brief Zera um vetor.
 * 
 * Auto-explicativo.
 * 
 * @param v Ponteiro para o vetor.
 * @param n Tamanho do vetor.
 */
void zeraVetor(real_t *v, int n);

/**
 * @brief Imprime um vetor.
 * 
 * Auto-explicativo.
 * 
 * @param v Ponteiro para um vetor.
 * @param n Tamanho do vetor.
 */
void prnVetor(real_t *v, unsigned int n);

/**
 * @brief Desaloca uma struct Tridiag.
 * 
 * Esta função desaloca memória para uma struct Tridiag.
 * 
 * @param sl Ponteiro de ponteiro de uma struct Tridiag.
 */
void liberaTridiag(Tridiag **sl);

/**
 * @brief Desaloca memória de um vetor.
 * 
 * Auto-explicativo.
 * 
 * @param v Ponteiro de ponteiro de um vetor.
 */
void liberaVetor(real_t **v);

/**
 * @brief Calcula a norma L2 do resíduo de uma EDO.
 * 
 * @param edo Ponteiro para a struct EDo com os parâmetros da equação.
 * @param Y Vetor com a solução numérica da EDO.
 * @return real_t A norma L2 do resíduos.
 */
real_t normaL2_EDO (EDo *edo, real_t *Y);

/**
 * @brief Calcula a norma L2 do resíduo de uma matriz tridiagonal.
 * 
 * @param sl Ponteiro para struct Tridiag.
 * @param Y  Ponteiro para vetor solução.
 * @return real_t A norma L2 do resíduo.
 */
real_t normaL2_3Diag(Tridiag *sl, real_t *Y);


/**
 * @brief Calcula o sistema linear Ax = B, onde A é uma matriz tridiagonal.
 * 
 * @param sl Ponteiro para uma struct Tridiag.
 * @param Y  Ponteiro para um vetor solução.
 * @param it Ponteiro para um inteiro.
 * @return real_t A norma L2 do cálculo do sistema linear.
 */
real_t gaussSeidel_3Diag(Tridiag *sl, real_t *Y, int *it);

/**
 * @brief Calcula o sistema linear Ax = B, onde A é uma matriz tridiagonal
 * formada por uma EDO.
 * 
 * @param edo Ponteiro para uma struct EDo.
 * @param Y   Ponteiro para um vetor solução.
 * @param it  Ponteiro para um inteiro.
 * @return real_t A norma L2 do cálculo do sistema linear.
 */
real_t gaussSeidel_EDO(EDo *edo, real_t *Y, int *it);

#endif // __EQDIFF_H__