#include "line.h"
#include "constants.h"
#include <stdlib.h>
#include <string.h>

static inline line *create_line(char *from, char *to, int pos) {
  line *l = malloc( sizeof(line));
  unsigned long size = to - from;
  l->content = strndup(from, size);
  l->lenght = size;
  l->pos = pos;
  return l;
}

struct line *build_lines(char *content) {
  char *from = content;
  char *to = strchrnul(from, '\n');
  int cur_pos = 0;
  line *first = create_line(from, to, cur_pos++);
  line *nextln = first;
  line* curln = first;
  while (*to) {
    from = to + 1;
    to = strchrnul(from, '\n');
    nextln = create_line(from, to, cur_pos++);
    curln->next = nextln;
    nextln->prev = curln;
    curln = nextln;
  }
  nextln->next = NULL;
  first->prev = NULL;
  return first;
}
