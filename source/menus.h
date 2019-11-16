#pragma once

#include <iostream>
#include "Creature.h"


extern int POPULATION_SIZE;
extern int MAX_NO_NODES;
extern int MIN_NO_NODES;

void resetScreen();
int menu(int, std::string*);
void generateCreaturesMenu (std::list<Creature>&);
void settingsMenu (std::list<Creature>&);
void simulationsMenu(std::list<Creature>&);
