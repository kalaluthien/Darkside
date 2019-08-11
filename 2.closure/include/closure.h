#ifndef __W_CLOSURE_H__
#define __W_CLOSURE_H__

#if __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////

typedef struct closure_env_struct *closure_env_t;

size_t closure_env_get_size(closure_env_t env);

void *closure_env_get_data(closure_env_t env);

typedef void (*closure_func_t)(closure_env_t, void *);

typedef struct closure_struct *closure_t;

closure_t closure_create(closure_func_t func, size_t size, const void *data_addr);

void closure_destroy(closure_t clos);

void closure_call(closure_t clos, void *arg);

////////////////////////////////////////////////////

#if __cplusplus
}
#endif

#endif // __W_CLOSURE_H__
