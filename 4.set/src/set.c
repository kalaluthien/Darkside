#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "set.h"

#define SET_MAX_LEVEL 10

struct set_node_struct {
  set_t parent;
  struct set_node_struct *next[SET_MAX_LEVEL];
  int level;
  char data[];
};

void set_init(set_t set, size_t data_size, bool (*compare)(void *, void *))
{
  set->head = (struct set_node_struct *)
    malloc(sizeof(struct set_node_struct) + data_size);

  set->tail = (struct set_node_struct *)
    malloc(sizeof(struct set_node_struct) + data_size);

  set->head->parent = set->tail->parent = set;
  set->head->level = set->tail->level = SET_MAX_LEVEL;

  for (int i = 0; i < SET_MAX_LEVEL; i++) {
    set->head->next[i] = set->tail;
    set->tail->next[i] = NULL;
  }

  set->data_size = data_size;
  set->compare = compare;
}

void set_destroy(set_t set)
{
  // TODO
}

void set_add(set_t set, void *elem)
{
  // TODO
}

void set_remove(set_t set, void *elem)
{
  // TODO
}
