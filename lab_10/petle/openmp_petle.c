#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10
double a[WYMIAR][WYMIAR];
int c[WYMIAR][WYMIAR];
int d[WYMIAR][WYMIAR];

void wierszowo() {
    printf("\n");
    int i, j;
    for(i = 0; i < WYMIAR; i++) for(j = 0; j < WYMIAR; j++) c[i][j] = -1;
    double suma = 0.0;
    #pragma omp parallel for default(none) private(j) shared(suma, a, c)
    for(i = 0; i < WYMIAR; i++) {
        for(j = 0; j < WYMIAR; j++) {
            #pragma omp atomic
            suma += a[i][j];
            c[i][j] = omp_get_thread_num();
        }
    }

    printf("Suma wyrazow tablicy(wierszowo): %lf\n", suma);
    for(i = 0; i < WYMIAR; i++) {
        for(j = 0; j < WYMIAR; j++) {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void kolumnowo_redux() {
    printf("\n");
    int i, j;
    for(i = 0; i < WYMIAR; i++) for(j = 0; j < WYMIAR; j++) c[i][j] = -1;
    double suma = 0.0;
    #pragma omp parallel for default(none) private(j) shared(a, c) reduction(+ : suma)
    for(i = 0; i < WYMIAR; i++) {
        for(j = 0; j < WYMIAR; j++) {
            #pragma omp atomic
            suma += a[j][i];
            c[j][i] = omp_get_thread_num();
        }
    }

    printf("Suma wyrazow tablicy(kolumnowo_redux): %lf\n", suma);
    for(i = 0; i < WYMIAR; i++) {
        for(j = 0; j < WYMIAR; j++) {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void kolumnowo_critical() {
    printf("\n");
    int i, j;
    for(i = 0; i < WYMIAR; i++) for(j = 0; j < WYMIAR; j++) c[i][j] = -1;
    double suma = 0.0;
    double suma_priv = 0.0;
    #pragma omp parallel for ordered default(none) private(j, suma_priv) shared(a, c, suma)
    for(i = 0; i < WYMIAR; i++) {
        suma_priv = 0.0;
        for(j = 0; j < WYMIAR; j++) {
            suma_priv += a[j][i];
            c[j][i] = omp_get_thread_num();
        }
        #pragma omp atomic
        suma += suma_priv;
    }

    printf("Suma wyrazow tablicy(kolumnowo_critical): %lf\n", suma);
    for(i = 0; i < WYMIAR; i++) {
        for(j = 0; j < WYMIAR; j++) {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void blokowo() {
    omp_set_nested(1);
    int threads_num = 3;
    int n = WYMIAR / threads_num;
    omp_set_num_threads(threads_num);
    printf("\n");
    int i, j, p, q;
    for(i = 0; i < WYMIAR; i++) for(j = 0; j < WYMIAR; j++) {c[i][j] = -1; d[i][j] = -1;}
    double suma = 0.0;
    double suma_priv_in = 0.0;
    double suma_priv_out = 0.0;
    int de;

    #pragma omp parallel for default(none) private(de,j,suma_priv_in,suma_priv_out) shared(a,d, c, threads_num, suma, n)
    for(i = 0; i < WYMIAR; i+=n) {
        suma_priv_out = 0;
        de = omp_get_thread_num();
        #pragma omp parallel for default(none) private(suma_priv_in, p, q) firstprivate(i,de) shared(suma_priv_out,d, a, c, threads_num, n)
        for(j = 0; j < WYMIAR; j+=n) {
            suma_priv_in = 0;
            for(p = i; p < i + n; p++) {
                if(p < WYMIAR) {
                    for(q = j; q < j + n; q++) {
                        if(q < WYMIAR) {
                            suma_priv_in += a[p][q];
                            c[p][q] = omp_get_thread_num();
                            d[p][q] = de;
                        }
                    }
                }
            }
            #pragma omp atomic
            suma_priv_out += suma_priv_in;
        }
        #pragma omp atomic
        suma += suma_priv_out;
    }
    printf("Suma wyrazow tablicy(blokowo): %lf\n\n", suma);
    for(i = 0; i < WYMIAR; i++) {
        for(j = 0; j < WYMIAR; j++) {
            printf("[%d,%d]",d[i][j],c[i][j]);
        }
        printf("\n");
    }
}

int main ()
{
  int i,j;


  for(i=0;i<WYMIAR;i++) for(j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;
  wierszowo();
  kolumnowo_redux();
  kolumnowo_critical();
  blokowo();
  double suma=0.0;
  for(i=0;i<WYMIAR;i++) {
    for(j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }

  //printf("Suma wyrazow tablicy: %lf\n", suma);



  double suma_parallel=0.0;
  for(i=0;i<WYMIAR;i++) {
    for(j=0;j<WYMIAR;j++) {
      suma_parallel += a[i][j];
    }
  }

  //printf("Suma wyrazow tablicy rownolegle: %lf\n", suma_parallel);
  return 0;
}
