#include <stdlib.h>
#include <iostream>
using namespace std;
class A 
{
    public:
        void bar ()
        {
            cout << rand()%100 << endl;
        }
};

int main () 
{
    for (int i = 0; i< 10; i++)
    {
        A bob = A();
        bob.bar();
    }
}

