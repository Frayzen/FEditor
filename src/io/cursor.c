#include "cursor.h"
#include "buffers/buffer.h"
#include "tools.h"
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

// accept negative values, clamp larger values
void gotoline(unsigned long id) {
  unsigned long nb_line = get_current_buffer()->last_line->pos;
  id = clamp(id, 0, nb_line);
  line *cur;
  if (id > nb_line / 2) {

    for (cur = get_current_buffer()->last_line; cur->pos != id; cur = cur->prev)
      ;
  } else {
    for (cur = get_current_buffer()->first_line; cur->pos != id; cur = cur->next)
      ;
  }
  get_current_view()->cursor->focus_line = cur;
  if (id < get_current_view()->top_line->pos)
    scroll_far(cur);
  if (id > get_current_view()->bot_line->pos)
    scroll_far(cur);
}

void bound_cursor(void) {
  view *v = get_current_view();
  cursor *crs = v->cursor;
  unsigned long pos = crs->focus_line->pos;
  if (pos <= v->top_line->pos)
    crs->focus_line = v->top_line;
  if (pos > v->bot_line->pos)
    crs->focus_line = v->bot_line;
}

void set_cursor_visibility(enum cursor_visibility visibility) {
  curs_set(visibility);
}
