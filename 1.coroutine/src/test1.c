#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "coroutine.h"

#define DEFAULT_COUNT 4

////////////////////////////////////////////////////
// Coroutine Example
////////////////////////////////////////////////////

static coroutine_t coro[2];
struct range { int begin; int end; int *it; bool *done; };

void generator_func(void *arg) {
  struct range range = *((struct range *)arg);

  *range.done = false;

  for (int i = range.begin; i < range.end; i++) {
    *range.it = i;
    *range.done = (i == range.end - 1);
    coroutine_yield(coro[1], coro[0]);
  }
}

////////////////////////////////////////////////////
// Coroutine Test
////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  int count;

  /* 1. Argument Parsing */
  if (argc < 2) {
    count = DEFAULT_COUNT;
  }
  else {
    count = atoi(argv[1]);

    if (count < 1) {
      fprintf(stderr, " Usage: %s [range]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  /* 2. Lift Subroutines to Coroutine */
  coro[0] = coroutine_create(NULL);
  coro[1] = coroutine_create(generator_func);

  /* 3. Create & Spawn Generator */
  int it = 0;
  bool done = false;
  struct range range = {
    .begin = 0,
    .end = count,
    .it = &it,
    .done = &done
  };

  printf("Test starts with %d\n", count);

  coroutine_spawn(coro[0], coro[1], &range);

  /* 4. Yield Generator */
  while (*range.done == false) {
    coroutine_yield(coro[0], coro[1]);
    printf("Got %d\n", *range.it);
  }

  printf("Test done\n");

  /* 5. Release Resources */
  coroutine_destroy(coro[0]);
  coroutine_destroy(coro[1]);

  return 0;
}
