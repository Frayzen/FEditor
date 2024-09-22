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
  // TODO
}

void normal_input(char in) {
  switch (in)
  {
    case 'h':
      next_line();
      break;
    case 'j':
      next_line();
      break;
    case 'k':
      prev_line();
      break;
    case 'l':
      prev_line();
      break;
      break;
    case 'i':
      set_current_mode(INSERT);
      break;
    case 'g':
      while(prev_line())
        continue;
    case 'G':
      while(next_line())
        continue;
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
