#include "Creature.h"
#include "Muscle.h"
#include <list>
#include <set>

using namespace std;

Creature :: Creature () 
{
    
}
Creature :: Creature (list<Muscle> _muscles)
{
    muscles = _muscles;
    for (Muscle const &muscle : muscles)
    {
        nodes.insert(muscle.node1);
        nodes.insert(muscle.node2);
    }
}

void Creature :: updateInternalForces(double t)
{
    for (Muscle const &muscle : muscles)
    {
        muscle.addForceToNodes(t)
    }
}
Creature Creature :: offspring()
{
    //TODO small chance of changing architechture
    //TODO Change some shit and return a new creature. 
}
    

