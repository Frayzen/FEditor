#include "editor.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

struct editor editor = {0};

void setupSize(void) {
  // Try from env
  char *columns = getenv("TEST");
  char *rows = getenv("TEST");
  if (columns)
    editor.columns = strtol(columns, NULL, 10);
  if (rows)
    editor.rows = strtol(rows, NULL, 10);
  if (editor.columns != 0 && editor.rows != 0)
    return;
  // Try from syscall
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  editor.columns = w.ws_col;
  editor.rows = w.ws_row;
}

void setupEditor(void) { setupSize(); }

struct editor *getEditor(void) { return &editor; }
