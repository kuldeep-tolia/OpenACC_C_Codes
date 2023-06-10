// OpenACC code for computing percentage of infected people in the city
// Code profiling done using PGI_ACC_TIME environment variable

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <openacc.h>

#define N 		100
#define PROBZERO	33

int main() {

  int a[N][N];			// cities x localities
  int x[N]   ,                  // sum of infected people for all the localities of a city
      y[N]   ;	                // number of localities in a city

  srand(time(NULL));

#pragma acc data create(a, x, y) copyout(x, y)
  {
#pragma acc parallel loop
    for (int i = 0; i < N; i++)	{
      x[i] = 0;
      for (int j = 0; j < N; j++)	{
	a[i][j] = (i * N + j) / N;
	if ((i * N + j) % 100 < PROBZERO) a[i][j] = 0;
      }
    }

#pragma acc parallel loop collapse(2) reduction(+:x)
    for (int i = 0; i < N; i++)	{
      for (int j = 0; j < N; j++)	{
	x[i] += a[i][j];
	if (a[i][j] > 0) y[i]++;
      }
    }
  } 
  
    for (int i = 0; i < N; i++)
      printf("%.0f ", x[i] * 100.0 / (y[i] * N));
    printf("\n"); 
  
  return 0;
}
