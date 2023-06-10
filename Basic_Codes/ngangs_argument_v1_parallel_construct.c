// OpenACC tutorial for parallel construct
// num_gangs taken as input argument from user
 
#include <stdio.h>
#include <stdlib.h>

void function1() {
  printf("This is print from function call\n");

  return;
}

int main(int argc, char* argv[]) {

  int ngangs = atoi(argv[1]);
  
#pragma acc parallel num_gangs(ngangs)
  {
    printf("Hello World\n");
    printf("Bye World\n");
  }

  printf("Host\n");

#pragma acc parallel num_gangs(ngangs/2)
  {
    function1();
  }
  
  return 0;
}
