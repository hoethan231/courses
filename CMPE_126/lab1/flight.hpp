#ifndef Flight_HPP_
#define Flight_HPP_

#include "time.hpp"

class Flight {

    private:
        string src;
        string dest;
        Time DepartureTime;

    public:
        Flight(string, string);
        void setDepartureTime(int, int);
        void setDepartureTime(Time);
        friend ostream& operator<<(ostream&, const Flight&);


};
#endif