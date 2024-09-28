#include "view.h"
#include "buffers/line.h"
#include "io/colors.h"
#include "tools.h"
#include "view/manager.h"
#include <ncurses.h>
#include <stdbool.h>
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

// Call it with w set to NULL to set the last val
void write_number(WINDOW *w, unsigned long val, bool is_focus) {
  static unsigned long last = -1;
  if (last == val)
    return;
  last = val;
  if (!w)
    return;
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

char *write_info_txt(WINDOW *w, int len) {
  static char infos[] = "asdfghjkl;ASDFGHJKL:";
  static int last_len = sizeof(infos) - 1;
  static char last_char = 0;
  len = clamp(len, 0, sizeof(infos) - 1);
  infos[last_len] = last_char;
  last_char = infos[len];
  last_len = len;
  infos[len] = 0;
  // Write actual text
  wattron(w, COLOR_PAIR(INFO_PAIR));
  wattron(w, A_BOLD);
  wprintw(w, "%s", infos);
  wattroff(w, A_BOLD);
  wattroff(w, COLOR_PAIR(INFO_PAIR));
  return infos;
}

int write_line(view *v, line *cur, int h) {
  write_number(NULL, -1, 0); // RESET
  WINDOW *w = v->win;

  // Define consts
  const int size_line_nb = min(5, v->w - 1);
  const int is_focus = cur == v->cursor->focus_line;
  // Define loop elements
  int remain = cur->lenght;
  char *begin = cur->content;
  int len = min(v->w - size_line_nb, remain);
  if (is_focus) {
    h++;
    wmove(w, h++, size_line_nb);
    write_info_txt(w, len);
  }
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
    wprintw(w, "%s", begin);
    *end = save; // RESTORE
    begin = end;
    h++;
  } while (remain != 0 && h != v->h - is_focus /* for bot infos */);
  if (is_focus) {
    wmove(w, h++, size_line_nb);
    write_info_txt(w, len);
    h++;
  }
  return h;
}

void render_view(view *v) {
  wclear(v->win);
  line *cur = v->top_line;
  v->bot_line = cur;
  int h = 0;
  while (h < v->h && cur) {
    v->bot_line = cur;
    h = write_line(v, cur, h);
    cur = cur->next;
  }
}

void scroll_down(void) { scroll_to(get_current_view()->top_line->next); }
void scroll_up(void) { scroll_to(get_current_view()->top_line->prev); }

void scroll_to(line *top) {
  if (!top)
    return;
  view *v = get_current_view();
  wclear(v->win);
  v->top_line = top;
  render_view(v);
  bound_cursor();
}

bool is_displayed(unsigned long line) {
  view *v = get_current_view();
  return line >= v->top_line->pos && line <= v->bot_line->pos;
}
