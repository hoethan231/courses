#include "flight.hpp"

Flight::Flight(string SRC, string DEST) : src(SRC), dest(DEST), DepartureTime(0,0) {}

void Flight::setDepartureTime(int hour, int minute) {
    Time temp(hour, minute);
    DepartureTime = temp;
}
void Flight::setDepartureTime(Time time) {
    DepartureTime = time;
}

ostream& operator<<(ostream& os, const Flight& flight) {
    os << "Your flight from " << flight.src << "to " << flight.dest << " will be departing at " << flight.DepartureTime << endl;
    return os;
}