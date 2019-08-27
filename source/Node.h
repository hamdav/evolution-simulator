#pragma once

#include "vector.h"

class Node
{
    public:
        Node();
        Node(Node n);
        void addForce(Vector f);
        Vector getPos();
        Vector getVel();
        void setVel(Vector v);
        Vector getAcc();
        Vector getForce();
        //void setForce(Vector f);

    private:
        Vector pos;
        Vector vel;
        Vector acc;
        Vector force;
        double mass;
        double mu;
        

};

