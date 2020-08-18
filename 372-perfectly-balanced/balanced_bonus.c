#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

int main(int argc, char *argv[])
{
  char line[MAX_LINE];
  char *s;

  while ((s = fgets(line, MAX_LINE, stdin)) != NULL) {
    int c;
    int letters[26] = {0};
    s[strlen(s) - 1] = '\0';
    while ((c = *(s++)) != '\0') {
      if (c >= 'a' && c <= 'z') {
        letters[c - 'a']++;
      } else {
        fprintf(stderr, "Unknown character: %c\n", c);
        exit(EXIT_FAILURE);
      }
    }
    int balanced = 1;
    for (int i=0, n=0; i < 26; i++) {
      if (!letters[i]) {
        continue;
      } else if (n > 0 && n != letters[i]) {
        balanced = 0;
        break;
      } else {
        n = letters[i];
      }
    }
    printf("%s\n", balanced ? "true" : "false");
  }

  return 0;

}
