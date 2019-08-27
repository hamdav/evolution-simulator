#include "Muscle.h"
#include "vector.h"
#include "mutate.h"


Muscle(Node n1, Node n2, double _period = 1, double _fraction_contracted = 0.5, double _contracted_length = 1, double _extended_length = 2, double _phase_shift = 0, double _k = 1, double _c = 1) 
{
    node1 = n1;
    node2 = n2;
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
    double phase_shifted_t = t - phase_shift;
    double internal_t = phase_shifted_t % period;
    double phase = internal_t/period;

    return phase <= fraction_contracted;
}

Vector Muscle :: forceOnNode1(bool is_contracted)
{
    // Positionvector from 1 to 2
    Vector relativePos = node2.getPos().sub(node1.getPos());
    Vector normedRelPos = relativePos/relativePos.length();

    // Magnitude is negative if spring force on node 1 is away from 2
    double springForceMagnitude = k*(relativePos.length() - (is_contracted ? lengthContracted : lengthExtended));
    Vector springForce = normedRelPos.mul(springForceMagnitude);

    // Velocity of node 1 relative to node 2
    Vector relativeVel = node1.velocity.sub(node2.velocity);
    
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
    force_on_1.mul(-1);
    node2.addForce(forceOn1);
}
Muscle Muscle :: offspring()
{
    _period = mutate(1,10,period);
    _fraction_contracted = mutate(0,1,fraction_contracted);
    _contracted_length = mutate(1,10,contracted_length);
    _extended_length = mutate(1,10,extended_length);
    _phase_shift = mutate(0,1,phase_shift);
    //_k = mutate(1,1,k);
    //_c = mutate(1,1,c);
    return Muscle(node1, node2, _period , _fraction_contracted , _contracted_length , _extended_length , _phase_shift , _k , _c );
}
