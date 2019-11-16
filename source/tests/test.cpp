
#include <iostream>
using namespace std;

int main ()
{
    long var[5] = {1,2,3,4,5};
    cout << "Memory location of var: ";
    cout << var << endl;
    cout << "Value: ";
    cout << *var << endl;
    cout << "Memory location of var + 2: ";
    cout << var +2 << endl;
    cout << "Value: ";
    cout << *(var +2) << endl;
    cout << "Changing to 10" << endl;
    *(var + 2) = 10;
    cout << "Value: ";
    cout << *(var +2) << endl;
    cout << "Value of one past the array: ";
    cout << *(var+5) << endl;
    cout << *(var+6) << endl;
    cout << *(var+7) << endl;
    int i = 5 / 2;
    cout << i << endl;
    return 0;
}
