#include "passenger.hpp"

Passenger::Passenger(string first, string last, DateOfBirth DOB) {
    
    setFirst(first);
    setLast(last);
    setDOB(DOB);
    setFareDiscount(0.0);

}

string Passenger::getFirst() {
    return this->first_name;
}

string Passenger::getLast() {
    return this->last_name;
}

DateOfBirth Passenger::getDOB() {
    return this->DOB;
}

double Passenger::getFareDiscount() {
    return this->fare_discount;
}

void Passenger::setFirst(string first) {
    this->first_name = first;
}

void Passenger::setLast(string last) {
    this->last_name = last;
}

void Passenger::setDOB(DateOfBirth DOB) {
    this->DOB = DOB;
}

void Passenger::setFareDiscount(double discount) {
    if(discount > 1.0 || discount < 0.0) {
        cout << "Discount must be a percent between 0 and 1" << endl;
    }
    else {
        this->fare_discount = discount;
    }
}

ostream& operator<<(ostream& os, Passenger pass) {
    os << pass.first_name << " " << pass.last_name << ", born on " << pass.DOB << endl;
    return os;
}

