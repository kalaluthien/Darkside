#ifndef __W_SUM_TYPE_H__
#define __W_SUM_TYPE_H__

#if __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifdef __GNUC__
////////////////////////////////////////////////////

#define sumtype(name, ...) \
typedef struct name {\
    enum { SUM_TYPE_TAG(__VA_ARGS__) } match_tag; \
    union { SUM_TYPE_VAL(__VA_ARGS__) } match_val; \
} name

#define SUM_TYPE_TAG(...) SUM_TYPE_TAG_(COUNT(__VA_ARGS__))(__VA_ARGS__)
#define SUM_TYPE_TAG_(N) SUM_TYPE_TAG__(N)
#define SUM_TYPE_TAG__(N) SUM_TYPE_TAG ## N

#define SUM_TYPE_TAG2(type, name) name
#define SUM_TYPE_TAG4(type, name, ...) name, SUM_TYPE_TAG2(__VA_ARGS__)
#define SUM_TYPE_TAG6(type, name, ...) name, SUM_TYPE_TAG4(__VA_ARGS__)
#define SUM_TYPE_TAG8(type, name, ...) name, SUM_TYPE_TAG6(__VA_ARGS__)

#define SUM_TYPE_VAL(...) SUM_TYPE_VAL_(COUNT(__VA_ARGS__))(__VA_ARGS__)
#define SUM_TYPE_VAL_(N) SUM_TYPE_VAL__(N)
#define SUM_TYPE_VAL__(N) SUM_TYPE_VAL ## N

#define SUM_TYPE_VAL2(type, name) type name;
#define SUM_TYPE_VAL4(type, name, ...) type name; SUM_TYPE_VAL2(__VA_ARGS__)
#define SUM_TYPE_VAL6(type, name, ...) type name; SUM_TYPE_VAL4(__VA_ARGS__)
#define SUM_TYPE_VAL8(type, name, ...) type name; SUM_TYPE_VAL6(__VA_ARGS__)

#define COUNT(...) COUNT_(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1)
#define COUNT_(A1, A2, A3, A4, A5, A6, A7, A8, N, ...) N

#define case_of(tag, val) { .match_tag = tag, .match_val.tag = val }

#define match(object) \
  for (bool done = false; !done; done = true)\
    for (typeof(object) _object = object; !done; done = true)

#define with(tag, var) \
  if (_object.match_tag == tag && !done)\
    for (var = _object.match_val.tag; !done; done = true)

////////////////////////////////////////////////////
#endif

#if __cplusplus
}
#endif

#endif // __W_SUM_TYPE_H__
