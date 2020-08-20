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

/* search: search for matches */
int search(Node *n, char **matches)
{
  while (n != NULL) {
    Node *m = n->next;
    int n_match = 0;
    matches[n_match++] = n->s;
    while (m != NULL) {
      if (same(n->s, m->s)) {
        matches[n_match++] = m->s;
        if (n_match == TARGET_MATCHES)
          return 1;
      }
      m = m->next;
    }
    n = n->next;
  }
  return 0;
}


int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILE\n", argv[0]);
    return 1;
  }

  /* read all words into array of linked lists organized by nchar */
  FILE *f = fopen(argv[1], "r");
  char word[MAX_NCHAR];
  Node **nodes = malloc(sizeof(Node*) * (MAX_NCHAR + 1));
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

  fclose(f);

  /* search through each linked list for matching words */
  int match = 0;
  char **matches = malloc(sizeof(char*) * TARGET_MATCHES);
  for (int i=TARGET_MATCHES; i <= MAX_NCHAR && !match; i++)
    match = search(nodes[i], matches);

  /* if match, print */
  if (match)
    for (int i=0; i < TARGET_MATCHES; i++)
      printf("%s%s", matches[i], i != TARGET_MATCHES - 1 ? ", " : "\n");
  else
    fprintf(stderr, "Match not found.\n");

  return 0;
}
