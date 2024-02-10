#include "ticket.hpp"


Ticket::Ticket(Passenger p, Flight f) : passenger(p), flight(f), passengerFare(0.0) {}

Passenger Ticket::getPassenger() {
    return passenger;
}

Flight Ticket::getFlight() {
    return flight;
}

double Ticket::getFare() {
    return passengerFare;
}

void Ticket::updateFare() {
    this->passengerFare = this->flight.getBaseFare()*this->passenger.getFareDiscount();
}

void Ticket::updateFlight(Flight f) {
    this->flight = f;
}

ostream& operator<<(ostream& os, Ticket t) {
    os << t.getFlight() << "for " << t.getPassenger();
    return os;
}