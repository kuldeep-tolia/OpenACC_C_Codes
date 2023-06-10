// OpenACC tutorial for kernel construct
// Check how it auto-parallelizes using Minfo
// comments added based on information from -Minfo-accel
 
#include <stdio.h>

int main() {

  int a[10];
  
#pragma acc kernels
  {				/* generate a copy of a[:] on GPU */
    printf("One\n"); 		/* run on CPU */
    for(int i = 0; i < 10; i++)	{ /* parallelizable loop, launches 1 gang with 32 vectors */
      a[i] = i;
      printf("first loop %d\n", i);
    }
    printf("Two: a[9] = %d\n", a[9]); /* avoids data transfer between CPU-GPU and thus launches a serial kernel(1 gang 32 vectors but only 1 vector lane is operating) on GPU */
    for(int i = 0; i < 10; i++)	{     /* parallelizable loop, launches 1 gang with 32 vectors */
      a[i] *= 2;
      printf("second loop %d\n", i);
    }
    printf("Three\n");		/* run on CPU */
  }
  
  return 0;
}
