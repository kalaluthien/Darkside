#ifndef __W_LAMBDA_H__
#define __W_LAMBDA_H__

#if __cplusplus
extern "C" {
#endif

#include "utils.h"

////////////////////////////////////////////////////

#define lambda(ret_type, ...) \
  (ret_type (*) (GET_INIT(__VA_ARGS__)))\
  lambda_from_string(\
      STRINGIFY(ret_type),\
      STRINGIFY(GET_INIT(__VA_ARGS__)),\
      GET_LAST(__VA_ARGS__))

void *lambda_from_string(
    const char *return_type,
    const char *arguments,
    const char *body);

////////////////////////////////////////////////////

#if __cplusplus
}
#endif

#endif // __W_LAMBDA_H__
