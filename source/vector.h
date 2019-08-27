#pragma once

class Vector
{
    public:
        double x,y;
        void add(Vector v);
        void mul(double k);
        void sub(Vector v);
        Vector(double _x, double _y);
        Vector();
};

