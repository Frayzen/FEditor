#ifndef VIEW_H
#define VIEW_H

#include "buffers/buffer.h"
#include "io/cursor.h"
#include <ncurses.h>

#define HALF_POS(View) ((View)->top_line->pos + (View)->h / 2)

typedef struct view {
  // A view aim to be a set of buffer arranged on a screen
  // It currently is only a single buffer
  WINDOW* win;
  int w, h;
  buffer* buffer;
  line* top_line; // The line at the top of the screen
  line* bot_line; // The line at the bottom of the screen
  cursor* cursor;
  char* searched;
} view;


view* create_view(WINDOW* win, buffer* buf);
void render_view(view* cur);
void scroll_down(void);
void scroll_up(void);
void scroll_to(line* to);
bool is_displayed(unsigned long line);

#endif /* !VIEW_H */
