#ifndef UI_H
#define UI_H

#include "io/view.h"
struct win_stats {
  int columns, rows;
};
extern struct win_stats win_stats;

// Ncurses related
void init(void);
void end(void);
void update(void);
view* get_current_view(void);

#endif /* !UI_H */
