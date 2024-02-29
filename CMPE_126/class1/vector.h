#pragma once

class Vector {

    private:
        int direction, magnitude;
        void update();

    protected:
        int scaler;
        int x;
        int y;

    public:
        Vector();
        Vector(int, int);
        int getX();
        int getY();
        void setX(int);
        void setY(int);
        double getMag();
        double getDir();
        virtual void print();
        friend Vector operator+(Vector, Vector);
        friend Vector operator-(Vector, Vector);
};

class scalerVector: public Vector {

    public: 
        scalerVector(int, int, int);
        void print();
        
};