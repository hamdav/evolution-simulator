#include <algorithm>    // std::sort
#include <iostream>     // cout
#include "generationSimulation.h"
#include "single.h"
#include "myRand.h"

bool creatureComparator(Creature& c1, Creature& c2)
{
    return c1.getScore() > c2.getScore();
}

void runGeneration(std::vector<Creature>& population)
{


    // Repopulate with roulette method
    double total_fittness = 0;
    double min_score = 0;
    for (Creature& c : population)
    {
        double score = c.getScore();
        total_fittness += score;
        if (score < -min_score)
            min_score = -score;
    }

    // As we only want positive probabillities, we need to add min score to every score
    total_fittness = total_fittness + POPULATION_SIZE*min_score;

    std::vector<Creature> newPopulation;
    // Add the children of POPULATION_SIZE -1 creatures and save the best
    for (int i = 0; i < POPULATION_SIZE-1; i++)
    {
        double cumulativeProbabillity = 0;
        double randnr = myRand(0,1,3);
        for (Creature& c : population)
        {
            // The first one has the highest probabillity of passing on their genes, and then it goes down from there
            cumulativeProbabillity += (c.getScore()+min_score)/total_fittness;
            if (randnr <= cumulativeProbabillity)
            {
                //Creature c = population[j].offspring();
                newPopulation.push_back(c.offspring());
                break;
            }
        }
    }

    population.swap(newPopulation);

    //Test them, each creature is in singleSimulations given a score (accessed by creature.getScore())
    for (Creature& c : population){
        // Sets creature score to the appropriate value
        singleSimulation(c, false, 1);
    }

}
