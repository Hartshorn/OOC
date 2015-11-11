#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/new.h"
#include "../include/Set.h"
#include "../include/Object.h"

/*
/ Implement a Bag - a set where items can repeat
/ Now with Dynamic memory
/ Set / Object are now Structs
/ A set has a count
/ An object has a count and points to a Set (that it belongs to);
*/
struct Set {
	unsigned count;
};

struct Object {
	unsigned count;
	struct Set *in;
};

/*
/ Similar to Set.c where we were passing in _set and _element,
/ here we create them using the struct size
/ these will be used in main
*/
static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

const void *Set = &_Set;
const void *Object = &_Object;

/*
/ New will now dynamically allocate the memory needed
/ returning a pointer to a location of size type
*/
void * new(const void *type, ...)
{
	const size_t size = * (const size_t *)type;
	void *p = calloc(1, size);

	assert(p);
	return p;
}

/*
/ delete now just calls free() to release the memory allocated to *item
*/
void delete(void *item)
{
	free(item);
}

/*
/ if the element has no set (in is null), assign it to *set
/ otherwise it must already be a part of the set, so assert this
/ then increase both counts
*/
void * add(void *_set, const void *_element)
{
	struct Set *set = _set;
	struct Object *element = (void *)_element;

	assert(set);
	assert(element);

	if(!element->in) {
		element->in = set;
	} else {
		assert(element->in == set);
	}
	++element->count, ++set->count;

	return element;
}

/*
/ return a pointer to the element if it is in the Set
/ otherwise return 0 (false)
*/
void * find(const void *_set, const void *_element)
{
	const struct Object *element = _element;

	assert(_set);
	assert(element);

	return element->in == _set ? (void *)element : 0;
}

/*
/ this calls find and checks that it isnt false
*/
int contains(const void *_set, const void *_element)
{
	return find(_set, _element) != 0;
}

/*
/ drop calls find to verify the element exists
/ it decrements the count, and if it becomes zero
/ remove it from the set
/ then decrement the count of the set
/
/ if the element doesnt exist in the set, just return it
*/
void * drop(void *_set, const void *_element)
{
	struct Set *set = _set;
	struct Object *element = find(set, _element);

	if(element) {
		if (--element->count == 0) {
			element->in = 0;
		}
		--set->count;
	}
	return element;
}

/*
/ return the value of the count for the set
*/
unsigned count(const void *_set)
{
	const struct Set *set = _set;
	assert(set);
	return set->count;
}

/*
/ return true if the two elements are different
/
*/
int differ(const void *a, const void *b)
{
	return a != b;
}
