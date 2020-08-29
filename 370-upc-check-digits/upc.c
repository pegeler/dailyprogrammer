#include <assert.h>
#include <string.h>

/**
 * Get UPC check digit
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

  /* Step 1 */
  for (i=0; i <= 10; i += 2)
    x += u[i] - '0';

  /* Step 2 */
  x *= 3;

  /* Step 3 */
  for (i = 1; i <= 9; i += 2)
    x += u[i] - '0';

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

