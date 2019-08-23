#include <stdio.h>
#include <stdlib.h>

#include "lambda.h"

typedef int (*monadic_t)(int);
typedef int (*dyadic_t)(int, int);

int main(int argc, char *argv[])
{
  dyadic_t foo = lambda(int, int x, int y, "return x * x + y * y;");

  int x = 3;
  int y = 4;
  int z = foo(x, y);

  printf("%d^2 + %d^2 = %d\n", x, y, z);

  monadic_t relu = lambda(int, int x, "return (x > 0) ? x : 0;");

  int v = -7;
  int w = relu(v);

  printf("ReLU(%d) = %d\n", -7, w);

  return 0;
}
