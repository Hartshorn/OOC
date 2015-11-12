#ifndef POINT_R
#define POINT_R

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


struct Point {
        const void *class;
        int x, y;
};

#define x(p)    (((const struct Point *) (p)) -> x)
#define y(p)    (((const struct Point *) (p)) -> y)

#endif
