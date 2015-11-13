#include <stdio.h>

#include "../include/vectors.h"




int main()
{
	const int f[] = { {1,2,3}, {4,5,6}};

	struct Vector *v1 = new_vector(point(0,0), NORTH);
	v1->print(v1);

	assert(v1->d == NORTH);

	move(v1);

	change_dir(v1);
	v1->print(v1);

	assert(v1->d == EAST);


	destroy(v1);

	return 0;
}
