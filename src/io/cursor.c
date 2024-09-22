#include "cursor.h"
#include "tools.h"
#include "ui.h"
#include <ncurses.h>
#include <stdlib.h>

cursor* create_cursor(line* line)
{
  cursor* cur = calloc(1, sizeof(cursor));
  cur->cur_line = line;
  return cur;
}

void set_pos(int next_x, int next_y) {
  cursor* c = get_current_view()->cursor;
  int x = max(0, min(next_x, c->cur_line->lenght));
  int y = max(0, min(next_y, win_stats.rows));
  if (x < next_x)
    y++;
  // if (y < next_y) TODO
  // if (y > next_y) TODO
  c->pos_x = x;
  c->pos_y = y;
}
void add_pos(int x, int y) {
  cursor* c = get_current_view()->cursor;
  set_pos(c->pos_x + x, c->pos_y + y); 
}
void write_char(char c) {
  static char str[2] = {0};
  str[0] = c;
  printw("%s", str);
}
void set_cursor_visibility(enum cursor_visibility visibility) {
  curs_set(visibility);
}
void reset_cursor(void)
{
  cursor* c = get_current_view()->cursor;
  move(c->pos_y, c->pos_x);
}
