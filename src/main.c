#include "io/ui.h"
#include <stdbool.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  init();
  while (true)
  {
    update();
  }
  end();
  return 0;
}
