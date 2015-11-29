#ifndef TYPES_H
#define TYPES_H

typedef enum {active, inactive} Activity;

struct Point {
	int x, y;
};

struct Agent {
	struct Point *p;
	Activity activity;
};

struct Agent * init_agent(int, int);
void free_agent(struct Agent *);
void show_agent(struct Agent *);
void move_agent(struct Agent *, int, int);


#endif
