#include <stdio.h>

struct Object {
    const struct Class *class;
};

struct Class {
    const struct Object _;
    const char *name;
};


void printp(const void *_self)
{
    const struct Class *self = _self;

    printf("object + 1: %s\n", self->_.class->name);
    printf("String: %s\n", self->name);
}

int main()
{
    static const struct Class object[] =
    {
        { { object + 1 },
        "Object" },
        { {object + 1 },
        "Class" }
    };

    const void *one = object;
    const void *two = object + 1;

    printp(one);
    printp(two);

    return 0;
}
