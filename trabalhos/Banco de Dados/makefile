CC = gcc
FLAGS = -Wall -Wextra -pedantic --std=c11
MAIN = fdtool

DISTFILES = *.c *.h makefile README relatorio.pdf .clang-format exemplos/
DISTDIR = selton_20235688

MAIN_OBJS = fdtool.o FD.o FDParse.o closure.o candidateKeys.o mincover.o normalForm.o

.PHONY: all purge clean debug format dist

# Target principal
all: $(MAIN)

debug: FLAGS+=-D__DEBUG__
debug: $(MAIN)

# Regra para construir o executável principal
$(MAIN): $(MAIN_OBJS)
				$(CC) $^ -o $@ $(FLAGS) 

%.o: %.c
				$(CC) -c $< -o $@ $(FLAGS)

debug:	FLAGS += -g -D_DEBUG_
debug:	$(MAIN)

clean:
	@echo "Removing object files (*.o, *.gch)"
	rm -f *.o *.gch

purge: clean
	@echo "Removing executables ($(MAIN))"
	rm -f $(MAIN) 

dist: purge
	@echo "Gerando arquivo .tar.gz -> ($(DISTDIR).tar.gz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tar.gz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)

format:
	find . -regex '.*\.\(c\|h\)$ ' -exec clang-format -i {} \;
