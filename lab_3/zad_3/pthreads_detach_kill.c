#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

typedef struct {
    int a;
    double b;
    int c;
} struktura;


void * operacje_na_strukturze(void *arg_wsk) {
    struktura s_lokalna;
    s_lokalna.a = 10;
    s_lokalna.b = 21;
    s_lokalna.c = 30;
    struktura *s_wsk = (struktura *) arg_wsk;
    printf("Watek: s_lokalna.a = %d, s_lokalna.b = %lf, s_lokalna.c = %d\n", s_lokalna.a, s_lokalna.b, s_lokalna.c);
    printf("Zewne: s_wsk->a = %d, s_wsk->b = %lf, s_wsk->c = %d\n\n", s_wsk->a, s_wsk->b, s_wsk->c);
	return(NULL);
}

int main()
{
    struktura s;
    s.a = 1;
    s.b = 2.1;
    s.c = 3;

	pthread_t tid;
	pthread_attr_t attr;
	void *wynik;
	int i;
    int n = 10;
    for(int a = 0; a < n ; a++) {
        pthread_create(&tid, NULL, operacje_na_strukturze, (void *)&s); // DODANE
        //sleep(1); // czas na uruchomienie watku
        // pthread_cancel(tid);
        // if (wynik == PTHREAD_CANCELED)
    	// 	printf("%d KILLED\n", a);
    	// else
    	// 	printf("%d NOT KILLED\n", a);
    }
    for(int a = 0; a < n; a++) {
        pthread_join(tid, &wynik); // DODANE
    }
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}
