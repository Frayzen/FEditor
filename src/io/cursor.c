#include "cursor.h"
#include "ui.h"
#include <ncurses.h>
#include <stdlib.h>

cursor* create_cursor(line* line)
{
  cursor* cur = calloc(1, sizeof(cursor));
  cur->focus_line = line;
  return cur;
}

bool prev_line(void)
{
 cursor* c = get_current_view()->cursor; 
 if (c->focus_line->prev != NULL)
 {
   c->focus_line = c->focus_line->prev;
   return true;
 }
 return false;
}

bool next_line(void)
{
 cursor* c = get_current_view()->cursor; 
 if (c->focus_line->next != NULL)
 {
   c->focus_line = c->focus_line->next;
   return true;
 }
 return false;
}

void set_cursor_visibility(enum cursor_visibility visibility) {
  curs_set(visibility);
}
