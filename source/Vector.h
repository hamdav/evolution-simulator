#pragma once

class Vector
{
    public:
        double x,y;
        Vector add(Vector v);
        Vector mul(double k);
        Vector sub(Vector v);
        Vector normed();
        double dot(Vector v);
        double length();
        Vector(double _x, double _y);
        Vector();
};

