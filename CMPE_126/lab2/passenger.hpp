#ifndef Passenger_HPP_
#define Passenger_HPP_
#include "date.hpp"

class Passenger {

    private:
        string first_name;
        string last_name;
        DateOfBirth DOB;
        double fare_discount;
    
    public:
        Passenger(string, string, DateOfBirth);
        string getFirst();
        string getLast();
        DateOfBirth getDOB();
        double getFareDiscount();
        void setFareDiscount(double);
        void setFirst(string);
        void setLast(string);
        void setDOB(DateOfBirth);
        friend ostream& operator<<(ostream&, Passenger);

};

#endif