#pragma once

#include "Vector.h"

extern double SINGLE_GENE_MUTATION_PROB;

class Node
{
    public:
        Node();
        Node(double, double);
        Node(const Node&);
        //Node child();
        void mutateInPlace();
        void addForce(Vector);
        Vector getPos();
        void setPos(Vector); // Should be set initial pos?
        Vector getVel();
        void setVel(Vector);
        Vector getAcc();
        Vector getForce();
        void zeroForce();
        //void setForce(Vector);
        void updateAcc();
        void updateVel(double); // Takes dt as argument
        void updatePos(double); // same
        double getRadius();
        double getMu();
        double getMass();
        int getId();
        void setId(int);
        void printNode();


    private:
        Vector pos;
        Vector prev_pos;
        Vector vel;
        Vector acc;
        Vector force;
        double mass;
        double mu;
        double radius = 0.2;
        int id;

        double MIN_MASS = 1; 
        double MAX_MASS = 1; 
        double MIN_MU = 0;
        double MAX_MU = 1;
        double MIN_RADIUS = 0.2;
        double MAX_RADIUS = 0.2;

};

