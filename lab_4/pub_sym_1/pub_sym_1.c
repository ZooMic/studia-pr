#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

struct kufle {
  // tab_kufli[] = [0 kufel wolnych] [= 1 kufel zajety]
  pthread_mutex_t *	tab_mut_kuff;
  int * tab_kufli;
  int l_kf;
} kuf;
pthread_mutex_t mut_kran;

void * watek_klient (void * arg_wsk){
  int moj_id = * ((int *)arg_wsk);
  int a, i, j, kufel, result;
  a = 0;
  int ile_musze_wypic = 2;
  printf("\nKlient %d, wchodzÄ do pubu\n", moj_id);
  for(i=0; i<ile_musze_wypic; i++){
    printf("\nKlient %d, wybieram kufel\n", moj_id);
    while(a < kuf.l_kf) {
      //thread_mutex_lock(&kuf.tab_mut_kuff[a]);
      if(kuf.tab_kufli[a] == 0) {
          kuf.tab_kufli[a] = 1;
          kufel = a;
          break;
      } else if(i == kuf.l_kf - 1) {
          a = 0;
      } else {
          i++;
      }
      //pthread_mutex_unlock(&kuf.tab_mut_kuff[a]);
    }
    j=0;
    printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j);
    //thread_mutex_lock(&mut_kran);
    usleep(300);
    //thread_mutex_unlock(&mut_kran);
    printf("\nKlient %d, pije\n", moj_id);
    nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
    printf("\nKlient %d, odkladam kufel\n", moj_id);
    kuf.tab_kufli[kufel] = 0;
  }
  printf("\nKlient %d, wychodzÄ z pubu\n", moj_id);
  return(NULL);
}

main(){
  pthread_t *tab_klient;
  int *tab_klient_id;
  int *tab_kufli;
  int l_kl, l_kf, l_kr, i;
  printf("\nLiczba klientow: "); scanf("%d", &l_kl);
  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  l_kr = 1;
  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++)
  {
    tab_klient_id[i]=i;
  }
  kuf.tab_kufli = (int *) malloc(l_kf * sizeof(int));
  kuf.tab_mut_kuff = (pthread_mutex_t *) malloc(l_kf * sizeof(pthread_mutex_t));
  kuf.l_kf = l_kf;
  for(i=0;i<l_kf;i++)
  {
    kuf.tab_kufli[i] = 0;
    pthread_mutex_init(&kuf.tab_mut_kuff[i], NULL);
  }
  printf("\nOtwieramy pub (simple)!\n");
  pthread_mutex_init(&mut_kran, NULL);
  printf("\nLiczba wolnych kufli %d\n", l_kf);
  for(i=0;i<l_kl;i++)
  {
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
  }
  for(i=0;i<l_kl;i++)
  {
    pthread_join( tab_klient[i], NULL);
  }
  printf("\nZamykamy pub!\n");
}
