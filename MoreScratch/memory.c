#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef enum {no, yes} Active;

struct Point {
    int x, y;
};

struct Pair {
    struct Point *p1, *p2;
    Active active;
};

int ARRAY_SIZE = 0;


void resize(struct Pair **);
struct Pair * init_p_at(int, int);
struct Point * init_pt_at(int, int);
void free_p(struct Pair *);
void add_p(struct Pair *, struct Pair **);


int main(int argc, char **argv)
{
    struct Pair *p1 = init_p_at(10, 10);
    struct Pair *p2 = init_p_at(10, 10);
    struct Pair *p3 = init_p_at(10, 10);

    assert(p1 && p2 && p3);

    struct Pair *p_a[ARRAY_SIZE];

    add_p(p1, p_a);
    add_p(p2, p_a);
    add_p(p3, p_a);

    printf("BFORE RESIZE\n");
    for(int i = 0; i < ARRAY_SIZE; i++){
        printf("p_a[%d]->active: %d\n", i, p_a[i]->active);
    }

    p_a[1]->active = no, p_a[0]->active = no, resize(p_a);


    printf("AFTER RESIZE\n");
    for(int i = 0; i < ARRAY_SIZE; i++){
        printf("p_a[%d]->active: %d\n", i, p_a[i]->active);
    }

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        free_p(p_a[i]);
    }
}

struct Pair * init_p_at(int x, int y)
{
    struct Pair *p = (struct Pair *) malloc(sizeof(struct Pair));
    struct Point *p1 = init_pt_at(x, y);
    struct Point *p2 = init_pt_at(x + 1, y + 1);

    p->p1 = p1, p->p2 = p2;
    p->active = yes;
    return p;
}

struct Point * init_pt_at(int x, int y)
{
    struct Point *p = (struct Point *) malloc(sizeof(struct Point));
    p->x = x, p->y = y;
    return p;
}

void add_p(struct Pair *pair, struct Pair **pair_array)
{
    pair_array[ARRAY_SIZE++] = pair;
}

void free_p(struct Pair *p)
{
    free(p->p1);
    free(p->p2);
    free(p);
}

void resize(struct Pair **pair_array)
{
    int p_idx = 0, p_cpy_idx = 0, diff = 0;
    struct Pair *pair_array_copy[ARRAY_SIZE];

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        if(pair_array[p_idx]->active == yes) {
            struct Pair *pair_copy = init_p_at(pair_array[p_idx]->p1->x, pair_array[p_idx]->p1->y);
            pair_array_copy[p_cpy_idx++] = pair_copy;
            p_idx++;
        } else {
            p_idx++;
        }
    }
    if(p_cpy_idx == ARRAY_SIZE) {
        for(int i = 0; i < p_cpy_idx; i++) {
            free_p(pair_array_copy[i]);
        }
    } else {
        diff = ARRAY_SIZE - p_cpy_idx;

        for(int i = 0; i < p_cpy_idx; i++) {
            struct Pair *another_pair_copy = init_p_at(pair_array_copy[i]->p1->x, pair_array_copy[i]->p1->y);
            free_p(pair_array[i]);
            pair_array[i] = another_pair_copy;
            free_p(pair_array_copy[i]);
        }
        for(int i = 1; i <= diff; i++) {
            free_p(pair_array[ARRAY_SIZE - i]);
        }
        ARRAY_SIZE -= diff;
    }
}
