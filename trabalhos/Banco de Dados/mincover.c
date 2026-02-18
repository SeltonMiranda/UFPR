#include "mincover.h"
#include "closure.h"

#include <stdlib.h>
#include <string.h>

#define PADDING 64

/*************************************************************************************
 ******************************* PRIVATE FUNCTIONS ***********************************
 *************************************************************************************/

/**
 * @brief Verifica se o conjunto a é coberto pelo fecho.
 *
 * @param a Conjunto de atributos.
 * @param closure Conjunto de atributos.
 * @return True, caso a seja coberto pelo fecho, False, caso contrário.
 */
static bool isCoveredByClosure(attributes a, attributes closure);

/**
 * @brief Desmembra o lado direito das dependencias funcionais.
 *
 * @param oldList Lista de dependencias funcionais.
 * @param newList Lista de dependencias funcionais.
 */
static void disjointFD(FDList* oldList, FDList* newList);

/**
 * @brief Retira atributos estranhos de uma dependencia funcional.
 *
 * @param list Lista de dependencias funcionais.
 */
static void removeAwkwardAttr(FDList* list);

/**
 * @brief Retira dependencias funcionais redundantes.
 *
 * @param list Lista de dependencias funcionais.
 */
static void removeRedundantFD(FDList* list);

static bool isCoveredByClosure(attributes a, attributes closure)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (a[i] && !closure[i])
    {
      return false;
    }
  }
  return true;
}

static void disjointFD(FDList* oldList, FDList* newList)
{
  for (size_t i = 0; i < oldList->size; i++)
  {
    FD fd = oldList->fds[i];
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
      if (fd.rhs[i])
      {
        FD newfd = {0};
        memcpy(newfd.lhs, fd.lhs, sizeof(fd.lhs));
        newfd.rhs[i] = true;

        newList->fds[newList->size] = newfd;
        newList->size++;
      }
    }
  }
}

static void removeAwkwardAttr(FDList* list)
{
  for (size_t i = 0; i < list->size; i++)
  {
    FD* fd = &list->fds[i];
    for (size_t j = 0; j < ALPHABET_SIZE; j++)
    {
      if (fd->lhs[j])
      {
        attributes temp = {0};
        memcpy(temp, fd->lhs, sizeof(attributes));
        temp[j] = false;

        attributes closureSet = {0};
        memcpy(closureSet, temp, sizeof(attributes));
        closure(list, closureSet);

        bool awkward = true;
        if (!isCoveredByClosure(fd->rhs, closureSet))
        {
          awkward = false;
        }

        if (awkward)
        {
          fd->lhs[j] = false;
        }
      }
    }
  }
}

static void removeRedundantFD(FDList* list)
{
  for (size_t i = 0; i < list->size; i++)
  {
    FD     fd = list->fds[i];
    FDList temp;
    temp.size = list->size - 1;
    temp.fds  = malloc(sizeof(FD) * temp.size);

    int count = 0;
    for (size_t j = 0; j < list->size; j++)
    {
      if (i != j)
      {
        temp.fds[count] = list->fds[j];
        count++;
      }
    }

    attributes closureSet = {0};
    memcpy(closureSet, fd.lhs, sizeof(attributes));
    closure(&temp, closureSet);

    bool redundant = true;
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (!isCoveredByClosure(fd.rhs, closureSet))
      {
        redundant = false;
      }
    }

    if (redundant)
    {
      list->fds[i] = list->fds[list->size - 1];
      list->size--;
      i--;
    }

    free(temp.fds);
  }
}

/*************************************************************************************
 ******************************* PUBLIC FUNCTIONS ***********************************
 *************************************************************************************/

void mincover(FDList* list)
{
  FDList new_list;
  new_list.fds  = malloc(sizeof(FD) * (list->size + PADDING));
  new_list.size = 0;

  disjointFD(list, &new_list);

  free(list->fds);
  list->fds  = new_list.fds;
  list->size = new_list.size;

  removeAwkwardAttr(list);
  removeRedundantFD(list);
}