#ifndef Date_HPP_
#define Date_HPP_
#include <iostream>
using namespace std;
class Date {

    protected:
        int month;
        int day;
        int year;

    public:
        Date();
        Date(int, int, int);
        int getDay();
        int getMonth();
        int getYear();
        void setDay(int);
        void setMonth(int);
        void setYear(int);
        friend ostream& operator<<(ostream&, Date);

};

class DateOfBirth : public Date {

    private:
        Date date;
    public:
        DateOfBirth(int, int, int);

        DateOfBirth(Date);
        int getAge();

};

Date today(2,9,2024);

#endif