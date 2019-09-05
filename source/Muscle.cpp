#include <cmath> // fmod
#include "Muscle.h"
#include "Vector.h"
#include "Node.h"
#include "mutate.h"
#include "myRand.h"
#include <iostream>


Muscle :: Muscle(Node& n1, Node& n2) : node1(n1), node2(n2)
{
    
    period = myRand(MIN_PERIOD,MAX_PERIOD);
    fraction_contracted = myRand(MIN_FRAC_CON,MAX_FRAC_CON);
    contracted_length = myRand(MIN_LEN_CON,MAX_LEN_CON);
    extended_length = myRand(MIN_LEN_EXT,MAX_LEN_EXT);
    phase_shift = myRand(MIN_PHASE_SHIFT,MAX_PHASE_SHIFT);
    k = myRand(MIN_K, MAX_K);
    c = myRand(MIN_C, MAX_C);
    
}
Muscle :: Muscle(Node& n1, Node& n2, double _period = 1, double _fraction_contracted = 0.5, double _contracted_length = 1, double _extended_length = 2, double _phase_shift = 0, double _k = 1, double _c = 10) : node1(n1), node2(n2)
{
    period = _period;
    fraction_contracted = _fraction_contracted;
    contracted_length = _contracted_length;
    extended_length = _extended_length;
    phase_shift = _phase_shift;
    k = _k;
    c = _c;
}

bool Muscle :: isContracted(double t)
{
    double internal_t = fmod(t, period);
    double phase = (double)internal_t / period;
    double phase_shifted_phase = phase - phase_shift;

    return phase <= fraction_contracted;
}

Vector Muscle :: forceOnNode1(bool is_contracted)
{
    // Positionvector from 1 to 2
    Vector relativePos = node2.getPos().sub(node1.getPos());
    Vector normedRelPos = relativePos.normed();

    // Magnitude is negative if spring force on node 1 is away from 2
    double springForceMagnitude = k*(relativePos.length() - (is_contracted ? contracted_length : extended_length));

    Vector springForce = normedRelPos.mul(springForceMagnitude);

    // Velocity of node 1 relative to node 2
    Vector relativeVel = node1.getVel().sub(node2.getVel());
    
    // Magnitude is negative if dampened force on node 1 is away node 2
    double dampenedForceMagnitude = -c * relativeVel.dot(normedRelPos);
    Vector dampenedForce = normedRelPos.mul(dampenedForceMagnitude);


    return springForce.add(dampenedForce);
}


void Muscle :: addForceToNodes(double t)
{
    bool contracted = isContracted(t);
    Vector force_on_1 = forceOnNode1(contracted);

    node1.addForce(force_on_1);

    // Newton's third law
    Vector force_on_2 = force_on_1.mul(-1);
    node2.addForce(force_on_2);
}
void Muscle :: mutateInPlace()
{
    period = mutate(MIN_PERIOD,MAX_PERIOD,period);
    fraction_contracted = mutate(MIN_FRAC_CON,MAX_FRAC_CON,fraction_contracted);
    contracted_length = mutate(MIN_LEN_CON,MAX_LEN_CON,contracted_length);
    extended_length = mutate(MIN_LEN_EXT,MAX_LEN_EXT,extended_length);
    phase_shift = mutate(MIN_PHASE_SHIFT,MAX_PHASE_SHIFT,phase_shift);
    k = 1;
    c = 1;
    //_k = mutate(1,1,k);
    //_c = mutate(1,1,c);
    //return Muscle(node1, node2, period = _period , fraction_contracted = _fraction_contracted , contracted_length = _contracted_length , extended_length = _extended_length , phase_shift = _phase_shift , k = _k , c = _c );
}
