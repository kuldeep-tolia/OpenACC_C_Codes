// OpenACC tutorial for parallel construct
// Check how many times printf is executed depending on #gangs used
 
#include <stdio.h>

int main() {
  
#pragma acc parallel num_gangs(2)
  {
    printf("How many time am I printed?\n");
  }
  
  return 0;
}
