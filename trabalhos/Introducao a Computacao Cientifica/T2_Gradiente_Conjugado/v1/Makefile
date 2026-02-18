CC = gcc
CFLAGS = -Wall -I$(SRC_DIR) -O3 -march=native -mavx -fopt-info-vec -I$(LIKWID_INCLUDE)
LFLAGS = -lm -L$(LIKWID_LIB) -llikwid

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
DISTFILES = $(SRC_DIR)/*.c $(SRC_DIR)/*.h Makefile LEIAME .clang-format
DISTDIR = smr23

.PHONY: clean purge dist all test format likwid

$(PROG):  $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

dirs:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) -c $(CFLAGS) $< -o $@

debug: CFLAGS+=-D__DEBUG__
debug: $(PROG)

likwid: CFLAGS+=-DLIKWID_PERFMON
likwid: $(PROG)

###### TESTS ######

TEST_NAME = run_tests
TEST_SRC = test/test.c
TEST_OBJ = $(BUILD_DIR)/test.o
TEST_OBJS = $(TEST_OBJ) $(filter-out $(BUILD_DIR)/$(PROG).o, $(OBJS))

$(TEST_OBJ): $(TEST_SRC) | dirs
	$(CC) -c $(CFLAGS) $< -o $@

$(TEST_NAME): $(TEST_OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

test: $(TEST_NAME)
	@clear
	@./$(TEST_NAME)

###### TESTS ######

clean:
	@echo "Limpando sujeira ....."
	@rm -rf $(TEST_OBJ) core *~ *.bak

purge: clean
	@echo "Fazendo a faxina ....."
	@rm -f a.out $(PROG) $(TEST_NAME)
	@rm -rf $(BUILD_DIR)

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)

format:
	find . -regex '.*\.\(c\|h\)$ ' -exec clang-format -i {} \;