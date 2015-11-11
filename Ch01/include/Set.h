#ifndef SET_H
#define SET_H

// external (declared elsewhere) pointer to an immutable block of memory
// extern const void *
//
// pointer to anything
// void *

// if it was a function pointer, it would be
// void (*func)(int x, int y)
//
// the ( ) keep the pointer on the function

extern const void * Set;

void * add(void * set, const void * element);
void * find(const void * set, const void * element);
void * drop(void * set, const void * element);
int contains(const void * set, const void * element);

#endif
