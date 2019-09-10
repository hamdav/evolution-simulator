#include "Node.h"
#include "Vector.h"
#include "mutate.h"
#include "myRand.h"

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
void Node :: mutateInPlace()
{
    mass = mutate(MIN_MASS,MAX_MASS,mass);
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


