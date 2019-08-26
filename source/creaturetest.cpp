
#include <iostream>
#include "Creature.h"
using namespace std;

int main ()
{
    srand(100);
    Creature bob = Creature();
    cout << bob.getNumber();
    Creature anna = Creature();
    cout << anna.getNumber();
    Creature charlie = anna.offspring();
    cout << charlie.getNumber();
    for (int i = 0; i< 100; i++) 
    {
        Creature tmp = anna.offspring();
        cout << tmp.getNumber();
    }
    return 0;
}
