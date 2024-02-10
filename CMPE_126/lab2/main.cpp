#include <iostream>
#include "date.cpp"
#include "passenger.cpp"
#include "flight.cpp"
#include "./lab1/flight.cpp"
#include <iostream>
using namespace std;

int main(){

    //Task 1
    Date d1;
    Date d2(3,15,2024);
    DateOfBirth d3(5,10,1970);
    DateOfBirth d4(d1);
    cout << d1;
    cout << d3 << d4;
    cout << d3.getAge() << endl;

    //Task 2
    string first_name = "John";
    string last_name = "Smith";
    DateOfBirth d(5,10,1970);
    Passenger p1(first_name, last_name, d);
    cout << p1;
    p1.setFareDiscount(0.25);

    //Importing flight 
    Time t1{};
    Time t2(3);
    Time t3(5,10);
    int minute = 10;
    
    string src = "SFO";
    string dest = "LAX";
    Flight f1(src, dest, 235.85, d2);
    f1.setDepartureTime(13,45);

    //Task 3
    Ticket ticket(p1, f1);
    cout << ticket << endl;
    p1.setFareDiscount(0.5);
    ticket.updateFare();
    cout << ticket.getFare();
    Date d5(3,18,2024);
    Flight f2("SFO", "LAS", d5);
    ticket.updateFlight(f2);

    return 0;
}