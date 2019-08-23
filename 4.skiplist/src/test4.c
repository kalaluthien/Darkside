#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "skiplist.h"

#define len(l) ( sizeof(l) / sizeof((l)[0]) )

////////////////////////////////////////////////////
// Skiplist Test
////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  skiplist_t list = skiplist_create();

  int values[] = {
    12, 345, 67, 891, 2, 34, 5, 678, 91, 23, 456, 78, 9, 123
  };

  printf("\n==================[Test1 - is_empty]=================\n");
  printf(" * is_empty = %d\n", skiplist_is_empty(list));
  printf(" * size = %d\n", skiplist_size(list));

  printf("\n==================[Test1 - insert]=================\n");
  for (int i = 0; i < len(values); i++) {
    printf(" * insert %d\n", values[i]);
    skiplist_insert(list, values[i], &values[i]);
  }
  skiplist_print(list);
  printf(" * size = %d\n", skiplist_size(list));

  printf("\n==================[Test2 - query]=================\n");
  for (int i = 0; i < len(values); i++) {
    int *vp = (int *)skiplist_query(list, values[i]);
    if (vp) {
      printf(" * query %d = %d\n", values[i], *vp);
    }
  }
  printf(" * size = %d\n", skiplist_size(list));

  printf("\n==================[Test3 - delete]=================\n");
  for (int i = 0; i < len(values); i += 3) {
    printf(" * delete %d\n", values[i]);
    skiplist_delete(list, values[i]);
  }
  skiplist_print(list);
  printf(" * size = %d\n", skiplist_size(list));

  printf("\n==================[Test4 - query]=================\n");
  for (int i = 0; i < len(values); i++) {
    int *vp = (int *)skiplist_query(list, values[i]);
    if (vp) {
      printf(" * query %d = %d\n", values[i], *vp);
    }
    else {
      printf(" * query %d = (nil)\n", values[i]);
    }
  }
  printf(" * size = %d\n", skiplist_size(list));

  return 0;
}
