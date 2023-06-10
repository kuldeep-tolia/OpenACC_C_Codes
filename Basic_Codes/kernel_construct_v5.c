// OpenACC tutorial for kernel construct
// Check how it auto-parallelizes using Minfo
// comments added based on information from -Minfo-accel
 
#include <stdio.h>

int main() {

  int a[10] = {0};
  
#pragma acc kernels async
  {				/* generate a copy of a[:] on GPU */
    int sum = 0;		/* a shared variable amongst threads is created */
    printf("One\n"); 		/* run on CPU */
    for(int i = 0; i < 10; i++)	 /* parallelizable loop, launches 1 gang with 32 vectors, also performing reduction (+:sum) operation on sum variable */
      sum += a[i] + i;
    printf("Two: %d\n", sum); /* avoids data transfer between CPU-GPU and thus launches a serial kernel(1 gang 32 vectors but only 1 vector lane is operating) on GPU */
    for(int i = 0; i < 10; i++)	     /* parallelizable loop, launches 1 gang with 32 vectors */
      a[i] += sum;
    printf("Three\n");		/* run on CPU */
    for(int i = 0; i < 10; i++)	/* run on CPU */
      printf("a[%d] = %d\n", i, a[i]);
    printf("Four\n");		/* run on CPU */
  }

  printf("Five\n");		/* run on CPU */
  
  return 0;
}
