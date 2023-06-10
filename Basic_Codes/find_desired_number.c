// OpenACC tutorial: Check and find the desired number in an array
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

void initialize(int *numbers, int n)	{

  srand(time(NULL));

  for(int i = 0; i < n; i++)	{
    numbers[i] = rand() % 100;
    //printf("%d\n", numbers[i]);
  }

  return;
}

int main(int argc, char* argv[]) {

  int numbers[N];
  initialize(numbers, N);

  int myNumber = numbers[N/2];
  //int myNumber = -1;
  int i;

  #pragma acc parallel loop
  for(i = 0; i < N; i++)
    if(numbers[i] == myNumber) printf("Number found at %d\n", i);

  //if(i == N) printf("Number not found\n"); 
  //else printf("Number found at location %d\n", i);

  return 0;
}
