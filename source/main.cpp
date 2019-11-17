#include <iostream>
#include <stdarg.h>
#include <cstdlib>
#include <list>
#include "Creature.h"
#include "menus.h"
//#include "big.h"


int POPULATION_SIZE = 100;
int NUMBER_OF_GENERATIONS = 100;
int MAX_NO_NODES = 8;
int MIN_NO_NODES = 4;

int main ()
{

    // Print default screen
    resetScreen();

    // Iitialize the list of creatures
    std::vector<Creature> population;

    generateCreaturesMenu(population);

    while (true)
    {
        simulationsMenu(population);
    }

    //bigSimulation();
    return 0;
}


    
