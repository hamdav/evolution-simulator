#pragma once

#include "Vector.h"
#include "Node.h"

class Muscle
{
    public:
        //Muscle(Node &n1, Node &n2, double period = 1, double fraction_contracted = 0.5, double contracted_length = 1, double extended_length = 2, double phase_shift = 0, double k = 1, double c = 1);
        Muscle(Node&, Node&);
        Muscle(Node&, Node&, Muscle);
        void addForceToNodes(double t);
        void mutateInPlace();
        Node& getNode1();
        Node& getNode2();
        void printMuscle();

    private:
        Vector forceOnNode1(bool is_contracted);
        bool isContracted(double t);

        Node& node1;
        Node& node2;
        //Total period of motion, not less than one second
        double period; 
        // fraction of the period that the muscle is contracted
        // 0-1
        double fraction_contracted;
        // Lenth of contracted muscle, greater than one
        double contracted_length;
        // Lenth of extended muscle, greater than one
        double extended_length;
        // what phase does the muscle start in
        // 0-1
        double phase_shift;
        // spring constant
        double k;
        // dampening constant TODO should be critically dampened?
        double c;

        double MIN_PERIOD = 1;
        double MAX_PERIOD = 4;
        double MIN_FRAC_CON = 0;
        double MAX_FRAC_CON = 1;
        double MIN_LEN_CON = 50;
        double MAX_LEN_CON = 100;
        double MIN_LEN_EXT = 100;
        double MAX_LEN_EXT = 400;
        double MIN_PHASE_SHIFT = 0;
        double MAX_PHASE_SHIFT = 1;
        double MIN_K = 1;
        double MAX_K = 30;
        double MIN_C = 1;
        double MAX_C = 30;

};


