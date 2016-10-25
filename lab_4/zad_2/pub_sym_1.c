#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

struct Kufle {
  // tab_kufli[] = [0 kufel wolnych] [= 1 kufel zajety]
  pthread_mutex_t *	tab_mut_kuff;
  int * tab_kufli;
  int l_kf;
} kuf;

struct Kran {
  pthread_mutex_t *	tab_mut_kran;
  int * tab_kran;
  int l_kr;
} kra;

void * watek_klient (void * arg_wsk){
  int moj_id = * ((int *)arg_wsk);
  int a, b, i, j, kufel, kran, result;
  a = 0;
  int ile_musze_wypic = 2;
  printf("Klient %d, wchodzi do pubu\n", moj_id);
  for(i=0; i<ile_musze_wypic; i++){
    printf("Klient %d, czeka na kufel\n", moj_id);
    a = 0;
    while(1) {
      if(pthread_mutex_trylock(&kuf.tab_mut_kuff[a]) == 0) {
        kufel = a;
        printf("Klient %d, wybrał kufel %d\n",moj_id,a);
        break;
      } else if(a == kuf.l_kf -1) {
        a = 0;
      } else {
        a++;
      }
    }
    printf("Klient %d, czeka na kran\n", moj_id);
    b = 0;
    while(1) {
      if(pthread_mutex_trylock(&kra.tab_mut_kran[b]) == 0) {
        kran = b;
        printf("Klient %d, wybrał kran %d\n",moj_id,b);
        break;
      } else if (b == kra.l_kr - 1){
        b = 0;
      } else {
        b++;
      }
    }
    printf("Klient %d, nalewam z kranu %d\n", moj_id, kran);
    usleep(300);
    kra.tab_kran[kran] = 0;
    pthread_mutex_unlock(&kra.tab_mut_kran[kran]);
    printf("Klient %d, pije\n", moj_id);
    nanosleep((struct timespec[]){{0, 500000000L}}, NULL);
    printf("Klient %d, odkladam kufel\n", moj_id);
    kuf.tab_kufli[kufel] = 0;
    pthread_mutex_unlock(&kuf.tab_mut_kuff[kufel]);
  }
  printf("Klient %d,!wychodzi z pubu\n", moj_id);
  return(NULL);
}

main(){
  pthread_t *tab_klient;
  int *tab_klient_id;
  int *tab_kufli;
  int l_kl, l_kf, l_kr, i;
  printf("\nLiczba klientow: "); scanf("%d", &l_kl);
  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
  printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  // Przygotowanie klientow
  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t));
  tab_klient_id = (int *) malloc(l_kl*sizeof(int));
  for(i=0;i<l_kl;i++)
  {
    tab_klient_id[i]=i;
  }
  // Przygotowanie kufli
  kuf.tab_kufli = (int *) malloc(l_kf * sizeof(int));
  kuf.tab_mut_kuff = (pthread_mutex_t *) malloc(l_kf * sizeof(pthread_mutex_t));
  kuf.l_kf = l_kf;
  for(i=0;i<l_kf;i++)
  {
    kuf.tab_kufli[i] = 0;
    pthread_mutex_init(&kuf.tab_mut_kuff[i], NULL);
  }
  // Przygotowanie kranow
  kra.tab_kran = (int *) malloc(l_kr * sizeof(int));
  kra.tab_mut_kran = (pthread_mutex_t *) malloc(l_kr * sizeof(pthread_mutex_t));
  kra.l_kr = l_kr;
  for(i=0;i<l_kr;i++)
  {
    kra.tab_kran[i] = 0;
    pthread_mutex_init(&kra.tab_mut_kran[i], NULL);
  }

  printf("\nOtwieramy pub (simple)!\n");
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
