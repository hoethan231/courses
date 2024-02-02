#include "vector.h"
#include <cmath>

Vector::Vector() {
    x = 0;
    y = 0;
}

Vector::Vector(int X, int Y) {
    x = X;
    y = Y;
}

void Vector::update() {
    this->x = x;
    this->y = y;
}

void Vector::setX(int X) {
    x = X;
    update();
}

void Vector::setY(int Y) {
    y = Y;
    update();
}

double Vector::getMag() {
    return sqrt(x*x + y*y);
}

double Vector::getDir() {
    return atan(y/x);
}
