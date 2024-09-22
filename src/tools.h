#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>

static inline int max(int x, int y) {
  return x > y ? x : y;
}

static inline int min(int x, int y) {
  return x < y ? x : y;
}

#define EXIT_ON_ERROR(Check, Message) \
  if (!(Check)) {\
    fprintf(stderr, Message);\
    exit(1);\
  }

#endif /* !TOOLS_H */

