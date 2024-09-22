#ifndef MANAGER_H
#define MANAGER_H

// This class aims to manage all open buffers

#include "buffers/buffer.h"
#include "view/view.h"

// Create a buffer
// If view is null, a new view is created
// If path is null, an empty file is defined
buffer* new_buf(view* v, char* path);
void render_current_view(void);

void set_current_view(view *v);
view *get_current_view(void);


#endif /* !MANAGER_H */
