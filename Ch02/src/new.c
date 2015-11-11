#include <assert.h>
#include <stdlib.h>

#include "../include/new.h"
#include "../include/new.r"

/*
/ New function - takes a class and returns
/ a pointer to an initialized, appropriately sized area of memory.
/ If the class has a constructor, it calls this as well
*/
void * new(const void *_class, ...)
{
  const struct Class *class = _class;
  void *p = calloc(1, class->size);

  assert(p);

  /*
  / this is worth a comment - directly from the book (14):
  /
  / p points to the beginning of the new memory area for the object.
  / We force a conversion of p which treats the beginning of the object
  / as a pointer to a struct Class and set the argument class
  / as the value of this pointer
  /
  / the result of this is in the following methods when we call
  /   << const Struct Class *const *cp = self >> or similar
  / we are looking for this type descriptor
  /
  / *p points to the first field of p
  / from String.c, the String struct:
  /
  /       struct String {
  /           const void *class;
  /           char *text;
  /      };
  /
  / So if p points to a String Struct, the address will refer to
  / the first field, which is class.  So this line casts the class
  / field of p to a (const struct Class **) equal to the class passed in.
  */
  *(const struct Class **)p = class;

  if(class->ctor)
  {
    va_list ap;

    /*
    / va_start takes an initialized va_list variable
    / and the last argument before the argument list begins
    / this makes sense as it needs to know where to start,
    / and the only sure thing we have is the place right before
    / the start.
    /
    / In this case, we point p to the pointer returned by calling
    / the creator function of the class.
    /
    / For a String - the "a" value is passed as &ap, but this leaves
    / room for a lot of possibilities for class constructors.
    /
    / va_arg() is in the constructor function for the class
    /
    */
    va_start(ap, _class);
    p = class->ctor(p, &ap);
    va_end(ap);
  }

  return p;
}

/*
/ Delete Function
/
/ cp points to the Class of self
/ then makes sure that everything lines up
/ first that self exists
/ then that cp points to something
/ then that cp has a destructor method
/ if so, we call this destructor on self
/ then call free(self) to relese the memory
*/
void delete(void *self)
{
  const struct Class **cp = self;

  if(self && *cp && (*cp)->dtor)
    self = (*cp)->dtor(self);

  free(self);
}

/*
/ Clone Function
/
/ cp points to the class of self
/ steps through the existence of everything
/ then calls cp->clone on self.
*/
void * clone(const void *self)
{
  const struct Class *const *cp = self;

  assert(self && *cp && (*cp)->clone);
  return (*cp)->clone(self);
}

/*
/ Differ Function
/
/ cp points to the class of self
/ carefully check existence
/ call cp->differ(self, other);
*/
int differ(const void *self, const void *other)
{
  const struct Class *const *cp = self;

  assert(self && *cp && (*cp)->differ);
  return (*cp)->differ(self, other);
}

/*
/ SizeOf Function
/
/ cp is the class of self
/ check existence
/ return cp->size
*/
size_t sizeOf(const void *self)
{
  const struct Class *const *cp = self;

  assert(self && *cp);
  return (*cp)->size;
}
