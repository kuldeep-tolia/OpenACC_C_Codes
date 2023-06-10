/* Parallel code using OpenACC for matrix addition */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 300			/* set number of rows */
#define M 300			/* set number of columns */

void initialize(int *matrix)	{

#pragma acc parallel loop collapse(2) present(matrix[0:N*M])
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      matrix[i*M+j] = i * N + j;

  return;
}

void displayMat(int *matrix)	{

#pragma acc serial loop present(matrix[0:N*M])
  for(int i = 0; i < N; i++)	{
    for(int j = 0; j < M; j++)
      printf("%d ", matrix[i*M+j]);
    printf("\n");
  }

  return;
}

void matAdd(int *C, int *A, int *B)	{

#pragma acc parallel loop collapse(2) present(A[0:N*M], B[0:N*M], C[0:N*M])
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      C[i*M+j] = A[i*M+j] + B[i*M+j];

  return;
}

int main()	{

  struct timeval start_t, end_t;
  
  /* allocate matrices */
  int *A = (int *)malloc(N * M * sizeof(int));
  int *B = (int *)malloc(N * M * sizeof(int));
  int *C = (int *)malloc(N * M * sizeof(int));

  gettimeofday(&start_t, NULL);
  
#pragma acc data create(A[0:N*M], B[0:N*M], C[0:N*M])
  {
    initialize(A);
    initialize(B);
    if(N <= 10 && M <= 10)	{
      printf("\nMatrix-A\n");
      displayMat(A);
      printf("\nMatrix-B:\n");
      displayMat(B);
    } 
    
    matAdd(C, A, B);
    if(N <= 10 && M <= 10)	{
      printf("\nMatrix-C\n");
      displayMat(C);
    } 
  }
  
  gettimeofday(&end_t, NULL);
  long seconds = end_t.tv_sec - start_t.tv_sec;
  long microseconds = ((seconds * 1000000) + end_t.tv_usec) - start_t.tv_usec;
  printf("Time measured = %ld seconds %ld microseconds\n", seconds, microseconds);
    
  /* deallocate matrices */
  free(A);
  free(B);
  free(C);

  return 0;
}
