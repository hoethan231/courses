#include "date.hpp"
#include <iostream>
using namespace std;

Date::Date(){

    this->day = 1;
    this->month = 1;
    this->year = 1900;

}

Date::Date(int day, int month, int year){

    this->day = day;
    this->month = month;
    this->year = year;

}

ostream& operator<<(ostream& os, Date date) {
    os << date.month << "/" << date.day << "/" << date.year << endl;
    return os;
}

