CCOMP = gcc
LOADER = gcc
OPT = -g -DDEBUG
# OPT = -O3

run: pub_sym_1 clean
	./pub_sym_1
pthreads_detach_kill: pub_sym_1.o
	$(LOADER) $(OPT) pub_sym_1.o -o pub_sym_1 -pthread
pthreads_detach_kill.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c -pthread
clean:
	rm -f *.o
