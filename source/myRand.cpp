#include <cmath>
#include <iostream>

// Non-inclusive, precision 3 gives three significant figures
double myRand(double min, double max, int precision) 
{
    double length_of_interval = max - min;

    //Random number with precision between 0 and 1
    double random = (rand() % (int)pow(10,precision))/pow(10,precision);


    double rv = random * length_of_interval + min;
    return rv;
}
int myRandInt(int min, int max)
{
    if (min == max)
        return min;
    int length_of_interval = max - min;
    int rv = (rand() % length_of_interval) + min;
    return rv;
}
bool randomBool(double probabillity_of_true)
{
    if (probabillity_of_true > 1 || probabillity_of_true < 0)
        throw std::invalid_argument("Bad probabillity");

    int d = myRand(0,1,3);
    return probabillity_of_true >= d;
}

