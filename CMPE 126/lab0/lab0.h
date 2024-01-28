#ifndef lab0_HPP_
#define lab0_HPP_


class myRectangle {

    private:
        int width;
        int length;

    public:
        myRectangle();
        myRectangle(int, int);
        void setLength(int);
        void setWidth(int);
        int getArea();
        int getWidth();
        int getLength();

};
#endif