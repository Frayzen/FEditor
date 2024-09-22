#include "manager.h"
#include "io/ui.h"
#include "view/view.h"
#include <stdio.h>

buffer *new_buf(view *v, char *path) {
  buffer *buf;
  if (path)
  {
    buf = create_buffer_from_file(path);
  }
  else
    buf = create_new_buffer("New window");
  if (!v)
    v = create_view(get_window(), buf);
  return buf;
}

static view *current_view = NULL;

void set_current_view(view *v) { current_view = v; }
view *get_current_view(void) { return current_view; }

void render_current_view(void) {
  if (current_view)
    render_view(current_view);
}
