#include <stdio.h>
#include <string.h>

int repeats(char *a)
{
  int repeats = 1;
  int len = strlen(a);
  for (int i=1; i < len; i++) {
    int match = 1;
    for (int j=0; j < len && match; j++)
      if (a[(i+j)%len] != a[j])
        match = 0;
    if (match)
      repeats++;
  }

  return repeats;

}

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  printf("%d\n", repeats(argv[1]));

  return 0;
}
