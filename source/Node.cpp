#include "Node.h"
#include "vector.h"

Node :: Node ()
{
    vel = Vector(0,0);
    acc = Vector(0,0);
    force = Vector(0,0);
    mass = 1;
    mu = 1;
}
Vector Node :: getPos() {return pos;}
Vector Node :: getVel() {return vel;}
Vector Node :: getAcc() {return acc;}
Vector Node :: getForce() {return force;}
void Node :: setVel(Vector v) {vel = v;}


