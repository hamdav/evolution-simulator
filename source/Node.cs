// Node class

using System;

namespace Creature
{
    public class Node
    {
        public Node(Node n, int id)
        {
            this.position = 0;
            this.velocity = 0;
            this.acceleration = 0;
            this.force = 0;
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
            
            this.position = 0;
            this.velocity = 0;
            this.acceleration = 0;
            this.force = 0;
            this.id = id;
            this.mu = rand.NextDouble();
            this.mass = rand.NextDouble();
        }
        private double position { get; }
        private double velocity { get; set; }
        private double acceleration { get; }
        private double force { get; set; }
        private int id { get; }
        private double mu;
        private double mass;
    }
}





