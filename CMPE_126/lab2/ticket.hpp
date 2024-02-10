#ifndef Ticket_HPP_
#define Ticket_HPP_
#include "passenger.hpp"
#include "../lab1/flight.hpp"

class Ticket {

    private:
        Passenger passenger;
        Flight flight;
        double passengerFare;

    public:
        Ticket(Passenger, Flight);
        Passenger getPassenger();
        Flight getFlight();
        double getFare();
        void updateFare();
        void updateFlight(Flight);
        friend ostream& operator<<(ostream&, Ticket);

};

#endif