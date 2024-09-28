#include "colors.h"
#include "tools.h"
#include <ncurses.h>
#define DEFINE_LIKE(Dest, Src) \
  color_content(Src, &r, &g, &b);\
  init_color(Dest, r, g, b);

void init_colors(void)
{
  // Load the colors
  int status = start_color();
  EXIT_ON_ERROR(status == OK, "The window's colors could not be loaded");
  
  if (has_colors() && can_change_color())
  {
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_GRAY, 800, 800, 800);
  }

  init_pair(BASE_PAIR, COLOR_WHITE, COLOR_BLACK);
  init_pair(FOCUS_PAIR, COLOR_WHITE, COLOR_RED);
  init_pair(INFO_PAIR, COLOR_GRAY, COLOR_BLACK);

  bkgd(PAIR_NUMBER(COLOR_BLACK));
  refresh();
}
