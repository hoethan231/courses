#ifndef Flight_HPP_
#define Flight_HPP_

#include "time.hpp"

class Flight {

    private:
        string src;
        string dest;
        Time DepartureTime;
        double baseFare;
        Date dateOfTravel;

    public:
        Flight(string, string, double);
        void setDepartureTime(int, int);
        void setDepartureTime(Time);
        void setDateOfTravel(Date);
        double getBaseFare();
        friend ostream& operator<<(ostream&, const Flight&);


};
#endif