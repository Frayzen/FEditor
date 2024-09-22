#include "mode.h"
#include "io/cursor.h"
#include <ncurses.h>

static enum mode current_mode = INSERT;
enum mode get_current_mode(void)
{
  return current_mode;
}

void set_current_mode(enum mode mode)
{
  current_mode = mode;
  switch (current_mode)
  {
    case INSERT:
      set_cursor_visibility(LINE);
      break;
    default:
      set_cursor_visibility(BLOCK);
      break;
  }
}

char* get_mode_str(void)
{
  switch(current_mode)
  {
    case INSERT:
      return "INSERT";
    case NORMAL:
      return "NORMAL";
    case VISUAL:
      return "VISUAL";
    default:
      return "NO MODE";
  }
}

