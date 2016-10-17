# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
	$(CCOMP) -c $(OPT) pomiar_czasu.c

clean:
	rm -f *.o
