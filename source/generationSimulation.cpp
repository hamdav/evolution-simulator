#include <algorithm>    // std::sort
#include <iostream>     // cout
#include "generationSimulation.h"
#include "single.h"
#include "myRand.h"

int PROB_OF_DEATH = 0.5;

bool creatureComparator(Creature c1, Creature c2)
{
    return c1.getScore() > c2.getScore();
}

void runGeneration(std::vector<Creature>& population)
{
    // Repopulate with roulette method

    // Add the children of POPULATION_SIZE -1 more to get a total of pop size back
    for (int i = 0; i < POPULATION_SIZE-1; i++)
    {
        double cumulativeProbabillity = 0;
        double randnr = myRand(0,1,3);
        for (int j = 0; j < POPULATION_SIZE; j++)
        {
            // The first one has the highest probabillity of passing on their genes, and then it goes down from there
            cumulativeProbabillity += ((double)(POPULATION_SIZE - j)/(POPULATION_SIZE*(POPULATION_SIZE+1)/2.0));
            if (randnr <= cumulativeProbabillity)
            {
                
                std::cout << " " << i << ":" << j;
                Creature c = population[j].offspring();
                population.insert(population.begin(),c);
                //newPopulation.push_back(population[j].offspring());
                break;
            }
        }
    }

    population.erase((population.begin()+POPULATION_SIZE),population.end());
            
    //Test them, each creature is in singleSimulations given a score (accessed by creature.getScore())
    for (Creature& c : population){
        // Sets creature score to the appropriate value
        singleSimulation(c, false, 1);
    }

    // Sort the population with the highest score first. 
    std::sort(population.begin(), population.end(), creatureComparator);

}
