#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

typedef struct {
    int a;
    double b;
    int c;
} struktura;
void * operacje_na_strukturze(void *arg_wsk) {
    struktura s_l;
    struktura *s_g = (struktura *) arg_wsk;
    s_l.a = s_g->a;
    s_l.b = s_g->b;
    s_l.c = s_g->c;
    s_l.a++;
    s_l.b++;
    s_l.c++;
    printf("Lokalna: a = %d, b = %lf, c = %d\n", s_l.a, s_l.b, s_l.c);
    printf("Globalna: a = %d, b = %lf, c = %d\n\n", s_g->a, s_g->b, s_g->c);
	return(NULL);
}

int main()
{
    struktura s;
    s.a = 1;
    s.b = 2.1;
    s.c = 3;
    void *wynik;
  	int i;
      int n = 10;
      pthread_t *tid = malloc(sizeof(pthread_t) * n);
      int *id = malloc(sizeof(int) * n);
      for(int a = 0; a < n ; a++) {
          id[a] = a;
          pthread_create(&tid[a], NULL, operacje_na_strukturze, (void *)&s); // DODANE
      }
      for(int a = 0; a < n; a++) {
          pthread_join(tid[a], &wynik); // DODANE
      }
    printf("Globalna: a = %d, b = %lf, c = %d\n\n", s_g->a, s_g->b, s_g->c);
  	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}
