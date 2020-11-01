#include "single.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>
#include <cmath> // for atan
//#include <algorithm> // for max
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <sstream>

#define PI 3.14159265 

const double GRAVITATIONAL_ACCELERATION = 5;
const int MAGNIFICATION_FACTOR = 100;
const double TIME_LIMIT = 20;

// There is a difference between physical coordinates (the ones used to calculate the physics with) and drawing coordinates (the ones drawn to the screen). 
// Physical is on the order of magnitue of 1 while drawing on 100
// Drawing also has the y axis flipped and moved down 600 pixels
// further, drawing is shifted center.x*100 units to the right to make the creature appear inside the screen at all times
// This function takes a positional vector v and center in physical coordinates and returns a vector in drawing coordinates
Vector toDrawCoord(Vector v, Vector center)
{
    v = v.mul(MAGNIFICATION_FACTOR);
    center = center.mul(MAGNIFICATION_FACTOR);
    return Vector(v.x + 500 - center.x, 600-v.y);
}

bool nodeTouchesGround(Node n)
{
    if (n.getPos().y <= n.getRadius())
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

std::string toString(int i)
{
    // Convert in to string
    std::string out_string;
    std::stringstream ss;
    ss << i;
    out_string = ss.str();
    return out_string;
}

bool updatePhysics(Creature& ann, double time, double dt)
{
    // If all nodes are on the ground at the same time, this returns false, and the simulation should be stopped. 
    ann.updateInternalForces(time);

    bool all_nodes_on_ground = true;

    for (auto& id_node_pair : ann.nodes)
    {
        Node& node = id_node_pair.second;
        //Gravity
        node.addForce(Vector(0,-node.getMass()*GRAVITATIONAL_ACCELERATION));
        if (nodeTouchesGround(node))
            addFrictionToNode(node); 

        node.updateAcc();
        node.updateVel(dt);

        if (nodeTouchesGround(node))
        {
            //If the node touches the ground, set velocity and acceleration to 0 if they are accelerating/velocitating down. Else leave them be. (the node should not travel into the ground).
            node.setVel(Vector(node.getVel().x, std::max(node.getVel().y, 0.0)));
            node.addForce(Vector(0,std::max(0.0,-1*node.getForce().y)));
            node.setPos(Vector(node.getPos().x, 0 + node.getRadius()));
        }
        else
            all_nodes_on_ground = false;

        node.updatePos(dt);
        node.zeroForce();
    }

    return all_nodes_on_ground;
}

    
void singleSimulation(Creature& bob, bool graphical, int playback_speed) 
{
    double time = 0;
    double dt = 0.01;

    bob.setInitialPos();

    if (!graphical)
    {
        while (time < TIME_LIMIT)
        {
            bool all_nodes_on_ground = updatePhysics(bob, time, dt);
            time += dt;
            if (all_nodes_on_ground)
                break;
        }
        bob.setScore(bob.getAvgPos().x);
        return;
    }
    else
    {
        sf::Font font;
        if (!font.loadFromFile("./resources/dealerplate california.ttf")){
            throw std::logic_error("font not found");
        }

        sf::RenderWindow window(sf::VideoMode(200,200),"Eve",sf::Style::Resize);
        window.setFramerateLimit(100);

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
            for (int i = 0; i <= playback_speed; i++)
            {
                bool all_nodes_on_ground = updatePhysics(bob, time, dt);
                time += dt;
                if (all_nodes_on_ground)
                    time = TIME_LIMIT;
            }


            //Clear the screen
            window.clear();

            // Draw sky
            sf::RectangleShape sky(sf::Vector2f(4000,4000));
            sky.setPosition(0,0);
            sky.setFillColor(sf::Color(0,100,250));
            window.draw(sky);
             
            
            // Draw ground
            sf::RectangleShape ground(sf::Vector2f(4000,4000));
            ground.setPosition(0,600);
            ground.setFillColor(sf::Color(0,100,0));
            window.draw(ground);

            //Draw poles
            double center_mod_4 = bob.getAvgPos().x - std::fmod(bob.getAvgPos().x,4.0);
            for (int i = -3; i < 3; i++)
            {
                //Draw clouds
                sf::CircleShape circle1(20);
                sf::CircleShape circle2(20);
                sf::CircleShape circle3(20);
                sf::CircleShape mouth(10);
                sf::CircleShape eye1(5);
                sf::CircleShape eye2(5);
                sf::RectangleShape cloudbase(sf::Vector2f(50,20));

                circle1.setOrigin(20,20);
                circle2.setOrigin(20,20);
                circle3.setOrigin(20,20);
                mouth.setOrigin(10,10);
                eye1.setOrigin(5,5);
                eye2.setOrigin(5,5);
                cloudbase.setOrigin(25,0);

                int upshift = (((int)center_mod_4 + i*4)%8)/10;
                Vector cloud_pos = toDrawCoord(Vector(center_mod_4 + i*4, 5 + upshift),bob.getAvgPos());

                circle1.setPosition(cloud_pos.x,cloud_pos.y);//400,220);
                circle2.setPosition(cloud_pos.x + 25, cloud_pos.y - 20); //425,200);
                circle3.setPosition(cloud_pos.x + 50, cloud_pos.y); //450,220);
                mouth.setPosition(cloud_pos.x + 25, cloud_pos.y-4);
                eye1.setPosition(cloud_pos.x +17, cloud_pos.y -15);
                eye2.setPosition(cloud_pos.x +32, cloud_pos.y -15);
                cloudbase.setPosition(cloud_pos.x + 25, cloud_pos.y); //420,240);
            
                circle1.setFillColor(sf::Color(255,255,255));
                circle2.setFillColor(sf::Color(255,255,255));
                circle3.setFillColor(sf::Color(255,255,255));
                cloudbase.setFillColor(sf::Color(255,255,255));
                mouth.setFillColor(sf::Color(0,0,0));
                eye1.setFillColor(sf::Color(0,0,0));
                eye2.setFillColor(sf::Color(0,0,0));

                window.draw(cloudbase);
                window.draw(circle1);
                window.draw(circle3);
                window.draw(mouth);
                window.draw(circle2);
                window.draw(eye1);
                window.draw(eye2);

                // Draw poles
                sf::RectangleShape pole(sf::Vector2f(20,100));
                pole.setOrigin(10,0);
                Vector pole_pos = toDrawCoord(Vector(center_mod_4 + i*4, 1),bob.getAvgPos());
                pole.setPosition(pole_pos.x, pole_pos.y);
                pole.setFillColor(sf::Color(255,255,255));
                window.draw(pole);

                sf::RectangleShape sign(sf::Vector2f(80,50));
                sign.setOrigin(40,0);
                Vector sign_pos = toDrawCoord(Vector(center_mod_4 + i*4, 1),bob.getAvgPos());
                sign.setPosition(sign_pos.x, sign_pos.y);
                sign.setFillColor(sf::Color(255,255,255));
                window.draw(sign);

                sf::Text text;
                text.setString( toString(center_mod_4 + i*4) + " m");
                text.setFont(font);
                //In pixels, not points
                text.setCharacterSize(25);
                text.setFillColor(sf::Color(255,0,0));
                text.setStyle(sf::Text::Bold );
                Vector text_pos = toDrawCoord(Vector(center_mod_4 + i*4 - 0.2, 0.95),bob.getAvgPos());
                text.setPosition(text_pos.x, text_pos.y);
                window.draw(text);
            }

            // Draw score and time
            sf::Text score;
            score.setString("Score: " +toString(bob.getAvgPos().x) + "\nTime: " + toString((int)time));
            score.setFont(font);
            score.setCharacterSize(25);
            score.setFillColor(sf::Color(255,255,255));
            score.setStyle(sf::Text::Bold);
            Vector score_pos = Vector(10,10);
            score.setPosition(score_pos.x, score_pos.y);
            window.draw(score);

            //Draw muscles 
            for (auto it = bob.muscles.begin(); it != bob.muscles.end(); ++it)
            {
                int n1 = it->first.first;
                int n2 = it->first.second;

                Vector p1 = bob.nodes[n1].getPos();
                Vector p2 = bob.nodes[n2].getPos();
                Vector diff = p2.sub(p1); // from p1 to p2
                Vector p12 = p1.add(diff.mul(0.5)); // Point in between p1 and p2

                double muscle_length = diff.length()*MAGNIFICATION_FACTOR;
                double muscle_width = 12;
                double angle = atan(-diff.y/diff.x) * 180 / PI ;
                //Create the rectangle
                sf::RectangleShape muscle(sf::Vector2f(muscle_length, muscle_width));
                // Set the origin of the rectangle to the center
                muscle.setOrigin(muscle_length/2, muscle_width/2);
                // Move the center of the rectangle in the middle of the two nodes
                Vector drawp12 = toDrawCoord(p12,bob.getAvgPos());
                muscle.setPosition(drawp12.x, drawp12.y);
                //Rotate the rectangle to fit
                muscle.setRotation(angle);
                //Make it a pretty color
                muscle.setFillColor(sf::Color(200, 100, 0));
                // Draw it to the screen
                window.draw(muscle);
            }
            // Draw nodes
            for (int i = 0; i < bob.nodes.size(); i++)
            {
                int radius = (int)(bob.nodes[i].getRadius() * MAGNIFICATION_FACTOR);
                sf::CircleShape circle(radius);
                circle.setOrigin(radius,radius);
                Vector drawp = toDrawCoord(bob.nodes[i].getPos(), bob.getAvgPos());
                circle.setPosition(drawp.x, drawp.y);
                double mu_for_color = bob.nodes[i].getMu();
                circle.setFillColor(sf::Color(255/(1+mu_for_color*10), 255/(1+mu_for_color*40), 255/(1+mu_for_color*40)));
                window.draw(circle);
            }

            window.display();

            if (time >= TIME_LIMIT)
            {
                bob.setScore(bob.getAvgPos().x);
                return;
            }
        }
    }
}
