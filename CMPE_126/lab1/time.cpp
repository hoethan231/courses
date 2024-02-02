#include "time.h"
#include <iostream>
using namespace std;

Time::Time() {
    hour = 0;
    minute = 0;
}

Time::Time(int hour) {
    if(hour < 0 || hour > 24) {
        cout << "Hour should be between 0 and 24" << endl;
        this->hour = 0;
    }
    else {
        this->hour = hour;
        this->minute = 0;
    }
}

Time::Time(int hour, int minute) {
    if(hour < 0 || hour > 23) {
        cout << "Hours should be between 0 and 23" << endl;
        this->hour = 0;
    }
    else {
        this->hour = hour;
        this->minute = 0;
    }
    if(minute < 0 || minute > 59) {
        cout << "Minutes should be between 0 and 59" << endl;
        this->minute = 0;
    }
    else {
        this->minute = minute;
    }
}

Time Time::operator+(Time time2) {
    Time temp;
    temp.hour, temp.minute = (this->hour + time2.hour) % 24, (this->minute + time2.minute) % 60;
    return temp;
}

Time Time::operator+(int min) {
    Time temp;
    temp.hour, temp.minute = (this->hour + (min / 60)) % 24, (this->minute + (min % 60)) % 60;
    return temp;
}

Time Time::operator=(Time other) {
    this->hour = other.hour;
    this->minute = other.minute;
    return *this;
}

ostream& operator<<(ostream& os, Time time) {
    os << time.hour << ":" << time.minute << endl;
    return os;
}