#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



typedef enum { NORTH, EAST, SOUTH, WEST } Direction;

struct Point {
	int x;
	int y;
};

struct Vector {
	struct Point *p;
	Direction d;
	void (*f)(struct Vector *);
};

void move(struct Vector *);
void change_dir(struct Vector *);
struct Vector * new(struct Point *, Direction);
struct Point * point(int, int);
void log_func(struct Vector *);
void destroy(struct Vector *);


int main()
{
	struct Vector *v1 = new(point(0,0), NORTH);
	v1->f(v1);
	assert(v1->d == NORTH);

	move(v1);

	change_dir(v1);
	log_func(v1);
	assert(v1->d == EAST);


	destroy(v1);

	return 0;
}

void move(struct Vector *v)
{
	v->p->x += 1;
	v->p->y += 1;
}

void change_dir(struct Vector *v)
{
	assert(v);
	v->d = (v->d += 1) % 4;
}

struct Point * point(int x, int y)
{
	struct Point *p = malloc(sizeof(struct Point));

	p->x = x;
	p->y = y;

	return p;
}

struct Vector * new(struct Point *p, Direction d)
{
	struct Vector *v = malloc(sizeof(struct Vector));
	assert(p);

	v->p = p;
	v->d = d;
	v->f = log_func;

  return  v;
}

void destroy(struct Vector *v)
{
	free(v->p), free(v);
}

void log_func(struct Vector *v)
{
	fprintf(stdout, "Location:\n\tx: %d, y: %d\nDirection:\n\t%d\n", \
			v->p->x, v->p->y, v->d);
}
