#include <iostream>
#include "./box.hpp"
using namespace std;

Box::Box() : name("Box"), weight(ImperialWeight(0,0)) {}

Box::Box(string n, ImperialWeight w) : name(n), weight(w) {}

string Box::getName() {
    return this->name;
}

ImperialWeight Box::getWeight() {
    return this->weight;
}

void Box::setName(string n) {
    this->name = n;
} 

void Box::setWeight(ImperialWeight w) {
    this->weight = w;
}

bool Box::operator>(Box b) {
    if (this->weight.getPounds() == b.getWeight().getPounds()) {
        return this->weight.getOunces() > b.getWeight().getOunces();
    }
    return this->weight.getPounds() > b.getWeight().getPounds();
}

bool Box::operator<(Box b) {
    if (this->weight.getPounds() == b.getWeight().getPounds()) {
        return this->weight.getOunces() < b.getWeight().getOunces();
    }
    return this->weight.getPounds() < b.getWeight().getPounds();
}

bool Box::operator>=(Box b) {
    if (this->weight.getPounds() == b.getWeight().getPounds()) {
        return this->weight.getOunces() >= b.getWeight().getOunces();
    }
    return this->weight.getPounds() >= b.getWeight().getPounds();
}

bool Box::operator<=(Box b) {
    if (this->weight.getPounds() == b.getWeight().getPounds()) {
        return this->weight.getOunces() <= b.getWeight().getOunces();
    }
    return this->weight.getPounds() <= b.getWeight().getPounds();
}
