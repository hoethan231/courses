#include "lab0.h"

myRectangle::myRectangle() {
    length = 0;
    width = 0;
}

myRectangle::myRectangle(int l, int w) {
    length = l;
    width = w;
}

void myRectangle::setLength(int len) {
    length = len;
}

void myRectangle::setWidth(int wid) {
    width = wid;
}

int myRectangle::getArea() {
    return length*width;
}

int myRectangle::getLength() {
    return length;
}

int myRectangle::getWidth() {
    return width;
}