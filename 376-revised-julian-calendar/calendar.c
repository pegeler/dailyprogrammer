#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int leaps(uint64_t a, uint64_t b)
{
  uint64_t i;
  int leaps = 0;

  /* Add all multiples of four */
  for (i=a; i % 4; i++)
    ;
  if (i < b)
    leaps += 1 + (b-i-1)/4;
  else
    return 0;

  /* Subtract multiples of 100 */
  for (i=a; i % 100; i++)
    ;
  if (i < b)
    leaps -= 1 + (b-i-1)/100;

  /* Re-add 900 in (200, 600) */
  for (i=a; i % 900 != 200; i++)
    ;
  if (i < b)
    leaps += 1 + (b-i-1)/900;

  for (i=a; i % 900 != 600; i++)
    ;
  if (i < b)
    leaps += 1 + (b-i-1)/900;

  return leaps;
}

int main(int argc, char *argv[])
{
  uint64_t a, b;

  if (argc != 3)
    exit(EXIT_FAILURE);

  a = strtoull(argv[1], NULL, 10);
  b = strtoull(argv[2], NULL, 10);

  printf("%d\n", leaps(a, b));

  return 0;
}
