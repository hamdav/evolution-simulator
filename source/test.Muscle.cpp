#include "Muscle.h"
#include "Node.h"
#include <SFML/Graphics.hpp>
#include <cmath> // for atan
#include <iostream>

#define PI 3.14159265 

int main()
{
    sf::RenderWindow window(sf::VideoMode(200,200),"Eve",sf::Style::Resize);
    window.setFramerateLimit(100);

    Node node1 = Node();
    Node node2 = Node();
    node1.setPos(Vector(100,100));
    node2.setPos(Vector(500,500));
    //node1.addForce(Vector(500,0));
    //node2.addForce(Vector(-500,0));
    // node node period frac_con len_con, len_ext, phase_shift, k, c, 
    // Critically dampened is c = 2*sqrt(k*m)
    Muscle marcus = Muscle(node1, node2, 1, 0.5, 100, 200, 0, 10, 6.5);

    double time = 0;
    double dt = 0.01;
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

        marcus.addForceToNodes(time);
        node1.updateAcc();
        node1.updateVel(dt);
        node1.updatePos(dt);
        node2.updateAcc();
        node2.updateVel(dt);
        node2.updatePos(dt);

        node1.zeroForce();
        node2.zeroForce();


        //Clear the screen
        window.clear();

        //Draw marcus
        Vector p1 = node1.getPos();
        Vector p2 = node2.getPos();
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
        
        
        window.display();
    }
    return 0;
}
