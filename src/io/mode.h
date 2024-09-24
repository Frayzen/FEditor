#ifndef MODE_H
#define MODE_H

#include "tools.h"
enum mode {
  VISUAL,
  NORMAL,
  INSERT,

  REQMSK = 32,
  REQNB,
  REQSTR
};

enum mode get_current_mode(void);
void set_current_mode(enum mode mode);
void exit_mode(void); // equivalent to set_current_mode(NORMAL) but skip potential callback
void set_mode_with_cb(enum mode mode, callback cb); // Careful: no certainty to have cb called (if ESCAPE pressed)
char* get_mode_str(void);

#endif /* !MODE_H */
