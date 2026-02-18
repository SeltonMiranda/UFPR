#include "candidateKeys.h"
#include "closure.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 32
#define KEYS_SIZE QUEUE_SIZE

/**
 * @brief Esta estrutura define um nó de uma fila.
 */
typedef struct Node
{
  /**
   * @var Conjunto de atributos.
   */
  attributes attrs;

  /**
   * @var Ponteiro para próximo nó.
   */
  struct Node* next;
} Node;

/**
 * @brief Esta estrutura define uma fila. Usada para
 * encontrar as chaves candidatas usando BFS.
 */
typedef struct Queue
{
  /**
   * var Ponteiro para o início da fila;
   */
  struct Node* front;

  /**
   * var Ponteiro para o final da fila;
   */
  struct Node* back;
} Queue;

/*************************************************************************************
 ******************************* PRIVATE FUNCTIONS ***********************************
 *************************************************************************************/

/**
 * @brief Inicializa uma fila.
 *
 * @param q Uma fila.
 */
static void queue_init(Queue* q);

/**
 * @brief Verifica se uma fila está vazia.
 *
 * @param q Uma fila.
 */
static bool queue_empty(Queue* q);

/**
 * @brief Enfileira um conjunto de atributos numa fila.
 *
 * @param q Uma fila.
 * @param attrSet Conjunto de atributos.
 */
static void enqueue(Queue* q, attributes attrSet);

/**
 * @brief Retira um conjunto de atributos de uma fila.
 *
 * @param q Uma fila.
 * @param out Conjunto de atributos (saída).
 */
static void dequeue(Queue* q, attributes out);

/**
 * @brief Verifica se conjunto a é um subconjunto do conjunto b.
 *
 * @param a Conjunto de atributos.
 * @param b Conjunto de atributos.
 * @return True, caso a seja subconjunto de b, False, caso contrário.
 */
static bool isSubset(attributes a, attributes b);

/**
 * @brief Verifica se o conjunto a é coberto pelo fecho.
 *
 * @param a Conjunto de atributos.
 * @param closure Conjunto de atributos.
 * @return True, caso a seja coberto pelo fecho, False, caso contrário.
 */
static bool isCoveredByClosure(attributes a, attributes closure);

static void queue_init(Queue* q)
{
  q->back  = NULL;
  q->front = NULL;
}

static bool queue_empty(Queue* q)
{
  return q->front == NULL;
}

static void enqueue(Queue* q, attributes attrSet)
{
  Node* node = (Node*)malloc(sizeof(Node));
  if (node == NULL)
  {
    printf("ERROR! Couldn't allocate memory for Queue Node at file %s at line "
           "%d\n",
           __FILE__, __LINE__);
    exit(1);
  }
  memcpy(node->attrs, attrSet, sizeof(attributes));
  node->next = NULL;

  if (q->back == NULL)
  {
    q->front = q->back = node;
  }
  else
  {
    q->back->next = node;
    q->back       = node;
  }
}

static void dequeue(Queue* q, attributes out)
{
  if (q->front == NULL)
  {
    return;
  }

  Node* temp = q->front;
  memcpy(out, temp->attrs, sizeof(attributes));
  q->front = temp->next;
  if (q->front == NULL)
  {
    q->back = NULL;
  }
  free(temp);
}

static bool isSubset(attributes a, attributes b)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (a[i] && !b[i])
    {
      return false;
    }
  }
  return true;
}

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

/*************************************************************************************
 ******************************* PUBLIC FUNCTIONS ***********************************
 *************************************************************************************/

attributes* candidateKeys(FDList* list, int* keys_count)
{
  attributes essentials = {0};
  attributes rhs        = {0};

  for (size_t i = 0; i < list->size; i++) // f.u²
  {
    for (size_t j = 0; j < ALPHABET_SIZE; j++)
    {
      if (list->fds[i].rhs[j])
      {
        rhs[j] = true;
      }
    }
  }

  for (size_t i = 0; i < ALPHABET_SIZE; i++)
  {
    if (universe[i] && !rhs[i])
    {
      essentials[i] = true;
    }
  }

  Queue q;
  queue_init(&q);
  enqueue(&q, essentials);

  int         key_count = 0;
  int         keys_size = KEYS_SIZE;
  attributes* keys      = malloc(sizeof(attributes) * keys_size);
  if (keys == NULL)
  {
    printf("ERROR! Couldn't allocate memory to candidate keys array at file %s "
           "at line %d\n",
           __FILE__, __LINE__);
    exit(1);
  }

  while (!queue_empty(&q))
  {
    attributes current    = {0};
    attributes closureSet = {0};

    dequeue(&q, current);
    memcpy(closureSet, current, sizeof(attributes));

    closure(list, closureSet);

    bool isSuperKey = true;
    if (!isCoveredByClosure(universe, closureSet))
    {
      isSuperKey = false;
    }

    if (isSuperKey)
    {
      bool isKeyMinimum = true;
      for (int i = 0; i < key_count; i++)
      {
        if (isSubset(keys[i], current))
        {
          isKeyMinimum = false;
        }
      }

      if (isKeyMinimum)
      {
        memcpy(keys[key_count], current, sizeof(attributes));
        key_count++;
        if (key_count >= keys_size)
        {
          keys_size *= 2;
          keys = realloc(keys, sizeof(attributes) * keys_size);
        }
      }

      continue;
    }

    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
      if (!universe[i] || current[i])
      {
        continue;
      }

      attributes next = {0};
      memcpy(next, current, sizeof(attributes));
      next[i] = true;

      bool isAlreadySuperKey = false;
      for (int j = 0; j < key_count; j++)
      {
        if (isSubset(keys[j], next))
        {
          isAlreadySuperKey = true;
        }
      }

      if (!isAlreadySuperKey)
      {
        enqueue(&q, next);
      }
    }
  }

  *keys_count = key_count;
  return keys;
}

void print_candidate_keys(attributes* cKeys, int keys_count)
{
  for (int i = 0; i < keys_count; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (cKeys[i][j] == true)
      {
        printf("%c", 'A' + j);
      }
    }
    printf("\n");
  }
}