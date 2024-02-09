#include "date.cpp"
#include <iostream>
using namespace std;

int main(){

    Date d1;
    Date d2(3,15,2024);
    DateOfBirth d3(5,10,1970);
    DateOfBirth d4(d1);
    cout << d1;
    cout << d3 << d4;
    cout << d3.getAge();


    return 0;
}