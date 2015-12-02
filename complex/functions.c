#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"

extern int AGENT_COUNT;

void clear_screen()
{
    printf("%c[2J",27);
}

void write_at(const char *c, int x, int y)
{
    printf("\033[%d;%df%s\n", y, x, c);
}

int get_x(struct Explorer e)
{
    return e.super->p->x;
}

int get_y(struct Explorer e)
{
    return e.super->p->y;
}

void copy_agent(struct Explorer *a, struct Explorer *b)
{
    b->super = a->super;
    b->armed = a->armed;
}


void resize_array(struct Explorer **explorers)
{
    int hold_index = 0, exp_index = 0, diff = 0;
    struct Explorer *hold[AGENT_COUNT];

    for(int i = 0; i < AGENT_COUNT; i++) {
        if(explorers[i]->super->alive == Yes) {
            struct Explorer *e = init_explorer(explorers[exp_index]->super->p->x,
                                               explorers[exp_index]->super->p->y);
            hold[hold_index++] = e;
            exp_index++;
        } else {
            exp_index++;
        }
    }

    if(hold_index == AGENT_COUNT) {
        for(int i = 0; i < hold_index; i++) {
            free_explorer(hold[i]);
        }
    } else {
        diff = AGENT_COUNT - hold_index;

        for(int i = 0; i < hold_index; i++) {
            struct Explorer *e = init_explorer(hold[i]->super->p->x, hold[i]->super->p->y);
            free_explorer(explorers[i]);
            explorers[i] = e;
            free_explorer(hold[i]);
        }
        for(int i = 1; i <= diff; i++) {
            free_explorer(explorers[AGENT_COUNT - i]);
        }
        AGENT_COUNT -= diff;
    }
}
