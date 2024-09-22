#include "cursor.h"
#include "view/manager.h"
#include "view/view.h"
#include <ncurses.h>
#include <stdlib.h>

cursor *create_cursor(line *line) {
  cursor *cur = calloc(1, sizeof(cursor));
  cur->focus_line = line;
  return cur;
}

bool prev_line(void) {
  if (!get_current_view())
    return false;
  cursor *c = get_current_view()->cursor;
  if (c->focus_line->prev != NULL) {
    if (c->focus_line == get_current_view()->top_line)
      scroll_up();
    c->focus_line = c->focus_line->prev;
    return true;
  }
  return false;
}

bool next_line(void) {
  if (!get_current_view())
    return false;
  cursor *c = get_current_view()->cursor;
  if (c->focus_line->next != NULL) {
    if (c->focus_line == get_current_view()->bot_line)
      scroll_down();
    c->focus_line = c->focus_line->next;
    return true;
  }
  return false;
}

void set_cursor_visibility(enum cursor_visibility visibility) {
  curs_set(visibility);
}
