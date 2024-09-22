#include "view.h"
#include "buffers/line.h"
#include "io/colors.h"
#include "tools.h"
#include "view/manager.h"
#include <ncurses.h>
#include <stdlib.h>

view *create_view(WINDOW *win, buffer *buf) {
  view *cur = calloc(1, sizeof(view));
  getmaxyx(win, cur->h, cur->w);
  cur->cursor = create_cursor(buf->first_line);
  cur->win = win;
  cur->buffer = buf;
  cur->top_line = buf->first_line;
  if (!get_current_view())
    set_current_view(cur);
  return cur;
}

void write_txt(WINDOW *w, char *line, int is_focus) {
  if (is_focus) // FOCUS LINE ON
    wattron(w, A_BOLD);
  wprintw(w, "%s", line);
  if (is_focus) // FOCUS LINE OFF
    wattroff(w, A_BOLD);
}

void write_number(WINDOW *w, unsigned long val, int is_focus) {
  static unsigned long last = -1;
  if (last == val)
    return;
  last = val;
  if (is_focus) {
    wattron(w, A_BOLD);
    wattron(w, COLOR_PAIR(FOCUS_PAIR)); // FOCUS LINE ON
  }
  wprintw(w, "%4lu", val);
  if (is_focus) {
    wattroff(w, A_BOLD);
    wattroff(w, COLOR_PAIR(FOCUS_PAIR)); // FOCUS LINE ON
  }
}

int write_line(view *v, line *cur, int h) {
  WINDOW *w = v->win;

  // Define consts
  const int size_line_nb = min(5, v->w - 1);
  const int is_focus = cur == v->cursor->focus_line;

  // Define loop elements
  int remain = cur->lenght;
  char *begin = cur->content;

  do {
    int len = min(v->w - size_line_nb, remain);
    char *end = begin + len;
    remain -= len;
    // PRINT LINE NUMBER
    wmove(w, h, 0);
    write_number(w, cur->pos + 1, is_focus);
    // PRINT LINE TEXT
    char save = *end; // SAVE THE END CHAR
    *end = 0;         // NULL TERMINATE
    wmove(w, h, size_line_nb);
    write_txt(w, begin, is_focus);
    *end = save; // RESTORE
    begin = end;
    h++;
  } while (remain != 0 && h != v->h);
  return h;
}

void render_view(view *v) {
  line *cur = v->top_line;
  int h = 0;
  while (h < v->h && cur) {
    v->bot_line = cur;
    h = write_line(v, cur, h);
    cur = cur->next;
  }
}

void scroll_down(void) {
  if (!get_current_view()->top_line->next)
    return;
  if (get_current_view()->cursor->focus_line == get_current_view()->top_line)
    get_current_view()->cursor->focus_line = get_current_view()->cursor->focus_line->next;
  get_current_view()->top_line = get_current_view()->top_line->next;
  get_current_view()->bot_line = get_current_view()->bot_line->next;
  wclear(get_current_view()->win);
}
void scroll_up(void)
{
  if (!get_current_view()->top_line->prev)
    return;
  if (get_current_view()->cursor->focus_line == get_current_view()->bot_line)
    get_current_view()->cursor->focus_line = get_current_view()->cursor->focus_line->prev;
  get_current_view()->top_line = get_current_view()->top_line->prev;
  get_current_view()->bot_line = get_current_view()->bot_line->prev;
  wclear(get_current_view()->win);
}
