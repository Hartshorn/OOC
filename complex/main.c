#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "types.h"
#include "functions.h"


int GLOBAL_WIDTH, GLOBAL_HEIGHT, GLOBAL_MAX, AGENT_COUNT = 0, DAY_COUNT = 0;
const char *AGENT_MARK = "!";


void event_loop(struct Explorer **, Living *, Item *);


int main(int argc, char **argv)
{
	srand(time(NULL));

	GLOBAL_WIDTH  = (int) strtol(argv[1], (char **)NULL, 10);
	GLOBAL_HEIGHT = (int) strtol(argv[2], (char **)NULL, 10);
	GLOBAL_MAX = GLOBAL_WIDTH * GLOBAL_HEIGHT;

	struct Explorer *EXPLORERS[GLOBAL_MAX];

	Living PLANTS[GLOBAL_MAX];
	init_plants(PLANTS);

	Item ITEMS[GLOBAL_MAX];
	init_items(ITEMS);

	event_loop(EXPLORERS, PLANTS, ITEMS);

	return 0;
}

void event_loop(struct Explorer **agents, Living *plants, Item *items)
{
    int i, x = 0;
	struct Explorer *e = init_explorer(GLOBAL_WIDTH / 2, GLOBAL_HEIGHT / 2);

	add_explorer(e, agents);
	grow_plants(plants);
	place_items(items);

	clear_screen();

	while(fscanf(stdin, "%d", &x) != EOF) {
		DAY_COUNT += 1;

		for (i = 0; i < AGENT_COUNT; i++) {
	        write_at(AGENT_MARK, get_x(*agents[i]), get_y(*agents[i]));
	    }

		for (i = 0; i < AGENT_COUNT; i++) {
			eat_explorer(agents[i], plants);
			search_explorer(agents[i], items);
			move_explorer(agents[i], 1, 1);
			if (agents[i]->super->alive == No) {
				delete_explorer(agents[i]);
				resize_array(agents);
			}
		}
	}

	delete_explorer(agents[0]);
	resize_array(agents);

	printf("Days: %d\n", DAY_COUNT);

	for (i = 0; i < AGENT_COUNT; i++){
		show_explorer(agents[i]);
		free_explorer(agents[i]);
	}
}
