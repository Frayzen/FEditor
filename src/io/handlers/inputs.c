#include "inputs.h"
#include "io/mode.h"
#include "io/ui.h"
#include <ncurses.h>

#define MAX_STACK_SIZE 20
static char input_stack[MAX_STACK_SIZE + 1] = {0};
static int stack_size = 0;

static handler handlers[] = {
    [NORMAL] = normal_handle,
    [INSERT] = insert_handle,
    [REQNB] = reqnb_handle,
    [REQSTR] = reqstr_handle,
};

void handle_inputs(void) {
  int in = getch();
  if (in == ERR)
    return;
  if (in == KEY_ESCAPE) {
    exit_mode();
    return;
  }
  handlers[get_current_mode()](in);
}

/*
 * ==== STACK ====
 */

char *get_stack(void) { return input_stack; }
void clear_stack(void) {
  stack_size = 0;
  input_stack[0] = 0;
}
void add_stack(char c) {
  if (stack_size == MAX_STACK_SIZE)
    return;
  input_stack[stack_size++] = c;
  input_stack[stack_size] = 0;
}

void show_stack(void) {
  move(win_stats.rows - 1, 0);
  input_stack[stack_size] = 0;
  printw("%s", input_stack);
}
