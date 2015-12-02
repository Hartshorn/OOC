#ifndef TYPES_H
#define TYPES_H

typedef enum {active, inactive} Activity;
typedef enum {Yes, No} Living;
typedef enum {False, True} Bool;
typedef enum {None, Stick, Rock, Sword} Item;

struct Point {
	int x, y;
};

struct Agent {
	struct Point *p;
	Living alive;
	int energy;
};

struct Explorer {
	struct Agent *super;
	Bool armed;
	Item weapon;
};

struct Agent * init_agent(int, int);
void show_agent(struct Agent *);
void move_agent(struct Agent *, int, int);
void eat_agent(struct Agent *, Living *);

struct Explorer * init_explorer(int, int);
void show_explorer(struct Explorer *);
void move_explorer(struct Explorer *, int, int);
void add_explorer(struct Explorer *, struct Explorer **);
void search_explorer(struct Explorer *, Item *);
void eat_explorer(struct Explorer *, Living *);
void delete_explorer(struct Explorer *);
void free_explorer(struct Explorer *);

void init_plants(Living *);
void grow_plants(Living *);

void init_items(Item *);
void place_items(Item *);


#endif
