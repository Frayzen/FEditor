#ifndef VIEW_H
#define VIEW_H

#include "buffers/buffer.h"
#include "io/cursor.h"
#include <ncurses.h>

typedef struct view {
  // A view aim to be a set of buffer arranged on a screen
  // It currently is only a single buffer
  WINDOW* win;
  int w, h;
  buffer* buffer;
  line* top_line; // The line at the top of the screen
  line* bot_line; // The line at the bottom of the screen
  cursor* cursor;
} view;


view* create_view(WINDOW* win, buffer* buf);
void render_view(view* cur);
void scroll_down(void);
void scroll_up(void);

#endif /* !VIEW_H */
