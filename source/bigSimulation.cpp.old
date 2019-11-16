#include <iostream>
//#include <algorithm> // For sort
#include <list>
#include "Creature.h"
#include "single.h"

using namespace std;
const int POPULATION_SIZE = 100;
const int NUMBER_OF_GENERATIONS = 100;

// To sort with creature with larger score first
bool creatureComparator(Creature c1, Creature c2)
{
    return c1.getScore() > c2.getScore();
}

void printPop(std::list<Creature> pop)
{
    int i = 0;
    for (Creature c : pop)
    {
        i++;
        printf("| id: %3d kind: %d%-2d score: % 6.2f | ", i, c.nodes.size(),  c.muscles.size(), c.getScore());
        if (i% 4 == 0)
            std::cout << std::endl;
    }
}


void bigSimulation ()
{
    // Create initial creatures
    std::list<Creature> population;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        population.push_back(Creature());
    }

    
    // Run a number of generations
    for (int generation = 1; generation <= NUMBER_OF_GENERATIONS; generation++){

        cout << "Generation " << generation << endl;

        //Test them, each creature is in singleSimulations given a score (accessed by creature.getScore())
        for (Creature& c : population){
            // Sets creature score to the appropriate value
            singleSimulation(c, false, 1);
        }

        // Sort the population with the highest score first. 
        population.sort(creatureComparator);
        cout << "Sorted " << endl;
        printPop(population);

        // Only kill if this is the last generation
        if (generation != NUMBER_OF_GENERATIONS)
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
        }

        //Repeat - The circle of life

    }

    printPop(population);
    
    int i = 0;
    while (true)
    {
        int speed;
        std::cout << "Which creature do you want to see? (arrays start at 0) ";
        std::cin >> i;
        std::cout << "At what speed (integer > 0)? ";
        std::cin >> speed;

        std::list<Creature>::iterator it = population.begin();
        std::advance(it, i);

        singleSimulation(*it, true, speed);
        std::cout << "Creature was scored: " << it->getScore() << std::endl;
    }
}
