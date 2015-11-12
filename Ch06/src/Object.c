#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Object.h"
#include "../include/Object.r"

/*
/ Object
*/

static void * Object_ctor(void *_self, va_list *app)
{
        return _self;
}

static void * Object_dtor(void *_self)
{
        return _self;
}

static int Object_differ(const void *_self, const void *b)
{
        return _self != b;
}

static int Object_puto(const void *_self, FILE *fp)
{
        const struct Class *class = classOf(_self);

        return fprintf(fp, "%s at %p\n", class->name, _self);
}

const void * classOf(const void *_self)
{
        const struct Object *self = _self;

        assert(self && self->class);
        return self->class;
}

size_t sizeOf(const void *_self)
{
        const struct Class *class = classOf(_self);
        return class->size;
}

/*
/ Class
*/

static void * Class_ctor(void *_self, va_list *app)
{
        struct Class *self = _self;
        const size_t offset = offsetof(struct Class, ctor);

        self->name   = va_arg(*app, char *);
        self->super  = va_arg(*app, struct Class *);
        self->size   = va_arg(*app, size_t);

        assert(self->super);

        memcpy((char *)self + offset,
               (char *)self->super + offset,
               sizeOf(self->super) - offset);
        {
                typedef void (*voidf) (); /* generic function pointer */
                voidf selector;
                va_list ap = *app;

                /*
                / when we call va_arg the first time, it sets the selector
                / the second call sets the method
                / this eats up two arguments on purpose - the constructor
                / will expect a method name and a class specific method
                / i.e << differ, Any_differ >>
                */
                while((selector = va_arg(ap, voidf)))
                {
                        voidf method = va_arg(ap, voidf);

                        if(selector == (voidf) ctor)
                                *(voidf *)&self->ctor = method;

                        else if(selector == (voidf) dtor)
                                *(voidf *)&self->dtor = method;

                        else if(selector == (voidf) differ)
                                *(voidf *)&self->differ = method;

                        else if(selector == (voidf) puto)
                                *(voidf *)&self->puto = method;
                }
                return self;
        }
}

static void * Class_dtor(void *_self)
{
        struct Class *self = _self;

        fprintf(stderr, "%s: cannot destroy class\n", self->name);
        return 0;
}

const void * super(const void *_self)
{
        const struct Class *self = _self;

        assert(self && self->super);
        return self->super;
}

/*
/ Initialization
*/

static const struct Class object[] = {
        { { object + 1 },
                "Object", object, sizeof(struct Object),
                Object_ctor, Object_dtor, Object_differ, Object_puto
        },
        { { object + 1 }
                "Class", object, sizeof(struct Class),
                Class_ctor, Class_dtor, Object_differ, Object_puto
        }
};

const void *Object = object;
const void *Class = object + 1;


// selectors - 68
