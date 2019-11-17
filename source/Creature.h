#pragma once

#include "Muscle.h"
#include "Node.h"
#include <list>
#include <vector>
#include <map>

extern int MAX_NO_NODES;
extern int MIN_NO_NODES;

class Creature
{
    public:
        Creature(); // Random creature
        Creature(const Creature&); // Copy constructor
        void updateInternalForces(double t);
        Creature offspring();
        Vector getAvgPos();
        std::list<Muscle> muscles;   //Should these be public?
        std::map<int, Node> nodes;       // ?
        std::map<int, std::list<int>> connections;
        double getScore();
        void setScore(double);
        void setInitialPos();
        void printCreature();
    private:
        double score;
};

