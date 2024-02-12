#include <iostream>
#include "vector.cpp"
using namespace std;

int main() {

    Vector vect(5, 8);
    cout << "The Magnitude is: " << vect.getMag() << endl;
    cout << "The Direction is: " << vect.getDir() << endl;

    

    return 0;
}

