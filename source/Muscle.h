#pragma once

class Muscle
{
    public:
        Muscle(Node n1, Node n2);
        Muscle(Node n1, Node n2, double period = 1, double fraction_contracted = 0.5, double contracted_length = 1, double extended_length = 2, double phase_shift = 0, double k = 1, double c = 1);
        void addForceToNodes(double t);
        Muscle offspring();

    private:
        Vector forceOnNode1(bool is_contracted);
        bool isContracted(double t);

        Node node1;
        Node node2;
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
}

