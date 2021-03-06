#include <assert.h>
#include <stdio.h>

#include "../include/new.h"
#include "../include/Object.h"
#include "../include/Set.h"

/*
/ these are not actually used in this file, but are needed later in main.c
*/
const void *Set;
const void *Object;

/*
/ make sure MANY is defined correctly
*/
#if ! defined MANY || MANY < 1
#define MANY  10
#endif


static int heap[MANY];

/*
/ new.h
/
/ parameters:
/             const void * type
/             ...
/ return:
/             int *
/
/ declare a new int * p
/ find space in the heap
/ assign MANY to it
/ return p
*/
void * new(const void *type, ...)
{
  int *p;

  for (p = heap + 1; p < heap + MANY; ++p) {
    if (! *p) {
        break;
      }
  }

  assert(p < heap + MANY);

  *p = MANY;

  fprintf(stdout, "\nNEW:\n");
  fprintf(stdout, "\tobj:\t%p\n", p);
  fprintf(stdout, "\theap:\t%p\n", heap);

  return p;
}

/*
/ new.h
/
/ parameters:
/             void * _item
/ return:
/             void
/
/ verify the item is on the heap
/ set the value of to zero
*/
void delete(void *_item)
{
  int *item = _item;

  if(item) {
    assert(item > heap && item < heap + MANY);
    *item = 0;
  }
}

/*
/ Set.h
/
/ parameters:
/             void * _set
/             const void * _element
/ return:
/             void *
/
/ verify that the set is in the heap
/ verify that the set has value MANY
/ verify that the element is in the heap
/ if the value of element is MANY
/     set the value of element to be the value of set - heap (1);
/ otherwise,
/     assert that it already exists
*/
void * add(void *_set, const void *_element)
{
  int *set = _set;
  const int *element = _element;

  assert(set > heap && set < heap + MANY);
  assert(*set == MANY);
  assert(element > heap && element < heap + MANY);

  fprintf(stdout, "\nADD:\n");
  fprintf(stdout, "\tset:\t%p\n", set);
  fprintf(stdout, "\theap:\t%p\n", heap);
  fprintf(stdout, "\telement: %p\n", element);
  fprintf(stdout, "\telement initial value: %d\n", *element);
  fprintf(stdout, "\tset - heap: %ld\n", set - heap);

  if(*element == MANY) {
    * (int *)element = set - heap;
  } else {
    assert(*element == set - heap);
  }

  fprintf(stdout, "\telement new value: %d\n", *element);

  return (void *)element;
}

/*
/ parameters:
/             const void *_set
/             const void *_element
/ returns:
/             void *
/
/ verify the set parameter is within the heap
/ verify that the size of the set (*set) is MANY (10 - initial object size)
/ verify that the element is on the heap and that it isnt null
/ return a pointer to the element, or else 0 (which is false)
*/
void * find(const void *_set, const void *_element)
{
  const int *set = _set;
  const int *element = _element;

  assert(set > heap && set < heap + MANY);
  assert(*set == MANY);
  assert(element > heap && element < heap + MANY);
  assert(*element);

  return *element == set - heap ? (void *) element : 0;
}

/*
/ parameters:
/             const void *_set
/             const void *_element
/ returns:
/             void *
/
/ call find and make sure it doesnt return 0
*/
int contains(const void *_set, const void *_element)
{
  return find(_set, _element) != 0;
}

/*
/ parameters:
/             const void *_set
/             const void *_element
/ returns:
/             void *
/
/ use find to look for the element in the set
/ if it isnt 0 << if(element != 0) or if(element) == true >>
/     set the value to MANY and return the pointer to it
/ if it isnt in the set
/     dont do anything and return the pointer to it
*/
void * drop(void *_set, const void *_element)
 {
   int *element = find(_set, _element);

   if (element) {
     *element = MANY;
   }
   return element;
 }

 /*
 / parameters:
 /             const void *a
 /             const void *b
 / returns:
 /             int
 /
 / verify that a and b point to differnet things
 / returns 0 (false) if they are the same
 */
 int differ(const void *a, const void *b)
 {
   return a != b;
 }
