// OpenACC tutorial for kernel construct
// Check how it auto-parallelizes 
 
#include <stdio.h>

int main() {

  int a[10];
  
#pragma acc kernels
  {
    printf("One\n");
    for(int i = 0; i < 10; i++)	{
      a[i] = i;
      printf("first loop %d\n", i);
    }
    printf("Two: a[9] = %d\n", a[9]);
    for(int i = 0; i < 10; i++)	{
      a[i] *= 2;
      printf("second loop %d\n", i);
    }
    printf("Three: a[9] = %d\n", a[9]);
  }
  
  return 0;
}
