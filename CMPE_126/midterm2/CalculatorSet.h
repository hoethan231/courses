#ifndef CALCULATORSET_H_
#define CALCULATORSET_H_
#include "Calculator.h"

class CalculatorSet {
public:
	CalculatorSet();
	void switchToCalc(unsigned int); 	// Switch to calculator with index specified
	// ^ Needs to check if the index is valid
	void openTab(Calculator); 			// Open a new calculator
	void closeCurrentCalc();				// Closes the current calculator
	unsigned int getCurrentCalcIndex();  // Returns the index of the current calculator
	unsigned int getNumCalcs();			// Returns the number of open calculators
	Calculator* getCurrentCalc();			// Returns the current Calculator object
	~CalculatorSet();
private:
	Calculator calcs[32]; //Temporarily created a static array of maximum of 32 calculators
	unsigned int current_calc_index; // Index of the current calculator
	unsigned int num_calcs; // Number of open calculators
};

#endif /* CALCULATORSET_H_ */
