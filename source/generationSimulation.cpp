#include "generationSimulation.h"
#include "single.h"

bool creatureComparator(Creature c1, Creature c2)
{
    return c1.getScore() > c2.getScore();
}

void runGeneration(std::list<Creature>& population)
{
    // Kill the worst
    std::list<Creature>::iterator it = population.begin();
    std::advance(it, POPULATION_SIZE/2);
    population.erase(it, population.end());

    // Make babies
    for (Creature c : population)
    {
        population.push_front(c.offspring());
    }

    //Test them, each creature is in singleSimulations given a score (accessed by creature.getScore())
    for (Creature& c : population){
        // Sets creature score to the appropriate value
        singleSimulation(c, false, 1);
    }

    // Sort the population with the highest score first. 
    population.sort(creatureComparator);

}
