#pragma once

#include <iostream>
#include "Creature.h"


extern int POPULATION_SIZE;
extern int MAX_NO_NODES;
extern int MIN_NO_NODES;

void resetScreen();
int menu(int, std::string*);
void generateCreaturesMenu (std::vector<Creature>&);
void settingsMenu (std::vector<Creature>&);
void simulationsMenu(std::vector<Creature>&);
