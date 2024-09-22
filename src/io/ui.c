#include "ui.h"
#include "inputs.h"
#include "io/colors.h"
#include "io/mode.h"
#include "tools.h"
#include "view/manager.h"
#include <ncurses.h>
#include <string.h>

struct win_stats win_stats = {0};
static WINDOW *main_window;

WINDOW* get_window(void)
{
  return main_window;
}

void write_mode(void)
{
  char* mode_str = get_mode_str();
  move(win_stats.rows - 1 ,win_stats.columns - strlen(mode_str) - 1);
  printw("%s", mode_str);
}

void init(void) {
  main_window = initscr();
  EXIT_ON_ERROR(main_window, "The window could not be loaded");
  init_colors();
  nodelay(main_window, TRUE);
  getmaxyx(main_window, win_stats.rows,
           win_stats.columns); // MACRO, no need for pointer
  noecho();
  set_current_mode(NORMAL);
}

void update(void) {
  handle_inputs();
  render_current_view();
  write_mode();
  refresh();
}

void end(void) {
  // TODO FREE ALL
  endwin();
}

