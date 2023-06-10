/* Parallel code using OpenACC for LU-decomposition */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 512			/* define the size of the matrix */
#define eps 0.001		/* define the tolerance level */

void init_mat(double mat[][N])	{

#pragma acc parallel loop collapse(2) present(mat[0:N][0:N])
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      mat[i][j] = (i + j) / N;

  return;
}

void init_vec(double vec[N])	{

#pragma acc parallel loop present(vec[0:N])
  for(int i = 0; i < N; i++)
    vec[i] = (i + 1.0) / N;

  return;
}

void LU_factor(double mat[][N])	{

#pragma acc parallel loop present(mat[0:N][0:N])
  for(int i = 0; i < N; i++)	{
#pragma acc loop
    for(int j = 0; j < i; j++)	{
      for(int k = 0; k < j; k++)
	mat[i][j] -= mat[i][k] * mat[k][j];
      mat[i][j] /= (mat[j][j] >= eps ? mat[j][j] : 1.0);
    }
    
#pragma acc loop
    for(int j = 0; j < N; j++)	{
      for(int k = 0; k < i; k++)
	mat[i][j] += -mat[i][k] * mat[k][j];
    }
  }
  
  return;
}

void decompose(double A[][N], double b[N], double x[N], double y[N])	{

#pragma acc parallel loop present(A[0:N][0:N], b[0:N], x[0:N], y[0:N])
  for(int i = 0; i < N; i++)	{
    #pragma acc loop
    for(int j = 0; j < i; j++)
      y[i] -= A[i][j] * y[j];
  }

#pragma acc parallel loop present(A[0:N][0:N], b[0:N], x[0:N], y[0:N])
  for(int i = 0; i < N; i++)	{
    #pragma acc loop
    for(int j = N-i; j < N; j++)
      y[N-i-1] -= A[N-i-1][j] * x[j];
    x[N-i-1] = y[N-i-1] / (A[N-i-1][N-i-1] >= eps ? A[N-i-1][N-i-1] : 1.0);
  }
  
  return;
}

int main()	{

  struct timeval start_t, end_t;

  double A[N][N], b[N], x[N], y[N];

  gettimeofday(&start_t, NULL);

#pragma acc data create(A, b, x, y) copyout(x, y)
  {
    init_mat(A);
    init_vec(b);
    LU_factor(A);
    decompose(A, b, x, y);
  }

  gettimeofday(&end_t, NULL);
  long seconds = end_t.tv_sec - start_t.tv_sec;
  long microseconds = ((seconds * 1000000) + end_t.tv_usec) - start_t.tv_usec;
  printf("Time measured = %ld seconds %ld microseconds\n", seconds, microseconds);

  return 0;
}
