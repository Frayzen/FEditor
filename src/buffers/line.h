#ifndef LINE_H
#define LINE_H

#include "frwd.h"

typedef struct line {
  char *content;
  unsigned long lenght;
  unsigned long pos;
  struct line *next; // NULL IF LAST
  struct line *prev; // NULL IF FIRST
} line;

void build_lines(struct buffer* buf, char *content);

#endif /* !LINE_H */
