CCOMP = gcc
LOADER = gcc
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
#OPT = -O3
INC = -lpthread
LIB = -L../pomiar_czasu -lpomiar_czasu -lm
run: fork
	./fork
fork: fork.o
	$(LOADER) $(OPT) fork.o -o fork $(LIB)
fork.o: fork.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC)
clean:
	rm -f *.o
