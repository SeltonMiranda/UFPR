# Nome do executável
MAIN = SpaceImpact

ENTREGA = smr23

# Flags de compilação
ALLEGRO_LIBS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs --cflags)
CFLAGS = -Wall -Wextra -pedantic -g --std=c99 -lm

# Diretórios
SRC_DIR = src
INCLUDE_DIR = includes
BUILD_DIR = build

# Encontrar todos os arquivos fonte e mapear para objetos
SRCS = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all clean entrega

all: clean $(MAIN)

$(MAIN): $(OBJECTS)
	gcc -o $(MAIN) $^ $(ALLEGRO_LIBS) $(CFLAGS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(MAIN) smr23.zip

entrega: clean
	mkdir -p $(ENTREGA)
	cp -r makefile .editorconfig .clang-format LEIA-ME $(SRC_DIR) $(INCLUDE_DIR) assets/ $(ENTREGA)
	zip -r $(ENTREGA).zip $(ENTREGA)
	rm -rf $(ENTREGA)
	@echo "Arquivo $(ENTREGA).zip criado!"