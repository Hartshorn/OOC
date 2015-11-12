#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../include/vectors.h"


void move(struct Vector *v)
{
	v->p->x += 1;
	v->p->y += 1;
}

void change_dir(struct Vector *v)
{
	assert(v);
	v->d = (v->d + 1) % 4;
}

struct Point * point(int x, int y)
{
	struct Point *p = malloc(sizeof(struct Point));

	x(p) = x;
	y(p) = y;

	return p;
}

void log_func(struct Vector *v)
{
	fprintf(stdout, "Location:\n\tx: %d, y: %d\nDirection:\n\t%d\n",
		v->p->x, v->p->y, v->d);
}

struct Vector * new_vector(struct Point *p, Direction d)
{
	struct Vector *v = malloc(sizeof(struct Vector));
	assert(p);

	v->p = p;
	v->d = d;
	v->print = log_func;

  return  v;
}

void destroy(struct Vector *v)
{
	free(v->p), free(v);
}
