#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "functions.h"

int GLOBAL_WIDTH, GLOBAL_HEIGHT;

int main(int argc, char **argv)
{
	struct Agent *a = init_agent(10, 10);
	struct Agent *b = init_agent(12, 12);

 	const char *c = "!";

	GLOBAL_WIDTH  = (int) strtol(argv[1], (char **)NULL, 10);
	GLOBAL_HEIGHT = (int) strtol(argv[2], (char **)NULL, 10);

	struct Agent * AGENTS[GLOBAL_WIDTH * GLOBAL_HEIGHT];
	AGENTS[0] = a;
	AGENTS[1] = b;

	clear_screen();
	write_at(c, GLOBAL_WIDTH / 2, GLOBAL_HEIGHT / 2);
	write_at(c, AGENTS[0]->p->x, AGENTS[0]->p->y);
	write_at(c, AGENTS[1]->p->x, AGENTS[1]->p->y);

	return 0;
}
