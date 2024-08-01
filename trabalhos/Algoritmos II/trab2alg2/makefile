parametrosCompilacao=-Wall -Wextra -pedantic -Wshadow
nomePrograma=trab2grr20235688

all: $(nomePrograma)

$(nomePrograma): main.o ordenacao.o auxFunc.o pilha.o teste.o
	gcc -o $(nomePrograma) main.o ordenacao.o auxFunc.o pilha.o teste.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: ordenacao.h ordenacao.c
	gcc -c ordenacao.c $(parametrosCompilacao)

auxFunc.o: auxFunc.h auxFunc.c
	gcc -c auxFunc.c $(parametrosCompilacao)

pilha.o: pilha.h pilha.c
	gcc -c pilha.c $(parametrosCompilacao)

teste.o: teste.c teste.h 
	gcc -c teste.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
