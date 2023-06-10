/* Parallel code using OpenACC for square matrix multiplication */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 100			/* define the size of the matrix */

void init_mat(int mat[][N])	{

#pragma acc parallel loop collapse(2) present(mat[0:N][0:N])
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      mat[i][j] = i + j;

  return;
}

void displayMat(int mat[][N])	{

#pragma acc serial loop present(mat[0:N][0:N])
  for(int i = 0; i < N; i++)	{
    for(int j = 0; j < N; j++)
      printf("%d ", mat[i][j]);
    printf("\n");
  }

  return;
}

void matMult(int C[][N], int A[][N], int B[][N])	{

  int temp;
  
#pragma acc parallel loop present(A[0:N][0:N], B[0:N][0:N], C[0:N][0:N]) collapse(2)
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)	{
      temp = 0;
      for(int k = 0; k < N; k++)
	temp += A[i][k] * B[k][j];
      C[i][j] = temp;
    }
  
  return;
}

int main()	{

  struct timeval start_t, end_t;

  int A[N][N], B[N][N], C[N][N];

  gettimeofday(&start_t, NULL);

#pragma acc data create(A[0:N][0:N], B[0:N][0:N], C[0:N][0:N]) copyout(C[0:N][0:N])
  {
    init_mat(A);
    init_mat(B);
    if(N <= 10)	{
      printf("\nMatrix-A\n");
      displayMat(A);
      printf("\nMatrix-B:\n");
      displayMat(B);
    }

    matMult(C, A, B);
    if(N <= 10)	{
      printf("\nMatrix-C\n");
      displayMat(C);
    }
  }

  printf("\nSanity check value for C[1][1] = %d\n", C[1][1]);
  gettimeofday(&end_t, NULL);
  long seconds = end_t.tv_sec - start_t.tv_sec;
  long microseconds = ((seconds * 1000000) + end_t.tv_usec) - start_t.tv_usec;
  printf("Time measured = %ld seconds %ld microseconds\n", seconds, microseconds);

  return 0;
}
