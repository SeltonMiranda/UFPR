#include "normalForm.h"
#include "FDParse.h"
#include "candidateKeys.h"
#include "closure.h"
#include "mincover.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VIOLATIONS_LIST_SIZE 64

/*************************************************************************************
 ******************************* PRIVATE FUNCTIONS ***********************************
 *************************************************************************************/

/**
 * @brief Verifica se o conjunto de atributos a é igual ao conjunto b.
 *
 * @param a Conjunto de atributos.
 * @param b Conjunto de atributos.
 * @return True caso sejam iguais, False, caso contrário.
 */
static bool equals(attributes a, attributes b);

static bool equals(attributes a, attributes b)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

/*************************************************************************************
 ******************************* PUBLIC FUNCTIONS ***********************************
 *************************************************************************************/

void normalform(FDList* list)
{
  mincover(list);

  int         keys_count = 0;
  attributes* keys       = candidateKeys(list, &keys_count);

  attributes primeAttr = {0};
  for (size_t i = 0; i < (size_t)keys_count; i++)
  {
    for (size_t j = 0; j < ALPHABET_SIZE; j++)
    {
      if (keys[i][j])
      {
        primeAttr[j] = true;
      }
    }
  }

  attributes BCNFViolationsList[VIOLATIONS_LIST_SIZE];
  int        BCNF_RHS[VIOLATIONS_LIST_SIZE];
  int        BCNFCount = 0;

  attributes _3FNViolationsList[VIOLATIONS_LIST_SIZE];
  int        _3FN_RHS[VIOLATIONS_LIST_SIZE];
  int        _3FNCount = 0;

  for (size_t i = 0; i < list->size; i++)
  {
    FD  fd = list->fds[i];
    int rhsIdx;

    for (size_t j = 0; j < ALPHABET_SIZE; j++)
    {
      if (fd.rhs[j])
      {
        rhsIdx = j;
      }
    }

    // ignora FD's triviais
    if (fd.lhs[rhsIdx])
    {
      continue;
    }

    attributes closureSet = {0};
    memcpy(closureSet, fd.lhs, sizeof(attributes));
    closure(list, closureSet);

    bool isSuperkey = equals(closureSet, universe);
    bool rhsIsPrime = primeAttr[rhsIdx];

    if (!isSuperkey)
    {
      memcpy(BCNFViolationsList[BCNFCount], fd.lhs, sizeof(attributes));
      BCNF_RHS[BCNFCount] = rhsIdx;
      BCNFCount++;
    }

    if (!isSuperkey && !rhsIsPrime)
    {
      memcpy(_3FNViolationsList[_3FNCount], fd.lhs, sizeof(attributes));
      _3FN_RHS[_3FNCount] = rhsIdx;
      _3FNCount++;
    }
  }

  if (BCNFCount > 0)
  {
    printf("BCNF: VIOLATIONS\n");
  }

  if (_3FNCount > 0)
  {
    printf("3NF: VIOLATIONS\n");
  }

  for (int i = 0; i < BCNFCount; i++)
  {
    printf("VIOLATION BCNF: %s->%c (%s not superkey)\n",
           attrToStr(BCNFViolationsList[i]), 'A' + BCNF_RHS[i],
           attrToStr(BCNFViolationsList[i]));
  }

  for (int i = 0; i < _3FNCount; i++)
  {
    printf("VIOLATION 3NF: %s->%c (%c not prime, %s not superkey)\n",
           attrToStr(_3FNViolationsList[i]), 'A' + _3FN_RHS[i],
           'A' + _3FN_RHS[i], attrToStr(_3FNViolationsList[i]));
  }

  free(keys);
}
