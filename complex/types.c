#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"


struct Agent * init_agent(int x, int y)
{
    struct Point *p = (struct Point *) malloc(sizeof(struct Point));
    struct Agent *a = (struct Agent *) malloc(sizeof(struct Agent));

    assert(p && a);

    p->x = x;
    p->y = y;
    a->p = p;
    a->activity = active;

    return a;
}

void free_agent(struct Agent *a)
{
    free(a->p);
    free(a);
}

void show_agent(struct Agent *a)
{
    fprintf(stdout, "x: %d\ny: %d\na: %s\n",
            a->p->x, a->p->y, a->activity == 0 ? "active" : "inactive");
}

void move_agent(struct Agent *a, int dx, int dy)
{
    a->p->x += dx, a->p->y += dy;
}
