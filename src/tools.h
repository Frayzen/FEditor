#ifndef TOOLS_H
#define TOOLS_H

#include "io/ui.h"
#include <errno.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

static inline int max(int x, int y) { return x > y ? x : y; }

static inline int min(int x, int y) { return x < y ? x : y; }

static inline int clamp(int x, int l, int h) {
  return (x) > (h) ? (h) : ((x) < (l) ? (l) : (x));
}

#define EXIT_ON_ERROR(Check, Message)                                          \
  if (!(Check)) {                                                              \
    fprintf(stderr, "%s", (Message));                                          \
    exit(1);                                                                   \
  }

#define EXIT_ON_ERRNO(Check) EXIT_ON_ERROR(Check, strerror(errno))

#define DBG(Str, Val)                                                          \
  move(win_stats.rows - 1, 12);                                                \
  printw(Str, Val);

typedef void (*callback)(void);

#endif /* !TOOLS_H */
