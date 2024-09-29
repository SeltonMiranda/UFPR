# Executável
MAIN=LBP

# FLAGS de compilação
CFLAGS= -Wall -Wextra --std=c17 -lm

# Diretórios
SRC_DIR = src
INCLUDE_DIR = includes
BUILD_DIR = build

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objetos
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))


all: $(MAIN)

$(MAIN): $(OBJECTS)
	gcc -o $@ $^ $(CFLAGS) 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	gcc -o $@ -c $< -I$(INCLUDE_DIR) $(CFLAGS)

clean:
	rm -rf $(MAIN) $(BUILD_DIR) *.o *.gch

.phony: clean all
