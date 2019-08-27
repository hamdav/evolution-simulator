#include "single.h"
#include "Creature.h"

void singleSimulation(Creature &bob) 
{
    // Score is how far you are from 1 squared and negative
    bob.setScore(-(1.0-bob.getNumber())*(1.0-bob.getNumber()));
}
