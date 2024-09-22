#include "inputs.h"
#include "io/cursor.h"
#include "io/mode.h"
#include "mode.h"
#include "view/manager.h"
#include "view/view.h"
#include <ctype.h>
#include <ncurses.h>

#define KEY_ESCAPE 27

void insert_input(char in) {
  if (!isprint(in)) {
    if (in == KEY_ESCAPE)
      set_current_mode(NORMAL);
    return; // cannot print char: TODO error message
  }
  // TODO
}

void normal_input(char in) {
  switch (in) {
  case 'h':
    scroll_up();
    break;
  case 'j':
    next_line();
    break;
  case 'k':
    prev_line();
    break;
  case 'l':
    scroll_down();
    break;
    break;
  case 'i':
    set_current_mode(INSERT);
    break;
  case 'g':
    if (get_current_view()->cursor->focus_line == get_current_view()->top_line)
      while (prev_line())
        continue;
    else
      get_current_view()->cursor->focus_line = get_current_view()->top_line;
    break;
  case 'G':
    if (get_current_view()->cursor->focus_line == get_current_view()->bot_line)
      while (next_line())
        continue;
    else
      get_current_view()->cursor->focus_line = get_current_view()->bot_line;
    break;
  }
}

void handle_inputs(void) {
  int in = getch();
  if (in == ERR)
    return;
  switch (get_current_mode()) {
  case INSERT:
    insert_input(in);
    break;
  case NORMAL:
    normal_input(in);
    break;
  default:
    break;
  }
}
