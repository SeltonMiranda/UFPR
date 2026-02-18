#ifndef __UTILS__
#define __UTILS__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int rand_between(int low, int high);

void must_init(bool test, const char *description);

#endif  // __UTILS__