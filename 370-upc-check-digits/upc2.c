#include <assert.h>
#include <string.h>

/**
 * Get UPC check digit.
 * The approach in upc.c is better for many reasons.
 * Not the least of which is that it's more readable/understandable
 * what the program is supposed to do. This is more compact, harder to
 * read. Another consideration is that now we are doing a multiplication
 * operation five times instead of one. This is meaningless on a small
 * string but would be expensive if we scaled.
 */
int upc(char *s)
{
  char u[11] = {'0'};
  int i = 11 - strlen(s);
  int j = 0;
  int x = 0;

  /* pad left */
  while (i < 11)
    u[i++] = s[j++];

  /* Example of combining steps 1-3 */
  for (i=0, j=0; i < 11; i++, (j = !j))
    x += j ? u[i] - '0' : (u[i] - '0') * 3;
    /* Alternatively: x += i % 2 == 0 ? (u[i] - '0') * 3 : u[i] - '0'; */

  /* Steps 4 & 5 */
  return (x = x % 10) ? 10 - x : 0;
}

int main(void)
{
  assert(upc("4210000526") == 4);
  assert(upc("3600029145") == 2);
  assert(upc("12345678910") == 4);
  assert(upc("1234567") == 0);

  return 0;
}

