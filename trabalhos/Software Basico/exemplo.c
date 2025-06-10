#include <stdio.h>
#include "meuAlocador.h"

int main (int argc, char** argv) {
  (void)argc;
  (void)argv;

  void *a, *b;

  iniciaAlocador();               // Impressão esperada
  imprimeMapa();                  // <vazio>

  a = (void *) alocaMem(10);
  imprimeMapa();                  // ################**********
  b = (void *) alocaMem(4);
  imprimeMapa();                  // ################**********##############****
  liberaMem(a);
  imprimeMapa();                  // ################----------##############****
  liberaMem(b);                   // ################----------------------------
                                  // ou
                                  // <vazio>
  imprimeMapa();
  a = alocaMem(14);
  imprimeMapa();
  finalizaAlocador();
}
