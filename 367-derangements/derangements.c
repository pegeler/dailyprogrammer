#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

/**
 * Compute the factorial
 * (Don't need this)
 */
int64_t factorial(int64_t n)
{
  int64_t x = 1;
  while (n > 1)
    x *= n--;
  return x;
}

/**
 * Get number of derangements possible given |set| = n
 */
int64_t D(int64_t n)
{
  int64_t x = 0, y = 1;
  while (n > 1) {
    if (n & 1)
      x -= y;
    else
      x += y;
    y *= n--;
  }
  return x;
}

int main(int argc, char *argv[])
{

  if (argc == 2) {
    printf("%ld\n", D(strtol(argv[1], NULL, 10)));
  } else {
    assert(D(1) == 0);
    assert(D(2) == 1);
    assert(D(3) == 2);
    assert(D(4) == 9);
    assert(D(5) == 44);
    /* challenge input */
    assert(D(6) == 265);
    assert(D(9) == 133496);
    assert(D(14) == 32071101049);
    fprintf(stderr, "checks OK\n");
  }

  return 0;
}
