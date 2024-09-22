#ifndef CURSOR_H
#define CURSOR_H

#include "buffers/line.h"
#include <stdbool.h>

enum cursor_visibility {
  INVISIBLE = 0,
  LINE = 1,
  BLOCK = 2,
};

typedef struct cursor {
  int pos_x, pos_y;
  line* cur_line;
} cursor;

void set_pos(int x, int y);
void add_pos(int x, int y);
void write_char(char c);
void set_cursor_visibility(enum cursor_visibility visibility);
void reset_cursor(void);
cursor* create_cursor(line* line);

#endif /* !CURSOR_H */
