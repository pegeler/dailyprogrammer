#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t sum_digits(uint64_t x)
{
  uint64_t a = 0;
  while (x) {
    a += x % 10;
    x /= 10;
  }
  return a;
}

int main(int argc, char *argv[])
{
  uint64_t x = strtoull(argv[1], NULL, 10);
  int a;

  for (a = 0; x / 10 != 0; a++)
    x = sum_digits(x);

  printf("%d\n", a);

  return 0;
}
