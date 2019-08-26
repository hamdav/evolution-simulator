#include <iostream>
#include "Creature.h"
#include <algorithm> // For sort
using namespace std;

// To sort with creature with larger score first
bool creatureComparator(Creature c1, Creature c2)
{
    return c1.getScore() > c2.getScore();
}

void singleSimulation(Creature &bob) 
{
    // Score is how far you are from 1 squared and negative
    bob.setScore(-(1.0-bob.getNumber())*(1.0-bob.getNumber()));
}


void printPop(Creature pop[20]) 
{
    for (int i = 0; i < 20; i++)
    {
        cout << i << ": s(" << pop[i].getScore() << ") n(" << pop[i].getNumber() << ")      ";
        if (i % 2 == 1) {cout << endl;}
    }
}

int main ()
{
    const int POPULATION_SIZE = 20;
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
            population[i] = NULL;
        }

        // Make babies
        for (int i = 0; i < POPULATION_SIZE/2; i++)
        {
            population[i+POPULATION_SIZE/2] = population[i].offspring();
        }

        //Repeat - The circle of life

    }
}
