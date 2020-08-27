/*
 * Came up with a very similar approach to spin81 and used that code as a hint
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
  for (i=0; i < max_len-1 && x; i++)
    s[i] = x % 10 + '0', x /= 10;

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
  if ((a == 0 || a > b) && b != 0 && a != b)
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

  if (argc != 3)
    return 1;

  a = atoui128(argv[1]);
  b = atoui128(argv[2]);
  c = leaps(a, b);

  ui128toa(output, 40, c);
  printf("%s\n", output);

  return 0;
}
