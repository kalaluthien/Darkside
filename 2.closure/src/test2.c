#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "closure.h"

////////////////////////////////////////////////////
// Closure Example
////////////////////////////////////////////////////

struct pair_int { int x; int y; };

void closure_function(closure_env_t env, void *z)
{
#define get_from(e, m) ( ((struct pair_int *)closure_env_get_data(e))->m )

  /* 1. Deconstruct Input Environment & Argument */
  int *env_x = &get_from(env, x);
  int *env_y = &get_from(env, y);
  int arg_z = *((int *)&z);

  /* 2. Work on Environment */
  *env_x += arg_z;
  *env_y += arg_z;
  printf("(%d, %d)\n", *env_x, *env_y);

#undef get_from
}

closure_t closure_factory(int x, int y)
{
  /* 1. Construct Input Environment */
  struct pair_int input = { .x = x, .y = y };

  /* 2. Save Environment with Function */
  return closure_create(closure_function, sizeof(input), &input);
}

////////////////////////////////////////////////////
// Closure Test
////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  closure_t clos1 = closure_factory(1, 2);
  closure_t clos2 = closure_factory(2, 1);

  closure_call(clos1, (void *)1); // (2, 3)
  closure_call(clos2, (void *)2); // (4, 3)
  closure_call(clos1, (void *)3); // (5, 8)
  closure_call(clos2, (void *)4); // (8, 7)

  closure_destroy(clos1);
  closure_destroy(clos2);

  return 0;
}
