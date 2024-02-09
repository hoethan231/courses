#include "date.hpp"
#include <iostream>
using namespace std;

Date::Date() {

    setDay(1);
    setMonth(1);
    setYear(1900);

}

Date::Date(int month, int day, int year){

    setDay(day);
    setMonth(month);
    setYear(year);

}

int Date::getDay() {
    return this->day;
}

int Date::getMonth() {
    return this->month;
}

int Date::getYear() {
    return this->year;
}

void Date::setDay(int day) {
    if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) {
        cout << "April, June, September, and November have only 30 days." << endl;
        this->day = 1;
    }
    else if (month == 2 && year % 4 != 0 && day > 28) {
        cout << "February in non-leap years has only 28 days." << endl;
        this->day = 1;
    }
    else if (day > 31 || day < 1) {
        cout << "Enter a day between 1 and 31" << endl;
        this->day = 1;
    }
    else {
        this->day = day;
    }
}

void Date::setMonth(int month) {
    if(month > 12 || month < 1) {
        cout << "Enter a month between 1 and 12" << endl;
        this->month = 1;
    }
    else {
        this->month = month;
    }
}

void Date::setYear(int year) {
    if(year > 2024 || year < 1900) {
        cout << "Enter a year between 1900 and 2024" << endl;
        this->year = 1900;
    }
    else {
        this->year = year;
    }
}

ostream& operator<<(ostream& os, Date date) {
    os << date.month << "/" << date.day << "/" << date.year << endl;
    return os;
}

DateOfBirth::DateOfBirth() : Date() {}

DateOfBirth::DateOfBirth(int m, int d, int y) : Date(m, d, y) {}

DateOfBirth::DateOfBirth(Date date) : Date(date) {}

int DateOfBirth::getAge() {
    return today.getYear() - getYear();
}
