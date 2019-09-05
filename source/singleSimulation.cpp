#include "single.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>
#include <cmath> // for atan
#include <iostream>
#include <ctime>

#define PI 3.14159265 

double GRAVITATIONAL_ACCELERATION = 9.8;

void singleSimulation(Creature &bob, bool graphical) 
{
    int seed = time(NULL);
    srand(seed);
    sf::RenderWindow window(sf::VideoMode(200,200),"Eve",sf::Style::Resize);
    window.setFramerateLimit(1000);


    int i = 0;
    for (Node& node : bob.nodes)
    {
        node.setPos(Vector(100*i,100*std::min(i,1)));
        i++;
    }

    double time = 0;
    double dt = 0.001;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
        }

        // Physics
        time += dt;
        bob.updateInternalForces(time);
        for (Node& node : bob.nodes)
        {
            //Gravity
            node.addForce(Vector(0,-node.getMass()*GRAVITATIONAL_ACCELERATION));
            if (nodeTouchesGround(node))
                addFrictionToNode(node); 

            node.updateAcc();
            node.updateVel(dt);
            if (nodeTouchesGround(node))
            {
                //If the node touches the ground, set velocity and acceleration to 0 if they are accelerating/velocitating down. Else leave them be. (the node should not travel into the ground).
                node.setVel(Vector(node.getVel().x, max(node.getVel().y, 0)));
                node.addForce(Vector(0,max(0,-1*node.getForce().y)));

            }

            node.updatePos(dt);
            node.zeroForce();
        }
        


        //Clear the screen
        window.clear();


        //Draw muscles
        for (int n1 = 0; n1 < bob.nodes.size(); n1++)
        {
            for (int n2 : bob.connections[n1])
            {
                Vector p1 = bob.nodes[n1].getPos();
                Vector p2 = bob.nodes[n2].getPos();
                Vector diff = p2.sub(p1); // from p1 to p2
                double muscle_length = diff.length();
                double muscle_width = 12;
                double angle = atan(diff.y/diff.x) * 180 / PI ;
                //Create the rectangle
                sf::RectangleShape muscle(sf::Vector2f(muscle_length, muscle_width));
                // Set the origin of the rectangle to the center
                muscle.setOrigin(muscle_length/2, muscle_width/2);
                // Move the center of the rectangle in the middle of the two nodes
                Vector p12 = p1.add(diff.mul(0.5));
                muscle.setPosition(p12.x, p12.y);
                //Rotate the rectangle to fit
                muscle.setRotation(angle);
                //Make it a pretty color
                muscle.setFillColor(sf::Color(200, 100, 0));
                // Draw it to the screen
                window.draw(muscle);

            }
        }
        // Draw nodes
        for (int i = 0; i < bob.nodes.size(); i++)
        {
            sf::CircleShape circle(bob.nodes[i].getRadius());
            circle.setOrigin(bob.nodes[i].getRadius(),bob.nodes[i].getRadius());
            circle.setPosition(bob.nodes[i].getPos().x, bob.nodes[i].getPos().y);
            circle.setFillColor(sf::Color(100, 150, 50));
            window.draw(circle);
        }

        window.display();
    }
}

bool nodeTouchesGround(Node n)
{
    if (n.getPos().y <= 0.0)
        return true;
    return false;
}
void addFrictionToNode(Node& n)
{
    double normal_force = -n.getForce().y;
    
    // No normal force, no friction
    if (normal_force < 0)
        return;

    double frictional_force_magnitude = normal_force * n.getMu();
    
    int direction = n.getVel().x > 0 ? -1 : 1;

    //if (abs(n.getVel().x) < 0.5) // Dont do anything if v is to small
    n.addForce(Vector(frictional_force_magnitude * direction,0));
}

    
