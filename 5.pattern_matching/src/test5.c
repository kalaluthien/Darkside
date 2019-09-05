#include <stdio.h>

#include "generic_type.h"
#include "sum_type.h"

////////////////////////////////////////////////////
// Generic DataTypes and Functions
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

void print_maybe(maybe(pair(int, int)));
void print_list(list(int) *);

int main(int argc, char *argv[])
{
  pair(int, int) pair_value = { .fst = 1, .snd = 4 };

  maybe(pair(int, int)) ma = case_of(Nothing, NULL);
  maybe(pair(int, int)) mb = case_of(Just, pair_value);

  print_maybe(mb); // Just (1, 4)
  print_maybe(ma); // Nothing

  list(int) l_ = case_of(Nil, NULL);
  list(int) la = list_push(int)(1, &l_);
  list(int) lb = list_push(int)(2, &la);
  list(int) lc = list_push(int)(3, &lb);
  list(int) ld = list_push(int)(4, &lc);
  list(int) le = list_push(int)(5, &ld);

  print_list(&le); // 5 4 3 2 1
  print_list(&ld); // 4 3 2 1
  print_list(&lc); // 3 2 1
  print_list(&lb); // 2 1
  print_list(&la); // 1

  return 0;
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

void print_list(list(int) *l)
{
  match (*l) {
    with (Nil, _) {
      printf("\n");
    }
    with (Cons, v) {
      int x = v.head;
      list(int) *xs = v.tail;

      printf("%d ", x);
      print_list(xs);
    }
  }
}
