#ifndef CIRCLE_R
#define CIRCLE_R

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

#include "Point.r"

struct Circle {
        const struct Point _;
        int rad;
};

#endif
