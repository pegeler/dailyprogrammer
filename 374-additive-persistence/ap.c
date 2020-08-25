#include <stdio.h>

typedef unsigned int uint;

uint atoi(char *s)
{
  uint x = 0;
  char c;
  while ((c = *(s++)) >= '0' && c <= '9')
    x = x * 10 + c - '0';
  return x;
}

uint sum_digits(uint x)
{
  int a = 0;
  while (x) {
    a += x % 10;
    x /= 10;
  }
  return a;
}

int main(int argc, char *argv[])
{
  uint x = atoi(argv[1]);
  int a;

  for (a = 0; x / 10 != 0; a++)
    x = sum_digits(x);

  printf("%d\n", a);

  return 0;
}
