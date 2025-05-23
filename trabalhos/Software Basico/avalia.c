#include <stdio.h>
#include "meuAlocador.h"
#include <unistd.h>
#include <string.h>

int main (int argc, char** argv) {
  (void)argc;
  (void)argv;

  char *str0 = "\n0)\n";
  char *str1 = "\n1)\n";
  char *str2 = "\n2)\n";
  char *str3 = "\n3)\n";
  char *str4 = "\n4)\n";

  void *a,*b,*c,*d,*e;

  iniciaAlocador(); 

  write(1, str0, strlen(str0));
  imprimeMapa();
  // 0) estado inicial

  write(1, str1, strlen(str1));
  a=(void *) alocaMem(100);
  imprimeMapa();
  b=(void *) alocaMem(130);
  imprimeMapa();
  c=(void *) alocaMem(120);
  imprimeMapa();
  d=(void *) alocaMem(110);
  imprimeMapa();
  // 1) Espero ver quatro segmentos ocupados

  write(1, str2, strlen(str2));
  liberaMem(b);
  imprimeMapa(); 
  liberaMem(d);
  imprimeMapa(); 
  // 2) Espero ver quatro segmentos alternando
  //    ocupados e livres

  write(1, str3, strlen(str3));
  b=(void *) alocaMem(50);
  imprimeMapa();
  d=(void *) alocaMem(90);
  imprimeMapa();
  e=(void *) alocaMem(40);
  imprimeMapa();
  // 3) Deduzam
	
  write(1, str4, strlen(str4));
  liberaMem(c);
  imprimeMapa(); 
  liberaMem(a);
  imprimeMapa();
  liberaMem(b);
  imprimeMapa();
  liberaMem(d);
  imprimeMapa();
  liberaMem(e);
  imprimeMapa();
   // 4) volta ao estado inicial

  finalizaAlocador();
}
