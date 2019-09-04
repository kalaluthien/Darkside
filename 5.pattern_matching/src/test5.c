#include <stdio.h>

#include "sum_type.h"

////////////////////////////////////////////////////
// Simple Macros for Fun
////////////////////////////////////////////////////

#define JOIN_(x, y) x ## _ ## y
#define JOIN(x, y) JOIN_(x, y)

////////////////////////////////////////////////////
// Pair Type Decl
////////////////////////////////////////////////////

#define pair(T1, T2) JOIN(pair, JOIN(T1, T2))
#define pair_of(T1, T2) { T1 fst; T2 snd; }

struct pair(int, int) pair_of(int, int); // (Int, Int)

////////////////////////////////////////////////////
// Maybe Type Decl
////////////////////////////////////////////////////

#define maybe(T) JOIN(maybe, T)
#define maybe_of(T) \
{\
  enum { Nothing, Just } match_tag;\
  union { void *Nothing; T Just; } match_val;\
}

struct maybe(pair(int, int)) maybe_of(struct pair(int, int)); // Maybe (Int, Int)

////////////////////////////////////////////////////
// List Type Decl
////////////////////////////////////////////////////

#define list(T) JOIN(list, T)
#define list_of(T) \
{\
  enum { Nil, Cons } match_tag;\
  union { void *Nil; struct { T head; struct list(T) *tail; } Cons; } match_val;\
}

struct list(int) list_of(int); // [Int]

struct list(int) cons(int x, struct list(int) *xs)
{
  struct list(int) l;
  l.match_tag = Cons;
  l.match_val.Cons.head = x;
  l.match_val.Cons.tail = xs;
  return l;
}

////////////////////////////////////////////////////
// Pattern Matching Test
////////////////////////////////////////////////////

void print_maybe(struct maybe(pair(int, int)));
void print_list(struct list(int) *);

int main(int argc, char *argv[])
{
  struct pair(int, int) pair_value = { .fst = 1, .snd = 4 };

  struct maybe(pair(int, int)) ma = case_of(Nothing, NULL);
  struct maybe(pair(int, int)) mb = case_of(Just, pair_value);

  print_maybe(ma); // Nothing
  print_maybe(mb); // Just (1, 4)

  struct list(int) empty = case_of(Nil, NULL);
  struct list(int) la = cons(1, &empty);
  struct list(int) lb = cons(2, &la);
  struct list(int) lc = cons(3, &lb);
  struct list(int) ld = cons(4, &lc);
  struct list(int) le = cons(5, &ld);

  print_list(&le); // 5 4 3 2 1

  return 0;
}

void print_maybe(struct maybe(pair(int, int)) m)
{
  match(m) {
    with(Nothing, _) {
      printf("Nothing\n");
    }
    with(Just, x) {
      printf("Just (%d, %d)\n", x.fst, x.snd);
    }
  }
}

void print_list(struct list(int) *l)
{
  match(*l) {
    with(Nil, _) {
      printf("\n");
    }
    with(Cons, v) {
      int x = v.head;
      struct list(int) *xs = v.tail;

      printf("%d ", x);
      print_list(xs);
    }
  }
}
