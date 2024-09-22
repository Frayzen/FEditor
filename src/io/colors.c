#include "colors.h"
#include "tools.h"
#include <ncurses.h>

void init_colors(void)
{
  // Load the colors
  EXIT_ON_ERROR(start_color() == OK, "The window's colors could not be loaded");
  init_pair(BASE_PAIR, COLOR_WHITE, COLOR_BLACK);
}
