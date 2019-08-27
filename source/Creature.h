#pragma once

#include "Muscle.h"
#include "Node.h"
#include <list>
#include <set>

using namespace std;

class Creature
{
    public:
        Creature(); // Random creature
        void updateInternalForces(double t);
        Creature offspring();
        list<Muscle> muscles;   //Should these be public?
        set<Node> nodes;       // ?
}

