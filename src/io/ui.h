#ifndef UI_H
#define UI_H

#include <ncurses.h>
struct win_stats {
  int columns, rows;
};
extern struct win_stats win_stats;

// Ncurses related
void init(void);
void end(void);
void update(void);
WINDOW* get_window(void);

#endif /* !UI_H */
