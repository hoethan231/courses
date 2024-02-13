#include <iostream>
#include "vector.cpp"
using namespace std;

int main() {

    Vector Vect(5, 8);
    cout << "The Magnitude is: " << Vect.getMag() << endl;
    cout << "The Direction is: " << Vect.getDir() << endl;

    scalerVector sVect(2,3,2);
    cout << "The Magnitude is: " << sVect.getMag() << endl;
    cout << "The Direction is: " << sVect.getDir() << endl;

    Vect.print();
    sVect.print();

    return 0;
}

