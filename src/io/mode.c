#include "mode.h"
#include "io/cursor.h"
#include "tools.h"
#include <ncurses.h>

static enum mode current_mode = NORMAL;
static callback last_cb = NULL;

enum mode get_current_mode(void)
{
  return current_mode;
}

void set_current_mode(enum mode mode)
{
  if (last_cb)
  {
    last_cb();
    last_cb = NULL;
  }
  if (current_mode != mode)
    clear();
  current_mode = mode;
  switch (current_mode)
  {
    case INSERT:
      set_cursor_visibility(BLOCK);
      break;
    default:
      set_cursor_visibility(INVISIBLE);
      break;
  }
}

void exit_mode(void) {
  last_cb = NULL;
  set_current_mode(NORMAL);
}

void set_mode_with_cb(enum mode mode, callback cb)
{
  set_current_mode(mode);
  last_cb = cb;
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
    case REQNB:
      return "REQNB";
    default:
      return "NO MODE";
  }
}

