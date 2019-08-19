#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#include "set.h"

#define SET_MAX_LEVEL 10

#define int_of(x) ( *((int *)&(x)) )

struct set_node_struct {
  set_t parent;
  struct set_node_struct *next[SET_MAX_LEVEL];
  int level;
  char data[];
};

////////////////////////////////////////////////////
// Set Object Management APIs
////////////////////////////////////////////////////

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
  // TODO: implement this after all
}

////////////////////////////////////////////////////
// Set Operation APIs
////////////////////////////////////////////////////

static void set_add_generic(set_t set, void *elem);
static void set_add_default(set_t set, int elem);

void set_add(set_t set, void *elem)
{
  if (set->compare) {
    set_add_generic(set, elem);
  }
  else {
    set_add_default(set, int_of(elem));
  }
}

static void set_remove_generic(set_t set, void *elem);
static void set_remove_default(set_t set, int elem);

void set_remove(set_t set, void *elem)
{
  if (set->compare) {
    set_remove_generic(set, elem);
  }
  else {
    set_remove_default(set, int_of(elem));
  }
}

static bool set_contains_generic(set_t set, void *elem);
static bool set_contains_default(set_t set, int elem);

bool set_contains(set_t set, void *elem)
{
  if (set->compare) {
    return set_contains_generic(set, elem);
  }
  else {
    return set_contains_default(set, int_of(elem));
  }
}

////////////////////////////////////////////////////
// Generic Set Operation Implementations
////////////////////////////////////////////////////

void set_add_generic(set_t set, void *elem)
{
  // TODO
}

void set_remove_generic(set_t set, void *elem)
{
  // TODO
}

bool set_contains_generic(set_t set, void *elem)
{
  // TODO
  return false;
}

////////////////////////////////////////////////////
// Default Set Operation Implementations
////////////////////////////////////////////////////

void set_add_default(set_t set, int elem)
{
  // TODO
}

void set_remove_default(set_t set, int elem)
{
  // TODO
}

bool set_contains_default(set_t set, int elem)
{
  // TODO
  return false;
}
