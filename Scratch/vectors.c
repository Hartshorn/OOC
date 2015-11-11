#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



typedef enum { NORTH, SOUTH, EAST, WEST } Direction;

struct Vector {
  int x;
  int y;
  Direction d;

  // constructor function?
};

void move(struct Vector *);
struct Vector * new(int x, int y, Direction d);


int main()
{
  struct Vector v1 = { 0, 0, NORTH };

  struct Vector *v2_ptr = new(10, 10, WEST);

  move(&v1);
  move(v2_ptr);

  return 0;
}

void move(struct Vector *v)
{
  v->x += 1;
  v->y += 1;
}

struct Vector * new(int x, int y, Direction d)
{
  struct Vector *v = malloc(sizeof(struct Vector));

  v->x = x;
  v->y = y;
  v->d = d;

  return  v;
}
