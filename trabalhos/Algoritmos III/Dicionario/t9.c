/**************************************
 * Arquivo principal que implementa o projeto especificado no enunciado.
 * Autores: Selton Miranda Rolim (GRR20235688) e Gabriel Carloto Nowak (GRR20235686).
***************************************/


#include "trie.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define MAX_TAM 50

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Forneça apenas o arquivo txt.\n");
    return 1;
  }

  FILE *dicionario = fopen(argv[1], "r");
  if (dicionario == NULL) {
    fprintf(stderr, "Não foi possível abrir o arquivo.\n");
    return 1;
  }

  char palavra[MAX_TAM];
  Trie arv;
  criaArv(&arv);
  while (fscanf(dicionario, "%49s", palavra) == 1) {
    arv = insereArv(&arv, palavra);
    if (arv == NULL) {
      destroiArv(arv);
      fclose(dicionario);
      return 1;
    }
  }

  if (ferror(dicionario)) {
    fprintf(stderr, "Não foi possível ler o arquivo.\n");
    destroiArv(arv);
    fclose(dicionario);
    return 1;
  }

  fclose(dicionario);

  char anterior[MAX_TAM * 2], input[MAX_TAM];
  char *busca;
  scanf("%s", input);
  while (strlen(input) != 1 || input[0] != ZERO) {

    if ( !palavraValida(input) ) {
      printf("entrada invalida\n");
    } else {
      if ( input[0] == HASHTAG ) busca = strcat(anterior, input);
      else busca = input;
      
      char *word = buscaPalavra(&arv, busca);
      if (!word)
        printf("palavra nao encontrada\n");
      else
        printf("%s\n", word);
      
      if (busca != anterior) 
        strcpy(anterior, busca);
    }

    scanf("%s", input);
  }

  destroiArv(arv);
  return 0;
}
