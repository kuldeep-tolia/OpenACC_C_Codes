/* Parallel code using OpenACC for red-black mapping */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 100			/* define the size of the matrix */
#define eps 0.0001		/* define the tolerance level */

void init_mat(double mat[][N])	{

#pragma acc parallel loop collapse(2) present(mat[0:N][0:N])
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      mat[i][j] = i * 0.5 + j * 0.3;

  return;
}

void displayMat(double mat[][N])	{

#pragma acc serial loop present(mat[0:N][0:N])
  for(int i = 0; i < N; i++)	{
    for(int j = 0; j < N; j++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }

  return;
}

double red_black(double A[][N])	{

  double err = 0;
  
#pragma acc parallel loop collapse(2) present(A[0:N][0:N]) copyin(err)
  for(int i = 1; i < N-1; i++)
    for(int j = 1; j < N-1; j++)
      if ((i+j) % 2 == 0)	{
	double temp = A[i][j];
	A[i][j] += 0.25 * (A[i-1][j] + A[i][j-1] + A[i][j+1] + A[i+1][j]);
	err += A[i][j] - temp;
      }
  
#pragma acc parallel loop collapse(2) present(A[0:N][0:N], err) copyout(err)
  for(int i = 1; i < N-1; i++)
    for(int j = 1; j < N-1; j++)
      if ((i+j) % 2 == 1)	{
	double temp = A[i][j];
	A[i][j] += 0.25 * (A[i-1][j] + A[i][j-1] + A[i][j+1] + A[i+1][j]);
	err += A[i][j] - temp;
      }
  
  return err;
}

int main()	{

  struct timeval start_t, end_t;

  double A[N][N];
  double error;
  int iter = 0;

  gettimeofday(&start_t, NULL);

#pragma acc data create(A[0:N][0:N])
  {
    init_mat(A);
    if(N <= 10)	{
      printf("\nMatrix-A\n");
      displayMat(A);
    }

    do	{

      error = red_black(A);
      iter += 1;
    }	while (iter < 20);
  }

  printf("iter = %d, error = %f\n", iter, error);
  gettimeofday(&end_t, NULL);
  long seconds = end_t.tv_sec - start_t.tv_sec;
  long microseconds = ((seconds * 1000000) + end_t.tv_usec) - start_t.tv_usec;
  printf("Time measured = %ld seconds %ld microseconds\n", seconds, microseconds);

  return 0;
}
