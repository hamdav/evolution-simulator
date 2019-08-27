#include "Node.h"
#include "Vector.h"
#include "mutate.h"

Node :: Node ()
{
    vel = Vector(0,0);
    acc = Vector(0,0);
    force = Vector(0,0);
    mass = 1;
    mu = 1;
}
Node :: Node (double _m, double _mu) : mass(_m), mu(_mu) 
{
    vel = Vector(0,0);
    acc = Vector(0,0);
    force = Vector(0,0);
}
Node Node :: child()
{
    double _m = mutate(1,1,mass);
    double _mu = mutate(1,1,mu);
    return Node(_m, _mu);
}
void Node :: addForce(Vector f) { force = force.add(f); }

void Node :: updateAcc() { acc = force.mul(1/mass); }

void Node :: updateVel(double dt) 
{
    vel = vel.add(acc.mul(dt));
}
void Node :: updatePos(double dt)
{
    pos = pos.add( vel.mul(dt) ).add(acc.mul(dt*dt/2.0));
}

Vector Node :: getPos() {return pos;}
void Node :: setPos(Vector p) {pos = p;}
Vector Node :: getVel() {return vel;}
Vector Node :: getAcc() {return acc;}
Vector Node :: getForce() {return force;}
void Node :: setVel(Vector v) {vel = v;}


