#include <iostream>
#include "./imperialWeight.hpp"
using namespace std;

ImperialWeight::ImperialWeight() : pounds(0), ounces(0) {}

ImperialWeight::ImperialWeight(int p, int o) {
    setPounds(p);
    setOunces(o);
}

int ImperialWeight::getPounds() const {
    return this->pounds;
}

int ImperialWeight::getOunces() const {
    return this->ounces;
}

void ImperialWeight::setPounds(int p) {
    if(p < 0) {
        cout << "Pounds must be positive. Default set to 0" << endl;
        this->pounds = 0;
    }
    this->pounds = p;
}

void ImperialWeight::setOunces(int o) {
    if(o < 0 || o > 15) {
    cout << "Ounces must be between 0-15. Default set to 0" << endl;
    this->ounces = 0;
    }
    this->ounces = o;
}

ImperialWeight ImperialWeight::operator+(ImperialWeight w1) {
    ImperialWeight temp{};
    temp.setPounds(w1.getPounds() + this->pounds);
    
    int totalOunces = w1.getOunces() + this->ounces;
    if (totalOunces >= 16) {
        temp.setPounds(temp.getPounds() + totalOunces / 16);
        temp.setOunces(totalOunces % 16);
    } else {
        temp.setOunces(totalOunces);
    }

    return temp;
}

ostream& operator<<(ostream& os, ImperialWeight weight) {
    os << weight.getPounds() << " lbs " << weight.getOunces() << " oz ";
    return os;
}