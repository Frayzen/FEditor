#include "manager.h"
#include "io/colors.h"
#include "io/ui.h"
#include "view/view.h"
#include <ncurses.h>

static view *current_view;

buffer *new_buf(view *v, char *path) {
  buffer *buf;
  if (path)
    buf = create_buffer_from_file(path);
  else
    buf = create_new_buffer("New window");
  if (!v) {
    WINDOW *win = newwin(win_stats.rows - 1, win_stats.columns, 0, 0); // The -1 is for the status line
    v = create_view(win, buf);
  }
  return buf;
}

void set_current_view(view *v) { current_view = v; }
view *get_current_view(void) { return current_view; }

void render_current_view(void) {
  if (current_view) {
    wbkgd(current_view->win, COLOR_PAIR(BASE_PAIR));
    refresh();
    render_view(current_view);
    wrefresh(current_view->win);
  }
}
