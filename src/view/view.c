#include "view.h"
#include "buffers/line.h"
#include "tools.h"
#include "view/manager.h"
#include <ncurses.h>
#include <stdlib.h>

view *create_view(WINDOW *win, buffer *buf) {
  view *cur = calloc(1, sizeof(view));
  getmaxyx(win, cur->h, cur->w);
  getyx(win, cur->x, cur->y);
  cur->cursor = create_cursor(buf->first_line);
  cur->win = win;
  cur->buffer = buf;
  cur->top_line = buf->first_line;
  if (!get_current_view())
    set_current_view(cur);
  return cur;
}

void render_view(view *v) {
  int h = 0;
  line *cur = v->top_line;
  int remain = cur->lenght;
  while (h < v->h && cur) {
    char *begin = cur->content;
    int len = min(v->w, remain);
    char *end = begin + len;
    remain -= len;

    char save = *end;
    move(v->y + h, v->x);
    if (cur == v->cursor->focus_line)
      attron(A_BOLD);
    printw("%s", begin);
    *end = save;
    attroff(A_BOLD);

    if (remain == 0) {
      // NEXT LINE
      cur = cur->next;
      if (cur)
        remain = cur->lenght;
    }
    h++;
  }
}
