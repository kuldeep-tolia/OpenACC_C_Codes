// OpenACC stencil computation code using in-situ update
// Code profiling done using PGI_ACC_TIME environment variable
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 256			/* set number of rows */
#define M 256			/* set number of columns */
#define num_iterations 10	/* set number of iterations */

void initialize(int **matrix)	{

#pragma acc parallel loop collapse(2) present(matrix[0:N][0:M])
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      matrix[i][j] = (i + j) % 10;

  return;
}

void displayMatrix(int **matrix)	{

#pragma acc serial loop present(matrix[0:N][0:M])
  for(int i = 0; i < N; i++)	{
    for(int j = 0; j < M; j++)
      printf("%d ", matrix[i][j]);
    printf("\n");
  }

  return;
}

void stencilCompute(int **matA, int **matA_old)	{

#pragma acc parallel loop collapse(2) present(matA[0:N][0:M], matA_old[0:N][0:M])
  for(int i = 1; i < N; i++)
    for(int j = 0; j < M-1; j++)
      matA[i][j] = matA_old[i][j] + matA_old[i-1][j] + matA_old[i-1][j+1];

  return;
}

void updatePrevious(int **matA, int **matA_old)	{

#pragma acc parallel loop collapse(2) present(matA[0:N][0:M], matA_old[0:N][0:M])
  for(int i = 0; i < N; i++)
    for(int j = 0; j < M; j++)
      matA_old[i][j] = matA[i][j];

  return;
}

int main(int argc, char* argv[]) {

  int j, iter;

  /* allocate matrix */
  int **A     = (int **)malloc(N * sizeof(int*));
  int **A_old = (int **)malloc(N * sizeof(int*));

  for(j = 0; j < N; j++)	{
    A[j]     = (int *)malloc(M * sizeof(int));
    A_old[j] = (int *)malloc(M * sizeof(int));
  }

  clock_t start = clock();
#pragma acc data copy(A[0:N][0:M], A_old[0:N][0:M])
  {
  initialize(A);
  initialize(A_old);
  if(N <= 10 && M <= 10)	{
    printf("Initial matrix elements\n");
    displayMatrix(A);
    printf("\n");
  }

  for(iter = 1; iter <= num_iterations; iter++)	{
    stencilCompute(A, A_old);
    updatePrevious(A, A_old);
  }
    
  if(N <= 10 && M <= 10)	{
    printf("After stencil computations for %d iterations\n", num_iterations);
    displayMatrix(A);
    printf("\n");
  }
  }
  clock_t end = clock();
  
  /* deallocate matrix */
  for(j = 0; j < N; j++)	{
    free(A[j]);
    free(A_old[j]);
  }
  free(A);
  free(A_old);

  double elapsed = ((double) (end - start))/ CLOCKS_PER_SEC;

  printf("Time measured = %.5f seconds\n", elapsed);

  return 0;
}
