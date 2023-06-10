#include <stdio.h>
#define N 10

struct s	{

  int data;
  int *ptr;
};

void init(struct s *sll)	{

  for (int i = 0; i < N; i++)	{
    sll[i].data = i;
    sll[i].ptr = &sll[i].data;
  }

  return;
}

int main()	{

  struct s sll[N];
  init(sll);

  printf("On CPU............\n");
  for (int i = 0; i < N; i++)
    printf("address of data = %p,  value in ptr = %p\n", &sll[i].data, sll[i].ptr);

  printf("\nOn GPU............\n");
#pragma acc parallel loop
  for (int i = 0; i < N; i++)
    printf("address of data = %p,  value in ptr = %p\n", &sll[i].data, sll[i].ptr);
  
  return 0;
}
