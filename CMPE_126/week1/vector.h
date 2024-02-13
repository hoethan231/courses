#pragma once

class Vector {

    private:
        int direction, magnitude;
        void update();

    protected:
        int scaler;

    public:
        int x, y;

        Vector();
        Vector(int, int);
        void setX(int);
        void setY(int);
        double getMag();
        double getDir();
        virtual void print();

};

class scalerVector: public Vector {

    public: 
        scalerVector(int, int, int);
        void print();
        
};