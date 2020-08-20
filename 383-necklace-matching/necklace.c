#include <stdio.h>
#include <string.h>

int same_necklace(char *a, char *b)
{
  int len = strlen(a);
  if (len != strlen(b))
    return 0;
  if (len == 0)
    return 1;

  for (int i=0; i < len; i++) {
    int match = 1;
    for (int j=0; j < len && match; j++)
      if (a[(i+j)%len] != b[j])
        match = 0;
    if (match)
      return 1;
  }

  return 0;

}

int main(int argc, char *argv[])
{
  if (argc != 3)
    return 1;

  printf("%s\n", same_necklace(argv[1], argv[2]) ? "true" : "false");

  return 0;
}
