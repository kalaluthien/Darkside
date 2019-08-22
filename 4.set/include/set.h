#ifndef __W_SET_H__
#define __W_SET_H__

#if __cplusplus
extern "C" {
#endif

#include <stdbool.h>

////////////////////////////////////////////////////

struct set_struct;

typedef struct set_struct *set_t;

set_t set_create(void);

void set_destroy(set_t set);

bool set_is_empty(set_t set);

void set_insert(set_t set, int key, void *value);

void set_delete(set_t set, int key);

bool set_contains(set_t set, int key);

void *set_query(set_t set, int key);

////////////////////////////////////////////////////

#if __cplusplus
}
#endif

#endif // __W_SET_H__
