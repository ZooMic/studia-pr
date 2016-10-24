#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int zmienna_globalna=0;

int main(int argc, char *argv[]){

  int pid, wynik, i;
  if(zmienna_globalna == 0) {
      inicjuj_czas();
  }
  for(i=0;i<1000;i++){

    pid = fork();

    if(pid==0){

      zmienna_globalna++;
      wynik=execv("./program", (char *)0);
       if(wynik==-1) {
            printf("Proces potomny nie wykonal programu\n");
       } else {
           printf("WORKS");
           wait(NULL);
       }

      exit(0);

    } else {

      wait(NULL);

    }
  }
  printf("Fork() - tworzenie procesow potomnych");
  drukuj_czas();

}
