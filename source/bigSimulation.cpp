#include <iostream>
#include <algorithm> // For sort
#include "Creature.h"
#include "single.h"

using namespace std;
const int POPULATION_SIZE = 20;

// To sort with creature with larger score first
bool creatureComparator(Creature c1, Creature c2)
{
    return c1.getScore() > c2.getScore();
}

void printPop(Creature pop[POPULATION_SIZE]) 
{
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        cout << i << ": s(" << pop[i].getScore() << ") n(" << pop[i].getNumber() << ")      ";
        if (i % 2 == 1) {cout << endl;}
    }
}

void bigSimulation ()
{
    // Create initial creatures
    Creature population[POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = Creature();
    }

    
    for (int generation = 1; generation < 10; generation++){

        //Test them
        for (int i = 0; i < POPULATION_SIZE; i++){
            // Sets creature score to the appropriate value
            singleSimulation(population[i]);
        }
        cout << "Generation " << generation << endl;
        printPop(population);
        cin.get();

        // Sort the population with the highest score first. 
        sort(population, population + POPULATION_SIZE, creatureComparator);
        cout << "Sorted " << endl;
        printPop(population);
        cin.get();

        // Kill the worst
        for (int i = POPULATION_SIZE/2; i < POPULATION_SIZE; i++)
        {
            //population[i] = NULL;
        }

        // Make babies
        for (int i = 0; i < POPULATION_SIZE/2; i++)
        {
            population[i+POPULATION_SIZE/2] = population[i].offspring();
        }

        //Repeat - The circle of life

    }
}
