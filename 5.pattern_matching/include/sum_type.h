#ifndef __W_SUM_TYPE_H__
#define __W_SUM_TYPE_H__

#if __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifdef __GNUC__
////////////////////////////////////////////////////

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
