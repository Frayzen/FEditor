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

void write_txt(WINDOW* w, char *line, int is_focus) {
  if (is_focus) // FOCUS LINE ON
    wattron(w, A_BOLD);
  wprintw(w, "%s", line);
  if (is_focus) // FOCUS LINE OFF
    wattroff(w, A_BOLD);
}

void write_number(WINDOW* w, unsigned long val, int is_focus) {
  if (is_focus) {
    wattron(w, A_BOLD);
    wattron(w, COLOR_PAIR(FOCUS_PAIR)); // FOCUS LINE ON
  }
  wprintw(w, "%4lu", val + 1);
  if (is_focus) {
    wattroff(w, A_BOLD);
    wattroff(w, COLOR_PAIR(FOCUS_PAIR)); // FOCUS LINE ON
  }
}

void render_view(view *v) {
  int size_line_nb = 5;

  int h = 0;
  line *cur = v->top_line;
  int remain = cur->lenght;
  WINDOW *w = v->win;
  while (h < v->h && cur) {
    int is_focus = cur == v->cursor->focus_line;
    char *begin = cur->content;
    int len = min(v->w, remain);
    char *end = begin + len;
    remain -= len;
    char save = *end;
    // PRINT LINE NUMBER
    wmove(w, h, 0);
    write_number(w, cur->pos + 1, is_focus);
    // PRINT LINE TEXT
    wmove(w, h, size_line_nb);
    write_txt(w, begin, is_focus);
    *end = save;
    if (remain == 0) {
      // NEXT LINE
      cur = cur->next;
      if (cur)
        remain = cur->lenght;
    }
    h++;
  }
}
