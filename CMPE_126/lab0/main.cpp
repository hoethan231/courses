#include <iostream>
#include "lab0.h"
using namespace std;

int main() {

    myRectangle rec(10, 15);
    cout << "The area is: " << rec.getArea() << endl;

    rec.setLength(20);
    rec.setWidth(20);
    cout << "The new length is: " << rec.getLength() << endl;
    cout << "The new width is: " << rec.getWidth() << endl;
    cout << "The area is: " << rec.getArea() << endl;

}