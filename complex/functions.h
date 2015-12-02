#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void clear_screen();
void write_at(const char *, int, int);
int get_x(struct Explorer);
int get_y(struct Explorer);
void copy_agent(struct Explorer *, struct Explorer *);
void resize_array(struct Explorer **);

#endif
