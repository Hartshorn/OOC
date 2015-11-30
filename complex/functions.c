#include <stdio.h>
#include <stdlib.h>

#include "types.h"

void clear_screen()
{
    printf("%c[2J",27);
}

void write_at(const char *c, int x, int y)
{
    printf("\033[%d;%df%s\n", y, x, c);
}
