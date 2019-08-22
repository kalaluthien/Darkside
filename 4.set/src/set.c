#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#include "set.h"

#define SET_MAX_LEVEL 10

struct set_node_struct;

typedef struct set_node_struct *node_t;

struct set_node_struct {
  node_t next[SET_MAX_LEVEL];
  int level;
  int key;
  void *value;
};

struct set_struct {
  node_t head;
  node_t tail;
};

////////////////////////////////////////////////////
// Set Object Management APIs
////////////////////////////////////////////////////

set_t set_create()
{
  set_t set = (set_t)malloc(sizeof(struct set_struct));

  set->head = (node_t)malloc(sizeof(struct set_node_struct));
  set->tail = (node_t)malloc(sizeof(struct set_node_struct));

  for (int i = 0; i < SET_MAX_LEVEL; i++) {
    set->head->next[i] = set->tail;
    set->tail->next[i] = NULL;
  }

  set->head->level = SET_MAX_LEVEL;
  set->tail->level = SET_MAX_LEVEL;

  set->head->key = INT_MIN;
  set->tail->key = INT_MAX;

  set->head->value = NULL;
  set->tail->value = NULL;

  return set;
}

void set_destroy(set_t set)
{
  node_t prev = set->head;

  while (prev != set->tail) {
    node_t succ = prev->next[0];
    free(prev);
    prev = succ;
  }

  free(set->tail);
}

////////////////////////////////////////////////////
// Set Operation APIs
////////////////////////////////////////////////////

bool set_is_empty(set_t set)
{
  return set->tail == set->head->next[0];
}

void set_insert(set_t set, int key, void *value)
{
  srand(time(NULL));

  node_t prevs[SET_MAX_LEVEL];
  node_t prev = set->head;

  for (int l = SET_MAX_LEVEL - 1; l >= 0; l--) {
    while (prev->next[l]->key < key) {
      prev = prev->next[l];
    }
    prevs[l] = prev;
  }

  node_t succ = prev->next[0];

  if (succ->key == key) {
    succ->value = value;
    return;
  }

  node_t curr = (node_t)malloc(sizeof(struct set_node_struct));

  memset(curr->next, 0, sizeof(node_t) * SET_MAX_LEVEL);
  curr->level = rand() % SET_MAX_LEVEL + 1;
  curr->key = key;
  curr->value = value;

  for (int l = 0; l < curr->level; l++) {
    curr->next[l] = prevs[l]->next[l];
    prevs[l]->next[l] = curr;
  }
}

void set_delete(set_t set, int key)
{
  node_t prevs[SET_MAX_LEVEL];
  node_t prev = set->head;

  for (int l = SET_MAX_LEVEL - 1; l >= 0; l--) {
    while (prev->next[l]->key < key) {
      prev = prev->next[l];
    }
    prevs[l] = prev;
  }

  node_t succ = prev->next[0];

  if (succ->key == key) {
    for (int l = 0; l < succ->level; l++) {
      prevs[l]->next[l] = succ->next[l];
    }
    free(succ);
  }
}

bool set_contains(set_t set, int key)
{
  node_t prev = set->head;

  for (int l = SET_MAX_LEVEL - 1; l >= 0; l--) {
    while (prev->next[l]->key < key) {
      prev = prev->next[l];
    }
  }

  node_t succ = prev->next[0];

  return succ->key == key;
}

void *set_query(set_t set, int key)
{
  node_t prev = set->head;

  for (int l = SET_MAX_LEVEL - 1; l >= 0; l--) {
    while (prev->next[l]->key < key) {
      prev = prev->next[l];
    }
  }

  node_t succ = prev->next[0];

  return (succ->key == key) ? succ->value : NULL;
}
