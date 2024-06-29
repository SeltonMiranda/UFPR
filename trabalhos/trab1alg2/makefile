parametrosCompilacao=-Wall -g #-Wshadow
nomePrograma=trab1grr20235688

all: $(nomePrograma)

$(nomePrograma): main.o ordenacao.o auxFunctions.o
	gcc -o $(nomePrograma) main.o ordenacao.o auxFunctions.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: ordenacao.h ordenacao.c 
	gcc -c ordenacao.c $(parametrosCompilacao)

auxFunctions.o: auxFunctions.h auxFunctions.c
	gcc -c auxFunctions.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
