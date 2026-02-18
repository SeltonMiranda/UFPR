CC = gcc
CFLAGS = -O0 -Wall -I$(SRC_DIR)
LFLAGS = -lm

SRC_DIR = src
BUILD_DIR = build

PROG = cgSolver
MODULES = utils    							\
	    		ConjugateGradient     \
					KDMatrix 							\
					LinearSystem   				\
          $(PROG)

OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o,$(MODULES)))
SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c,$(MODULES)))

# Lista de arquivos para distribuição
DISTFILES = $(SRC_DIR)/*.c $(SRC_DIR)/*.h Makefile LEIAME
DISTDIR = smr23

.PHONY: clean purge dist all

$(PROG):  $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

dirs:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) -c $(CFLAGS) $< -o $@

debug: CFLAGS+=-D__DEBUG__
debug: $(PROG)

clean:
	@echo "Limpando sujeira ....."
	@rm -rf core *~ *.bak

purge: clean
	@echo "Fazendo a faxina ....."
	@rm -f a.out $(PROG)
	@rm -rf $(BUILD_DIR)

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
