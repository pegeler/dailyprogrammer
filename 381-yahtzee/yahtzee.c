#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_LINE 1000

typedef struct node {
  uint64_t val, score;
  struct node *left, *right;
} Node;

/**
 * Insert values into tree.
 * reference K&R C 2ed
 */
Node *tree_ins(Node *p, uint64_t val)
{
  if (p == NULL) {
    p = malloc(sizeof(Node));
    if (p == NULL)
      exit(EXIT_FAILURE);
    p->val = p->score = val;
    p->left = p->right = NULL;
  } else if (p->val == val) {
    p->score += val;
  } else if (p->val < val) {
    p->right = tree_ins(p->right, val);
  } else {
    p->left = tree_ins(p->left, val);
  }
  return p;
}

/**
 * Find the max score stored within tree.
 */
uint64_t tree_max_score(Node *p, uint64_t max)
{
  uint64_t i;
  if (p != NULL) {
    if (p->score > max)
      max = p->score;
    if((i = tree_max_score(p->left, max)) > max)
      max = i;
    if((i = tree_max_score(p->right, max)) > max)
      max = i;
  }
  return max;
}

int main(int argc, char *argv[])
{
  Node *root = NULL;
  char line[MAX_LINE];

  while (fgets(line, MAX_LINE, stdin) != NULL)
    root = tree_ins(root, strtoul(line, NULL, 10));

  printf("%ld\n", tree_max_score(root, 0));

  return 0;
}

