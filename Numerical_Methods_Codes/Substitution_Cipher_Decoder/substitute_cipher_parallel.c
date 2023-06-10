/* Parallel code using OpenACC for substitute cipher */
/* Encrypts the lower-case alphabets to next character, i.e. a->b, d->e and so on... */
/* Other capital letters, digits, symbols or characters are ignored and kept as it is */
/* After the encryption, the encrypted message is decrypted back to check the original message */
#include <stdio.h>
#include <string.h>

#define N 	 10000
#define DISTANCE 1

void transform(char src[], int srclen, char dest[], int distance)	{
  
#pragma acc parallel loop copyout(dest[0:srclen+1])
  for (int i = 0; i < srclen + 1; i++)
    if ('a' <= src[i] && src[i] <= 'z')
      dest[i] = 'a' + (src[i] - 'a' + distance) % 26;
    else
      dest[i] = src[i];

  return;
}

void encrypt(char plaintext[], char encryptext[])	{

  int plen = strlen(plaintext);
  transform(plaintext, plen, encryptext, DISTANCE);

  return;
}

void decrypt(char encryptext[], char decryptext[])	{
  
  int plen = strlen(encryptext);
  transform(encryptext, plen, decryptext, 26 - DISTANCE);

  return;
}

int main()	{
  char plaintext[N], encryptext[N], decryptext[N];
  
  fgets(plaintext, N, stdin);
  encrypt(plaintext, encryptext);
  decrypt(encryptext, decryptext);
  
  puts(encryptext);
  puts(decryptext);

	return 0;
}
