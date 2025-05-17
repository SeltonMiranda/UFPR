#include "meuAlocador.h"

int main() {
  void *a;
  void *b;
  
  iniciaAlocador();
  imprimeMapa();

  a = (void *)alocaMem(10);
  imprimeMapa();
  b = (void *)alocaMem(4);
  imprimeMapa();
  liberaMem(a);
  imprimeMapa();
  liberaMem(b);
  imprimeMapa();
  

  finalizaAlocador();
  return 0;
}