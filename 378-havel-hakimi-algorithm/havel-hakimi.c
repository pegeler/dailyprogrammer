#include <stdio.h>
#include <stdlib.h>

/* print: print an array of ints (used for debugging) */
void print(uint *x, uint len)
{
  for (uint i=0; i < len; i++)
    printf("%d%s", x[i], i != len - 1 ? ", " : "\n");
}

/* max_element: get the max element out of an integer array */
uint max_element(uint *x, uint len){
  uint best=0;
  for (uint i=0; i < len; i++)
    if (x[i] > best)
      best = x[i];
  return best;
}

/* sort: counting sort, reversed, drops zeros, returns new length */
uint sort(uint *x, uint len)
{
  uint max = max_element(x, len);
  uint *a = calloc(sizeof(uint), max + 1);
  uint out_len = 0;

  /* make an array of counts */
  for (uint i=0; i < len; i++)
    a[*(x + i)]++;

  /* replace existing array with reverse-sorted data */
  while (max) {
    while (a[max]--)
      x[out_len++] = max;
    max--;
  }

  x = realloc(x, sizeof(uint) * out_len);
  free(a);
  return out_len;
}

/* hh: Havel-Hakimi Algorithm */
uint hh(uint *x, uint len)
{
  uint n;
  len = sort(x, len);

  if (!len)
    return 1;

  if ((n = x[0]) > --len)
    return 0;

  for (uint i=0; i < len; i++)
    x[i] = i < n ? x[i + 1] - 1 : x[i + 1];

  x = realloc(x, sizeof(uint) * len);

  return hh(x, len);
}

int main(int argc, char *argv[])
{
  uint len = (uint) --argc;
  uint *x = malloc(sizeof(uint) * len);

  while (argc--)
    x[argc] = (uint) atoi(argv[argc+1]);

  printf("%s\n", hh(x, len) ? "true" : "false" );

  return 0;
}
