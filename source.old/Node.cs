// Node class

using System;

namespace Creature
{
    public class Node
    {
        public Node(Node n, int id)
        {
            this.position = new Vector(0,0);
            this.velocity = new Vector(0,0);
            this.acceleration =  new Vector(0,0);
            this.force = new Vector(0,0);
            this.id = id;

            Random rand = new Random();
            double mutationFactor = 0.1; 
            
            double dmu = rand.NextDouble()*mutationFactor - mutationFactor/2;
            this.mu = n.mu + dmu;

            double dmass = rand.NextDouble()*mutationFactor - mutationFactor/2;
            this.mass = n.mass + dmass;
        }
        public Node(int id){
            Random rand = new Random();
            
            this.position = new Vector(0,0);
            this.velocity = new Vector(0,0);
            this.acceleration = new Vector(0,0);
            this.force = new Vector(0,0);
            this.id = id;
            this.mu = rand.NextDouble();
            this.mass = 1;

            //Remember to make mass nonzero when variable mass is implemented, maybe have a minimum mass?
            //this.mass = rand.NextDouble();
        }
        private Vector position { get; }
        private Vector velocity { get; set; }
        private Vector acceleration { get; }
        private Vector force { get; set; }
        private int id { get; }
        private double mu;
        private double mass;
        public void addForce(Vector f){
            force = force + f;
        }
    }
}





