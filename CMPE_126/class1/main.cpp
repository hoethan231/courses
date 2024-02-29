#include <iostream>
#include "vector.cpp"
using namespace std;

int main() {

    Vector Vect(5, 8);
    Vect.print();
    cout << "The Magnitude is: " << Vect.getMag() << endl;
    cout << "The Direction is: " << Vect.getDir() << endl << endl;

    scalerVector sVect(2,3,2);
    sVect.print();
    cout << "The Magnitude of is: " << sVect.getMag() << endl;
    cout << "The Direction is: " << sVect.getDir() << endl << endl;

    Vector v1(1,2);
    Vector v2(3,4);
    Vector v3 = v1 + v2;
    cout << "V1 + V2 = " << v3.getMag() << endl;
    Vector v4 = v2 - v1;
    cout << "V2 - V1 = " << v4.getMag() << endl;



    return 0;
}

