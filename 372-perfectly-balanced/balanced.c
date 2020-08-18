#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

int main(int argc, char *argv[])
{
  char line[MAX_LINE];
  char *s;

  while ((s = fgets(line, MAX_LINE, stdin)) != NULL) {
    int x, y, c;
    x = y = 0;
    s[strlen(s) - 1] = '\0';
    while ((c = *(s++)) != '\0') {
      if (c == 'x') {
        x++;
      } else if (c == 'y') {
        y++;
      } else {
        fprintf(stderr, "Unknown character: %c\n", c);
        exit(EXIT_FAILURE);
      }
    }
    printf("%s\n", x == y ? "true" : "false");
  }

  return 0;

}
