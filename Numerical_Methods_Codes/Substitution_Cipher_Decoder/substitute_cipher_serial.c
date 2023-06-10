/* Serial code for substitute cipher */
/* Encrypts the lower-case alphabets to next character, i.e. a->b, d->e and so on... */
/* Other capital letters, digits, symbols or characters are ignored and kept as it is */
/* After the encryption, the encrypted message is decrypted back to check the original message */
#include <stdio.h>
#include <string.h>

#define N 	 10000
#define DISTANCE 1      

void transform(char src[], char dest[], int distance)	{

  char *eptr = dest;
  
  for (char *pptr = src; *pptr; ++pptr, ++eptr)
    if ('a' <= *pptr && *pptr <= 'z')
      *eptr = 'a' + (*pptr - 'a' + distance) % 26;
    else
      *eptr = *pptr;
  *eptr = '\0';

  return;
}

void encrypt(char plaintext[], char encryptext[])	{

  transform(plaintext, encryptext, DISTANCE);

  return;
}

void decrypt(char encryptext[], char decryptext[])	{

  transform(encryptext, decryptext, 26 - DISTANCE);

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
