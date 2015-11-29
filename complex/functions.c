#include <stdio.h>

void write_at(const char *c, int x, int y)
{
    printf("\033[%d;%df%s\n", x, y, c);
}
