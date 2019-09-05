#pragma once

#include "Muscle.h"
#include "Node.h"
#include <list>
#include <vector>
#include <map>


class Creature
{
    public:
        Creature(); // Random creature
        void updateInternalForces(double t);
        Creature offspring();
        std::list<Muscle> muscles;   //Should these be public?
        std::vector<Node> nodes;       // ?
        std::map<int, std::list<int>> connections;
    private:
        int MAX_NO_NODES = 7;
        int MIN_NO_NODES = 3;
};

