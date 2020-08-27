/*
 * Came up with a very similar approach to /u/spin81 and used that code as a hint
 * to fix my off-by-one errors. So thanks spin81!
 */
#include <stdio.h>
#include <assert.h>

typedef __uint128_t uint128_t;

/**
 * convert string to uint128_t
 */
uint128_t atoui128(char *s)
{
  uint128_t x = 0;
  char c;
  while ((c = *(s++)) >= '0' && c <= '9')
    x = x * 10 + c - '0';
  return x;
}

/**
 * convert uint128_t to string
 */
void ui128toa(char *s, int max_len, uint128_t x)
{
  int i, j, c, len;
  i=0;

  do
    s[i++] = x % 10 + '0';
  while (i < max_len-1 && (x /= 10));

  len = i;

  for (i=0, j=len-1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;

  for (i=len; i < max_len; i++)
    s[i] = '\0';
}

/**
  * count number of occurences, given periodicity
  */
uint128_t count(uint128_t a, uint128_t b, int period, int offset)
{
  uint128_t count = (b-a) / period;
  a = (a + period - offset) % period;
  b = (b + period - offset) % period;
  if ((a == 0 || a > b) && b != 0)
    count++;
  return count;
}

/**
  * count number of leap years in Revised Julian Calendar
  */
uint128_t leaps(uint128_t a, uint128_t b)
{
  return  count(a,b,4,0)      /* Add all multiples of four */
        - count(a,b,100,0)    /* Subtract multiples of 100 */
        + count(a,b,900,200)  /* Re-add 900 % 200 */
        + count(a,b,900,600)  /* Re-add 900 % 600 */
  ;
}

int main(int argc, char *argv[])
{
  uint128_t a, b, c;
  char output[40];

  if (argc == 1) {
    /* using /u/spin81's assertions */
    assert(leaps(2016, 2017) == 1);
    assert(leaps(2019, 2020) == 0);
    assert(leaps(1900, 1901) == 0);
    assert(leaps(2000, 2001) == 1);
    assert(leaps(2800, 2801) == 0);
    assert(leaps(123456, 123456) == 0);
    assert(leaps(1234, 5678) == 1077);
    assert(leaps(123456, 7891011) == 1881475);
    assert(leaps(123456789101112, 1314151617181920) == 288412747246240);
    fprintf(stderr, "checks OK\n");
    return 0;
  } else if (argc != 3) {
    return 1;
  }

  a = atoui128(argv[1]);
  b = atoui128(argv[2]);
  c = leaps(a, b);

  ui128toa(output, 40, c);
  printf("%s\n", output);

  return 0;
}
