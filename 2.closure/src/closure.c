#include <stdlib.h>
#include <string.h>

#include "closure.h"

struct closure_env_struct {
  size_t size;
  char data[];
};

struct closure_struct {
  closure_env_t env;
  closure_func_t func;
};

////////////////////////////////////////////////////
// Closure Environment APIs
////////////////////////////////////////////////////

size_t closure_env_get_size(closure_env_t env)
{
  return env->size;
}

void *closure_env_get_data(closure_env_t env)
{
  return (void *)env->data;
}

////////////////////////////////////////////////////
// Closure APIs
////////////////////////////////////////////////////

closure_t closure_create(closure_func_t func, size_t size, const void *data_addr)
{
  closure_env_t env =
    (closure_env_t)malloc(sizeof(struct closure_env_struct) + size);

  memcpy(env->data, data_addr, size);

  closure_t clos = (closure_t)malloc(sizeof(struct closure_struct));
  clos->env = env;
  clos->func = func;

  return clos;
}

void closure_destroy(closure_t clos)
{
  if (clos) {
    if (clos->env) {
      free(clos->env);
    }
    free(clos);
  }
}

void closure_call(closure_t clos, void *arg)
{
  clos->func(clos->env, arg);
}
