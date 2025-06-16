
SOURCE = meuAlocadorV1.s
OBJECT = $(SOURCE:.s=.o)

MAIN = exemplo.c
OBJECT_MAIN = $(MAIN:.c=.o)

EXECUTABLE = alocador

all:
	as $(SOURCE) -o $(OBJECT) -g
	gcc -c ../$(MAIN) -g
	gcc -o $(EXECUTABLE) $(OBJECT_MAIN) $(OBJECT) -g
	
clean:
	rm -rf *.o

purge:
	rm -rf *.o $(EXECUTABLE)