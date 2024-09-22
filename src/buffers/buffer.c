#include "constants.h"

#include "buffer.h"
#include "buffers/line.h"
#include "tools.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int current_buffer = -1;
static struct buffer *buf_list[MAX_BUFFER] = {0};

buffer *get_current_buffer(void) {
  if (current_buffer == -1)
    return NULL;
  return buf_list[current_buffer];
}

buffer *allocate_buffer(void) {
  int i = 0;
  while (buf_list[i] != 0 && i < MAX_BUFFER)
    i++;
  if (i == MAX_BUFFER)
    return NULL;
  buf_list[i] = (struct buffer *)calloc(1, sizeof(buffer));
  buf_list[i]->id = i;
  if (current_buffer == -1)
    current_buffer = i;
  return buf_list[i];
}

buffer *create_new_buffer(char *name) {
  buffer *buf = allocate_buffer();
  buf->name = strdup(name);
  buf->file = NULL;
  buf->first_line = build_lines("This is a test\nAnd here also");
  return buf;
}

buffer *create_buffer_from_file(char *path) {
  FILE *file = fopen(path, "a+");
  EXIT_ON_ERRNO(file);
  buffer *buf = allocate_buffer();

  // Build content
  fseek(file, 0, SEEK_END); // Get the size
  long len = ftell(file);
  EXIT_ON_ERRNO(len != -1);
  char *content = malloc(len+1); // Allocate buffer
  rewind(file); // Reset position
  fread(content, len, 1, file);
  content[len] = 0; // Null terminate
  buf->first_line = build_lines(content); //
  free(content);

  buf->file = file;

  char *name = basename(path);
  buf->name = strdup(name);
  return buf;
}
