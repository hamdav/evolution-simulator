#include "vector.h"

Vector :: Vector (double _x, double _y) : x(_x), y(_y) {}

Vector :: Vector () {x=0;y=0;}

void Vector :: add (Vector v)
{
    x = x + v.x;
    y = y + v.y;
}

void Vector :: mul (double k)
{
    x = k*x;
    y = k*y;
}

void Vector :: sub (Vector v)
{
    x = x - v.x;
    y = y - v.y;
}   
