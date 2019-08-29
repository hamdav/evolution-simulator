#pragma once

#include "Muscle.h"
#include "Node.h"
#include <list>
#include <set>


class Creature
{
    public:
        Creature(); // Random creature
        void updateInternalForces(double t);
        Creature offspring();
        std::list<Muscle> muscles;   //Should these be public?
        std::set<Node> nodes;       // ?
    private:
        int MAX_NO_NODES = 7;
        int MIN_NO_NODES = 3;
}

