#ifndef MODE_H
#define MODE_H

enum mode {
  VISUAL,
  NORMAL,
  INSERT,

  REQMSK = 32,
  REQNB
};

enum mode get_current_mode(void);
void set_current_mode(enum mode mode);
char* get_mode_str(void);

#endif /* !MODE_H */
