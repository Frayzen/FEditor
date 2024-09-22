#ifndef LINE_H
#define LINE_H

typedef struct line {
  char *content;
  unsigned long lenght;
  unsigned long pos;
  struct line *next; // NULL IF LAST
  struct line *prev; // NULL IF FIRST
} line;


struct line *build_lines(char *content);

#endif /* !LINE_H */
