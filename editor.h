#ifndef EDITOR_H
#define EDITOR_H

struct editor {
  int columns, rows;
};

void setupEditor(void);
struct editor *getEditor(void);

#endif /* !EDITOR_H */
