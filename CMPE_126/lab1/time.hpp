#ifndef Time_HPP_
#define Time_HPP_

#include <ostream>
using namespace std;
class Time {

    private:
        int hour;
        int minute;

    public:
        Time();
        Time(int);
        Time(int, int);
        Time operator+(const Time);
        Time operator+(int);
        Time& operator=(const Time&);
        friend ostream& operator<<(ostream&, const Time&);

};
#endif