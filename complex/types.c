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
    a->alive = yes;

    return a;
}

void free_agent(struct Agent *a)
{
    free(a->p);
    free(a);
}

void show_agent(struct Agent *a)
{
    fprintf(stdout, "x: %d y: %d a: %s\n",
            a->p->x, a->p->y, a->alive == yes ? "alive" : "dead");
}

void move_agent(struct Agent *a, int dx, int dy)
{
    a->p->x += dx, a->p->y += dy;
}

void add_agent(struct Agent *a, struct Agent **agents, int *agent_count)
{
    agents[(*agent_count)++] = a;
}

void eat_agent(struct Agent *agent, Living *plants, int width)
{
    if(plants[agent->p->x * width + agent->p->y] == yes)
        agent->energy += 10;
}


Living * init_plants(Living *plants, int max)
{
    int i;

    for(i = 0; i < max; i++) {
        plants[i] = no;
    }
    return plants;
}

void grow_plants(Living *plants, int max, int width, int height)
{
    int i, x, y;

    for(i = 0; i < max; i++) {
        x = rand() % width, y = rand() % height;
        // y * width + x
        plants[y * width + x] = yes;
    }
}
