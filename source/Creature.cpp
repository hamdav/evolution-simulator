#include "Creature.h"
#include "Muscle.h"
#include <list>
#include <set>

using namespace std;

Creature :: Creature () 
{
    //Decide how many nodes and muscles there should be. 
    //The number of muscles must be at least one more than the number of nodes. 
    //The number of muscles cannot be more than n*(n-1)/2 as there would then be more than one muscle per pair of nodes. 
    int number_of_nodes = myRandInt(MIN_NO_NODES,MAX_NO_NODES);
    int number_of_muscles = myRandInt(number_of_nodes +1, number_of_nodes*(number_of_nodes-1)/2);

    // Create nodes 
    // connections is a map of ints that keeps track of the other nodes that the node is connected to. 
    map<int, list<int>> connections;
    for (int i = 0; i < number_of_nodes; i++)
    {
        Node n = Node();
        nodes.insert(n);
        connections[i] = list<int>();
    }

    // Create muscles
    int muscles_created = 0;
    

    set<Node>::iterator it = nodes.begin();
    int i = 0;

    while ((it + i) != nodes.end() -1)
    {
        //Connect node i and node i+1 with each other
        Muscle m = Muscle(*(it+i), *(it + i+1));
        muscles.push_back(m);

        //Add the connection to the list. 
        connections[i].push_back(i+1);
        muscles_created++;
        i++;
    }

    it = nodes.begin();
    while (muscles_created < number_of_muscles)
    {
        int n1 = myRandInt(0,number_of_nodes);
        int n2 = myRandInt(0,number_of_nodes);
        // is_not_already_connected is true if n2 is not in connections[n1]
        bool is_not_already_connected = find(connections[n1].begin(), connections[n1].end(), n2) == connections[n1].end();
        if (n1 != n2 && is_not_already_connected)
        {
            muscles_created++;
            Muscle m = Muscle(*(it+n1),*(it+n2));
            muscles.push_back(m);
        }
    }
}

Creature :: Creature (list<Muscle> _muscles)
{
    muscles = _muscles;
    for (Muscle const &muscle : muscles)
    {
        nodes.insert(muscle.node1);
        nodes.insert(muscle.node2);
    }
}

void Creature :: updateInternalForces(double t)
{
    for (Muscle const &muscle : muscles)
    {
        muscle.addForceToNodes(t)
    }
}
Creature Creature :: offspring()
{
    //TODO small chance of changing architechture
    //TODO Change some shit and return a new creature. 
}
    

