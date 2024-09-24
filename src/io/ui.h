#ifndef UI_H
#define UI_H

#include <ncurses.h>
struct win_stats {
  int columns, rows;
};
extern struct win_stats win_stats;

#define WIN_MH (win_stats.rows - 1)
#define WIN_MW (win_stats.columns - 1)

// Ncurses related
void init(void);
void end(void);
void render(void);
void update(void); // handle input + render
WINDOW* get_window(void);

#endif /* !UI_H */
