#include "Creature.h"
#include "Muscle.h"
#include "myRand.h"
#include <list>
#include <map>
#include <vector>
#include <algorithm> // for find
#include <iostream> // tmp please remove when appropriate
#include <utility>

using namespace std;

Creature :: Creature () 
{
    //Decide how many nodes and muscles there should be. 
    //The number of muscles must be at least one more than the number of nodes. 
    //The number of muscles cannot be more than n*(n-1)/2 as there would then be more than one muscle per pair of nodes. 
    int number_of_nodes = myRandInt(MIN_NO_NODES,MAX_NO_NODES);
    
    int number_of_muscles = myRandInt(number_of_nodes, number_of_nodes*(number_of_nodes-1)/2+1);

    // Create nodes 
    for (int i = 0; i < number_of_nodes; i++)
    {
        Node n = Node();
        n.setId(i);
        nodes[i] = n;
    }

    // Create muscles
    int muscles_created = 0;
    
     
    for (int i = 0; i < number_of_nodes -1; i++)
    {
        //Connect node i with random other node
        Muscle m = Muscle();
        muscles[std::make_pair(i,i+1)] = m;

        muscles_created++;
    }

    // Generate more muscles connecting two random nodes until there are enough
    while (muscles_created < number_of_muscles)
    {
        int n1 = myRandInt(0,number_of_nodes);
        int n2 = myRandInt(0,number_of_nodes);
        // is_not_already_connected is true if n2 is not connected to n1
        bool is_not_already_connected = (muscles.find(std::make_pair(n1,n2)) == muscles.end()) && (muscles.find(std::make_pair(n2,n1)) == muscles.end());
        if (n1 != n2 && is_not_already_connected)
        {
            muscles_created++;
            Muscle m = Muscle();
            muscles[std::make_pair(n1,n2)] = m;
        }
    }
}

Creature :: Creature (const Creature& c)
{
    for (auto nodeidpair : c.nodes)
    {
        int nodeid = nodeidpair.first;
        nodes[nodeid] = Node(nodeidpair.second);
    }

    for (auto mappair : c.muscles)
    {
        std::pair<int,int> nodeids = mappair.first;
        muscles[nodeids] = Muscle(mappair.second);
    }
}

void Creature :: setInitialPos()
{
    for (int i = 0;i < nodes.size(); i++)
    {
        // Initial position is (1,-0.5),(1, 0.5),(1.5,-0.5),(1.5,0.5),(2,-0.5) and so on
        Vector init_pos = Vector(-0.5 + (i%2), 1 + 0.25*(i - (i%2)));
        nodes[i].setPos(init_pos);
    }
}


void Creature :: updateInternalForces(double t)
{
    for (auto it = muscles.begin(); it != muscles.end(); ++it)
    {
        Muscle& m = it->second;
        int node1id = it->first.first;
        int node2id = it->first.second;
        m.addForceToNodes(nodes[node1id], nodes[node2id], t);
    }
}
Creature Creature :: offspring()
{

    Creature new_creature(*this);

    for (auto it = new_creature.muscles.begin(); it != new_creature.muscles.end(); ++it)
    {
        it->second.mutateInPlace();
    }
    for (auto it = new_creature.nodes.begin(); it != new_creature.nodes.end(); ++it)
    {
        it->second.mutateInPlace();
    }

    return new_creature;
}

Vector Creature :: getAvgPos()
{
    Vector cum_pos = Vector(0,0);
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        Node& n = it->second;
        cum_pos = cum_pos.add(n.getPos());
    }
    Vector avg_pos = cum_pos.mul(1.0/nodes.size());
    return avg_pos;
}

void Creature :: setScore(double s) { score = s; }
double Creature :: getScore () {return score;}

void Creature :: printCreature()
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        it->second.printNode();
    }
    std::cout << std::endl;

    for (auto it = muscles.begin(); it != muscles.end(); ++it)
    {
        it->second.printMuscle();
    }
}


    

