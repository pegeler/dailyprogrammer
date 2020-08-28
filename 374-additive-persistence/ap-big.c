#include <stdio.h>

typedef __uint128_t uint128_t;

uint128_t atoui128(char *s)
{
  uint128_t x = 0;
  char c;
  while ((c = *(s++)) >= '0' && c <= '9')
    x = x * 10 + c - '0';
  return x;
}

uint128_t sum_digits(uint128_t x)
{
  uint128_t a = 0;
  while (x) {
    a += x % 10;
    x /= 10;
  }
  return a;
}

int main(int argc, char *argv[])
{
  uint128_t x = atoui128(argv[1]);
  int a;

  for (a = 0; x > 9; a++)
    x = sum_digits(x);

  printf("%d\n", a);

  return 0;
}
