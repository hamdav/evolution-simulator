#include "myRand.h"
#include <ctime>
#include <vector>
#include <iostream>

int main() 
{
    srand(time(NULL));
    int array[] = {0,0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < 10000000; i++)
    {
        array[myRandInt(4,7)]++;
    }
    for (int i : array)
    {
        std::cout << i << std::endl;
    }
}

    
