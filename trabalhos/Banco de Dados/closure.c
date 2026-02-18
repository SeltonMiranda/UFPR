#include "closure.h"

#include "string.h"

/*************************************************************************************
 ******************************* PRIVATE FUNCTIONS ***********************************
 *************************************************************************************/

/**
 * @brief Verifica se os atributos do lado esquerdo estão contidos
 * no fecho.
 *
 * @param lhs Conjunto de atributos.
 * @param closure Fecho de um conjunto.
 * @return True, caso esteja contido, False, caso contrário.
 */
static bool isLhsInClosure(attributes lhs, attributes closure);

static bool isLhsInClosure(attributes lhs, attributes closure)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (lhs[i] == true && closure[i] == false)
    {
      return false;
    }
  }
  return true;
}

/*************************************************************************************
 ******************************* PUBLIC FUNCTIONS ***********************************
 *************************************************************************************/

void closure(FDList* list, attributes closureSet)
{
  bool closureHasIncreased;
  do
  {
    closureHasIncreased = false;
    for (size_t i = 0; i < list->size; i++)
    {
      FD fd = list->fds[i];
      if (isLhsInClosure(fd.lhs, closureSet))
      {
        for (size_t j = 0; j < ALPHABET_SIZE; j++)
        {
          if (fd.rhs[j] && !closureSet[j])
          {
            closureSet[j]       = true;
            closureHasIncreased = true;
          }
        }
      }
    }
  } while (closureHasIncreased);
}
