MAIN=clienteArvBin

all: $(MAIN)

$(MAIN): clienteArvBin.c tadArvBinInt.o tadFilaApontador.o
	gcc clienteArvBin.c tadArvBinInt.o tadFilaApontador.o -lm -o $(MAIN)

tadFilaApontador.o: tadFila.c 
	gcc -c $< -o $@

tadArvBinInt.o: tadArvBin.c 
	gcc -c $< -o $@

clean:
	rm -f $(MAIN) *.o *.gch
