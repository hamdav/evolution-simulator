// Muscle class
using System;

namespace Creature
{
    public class Muscle
    {
        public Muscle(int id, Node node1, Node node2, Muscle m)
        {
            this.id = id;
            this.node1 = node1;
            this.node2 = node2;

            Random rand = new Random();
            double mutationFactor = 0.1; 

            double dp  = (rand.NextDouble()-1/2)*mutationFactor;
            double newPer = m.period + dp;
            this.period = newPer <= 10 && newPer >= 1 ? newPer : m.period;
            
            // Add df only if that does not bring the fraction over 1 or below 0
            double df  = (rand.NextDouble()-1/2)*mutationFactor;
            double newfrac = m.fractionContracted + df ;
            this.fractionContracted = newfrac <= 1 && newfrac >= 0 ? newfrac : m.fractionContracted;

            // Add dp only if that does not bring the phaseShift over 1 or below 0
            double dph  = (rand.NextDouble()-1/2)*mutationFactor;
            double newphase = m.phaseShift + dph ;
            this.phaseShift = newphase <= 1 && newphase >= 0 ? newphase : m.phaseShift;

            this.k = m.k;
            this.c = m.c;
        }

        public Muscle(int id, Node node1, Node node2)
        {
            this.id = id;
            this.node1 = node1;
            this.node2 = node2;

            Random rand = new Random();
            this.period = 1+rand.NextDouble() * 9;
            this.fractionContracted = rand.NextDouble();
            this.phaseShift = rand.NextDouble();
            //TODO make these random as well. First, find suitable intervals though
            this.k = 1;
            this.c = 1;

        }
        private int id { get; }
        private Node node1 { get; }
        private Node node2 { get; }
        // Total period of motion, number between 0 and 10 seconds
        private double period { get; }
        // Fraction of period when muscle is contracted, number between 0 and 1. The "first" fractionContracted of the period (not accounted for phase shift) is contracted. 
        private double fractionContracted { get; }
        // At witch point in the cycle does the muscle begin. Number between 0 and 1
        private double phaseShift { get; }
        private double lengthContracted;
        private double lengthExtended;

        // Spring constant
        private double k { get; }
        // Dampening constant TODO SHOULD IT BE CRITICALLY DAMPENED?
        private double c { get; }

        public void AddForceToNodes(double t){
            bool contracted = IsContracted(t);
            Vector forceOn1 = ForceOnNode1(contracted);

            node1.addForce(forceOn1);
            // Newton's third law
            node2.addForce(-1*forceOn1);

        }
        public Vector ForceOnNode1(bool contracted){
            // Positionvector from 1 to 2
            Vector relativePos = node2.position - node1.position;
            Vector normedRelPos = relativePos/relativePos.Length;

            // Magnitude is negative if spring force on node 1 is away from 2
            double springForceMagnitude = k*(relativePos.Length - (contracted ? lengthContracted : lengthExtended));
            Vector springForce = normedRelPos*springForceMagnitude;

            // Velocity of node 1 relative to node 2
            Vector relativeVel = node1.velocity - node2.velocity;
            
            // Magnitude is negative if dampened force on node 1 is away node 2
            double dampenedForceMagnitude = -c*Vector.Multiply(relativeVel,normedRelPos);
            Vector dampenedForce = normedRelPos*dampenedForceMagnitude;

            return springForce+dampenedForce;

        }
        private bool IsContracted(double t){
            double phaseShiftedT = t - phaseShift;
            double internalT = phaseShiftedT % period;
            double phase = internalT/period;

            return phase <= fractionContracted;
        }


    }
}