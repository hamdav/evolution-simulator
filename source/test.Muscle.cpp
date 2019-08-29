#include <iostream>
#include "Muscle.h"
#include "Node.h"
#include "Vector.h"

using namespace std;


int main()
{
    Node n1 = Node();
    Node n2 = Node();

    Muscle bicep = Muscle(n1,n2,1,0,1,1,0,1,10);
    n1.setPos(Vector(0,0));
    n2.setPos(Vector(2,0));

    double dt = 0.05;
    for (double i = 0; i < 20; i+=dt)
    {
    bicep.addForceToNodes(i);

    cout << "0";
    //cout << (int)(10*(n2.getPos().x - n1.getPos().x));
    for (int j = 0; j < (int)(30*(n2.getPos().x - n1.getPos().x)); j++){
        cout << " ";
    }
            

    cout << "0" << endl;

    //cout << "n1 Pos: " << n1.getPos().x << n1.getPos().y << endl;
    //cout << "n2 Pos: " << n2.getPos().x << n2.getPos().y << endl;
    //cout << "n1 Vel: " << n1.getVel().x << n1.getVel().y << endl;
    //cout << "n2 Vel: " << n2.getVel().x << n2.getVel().y << endl;
    //cout << "n1 Acc: " << n1.getAcc().x << n1.getAcc().y << endl;
    //cout << "n2 Acc: " << n2.getAcc().x << n2.getAcc().y << endl;
    //cout << "n1 Force: " << n1.getForce().x << n1.getForce().y << endl;
    //cout << "n2 Force: " << n2.getForce().x << n2.getForce().y << endl;

    //cout << "Updating Acc" << endl;
    n1.updateAcc();
    n2.updateAcc();

    //cout << "n1 Pos: " << n1.getPos().x << n1.getPos().y << endl;
    //cout << "n2 Pos: " << n2.getPos().x << n2.getPos().y << endl;
    //cout << "n1 Vel: " << n1.getVel().x << n1.getVel().y << endl;
    //cout << "n2 Vel: " << n2.getVel().x << n2.getVel().y << endl;
    //cout << "n1 Acc: " << n1.getAcc().x << n1.getAcc().y << endl;
    //cout << "n2 Acc: " << n2.getAcc().x << n2.getAcc().y << endl;
    //cout << "n1 Force: " << n1.getForce().x << n1.getForce().y << endl;
    //cout << "n2 Force: " << n2.getForce().x << n2.getForce().y << endl;

    //cout << "Updating Vel" << endl;
    n1.updateVel(dt);
    n2.updateVel(dt);

    //cout << "n1 Pos: " << n1.getPos().x << n1.getPos().y << endl;
    //cout << "n2 Pos: " << n2.getPos().x << n2.getPos().y << endl;
    //cout << "n1 Vel: " << n1.getVel().x << n1.getVel().y << endl;
    //cout << "n2 Vel: " << n2.getVel().x << n2.getVel().y << endl;
    //cout << "n1 Acc: " << n1.getAcc().x << n1.getAcc().y << endl;
    //cout << "n2 Acc: " << n2.getAcc().x << n2.getAcc().y << endl;
    //cout << "n1 Force: " << n1.getForce().x << n1.getForce().y << endl;
    //cout << "n2 Force: " << n2.getForce().x << n2.getForce().y << endl;

    //cout << "Updating Pos" << endl;
    n1.updatePos(dt);
    n2.updatePos(dt);

    //cout << "n1 Pos: " << n1.getPos().x << n1.getPos().y << endl;
    //cout << "n2 Pos: " << n2.getPos().x << n2.getPos().y << endl;
    //cout << "n1 Vel: " << n1.getVel().x << n1.getVel().y << endl;
    //cout << "n2 Vel: " << n2.getVel().x << n2.getVel().y << endl;
    //cout << "n1 Acc: " << n1.getAcc().x << n1.getAcc().y << endl;
    //cout << "n2 Acc: " << n2.getAcc().x << n2.getAcc().y << endl;
    //cout << "n1 Force: " << n1.getForce().x << n1.getForce().y << endl;
    //cout << "n2 Force: " << n2.getForce().x << n2.getForce().y << endl;

    //cout << endl << endl;
    }

}
