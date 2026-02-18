#include "FDParse.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define charToIndex(c) ((c) - 'A')
#define idxToChar(idx) ((idx) + 'A')

static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*************************************************************************************
 ******************************* PRIVATE FUNCTIONS ***********************************
 *************************************************************************************/

/**
 * @brief Verifica se um dado caractere pertence ao alfabeto.
 *
 * @param c Um caractere.
 * @return True caso pertença, False, caso contrário.
 */
static bool isInAlphabet(char c);

/**
 * @brief Lê um arquivo e armazena num buffer.
 *
 * @param path Caminho para o arquivo.
 * @return Um buffer com o conteúdo do arquivo.
 */
static char* read_file(char* path);

/**
 * @brief Pré-computa o tamanho da lista de dependencias funcionais.
 *
 * @param content O conteúdo do arquivo.
 * @return A quantidade de dependencias funcionais.
 */
static int preComputeLength(char* content);

/**
 * @brief Verifica se o caractere pertence ao universo da relação.
 *
 * @param c Um caractere.
 * @return True, caso pertença, False, caso contrário.
 */
static bool isInUniverse(char c);

static bool isInAlphabet(char c)
{
  size_t len = strlen(alphabet);
  for (size_t i = 0; i < len; i++)
  {
    if (alphabet[i] == c)
    {
      return true;
    }
  }
  return false;
}

static char* read_file(char* path)
{
  FILE*  f = fopen(path, "rb");
  size_t bufflen;
  char*  buffer;

  if (!f)
  {
    printf("ERROR! Couldn't open file %s\n", path ? "" : path);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  bufflen = ftell(f);
  rewind(f);

  buffer = (char*)malloc(bufflen + 1);
  if (!buffer)
  {
    printf("ERROR! Couldn't allocate memory for buffer at %s in line %d\n",
           __FILE__, __LINE__);
    exit(1);
  }

  size_t bytes_read  = fread(buffer, 1, bufflen, f);
  buffer[bytes_read] = '\0';
  fclose(f);

  return buffer;
}

static int preComputeLength(char* content)
{
  char* ptr   = strstr(content, "F");
  int   count = 0;
  if (!ptr)
  {
    printf("ERROR! List of functional dependencies doesn't exists\n");
    exit(1);
  }

  // Caso haja um atributo F não queremos ele
  while (ptr)
  {
    char* tmp = ptr + 1;
    while (*tmp == ' ')
    {
      tmp++;
    }

    if (*tmp == '=')
    {
      break;
    }
    ptr = strstr(ptr + 1, "F");
  }

  while (*ptr && *ptr != '}')
  {
    if (ptr[0] == '-' && ptr[1] == '>')
    {
      count++;
      ptr += 2;
    }
    else
    {
      ptr++;
    }
  }

  return count;
}

static bool isInUniverse(char c)
{
  return universe[charToIndex(c)];
}

/*************************************************************************************
 ******************************* PUBLIC FUNCTIONS ************************************
 *************************************************************************************/

void parse(char* path, FDList* list)
{
  char* content  = read_file(path);
  int   i        = 0;
  int   fd_count = 0;
  char  c        = content[i];

  list->size = preComputeLength(content);
  list->fds  = (FD*)malloc(sizeof(FD) * list->size);
  if (!list->fds)
  {
    fprintf(stderr, "ERROR! Couldn't allocate memory for list of functional "
                    "dependencies\n");
    exit(1);
  }

  while (c != '\0')
  {
    if (c == '#') // Pular comentários
    {
      while (content[i] != '\n' && content[i] != '\0')
      {
        i++;
      }
    }
    else if (c == 'U')
    {
      while (content[i] != '{' && content[i] != '\0')
      {
        i++;
      }
      i++; // Pula '{'

      while (content[i] != '}' && content[i] != '\0')
      {
        if (isInAlphabet(content[i]))
        {
          universe[charToIndex(content[i])] = true;
        }
        i++;
      }
    }
    else if (c == 'F')
    {
      while (content[i] != '{' && content[i] != '\0')
      {
        i++;
      }
      i++; // Pula '{'

      while (content[i] != '}' && content[i] != '\0')
      {
        attributes lhs = {0};
        attributes rhs = {0};

#ifdef _DEBUG_
        printf("content[i]: %c, %d, %s\n", content[i], __LINE__, __FILE__);
#endif

        while ((content[i] != '-' && content[i] != '\0'))
        {
          if (isInAlphabet(content[i]))
          {
            if (!isInUniverse(content[i]))
            {
              fprintf(stderr,
                      "ERROR! Attribute <%c> doesn't belongs to relation U\n",
                      content[i]);
              exit(1);
            }
            lhs[charToIndex(content[i])] = true;
          }
          i++;
        }

        if (content[i] == '-' && content[i + 1] == '>')
        {
          i += 2;
        }

        while (isspace(content[i]))
          i++;

#ifdef _DEBUG_
        printf("content[i]: %c, line: [%d], at file %s\n", content[i], __LINE__,
               __FILE__);
#endif
        // while ((content[i] != ',' || content[i] == ';') && content[i] != '}'
        // && content[i] != '\0')
        while (content[i] != ',' && content[i] != ';' && content[i] != '}' &&
               content[i] != '\0')
        {
          if (isalpha(content[i]) &&
              (!isInAlphabet(content[i]) || !isInUniverse(content[i])))
          {
            fprintf(stderr,
                    "ERROR! Attribute <%c> doesn't belongs to relation U or "
                    "doesn't exists\n",
                    content[i]);
            exit(1);
          }
          rhs[charToIndex(content[i])] = true;
          i++;
        }

        memcpy(&list->fds[fd_count].lhs, lhs, sizeof(attributes));
        memcpy(&list->fds[fd_count].rhs, rhs, sizeof(attributes));
        fd_count++;

        if (content[i] == ',' || content[i] == ';')
        {
          i++;
        }
      }
    }

    i++;
    c = content[i];
  }
}

void strToAttr(char* str_attr, attributes set)
{
  for (size_t i = 0; i < strlen(str_attr); i++)
  {
    set[charToIndex(str_attr[i])] = true;
  }
}

char* attrToStr(attributes set)
{
  int len = 0;
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (set[i] == true)
    {
      len++;
    }
  }

  char* str = (char*)malloc(len + 1);
  memset(str, 0, len + 1);

  len = 0;
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (set[i] == true)
    {
      str[len] = idxToChar(i);
      len++;
    }
  }

  return str;
}

void print_fds(FDList* list)
{
  for (size_t i = 0; i < list->size; i++)
  {
    FD _fd = list->fds[i];
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (_fd.lhs[j] == true)
      {
        printf("%c", 'A' + j);
      }
    }
    printf("->");
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (_fd.rhs[j] == true)
      {
        printf("%c", 'A' + j);
      }
    }
    printf("\n");
  }
}

/*************************************************************************************
 ******************************* DEBUG FUNCTIONS *************************************
 *************************************************************************************/

void print_debug(FDList* list)
{
  for (size_t i = 0; i < list->size; i++)
  {
    FD _fd = list->fds[i];
    printf("lhs\n");
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
      printf("%c: %s\n", 'A' + i, _fd.lhs[i] == 1 ? "true" : "false");
    }

    printf("\nrhs\n");
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
      printf("%c: %s\n", 'A' + i, _fd.rhs[i] == 1 ? "true" : "false");
    }
    printf("--------------------\n");
  }
}

void print_attr_debug(attributes attr)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (attr[i])
    {
      printf("%c: %s\n", i + 'A', attr[i] == true ? "true" : "false");
    }
  }
}