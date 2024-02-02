#include <iostream>
#include "time.hpp"
#include "flight.hpp"
using namespace std;

int main() {

    Time t1{};
    Time t2(3);
    Time t3(5,10);
    int minute = 10;
    cout << t1;
    cout << t2 << t3;
    cout << t2+t3;
    t1 = t3+minute;

    string src = "SFO";
    string dest = "LAX";
    Flight f1(src, dest);
    f1.setDepartureTime(13,45);
    Time t(6,30);
    f1.setDepartureTime(t);
    cout << f1;

    return 0;
}