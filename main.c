#include "editor.h"
#include <stdio.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  setupEditor();
  printf("%d x %d\n", getEditor()->rows, getEditor()->columns);
  return 0;
}
