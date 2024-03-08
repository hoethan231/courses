#pragma once
#include <iostream>
#include "./imperialWeight.hpp"
using namespace std;

class Box {

    private:
        string name;
        ImperialWeight weight;

    public:
        Box();
        Box(string, ImperialWeight);
        string getName();
        ImperialWeight getWeight();
        void setName(string);
        void setWeight(ImperialWeight);
        bool operator>(Box);
        bool operator<(Box);
        bool operator>=(Box);
        bool operator<=(Box);
        
};