#include "io/ui.h"
#include "view/manager.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
  init();
  (void) argc;
  new_buf(NULL, argv[1]);
  while (true)
    update();
  end();
  return 0;
}
