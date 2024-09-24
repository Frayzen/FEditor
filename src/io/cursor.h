#ifndef CURSOR_H
#define CURSOR_H

#include "buffers/line.h"
#include <stdbool.h>

enum cursor_visibility {
  INVISIBLE = 0,
  BLINK = 1,
  BLOCK = 2,
};

typedef struct cursor {
  line* focus_line;
  int cur_char;
} cursor;

bool prev_line(void);
bool next_line(void);
void set_cursor_visibility(enum cursor_visibility visibility);
cursor* create_cursor(line* line);
void goto_line_id(unsigned long id); // accept negative values, clamp larger values
void goto_line(line *l); 
void bound_cursor(void);
void center_cursor(void);
cursor* get_current_cursor(void);

#endif /* !CURSOR_H */
