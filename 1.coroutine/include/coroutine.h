#ifndef __W_COROUTINE_H__
#define __W_COROUTINE_H__

#if __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////

#include <setjmp.h>

typedef struct coroutine_struct *coroutine_t;

typedef void (*coroutine_func_t)(void *);

coroutine_t coroutine_create(coroutine_func_t func);

void coroutine_destroy(coroutine_t coro);

void coroutine_spawn(coroutine_t from, coroutine_t to, void *arg);

void coroutine_yield(coroutine_t from, coroutine_t to);

////////////////////////////////////////////////////

#if __cplusplus
}
#endif

#endif // __W_COROUTINE_H__
