# kompilator c
CCOMP = gcc
# konsolidator
LOADER = gcc
# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG  -fopenmp -Wall
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3
# pliki naglowkowe
INC =
# biblioteki
LIB = -lm
# zaleznosci i komendy
run: openmp_petle clean
	./openmp_petle
openmp_petle: openmp_petle.o
	$(LOADER) $(OPT) openmp_petle.o -o openmp_petle $(LIB)
# jak uzyskac plik openmp_watki_zmienne.o ?
openmp_petle.o: openmp_petle.c
	$(CCOMP) -c $(OPT) openmp_petle.c $(INC)
clean:
	rm -f *.o
