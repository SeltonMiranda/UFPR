CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm
ENTREGA = theboys-entrega

CC = gcc

# arquivos-objeto
objects = theboys.o lef.o fila.o mundo.o

all: theboys

theboys: $(objects)
	$(CC) -o theboys conjunto.o $(objects) $(LDFLAGS)

lef.o: lef.c
	$(CC) -c $(CFLAGS) lef.c

fila.o: fila.c
	$(CC) -c $(CFLAGS) fila.c

theboys.o: theboys.c missao.h base.h heroi.h
	$(CC) -c $(CFLAGS) theboys.c  

mundo.o: mundo.c mundo.h
	$(CC) -c $(CFLAGS) mundo.c

# arquivo TGZ para entregar
entrega: clean
	mkdir $(ENTREGA)
	cp *.c *.h *.o makefile $(ENTREGA)
	chmod 600 $(ENTREGA)/*
	tar czvf $(ENTREGA).tgz $(ENTREGA)
	rm -rf $(ENTREGA)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

clean:
	rm -f $(objects) theboys

