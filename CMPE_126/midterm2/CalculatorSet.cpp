#include <iostream>
#include "CalculatorSet.h"

CalculatorSet::CalculatorSet() : current_calc_index(0), num_calcs(0) {}
CalculatorSet::~CalculatorSet() {
    current_calc_index = 0;
    num_calcs = 0;
}

void CalculatorSet::switchToCalc(unsigned int idx) {
    if(idx >= num_calcs) {
        std::cout << "That is not a valid index" << std::endl;
    }
    current_calc_index = idx;
}

void CalculatorSet::openTab(Calculator c) {
    calcs[num_calcs] = c;
    num_calcs++;
}

void CalculatorSet::closeCurrentCalc() {
    
    if(num_calcs == 0) {
        std::cout << "There are no calculators in the set" << std::endl;
        return;
    }

    for(int i=current_calc_index; i<num_calcs; i++){
        calcs[i] = calcs[i+1];
    }

}

unsigned int CalculatorSet::getCurrentCalcIndex() {
    return current_calc_index;
}

unsigned int CalculatorSet::getNumCalcs() {
    return num_calcs;
}

Calculator* CalculatorSet::getCurrentCalc() {
    return &calcs[current_calc_index];
}
