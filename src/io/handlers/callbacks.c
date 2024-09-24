#include "callbacks.h"
#include "io/cursor.h"
#include "io/handlers/inputs.h"
#include <stdlib.h>

void goto_cb(void) {
  long val = strtol(get_stack(), NULL, 10);
  goto_line_id(val - 1);
}
void search_cb(void) {
  // TODO
}
