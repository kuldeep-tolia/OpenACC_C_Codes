// Hello world program with OpenACC
 
#include <stdio.h>

int main() {
  
  #pragma acc parallel loop
  for (int i = 0; i < 1000; ++i)
    printf("Hello World %d\n", i); 
  return 0;
}
