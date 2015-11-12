#ifndef CLASS_R
#define CLASS_R

/*****************************************************************************
*
*                       Private Class File
*
* .h     Header file with external interfaces, such as methods.
*
* .r     Representation file for internal use within the class, such as
*                structs that define the internal states.
*
* .c     Implementation of the Circle class.
*
*****************************************************************************/

#include <stdarg.h>

struct Class {
        size_t size;
        void * (*ctor)(void *self, va_list *app);
        void * (*dtor)(void *self);
        void (*draw)(const void *self);
};

#endif
