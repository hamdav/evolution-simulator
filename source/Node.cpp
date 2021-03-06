#include "Node.h"
#include "Vector.h"
#include "mutate.h"
#include "myRand.h"
#include <iostream>

Node :: Node ()
{
    vel = Vector(0,0);
    acc = Vector(0,0);
    force = Vector(0,0);
    mass = myRandInt(MIN_MASS,MAX_MASS);
    mu = myRand(MIN_MU, MAX_MU);
}
Node :: Node (double _m, double _mu) : mass(_m), mu(_mu) 
{
    vel = Vector(0,0);
    acc = Vector(0,0);
    force = Vector(0,0);
}
Node :: Node (const Node& n)
{
    mass = n.mass;
    mu = n.mu;
    pos = n.pos;
    prev_pos = n.prev_pos;
    vel = n.vel;
    acc = n.acc;
    force = n.force;
}

void Node :: mutateInPlace()
{
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        mass = mutate(MIN_MASS,MAX_MASS,mass);
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        mu = mutate(MIN_MU,MAX_MU,mu);
}
void Node :: addForce(Vector f) { force = force.add(f); }


void Node :: updateAcc() { acc = force.mul(1/mass); }

void Node :: updateVel(double dt) 
{
    vel = vel.add(acc.mul(dt));
}

void Node :: updatePos(double dt)
{
    pos = pos.add(vel.mul(dt)).add(acc.mul(dt*dt/2));
}
/* Verlet shit
void Node :: updatePos(double dt)
{
    Vector local_prev_pos = prev_pos;
    prev_pos = pos;

    pos = pos.mul(2).sub(local_prev_pos).add(acc.mul(dt*dt));
}
*/

void Node :: printNode() 
{
    std::cout << "Node: " << id << " Mass: " << mass << " Mu: " << mu << std::endl;
}

void Node :: zeroForce() {force = Vector(0,0);}
Vector Node :: getPos() {return pos;}
void Node :: setPos(Vector p) {pos = p; prev_pos = p;}
Vector Node :: getVel() {return vel;}
Vector Node :: getAcc() {return acc;}
Vector Node :: getForce() {return force;}
void Node :: setVel(Vector v) {vel = v;}
double Node :: getRadius() {return radius;}
double Node :: getMu() {return mu;}
double Node :: getMass() {return mass;}
int Node :: getId() {return id;}
void Node :: setId(int _id) {id = _id;}


