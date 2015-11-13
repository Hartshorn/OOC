#include "../include/Point.h"
#include "../include/Circle.h"

int main(int argc, char **argv)
{
    void *p;

    initCircle();

    while(*++argv)
    {
        switch(**argv) {
            case('p'):
                p = new(Point, 1, 2);
                break;
            case('c'):
                p = new(Circle, 1, 2, 3);
                break;
            default:
                continue;
        }
        draw(p);
        move(p, 100, 100);
        draw(p);

        draw(p);
        move(p, 10, 20);
        draw(p);

        delete(p);
    }
}
