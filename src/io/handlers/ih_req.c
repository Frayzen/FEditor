#include "inputs.h"

#include "inputs.h"
#include "io/mode.h"
#include <ctype.h>

void reqnb_handle(int in) {
  if (in == ' ') {
    set_current_mode(NORMAL);
    return;
  }
#define ASSIGN(C, N)                                                           \
  case C:                                                                      \
    add_stack(N);                                                              \
    break;
  switch (in) {
    ASSIGN('a', '1')
    ASSIGN('s', '2')
    ASSIGN('d', '3')
    ASSIGN('f', '4')
    ASSIGN('g', '5')
    ASSIGN('h', '6')
    ASSIGN('j', '7')
    ASSIGN('k', '8')
    ASSIGN('l', '9')
    ASSIGN(';', '0')
  }
}

void reqstr_handle(int in) {
  if (!isprint(in))
    return;
  if (in == ' ') {
    set_current_mode(NORMAL);
    return;
  }
  add_stack(in);
}
