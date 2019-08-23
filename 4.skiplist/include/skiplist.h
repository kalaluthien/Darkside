#ifndef __W_SKIPLIST_H__
#define __W_SKIPLIST_H__

#if __cplusplus
extern "C" {
#endif

#include <stdbool.h>

////////////////////////////////////////////////////

struct skiplist_struct;

typedef struct skiplist_struct *skiplist_t;

skiplist_t skiplist_create(void);

void skiplist_destroy(skiplist_t list);

bool skiplist_is_empty(skiplist_t list);

void skiplist_insert(skiplist_t list, int key, void *value);

void skiplist_delete(skiplist_t list, int key);

bool skiplist_contains(skiplist_t list, int key);

void *skiplist_query(skiplist_t list, int key);

size_t skiplist_size(skiplist_t list);

void skiplist_print(skiplist_t list);

////////////////////////////////////////////////////

#if __cplusplus
}
#endif

#endif // __W_SKIPLIST_H__
