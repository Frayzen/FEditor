#ifndef INPUTS_H
#define INPUTS_H

#define KEY_ESCAPE 27
#define MAX_STACK_SIZE 20

void handle_inputs(void);

typedef void (*handler)(int);

// HANDLERS
void normal_handle(int in);
void insert_handle(int in);
void reqnb_handle(int in);
void reqstr_handle(int in);

// STACK RELATED
char *get_stack(void);
void clear_stack(void);
void add_stack(char c);
void show_stack(void);

#endif /* !INPUTS_H */
