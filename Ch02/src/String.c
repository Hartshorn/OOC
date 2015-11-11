#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../include/String.h"
#include "../include/new.h"
#include "../include/new.r"


struct String {
  const void *class;
  char *text;
};

/*
/ String creator function
/
/ This function is called by new (in new.c), passed through
/ the class it was given (String in this case).
/ The _self here is the newly calloc-ed block of memory
/ in the new function, a va_list is created and passed here, which
/ contains the text to set.
*/
static void * String_ctor(void *_self, va_list *app)
{
  struct String *self = _self;
  const char *text = va_arg(*app, const char *);

  self->text = malloc(strlen(text) + 1);
  assert(self->text);
  strcpy(self->text, text);

  return self;
}

/*
/ String destructor function
*/
static void * String_dtor(void *_self)
{
  struct String *self = _self;

  free(self->text), self->text = 0;
  return self;
}

/*
/ String clone function - use self to make a new one
*/
static void * String_clone(const void *_self)
{
  const struct String *self = _self;

  return new(String, self->text);
}

/*
/ String differ function
/
/ compare two String objects by first verifying they arent exactly the same
/ then verify that other isnt null or of a differnt class
/ then compare the text stored in each
*/
static int String_differ(const void *_self, const void *_other)
{
  const struct String *self = _self;
  const struct String *other = _other;

  if(self == other)
    return 0;

  if(!other || other->class != String)
    return 1;

  return strcmp(self->text, other->text);
}


/*
/ Construct a new String
/ when a new(String, "something") is created
/ in main, this will be the prototype used.
/ It assigns a size and all functions.
*/
static const struct Class _String = {
  sizeof(struct String),
  String_ctor,
  String_dtor,
  String_clone,
  String_differ
};

/*
/ String is a pointer to the prototype
*/
const void *String = &_String;
