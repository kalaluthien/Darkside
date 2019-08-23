#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <dlfcn.h>

void *lambda_from_string(
    const char *return_type,
    const char *arguments,
    const char *body)
{
  static bool initialized = false;

  if (!initialized) {
    srand(time(NULL));
    initialized = true;
  }

  int id = rand();

  char path[FILENAME_MAX];
  getcwd(path, FILENAME_MAX);

  char buffer[1024];
  sprintf(buffer, "%s/.func_%d.c", path, id);

  FILE *ostream = fopen(buffer, "w");
  if (!ostream) return NULL;

  sprintf(buffer, "%s func_%d(%s) { %s }",
      return_type, id, arguments, body);

  size_t length = strlen(buffer);
  size_t wcount = fwrite(buffer, sizeof(char), length, ostream);

  fclose(ostream);

  if (wcount != length) return NULL;

  sprintf(buffer, "gcc -fPIC -c %s/.func_%d.c -o %s/.func_%d.o",
      path, id, path, id);

  if (system(buffer) != EXIT_SUCCESS) return NULL;

  sprintf(buffer, "rm %s/.func_%d.c", path, id);

  if (system(buffer) != EXIT_SUCCESS) return NULL;

  sprintf(buffer, "gcc --shared -fPIC -o %s/.func_%d.so %s/.func_%d.o",
      path, id, path, id);

  if (system(buffer) != EXIT_SUCCESS) return NULL;

  sprintf(buffer, "rm %s/.func_%d.o", path, id);

  if (system(buffer) != EXIT_SUCCESS) return NULL;

  sprintf(buffer, "%s/.func_%d.so", path, id);

  void *handle = dlopen(buffer, RTLD_NOW);
  if (!handle) {
    fputs(dlerror(), stderr);
    exit(EXIT_FAILURE);
  }

  sprintf(buffer, "func_%d", id);

  return dlsym(handle, buffer);
}
