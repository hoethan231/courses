#pragma once

class Vector {

    private:
        int direction, magnitude;
        void update();

    public:
        int x, y;

    Vector();
    Vector(int, int);
    void setX(int);
    void setY(int);
    double getMag();
    double getDir();

};