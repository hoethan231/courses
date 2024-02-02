#ifndef Time_HPP_
#define Time_HPP_

class Time {

    private:
        int hour;
        int minute;

    public:
        Time();
        Time(int);
        Time(int, int);
        Time operator+(Time);
        Time operator+(int);
        Time operator=(Time);
        friend ostream& operator<<(ostream&, Time);

};
#endif