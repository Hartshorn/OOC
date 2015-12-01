#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "types.h"
#include "functions.h"

int GLOBAL_WIDTH, GLOBAL_HEIGHT, GLOBAL_MAX, AGENT_COUNT = 0;
const char *AGENT_MARK = "!";

void event_loop(struct Agent **, Living *);

int main(int argc, char **argv)
{
	srand(time(NULL));

	GLOBAL_WIDTH  = (int) strtol(argv[1], (char **)NULL, 10);
	GLOBAL_HEIGHT = (int) strtol(argv[2], (char **)NULL, 10);
	GLOBAL_MAX = GLOBAL_WIDTH * GLOBAL_HEIGHT;

	struct Agent *AGENTS[GLOBAL_MAX];
	Living PLANTS[GLOBAL_MAX];

	event_loop(AGENTS, PLANTS);

	return 0;
}

void event_loop(struct Agent **agents, Living *plants)
{
    int i, x = 0, y = 0;

	grow_plants(init_plants(plants, GLOBAL_MAX), GLOBAL_MAX, GLOBAL_WIDTH, GLOBAL_HEIGHT);

	clear_screen();

	while(fscanf(stdin, "%d %d", &x, &y)
			&& x < GLOBAL_WIDTH
			&& y < GLOBAL_HEIGHT) {

		add_agent(init_agent(x, y), agents, &AGENT_COUNT);

		for (i = 0; i < AGENT_COUNT; i++) {
	        write_at(AGENT_MARK, agents[i]->p->x, agents[i]->p->y);
	    }

		for (i = 0; i < AGENT_COUNT; i++) {
			move_agent(agents[i], 1, 1);
			eat_agent(agents[i], plants, GLOBAL_WIDTH);
		}

		for (i = 0; i < AGENT_COUNT; i++) {
	        show_agent(agents[i]);
	    }
	}
}
