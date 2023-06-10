// OpenACC tutorial for parallel construct
// Check async host-device printing
 
#include <stdio.h>

int main() {

  int x, y;
  
#pragma acc parallel num_gangs(20) async
  {
    y = 2;
    printf("Hello\n");
    y = y + 8;
    printf("Bye\n");
    x = 4;
    x = x +3;
  }

  printf("Host\n");

#pragma acc parallel num_gangs(3)
  {
    printf("One %d\n", x);
    printf("Two %d\n", y);
  }
  
  return 0;
}
