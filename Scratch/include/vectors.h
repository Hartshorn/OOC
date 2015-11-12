#ifndef VECTORS_H
#define VECTORS_H

#include <assert.h>
#include <stdlib.h>

#define x(p)	(((struct Point *) (p)) -> x)
#define y(p)	(((struct Point *) (p)) -> y)


typedef enum { NORTH, EAST, SOUTH, WEST } Direction;

struct Point {
	int x;
	int y;
};


struct Vector {
	struct Point *p;
	Direction d;
	void (*print)(struct Vector *);
};

void move(struct Vector *v);
void change_dir(struct Vector *v);
struct Point * point(int x, int y);
void log_func(struct Vector *v);
struct Vector * new_vector(struct Point *p, Direction d);
void destroy(struct Vector *v);

#endif
