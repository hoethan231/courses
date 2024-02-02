#include <iostream>
#include "time.cpp"
using namespace std;

int main() {

    Time t1();
    Time t2(3);
    Time t3(5,10);
    int minute = 10;
    cout << t1;
    cout << t2 << t3;
    cout << t2+t3;
    t1 = t3+minute;

    return 0;
}