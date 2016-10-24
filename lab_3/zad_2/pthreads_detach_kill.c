#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
void * wypisywanie_swoich_id(void *arg_wsk) {
    int id;
    id = *((int*) arg_wsk);
    pthread_t id_self = pthread_self();
    printf("Przekazany ID %d, pthread_self %u\n", id, id_self);
	return(NULL);
}
int main()
{
	pthread_attr_t attr;
	void *wynik;
	int i;
    int n = 10;
    pthread_t *tid = malloc(sizeof(pthread_t) * n);
    int *id = malloc(sizeof(int) * n);
    for(int a = 0; a < n ; a++) {
        id[a] = a;
        pthread_create(&tid[a], NULL, wypisywanie_swoich_id, &id[a]); // DODANE
    }
    for(int a = 0; a < n; a++) {
        pthread_join(tid[a], &wynik); // DODANE
    }
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}
