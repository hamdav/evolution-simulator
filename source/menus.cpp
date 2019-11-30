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
    //system("clear");

    std::cout << "\n\n";
    std::cout << h1 << " - - - Evolution Simulator - - - " << backToNormal << std::endl;
    std::cout << std::endl;
}

void printPopulation(std::vector<Creature>& population)
{
    int i = 0;
    for (Creature& c : population)
    {
        printf("| id: %3d kind: %d%-2d score: % 6.2f | ", i, c.nodes.size(),  c.muscles.size(), c.getScore());
        if (i% 4 == 3)
            std::cout << std::endl;
        i++;
    }
    std::cout << "Press enter key to go back to menu" << std::endl;
    std::cin.get();
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
void generateCreaturesMenu (std::vector<Creature> &population)
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

        //Test them, each creature is in singleSimulations given a score (accessed by creature.getScore())
        for (Creature& c : population){
            // Sets creature score to the appropriate value
            singleSimulation(c, false, 1);
        }
    }
    else if (choice==1)
    {
        settingsMenu(population);
    }
    return;
}

void settingsMenu (std::vector<Creature> &population)
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

void simulationsMenu (std::vector<Creature> &population)
{
    resetScreen();

    std::cout << h2 << " - - Main Menu - - " << backToNormal << std::endl;
    std::cout << "The current generation is " << currentGeneration << std::endl;

    double total_score = 0;
    double max_score = -1;
    Creature best_creature;
    for (Creature& c : population)
    {
        total_score += c.getScore();
        if (c.getScore() > max_score)
        {
            max_score = c.getScore();
            best_creature = c;
        }
    }
    double mean_score = total_score/POPULATION_SIZE;


    std::cout << "The maximum score of the population is " << max_score << std::endl;
    std::cout << "The mean score of the population is "<< mean_score << std::endl;

    std::string options[4] = {"Run a single generation", "Run n generations", "View a single simulation", "View Population"};
    int choice = menu(4,options);

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

            double total_score = 0;
            double max_score = -1;
            for (Creature& c : population)
            {
                total_score += c.getScore();
                if (c.getScore() > max_score)
                    max_score = c.getScore();
            }
            double mean_score = total_score/POPULATION_SIZE;


            std::cout << "The maximum score of the population is " << max_score << std::endl;
            std::cout << "The mean score of the population is "<< mean_score << std::endl;

            std::cout << "Running generation " << i+1 << " out of " << numberOfGenerations << "..." << std::endl;
            runGeneration(population);

        }
    }
    else if (choice==2)
    {
        int creatureId = POPULATION_SIZE + 1;
        std::cout << "Which creature would you like to see? " << std::endl;
        std::cout << "Must be number between 0 and " << POPULATION_SIZE-1 << " or -1 for best creature" << std::endl;
        
        while (true)
        {
            std::cout << "\n:";
            std::cin >> creatureId;

            if (std::cin.fail() || creatureId >= POPULATION_SIZE || creatureId < -1) { 
                std::cout << "Invalid option, try again...\n";
                std::cin.clear();
                std::cin.ignore(100,'\n');
                continue;
            }
            break;
        }

        if (creatureId == -1)
        {
            int speed = 1;
            singleSimulation(best_creature,true,speed);
            return;
        }

        std::vector<Creature>::iterator it = population.begin();
        std::advance(it, creatureId);

        int speed = 1;
        singleSimulation(*it, true, speed);
        std::cout << "Creature was scored: " << it->getScore() << std::endl;
    }
    else if (choice==3)
    {
        printPopulation(population);
    }

    return;
}

