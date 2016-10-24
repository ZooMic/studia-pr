#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

void * watek_klient (void * arg_wsk){
  printf("Hello World!\n");
  return(NULL);
}

main(){
  int l_kl, l_kf, i;
  printf("\nLiczba klientow: "); scanf("%d", &l_kl);
  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  pthread_t *tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  int *tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++)
  {
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
  }
  for(i=0;i<l_kl;i++)
  {
    pthread_join( tab_klient[i], NULL);
  }
}
