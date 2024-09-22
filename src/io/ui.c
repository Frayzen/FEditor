#include "ui.h"
#include "buffers/buffer.h"
#include "inputs.h"
#include "io/cursor.h"
#include "io/mode.h"
#include <ncurses.h>
#include <string.h>

struct win_stats win_stats = {0};
static WINDOW *main_window;
static view* current_view = NULL;

view* get_current_view(void)
{
  return current_view;
}

void write_mode(void)
{
  char* mode_str = get_mode_str();
  move(win_stats.rows - 1 ,win_stats.columns - strlen(mode_str) - 1);
  printw("%s", mode_str);
}

void init(void) {
  main_window = initscr();
  nodelay(main_window, TRUE);
  getmaxyx(main_window, win_stats.rows,
           win_stats.columns); // MACRO, no need for pointer
  noecho();
  set_current_mode(INSERT);
  buffer* buf = create_new_buffer("New window");
  current_view = create_view(main_window, buf);
}

void update(void) {
  handle_inputs();
  if (current_view)
    render_view(current_view);
  write_mode();
  reset_cursor();
  refresh();
}

void end(void) {
  // TODO FREE ALL
  endwin();
}

