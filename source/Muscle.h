#pragma once

#include "Vector.h"
#include "Node.h"

extern double SINGLE_GENE_MUTATION_PROB;
class Muscle
{
    public:
        //Muscle(Node &n1, Node &n2, double period = 1, double fraction_contracted = 0.5, double contracted_length = 1, double extended_length = 2, double phase_shift = 0, double k = 1, double c = 1);
        Muscle();
        Muscle(const Muscle&);
        void addForceToNodes(Node&, Node&, double);
        void mutateInPlace();
        void printMuscle();

    private:
        Vector forceOnNode1(Node&, Node&, bool);
        bool isContracted(double);

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
        double MIN_LEN_CON = 1;
        double MAX_LEN_CON = 2;
        double MIN_LEN_EXT = 1;
        double MAX_LEN_EXT = 2;
        double MIN_PHASE_SHIFT = 0;
        double MAX_PHASE_SHIFT = 1;
        double MIN_K = 0;
        double MAX_K = 50;
        double MIN_C = 0;
        double MAX_C = 5;

};


