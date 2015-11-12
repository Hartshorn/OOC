#ifndef OBJECT_H
#define OBJECT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>


extern const void *Object;

void * new(const void *class, ...);
void delete(void *self);

int differ(const void *self, const void *b);
int puto(const void *self, FILE *fp);


#endif
