#include "inputs.h"
#include "io/handlers/callbacks.h"
#include "io/mode.h"
#include "view/manager.h"
#include "view/view.h"

void normal_handle(int in) {
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
  case 'z':
    center_cursor();
    break;
  case 'i':
    set_current_mode(INSERT);
    break;
  case ' ':
    set_mode_with_cb(REQNB, goto_cb);
    break;
  case '/':
    set_current_mode(REQSTR);
    break;
  case 'g':
    if (get_current_cursor()->focus_line == get_current_view()->top_line)
      goto_line(get_current_buffer()->first_line);
    else
      get_current_cursor()->focus_line = get_current_view()->top_line;
    break;
  case 'G':
    if (get_current_cursor()->focus_line == get_current_view()->bot_line)
      goto_line(get_current_buffer()->last_line);
    else
      get_current_cursor()->focus_line = get_current_view()->bot_line;
    break;
  default:
    add_stack(in);
    return;
  }
  clear_stack();
}

