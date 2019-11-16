#include "menus.h"
#include "generationSimulation.h"
#include "single.h"

#define backToNormal "\033[0m"
#define bold "\033[1m"
#define underline "\033[4m"
#define inverse "\033[7m"
#define red "\033[34m"
#define yellow "\033[33m"

#define h1 "\033[4;1;7;34m"
#define h2 "\033[4;1;33m"

int currentGeneration = 0;

void resetScreen ()
{
    system("clear");

    std::cout << "\n\n";
    std::cout << h1 << " - - - Evolution Simulator - - - " << backToNormal << std::endl;
    std::cout << std::endl;
}

int menu (int n_args, std::string* options)
{

    std::cout << std::endl;
    for (int i = 0; i < n_args; i++)
    {
        std::cout << "  " << i << ":" << options[i] << std::endl;
    }

    int rv = n_args;

    while (true)
    {
        std::cout << "\n:";
        std::cin >> rv; 

        if (std::cin.fail() || rv >= n_args) { 
            std::cout << "Invalid option, try again...\n";
            std::cin.clear();
            std::cin.ignore(100,'\n');
            continue;
        }
        return rv;
    }
}
void generateCreaturesMenu (std::list<Creature> &population)
{
    resetScreen();
    std::cout << h2 << " - - Main Menu - - " << backToNormal << std::endl;
    std::cout << "Welcome to the evolutionsimulator 2000" << std::endl;

    std::string options[2] = {"Generate creatures", "Edit settings"};
    int choice = menu(2,options);

    if (choice==0)
    {
        // Create initial creatures
        for (int i = 0; i < POPULATION_SIZE; i++) {
            population.push_back(Creature());
        }
    }
    else if (choice==1)
    {
        settingsMenu(population);
    }
    return;
}

void settingsMenu (std::list<Creature> &population)
{
    resetScreen();
    std::cout << h2 << "Edit settings" << backToNormal << std::endl;
    std::cout << std::endl;
    std::cout << "Current settings are:" << std::endl;
    std::cout << "Population size: " << POPULATION_SIZE << std::endl;
    std::cout << "Maximum number of nodes: " << MAX_NO_NODES << std::endl;
    std::cout << "Minimum number of nodes: " << MIN_NO_NODES << std::endl;

    std::string options[4] = {"Go back to Main Menu","Edit Population Size","Edit Maximum Number of Nodes", "Edit Minimum Number of Nodes" };
    int choice = menu(4,options);

    if (choice==0)
    {
        generateCreaturesMenu(population);
    }
    else if (choice==1)
    {
        std::cout << "Input Population Size: ";
        std::cin >> POPULATION_SIZE;
        settingsMenu(population);
    }
    else if (choice==2)
    {
        std::cout << "Input Maximum Number of Nodes: ";
        std::cin >> MAX_NO_NODES;
        settingsMenu(population);
    }
    else if (choice==3)
    {
        std::cout << "Input Minimum Number of Nodes: ";
        std::cin >> MIN_NO_NODES;
        settingsMenu(population);
    }
    return;
}

void simulationsMenu (std::list<Creature> &population)
{
    resetScreen();

    std::cout << h2 << " - - Main Menu - - " << backToNormal << std::endl;
    std::cout << "The current generation is " << currentGeneration << std::endl;

    if (currentGeneration > 0)
    {
        std::list<Creature>::iterator it = population.begin();

        std::cout << "The maximum score of the population is " << it->getScore() << std::endl;
        std::advance(it, POPULATION_SIZE/2);
        std::cout << "The mean score of the population is "<< it->getScore() << std::endl;
    }

    std::string options[3] = {"Run a single generation", "Run n generations", "View a single simulation"};
    int choice = menu(3,options);

    if (choice==0)
    {
        currentGeneration++;
        runGeneration(population);
    }
    else if (choice==1)
    {
        int numberOfGenerations = 1;
        std::cout << "How many generations should be run?" << std::endl;
        std::cin >> numberOfGenerations;
        
        for (int i = 0; i < numberOfGenerations; i++)
        {
            resetScreen();
            currentGeneration++;

            std::list<Creature>::iterator it = population.begin();
            std::cout << "The maximum score of the population is " << it->getScore() << std::endl;
            std::advance(it, POPULATION_SIZE/2);
            std::cout << "The mean score of the population is "<< it->getScore() << std::endl;

            std::cout << "Running generation " << i+1 << " out of " << numberOfGenerations << "..." << std::endl;
            runGeneration(population);

        }
    }
    else if (choice==2)
    {
        int creatureId = POPULATION_SIZE + 1;
        std::cout << "Which creature would you like to see? " << std::endl;
        std::cout << "Must be number between 0 and " << POPULATION_SIZE-1 << std::endl;
        
        while (true)
        {
            std::cout << "\n:";
            std::cin >> creatureId;

            if (std::cin.fail() || creatureId >= POPULATION_SIZE) { 
                std::cout << "Invalid option, try again...\n";
                std::cin.clear();
                std::cin.ignore(100,'\n');
                continue;
            }
            break;
        }

        std::list<Creature>::iterator it = population.begin();
        std::advance(it, creatureId);

        int speed = 1;
        singleSimulation(*it, true, speed);
        std::cout << "Creature was scored: " << it->getScore() << std::endl;
    }

    return;
}

