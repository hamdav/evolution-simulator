#include "Muscle.h"
#include "vector.h"


bool Muscle :: isContracted(double t)
{
    double phase_shifted_t = t - phase_shift;
    double internal_t = phase_shifted_t % period;
    double phase = internal_t/period;

    return phase <= fraction_contracted;
}

Vector Muslce :: forceOnNode1(bool is_contracted)
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

