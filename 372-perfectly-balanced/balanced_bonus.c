#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

void count_chars(char *s, int *h)
{
  int c;
  while ((c = *(s++)) != '\0') {
    if (c >= 'a' && c <= 'z') {
      h[c - 'a']++;
    } else {
      fprintf(stderr, "Unknown character: %c\n", c);
      exit(EXIT_FAILURE);
    }
  }
}

int review_tally(int *h)
{
  for (int i=0, n=0; i < 26; i++)
    if (!h[i])
      continue;
    else if (n > 0 && n != h[i])
      return 0;
    else
      n = h[i];
  return 1;
}

int main(int argc, char *argv[])
{
  char line[MAX_LINE];

  while (fgets(line, MAX_LINE, stdin) != NULL) {
    line[strlen(line) - 1] = '\0';
    int h[26] = {0};
    count_chars(line, h);
    printf("%s\n", review_tally(h) ? "true" : "false");
  }

  return 0;

}
