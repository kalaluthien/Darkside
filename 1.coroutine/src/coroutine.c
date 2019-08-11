#include <stdlib.h>
#include <alloca.h>
#include <setjmp.h>

#include "coroutine.h"

struct coroutine_struct {
  jmp_buf env;
  coroutine_func_t func;
};

////////////////////////////////////////////////////
// Coroutine Object Management APIs
////////////////////////////////////////////////////

coroutine_t coroutine_create(coroutine_func_t func)
{
  coroutine_t coro = (coroutine_t)malloc(sizeof(struct coroutine_struct));
  coro->func = func;
  return coro;
}

void coroutine_destroy(coroutine_t coro)
{
  if (coro) {
    free(coro);
  }
}

////////////////////////////////////////////////////
// Coroutine Execution APIs
////////////////////////////////////////////////////

#define extend_stack(stack_top) ( stack_top -= (1 << 10) )

void coroutine_spawn(coroutine_t from, coroutine_t to, void *arg)
{
  static char *stack_top = NULL;
  static coroutine_t saved_from = NULL;
  static coroutine_t saved_to = NULL;
  static void *saved_arg = NULL;

  if (!stack_top) stack_top = (char *)&arg;

  extend_stack(stack_top);

  size_t stack_size = (size_t)((char *)&arg - stack_top);

  volatile char *stack_displ = (char *)alloca(stack_size);

  /* Thread-unsafe implementation */
  saved_from = from;
  saved_to = to;
  saved_arg = arg;

  if (setjmp(to->env)) {
    saved_to->func(saved_arg);
    longjmp(saved_from->env, 1);
  }
}

void coroutine_yield(coroutine_t from, coroutine_t to)
{
  if (!setjmp(from->env)) {
    longjmp(to->env, 1);
  }
}
