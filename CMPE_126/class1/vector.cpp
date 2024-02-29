#include <iostream>
#include "vector.h"
#include <cmath>
using namespace std;

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

int Vector::getX() {
    return this->x;
}

int Vector::getY() {
    return this->y;
}

void Vector::setX(int X) {
    this->x = X;
}

void Vector::setY(int Y) {
    this->y = Y;
}

double Vector::getMag() {
    return sqrt(x*x + y*y);
}

double Vector::getDir() {
    return atan(y/x);
}

void Vector::print() {
    cout << "This is a Vector" << endl;
}

Vector operator+(Vector v1, Vector v2) {
    int x = v1.getX() + v2.getX();
    int y = v1.getY() + v2.getY();
    return Vector(x,y);
}

Vector operator-(Vector v1, Vector v2) {
    int x = v1.getX() - v2.getX();
    int y = v1.getY() - v2.getY();
    return Vector(x,y);
}

scalerVector::scalerVector(int x, int y, int scaler) {
    this->x = x;
    this->y = y;
    this->scaler = scaler;
}

void scalerVector::print() {
    cout << "This is a Scaler Vector" << endl;
}