#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1000

/**
 * reverse a character string
 */
void reverse(char *s)
{
  char c;
  for(int i = 0, j = strlen(s) - 1; i < j; i++, j--)
     c = s[i], s[i] = s[j], s[j] = c;
}

/**
 * add one to each digit
 * directly manipulates strings
 */
void add(char *s, char *t)
{
  int i, j, c, d;
  i = strlen(s) - 1;
  j = 0;

  while (i >= 0 && j < MAX_LINE - 1) {
    c = s[i--] - '0';
    if (c == 9) {
      t[j++] = 0 + '0';
      t[j++] = 1 + '0';
    } else if (c >= 0 && c < 9) {
      t[j++] = c + 1 + '0';
    } else {
      fprintf(stderr, "Invalid char: '%c'\n", c + '0');
      exit(EXIT_FAILURE);
    }
  }

  while (j < MAX_LINE)
    t[j++] = '\0';

  reverse(t);
}

/**
 * add one to each digit (bonus)
 * manipulates integers
 */
int bonus(int x)
{
  int y, z, d;
  y = 0;
  d = 1;
  do {
    z = x % 10;
    if (z == 9) {
      y += 10 * d;
      d *= 100;
    } else {
      y += (z + 1) * d;
      d *= 10;
    }
  } while (x /= 10);
  return y;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  char t[MAX_LINE];
  add(argv[1], t);
  printf("add: %s, bonus: %d\n", t, bonus(atoi(argv[1])));

  return 0;
}
