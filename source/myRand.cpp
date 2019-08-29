#include <cmath>
#include <iostream>

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
    int length_of_interval = max - min;
    rv = (rand() % length_of_interval) + min;
    return rv;
}
