#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "types.h"
#include "functions.h"


int main(int argc, char **argv)
{
	struct Agent *a = init_agent(10, 10);
 	const char *c = "!";
	int x, y;

	x = (int) strtol(argv[2], (char **)NULL, 10);
	y = (int) strtol(argv[1], (char **)NULL, 10);

	write_at(c, x / 2, y / 2);

	free_agent(a);
	return 0;
}
