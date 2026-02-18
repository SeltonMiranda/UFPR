MAIN=t9
CFLAGS=-Wall -Wextra -pedantic
ENTREGA=smr23-gcn23

.phony: clean purge all entrega

all:$(MAIN)

$(MAIN): t9.o trie.o utils.o
	gcc -o $(MAIN) $^ $(CFLAGS)

%.o: %.c
	gcc -c $< $(CFLAGS)

# Remove *.o
clean:
	rm -f *.o *.gch

# Remove *.o e t9
purge:
	rm -f *.o *.gch $(MAIN) $(ENTREGA).tar.gz

# Cria um arquivo tar.gz para entrega do trabalho
entrega: clean
	@mkdir $(ENTREGA)
	@cp *.c *.h makefile LEIAME $(ENTREGA)
	@tar czvf $(ENTREGA).tar.gz $(ENTREGA)
	@rm -rf $(ENTREGA)
	@echo "Arquivo $(ENTREGA).tar.gz criado\n"
