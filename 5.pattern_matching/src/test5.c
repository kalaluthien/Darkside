#include <stdio.h>

#include "sum_type.h"

////////////////////////////////////////////////////
// Custom DataType Example
////////////////////////////////////////////////////

typedef struct {
  enum { None, Some } match_tag;
  union { void *None; void *Some; } match_val;
} option_t;

typedef struct btree_struct btree_t;

typedef struct { btree_t *lst; btree_t *rst; } subtree_t;

struct btree_struct {
  enum { Leaf, Branch } match_tag;
  union { int Leaf; subtree_t Branch; } match_val;
};

////////////////////////////////////////////////////
// Pattern Matching Test
////////////////////////////////////////////////////

static btree_t branch_of(btree_t *, btree_t *);
static void print_option(option_t);
static void print_btree(btree_t);

int main(int argc, char *argv[])
{
  /* 1. Settings */
  char msg[] = "Hello, world!";
  option_t none = case_of(None, NULL);
  option_t some = case_of(Some, (void *)msg);

  btree_t t1a = case_of(Leaf, 1);
  btree_t t1b = case_of(Leaf, 2);
  btree_t t1c = case_of(Leaf, 3);
  btree_t t1d = case_of(Leaf, 4);
  btree_t t1e = case_of(Leaf, 5);

  btree_t t2a = branch_of(&t1a, &t1b);
  btree_t t2b = branch_of(&t1c, &t1d);
  btree_t t2c = branch_of(&t2b, &t1e);
  btree_t t2d = branch_of(&t2a, &t2c);

  /* 2. Tests */
  print_option(none); // None: (nil)
  print_option(some); // Some: Hello, world!

  print_btree(t2d); // 1 2 3 4 5
  print_btree(t2c); // 3 4 5
  print_btree(t2b); // 3 4
  print_btree(t2a); // 1 2

  return 0;
}

////////////////////////////////////////////////////
// Custom CaseOf Wrapper Example
////////////////////////////////////////////////////

btree_t branch_of(btree_t *lst, btree_t *rst)
{
  subtree_t tmp = { .lst = lst, .rst = rst };
  btree_t tree = case_of(Branch, tmp);
  return tree;
}

////////////////////////////////////////////////////
// MatchWith Example
////////////////////////////////////////////////////

void print_option(option_t maybe)
{
  void *value;

  match (maybe) {
    with (None, value) {
      printf("None: %p\n", value);
    }
    with (Some, value) {
      printf("Some: %s\n", (const char *)value);
    }
  }
}

static void print_btree_rec(btree_t root);

void print_btree(btree_t root)
{
  print_btree_rec(root);
  printf("\n");
}

void print_btree_rec(btree_t root)
{
  int leaf;
  subtree_t tree;

  match (root) {
    with (Leaf, leaf) {
      printf("%d ", leaf);
    }
    with (Branch, tree) {
      btree_t *lst = tree.lst;
      btree_t *rst = tree.rst;

      print_btree_rec(*lst);
      print_btree_rec(*rst);
    }
  }
}
