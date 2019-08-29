#include "Vector.h"

Vector :: Vector (double _x, double _y) : x(_x), y(_y) {}

Vector :: Vector () {x=0;y=0;}

Vector Vector :: add (Vector v)
{
    return Vector(x + v.x, y + v.y);
}

Vector Vector :: mul (double k)
{
    return Vector(k*x, k*y);
}

Vector Vector :: sub (Vector v)
{
    return Vector(x - v.x, y - v.y);
}   
double Vector :: length()
{
    return (x*x+y*y);
}
double Vector :: dot(Vector v)
{
    return (x*v.x + y*v.y);
}
Vector Vector :: normed()
{
    return mul(1/length());
}
