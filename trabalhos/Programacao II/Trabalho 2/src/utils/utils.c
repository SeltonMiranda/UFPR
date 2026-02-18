#include "../../includes/utils/utils.h"

int rand_between(int low, int high) {
  return low + (rand() % (high - low));
}

void must_init(bool test, const char *description) {
  if (test) return;
  printf("Couldn't initialize %s\n", description);
  exit(1);
}