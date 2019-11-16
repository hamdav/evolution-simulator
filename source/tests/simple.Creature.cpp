#include "Creature.h"
#include <stdlib.h>
#include <iostream>
//#include <


float Creature::getNumber() {
    return number;
}
float Creature::getScore() {
    return score;
}
void Creature::setScore(float s) 
{
    score = s;
}

Creature Creature :: offspring() {
    //srand(0);
    
    float new_number = number + (rand() % 201 - 100)/1000.0;
    Creature bob = Creature(new_number);
    return bob; 
}

Creature :: Creature() {
    number = (rand() % 100) / 100.0;
}

// sets number to n
Creature :: Creature(float n) : number(n) {}


