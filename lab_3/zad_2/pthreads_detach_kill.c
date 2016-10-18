#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

// rzutowanie przekazanego argumentu
void * wypisywanie_swoich_id(void *arg_wsk) {
    int id;
    id = *((int*) arg_wsk);
    // wywołanie pthread_self
    pthread_t id_self = pthread_self();
    printf("Przekazany ID %d, pthread_self %u\n", id, id_self);
    // printf("Pthread_self %u\n", id_self);
	//pthread_testcancel();
	return(NULL);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	void *wynik;
	int i;
    int n = 10;
    for(int a = 0; a < n ; a++) {
        pthread_create(&tid, NULL, wypisywanie_swoich_id, &a); // DODANE

        // sleep(1); // czas na uruchomienie watku
        // pthread_cancel(tid);
        // if (wynik == PTHREAD_CANCELED)
    	// 	printf("%d KILLED\n", a);
    	// else
    	// 	printf("%d NOT KILLED\n", a);
    }
    //pthread_join(tid, &wynik);
    for(int a = 0; a < n; a++) {
        pthread_join(tid, &wynik); // DODANE
    }
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}
