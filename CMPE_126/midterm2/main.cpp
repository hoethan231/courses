//============================================================================
// Name        : main.cpp
// Author      : Mahima
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Calculator.cpp"
#include "CalculatorSet.cpp"
using namespace std;


int main(){
	try{
		Calculator c;
		c.add(1);
		c.add(14);
		c.subtract(6);
		c.add(4);
		// Result is 13
		cout << "Result: " << c.getResult() << endl;

		c.undo(); // Expects 9
		cout << "After undo: " << c.getResult() << endl;

		c.undo(); // Expects 15
		cout << "After undo: " << c.getResult() << endl;

		c.redo(); // Expects 9
		cout << "After redo: " << c.getResult() << endl;

		c.redo(); // Expects 13
		cout << "After redo: " << c.getResult() << endl;

		// c.redo(); // Uncommenting this statement should throw an error that no more redoes are possible
		cout << "After redo: " << c.getResult() << endl;

		c.undo(); // Expects 9
		cout << "After undo: " << c.getResult() << endl;
		
		c.printAllOperations(); //Prints all the operations from the beginning
		// Expects Add 1. Add 14. Subtract 6. Add 4. Undo. Undo. Redo. Redo. Undo.

	}
	catch(const char* c){
		cout << c << endl;
	}
	// try{
	// 	CalculatorSet calculator;
	// 	Calculator c;
	// 	c.add(1);
	// 	c.add(14);
	// 	c.subtract(6);
	// 	c.add(4);
	// 	calculator.openTab(c);
	// 	calculator.getCurrentCalc()->printAllOperations();
	// 	cout << "Current tab index: " << calculator.getCurrentCalcIndex() << endl;
	// 	cout << "Num Tabs: " << calculator.getNumCalcs() << endl;

	// 	Calculator c2;
	// 	calculator.openTab(c2);
	// 	calculator.switchToCalc(1);
	// 	cout << "Current tab index: " << calculator.getCurrentCalcIndex() << endl;
	// 	cout << "Num Tabs: " << calculator.getNumCalcs() << endl;

	// 	calculator.getCurrentCalc()->add(2);
	// 	calculator.getCurrentCalc()->add(5);
	// 	calculator.getCurrentCalc()->undo();
	// 	calculator.getCurrentCalc()->printAllOperations();

	// }
	// catch(const char* c){
	// 	cout << c << endl;
	// }
	// /*********************************************************************************/
	// return 0;
}
