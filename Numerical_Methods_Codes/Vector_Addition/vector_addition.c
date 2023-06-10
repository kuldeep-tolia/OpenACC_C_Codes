// OpenACC tutorial for vector addition
// Use -Minfo=accel to see the compiler behaviour
// Use export PGI_ACC_TIME=1 to profile the time behaviour of the code
 
#include <stdio.h>
#include <stdlib.h>

#define N 1000

void init(int X[], int n)	{
#pragma acc parallel loop present(X)
  for(int i = 0; i < n; i++)
    X[i] = i;
}

void add(int C[], int A[], int B[], int n)	{
#pragma acc parallel loop present(A, B, C)
  for(int i = 0; i < n; i++)
    C[i] = A[i] + B[i];
}

int main() {

  int A[N], B[N], C[N];

#pragma acc data copyin(A, B) copyout(C)
  {
    init(A, N);
    init(B, N);
    add(C, A, B, N);
  }

  for(int i = 0; i < N; i++)
    printf("%d\n", C[i]);

  return 0;
}
