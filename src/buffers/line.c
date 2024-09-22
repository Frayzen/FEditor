#include "constants.h"

#include "constants.h"
#include "line.h"
#include <stdlib.h>
#include <string.h>

static inline line *create_line(char *from, int len, int pos) {
  line *l = malloc(sizeof(line));
  l->content = strndup(from, len);
  l->lenght = len;
  l->pos = pos;
  return l;
}

// return the size of the token (including delimiter) and replace the delimiter
// by NULL
// return the size of the token excluding delimiter if no more token can be read
static int tokenize(char *src) {
  char *find = strchrnul(src, '\n');
  if (!*find)
    return 0;
  *find = 0;
  return find - src + 1;
}

struct line *build_lines(char *content) {
  char *from = content;
  int cur_pos = 0;
  int len = tokenize(from);
  line *first = create_line(from, len, cur_pos++);
  line *nextln = first;
  line *curln = first;
  for (from += len; (len = tokenize(from)); from += len) {
    nextln = create_line(from, len, cur_pos++);
    curln->next = nextln;
    nextln->prev = curln;
    curln = nextln;
  }
  nextln->next = NULL;
  first->prev = NULL;
  return first;
}
