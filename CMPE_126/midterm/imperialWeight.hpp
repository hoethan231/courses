#pragma once
#include <iostream>
using namespace std;

class ImperialWeight {

    private:
        int pounds;
        int ounces;

    public:
        ImperialWeight();
        ImperialWeight(int, int);
        int getPounds() const;
        int getOunces() const;
        void setPounds(int);
        void setOunces(int);
        ImperialWeight operator+(const ImperialWeight);
        friend ostream& operator<<(ostream&, ImperialWeight);

};