#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NCHAR 28
#define TARGET_MATCHES 4

typedef struct node {
  char *s;
  struct node *next;
} Node;

/* same: check if the strings can be rotated to match each other */
int same(char *a, char *b)
{
  int len = strlen(a);
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
  Node **nodes = malloc(sizeof(Node*) * (MAX_NCHAR + 1));
  char **matches = malloc(sizeof(char*) * TARGET_MATCHES);

  if (argc != 2)
    return 1;

  FILE *f = fopen(argv[1], "r");

  char word[MAX_NCHAR];
  while (fgets(word, MAX_NCHAR, f) != NULL) {
    int len = strlen(word) - 1;
    if (len < 4)
      continue;

    Node *node = malloc(sizeof(Node));

    /* add new word to node of linked list */
    word[len] = '\0';
    node->s = strdup(word);

    /* grow the linked list */
    node->next = nodes[len];
    nodes[len] = node;
  }

  int n_match;
  for (int i=TARGET_MATCHES; i <= MAX_NCHAR; i++) {
    Node *n = nodes[i];
    while (n != NULL) {
      Node *m = n->next;
      n_match = 0;
      matches[n_match++] = n->s;
      while (m != NULL) {
        if (same(n->s, m->s)) {
          matches[n_match++] = m->s;
          if (n_match == TARGET_MATCHES)
            goto FINISH; /* Considered harmless */
        }
        m = m->next;
      }
      n = n->next;
    }
  }

  FINISH:

  if (n_match ==  4)
    for (int i=0; i < TARGET_MATCHES; i++)
      printf("%s%s", matches[i], i != TARGET_MATCHES - 1 ? ", " : "\n");
  else
    fprintf(stderr, "Match not found.\n");

  return 0;
}
