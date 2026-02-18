#include <stdio.h>
#include <string.h>

#include "FD.h"
#include "FDParse.h"
#include "candidateKeys.h"
#include "closure.h"
#include "mincover.h"
#include "normalForm.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    printf("USAGE: ./%s closure --fds <arquivo.fds> --X <ATRIBUTOS>\n",
           argv[0]);
    printf("USAGE: ./%s mincover --fds <arquivo.fds>\n", argv[0]);
    printf("USAGE: ./%s keys --fds <arquivo.fds>\n", argv[0]);
    printf("USAGE: ./%s normalform --fds <arquivo.fds>\n", argv[0]);
    return 1;
  }

  char*  cmd       = argv[1];
  char*  file_path = argv[3];
  FDList list;

  parse(file_path, &list);

#ifdef _DEBUG_
  print_debug(&list);
  print_attr_debug(universe);
#endif

  if (strcmp(cmd, "closure") == 0)
  {
    if (argc != 6)
    {
      printf("ERROR! Must have <ATRIBUTOS>\n");
      return 1;
    }

    char*      str_attr   = argv[5];
    attributes closureSet = {0};
    strToAttr(str_attr, closureSet);

    closure(&list, closureSet);
    char* str = attrToStr(closureSet);
    printf("%s\n", str);
  }

  if (strcmp(cmd, "mincover") == 0)
  {
    mincover(&list);
    print_fds(&list);
  }

  if (strcmp(cmd, "keys") == 0)
  {
    int         keys_count;
    attributes* cKeys = candidateKeys(&list, &keys_count);
    print_candidate_keys(cKeys, keys_count);
  }

  if (strcmp(cmd, "normalform") == 0)
  {
    normalform(&list);
  }

  return 0;
}