#include <cmath> // fmod
#include "Muscle.h"
#include "Vector.h"
#include "Node.h"
#include "mutate.h"
#include "myRand.h"
#include <iostream>


Muscle :: Muscle()
{
    period = myRand(MIN_PERIOD,MAX_PERIOD);
    fraction_contracted = myRand(MIN_FRAC_CON,MAX_FRAC_CON);
    contracted_length = myRand(MIN_LEN_CON,MAX_LEN_CON);
    extended_length = myRand(MIN_LEN_EXT,MAX_LEN_EXT);
    phase_shift = myRand(MIN_PHASE_SHIFT,MAX_PHASE_SHIFT);
    k = myRand(MIN_K, MAX_K);
    c = myRand(MIN_C, MAX_C);
    
}
Muscle :: Muscle(const Muscle& m)
{
    period = m.period;
    fraction_contracted = m.fraction_contracted;
    contracted_length = m.contracted_length;
    extended_length = m.extended_length;
    phase_shift = m.phase_shift;
    k = m.k;
    c = m.c;
}
void Muscle :: mutateInPlace()
{
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        period = mutate(MIN_PERIOD,MAX_PERIOD,period);
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        fraction_contracted = mutate(MIN_FRAC_CON,MAX_FRAC_CON,fraction_contracted);
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        contracted_length = mutate(MIN_LEN_CON,MAX_LEN_CON,contracted_length);
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        extended_length = mutate(MIN_LEN_EXT,MAX_LEN_EXT,extended_length);
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        phase_shift = mutate(MIN_PHASE_SHIFT,MAX_PHASE_SHIFT,phase_shift);
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        k = mutate(MIN_K, MAX_K, k);
    if (myRand(0,1,3) < SINGLE_GENE_MUTATION_PROB)
        c = mutate(MIN_C, MAX_C, c);
}
bool Muscle :: isContracted(double t)
{
    double internal_t = fmod(t, period);
    double phase = (double)internal_t / period;
    double phase_shifted_phase = phase - phase_shift;

    return phase <= fraction_contracted;
}

Vector Muscle :: forceOnNode1(Node& node1, Node& node2, bool is_contracted)
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


void Muscle :: addForceToNodes(Node& node1, Node& node2, double t)
{
    bool contracted = isContracted(t);
    Vector force_on_1 = forceOnNode1(node1 ,node2, contracted);

    node1.addForce(force_on_1);

    // Newton's third law
    Vector force_on_2 = force_on_1.mul(-1);
    node2.addForce(force_on_2);
}
void Muscle :: printMuscle()
{
    std::cout << "Period: " << period <<" Fraction contracted: " << fraction_contracted << " Ext: " << extended_length << " Con: " << contracted_length << " Phase: " << phase_shift << " k: " << k << " c: " << c << std::endl;
}
