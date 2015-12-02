#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "functions.h"

extern int GLOBAL_WIDTH, GLOBAL_HEIGHT, GLOBAL_MAX, AGENT_COUNT;

struct Agent * init_agent(int x, int y)
{
    struct Point *p = (struct Point *) malloc(sizeof(struct Point));
    struct Agent *a = (struct Agent *) malloc(sizeof(struct Agent));

    assert(p && a);

    p->x = x;
    p->y = y;
    a->p = p;
    a->energy = 1000;
    a->alive = Yes;

    return a;
}

struct Explorer * init_explorer(int x, int y)
{
    struct Agent *a = init_agent(x, y);
    struct Explorer *e = (struct Explorer *) malloc(sizeof(struct Explorer));

    assert(a && e);

    e->super = a;
    e->armed = False;
    e->weapon = None;

    return e;
}

void show_agent(struct Agent *a)
{
    assert(a->p);
    fprintf(stdout, "x: %d y: %d en: %d, a: %s",
            a->p->x, a->p->y, a->energy, a->alive == Yes ? "alive" : "dead");
}

void show_explorer(struct Explorer *e)
{
    assert(e && e->super);
    show_agent(e->super);
    fprintf(stdout, " armed: %s\n", e->armed == True ? "yes" : "no");
}

void move_agent(struct Agent *a, int dx, int dy)
{
    assert(a && a->p);
    a->p->x += dx, a->p->y += dy;
}

void move_explorer(struct Explorer *e, int dx, int dy)
{
    assert(e && e->super);
    move_agent(e->super, dx, dy);
}

void add_explorer(struct Explorer *e, struct Explorer **explorers)
{
    explorers[AGENT_COUNT++] = e;

}

void eat_agent(struct Agent *agent, Living *plants)
{
    int index = agent->p->x * GLOBAL_WIDTH + agent->p->y;

    if(plants[index] == Yes) {
        agent->energy += 10;
        plants[index] = No;
    }
}

void eat_explorer(struct Explorer *explorer, Living *plants)
{
    // eat_agent(explorer->super, plants);
    int index = get_x(*explorer) * GLOBAL_WIDTH + get_y(*explorer);

    if(plants[index] == Yes) {
        explorer->super->energy += 10;
        plants[index] = No;
    }
}

void delete_explorer(struct Explorer *e)
{
    e->super->alive = No;
}

void free_explorer(struct Explorer *e)
{
    free(e->super->p);
    free(e->super);
    free(e);
}

void search_explorer(struct Explorer *e, Item *items)
{
    int index = get_y(*e) * GLOBAL_WIDTH + get_x(*e);

    if(items[index] > e->weapon) {
        e->weapon = items[index];
        items[index] = None;
    }
}


void init_plants(Living *plants)
{
    int i;

    for(i = 0; i < GLOBAL_MAX; i++) {
        plants[i] = No;
    }
}

void grow_plants(Living *plants)
{
    int i, x, y;

    for(i = 0; i < GLOBAL_MAX; i++) {
        x = rand() % GLOBAL_WIDTH, y = rand() % GLOBAL_HEIGHT;
        // y * width + x
        plants[y * GLOBAL_WIDTH + x] = Yes;
    }
}

void init_items(Item *items)
{
    int i;

    for(i = 0; i < GLOBAL_MAX; i++) {
        items[i] = None;
    }
}

void place_items(Item *items)
{
    int i, x, y, item_v;
    Item item;

    for(i = 0; i < GLOBAL_MAX; i++) {
        x = rand() % GLOBAL_WIDTH;
        y = rand() % GLOBAL_HEIGHT;
        item_v = (rand() % 4) + 1;
        item =  item_v == 1 ? Stick :
                item_v == 2 ? Rock  :
                item_v == 3 ? Sword :
                None;

        items[y * GLOBAL_WIDTH + x] = item;
    }
}
