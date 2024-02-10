#include "flight.hpp"

Flight::Flight(string SRC, string DEST, double baseFare) : src(SRC), dest(DEST), DepartureTime(0,0), baseFare(baseFare), dateOfTravel() {}

void Flight::setDepartureTime(int hour, int minute) {
    Time temp(hour, minute);
    DepartureTime = temp;
}
void Flight::setDepartureTime(Time time) {
    DepartureTime = time;
}

void Flight::setDateOfTravel(Date d) {
    this->dateOfTravel = d;
}

double Flight::getBaseFare() {
    return baseFare;
}

ostream& operator<<(ostream& os, const Flight& flight) {
    os << "Your flight from " << flight.src << "to " << flight.dest << " will be departing at " << flight.DepartureTime << endl;
    return os;
}