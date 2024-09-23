#include "inputs.h"
#include "buffers/buffer.h"
#include "io/cursor.h"
#include "io/mode.h"
#include "io/ui.h"
#include "mode.h"
#include "view/manager.h"
#include "view/view.h"
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 20
static char input_stack[MAX_STACK_SIZE] = {0};
static int stack_size = 0;

#define KEY_ESCAPE 27

void add_stack(char c) {
  if (stack_size == MAX_STACK_SIZE)
    return;
  input_stack[stack_size++] = c;
}

void insert_input(char in) {
  if (!isprint(in)) {
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
  case 'i':
    set_current_mode(INSERT);
    break;
  case ' ':
    set_current_mode(REQNB);
    break;
  case 'g':
    if (get_current_view()->cursor->focus_line == get_current_view()->top_line)
      scroll_far(get_current_buffer()->first_line);
    else
      get_current_view()->cursor->focus_line = get_current_view()->top_line;
    break;
  case 'G':
    if (get_current_view()->cursor->focus_line == get_current_view()->bot_line)
      scroll_far(get_current_buffer()->last_line);
    else
      get_current_view()->cursor->focus_line = get_current_view()->bot_line;
    break;
  default:
    input_stack[stack_size++] = in;
    return;
  }
  stack_size = 0;
}

void reqnb_input(int in) {
  if (in == '\n' || in == ' ') {
    long val = strtol(input_stack, NULL, 10);
    gotoline(val - 1);
    set_current_mode(NORMAL);
    return;
  }
#define ASSIGN(C, N)                                                           \
  case C:                                                                      \
    add_stack(N);                                                              \
    break;
  switch (in) {
    ASSIGN('a', '1')
    ASSIGN('s', '2')
    ASSIGN('d', '3')
    ASSIGN('f', '4')
    ASSIGN('g', '5')
    ASSIGN('h', '6')
    ASSIGN('j', '7')
    ASSIGN('k', '8')
    ASSIGN('l', '9')
    ASSIGN(';', '0')
  }
}

void show_stack(void) {
  move(win_stats.rows - 1, 0);
  input_stack[stack_size] = 0;
  printw("%s", input_stack);
}

void handle_inputs(void) {
  int in = getch();
  if (in == ERR)
    return;
  if (get_current_mode() == NORMAL) {
    normal_input(in);
    return;
  }
  if (in == KEY_ESCAPE) {
    set_current_mode(NORMAL);
    return;
  }
  switch (get_current_mode()) {
  case INSERT:
    insert_input(in);
    break;
  case NORMAL:
    break;
  case REQNB:
    reqnb_input(in);
    break;
  default:
    break;
  }
}
