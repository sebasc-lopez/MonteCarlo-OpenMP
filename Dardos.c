#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

int main(int argc, char * argv[]){
    int n,i;
    double pi_est, x, y;
    int in_circle = 0;
    int local_in_circle, t;
    unsigned short xi[3];
    struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;

    n = atoi(argv[1]);
    omp_set_num_threads(atoi(argv[2]));

    gettimeofday(&inicio, 0);

    #pragma omp parrallel private(i,xi,t,x,y,local_in_circle)
    {
        local_in_circle = 0;
        xi[2] = omp_get_thread_num();
        t = omp_get_num_threads();
        for(i=xi[2];i<n;i+=t){
            x=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
            y=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
            if(x*x + y*y <= 1.0){
                local_in_circle++;
            }
        }
        #pragma omp critical
        in_circle+=local_in_circle;
    }


    gettimeofday(&fin, 0);

    segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);


    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);
    //printf("Estimate of pi=%7.5f\n",4.0*((float)in_circle)/(float)n);
    return 0;
}