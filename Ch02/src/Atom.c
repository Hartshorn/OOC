#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../include/String.h"
#include "../include/new.h"
#include "../include/new.r"


/*
/ An atom is a unique String object; if two atoms contain the same
/ strings, they are identical
*/

struct String {
  const void *class;
  char *text;
  struct String *next;
  unsigned count;
};

/*
/ Ring is a circular list of all Atoms
/ it is just a pointer to another String structure
*/
static struct String *ring;


/*
/ Constructor for Atom
/
/ Everything but the middle:
/ create a pointer to _self
/ pull the passed in string value from the va_list (from new())
/ set self->next = ring->next, ring-> = self (see? circular)
/ increase the count on self and copy the text
/
/ The middle:
/ if a ring exists (more than one atom has been created)
/ create a pointer to it, then check that the text
/ inside is not equal to the text passed in
/ (this is the compare part - atoms are unique)
/ if it is, increase the count on p (the ring), and return it
/ and free the memory of self
/
/ loop though the whole ring like this, as long as the next one isnt the start
/
*/
static void * String_ctor(void *_self, va_list *app)
{
  struct String *self = _self;
  const char *text = va_arg(*app, const char *);

  if(ring)
  {
    struct String *p = ring;

      do {
        if(strcmp(p->text, text) == 0)
        {
          ++p->count;
          free(self);
          return p;
        }
      } while((p = p->next) != ring);

  } else
    ring = self;

  self->next = ring->next, ring->next = self;
  self->count = 1;

  self->text = malloc(strlen(text) + 1);
  assert(self->text);
  strcpy(self->text, text);

  return self;
}

/*
/ Atom destructor
/
/ first check that self->count isnt 0 - if it is return 0
/
/ assert that there is a ring
/ then check if it is exactly equal to self
/ if it is, set the ring equal to self->next
/ check again if ring == self,
/ if it still is, set the ring = 0;
/ (this will take care of the very last atom being destructed_)
/
/ otherwise:
/ get a copy of the ring, and loop through until p->next is self
/ then set p->next = self->next, effectively removing self from the ring
/ free the memory of self->text and zero it out, then return self
*/
static void * String_dtor(void *_self)
{
  struct String *self = _self;

  if(--self->count > 0)
    return 0;

  assert(ring);
  if(ring == self)
    ring = self->next;

  if(ring == self)
    ring = 0;

  else
  {
    struct String *p = ring;

    while(p->next != self)
    {
      p = p->next;
      assert(p != ring);
    }
    p->next = self->next;
  }

  free(self->text), self->text = 0;
  return self;
}

/*
/ Atom Clone Function
*/
static void * String_clone(const void *_self)
{
  struct String *self = (void *) _self;

  ++self->count;
  return self;
}

/*
/ Atom Differ Function
*/
static int String_differ(const void *self, const void *other)
{
  return self != other;
}

static void String_write(const void *_self)
{
        const struct String *self = _self;

        printf("Atom Text: %s\n", self->text);
}


/*
/ Atom Prototype
*/
static const struct Class _String = {
  sizeof(struct String),
  String_ctor,
  String_dtor,
  String_clone,
  String_differ,
  String_write
};

const void *String = &_String;
