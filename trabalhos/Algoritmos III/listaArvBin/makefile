MAIN=GRR20235688
CFLAGS= -Wall -Wextra -pedantic -Wshadow -std=c11

all: $(MAIN)

$(MAIN): clienteArvBin.o tadArvBinInt.o tadFilaApontador.o
	gcc -o $(MAIN) $^ $(CFLAGS) -lm

clienteArvBin.o: clienteArvBin.c
	gcc -c clienteArvBin.c $(CFLAGS)

clean:
	rm -f clienteArvBin.o $(MAIN)
