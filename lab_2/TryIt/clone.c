#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
  int zmienna_lokalna = 0;
  for(int i = 0; i < 1000000; i++) {
      zmienna_globalna++;
      zmienna_lokalna++;
  }
  printf("Zminna_lokalna: %d\n",zmienna_lokalna);
  printf("Zminna_globalna: %d\n",zmienna_globalna);
  return 0;
}

main()
{

  void *stos;
  void *stos2;
  pid_t pid, pid2;
  int i;

  stos = malloc( ROZMIAR_STOSU );
  stos2 = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
  if (stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu2\n");
    exit( 1 );
  }
  pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU,
   CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
  pid2 = clone( &funkcja_watku, (void *) stos2+ROZMIAR_STOSU,
    CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );

  waitpid(pid, NULL, __WCLONE);
  waitpid(pid2, NULL, __WCLONE);

  free( stos );
  free( stos2 );
}
