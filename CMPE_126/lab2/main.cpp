#include "date.cpp"
#include "passenger.cpp"
#include <iostream>
using namespace std;

int main(){

    Date d1;
    Date d2(3,15,2024);
    DateOfBirth d3(5,10,1970);
    DateOfBirth d4(d1);
    cout << d1;
    cout << d3 << d4;
    cout << d3.getAge() << endl;

    string first_name = "John";
    string last_name = "Smith";
    DateOfBirth d(5,10,1970);
    Passenger p1(first_name, last_name, d);
    cout << p1;
    p1.setFareDiscount(0.25);



    return 0;
}