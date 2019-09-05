#include <stdio.h>

#include "sum_type.h"
#include "generic_type.h"

////////////////////////////////////////////////////
// Custom DataType Example
////////////////////////////////////////////////////

typedef struct btree_struct btree_t;

typedef struct { btree_t *lst; btree_t *rst; } subtree_t;

struct btree_struct {
  enum { Leaf, Branch } match_tag;
  union { int Leaf; subtree_t Branch; } match_val;
};

////////////////////////////////////////////////////
// Generic DataType Example
////////////////////////////////////////////////////

DECL_PAIR(int, int); // (Int, Int)
DECL_MAYBE(pair(int, int)); // Maybe (Int, Int)
DECL_LIST(int); // [Int]

IMPORT_LIST(int, list_push); // Int -> *[Int] -> [Int]
IMPORT_LIST(int, list_head); // *[Int] -> Int
IMPORT_LIST(int, list_tail); // *[Int] -> [Int]

////////////////////////////////////////////////////
// Pattern Matching Test
////////////////////////////////////////////////////

static btree_t leaf_of(int);
static btree_t branch_of(btree_t *, btree_t *);
static void print_btree(btree_t);
static void print_maybe(maybe(pair(int, int)));
static void print_list(list(int));

int main(int argc, char *argv[])
{
  /* 1. Custom DataType Settings */
  btree_t t1a = leaf_of(1);
  btree_t t1b = leaf_of(2);
  btree_t t1c = leaf_of(3);
  btree_t t1d = leaf_of(4);
  btree_t t1e = leaf_of(5);

  btree_t t2a = branch_of(&t1a, &t1b);
  btree_t t2b = branch_of(&t1c, &t1d);
  btree_t t2c = branch_of(&t2b, &t1e);
  btree_t t2d = branch_of(&t2a, &t2c);

  /* 2. Custom DataType Test */
  print_btree(t2d); // 1 2 3 4 5
  print_btree(t2c); // 3 4 5
  print_btree(t2b); // 3 4
  print_btree(t2a); // 1 2

  /* 3. Generic DataType Settings */
  pair(int, int) pair_value = { .fst = 1, .snd = 4 };

  maybe(pair(int, int)) ma = case_of(Nothing, NULL);
  maybe(pair(int, int)) mb = case_of(Just, pair_value);

  list(int) l_ = case_of(Nil, NULL);
  list(int) la = list_push(int)(1, &l_);
  list(int) lb = list_push(int)(2, &la);
  list(int) lc = list_push(int)(3, &lb);
  list(int) ld = list_push(int)(4, &lc);
  list(int) le = list_push(int)(5, &ld);

  /* 4. Generic DataType Test */
  print_maybe(mb); // Just (1, 4)
  print_maybe(ma); // Nothing

  print_list(le); // 5 4 3 2 1
  print_list(ld); // 4 3 2 1
  print_list(lc); // 3 2 1
  print_list(lb); // 2 1
  print_list(la); // 1

  return 0;
}

////////////////////////////////////////////////////
// CaseOf Example
////////////////////////////////////////////////////

btree_t leaf_of(int x)
{
  btree_t tree = case_of(Leaf, x);
  return tree;
}

btree_t branch_of(btree_t *lst, btree_t *rst)
{
  subtree_t tmp = { .lst = lst, .rst = rst };
  btree_t tree = case_of(Branch, tmp);
  return tree;
}

////////////////////////////////////////////////////
// MatchWith Example
////////////////////////////////////////////////////

static void print_btree_rec(btree_t root);

void print_btree(btree_t root)
{
  print_btree_rec(root);
  printf("\n");
}

void print_btree_rec(btree_t root)
{
  match (root) {
    with (Leaf, x) {
      printf("%d ", x);
    }
    with (Branch, x) {
      btree_t *lst = x.lst;
      btree_t *rst = x.rst;

      print_btree_rec(*lst);
      print_btree_rec(*rst);
    }
  }
}

void print_maybe(maybe(pair(int, int)) m)
{
  match (m) {
    with (Nothing, _) {
      printf("Nothing\n");
    }
    with (Just, x) {
      printf("Just (%d, %d)\n", x.fst, x.snd);
    }
  }
}

void print_list(list(int) l)
{
  match (l) {
    with (Nil, _) {
      printf("\n");
    }
    with (Cons, v) {
      int x = v.head;
      list(int) *xs = v.tail;

      printf("%d ", x);
      print_list(*xs);
    }
  }
}
