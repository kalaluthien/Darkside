#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#include "skiplist.h"

#define MAX_LEVEL 6

struct skiplist_node_struct;

typedef struct skiplist_node_struct *node_t;

struct skiplist_node_struct {
  node_t next[MAX_LEVEL];
  int level;
  int key;
  void *value;
};

struct skiplist_struct {
  node_t head;
  node_t tail;
};

////////////////////////////////////////////////////
// list Object Management APIs
////////////////////////////////////////////////////

skiplist_t skiplist_create()
{
  skiplist_t list = (skiplist_t)malloc(sizeof(struct skiplist_struct));

  list->head = (node_t)malloc(sizeof(struct skiplist_node_struct));
  list->tail = (node_t)malloc(sizeof(struct skiplist_node_struct));

  for (int l = 0; l < MAX_LEVEL; l++) {
    list->head->next[l] = list->tail;
    list->tail->next[l] = NULL;
  }

  list->head->level = MAX_LEVEL;
  list->tail->level = MAX_LEVEL;

  list->head->key = INT_MIN;
  list->tail->key = INT_MAX;

  list->head->value = NULL;
  list->tail->value = NULL;

  return list;
}

void skiplist_destroy(skiplist_t list)
{
  if (list) {
    node_t prev = list->head;

    while (prev != list->tail) {
      node_t succ = prev->next[0];
      free(prev);
      prev = succ;
    }

    free(list->tail);
    free(list);
  }
}

////////////////////////////////////////////////////
// list Operation APIs
////////////////////////////////////////////////////

bool skiplist_is_empty(skiplist_t list)
{
  return list->tail == list->head->next[0];
}

static int random_level(void);

void skiplist_insert(skiplist_t list, int key, void *value)
{
  node_t prevs[MAX_LEVEL];
  node_t prev = list->head;

  for (int l = MAX_LEVEL - 1; l >= 0; l--) {
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

  node_t curr = (node_t)malloc(sizeof(struct skiplist_node_struct));

  memset(curr->next, 0, sizeof(node_t) * MAX_LEVEL);
  curr->level = random_level();
  curr->key = key;
  curr->value = value;

  for (int l = 0; l < curr->level; l++) {
    curr->next[l] = prevs[l]->next[l];
    prevs[l]->next[l] = curr;
  }
}

void skiplist_delete(skiplist_t list, int key)
{
  node_t prevs[MAX_LEVEL];
  node_t prev = list->head;

  for (int l = MAX_LEVEL - 1; l >= 0; l--) {
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

bool skiplist_contains(skiplist_t list, int key)
{
  node_t prev = list->head;

  for (int l = MAX_LEVEL - 1; l >= 0; l--) {
    while (prev->next[l]->key < key) {
      prev = prev->next[l];
    }
  }

  node_t succ = prev->next[0];

  return succ->key == key;
}

void *skiplist_query(skiplist_t list, int key)
{
  node_t prev = list->head;

  for (int l = MAX_LEVEL - 1; l >= 0; l--) {
    while (prev->next[l]->key < key) {
      prev = prev->next[l];
    }
  }

  node_t succ = prev->next[0];

  return (succ->key == key) ? succ->value : NULL;
}

static node_t begin(skiplist_t list);
static node_t end(skiplist_t list);

size_t skiplist_size(skiplist_t list)
{
  size_t num = 0;

  for (node_t it = begin(list); it != end(list); it = it->next[0]) {
    num++;
  }

  return num;
}

void skiplist_print(skiplist_t list)
{
  if (skiplist_is_empty(list)) {
    printf("(nil)\n");
    return;
  }

  printf("elements:\n");
  for (int l = MAX_LEVEL - 1; l >= 0; l--) {
    node_t prev = list->head->next[l];

    printf("[%d]", l+1);

    while (prev != list->tail) {
      printf(" (%d)", prev->key);
      prev = prev->next[l];
    }

    printf("\n");
  }
  printf("\n");

  printf("levels:");
  for (node_t it = begin(list); it != end(list); it = it->next[0]) {
    printf(" %d", it->level);
  }
  printf("\n");
}

////////////////////////////////////////////////////
// Utilities
////////////////////////////////////////////////////

static int random_level()
{
  static bool initialized = false;

  if (!initialized) {
    srand(time(NULL));
    initialized = true;
  }

  int level = 0;

  while (level < MAX_LEVEL) {
    level++;
    if (rand() % 2) break;
  }

  return level;
}

static node_t begin(skiplist_t list)
{
  return list->head->next[0];
}

static node_t end(skiplist_t list)
{
  return list->tail;
}
