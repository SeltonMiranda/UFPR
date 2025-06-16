CC = gcc
CFLAGS = -Wall -Wextra --pedantic

HEADER = meuAlocador.h
MAIN = avalia.c

SRC_V1 = c/meuAlocadorV1.c
SRC_V2 = c/meuAlocadorV2.c
SRC_V3 = c/meuAlocadorV3.c

OBJ_V1 = meuAlocadorV1.o
OBJ_V2 = meuAlocadorV2.o
OBJ_V3 = meuAlocadorV3.o

# Executáveis
EXEC_V1 = programaV1
EXEC_V2 = programaV2
EXEC_V3 = programaV3

# Alvo padrão
# all: $(EXEC_V1) $(EXEC_V2) # $(EXEC_V3)
all: $(EXEC_V3) 

# Compila V1
#$(EXEC_V1): $(OBJ_V1) $(MAIN) 
#	$(CC) $(CFLAGS) -o $@ $^ 
# 
#$(OBJ_V1): $(SRC_V1) $(HEADER)
#	$(CC) $(CFLAGS) -c -o $@ $(SRC_V1)

 # Compila V2
#$(EXEC_V2): $(OBJ_V2) $(MAIN)
#	$(CC) $(CFLAGS) -o $@ $^ 
# 
#$(OBJ_V2): $(SRC_V2) $(HEADER)
#	$(CC) $(CFLAGS) -c -o $@ $(SRC_V2)

 # Compila V3
$(EXEC_V3): $(OBJ_V3) $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ -g
 
$(OBJ_V3): $(SRC_V3) $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $(SRC_V3) -g

# Limpeza
clean:
	rm -f *.o $(EXEC_V1) $(EXEC_V2) $(EXEC_V3) avalia exemplo
