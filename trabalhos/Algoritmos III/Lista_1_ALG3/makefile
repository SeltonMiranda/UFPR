MAIN=clienteArvBin

all: $(MAIN)

$(MAIN): clienteArvBin.c tadArvBinInt.o tadFilaApontador.o
	gcc clienteArvBin.c tadArvBinInt.o tadFilaApontador.o -lm -o $(MAIN)

tadFilaApontador.o: tadFila.c fila.h itemApontador.h
	gcc -c $< -o $@

tadArvBinInt.o: tadArvBin.c fila.h itemInt.h
	gcc -c $< -o $@

clean:
	rm -f $(MAIN) *.o *.gch
