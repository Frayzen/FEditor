#include "inputs.h"
#include "io/cursor.h"
#include "io/mode.h"
#include "mode.h"
#include <ctype.h>
#include <ncurses.h>

#define KEY_ESCAPE 27

void insert_input(char in) {
  if (!isprint(in))
  {
    if (in == KEY_ESCAPE)
      set_current_mode(NORMAL);
    return; // cannot print char: TODO error message
  }
  write_char(in);
  add_pos(1, 0);
}

void normal_input(char in) {
  switch (in)
  {
    case 'h':
      add_pos(-1, 0);
      break;
    case 'j':
      add_pos(0, 1);
      break;
    case 'k':
      add_pos(0, -1);
      break;
    case 'l':
      add_pos(1, 0);
      break;
    case 'i':
      set_current_mode(INSERT);
      break;
    case 'a':
      add_pos(1, 0);
      set_current_mode(INSERT);
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
