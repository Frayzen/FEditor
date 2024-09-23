#include "io/colors.h"
#include "io/ui.h"
#include "view/manager.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
  (void) argc;
  init();
  new_buf(NULL, argv[1]);
  init_colors();
  render();
  while (true)
  {
    update();
  }
  end();
  return 0;
}
