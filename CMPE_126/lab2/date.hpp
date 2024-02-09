#ifndef Date_HPP_
#define Date_HPP_
#include <iostream>
using namespace std;

class Date {

    private:
        int day;
        int month;
        int year;

    public:
        Date();
        Date(int, int, int);
        friend ostream& operator<<(ostream&, Date);


        

};

class DateOfBirth : public Date {

    public:
        getAge();

};
#endif