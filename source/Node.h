#pragma once

#include "Vector.h"

class Node
{
    public:
        Node();
        Node(double, double);
        Node child();
        void addForce(Vector);
        Vector getPos();
        void setPos(Vector); // Should be set initial pos?
        Vector getVel();
        void setVel(Vector);
        Vector getAcc();
        Vector getForce();
        //void setForce(Vector);
        void updateAcc();
        void updateVel(double); // Takes dt as argument
        void updatePos(double); // same

    private:
        Vector pos;
        Vector vel;
        Vector acc;
        Vector force;
        double mass;
        double mu;
        

};

