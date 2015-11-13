#include <stdio.h>
#include <stdlib.h>

typedef void (*voidf)(); // generic function pointer

struct Calculator {
    int(*add)(int, int);
    int(*sub)(int, int);
};

int consumer(int(*f)(int, int), int, int);
struct Calculator * create_calc();
void * destroy_calc(struct Calculator *);

int main(int argc, char **argv)
{
    int n;
    struct Calculator *calc = create_calc();

    n = consumer(calc->add, 1, 2);

    printf("n: %d\n", n);

    destroy_calc(calc);
    return 0;
}

int add_impl(int x, int y) { return x + y; }
int sub_impl(int x, int y) { return x - y; }

struct Calculator * create_calc()
{
    struct Calculator *calc = calloc(1, sizeof(struct Calculator));
    calc->add = add_impl;
    calc->sub = sub_impl;
    return calc;
}

void * destroy_calc(struct Calculator *_self)
{
    struct Calculator *self = _self;
    free(self);
    return self;
}

int consumer(int(*f)(int, int), int x, int y)
{
    return f(x, y);
}
