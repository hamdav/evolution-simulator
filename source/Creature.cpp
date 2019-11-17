#include "Creature.h"
#include "Muscle.h"
#include "myRand.h"
#include <list>
#include <map>
#include <vector>
#include <algorithm> // for find
#include <iostream> // tmp please remove when appropriate

using namespace std;

Creature :: Creature () 
{
    //Decide how many nodes and muscles there should be. 
    //The number of muscles must be at least one more than the number of nodes. 
    //The number of muscles cannot be more than n*(n-1)/2 as there would then be more than one muscle per pair of nodes. 
    int number_of_nodes = myRandInt(MIN_NO_NODES,MAX_NO_NODES);
    //cout << number_of_nodes << endl;
    
    int number_of_muscles = myRandInt(number_of_nodes, number_of_nodes*(number_of_nodes-1)/2+1);
    //cout << number_of_muscles << endl;

    // Create nodes 
    // connections is a map of ints that keeps track of the other nodes that the node is connected to. 
    for (int i = 0; i < number_of_nodes; i++)
    {
        Node n = Node();
        n.setId(i);
        nodes[i] = n;
        connections[i] = list<int>();
    }

    // Create muscles
    int muscles_created = 0;
    
     
    for (int i = 0; i < number_of_nodes -1; i++)
    {
        //Connect node i with random other node
        Muscle m = Muscle(nodes[i], nodes[i+1]);
        muscles.push_back(m);

        //Add the connection to the list. 
        connections[i].push_back(i+1);
        connections[i+1].push_back(i);
        muscles_created++;
    }

    while (muscles_created < number_of_muscles)
    {
        int n1 = myRandInt(0,number_of_nodes);
        int n2 = myRandInt(0,number_of_nodes);
        // is_not_already_connected is true if n2 is not in connections[n1]
        bool is_not_already_connected = find(connections[n1].begin(), connections[n1].end(), n2) == connections[n1].end();
        if (n1 != n2 && is_not_already_connected)
        {
            muscles_created++;
            Muscle m = Muscle(nodes[n1], nodes[n2]);
            muscles.push_back(m);
            connections[n1].push_back(n2);
            connections[n2].push_back(n1);
        }
    }
    // TMP Printing code to se that everything is alright
    /*
    for (int i = 0; i < number_of_nodes; i++)
    {
        cout << i << ": " << endl;
        for (int j : connections[i])
            cout << j << endl;
    }
    cout << "Number of muscles: " << muscles_created << "should be " << number_of_muscles << endl;
    
    */
}
Creature :: Creature (const Creature &c)
{

    for (const Muscle& m : c.muscles)
    {
        Node node1(m.getNode1());
        int n1id = m.getNode1().getId();
        node1.setId(n1id);

        Node node2(m.getNode2());
        int n2id = m.getNode2().getId();
        node2.setId(n2id);

        if ( nodes.find(n1id) == nodes.end() )
            nodes[n1id] = node1;
        if ( nodes.find(n2id) == nodes.end() )
            nodes[n2id] = node2;

        Muscle new_m = Muscle(nodes[n1id], nodes[n2id], m);
        muscles.push_back(new_m);
    }
    connections = c.connections;

    std::cout << "COPY CONSTRUCTOR WAS CALLED";
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
    for (Muscle& muscle : muscles)
    {
        muscle.addForceToNodes(t);
    }
}
Creature Creature :: offspring()
{

    Creature new_creature = Creature();
    // Make nodes map empty to accomodate the new nodes. 
    new_creature.nodes.clear();
    // Same with muscles
    // We may have a problem as the Muscles may be destroyed... will look into this later. 
    new_creature.muscles.clear();
    

    std::cout << muscles.size();
    for (Muscle m : muscles)
    {
        Node node1 = m.getNode1();
        node1.mutateInPlace();
        int n1id = node1.getId();

        Node node2 = m.getNode2();
        node2.mutateInPlace();
        int n2id = node2.getId();

        if ( new_creature.nodes.find(n1id) == new_creature.nodes.end() )
            new_creature.nodes[n1id] = node1;
        if ( new_creature.nodes.find(n2id) == new_creature.nodes.end() )
            new_creature.nodes[n2id] = node2;

        Muscle new_m = Muscle(new_creature.nodes[n1id], new_creature.nodes[n2id], m);
        new_m.mutateInPlace();
        new_creature.muscles.push_back(new_m);
    }
    new_creature.connections = connections;

    //TODO Change some shit and return a new creature. 
    return new_creature;
}

Vector Creature :: getAvgPos()
{
    Vector cum_pos = Vector(0,0);
    for (auto id_node_pair : nodes)
    {
        Node n = id_node_pair.second;
        cum_pos = cum_pos.add(n.getPos());
    }
    Vector avg_pos = cum_pos.mul(1.0/nodes.size());
    return avg_pos;
}

void Creature :: setScore(double s) { score = s; }
double Creature :: getScore () {return score;}

void Creature :: printCreature()
{
    for (auto id_node_pair : nodes)
    {
        id_node_pair.second.printNode();
    }
    std::cout << std::endl;
    for (Muscle m : muscles)
    {
        m.printMuscle();
    }
}


    

