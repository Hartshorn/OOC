#ifndef TYPES_H
#define TYPES_H

typedef enum {active, inactive} Activity;
typedef enum {yes, no} Living;

struct Point {
	int x, y;
};

struct Agent {
	struct Point *p;
	Living alive;
	int energy;
};

struct Agent * init_agent(int, int);
void free_agent(struct Agent *);
void show_agent(struct Agent *);
void move_agent(struct Agent *, int, int);
void add_agent(struct Agent *, struct Agent **, int *);
void eat_agent(struct Agent *, Living *, int);


Living * init_plants(Living *, int);
void grow_plants(Living *, int, int, int);



#endif
