#ifndef __FD__
#define __FD__

#include <stdbool.h>
#include <stddef.h>

#define ALPHABET_SIZE 26

/**
 * @brief Estrutura que define um conjunto de atributos de uma relação.
 */
typedef bool      attributes[ALPHABET_SIZE];
extern attributes universe;

/**
 * @brief Estrutura que define uma dependencia funcional.
 */
typedef struct fd_t
{
  /**
   * @var Atributos do lado esquerdo da FD.
   */
  attributes lhs;

  /**
   * @var Atributos do lado direito da FD.
   */
  attributes rhs;
} FD;

/**
 * @brief Estrutura que define uma lista de dependencias funcionais.
 */
typedef struct fd_list_t
{
  /**
   * @var Vetor dinâmico de dependencias funcionais.
   */
  FD* fds;

  /**
   * @var Tamanho do vetor.
   */
  size_t size;
} FDList;

#endif // __FD__