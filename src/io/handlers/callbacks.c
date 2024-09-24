#include "constants.h"

#include "callbacks.h"
#include "io/cursor.h"
#include "io/handlers/inputs.h"
#include "view/manager.h"
#include <stdlib.h>
#include <string.h>

void goto_cb(void) {
  long val = strtol(get_stack(), NULL, 10);
  goto_line_id(val - 1);
}
void search_cb(void) {
  free(get_current_view()->searched);
  get_current_view()->searched = strdup(get_stack());
}
