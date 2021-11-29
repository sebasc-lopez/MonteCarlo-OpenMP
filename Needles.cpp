#include <iostream>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <chrono>
#include <unistd.h>
#include <string>
#include <time.h>
#include <omp.h>

using namespace std;

long double calc(int n)
{
  unsigned semilla = 17937 + omp_get_thread_num() * chrono::system_clock::now().time_since_epoch().count();
  default_random_engine gen(semilla);
  uniform_real_distribution<float> prob(0.0, 1.0);
  double x;
  double y;
  double d;
  
  double P = 0;
  for (int i = 0; i < n; i++)
  {
    x = (prob(semilla)) * 3.1415;
    d = (prob(semilla));
    y = 0.5 * sin(x);
    if (d <= y)
    {
      P++;
    }
  }
  return (long double)n / P;
}

int main(int argc, char **argv)
{
  int n;
  struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;

  n = stoi(argv[1]);
  int canHilos = stoi(argv[2]);
  int n1 = n / canHilos;
  long double tavg = (long double)0;
  gettimeofday(&inicio, 0);
  omp_set_num_threads(canHilos);
#pragma omp parallel
  {
    int i;
#pragma omp for
    for (i = 0; i < canHilos; i++)
    {
      tavg += (long double)calc(n1);
    }
  }
gettimeofday(&fin, 0);
  segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);

    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);
  tavg = (long double)tavg / canHilos;
  

  return 0;
}