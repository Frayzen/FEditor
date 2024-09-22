#include "buffer.h"
#include "buffers/line.h"
#include "constants.h"
#include <string.h>
#include <stdlib.h>

static int current_buffer = -1;
static struct buffer *buf_list[MAX_BUFFER] = {0};


buffer* allocate_buffer(void)
{
  int i = 0;
  while (buf_list[i] != 0 && i < MAX_BUFFER) 
    i++;
  if (i == MAX_BUFFER)
    return NULL;
  buf_list[i] = (struct buffer*) malloc(sizeof(buffer));
  buf_list[i]->id = i;
  return buf_list[i];
}

buffer* create_new_buffer(char* name)
{
  buffer* buf = allocate_buffer();
  buf->name = strdup(name);
  buf->fd = -1;
  buf->first_line = build_lines("This is a test\nHello");
  if (current_buffer == -1)
    current_buffer = buf->id;
  return buf;
}

buffer* get_current_buffer(void)
{
  if (current_buffer == -1)
    return NULL;
  return buf_list[current_buffer];
}
