#ifndef NEW_H
#define NEW_H

#include <stddef.h>

void * new(const void *class, ...);
void delete(void *item);

void * clone(const void *self);
int differ(const void *self, const void *other);

size_t sizeOf(const void *self);

void write(const void *self);

#endif
