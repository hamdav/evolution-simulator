#include <stdexcept>

double MUTATION_FACTOR_UPPER_BOUND = 1.5;
double MUTATION_FACTOR_LOWER_BOUND = 0.6;

double mutate(double low_bound, double high_bound, double value)
{
    if (value < low_bound || value > high_bound)
    {
        throw std::invalid_argument("value not within bounds");
    }
    //Random number between MF LOWER BOUND and MF UPPER BOUND
    double mutationfactor = (rand() % ((MUTATION_FACTOR_UPPER_BOUND - MUTATION_FACTOR_LOWER_BOUND) *1000))/1000.0 + MUTATION_FACTOR_LOWER_BOUND;
   double new_value = value * mutationfactor;

   if (new_value < low_bound) {return low_bound;}
   else if (new_value > high_bound) {return high_bound;}
   else {return new_value}
}
