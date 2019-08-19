#ifndef __W_SET_H__
#define __W_SET_H__

#if __cplusplus
extern "C" {
#endif

#include <stdbool.h>

////////////////////////////////////////////////////

struct set_node_struct;

struct set_struct {
  struct set_node_struct *head;
  struct set_node_struct *tail;
  size_t data_size;
  bool (*compare)(void *, void *);
};

typedef struct set_struct *set_t;

void set_init(set_t set, size_t data_size, bool (*compare)(void *, void *));

void set_destroy(set_t set);

void set_add(set_t set, void *elem);

void set_remove(set_t set, void *elem);

bool set_contains(set_t set, void *elem);

////////////////////////////////////////////////////

#if __cplusplus
}
#endif

#endif // __W_SET_H__
