#ifndef BUFFER_H
#define BUFFER_H

#include "buffers/line.h"
#define MAX_BUFFER 255

typedef struct buffer {
  int id;
  char* name;
  line* first_line; // The first line of the buffer
  int fd;
} buffer;

buffer* create_new_buffer(char* name);
buffer* get_current_buffer(void);

/* int create_buffer_from(char* name, int fd); */

#endif /* !BUFFER_H */
