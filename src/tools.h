#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>
#include <errno.h>
#include <string.h>

static inline int max(int x, int y) {
  return x > y ? x : y;
}

static inline int min(int x, int y) {
  return x < y ? x : y;
}

#define EXIT_ON_ERROR(Check, Message) \
  if (!(Check)) {\
    fprintf(stderr, "%s", Message);\
    exit(1);\
  }


#define EXIT_ON_ERRNO(Check) EXIT_ON_ERROR(Check, strerror(errno))

#endif /* !TOOLS_H */

