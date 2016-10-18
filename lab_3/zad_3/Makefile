CCOMP = gcc
LOADER = gcc
OPT = -g -DDEBUG
# OPT = -O3

run: pthreads_detach_kill clean
	./pthreads_detach_kill
pthreads_detach_kill: pthreads_detach_kill.o
	$(LOADER) $(OPT) pthreads_detach_kill.o -o pthreads_detach_kill -pthread
pthreads_detach_kill.o: pthreads_detach_kill.c
	$(CCOMP) -c $(OPT) pthreads_detach_kill.c -pthread
clean:
	rm -f *.o
