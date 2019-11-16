#include "single.h"
#include <iostream>
#include <ctime>
#include <algorithm> // srand()

int main()
{
    
    int seed = time(NULL);
    std::cout << seed << std::endl;
    srand(seed);
    std::cout << rand() << std::endl;

    Creature bob = Creature();
    singleSimulation(bob, true, 4);
    return 0;
}
