#include "Node.h"
#include "Vector.h"
#include <iostream>

using namespace std;
int main()
{
    Node n1 = Node();
    Node n2 = Node(1,1);
    Node n3 = n2.child();

    n1.setPos(Vector(0,0));
    n1.setVel(Vector(1,1));
    cout << "Pos: " << n1.getPos().x << n1.getPos().y << endl;
    n1.updatePos(1);
    cout << "Pos: " << n1.getPos().x << n1.getPos().y << endl;
    cout << "Vel: " << n1.getVel().x << n1.getVel().y << endl;
    n1.addForce(Vector(1,1));
    n1.updateAcc();
    n1.updateVel(1);
    cout << "Vel: " << n1.getVel().x << n1.getVel().y << endl;


}
