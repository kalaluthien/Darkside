#include <stdio.h>

#include "utils.h"

int main(int argc, char *argv[])
{
  int a = _MACRO_GET_LAST(10);

  int b = _MACRO_GET_LAST(10, 20);

  int c = _MACRO_GET_LAST(10, 20, 30);

  int d = _MACRO_GET_LAST(10, 20, 30, 40, 50, 60, 70, 80);

  int e = _MACRO_GET_LAST(10, 20, 30, 40, 50, 60, 70, 80, 90);

  printf("[last] a=%d(10), b=%d(20), c=%d(30), d=%d(80), e=%d(90)\n",
      a, b, c, d, e);

  a = _MACRO_GET_LAST(_MACRO_GET_TAIL(10, 20));

  b = _MACRO_GET_LAST(_MACRO_GET_TAIL(10, 20, 30));

  c = _MACRO_GET_LAST(_MACRO_GET_TAIL(10, 20, 30, 40));

  d = _MACRO_GET_LAST(_MACRO_GET_TAIL(10, 20, 30, 40, 50, 60, 70, 80, 90));

  printf("[tail] a=%d(10), b=%d(20), c=%d(30), d=%d(80)\n",
      a, b, c, d);

  return 0;
}
